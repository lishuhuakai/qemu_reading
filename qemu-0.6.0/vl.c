/*
 * QEMU System Emulator
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

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>

#ifndef _WIN32
#include <sys/times.h>
#include <sys/wait.h>
#include <termios.h>
#include <sys/poll.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#ifdef _BSD
#include <sys/stat.h>
#ifndef __APPLE__
#include <libutil.h>
#endif
#else
#include <linux/if.h>
#include <linux/if_tun.h>
#include <pty.h>
#include <malloc.h>
#include <linux/rtc.h>
#endif
#endif

#if defined(CONFIG_SLIRP)
#include "libslirp.h"
#endif

#ifdef _WIN32
#include <malloc.h>
#include <sys/timeb.h>
#include <windows.h>
#define getopt_long_only getopt_long
#define memalign(align, size) malloc(size)
#endif

#ifdef CONFIG_SDL
#ifdef __APPLE__
#include <SDL/SDL.h>
#endif
#if defined(__linux__)
/* SDL use the pthreads and they modify sigaction. We don't
   want that. */
#if (__GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 2))
extern void __libc_sigaction();
#define sigaction(sig, act, oact) __libc_sigaction(sig, act, oact)
#else
extern void __sigaction();
#define sigaction(sig, act, oact) __sigaction(sig, act, oact)
#endif
#endif /* __linux__ */
#endif /* CONFIG_SDL */

#include "disas.h"

#include "exec-all.h"

//#define DO_TB_FLUSH

#define DEFAULT_NETWORK_SCRIPT "/etc/qemu-ifup"

//#define DEBUG_UNUSED_IOPORT
//#define DEBUG_IOPORT

#if !defined(CONFIG_SOFTMMU)
#define PHYS_RAM_MAX_SIZE (256 * 1024 * 1024)
#else
#define PHYS_RAM_MAX_SIZE (2047 * 1024 * 1024)
#endif

#ifdef TARGET_PPC
#define DEFAULT_RAM_SIZE 144
#else
#define DEFAULT_RAM_SIZE 128
#endif
/* in ms */
#define GUI_REFRESH_INTERVAL 30

/* XXX: use a two level table to limit memory usage */
#define MAX_IOPORTS 65536

const char *bios_dir = CONFIG_QEMU_SHAREDIR;
char phys_ram_file[1024];
CPUState *global_env;
CPUState *cpu_single_env;
void *ioport_opaque[MAX_IOPORTS];
IOPortReadFunc *ioport_read_table[3][MAX_IOPORTS];
IOPortWriteFunc *ioport_write_table[3][MAX_IOPORTS];
BlockDriverState *bs_table[MAX_DISKS], *fd_table[MAX_FD];
int vga_ram_size;
int bios_size;
static DisplayState display_state;
int nographic;
int64_t ticks_per_sec;
int boot_device = 'c';
int ram_size;
static char network_script[1024];
int pit_min_timer_count = 0;
int nb_nics;
NetDriverState nd_table[MAX_NICS];
SerialState *serial_console;
QEMUTimer *gui_timer;
int vm_running;
int audio_enabled = 0;
int pci_enabled = 1;
int prep_enabled = 0;
int rtc_utc = 1;
int cirrus_vga_enabled = 1;
int graphic_width = 800;
int graphic_height = 600;
int graphic_depth = 15;

/***********************************************************/
/* x86 ISA bus support */

target_phys_addr_t isa_mem_base = 0;

uint32_t default_ioport_readb(void *opaque, uint32_t address)
{
#ifdef DEBUG_UNUSED_IOPORT
    fprintf(stderr, "inb: port=0x%04x\n", address);
#endif
    return 0xff;
}

void default_ioport_writeb(void *opaque, uint32_t address, uint32_t data)
{
#ifdef DEBUG_UNUSED_IOPORT
    fprintf(stderr, "outb: port=0x%04x data=0x%02x\n", address, data);
#endif
}

/* default is to make two byte accesses */
uint32_t default_ioport_readw(void *opaque, uint32_t address)
{
    uint32_t data;
    data = ioport_read_table[0][address](ioport_opaque[address], address);
    address = (address + 1) & (MAX_IOPORTS - 1);
    data |= ioport_read_table[0][address](ioport_opaque[address], address) << 8;
    return data;
}

void default_ioport_writew(void *opaque, uint32_t address, uint32_t data)
{
    ioport_write_table[0][address](ioport_opaque[address], address, data & 0xff);
    address = (address + 1) & (MAX_IOPORTS - 1);
    ioport_write_table[0][address](ioport_opaque[address], address, (data >> 8) & 0xff);
}

uint32_t default_ioport_readl(void *opaque, uint32_t address)
{
#ifdef DEBUG_UNUSED_IOPORT
    fprintf(stderr, "inl: port=0x%04x\n", address);
#endif
    return 0xffffffff;
}

void default_ioport_writel(void *opaque, uint32_t address, uint32_t data)
{
#ifdef DEBUG_UNUSED_IOPORT
    fprintf(stderr, "outl: port=0x%04x data=0x%02x\n", address, data);
#endif
}

void init_ioports(void)
{
    int i;

    for(i = 0; i < MAX_IOPORTS; i++) {
        ioport_read_table[0][i] = default_ioport_readb;
        ioport_write_table[0][i] = default_ioport_writeb;
        ioport_read_table[1][i] = default_ioport_readw;
        ioport_write_table[1][i] = default_ioport_writew;
        ioport_read_table[2][i] = default_ioport_readl;
        ioport_write_table[2][i] = default_ioport_writel;
    }
}

/* size is the word size in byte */
int register_ioport_read(int start, int length, int size, 
                         IOPortReadFunc *func, void *opaque)
{
    int i, bsize;

    if (size == 1) {
        bsize = 0;
    } else if (size == 2) {
        bsize = 1;
    } else if (size == 4) {
        bsize = 2;
    } else {
        hw_error("register_ioport_read: invalid size");
        return -1;
    }
    for(i = start; i < start + length; i += size) {
        ioport_read_table[bsize][i] = func;
        if (ioport_opaque[i] != NULL && ioport_opaque[i] != opaque)
            hw_error("register_ioport_read: invalid opaque");
        ioport_opaque[i] = opaque;
    }
    return 0;
}

/* size is the word size in byte */
int register_ioport_write(int start, int length, int size, 
                          IOPortWriteFunc *func, void *opaque)
{
    int i, bsize;

    if (size == 1) {
        bsize = 0;
    } else if (size == 2) {
        bsize = 1;
    } else if (size == 4) {
        bsize = 2;
    } else {
        hw_error("register_ioport_write: invalid size");
        return -1;
    }
    for(i = start; i < start + length; i += size) {
        ioport_write_table[bsize][i] = func;
        if (ioport_opaque[i] != NULL && ioport_opaque[i] != opaque)
            hw_error("register_ioport_read: invalid opaque");
        ioport_opaque[i] = opaque;
    }
    return 0;
}

void isa_unassign_ioport(int start, int length)
{
    int i;

    for(i = start; i < start + length; i++) {
        ioport_read_table[0][i] = default_ioport_readb;
        ioport_read_table[1][i] = default_ioport_readw;
        ioport_read_table[2][i] = default_ioport_readl;

        ioport_write_table[0][i] = default_ioport_writeb;
        ioport_write_table[1][i] = default_ioport_writew;
        ioport_write_table[2][i] = default_ioport_writel;
    }
}

void pstrcpy(char *buf, int buf_size, const char *str)
{
    int c;
    char *q = buf;

    if (buf_size <= 0)
        return;

    for(;;) {
        c = *str++;
        if (c == 0 || q >= buf + buf_size - 1)
            break;
        *q++ = c;
    }
    *q = '\0';
}

/* strcat and truncate. */
char *pstrcat(char *buf, int buf_size, const char *s)
{
    int len;
    len = strlen(buf);
    if (len < buf_size) 
        pstrcpy(buf + len, buf_size - len, s);
    return buf;
}

/* return the size or -1 if error */
int get_image_size(const char *filename)
{
    int fd, size;
    fd = open(filename, O_RDONLY | O_BINARY);
    if (fd < 0)
        return -1;
    size = lseek(fd, 0, SEEK_END);
    close(fd);
    return size;
}

/* return the size or -1 if error */
int load_image(const char *filename, uint8_t *addr)
{
    int fd, size;
    fd = open(filename, O_RDONLY | O_BINARY);
    if (fd < 0)
        return -1;
    size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    if (read(fd, addr, size) != size) {
        close(fd);
        return -1;
    }
    close(fd);
    return size;
}

void cpu_outb(CPUState *env, int addr, int val)
{
#ifdef DEBUG_IOPORT
    if (loglevel & CPU_LOG_IOPORT)
        fprintf(logfile, "outb: %04x %02x\n", addr, val);
#endif    
    ioport_write_table[0][addr](ioport_opaque[addr], addr, val);
}

void cpu_outw(CPUState *env, int addr, int val)
{
#ifdef DEBUG_IOPORT
    if (loglevel & CPU_LOG_IOPORT)
        fprintf(logfile, "outw: %04x %04x\n", addr, val);
#endif    
    ioport_write_table[1][addr](ioport_opaque[addr], addr, val);
}

void cpu_outl(CPUState *env, int addr, int val)
{
#ifdef DEBUG_IOPORT
    if (loglevel & CPU_LOG_IOPORT)
        fprintf(logfile, "outl: %04x %08x\n", addr, val);
#endif
    ioport_write_table[2][addr](ioport_opaque[addr], addr, val);
}

int cpu_inb(CPUState *env, int addr)
{
    int val;
    val = ioport_read_table[0][addr](ioport_opaque[addr], addr);
#ifdef DEBUG_IOPORT
    if (loglevel & CPU_LOG_IOPORT)
        fprintf(logfile, "inb : %04x %02x\n", addr, val);
#endif
    return val;
}

int cpu_inw(CPUState *env, int addr)
{
    int val;
    val = ioport_read_table[1][addr](ioport_opaque[addr], addr);
#ifdef DEBUG_IOPORT
    if (loglevel & CPU_LOG_IOPORT)
        fprintf(logfile, "inw : %04x %04x\n", addr, val);
#endif
    return val;
}

int cpu_inl(CPUState *env, int addr)
{
    int val;
    val = ioport_read_table[2][addr](ioport_opaque[addr], addr);
#ifdef DEBUG_IOPORT
    if (loglevel & CPU_LOG_IOPORT)
        fprintf(logfile, "inl : %04x %08x\n", addr, val);
#endif
    return val;
}

/***********************************************************/
void hw_error(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, "qemu: hardware error: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
#ifdef TARGET_I386
    cpu_x86_dump_state(global_env, stderr, X86_DUMP_FPU | X86_DUMP_CCOP);
#else
    cpu_dump_state(global_env, stderr, 0);
#endif
    va_end(ap);
    abort();
}

/***********************************************************/
/* keyboard/mouse */

static QEMUPutKBDEvent *qemu_put_kbd_event;
static void *qemu_put_kbd_event_opaque;
static QEMUPutMouseEvent *qemu_put_mouse_event;
static void *qemu_put_mouse_event_opaque;

void qemu_add_kbd_event_handler(QEMUPutKBDEvent *func, void *opaque)
{
    qemu_put_kbd_event_opaque = opaque;
    qemu_put_kbd_event = func;
}

void qemu_add_mouse_event_handler(QEMUPutMouseEvent *func, void *opaque)
{
    qemu_put_mouse_event_opaque = opaque;
    qemu_put_mouse_event = func;
}

void kbd_put_keycode(int keycode)
{
    if (qemu_put_kbd_event) {
        qemu_put_kbd_event(qemu_put_kbd_event_opaque, keycode);
    }
}

void kbd_mouse_event(int dx, int dy, int dz, int buttons_state)
{
    if (qemu_put_mouse_event) {
        qemu_put_mouse_event(qemu_put_mouse_event_opaque, 
                             dx, dy, dz, buttons_state);
    }
}

/***********************************************************/
/* timers */

#if defined(__powerpc__)

static inline uint32_t get_tbl(void) 
{
    uint32_t tbl;
    asm volatile("mftb %0" : "=r" (tbl));
    return tbl;
}

static inline uint32_t get_tbu(void) 
{
	uint32_t tbl;
	asm volatile("mftbu %0" : "=r" (tbl));
	return tbl;
}

int64_t cpu_get_real_ticks(void)
{
    uint32_t l, h, h1;
    /* NOTE: we test if wrapping has occurred */
    do {
        h = get_tbu();
        l = get_tbl();
        h1 = get_tbu();
    } while (h != h1);
    return ((int64_t)h << 32) | l;
}

#elif defined(__i386__)

int64_t cpu_get_real_ticks(void)
{
    int64_t val;
    asm volatile ("rdtsc" : "=A" (val));
    return val;
}

#elif defined(__x86_64__)

int64_t cpu_get_real_ticks(void)
{
    uint32_t low,high;
    int64_t val;
    asm volatile("rdtsc" : "=a" (low), "=d" (high));
    val = high;
    val <<= 32;
    val |= low;
    return val;
}

#else
#error unsupported CPU
#endif

static int64_t cpu_ticks_offset;
static int cpu_ticks_enabled;

static inline int64_t cpu_get_ticks(void)
{
    if (!cpu_ticks_enabled) {
        return cpu_ticks_offset;
    } else {
        return cpu_get_real_ticks() + cpu_ticks_offset;
    }
}

/* enable cpu_get_ticks() */
void cpu_enable_ticks(void)
{
    if (!cpu_ticks_enabled) {
        cpu_ticks_offset -= cpu_get_real_ticks();
        cpu_ticks_enabled = 1;
    }
}

/* disable cpu_get_ticks() : the clock is stopped. You must not call
   cpu_get_ticks() after that.  */
void cpu_disable_ticks(void)
{
    if (cpu_ticks_enabled) {
        cpu_ticks_offset = cpu_get_ticks();
        cpu_ticks_enabled = 0;
    }
}

static int64_t get_clock(void)
{
#ifdef _WIN32
    struct _timeb tb;
    _ftime(&tb);
    return ((int64_t)tb.time * 1000 + (int64_t)tb.millitm) * 1000;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
#endif
}

void cpu_calibrate_ticks(void)
{
    int64_t usec, ticks;

    usec = get_clock();
    ticks = cpu_get_real_ticks();
#ifdef _WIN32
    Sleep(50);
#else
    usleep(50 * 1000);
#endif
    usec = get_clock() - usec;
    ticks = cpu_get_real_ticks() - ticks;
    ticks_per_sec = (ticks * 1000000LL + (usec >> 1)) / usec;
}

/* compute with 96 bit intermediate result: (a*b)/c */
uint64_t muldiv64(uint64_t a, uint32_t b, uint32_t c)
{
    union {
        uint64_t ll;
        struct {
#ifdef WORDS_BIGENDIAN
            uint32_t high, low;
#else
            uint32_t low, high;
#endif            
        } l;
    } u, res;
    uint64_t rl, rh;

    u.ll = a;
    rl = (uint64_t)u.l.low * (uint64_t)b;
    rh = (uint64_t)u.l.high * (uint64_t)b;
    rh += (rl >> 32);
    res.l.high = rh / c;
    res.l.low = (((rh % c) << 32) + (rl & 0xffffffff)) / c;
    return res.ll;
}

#define QEMU_TIMER_REALTIME 0
#define QEMU_TIMER_VIRTUAL  1

struct QEMUClock {
    int type;
    /* XXX: add frequency */
};

struct QEMUTimer {
    QEMUClock *clock;
    int64_t expire_time;
    QEMUTimerCB *cb;
    void *opaque;
    struct QEMUTimer *next;
};

QEMUClock *rt_clock;
QEMUClock *vm_clock;

static QEMUTimer *active_timers[2];
#ifdef _WIN32
static MMRESULT timerID;
#else
/* frequency of the times() clock tick */
static int timer_freq;
#endif

QEMUClock *qemu_new_clock(int type)
{
    QEMUClock *clock;
    clock = qemu_mallocz(sizeof(QEMUClock));
    if (!clock)
        return NULL;
    clock->type = type;
    return clock;
}

QEMUTimer *qemu_new_timer(QEMUClock *clock, QEMUTimerCB *cb, void *opaque)
{
    QEMUTimer *ts;

    ts = qemu_mallocz(sizeof(QEMUTimer));
    ts->clock = clock;
    ts->cb = cb;
    ts->opaque = opaque;
    return ts;
}

void qemu_free_timer(QEMUTimer *ts)
{
    qemu_free(ts);
}

/* stop a timer, but do not dealloc it */
void qemu_del_timer(QEMUTimer *ts)
{
    QEMUTimer **pt, *t;

    /* NOTE: this code must be signal safe because
       qemu_timer_expired() can be called from a signal. */
    pt = &active_timers[ts->clock->type];
    for(;;) {
        t = *pt;
        if (!t)
            break;
        if (t == ts) {
            *pt = t->next;
            break;
        }
        pt = &t->next;
    }
}

/* modify the current timer so that it will be fired when current_time
   >= expire_time. The corresponding callback will be called. */
void qemu_mod_timer(QEMUTimer *ts, int64_t expire_time)
{
    QEMUTimer **pt, *t;

    qemu_del_timer(ts);

    /* add the timer in the sorted list */
    /* NOTE: this code must be signal safe because
       qemu_timer_expired() can be called from a signal. */
    pt = &active_timers[ts->clock->type];
    for(;;) {
        t = *pt;
        if (!t)
            break;
        if (t->expire_time > expire_time) 
            break;
        pt = &t->next;
    }
    ts->expire_time = expire_time;
    ts->next = *pt;
    *pt = ts;
}

int qemu_timer_pending(QEMUTimer *ts)
{
    QEMUTimer *t;
    for(t = active_timers[ts->clock->type]; t != NULL; t = t->next) {
        if (t == ts)
            return 1;
    }
    return 0;
}

static inline int qemu_timer_expired(QEMUTimer *timer_head, int64_t current_time)
{
    if (!timer_head)
        return 0;
    return (timer_head->expire_time <= current_time);
}

static void qemu_run_timers(QEMUTimer **ptimer_head, int64_t current_time)
{
    QEMUTimer *ts;
    
    for(;;) {
        ts = *ptimer_head;
        if (ts->expire_time > current_time)
            break;
        /* remove timer from the list before calling the callback */
        *ptimer_head = ts->next;
        ts->next = NULL;
        
        /* run the callback (the timer list can be modified) */
        ts->cb(ts->opaque);
    }
}

int64_t qemu_get_clock(QEMUClock *clock)
{
    switch(clock->type) {
    case QEMU_TIMER_REALTIME:
#ifdef _WIN32
        return GetTickCount();
#else
        {
            struct tms tp;

            /* Note that using gettimeofday() is not a good solution
               for timers because its value change when the date is
               modified. */
            if (timer_freq == 100) {
                return times(&tp) * 10;
            } else {
                return ((int64_t)times(&tp) * 1000) / timer_freq;
            }
        }
#endif
    default:
    case QEMU_TIMER_VIRTUAL:
        return cpu_get_ticks();
    }
}

/* save a timer */
void qemu_put_timer(QEMUFile *f, QEMUTimer *ts)
{
    uint64_t expire_time;

    if (qemu_timer_pending(ts)) {
        expire_time = ts->expire_time;
    } else {
        expire_time = -1;
    }
    qemu_put_be64(f, expire_time);
}

void qemu_get_timer(QEMUFile *f, QEMUTimer *ts)
{
    uint64_t expire_time;

    expire_time = qemu_get_be64(f);
    if (expire_time != -1) {
        qemu_mod_timer(ts, expire_time);
    } else {
        qemu_del_timer(ts);
    }
}

static void timer_save(QEMUFile *f, void *opaque)
{
    if (cpu_ticks_enabled) {
        hw_error("cannot save state if virtual timers are running");
    }
    qemu_put_be64s(f, &cpu_ticks_offset);
    qemu_put_be64s(f, &ticks_per_sec);
}

static int timer_load(QEMUFile *f, void *opaque, int version_id)
{
    if (version_id != 1)
        return -EINVAL;
    if (cpu_ticks_enabled) {
        return -EINVAL;
    }
    qemu_get_be64s(f, &cpu_ticks_offset);
    qemu_get_be64s(f, &ticks_per_sec);
    return 0;
}

#ifdef _WIN32
void CALLBACK host_alarm_handler(UINT uTimerID, UINT uMsg, 
                                 DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
#else
static void host_alarm_handler(int host_signum)
#endif
{
#if 0
#define DISP_FREQ 1000
    {
        static int64_t delta_min = INT64_MAX;
        static int64_t delta_max, delta_cum, last_clock, delta, ti;
        static int count;
        ti = qemu_get_clock(vm_clock);
        if (last_clock != 0) {
            delta = ti - last_clock;
            if (delta < delta_min)
                delta_min = delta;
            if (delta > delta_max)
                delta_max = delta;
            delta_cum += delta;
            if (++count == DISP_FREQ) {
                printf("timer: min=%lld us max=%lld us avg=%lld us avg_freq=%0.3f Hz\n",
                       muldiv64(delta_min, 1000000, ticks_per_sec),
                       muldiv64(delta_max, 1000000, ticks_per_sec),
                       muldiv64(delta_cum, 1000000 / DISP_FREQ, ticks_per_sec),
                       (double)ticks_per_sec / ((double)delta_cum / DISP_FREQ));
                count = 0;
                delta_min = INT64_MAX;
                delta_max = 0;
                delta_cum = 0;
            }
        }
        last_clock = ti;
    }
#endif
    if (qemu_timer_expired(active_timers[QEMU_TIMER_VIRTUAL],
                           qemu_get_clock(vm_clock)) ||
        qemu_timer_expired(active_timers[QEMU_TIMER_REALTIME],
                           qemu_get_clock(rt_clock))) {
        /* stop the cpu because a timer occured */
        cpu_interrupt(global_env, CPU_INTERRUPT_EXIT);
    }
}

#ifndef _WIN32

#if defined(__linux__)

#define RTC_FREQ 1024

static int rtc_fd;

static int start_rtc_timer(void)
{
    rtc_fd = open("/dev/rtc", O_RDONLY);
    if (rtc_fd < 0)
        return -1;
    if (ioctl(rtc_fd, RTC_IRQP_SET, RTC_FREQ) < 0) {
        fprintf(stderr, "Could not configure '/dev/rtc' to have a 1024 Hz timer. This is not a fatal\n"
                "error, but for better emulation accuracy either use a 2.6 host Linux kernel or\n"
                "type 'echo 1024 > /proc/sys/dev/rtc/max-user-freq' as root.\n");
        goto fail;
    }
    if (ioctl(rtc_fd, RTC_PIE_ON, 0) < 0) {
    fail:
        close(rtc_fd);
        return -1;
    }
    pit_min_timer_count = PIT_FREQ / RTC_FREQ;
    return 0;
}

#else

static int start_rtc_timer(void)
{
    return -1;
}

#endif /* !defined(__linux__) */

#endif /* !defined(_WIN32) */

static void init_timers(void)
{
    rt_clock = qemu_new_clock(QEMU_TIMER_REALTIME);
    vm_clock = qemu_new_clock(QEMU_TIMER_VIRTUAL);

#ifdef _WIN32
    {
        int count=0;
        timerID = timeSetEvent(10,    // interval (ms)
                               0,     // resolution
                               host_alarm_handler, // function
                               (DWORD)&count,  // user parameter
                               TIME_PERIODIC | TIME_CALLBACK_FUNCTION);
 	if( !timerID ) {
            perror("failed timer alarm");
            exit(1);
 	}
    }
    pit_min_timer_count = ((uint64_t)10000 * PIT_FREQ) / 1000000;
#else
    {
        struct sigaction act;
        struct itimerval itv;
        
        /* get times() syscall frequency */
        timer_freq = sysconf(_SC_CLK_TCK);
        
        /* timer signal */
        sigfillset(&act.sa_mask);
        act.sa_flags = 0;
#if defined (TARGET_I386) && defined(USE_CODE_COPY)
        act.sa_flags |= SA_ONSTACK;
#endif
        act.sa_handler = host_alarm_handler;
        sigaction(SIGALRM, &act, NULL);

        itv.it_interval.tv_sec = 0;
        itv.it_interval.tv_usec = 1000;
        itv.it_value.tv_sec = 0;
        itv.it_value.tv_usec = 10 * 1000;
        setitimer(ITIMER_REAL, &itv, NULL);
        /* we probe the tick duration of the kernel to inform the user if
           the emulated kernel requested a too high timer frequency */
        getitimer(ITIMER_REAL, &itv);

#if defined(__linux__)
        if (itv.it_interval.tv_usec > 1000) {
            /* try to use /dev/rtc to have a faster timer */
            if (start_rtc_timer() < 0)
                goto use_itimer;
            /* disable itimer */
            itv.it_interval.tv_sec = 0;
            itv.it_interval.tv_usec = 0;
            itv.it_value.tv_sec = 0;
            itv.it_value.tv_usec = 0;
            setitimer(ITIMER_REAL, &itv, NULL);

            /* use the RTC */
            sigaction(SIGIO, &act, NULL);
            fcntl(rtc_fd, F_SETFL, O_ASYNC);
            fcntl(rtc_fd, F_SETOWN, getpid());
        } else 
#endif /* defined(__linux__) */
        {
        use_itimer:
            pit_min_timer_count = ((uint64_t)itv.it_interval.tv_usec * 
                                   PIT_FREQ) / 1000000;
        }
    }
#endif
}

void quit_timers(void)
{
#ifdef _WIN32
    timeKillEvent(timerID);
#endif
}

/***********************************************************/
/* serial device */

#ifdef _WIN32

int serial_open_device(void)
{
    return -1;
}

#else

int serial_open_device(void)
{
    if (serial_console == NULL && nographic) {
        /* use console for serial port */
        return 0;
    } else {
#if 0
        char slave_name[1024];
        int master_fd, slave_fd;
        
        /* Not satisfying */
        if (openpty(&master_fd, &slave_fd, slave_name, NULL, NULL) < 0) {
            fprintf(stderr, "warning: could not create pseudo terminal for serial port\n");
            return -1;
        }
        fprintf(stderr, "Serial port redirected to %s\n", slave_name);
        return master_fd;
#else
        return -1;
#endif
    }
}

#endif

/***********************************************************/
/* Linux network device redirectors */

void hex_dump(FILE *f, const uint8_t *buf, int size)
{
    int len, i, j, c;

    for(i=0;i<size;i+=16) {
        len = size - i;
        if (len > 16)
            len = 16;
        fprintf(f, "%08x ", i);
        for(j=0;j<16;j++) {
            if (j < len)
                fprintf(f, " %02x", buf[i+j]);
            else
                fprintf(f, "   ");
        }
        fprintf(f, " ");
        for(j=0;j<len;j++) {
            c = buf[i+j];
            if (c < ' ' || c > '~')
                c = '.';
            fprintf(f, "%c", c);
        }
        fprintf(f, "\n");
    }
}

void qemu_send_packet(NetDriverState *nd, const uint8_t *buf, int size)
{
    nd->send_packet(nd, buf, size);
}

void qemu_add_read_packet(NetDriverState *nd, IOCanRWHandler *fd_can_read, 
                          IOReadHandler *fd_read, void *opaque)
{
    nd->add_read_packet(nd, fd_can_read, fd_read, opaque);
}

/* dummy network adapter */

static void dummy_send_packet(NetDriverState *nd, const uint8_t *buf, int size)
{
}

static void dummy_add_read_packet(NetDriverState *nd, 
                                  IOCanRWHandler *fd_can_read, 
                                  IOReadHandler *fd_read, void *opaque)
{
}

static int net_dummy_init(NetDriverState *nd)
{
    nd->send_packet = dummy_send_packet;
    nd->add_read_packet = dummy_add_read_packet;
    pstrcpy(nd->ifname, sizeof(nd->ifname), "dummy");
    return 0;
}

#if defined(CONFIG_SLIRP)

/* slirp network adapter */

static void *slirp_fd_opaque;
static IOCanRWHandler *slirp_fd_can_read;
static IOReadHandler *slirp_fd_read;
static int slirp_inited;

int slirp_can_output(void)
{
    return slirp_fd_can_read(slirp_fd_opaque);
}

void slirp_output(const uint8_t *pkt, int pkt_len)
{
#if 0
    printf("output:\n");
    hex_dump(stdout, pkt, pkt_len);
#endif
    slirp_fd_read(slirp_fd_opaque, pkt, pkt_len);
}

static void slirp_send_packet(NetDriverState *nd, const uint8_t *buf, int size)
{
#if 0
    printf("input:\n");
    hex_dump(stdout, buf, size);
#endif
    slirp_input(buf, size);
}

static void slirp_add_read_packet(NetDriverState *nd, 
                                  IOCanRWHandler *fd_can_read, 
                                  IOReadHandler *fd_read, void *opaque)
{
    slirp_fd_opaque = opaque;
    slirp_fd_can_read = fd_can_read;
    slirp_fd_read = fd_read;
}

static int net_slirp_init(NetDriverState *nd)
{
    if (!slirp_inited) {
        slirp_inited = 1;
        slirp_init();
    }
    nd->send_packet = slirp_send_packet;
    nd->add_read_packet = slirp_add_read_packet;
    pstrcpy(nd->ifname, sizeof(nd->ifname), "slirp");
    return 0;
}

#endif /* CONFIG_SLIRP */

#if !defined(_WIN32)
#ifdef _BSD
static int tun_open(char *ifname, int ifname_size)
{
    int fd;
    char *dev;
    struct stat s;

    fd = open("/dev/tap", O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "warning: could not open /dev/tap: no virtual network emulation\n");
        return -1;
    }

    fstat(fd, &s);
    dev = devname(s.st_rdev, S_IFCHR);
    pstrcpy(ifname, ifname_size, dev);

    fcntl(fd, F_SETFL, O_NONBLOCK);
    return fd;
}
#else
static int tun_open(char *ifname, int ifname_size)
{
    struct ifreq ifr;
    int fd, ret;
    
    fd = open("/dev/net/tun", O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "warning: could not open /dev/net/tun: no virtual network emulation\n");
        return -1;
    }
    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    pstrcpy(ifr.ifr_name, IFNAMSIZ, "tun%d");
    ret = ioctl(fd, TUNSETIFF, (void *) &ifr);
    if (ret != 0) {
        fprintf(stderr, "warning: could not configure /dev/net/tun: no virtual network emulation\n");
        close(fd);
        return -1;
    }
    printf("Connected to host network interface: %s\n", ifr.ifr_name);
    pstrcpy(ifname, ifname_size, ifr.ifr_name);
    fcntl(fd, F_SETFL, O_NONBLOCK);
    return fd;
}
#endif

static void tun_send_packet(NetDriverState *nd, const uint8_t *buf, int size)
{
    write(nd->fd, buf, size);
}

static void tun_add_read_packet(NetDriverState *nd, 
                                IOCanRWHandler *fd_can_read, 
                                IOReadHandler *fd_read, void *opaque)
{
    qemu_add_fd_read_handler(nd->fd, fd_can_read, fd_read, opaque);
}

static int net_tun_init(NetDriverState *nd)
{
    int pid, status;
    char *args[3];
    char **parg;

    nd->fd = tun_open(nd->ifname, sizeof(nd->ifname));
    if (nd->fd < 0)
        return -1;

    /* try to launch network init script */
    pid = fork();
    if (pid >= 0) {
        if (pid == 0) {
            parg = args;
            *parg++ = network_script;
            *parg++ = nd->ifname;
            *parg++ = NULL;
            execv(network_script, args);
            exit(1);
        }
        while (waitpid(pid, &status, 0) != pid);
        if (!WIFEXITED(status) ||
            WEXITSTATUS(status) != 0) {
            fprintf(stderr, "%s: could not launch network script\n",
                    network_script);
        }
    }
    nd->send_packet = tun_send_packet;
    nd->add_read_packet = tun_add_read_packet;
    return 0;
}

static int net_fd_init(NetDriverState *nd, int fd)
{
    nd->fd = fd;
    nd->send_packet = tun_send_packet;
    nd->add_read_packet = tun_add_read_packet;
    pstrcpy(nd->ifname, sizeof(nd->ifname), "tunfd");
    return 0;
}

#endif /* !_WIN32 */

/***********************************************************/
/* dumb display */

#ifdef _WIN32

static void term_exit(void)
{
}

static void term_init(void)
{
}

#else

/* init terminal so that we can grab keys */
static struct termios oldtty;
static int old_fd0_flags;

static void term_exit(void)
{
    tcsetattr (0, TCSANOW, &oldtty);
    fcntl(0, F_SETFL, old_fd0_flags);
}

static void term_init(void)
{
    struct termios tty;

    tcgetattr (0, &tty);
    oldtty = tty;
    old_fd0_flags = fcntl(0, F_GETFL);

    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP
                          |INLCR|IGNCR|ICRNL|IXON);
    tty.c_oflag |= OPOST;
    tty.c_lflag &= ~(ECHO|ECHONL|ICANON|IEXTEN);
    /* if graphical mode, we allow Ctrl-C handling */
    if (nographic)
        tty.c_lflag &= ~ISIG;
    tty.c_cflag &= ~(CSIZE|PARENB);
    tty.c_cflag |= CS8;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;
    
    tcsetattr (0, TCSANOW, &tty);

    atexit(term_exit);

    fcntl(0, F_SETFL, O_NONBLOCK);
}

#endif

static void dumb_update(DisplayState *ds, int x, int y, int w, int h)
{
}

static void dumb_resize(DisplayState *ds, int w, int h)
{
}

static void dumb_refresh(DisplayState *ds)
{
    vga_update_display();
}

void dumb_display_init(DisplayState *ds)
{
    ds->data = NULL;
    ds->linesize = 0;
    ds->depth = 0;
    ds->dpy_update = dumb_update;
    ds->dpy_resize = dumb_resize;
    ds->dpy_refresh = dumb_refresh;
}

#if !defined(CONFIG_SOFTMMU)
/***********************************************************/
/* cpu signal handler */
static void host_segv_handler(int host_signum, siginfo_t *info, 
                              void *puc)
{
    if (cpu_signal_handler(host_signum, info, puc))
        return;
    term_exit();
    abort();
}
#endif

/***********************************************************/
/* I/O handling */

#define MAX_IO_HANDLERS 64

typedef struct IOHandlerRecord {
    int fd;
    IOCanRWHandler *fd_can_read;
    IOReadHandler *fd_read;
    void *opaque;
    /* temporary data */
    struct pollfd *ufd;
    int max_size;
    struct IOHandlerRecord *next;
} IOHandlerRecord;

static IOHandlerRecord *first_io_handler;

int qemu_add_fd_read_handler(int fd, IOCanRWHandler *fd_can_read, 
                             IOReadHandler *fd_read, void *opaque)
{
    IOHandlerRecord *ioh;

    ioh = qemu_mallocz(sizeof(IOHandlerRecord));
    if (!ioh)
        return -1;
    ioh->fd = fd;
    ioh->fd_can_read = fd_can_read;
    ioh->fd_read = fd_read;
    ioh->opaque = opaque;
    ioh->next = first_io_handler;
    first_io_handler = ioh;
    return 0;
}

void qemu_del_fd_read_handler(int fd)
{
    IOHandlerRecord **pioh, *ioh;

    pioh = &first_io_handler;
    for(;;) {
        ioh = *pioh;
        if (ioh == NULL)
            break;
        if (ioh->fd == fd) {
            *pioh = ioh->next;
            break;
        }
        pioh = &ioh->next;
    }
}

/***********************************************************/
/* savevm/loadvm support */

void qemu_put_buffer(QEMUFile *f, const uint8_t *buf, int size)
{
    fwrite(buf, 1, size, f);
}

void qemu_put_byte(QEMUFile *f, int v)
{
    fputc(v, f);
}

void qemu_put_be16(QEMUFile *f, unsigned int v)
{
    qemu_put_byte(f, v >> 8);
    qemu_put_byte(f, v);
}

void qemu_put_be32(QEMUFile *f, unsigned int v)
{
    qemu_put_byte(f, v >> 24);
    qemu_put_byte(f, v >> 16);
    qemu_put_byte(f, v >> 8);
    qemu_put_byte(f, v);
}

void qemu_put_be64(QEMUFile *f, uint64_t v)
{
    qemu_put_be32(f, v >> 32);
    qemu_put_be32(f, v);
}

int qemu_get_buffer(QEMUFile *f, uint8_t *buf, int size)
{
    return fread(buf, 1, size, f);
}

int qemu_get_byte(QEMUFile *f)
{
    int v;
    v = fgetc(f);
    if (v == EOF)
        return 0;
    else
        return v;
}

unsigned int qemu_get_be16(QEMUFile *f)
{
    unsigned int v;
    v = qemu_get_byte(f) << 8;
    v |= qemu_get_byte(f);
    return v;
}

unsigned int qemu_get_be32(QEMUFile *f)
{
    unsigned int v;
    v = qemu_get_byte(f) << 24;
    v |= qemu_get_byte(f) << 16;
    v |= qemu_get_byte(f) << 8;
    v |= qemu_get_byte(f);
    return v;
}

uint64_t qemu_get_be64(QEMUFile *f)
{
    uint64_t v;
    v = (uint64_t)qemu_get_be32(f) << 32;
    v |= qemu_get_be32(f);
    return v;
}

int64_t qemu_ftell(QEMUFile *f)
{
    return ftell(f);
}

int64_t qemu_fseek(QEMUFile *f, int64_t pos, int whence)
{
    if (fseek(f, pos, whence) < 0)
        return -1;
    return ftell(f);
}

typedef struct SaveStateEntry {
    char idstr[256];
    int instance_id;
    int version_id;
    SaveStateHandler *save_state;
    LoadStateHandler *load_state;
    void *opaque;
    struct SaveStateEntry *next;
} SaveStateEntry;

static SaveStateEntry *first_se;

int register_savevm(const char *idstr, 
                    int instance_id, 
                    int version_id,
                    SaveStateHandler *save_state,
                    LoadStateHandler *load_state,
                    void *opaque)
{
    SaveStateEntry *se, **pse;

    se = qemu_malloc(sizeof(SaveStateEntry));
    if (!se)
        return -1;
    pstrcpy(se->idstr, sizeof(se->idstr), idstr);
    se->instance_id = instance_id;
    se->version_id = version_id;
    se->save_state = save_state;
    se->load_state = load_state;
    se->opaque = opaque;
    se->next = NULL;

    /* add at the end of list */
    pse = &first_se;
    while (*pse != NULL)
        pse = &(*pse)->next;
    *pse = se;
    return 0;
}

#define QEMU_VM_FILE_MAGIC   0x5145564d
#define QEMU_VM_FILE_VERSION 0x00000001

int qemu_savevm(const char *filename)
{
    SaveStateEntry *se;
    QEMUFile *f;
    int len, len_pos, cur_pos, saved_vm_running, ret;

    saved_vm_running = vm_running;
    vm_stop(0);

    f = fopen(filename, "wb");
    if (!f) {
        ret = -1;
        goto the_end;
    }

    qemu_put_be32(f, QEMU_VM_FILE_MAGIC);
    qemu_put_be32(f, QEMU_VM_FILE_VERSION);

    for(se = first_se; se != NULL; se = se->next) {
        /* ID string */
        len = strlen(se->idstr);
        qemu_put_byte(f, len);
        qemu_put_buffer(f, se->idstr, len);

        qemu_put_be32(f, se->instance_id);
        qemu_put_be32(f, se->version_id);

        /* record size: filled later */
        len_pos = ftell(f);
        qemu_put_be32(f, 0);
        
        se->save_state(f, se->opaque);

        /* fill record size */
        cur_pos = ftell(f);
        len = ftell(f) - len_pos - 4;
        fseek(f, len_pos, SEEK_SET);
        qemu_put_be32(f, len);
        fseek(f, cur_pos, SEEK_SET);
    }

    fclose(f);
    ret = 0;
 the_end:
    if (saved_vm_running)
        vm_start();
    return ret;
}

static SaveStateEntry *find_se(const char *idstr, int instance_id)
{
    SaveStateEntry *se;

    for(se = first_se; se != NULL; se = se->next) {
        if (!strcmp(se->idstr, idstr) && 
            instance_id == se->instance_id)
            return se;
    }
    return NULL;
}

int qemu_loadvm(const char *filename)
{
    SaveStateEntry *se;
    QEMUFile *f;
    int len, cur_pos, ret, instance_id, record_len, version_id;
    int saved_vm_running;
    unsigned int v;
    char idstr[256];
    
    saved_vm_running = vm_running;
    vm_stop(0);

    f = fopen(filename, "rb");
    if (!f) {
        ret = -1;
        goto the_end;
    }

    v = qemu_get_be32(f);
    if (v != QEMU_VM_FILE_MAGIC)
        goto fail;
    v = qemu_get_be32(f);
    if (v != QEMU_VM_FILE_VERSION) {
    fail:
        fclose(f);
        ret = -1;
        goto the_end;
    }
    for(;;) {
#if defined (DO_TB_FLUSH)
        tb_flush(global_env);
#endif
        len = qemu_get_byte(f);
        if (feof(f))
            break;
        qemu_get_buffer(f, idstr, len);
        idstr[len] = '\0';
        instance_id = qemu_get_be32(f);
        version_id = qemu_get_be32(f);
        record_len = qemu_get_be32(f);
#if 0
        printf("idstr=%s instance=0x%x version=%d len=%d\n", 
               idstr, instance_id, version_id, record_len);
#endif
        cur_pos = ftell(f);
        se = find_se(idstr, instance_id);
        if (!se) {
            fprintf(stderr, "qemu: warning: instance 0x%x of device '%s' not present in current VM\n", 
                    instance_id, idstr);
        } else {
            ret = se->load_state(f, se->opaque, version_id);
            if (ret < 0) {
                fprintf(stderr, "qemu: warning: error while loading state for instance 0x%x of device '%s'\n", 
                        instance_id, idstr);
            }
        }
        /* always seek to exact end of record */
        qemu_fseek(f, cur_pos + record_len, SEEK_SET);
    }
    fclose(f);
    ret = 0;
 the_end:
    if (saved_vm_running)
        vm_start();
    return ret;
}

/***********************************************************/
/* cpu save/restore */

#if defined(TARGET_I386)

static void cpu_put_seg(QEMUFile *f, SegmentCache *dt)
{
    qemu_put_be32(f, dt->selector);
    qemu_put_be32(f, (uint32_t)dt->base);
    qemu_put_be32(f, dt->limit);
    qemu_put_be32(f, dt->flags);
}

static void cpu_get_seg(QEMUFile *f, SegmentCache *dt)
{
    dt->selector = qemu_get_be32(f);
    dt->base = (uint8_t *)qemu_get_be32(f);
    dt->limit = qemu_get_be32(f);
    dt->flags = qemu_get_be32(f);
}

void cpu_save(QEMUFile *f, void *opaque)
{
    CPUState *env = opaque;
    uint16_t fptag, fpus, fpuc;
    uint32_t hflags;
    int i;

    for(i = 0; i < 8; i++)
        qemu_put_be32s(f, &env->regs[i]);
    qemu_put_be32s(f, &env->eip);
    qemu_put_be32s(f, &env->eflags);
    qemu_put_be32s(f, &env->eflags);
    hflags = env->hflags; /* XXX: suppress most of the redundant hflags */
    qemu_put_be32s(f, &hflags);
    
    /* FPU */
    fpuc = env->fpuc;
    fpus = (env->fpus & ~0x3800) | (env->fpstt & 0x7) << 11;
    fptag = 0;
    for (i=7; i>=0; i--) {
	fptag <<= 2;
	if (env->fptags[i]) {
            fptag |= 3;
        }
    }
    
    qemu_put_be16s(f, &fpuc);
    qemu_put_be16s(f, &fpus);
    qemu_put_be16s(f, &fptag);

    for(i = 0; i < 8; i++) {
        uint64_t mant;
        uint16_t exp;
        cpu_get_fp80(&mant, &exp, env->fpregs[i]);
        qemu_put_be64(f, mant);
        qemu_put_be16(f, exp);
    }

    for(i = 0; i < 6; i++)
        cpu_put_seg(f, &env->segs[i]);
    cpu_put_seg(f, &env->ldt);
    cpu_put_seg(f, &env->tr);
    cpu_put_seg(f, &env->gdt);
    cpu_put_seg(f, &env->idt);
    
    qemu_put_be32s(f, &env->sysenter_cs);
    qemu_put_be32s(f, &env->sysenter_esp);
    qemu_put_be32s(f, &env->sysenter_eip);
    
    qemu_put_be32s(f, &env->cr[0]);
    qemu_put_be32s(f, &env->cr[2]);
    qemu_put_be32s(f, &env->cr[3]);
    qemu_put_be32s(f, &env->cr[4]);
    
    for(i = 0; i < 8; i++)
        qemu_put_be32s(f, &env->dr[i]);

    /* MMU */
    qemu_put_be32s(f, &env->a20_mask);
}

int cpu_load(QEMUFile *f, void *opaque, int version_id)
{
    CPUState *env = opaque;
    int i;
    uint32_t hflags;
    uint16_t fpus, fpuc, fptag;

    if (version_id != 2)
        return -EINVAL;
    for(i = 0; i < 8; i++)
        qemu_get_be32s(f, &env->regs[i]);
    qemu_get_be32s(f, &env->eip);
    qemu_get_be32s(f, &env->eflags);
    qemu_get_be32s(f, &env->eflags);
    qemu_get_be32s(f, &hflags);

    qemu_get_be16s(f, &fpuc);
    qemu_get_be16s(f, &fpus);
    qemu_get_be16s(f, &fptag);

    for(i = 0; i < 8; i++) {
        uint64_t mant;
        uint16_t exp;
        mant = qemu_get_be64(f);
        exp = qemu_get_be16(f);
        env->fpregs[i] = cpu_set_fp80(mant, exp);
    }

    env->fpuc = fpuc;
    env->fpstt = (fpus >> 11) & 7;
    env->fpus = fpus & ~0x3800;
    for(i = 0; i < 8; i++) {
        env->fptags[i] = ((fptag & 3) == 3);
        fptag >>= 2;
    }
    
    for(i = 0; i < 6; i++)
        cpu_get_seg(f, &env->segs[i]);
    cpu_get_seg(f, &env->ldt);
    cpu_get_seg(f, &env->tr);
    cpu_get_seg(f, &env->gdt);
    cpu_get_seg(f, &env->idt);
    
    qemu_get_be32s(f, &env->sysenter_cs);
    qemu_get_be32s(f, &env->sysenter_esp);
    qemu_get_be32s(f, &env->sysenter_eip);
    
    qemu_get_be32s(f, &env->cr[0]);
    qemu_get_be32s(f, &env->cr[2]);
    qemu_get_be32s(f, &env->cr[3]);
    qemu_get_be32s(f, &env->cr[4]);
    
    for(i = 0; i < 8; i++)
        qemu_get_be32s(f, &env->dr[i]);

    /* MMU */
    qemu_get_be32s(f, &env->a20_mask);

    /* XXX: compute hflags from scratch, except for CPL and IIF */
    env->hflags = hflags;
    tlb_flush(env, 1);
    return 0;
}

#elif defined(TARGET_PPC)
void cpu_save(QEMUFile *f, void *opaque)
{
}

int cpu_load(QEMUFile *f, void *opaque, int version_id)
{
    return 0;
}
#else

#warning No CPU save/restore functions

#endif

/***********************************************************/
/* ram save/restore */

/* we just avoid storing empty pages */
static void ram_put_page(QEMUFile *f, const uint8_t *buf, int len)
{
    int i, v;

    v = buf[0];
    for(i = 1; i < len; i++) {
        if (buf[i] != v)
            goto normal_save;
    }
    qemu_put_byte(f, 1);
    qemu_put_byte(f, v);
    return;
 normal_save:
    qemu_put_byte(f, 0); 
    qemu_put_buffer(f, buf, len);
}

static int ram_get_page(QEMUFile *f, uint8_t *buf, int len)
{
    int v;

    v = qemu_get_byte(f);
    switch(v) {
    case 0:
        if (qemu_get_buffer(f, buf, len) != len)
            return -EIO;
        break;
    case 1:
        v = qemu_get_byte(f);
        memset(buf, v, len);
        break;
    default:
        return -EINVAL;
    }
    return 0;
}

static void ram_save(QEMUFile *f, void *opaque)
{
    int i;
    qemu_put_be32(f, phys_ram_size);
    for(i = 0; i < phys_ram_size; i+= TARGET_PAGE_SIZE) {
        ram_put_page(f, phys_ram_base + i, TARGET_PAGE_SIZE);
    }
}

static int ram_load(QEMUFile *f, void *opaque, int version_id)
{
    int i, ret;

    if (version_id != 1)
        return -EINVAL;
    if (qemu_get_be32(f) != phys_ram_size)
        return -EINVAL;
    for(i = 0; i < phys_ram_size; i+= TARGET_PAGE_SIZE) {
        ret = ram_get_page(f, phys_ram_base + i, TARGET_PAGE_SIZE);
        if (ret)
            return ret;
    }
    return 0;
}

/***********************************************************/
/* main execution loop */

void gui_update(void *opaque)
{
    display_state.dpy_refresh(&display_state);
    qemu_mod_timer(gui_timer, GUI_REFRESH_INTERVAL + qemu_get_clock(rt_clock));
}

/* XXX: support several handlers */
VMStopHandler *vm_stop_cb;
VMStopHandler *vm_stop_opaque;

int qemu_add_vm_stop_handler(VMStopHandler *cb, void *opaque)
{
    vm_stop_cb = cb;
    vm_stop_opaque = opaque;
    return 0;
}

void qemu_del_vm_stop_handler(VMStopHandler *cb, void *opaque)
{
    vm_stop_cb = NULL;
}

void vm_start(void)
{
    if (!vm_running) {
        cpu_enable_ticks();
        vm_running = 1;
    }
}

void vm_stop(int reason) 
{
    if (vm_running) {
        cpu_disable_ticks();
        vm_running = 0;
        if (reason != 0) {
            if (vm_stop_cb) {
                vm_stop_cb(vm_stop_opaque, reason);
            }
        }
    }
}

/* reset/shutdown handler */

typedef struct QEMUResetEntry {
    QEMUResetHandler *func;
    void *opaque;
    struct QEMUResetEntry *next;
} QEMUResetEntry;

static QEMUResetEntry *first_reset_entry;
static int reset_requested;
static int shutdown_requested;

void qemu_register_reset(QEMUResetHandler *func, void *opaque)
{
    QEMUResetEntry **pre, *re;

    pre = &first_reset_entry;
    while (*pre != NULL)
        pre = &(*pre)->next;
    re = qemu_mallocz(sizeof(QEMUResetEntry));
    re->func = func;
    re->opaque = opaque;
    re->next = NULL;
    *pre = re;
}

void qemu_system_reset(void)
{
    QEMUResetEntry *re;

    /* reset all devices */
    for(re = first_reset_entry; re != NULL; re = re->next) {
        re->func(re->opaque);
    }
}

void qemu_system_reset_request(void)
{
    reset_requested = 1;
    cpu_interrupt(cpu_single_env, CPU_INTERRUPT_EXIT);
}

void qemu_system_shutdown_request(void)
{
    shutdown_requested = 1;
    cpu_interrupt(cpu_single_env, CPU_INTERRUPT_EXIT);
}

static void main_cpu_reset(void *opaque)
{
#ifdef TARGET_I386
    CPUState *env = opaque;
    cpu_reset(env);
#endif
}

int main_loop(void)
{
#ifndef _WIN32
    struct pollfd ufds[MAX_IO_HANDLERS + 1], *pf;
    IOHandlerRecord *ioh, *ioh_next;
    uint8_t buf[4096];
    int n, max_size;
#endif
    int ret, timeout;
    CPUState *env = global_env;

    for(;;) {
        if (vm_running) {
            ret = cpu_exec(env);
            if (shutdown_requested) {
                ret = EXCP_INTERRUPT; 
                break;
            }
            if (reset_requested) {
                reset_requested = 0;
                qemu_system_reset();
                ret = EXCP_INTERRUPT; 
            }
            if (ret == EXCP_DEBUG) {
                vm_stop(EXCP_DEBUG);
            }
            /* if hlt instruction, we wait until the next IRQ */
            /* XXX: use timeout computed from timers */
            if (ret == EXCP_HLT) 
                timeout = 10;
            else
                timeout = 0;
        } else {
            timeout = 10;
        }

#ifdef _WIN32
        if (timeout > 0)
            Sleep(timeout);
#else

        /* poll any events */
        /* XXX: separate device handlers from system ones */
        pf = ufds;
        for(ioh = first_io_handler; ioh != NULL; ioh = ioh->next) {
            if (!ioh->fd_can_read) {
                max_size = 0;
                pf->fd = ioh->fd;
                pf->events = POLLIN;
                ioh->ufd = pf;
                pf++;
            } else {
                max_size = ioh->fd_can_read(ioh->opaque);
                if (max_size > 0) {
                    if (max_size > sizeof(buf))
                        max_size = sizeof(buf);
                    pf->fd = ioh->fd;
                    pf->events = POLLIN;
                    ioh->ufd = pf;
                    pf++;
                } else {
                    ioh->ufd = NULL;
                }
            }
            ioh->max_size = max_size;
        }
        
        ret = poll(ufds, pf - ufds, timeout);
        if (ret > 0) {
            /* XXX: better handling of removal */
            for(ioh = first_io_handler; ioh != NULL; ioh = ioh_next) {
                ioh_next = ioh->next;
                pf = ioh->ufd;
                if (pf) {
                    if (pf->revents & POLLIN) {
                        if (ioh->max_size == 0) {
                            /* just a read event */
                            ioh->fd_read(ioh->opaque, NULL, 0);
                        } else {
                            n = read(ioh->fd, buf, ioh->max_size);
                            if (n >= 0) {
                                ioh->fd_read(ioh->opaque, buf, n);
                            } else if (errno != EAGAIN) {
                                ioh->fd_read(ioh->opaque, NULL, -errno);
                            }
                        }
                    }
                }
            }
        }

#if defined(CONFIG_SLIRP)
        /* XXX: merge with poll() */
        if (slirp_inited) {
            fd_set rfds, wfds, xfds;
            int nfds;
            struct timeval tv;

            nfds = -1;
            FD_ZERO(&rfds);
            FD_ZERO(&wfds);
            FD_ZERO(&xfds);
            slirp_select_fill(&nfds, &rfds, &wfds, &xfds);
            tv.tv_sec = 0;
            tv.tv_usec = 0;
            ret = select(nfds + 1, &rfds, &wfds, &xfds, &tv);
            if (ret >= 0) {
                slirp_select_poll(&rfds, &wfds, &xfds);
            }
        }
#endif

#endif

        if (vm_running) {
            qemu_run_timers(&active_timers[QEMU_TIMER_VIRTUAL], 
                            qemu_get_clock(vm_clock));
            
            if (audio_enabled) {
                /* XXX: add explicit timer */
                SB16_run();
            }
            
            /* run dma transfers, if any */
            DMA_run();
        }

        /* real time timers */
        qemu_run_timers(&active_timers[QEMU_TIMER_REALTIME], 
                        qemu_get_clock(rt_clock));
    }
    cpu_disable_ticks();
    return ret;
}

void help(void)
{
    printf("QEMU PC emulator version " QEMU_VERSION ", Copyright (c) 2003-2004 Fabrice Bellard\n"
           "usage: %s [options] [disk_image]\n"
           "\n"
           "'disk_image' is a raw hard image image for IDE hard disk 0\n"
           "\n"
           "Standard options:\n"
           "-fda/-fdb file  use 'file' as floppy disk 0/1 image\n"
           "-hda/-hdb file  use 'file' as IDE hard disk 0/1 image\n"
           "-hdc/-hdd file  use 'file' as IDE hard disk 2/3 image\n"
           "-cdrom file     use 'file' as IDE cdrom image (cdrom is ide1 master)\n"
           "-boot [a|b|c|d] boot on floppy (a, b), hard disk (c) or CD-ROM (d)\n"
	   "-snapshot       write to temporary files instead of disk image files\n"
           "-m megs         set virtual RAM size to megs MB [default=%d]\n"
           "-nographic      disable graphical output and redirect serial I/Os to console\n"
           "-enable-audio   enable audio support\n"
           "-localtime      set the real time clock to local time [default=utc]\n"
#ifdef TARGET_PPC
           "-prep           Simulate a PREP system (default is PowerMAC)\n"
           "-g WxH[xDEPTH]  Set the initial VGA graphic mode\n"
#endif
           "\n"
           "Network options:\n"
           "-nics n         simulate 'n' network cards [default=1]\n"
           "-macaddr addr   set the mac address of the first interface\n"
           "-n script       set tap/tun network init script [default=%s]\n"
           "-tun-fd fd      use this fd as already opened tap/tun interface\n"
#ifdef CONFIG_SLIRP
           "-user-net       use user mode network stack [default if no tap/tun script]\n"
#endif
           "-dummy-net      use dummy network stack\n"
           "\n"
           "Linux boot specific:\n"
           "-kernel bzImage use 'bzImage' as kernel image\n"
           "-append cmdline use 'cmdline' as kernel command line\n"
           "-initrd file    use 'file' as initial ram disk\n"
           "\n"
           "Debug/Expert options:\n"
           "-S              freeze CPU at startup (use 'c' to start execution)\n"
           "-s              wait gdb connection to port %d\n"
           "-p port         change gdb connection port\n"
           "-d item1,...    output log to %s (use -d ? for a list of log items)\n"
           "-hdachs c,h,s   force hard disk 0 geometry (usually qemu can guess it)\n"
           "-L path         set the directory for the BIOS and VGA BIOS\n"
#ifdef USE_CODE_COPY
           "-no-code-copy   disable code copy acceleration\n"
#endif
#ifdef TARGET_I386
           "-isa            simulate an ISA-only system (default is PCI system)\n"
           "-std-vga        simulate a standard VGA card with VESA Bochs Extensions\n"
           "                (default is CL-GD5446 PCI VGA)\n"
#endif
           "\n"
           "During emulation, use C-a h to get terminal commands:\n",
#ifdef CONFIG_SOFTMMU
           "qemu",
#else
           "qemu-fast",
#endif
           DEFAULT_RAM_SIZE,
           DEFAULT_NETWORK_SCRIPT,
           DEFAULT_GDBSTUB_PORT,
           "/tmp/qemu.log");
    term_print_help();
#ifndef CONFIG_SOFTMMU
    printf("\n"
           "NOTE: this version of QEMU is faster but it needs slightly patched OSes to\n"
           "work. Please use the 'qemu' executable to have a more accurate (but slower)\n"
           "PC emulation.\n");
#endif
    exit(1);
}

#define HAS_ARG 0x0001

enum {
    QEMU_OPTION_h,

    QEMU_OPTION_fda,
    QEMU_OPTION_fdb,
    QEMU_OPTION_hda,
    QEMU_OPTION_hdb,
    QEMU_OPTION_hdc,
    QEMU_OPTION_hdd,
    QEMU_OPTION_cdrom,
    QEMU_OPTION_boot,
    QEMU_OPTION_snapshot,
    QEMU_OPTION_m,
    QEMU_OPTION_nographic,
    QEMU_OPTION_enable_audio,

    QEMU_OPTION_nics,
    QEMU_OPTION_macaddr,
    QEMU_OPTION_n,
    QEMU_OPTION_tun_fd,
    QEMU_OPTION_user_net,
    QEMU_OPTION_dummy_net,

    QEMU_OPTION_kernel,
    QEMU_OPTION_append,
    QEMU_OPTION_initrd,

    QEMU_OPTION_S,
    QEMU_OPTION_s,
    QEMU_OPTION_p,
    QEMU_OPTION_d,
    QEMU_OPTION_hdachs,
    QEMU_OPTION_L,
    QEMU_OPTION_no_code_copy,
    QEMU_OPTION_pci,
    QEMU_OPTION_isa,
    QEMU_OPTION_prep,
    QEMU_OPTION_localtime,
    QEMU_OPTION_cirrusvga,
    QEMU_OPTION_g,
    QEMU_OPTION_std_vga,
};

typedef struct QEMUOption {
    const char *name;
    int flags;
    int index;
} QEMUOption;

const QEMUOption qemu_options[] = {
    { "h", 0, QEMU_OPTION_h },

    { "fda", HAS_ARG, QEMU_OPTION_fda },
    { "fdb", HAS_ARG, QEMU_OPTION_fdb },
    { "hda", HAS_ARG, QEMU_OPTION_hda },
    { "hdb", HAS_ARG, QEMU_OPTION_hdb },
    { "hdc", HAS_ARG, QEMU_OPTION_hdc },
    { "hdd", HAS_ARG, QEMU_OPTION_hdd },
    { "cdrom", HAS_ARG, QEMU_OPTION_cdrom },
    { "boot", HAS_ARG, QEMU_OPTION_boot },
    { "snapshot", 0, QEMU_OPTION_snapshot },
    { "m", HAS_ARG, QEMU_OPTION_m },
    { "nographic", 0, QEMU_OPTION_nographic },
    { "enable-audio", 0, QEMU_OPTION_enable_audio },

    { "nics", HAS_ARG, QEMU_OPTION_nics},
    { "macaddr", HAS_ARG, QEMU_OPTION_macaddr},
    { "n", HAS_ARG, QEMU_OPTION_n },
    { "tun-fd", HAS_ARG, QEMU_OPTION_tun_fd },
#ifdef CONFIG_SLIRP
    { "user-net", 0, QEMU_OPTION_user_net },
#endif
    { "dummy-net", 0, QEMU_OPTION_dummy_net },

    { "kernel", HAS_ARG, QEMU_OPTION_kernel },
    { "append", HAS_ARG, QEMU_OPTION_append },
    { "initrd", HAS_ARG, QEMU_OPTION_initrd },

    { "S", 0, QEMU_OPTION_S },
    { "s", 0, QEMU_OPTION_s },
    { "p", HAS_ARG, QEMU_OPTION_p },
    { "d", HAS_ARG, QEMU_OPTION_d },
    { "hdachs", HAS_ARG, QEMU_OPTION_hdachs },
    { "L", HAS_ARG, QEMU_OPTION_L },
    { "no-code-copy", 0, QEMU_OPTION_no_code_copy },
#ifdef TARGET_PPC
    { "prep", 0, QEMU_OPTION_prep },
    { "g", 1, QEMU_OPTION_g },
#endif
    { "localtime", 0, QEMU_OPTION_localtime },
    { "isa", 0, QEMU_OPTION_isa },
    { "std-vga", 0, QEMU_OPTION_std_vga },

    /* temporary options */
    { "pci", 0, QEMU_OPTION_pci },
    { "cirrusvga", 0, QEMU_OPTION_cirrusvga },
    { NULL },
};

#if defined (TARGET_I386) && defined(USE_CODE_COPY)

/* this stack is only used during signal handling */
#define SIGNAL_STACK_SIZE 32768

static uint8_t *signal_stack;

#endif

#define NET_IF_TUN   0
#define NET_IF_USER  1
#define NET_IF_DUMMY 2

int main(int argc, char **argv)
{
#ifdef CONFIG_GDBSTUB
    int use_gdbstub, gdbstub_port;
#endif
    int i, has_cdrom;
    int snapshot, linux_boot;
    CPUState *env;
    const char *initrd_filename;
    const char *hd_filename[MAX_DISKS], *fd_filename[MAX_FD];
    const char *kernel_filename, *kernel_cmdline;
    DisplayState *ds = &display_state;
    int cyls, heads, secs;
    int start_emulation = 1;
    uint8_t macaddr[6];
    int net_if_type, nb_tun_fds, tun_fds[MAX_NICS];
    int optind;
    const char *r, *optarg;

#if !defined(CONFIG_SOFTMMU)
    /* we never want that malloc() uses mmap() */
    mallopt(M_MMAP_THRESHOLD, 4096 * 1024);
#endif
    initrd_filename = NULL;
    for(i = 0; i < MAX_FD; i++)
        fd_filename[i] = NULL;
    for(i = 0; i < MAX_DISKS; i++)
        hd_filename[i] = NULL;
    ram_size = DEFAULT_RAM_SIZE * 1024 * 1024;
    vga_ram_size = VGA_RAM_SIZE;
    bios_size = BIOS_SIZE;
    pstrcpy(network_script, sizeof(network_script), DEFAULT_NETWORK_SCRIPT);
#ifdef CONFIG_GDBSTUB
    use_gdbstub = 0;
    gdbstub_port = DEFAULT_GDBSTUB_PORT;
#endif
    snapshot = 0;
    nographic = 0;
    kernel_filename = NULL;
    kernel_cmdline = "";
    has_cdrom = 1;
    cyls = heads = secs = 0;

    nb_tun_fds = 0;
    net_if_type = -1;
    nb_nics = 1;
    /* default mac address of the first network interface */
    macaddr[0] = 0x52;
    macaddr[1] = 0x54;
    macaddr[2] = 0x00;
    macaddr[3] = 0x12;
    macaddr[4] = 0x34;
    macaddr[5] = 0x56;

    optind = 1;
    for(;;) {
        if (optind >= argc)
            break;
        r = argv[optind];
        if (r[0] != '-') {
            hd_filename[0] = argv[optind++];
        } else {
            const QEMUOption *popt;

            optind++;
            popt = qemu_options;
            for(;;) {
                if (!popt->name) {
                    fprintf(stderr, "%s: invalid option -- '%s'\n", 
                            argv[0], r);
                    exit(1);
                }
                if (!strcmp(popt->name, r + 1))
                    break;
                popt++;
            }
            if (popt->flags & HAS_ARG) {
                if (optind >= argc) {
                    fprintf(stderr, "%s: option '%s' requires an argument\n",
                            argv[0], r);
                    exit(1);
                }
                optarg = argv[optind++];
            } else {
                optarg = NULL;
            }

            switch(popt->index) {
            case QEMU_OPTION_initrd:
                initrd_filename = optarg;
                break;
            case QEMU_OPTION_hda:
                hd_filename[0] = optarg;
                break;
            case QEMU_OPTION_hdb:
                hd_filename[1] = optarg;
                break;
            case QEMU_OPTION_snapshot:
                snapshot = 1;
                break;
            case QEMU_OPTION_hdachs:
                {
                    const char *p;
                    p = optarg;
                    cyls = strtol(p, (char **)&p, 0);
                    if (*p != ',')
                        goto chs_fail;
                    p++;
                    heads = strtol(p, (char **)&p, 0);
                    if (*p != ',')
                        goto chs_fail;
                    p++;
                    secs = strtol(p, (char **)&p, 0);
                    if (*p != '\0') {
                    chs_fail:
                        cyls = 0;
                    }
                }
                break;
            case QEMU_OPTION_nographic:
                nographic = 1;
                break;
            case QEMU_OPTION_kernel:
                kernel_filename = optarg;
                break;
            case QEMU_OPTION_append:
                kernel_cmdline = optarg;
                break;
	    case QEMU_OPTION_tun_fd:
                {
                    const char *p;
                    int fd;
                    net_if_type = NET_IF_TUN;
                    if (nb_tun_fds < MAX_NICS) {
                        fd = strtol(optarg, (char **)&p, 0);
                        if (*p != '\0') {
                            fprintf(stderr, "qemu: invalid fd for network interface %d\n", nb_tun_fds);
                            exit(1);
                        }
                        tun_fds[nb_tun_fds++] = fd;
                    }
                }
		break;
            case QEMU_OPTION_hdc:
                hd_filename[2] = optarg;
                has_cdrom = 0;
                break;
            case QEMU_OPTION_hdd:
                hd_filename[3] = optarg;
                break;
            case QEMU_OPTION_cdrom:
                hd_filename[2] = optarg;
                has_cdrom = 1;
                break;
            case QEMU_OPTION_boot:
                boot_device = optarg[0];
                if (boot_device != 'a' && boot_device != 'b' &&
                    boot_device != 'c' && boot_device != 'd') {
                    fprintf(stderr, "qemu: invalid boot device '%c'\n", boot_device);
                    exit(1);
                }
                break;
            case QEMU_OPTION_fda:
                fd_filename[0] = optarg;
                break;
            case QEMU_OPTION_fdb:
                fd_filename[1] = optarg;
                break;
            case QEMU_OPTION_no_code_copy:
                code_copy_enabled = 0;
                break;
            case QEMU_OPTION_nics:
                nb_nics = atoi(optarg);
                if (nb_nics < 0 || nb_nics > MAX_NICS) {
                    fprintf(stderr, "qemu: invalid number of network interfaces\n");
                    exit(1);
                }
                break;
            case QEMU_OPTION_macaddr:
                {
                    const char *p;
                    int i;
                    p = optarg;
                    for(i = 0; i < 6; i++) {
                        macaddr[i] = strtol(p, (char **)&p, 16);
                        if (i == 5) {
                            if (*p != '\0') 
                                goto macaddr_error;
                        } else {
                            if (*p != ':') {
                            macaddr_error:
                                fprintf(stderr, "qemu: invalid syntax for ethernet address\n");
                                exit(1);
                            }
                            p++;
                        }
                    }
                }
                break;
            case QEMU_OPTION_user_net:
                net_if_type = NET_IF_USER;
                break;
            case QEMU_OPTION_dummy_net:
                net_if_type = NET_IF_DUMMY;
                break;
            case QEMU_OPTION_enable_audio:
                audio_enabled = 1;
                break;
            case QEMU_OPTION_h:
                help();
                break;
            case QEMU_OPTION_m:
                ram_size = atoi(optarg) * 1024 * 1024;
                if (ram_size <= 0)
                    help();
                if (ram_size > PHYS_RAM_MAX_SIZE) {
                    fprintf(stderr, "qemu: at most %d MB RAM can be simulated\n",
                            PHYS_RAM_MAX_SIZE / (1024 * 1024));
                    exit(1);
                }
                break;
            case QEMU_OPTION_d:
                {
                    int mask;
                    CPULogItem *item;
                    
                    mask = cpu_str_to_log_mask(optarg);
                    if (!mask) {
                        printf("Log items (comma separated):\n");
                    for(item = cpu_log_items; item->mask != 0; item++) {
                        printf("%-10s %s\n", item->name, item->help);
                    }
                    exit(1);
                    }
                    cpu_set_log(mask);
                }
                break;
            case QEMU_OPTION_n:
                pstrcpy(network_script, sizeof(network_script), optarg);
                break;
#ifdef CONFIG_GDBSTUB
            case QEMU_OPTION_s:
                use_gdbstub = 1;
                break;
            case QEMU_OPTION_p:
                gdbstub_port = atoi(optarg);
                break;
#endif
            case QEMU_OPTION_L:
                bios_dir = optarg;
                break;
            case QEMU_OPTION_S:
                start_emulation = 0;
                break;
            case QEMU_OPTION_pci:
                pci_enabled = 1;
                break;
            case QEMU_OPTION_isa:
                pci_enabled = 0;
                break;
            case QEMU_OPTION_prep:
                prep_enabled = 1;
                break;
            case QEMU_OPTION_localtime:
                rtc_utc = 0;
                break;
            case QEMU_OPTION_cirrusvga:
                cirrus_vga_enabled = 1;
                break;
            case QEMU_OPTION_std_vga:
                cirrus_vga_enabled = 0;
                break;
            case QEMU_OPTION_g:
                {
                    const char *p;
                    int w, h, depth;
                    p = optarg;
                    w = strtol(p, (char **)&p, 10);
                    if (w <= 0) {
                    graphic_error:
                        fprintf(stderr, "qemu: invalid resolution or depth\n");
                        exit(1);
                    }
                    if (*p != 'x')
                        goto graphic_error;
                    p++;
                    h = strtol(p, (char **)&p, 10);
                    if (h <= 0)
                        goto graphic_error;
                    if (*p == 'x') {
                        p++;
                        depth = strtol(p, (char **)&p, 10);
                        if (depth != 8 && depth != 15 && depth != 16 && 
                            depth != 24 && depth != 32)
                            goto graphic_error;
                    } else if (*p == '\0') {
                        depth = graphic_depth;
                    } else {
                        goto graphic_error;
                    }
                    
                    graphic_width = w;
                    graphic_height = h;
                    graphic_depth = depth;
                }
                break;
            }
        }
    }

    linux_boot = (kernel_filename != NULL);
        
    if (!linux_boot && hd_filename[0] == '\0' && hd_filename[2] == '\0' &&
        fd_filename[0] == '\0')
        help();
    
    /* boot to cd by default if no hard disk */
    if (hd_filename[0] == '\0' && boot_device == 'c') {
        if (fd_filename[0] != '\0')
            boot_device = 'a';
        else
            boot_device = 'd';
    }

#if !defined(CONFIG_SOFTMMU)
    /* must avoid mmap() usage of glibc by setting a buffer "by hand" */
    {
        static uint8_t stdout_buf[4096];
        setvbuf(stdout, stdout_buf, _IOLBF, sizeof(stdout_buf));
    }
#else
    setvbuf(stdout, NULL, _IOLBF, 0);
#endif

    /* init host network redirectors */
    if (net_if_type == -1) {
        net_if_type = NET_IF_TUN;
#if defined(CONFIG_SLIRP)
        if (access(network_script, R_OK) < 0) {
            net_if_type = NET_IF_USER;
        }
#endif
    }

    for(i = 0; i < nb_nics; i++) {
        NetDriverState *nd = &nd_table[i];
        nd->index = i;
        /* init virtual mac address */
        nd->macaddr[0] = macaddr[0];
        nd->macaddr[1] = macaddr[1];
        nd->macaddr[2] = macaddr[2];
        nd->macaddr[3] = macaddr[3];
        nd->macaddr[4] = macaddr[4];
        nd->macaddr[5] = macaddr[5] + i;
        switch(net_if_type) {
#if defined(CONFIG_SLIRP)
        case NET_IF_USER:
            net_slirp_init(nd);
            break;
#endif
#if !defined(_WIN32)
        case NET_IF_TUN:
            if (i < nb_tun_fds) {
                net_fd_init(nd, tun_fds[i]);
            } else {
                if (net_tun_init(nd) < 0)
                    net_dummy_init(nd);
            }
            break;
#endif
        case NET_IF_DUMMY:
        default:
            net_dummy_init(nd);
            break;
        }
    }

    /* init the memory */
    phys_ram_size = ram_size + vga_ram_size + bios_size;

#ifdef CONFIG_SOFTMMU
#ifdef _BSD
    /* mallocs are always aligned on BSD. valloc is better for correctness */
    phys_ram_base = valloc(phys_ram_size);
#else
    phys_ram_base = memalign(TARGET_PAGE_SIZE, phys_ram_size);
#endif
    if (!phys_ram_base) {
        fprintf(stderr, "Could not allocate physical memory\n");
        exit(1);
    }
#else
    /* as we must map the same page at several addresses, we must use
       a fd */
    {
        const char *tmpdir;

        tmpdir = getenv("QEMU_TMPDIR");
        if (!tmpdir)
            tmpdir = "/tmp";
        snprintf(phys_ram_file, sizeof(phys_ram_file), "%s/vlXXXXXX", tmpdir);
        if (mkstemp(phys_ram_file) < 0) {
            fprintf(stderr, "Could not create temporary memory file '%s'\n", 
                    phys_ram_file);
            exit(1);
        }
        phys_ram_fd = open(phys_ram_file, O_CREAT | O_TRUNC | O_RDWR, 0600);
        if (phys_ram_fd < 0) {
            fprintf(stderr, "Could not open temporary memory file '%s'\n", 
                    phys_ram_file);
            exit(1);
        }
        ftruncate(phys_ram_fd, phys_ram_size);
        unlink(phys_ram_file);
        phys_ram_base = mmap(get_mmap_addr(phys_ram_size), 
                             phys_ram_size, 
                             PROT_WRITE | PROT_READ, MAP_SHARED | MAP_FIXED, 
                             phys_ram_fd, 0);
        if (phys_ram_base == MAP_FAILED) {
            fprintf(stderr, "Could not map physical memory\n");
            exit(1);
        }
    }
#endif

    /* we always create the cdrom drive, even if no disk is there */
    if (has_cdrom) {
        bs_table[2] = bdrv_new("cdrom");
        bdrv_set_type_hint(bs_table[2], BDRV_TYPE_CDROM);
    }

    /* open the virtual block devices */
    for(i = 0; i < MAX_DISKS; i++) {
        if (hd_filename[i]) {
            if (!bs_table[i]) {
                char buf[64];
                snprintf(buf, sizeof(buf), "hd%c", i + 'a');
                bs_table[i] = bdrv_new(buf);
            }
            if (bdrv_open(bs_table[i], hd_filename[i], snapshot) < 0) {
                fprintf(stderr, "qemu: could not open hard disk image '%s\n",
                        hd_filename[i]);
                exit(1);
            }
            if (i == 0 && cyls != 0) 
                bdrv_set_geometry_hint(bs_table[i], cyls, heads, secs);
        }
    }

    /* we always create at least one floppy disk */
    fd_table[0] = bdrv_new("fda");
    bdrv_set_type_hint(fd_table[0], BDRV_TYPE_FLOPPY);

    for(i = 0; i < MAX_FD; i++) {
        if (fd_filename[i]) {
            if (!fd_table[i]) {
                char buf[64];
                snprintf(buf, sizeof(buf), "fd%c", i + 'a');
                fd_table[i] = bdrv_new(buf);
                bdrv_set_type_hint(fd_table[i], BDRV_TYPE_FLOPPY);
            }
            if (fd_filename[i] != '\0') {
                if (bdrv_open(fd_table[i], fd_filename[i], snapshot) < 0) {
                    fprintf(stderr, "qemu: could not open floppy disk image '%s'\n",
                            fd_filename[i]);
                    exit(1);
                }
            }
        }
    }

    /* init CPU state */
    env = cpu_init();
    global_env = env;
    cpu_single_env = env;

    register_savevm("timer", 0, 1, timer_save, timer_load, env);
    register_savevm("cpu", 0, 2, cpu_save, cpu_load, env);
    register_savevm("ram", 0, 1, ram_save, ram_load, NULL);
    qemu_register_reset(main_cpu_reset, global_env);

    init_ioports();
    cpu_calibrate_ticks();

    /* terminal init */
    if (nographic) {
        dumb_display_init(ds);
    } else {
#ifdef CONFIG_SDL
        sdl_display_init(ds);
#else
        dumb_display_init(ds);
#endif
    }

    /* setup cpu signal handlers for MMU / self modifying code handling */
#if !defined(CONFIG_SOFTMMU)
    
#if defined (TARGET_I386) && defined(USE_CODE_COPY)
    {
        stack_t stk;
        signal_stack = memalign(16, SIGNAL_STACK_SIZE);
        stk.ss_sp = signal_stack;
        stk.ss_size = SIGNAL_STACK_SIZE;
        stk.ss_flags = 0;

        if (sigaltstack(&stk, NULL) < 0) {
            perror("sigaltstack");
            exit(1);
        }
    }
#endif
    {
        struct sigaction act;
        
        sigfillset(&act.sa_mask);
        act.sa_flags = SA_SIGINFO;
#if defined (TARGET_I386) && defined(USE_CODE_COPY)
        act.sa_flags |= SA_ONSTACK;
#endif
        act.sa_sigaction = host_segv_handler;
        sigaction(SIGSEGV, &act, NULL);
        sigaction(SIGBUS, &act, NULL);
#if defined (TARGET_I386) && defined(USE_CODE_COPY)
        sigaction(SIGFPE, &act, NULL);
#endif
    }
#endif

#ifndef _WIN32
    {
        struct sigaction act;
        sigfillset(&act.sa_mask);
        act.sa_flags = 0;
        act.sa_handler = SIG_IGN;
        sigaction(SIGPIPE, &act, NULL);
    }
#endif
    init_timers();

#if defined(TARGET_I386)
    pc_init(ram_size, vga_ram_size, boot_device,
            ds, fd_filename, snapshot,
            kernel_filename, kernel_cmdline, initrd_filename);
#elif defined(TARGET_PPC)
    ppc_init(ram_size, vga_ram_size, boot_device,
	     ds, fd_filename, snapshot,
	     kernel_filename, kernel_cmdline, initrd_filename);
#endif

    /* launched after the device init so that it can display or not a
       banner */
    monitor_init();

    gui_timer = qemu_new_timer(rt_clock, gui_update, NULL);
    qemu_mod_timer(gui_timer, qemu_get_clock(rt_clock));

#ifdef CONFIG_GDBSTUB
    if (use_gdbstub) {
        if (gdbserver_start(gdbstub_port) < 0) {
            fprintf(stderr, "Could not open gdbserver socket on port %d\n", 
                    gdbstub_port);
            exit(1);
        } else {
            printf("Waiting gdb connection on port %d\n", gdbstub_port);
        }
    } else 
#endif
    if (start_emulation)
    {
        vm_start();
    }
    term_init();
    main_loop();
    quit_timers();
    return 0;
}
