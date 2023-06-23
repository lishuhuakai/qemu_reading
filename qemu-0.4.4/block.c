/*
 * QEMU System Emulator block driver
 * 
 * Copyright (c) 2003 Fabrice Bellard
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <getopt.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <malloc.h>
#include <termios.h>
#include <sys/poll.h>
#include <errno.h>
#include <sys/wait.h>
#include <netinet/in.h>

#include "vl.h"

#define NO_THUNK_TYPE_SIZE
#include "thunk.h"

struct BlockDriverState {
    int fd; /* if -1, only COW mappings */
    int64_t total_sectors; /* 块的个数，每512个字节为1块 */
    int read_only; /* 是否只读 */

    uint8_t *cow_bitmap; /* if non NULL, COW mappings are used first */
    uint8_t *cow_bitmap_addr; /* mmap address of cow_bitmap */
    int cow_bitmap_size;
    int cow_fd;
    int64_t cow_sectors_offset;
    char filename[1024]; /* 文件名称 */
};
/* 块设备驱动
 * @param 
 */
BlockDriverState *bdrv_open(const char *filename, int snapshot)
{
    BlockDriverState *bs;
    int fd, cow_fd;
    int64_t size;
    char template[] = "/tmp/vl.XXXXXX";
    struct cow_header_v2 cow_header;
    struct stat st;

    bs = malloc(sizeof(BlockDriverState));
    if(!bs)
        return NULL;
    bs->read_only = 0;
    bs->fd = -1;
    bs->cow_fd = -1;
    bs->cow_bitmap = NULL;
    strcpy(bs->filename, filename);

    /* open standard HD image */
    fd = open(filename, O_RDWR | O_LARGEFILE);
    if (fd < 0) {
        /* read only image on disk */
        fd = open(filename, O_RDONLY | O_LARGEFILE);
        if (fd < 0) {
            perror(filename);
            goto fail;
        }
        if (!snapshot)
            bs->read_only = 1;
    }
    bs->fd = fd;

    /* see if it is a cow image */
    if (read(fd, &cow_header, sizeof(cow_header)) != sizeof(cow_header)) {
        fprintf(stderr, "%s: could not read header\n", filename);
        goto fail;
    }
    if (cow_header.magic == htonl(COW_MAGIC) &&
        cow_header.version == htonl(COW_VERSION)) {
        /* cow image found */
        size = cow_header.size;
#ifndef WORDS_BIGENDIAN
        size = bswap64(size);
#endif    
        bs->total_sectors = size / 512;

        bs->cow_fd = fd;
        bs->fd = -1;
        if (cow_header.backing_file[0] != '\0') {
            if (stat(cow_header.backing_file, &st) != 0) {
                fprintf(stderr, "%s: could not find original disk image '%s'\n", filename, cow_header.backing_file);
                goto fail;
            }
            if (st.st_mtime != htonl(cow_header.mtime)) {
                fprintf(stderr, "%s: original raw disk image '%s' does not match saved timestamp\n", filename, cow_header.backing_file);
                goto fail;
            }
            fd = open(cow_header.backing_file, O_RDONLY | O_LARGEFILE);
            if (fd < 0)
                goto fail;
            bs->fd = fd;
        }
        /* mmap the bitmap */
        bs->cow_bitmap_size = ((bs->total_sectors + 7) >> 3) + sizeof(cow_header);
        bs->cow_bitmap_addr = mmap(get_mmap_addr(bs->cow_bitmap_size), 
                                   bs->cow_bitmap_size, 
                                   PROT_READ | PROT_WRITE,
                                   MAP_SHARED, bs->cow_fd, 0);
        if (bs->cow_bitmap_addr == MAP_FAILED)
            goto fail;
        bs->cow_bitmap = bs->cow_bitmap_addr + sizeof(cow_header);
        bs->cow_sectors_offset = (bs->cow_bitmap_size + 511) & ~511;
        snapshot = 0;
    } else {
        /* standard raw image */
        size = lseek64(fd, 0, SEEK_END);
        bs->total_sectors = size / 512;
        bs->fd = fd;
    }

    if (snapshot) { /* 快照 */
        /* create a temporary COW file */
        cow_fd = mkstemp(template);
        if (cow_fd < 0)
            goto fail;
        bs->cow_fd = cow_fd;
        unlink(template);
        
        /* just need to allocate bitmap */
        bs->cow_bitmap_size = (bs->total_sectors + 7) >> 3;
        /* 在内存之中实现映射 */
        bs->cow_bitmap_addr = mmap(get_mmap_addr(bs->cow_bitmap_size), 
                                   bs->cow_bitmap_size, 
                                   PROT_READ | PROT_WRITE,
                                   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (bs->cow_bitmap_addr == MAP_FAILED)
            goto fail;
        bs->cow_bitmap = bs->cow_bitmap_addr;
        bs->cow_sectors_offset = 0;
    }
    
    return bs;
 fail:
    bdrv_close(bs);
    return NULL;
}

void bdrv_close(BlockDriverState *bs)
{
    /* we unmap the mapping so that it is written to the COW file */
    if (bs->cow_bitmap_addr)
        munmap(bs->cow_bitmap_addr, bs->cow_bitmap_size);
    if (bs->cow_fd >= 0)
        close(bs->cow_fd);
    if (bs->fd >= 0)
        close(bs->fd);
    free(bs);
}

static inline void set_bit(uint8_t *bitmap, int64_t bitnum)
{
    bitmap[bitnum / 8] |= (1 << (bitnum%8));
}

static inline int is_bit_set(const uint8_t *bitmap, int64_t bitnum)
{
    return !!(bitmap[bitnum / 8] & (1 << (bitnum%8)));
}


/* Return true if first block has been changed (ie. current version is
 * in COW file).  Set the number of continuous blocks for which that
 * is true. */
static int is_changed(uint8_t *bitmap,
                      int64_t sector_num, int nb_sectors,
                      int *num_same)
{
    int changed;

    if (!bitmap || nb_sectors == 0) {
	*num_same = nb_sectors;
	return 0;
    }

    changed = is_bit_set(bitmap, sector_num);
    for (*num_same = 1; *num_same < nb_sectors; (*num_same)++) {
	if (is_bit_set(bitmap, sector_num + *num_same) != changed)
	    break;
    }

    return changed;
}

/* commit COW file into the raw image */
int bdrv_commit(BlockDriverState *bs)
{
    int64_t i;
    uint8_t *cow_bitmap;

    if (!bs->cow_bitmap) {
	fprintf(stderr, "Already committed to %s\n", bs->filename);
	return 0;
    }

    if (bs->read_only) {
	fprintf(stderr, "Can't commit to %s: read-only\n", bs->filename);
	return -1;
    }

    cow_bitmap = bs->cow_bitmap;
    for (i = 0; i < bs->total_sectors; i++) {
	if (is_bit_set(cow_bitmap, i)) {
	    unsigned char sector[512];
	    if (bdrv_read(bs, i, sector, 1) != 0) {
		fprintf(stderr, "Error reading sector %lli: aborting commit\n",
			(long long)i);
		return -1;
	    }

	    /* Make bdrv_write write to real file for a moment. */
	    bs->cow_bitmap = NULL;
	    if (bdrv_write(bs, i, sector, 1) != 0) {
		fprintf(stderr, "Error writing sector %lli: aborting commit\n",
			(long long)i);
		bs->cow_bitmap = cow_bitmap;
		return -1;
	    }
	    bs->cow_bitmap = cow_bitmap;
	}
    }
    fprintf(stderr, "Committed snapshot to %s\n", bs->filename);
    return 0;
}

/* return -1 if error */
int bdrv_read(BlockDriverState *bs, int64_t sector_num, 
              uint8_t *buf, int nb_sectors)
{
    int ret, n, fd;
    int64_t offset;
    
    while (nb_sectors > 0) {
        if (is_changed(bs->cow_bitmap, sector_num, nb_sectors, &n)) {
            fd = bs->cow_fd;
            offset = bs->cow_sectors_offset;
        } else {
            fd = bs->fd;
            offset = 0;
        }

        if (fd < 0) {
            /* no file, just return empty sectors */
            memset(buf, 0, n * 512);
        } else {
            offset += sector_num * 512;
            lseek64(fd, offset, SEEK_SET);
            ret = read(fd, buf, n * 512);
            if (ret != n * 512) {
                return -1;
            }
        }
        nb_sectors -= n;
        sector_num += n;
        buf += n * 512;
    }
    return 0;
}

/* return -1 if error */
int bdrv_write(BlockDriverState *bs, int64_t sector_num, 
               const uint8_t *buf, int nb_sectors)
{
    int ret, fd, i;
    int64_t offset, retl;

    if (bs->read_only)
        return -1;

    if (bs->cow_bitmap) {
        fd = bs->cow_fd;
        offset = bs->cow_sectors_offset;
    } else {
        fd = bs->fd;
        offset = 0;
    }
    
    offset += sector_num * 512;
    retl = lseek64(fd, offset, SEEK_SET);
    if (retl == -1) {
        return -1;
    }
    ret = write(fd, buf, nb_sectors * 512);
    if (ret != nb_sectors * 512) {
        return -1;
    }

    if (bs->cow_bitmap) {
	for (i = 0; i < nb_sectors; i++)
	    set_bit(bs->cow_bitmap, sector_num + i);
    }
    return 0;
}

void bdrv_get_geometry(BlockDriverState *bs, int64_t *nb_sectors_ptr)
{
    *nb_sectors_ptr = bs->total_sectors;
}
