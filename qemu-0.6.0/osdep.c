/*
 * QEMU low level functions
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
#include <errno.h>
#include <unistd.h>

#include "cpu.h"

#if defined(__i386__) && !defined(CONFIG_SOFTMMU) && !defined(CONFIG_USER_ONLY)

#include <sys/mman.h>
#include <sys/ipc.h>

/* When not using soft mmu, libc independant functions are needed for
   the CPU core because it needs to use alternates stacks and
   libc/thread incompatibles settings */

#include <linux/unistd.h>

#define QEMU_SYSCALL0(name) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name)); \
return __res; \
}

#define QEMU_SYSCALL1(name,arg1) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name),"b" ((long)(arg1))); \
return __res; \
}

#define QEMU_SYSCALL2(name,arg1,arg2) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name),"b" ((long)(arg1)),"c" ((long)(arg2))); \
return __res; \
}

#define QEMU_SYSCALL3(name,arg1,arg2,arg3) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name),"b" ((long)(arg1)),"c" ((long)(arg2)), \
		  "d" ((long)(arg3))); \
return __res; \
}

#define QEMU_SYSCALL4(name,arg1,arg2,arg3,arg4) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name),"b" ((long)(arg1)),"c" ((long)(arg2)), \
	  "d" ((long)(arg3)),"S" ((long)(arg4))); \
return __res; \
} 

#define QEMU_SYSCALL5(name,arg1,arg2,arg3,arg4,arg5) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name),"b" ((long)(arg1)),"c" ((long)(arg2)), \
	  "d" ((long)(arg3)),"S" ((long)(arg4)),"D" ((long)(arg5))); \
return __res; \
}

#define QEMU_SYSCALL6(name,arg1,arg2,arg3,arg4,arg5,arg6) \
{ \
long __res; \
__asm__ volatile ("push %%ebp ; movl %%eax,%%ebp ; movl %1,%%eax ; int $0x80 ; pop %%ebp" \
	: "=a" (__res) \
	: "i" (__NR_##name),"b" ((long)(arg1)),"c" ((long)(arg2)), \
	  "d" ((long)(arg3)),"S" ((long)(arg4)),"D" ((long)(arg5)), \
	  "0" ((long)(arg6))); \
return __res; \
}

int qemu_write(int fd, const void *buf, size_t n)
{
    QEMU_SYSCALL3(write, fd, buf, n);
}



/****************************************************************/
/* shmat replacement */

int qemu_ipc(int call, unsigned long first, 
            unsigned long second, unsigned long third, 
            void *ptr, unsigned long fifth)
{
    QEMU_SYSCALL6(ipc, call, first, second, third, ptr, fifth);
}

#define SHMAT 21

/* we must define shmat so that a specific address will be used when
   mapping the X11 ximage */
void *shmat(int shmid, const void *shmaddr, int shmflg)
{
    void *ptr;
    int ret;
    /* we give an address in the right memory area */
    if (!shmaddr)
        shmaddr = get_mmap_addr(8192 * 1024);
    ret = qemu_ipc(SHMAT, shmid, shmflg, (unsigned long)&ptr, (void *)shmaddr, 0);
    if (ret < 0)
        return NULL;
    return ptr;
}

/****************************************************************/
/* memory allocation */

//#define DEBUG_MALLOC

#define MALLOC_BASE       0xab000000
#define PHYS_RAM_BASE     0xac000000

#define MALLOC_ALIGN      16
#define BLOCK_HEADER_SIZE 16

typedef struct MemoryBlock {
    struct MemoryBlock *next;
    unsigned long size; /* size of block, including header */
} MemoryBlock;

static MemoryBlock *first_free_block;
static unsigned long malloc_addr = MALLOC_BASE;

static void *malloc_get_space(size_t size)
{
    void *ptr;
    size = TARGET_PAGE_ALIGN(size);
    ptr = mmap((void *)malloc_addr, size, 
               PROT_WRITE | PROT_READ, 
               MAP_PRIVATE | MAP_FIXED | MAP_ANON, -1, 0);
    if (ptr == MAP_FAILED)
        return NULL;
    malloc_addr += size;
    return ptr;
}

void *qemu_malloc(size_t size)
{
    MemoryBlock *mb, *mb1, **pmb;
    void *ptr;
    size_t size1, area_size;
    
    if (size == 0)
        return NULL;

    size = (size + BLOCK_HEADER_SIZE + MALLOC_ALIGN - 1) & ~(MALLOC_ALIGN - 1);
    pmb = &first_free_block;
    for(;;) {
        mb = *pmb;
        if (mb == NULL)
            break;
        if (size <= mb->size)
            goto found;
        pmb = &mb->next;
    }
    /* no big enough blocks found: get new space */
    area_size = TARGET_PAGE_ALIGN(size);
    mb = malloc_get_space(area_size);
    if (!mb)
        return NULL;
    size1 = area_size - size;
    if (size1 > 0) {
        /* create a new free block */
        mb1 = (MemoryBlock *)((uint8_t *)mb + size);
        mb1->next = NULL;
        mb1->size = size1;
        *pmb = mb1;
    }
    goto the_end;
 found:
    /* a free block was found: use it */
    size1 = mb->size - size;
    if (size1 > 0) {
        /* create a new free block */
        mb1 = (MemoryBlock *)((uint8_t *)mb + size);
        mb1->next = mb->next;
        mb1->size = size1;
        *pmb = mb1;
    } else {
        /* suppress the first block */
        *pmb = mb->next;
    }
 the_end:
    mb->size = size;
    mb->next = NULL;
    ptr = ((uint8_t *)mb + BLOCK_HEADER_SIZE);
#ifdef DEBUG_MALLOC
    qemu_printf("malloc: size=0x%x ptr=0x%lx\n", size, (unsigned long)ptr);
#endif
    return ptr;
}

void qemu_free(void *ptr)
{
    MemoryBlock *mb;

    if (!ptr)
        return;
    mb = (MemoryBlock *)((uint8_t *)ptr - BLOCK_HEADER_SIZE);
    mb->next = first_free_block;
    first_free_block = mb;
}

/****************************************************************/
/* virtual memory allocation */

unsigned long mmap_addr = PHYS_RAM_BASE;

void *get_mmap_addr(unsigned long size)
{
    unsigned long addr;
    addr = mmap_addr;
    mmap_addr += ((size + 4095) & ~4095) + 4096;
    return (void *)addr;
}

#else

int qemu_write(int fd, const void *buf, size_t n)
{
    int ret;
    ret = write(fd, buf, n);
    if (ret < 0)
        return -errno;
    else
        return ret;
}

void *get_mmap_addr(unsigned long size)
{
    return NULL;
}

void qemu_free(void *ptr)
{
    free(ptr);
}

void *qemu_malloc(size_t size)
{
    return malloc(size);
}

#endif

void *qemu_mallocz(size_t size)
{
    void *ptr;
    ptr = qemu_malloc(size);
    if (!ptr)
        return NULL;
    memset(ptr, 0, size);
    return ptr;
}

/****************************************************************/
/* printf support */

static inline int qemu_isdigit(int c)
{
    return c >= '0' && c <= '9';
}

#define OUTCHAR(c)	(buflen > 0? (--buflen, *buf++ = (c)): 0)

/* from BSD ppp sources */
int qemu_vsnprintf(char *buf, int buflen, const char *fmt, va_list args)
{
    int c, i, n;
    int width, prec, fillch;
    int base, len, neg;
    unsigned long val = 0;
    const char *f;
    char *str, *buf0;
    char num[32];
    static const char hexchars[] = "0123456789abcdef";

    buf0 = buf;
    --buflen;
    while (buflen > 0) {
	for (f = fmt; *f != '%' && *f != 0; ++f)
	    ;
	if (f > fmt) {
	    len = f - fmt;
	    if (len > buflen)
		len = buflen;
	    memcpy(buf, fmt, len);
	    buf += len;
	    buflen -= len;
	    fmt = f;
	}
	if (*fmt == 0)
	    break;
	c = *++fmt;
	width = prec = 0;
	fillch = ' ';
	if (c == '0') {
	    fillch = '0';
	    c = *++fmt;
	}
	if (c == '*') {
	    width = va_arg(args, int);
	    c = *++fmt;
	} else {
	    while (qemu_isdigit(c)) {
		width = width * 10 + c - '0';
		c = *++fmt;
	    }
	}
	if (c == '.') {
	    c = *++fmt;
	    if (c == '*') {
		prec = va_arg(args, int);
		c = *++fmt;
	    } else {
		while (qemu_isdigit(c)) {
		    prec = prec * 10 + c - '0';
		    c = *++fmt;
		}
	    }
	}
        /* modifiers */
        switch(c) {
        case 'l':
            c = *++fmt;
            break;
        default:
            break;
        }
        str = 0;
	base = 0;
	neg = 0;
	++fmt;
	switch (c) {
	case 'd':
	    i = va_arg(args, int);
	    if (i < 0) {
		neg = 1;
		val = -i;
	    } else
		val = i;
	    base = 10;
	    break;
	case 'o':
	    val = va_arg(args, unsigned int);
	    base = 8;
	    break;
	case 'x':
	case 'X':
	    val = va_arg(args, unsigned int);
	    base = 16;
	    break;
	case 'p':
	    val = (unsigned long) va_arg(args, void *);
	    base = 16;
	    neg = 2;
	    break;
	case 's':
	    str = va_arg(args, char *);
	    break;
	case 'c':
	    num[0] = va_arg(args, int);
	    num[1] = 0;
	    str = num;
	    break;
	default:
	    *buf++ = '%';
	    if (c != '%')
		--fmt;		/* so %z outputs %z etc. */
	    --buflen;
	    continue;
	}
	if (base != 0) {
	    str = num + sizeof(num);
	    *--str = 0;
	    while (str > num + neg) {
		*--str = hexchars[val % base];
		val = val / base;
		if (--prec <= 0 && val == 0)
		    break;
	    }
	    switch (neg) {
	    case 1:
		*--str = '-';
		break;
	    case 2:
		*--str = 'x';
		*--str = '0';
		break;
	    }
	    len = num + sizeof(num) - 1 - str;
	} else {
	    len = strlen(str);
	    if (prec > 0 && len > prec)
		len = prec;
	}
	if (width > 0) {
	    if (width > buflen)
		width = buflen;
	    if ((n = width - len) > 0) {
		buflen -= n;
		for (; n > 0; --n)
		    *buf++ = fillch;
	    }
	}
	if (len > buflen)
	    len = buflen;
	memcpy(buf, str, len);
	buf += len;
	buflen -= len;
    }
    *buf = 0;
    return buf - buf0;
}

void qemu_vprintf(const char *fmt, va_list ap)
{
    char buf[1024];
    int len;
    
    len = qemu_vsnprintf(buf, sizeof(buf), fmt, ap);
    qemu_write(1, buf, len);
}

void qemu_printf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    qemu_vprintf(fmt, ap);
    va_end(ap);
}

