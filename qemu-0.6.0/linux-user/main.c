/*
 *  qemu user main
 * 
 *  Copyright (c) 2003 Fabrice Bellard
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "qemu.h"

#define DEBUG_LOGFILE "/tmp/qemu.log"

#ifdef __APPLE__
#include <crt_externs.h>
# define environ  (*_NSGetEnviron())
#endif

static const char *interp_prefix = CONFIG_QEMU_PREFIX;

#if defined(__i386__) && !defined(CONFIG_STATIC)
/* Force usage of an ELF interpreter even if it is an ELF shared
   object ! */
const char interp[] __attribute__((section(".interp"))) = "/lib/ld-linux.so.2";
#endif

/* for recent libc, we add these dummy symbols which are not declared
   when generating a linked object (bug in ld ?) */
#if (__GLIBC__ > 2 || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 3)) && !defined(CONFIG_STATIC)
long __preinit_array_start[0];
long __preinit_array_end[0];
long __init_array_start[0];
long __init_array_end[0];
long __fini_array_start[0];
long __fini_array_end[0];
#endif

/* XXX: on x86 MAP_GROWSDOWN only works if ESP <= address + 32, so
   we allocate a bigger stack. Need a better solution, for example
   by remapping the process stack directly at the right place */
unsigned long x86_stack_size = 512 * 1024;

void gemu_log(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
}

void cpu_outb(CPUState *env, int addr, int val)
{
    fprintf(stderr, "outb: port=0x%04x, data=%02x\n", addr, val);
}

void cpu_outw(CPUState *env, int addr, int val)
{
    fprintf(stderr, "outw: port=0x%04x, data=%04x\n", addr, val);
}

void cpu_outl(CPUState *env, int addr, int val)
{
    fprintf(stderr, "outl: port=0x%04x, data=%08x\n", addr, val);
}

int cpu_inb(CPUState *env, int addr)
{
    fprintf(stderr, "inb: port=0x%04x\n", addr);
    return 0;
}

int cpu_inw(CPUState *env, int addr)
{
    fprintf(stderr, "inw: port=0x%04x\n", addr);
    return 0;
}

int cpu_inl(CPUState *env, int addr)
{
    fprintf(stderr, "inl: port=0x%04x\n", addr);
    return 0;
}

int cpu_get_pic_interrupt(CPUState *env)
{
    return -1;
}

/* timers for rdtsc */

#if defined(__i386__)

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

static uint64_t emu_time;

int64_t cpu_get_real_ticks(void)
{
    return emu_time++;
}

#endif

#ifdef TARGET_I386
/***********************************************************/
/* CPUX86 core interface */

uint64_t cpu_get_tsc(CPUX86State *env)
{
    return cpu_get_real_ticks();
}

static void write_dt(void *ptr, unsigned long addr, unsigned long limit, 
                     int flags)
{
    unsigned int e1, e2;
    e1 = (addr << 16) | (limit & 0xffff);
    e2 = ((addr >> 16) & 0xff) | (addr & 0xff000000) | (limit & 0x000f0000);
    e2 |= flags;
    stl((uint8_t *)ptr, e1);
    stl((uint8_t *)ptr + 4, e2);
}

static void set_gate(void *ptr, unsigned int type, unsigned int dpl, 
                     unsigned long addr, unsigned int sel)
{
    unsigned int e1, e2;
    e1 = (addr & 0xffff) | (sel << 16);
    e2 = (addr & 0xffff0000) | 0x8000 | (dpl << 13) | (type << 8);
    stl((uint8_t *)ptr, e1);
    stl((uint8_t *)ptr + 4, e2);
}

uint64_t gdt_table[6];
uint64_t idt_table[256];

/* only dpl matters as we do only user space emulation */
static void set_idt(int n, unsigned int dpl)
{
    set_gate(idt_table + n, 0, dpl, 0, 0);
}

void cpu_loop(CPUX86State *env)
{
    int trapnr;
    uint8_t *pc;
    target_siginfo_t info;

    for(;;) {
        trapnr = cpu_x86_exec(env);
        switch(trapnr) {
        case 0x80:
            /* linux syscall */
            env->regs[R_EAX] = do_syscall(env, 
                                          env->regs[R_EAX], 
                                          env->regs[R_EBX],
                                          env->regs[R_ECX],
                                          env->regs[R_EDX],
                                          env->regs[R_ESI],
                                          env->regs[R_EDI],
                                          env->regs[R_EBP]);
            break;
        case EXCP0B_NOSEG:
        case EXCP0C_STACK:
            info.si_signo = SIGBUS;
            info.si_errno = 0;
            info.si_code = TARGET_SI_KERNEL;
            info._sifields._sigfault._addr = 0;
            queue_signal(info.si_signo, &info);
            break;
        case EXCP0D_GPF:
            if (env->eflags & VM_MASK) {
                handle_vm86_fault(env);
            } else {
                info.si_signo = SIGSEGV;
                info.si_errno = 0;
                info.si_code = TARGET_SI_KERNEL;
                info._sifields._sigfault._addr = 0;
                queue_signal(info.si_signo, &info);
            }
            break;
        case EXCP0E_PAGE:
            info.si_signo = SIGSEGV;
            info.si_errno = 0;
            if (!(env->error_code & 1))
                info.si_code = TARGET_SEGV_MAPERR;
            else
                info.si_code = TARGET_SEGV_ACCERR;
            info._sifields._sigfault._addr = env->cr[2];
            queue_signal(info.si_signo, &info);
            break;
        case EXCP00_DIVZ:
            if (env->eflags & VM_MASK) {
                handle_vm86_trap(env, trapnr);
            } else {
                /* division by zero */
                info.si_signo = SIGFPE;
                info.si_errno = 0;
                info.si_code = TARGET_FPE_INTDIV;
                info._sifields._sigfault._addr = env->eip;
                queue_signal(info.si_signo, &info);
            }
            break;
        case EXCP01_SSTP:
        case EXCP03_INT3:
            if (env->eflags & VM_MASK) {
                handle_vm86_trap(env, trapnr);
            } else {
                info.si_signo = SIGTRAP;
                info.si_errno = 0;
                if (trapnr == EXCP01_SSTP) {
                    info.si_code = TARGET_TRAP_BRKPT;
                    info._sifields._sigfault._addr = env->eip;
                } else {
                    info.si_code = TARGET_SI_KERNEL;
                    info._sifields._sigfault._addr = 0;
                }
                queue_signal(info.si_signo, &info);
            }
            break;
        case EXCP04_INTO:
        case EXCP05_BOUND:
            if (env->eflags & VM_MASK) {
                handle_vm86_trap(env, trapnr);
            } else {
                info.si_signo = SIGSEGV;
                info.si_errno = 0;
                info.si_code = TARGET_SI_KERNEL;
                info._sifields._sigfault._addr = 0;
                queue_signal(info.si_signo, &info);
            }
            break;
        case EXCP06_ILLOP:
            info.si_signo = SIGILL;
            info.si_errno = 0;
            info.si_code = TARGET_ILL_ILLOPN;
            info._sifields._sigfault._addr = env->eip;
            queue_signal(info.si_signo, &info);
            break;
        case EXCP_INTERRUPT:
            /* just indicate that signals should be handled asap */
            break;
        default:
            pc = env->segs[R_CS].base + env->eip;
            fprintf(stderr, "qemu: 0x%08lx: unhandled CPU exception 0x%x - aborting\n", 
                    (long)pc, trapnr);
            abort();
        }
        process_pending_signals(env);
    }
}
#endif

#ifdef TARGET_ARM

/* XXX: find a better solution */
extern void tb_invalidate_page_range(target_ulong start, target_ulong end);

static void arm_cache_flush(target_ulong start, target_ulong last)
{
    target_ulong addr, last1;

    if (last < start)
        return;
    addr = start;
    for(;;) {
        last1 = ((addr + TARGET_PAGE_SIZE) & TARGET_PAGE_MASK) - 1;
        if (last1 > last)
            last1 = last;
        tb_invalidate_page_range(addr, last1 + 1);
        if (last1 == last)
            break;
        addr = last1 + 1;
    }
}

void cpu_loop(CPUARMState *env)
{
    int trapnr;
    unsigned int n, insn;
    target_siginfo_t info;
    
    for(;;) {
        trapnr = cpu_arm_exec(env);
        switch(trapnr) {
        case EXCP_UDEF:
            {
                TaskState *ts = env->opaque;
                uint32_t opcode;

                /* we handle the FPU emulation here, as Linux */
                /* we get the opcode */
                opcode = ldl_raw((uint8_t *)env->regs[15]);
                
                if (EmulateAll(opcode, &ts->fpa, env->regs) == 0) {
                    info.si_signo = SIGILL;
                    info.si_errno = 0;
                    info.si_code = TARGET_ILL_ILLOPN;
                    info._sifields._sigfault._addr = env->regs[15];
                    queue_signal(info.si_signo, &info);
                } else {
                    /* increment PC */
                    env->regs[15] += 4;
                }
            }
            break;
        case EXCP_SWI:
            {
                /* system call */
                insn = ldl((void *)(env->regs[15] - 4));
                n = insn & 0xffffff;
                if (n == ARM_NR_cacheflush) {
                    arm_cache_flush(env->regs[0], env->regs[1]);
                } else if (n >= ARM_SYSCALL_BASE) {
                    /* linux syscall */
                    n -= ARM_SYSCALL_BASE;
                    env->regs[0] = do_syscall(env, 
                                              n, 
                                              env->regs[0],
                                              env->regs[1],
                                              env->regs[2],
                                              env->regs[3],
                                              env->regs[4],
                                              0);
                } else {
                    goto error;
                }
            }
            break;
        case EXCP_INTERRUPT:
            /* just indicate that signals should be handled asap */
            break;
        default:
        error:
            fprintf(stderr, "qemu: unhandled CPU exception 0x%x - aborting\n", 
                    trapnr);
            cpu_arm_dump_state(env, stderr, 0);
            abort();
        }
        process_pending_signals(env);
    }
}

#endif

#ifdef TARGET_SPARC

//#define DEBUG_WIN

/* WARNING: dealing with register windows _is_ complicated */
static inline int get_reg_index(CPUSPARCState *env, int cwp, int index)
{
    index = (index + cwp * 16) & (16 * NWINDOWS - 1);
    /* wrap handling : if cwp is on the last window, then we use the
       registers 'after' the end */
    if (index < 8 && env->cwp == (NWINDOWS - 1))
        index += (16 * NWINDOWS);
    return index;
}

static inline void save_window_offset(CPUSPARCState *env, int offset)
{
    unsigned int new_wim, i, cwp1;
    uint32_t *sp_ptr;
    
    new_wim = ((env->wim >> 1) | (env->wim << (NWINDOWS - 1))) &
        ((1LL << NWINDOWS) - 1);
    /* save the window */
    cwp1 = (env->cwp + offset) & (NWINDOWS - 1);
    sp_ptr = (uint32_t *)(env->regbase[get_reg_index(env, cwp1, 6)]);
#if defined(DEBUG_WIN)
    printf("win_overflow: sp_ptr=0x%x save_cwp=%d\n", 
           (int)sp_ptr, cwp1);
#endif
    for(i = 0; i < 16; i++)
        stl_raw(sp_ptr + i, env->regbase[get_reg_index(env, cwp1, 8 + i)]);
    env->wim = new_wim;
}

static void save_window(CPUSPARCState *env)
{
    save_window_offset(env, 2);
}

static void restore_window(CPUSPARCState *env)
{
    unsigned int new_wim, i, cwp1;
    uint32_t *sp_ptr;
    
    new_wim = ((env->wim << 1) | (env->wim >> (NWINDOWS - 1))) &
        ((1LL << NWINDOWS) - 1);
    
    /* restore the invalid window */
    cwp1 = (env->cwp + 1) & (NWINDOWS - 1);
    sp_ptr = (uint32_t *)(env->regbase[get_reg_index(env, cwp1, 6)]);
#if defined(DEBUG_WIN)
    printf("win_underflow: sp_ptr=0x%x load_cwp=%d\n", 
           (int)sp_ptr, cwp1);
#endif
    for(i = 0; i < 16; i++)
        env->regbase[get_reg_index(env, cwp1, 8 + i)] = ldl_raw(sp_ptr + i);
    env->wim = new_wim;
}

static void flush_windows(CPUSPARCState *env)
{
    int offset, cwp1;
#if defined(DEBUG_WIN)
    printf("flush_windows:\n");
#endif
    offset = 2;
    for(;;) {
        /* if restore would invoke restore_window(), then we can stop */
        cwp1 = (env->cwp + 1) & (NWINDOWS - 1);
        if (env->wim & (1 << cwp1))
            break;
#if defined(DEBUG_WIN)
        printf("offset=%d: ", offset);
#endif
        save_window_offset(env, offset);
        offset++;
    }
}

void cpu_loop (CPUSPARCState *env)
{
    int trapnr, ret;
    
    while (1) {
        trapnr = cpu_sparc_exec (env);
        
        switch (trapnr) {
        case 0x88: 
        case 0x90:
            ret = do_syscall (env, env->gregs[1],
                              env->regwptr[0], env->regwptr[1], 
                              env->regwptr[2], env->regwptr[3], 
                              env->regwptr[4], env->regwptr[5]);
            if ((unsigned int)ret >= (unsigned int)(-515)) {
                env->psr |= PSR_CARRY;
                ret = -ret;
            } else {
                env->psr &= ~PSR_CARRY;
            }
            env->regwptr[0] = ret;
            /* next instruction */
            env->pc = env->npc;
            env->npc = env->npc + 4;
            break;
        case 0x83: /* flush windows */
            //            flush_windows(env);
            /* next instruction */
            env->pc = env->npc;
            env->npc = env->npc + 4;
            break;
        case TT_WIN_OVF: /* window overflow */
            save_window(env);
            break;
        case TT_WIN_UNF: /* window underflow */
            restore_window(env);
            break;
        default:
            printf ("Unhandled trap: 0x%x\n", trapnr);
            cpu_sparc_dump_state(env, stderr, 0);
            exit (1);
        }
        process_pending_signals (env);
    }
}

#endif

#ifdef TARGET_PPC

static inline uint64_t cpu_ppc_get_tb (CPUState *env)
{
    /* TO FIX */
    return 0;
}
  
uint32_t cpu_ppc_load_tbl (CPUState *env)
{
    return cpu_ppc_get_tb(env) & 0xFFFFFFFF;
}
  
uint32_t cpu_ppc_load_tbu (CPUState *env)
{
    return cpu_ppc_get_tb(env) >> 32;
}
  
static void cpu_ppc_store_tb (CPUState *env, uint64_t value)
{
    /* TO FIX */
}

void cpu_ppc_store_tbu (CPUState *env, uint32_t value)
{
    cpu_ppc_store_tb(env, ((uint64_t)value << 32) | cpu_ppc_load_tbl(env));
}
 
void cpu_ppc_store_tbl (CPUState *env, uint32_t value)
{
    cpu_ppc_store_tb(env, ((uint64_t)cpu_ppc_load_tbl(env) << 32) | value);
}
  
uint32_t cpu_ppc_load_decr (CPUState *env)
{
    /* TO FIX */
    return -1;
}
 
void cpu_ppc_store_decr (CPUState *env, uint32_t value)
{
    /* TO FIX */
}
 
void cpu_loop(CPUPPCState *env)
{
    target_siginfo_t info;
    int trapnr;
    uint32_t ret;
    
    for(;;) {
        trapnr = cpu_ppc_exec(env);
        if (trapnr != EXCP_SYSCALL_USER && trapnr != EXCP_BRANCH &&
            trapnr != EXCP_TRACE) {
            if (loglevel > 0) {
                cpu_ppc_dump_state(env, logfile, 0);
            }
        }
        switch(trapnr) {
        case EXCP_NONE:
            break;
        case EXCP_SYSCALL_USER:
            /* system call */
            /* WARNING:
             * PPC ABI uses overflow flag in cr0 to signal an error
             * in syscalls.
             */
#if 0
            printf("syscall %d 0x%08x 0x%08x 0x%08x 0x%08x\n", env->gpr[0],
                   env->gpr[3], env->gpr[4], env->gpr[5], env->gpr[6]);
#endif
            env->crf[0] &= ~0x1;
            ret = do_syscall(env, env->gpr[0], env->gpr[3], env->gpr[4],
                             env->gpr[5], env->gpr[6], env->gpr[7],
                             env->gpr[8]);
            if (ret > (uint32_t)(-515)) {
                env->crf[0] |= 0x1;
                ret = -ret;
            }
            env->gpr[3] = ret;
#if 0
            printf("syscall returned 0x%08x (%d)\n", ret, ret);
#endif
            break;
        case EXCP_RESET:
            /* Should not happen ! */
            fprintf(stderr, "RESET asked... Stop emulation\n");
            if (loglevel)
                fprintf(logfile, "RESET asked... Stop emulation\n");
            abort();
        case EXCP_MACHINE_CHECK:
            fprintf(stderr, "Machine check exeption...  Stop emulation\n");
            if (loglevel)
                fprintf(logfile, "RESET asked... Stop emulation\n");
            info.si_signo = TARGET_SIGBUS;
            info.si_errno = 0;
            info.si_code = TARGET_BUS_OBJERR;
            info._sifields._sigfault._addr = env->nip - 4;
            queue_signal(info.si_signo, &info);
        case EXCP_DSI:
            fprintf(stderr, "Invalid data memory access: 0x%08x\n", env->spr[DAR]);
            if (loglevel) {
                fprintf(logfile, "Invalid data memory access: 0x%08x\n",
                        env->spr[DAR]);
            }
            switch (env->error_code & 0xF) {
            case EXCP_DSI_TRANSLATE:
                info.si_signo = TARGET_SIGSEGV;
                info.si_errno = 0;
                info.si_code = TARGET_SEGV_MAPERR;
                break;
            case EXCP_DSI_NOTSUP:
            case EXCP_DSI_EXTERNAL:
                info.si_signo = TARGET_SIGILL;
                info.si_errno = 0;
                info.si_code = TARGET_ILL_ILLADR;
                break;
            case EXCP_DSI_PROT: 
                info.si_signo = TARGET_SIGSEGV;
                info.si_errno = 0;
                info.si_code = TARGET_SEGV_ACCERR;
                break;
            case EXCP_DSI_DABR:
                info.si_signo = TARGET_SIGTRAP;
                info.si_errno = 0;
                info.si_code = TARGET_TRAP_BRKPT;
                break;
            default:
                /* Let's send a regular segfault... */
                fprintf(stderr, "Invalid segfault errno (%02x)\n",
                        env->error_code);
                if (loglevel) {
                    fprintf(logfile, "Invalid segfault errno (%02x)\n",
                            env->error_code);
                }
                info.si_signo = TARGET_SIGSEGV;
                info.si_errno = 0;
                info.si_code = TARGET_SEGV_MAPERR;
                break;
            }
            info._sifields._sigfault._addr = env->nip;
            queue_signal(info.si_signo, &info);
            break;
        case EXCP_ISI:
            fprintf(stderr, "Invalid instruction fetch\n");
            if (loglevel)
                fprintf(logfile, "Invalid instruction fetch\n");
            switch (env->error_code) {
            case EXCP_ISI_TRANSLATE:
                info.si_signo = TARGET_SIGSEGV;
            info.si_errno = 0;
                info.si_code = TARGET_SEGV_MAPERR;
                break;
            case EXCP_ISI_GUARD:
                info.si_signo = TARGET_SIGILL;
                info.si_errno = 0;
                info.si_code = TARGET_ILL_ILLADR;
                break;
            case EXCP_ISI_NOEXEC:
            case EXCP_ISI_PROT:
                info.si_signo = TARGET_SIGSEGV;
                info.si_errno = 0;
                info.si_code = TARGET_SEGV_ACCERR;
                break;
            default:
                /* Let's send a regular segfault... */
                fprintf(stderr, "Invalid segfault errno (%02x)\n",
                        env->error_code);
                if (loglevel) {
                    fprintf(logfile, "Invalid segfault errno (%02x)\n",
                            env->error_code);
                }
                info.si_signo = TARGET_SIGSEGV;
                info.si_errno = 0;
                info.si_code = TARGET_SEGV_MAPERR;
                break;
            }
            info._sifields._sigfault._addr = env->nip - 4;
            queue_signal(info.si_signo, &info);
            break;
        case EXCP_EXTERNAL:
            /* Should not happen ! */
            fprintf(stderr, "External interruption... Stop emulation\n");
            if (loglevel)
                fprintf(logfile, "External interruption... Stop emulation\n");
            abort();
        case EXCP_ALIGN:
            fprintf(stderr, "Invalid unaligned memory access\n");
            if (loglevel)
                fprintf(logfile, "Invalid unaligned memory access\n");
            info.si_signo = TARGET_SIGBUS;
            info.si_errno = 0;
            info.si_code = TARGET_BUS_ADRALN;
            info._sifields._sigfault._addr = env->nip - 4;
            queue_signal(info.si_signo, &info);
            break;
        case EXCP_PROGRAM:
            switch (env->error_code & ~0xF) {
            case EXCP_FP:
            fprintf(stderr, "Program exception\n");
                if (loglevel)
                    fprintf(logfile, "Program exception\n");
                /* Set FX */
                env->fpscr[7] |= 0x8;
                /* Finally, update FEX */
                if ((((env->fpscr[7] & 0x3) << 3) | (env->fpscr[6] >> 1)) &
                    ((env->fpscr[1] << 1) | (env->fpscr[0] >> 3)))
                    env->fpscr[7] |= 0x4;
                info.si_signo = TARGET_SIGFPE;
                info.si_errno = 0;
                switch (env->error_code & 0xF) {
                case EXCP_FP_OX:
                    info.si_code = TARGET_FPE_FLTOVF;
                    break;
                case EXCP_FP_UX:
                    info.si_code = TARGET_FPE_FLTUND;
                    break;
                case EXCP_FP_ZX:
                case EXCP_FP_VXZDZ:
                    info.si_code = TARGET_FPE_FLTDIV;
                    break;
                case EXCP_FP_XX:
                    info.si_code = TARGET_FPE_FLTRES;
                    break;
                case EXCP_FP_VXSOFT:
                    info.si_code = TARGET_FPE_FLTINV;
                    break;
                case EXCP_FP_VXNAN:
                case EXCP_FP_VXISI:
                case EXCP_FP_VXIDI:
                case EXCP_FP_VXIMZ:
                case EXCP_FP_VXVC:
                case EXCP_FP_VXSQRT:
                case EXCP_FP_VXCVI:
                    info.si_code = TARGET_FPE_FLTSUB;
                    break;
                default:
                    fprintf(stderr, "Unknown floating point exception "
                            "(%02x)\n", env->error_code);
                    if (loglevel) {
                        fprintf(logfile, "Unknown floating point exception "
                                "(%02x)\n", env->error_code & 0xF);
                    }
                }
            break;
        case EXCP_INVAL:
                fprintf(stderr, "Invalid instruction\n");
                if (loglevel)
                    fprintf(logfile, "Invalid instruction\n");
                info.si_signo = TARGET_SIGILL;
                info.si_errno = 0;
                switch (env->error_code & 0xF) {
                case EXCP_INVAL_INVAL:
                    info.si_code = TARGET_ILL_ILLOPC;
                    break;
                case EXCP_INVAL_LSWX:
            info.si_code = TARGET_ILL_ILLOPN;
                    break;
                case EXCP_INVAL_SPR:
                    info.si_code = TARGET_ILL_PRVREG;
                    break;
                case EXCP_INVAL_FP:
                    info.si_code = TARGET_ILL_COPROC;
                    break;
                default:
                    fprintf(stderr, "Unknown invalid operation (%02x)\n",
                            env->error_code & 0xF);
                    if (loglevel) {
                        fprintf(logfile, "Unknown invalid operation (%02x)\n",
                                env->error_code & 0xF);
                    }
                    info.si_code = TARGET_ILL_ILLADR;
                    break;
                }
                break;
            case EXCP_PRIV:
                fprintf(stderr, "Privilege violation\n");
                if (loglevel)
                    fprintf(logfile, "Privilege violation\n");
                info.si_signo = TARGET_SIGILL;
                info.si_errno = 0;
                switch (env->error_code & 0xF) {
                case EXCP_PRIV_OPC:
                    info.si_code = TARGET_ILL_PRVOPC;
                    break;
                case EXCP_PRIV_REG:
                    info.si_code = TARGET_ILL_PRVREG;
                break;
                default:
                    fprintf(stderr, "Unknown privilege violation (%02x)\n",
                            env->error_code & 0xF);
                    info.si_code = TARGET_ILL_PRVOPC;
                    break;
                }
                break;
            case EXCP_TRAP:
                fprintf(stderr, "Tried to call a TRAP\n");
                if (loglevel)
                    fprintf(logfile, "Tried to call a TRAP\n");
                abort();
            default:
                /* Should not happen ! */
                fprintf(stderr, "Unknown program exception (%02x)\n",
                        env->error_code);
                if (loglevel) {
                    fprintf(logfile, "Unknwon program exception (%02x)\n",
                            env->error_code);
                }
                abort();
            }
            info._sifields._sigfault._addr = env->nip - 4;
            queue_signal(info.si_signo, &info);
            break;
        case EXCP_NO_FP:
            fprintf(stderr, "No floating point allowed\n");
            if (loglevel)
                fprintf(logfile, "No floating point allowed\n");
            info.si_signo = TARGET_SIGILL;
            info.si_errno = 0;
            info.si_code = TARGET_ILL_COPROC;
            info._sifields._sigfault._addr = env->nip - 4;
            queue_signal(info.si_signo, &info);
            break;
        case EXCP_DECR:
            /* Should not happen ! */
            fprintf(stderr, "Decrementer exception\n");
            if (loglevel)
                fprintf(logfile, "Decrementer exception\n");
            abort();
        case EXCP_RESA: /* Implementation specific          */
            /* Should not happen ! */
            fprintf(stderr, "RESA exception should never happen !\n");
            if (loglevel)
                fprintf(logfile, "RESA exception should never happen !\n");
            abort();
        case EXCP_RESB: /* Implementation specific          */
            /* Should not happen ! */
            fprintf(stderr, "RESB exception should never happen !\n");
            if (loglevel)
                fprintf(logfile, "RESB exception should never happen !\n");
            abort();
        case EXCP_TRACE:
            /* Do nothing: we use this to trace execution */
            break;
        case EXCP_FP_ASSIST:
            /* Should not happen ! */
            fprintf(stderr, "Floating point assist exception\n");
            if (loglevel)
                fprintf(logfile, "Floating point assist exception\n");
            abort();
        case EXCP_MTMSR:
            /* We reloaded the msr, just go on */
            if (msr_pr == 0) {
                fprintf(stderr, "Tried to go into supervisor mode !\n");
                if (loglevel)
                    fprintf(logfile, "Tried to go into supervisor mode !\n");
                abort();
        }
            break;
        case EXCP_BRANCH:
            /* We stopped because of a jump... */
            break;
        case EXCP_RFI:
            /* Should not occur: we always are in user mode */
            fprintf(stderr, "Return from interrupt ?\n");
            if (loglevel)
                fprintf(logfile, "Return from interrupt ?\n");
            abort();
        case EXCP_INTERRUPT:
            /* Don't know why this should ever happen... */
            break;
	case EXCP_DEBUG:
	    break;
        default:
            fprintf(stderr, "qemu: unhandled CPU exception 0x%x - aborting\n", 
                    trapnr);
            if (loglevel) {
                fprintf(logfile, "qemu: unhandled CPU exception 0x%02x - "
                        "0x%02x - aborting\n", trapnr, env->error_code);
            }
            abort();
        }
        process_pending_signals(env);
    }
}
#endif

void usage(void)
{
    printf("qemu-" TARGET_ARCH " version " QEMU_VERSION ", Copyright (c) 2003-2004 Fabrice Bellard\n"
           "usage: qemu-" TARGET_ARCH " [-h] [-d opts] [-L path] [-s size] program [arguments...]\n"
           "Linux CPU emulator (compiled for %s emulation)\n"
           "\n"
           "-h           print this help\n"
           "-L path      set the elf interpreter prefix (default=%s)\n"
           "-s size      set the stack size in bytes (default=%ld)\n"
           "\n"
           "debug options:\n"
#ifdef USE_CODE_COPY
           "-no-code-copy   disable code copy acceleration\n"
#endif
           "-d options   activate log (logfile=%s)\n"
           "-p pagesize  set the host page size to 'pagesize'\n",
           TARGET_ARCH,
           interp_prefix, 
           x86_stack_size,
           DEBUG_LOGFILE);
    _exit(1);
}

/* XXX: currently only used for async signals (see signal.c) */
CPUState *global_env;
/* used only if single thread */
CPUState *cpu_single_env = NULL;

/* used to free thread contexts */
TaskState *first_task_state;

int main(int argc, char **argv)
{
    const char *filename;
    struct target_pt_regs regs1, *regs = &regs1;
    struct image_info info1, *info = &info1;
    TaskState ts1, *ts = &ts1;
    CPUState *env;
    int optind;
    const char *r;
    
    if (argc <= 1)
        usage();

    /* init debug */
    cpu_set_log_filename(DEBUG_LOGFILE);

    optind = 1;
    for(;;) {
        if (optind >= argc)
            break;
        r = argv[optind];
        if (r[0] != '-')
            break;
        optind++;
        r++;
        if (!strcmp(r, "-")) {
            break;
        } else if (!strcmp(r, "d")) {
            int mask;
            CPULogItem *item;

	    if (optind >= argc)
		break;
            
	    r = argv[optind++];
            mask = cpu_str_to_log_mask(r);
            if (!mask) {
                printf("Log items (comma separated):\n");
                for(item = cpu_log_items; item->mask != 0; item++) {
                    printf("%-10s %s\n", item->name, item->help);
                }
                exit(1);
            }
            cpu_set_log(mask);
        } else if (!strcmp(r, "s")) {
            r = argv[optind++];
            x86_stack_size = strtol(r, (char **)&r, 0);
            if (x86_stack_size <= 0)
                usage();
            if (*r == 'M')
                x86_stack_size *= 1024 * 1024;
            else if (*r == 'k' || *r == 'K')
                x86_stack_size *= 1024;
        } else if (!strcmp(r, "L")) {
            interp_prefix = argv[optind++];
        } else if (!strcmp(r, "p")) {
            qemu_host_page_size = atoi(argv[optind++]);
            if (qemu_host_page_size == 0 ||
                (qemu_host_page_size & (qemu_host_page_size - 1)) != 0) {
                fprintf(stderr, "page size must be a power of two\n");
                exit(1);
            }
        } else 
#ifdef USE_CODE_COPY
        if (!strcmp(r, "no-code-copy")) {
            code_copy_enabled = 0;
        } else 
#endif
        {
            usage();
        }
    }
    if (optind >= argc)
        usage();
    filename = argv[optind];

    /* Zero out regs */
    memset(regs, 0, sizeof(struct target_pt_regs));

    /* Zero out image_info */
    memset(info, 0, sizeof(struct image_info));

    /* Scan interp_prefix dir for replacement files. */
    init_paths(interp_prefix);

    /* NOTE: we need to init the CPU at this stage to get
       qemu_host_page_size */
    env = cpu_init();
    
    if (elf_exec(filename, argv+optind, environ, regs, info) != 0) {
	printf("Error loading %s\n", filename);
	_exit(1);
    }
    
    if (loglevel) {
        page_dump(logfile);
    
        fprintf(logfile, "start_brk   0x%08lx\n" , info->start_brk);
        fprintf(logfile, "end_code    0x%08lx\n" , info->end_code);
        fprintf(logfile, "start_code  0x%08lx\n" , info->start_code);
        fprintf(logfile, "end_data    0x%08lx\n" , info->end_data);
        fprintf(logfile, "start_stack 0x%08lx\n" , info->start_stack);
        fprintf(logfile, "brk         0x%08lx\n" , info->brk);
        fprintf(logfile, "entry       0x%08lx\n" , info->entry);
    }

    target_set_brk((char *)info->brk);
    syscall_init();
    signal_init();

    global_env = env;

    /* build Task State */
    memset(ts, 0, sizeof(TaskState));
    env->opaque = ts;
    ts->used = 1;
    env->user_mode_only = 1;
    
#if defined(TARGET_I386)
    cpu_x86_set_cpl(env, 3);

    env->cr[0] = CR0_PG_MASK | CR0_WP_MASK | CR0_PE_MASK;
    env->hflags |= HF_PE_MASK;

    /* flags setup : we activate the IRQs by default as in user mode */
    env->eflags |= IF_MASK;
    
    /* linux register setup */
    env->regs[R_EAX] = regs->eax;
    env->regs[R_EBX] = regs->ebx;
    env->regs[R_ECX] = regs->ecx;
    env->regs[R_EDX] = regs->edx;
    env->regs[R_ESI] = regs->esi;
    env->regs[R_EDI] = regs->edi;
    env->regs[R_EBP] = regs->ebp;
    env->regs[R_ESP] = regs->esp;
    env->eip = regs->eip;

    /* linux interrupt setup */
    env->idt.base = (void *)idt_table;
    env->idt.limit = sizeof(idt_table) - 1;
    set_idt(0, 0);
    set_idt(1, 0);
    set_idt(2, 0);
    set_idt(3, 3);
    set_idt(4, 3);
    set_idt(5, 3);
    set_idt(6, 0);
    set_idt(7, 0);
    set_idt(8, 0);
    set_idt(9, 0);
    set_idt(10, 0);
    set_idt(11, 0);
    set_idt(12, 0);
    set_idt(13, 0);
    set_idt(14, 0);
    set_idt(15, 0);
    set_idt(16, 0);
    set_idt(17, 0);
    set_idt(18, 0);
    set_idt(19, 0);
    set_idt(0x80, 3);

    /* linux segment setup */
    env->gdt.base = (void *)gdt_table;
    env->gdt.limit = sizeof(gdt_table) - 1;
    write_dt(&gdt_table[__USER_CS >> 3], 0, 0xfffff,
             DESC_G_MASK | DESC_B_MASK | DESC_P_MASK | DESC_S_MASK | 
             (3 << DESC_DPL_SHIFT) | (0xa << DESC_TYPE_SHIFT));
    write_dt(&gdt_table[__USER_DS >> 3], 0, 0xfffff,
             DESC_G_MASK | DESC_B_MASK | DESC_P_MASK | DESC_S_MASK | 
             (3 << DESC_DPL_SHIFT) | (0x2 << DESC_TYPE_SHIFT));
    cpu_x86_load_seg(env, R_CS, __USER_CS);
    cpu_x86_load_seg(env, R_DS, __USER_DS);
    cpu_x86_load_seg(env, R_ES, __USER_DS);
    cpu_x86_load_seg(env, R_SS, __USER_DS);
    cpu_x86_load_seg(env, R_FS, __USER_DS);
    cpu_x86_load_seg(env, R_GS, __USER_DS);

#elif defined(TARGET_ARM)
    {
        int i;
        for(i = 0; i < 16; i++) {
            env->regs[i] = regs->uregs[i];
        }
        env->cpsr = regs->uregs[16];
    }
#elif defined(TARGET_SPARC)
    {
        int i;
	env->pc = regs->pc;
	env->npc = regs->npc;
        env->y = regs->y;
        for(i = 0; i < 8; i++)
            env->gregs[i] = regs->u_regs[i];
        for(i = 0; i < 8; i++)
            env->regwptr[i] = regs->u_regs[i + 8];
    }
#elif defined(TARGET_PPC)
    {
        int i;
        for (i = 0; i < 32; i++) {
            if (i != 12 && i != 6)
                env->msr[i] = (regs->msr >> i) & 1;
        }
        env->nip = regs->nip;
        for(i = 0; i < 32; i++) {
            env->gpr[i] = regs->gpr[i];
        }
    }
#else
#error unsupported target CPU
#endif

    cpu_loop(env);
    /* never exits */
    return 0;
}
