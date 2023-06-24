/*
 * QEMU PC System Emulator
 * 
 * Copyright (c) 2003-2004 Fabrice Bellard
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

/* output Bochs bios info messages */
//#define DEBUG_BIOS

#define BIOS_FILENAME "bios.bin"
#define VGABIOS_FILENAME "vgabios.bin"
#define VGABIOS_CIRRUS_FILENAME "vgabios-cirrus.bin"
#define LINUX_BOOT_FILENAME "linux_boot.bin"

#define KERNEL_LOAD_ADDR     0x00100000
#define INITRD_LOAD_ADDR     0x00400000
#define KERNEL_PARAMS_ADDR   0x00090000
#define KERNEL_CMDLINE_ADDR  0x00099000

int speaker_data_on;
int dummy_refresh_clock;
static fdctrl_t *floppy_controller;
static RTCState *rtc_state;
static PITState *pit;

static void ioport80_write(void *opaque, uint32_t addr, uint32_t data)
{
}

/* MSDOS compatibility mode FPU exception support */
/* XXX: add IGNNE support */
void cpu_set_ferr(CPUX86State *s)
{
    pic_set_irq(13, 1);
}

static void ioportF0_write(void *opaque, uint32_t addr, uint32_t data)
{
    pic_set_irq(13, 0);
}

/* TSC handling */

uint64_t cpu_get_tsc(CPUX86State *env)
{
    return qemu_get_clock(vm_clock);
}

/* PC cmos mappings */

#define REG_EQUIPMENT_BYTE          0x14
#define REG_IBM_CENTURY_BYTE        0x32
#define REG_IBM_PS2_CENTURY_BYTE    0x37


static inline int to_bcd(RTCState *s, int a)
{
    return ((a / 10) << 4) | (a % 10);
}

static int cmos_get_fd_drive_type(int fd0)
{
    int val;

    switch (fd0) {
    case 0:
        /* 1.44 Mb 3"5 drive */
        val = 4;
        break;
    case 1:
        /* 2.88 Mb 3"5 drive */
        val = 5;
        break;
    case 2:
        /* 1.2 Mb 5"5 drive */
        val = 2;
        break;
    default:
        val = 0;
        break;
    }
    return val;
}

static void cmos_init(int ram_size, int boot_device)
{
    RTCState *s = rtc_state;
    int val;
    int fd0, fd1, nb;
    time_t ti;
    struct tm *tm;

    /* set the CMOS date */
    time(&ti);
    if (rtc_utc)
        tm = gmtime(&ti);
    else
        tm = localtime(&ti);
    rtc_set_date(s, tm);

    val = to_bcd(s, (tm->tm_year / 100) + 19);
    rtc_set_memory(s, REG_IBM_CENTURY_BYTE, val);
    rtc_set_memory(s, REG_IBM_PS2_CENTURY_BYTE, val);

    /* various important CMOS locations needed by PC/Bochs bios */

    /* memory size */
    val = 640; /* base memory in K */
    rtc_set_memory(s, 0x15, val);
    rtc_set_memory(s, 0x16, val >> 8);

    val = (ram_size / 1024) - 1024;
    if (val > 65535)
        val = 65535;
    rtc_set_memory(s, 0x17, val);
    rtc_set_memory(s, 0x18, val >> 8);
    rtc_set_memory(s, 0x30, val);
    rtc_set_memory(s, 0x31, val >> 8);

    if (ram_size > (16 * 1024 * 1024))
        val = (ram_size / 65536) - ((16 * 1024 * 1024) / 65536);
    else
        val = 0;
    if (val > 65535)
        val = 65535;
    rtc_set_memory(s, 0x34, val);
    rtc_set_memory(s, 0x35, val >> 8);
    
    switch(boot_device) {
    case 'a':
    case 'b':
        rtc_set_memory(s, 0x3d, 0x01); /* floppy boot */
        break;
    default:
    case 'c':
        rtc_set_memory(s, 0x3d, 0x02); /* hard drive boot */
        break;
    case 'd':
        rtc_set_memory(s, 0x3d, 0x03); /* CD-ROM boot */
        break;
    }

    /* floppy type */

    fd0 = fdctrl_get_drive_type(floppy_controller, 0);
    fd1 = fdctrl_get_drive_type(floppy_controller, 1);

    val = (cmos_get_fd_drive_type(fd0) << 4) | cmos_get_fd_drive_type(fd1);
    rtc_set_memory(s, 0x10, val);
    
    val = 0;
    nb = 0;
    if (fd0 < 3)
        nb++;
    if (fd1 < 3)
        nb++;
    switch (nb) {
    case 0:
        break;
    case 1:
        val |= 0x01; /* 1 drive, ready for boot */
        break;
    case 2:
        val |= 0x41; /* 2 drives, ready for boot */
        break;
    }
    val |= 0x02; /* FPU is there */
    val |= 0x04; /* PS/2 mouse installed */
    rtc_set_memory(s, REG_EQUIPMENT_BYTE, val);

}

static void speaker_ioport_write(void *opaque, uint32_t addr, uint32_t val)
{
    speaker_data_on = (val >> 1) & 1;
    pit_set_gate(pit, 2, val & 1);
}

static uint32_t speaker_ioport_read(void *opaque, uint32_t addr)
{
    int out;
    out = pit_get_out(pit, 2, qemu_get_clock(vm_clock));
    dummy_refresh_clock ^= 1;
    return (speaker_data_on << 1) | pit_get_gate(pit, 2) | (out << 5) |
      (dummy_refresh_clock << 4);
}

static void ioport92_write(void *opaque, uint32_t addr, uint32_t val)
{
    cpu_x86_set_a20(cpu_single_env, (val >> 1) & 1);
    /* XXX: bit 0 is fast reset */
}

static uint32_t ioport92_read(void *opaque, uint32_t addr)
{
    return ((cpu_single_env->a20_mask >> 20) & 1) << 1;
}

/***********************************************************/
/* Bochs BIOS debug ports */

void bochs_bios_write(void *opaque, uint32_t addr, uint32_t val)
{
    static const char shutdown_str[8] = "Shutdown";
    static int shutdown_index = 0;
    
    switch(addr) {
        /* Bochs BIOS messages */
    case 0x400:
    case 0x401:
        fprintf(stderr, "BIOS panic at rombios.c, line %d\n", val);
        exit(1);
    case 0x402:
    case 0x403:
#ifdef DEBUG_BIOS
        fprintf(stderr, "%c", val);
#endif
        break;
    case 0x8900:
        /* same as Bochs power off */
        if (val == shutdown_str[shutdown_index]) {
            shutdown_index++;
            if (shutdown_index == 8) {
                shutdown_index = 0;
                qemu_system_shutdown_request();
            }
        } else {
            shutdown_index = 0;
        }
        break;

        /* LGPL'ed VGA BIOS messages */
    case 0x501:
    case 0x502:
        fprintf(stderr, "VGA BIOS panic, line %d\n", val);
        exit(1);
    case 0x500:
    case 0x503:
#ifdef DEBUG_BIOS
        fprintf(stderr, "%c", val);
#endif
        break;
    }
}

void bochs_bios_init(void)
{
    register_ioport_write(0x400, 1, 2, bochs_bios_write, NULL);
    register_ioport_write(0x401, 1, 2, bochs_bios_write, NULL);
    register_ioport_write(0x402, 1, 1, bochs_bios_write, NULL);
    register_ioport_write(0x403, 1, 1, bochs_bios_write, NULL);
    register_ioport_write(0x8900, 1, 1, bochs_bios_write, NULL);

    register_ioport_write(0x501, 1, 2, bochs_bios_write, NULL);
    register_ioport_write(0x502, 1, 2, bochs_bios_write, NULL);
    register_ioport_write(0x500, 1, 1, bochs_bios_write, NULL);
    register_ioport_write(0x503, 1, 1, bochs_bios_write, NULL);
}


int load_kernel(const char *filename, uint8_t *addr, 
                uint8_t *real_addr)
{
    int fd, size;
    int setup_sects;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return -1;

    /* load 16 bit code */
    if (read(fd, real_addr, 512) != 512)
        goto fail;
    setup_sects = real_addr[0x1F1];
    if (!setup_sects)
        setup_sects = 4;
    if (read(fd, real_addr + 512, setup_sects * 512) != 
        setup_sects * 512)
        goto fail;
    
    /* load 32 bit code */
    size = read(fd, addr, 16 * 1024 * 1024);
    if (size < 0)
        goto fail;
    close(fd);
    return size;
 fail:
    close(fd);
    return -1;
}

static const int ide_iobase[2] = { 0x1f0, 0x170 };
static const int ide_iobase2[2] = { 0x3f6, 0x376 };
static const int ide_irq[2] = { 14, 15 };

#define NE2000_NB_MAX 6

static uint32_t ne2000_io[NE2000_NB_MAX] = { 0x300, 0x320, 0x340, 0x360, 0x280, 0x380 };
static int ne2000_irq[NE2000_NB_MAX] = { 9, 10, 11, 3, 4, 5 };

/* PC hardware initialisation */
void pc_init(int ram_size, int vga_ram_size, int boot_device,
             DisplayState *ds, const char **fd_filename, int snapshot,
             const char *kernel_filename, const char *kernel_cmdline,
             const char *initrd_filename)
{
    char buf[1024];
    int ret, linux_boot, initrd_size, i, nb_nics1, fd;
    unsigned long bios_offset, vga_bios_offset;
    int bios_size, isa_bios_size;
    PCIBus *pci_bus;
    
    linux_boot = (kernel_filename != NULL);

    /* allocate RAM */
    cpu_register_physical_memory(0, ram_size, 0);

    /* BIOS load */
    bios_offset = ram_size + vga_ram_size;
    vga_bios_offset = bios_offset + 256 * 1024;

    snprintf(buf, sizeof(buf), "%s/%s", bios_dir, BIOS_FILENAME);
    bios_size = get_image_size(buf);
    if (bios_size <= 0 || 
        (bios_size % 65536) != 0 ||
        bios_size > (256 * 1024)) {
        goto bios_error;
    }
    ret = load_image(buf, phys_ram_base + bios_offset);
    if (ret != bios_size) {
    bios_error:
        fprintf(stderr, "qemu: could not load PC bios '%s'\n", buf);
        exit(1);
    }

    /* VGA BIOS load */
    if (cirrus_vga_enabled) {
        snprintf(buf, sizeof(buf), "%s/%s", bios_dir, VGABIOS_CIRRUS_FILENAME);
    } else {
        snprintf(buf, sizeof(buf), "%s/%s", bios_dir, VGABIOS_FILENAME);
    }
    ret = load_image(buf, phys_ram_base + vga_bios_offset);
    
    /* setup basic memory access */
    cpu_register_physical_memory(0xc0000, 0x10000, 
                                 vga_bios_offset | IO_MEM_ROM);

    /* map the last 128KB of the BIOS in ISA space */
    isa_bios_size = bios_size;
    if (isa_bios_size > (128 * 1024))
        isa_bios_size = 128 * 1024;
    cpu_register_physical_memory(0xd0000, (192 * 1024) - isa_bios_size, 
                                 IO_MEM_UNASSIGNED);
    cpu_register_physical_memory(0x100000 - isa_bios_size, 
                                 isa_bios_size, 
                                 (bios_offset + bios_size - isa_bios_size) | IO_MEM_ROM);
    /* map all the bios at the top of memory */
    cpu_register_physical_memory((uint32_t)(-bios_size), 
                                 bios_size, bios_offset | IO_MEM_ROM);
    
    bochs_bios_init();

    if (linux_boot) {
        uint8_t bootsect[512];
        uint8_t old_bootsect[512];

        if (bs_table[0] == NULL) {
            fprintf(stderr, "A disk image must be given for 'hda' when booting a Linux kernel\n");
            exit(1);
        }
        snprintf(buf, sizeof(buf), "%s/%s", bios_dir, LINUX_BOOT_FILENAME);
        ret = load_image(buf, bootsect);
        if (ret != sizeof(bootsect)) {
            fprintf(stderr, "qemu: could not load linux boot sector '%s'\n",
                    buf);
            exit(1);
        }

        if (bdrv_read(bs_table[0], 0, old_bootsect, 1) >= 0) {
            /* copy the MSDOS partition table */
            memcpy(bootsect + 0x1be, old_bootsect + 0x1be, 0x40);
        }

        bdrv_set_boot_sector(bs_table[0], bootsect, sizeof(bootsect));

        /* now we can load the kernel */
        ret = load_kernel(kernel_filename, 
                          phys_ram_base + KERNEL_LOAD_ADDR,
                          phys_ram_base + KERNEL_PARAMS_ADDR);
        if (ret < 0) {
            fprintf(stderr, "qemu: could not load kernel '%s'\n", 
                    kernel_filename);
            exit(1);
        }
        
        /* load initrd */
        initrd_size = 0;
        if (initrd_filename) {
            initrd_size = load_image(initrd_filename, phys_ram_base + INITRD_LOAD_ADDR);
            if (initrd_size < 0) {
                fprintf(stderr, "qemu: could not load initial ram disk '%s'\n", 
                        initrd_filename);
                exit(1);
            }
        }
        if (initrd_size > 0) {
            stl_raw(phys_ram_base + KERNEL_PARAMS_ADDR + 0x218, INITRD_LOAD_ADDR);
            stl_raw(phys_ram_base + KERNEL_PARAMS_ADDR + 0x21c, initrd_size);
        }
        pstrcpy(phys_ram_base + KERNEL_CMDLINE_ADDR, 4096,
                kernel_cmdline);
        stw_raw(phys_ram_base + KERNEL_PARAMS_ADDR + 0x20, 0xA33F);
        stw_raw(phys_ram_base + KERNEL_PARAMS_ADDR + 0x22,
                KERNEL_CMDLINE_ADDR - KERNEL_PARAMS_ADDR);
        /* loader type */
        stw_raw(phys_ram_base + KERNEL_PARAMS_ADDR + 0x210, 0x01);
    }

    if (pci_enabled) {
        pci_bus = i440fx_init();
        piix3_init(pci_bus);
    } else {
        pci_bus = NULL;
    }

    /* init basic PC hardware */
    register_ioport_write(0x80, 1, 1, ioport80_write, NULL);

    register_ioport_write(0xf0, 1, 1, ioportF0_write, NULL);

    if (cirrus_vga_enabled) {
        if (pci_enabled) {
            pci_cirrus_vga_init(pci_bus, 
                                ds, phys_ram_base + ram_size, ram_size, 
                                vga_ram_size);
        } else {
            isa_cirrus_vga_init(ds, phys_ram_base + ram_size, ram_size, 
                                vga_ram_size);
        }
    } else {
        vga_initialize(pci_bus, ds, phys_ram_base + ram_size, ram_size, 
                       vga_ram_size);
    }

    rtc_state = rtc_init(0x70, 8);
    register_ioport_read(0x61, 1, 1, speaker_ioport_read, NULL);
    register_ioport_write(0x61, 1, 1, speaker_ioport_write, NULL);

    register_ioport_read(0x92, 1, 1, ioport92_read, NULL);
    register_ioport_write(0x92, 1, 1, ioport92_write, NULL);

    pic_init();
    pit = pit_init(0x40, 0);

    fd = serial_open_device();
    serial_init(0x3f8, 4, fd);

    if (pci_enabled) {
        for(i = 0; i < nb_nics; i++) {
            pci_ne2000_init(pci_bus, &nd_table[i]);
        }
        pci_piix3_ide_init(pci_bus, bs_table);
    } else {
        nb_nics1 = nb_nics;
        if (nb_nics1 > NE2000_NB_MAX)
            nb_nics1 = NE2000_NB_MAX;
        for(i = 0; i < nb_nics1; i++) {
            isa_ne2000_init(ne2000_io[i], ne2000_irq[i], &nd_table[i]);
        }

        for(i = 0; i < 2; i++) {
            isa_ide_init(ide_iobase[i], ide_iobase2[i], ide_irq[i],
                         bs_table[2 * i], bs_table[2 * i + 1]);
        }
    }

    kbd_init();
    DMA_init(0);

#ifndef _WIN32
    if (audio_enabled) {
        /* no audio supported yet for win32 */
        AUD_init();
        SB16_init();
    }
#endif

    floppy_controller = fdctrl_init(6, 2, 0, 0x3f0, fd_table);

    cmos_init(ram_size, boot_device);

    /* must be done after all PCI devices are instanciated */
    /* XXX: should be done in the Bochs BIOS */
    if (pci_enabled) {
        pci_bios_init();
    }
}
