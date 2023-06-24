/*
 *  i386 helpers
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
#include "exec.h"

//#define DEBUG_PCALL

#if 0
#define raise_exception_err(a, b)\
do {\
    fprintf(logfile, "raise_exception line=%d\n", __LINE__);\
    (raise_exception_err)(a, b);\
} while (0)
#endif

const uint8_t parity_table[256] = {
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    CC_P, 0, 0, CC_P, 0, CC_P, CC_P, 0,
    0, CC_P, CC_P, 0, CC_P, 0, 0, CC_P,
};

/* modulo 17 table */
const uint8_t rclw_table[32] = {
    0, 1, 2, 3, 4, 5, 6, 7, 
    8, 9,10,11,12,13,14,15,
   16, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 9,10,11,12,13,14,
};

/* modulo 9 table */
const uint8_t rclb_table[32] = {
    0, 1, 2, 3, 4, 5, 6, 7, 
    8, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 0, 1, 2, 3, 4, 5, 
    6, 7, 8, 0, 1, 2, 3, 4,
};

const CPU86_LDouble f15rk[7] =
{
    0.00000000000000000000L,
    1.00000000000000000000L,
    3.14159265358979323851L,  /*pi*/
    0.30102999566398119523L,  /*lg2*/
    0.69314718055994530943L,  /*ln2*/
    1.44269504088896340739L,  /*l2e*/
    3.32192809488736234781L,  /*l2t*/
};
    
/* thread support */

spinlock_t global_cpu_lock = SPIN_LOCK_UNLOCKED;

void cpu_lock(void)
{
    spin_lock(&global_cpu_lock);
}

void cpu_unlock(void)
{
    spin_unlock(&global_cpu_lock);
}

void cpu_loop_exit(void)
{
    /* NOTE: the register at this point must be saved by hand because
       longjmp restore them */
#ifdef reg_EAX
    env->regs[R_EAX] = EAX;
#endif
#ifdef reg_ECX
    env->regs[R_ECX] = ECX;
#endif
#ifdef reg_EDX
    env->regs[R_EDX] = EDX;
#endif
#ifdef reg_EBX
    env->regs[R_EBX] = EBX;
#endif
#ifdef reg_ESP
    env->regs[R_ESP] = ESP;
#endif
#ifdef reg_EBP
    env->regs[R_EBP] = EBP;
#endif
#ifdef reg_ESI
    env->regs[R_ESI] = ESI;
#endif
#ifdef reg_EDI
    env->regs[R_EDI] = EDI;
#endif
    longjmp(env->jmp_env, 1);
}

/* return non zero if error */
static inline int load_segment(uint32_t *e1_ptr, uint32_t *e2_ptr,
                               int selector)
{
    SegmentCache *dt;
    int index;
    uint8_t *ptr;

    if (selector & 0x4)
        dt = &env->ldt;
    else
        dt = &env->gdt;
    index = selector & ~7;
    if ((index + 7) > dt->limit)
        return -1;
    ptr = dt->base + index;
    *e1_ptr = ldl_kernel(ptr);
    *e2_ptr = ldl_kernel(ptr + 4);
    return 0;
}
                                     
static inline unsigned int get_seg_limit(uint32_t e1, uint32_t e2)
{
    unsigned int limit;
    limit = (e1 & 0xffff) | (e2 & 0x000f0000);
    if (e2 & DESC_G_MASK)
        limit = (limit << 12) | 0xfff;
    return limit;
}

static inline uint8_t *get_seg_base(uint32_t e1, uint32_t e2)
{
    return (uint8_t *)((e1 >> 16) | ((e2 & 0xff) << 16) | (e2 & 0xff000000));
}

static inline void load_seg_cache_raw_dt(SegmentCache *sc, uint32_t e1, uint32_t e2)
{
    sc->base = get_seg_base(e1, e2);
    sc->limit = get_seg_limit(e1, e2);
    sc->flags = e2;
}

/* init the segment cache in vm86 mode. */
static inline void load_seg_vm(int seg, int selector)
{
    selector &= 0xffff;
    cpu_x86_load_seg_cache(env, seg, selector, 
                           (uint8_t *)(selector << 4), 0xffff, 0);
}

static inline void get_ss_esp_from_tss(uint32_t *ss_ptr, 
                                       uint32_t *esp_ptr, int dpl)
{
    int type, index, shift;
    
#if 0
    {
        int i;
        printf("TR: base=%p limit=%x\n", env->tr.base, env->tr.limit);
        for(i=0;i<env->tr.limit;i++) {
            printf("%02x ", env->tr.base[i]);
            if ((i & 7) == 7) printf("\n");
        }
        printf("\n");
    }
#endif

    if (!(env->tr.flags & DESC_P_MASK))
        cpu_abort(env, "invalid tss");
    type = (env->tr.flags >> DESC_TYPE_SHIFT) & 0xf;
    if ((type & 7) != 1)
        cpu_abort(env, "invalid tss type");
    shift = type >> 3;
    index = (dpl * 4 + 2) << shift;
    if (index + (4 << shift) - 1 > env->tr.limit)
        raise_exception_err(EXCP0A_TSS, env->tr.selector & 0xfffc);
    if (shift == 0) {
        *esp_ptr = lduw_kernel(env->tr.base + index);
        *ss_ptr = lduw_kernel(env->tr.base + index + 2);
    } else {
        *esp_ptr = ldl_kernel(env->tr.base + index);
        *ss_ptr = lduw_kernel(env->tr.base + index + 4);
    }
}

/* XXX: merge with load_seg() */
static void tss_load_seg(int seg_reg, int selector)
{
    uint32_t e1, e2;
    int rpl, dpl, cpl;

    if ((selector & 0xfffc) != 0) {
        if (load_segment(&e1, &e2, selector) != 0)
            raise_exception_err(EXCP0A_TSS, selector & 0xfffc);
        if (!(e2 & DESC_S_MASK))
            raise_exception_err(EXCP0A_TSS, selector & 0xfffc);
        rpl = selector & 3;
        dpl = (e2 >> DESC_DPL_SHIFT) & 3;
        cpl = env->hflags & HF_CPL_MASK;
        if (seg_reg == R_CS) {
            if (!(e2 & DESC_CS_MASK))
                raise_exception_err(EXCP0A_TSS, selector & 0xfffc);
            if (dpl != rpl)
                raise_exception_err(EXCP0A_TSS, selector & 0xfffc);
            if ((e2 & DESC_C_MASK) && dpl > rpl)
                raise_exception_err(EXCP0A_TSS, selector & 0xfffc);
                
        } else if (seg_reg == R_SS) {
            /* SS must be writable data */
            if ((e2 & DESC_CS_MASK) || !(e2 & DESC_W_MASK))
                raise_exception_err(EXCP0A_TSS, selector & 0xfffc);
            if (dpl != cpl || dpl != rpl)
                raise_exception_err(EXCP0A_TSS, selector & 0xfffc);
        } else {
            /* not readable code */
            if ((e2 & DESC_CS_MASK) && !(e2 & DESC_R_MASK))
                raise_exception_err(EXCP0A_TSS, selector & 0xfffc);
            /* if data or non conforming code, checks the rights */
            if (((e2 >> DESC_TYPE_SHIFT) & 0xf) < 12) {
                if (dpl < cpl || dpl < rpl)
                    raise_exception_err(EXCP0A_TSS, selector & 0xfffc);
            }
        }
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(EXCP0B_NOSEG, selector & 0xfffc);
        cpu_x86_load_seg_cache(env, seg_reg, selector, 
                       get_seg_base(e1, e2),
                       get_seg_limit(e1, e2),
                       e2);
    } else {
        if (seg_reg == R_SS || seg_reg == R_CS) 
            raise_exception_err(EXCP0A_TSS, selector & 0xfffc);
    }
}

#define SWITCH_TSS_JMP  0
#define SWITCH_TSS_IRET 1
#define SWITCH_TSS_CALL 2

/* XXX: restore CPU state in registers (PowerPC case) */
static void switch_tss(int tss_selector, 
                       uint32_t e1, uint32_t e2, int source,
                       uint32_t next_eip)
{
    int tss_limit, tss_limit_max, type, old_tss_limit_max, old_type, v1, v2, i;
    uint8_t *tss_base;
    uint32_t new_regs[8], new_segs[6];
    uint32_t new_eflags, new_eip, new_cr3, new_ldt, new_trap;
    uint32_t old_eflags, eflags_mask;
    SegmentCache *dt;
    int index;
    uint8_t *ptr;

    type = (e2 >> DESC_TYPE_SHIFT) & 0xf;
#ifdef DEBUG_PCALL
    if (loglevel & CPU_LOG_PCALL)
        fprintf(logfile, "switch_tss: sel=0x%04x type=%d src=%d\n", tss_selector, type, source);
#endif

    /* if task gate, we read the TSS segment and we load it */
    if (type == 5) {
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(EXCP0B_NOSEG, tss_selector & 0xfffc);
        tss_selector = e1 >> 16;
        if (tss_selector & 4)
            raise_exception_err(EXCP0A_TSS, tss_selector & 0xfffc);
        if (load_segment(&e1, &e2, tss_selector) != 0)
            raise_exception_err(EXCP0D_GPF, tss_selector & 0xfffc);
        if (e2 & DESC_S_MASK)
            raise_exception_err(EXCP0D_GPF, tss_selector & 0xfffc);
        type = (e2 >> DESC_TYPE_SHIFT) & 0xf;
        if ((type & 7) != 1)
            raise_exception_err(EXCP0D_GPF, tss_selector & 0xfffc);
    }

    if (!(e2 & DESC_P_MASK))
        raise_exception_err(EXCP0B_NOSEG, tss_selector & 0xfffc);

    if (type & 8)
        tss_limit_max = 103;
    else
        tss_limit_max = 43;
    tss_limit = get_seg_limit(e1, e2);
    tss_base = get_seg_base(e1, e2);
    if ((tss_selector & 4) != 0 || 
        tss_limit < tss_limit_max)
        raise_exception_err(EXCP0A_TSS, tss_selector & 0xfffc);
    old_type = (env->tr.flags >> DESC_TYPE_SHIFT) & 0xf;
    if (old_type & 8)
        old_tss_limit_max = 103;
    else
        old_tss_limit_max = 43;

    /* read all the registers from the new TSS */
    if (type & 8) {
        /* 32 bit */
        new_cr3 = ldl_kernel(tss_base + 0x1c);
        new_eip = ldl_kernel(tss_base + 0x20);
        new_eflags = ldl_kernel(tss_base + 0x24);
        for(i = 0; i < 8; i++)
            new_regs[i] = ldl_kernel(tss_base + (0x28 + i * 4));
        for(i = 0; i < 6; i++)
            new_segs[i] = lduw_kernel(tss_base + (0x48 + i * 4));
        new_ldt = lduw_kernel(tss_base + 0x60);
        new_trap = ldl_kernel(tss_base + 0x64);
    } else {
        /* 16 bit */
        new_cr3 = 0;
        new_eip = lduw_kernel(tss_base + 0x0e);
        new_eflags = lduw_kernel(tss_base + 0x10);
        for(i = 0; i < 8; i++)
            new_regs[i] = lduw_kernel(tss_base + (0x12 + i * 2)) | 0xffff0000;
        for(i = 0; i < 4; i++)
            new_segs[i] = lduw_kernel(tss_base + (0x22 + i * 4));
        new_ldt = lduw_kernel(tss_base + 0x2a);
        new_segs[R_FS] = 0;
        new_segs[R_GS] = 0;
        new_trap = 0;
    }
    
    /* NOTE: we must avoid memory exceptions during the task switch,
       so we make dummy accesses before */
    /* XXX: it can still fail in some cases, so a bigger hack is
       necessary to valid the TLB after having done the accesses */

    v1 = ldub_kernel(env->tr.base);
    v2 = ldub(env->tr.base + old_tss_limit_max);
    stb_kernel(env->tr.base, v1);
    stb_kernel(env->tr.base + old_tss_limit_max, v2);
    
    /* clear busy bit (it is restartable) */
    if (source == SWITCH_TSS_JMP || source == SWITCH_TSS_IRET) {
        uint8_t *ptr;
        uint32_t e2;
        ptr = env->gdt.base + (env->tr.selector & ~7);
        e2 = ldl_kernel(ptr + 4);
        e2 &= ~DESC_TSS_BUSY_MASK;
        stl_kernel(ptr + 4, e2);
    }
    old_eflags = compute_eflags();
    if (source == SWITCH_TSS_IRET)
        old_eflags &= ~NT_MASK;
    
    /* save the current state in the old TSS */
    if (type & 8) {
        /* 32 bit */
        stl_kernel(env->tr.base + 0x20, next_eip);
        stl_kernel(env->tr.base + 0x24, old_eflags);
        for(i = 0; i < 8; i++)
            stl_kernel(env->tr.base + (0x28 + i * 4), env->regs[i]);
        for(i = 0; i < 6; i++)
            stw_kernel(env->tr.base + (0x48 + i * 4), env->segs[i].selector);
    } else {
        /* 16 bit */
        stw_kernel(env->tr.base + 0x0e, next_eip);
        stw_kernel(env->tr.base + 0x10, old_eflags);
        for(i = 0; i < 8; i++)
            stw_kernel(env->tr.base + (0x12 + i * 2), env->regs[i]);
        for(i = 0; i < 4; i++)
            stw_kernel(env->tr.base + (0x22 + i * 4), env->segs[i].selector);
    }
    
    /* now if an exception occurs, it will occurs in the next task
       context */

    if (source == SWITCH_TSS_CALL) {
        stw_kernel(tss_base, env->tr.selector);
        new_eflags |= NT_MASK;
    }

    /* set busy bit */
    if (source == SWITCH_TSS_JMP || source == SWITCH_TSS_CALL) {
        uint8_t *ptr;
        uint32_t e2;
        ptr = env->gdt.base + (tss_selector & ~7);
        e2 = ldl_kernel(ptr + 4);
        e2 |= DESC_TSS_BUSY_MASK;
        stl_kernel(ptr + 4, e2);
    }

    /* set the new CPU state */
    /* from this point, any exception which occurs can give problems */
    env->cr[0] |= CR0_TS_MASK;
    env->hflags |= HF_TS_MASK;
    env->tr.selector = tss_selector;
    env->tr.base = tss_base;
    env->tr.limit = tss_limit;
    env->tr.flags = e2 & ~DESC_TSS_BUSY_MASK;
    
    if ((type & 8) && (env->cr[0] & CR0_PG_MASK)) {
        cpu_x86_update_cr3(env, new_cr3);
    }
    
    /* load all registers without an exception, then reload them with
       possible exception */
    env->eip = new_eip;
    eflags_mask = TF_MASK | AC_MASK | ID_MASK | 
        IF_MASK | IOPL_MASK | VM_MASK | RF_MASK | NT_MASK;
    if (!(type & 8))
        eflags_mask &= 0xffff;
    load_eflags(new_eflags, eflags_mask);
    for(i = 0; i < 8; i++)
        env->regs[i] = new_regs[i];
    if (new_eflags & VM_MASK) {
        for(i = 0; i < 6; i++) 
            load_seg_vm(i, new_segs[i]);
        /* in vm86, CPL is always 3 */
        cpu_x86_set_cpl(env, 3);
    } else {
        /* CPL is set the RPL of CS */
        cpu_x86_set_cpl(env, new_segs[R_CS] & 3);
        /* first just selectors as the rest may trigger exceptions */
        for(i = 0; i < 6; i++)
            cpu_x86_load_seg_cache(env, i, new_segs[i], NULL, 0, 0);
    }
    
    env->ldt.selector = new_ldt & ~4;
    env->ldt.base = NULL;
    env->ldt.limit = 0;
    env->ldt.flags = 0;

    /* load the LDT */
    if (new_ldt & 4)
        raise_exception_err(EXCP0A_TSS, new_ldt & 0xfffc);

    if ((new_ldt & 0xfffc) != 0) {
        dt = &env->gdt;
        index = new_ldt & ~7;
        if ((index + 7) > dt->limit)
            raise_exception_err(EXCP0A_TSS, new_ldt & 0xfffc);
        ptr = dt->base + index;
        e1 = ldl_kernel(ptr);
        e2 = ldl_kernel(ptr + 4);
        if ((e2 & DESC_S_MASK) || ((e2 >> DESC_TYPE_SHIFT) & 0xf) != 2)
            raise_exception_err(EXCP0A_TSS, new_ldt & 0xfffc);
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(EXCP0A_TSS, new_ldt & 0xfffc);
        load_seg_cache_raw_dt(&env->ldt, e1, e2);
    }
    
    /* load the segments */
    if (!(new_eflags & VM_MASK)) {
        tss_load_seg(R_CS, new_segs[R_CS]);
        tss_load_seg(R_SS, new_segs[R_SS]);
        tss_load_seg(R_ES, new_segs[R_ES]);
        tss_load_seg(R_DS, new_segs[R_DS]);
        tss_load_seg(R_FS, new_segs[R_FS]);
        tss_load_seg(R_GS, new_segs[R_GS]);
    }
    
    /* check that EIP is in the CS segment limits */
    if (new_eip > env->segs[R_CS].limit) {
        /* XXX: different exception if CALL ? */
        raise_exception_err(EXCP0D_GPF, 0);
    }
}

/* check if Port I/O is allowed in TSS */
static inline void check_io(int addr, int size)
{
    int io_offset, val, mask;
    
    /* TSS must be a valid 32 bit one */
    if (!(env->tr.flags & DESC_P_MASK) ||
        ((env->tr.flags >> DESC_TYPE_SHIFT) & 0xf) != 9 ||
        env->tr.limit < 103)
        goto fail;
    io_offset = lduw_kernel(env->tr.base + 0x66);
    io_offset += (addr >> 3);
    /* Note: the check needs two bytes */
    if ((io_offset + 1) > env->tr.limit)
        goto fail;
    val = lduw_kernel(env->tr.base + io_offset);
    val >>= (addr & 7);
    mask = (1 << size) - 1;
    /* all bits must be zero to allow the I/O */
    if ((val & mask) != 0) {
    fail:
        raise_exception_err(EXCP0D_GPF, 0);
    }
}

void check_iob_T0(void)
{
    check_io(T0, 1);
}

void check_iow_T0(void)
{
    check_io(T0, 2);
}

void check_iol_T0(void)
{
    check_io(T0, 4);
}

void check_iob_DX(void)
{
    check_io(EDX & 0xffff, 1);
}

void check_iow_DX(void)
{
    check_io(EDX & 0xffff, 2);
}

void check_iol_DX(void)
{
    check_io(EDX & 0xffff, 4);
}

static inline unsigned int get_sp_mask(unsigned int e2)
{
    if (e2 & DESC_B_MASK)
        return 0xffffffff;
    else
        return 0xffff;
}

/* XXX: add a is_user flag to have proper security support */
#define PUSHW(ssp, sp, sp_mask, val)\
{\
    sp -= 2;\
    stw_kernel((ssp) + (sp & (sp_mask)), (val));\
}

#define PUSHL(ssp, sp, sp_mask, val)\
{\
    sp -= 4;\
    stl_kernel((ssp) + (sp & (sp_mask)), (val));\
}

#define POPW(ssp, sp, sp_mask, val)\
{\
    val = lduw_kernel((ssp) + (sp & (sp_mask)));\
    sp += 2;\
}

#define POPL(ssp, sp, sp_mask, val)\
{\
    val = ldl_kernel((ssp) + (sp & (sp_mask)));\
    sp += 4;\
}

/* protected mode interrupt */
static void do_interrupt_protected(int intno, int is_int, int error_code,
                                   unsigned int next_eip, int is_hw)
{
    SegmentCache *dt;
    uint8_t *ptr, *ssp;
    int type, dpl, selector, ss_dpl, cpl, sp_mask;
    int has_error_code, new_stack, shift;
    uint32_t e1, e2, offset, ss, esp, ss_e1, ss_e2;
    uint32_t old_eip;

    has_error_code = 0;
    if (!is_int && !is_hw) {
        switch(intno) {
        case 8:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 17:
            has_error_code = 1;
            break;
        }
    }
    if (is_int)
        old_eip = next_eip;
    else
        old_eip = env->eip;

    dt = &env->idt;
    if (intno * 8 + 7 > dt->limit)
        raise_exception_err(EXCP0D_GPF, intno * 8 + 2);
    ptr = dt->base + intno * 8;
    e1 = ldl_kernel(ptr);
    e2 = ldl_kernel(ptr + 4);
    /* check gate type */
    type = (e2 >> DESC_TYPE_SHIFT) & 0x1f;
    switch(type) {
    case 5: /* task gate */
        /* must do that check here to return the correct error code */
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(EXCP0B_NOSEG, intno * 8 + 2);
        switch_tss(intno * 8, e1, e2, SWITCH_TSS_CALL, old_eip);
        if (has_error_code) {
            int mask;
            /* push the error code */
            shift = (env->segs[R_CS].flags >> DESC_B_SHIFT) & 1;
            if (env->segs[R_SS].flags & DESC_B_MASK)
                mask = 0xffffffff;
            else
                mask = 0xffff;
            esp = (env->regs[R_ESP] - (2 << shift)) & mask;
            ssp = env->segs[R_SS].base + esp;
            if (shift)
                stl_kernel(ssp, error_code);
            else
                stw_kernel(ssp, error_code);
            env->regs[R_ESP] = (esp & mask) | (env->regs[R_ESP] & ~mask);
        }
        return;
    case 6: /* 286 interrupt gate */
    case 7: /* 286 trap gate */
    case 14: /* 386 interrupt gate */
    case 15: /* 386 trap gate */
        break;
    default:
        raise_exception_err(EXCP0D_GPF, intno * 8 + 2);
        break;
    }
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    cpl = env->hflags & HF_CPL_MASK;
    /* check privledge if software int */
    if (is_int && dpl < cpl)
        raise_exception_err(EXCP0D_GPF, intno * 8 + 2);
    /* check valid bit */
    if (!(e2 & DESC_P_MASK))
        raise_exception_err(EXCP0B_NOSEG, intno * 8 + 2);
    selector = e1 >> 16;
    offset = (e2 & 0xffff0000) | (e1 & 0x0000ffff);
    if ((selector & 0xfffc) == 0)
        raise_exception_err(EXCP0D_GPF, 0);

    if (load_segment(&e1, &e2, selector) != 0)
        raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
    if (!(e2 & DESC_S_MASK) || !(e2 & (DESC_CS_MASK)))
        raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    if (dpl > cpl)
        raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
    if (!(e2 & DESC_P_MASK))
        raise_exception_err(EXCP0B_NOSEG, selector & 0xfffc);
    if (!(e2 & DESC_C_MASK) && dpl < cpl) {
        /* to inner priviledge */
        get_ss_esp_from_tss(&ss, &esp, dpl);
        if ((ss & 0xfffc) == 0)
            raise_exception_err(EXCP0A_TSS, ss & 0xfffc);
        if ((ss & 3) != dpl)
            raise_exception_err(EXCP0A_TSS, ss & 0xfffc);
        if (load_segment(&ss_e1, &ss_e2, ss) != 0)
            raise_exception_err(EXCP0A_TSS, ss & 0xfffc);
        ss_dpl = (ss_e2 >> DESC_DPL_SHIFT) & 3;
        if (ss_dpl != dpl)
            raise_exception_err(EXCP0A_TSS, ss & 0xfffc);
        if (!(ss_e2 & DESC_S_MASK) ||
            (ss_e2 & DESC_CS_MASK) ||
            !(ss_e2 & DESC_W_MASK))
            raise_exception_err(EXCP0A_TSS, ss & 0xfffc);
        if (!(ss_e2 & DESC_P_MASK))
            raise_exception_err(EXCP0A_TSS, ss & 0xfffc);
        new_stack = 1;
        sp_mask = get_sp_mask(ss_e2);
        ssp = get_seg_base(ss_e1, ss_e2);
    } else if ((e2 & DESC_C_MASK) || dpl == cpl) {
        /* to same priviledge */
        if (env->eflags & VM_MASK)
            raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
        new_stack = 0;
        sp_mask = get_sp_mask(env->segs[R_SS].flags);
        ssp = env->segs[R_SS].base;
        esp = ESP;
        dpl = cpl;
    } else {
        raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
        new_stack = 0; /* avoid warning */
        sp_mask = 0; /* avoid warning */
        ssp = NULL; /* avoid warning */
        esp = 0; /* avoid warning */
    }

    shift = type >> 3;

#if 0
    /* XXX: check that enough room is available */
    push_size = 6 + (new_stack << 2) + (has_error_code << 1);
    if (env->eflags & VM_MASK)
        push_size += 8;
    push_size <<= shift;
#endif
    if (shift == 1) {
        if (new_stack) {
            if (env->eflags & VM_MASK) {
                PUSHL(ssp, esp, sp_mask, env->segs[R_GS].selector);
                PUSHL(ssp, esp, sp_mask, env->segs[R_FS].selector);
                PUSHL(ssp, esp, sp_mask, env->segs[R_DS].selector);
                PUSHL(ssp, esp, sp_mask, env->segs[R_ES].selector);
            }
            PUSHL(ssp, esp, sp_mask, env->segs[R_SS].selector);
            PUSHL(ssp, esp, sp_mask, ESP);
        }
        PUSHL(ssp, esp, sp_mask, compute_eflags());
        PUSHL(ssp, esp, sp_mask, env->segs[R_CS].selector);
        PUSHL(ssp, esp, sp_mask, old_eip);
        if (has_error_code) {
            PUSHL(ssp, esp, sp_mask, error_code);
        }
    } else {
        if (new_stack) {
            if (env->eflags & VM_MASK) {
                PUSHW(ssp, esp, sp_mask, env->segs[R_GS].selector);
                PUSHW(ssp, esp, sp_mask, env->segs[R_FS].selector);
                PUSHW(ssp, esp, sp_mask, env->segs[R_DS].selector);
                PUSHW(ssp, esp, sp_mask, env->segs[R_ES].selector);
            }
            PUSHW(ssp, esp, sp_mask, env->segs[R_SS].selector);
            PUSHW(ssp, esp, sp_mask, ESP);
        }
        PUSHW(ssp, esp, sp_mask, compute_eflags());
        PUSHW(ssp, esp, sp_mask, env->segs[R_CS].selector);
        PUSHW(ssp, esp, sp_mask, old_eip);
        if (has_error_code) {
            PUSHW(ssp, esp, sp_mask, error_code);
        }
    }
    
    if (new_stack) {
        if (env->eflags & VM_MASK) {
            cpu_x86_load_seg_cache(env, R_ES, 0, NULL, 0, 0);
            cpu_x86_load_seg_cache(env, R_DS, 0, NULL, 0, 0);
            cpu_x86_load_seg_cache(env, R_FS, 0, NULL, 0, 0);
            cpu_x86_load_seg_cache(env, R_GS, 0, NULL, 0, 0);
        }
        ss = (ss & ~3) | dpl;
        cpu_x86_load_seg_cache(env, R_SS, ss, 
                               ssp, get_seg_limit(ss_e1, ss_e2), ss_e2);
    }
    ESP = (ESP & ~sp_mask) | (esp & sp_mask);

    selector = (selector & ~3) | dpl;
    cpu_x86_load_seg_cache(env, R_CS, selector, 
                   get_seg_base(e1, e2),
                   get_seg_limit(e1, e2),
                   e2);
    cpu_x86_set_cpl(env, dpl);
    env->eip = offset;

    /* interrupt gate clear IF mask */
    if ((type & 1) == 0) {
        env->eflags &= ~IF_MASK;
    }
    env->eflags &= ~(TF_MASK | VM_MASK | RF_MASK | NT_MASK);
}

/* real mode interrupt */
static void do_interrupt_real(int intno, int is_int, int error_code,
                              unsigned int next_eip)
{
    SegmentCache *dt;
    uint8_t *ptr, *ssp;
    int selector;
    uint32_t offset, esp;
    uint32_t old_cs, old_eip;

    /* real mode (simpler !) */
    dt = &env->idt;
    if (intno * 4 + 3 > dt->limit)
        raise_exception_err(EXCP0D_GPF, intno * 8 + 2);
    ptr = dt->base + intno * 4;
    offset = lduw_kernel(ptr);
    selector = lduw_kernel(ptr + 2);
    esp = ESP;
    ssp = env->segs[R_SS].base;
    if (is_int)
        old_eip = next_eip;
    else
        old_eip = env->eip;
    old_cs = env->segs[R_CS].selector;
    /* XXX: use SS segment size ? */
    PUSHW(ssp, esp, 0xffff, compute_eflags());
    PUSHW(ssp, esp, 0xffff, old_cs);
    PUSHW(ssp, esp, 0xffff, old_eip);
    
    /* update processor state */
    ESP = (ESP & ~0xffff) | (esp & 0xffff);
    env->eip = offset;
    env->segs[R_CS].selector = selector;
    env->segs[R_CS].base = (uint8_t *)(selector << 4);
    env->eflags &= ~(IF_MASK | TF_MASK | AC_MASK | RF_MASK);
}

/* fake user mode interrupt */
void do_interrupt_user(int intno, int is_int, int error_code, 
                       unsigned int next_eip)
{
    SegmentCache *dt;
    uint8_t *ptr;
    int dpl, cpl;
    uint32_t e2;

    dt = &env->idt;
    ptr = dt->base + (intno * 8);
    e2 = ldl_kernel(ptr + 4);
    
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    cpl = env->hflags & HF_CPL_MASK;
    /* check privledge if software int */
    if (is_int && dpl < cpl)
        raise_exception_err(EXCP0D_GPF, intno * 8 + 2);

    /* Since we emulate only user space, we cannot do more than
       exiting the emulation with the suitable exception and error
       code */
    if (is_int)
        EIP = next_eip;
}

/*
 * Begin execution of an interruption. is_int is TRUE if coming from
 * the int instruction. next_eip is the EIP value AFTER the interrupt
 * instruction. It is only relevant if is_int is TRUE.  
 */
void do_interrupt(int intno, int is_int, int error_code, 
                  unsigned int next_eip, int is_hw)
{
#ifdef DEBUG_PCALL
    if (loglevel & (CPU_LOG_PCALL | CPU_LOG_INT)) {
        if ((env->cr[0] & CR0_PE_MASK)) {
            static int count;
            fprintf(logfile, "%6d: v=%02x e=%04x i=%d cpl=%d IP=%04x:%08x pc=%08x SP=%04x:%08x",
                    count, intno, error_code, is_int,
                    env->hflags & HF_CPL_MASK,
                    env->segs[R_CS].selector, EIP,
                    (int)env->segs[R_CS].base + EIP,
                    env->segs[R_SS].selector, ESP);
            if (intno == 0x0e) {
                fprintf(logfile, " CR2=%08x", env->cr[2]);
            } else {
                fprintf(logfile, " EAX=%08x", env->regs[R_EAX]);
            }
            fprintf(logfile, "\n");
#if 0
            cpu_x86_dump_state(env, logfile, X86_DUMP_CCOP);
            {
                int i;
                uint8_t *ptr;
                fprintf(logfile, "       code=");
                ptr = env->segs[R_CS].base + env->eip;
                for(i = 0; i < 16; i++) {
                    fprintf(logfile, " %02x", ldub(ptr + i));
                }
                fprintf(logfile, "\n");
            }
#endif
            count++;
        }
    }
#endif
    if (env->cr[0] & CR0_PE_MASK) {
        do_interrupt_protected(intno, is_int, error_code, next_eip, is_hw);
    } else {
        do_interrupt_real(intno, is_int, error_code, next_eip);
    }
}

/*
 * Signal an interruption. It is executed in the main CPU loop.
 * is_int is TRUE if coming from the int instruction. next_eip is the
 * EIP value AFTER the interrupt instruction. It is only relevant if
 * is_int is TRUE.  
 */
void raise_interrupt(int intno, int is_int, int error_code, 
                     unsigned int next_eip)
{
    env->exception_index = intno;
    env->error_code = error_code;
    env->exception_is_int = is_int;
    env->exception_next_eip = next_eip;
    cpu_loop_exit();
}

/* shortcuts to generate exceptions */

void (raise_exception_err)(int exception_index, int error_code)
{
    raise_interrupt(exception_index, 0, error_code, 0);
}

void raise_exception(int exception_index)
{
    raise_interrupt(exception_index, 0, 0, 0);
}

#ifdef BUGGY_GCC_DIV64
/* gcc 2.95.4 on PowerPC does not seem to like using __udivdi3, so we
   call it from another function */
uint32_t div64(uint32_t *q_ptr, uint64_t num, uint32_t den)
{
    *q_ptr = num / den;
    return num % den;
}

int32_t idiv64(int32_t *q_ptr, int64_t num, int32_t den)
{
    *q_ptr = num / den;
    return num % den;
}
#endif

void helper_divl_EAX_T0(uint32_t eip)
{
    unsigned int den, q, r;
    uint64_t num;
    
    num = EAX | ((uint64_t)EDX << 32);
    den = T0;
    if (den == 0) {
        EIP = eip;
        raise_exception(EXCP00_DIVZ);
    }
#ifdef BUGGY_GCC_DIV64
    r = div64(&q, num, den);
#else
    q = (num / den);
    r = (num % den);
#endif
    EAX = q;
    EDX = r;
}

void helper_idivl_EAX_T0(uint32_t eip)
{
    int den, q, r;
    int64_t num;
    
    num = EAX | ((uint64_t)EDX << 32);
    den = T0;
    if (den == 0) {
        EIP = eip;
        raise_exception(EXCP00_DIVZ);
    }
#ifdef BUGGY_GCC_DIV64
    r = idiv64(&q, num, den);
#else
    q = (num / den);
    r = (num % den);
#endif
    EAX = q;
    EDX = r;
}

void helper_cmpxchg8b(void)
{
    uint64_t d;
    int eflags;

    eflags = cc_table[CC_OP].compute_all();
    d = ldq((uint8_t *)A0);
    if (d == (((uint64_t)EDX << 32) | EAX)) {
        stq((uint8_t *)A0, ((uint64_t)ECX << 32) | EBX);
        eflags |= CC_Z;
    } else {
        EDX = d >> 32;
        EAX = d;
        eflags &= ~CC_Z;
    }
    CC_SRC = eflags;
}

#define CPUID_FP87 (1 << 0)
#define CPUID_VME  (1 << 1)
#define CPUID_DE   (1 << 2)
#define CPUID_PSE  (1 << 3)
#define CPUID_TSC  (1 << 4)
#define CPUID_MSR  (1 << 5)
#define CPUID_PAE  (1 << 6)
#define CPUID_MCE  (1 << 7)
#define CPUID_CX8  (1 << 8)
#define CPUID_APIC (1 << 9)
#define CPUID_SEP  (1 << 11) /* sysenter/sysexit */
#define CPUID_MTRR (1 << 12)
#define CPUID_PGE  (1 << 13)
#define CPUID_MCA  (1 << 14)
#define CPUID_CMOV (1 << 15)
/* ... */
#define CPUID_MMX  (1 << 23)
#define CPUID_FXSR (1 << 24)
#define CPUID_SSE  (1 << 25)
#define CPUID_SSE2 (1 << 26)

void helper_cpuid(void)
{
    switch(EAX) {
    case 0:
        EAX = 2; /* max EAX index supported */
        EBX = 0x756e6547;
        ECX = 0x6c65746e;
        EDX = 0x49656e69;
        break;
    case 1:
        {
            int family, model, stepping;
            /* EAX = 1 info */
#if 0
            /* pentium 75-200 */
            family = 5;
            model = 2;
            stepping = 11;
#else
            /* pentium pro */
            family = 6;
            model = 1;
            stepping = 3;
#endif
            EAX = (family << 8) | (model << 4) | stepping;
            EBX = 0;
            ECX = 0;
            EDX = CPUID_FP87 | CPUID_DE | CPUID_PSE |
                CPUID_TSC | CPUID_MSR | CPUID_MCE |
                CPUID_CX8 | CPUID_PGE | CPUID_CMOV;
        }
        break;
    default:
        /* cache info: needed for Pentium Pro compatibility */
        EAX = 0x410601;
        EBX = 0;
        ECX = 0;
        EDX = 0;
        break;
    }
}

void helper_lldt_T0(void)
{
    int selector;
    SegmentCache *dt;
    uint32_t e1, e2;
    int index;
    uint8_t *ptr;
    
    selector = T0 & 0xffff;
    if ((selector & 0xfffc) == 0) {
        /* XXX: NULL selector case: invalid LDT */
        env->ldt.base = NULL;
        env->ldt.limit = 0;
    } else {
        if (selector & 0x4)
            raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
        dt = &env->gdt;
        index = selector & ~7;
        if ((index + 7) > dt->limit)
            raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
        ptr = dt->base + index;
        e1 = ldl_kernel(ptr);
        e2 = ldl_kernel(ptr + 4);
        if ((e2 & DESC_S_MASK) || ((e2 >> DESC_TYPE_SHIFT) & 0xf) != 2)
            raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(EXCP0B_NOSEG, selector & 0xfffc);
        load_seg_cache_raw_dt(&env->ldt, e1, e2);
    }
    env->ldt.selector = selector;
}

void helper_ltr_T0(void)
{
    int selector;
    SegmentCache *dt;
    uint32_t e1, e2;
    int index, type;
    uint8_t *ptr;
    
    selector = T0 & 0xffff;
    if ((selector & 0xfffc) == 0) {
        /* NULL selector case: invalid LDT */
        env->tr.base = NULL;
        env->tr.limit = 0;
        env->tr.flags = 0;
    } else {
        if (selector & 0x4)
            raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
        dt = &env->gdt;
        index = selector & ~7;
        if ((index + 7) > dt->limit)
            raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
        ptr = dt->base + index;
        e1 = ldl_kernel(ptr);
        e2 = ldl_kernel(ptr + 4);
        type = (e2 >> DESC_TYPE_SHIFT) & 0xf;
        if ((e2 & DESC_S_MASK) || 
            (type != 1 && type != 9))
            raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(EXCP0B_NOSEG, selector & 0xfffc);
        load_seg_cache_raw_dt(&env->tr, e1, e2);
        e2 |= DESC_TSS_BUSY_MASK;
        stl_kernel(ptr + 4, e2);
    }
    env->tr.selector = selector;
}

/* only works if protected mode and not VM86. seg_reg must be != R_CS */
void load_seg(int seg_reg, int selector)
{
    uint32_t e1, e2;
    int cpl, dpl, rpl;
    SegmentCache *dt;
    int index;
    uint8_t *ptr;

    selector &= 0xffff;
    if ((selector & 0xfffc) == 0) {
        /* null selector case */
        if (seg_reg == R_SS)
            raise_exception_err(EXCP0D_GPF, 0);
        cpu_x86_load_seg_cache(env, seg_reg, selector, NULL, 0, 0);
    } else {
        
        if (selector & 0x4)
            dt = &env->ldt;
        else
            dt = &env->gdt;
        index = selector & ~7;
        if ((index + 7) > dt->limit)
            raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
        ptr = dt->base + index;
        e1 = ldl_kernel(ptr);
        e2 = ldl_kernel(ptr + 4);

        if (!(e2 & DESC_S_MASK))
            raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
        rpl = selector & 3;
        dpl = (e2 >> DESC_DPL_SHIFT) & 3;
        cpl = env->hflags & HF_CPL_MASK;
        if (seg_reg == R_SS) {
            /* must be writable segment */
            if ((e2 & DESC_CS_MASK) || !(e2 & DESC_W_MASK))
                raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
            if (rpl != cpl || dpl != cpl)
                raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
        } else {
            /* must be readable segment */
            if ((e2 & (DESC_CS_MASK | DESC_R_MASK)) == DESC_CS_MASK)
                raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
            
            if (!(e2 & DESC_CS_MASK) || !(e2 & DESC_C_MASK)) {
                /* if not conforming code, test rights */
                if (dpl < cpl || dpl < rpl)
                    raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
            }
        }

        if (!(e2 & DESC_P_MASK)) {
            if (seg_reg == R_SS)
                raise_exception_err(EXCP0C_STACK, selector & 0xfffc);
            else
                raise_exception_err(EXCP0B_NOSEG, selector & 0xfffc);
        }

        /* set the access bit if not already set */
        if (!(e2 & DESC_A_MASK)) {
            e2 |= DESC_A_MASK;
            stl_kernel(ptr + 4, e2);
        }

        cpu_x86_load_seg_cache(env, seg_reg, selector, 
                       get_seg_base(e1, e2),
                       get_seg_limit(e1, e2),
                       e2);
#if 0
        fprintf(logfile, "load_seg: sel=0x%04x base=0x%08lx limit=0x%08lx flags=%08x\n", 
                selector, (unsigned long)sc->base, sc->limit, sc->flags);
#endif
    }
}

/* protected mode jump */
void helper_ljmp_protected_T0_T1(int next_eip)
{
    int new_cs, new_eip, gate_cs, type;
    uint32_t e1, e2, cpl, dpl, rpl, limit;

    new_cs = T0;
    new_eip = T1;
    if ((new_cs & 0xfffc) == 0)
        raise_exception_err(EXCP0D_GPF, 0);
    if (load_segment(&e1, &e2, new_cs) != 0)
        raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
    cpl = env->hflags & HF_CPL_MASK;
    if (e2 & DESC_S_MASK) {
        if (!(e2 & DESC_CS_MASK))
            raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
        dpl = (e2 >> DESC_DPL_SHIFT) & 3;
        if (e2 & DESC_C_MASK) {
            /* conforming code segment */
            if (dpl > cpl)
                raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
        } else {
            /* non conforming code segment */
            rpl = new_cs & 3;
            if (rpl > cpl)
                raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
            if (dpl != cpl)
                raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
        }
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(EXCP0B_NOSEG, new_cs & 0xfffc);
        limit = get_seg_limit(e1, e2);
        if (new_eip > limit)
            raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
        cpu_x86_load_seg_cache(env, R_CS, (new_cs & 0xfffc) | cpl,
                       get_seg_base(e1, e2), limit, e2);
        EIP = new_eip;
    } else {
        /* jump to call or task gate */
        dpl = (e2 >> DESC_DPL_SHIFT) & 3;
        rpl = new_cs & 3;
        cpl = env->hflags & HF_CPL_MASK;
        type = (e2 >> DESC_TYPE_SHIFT) & 0xf;
        switch(type) {
        case 1: /* 286 TSS */
        case 9: /* 386 TSS */
        case 5: /* task gate */
            if (dpl < cpl || dpl < rpl)
                raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
            switch_tss(new_cs, e1, e2, SWITCH_TSS_JMP, next_eip);
            break;
        case 4: /* 286 call gate */
        case 12: /* 386 call gate */
            if ((dpl < cpl) || (dpl < rpl))
                raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
            if (!(e2 & DESC_P_MASK))
                raise_exception_err(EXCP0B_NOSEG, new_cs & 0xfffc);
            gate_cs = e1 >> 16;
            new_eip = (e1 & 0xffff);
            if (type == 12)
                new_eip |= (e2 & 0xffff0000);
            if (load_segment(&e1, &e2, gate_cs) != 0)
                raise_exception_err(EXCP0D_GPF, gate_cs & 0xfffc);
            dpl = (e2 >> DESC_DPL_SHIFT) & 3;
            /* must be code segment */
            if (((e2 & (DESC_S_MASK | DESC_CS_MASK)) != 
                 (DESC_S_MASK | DESC_CS_MASK)))
                raise_exception_err(EXCP0D_GPF, gate_cs & 0xfffc);
            if (((e2 & DESC_C_MASK) && (dpl > cpl)) ||
                (!(e2 & DESC_C_MASK) && (dpl != cpl)))
                raise_exception_err(EXCP0D_GPF, gate_cs & 0xfffc);
            if (!(e2 & DESC_P_MASK))
                raise_exception_err(EXCP0D_GPF, gate_cs & 0xfffc);
            limit = get_seg_limit(e1, e2);
            if (new_eip > limit)
                raise_exception_err(EXCP0D_GPF, 0);
            cpu_x86_load_seg_cache(env, R_CS, (gate_cs & 0xfffc) | cpl,
                                   get_seg_base(e1, e2), limit, e2);
            EIP = new_eip;
            break;
        default:
            raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
            break;
        }
    }
}

/* real mode call */
void helper_lcall_real_T0_T1(int shift, int next_eip)
{
    int new_cs, new_eip;
    uint32_t esp, esp_mask;
    uint8_t *ssp;

    new_cs = T0;
    new_eip = T1;
    esp = ESP;
    esp_mask = get_sp_mask(env->segs[R_SS].flags);
    ssp = env->segs[R_SS].base;
    if (shift) {
        PUSHL(ssp, esp, esp_mask, env->segs[R_CS].selector);
        PUSHL(ssp, esp, esp_mask, next_eip);
    } else {
        PUSHW(ssp, esp, esp_mask, env->segs[R_CS].selector);
        PUSHW(ssp, esp, esp_mask, next_eip);
    }

    ESP = (ESP & ~esp_mask) | (esp & esp_mask);
    env->eip = new_eip;
    env->segs[R_CS].selector = new_cs;
    env->segs[R_CS].base = (uint8_t *)(new_cs << 4);
}

/* protected mode call */
void helper_lcall_protected_T0_T1(int shift, int next_eip)
{
    int new_cs, new_eip, new_stack, i;
    uint32_t e1, e2, cpl, dpl, rpl, selector, offset, param_count;
    uint32_t ss, ss_e1, ss_e2, sp, type, ss_dpl, sp_mask;
    uint32_t val, limit, old_sp_mask;
    uint8_t *ssp, *old_ssp;
    
    new_cs = T0;
    new_eip = T1;
#ifdef DEBUG_PCALL
    if (loglevel & CPU_LOG_PCALL) {
        fprintf(logfile, "lcall %04x:%08x s=%d\n",
                new_cs, new_eip, shift);
        cpu_x86_dump_state(env, logfile, X86_DUMP_CCOP);
    }
#endif
    if ((new_cs & 0xfffc) == 0)
        raise_exception_err(EXCP0D_GPF, 0);
    if (load_segment(&e1, &e2, new_cs) != 0)
        raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
    cpl = env->hflags & HF_CPL_MASK;
#ifdef DEBUG_PCALL
    if (loglevel & CPU_LOG_PCALL) {
        fprintf(logfile, "desc=%08x:%08x\n", e1, e2);
    }
#endif
    if (e2 & DESC_S_MASK) {
        if (!(e2 & DESC_CS_MASK))
            raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
        dpl = (e2 >> DESC_DPL_SHIFT) & 3;
        if (e2 & DESC_C_MASK) {
            /* conforming code segment */
            if (dpl > cpl)
                raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
        } else {
            /* non conforming code segment */
            rpl = new_cs & 3;
            if (rpl > cpl)
                raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
            if (dpl != cpl)
                raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
        }
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(EXCP0B_NOSEG, new_cs & 0xfffc);

        sp = ESP;
        sp_mask = get_sp_mask(env->segs[R_SS].flags);
        ssp = env->segs[R_SS].base;
        if (shift) {
            PUSHL(ssp, sp, sp_mask, env->segs[R_CS].selector);
            PUSHL(ssp, sp, sp_mask, next_eip);
        } else {
            PUSHW(ssp, sp, sp_mask, env->segs[R_CS].selector);
            PUSHW(ssp, sp, sp_mask, next_eip);
        }
        
        limit = get_seg_limit(e1, e2);
        if (new_eip > limit)
            raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
        /* from this point, not restartable */
        ESP = (ESP & ~sp_mask) | (sp & sp_mask);
        cpu_x86_load_seg_cache(env, R_CS, (new_cs & 0xfffc) | cpl,
                       get_seg_base(e1, e2), limit, e2);
        EIP = new_eip;
    } else {
        /* check gate type */
        type = (e2 >> DESC_TYPE_SHIFT) & 0x1f;
        dpl = (e2 >> DESC_DPL_SHIFT) & 3;
        rpl = new_cs & 3;
        switch(type) {
        case 1: /* available 286 TSS */
        case 9: /* available 386 TSS */
        case 5: /* task gate */
            if (dpl < cpl || dpl < rpl)
                raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
            switch_tss(new_cs, e1, e2, SWITCH_TSS_CALL, next_eip);
            return;
        case 4: /* 286 call gate */
        case 12: /* 386 call gate */
            break;
        default:
            raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
            break;
        }
        shift = type >> 3;

        if (dpl < cpl || dpl < rpl)
            raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
        /* check valid bit */
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(EXCP0B_NOSEG,  new_cs & 0xfffc);
        selector = e1 >> 16;
        offset = (e2 & 0xffff0000) | (e1 & 0x0000ffff);
        param_count = e2 & 0x1f;
        if ((selector & 0xfffc) == 0)
            raise_exception_err(EXCP0D_GPF, 0);

        if (load_segment(&e1, &e2, selector) != 0)
            raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
        if (!(e2 & DESC_S_MASK) || !(e2 & (DESC_CS_MASK)))
            raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
        dpl = (e2 >> DESC_DPL_SHIFT) & 3;
        if (dpl > cpl)
            raise_exception_err(EXCP0D_GPF, selector & 0xfffc);
        if (!(e2 & DESC_P_MASK))
            raise_exception_err(EXCP0B_NOSEG, selector & 0xfffc);

        if (!(e2 & DESC_C_MASK) && dpl < cpl) {
            /* to inner priviledge */
            get_ss_esp_from_tss(&ss, &sp, dpl);
#ifdef DEBUG_PCALL
            if (loglevel & CPU_LOG_PCALL)
                fprintf(logfile, "new ss:esp=%04x:%08x param_count=%d ESP=%x\n", 
                        ss, sp, param_count, ESP);
#endif
            if ((ss & 0xfffc) == 0)
                raise_exception_err(EXCP0A_TSS, ss & 0xfffc);
            if ((ss & 3) != dpl)
                raise_exception_err(EXCP0A_TSS, ss & 0xfffc);
            if (load_segment(&ss_e1, &ss_e2, ss) != 0)
                raise_exception_err(EXCP0A_TSS, ss & 0xfffc);
            ss_dpl = (ss_e2 >> DESC_DPL_SHIFT) & 3;
            if (ss_dpl != dpl)
                raise_exception_err(EXCP0A_TSS, ss & 0xfffc);
            if (!(ss_e2 & DESC_S_MASK) ||
                (ss_e2 & DESC_CS_MASK) ||
                !(ss_e2 & DESC_W_MASK))
                raise_exception_err(EXCP0A_TSS, ss & 0xfffc);
            if (!(ss_e2 & DESC_P_MASK))
                raise_exception_err(EXCP0A_TSS, ss & 0xfffc);
            
            //            push_size = ((param_count * 2) + 8) << shift;

            old_sp_mask = get_sp_mask(env->segs[R_SS].flags);
            old_ssp = env->segs[R_SS].base;
            
            sp_mask = get_sp_mask(ss_e2);
            ssp = get_seg_base(ss_e1, ss_e2);
            if (shift) {
                PUSHL(ssp, sp, sp_mask, env->segs[R_SS].selector);
                PUSHL(ssp, sp, sp_mask, ESP);
                for(i = param_count - 1; i >= 0; i--) {
                    val = ldl_kernel(old_ssp + ((ESP + i * 4) & old_sp_mask));
                    PUSHL(ssp, sp, sp_mask, val);
                }
            } else {
                PUSHW(ssp, sp, sp_mask, env->segs[R_SS].selector);
                PUSHW(ssp, sp, sp_mask, ESP);
                for(i = param_count - 1; i >= 0; i--) {
                    val = lduw_kernel(old_ssp + ((ESP + i * 2) & old_sp_mask));
                    PUSHW(ssp, sp, sp_mask, val);
                }
            }
            new_stack = 1;
        } else {
            /* to same priviledge */
            sp = ESP;
            sp_mask = get_sp_mask(env->segs[R_SS].flags);
            ssp = env->segs[R_SS].base;
            //            push_size = (4 << shift);
            new_stack = 0;
        }

        if (shift) {
            PUSHL(ssp, sp, sp_mask, env->segs[R_CS].selector);
            PUSHL(ssp, sp, sp_mask, next_eip);
        } else {
            PUSHW(ssp, sp, sp_mask, env->segs[R_CS].selector);
            PUSHW(ssp, sp, sp_mask, next_eip);
        }

        /* from this point, not restartable */

        if (new_stack) {
            ss = (ss & ~3) | dpl;
            cpu_x86_load_seg_cache(env, R_SS, ss, 
                                   ssp,
                                   get_seg_limit(ss_e1, ss_e2),
                                   ss_e2);
        }

        selector = (selector & ~3) | dpl;
        cpu_x86_load_seg_cache(env, R_CS, selector, 
                       get_seg_base(e1, e2),
                       get_seg_limit(e1, e2),
                       e2);
        cpu_x86_set_cpl(env, dpl);
        ESP = (ESP & ~sp_mask) | (sp & sp_mask);
        EIP = offset;
    }
}

/* real and vm86 mode iret */
void helper_iret_real(int shift)
{
    uint32_t sp, new_cs, new_eip, new_eflags, sp_mask;
    uint8_t *ssp;
    int eflags_mask;

    sp_mask = 0xffff; /* XXXX: use SS segment size ? */
    sp = ESP;
    ssp = env->segs[R_SS].base;
    if (shift == 1) {
        /* 32 bits */
        POPL(ssp, sp, sp_mask, new_eip);
        POPL(ssp, sp, sp_mask, new_cs);
        new_cs &= 0xffff;
        POPL(ssp, sp, sp_mask, new_eflags);
    } else {
        /* 16 bits */
        POPW(ssp, sp, sp_mask, new_eip);
        POPW(ssp, sp, sp_mask, new_cs);
        POPW(ssp, sp, sp_mask, new_eflags);
    }
    ESP = (ESP & ~sp_mask) | (sp & sp_mask);
    load_seg_vm(R_CS, new_cs);
    env->eip = new_eip;
    if (env->eflags & VM_MASK)
        eflags_mask = TF_MASK | AC_MASK | ID_MASK | IF_MASK | RF_MASK | NT_MASK;
    else
        eflags_mask = TF_MASK | AC_MASK | ID_MASK | IF_MASK | IOPL_MASK | RF_MASK | NT_MASK;
    if (shift == 0)
        eflags_mask &= 0xffff;
    load_eflags(new_eflags, eflags_mask);
}

static inline void validate_seg(int seg_reg, int cpl)
{
    int dpl;
    uint32_t e2;
    
    e2 = env->segs[seg_reg].flags;
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    if (!(e2 & DESC_CS_MASK) || !(e2 & DESC_C_MASK)) {
        /* data or non conforming code segment */
        if (dpl < cpl) {
            cpu_x86_load_seg_cache(env, seg_reg, 0, NULL, 0, 0);
        }
    }
}

/* protected mode iret */
static inline void helper_ret_protected(int shift, int is_iret, int addend)
{
    uint32_t sp, new_cs, new_eip, new_eflags, new_esp, new_ss, sp_mask;
    uint32_t new_es, new_ds, new_fs, new_gs;
    uint32_t e1, e2, ss_e1, ss_e2;
    int cpl, dpl, rpl, eflags_mask, iopl;
    uint8_t *ssp;
    
    sp_mask = get_sp_mask(env->segs[R_SS].flags);
    sp = ESP;
    ssp = env->segs[R_SS].base;
    if (shift == 1) {
        /* 32 bits */
        POPL(ssp, sp, sp_mask, new_eip);
        POPL(ssp, sp, sp_mask, new_cs);
        new_cs &= 0xffff;
        if (is_iret) {
            POPL(ssp, sp, sp_mask, new_eflags);
            if (new_eflags & VM_MASK)
                goto return_to_vm86;
        }
    } else {
        /* 16 bits */
        POPW(ssp, sp, sp_mask, new_eip);
        POPW(ssp, sp, sp_mask, new_cs);
        if (is_iret)
            POPW(ssp, sp, sp_mask, new_eflags);
    }
#ifdef DEBUG_PCALL
    if (loglevel & CPU_LOG_PCALL) {
        fprintf(logfile, "lret new %04x:%08x s=%d addend=0x%x\n",
                new_cs, new_eip, shift, addend);
        cpu_x86_dump_state(env, logfile, X86_DUMP_CCOP);
    }
#endif
    if ((new_cs & 0xfffc) == 0)
        raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
    if (load_segment(&e1, &e2, new_cs) != 0)
        raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
    if (!(e2 & DESC_S_MASK) ||
        !(e2 & DESC_CS_MASK))
        raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
    cpl = env->hflags & HF_CPL_MASK;
    rpl = new_cs & 3; 
    if (rpl < cpl)
        raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    if (e2 & DESC_C_MASK) {
        if (dpl > rpl)
            raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
    } else {
        if (dpl != rpl)
            raise_exception_err(EXCP0D_GPF, new_cs & 0xfffc);
    }
    if (!(e2 & DESC_P_MASK))
        raise_exception_err(EXCP0B_NOSEG, new_cs & 0xfffc);
    
    sp += addend;
    if (rpl == cpl) {
        /* return to same priledge level */
        cpu_x86_load_seg_cache(env, R_CS, new_cs, 
                       get_seg_base(e1, e2),
                       get_seg_limit(e1, e2),
                       e2);
    } else {
        /* return to different priviledge level */
        if (shift == 1) {
            /* 32 bits */
            POPL(ssp, sp, sp_mask, new_esp);
            POPL(ssp, sp, sp_mask, new_ss);
            new_ss &= 0xffff;
        } else {
            /* 16 bits */
            POPW(ssp, sp, sp_mask, new_esp);
            POPW(ssp, sp, sp_mask, new_ss);
        }
#ifdef DEBUG_PCALL
        if (loglevel & CPU_LOG_PCALL) {
            fprintf(logfile, "new ss:esp=%04x:%08x\n",
                    new_ss, new_esp);
        }
#endif
        
        if ((new_ss & 3) != rpl)
            raise_exception_err(EXCP0D_GPF, new_ss & 0xfffc);
        if (load_segment(&ss_e1, &ss_e2, new_ss) != 0)
            raise_exception_err(EXCP0D_GPF, new_ss & 0xfffc);
        if (!(ss_e2 & DESC_S_MASK) ||
            (ss_e2 & DESC_CS_MASK) ||
            !(ss_e2 & DESC_W_MASK))
            raise_exception_err(EXCP0D_GPF, new_ss & 0xfffc);
        dpl = (ss_e2 >> DESC_DPL_SHIFT) & 3;
        if (dpl != rpl)
            raise_exception_err(EXCP0D_GPF, new_ss & 0xfffc);
        if (!(ss_e2 & DESC_P_MASK))
            raise_exception_err(EXCP0B_NOSEG, new_ss & 0xfffc);

        cpu_x86_load_seg_cache(env, R_CS, new_cs, 
                       get_seg_base(e1, e2),
                       get_seg_limit(e1, e2),
                       e2);
        cpu_x86_load_seg_cache(env, R_SS, new_ss, 
                       get_seg_base(ss_e1, ss_e2),
                       get_seg_limit(ss_e1, ss_e2),
                       ss_e2);
        cpu_x86_set_cpl(env, rpl);
        sp = new_esp;
        sp_mask = get_sp_mask(ss_e2);

        /* validate data segments */
        validate_seg(R_ES, cpl);
        validate_seg(R_DS, cpl);
        validate_seg(R_FS, cpl);
        validate_seg(R_GS, cpl);

        sp += addend;
    }
    ESP = (ESP & ~sp_mask) | (sp & sp_mask);
    env->eip = new_eip;
    if (is_iret) {
        /* NOTE: 'cpl' is the _old_ CPL */
        eflags_mask = TF_MASK | AC_MASK | ID_MASK | RF_MASK | NT_MASK;
        if (cpl == 0)
            eflags_mask |= IOPL_MASK;
        iopl = (env->eflags >> IOPL_SHIFT) & 3;
        if (cpl <= iopl)
            eflags_mask |= IF_MASK;
        if (shift == 0)
            eflags_mask &= 0xffff;
        load_eflags(new_eflags, eflags_mask);
    }
    return;

 return_to_vm86:
    POPL(ssp, sp, sp_mask, new_esp);
    POPL(ssp, sp, sp_mask, new_ss);
    POPL(ssp, sp, sp_mask, new_es);
    POPL(ssp, sp, sp_mask, new_ds);
    POPL(ssp, sp, sp_mask, new_fs);
    POPL(ssp, sp, sp_mask, new_gs);
    
    /* modify processor state */
    load_eflags(new_eflags, TF_MASK | AC_MASK | ID_MASK | 
                IF_MASK | IOPL_MASK | VM_MASK | NT_MASK | VIF_MASK | VIP_MASK);
    load_seg_vm(R_CS, new_cs & 0xffff);
    cpu_x86_set_cpl(env, 3);
    load_seg_vm(R_SS, new_ss & 0xffff);
    load_seg_vm(R_ES, new_es & 0xffff);
    load_seg_vm(R_DS, new_ds & 0xffff);
    load_seg_vm(R_FS, new_fs & 0xffff);
    load_seg_vm(R_GS, new_gs & 0xffff);

    env->eip = new_eip & 0xffff;
    ESP = new_esp;
}

void helper_iret_protected(int shift, int next_eip)
{
    int tss_selector, type;
    uint32_t e1, e2;
    
    /* specific case for TSS */
    if (env->eflags & NT_MASK) {
        tss_selector = lduw_kernel(env->tr.base + 0);
        if (tss_selector & 4)
            raise_exception_err(EXCP0A_TSS, tss_selector & 0xfffc);
        if (load_segment(&e1, &e2, tss_selector) != 0)
            raise_exception_err(EXCP0A_TSS, tss_selector & 0xfffc);
        type = (e2 >> DESC_TYPE_SHIFT) & 0x17;
        /* NOTE: we check both segment and busy TSS */
        if (type != 3)
            raise_exception_err(EXCP0A_TSS, tss_selector & 0xfffc);
        switch_tss(tss_selector, e1, e2, SWITCH_TSS_IRET, next_eip);
    } else {
        helper_ret_protected(shift, 1, 0);
    }
}

void helper_lret_protected(int shift, int addend)
{
    helper_ret_protected(shift, 0, addend);
}

void helper_sysenter(void)
{
    if (env->sysenter_cs == 0) {
        raise_exception_err(EXCP0D_GPF, 0);
    }
    env->eflags &= ~(VM_MASK | IF_MASK | RF_MASK);
    cpu_x86_set_cpl(env, 0);
    cpu_x86_load_seg_cache(env, R_CS, env->sysenter_cs & 0xfffc, 
                           NULL, 0xffffffff, 
                           DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                           DESC_S_MASK |
                           DESC_CS_MASK | DESC_R_MASK | DESC_A_MASK);
    cpu_x86_load_seg_cache(env, R_SS, (env->sysenter_cs + 8) & 0xfffc, 
                           NULL, 0xffffffff,
                           DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                           DESC_S_MASK |
                           DESC_W_MASK | DESC_A_MASK);
    ESP = env->sysenter_esp;
    EIP = env->sysenter_eip;
}

void helper_sysexit(void)
{
    int cpl;

    cpl = env->hflags & HF_CPL_MASK;
    if (env->sysenter_cs == 0 || cpl != 0) {
        raise_exception_err(EXCP0D_GPF, 0);
    }
    cpu_x86_set_cpl(env, 3);
    cpu_x86_load_seg_cache(env, R_CS, ((env->sysenter_cs + 16) & 0xfffc) | 3, 
                           NULL, 0xffffffff, 
                           DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                           DESC_S_MASK | (3 << DESC_DPL_SHIFT) |
                           DESC_CS_MASK | DESC_R_MASK | DESC_A_MASK);
    cpu_x86_load_seg_cache(env, R_SS, ((env->sysenter_cs + 24) & 0xfffc) | 3, 
                           NULL, 0xffffffff,
                           DESC_G_MASK | DESC_B_MASK | DESC_P_MASK |
                           DESC_S_MASK | (3 << DESC_DPL_SHIFT) |
                           DESC_W_MASK | DESC_A_MASK);
    ESP = ECX;
    EIP = EDX;
}

void helper_movl_crN_T0(int reg)
{
    switch(reg) {
    case 0:
        cpu_x86_update_cr0(env, T0);
        break;
    case 3:
        cpu_x86_update_cr3(env, T0);
        break;
    case 4:
        cpu_x86_update_cr4(env, T0);
        break;
    default:
        env->cr[reg] = T0;
        break;
    }
}

/* XXX: do more */
void helper_movl_drN_T0(int reg)
{
    env->dr[reg] = T0;
}

void helper_invlpg(unsigned int addr)
{
    cpu_x86_flush_tlb(env, addr);
}

void helper_rdtsc(void)
{
    uint64_t val;
    
    val = cpu_get_tsc(env);
    EAX = val;
    EDX = val >> 32;
}

void helper_wrmsr(void)
{
    switch(ECX) {
    case MSR_IA32_SYSENTER_CS:
        env->sysenter_cs = EAX & 0xffff;
        break;
    case MSR_IA32_SYSENTER_ESP:
        env->sysenter_esp = EAX;
        break;
    case MSR_IA32_SYSENTER_EIP:
        env->sysenter_eip = EAX;
        break;
    default:
        /* XXX: exception ? */
        break; 
    }
}

void helper_rdmsr(void)
{
    switch(ECX) {
    case MSR_IA32_SYSENTER_CS:
        EAX = env->sysenter_cs;
        EDX = 0;
        break;
    case MSR_IA32_SYSENTER_ESP:
        EAX = env->sysenter_esp;
        EDX = 0;
        break;
    case MSR_IA32_SYSENTER_EIP:
        EAX = env->sysenter_eip;
        EDX = 0;
        break;
    default:
        /* XXX: exception ? */
        break; 
    }
}

void helper_lsl(void)
{
    unsigned int selector, limit;
    uint32_t e1, e2;
    int rpl, dpl, cpl, type;

    CC_SRC = cc_table[CC_OP].compute_all() & ~CC_Z;
    selector = T0 & 0xffff;
    if (load_segment(&e1, &e2, selector) != 0)
        return;
    rpl = selector & 3;
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    cpl = env->hflags & HF_CPL_MASK;
    if (e2 & DESC_S_MASK) {
        if ((e2 & DESC_CS_MASK) && (e2 & DESC_C_MASK)) {
            /* conforming */
        } else {
            if (dpl < cpl || dpl < rpl)
                return;
        }
    } else {
        type = (e2 >> DESC_TYPE_SHIFT) & 0xf;
        switch(type) {
        case 1:
        case 2:
        case 3:
        case 9:
        case 11:
            break;
        default:
            return;
        }
        if (dpl < cpl || dpl < rpl)
            return;
    }
    limit = get_seg_limit(e1, e2);
    T1 = limit;
    CC_SRC |= CC_Z;
}

void helper_lar(void)
{
    unsigned int selector;
    uint32_t e1, e2;
    int rpl, dpl, cpl, type;

    CC_SRC = cc_table[CC_OP].compute_all() & ~CC_Z;
    selector = T0 & 0xffff;
    if ((selector & 0xfffc) == 0)
        return;
    if (load_segment(&e1, &e2, selector) != 0)
        return;
    rpl = selector & 3;
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    cpl = env->hflags & HF_CPL_MASK;
    if (e2 & DESC_S_MASK) {
        if ((e2 & DESC_CS_MASK) && (e2 & DESC_C_MASK)) {
            /* conforming */
        } else {
            if (dpl < cpl || dpl < rpl)
                return;
        }
    } else {
        type = (e2 >> DESC_TYPE_SHIFT) & 0xf;
        switch(type) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 9:
        case 11:
        case 12:
            break;
        default:
            return;
        }
        if (dpl < cpl || dpl < rpl)
            return;
    }
    T1 = e2 & 0x00f0ff00;
    CC_SRC |= CC_Z;
}

void helper_verr(void)
{
    unsigned int selector;
    uint32_t e1, e2;
    int rpl, dpl, cpl;

    CC_SRC = cc_table[CC_OP].compute_all() & ~CC_Z;
    selector = T0 & 0xffff;
    if ((selector & 0xfffc) == 0)
        return;
    if (load_segment(&e1, &e2, selector) != 0)
        return;
    if (!(e2 & DESC_S_MASK))
        return;
    rpl = selector & 3;
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    cpl = env->hflags & HF_CPL_MASK;
    if (e2 & DESC_CS_MASK) {
        if (!(e2 & DESC_R_MASK))
            return;
        if (!(e2 & DESC_C_MASK)) {
            if (dpl < cpl || dpl < rpl)
                return;
        }
    } else {
        if (dpl < cpl || dpl < rpl)
            return;
    }
    CC_SRC |= CC_Z;
}

void helper_verw(void)
{
    unsigned int selector;
    uint32_t e1, e2;
    int rpl, dpl, cpl;

    CC_SRC = cc_table[CC_OP].compute_all() & ~CC_Z;
    selector = T0 & 0xffff;
    if ((selector & 0xfffc) == 0)
        return;
    if (load_segment(&e1, &e2, selector) != 0)
        return;
    if (!(e2 & DESC_S_MASK))
        return;
    rpl = selector & 3;
    dpl = (e2 >> DESC_DPL_SHIFT) & 3;
    cpl = env->hflags & HF_CPL_MASK;
    if (e2 & DESC_CS_MASK) {
        return;
    } else {
        if (dpl < cpl || dpl < rpl)
            return;
        if (!(e2 & DESC_W_MASK))
            return;
    }
    CC_SRC |= CC_Z;
}

/* FPU helpers */

void helper_fldt_ST0_A0(void)
{
    int new_fpstt;
    new_fpstt = (env->fpstt - 1) & 7;
    env->fpregs[new_fpstt] = helper_fldt((uint8_t *)A0);
    env->fpstt = new_fpstt;
    env->fptags[new_fpstt] = 0; /* validate stack entry */
}

void helper_fstt_ST0_A0(void)
{
    helper_fstt(ST0, (uint8_t *)A0);
}

void fpu_set_exception(int mask)
{
    env->fpus |= mask;
    if (env->fpus & (~env->fpuc & FPUC_EM))
        env->fpus |= FPUS_SE | FPUS_B;
}

CPU86_LDouble helper_fdiv(CPU86_LDouble a, CPU86_LDouble b)
{
    if (b == 0.0) 
        fpu_set_exception(FPUS_ZE);
    return a / b;
}

void fpu_raise_exception(void)
{
    if (env->cr[0] & CR0_NE_MASK) {
        raise_exception(EXCP10_COPR);
    } 
#if !defined(CONFIG_USER_ONLY) 
    else {
        cpu_set_ferr(env);
    }
#endif
}

/* BCD ops */

void helper_fbld_ST0_A0(void)
{
    CPU86_LDouble tmp;
    uint64_t val;
    unsigned int v;
    int i;

    val = 0;
    for(i = 8; i >= 0; i--) {
        v = ldub((uint8_t *)A0 + i);
        val = (val * 100) + ((v >> 4) * 10) + (v & 0xf);
    }
    tmp = val;
    if (ldub((uint8_t *)A0 + 9) & 0x80)
        tmp = -tmp;
    fpush();
    ST0 = tmp;
}

void helper_fbst_ST0_A0(void)
{
    CPU86_LDouble tmp;
    int v;
    uint8_t *mem_ref, *mem_end;
    int64_t val;

    tmp = rint(ST0);
    val = (int64_t)tmp;
    mem_ref = (uint8_t *)A0;
    mem_end = mem_ref + 9;
    if (val < 0) {
        stb(mem_end, 0x80);
        val = -val;
    } else {
        stb(mem_end, 0x00);
    }
    while (mem_ref < mem_end) {
        if (val == 0)
            break;
        v = val % 100;
        val = val / 100;
        v = ((v / 10) << 4) | (v % 10);
        stb(mem_ref++, v);
    }
    while (mem_ref < mem_end) {
        stb(mem_ref++, 0);
    }
}

void helper_f2xm1(void)
{
    ST0 = pow(2.0,ST0) - 1.0;
}

void helper_fyl2x(void)
{
    CPU86_LDouble fptemp;
    
    fptemp = ST0;
    if (fptemp>0.0){
        fptemp = log(fptemp)/log(2.0);	 /* log2(ST) */
        ST1 *= fptemp;
        fpop();
    } else { 
        env->fpus &= (~0x4700);
        env->fpus |= 0x400;
    }
}

void helper_fptan(void)
{
    CPU86_LDouble fptemp;

    fptemp = ST0;
    if((fptemp > MAXTAN)||(fptemp < -MAXTAN)) {
        env->fpus |= 0x400;
    } else {
        ST0 = tan(fptemp);
        fpush();
        ST0 = 1.0;
        env->fpus &= (~0x400);  /* C2 <-- 0 */
        /* the above code is for  |arg| < 2**52 only */
    }
}

void helper_fpatan(void)
{
    CPU86_LDouble fptemp, fpsrcop;

    fpsrcop = ST1;
    fptemp = ST0;
    ST1 = atan2(fpsrcop,fptemp);
    fpop();
}

void helper_fxtract(void)
{
    CPU86_LDoubleU temp;
    unsigned int expdif;

    temp.d = ST0;
    expdif = EXPD(temp) - EXPBIAS;
    /*DP exponent bias*/
    ST0 = expdif;
    fpush();
    BIASEXPONENT(temp);
    ST0 = temp.d;
}

void helper_fprem1(void)
{
    CPU86_LDouble dblq, fpsrcop, fptemp;
    CPU86_LDoubleU fpsrcop1, fptemp1;
    int expdif;
    int q;

    fpsrcop = ST0;
    fptemp = ST1;
    fpsrcop1.d = fpsrcop;
    fptemp1.d = fptemp;
    expdif = EXPD(fpsrcop1) - EXPD(fptemp1);
    if (expdif < 53) {
        dblq = fpsrcop / fptemp;
        dblq = (dblq < 0.0)? ceil(dblq): floor(dblq);
        ST0 = fpsrcop - fptemp*dblq;
        q = (int)dblq; /* cutting off top bits is assumed here */
        env->fpus &= (~0x4700); /* (C3,C2,C1,C0) <-- 0000 */
				/* (C0,C1,C3) <-- (q2,q1,q0) */
        env->fpus |= (q&0x4) << 6; /* (C0) <-- q2 */
        env->fpus |= (q&0x2) << 8; /* (C1) <-- q1 */
        env->fpus |= (q&0x1) << 14; /* (C3) <-- q0 */
    } else {
        env->fpus |= 0x400;  /* C2 <-- 1 */
        fptemp = pow(2.0, expdif-50);
        fpsrcop = (ST0 / ST1) / fptemp;
        /* fpsrcop = integer obtained by rounding to the nearest */
        fpsrcop = (fpsrcop-floor(fpsrcop) < ceil(fpsrcop)-fpsrcop)?
            floor(fpsrcop): ceil(fpsrcop);
        ST0 -= (ST1 * fpsrcop * fptemp);
    }
}

void helper_fprem(void)
{
    CPU86_LDouble dblq, fpsrcop, fptemp;
    CPU86_LDoubleU fpsrcop1, fptemp1;
    int expdif;
    int q;
    
    fpsrcop = ST0;
    fptemp = ST1;
    fpsrcop1.d = fpsrcop;
    fptemp1.d = fptemp;
    expdif = EXPD(fpsrcop1) - EXPD(fptemp1);
    if ( expdif < 53 ) {
        dblq = fpsrcop / fptemp;
        dblq = (dblq < 0.0)? ceil(dblq): floor(dblq);
        ST0 = fpsrcop - fptemp*dblq;
        q = (int)dblq; /* cutting off top bits is assumed here */
        env->fpus &= (~0x4700); /* (C3,C2,C1,C0) <-- 0000 */
				/* (C0,C1,C3) <-- (q2,q1,q0) */
        env->fpus |= (q&0x4) << 6; /* (C0) <-- q2 */
        env->fpus |= (q&0x2) << 8; /* (C1) <-- q1 */
        env->fpus |= (q&0x1) << 14; /* (C3) <-- q0 */
    } else {
        env->fpus |= 0x400;  /* C2 <-- 1 */
        fptemp = pow(2.0, expdif-50);
        fpsrcop = (ST0 / ST1) / fptemp;
        /* fpsrcop = integer obtained by chopping */
        fpsrcop = (fpsrcop < 0.0)?
            -(floor(fabs(fpsrcop))): floor(fpsrcop);
        ST0 -= (ST1 * fpsrcop * fptemp);
    }
}

void helper_fyl2xp1(void)
{
    CPU86_LDouble fptemp;

    fptemp = ST0;
    if ((fptemp+1.0)>0.0) {
        fptemp = log(fptemp+1.0) / log(2.0); /* log2(ST+1.0) */
        ST1 *= fptemp;
        fpop();
    } else { 
        env->fpus &= (~0x4700);
        env->fpus |= 0x400;
    }
}

void helper_fsqrt(void)
{
    CPU86_LDouble fptemp;

    fptemp = ST0;
    if (fptemp<0.0) { 
        env->fpus &= (~0x4700);  /* (C3,C2,C1,C0) <-- 0000 */
        env->fpus |= 0x400;
    }
    ST0 = sqrt(fptemp);
}

void helper_fsincos(void)
{
    CPU86_LDouble fptemp;

    fptemp = ST0;
    if ((fptemp > MAXTAN)||(fptemp < -MAXTAN)) {
        env->fpus |= 0x400;
    } else {
        ST0 = sin(fptemp);
        fpush();
        ST0 = cos(fptemp);
        env->fpus &= (~0x400);  /* C2 <-- 0 */
        /* the above code is for  |arg| < 2**63 only */
    }
}

void helper_frndint(void)
{
    CPU86_LDouble a;

    a = ST0;
#ifdef __arm__
    switch(env->fpuc & RC_MASK) {
    default:
    case RC_NEAR:
        asm("rndd %0, %1" : "=f" (a) : "f"(a));
        break;
    case RC_DOWN:
        asm("rnddm %0, %1" : "=f" (a) : "f"(a));
        break;
    case RC_UP:
        asm("rnddp %0, %1" : "=f" (a) : "f"(a));
        break;
    case RC_CHOP:
        asm("rnddz %0, %1" : "=f" (a) : "f"(a));
        break;
    }
#else
    a = rint(a);
#endif
    ST0 = a;
}

void helper_fscale(void)
{
    CPU86_LDouble fpsrcop, fptemp;

    fpsrcop = 2.0;
    fptemp = pow(fpsrcop,ST1);
    ST0 *= fptemp;
}

void helper_fsin(void)
{
    CPU86_LDouble fptemp;

    fptemp = ST0;
    if ((fptemp > MAXTAN)||(fptemp < -MAXTAN)) {
        env->fpus |= 0x400;
    } else {
        ST0 = sin(fptemp);
        env->fpus &= (~0x400);  /* C2 <-- 0 */
        /* the above code is for  |arg| < 2**53 only */
    }
}

void helper_fcos(void)
{
    CPU86_LDouble fptemp;

    fptemp = ST0;
    if((fptemp > MAXTAN)||(fptemp < -MAXTAN)) {
        env->fpus |= 0x400;
    } else {
        ST0 = cos(fptemp);
        env->fpus &= (~0x400);  /* C2 <-- 0 */
        /* the above code is for  |arg5 < 2**63 only */
    }
}

void helper_fxam_ST0(void)
{
    CPU86_LDoubleU temp;
    int expdif;

    temp.d = ST0;

    env->fpus &= (~0x4700);  /* (C3,C2,C1,C0) <-- 0000 */
    if (SIGND(temp))
        env->fpus |= 0x200; /* C1 <-- 1 */

    expdif = EXPD(temp);
    if (expdif == MAXEXPD) {
        if (MANTD(temp) == 0)
            env->fpus |=  0x500 /*Infinity*/;
        else
            env->fpus |=  0x100 /*NaN*/;
    } else if (expdif == 0) {
        if (MANTD(temp) == 0)
            env->fpus |=  0x4000 /*Zero*/;
        else
            env->fpus |= 0x4400 /*Denormal*/;
    } else {
        env->fpus |= 0x400;
    }
}

void helper_fstenv(uint8_t *ptr, int data32)
{
    int fpus, fptag, exp, i;
    uint64_t mant;
    CPU86_LDoubleU tmp;

    fpus = (env->fpus & ~0x3800) | (env->fpstt & 0x7) << 11;
    fptag = 0;
    for (i=7; i>=0; i--) {
	fptag <<= 2;
	if (env->fptags[i]) {
            fptag |= 3;
	} else {
            tmp.d = env->fpregs[i];
            exp = EXPD(tmp);
            mant = MANTD(tmp);
            if (exp == 0 && mant == 0) {
                /* zero */
	        fptag |= 1;
	    } else if (exp == 0 || exp == MAXEXPD
#ifdef USE_X86LDOUBLE
                       || (mant & (1LL << 63)) == 0
#endif
                       ) {
                /* NaNs, infinity, denormal */
                fptag |= 2;
            }
        }
    }
    if (data32) {
        /* 32 bit */
        stl(ptr, env->fpuc);
        stl(ptr + 4, fpus);
        stl(ptr + 8, fptag);
        stl(ptr + 12, 0); /* fpip */
        stl(ptr + 16, 0); /* fpcs */
        stl(ptr + 20, 0); /* fpoo */
        stl(ptr + 24, 0); /* fpos */
    } else {
        /* 16 bit */
        stw(ptr, env->fpuc);
        stw(ptr + 2, fpus);
        stw(ptr + 4, fptag);
        stw(ptr + 6, 0);
        stw(ptr + 8, 0);
        stw(ptr + 10, 0);
        stw(ptr + 12, 0);
    }
}

void helper_fldenv(uint8_t *ptr, int data32)
{
    int i, fpus, fptag;

    if (data32) {
	env->fpuc = lduw(ptr);
        fpus = lduw(ptr + 4);
        fptag = lduw(ptr + 8);
    }
    else {
	env->fpuc = lduw(ptr);
        fpus = lduw(ptr + 2);
        fptag = lduw(ptr + 4);
    }
    env->fpstt = (fpus >> 11) & 7;
    env->fpus = fpus & ~0x3800;
    for(i = 0;i < 8; i++) {
        env->fptags[i] = ((fptag & 3) == 3);
        fptag >>= 2;
    }
}

void helper_fsave(uint8_t *ptr, int data32)
{
    CPU86_LDouble tmp;
    int i;

    helper_fstenv(ptr, data32);

    ptr += (14 << data32);
    for(i = 0;i < 8; i++) {
        tmp = ST(i);
        helper_fstt(tmp, ptr);
        ptr += 10;
    }

    /* fninit */
    env->fpus = 0;
    env->fpstt = 0;
    env->fpuc = 0x37f;
    env->fptags[0] = 1;
    env->fptags[1] = 1;
    env->fptags[2] = 1;
    env->fptags[3] = 1;
    env->fptags[4] = 1;
    env->fptags[5] = 1;
    env->fptags[6] = 1;
    env->fptags[7] = 1;
}

void helper_frstor(uint8_t *ptr, int data32)
{
    CPU86_LDouble tmp;
    int i;

    helper_fldenv(ptr, data32);
    ptr += (14 << data32);

    for(i = 0;i < 8; i++) {
        tmp = helper_fldt(ptr);
        ST(i) = tmp;
        ptr += 10;
    }
}

/* XXX: merge with helper_fstt ? */

#ifndef USE_X86LDOUBLE

void cpu_get_fp80(uint64_t *pmant, uint16_t *pexp, CPU86_LDouble f)
{
    CPU86_LDoubleU temp;
    int e;

    temp.d = f;
    /* mantissa */
    *pmant = (MANTD(temp) << 11) | (1LL << 63);
    /* exponent + sign */
    e = EXPD(temp) - EXPBIAS + 16383;
    e |= SIGND(temp) >> 16;
    *pexp = e;
}

CPU86_LDouble cpu_set_fp80(uint64_t mant, uint16_t upper)
{
    CPU86_LDoubleU temp;
    int e;
    uint64_t ll;

    /* XXX: handle overflow ? */
    e = (upper & 0x7fff) - 16383 + EXPBIAS; /* exponent */
    e |= (upper >> 4) & 0x800; /* sign */
    ll = (mant >> 11) & ((1LL << 52) - 1);
#ifdef __arm__
    temp.l.upper = (e << 20) | (ll >> 32);
    temp.l.lower = ll;
#else
    temp.ll = ll | ((uint64_t)e << 52);
#endif
    return temp.d;
}

#else

void cpu_get_fp80(uint64_t *pmant, uint16_t *pexp, CPU86_LDouble f)
{
    CPU86_LDoubleU temp;

    temp.d = f;
    *pmant = temp.l.lower;
    *pexp = temp.l.upper;
}

CPU86_LDouble cpu_set_fp80(uint64_t mant, uint16_t upper)
{
    CPU86_LDoubleU temp;

    temp.l.upper = upper;
    temp.l.lower = mant;
    return temp.d;
}
#endif

#if !defined(CONFIG_USER_ONLY) 

#define MMUSUFFIX _mmu
#define GETPC() (__builtin_return_address(0))

#define SHIFT 0
#include "softmmu_template.h"

#define SHIFT 1
#include "softmmu_template.h"

#define SHIFT 2
#include "softmmu_template.h"

#define SHIFT 3
#include "softmmu_template.h"

#endif

/* try to fill the TLB and return an exception if error. If retaddr is
   NULL, it means that the function was called in C code (i.e. not
   from generated code or from helper.c) */
/* XXX: fix it to restore all registers */
void tlb_fill(unsigned long addr, int is_write, int is_user, void *retaddr)
{
    TranslationBlock *tb;
    int ret;
    unsigned long pc;
    CPUX86State *saved_env;

    /* XXX: hack to restore env in all cases, even if not called from
       generated code */
    saved_env = env;
    env = cpu_single_env;

    ret = cpu_x86_handle_mmu_fault(env, addr, is_write, is_user, 1);
    if (ret) {
        if (retaddr) {
            /* now we have a real cpu fault */
            pc = (unsigned long)retaddr;
            tb = tb_find_pc(pc);
            if (tb) {
                /* the PC is inside the translated code. It means that we have
                   a virtual CPU fault */
                cpu_restore_state(tb, env, pc, NULL);
            }
        }
        raise_exception_err(EXCP0E_PAGE, env->error_code);
    }
    env = saved_env;
}
