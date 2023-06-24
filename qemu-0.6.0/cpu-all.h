/*
 * defines common to all virtual CPUs
 * 
 *  Copyright (c) 2003 Fabrice Bellard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef CPU_ALL_H
#define CPU_ALL_H

#if defined(__arm__) || defined(__sparc__)
#define WORDS_ALIGNED
#endif

/* some important defines: 
 * 
 * WORDS_ALIGNED : if defined, the host cpu can only make word aligned
 * memory accesses.
 * 
 * WORDS_BIGENDIAN : if defined, the host cpu is big endian and
 * otherwise little endian.
 * 
 * (TARGET_WORDS_ALIGNED : same for target cpu (not supported yet))
 * 
 * TARGET_WORDS_BIGENDIAN : same for target cpu
 */

#include "bswap.h"

#if defined(WORDS_BIGENDIAN) != defined(TARGET_WORDS_BIGENDIAN)
#define BSWAP_NEEDED
#endif

#ifdef BSWAP_NEEDED

static inline uint16_t tswap16(uint16_t s)
{
    return bswap16(s);
}

static inline uint32_t tswap32(uint32_t s)
{
    return bswap32(s);
}

static inline uint64_t tswap64(uint64_t s)
{
    return bswap64(s);
}

static inline void tswap16s(uint16_t *s)
{
    *s = bswap16(*s);
}

static inline void tswap32s(uint32_t *s)
{
    *s = bswap32(*s);
}

static inline void tswap64s(uint64_t *s)
{
    *s = bswap64(*s);
}

#else

static inline uint16_t tswap16(uint16_t s)
{
    return s;
}

static inline uint32_t tswap32(uint32_t s)
{
    return s;
}

static inline uint64_t tswap64(uint64_t s)
{
    return s;
}

static inline void tswap16s(uint16_t *s)
{
}

static inline void tswap32s(uint32_t *s)
{
}

static inline void tswap64s(uint64_t *s)
{
}

#endif

#if TARGET_LONG_SIZE == 4
#define tswapl(s) tswap32(s)
#define tswapls(s) tswap32s((uint32_t *)(s))
#else
#define tswapl(s) tswap64(s)
#define tswapls(s) tswap64s((uint64_t *)(s))
#endif

/* NOTE: arm is horrible as double 32 bit words are stored in big endian ! */
typedef union {
    double d;
#if !defined(WORDS_BIGENDIAN) && !defined(__arm__)
    struct {
        uint32_t lower;
        uint32_t upper;
    } l;
#else
    struct {
        uint32_t upper;
        uint32_t lower;
    } l;
#endif
    uint64_t ll;
} CPU_DoubleU;

/* CPU memory access without any memory or io remapping */

/*
 * the generic syntax for the memory accesses is:
 *
 * load: ld{type}{sign}{size}{endian}_{access_type}(ptr)
 *
 * store: st{type}{size}{endian}_{access_type}(ptr, val)
 *
 * type is:
 * (empty): integer access
 *   f    : float access
 * 
 * sign is:
 * (empty): for floats or 32 bit size
 *   u    : unsigned
 *   s    : signed
 *
 * size is:
 *   b: 8 bits
 *   w: 16 bits
 *   l: 32 bits
 *   q: 64 bits
 * 
 * endian is:
 * (empty): target cpu endianness or 8 bit access
 *   r    : reversed target cpu endianness (not implemented yet)
 *   be   : big endian (not implemented yet)
 *   le   : little endian (not implemented yet)
 *
 * access_type is:
 *   raw    : host memory access
 *   user   : user mode access using soft MMU
 *   kernel : kernel mode access using soft MMU
 */
static inline int ldub_raw(void *ptr)
{
    return *(uint8_t *)ptr;
}

static inline int ldsb_raw(void *ptr)
{
    return *(int8_t *)ptr;
}

static inline void stb_raw(void *ptr, int v)
{
    *(uint8_t *)ptr = v;
}

/* NOTE: on arm, putting 2 in /proc/sys/debug/alignment so that the
   kernel handles unaligned load/stores may give better results, but
   it is a system wide setting : bad */
#if !defined(TARGET_WORDS_BIGENDIAN) && (defined(WORDS_BIGENDIAN) || defined(WORDS_ALIGNED))

/* conservative code for little endian unaligned accesses */
static inline int lduw_raw(void *ptr)
{
#ifdef __powerpc__
    int val;
    __asm__ __volatile__ ("lhbrx %0,0,%1" : "=r" (val) : "r" (ptr));
    return val;
#else
    uint8_t *p = ptr;
    return p[0] | (p[1] << 8);
#endif
}

static inline int ldsw_raw(void *ptr)
{
#ifdef __powerpc__
    int val;
    __asm__ __volatile__ ("lhbrx %0,0,%1" : "=r" (val) : "r" (ptr));
    return (int16_t)val;
#else
    uint8_t *p = ptr;
    return (int16_t)(p[0] | (p[1] << 8));
#endif
}

static inline int ldl_raw(void *ptr)
{
#ifdef __powerpc__
    int val;
    __asm__ __volatile__ ("lwbrx %0,0,%1" : "=r" (val) : "r" (ptr));
    return val;
#else
    uint8_t *p = ptr;
    return p[0] | (p[1] << 8) | (p[2] << 16) | (p[3] << 24);
#endif
}

static inline uint64_t ldq_raw(void *ptr)
{
    uint8_t *p = ptr;
    uint32_t v1, v2;
    v1 = ldl_raw(p);
    v2 = ldl_raw(p + 4);
    return v1 | ((uint64_t)v2 << 32);
}

static inline void stw_raw(void *ptr, int v)
{
#ifdef __powerpc__
    __asm__ __volatile__ ("sthbrx %1,0,%2" : "=m" (*(uint16_t *)ptr) : "r" (v), "r" (ptr));
#else
    uint8_t *p = ptr;
    p[0] = v;
    p[1] = v >> 8;
#endif
}

static inline void stl_raw(void *ptr, int v)
{
#ifdef __powerpc__
    __asm__ __volatile__ ("stwbrx %1,0,%2" : "=m" (*(uint32_t *)ptr) : "r" (v), "r" (ptr));
#else
    uint8_t *p = ptr;
    p[0] = v;
    p[1] = v >> 8;
    p[2] = v >> 16;
    p[3] = v >> 24;
#endif
}

static inline void stq_raw(void *ptr, uint64_t v)
{
    uint8_t *p = ptr;
    stl_raw(p, (uint32_t)v);
    stl_raw(p + 4, v >> 32);
}

/* float access */

static inline float ldfl_raw(void *ptr)
{
    union {
        float f;
        uint32_t i;
    } u;
    u.i = ldl_raw(ptr);
    return u.f;
}

static inline void stfl_raw(void *ptr, float v)
{
    union {
        float f;
        uint32_t i;
    } u;
    u.f = v;
    stl_raw(ptr, u.i);
}

static inline double ldfq_raw(void *ptr)
{
    CPU_DoubleU u;
    u.l.lower = ldl_raw(ptr);
    u.l.upper = ldl_raw(ptr + 4);
    return u.d;
}

static inline void stfq_raw(void *ptr, double v)
{
    CPU_DoubleU u;
    u.d = v;
    stl_raw(ptr, u.l.lower);
    stl_raw(ptr + 4, u.l.upper);
}

#elif defined(TARGET_WORDS_BIGENDIAN) && (!defined(WORDS_BIGENDIAN) || defined(WORDS_ALIGNED))

static inline int lduw_raw(void *ptr)
{
#if defined(__i386__)
    int val;
    asm volatile ("movzwl %1, %0\n"
                  "xchgb %b0, %h0\n"
                  : "=q" (val)
                  : "m" (*(uint16_t *)ptr));
    return val;
#else
    uint8_t *b = (uint8_t *) ptr;
    return ((b[0] << 8) | b[1]);
#endif
}

static inline int ldsw_raw(void *ptr)
{
#if defined(__i386__)
    int val;
    asm volatile ("movzwl %1, %0\n"
                  "xchgb %b0, %h0\n"
                  : "=q" (val)
                  : "m" (*(uint16_t *)ptr));
    return (int16_t)val;
#else
    uint8_t *b = (uint8_t *) ptr;
    return (int16_t)((b[0] << 8) | b[1]);
#endif
}

static inline int ldl_raw(void *ptr)
{
#if defined(__i386__) || defined(__x86_64__)
    int val;
    asm volatile ("movl %1, %0\n"
                  "bswap %0\n"
                  : "=r" (val)
                  : "m" (*(uint32_t *)ptr));
    return val;
#else
    uint8_t *b = (uint8_t *) ptr;
    return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3];
#endif
}

static inline uint64_t ldq_raw(void *ptr)
{
    uint32_t a,b;
    a = ldl_raw(ptr);
    b = ldl_raw(ptr+4);
    return (((uint64_t)a<<32)|b);
}

static inline void stw_raw(void *ptr, int v)
{
#if defined(__i386__)
    asm volatile ("xchgb %b0, %h0\n"
                  "movw %w0, %1\n"
                  : "=q" (v)
                  : "m" (*(uint16_t *)ptr), "0" (v));
#else
    uint8_t *d = (uint8_t *) ptr;
    d[0] = v >> 8;
    d[1] = v;
#endif
}

static inline void stl_raw(void *ptr, int v)
{
#if defined(__i386__) || defined(__x86_64__)
    asm volatile ("bswap %0\n"
                  "movl %0, %1\n"
                  : "=r" (v)
                  : "m" (*(uint32_t *)ptr), "0" (v));
#else
    uint8_t *d = (uint8_t *) ptr;
    d[0] = v >> 24;
    d[1] = v >> 16;
    d[2] = v >> 8;
    d[3] = v;
#endif
}

static inline void stq_raw(void *ptr, uint64_t v)
{
    stl_raw(ptr, v >> 32);
    stl_raw(ptr + 4, v);
}

/* float access */

static inline float ldfl_raw(void *ptr)
{
    union {
        float f;
        uint32_t i;
    } u;
    u.i = ldl_raw(ptr);
    return u.f;
}

static inline void stfl_raw(void *ptr, float v)
{
    union {
        float f;
        uint32_t i;
    } u;
    u.f = v;
    stl_raw(ptr, u.i);
}

static inline double ldfq_raw(void *ptr)
{
    CPU_DoubleU u;
    u.l.upper = ldl_raw(ptr);
    u.l.lower = ldl_raw(ptr + 4);
    return u.d;
}

static inline void stfq_raw(void *ptr, double v)
{
    CPU_DoubleU u;
    u.d = v;
    stl_raw(ptr, u.l.upper);
    stl_raw(ptr + 4, u.l.lower);
}

#else

static inline int lduw_raw(void *ptr)
{
    return *(uint16_t *)ptr;
}

static inline int ldsw_raw(void *ptr)
{
    return *(int16_t *)ptr;
}

static inline int ldl_raw(void *ptr)
{
    return *(uint32_t *)ptr;
}

static inline uint64_t ldq_raw(void *ptr)
{
    return *(uint64_t *)ptr;
}

static inline void stw_raw(void *ptr, int v)
{
    *(uint16_t *)ptr = v;
}

static inline void stl_raw(void *ptr, int v)
{
    *(uint32_t *)ptr = v;
}

static inline void stq_raw(void *ptr, uint64_t v)
{
    *(uint64_t *)ptr = v;
}

/* float access */

static inline float ldfl_raw(void *ptr)
{
    return *(float *)ptr;
}

static inline double ldfq_raw(void *ptr)
{
    return *(double *)ptr;
}

static inline void stfl_raw(void *ptr, float v)
{
    *(float *)ptr = v;
}

static inline void stfq_raw(void *ptr, double v)
{
    *(double *)ptr = v;
}
#endif

/* MMU memory access macros */

#if defined(CONFIG_USER_ONLY) 

/* if user mode, no other memory access functions */
#define ldub(p) ldub_raw(p)
#define ldsb(p) ldsb_raw(p)
#define lduw(p) lduw_raw(p)
#define ldsw(p) ldsw_raw(p)
#define ldl(p) ldl_raw(p)
#define ldq(p) ldq_raw(p)
#define ldfl(p) ldfl_raw(p)
#define ldfq(p) ldfq_raw(p)
#define stb(p, v) stb_raw(p, v)
#define stw(p, v) stw_raw(p, v)
#define stl(p, v) stl_raw(p, v)
#define stq(p, v) stq_raw(p, v)
#define stfl(p, v) stfl_raw(p, v)
#define stfq(p, v) stfq_raw(p, v)

#define ldub_code(p) ldub_raw(p)
#define ldsb_code(p) ldsb_raw(p)
#define lduw_code(p) lduw_raw(p)
#define ldsw_code(p) ldsw_raw(p)
#define ldl_code(p) ldl_raw(p)

#define ldub_kernel(p) ldub_raw(p)
#define ldsb_kernel(p) ldsb_raw(p)
#define lduw_kernel(p) lduw_raw(p)
#define ldsw_kernel(p) ldsw_raw(p)
#define ldl_kernel(p) ldl_raw(p)
#define ldfl_kernel(p) ldfl_raw(p)
#define ldfq_kernel(p) ldfq_raw(p)
#define stb_kernel(p, v) stb_raw(p, v)
#define stw_kernel(p, v) stw_raw(p, v)
#define stl_kernel(p, v) stl_raw(p, v)
#define stq_kernel(p, v) stq_raw(p, v)
#define stfl_kernel(p, v) stfl_raw(p, v)
#define stfq_kernel(p, vt) stfq_raw(p, v)

#endif /* defined(CONFIG_USER_ONLY) */

/* page related stuff */

#define TARGET_PAGE_SIZE (1 << TARGET_PAGE_BITS)
#define TARGET_PAGE_MASK ~(TARGET_PAGE_SIZE - 1)
#define TARGET_PAGE_ALIGN(addr) (((addr) + TARGET_PAGE_SIZE - 1) & TARGET_PAGE_MASK)

extern unsigned long qemu_real_host_page_size;
extern unsigned long qemu_host_page_bits;
extern unsigned long qemu_host_page_size;
extern unsigned long qemu_host_page_mask;

#define HOST_PAGE_ALIGN(addr) (((addr) + qemu_host_page_size - 1) & qemu_host_page_mask)

/* same as PROT_xxx */
#define PAGE_READ      0x0001
#define PAGE_WRITE     0x0002
#define PAGE_EXEC      0x0004
#define PAGE_BITS      (PAGE_READ | PAGE_WRITE | PAGE_EXEC)
#define PAGE_VALID     0x0008
/* original state of the write flag (used when tracking self-modifying
   code */
#define PAGE_WRITE_ORG 0x0010 

void page_dump(FILE *f);
int page_get_flags(unsigned long address);
void page_set_flags(unsigned long start, unsigned long end, int flags);
void page_unprotect_range(uint8_t *data, unsigned long data_size);

#define SINGLE_CPU_DEFINES
#ifdef SINGLE_CPU_DEFINES

#if defined(TARGET_I386)

#define CPUState CPUX86State
#define cpu_init cpu_x86_init
#define cpu_exec cpu_x86_exec
#define cpu_gen_code cpu_x86_gen_code
#define cpu_signal_handler cpu_x86_signal_handler
#define cpu_dump_state cpu_x86_dump_state

#elif defined(TARGET_ARM)

#define CPUState CPUARMState
#define cpu_init cpu_arm_init
#define cpu_exec cpu_arm_exec
#define cpu_gen_code cpu_arm_gen_code
#define cpu_signal_handler cpu_arm_signal_handler
#define cpu_dump_state cpu_arm_dump_state

#elif defined(TARGET_SPARC)

#define CPUState CPUSPARCState
#define cpu_init cpu_sparc_init
#define cpu_exec cpu_sparc_exec
#define cpu_gen_code cpu_sparc_gen_code
#define cpu_signal_handler cpu_sparc_signal_handler
#define cpu_dump_state cpu_sparc_dump_state

#elif defined(TARGET_PPC)

#define CPUState CPUPPCState
#define cpu_init cpu_ppc_init
#define cpu_exec cpu_ppc_exec
#define cpu_gen_code cpu_ppc_gen_code
#define cpu_signal_handler cpu_ppc_signal_handler
#define cpu_dump_state cpu_ppc_dump_state

#else

#error unsupported target CPU

#endif

#endif /* SINGLE_CPU_DEFINES */

void cpu_abort(CPUState *env, const char *fmt, ...);
extern CPUState *cpu_single_env;
extern int code_copy_enabled;

#define CPU_INTERRUPT_EXIT   0x01 /* wants exit from main loop */
#define CPU_INTERRUPT_HARD   0x02 /* hardware interrupt pending */
#define CPU_INTERRUPT_EXITTB 0x04 /* exit the current TB (use for x86 a20 case) */
#define CPU_INTERRUPT_TIMER  0x08 /* internal timer exception pending */
void cpu_interrupt(CPUState *s, int mask);
void cpu_reset_interrupt(CPUState *env, int mask);

int cpu_breakpoint_insert(CPUState *env, target_ulong pc);
int cpu_breakpoint_remove(CPUState *env, target_ulong pc);
void cpu_single_step(CPUState *env, int enabled);
void cpu_reset(CPUState *s);

/* Return the physical page corresponding to a virtual one. Use it
   only for debugging because no protection checks are done. Return -1
   if no page found. */
target_ulong cpu_get_phys_page_debug(CPUState *env, target_ulong addr);

#define CPU_LOG_TB_OUT_ASM (1 << 0) 
#define CPU_LOG_TB_IN_ASM  (1 << 1)
#define CPU_LOG_TB_OP      (1 << 2)
#define CPU_LOG_TB_OP_OPT  (1 << 3)
#define CPU_LOG_INT        (1 << 4)
#define CPU_LOG_EXEC       (1 << 5)
#define CPU_LOG_PCALL      (1 << 6)
#define CPU_LOG_IOPORT     (1 << 7)
#define CPU_LOG_TB_CPU     (1 << 8)

/* define log items */
typedef struct CPULogItem {
    int mask;
    const char *name;
    const char *help;
} CPULogItem;

extern CPULogItem cpu_log_items[];

void cpu_set_log(int log_flags);
void cpu_set_log_filename(const char *filename);
int cpu_str_to_log_mask(const char *str);

/* IO ports API */

/* NOTE: as these functions may be even used when there is an isa
   brige on non x86 targets, we always defined them */
#ifndef NO_CPU_IO_DEFS
void cpu_outb(CPUState *env, int addr, int val);
void cpu_outw(CPUState *env, int addr, int val);
void cpu_outl(CPUState *env, int addr, int val);
int cpu_inb(CPUState *env, int addr);
int cpu_inw(CPUState *env, int addr);
int cpu_inl(CPUState *env, int addr);
#endif

/* memory API */

extern int phys_ram_size;
extern int phys_ram_fd;
extern uint8_t *phys_ram_base;
extern uint8_t *phys_ram_dirty;

/* physical memory access */
#define IO_MEM_NB_ENTRIES  256
#define TLB_INVALID_MASK   (1 << 3)
#define IO_MEM_SHIFT       4

#define IO_MEM_RAM         (0 << IO_MEM_SHIFT) /* hardcoded offset */
#define IO_MEM_ROM         (1 << IO_MEM_SHIFT) /* hardcoded offset */
#define IO_MEM_UNASSIGNED  (2 << IO_MEM_SHIFT)
#define IO_MEM_CODE        (3 << IO_MEM_SHIFT) /* used internally, never use directly */
#define IO_MEM_NOTDIRTY    (4 << IO_MEM_SHIFT) /* used internally, never use directly */

typedef void CPUWriteMemoryFunc(void *opaque, target_phys_addr_t addr, uint32_t value);
typedef uint32_t CPUReadMemoryFunc(void *opaque, target_phys_addr_t addr);

void cpu_register_physical_memory(target_phys_addr_t start_addr, 
                                  unsigned long size,
                                  unsigned long phys_offset);
int cpu_register_io_memory(int io_index,
                           CPUReadMemoryFunc **mem_read,
                           CPUWriteMemoryFunc **mem_write,
                           void *opaque);

void cpu_physical_memory_rw(target_phys_addr_t addr, uint8_t *buf,
                            int len, int is_write);
static inline void cpu_physical_memory_read(target_phys_addr_t addr, 
                                            uint8_t *buf, int len)
{
    cpu_physical_memory_rw(addr, buf, len, 0);
}
static inline void cpu_physical_memory_write(target_phys_addr_t addr, 
                                             const uint8_t *buf, int len)
{
    cpu_physical_memory_rw(addr, (uint8_t *)buf, len, 1);
}

int cpu_memory_rw_debug(CPUState *env, target_ulong addr, 
                        uint8_t *buf, int len, int is_write);

/* read dirty bit (return 0 or 1) */
static inline int cpu_physical_memory_is_dirty(target_ulong addr)
{
    return phys_ram_dirty[addr >> TARGET_PAGE_BITS];
}

static inline void cpu_physical_memory_set_dirty(target_ulong addr)
{
    phys_ram_dirty[addr >> TARGET_PAGE_BITS] = 1;
}

void cpu_physical_memory_reset_dirty(target_ulong start, target_ulong end);

#endif /* CPU_ALL_H */
