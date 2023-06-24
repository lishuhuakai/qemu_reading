/*
 * QEMU IDE disk and CD-ROM Emulator
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
#include "vl.h"

/* debug IDE devices */
//#define DEBUG_IDE
//#define DEBUG_IDE_ATAPI

/* Bits of HD_STATUS */
#define ERR_STAT		0x01
#define INDEX_STAT		0x02
#define ECC_STAT		0x04	/* Corrected error */
#define DRQ_STAT		0x08
#define SEEK_STAT		0x10
#define SRV_STAT		0x10
#define WRERR_STAT		0x20
#define READY_STAT		0x40
#define BUSY_STAT		0x80

/* Bits for HD_ERROR */
#define MARK_ERR		0x01	/* Bad address mark */
#define TRK0_ERR		0x02	/* couldn't find track 0 */
#define ABRT_ERR		0x04	/* Command aborted */
#define MCR_ERR			0x08	/* media change request */
#define ID_ERR			0x10	/* ID field not found */
#define MC_ERR			0x20	/* media changed */
#define ECC_ERR			0x40	/* Uncorrectable ECC error */
#define BBD_ERR			0x80	/* pre-EIDE meaning:  block marked bad */
#define ICRC_ERR		0x80	/* new meaning:  CRC error during transfer */

/* Bits of HD_NSECTOR */
#define CD			0x01
#define IO			0x02
#define REL			0x04
#define TAG_MASK		0xf8

#define IDE_CMD_RESET           0x04
#define IDE_CMD_DISABLE_IRQ     0x02

/* ATA/ATAPI Commands pre T13 Spec */
#define WIN_NOP				0x00
/*
 *	0x01->0x02 Reserved
 */
#define CFA_REQ_EXT_ERROR_CODE		0x03 /* CFA Request Extended Error Code */
/*
 *	0x04->0x07 Reserved
 */
#define WIN_SRST			0x08 /* ATAPI soft reset command */
#define WIN_DEVICE_RESET		0x08
/*
 *	0x09->0x0F Reserved
 */
#define WIN_RECAL			0x10
#define WIN_RESTORE			WIN_RECAL
/*
 *	0x10->0x1F Reserved
 */
#define WIN_READ			0x20 /* 28-Bit */
#define WIN_READ_ONCE			0x21 /* 28-Bit without retries */
#define WIN_READ_LONG			0x22 /* 28-Bit */
#define WIN_READ_LONG_ONCE		0x23 /* 28-Bit without retries */
#define WIN_READ_EXT			0x24 /* 48-Bit */
#define WIN_READDMA_EXT			0x25 /* 48-Bit */
#define WIN_READDMA_QUEUED_EXT		0x26 /* 48-Bit */
#define WIN_READ_NATIVE_MAX_EXT		0x27 /* 48-Bit */
/*
 *	0x28
 */
#define WIN_MULTREAD_EXT		0x29 /* 48-Bit */
/*
 *	0x2A->0x2F Reserved
 */
#define WIN_WRITE			0x30 /* 28-Bit */
#define WIN_WRITE_ONCE			0x31 /* 28-Bit without retries */
#define WIN_WRITE_LONG			0x32 /* 28-Bit */
#define WIN_WRITE_LONG_ONCE		0x33 /* 28-Bit without retries */
#define WIN_WRITE_EXT			0x34 /* 48-Bit */
#define WIN_WRITEDMA_EXT		0x35 /* 48-Bit */
#define WIN_WRITEDMA_QUEUED_EXT		0x36 /* 48-Bit */
#define WIN_SET_MAX_EXT			0x37 /* 48-Bit */
#define CFA_WRITE_SECT_WO_ERASE		0x38 /* CFA Write Sectors without erase */
#define WIN_MULTWRITE_EXT		0x39 /* 48-Bit */
/*
 *	0x3A->0x3B Reserved
 */
#define WIN_WRITE_VERIFY		0x3C /* 28-Bit */
/*
 *	0x3D->0x3F Reserved
 */
#define WIN_VERIFY			0x40 /* 28-Bit - Read Verify Sectors */
#define WIN_VERIFY_ONCE			0x41 /* 28-Bit - without retries */
#define WIN_VERIFY_EXT			0x42 /* 48-Bit */
/*
 *	0x43->0x4F Reserved
 */
#define WIN_FORMAT			0x50
/*
 *	0x51->0x5F Reserved
 */
#define WIN_INIT			0x60
/*
 *	0x61->0x5F Reserved
 */
#define WIN_SEEK			0x70 /* 0x70-0x7F Reserved */
#define CFA_TRANSLATE_SECTOR		0x87 /* CFA Translate Sector */
#define WIN_DIAGNOSE			0x90
#define WIN_SPECIFY			0x91 /* set drive geometry translation */
#define WIN_DOWNLOAD_MICROCODE		0x92
#define WIN_STANDBYNOW2			0x94
#define WIN_STANDBY2			0x96
#define WIN_SETIDLE2			0x97
#define WIN_CHECKPOWERMODE2		0x98
#define WIN_SLEEPNOW2			0x99
/*
 *	0x9A VENDOR
 */
#define WIN_PACKETCMD			0xA0 /* Send a packet command. */
#define WIN_PIDENTIFY			0xA1 /* identify ATAPI device	*/
#define WIN_QUEUED_SERVICE		0xA2
#define WIN_SMART			0xB0 /* self-monitoring and reporting */
#define CFA_ERASE_SECTORS       	0xC0
#define WIN_MULTREAD			0xC4 /* read sectors using multiple mode*/
#define WIN_MULTWRITE			0xC5 /* write sectors using multiple mode */
#define WIN_SETMULT			0xC6 /* enable/disable multiple mode */
#define WIN_READDMA_QUEUED		0xC7 /* read sectors using Queued DMA transfers */
#define WIN_READDMA			0xC8 /* read sectors using DMA transfers */
#define WIN_READDMA_ONCE		0xC9 /* 28-Bit - without retries */
#define WIN_WRITEDMA			0xCA /* write sectors using DMA transfers */
#define WIN_WRITEDMA_ONCE		0xCB /* 28-Bit - without retries */
#define WIN_WRITEDMA_QUEUED		0xCC /* write sectors using Queued DMA transfers */
#define CFA_WRITE_MULTI_WO_ERASE	0xCD /* CFA Write multiple without erase */
#define WIN_GETMEDIASTATUS		0xDA	
#define WIN_ACKMEDIACHANGE		0xDB /* ATA-1, ATA-2 vendor */
#define WIN_POSTBOOT			0xDC
#define WIN_PREBOOT			0xDD
#define WIN_DOORLOCK			0xDE /* lock door on removable drives */
#define WIN_DOORUNLOCK			0xDF /* unlock door on removable drives */
#define WIN_STANDBYNOW1			0xE0
#define WIN_IDLEIMMEDIATE		0xE1 /* force drive to become "ready" */
#define WIN_STANDBY             	0xE2 /* Set device in Standby Mode */
#define WIN_SETIDLE1			0xE3
#define WIN_READ_BUFFER			0xE4 /* force read only 1 sector */
#define WIN_CHECKPOWERMODE1		0xE5
#define WIN_SLEEPNOW1			0xE6
#define WIN_FLUSH_CACHE			0xE7
#define WIN_WRITE_BUFFER		0xE8 /* force write only 1 sector */
#define WIN_WRITE_SAME			0xE9 /* read ata-2 to use */
	/* SET_FEATURES 0x22 or 0xDD */
#define WIN_FLUSH_CACHE_EXT		0xEA /* 48-Bit */
#define WIN_IDENTIFY			0xEC /* ask drive to identify itself	*/
#define WIN_MEDIAEJECT			0xED
#define WIN_IDENTIFY_DMA		0xEE /* same as WIN_IDENTIFY, but DMA */
#define WIN_SETFEATURES			0xEF /* set special drive features */
#define EXABYTE_ENABLE_NEST		0xF0
#define WIN_SECURITY_SET_PASS		0xF1
#define WIN_SECURITY_UNLOCK		0xF2
#define WIN_SECURITY_ERASE_PREPARE	0xF3
#define WIN_SECURITY_ERASE_UNIT		0xF4
#define WIN_SECURITY_FREEZE_LOCK	0xF5
#define WIN_SECURITY_DISABLE		0xF6
#define WIN_READ_NATIVE_MAX		0xF8 /* return the native maximum address */
#define WIN_SET_MAX			0xF9
#define DISABLE_SEAGATE			0xFB

/* set to 1 set disable mult support */
#define MAX_MULT_SECTORS 16

/* ATAPI defines */

#define ATAPI_PACKET_SIZE 12

/* The generic packet command opcodes for CD/DVD Logical Units,
 * From Table 57 of the SFF8090 Ver. 3 (Mt. Fuji) draft standard. */
#define GPCMD_BLANK			    0xa1
#define GPCMD_CLOSE_TRACK		    0x5b
#define GPCMD_FLUSH_CACHE		    0x35
#define GPCMD_FORMAT_UNIT		    0x04
#define GPCMD_GET_CONFIGURATION		    0x46
#define GPCMD_GET_EVENT_STATUS_NOTIFICATION 0x4a
#define GPCMD_GET_PERFORMANCE		    0xac
#define GPCMD_INQUIRY			    0x12
#define GPCMD_LOAD_UNLOAD		    0xa6
#define GPCMD_MECHANISM_STATUS		    0xbd
#define GPCMD_MODE_SELECT_10		    0x55
#define GPCMD_MODE_SENSE_10		    0x5a
#define GPCMD_PAUSE_RESUME		    0x4b
#define GPCMD_PLAY_AUDIO_10		    0x45
#define GPCMD_PLAY_AUDIO_MSF		    0x47
#define GPCMD_PLAY_AUDIO_TI		    0x48
#define GPCMD_PLAY_CD			    0xbc
#define GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL  0x1e
#define GPCMD_READ_10			    0x28
#define GPCMD_READ_12			    0xa8
#define GPCMD_READ_CDVD_CAPACITY	    0x25
#define GPCMD_READ_CD			    0xbe
#define GPCMD_READ_CD_MSF		    0xb9
#define GPCMD_READ_DISC_INFO		    0x51
#define GPCMD_READ_DVD_STRUCTURE	    0xad
#define GPCMD_READ_FORMAT_CAPACITIES	    0x23
#define GPCMD_READ_HEADER		    0x44
#define GPCMD_READ_TRACK_RZONE_INFO	    0x52
#define GPCMD_READ_SUBCHANNEL		    0x42
#define GPCMD_READ_TOC_PMA_ATIP		    0x43
#define GPCMD_REPAIR_RZONE_TRACK	    0x58
#define GPCMD_REPORT_KEY		    0xa4
#define GPCMD_REQUEST_SENSE		    0x03
#define GPCMD_RESERVE_RZONE_TRACK	    0x53
#define GPCMD_SCAN			    0xba
#define GPCMD_SEEK			    0x2b
#define GPCMD_SEND_DVD_STRUCTURE	    0xad
#define GPCMD_SEND_EVENT		    0xa2
#define GPCMD_SEND_KEY			    0xa3
#define GPCMD_SEND_OPC			    0x54
#define GPCMD_SET_READ_AHEAD		    0xa7
#define GPCMD_SET_STREAMING		    0xb6
#define GPCMD_START_STOP_UNIT		    0x1b
#define GPCMD_STOP_PLAY_SCAN		    0x4e
#define GPCMD_TEST_UNIT_READY		    0x00
#define GPCMD_VERIFY_10			    0x2f
#define GPCMD_WRITE_10			    0x2a
#define GPCMD_WRITE_AND_VERIFY_10	    0x2e
/* This is listed as optional in ATAPI 2.6, but is (curiously) 
 * missing from Mt. Fuji, Table 57.  It _is_ mentioned in Mt. Fuji
 * Table 377 as an MMC command for SCSi devices though...  Most ATAPI
 * drives support it. */
#define GPCMD_SET_SPEED			    0xbb
/* This seems to be a SCSI specific CD-ROM opcode 
 * to play data at track/index */
#define GPCMD_PLAYAUDIO_TI		    0x48
/*
 * From MS Media Status Notification Support Specification. For
 * older drives only.
 */
#define GPCMD_GET_MEDIA_STATUS		    0xda

/* Mode page codes for mode sense/set */
#define GPMODE_R_W_ERROR_PAGE		0x01
#define GPMODE_WRITE_PARMS_PAGE		0x05
#define GPMODE_AUDIO_CTL_PAGE		0x0e
#define GPMODE_POWER_PAGE		0x1a
#define GPMODE_FAULT_FAIL_PAGE		0x1c
#define GPMODE_TO_PROTECT_PAGE		0x1d
#define GPMODE_CAPABILITIES_PAGE	0x2a
#define GPMODE_ALL_PAGES		0x3f
/* Not in Mt. Fuji, but in ATAPI 2.6 -- depricated now in favor
 * of MODE_SENSE_POWER_PAGE */
#define GPMODE_CDROM_PAGE		0x0d

#define ATAPI_INT_REASON_CD             0x01 /* 0 = data transfer */
#define ATAPI_INT_REASON_IO             0x02 /* 1 = transfer to the host */
#define ATAPI_INT_REASON_REL            0x04
#define ATAPI_INT_REASON_TAG            0xf8

/* same constants as bochs */
#define ASC_ILLEGAL_OPCODE                   0x20
#define ASC_LOGICAL_BLOCK_OOR                0x21
#define ASC_INV_FIELD_IN_CMD_PACKET          0x24
#define ASC_MEDIUM_NOT_PRESENT               0x3a
#define ASC_SAVING_PARAMETERS_NOT_SUPPORTED  0x39

#define SENSE_NONE            0
#define SENSE_NOT_READY       2
#define SENSE_ILLEGAL_REQUEST 5
#define SENSE_UNIT_ATTENTION  6

struct IDEState;

typedef void EndTransferFunc(struct IDEState *);

/* NOTE: IDEState represents in fact one drive */
typedef struct IDEState {
    /* ide config */
    int is_cdrom;
    int cylinders, heads, sectors;
    int64_t nb_sectors;
    int mult_sectors;
    int irq;
    openpic_t *openpic;
    PCIDevice *pci_dev;
    struct BMDMAState *bmdma;
    int drive_serial;
    /* ide regs */
    uint8_t feature;
    uint8_t error;
    uint16_t nsector; /* 0 is 256 to ease computations */
    uint8_t sector;
    uint8_t lcyl;
    uint8_t hcyl;
    uint8_t select;
    uint8_t status;
    /* 0x3f6 command, only meaningful for drive 0 */
    uint8_t cmd;
    /* depends on bit 4 in select, only meaningful for drive 0 */
    struct IDEState *cur_drive; 
    BlockDriverState *bs;
    /* ATAPI specific */
    uint8_t sense_key;
    uint8_t asc;
    int packet_transfer_size;
    int elementary_transfer_size;
    int io_buffer_index;
    int lba;
    int cd_sector_size;
    int atapi_dma; /* true if dma is requested for the packet cmd */
    /* ATA DMA state */
    int io_buffer_size;
    /* PIO transfer handling */
    int req_nb_sectors; /* number of sectors per interrupt */
    EndTransferFunc *end_transfer_func;
    uint8_t *data_ptr;
    uint8_t *data_end;
    uint8_t io_buffer[MAX_MULT_SECTORS*512 + 4];
} IDEState;

#define BM_STATUS_DMAING 0x01
#define BM_STATUS_ERROR  0x02
#define BM_STATUS_INT    0x04

#define BM_CMD_START     0x01
#define BM_CMD_READ      0x08

typedef int IDEDMAFunc(IDEState *s, 
                       target_phys_addr_t phys_addr, 
                       int transfer_size1);

typedef struct BMDMAState {
    uint8_t cmd;
    uint8_t status;
    uint32_t addr;
    /* current transfer state */
    IDEState *ide_if;
    IDEDMAFunc *dma_cb;
} BMDMAState;

typedef struct PCIIDEState {
    PCIDevice dev;
    IDEState ide_if[4];
    BMDMAState bmdma[2];
} PCIIDEState;

static void ide_dma_start(IDEState *s, IDEDMAFunc *dma_cb);

static void padstr(char *str, const char *src, int len)
{
    int i, v;
    for(i = 0; i < len; i++) {
        if (*src)
            v = *src++;
        else
            v = ' ';
        *(char *)((long)str ^ 1) = v;
        str++;
    }
}

static void padstr8(uint8_t *buf, int buf_size, const char *src)
{
    int i;
    for(i = 0; i < buf_size; i++) {
        if (*src)
            buf[i] = *src++;
        else
            buf[i] = ' ';
    }
}

static void put_le16(uint16_t *p, unsigned int v)
{
    *p = cpu_to_le16(v);
}

static void ide_identify(IDEState *s)
{
    uint16_t *p;
    unsigned int oldsize;
    char buf[20];

    memset(s->io_buffer, 0, 512);
    p = (uint16_t *)s->io_buffer;
    put_le16(p + 0, 0x0040);
    put_le16(p + 1, s->cylinders); 
    put_le16(p + 3, s->heads);
    put_le16(p + 4, 512 * s->sectors); /* XXX: retired, remove ? */
    put_le16(p + 5, 512); /* XXX: retired, remove ? */
    put_le16(p + 6, s->sectors); 
    snprintf(buf, sizeof(buf), "QM%05d", s->drive_serial);
    padstr((uint8_t *)(p + 10), buf, 20); /* serial number */
    put_le16(p + 20, 3); /* XXX: retired, remove ? */
    put_le16(p + 21, 512); /* cache size in sectors */
    put_le16(p + 22, 4); /* ecc bytes */
    padstr((uint8_t *)(p + 23), QEMU_VERSION, 8); /* firmware version */
    padstr((uint8_t *)(p + 27), "QEMU HARDDISK", 40); /* model */
#if MAX_MULT_SECTORS > 1    
    put_le16(p + 47, 0x8000 | MAX_MULT_SECTORS);
#endif
    put_le16(p + 48, 1); /* dword I/O */
    put_le16(p + 49, 1 << 9); /* LBA supported, no DMA */
    put_le16(p + 51, 0x200); /* PIO transfer cycle */
    put_le16(p + 52, 0x200); /* DMA transfer cycle */
    put_le16(p + 53, 1); /* words 54-58 are valid */
    put_le16(p + 54, s->cylinders);
    put_le16(p + 55, s->heads);
    put_le16(p + 56, s->sectors);
    oldsize = s->cylinders * s->heads * s->sectors;
    put_le16(p + 57, oldsize);
    put_le16(p + 58, oldsize >> 16);
    if (s->mult_sectors)
        put_le16(p + 59, 0x100 | s->mult_sectors);
    put_le16(p + 60, s->nb_sectors);
    put_le16(p + 61, s->nb_sectors >> 16);
    put_le16(p + 80, (1 << 1) | (1 << 2));
    put_le16(p + 82, (1 << 14));
    put_le16(p + 83, (1 << 14));
    put_le16(p + 84, (1 << 14));
    put_le16(p + 85, (1 << 14));
    put_le16(p + 86, 0);
    put_le16(p + 87, (1 << 14));
}

static void ide_atapi_identify(IDEState *s)
{
    uint16_t *p;
    char buf[20];

    memset(s->io_buffer, 0, 512);
    p = (uint16_t *)s->io_buffer;
    /* Removable CDROM, 50us response, 12 byte packets */
    put_le16(p + 0, (2 << 14) | (5 << 8) | (1 << 7) | (2 << 5) | (0 << 0));
    snprintf(buf, sizeof(buf), "QM%05d", s->drive_serial);
    padstr((uint8_t *)(p + 10), buf, 20); /* serial number */
    put_le16(p + 20, 3); /* buffer type */
    put_le16(p + 21, 512); /* cache size in sectors */
    put_le16(p + 22, 4); /* ecc bytes */
    padstr((uint8_t *)(p + 23), QEMU_VERSION, 8); /* firmware version */
    padstr((uint8_t *)(p + 27), "QEMU CD-ROM", 40); /* model */
    put_le16(p + 48, 1); /* dword I/O (XXX: should not be set on CDROM) */
    put_le16(p + 49, 1 << 9); /* LBA supported, no DMA */
    put_le16(p + 53, 3); /* words 64-70, 54-58 valid */
    put_le16(p + 63, 0x103); /* DMA modes XXX: may be incorrect */
    put_le16(p + 64, 1); /* PIO modes */
    put_le16(p + 65, 0xb4); /* minimum DMA multiword tx cycle time */
    put_le16(p + 66, 0xb4); /* recommended DMA multiword tx cycle time */
    put_le16(p + 67, 0x12c); /* minimum PIO cycle time without flow control */
    put_le16(p + 68, 0xb4); /* minimum PIO cycle time with IORDY flow control */
    
    put_le16(p + 71, 30); /* in ns */
    put_le16(p + 72, 30); /* in ns */

    put_le16(p + 80, 0x1e); /* support up to ATA/ATAPI-4 */
}

static void ide_set_signature(IDEState *s)
{
    s->select &= 0xf0; /* clear head */
    /* put signature */
    s->nsector = 1;
    s->sector = 1;
    if (s->is_cdrom) {
        s->lcyl = 0x14;
        s->hcyl = 0xeb;
    } else if (s->bs) {
        s->lcyl = 0;
        s->hcyl = 0;
    } else {
        s->lcyl = 0xff;
        s->hcyl = 0xff;
    }
}

static inline void ide_abort_command(IDEState *s)
{
    s->status = READY_STAT | ERR_STAT;
    s->error = ABRT_ERR;
}

static inline void ide_set_irq(IDEState *s)
{
    if (!(s->cmd & IDE_CMD_DISABLE_IRQ)) {
#ifdef TARGET_PPC
        if (s->openpic) 
            openpic_set_irq(s->openpic, s->irq, 1);
        else 
#endif
        if (s->irq == 16)
            pci_set_irq(s->pci_dev, 0, 1);
        else
            pic_set_irq(s->irq, 1);
    }
}

/* prepare data transfer and tell what to do after */
static void ide_transfer_start(IDEState *s, uint8_t *buf, int size, 
                               EndTransferFunc *end_transfer_func)
{
    s->end_transfer_func = end_transfer_func;
    s->data_ptr = buf;
    s->data_end = buf + size;
    s->status |= DRQ_STAT;
}

static void ide_transfer_stop(IDEState *s)
{
    s->end_transfer_func = ide_transfer_stop;
    s->data_ptr = s->io_buffer;
    s->data_end = s->io_buffer;
    s->status &= ~DRQ_STAT;
}

static int64_t ide_get_sector(IDEState *s)
{
    int64_t sector_num;
    if (s->select & 0x40) {
        /* lba */
        sector_num = ((s->select & 0x0f) << 24) | (s->hcyl << 16) | 
            (s->lcyl << 8) | s->sector;
    } else {
        sector_num = ((s->hcyl << 8) | s->lcyl) * s->heads * s->sectors +
            (s->select & 0x0f) * s->sectors + 
            (s->sector - 1);
    }
    return sector_num;
}

static void ide_set_sector(IDEState *s, int64_t sector_num)
{
    unsigned int cyl, r;
    if (s->select & 0x40) {
        s->select = (s->select & 0xf0) | (sector_num >> 24);
        s->hcyl = (sector_num >> 16);
        s->lcyl = (sector_num >> 8);
        s->sector = (sector_num);
    } else {
        cyl = sector_num / (s->heads * s->sectors);
        r = sector_num % (s->heads * s->sectors);
        s->hcyl = cyl >> 8;
        s->lcyl = cyl;
        s->select = (s->select & 0xf0) | ((r / s->sectors) & 0x0f);
        s->sector = (r % s->sectors) + 1;
    }
}

static void ide_sector_read(IDEState *s)
{
    int64_t sector_num;
    int ret, n;

    s->status = READY_STAT | SEEK_STAT;
    s->error = 0; /* not needed by IDE spec, but needed by Windows */
    sector_num = ide_get_sector(s);
    n = s->nsector;
    if (n == 0) {
        /* no more sector to read from disk */
        ide_transfer_stop(s);
    } else {
#if defined(DEBUG_IDE)
        printf("read sector=%Ld\n", sector_num);
#endif
        if (n > s->req_nb_sectors)
            n = s->req_nb_sectors;
        ret = bdrv_read(s->bs, sector_num, s->io_buffer, n);
        ide_transfer_start(s, s->io_buffer, 512 * n, ide_sector_read);
        ide_set_irq(s);
        ide_set_sector(s, sector_num + n);
        s->nsector -= n;
    }
}

static int ide_read_dma_cb(IDEState *s, 
                           target_phys_addr_t phys_addr, 
                           int transfer_size1)
{
    int len, transfer_size, n;
    int64_t sector_num;

    transfer_size = transfer_size1;
    while (transfer_size > 0) {
        len = s->io_buffer_size - s->io_buffer_index;
        if (len <= 0) {
            /* transfert next data */
            n = s->nsector;
            if (n == 0)
                break;
            if (n > MAX_MULT_SECTORS)
                n = MAX_MULT_SECTORS;
            sector_num = ide_get_sector(s);
            bdrv_read(s->bs, sector_num, s->io_buffer, n);
            s->io_buffer_index = 0;
            s->io_buffer_size = n * 512;
            len = s->io_buffer_size;
            sector_num += n;
            ide_set_sector(s, sector_num);
            s->nsector -= n;
        }
        if (len > transfer_size)
            len = transfer_size;
        cpu_physical_memory_write(phys_addr, 
                                  s->io_buffer + s->io_buffer_index, len);
        s->io_buffer_index += len;
        transfer_size -= len;
        phys_addr += len;
    }
    if (s->io_buffer_index >= s->io_buffer_size && s->nsector == 0) {
        s->status = READY_STAT | SEEK_STAT;
        ide_set_irq(s);
#ifdef DEBUG_IDE_ATAPI
        printf("dma status=0x%x\n", s->status);
#endif
        return 0;
    }
    return transfer_size1 - transfer_size;
}

static void ide_sector_read_dma(IDEState *s)
{
    s->status = READY_STAT | SEEK_STAT | DRQ_STAT;
    s->io_buffer_index = 0;
    s->io_buffer_size = 0;
    ide_dma_start(s, ide_read_dma_cb);
}

static void ide_sector_write(IDEState *s)
{
    int64_t sector_num;
    int ret, n, n1;

    s->status = READY_STAT | SEEK_STAT;
    sector_num = ide_get_sector(s);
#if defined(DEBUG_IDE)
    printf("write sector=%Ld\n", sector_num);
#endif
    n = s->nsector;
    if (n > s->req_nb_sectors)
        n = s->req_nb_sectors;
    ret = bdrv_write(s->bs, sector_num, s->io_buffer, n);
    s->nsector -= n;
    if (s->nsector == 0) {
        /* no more sector to write */
        ide_transfer_stop(s);
    } else {
        n1 = s->nsector;
        if (n1 > s->req_nb_sectors)
            n1 = s->req_nb_sectors;
        ide_transfer_start(s, s->io_buffer, 512 * n1, ide_sector_write);
    }
    ide_set_sector(s, sector_num + n);
    ide_set_irq(s);
}

static int ide_write_dma_cb(IDEState *s, 
                            target_phys_addr_t phys_addr, 
                            int transfer_size1)
{
    int len, transfer_size, n;
    int64_t sector_num;

    transfer_size = transfer_size1;
    for(;;) {
        len = s->io_buffer_size - s->io_buffer_index;
        if (len == 0) {
            n = s->io_buffer_size >> 9;
            sector_num = ide_get_sector(s);
            bdrv_write(s->bs, sector_num, s->io_buffer, 
                       s->io_buffer_size >> 9);
            sector_num += n;
            ide_set_sector(s, sector_num);
            s->nsector -= n;
            n = s->nsector;
            if (n == 0) {
                /* end of transfer */
                s->status = READY_STAT | SEEK_STAT;
                ide_set_irq(s);
                return 0;
            }
            if (n > MAX_MULT_SECTORS)
                n = MAX_MULT_SECTORS;
            s->io_buffer_index = 0;
            s->io_buffer_size = n * 512;
            len = s->io_buffer_size;
        }
        if (transfer_size <= 0)
            break;
        if (len > transfer_size)
            len = transfer_size;
        cpu_physical_memory_read(phys_addr, 
                                 s->io_buffer + s->io_buffer_index, len);
        s->io_buffer_index += len;
        transfer_size -= len;
        phys_addr += len;
    }
    return transfer_size1 - transfer_size;
}

static void ide_sector_write_dma(IDEState *s)
{
    int n;
    s->status = READY_STAT | SEEK_STAT | DRQ_STAT;
    n = s->nsector;
    if (n > MAX_MULT_SECTORS)
        n = MAX_MULT_SECTORS;
    s->io_buffer_index = 0;
    s->io_buffer_size = n * 512;
    ide_dma_start(s, ide_write_dma_cb);
}

static void ide_atapi_cmd_ok(IDEState *s)
{
    s->error = 0;
    s->status = READY_STAT;
    s->nsector = (s->nsector & ~7) | ATAPI_INT_REASON_IO | ATAPI_INT_REASON_CD;
    ide_set_irq(s);
}

static void ide_atapi_cmd_error(IDEState *s, int sense_key, int asc)
{
#ifdef DEBUG_IDE_ATAPI
    printf("atapi_cmd_error: sense=0x%x asc=0x%x\n", sense_key, asc);
#endif
    s->error = sense_key << 4;
    s->status = READY_STAT | ERR_STAT;
    s->nsector = (s->nsector & ~7) | ATAPI_INT_REASON_IO | ATAPI_INT_REASON_CD;
    s->sense_key = sense_key;
    s->asc = asc;
    ide_set_irq(s);
}

static inline void cpu_to_ube16(uint8_t *buf, int val)
{
    buf[0] = val >> 8;
    buf[1] = val;
}

static inline void cpu_to_ube32(uint8_t *buf, unsigned int val)
{
    buf[0] = val >> 24;
    buf[1] = val >> 16;
    buf[2] = val >> 8;
    buf[3] = val;
}

static inline int ube16_to_cpu(const uint8_t *buf)
{
    return (buf[0] << 8) | buf[1];
}

static inline int ube32_to_cpu(const uint8_t *buf)
{
    return (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
}

static void lba_to_msf(uint8_t *buf, int lba)
{
    lba += 150;
    buf[0] = (lba / 75) / 60;
    buf[1] = (lba / 75) % 60;
    buf[2] = lba % 75;
}

static void cd_read_sector(BlockDriverState *bs, int lba, uint8_t *buf, 
                           int sector_size)
{
    switch(sector_size) {
    case 2048:
        bdrv_read(bs, (int64_t)lba << 2, buf, 4);
        break;
    case 2352:
        /* sync bytes */
        buf[0] = 0x00;
        memset(buf + 1, 0xff, 11);
        buf += 12;
        /* MSF */
        lba_to_msf(buf, lba);
        buf[3] = 0x01; /* mode 1 data */
        buf += 4;
        /* data */
        bdrv_read(bs, (int64_t)lba << 2, buf, 4);
        buf += 2048;
        /* ECC */
        memset(buf, 0, 288);
        break;
    default:
        break;
    }
}

/* The whole ATAPI transfer logic is handled in this function */
static void ide_atapi_cmd_reply_end(IDEState *s)
{
    int byte_count_limit, size;
#ifdef DEBUG_IDE_ATAPI
    printf("reply: tx_size=%d elem_tx_size=%d index=%d\n", 
           s->packet_transfer_size,
           s->elementary_transfer_size,
           s->io_buffer_index);
#endif
    if (s->packet_transfer_size <= 0) {
        /* end of transfer */
        ide_transfer_stop(s);
        s->status = READY_STAT;
        s->nsector = (s->nsector & ~7) | ATAPI_INT_REASON_IO | ATAPI_INT_REASON_CD;
        ide_set_irq(s);
#ifdef DEBUG_IDE_ATAPI
        printf("status=0x%x\n", s->status);
#endif
    } else {
        /* see if a new sector must be read */
        if (s->lba != -1 && s->io_buffer_index >= s->cd_sector_size) {
            cd_read_sector(s->bs, s->lba, s->io_buffer, s->cd_sector_size);
            s->lba++;
            s->io_buffer_index = 0;
        }
        if (s->elementary_transfer_size > 0) {
            /* there are some data left to transmit in this elementary
               transfer */
            size = s->cd_sector_size - s->io_buffer_index;
            if (size > s->elementary_transfer_size)
                size = s->elementary_transfer_size;
            ide_transfer_start(s, s->io_buffer + s->io_buffer_index, 
                               size, ide_atapi_cmd_reply_end);
            s->packet_transfer_size -= size;
            s->elementary_transfer_size -= size;
            s->io_buffer_index += size;
        } else {
            /* a new transfer is needed */
            s->nsector = (s->nsector & ~7) | ATAPI_INT_REASON_IO;
            byte_count_limit = s->lcyl | (s->hcyl << 8);
#ifdef DEBUG_IDE_ATAPI
            printf("byte_count_limit=%d\n", byte_count_limit);
#endif
            if (byte_count_limit == 0xffff)
                byte_count_limit--;
            size = s->packet_transfer_size;
            if (size > byte_count_limit) {
                /* byte count limit must be even if this case */
                if (byte_count_limit & 1)
                    byte_count_limit--;
                size = byte_count_limit;
            }
            s->lcyl = size;
            s->hcyl = size >> 8;
            s->elementary_transfer_size = size;
            /* we cannot transmit more than one sector at a time */
            if (s->lba != -1) {
                if (size > (s->cd_sector_size - s->io_buffer_index))
                    size = (s->cd_sector_size - s->io_buffer_index);
            }
            ide_transfer_start(s, s->io_buffer + s->io_buffer_index, 
                               size, ide_atapi_cmd_reply_end);
            s->packet_transfer_size -= size;
            s->elementary_transfer_size -= size;
            s->io_buffer_index += size;
            ide_set_irq(s);
#ifdef DEBUG_IDE_ATAPI
            printf("status=0x%x\n", s->status);
#endif
        }
    }
}

/* send a reply of 'size' bytes in s->io_buffer to an ATAPI command */
static void ide_atapi_cmd_reply(IDEState *s, int size, int max_size)
{
    if (size > max_size)
        size = max_size;
    s->lba = -1; /* no sector read */
    s->packet_transfer_size = size;
    s->elementary_transfer_size = 0;
    s->io_buffer_index = 0;

    s->status = READY_STAT;
    ide_atapi_cmd_reply_end(s);
}

/* start a CD-CDROM read command */
static void ide_atapi_cmd_read_pio(IDEState *s, int lba, int nb_sectors,
                                   int sector_size)
{
    s->lba = lba;
    s->packet_transfer_size = nb_sectors * sector_size;
    s->elementary_transfer_size = 0;
    s->io_buffer_index = sector_size;
    s->cd_sector_size = sector_size;

    s->status = READY_STAT;
    ide_atapi_cmd_reply_end(s);
}

/* ATAPI DMA support */
static int ide_atapi_cmd_read_dma_cb(IDEState *s, 
                                     target_phys_addr_t phys_addr, 
                                     int transfer_size1)
{
    int len, transfer_size;
    
    transfer_size = transfer_size1;
    while (transfer_size > 0) {
        if (s->packet_transfer_size <= 0)
            break;
        len = s->cd_sector_size - s->io_buffer_index;
        if (len <= 0) {
            /* transfert next data */
            cd_read_sector(s->bs, s->lba, s->io_buffer, s->cd_sector_size);
            s->lba++;
            s->io_buffer_index = 0;
            len = s->cd_sector_size;
        }
        if (len > transfer_size)
            len = transfer_size;
        cpu_physical_memory_write(phys_addr, 
                                  s->io_buffer + s->io_buffer_index, len);
        s->packet_transfer_size -= len;
        s->io_buffer_index += len;
        transfer_size -= len;
        phys_addr += len;
    }
    if (s->packet_transfer_size <= 0) {
        s->status = READY_STAT;
        s->nsector = (s->nsector & ~7) | ATAPI_INT_REASON_IO | ATAPI_INT_REASON_CD;
        ide_set_irq(s);
#ifdef DEBUG_IDE_ATAPI
        printf("dma status=0x%x\n", s->status);
#endif
        return 0;
    }
    return transfer_size1 - transfer_size;
}

/* start a CD-CDROM read command with DMA */
/* XXX: test if DMA is available */
static void ide_atapi_cmd_read_dma(IDEState *s, int lba, int nb_sectors,
                                   int sector_size)
{
    s->lba = lba;
    s->packet_transfer_size = nb_sectors * sector_size;
    s->io_buffer_index = sector_size;
    s->cd_sector_size = sector_size;

    s->status = READY_STAT | DRQ_STAT;
    ide_dma_start(s, ide_atapi_cmd_read_dma_cb);
}

static void ide_atapi_cmd_read(IDEState *s, int lba, int nb_sectors, 
                               int sector_size)
{
#ifdef DEBUG_IDE_ATAPI
    printf("read: LBA=%d nb_sectors=%d\n", lba, nb_sectors);
#endif
    if (s->atapi_dma) {
        ide_atapi_cmd_read_dma(s, lba, nb_sectors, sector_size);
    } else {
        ide_atapi_cmd_read_pio(s, lba, nb_sectors, sector_size);
    }
}

/* same toc as bochs. Return -1 if error or the toc length */
/* XXX: check this */
static int cdrom_read_toc(IDEState *s, uint8_t *buf, int msf, int start_track)
{
    uint8_t *q;
    int nb_sectors, len;
    
    if (start_track > 1 && start_track != 0xaa)
        return -1;
    q = buf + 2;
    *q++ = 1; /* first session */
    *q++ = 1; /* last session */
    if (start_track <= 1) {
        *q++ = 0; /* reserved */
        *q++ = 0x14; /* ADR, control */
        *q++ = 1;    /* track number */
        *q++ = 0; /* reserved */
        if (msf) {
            *q++ = 0; /* reserved */
            *q++ = 0; /* minute */
            *q++ = 2; /* second */
            *q++ = 0; /* frame */
        } else {
            /* sector 0 */
            cpu_to_ube32(q, 0);
            q += 4;
        }
    }
    /* lead out track */
    *q++ = 0; /* reserved */
    *q++ = 0x16; /* ADR, control */
    *q++ = 0xaa; /* track number */
    *q++ = 0; /* reserved */
    nb_sectors = s->nb_sectors >> 2;
    if (msf) {
        *q++ = 0; /* reserved */
        lba_to_msf(q, nb_sectors);
        q += 3;
    } else {
        cpu_to_ube32(q, nb_sectors);
        q += 4;
    }
    len = q - buf;
    cpu_to_ube16(buf, len - 2);
    return len;
}

/* mostly same info as PearPc */
static int cdrom_read_toc_raw(IDEState *s, uint8_t *buf, int msf, 
                              int session_num)
{
    uint8_t *q;
    int nb_sectors, len;
    
    q = buf + 2;
    *q++ = 1; /* first session */
    *q++ = 1; /* last session */

    *q++ = 1; /* session number */
    *q++ = 0x14; /* data track */
    *q++ = 0; /* track number */
    *q++ = 0xa0; /* lead-in */
    *q++ = 0; /* min */
    *q++ = 0; /* sec */
    *q++ = 0; /* frame */
    *q++ = 0;
    *q++ = 1; /* first track */
    *q++ = 0x00; /* disk type */
    *q++ = 0x00;
    
    *q++ = 1; /* session number */
    *q++ = 0x14; /* data track */
    *q++ = 0; /* track number */
    *q++ = 0xa1;
    *q++ = 0; /* min */
    *q++ = 0; /* sec */
    *q++ = 0; /* frame */
    *q++ = 0;
    *q++ = 1; /* last track */
    *q++ = 0x00;
    *q++ = 0x00;
    
    *q++ = 1; /* session number */
    *q++ = 0x14; /* data track */
    *q++ = 0; /* track number */
    *q++ = 0xa2; /* lead-out */
    *q++ = 0; /* min */
    *q++ = 0; /* sec */
    *q++ = 0; /* frame */
    nb_sectors = s->nb_sectors >> 2;
    if (msf) {
        *q++ = 0; /* reserved */
        lba_to_msf(q, nb_sectors);
        q += 3;
    } else {
        cpu_to_ube32(q, nb_sectors);
        q += 4;
    }

    *q++ = 1; /* session number */
    *q++ = 0x14; /* ADR, control */
    *q++ = 0;    /* track number */
    *q++ = 1;    /* point */
    *q++ = 0; /* min */
    *q++ = 0; /* sec */
    *q++ = 0; /* frame */
    *q++ = 0; 
    *q++ = 0; 
    *q++ = 0; 
    *q++ = 0; 

    len = q - buf;
    cpu_to_ube16(buf, len - 2);
    return len;
}

static void ide_atapi_cmd(IDEState *s)
{
    const uint8_t *packet;
    uint8_t *buf;
    int max_len;

    packet = s->io_buffer;
    buf = s->io_buffer;
#ifdef DEBUG_IDE_ATAPI
    {
        int i;
        printf("ATAPI limit=0x%x packet:", s->lcyl | (s->hcyl << 8));
        for(i = 0; i < ATAPI_PACKET_SIZE; i++) {
            printf(" %02x", packet[i]);
        }
        printf("\n");
    }
#endif
    switch(s->io_buffer[0]) {
    case GPCMD_TEST_UNIT_READY:
        if (bdrv_is_inserted(s->bs)) {
            ide_atapi_cmd_ok(s);
        } else {
            ide_atapi_cmd_error(s, SENSE_NOT_READY, 
                                ASC_MEDIUM_NOT_PRESENT);
        }
        break;
    case GPCMD_MODE_SENSE_10:
        {
            int action, code;
            max_len = ube16_to_cpu(packet + 7);
            action = packet[2] >> 6;
            code = packet[2] & 0x3f;
            switch(action) {
            case 0: /* current values */
                switch(code) {
                case 0x01: /* error recovery */
                    cpu_to_ube16(&buf[0], 16 + 6);
                    buf[2] = 0x70;
                    buf[3] = 0;
                    buf[4] = 0;
                    buf[5] = 0;
                    buf[6] = 0;
                    buf[7] = 0;

                    buf[8] = 0x01;
                    buf[9] = 0x06;
                    buf[10] = 0x00;
                    buf[11] = 0x05;
                    buf[12] = 0x00;
                    buf[13] = 0x00;
                    buf[14] = 0x00;
                    buf[15] = 0x00;
                    ide_atapi_cmd_reply(s, 16, max_len);
                    break;
                case 0x2a:
                    cpu_to_ube16(&buf[0], 28 + 6);
                    buf[2] = 0x70;
                    buf[3] = 0;
                    buf[4] = 0;
                    buf[5] = 0;
                    buf[6] = 0;
                    buf[7] = 0;

                    buf[8] = 0x2a;
                    buf[9] = 0x12;
                    buf[10] = 0x00;
                    buf[11] = 0x00;
                    
                    buf[12] = 0x70;
                    buf[13] = 3 << 5;
                    buf[14] = (1 << 0) | (1 << 3) | (1 << 5);
                    if (bdrv_is_locked(s->bs))
                        buf[6] |= 1 << 1;
                    buf[15] = 0x00;
                    cpu_to_ube16(&buf[16], 706);
                    buf[18] = 0;
                    buf[19] = 2;
                    cpu_to_ube16(&buf[20], 512);
                    cpu_to_ube16(&buf[22], 706);
                    buf[24] = 0;
                    buf[25] = 0;
                    buf[26] = 0;
                    buf[27] = 0;
                    ide_atapi_cmd_reply(s, 28, max_len);
                    break;
                default:
                    goto error_cmd;
                }
                break;
            case 1: /* changeable values */
                goto error_cmd;
            case 2: /* default values */
                goto error_cmd;
            default:
            case 3: /* saved values */
                ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST, 
                                    ASC_SAVING_PARAMETERS_NOT_SUPPORTED);
                break;
            }
        }
        break;
    case GPCMD_REQUEST_SENSE:
        max_len = packet[4];
        memset(buf, 0, 18);
        buf[0] = 0x70 | (1 << 7);
        buf[2] = s->sense_key;
        buf[7] = 10;
        buf[12] = s->asc;
        ide_atapi_cmd_reply(s, 18, max_len);
        break;
    case GPCMD_PREVENT_ALLOW_MEDIUM_REMOVAL:
        if (bdrv_is_inserted(s->bs)) {
            bdrv_set_locked(s->bs, packet[4] & 1);
            ide_atapi_cmd_ok(s);
        } else {
            ide_atapi_cmd_error(s, SENSE_NOT_READY, 
                                ASC_MEDIUM_NOT_PRESENT);
        }
        break;
    case GPCMD_READ_10:
    case GPCMD_READ_12:
        {
            int nb_sectors, lba;

            if (!bdrv_is_inserted(s->bs)) {
                ide_atapi_cmd_error(s, SENSE_NOT_READY, 
                                    ASC_MEDIUM_NOT_PRESENT);
                break;
            }
            if (packet[0] == GPCMD_READ_10)
                nb_sectors = ube16_to_cpu(packet + 7);
            else
                nb_sectors = ube32_to_cpu(packet + 6);
            lba = ube32_to_cpu(packet + 2);
            if (nb_sectors == 0) {
                ide_atapi_cmd_ok(s);
                break;
            }
            if (((int64_t)(lba + nb_sectors) << 2) > s->nb_sectors) {
                ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST, 
                                    ASC_LOGICAL_BLOCK_OOR);
                break;
            }
            ide_atapi_cmd_read(s, lba, nb_sectors, 2048);
        }
        break;
    case GPCMD_READ_CD:
        {
            int nb_sectors, lba, transfer_request;

            if (!bdrv_is_inserted(s->bs)) {
                ide_atapi_cmd_error(s, SENSE_NOT_READY, 
                                    ASC_MEDIUM_NOT_PRESENT);
                break;
            }
            nb_sectors = (packet[6] << 16) | (packet[7] << 8) | packet[8];
            lba = ube32_to_cpu(packet + 2);
            if (nb_sectors == 0) {
                ide_atapi_cmd_ok(s);
                break;
            }
            if (((int64_t)(lba + nb_sectors) << 2) > s->nb_sectors) {
                ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST, 
                                    ASC_LOGICAL_BLOCK_OOR);
                break;
            }
            transfer_request = packet[9];
            switch(transfer_request & 0xf8) {
            case 0x00:
                /* nothing */
                ide_atapi_cmd_ok(s);
                break;
            case 0x10:
                /* normal read */
                ide_atapi_cmd_read(s, lba, nb_sectors, 2048);
                break;
            case 0xf8:
                /* read all data */
                ide_atapi_cmd_read(s, lba, nb_sectors, 2352);
                break;
            default:
                ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST, 
                                    ASC_INV_FIELD_IN_CMD_PACKET);
                break;
            }
        }
        break;
    case GPCMD_SEEK:
        {
            int lba;
            if (!bdrv_is_inserted(s->bs)) {
                ide_atapi_cmd_error(s, SENSE_NOT_READY, 
                                    ASC_MEDIUM_NOT_PRESENT);
                break;
            }
            lba = ube32_to_cpu(packet + 2);
            if (((int64_t)lba << 2) > s->nb_sectors) {
                ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST, 
                                    ASC_LOGICAL_BLOCK_OOR);
                break;
            }
            ide_atapi_cmd_ok(s);
        }
        break;
    case GPCMD_START_STOP_UNIT:
        {
            int start, eject;
            start = packet[4] & 1;
            eject = (packet[4] >> 1) & 1;
            
            if (eject && !start) {
                /* eject the disk */
                bdrv_close(s->bs);
            }
            ide_atapi_cmd_ok(s);
        }
        break;
    case GPCMD_MECHANISM_STATUS:
        {
            max_len = ube16_to_cpu(packet + 8);
            cpu_to_ube16(buf, 0);
            /* no current LBA */
            buf[2] = 0;
            buf[3] = 0;
            buf[4] = 0;
            buf[5] = 1;
            cpu_to_ube16(buf + 6, 0);
            ide_atapi_cmd_reply(s, 8, max_len);
        }
        break;
    case GPCMD_READ_TOC_PMA_ATIP:
        {
            int format, msf, start_track, len;

            if (!bdrv_is_inserted(s->bs)) {
                ide_atapi_cmd_error(s, SENSE_NOT_READY, 
                                    ASC_MEDIUM_NOT_PRESENT);
                break;
            }
            max_len = ube16_to_cpu(packet + 7);
            format = packet[9] >> 6;
            msf = (packet[1] >> 1) & 1;
            start_track = packet[6];
            switch(format) {
            case 0:
                len = cdrom_read_toc(s, buf, msf, start_track);
                if (len < 0)
                    goto error_cmd;
                ide_atapi_cmd_reply(s, len, max_len);
                break;
            case 1:
                /* multi session : only a single session defined */
                memset(buf, 0, 12);
                buf[1] = 0x0a;
                buf[2] = 0x01;
                buf[3] = 0x01;
                ide_atapi_cmd_reply(s, 12, max_len);
                break;
            case 2:
                len = cdrom_read_toc_raw(s, buf, msf, start_track);
                if (len < 0)
                    goto error_cmd;
                ide_atapi_cmd_reply(s, len, max_len);
                break;
            default:
            error_cmd:
                ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST, 
                                    ASC_INV_FIELD_IN_CMD_PACKET);
                break;
            }
        }
        break;
    case GPCMD_READ_CDVD_CAPACITY:
        if (!bdrv_is_inserted(s->bs)) {
            ide_atapi_cmd_error(s, SENSE_NOT_READY, 
                                ASC_MEDIUM_NOT_PRESENT);
            break;
        }
        /* NOTE: it is really the number of sectors minus 1 */
        cpu_to_ube32(buf, (s->nb_sectors >> 2) - 1);
        cpu_to_ube32(buf + 4, 2048);
        ide_atapi_cmd_reply(s, 8, 8);
        break;
    case GPCMD_INQUIRY:
        max_len = packet[4];
        buf[0] = 0x05; /* CD-ROM */
        buf[1] = 0x80; /* removable */
        buf[2] = 0x00; /* ISO */
        buf[3] = 0x21; /* ATAPI-2 (XXX: put ATAPI-4 ?) */
        buf[4] = 31; /* additionnal length */
        buf[5] = 0; /* reserved */
        buf[6] = 0; /* reserved */
        buf[7] = 0; /* reserved */
        padstr8(buf + 8, 8, "QEMU");
        padstr8(buf + 16, 16, "QEMU CD-ROM");
        padstr8(buf + 32, 4, QEMU_VERSION);
        ide_atapi_cmd_reply(s, 36, max_len);
        break;
    default:
        ide_atapi_cmd_error(s, SENSE_ILLEGAL_REQUEST, 
                            ASC_ILLEGAL_OPCODE);
        break;
    }
}

/* called when the inserted state of the media has changed */
static void cdrom_change_cb(void *opaque)
{
    IDEState *s = opaque;
    int64_t nb_sectors;

    /* XXX: send interrupt too */
    bdrv_get_geometry(s->bs, &nb_sectors);
    s->nb_sectors = nb_sectors;
}

static void ide_ioport_write(void *opaque, uint32_t addr, uint32_t val)
{
    IDEState *ide_if = opaque;
    IDEState *s;
    int unit, n;

#ifdef DEBUG_IDE
    printf("IDE: write addr=0x%x val=0x%02x\n", addr, val);
#endif
    addr &= 7;
    switch(addr) {
    case 0:
        break;
    case 1:
        /* NOTE: data is written to the two drives */
        ide_if[0].feature = val;
        ide_if[1].feature = val;
        break;
    case 2:
        if (val == 0)
            val = 256;
        ide_if[0].nsector = val;
        ide_if[1].nsector = val;
        break;
    case 3:
        ide_if[0].sector = val;
        ide_if[1].sector = val;
        break;
    case 4:
        ide_if[0].lcyl = val;
        ide_if[1].lcyl = val;
        break;
    case 5:
        ide_if[0].hcyl = val;
        ide_if[1].hcyl = val;
        break;
    case 6:
        ide_if[0].select = (val & ~0x10) | 0xa0;
        ide_if[1].select = (val | 0x10) | 0xa0;
        /* select drive */
        unit = (val >> 4) & 1;
        s = ide_if + unit;
        ide_if->cur_drive = s;
        break;
    default:
    case 7:
        /* command */
#if defined(DEBUG_IDE)
        printf("ide: CMD=%02x\n", val);
#endif
        s = ide_if->cur_drive;
        /* ignore commands to non existant slave */
        if (s != ide_if && !s->bs) 
            break;
        switch(val) {
        case WIN_IDENTIFY:
            if (s->bs && !s->is_cdrom) {
                ide_identify(s);
                s->status = READY_STAT | SEEK_STAT;
                ide_transfer_start(s, s->io_buffer, 512, ide_transfer_stop);
            } else {
                if (s->is_cdrom) {
                    ide_set_signature(s);
                }
                ide_abort_command(s);
            }
            ide_set_irq(s);
            break;
        case WIN_SPECIFY:
        case WIN_RECAL:
            s->error = 0;
            s->status = READY_STAT;
            ide_set_irq(s);
            break;
        case WIN_SETMULT:
            if (s->nsector > MAX_MULT_SECTORS || 
                s->nsector == 0 ||
                (s->nsector & (s->nsector - 1)) != 0) {
                ide_abort_command(s);
            } else {
                s->mult_sectors = s->nsector;
                s->status = READY_STAT;
            }
            ide_set_irq(s);
            break;
        case WIN_VERIFY:
        case WIN_VERIFY_ONCE:
            /* do sector number check ? */
            s->status = READY_STAT;
            ide_set_irq(s);
            break;
        case WIN_READ:
        case WIN_READ_ONCE:
            if (!s->bs) 
                goto abort_cmd;
            s->req_nb_sectors = 1;
            ide_sector_read(s);
            break;
        case WIN_WRITE:
        case WIN_WRITE_ONCE:
            s->error = 0;
            s->status = SEEK_STAT | READY_STAT;
            s->req_nb_sectors = 1;
            ide_transfer_start(s, s->io_buffer, 512, ide_sector_write);
            break;
        case WIN_MULTREAD:
            if (!s->mult_sectors)
                goto abort_cmd;
            s->req_nb_sectors = s->mult_sectors;
            ide_sector_read(s);
            break;
        case WIN_MULTWRITE:
            if (!s->mult_sectors)
                goto abort_cmd;
            s->error = 0;
            s->status = SEEK_STAT | READY_STAT;
            s->req_nb_sectors = s->mult_sectors;
            n = s->nsector;
            if (n > s->req_nb_sectors)
                n = s->req_nb_sectors;
            ide_transfer_start(s, s->io_buffer, 512 * n, ide_sector_write);
            break;
        case WIN_READDMA:
        case WIN_READDMA_ONCE:
            if (!s->bs) 
                goto abort_cmd;
            ide_sector_read_dma(s);
            break;
        case WIN_WRITEDMA:
        case WIN_WRITEDMA_ONCE:
            if (!s->bs) 
                goto abort_cmd;
            ide_sector_write_dma(s);
            break;
        case WIN_READ_NATIVE_MAX:
            ide_set_sector(s, s->nb_sectors - 1);
            s->status = READY_STAT;
            ide_set_irq(s);
            break;
        case WIN_CHECKPOWERMODE1:
            s->nsector = 0xff; /* device active or idle */
            s->status = READY_STAT;
            ide_set_irq(s);
            break;
        case WIN_SETFEATURES:
            if (!s->bs)
                goto abort_cmd;
            /* XXX: valid for CDROM ? */
            switch(s->feature) {
            case 0x02: /* write cache enable */
            case 0x03: /* set transfer mode */
            case 0x82: /* write cache disable */
            case 0xaa: /* read look-ahead enable */
            case 0x55: /* read look-ahead disable */
                s->status = READY_STAT;
                ide_set_irq(s);
                break;
            default:
                goto abort_cmd;
            }
            break;
            /* ATAPI commands */
        case WIN_PIDENTIFY:
            if (s->is_cdrom) {
                ide_atapi_identify(s);
                s->status = READY_STAT;
                ide_transfer_start(s, s->io_buffer, 512, ide_transfer_stop);
            } else {
                ide_abort_command(s);
            }
            ide_set_irq(s);
            break;
        case WIN_SRST:
            if (!s->is_cdrom)
                goto abort_cmd;
            ide_set_signature(s);
            s->status = 0x00; /* NOTE: READY is _not_ set */
            s->error = 0x01;
            break;
        case WIN_PACKETCMD:
            if (!s->is_cdrom)
                goto abort_cmd;
            /* overlapping commands not supported */
            if (s->feature & 0x02)
                goto abort_cmd;
            s->atapi_dma = s->feature & 1;
            s->nsector = 1;
            ide_transfer_start(s, s->io_buffer, ATAPI_PACKET_SIZE, 
                               ide_atapi_cmd);
            break;
        default:
        abort_cmd:
            ide_abort_command(s);
            ide_set_irq(s);
            break;
        }
    }
}

static uint32_t ide_ioport_read(void *opaque, uint32_t addr1)
{
    IDEState *ide_if = opaque;
    IDEState *s = ide_if->cur_drive;
    uint32_t addr;
    int ret;

    addr = addr1 & 7;
    switch(addr) {
    case 0:
        ret = 0xff;
        break;
    case 1:
        if (!ide_if[0].bs && !ide_if[1].bs)
            ret = 0;
        else
            ret = s->error;
        break;
    case 2:
        if (!ide_if[0].bs && !ide_if[1].bs)
            ret = 0;
        else
            ret = s->nsector & 0xff;
        break;
    case 3:
        if (!ide_if[0].bs && !ide_if[1].bs)
            ret = 0;
        else
            ret = s->sector;
        break;
    case 4:
        if (!ide_if[0].bs && !ide_if[1].bs)
            ret = 0;
        else
            ret = s->lcyl;
        break;
    case 5:
        if (!ide_if[0].bs && !ide_if[1].bs)
            ret = 0;
        else
            ret = s->hcyl;
        break;
    case 6:
        if (!ide_if[0].bs && !ide_if[1].bs)
            ret = 0;
        else
            ret = s->select;
        break;
    default:
    case 7:
        if ((!ide_if[0].bs && !ide_if[1].bs) ||
            (s != ide_if && !s->bs))
            ret = 0;
        else
            ret = s->status;
#ifdef TARGET_PPC
        if (s->openpic) 
            openpic_set_irq(s->openpic, s->irq, 0);
        else 
#endif
        if (s->irq == 16)
            pci_set_irq(s->pci_dev, 0, 0);
        else
            pic_set_irq(s->irq, 0);
        break;
    }
#ifdef DEBUG_IDE
    printf("ide: read addr=0x%x val=%02x\n", addr1, ret);
#endif
    return ret;
}

static uint32_t ide_status_read(void *opaque, uint32_t addr)
{
    IDEState *ide_if = opaque;
    IDEState *s = ide_if->cur_drive;
    int ret;

    if ((!ide_if[0].bs && !ide_if[1].bs) ||
        (s != ide_if && !s->bs))
        ret = 0;
    else
        ret = s->status;
#ifdef DEBUG_IDE
    printf("ide: read status addr=0x%x val=%02x\n", addr, ret);
#endif
    return ret;
}

static void ide_cmd_write(void *opaque, uint32_t addr, uint32_t val)
{
    IDEState *ide_if = opaque;
    IDEState *s;
    int i;

#ifdef DEBUG_IDE
    printf("ide: write control addr=0x%x val=%02x\n", addr, val);
#endif
    /* common for both drives */
    if (!(ide_if[0].cmd & IDE_CMD_RESET) &&
        (val & IDE_CMD_RESET)) {
        /* reset low to high */
        for(i = 0;i < 2; i++) {
            s = &ide_if[i];
            s->status = BUSY_STAT | SEEK_STAT;
            s->error = 0x01;
        }
    } else if ((ide_if[0].cmd & IDE_CMD_RESET) &&
               !(val & IDE_CMD_RESET)) {
        /* high to low */
        for(i = 0;i < 2; i++) {
            s = &ide_if[i];
            if (s->is_cdrom)
                s->status = 0x00; /* NOTE: READY is _not_ set */
            else
                s->status = READY_STAT | SEEK_STAT;
            ide_set_signature(s);
        }
    }

    ide_if[0].cmd = val;
    ide_if[1].cmd = val;
}

static void ide_data_writew(void *opaque, uint32_t addr, uint32_t val)
{
    IDEState *s = ((IDEState *)opaque)->cur_drive;
    uint8_t *p;

    p = s->data_ptr;
    *(uint16_t *)p = le16_to_cpu(val);
    p += 2;
    s->data_ptr = p;
    if (p >= s->data_end)
        s->end_transfer_func(s);
}

static uint32_t ide_data_readw(void *opaque, uint32_t addr)
{
    IDEState *s = ((IDEState *)opaque)->cur_drive;
    uint8_t *p;
    int ret;
    p = s->data_ptr;
    ret = cpu_to_le16(*(uint16_t *)p);
    p += 2;
    s->data_ptr = p;
    if (p >= s->data_end)
        s->end_transfer_func(s);
    return ret;
}

static void ide_data_writel(void *opaque, uint32_t addr, uint32_t val)
{
    IDEState *s = ((IDEState *)opaque)->cur_drive;
    uint8_t *p;

    p = s->data_ptr;
    *(uint32_t *)p = le32_to_cpu(val);
    p += 4;
    s->data_ptr = p;
    if (p >= s->data_end)
        s->end_transfer_func(s);
}

static uint32_t ide_data_readl(void *opaque, uint32_t addr)
{
    IDEState *s = ((IDEState *)opaque)->cur_drive;
    uint8_t *p;
    int ret;
    
    p = s->data_ptr;
    ret = cpu_to_le32(*(uint32_t *)p);
    p += 4;
    s->data_ptr = p;
    if (p >= s->data_end)
        s->end_transfer_func(s);
    return ret;
}

static void ide_reset(IDEState *s)
{
    s->mult_sectors = MAX_MULT_SECTORS;
    s->cur_drive = s;
    s->select = 0xa0;
    s->status = READY_STAT;
    ide_set_signature(s);
}

struct partition {
	uint8_t boot_ind;		/* 0x80 - active */
	uint8_t head;		/* starting head */
	uint8_t sector;		/* starting sector */
	uint8_t cyl;		/* starting cylinder */
	uint8_t sys_ind;		/* What partition type */
	uint8_t end_head;		/* end head */
	uint8_t end_sector;	/* end sector */
	uint8_t end_cyl;		/* end cylinder */
	uint32_t start_sect;	/* starting sector counting from 0 */
	uint32_t nr_sects;		/* nr of sectors in partition */
} __attribute__((packed));

/* try to guess the IDE geometry from the MSDOS partition table */
static void ide_guess_geometry(IDEState *s)
{
    uint8_t buf[512];
    int ret, i;
    struct partition *p;
    uint32_t nr_sects;

    if (s->cylinders != 0)
        return;
    ret = bdrv_read(s->bs, 0, buf, 1);
    if (ret < 0)
        return;
    /* test msdos magic */
    if (buf[510] != 0x55 || buf[511] != 0xaa)
        return;
    for(i = 0; i < 4; i++) {
        p = ((struct partition *)(buf + 0x1be)) + i;
        nr_sects = le32_to_cpu(p->nr_sects);
        if (nr_sects && p->end_head) {
            /* We make the assumption that the partition terminates on
               a cylinder boundary */
            s->heads = p->end_head + 1;
            s->sectors = p->end_sector & 63;
            s->cylinders = s->nb_sectors / (s->heads * s->sectors);
#if 0
            printf("guessed partition: CHS=%d %d %d\n", 
                   s->cylinders, s->heads, s->sectors);
#endif
        }
    }
}

static void ide_init2(IDEState *ide_state, int irq,
                      BlockDriverState *hd0, BlockDriverState *hd1)
{
    IDEState *s;
    static int drive_serial = 1;
    int i, cylinders, heads, secs;
    int64_t nb_sectors;

    for(i = 0; i < 2; i++) {
        s = ide_state + i;
        if (i == 0)
            s->bs = hd0;
        else
            s->bs = hd1;
        if (s->bs) {
            bdrv_get_geometry(s->bs, &nb_sectors);
            s->nb_sectors = nb_sectors;
            /* if a geometry hint is available, use it */
            bdrv_get_geometry_hint(s->bs, &cylinders, &heads, &secs);
            if (cylinders != 0) {
                s->cylinders = cylinders;
                s->heads = heads;
                s->sectors = secs;
            } else {
                ide_guess_geometry(s);
                if (s->cylinders == 0) {
                    /* if no geometry, use a LBA compatible one */
                    cylinders = nb_sectors / (16 * 63);
                    if (cylinders > 16383)
                        cylinders = 16383;
                    else if (cylinders < 2)
                        cylinders = 2;
                    s->cylinders = cylinders;
                    s->heads = 16;
                    s->sectors = 63;
                }
            }
            if (bdrv_get_type_hint(s->bs) == BDRV_TYPE_CDROM) {
                s->is_cdrom = 1;
                bdrv_set_change_cb(s->bs, cdrom_change_cb, s);
            }
        }
        s->drive_serial = drive_serial++;
        s->irq = irq;
        ide_reset(s);
    }
}

static void ide_init_ioport(IDEState *ide_state, int iobase, int iobase2)
{
    register_ioport_write(iobase, 8, 1, ide_ioport_write, ide_state);
    register_ioport_read(iobase, 8, 1, ide_ioport_read, ide_state);
    if (iobase2) {
        register_ioport_read(iobase2, 1, 1, ide_status_read, ide_state);
        register_ioport_write(iobase2, 1, 1, ide_cmd_write, ide_state);
    }
    
    /* data ports */
    register_ioport_write(iobase, 2, 2, ide_data_writew, ide_state);
    register_ioport_read(iobase, 2, 2, ide_data_readw, ide_state);
    register_ioport_write(iobase, 4, 4, ide_data_writel, ide_state);
    register_ioport_read(iobase, 4, 4, ide_data_readl, ide_state);
}

/***********************************************************/
/* ISA IDE definitions */

void isa_ide_init(int iobase, int iobase2, int irq,
                  BlockDriverState *hd0, BlockDriverState *hd1)
{
    IDEState *ide_state;

    ide_state = qemu_mallocz(sizeof(IDEState) * 2);
    if (!ide_state)
        return;
    
    ide_init2(ide_state, irq, hd0, hd1);
    ide_init_ioport(ide_state, iobase, iobase2);
}

/***********************************************************/
/* PCI IDE definitions */

static void ide_map(PCIDevice *pci_dev, int region_num, 
                    uint32_t addr, uint32_t size, int type)
{
    PCIIDEState *d = (PCIIDEState *)pci_dev;
    IDEState *ide_state;

    if (region_num <= 3) {
        ide_state = &d->ide_if[(region_num >> 1) * 2];
        if (region_num & 1) {
            register_ioport_read(addr + 2, 1, 1, ide_status_read, ide_state);
            register_ioport_write(addr + 2, 1, 1, ide_cmd_write, ide_state);
        } else {
            register_ioport_write(addr, 8, 1, ide_ioport_write, ide_state);
            register_ioport_read(addr, 8, 1, ide_ioport_read, ide_state);

            /* data ports */
            register_ioport_write(addr, 2, 2, ide_data_writew, ide_state);
            register_ioport_read(addr, 2, 2, ide_data_readw, ide_state);
            register_ioport_write(addr, 4, 4, ide_data_writel, ide_state);
            register_ioport_read(addr, 4, 4, ide_data_readl, ide_state);
        }
    }
}

/* XXX: full callback usage to prepare non blocking I/Os support -
   error handling */
static void ide_dma_loop(BMDMAState *bm)
{
    struct {
        uint32_t addr;
        uint32_t size;
    } prd;
    target_phys_addr_t cur_addr;
    int len, i, len1;

    cur_addr = bm->addr;
    /* at most one page to avoid hanging if erroneous parameters */
    for(i = 0; i < 512; i++) {
        cpu_physical_memory_read(cur_addr, (uint8_t *)&prd, 8);
        prd.addr = le32_to_cpu(prd.addr);
        prd.size = le32_to_cpu(prd.size);
#ifdef DEBUG_IDE
        printf("ide: dma: prd: %08x: addr=0x%08x size=0x%08x\n", 
               (int)cur_addr, prd.addr, prd.size);
#endif
        len = prd.size & 0xfffe;
        if (len == 0)
            len = 0x10000;
        while (len > 0) {
            len1 = bm->dma_cb(bm->ide_if, prd.addr, len);
            if (len1 == 0)
                goto the_end;
            prd.addr += len1;
            len -= len1;
        }
        /* end of transfer */
        if (prd.size & 0x80000000)
            break;
        cur_addr += 8;
    }
    /* end of transfer */
 the_end:
    bm->status &= ~BM_STATUS_DMAING;
    bm->status |= BM_STATUS_INT;
    bm->dma_cb = NULL;
    bm->ide_if = NULL;
}

static void ide_dma_start(IDEState *s, IDEDMAFunc *dma_cb)
{
    BMDMAState *bm = s->bmdma;
    if(!bm)
        return;
    bm->ide_if = s;
    bm->dma_cb = dma_cb;
    if (bm->status & BM_STATUS_DMAING) {
        ide_dma_loop(bm);
    }
}

static uint32_t bmdma_cmd_readb(void *opaque, uint32_t addr)
{
    BMDMAState *bm = opaque;
    uint32_t val;
    val = bm->cmd;
#ifdef DEBUG_IDE
    printf("%s: 0x%08x\n", __func__, val);
#endif
    return val;
}

static void bmdma_cmd_writeb(void *opaque, uint32_t addr, uint32_t val)
{
    BMDMAState *bm = opaque;
#ifdef DEBUG_IDE
    printf("%s: 0x%08x\n", __func__, val);
#endif
    if (!(val & BM_CMD_START)) {
        /* XXX: do it better */
        bm->status &= ~BM_STATUS_DMAING;
        bm->cmd = val & 0x09;
    } else {
        bm->status |= BM_STATUS_DMAING;
        bm->cmd = val & 0x09;
        /* start dma transfer if possible */
        if (bm->dma_cb)
            ide_dma_loop(bm);
    }
}

static uint32_t bmdma_status_readb(void *opaque, uint32_t addr)
{
    BMDMAState *bm = opaque;
    uint32_t val;
    val = bm->status;
#ifdef DEBUG_IDE
    printf("%s: 0x%08x\n", __func__, val);
#endif
    return val;
}

static void bmdma_status_writeb(void *opaque, uint32_t addr, uint32_t val)
{
    BMDMAState *bm = opaque;
#ifdef DEBUG_IDE
    printf("%s: 0x%08x\n", __func__, val);
#endif
    bm->status = (val & 0x60) | (bm->status & 1) | (bm->status & ~val & 0x06);
}

static uint32_t bmdma_addr_readl(void *opaque, uint32_t addr)
{
    BMDMAState *bm = opaque;
    uint32_t val;
    val = bm->addr;
#ifdef DEBUG_IDE
    printf("%s: 0x%08x\n", __func__, val);
#endif
    return val;
}

static void bmdma_addr_writel(void *opaque, uint32_t addr, uint32_t val)
{
    BMDMAState *bm = opaque;
#ifdef DEBUG_IDE
    printf("%s: 0x%08x\n", __func__, val);
#endif
    bm->addr = val & ~3;
}

static void bmdma_map(PCIDevice *pci_dev, int region_num, 
                    uint32_t addr, uint32_t size, int type)
{
    PCIIDEState *d = (PCIIDEState *)pci_dev;
    int i;

    for(i = 0;i < 2; i++) {
        BMDMAState *bm = &d->bmdma[i];
        d->ide_if[2 * i].bmdma = bm;
        d->ide_if[2 * i + 1].bmdma = bm;
        
        register_ioport_write(addr, 1, 1, bmdma_cmd_writeb, bm);
        register_ioport_read(addr, 1, 1, bmdma_cmd_readb, bm);

        register_ioport_write(addr + 2, 1, 1, bmdma_status_writeb, bm);
        register_ioport_read(addr + 2, 1, 1, bmdma_status_readb, bm);

        register_ioport_write(addr + 4, 4, 4, bmdma_addr_writel, bm);
        register_ioport_read(addr + 4, 4, 4, bmdma_addr_readl, bm);
        addr += 8;
    }
}

/* hd_table must contain 4 block drivers */
void pci_ide_init(PCIBus *bus, BlockDriverState **hd_table)
{
    PCIIDEState *d;
    uint8_t *pci_conf;
    int i;

    d = (PCIIDEState *)pci_register_device(bus, "IDE", sizeof(PCIIDEState),
                                           -1, 
                                           NULL, NULL);
    pci_conf = d->dev.config;
    pci_conf[0x00] = 0x86; // Intel
    pci_conf[0x01] = 0x80;
    pci_conf[0x02] = 0x00; // fake
    pci_conf[0x03] = 0x01; // fake
    pci_conf[0x0a] = 0x01; // class_sub = PCI_IDE
    pci_conf[0x0b] = 0x01; // class_base = PCI_mass_storage
    pci_conf[0x0e] = 0x80; // header_type = PCI_multifunction, generic

    pci_conf[0x2c] = 0x86; // subsys vendor
    pci_conf[0x2d] = 0x80; // subsys vendor
    pci_conf[0x2e] = 0x00; // fake
    pci_conf[0x2f] = 0x01; // fake

    pci_register_io_region((PCIDevice *)d, 0, 0x8, 
                           PCI_ADDRESS_SPACE_IO, ide_map);
    pci_register_io_region((PCIDevice *)d, 1, 0x4, 
                           PCI_ADDRESS_SPACE_IO, ide_map);
    pci_register_io_region((PCIDevice *)d, 2, 0x8, 
                           PCI_ADDRESS_SPACE_IO, ide_map);
    pci_register_io_region((PCIDevice *)d, 3, 0x4, 
                           PCI_ADDRESS_SPACE_IO, ide_map);
    pci_register_io_region((PCIDevice *)d, 4, 0x10, 
                           PCI_ADDRESS_SPACE_IO, bmdma_map);

    pci_conf[0x3d] = 0x01; // interrupt on pin 1

    for(i = 0; i < 4; i++)
        d->ide_if[i].pci_dev = (PCIDevice *)d;
    ide_init2(&d->ide_if[0], 16, hd_table[0], hd_table[1]);
    ide_init2(&d->ide_if[2], 16, hd_table[2], hd_table[3]);
}

/* hd_table must contain 4 block drivers */
/* NOTE: for the PIIX3, the IRQs and IOports are hardcoded */
void pci_piix3_ide_init(PCIBus *bus, BlockDriverState **hd_table)
{
    PCIIDEState *d;
    uint8_t *pci_conf;
    
    /* register a function 1 of PIIX3 */
    d = (PCIIDEState *)pci_register_device(bus, "PIIX3 IDE", 
                                           sizeof(PCIIDEState),
                                           ((PCIDevice *)piix3_state)->devfn + 1, 
                                           NULL, NULL);
    pci_conf = d->dev.config;
    pci_conf[0x00] = 0x86; // Intel
    pci_conf[0x01] = 0x80;
    pci_conf[0x02] = 0x10;
    pci_conf[0x03] = 0x70;
    pci_conf[0x0a] = 0x01; // class_sub = PCI_IDE
    pci_conf[0x0b] = 0x01; // class_base = PCI_mass_storage
    pci_conf[0x0e] = 0x00; // header_type

    pci_register_io_region((PCIDevice *)d, 4, 0x10, 
                           PCI_ADDRESS_SPACE_IO, bmdma_map);

    ide_init2(&d->ide_if[0], 14, hd_table[0], hd_table[1]);
    ide_init2(&d->ide_if[2], 15, hd_table[2], hd_table[3]);
    ide_init_ioport(&d->ide_if[0], 0x1f0, 0x3f6);
    ide_init_ioport(&d->ide_if[2], 0x170, 0x376);
}

/***********************************************************/
/* MacIO based PowerPC IDE */

/* PowerMac IDE memory IO */
static void pmac_ide_writeb (void *opaque,
                             target_phys_addr_t addr, uint32_t val)
{
    addr = (addr & 0xFFF) >> 4; 
    switch (addr) {
    case 1 ... 7:
        ide_ioport_write(opaque, addr, val);
        break;
    case 8:
    case 22:
        ide_cmd_write(opaque, 0, val);
        break;
    default:
        break;
    }
}

static uint32_t pmac_ide_readb (void *opaque,target_phys_addr_t addr)
{
    uint8_t retval;

    addr = (addr & 0xFFF) >> 4;
    switch (addr) {
    case 1 ... 7:
        retval = ide_ioport_read(opaque, addr);
        break;
    case 8:
    case 22:
        retval = ide_status_read(opaque, 0);
        break;
    default:
        retval = 0xFF;
        break;
    }
    return retval;
}

static void pmac_ide_writew (void *opaque,
                             target_phys_addr_t addr, uint32_t val)
{
    addr = (addr & 0xFFF) >> 4; 
#ifdef TARGET_WORDS_BIGENDIAN
    val = bswap16(val);
#endif
    if (addr == 0) {
        ide_data_writew(opaque, 0, val);
    }
}

static uint32_t pmac_ide_readw (void *opaque,target_phys_addr_t addr)
{
    uint16_t retval;

    addr = (addr & 0xFFF) >> 4; 
    if (addr == 0) {
        retval = ide_data_readw(opaque, 0);
    } else {
        retval = 0xFFFF;
    }
#ifdef TARGET_WORDS_BIGENDIAN
    retval = bswap16(retval);
#endif
    return retval;
}

static void pmac_ide_writel (void *opaque,
                             target_phys_addr_t addr, uint32_t val)
{
    addr = (addr & 0xFFF) >> 4; 
#ifdef TARGET_WORDS_BIGENDIAN
    val = bswap32(val);
#endif
    if (addr == 0) {
        ide_data_writel(opaque, 0, val);
    }
}

static uint32_t pmac_ide_readl (void *opaque,target_phys_addr_t addr)
{
    uint32_t retval;

    addr = (addr & 0xFFF) >> 4; 
    if (addr == 0) {
        retval = ide_data_readl(opaque, 0);
    } else {
        retval = 0xFFFFFFFF;
    }
#ifdef TARGET_WORDS_BIGENDIAN
    retval = bswap32(retval);
#endif
    return retval;
}

static CPUWriteMemoryFunc *pmac_ide_write[] = {
    pmac_ide_writeb,
    pmac_ide_writew,
    pmac_ide_writel,
};

static CPUReadMemoryFunc *pmac_ide_read[] = {
    pmac_ide_readb,
    pmac_ide_readw,
    pmac_ide_readl,
};

/* hd_table must contain 4 block drivers */
/* PowerMac uses memory mapped registers, not I/O. Return the memory
   I/O index to access the ide. */
int pmac_ide_init (BlockDriverState **hd_table,
                   openpic_t *openpic, int irq)
{
    IDEState *ide_if;
    int pmac_ide_memory;

    ide_if = qemu_mallocz(sizeof(IDEState) * 2);
    ide_init2(&ide_if[0], irq, hd_table[0], hd_table[1]);
    ide_if[0].openpic = openpic;
    ide_if[1].openpic = openpic;
    
    pmac_ide_memory = cpu_register_io_memory(0, pmac_ide_read,
                                             pmac_ide_write, &ide_if[0]);
    return pmac_ide_memory;
}
