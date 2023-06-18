/*
 *  i386 translation
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
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <signal.h>
#include <assert.h>

#define DEBUG_DISAS

#define IN_OP_I386
#include "cpu-i386.h"

/* dump all code */
#ifdef DEBUG_DISAS
#include "dis-asm.h"
#endif

#ifndef offsetof
#define offsetof(type, field) ((size_t) &((type *)0)->field)
#endif

/* XXX: move that elsewhere */
static uint16_t *gen_opc_ptr;
static uint32_t *gen_opparam_ptr;
int __op_param1, __op_param2, __op_param3;

#ifdef __i386__
static inline void flush_icache_range(unsigned long start, unsigned long stop)
{
}
#endif

#ifdef __s390__
static inline void flush_icache_range(unsigned long start, unsigned long stop)
{
}
#endif

#ifdef __powerpc__

#define MIN_CACHE_LINE_SIZE 8 /* conservative value */

static void inline flush_icache_range(unsigned long start, unsigned long stop)
{
    unsigned long p;

    p = start & ~(MIN_CACHE_LINE_SIZE - 1);
    stop = (stop + MIN_CACHE_LINE_SIZE - 1) & ~(MIN_CACHE_LINE_SIZE - 1);

    for (p = start; p < stop; p += MIN_CACHE_LINE_SIZE) {
        asm ("dcbst 0,%0;" : : "r"(p) : "memory");
    }
    asm ("sync");
    for (p = start; p < stop; p += MIN_CACHE_LINE_SIZE) {
        asm ("icbi 0,%0; sync;" : : "r"(p) : "memory");
    }
    asm ("sync");
    asm ("isync");
}
#endif

extern FILE *logfile;
extern int loglevel;

#define PREFIX_REPZ   0x01
#define PREFIX_REPNZ  0x02
#define PREFIX_LOCK   0x04
#define PREFIX_DATA   0x08
#define PREFIX_ADR    0x10
#define PREFIX_FWAIT  0x20

/* 指令上下文 */
typedef struct DisasContext {
    /* current insn context */
    int override; /* -1 if no override */
    int prefix;
    int aflag, dflag;
    uint8_t *pc; /* pc = eip + cs_base */
    int is_jmp; /* 1 = means jump (stop translation), 2 means CPU
                   static state change (stop translation) */
    /* current block context */
    uint8_t *cs_base; /* base of CS segment */
    int code32; /* 32 bit code segment */
    int ss32;   /* 32 bit stack segment */
    int cc_op;  /* current CC operation */
    int addseg; /* non zero if either DS/ES/SS have a non zero base */
    int f_st;   /* currently unused */
    int vm86;   /* vm86 mode */
} DisasContext;

/* i386 arith/logic operations */
enum {
    OP_ADDL,
    OP_ORL,
    OP_ADCL,
    OP_SBBL,
    OP_ANDL,
    OP_SUBL,
    OP_XORL,
    OP_CMPL,
};

/* i386 shift ops */
enum {
    OP_ROL,
    OP_ROR,
    OP_RCL,
    OP_RCR,
    OP_SHL,
    OP_SHR,
    OP_SHL1, /* undocumented */
    OP_SAR = 7,
};

enum {
#define DEF(s, n) INDEX_op_ ## s,
#include "opc-i386.h"
#undef DEF
    NB_OPS,
};

#include "op-i386.h"

/* operand size */
/* 操作数大小 */
enum {
    OT_BYTE = 0,
    OT_WORD,
    OT_LONG,
    OT_QUAD,
};

enum {
    /* I386 int registers */
    OR_EAX,   /* MUST be even numbered */
    OR_ECX,
    OR_EDX,
    OR_EBX,
    OR_ESP,
    OR_EBP,
    OR_ESI,
    OR_EDI,
    OR_TMP0,    /* temporary operand register */
    OR_TMP1,
    OR_A0, /* temporary register used when doing address evaluation */
    OR_ZERO, /* fixed zero register */
    NB_OREGS,
};

typedef void (GenOpFunc)(void);
typedef void (GenOpFunc1)(long);
typedef void (GenOpFunc2)(long, long);

static GenOpFunc *gen_op_mov_reg_T0[3][8] = {
    [OT_BYTE] = {
        gen_op_movb_EAX_T0,
        gen_op_movb_ECX_T0,
        gen_op_movb_EDX_T0,
        gen_op_movb_EBX_T0,
        gen_op_movh_EAX_T0,
        gen_op_movh_ECX_T0,
        gen_op_movh_EDX_T0,
        gen_op_movh_EBX_T0,
    },
    [OT_WORD] = {
        gen_op_movw_EAX_T0,
        gen_op_movw_ECX_T0,
        gen_op_movw_EDX_T0,
        gen_op_movw_EBX_T0,
        gen_op_movw_ESP_T0,
        gen_op_movw_EBP_T0,
        gen_op_movw_ESI_T0,
        gen_op_movw_EDI_T0,
    },
    [OT_LONG] = {
        gen_op_movl_EAX_T0,
        gen_op_movl_ECX_T0,
        gen_op_movl_EDX_T0,
        gen_op_movl_EBX_T0,
        gen_op_movl_ESP_T0,
        gen_op_movl_EBP_T0,
        gen_op_movl_ESI_T0,
        gen_op_movl_EDI_T0,
    },
};
/* 将T1寄存器的值移动到对应的寄存器之中 */
static GenOpFunc *gen_op_mov_reg_T1[3][8] = {
    [OT_BYTE] = {
        gen_op_movb_EAX_T1,
        gen_op_movb_ECX_T1,
        gen_op_movb_EDX_T1,
        gen_op_movb_EBX_T1,
        gen_op_movh_EAX_T1,
        gen_op_movh_ECX_T1,
        gen_op_movh_EDX_T1,
        gen_op_movh_EBX_T1,
    },
    [OT_WORD] = {
        gen_op_movw_EAX_T1,
        gen_op_movw_ECX_T1,
        gen_op_movw_EDX_T1,
        gen_op_movw_EBX_T1,
        gen_op_movw_ESP_T1,
        gen_op_movw_EBP_T1,
        gen_op_movw_ESI_T1,
        gen_op_movw_EDI_T1,
    },
    [OT_LONG] = {
        gen_op_movl_EAX_T1,
        gen_op_movl_ECX_T1,
        gen_op_movl_EDX_T1,
        gen_op_movl_EBX_T1,
        gen_op_movl_ESP_T1,
        gen_op_movl_EBP_T1,
        gen_op_movl_ESI_T1,
        gen_op_movl_EDI_T1,
    },
};

static GenOpFunc *gen_op_mov_reg_A0[2][8] = {
    [0] = {
        gen_op_movw_EAX_A0,
        gen_op_movw_ECX_A0,
        gen_op_movw_EDX_A0,
        gen_op_movw_EBX_A0,
        gen_op_movw_ESP_A0,
        gen_op_movw_EBP_A0,
        gen_op_movw_ESI_A0,
        gen_op_movw_EDI_A0,
    },
    [1] = {
        gen_op_movl_EAX_A0,
        gen_op_movl_ECX_A0,
        gen_op_movl_EDX_A0,
        gen_op_movl_EBX_A0,
        gen_op_movl_ESP_A0,
        gen_op_movl_EBP_A0,
        gen_op_movl_ESI_A0,
        gen_op_movl_EDI_A0,
    },
};

static GenOpFunc *gen_op_mov_TN_reg[3][2][8] =
{
    [OT_BYTE] = {
        {
            gen_op_movl_T0_EAX,
            gen_op_movl_T0_ECX,
            gen_op_movl_T0_EDX,
            gen_op_movl_T0_EBX,
            gen_op_movh_T0_EAX,
            gen_op_movh_T0_ECX,
            gen_op_movh_T0_EDX,
            gen_op_movh_T0_EBX,
        },
        {
            gen_op_movl_T1_EAX,
            gen_op_movl_T1_ECX,
            gen_op_movl_T1_EDX,
            gen_op_movl_T1_EBX,
            gen_op_movh_T1_EAX,
            gen_op_movh_T1_ECX,
            gen_op_movh_T1_EDX,
            gen_op_movh_T1_EBX,
        },
    },
    [OT_WORD] = {
        {
            gen_op_movl_T0_EAX,
            gen_op_movl_T0_ECX,
            gen_op_movl_T0_EDX,
            gen_op_movl_T0_EBX,
            gen_op_movl_T0_ESP,
            gen_op_movl_T0_EBP,
            gen_op_movl_T0_ESI,
            gen_op_movl_T0_EDI,
        },
        {
            gen_op_movl_T1_EAX,
            gen_op_movl_T1_ECX,
            gen_op_movl_T1_EDX,
            gen_op_movl_T1_EBX,
            gen_op_movl_T1_ESP,
            gen_op_movl_T1_EBP,
            gen_op_movl_T1_ESI,
            gen_op_movl_T1_EDI,
        },
    },
    [OT_LONG] = {
        {
            gen_op_movl_T0_EAX,
            gen_op_movl_T0_ECX,
            gen_op_movl_T0_EDX,
            gen_op_movl_T0_EBX,
            gen_op_movl_T0_ESP,
            gen_op_movl_T0_EBP,
            gen_op_movl_T0_ESI,
            gen_op_movl_T0_EDI,
        },
        {
            gen_op_movl_T1_EAX,
            gen_op_movl_T1_ECX,
            gen_op_movl_T1_EDX,
            gen_op_movl_T1_EBX,
            gen_op_movl_T1_ESP,
            gen_op_movl_T1_EBP,
            gen_op_movl_T1_ESI,
            gen_op_movl_T1_EDI,
        },
    },
};

static GenOpFunc *gen_op_movl_A0_reg[8] = {
    gen_op_movl_A0_EAX,
    gen_op_movl_A0_ECX,
    gen_op_movl_A0_EDX,
    gen_op_movl_A0_EBX,
    gen_op_movl_A0_ESP,
    gen_op_movl_A0_EBP,
    gen_op_movl_A0_ESI,
    gen_op_movl_A0_EDI,
};

static GenOpFunc *gen_op_addl_A0_reg_sN[4][8] = {
    [0] = {
        gen_op_addl_A0_EAX,
        gen_op_addl_A0_ECX,
        gen_op_addl_A0_EDX,
        gen_op_addl_A0_EBX,
        gen_op_addl_A0_ESP,
        gen_op_addl_A0_EBP,
        gen_op_addl_A0_ESI,
        gen_op_addl_A0_EDI,
    },
    [1] = {
        gen_op_addl_A0_EAX_s1,
        gen_op_addl_A0_ECX_s1,
        gen_op_addl_A0_EDX_s1,
        gen_op_addl_A0_EBX_s1,
        gen_op_addl_A0_ESP_s1,
        gen_op_addl_A0_EBP_s1,
        gen_op_addl_A0_ESI_s1,
        gen_op_addl_A0_EDI_s1,
    },
    [2] = {
        gen_op_addl_A0_EAX_s2,
        gen_op_addl_A0_ECX_s2,
        gen_op_addl_A0_EDX_s2,
        gen_op_addl_A0_EBX_s2,
        gen_op_addl_A0_ESP_s2,
        gen_op_addl_A0_EBP_s2,
        gen_op_addl_A0_ESI_s2,
        gen_op_addl_A0_EDI_s2,
    },
    [3] = {
        gen_op_addl_A0_EAX_s3,
        gen_op_addl_A0_ECX_s3,
        gen_op_addl_A0_EDX_s3,
        gen_op_addl_A0_EBX_s3,
        gen_op_addl_A0_ESP_s3,
        gen_op_addl_A0_EBP_s3,
        gen_op_addl_A0_ESI_s3,
        gen_op_addl_A0_EDI_s3,
    },
};

static GenOpFunc *gen_op_cmov_reg_T1_T0[2][8] = {
    [0] = {
        gen_op_cmovw_EAX_T1_T0,
        gen_op_cmovw_ECX_T1_T0,
        gen_op_cmovw_EDX_T1_T0,
        gen_op_cmovw_EBX_T1_T0,
        gen_op_cmovw_ESP_T1_T0,
        gen_op_cmovw_EBP_T1_T0,
        gen_op_cmovw_ESI_T1_T0,
        gen_op_cmovw_EDI_T1_T0,
    },
    [1] = {
        gen_op_cmovl_EAX_T1_T0,
        gen_op_cmovl_ECX_T1_T0,
        gen_op_cmovl_EDX_T1_T0,
        gen_op_cmovl_EBX_T1_T0,
        gen_op_cmovl_ESP_T1_T0,
        gen_op_cmovl_EBP_T1_T0,
        gen_op_cmovl_ESI_T1_T0,
        gen_op_cmovl_EDI_T1_T0,
    },
};

static GenOpFunc *gen_op_arith_T0_T1_cc[8] = {
    gen_op_addl_T0_T1_cc,
    gen_op_orl_T0_T1_cc,
    NULL,
    NULL,
    gen_op_andl_T0_T1_cc,
    gen_op_subl_T0_T1_cc,
    gen_op_xorl_T0_T1_cc,
    gen_op_cmpl_T0_T1_cc,
};

static GenOpFunc *gen_op_arithc_T0_T1_cc[3][2] = {
    [OT_BYTE] = {
        gen_op_adcb_T0_T1_cc,
        gen_op_sbbb_T0_T1_cc,
    },
    [OT_WORD] = {
        gen_op_adcw_T0_T1_cc,
        gen_op_sbbw_T0_T1_cc,
    },
    [OT_LONG] = {
        gen_op_adcl_T0_T1_cc,
        gen_op_sbbl_T0_T1_cc,
    },
};

static const int cc_op_arithb[8] = {
    CC_OP_ADDB,
    CC_OP_LOGICB,
    CC_OP_ADDB,
    CC_OP_SUBB,
    CC_OP_LOGICB,
    CC_OP_SUBB,
    CC_OP_LOGICB,
    CC_OP_SUBB,
};

static GenOpFunc *gen_op_cmpxchg_T0_T1_EAX_cc[3] = {
    gen_op_cmpxchgb_T0_T1_EAX_cc,
    gen_op_cmpxchgw_T0_T1_EAX_cc,
    gen_op_cmpxchgl_T0_T1_EAX_cc,
};

static GenOpFunc *gen_op_shift_T0_T1_cc[3][8] = {
    [OT_BYTE] = {
        gen_op_rolb_T0_T1_cc,
        gen_op_rorb_T0_T1_cc,
        gen_op_rclb_T0_T1_cc,
        gen_op_rcrb_T0_T1_cc,
        gen_op_shlb_T0_T1_cc,
        gen_op_shrb_T0_T1_cc,
        gen_op_shlb_T0_T1_cc,
        gen_op_sarb_T0_T1_cc,
    },
    [OT_WORD] = {
        gen_op_rolw_T0_T1_cc,
        gen_op_rorw_T0_T1_cc,
        gen_op_rclw_T0_T1_cc,
        gen_op_rcrw_T0_T1_cc,
        gen_op_shlw_T0_T1_cc,
        gen_op_shrw_T0_T1_cc,
        gen_op_shlw_T0_T1_cc,
        gen_op_sarw_T0_T1_cc,
    },
    [OT_LONG] = {
        gen_op_roll_T0_T1_cc,
        gen_op_rorl_T0_T1_cc,
        gen_op_rcll_T0_T1_cc,
        gen_op_rcrl_T0_T1_cc,
        gen_op_shll_T0_T1_cc,
        gen_op_shrl_T0_T1_cc,
        gen_op_shll_T0_T1_cc,
        gen_op_sarl_T0_T1_cc,
    },
};

static GenOpFunc1 *gen_op_shiftd_T0_T1_im_cc[2][2] = {
    [0] = {
        gen_op_shldw_T0_T1_im_cc,
        gen_op_shrdw_T0_T1_im_cc,
    },
    [1] = {
        gen_op_shldl_T0_T1_im_cc,
        gen_op_shrdl_T0_T1_im_cc,
    },
};

static GenOpFunc *gen_op_shiftd_T0_T1_ECX_cc[2][2] = {
    [0] = {
        gen_op_shldw_T0_T1_ECX_cc,
        gen_op_shrdw_T0_T1_ECX_cc,
    },
    [1] = {
        gen_op_shldl_T0_T1_ECX_cc,
        gen_op_shrdl_T0_T1_ECX_cc,
    },
};

static GenOpFunc *gen_op_btx_T0_T1_cc[2][4] = {
    [0] = {
        gen_op_btw_T0_T1_cc,
        gen_op_btsw_T0_T1_cc,
        gen_op_btrw_T0_T1_cc,
        gen_op_btcw_T0_T1_cc,
    },
    [1] = {
        gen_op_btl_T0_T1_cc,
        gen_op_btsl_T0_T1_cc,
        gen_op_btrl_T0_T1_cc,
        gen_op_btcl_T0_T1_cc,
    },
};

static GenOpFunc *gen_op_bsx_T0_cc[2][2] = {
    [0] = {
        gen_op_bsfw_T0_cc,
        gen_op_bsrw_T0_cc,
    },
    [1] = {
        gen_op_bsfl_T0_cc,
        gen_op_bsrl_T0_cc,
    },
};

static GenOpFunc *gen_op_lds_T0_A0[3] = {
    gen_op_ldsb_T0_A0,
    gen_op_ldsw_T0_A0,
};

static GenOpFunc *gen_op_ldu_T0_A0[3] = {
    gen_op_ldub_T0_A0,
    gen_op_lduw_T0_A0,
};

/* sign does not matter */
static GenOpFunc *gen_op_ld_T0_A0[3] = {
    gen_op_ldub_T0_A0, /*   1 */
    gen_op_lduw_T0_A0, /* 2 */
    gen_op_ldl_T0_A0,    /* 4 */
};

static GenOpFunc *gen_op_ld_T1_A0[3] = {
    gen_op_ldub_T1_A0,
    gen_op_lduw_T1_A0,
    gen_op_ldl_T1_A0,
};

static GenOpFunc *gen_op_st_T0_A0[3] = {
    gen_op_stb_T0_A0,
    gen_op_stw_T0_A0,
    gen_op_stl_T0_A0,
};

/* the _a32 and _a16 string operations use A0 as the base register. */

#define STRINGOP(x) \
    gen_op_ ## x ## b_fast, \
    gen_op_ ## x ## w_fast, \
    gen_op_ ## x ## l_fast, \
    gen_op_ ## x ## b_a32, \
    gen_op_ ## x ## w_a32, \
    gen_op_ ## x ## l_a32, \
    gen_op_ ## x ## b_a16, \
    gen_op_ ## x ## w_a16, \
    gen_op_ ## x ## l_a16,

static GenOpFunc *gen_op_movs[9 * 2] = {
    STRINGOP(movs)
    STRINGOP(rep_movs)
};

static GenOpFunc *gen_op_stos[9 * 2] = {
    STRINGOP(stos)
    STRINGOP(rep_stos)
};

static GenOpFunc *gen_op_lods[9 * 2] = {
    STRINGOP(lods)
    STRINGOP(rep_lods)
};

static GenOpFunc *gen_op_scas[9 * 3] = {
    STRINGOP(scas)
    STRINGOP(repz_scas)
    STRINGOP(repnz_scas)
};

static GenOpFunc *gen_op_cmps[9 * 3] = {
    STRINGOP(cmps)
    STRINGOP(repz_cmps)
    STRINGOP(repnz_cmps)
};

static GenOpFunc *gen_op_ins[9 * 2] = {
    STRINGOP(ins)
    STRINGOP(rep_ins)
};


static GenOpFunc *gen_op_outs[9 * 2] = {
    STRINGOP(outs)
    STRINGOP(rep_outs)
};


static inline void gen_string_ds(DisasContext *s, int ot, GenOpFunc **func)
{
    int index, override;

    override = s->override;
    if (s->aflag) {
        /* 32 bit address */
        if (s->addseg && override < 0)
            override = R_DS;
        if (override >= 0) {
            gen_op_movl_A0_seg(offsetof(CPUX86State,seg_cache[override].base));
            index = 3 + ot;
        } else {
            index = ot;
        }
    } else {
        if (override < 0)
            override = R_DS;
        gen_op_movl_A0_seg(offsetof(CPUX86State,seg_cache[override].base));
        /* 16 address, always override */
        index = 6 + ot;
    }
    func[index]();
}

static inline void gen_string_es(DisasContext *s, int ot, GenOpFunc **func)
{
    int index;

    if (s->aflag) {
        if (s->addseg) {
            index = 3 + ot;
        } else {
            index = ot;
        }
    } else {
        index = 6 + ot;
    }
    func[index]();
}


static GenOpFunc *gen_op_in[3] = {
    gen_op_inb_T0_T1,
    gen_op_inw_T0_T1,
    gen_op_inl_T0_T1,
};

static GenOpFunc *gen_op_out[3] = {
    gen_op_outb_T0_T1,
    gen_op_outw_T0_T1,
    gen_op_outl_T0_T1,
};

enum {
    JCC_O,
    JCC_B,
    JCC_Z,
    JCC_BE,
    JCC_S,
    JCC_P,
    JCC_L,
    JCC_LE,
};

static GenOpFunc2 *gen_jcc_slow[8] = {
    gen_op_jo_cc,
    gen_op_jb_cc,
    gen_op_jz_cc,
    gen_op_jbe_cc,
    gen_op_js_cc,
    gen_op_jp_cc,
    gen_op_jl_cc,
    gen_op_jle_cc,
};

static GenOpFunc2 *gen_jcc_sub[3][8] = {
    [OT_BYTE] = {
        NULL,
        gen_op_jb_subb,
        gen_op_jz_subb,
        gen_op_jbe_subb,
        gen_op_js_subb,
        NULL,
        gen_op_jl_subb,
        gen_op_jle_subb,
    },
    [OT_WORD] = {
        NULL,
        gen_op_jb_subw,
        gen_op_jz_subw,
        gen_op_jbe_subw,
        gen_op_js_subw,
        NULL,
        gen_op_jl_subw,
        gen_op_jle_subw,
    },
    [OT_LONG] = {
        NULL,
        gen_op_jb_subl,
        gen_op_jz_subl,
        gen_op_jbe_subl,
        gen_op_js_subl,
        NULL,
        gen_op_jl_subl,
        gen_op_jle_subl,
    },
};
static GenOpFunc2 *gen_op_loop[2][4] = {
    [0] = {
        gen_op_loopnzw,
        gen_op_loopzw,
        gen_op_loopw,
        gen_op_jecxzw,
    },
    [1] = {
        gen_op_loopnzl,
        gen_op_loopzl,
        gen_op_loopl,
        gen_op_jecxzl,
    },
};

static GenOpFunc *gen_setcc_slow[8] = {
    gen_op_seto_T0_cc,
    gen_op_setb_T0_cc,
    gen_op_setz_T0_cc,
    gen_op_setbe_T0_cc,
    gen_op_sets_T0_cc,
    gen_op_setp_T0_cc,
    gen_op_setl_T0_cc,
    gen_op_setle_T0_cc,
};

static GenOpFunc *gen_setcc_sub[3][8] = {
    [OT_BYTE] = {
        NULL,
        gen_op_setb_T0_subb,
        gen_op_setz_T0_subb,
        gen_op_setbe_T0_subb,
        gen_op_sets_T0_subb,
        NULL,
        gen_op_setl_T0_subb,
        gen_op_setle_T0_subb,
    },
    [OT_WORD] = {
        NULL,
        gen_op_setb_T0_subw,
        gen_op_setz_T0_subw,
        gen_op_setbe_T0_subw,
        gen_op_sets_T0_subw,
        NULL,
        gen_op_setl_T0_subw,
        gen_op_setle_T0_subw,
    },
    [OT_LONG] = {
        NULL,
        gen_op_setb_T0_subl,
        gen_op_setz_T0_subl,
        gen_op_setbe_T0_subl,
        gen_op_sets_T0_subl,
        NULL,
        gen_op_setl_T0_subl,
        gen_op_setle_T0_subl,
    },
};

static GenOpFunc *gen_op_fp_arith_ST0_FT0[8] = {
    gen_op_fadd_ST0_FT0,
    gen_op_fmul_ST0_FT0,
    gen_op_fcom_ST0_FT0,
    gen_op_fcom_ST0_FT0,
    gen_op_fsub_ST0_FT0,
    gen_op_fsubr_ST0_FT0,
    gen_op_fdiv_ST0_FT0,
    gen_op_fdivr_ST0_FT0,
};

/* NOTE the exception in "r" op ordering */
static GenOpFunc1 *gen_op_fp_arith_STN_ST0[8] = {
    gen_op_fadd_STN_ST0,
    gen_op_fmul_STN_ST0,
    NULL,
    NULL,
    gen_op_fsubr_STN_ST0,
    gen_op_fsub_STN_ST0,
    gen_op_fdivr_STN_ST0,
    gen_op_fdiv_STN_ST0,
};

/*
 * @param op 操作码
 * @param d 目的
 * @param s 源
 * @param ot 操作数的所占用的长度
 */
static void gen_op(DisasContext *s1, int op, int ot, int d, int s)
{
    if (d != OR_TMP0) /* 将目的操作数移动到T0寄存器 */
        gen_op_mov_TN_reg[ot][0][d]();
    if (s != OR_TMP1) /* 将源操作数移动到T1寄存器 */
        gen_op_mov_TN_reg[ot][1][s]();
    if (op == OP_ADCL || op == OP_SBBL) {
        if (s1->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s1->cc_op);
        gen_op_arithc_T0_T1_cc[ot][op - OP_ADCL]();
        s1->cc_op = CC_OP_DYNAMIC;
    } else {
        gen_op_arith_T0_T1_cc[op]();
        s1->cc_op = cc_op_arithb[op] + ot;
    }
    if (d != OR_TMP0 && op != OP_CMPL)
        gen_op_mov_reg_T0[ot][d]();
}

/* 源操作数为立即数 */
static void gen_opi(DisasContext *s1, int op, int ot, int d, int c)
{
    gen_op_movl_T1_im(c); /* 将立即数移动到T1寄存器 */
    gen_op(s1, op, ot, d, OR_TMP1);
}

/* 自增/自减指令产生代码
 * @param ot 操作数占用字节数
 * @param d 用于指示操作数位于哪一个寄存器之中
 * @param c 增量,可选值有+1,表示自增, -1,表示自减
 */
static void gen_inc(DisasContext *s1, int ot, int d, int c)
{
    if (d != OR_TMP0)
        gen_op_mov_TN_reg[ot][0][d](); /* 移动到T0寄存器, reg由d决定 */
    if (s1->cc_op != CC_OP_DYNAMIC)
        gen_op_set_cc_op(s1->cc_op); /* 需要提前计算eflags */
    if (c > 0) { /* 自增 */
        gen_op_incl_T0_cc();
        s1->cc_op = CC_OP_INCB + ot; /* 更新cc_op */
    } else { /* 自减 */
        gen_op_decl_T0_cc();
        s1->cc_op = CC_OP_DECB + ot;
    }
    if (d != OR_TMP0)
        gen_op_mov_reg_T0[ot][d](); /* 将结果移动到reg寄存器之中,reg由d指定 */
}

static void gen_shift(DisasContext *s1, int op, int ot, int d, int s)
{
    if (d != OR_TMP0)
        gen_op_mov_TN_reg[ot][0][d]();
    if (s != OR_TMP1)
        gen_op_mov_TN_reg[ot][1][s]();
    /* for zero counts, flags are not updated, so must do it dynamically */
    if (s1->cc_op != CC_OP_DYNAMIC)
        gen_op_set_cc_op(s1->cc_op);

    gen_op_shift_T0_T1_cc[ot][op]();

    if (d != OR_TMP0)
        gen_op_mov_reg_T0[ot][d]();
    s1->cc_op = CC_OP_DYNAMIC; /* cannot predict flags after */
}

static void gen_shifti(DisasContext *s1, int op, int ot, int d, int c)
{
    /* currently not optimized */
    gen_op_movl_T1_im(c);
    gen_shift(s1, op, ot, d, OR_TMP1);
}

static void gen_lea_modrm(DisasContext *s, int modrm, int *reg_ptr, int *offset_ptr)
{
    int havesib;
    int base, disp;
    int index;
    int scale;
    int opreg;
    int mod, rm, code, override, must_add_seg;

    override = s->override;
    must_add_seg = s->addseg;
    if (override >= 0)
        must_add_seg = 1;
    mod = (modrm >> 6) & 3;
    rm = modrm & 7;

    if (s->aflag) {

        havesib = 0;
        base = rm;
        index = 0;
        scale = 0;

        if (base == 4) {
            havesib = 1;
            code = ldub(s->pc++);
            scale = (code >> 6) & 3;
            index = (code >> 3) & 7;
            base = code & 7;
        }

        switch (mod) {
        case 0:
            if (base == 5) {
                base = -1;
                disp = ldl(s->pc);
                s->pc += 4;
            } else {
                disp = 0;
            }
            break;
        case 1:
            disp = (int8_t)ldub(s->pc++);
            break;
        default:
        case 2:
            disp = ldl(s->pc);
            s->pc += 4;
            break;
        }

        if (base >= 0) { /* base用于指示寄存器 */
            /* 这里说明一下,i386指令的操作数可能涉及多个寄存器,总之不管怎样,统一加载到A0寄存器 */
            gen_op_movl_A0_reg[base](); /* 将寄存器的值移动到A0寄存器 */
            if (disp != 0)
                gen_op_addl_A0_im(disp); /* A0 + im -> A0 */
        } else {
            gen_op_movl_A0_im(disp); /* A0 + im -> A0 */
        }
        if (havesib && (index != 4 || scale != 0)) {
            gen_op_addl_A0_reg_sN[scale][index]();
        }
        if (must_add_seg) {
            if (override < 0) {
                if (base == R_EBP || base == R_ESP)
                    override = R_SS;
                else
                    override = R_DS;
            }
            gen_op_addl_A0_seg(offsetof(CPUX86State,seg_cache[override].base));
        }
    } else {
        switch (mod) {
        case 0:
            if (rm == 6) {
                disp = lduw(s->pc);
                s->pc += 2;
                gen_op_movl_A0_im(disp);
                rm = 0; /* avoid SS override */
                goto no_rm;
            } else {
                disp = 0;
            }
            break;
        case 1:
            disp = (int8_t)ldub(s->pc++);
            break;
        default:
        case 2:
            disp = lduw(s->pc);
            s->pc += 2;
            break;
        }
        switch(rm) {
        case 0:
            gen_op_movl_A0_reg[R_EBX]();
            gen_op_addl_A0_reg_sN[0][R_ESI]();
            break;
        case 1:
            gen_op_movl_A0_reg[R_EBX]();
            gen_op_addl_A0_reg_sN[0][R_EDI]();
            break;
        case 2:
            gen_op_movl_A0_reg[R_EBP]();
            gen_op_addl_A0_reg_sN[0][R_ESI]();
            break;
        case 3:
            gen_op_movl_A0_reg[R_EBP]();
            gen_op_addl_A0_reg_sN[0][R_EDI]();
            break;
        case 4:
            gen_op_movl_A0_reg[R_ESI]();
            break;
        case 5:
            gen_op_movl_A0_reg[R_EDI]();
            break;
        case 6:
            gen_op_movl_A0_reg[R_EBP]();
            break;
        default:
        case 7:
            gen_op_movl_A0_reg[R_EBX]();
            break;
        }
        if (disp != 0)
            gen_op_addl_A0_im(disp);
        gen_op_andl_A0_ffff();
    no_rm:
        if (must_add_seg) {
            if (override < 0) {
                if (rm == 2 || rm == 3 || rm == 6)
                    override = R_SS;
                else
                    override = R_DS;
            }
            gen_op_addl_A0_seg(offsetof(CPUX86State,seg_cache[override].base));
        }
    }

    opreg = OR_A0;
    disp = 0;
    *reg_ptr = opreg;
    *offset_ptr = disp;
}

/* generate modrm memory load or store of 'reg'. TMP0 is used if reg !=
   OR_TMP0 */
static void gen_ldst_modrm(DisasContext *s, int modrm, int ot, int reg, int is_store)
{
    int mod, rm, opreg, disp;

    mod = (modrm >> 6) & 3;
    rm = modrm & 7;
    if (mod == 3) {
        if (is_store) {
            if (reg != OR_TMP0)
                gen_op_mov_TN_reg[ot][0][reg]();
            gen_op_mov_reg_T0[ot][rm]();
        } else {
            gen_op_mov_TN_reg[ot][0][rm]();
            if (reg != OR_TMP0)
                gen_op_mov_reg_T0[ot][reg]();
        }
    } else {
        gen_lea_modrm(s, modrm, &opreg, &disp);
        if (is_store) {
            if (reg != OR_TMP0)
                gen_op_mov_TN_reg[ot][0][reg]();
            gen_op_st_T0_A0[ot]();
        } else {
            gen_op_ld_T0_A0[ot]();
            if (reg != OR_TMP0)
                gen_op_mov_reg_T0[ot][reg]();
        }
    }
}

static inline uint32_t insn_get(DisasContext *s, int ot)
{
    uint32_t ret;

    switch(ot) {
    case OT_BYTE:
        ret = ldub(s->pc);
        s->pc++;
        break;
    case OT_WORD:
        ret = lduw(s->pc);
        s->pc += 2;
        break;
    default:
    case OT_LONG:
        ret = ldl(s->pc);
        s->pc += 4;
        break;
    }
    return ret;
}

static inline void gen_jcc(DisasContext *s, int b, int val, int next_eip)
{
    int inv, jcc_op;
    GenOpFunc2 *func;

    inv = b & 1;
    jcc_op = (b >> 1) & 7;
    switch(s->cc_op) {
        /* we optimize the cmp/jcc case */
    case CC_OP_SUBB:
    case CC_OP_SUBW:
    case CC_OP_SUBL:
        func = gen_jcc_sub[s->cc_op - CC_OP_SUBB][jcc_op];
        if (!func)
            goto slow_jcc;
        break;

        /* some jumps are easy to compute */
    case CC_OP_ADDB:
    case CC_OP_ADDW:
    case CC_OP_ADDL:
    case CC_OP_ADCB:
    case CC_OP_ADCW:
    case CC_OP_ADCL:
    case CC_OP_SBBB:
    case CC_OP_SBBW:
    case CC_OP_SBBL:
    case CC_OP_LOGICB:
    case CC_OP_LOGICW:
    case CC_OP_LOGICL:
    case CC_OP_INCB:
    case CC_OP_INCW:
    case CC_OP_INCL:
    case CC_OP_DECB:
    case CC_OP_DECW:
    case CC_OP_DECL:
    case CC_OP_SHLB:
    case CC_OP_SHLW:
    case CC_OP_SHLL:
    case CC_OP_SARB:
    case CC_OP_SARW:
    case CC_OP_SARL:
        switch(jcc_op) {
        case JCC_Z:
            func = gen_jcc_sub[(s->cc_op - CC_OP_ADDB) % 3][jcc_op];
            break;
        case JCC_S:
            func = gen_jcc_sub[(s->cc_op - CC_OP_ADDB) % 3][jcc_op];
            break;
        default:
            goto slow_jcc;
        }
        break;
    default:
    slow_jcc:
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        func = gen_jcc_slow[jcc_op];
        break;
    }
    if (!inv) {
        func(val, next_eip);
    } else {
        func(next_eip, val);
    }
}

static void gen_setcc(DisasContext *s, int b)
{
    int inv, jcc_op;
    GenOpFunc *func;

    inv = b & 1;
    jcc_op = (b >> 1) & 7;
    switch(s->cc_op) {
        /* we optimize the cmp/jcc case */
    case CC_OP_SUBB:
    case CC_OP_SUBW:
    case CC_OP_SUBL:
        func = gen_setcc_sub[s->cc_op - CC_OP_SUBB][jcc_op];
        if (!func)
            goto slow_jcc;
        break;

        /* some jumps are easy to compute */
    case CC_OP_ADDB:
    case CC_OP_ADDW:
    case CC_OP_ADDL:
    case CC_OP_LOGICB:
    case CC_OP_LOGICW:
    case CC_OP_LOGICL:
    case CC_OP_INCB:
    case CC_OP_INCW:
    case CC_OP_INCL:
    case CC_OP_DECB:
    case CC_OP_DECW:
    case CC_OP_DECL:
    case CC_OP_SHLB:
    case CC_OP_SHLW:
    case CC_OP_SHLL:
        switch(jcc_op) {
        case JCC_Z:
            func = gen_setcc_sub[(s->cc_op - CC_OP_ADDB) % 3][jcc_op];
            break;
        case JCC_S:
            func = gen_setcc_sub[(s->cc_op - CC_OP_ADDB) % 3][jcc_op];
            break;
        default:
            goto slow_jcc;
        }
        break;
    default:
    slow_jcc:
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        func = gen_setcc_slow[jcc_op];
        break;
    }
    func();
    if (inv) {
        gen_op_xor_T0_1();
    }
}

/* move T0 to seg_reg and compute if the CPU state may change */
static void gen_movl_seg_T0(DisasContext *s, int seg_reg)
{
    gen_op_movl_seg_T0(seg_reg);
    if (!s->addseg && seg_reg < R_FS)
        s->is_jmp = 2; /* abort translation because the register may
                          have a non zero base */
}

/* generate a push. It depends on ss32, addseg and dflag */
/* 为push产生指令码 */
static void gen_push_T0(DisasContext *s)
{
    if (s->ss32) {
        if (!s->addseg) {
            if (s->dflag)
                gen_op_pushl_T0(); /* 将T0寄存器的值压栈 */
            else
                gen_op_pushw_T0();
        } else {
            if (s->dflag)
                gen_op_pushl_ss32_T0();
            else
                gen_op_pushw_ss32_T0();
        }
    } else {
        if (s->dflag)
            gen_op_pushl_ss16_T0();
        else
            gen_op_pushw_ss16_T0();
    }
}

/* two step pop is necessary for precise exceptions */
static void gen_pop_T0(DisasContext *s)
{
    if (s->ss32) {
        if (!s->addseg) {
            if (s->dflag)
                gen_op_popl_T0();
            else
                gen_op_popw_T0();
        } else {
            if (s->dflag)
                gen_op_popl_ss32_T0();
            else
                gen_op_popw_ss32_T0();
        }
    } else {
        if (s->dflag)
            gen_op_popl_ss16_T0();
        else
            gen_op_popw_ss16_T0();
    }
}

static void gen_pop_update(DisasContext *s)
{
    if (s->ss32) {
        if (s->dflag)
            gen_op_addl_ESP_4();
        else
            gen_op_addl_ESP_2();
    } else {
        if (s->dflag)
            gen_op_addw_ESP_4();
        else
            gen_op_addw_ESP_2();
    }
}

/* NOTE: wrap around in 16 bit not fully handled */
static void gen_pusha(DisasContext *s)
{
    int i;
    gen_op_movl_A0_ESP();
    gen_op_addl_A0_im(-16 <<  s->dflag);
    if (!s->ss32)
        gen_op_andl_A0_ffff();
    gen_op_movl_T1_A0();
    if (s->addseg)
        gen_op_addl_A0_seg(offsetof(CPUX86State,seg_cache[R_SS].base));
    for(i = 0;i < 8; i++) {
        gen_op_mov_TN_reg[OT_LONG][0][7 - i]();
        gen_op_st_T0_A0[OT_WORD + s->dflag]();
        gen_op_addl_A0_im(2 <<  s->dflag);
    }
    gen_op_mov_reg_T1[OT_WORD + s->dflag][R_ESP]();
}

/* NOTE: wrap around in 16 bit not fully handled */
static void gen_popa(DisasContext *s)
{
    int i;
    gen_op_movl_A0_ESP();
    if (!s->ss32)
        gen_op_andl_A0_ffff();
    gen_op_movl_T1_A0();
    gen_op_addl_T1_im(16 <<  s->dflag);
    if (s->addseg)
        gen_op_addl_A0_seg(offsetof(CPUX86State,seg_cache[R_SS].base));
    for(i = 0;i < 8; i++) {
        /* ESP is not reloaded */
        if (i != 3) {
            gen_op_ld_T0_A0[OT_WORD + s->dflag]();
            gen_op_mov_reg_T0[OT_WORD + s->dflag][7 - i]();
        }
        gen_op_addl_A0_im(2 <<  s->dflag);
    }
    gen_op_mov_reg_T1[OT_WORD + s->dflag][R_ESP]();
}

/* NOTE: wrap around in 16 bit not fully handled */
/* XXX: check this */
static void gen_enter(DisasContext *s, int esp_addend, int level)
{
    int ot, level1, addend, opsize;

    ot = s->dflag + OT_WORD;
    level &= 0x1f;
    level1 = level;
    opsize = 2 << s->dflag;

    gen_op_movl_A0_ESP();
    gen_op_addl_A0_im(-opsize);
    if (!s->ss32)
        gen_op_andl_A0_ffff();
    gen_op_movl_T1_A0();
    if (s->addseg)
        gen_op_addl_A0_seg(offsetof(CPUX86State,seg_cache[R_SS].base));
    /* push bp */
    gen_op_mov_TN_reg[OT_LONG][0][R_EBP]();
    gen_op_st_T0_A0[ot]();
    if (level) {
        while (level--) {
            gen_op_addl_A0_im(-opsize);
            gen_op_addl_T0_im(-opsize);
            gen_op_st_T0_A0[ot]();
        }
        gen_op_addl_A0_im(-opsize);
        /* XXX: add st_T1_A0 ? */
        gen_op_movl_T0_T1();
        gen_op_st_T0_A0[ot]();
    }
    gen_op_mov_reg_T1[ot][R_EBP]();
    addend = -esp_addend;
    if (level1)
        addend -= opsize * (level1 + 1);
    gen_op_addl_T1_im(addend);
    gen_op_mov_reg_T1[ot][R_ESP]();
}

/* return the next pc address. Return -1 if no insn found. *is_jmp_ptr
   is set to true if the instruction sets the PC (last instruction of
   a basic block) */
/* 返回下一条指令的地址,如果返回-1,那么表示已经没有指令了. 
 * disas -> disassembly 反汇编
 */
long disas_insn(DisasContext *s, uint8_t *pc_start)
{
    int b, prefixes, aflag, dflag;
    int shift, ot;
    int modrm, reg, rm, mod, reg_addr, op, opreg, offset_addr, val;
    unsigned int next_eip;

    s->pc = pc_start;
    prefixes = 0;
    aflag = s->code32;
    dflag = s->code32;
    s->override = -1;
 next_byte:
    b = ldub(s->pc);
    s->pc++;
    /* check prefixes */
    switch (b) {
    case 0xf3:
        prefixes |= PREFIX_REPZ;
        goto next_byte;
    case 0xf2:
        prefixes |= PREFIX_REPNZ;
        goto next_byte;
    case 0xf0:
        prefixes |= PREFIX_LOCK;
        goto next_byte;
    case 0x2e:
        s->override = R_CS;
        goto next_byte;
    case 0x36:
        s->override = R_SS;
        goto next_byte;
    case 0x3e:
        s->override = R_DS;
        goto next_byte;
    case 0x26:
        s->override = R_ES;
        goto next_byte;
    case 0x64:
        s->override = R_FS;
        goto next_byte;
    case 0x65:
        s->override = R_GS;
        goto next_byte;
    case 0x66:
        prefixes |= PREFIX_DATA;
        goto next_byte;
    case 0x67:
        prefixes |= PREFIX_ADR;
        goto next_byte;
    case 0x9b:
        prefixes |= PREFIX_FWAIT;
        goto next_byte;
    }

    if (prefixes & PREFIX_DATA)
        dflag ^= 1;
    if (prefixes & PREFIX_ADR)
        aflag ^= 1;

    s->prefix = prefixes;
    s->aflag = aflag;
    s->dflag = dflag;

    /* lock generation */
    if (prefixes & PREFIX_LOCK)
        gen_op_lock();

    /* now check op code */
 reswitch: /* 检查操作码 */
    switch(b) {
    case 0x0f:
        /**************************/
        /* extended op code */
        b = ldub(s->pc++) | 0x100;
        goto reswitch;

        /**************************/
        /* arith & logic */
    case 0x00 ... 0x05:
    case 0x08 ... 0x0d:
    case 0x10 ... 0x15:
    case 0x18 ... 0x1d:
    case 0x20 ... 0x25:
    case 0x28 ... 0x2d:
    case 0x30 ... 0x35:
    case 0x38 ... 0x3d:
        {
            int op, f, val;
            op = (b >> 3) & 7;
            f = (b >> 1) & 3;

            if ((b & 1) == 0)
                ot = OT_BYTE; /* ot表示操作符长度? */
            else
                ot = dflag ? OT_LONG : OT_WORD;

            switch(f) {
            case 0: /* OP Ev, Gv */
                modrm = ldub(s->pc++);
                reg = ((modrm >> 3) & 7) + OR_EAX; /* 寄存器 */
                mod = (modrm >> 6) & 3;
                rm = modrm & 7;
                if (mod != 3) {
                    gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
                    gen_op_ld_T0_A0[ot]();
                    opreg = OR_TMP0;
                } else {
                    opreg = OR_EAX + rm;
                }
                gen_op(s, op, ot, opreg, reg);
                if (mod != 3 && op != 7) {
                    gen_op_st_T0_A0[ot](); /* 存值 */
                }
                break;
            case 1: /* OP Gv, Ev */
                modrm = ldub(s->pc++);
                mod = (modrm >> 6) & 3;
                reg = ((modrm >> 3) & 7) + OR_EAX;
                rm = modrm & 7;
                if (mod != 3) {
                    gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
                    gen_op_ld_T1_A0[ot]();
                    opreg = OR_TMP1;
                } else {
                    opreg = OR_EAX + rm;
                }
                gen_op(s, op, ot, reg, opreg);
                break;
            case 2: /* OP A, Iv */
                val = insn_get(s, ot);
                gen_opi(s, op, ot, OR_EAX, val);
                break;
            }
        }
        break;

    case 0x80: /* GRP1 */
    case 0x81:
    case 0x83:
        {
            int val;

            if ((b & 1) == 0)
                ot = OT_BYTE;
            else
                ot = dflag ? OT_LONG : OT_WORD;

            modrm = ldub(s->pc++);
            mod = (modrm >> 6) & 3;
            rm = modrm & 7;
            op = (modrm >> 3) & 7;

            if (mod != 3) {
                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
                /* 加载到T0寄存器 */
                gen_op_ld_T0_A0[ot]();
                opreg = OR_TMP0;
            } else {
                opreg = rm + OR_EAX; /* 目的寄存器 */
            }

            switch(b) {
            default:
            case 0x80:
            case 0x81:
                val = insn_get(s, ot);
                break;
            case 0x83:
                val = (int8_t)insn_get(s, OT_BYTE);
                break;
            }

            gen_opi(s, op, ot, opreg, val);
            if (op != 7 && mod != 3) {
                /* 存值T0 -> [A0] */
                gen_op_st_T0_A0[ot]();
            }
        }
        break;

        /**************************/
        /* inc, dec, and other misc arith */
    case 0x40 ... 0x47: /* inc Gv */
        ot = dflag ? OT_LONG : OT_WORD;
        gen_inc(s, ot, OR_EAX + (b & 7), 1); /* 自增 */
        break;
    case 0x48 ... 0x4f: /* dec Gv */
        ot = dflag ? OT_LONG : OT_WORD;
        gen_inc(s, ot, OR_EAX + (b & 7), -1); /* 自减 */
        break;
    case 0xf6: /* GRP3 */
    case 0xf7:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);
        mod = (modrm >> 6) & 3;
        rm = modrm & 7;
        op = (modrm >> 3) & 7;
        if (mod != 3) {
            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
            gen_op_ld_T0_A0[ot]();
        } else {
            gen_op_mov_TN_reg[ot][0][rm]();
        }

        switch(op) {
        case 0: /* test */
            val = insn_get(s, ot);
            gen_op_movl_T1_im(val); /* 将立即数val移动到T1寄存器 */
            gen_op_testl_T0_T1_cc();
            s->cc_op = CC_OP_LOGICB + ot;
            break;
        case 2: /* not */
            gen_op_notl_T0();
            if (mod != 3) {
                gen_op_st_T0_A0[ot]();
            } else {
                gen_op_mov_reg_T0[ot][rm]();
            }
            break;
        case 3: /* neg */
            gen_op_negl_T0_cc();
            if (mod != 3) {
                gen_op_st_T0_A0[ot]();
            } else {
                gen_op_mov_reg_T0[ot][rm]();
            }
            s->cc_op = CC_OP_SUBB + ot;
            break;
        case 4: /* mul */
            switch(ot) { /* ot为操作数占用的字节数 */
            case OT_BYTE:
                gen_op_mulb_AL_T0();
                break;
            case OT_WORD:
                gen_op_mulw_AX_T0();
                break;
            default:
            case OT_LONG:
                gen_op_mull_EAX_T0();
                break;
            }
            s->cc_op = CC_OP_MUL; /* 乘法会影响eflags,更新cc_op */
            break;
        case 5: /* imul */
            switch(ot) {
            case OT_BYTE:
                gen_op_imulb_AL_T0();
                break;
            case OT_WORD:
                gen_op_imulw_AX_T0();
                break;
            default:
            case OT_LONG:
                gen_op_imull_EAX_T0();
                break;
            }
            s->cc_op = CC_OP_MUL; /* 乘法会影响eflags,更新cc_op */
            break;
        case 6: /* div */
            switch(ot) {
            case OT_BYTE:
                gen_op_divb_AL_T0();
                break;
            case OT_WORD:
                gen_op_divw_AX_T0();
                break;
            default:
            case OT_LONG:
                gen_op_divl_EAX_T0();
                break;
            }
            break;
        case 7: /* idiv */
            switch(ot) {
            case OT_BYTE:
                gen_op_idivb_AL_T0();
                break;
            case OT_WORD:
                gen_op_idivw_AX_T0();
                break;
            default:
            case OT_LONG:
                gen_op_idivl_EAX_T0();
                break;
            }
            break;
        default:
            goto illegal_op;
        }
        break;

    case 0xfe: /* GRP4 */
    case 0xff: /* GRP5 */
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);
        mod = (modrm >> 6) & 3;
        rm = modrm & 7;
        op = (modrm >> 3) & 7;
        if (op >= 2 && b == 0xfe) {
            goto illegal_op;
        }
        if (mod != 3) {
            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
            if (op != 3 && op != 5)
                gen_op_ld_T0_A0[ot]();
        } else {
            gen_op_mov_TN_reg[ot][0][rm]();
        }

        switch(op) {
        case 0: /* inc Ev */
            gen_inc(s, ot, OR_TMP0, 1);
            if (mod != 3)
                gen_op_st_T0_A0[ot]();
            else
                gen_op_mov_reg_T0[ot][rm]();
            break;
        case 1: /* dec Ev */
            gen_inc(s, ot, OR_TMP0, -1);
            if (mod != 3)
                gen_op_st_T0_A0[ot]();
            else
                gen_op_mov_reg_T0[ot][rm]();
            break;
        case 2: /* call Ev */
            /* XXX: optimize if memory (no and is necessary) */
            if (s->dflag == 0)
                gen_op_andl_T0_ffff();
            gen_op_jmp_T0();
            next_eip = s->pc - s->cs_base;
            gen_op_movl_T0_im(next_eip);
            gen_push_T0(s);
            s->is_jmp = 1;
            break;
        case 3: /* lcall Ev */
            /* push return segment + offset */
            gen_op_movl_T0_seg(R_CS);
            gen_push_T0(s);
            next_eip = s->pc - s->cs_base;
            gen_op_movl_T0_im(next_eip);
            gen_push_T0(s);

            gen_op_ld_T1_A0[ot]();
            gen_op_addl_A0_im(1 << (ot - OT_WORD + 1));
            gen_op_lduw_T0_A0();
            gen_movl_seg_T0(s, R_CS);
            gen_op_movl_T0_T1();
            gen_op_jmp_T0();
            s->is_jmp = 1;
            break;
        case 4: /* jmp Ev */
            if (s->dflag == 0)
                gen_op_andl_T0_ffff();
            gen_op_jmp_T0();
            s->is_jmp = 1;
            break;
        case 5: /* ljmp Ev */
            gen_op_ld_T1_A0[ot]();
            gen_op_addl_A0_im(1 << (ot - OT_WORD + 1));
            gen_op_lduw_T0_A0();
            gen_movl_seg_T0(s, R_CS);
            gen_op_movl_T0_T1();
            gen_op_jmp_T0();
            s->is_jmp = 1;
            break;
        case 6: /* push Ev */
            gen_push_T0(s);
            break;
        default:
            goto illegal_op;
        }
        break;

    case 0x84: /* test Ev, Gv */
    case 0x85:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);
        mod = (modrm >> 6) & 3;
        rm = modrm & 7;
        reg = (modrm >> 3) & 7;

        gen_ldst_modrm(s, modrm, ot, OR_TMP0, 0);
        /* 将寄存器reg的值移动到T1寄存器 */
        gen_op_mov_TN_reg[ot][1][reg + OR_EAX]();
        gen_op_testl_T0_T1_cc();
        s->cc_op = CC_OP_LOGICB + ot; /* logicb会影响eflags,更新cc_op */
        break;

    case 0xa8: /* test eAX, Iv */
    case 0xa9:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        val = insn_get(s, ot);

        gen_op_mov_TN_reg[ot][0][OR_EAX]();
        gen_op_movl_T1_im(val);
        gen_op_testl_T0_T1_cc();
        s->cc_op = CC_OP_LOGICB + ot;  /* logicb会影响eflags,更新cc_op */
        break;

    case 0x98: /* CWDE/CBW */
        if (dflag)
            gen_op_movswl_EAX_AX();
        else
            gen_op_movsbw_AX_AL();
        break;
    case 0x99: /* CDQ/CWD */
        if (dflag)
            gen_op_movslq_EDX_EAX();
        else
            gen_op_movswl_DX_AX();
        break;
    case 0x1af: /* imul Gv, Ev */
    case 0x69: /* imul Gv, Ev, I */
    case 0x6b:
        ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        reg = ((modrm >> 3) & 7) + OR_EAX;
        gen_ldst_modrm(s, modrm, ot, OR_TMP0, 0);
        if (b == 0x69) {
            val = insn_get(s, ot);
            gen_op_movl_T1_im(val);
        } else if (b == 0x6b) {
            val = insn_get(s, OT_BYTE);
            gen_op_movl_T1_im(val);
        } else {
            gen_op_mov_TN_reg[ot][1][reg]();
        }

        if (ot == OT_LONG) {
            gen_op_imull_T0_T1();
        } else {
            gen_op_imulw_T0_T1();
        }
        gen_op_mov_reg_T0[ot][reg]();
        s->cc_op = CC_OP_MUL;
        break;
    case 0x1c0:
    case 0x1c1: /* xadd Ev, Gv */
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        reg = (modrm >> 3) & 7;
        mod = (modrm >> 6) & 3;
        if (mod == 3) {
            rm = modrm & 7;
            gen_op_mov_TN_reg[ot][0][reg]();
            gen_op_mov_TN_reg[ot][1][rm]();
            gen_op_addl_T0_T1_cc();
            gen_op_mov_reg_T0[ot][rm]();
            gen_op_mov_reg_T1[ot][reg]();
        } else {
            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
            gen_op_mov_TN_reg[ot][0][reg]();
            gen_op_ld_T1_A0[ot]();
            gen_op_addl_T0_T1_cc();
            gen_op_st_T0_A0[ot]();
            gen_op_mov_reg_T1[ot][reg]();
        }
        s->cc_op = CC_OP_ADDB + ot;
        break;
    case 0x1b0:
    case 0x1b1: /* cmpxchg Ev, Gv */
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        reg = (modrm >> 3) & 7;
        mod = (modrm >> 6) & 3;
        gen_op_mov_TN_reg[ot][1][reg]();
        if (mod == 3) {
            rm = modrm & 7;
            gen_op_mov_TN_reg[ot][0][rm]();
            gen_op_cmpxchg_T0_T1_EAX_cc[ot]();
            gen_op_mov_reg_T0[ot][rm]();
        } else {
            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
            gen_op_ld_T0_A0[ot]();
            gen_op_cmpxchg_T0_T1_EAX_cc[ot]();
            gen_op_st_T0_A0[ot]();
        }
        s->cc_op = CC_OP_SUBB + ot;
        break;
    case 0x1c7: /* cmpxchg8b */
        modrm = ldub(s->pc++);
        mod = (modrm >> 6) & 3;
        if (mod == 3)
            goto illegal_op;
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
        gen_op_cmpxchg8b();
        s->cc_op = CC_OP_EFLAGS;
        break;

        /**************************/
        /* push/pop */
    case 0x50 ... 0x57: /* push */
        gen_op_mov_TN_reg[OT_LONG][0][b & 7]();
        gen_push_T0(s);
        break;
    case 0x58 ... 0x5f: /* pop */
        ot = dflag ? OT_LONG : OT_WORD;
        gen_pop_T0(s);
        /* 出栈,移动到寄存器T0 */
        gen_op_mov_reg_T0[ot][b & 7]();
        gen_pop_update(s);
        break;
    case 0x60: /* pusha */
        gen_pusha(s);
        break;
    case 0x61: /* popa */
        gen_popa(s);
        break;
    case 0x68: /* push Iv */
    case 0x6a:
        ot = dflag ? OT_LONG : OT_WORD;
        if (b == 0x68)
            val = insn_get(s, ot);
        else
            val = (int8_t)insn_get(s, OT_BYTE);
        gen_op_movl_T0_im(val);
        gen_push_T0(s);
        break;
    case 0x8f: /* pop Ev */
        ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        gen_pop_T0(s);
        gen_ldst_modrm(s, modrm, ot, OR_TMP0, 1);
        gen_pop_update(s);
        break;
    case 0xc8: /* enter */
        {
            int level;
            val = lduw(s->pc);
            s->pc += 2;
            level = ldub(s->pc++);
            gen_enter(s, val, level);
        }
        break;
    case 0xc9: /* leave */
        /* XXX: exception not precise (ESP is update before potential exception) */
        if (s->ss32) {
            gen_op_mov_TN_reg[OT_LONG][0][R_EBP]();
            gen_op_mov_reg_T0[OT_LONG][R_ESP]();
        } else {
            gen_op_mov_TN_reg[OT_WORD][0][R_EBP]();
            gen_op_mov_reg_T0[OT_WORD][R_ESP]();
        }
        gen_pop_T0(s);
        ot = dflag ? OT_LONG : OT_WORD;
        gen_op_mov_reg_T0[ot][R_EBP]();
        gen_pop_update(s);
        break;
    case 0x06: /* push es */
    case 0x0e: /* push cs */
    case 0x16: /* push ss */
    case 0x1e: /* push ds */
        gen_op_movl_T0_seg(b >> 3);
        gen_push_T0(s);
        break;
    case 0x1a0: /* push fs */
    case 0x1a8: /* push gs */
        gen_op_movl_T0_seg((b >> 3) & 7);
        gen_push_T0(s);
        break;
    case 0x07: /* pop es */
    case 0x17: /* pop ss */
    case 0x1f: /* pop ds */
        gen_pop_T0(s);
        gen_movl_seg_T0(s, b >> 3);
        gen_pop_update(s);
        break;
    case 0x1a1: /* pop fs */
    case 0x1a9: /* pop gs */
        gen_pop_T0(s);
        gen_movl_seg_T0(s, (b >> 3) & 7);
        gen_pop_update(s);
        break;

        /**************************/
        /* mov */
    case 0x88:
    case 0x89: /* mov Gv, Ev */
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        reg = (modrm >> 3) & 7;

        /* generate a generic store */
        gen_ldst_modrm(s, modrm, ot, OR_EAX + reg, 1);
        break;
    case 0xc6:
    case 0xc7: /* mov Ev, Iv */
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        mod = (modrm >> 6) & 3;
        if (mod != 3)
            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
        val = insn_get(s, ot);
        gen_op_movl_T0_im(val);
        if (mod != 3)
            gen_op_st_T0_A0[ot]();
        else
            gen_op_mov_reg_T0[ot][modrm & 7]();
        break;
    case 0x8a:
    case 0x8b: /* mov Ev, Gv */
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        reg = (modrm >> 3) & 7;

        gen_ldst_modrm(s, modrm, ot, OR_TMP0, 0);
        gen_op_mov_reg_T0[ot][reg]();
        break;
    case 0x8e: /* mov seg, Gv */
        ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        reg = (modrm >> 3) & 7;
        gen_ldst_modrm(s, modrm, ot, OR_TMP0, 0);
        if (reg >= 6 || reg == R_CS)
            goto illegal_op;
        gen_movl_seg_T0(s, reg);
        break;
    case 0x8c: /* mov Gv, seg */
        ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        reg = (modrm >> 3) & 7;
        if (reg >= 6)
            goto illegal_op;
        gen_op_movl_T0_seg(reg);
        gen_ldst_modrm(s, modrm, ot, OR_TMP0, 1);
        break;

    case 0x1b6: /* movzbS Gv, Eb */
    case 0x1b7: /* movzwS Gv, Eb */
    case 0x1be: /* movsbS Gv, Eb */
    case 0x1bf: /* movswS Gv, Eb */
        {
            int d_ot;
            /* d_ot is the size of destination */
            d_ot = dflag + OT_WORD;
            /* ot is the size of source */
            ot = (b & 1) + OT_BYTE;
            modrm = ldub(s->pc++);
            reg = ((modrm >> 3) & 7) + OR_EAX;
            mod = (modrm >> 6) & 3;
            rm = modrm & 7;

            if (mod == 3) {
                gen_op_mov_TN_reg[ot][0][rm]();
                switch(ot | (b & 8)) {
                case OT_BYTE:
                    gen_op_movzbl_T0_T0();
                    break;
                case OT_BYTE | 8:
                    gen_op_movsbl_T0_T0();
                    break;
                case OT_WORD:
                    gen_op_movzwl_T0_T0();
                    break;
                default:
                case OT_WORD | 8:
                    gen_op_movswl_T0_T0();
                    break;
                }
                gen_op_mov_reg_T0[d_ot][reg]();
            } else {
                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
                if (b & 8) {
                    gen_op_lds_T0_A0[ot]();
                } else {
                    gen_op_ldu_T0_A0[ot]();
                }
                gen_op_mov_reg_T0[d_ot][reg]();
            }
        }
        break;

    case 0x8d: /* lea */
        ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        reg = (modrm >> 3) & 7;
        /* we must ensure that no segment is added */
        s->override = -1;
        val = s->addseg;
        s->addseg = 0;
        gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
        s->addseg = val;
        gen_op_mov_reg_A0[ot - OT_WORD][reg]();
        break;

    case 0xa0: /* mov EAX, Ov */
    case 0xa1:
    case 0xa2: /* mov Ov, EAX */
    case 0xa3:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        if (s->aflag)
            offset_addr = insn_get(s, OT_LONG);
        else
            offset_addr = insn_get(s, OT_WORD);
        gen_op_movl_A0_im(offset_addr);
        /* handle override */
        {
            int override, must_add_seg;
            must_add_seg = s->addseg;
            if (s->override >= 0) {
                override = s->override;
                must_add_seg = 1;
            } else {
                override = R_DS;
            }
            if (must_add_seg) {
                gen_op_addl_A0_seg(offsetof(CPUX86State,seg_cache[override].base));
            }
        }
        if ((b & 2) == 0) {
            gen_op_ld_T0_A0[ot]();
            gen_op_mov_reg_T0[ot][R_EAX]();
        } else {
            gen_op_mov_TN_reg[ot][0][R_EAX]();
            gen_op_st_T0_A0[ot]();
        }
        break;
    case 0xd7: /* xlat */
        gen_op_movl_A0_reg[R_EBX]();
        gen_op_addl_A0_AL();
        if (s->aflag == 0)
            gen_op_andl_A0_ffff();
        /* handle override */
        {
            int override, must_add_seg;
            must_add_seg = s->addseg;
            override = R_DS;
            if (s->override >= 0) {
                override = s->override;
                must_add_seg = 1;
            } else {
                override = R_DS;
            }
            if (must_add_seg) {
                gen_op_addl_A0_seg(offsetof(CPUX86State,seg_cache[override].base));
            }
        }
        gen_op_ldub_T0_A0();
        gen_op_mov_reg_T0[OT_BYTE][R_EAX]();
        break;
    case 0xb0 ... 0xb7: /* mov R, Ib */
        val = insn_get(s, OT_BYTE);
        gen_op_movl_T0_im(val);
        gen_op_mov_reg_T0[OT_BYTE][b & 7]();
        break;
    case 0xb8 ... 0xbf: /* mov R, Iv */
        ot = dflag ? OT_LONG : OT_WORD;
        val = insn_get(s, ot);
        reg = OR_EAX + (b & 7);
        gen_op_movl_T0_im(val);
        gen_op_mov_reg_T0[ot][reg]();
        break;

    case 0x91 ... 0x97: /* xchg R, EAX */
        ot = dflag ? OT_LONG : OT_WORD;
        reg = b & 7;
        rm = R_EAX;
        goto do_xchg_reg;
    case 0x86:
    case 0x87: /* xchg Ev, Gv */
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        reg = (modrm >> 3) & 7;
        mod = (modrm >> 6) & 3;
        if (mod == 3) {
            rm = modrm & 7;
        do_xchg_reg:
            gen_op_mov_TN_reg[ot][0][reg]();
            gen_op_mov_TN_reg[ot][1][rm]();
            gen_op_mov_reg_T0[ot][rm]();
            gen_op_mov_reg_T1[ot][reg]();
        } else {
            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
            gen_op_mov_TN_reg[ot][0][reg]();
            /* for xchg, lock is implicit */
            if (!(prefixes & PREFIX_LOCK))
                gen_op_lock();
            gen_op_ld_T1_A0[ot]();
            gen_op_st_T0_A0[ot]();
            if (!(prefixes & PREFIX_LOCK))
                gen_op_unlock();
            gen_op_mov_reg_T1[ot][reg]();
        }
        break;
    case 0xc4: /* les Gv */
        op = R_ES;
        goto do_lxx;
    case 0xc5: /* lds Gv */
        op = R_DS;
        goto do_lxx;
    case 0x1b2: /* lss Gv */
        op = R_SS;
        goto do_lxx;
    case 0x1b4: /* lfs Gv */
        op = R_FS;
        goto do_lxx;
    case 0x1b5: /* lgs Gv */
        op = R_GS;
    do_lxx:
        ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        reg = (modrm >> 3) & 7;
        mod = (modrm >> 6) & 3;
        if (mod == 3)
            goto illegal_op;
        gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
        gen_op_ld_T1_A0[ot]();
        gen_op_addl_A0_im(1 << (ot - OT_WORD + 1));
        /* load the segment first to handle exceptions properly */
        gen_op_lduw_T0_A0();
        gen_movl_seg_T0(s, op);
        /* then put the data */
        gen_op_mov_reg_T1[ot][reg]();
        break;

        /************************/
        /* shifts */
    case 0xc0:
    case 0xc1:
        /* shift Ev,Ib */
        shift = 2;
    grp2:
        {
            if ((b & 1) == 0)
                ot = OT_BYTE;
            else
                ot = dflag ? OT_LONG : OT_WORD;

            modrm = ldub(s->pc++);
            mod = (modrm >> 6) & 3;
            rm = modrm & 7;
            op = (modrm >> 3) & 7;

            if (mod != 3) {
                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
                gen_op_ld_T0_A0[ot]();
                opreg = OR_TMP0;
            } else {
                opreg = rm + OR_EAX;
            }

            /* simpler op */
            if (shift == 0) {
                gen_shift(s, op, ot, opreg, OR_ECX);
            } else {
                if (shift == 2) {
                    shift = ldub(s->pc++);
                }
                gen_shifti(s, op, ot, opreg, shift);
            }

            if (mod != 3) {
                gen_op_st_T0_A0[ot]();
            }
        }
        break;
    case 0xd0:
    case 0xd1:
        /* shift Ev,1 */
        shift = 1;
        goto grp2;
    case 0xd2:
    case 0xd3:
        /* shift Ev,cl */
        shift = 0;
        goto grp2;

    case 0x1a4: /* shld imm */
        op = 0;
        shift = 1;
        goto do_shiftd;
    case 0x1a5: /* shld cl */
        op = 0;
        shift = 0;
        goto do_shiftd;
    case 0x1ac: /* shrd imm */
        op = 1;
        shift = 1;
        goto do_shiftd;
    case 0x1ad: /* shrd cl */
        op = 1;
        shift = 0;
    do_shiftd:
        ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        mod = (modrm >> 6) & 3;
        rm = modrm & 7;
        reg = (modrm >> 3) & 7;

        if (mod != 3) {
            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
            gen_op_ld_T0_A0[ot]();
        } else {
            gen_op_mov_TN_reg[ot][0][rm]();
        }
        gen_op_mov_TN_reg[ot][1][reg]();

        if (shift) {
            val = ldub(s->pc++);
            val &= 0x1f;
            if (val) {
                gen_op_shiftd_T0_T1_im_cc[ot - OT_WORD][op](val);
                if (op == 0 && ot != OT_WORD)
                    s->cc_op = CC_OP_SHLB + ot;
                else
                    s->cc_op = CC_OP_SARB + ot;
            }
        } else {
            if (s->cc_op != CC_OP_DYNAMIC)
                gen_op_set_cc_op(s->cc_op);
            gen_op_shiftd_T0_T1_ECX_cc[ot - OT_WORD][op]();
            s->cc_op = CC_OP_DYNAMIC; /* cannot predict flags after */
        }
        if (mod != 3) {
            gen_op_st_T0_A0[ot]();
        } else {
            gen_op_mov_reg_T0[ot][rm]();
        }
        break;

        /************************/
        /* floats */
    case 0xd8 ... 0xdf:
        modrm = ldub(s->pc++);
        mod = (modrm >> 6) & 3;
        rm = modrm & 7;
        op = ((b & 7) << 3) | ((modrm >> 3) & 7);

        if (mod != 3) {
            /* memory op */
            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
            switch(op) {
            case 0x00 ... 0x07: /* fxxxs */
            case 0x10 ... 0x17: /* fixxxl */
            case 0x20 ... 0x27: /* fxxxl */
            case 0x30 ... 0x37: /* fixxx */
                {
                    int op1;
                    op1 = op & 7;

                    switch(op >> 4) {
                    case 0:
                        gen_op_flds_FT0_A0();
                        break;
                    case 1:
                        gen_op_fildl_FT0_A0();
                        break;
                    case 2:
                        gen_op_fldl_FT0_A0();
                        break;
                    case 3:
                    default:
                        gen_op_fild_FT0_A0();
                        break;
                    }

                    gen_op_fp_arith_ST0_FT0[op1]();
                    if (op1 == 3) {
                        /* fcomp needs pop */
                        gen_op_fpop();
                    }
                }
                break;
            case 0x08: /* flds */
            case 0x0a: /* fsts */
            case 0x0b: /* fstps */
            case 0x18: /* fildl */
            case 0x1a: /* fistl */
            case 0x1b: /* fistpl */
            case 0x28: /* fldl */
            case 0x2a: /* fstl */
            case 0x2b: /* fstpl */
            case 0x38: /* filds */
            case 0x3a: /* fists */
            case 0x3b: /* fistps */

                switch(op & 7) {
                case 0:
                    gen_op_fpush();
                    switch(op >> 4) {
                    case 0:
                        gen_op_flds_ST0_A0();
                        break;
                    case 1:
                        gen_op_fildl_ST0_A0();
                        break;
                    case 2:
                        gen_op_fldl_ST0_A0();
                        break;
                    case 3:
                    default:
                        gen_op_fild_ST0_A0();
                        break;
                    }
                    break;
                default:
                    switch(op >> 4) {
                    case 0:
                        gen_op_fsts_ST0_A0();
                        break;
                    case 1:
                        gen_op_fistl_ST0_A0();
                        break;
                    case 2:
                        gen_op_fstl_ST0_A0();
                        break;
                    case 3:
                    default:
                        gen_op_fist_ST0_A0();
                        break;
                    }
                    if ((op & 7) == 3)
                        gen_op_fpop();
                    break;
                }
                break;
            case 0x0d: /* fldcw mem */
                gen_op_fldcw_A0();
                break;
            case 0x0f: /* fnstcw mem */
                gen_op_fnstcw_A0();
                break;
            case 0x1d: /* fldt mem */
                gen_op_fpush();
                gen_op_fldt_ST0_A0();
                break;
            case 0x1f: /* fstpt mem */
                gen_op_fstt_ST0_A0();
                gen_op_fpop();
                break;
            case 0x2f: /* fnstsw mem */
                gen_op_fnstsw_A0();
                break;
            case 0x3c: /* fbld */
                gen_op_fpush();
                gen_op_fbld_ST0_A0();
                break;
            case 0x3e: /* fbstp */
                gen_op_fbst_ST0_A0();
                gen_op_fpop();
                break;
            case 0x3d: /* fildll */
                gen_op_fpush();
                gen_op_fildll_ST0_A0();
                break;
            case 0x3f: /* fistpll */
                gen_op_fistll_ST0_A0();
                gen_op_fpop();
                break;
            default:
                goto illegal_op;
            }
        } else {
            /* register float ops */
            opreg = rm;

            switch(op) {
            case 0x08: /* fld sti */
                gen_op_fpush();
                gen_op_fmov_ST0_STN((opreg + 1) & 7);
                break;
            case 0x09: /* fxchg sti */
                gen_op_fxchg_ST0_STN(opreg);
                break;
            case 0x0a: /* grp d9/2 */
                switch(rm) {
                case 0: /* fnop */
                    break;
                default:
                    goto illegal_op;
                }
                break;
            case 0x0c: /* grp d9/4 */
                switch(rm) {
                case 0: /* fchs */
                    gen_op_fchs_ST0();
                    break;
                case 1: /* fabs */
                    gen_op_fabs_ST0();
                    break;
                case 4: /* ftst */
                    gen_op_fldz_FT0();
                    gen_op_fcom_ST0_FT0();
                    break;
                case 5: /* fxam */
                    gen_op_fxam_ST0();
                    break;
                default:
                    goto illegal_op;
                }
                break;
            case 0x0d: /* grp d9/5 */
                {
                    switch(rm) {
                    case 0:
                        gen_op_fpush();
                        gen_op_fld1_ST0();
                        break;
                    case 1:
                        gen_op_fpush();
                        gen_op_fldl2t_ST0();
                        break;
                    case 2:
                        gen_op_fpush();
                        gen_op_fldl2e_ST0();
                        break;
                    case 3:
                        gen_op_fpush();
                        gen_op_fldpi_ST0();
                        break;
                    case 4:
                        gen_op_fpush();
                        gen_op_fldlg2_ST0();
                        break;
                    case 5:
                        gen_op_fpush();
                        gen_op_fldln2_ST0();
                        break;
                    case 6:
                        gen_op_fpush();
                        gen_op_fldz_ST0();
                        break;
                    default:
                        goto illegal_op;
                    }
                }
                break;
            case 0x0e: /* grp d9/6 */
                switch(rm) {
                case 0: /* f2xm1 */
                    gen_op_f2xm1();
                    break;
                case 1: /* fyl2x */
                    gen_op_fyl2x();
                    break;
                case 2: /* fptan */
                    gen_op_fptan();
                    break;
                case 3: /* fpatan */
                    gen_op_fpatan();
                    break;
                case 4: /* fxtract */
                    gen_op_fxtract();
                    break;
                case 5: /* fprem1 */
                    gen_op_fprem1();
                    break;
                case 6: /* fdecstp */
                    gen_op_fdecstp();
                    break;
                default:
                case 7: /* fincstp */
                    gen_op_fincstp();
                    break;
                }
                break;
            case 0x0f: /* grp d9/7 */
                switch(rm) {
                case 0: /* fprem */
                    gen_op_fprem();
                    break;
                case 1: /* fyl2xp1 */
                    gen_op_fyl2xp1();
                    break;
                case 2: /* fsqrt */
                    gen_op_fsqrt();
                    break;
                case 3: /* fsincos */
                    gen_op_fsincos();
                    break;
                case 5: /* fscale */
                    gen_op_fscale();
                    break;
                case 4: /* frndint */
                    gen_op_frndint();
                    break;
                case 6: /* fsin */
                    gen_op_fsin();
                    break;
                default:
                case 7: /* fcos */
                    gen_op_fcos();
                    break;
                }
                break;
            case 0x00: case 0x01: case 0x04 ... 0x07: /* fxxx st, sti */
            case 0x20: case 0x21: case 0x24 ... 0x27: /* fxxx sti, st */
            case 0x30: case 0x31: case 0x34 ... 0x37: /* fxxxp sti, st */
                {
                    int op1;

                    op1 = op & 7;
                    if (op >= 0x20) {
                        gen_op_fp_arith_STN_ST0[op1](opreg);
                        if (op >= 0x30)
                            gen_op_fpop();
                    } else {
                        gen_op_fmov_FT0_STN(opreg);
                        gen_op_fp_arith_ST0_FT0[op1]();
                    }
                }
                break;
            case 0x02: /* fcom */
                gen_op_fmov_FT0_STN(opreg);
                gen_op_fcom_ST0_FT0();
                break;
            case 0x03: /* fcomp */
                gen_op_fmov_FT0_STN(opreg);
                gen_op_fcom_ST0_FT0();
                gen_op_fpop();
                break;
            case 0x15: /* da/5 */
                switch(rm) {
                case 1: /* fucompp */
                    gen_op_fmov_FT0_STN(1);
                    gen_op_fucom_ST0_FT0();
                    gen_op_fpop();
                    gen_op_fpop();
                    break;
                default:
                    goto illegal_op;
                }
                break;
            case 0x1c:
                switch(rm) {
                case 2: /* fclex */
                    gen_op_fclex();
                    break;
                case 3: /* fninit */
                    gen_op_fninit();
                    break;
                default:
                    goto illegal_op;
                }
                break;
            case 0x2a: /* fst sti */
                gen_op_fmov_STN_ST0(opreg);
                break;
            case 0x2b: /* fstp sti */
                gen_op_fmov_STN_ST0(opreg);
                gen_op_fpop();
                break;
            case 0x2c: /* fucom st(i) */
                gen_op_fmov_FT0_STN(opreg);
                gen_op_fucom_ST0_FT0();
                break;
            case 0x2d: /* fucomp st(i) */
                gen_op_fmov_FT0_STN(opreg);
                gen_op_fucom_ST0_FT0();
                gen_op_fpop();
                break;
            case 0x33: /* de/3 */
                switch(rm) {
                case 1: /* fcompp */
                    gen_op_fmov_FT0_STN(1);
                    gen_op_fcom_ST0_FT0();
                    gen_op_fpop();
                    gen_op_fpop();
                    break;
                default:
                    goto illegal_op;
                }
                break;
            case 0x3c: /* df/4 */
                switch(rm) {
                case 0:
                    gen_op_fnstsw_EAX();
                    break;
                default:
                    goto illegal_op;
                }
                break;
            default:
                goto illegal_op;
            }
        }
        break;
        /************************/
        /* string ops */

    case 0xa4: /* movsS */
    case 0xa5:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;

        if (prefixes & PREFIX_REPZ) {
            gen_string_ds(s, ot, gen_op_movs + 9);
        } else {
            gen_string_ds(s, ot, gen_op_movs);
        }
        break;

    case 0xaa: /* stosS */
    case 0xab:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;

        if (prefixes & PREFIX_REPZ) {
            gen_string_es(s, ot, gen_op_stos + 9);
        } else {
            gen_string_es(s, ot, gen_op_stos);
        }
        break;
    case 0xac: /* lodsS */
    case 0xad:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        if (prefixes & PREFIX_REPZ) {
            gen_string_ds(s, ot, gen_op_lods + 9);
        } else {
            gen_string_ds(s, ot, gen_op_lods);
        }
        break;
    case 0xae: /* scasS */
    case 0xaf:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
                ot = dflag ? OT_LONG : OT_WORD;
        if (prefixes & PREFIX_REPNZ) {
            if (s->cc_op != CC_OP_DYNAMIC)
                gen_op_set_cc_op(s->cc_op);
            gen_string_es(s, ot, gen_op_scas + 9 * 2);
            s->cc_op = CC_OP_DYNAMIC; /* cannot predict flags after */
        } else if (prefixes & PREFIX_REPZ) {
            if (s->cc_op != CC_OP_DYNAMIC)
                gen_op_set_cc_op(s->cc_op);
            gen_string_es(s, ot, gen_op_scas + 9);
            s->cc_op = CC_OP_DYNAMIC; /* cannot predict flags after */
        } else {
            gen_string_es(s, ot, gen_op_scas);
            s->cc_op = CC_OP_SUBB + ot;
        }
        break;

    case 0xa6: /* cmpsS */
    case 0xa7:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        if (prefixes & PREFIX_REPNZ) {
            if (s->cc_op != CC_OP_DYNAMIC)
                gen_op_set_cc_op(s->cc_op);
            gen_string_ds(s, ot, gen_op_cmps + 9 * 2);
            s->cc_op = CC_OP_DYNAMIC; /* cannot predict flags after */
        } else if (prefixes & PREFIX_REPZ) {
            if (s->cc_op != CC_OP_DYNAMIC)
                gen_op_set_cc_op(s->cc_op);
            gen_string_ds(s, ot, gen_op_cmps + 9);
            s->cc_op = CC_OP_DYNAMIC; /* cannot predict flags after */
        } else {
            gen_string_ds(s, ot, gen_op_cmps);
            s->cc_op = CC_OP_SUBB + ot;
        }
        break;
    case 0x6c: /* insS */
    case 0x6d:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        if (prefixes & PREFIX_REPZ) {
            gen_string_es(s, ot, gen_op_ins + 9);
        } else {
            gen_string_es(s, ot, gen_op_ins);
        }
        break;
    case 0x6e: /* outsS */
    case 0x6f:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        if (prefixes & PREFIX_REPZ) {
            gen_string_ds(s, ot, gen_op_outs + 9);
        } else {
            gen_string_ds(s, ot, gen_op_outs);
        }
        break;

        /************************/
        /* port I/O */
    case 0xe4:
    case 0xe5:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        val = ldub(s->pc++);
        gen_op_movl_T0_im(val);
        gen_op_in[ot]();
        gen_op_mov_reg_T1[ot][R_EAX]();
        break;
    case 0xe6:
    case 0xe7:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        val = ldub(s->pc++);
        gen_op_movl_T0_im(val);
        gen_op_mov_TN_reg[ot][1][R_EAX]();
        gen_op_out[ot]();
        break;
    case 0xec:
    case 0xed:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        gen_op_mov_TN_reg[OT_WORD][0][R_EDX]();
        gen_op_in[ot]();
        gen_op_mov_reg_T1[ot][R_EAX]();
        break;
    case 0xee:
    case 0xef:
        if ((b & 1) == 0)
            ot = OT_BYTE;
        else
            ot = dflag ? OT_LONG : OT_WORD;
        gen_op_mov_TN_reg[OT_WORD][0][R_EDX]();
        gen_op_mov_TN_reg[ot][1][R_EAX]();
        gen_op_out[ot]();
        break;

        /************************/
        /* control */
    case 0xc2: /* ret im */
        val = ldsw(s->pc);
        s->pc += 2;
        gen_pop_T0(s);
        if (s->ss32)
            gen_op_addl_ESP_im(val + (2 << s->dflag));
        else
            gen_op_addw_ESP_im(val + (2 << s->dflag));
        if (s->dflag == 0)
            gen_op_andl_T0_ffff();
        gen_op_jmp_T0();
        s->is_jmp = 1;
        break;
    case 0xc3: /* ret */
        gen_pop_T0(s);
        gen_pop_update(s);
        if (s->dflag == 0)
            gen_op_andl_T0_ffff();
        gen_op_jmp_T0();
        s->is_jmp = 1;
        break;
    case 0xca: /* lret im */
        /* XXX: not restartable */
        val = ldsw(s->pc);
        s->pc += 2;
        /* pop offset */
        gen_pop_T0(s);
        if (s->dflag == 0)
            gen_op_andl_T0_ffff();
        gen_op_jmp_T0();
        gen_pop_update(s);
        /* pop selector */
        gen_pop_T0(s);
        gen_movl_seg_T0(s, R_CS);
        gen_pop_update(s);
        /* add stack offset */
        if (s->ss32)
            gen_op_addl_ESP_im(val + (2 << s->dflag));
        else
            gen_op_addw_ESP_im(val + (2 << s->dflag));
        s->is_jmp = 1;
        break;
    case 0xcb: /* lret */
        /* XXX: not restartable */
        /* pop offset */
        gen_pop_T0(s);
        if (s->dflag == 0)
            gen_op_andl_T0_ffff();
        gen_op_jmp_T0();
        gen_pop_update(s);
        /* pop selector */
        gen_pop_T0(s);
        gen_movl_seg_T0(s, R_CS);
        gen_pop_update(s);
        s->is_jmp = 1;
        break;
    case 0xcf: /* iret */
        /* XXX: not restartable */
        /* pop offset */
        gen_pop_T0(s);
        if (s->dflag == 0)
            gen_op_andl_T0_ffff();
        gen_op_jmp_T0();
        gen_pop_update(s);
        /* pop selector */
        gen_pop_T0(s);
        gen_movl_seg_T0(s, R_CS);
        gen_pop_update(s);
        /* pop eflags */
        gen_pop_T0(s);
        if (s->dflag) {
            if (s->vm86)
                gen_op_movl_eflags_T0_vm(pc_start - s->cs_base);
            else
                gen_op_movl_eflags_T0();
        } else {
            if (s->vm86)
                gen_op_movw_eflags_T0_vm(pc_start - s->cs_base);
            else
                gen_op_movw_eflags_T0();
        }
        gen_pop_update(s);
        s->cc_op = CC_OP_EFLAGS;
        s->is_jmp = 1;
        break;
    case 0xe8: /* call im */
        {
            unsigned int next_eip;
            ot = dflag ? OT_LONG : OT_WORD;
            val = insn_get(s, ot);
            next_eip = s->pc - s->cs_base;
            val += next_eip;
            if (s->dflag == 0)
                val &= 0xffff;
            gen_op_movl_T0_im(next_eip);
            gen_push_T0(s);
            gen_op_jmp_im(val);
            s->is_jmp = 1;
        }
        break;
    case 0x9a: /* lcall im */
        {
            unsigned int selector, offset;

            ot = dflag ? OT_LONG : OT_WORD;
            offset = insn_get(s, ot);
            selector = insn_get(s, OT_WORD);

            /* push return segment + offset */
            gen_op_movl_T0_seg(R_CS);
            gen_push_T0(s);
            next_eip = s->pc - s->cs_base;
            gen_op_movl_T0_im(next_eip);
            gen_push_T0(s);

            /* change cs and pc */
            gen_op_movl_T0_im(selector);
            gen_movl_seg_T0(s, R_CS);
            gen_op_jmp_im((unsigned long)offset);
            s->is_jmp = 1;
        }
        break;
    case 0xe9: /* jmp */
        ot = dflag ? OT_LONG : OT_WORD;
        val = insn_get(s, ot);
        val += s->pc - s->cs_base;
        if (s->dflag == 0)
            val = val & 0xffff;
        gen_op_jmp_im(val);
        s->is_jmp = 1;
        break;
    case 0xea: /* ljmp im */
        {
            unsigned int selector, offset;

            ot = dflag ? OT_LONG : OT_WORD;
            offset = insn_get(s, ot);
            selector = insn_get(s, OT_WORD);

            /* change cs and pc */
            gen_op_movl_T0_im(selector);
            gen_movl_seg_T0(s, R_CS);
            gen_op_jmp_im((unsigned long)offset);
            s->is_jmp = 1;
        }
        break;
    case 0xeb: /* jmp Jb */
        val = (int8_t)insn_get(s, OT_BYTE);
        val += s->pc - s->cs_base;
        if (s->dflag == 0)
            val = val & 0xffff;
        gen_op_jmp_im(val);
        s->is_jmp = 1;
        break;
    case 0x70 ... 0x7f: /* jcc Jb */
        val = (int8_t)insn_get(s, OT_BYTE);
        goto do_jcc;
    case 0x180 ... 0x18f: /* jcc Jv */
        if (dflag) {
            val = insn_get(s, OT_LONG);
        } else {
            val = (int16_t)insn_get(s, OT_WORD);
        }
    do_jcc:
        next_eip = s->pc - s->cs_base;
        val += next_eip;
        if (s->dflag == 0)
            val &= 0xffff;
        gen_jcc(s, b, val, next_eip);
        s->is_jmp = 1;
        break;

    case 0x190 ... 0x19f: /* setcc Gv */
        modrm = ldub(s->pc++);
        gen_setcc(s, b);
        gen_ldst_modrm(s, modrm, OT_BYTE, OR_TMP0, 1);
        break;
    case 0x140 ... 0x14f: /* cmov Gv, Ev */
        ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        reg = (modrm >> 3) & 7;
        mod = (modrm >> 6) & 3;
        gen_setcc(s, b);
        if (mod != 3) {
            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
            gen_op_ld_T1_A0[ot]();
        } else {
            rm = modrm & 7;
            gen_op_mov_TN_reg[ot][1][rm]();
        }
        gen_op_cmov_reg_T1_T0[ot - OT_WORD][reg]();
        break;

        /************************/
        /* flags */
    case 0x9c: /* pushf */
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        if (s->vm86)
            gen_op_movl_T0_eflags_vm();
        else
            gen_op_movl_T0_eflags();
        gen_push_T0(s);
        break;
    case 0x9d: /* popf */
        gen_pop_T0(s);
        if (s->dflag) {
            if (s->vm86)
                gen_op_movl_eflags_T0_vm(pc_start - s->cs_base);
            else
                gen_op_movl_eflags_T0();
        } else {
            if (s->vm86)
                gen_op_movw_eflags_T0_vm(pc_start - s->cs_base);
            else
                gen_op_movw_eflags_T0();
        }
        gen_pop_update(s);
        s->cc_op = CC_OP_EFLAGS;
        break;
    case 0x9e: /* sahf */
        gen_op_mov_TN_reg[OT_BYTE][0][R_AH]();
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        gen_op_movb_eflags_T0();
        s->cc_op = CC_OP_EFLAGS;
        break;
    case 0x9f: /* lahf */
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        gen_op_movl_T0_eflags();
        gen_op_mov_reg_T0[OT_BYTE][R_AH]();
        break;
    case 0xf5: /* cmc */
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        gen_op_cmc();
        s->cc_op = CC_OP_EFLAGS;
        break;
    case 0xf8: /* clc */
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        gen_op_clc();
        s->cc_op = CC_OP_EFLAGS;
        break;
    case 0xf9: /* stc */
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        gen_op_stc();
        s->cc_op = CC_OP_EFLAGS;
        break;
    case 0xfc: /* cld */
        gen_op_cld();
        break;
    case 0xfd: /* std */
        gen_op_std();
        break;

        /************************/
        /* bit operations */
    case 0x1ba: /* bt/bts/btr/btc Gv, im */
        ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        op = (modrm >> 3) & 7;
        mod = (modrm >> 6) & 3;
        rm = modrm & 7;
        if (mod != 3) {
            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
            gen_op_ld_T0_A0[ot]();
        } else {
            gen_op_mov_TN_reg[ot][0][rm]();
        }
        /* load shift */
        val = ldub(s->pc++);
        gen_op_movl_T1_im(val);
        if (op < 4)
            goto illegal_op;
        op -= 4;
        gen_op_btx_T0_T1_cc[ot - OT_WORD][op]();
        s->cc_op = CC_OP_SARB + ot;
        if (op != 0) {
            if (mod != 3)
                gen_op_st_T0_A0[ot]();
            else
                gen_op_mov_reg_T0[ot][rm]();
        }
        break;
    case 0x1a3: /* bt Gv, Ev */
        op = 0;
        goto do_btx;
    case 0x1ab: /* bts */
        op = 1;
        goto do_btx;
    case 0x1b3: /* btr */
        op = 2;
        goto do_btx;
    case 0x1bb: /* btc */
        op = 3;
    do_btx:
        ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        reg = (modrm >> 3) & 7;
        mod = (modrm >> 6) & 3;
        rm = modrm & 7;
        gen_op_mov_TN_reg[OT_LONG][1][reg]();
        if (mod != 3) {
            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
            /* specific case: we need to add a displacement */
            if (ot == OT_WORD)
                gen_op_add_bitw_A0_T1();
            else
                gen_op_add_bitl_A0_T1();
            gen_op_ld_T0_A0[ot]();
        } else {
            gen_op_mov_TN_reg[ot][0][rm]();
        }
        gen_op_btx_T0_T1_cc[ot - OT_WORD][op]();
        s->cc_op = CC_OP_SARB + ot;
        if (op != 0) {
            if (mod != 3)
                gen_op_st_T0_A0[ot]();
            else
                gen_op_mov_reg_T0[ot][rm]();
        }
        break;
    case 0x1bc: /* bsf */
    case 0x1bd: /* bsr */
        ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        reg = (modrm >> 3) & 7;
        gen_ldst_modrm(s, modrm, ot, OR_TMP0, 0);
        gen_op_bsx_T0_cc[ot - OT_WORD][b & 1]();
        /* NOTE: we always write back the result. Intel doc says it is
           undefined if T0 == 0 */
        gen_op_mov_reg_T0[ot][reg]();
        s->cc_op = CC_OP_LOGICB + ot;
        break;
        /************************/
        /* bcd */
    case 0x27: /* daa */
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        gen_op_daa();
        s->cc_op = CC_OP_EFLAGS;
        break;
    case 0x2f: /* das */
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        gen_op_das();
        s->cc_op = CC_OP_EFLAGS;
        break;
    case 0x37: /* aaa */
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        gen_op_aaa();
        s->cc_op = CC_OP_EFLAGS;
        break;
    case 0x3f: /* aas */
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        gen_op_aas();
        s->cc_op = CC_OP_EFLAGS;
        break;
    case 0xd4: /* aam */
        val = ldub(s->pc++);
        gen_op_aam(val);
        s->cc_op = CC_OP_LOGICB;
        break;
    case 0xd5: /* aad */
        val = ldub(s->pc++);
        gen_op_aad(val);
        s->cc_op = CC_OP_LOGICB;
        break;
        /************************/
        /* misc */
    case 0x90: /* nop */
        break;
    case 0xcc: /* int3 */
        gen_op_int3((long)pc_start);
        s->is_jmp = 1;
        break;
    case 0xcd: /* int N */
        val = ldub(s->pc++);
        /* XXX: currently we ignore the interrupt number */
        gen_op_int_im(pc_start - s->cs_base);
        s->is_jmp = 1;
        break;
    case 0xce: /* into */
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        gen_op_into();
        break;
    case 0xfa: /* cli */
        if (s->vm86)
            gen_op_cli_vm();
        else
            gen_op_cli();
        break;
    case 0xfb: /* sti */
        if (s->vm86)
            gen_op_sti_vm(pc_start - s->cs_base);
        else
            gen_op_sti();
        break;
    case 0x62: /* bound */
        ot = dflag ? OT_LONG : OT_WORD;
        modrm = ldub(s->pc++);
        reg = (modrm >> 3) & 7;
        mod = (modrm >> 6) & 3;
        if (mod == 3)
            goto illegal_op;
        gen_op_mov_reg_T0[ot][reg]();
        gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);
        if (ot == OT_WORD)
            gen_op_boundw();
        else
            gen_op_boundl();
        break;
    case 0x1c8 ... 0x1cf: /* bswap reg */
        reg = b & 7;
        gen_op_mov_TN_reg[OT_LONG][0][reg]();
        gen_op_bswapl_T0();
        gen_op_mov_reg_T0[OT_LONG][reg]();
        break;
    case 0xd6: /* salc */
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        gen_op_salc();
        break;
    case 0xe0: /* loopnz */
    case 0xe1: /* loopz */
        if (s->cc_op != CC_OP_DYNAMIC)
            gen_op_set_cc_op(s->cc_op);
        /* FALL THRU */
    case 0xe2: /* loop */
    case 0xe3: /* jecxz */
        val = (int8_t)insn_get(s, OT_BYTE);
        next_eip = s->pc - s->cs_base;
        val += next_eip;
        if (s->dflag == 0)
            val &= 0xffff;
        gen_op_loop[s->aflag][b & 3](val, next_eip);
        s->is_jmp = 1;
        break;
    case 0x131: /* rdtsc */
        gen_op_rdtsc();
        break;
    case 0x1a2: /* cpuid */
        gen_op_cpuid();
        break;
    default:
        goto illegal_op;
    }
    /* lock generation */
    if (s->prefix & PREFIX_LOCK)
        gen_op_unlock();
    return (long)s->pc;
 illegal_op:
    /* XXX: ensure that no lock was generated */
    return -1;
}

#define CC_OSZAPC (CC_O | CC_S | CC_Z | CC_A | CC_P | CC_C)
#define CC_OSZAP (CC_O | CC_S | CC_Z | CC_A | CC_P)

/* flags read by an operation */
/* 指令需要读取的标志 */
static uint16_t opc_read_flags[NB_OPS] = {
    [INDEX_op_aas] = CC_A,
    [INDEX_op_aaa] = CC_A,
    [INDEX_op_das] = CC_A | CC_C,
    [INDEX_op_daa] = CC_A | CC_C,

    [INDEX_op_adcb_T0_T1_cc] = CC_C,
    [INDEX_op_adcw_T0_T1_cc] = CC_C,
    [INDEX_op_adcl_T0_T1_cc] = CC_C,
    [INDEX_op_sbbb_T0_T1_cc] = CC_C,
    [INDEX_op_sbbw_T0_T1_cc] = CC_C,
    [INDEX_op_sbbl_T0_T1_cc] = CC_C,

    [INDEX_op_into] = CC_O,

    [INDEX_op_jo_cc] = CC_O,
    [INDEX_op_jb_cc] = CC_C,
    [INDEX_op_jz_cc] = CC_Z,
    [INDEX_op_jbe_cc] = CC_Z | CC_C,
    [INDEX_op_js_cc] = CC_S,
    [INDEX_op_jp_cc] = CC_P,
    [INDEX_op_jl_cc] = CC_O | CC_S,
    [INDEX_op_jle_cc] = CC_O | CC_S | CC_Z,

    [INDEX_op_jb_subb] = CC_C,
    [INDEX_op_jb_subw] = CC_C,
    [INDEX_op_jb_subl] = CC_C,

    [INDEX_op_jz_subb] = CC_Z,
    [INDEX_op_jz_subw] = CC_Z,
    [INDEX_op_jz_subl] = CC_Z,

    [INDEX_op_jbe_subb] = CC_Z | CC_C,
    [INDEX_op_jbe_subw] = CC_Z | CC_C,
    [INDEX_op_jbe_subl] = CC_Z | CC_C,

    [INDEX_op_js_subb] = CC_S,
    [INDEX_op_js_subw] = CC_S,
    [INDEX_op_js_subl] = CC_S,

    [INDEX_op_jl_subb] = CC_O | CC_S,
    [INDEX_op_jl_subw] = CC_O | CC_S,
    [INDEX_op_jl_subl] = CC_O | CC_S,

    [INDEX_op_jle_subb] = CC_O | CC_S | CC_Z,
    [INDEX_op_jle_subw] = CC_O | CC_S | CC_Z,
    [INDEX_op_jle_subl] = CC_O | CC_S | CC_Z,

    [INDEX_op_loopnzw] = CC_Z,
    [INDEX_op_loopnzl] = CC_Z,
    [INDEX_op_loopzw] = CC_Z,
    [INDEX_op_loopzl] = CC_Z,

    [INDEX_op_seto_T0_cc] = CC_O,
    [INDEX_op_setb_T0_cc] = CC_C,
    [INDEX_op_setz_T0_cc] = CC_Z,
    [INDEX_op_setbe_T0_cc] = CC_Z | CC_C,
    [INDEX_op_sets_T0_cc] = CC_S,
    [INDEX_op_setp_T0_cc] = CC_P,
    [INDEX_op_setl_T0_cc] = CC_O | CC_S,
    [INDEX_op_setle_T0_cc] = CC_O | CC_S | CC_Z,

    [INDEX_op_setb_T0_subb] = CC_C,
    [INDEX_op_setb_T0_subw] = CC_C,
    [INDEX_op_setb_T0_subl] = CC_C,

    [INDEX_op_setz_T0_subb] = CC_Z,
    [INDEX_op_setz_T0_subw] = CC_Z,
    [INDEX_op_setz_T0_subl] = CC_Z,

    [INDEX_op_setbe_T0_subb] = CC_Z | CC_C,
    [INDEX_op_setbe_T0_subw] = CC_Z | CC_C,
    [INDEX_op_setbe_T0_subl] = CC_Z | CC_C,

    [INDEX_op_sets_T0_subb] = CC_S,
    [INDEX_op_sets_T0_subw] = CC_S,
    [INDEX_op_sets_T0_subl] = CC_S,

    [INDEX_op_setl_T0_subb] = CC_O | CC_S,
    [INDEX_op_setl_T0_subw] = CC_O | CC_S,
    [INDEX_op_setl_T0_subl] = CC_O | CC_S,

    [INDEX_op_setle_T0_subb] = CC_O | CC_S | CC_Z,
    [INDEX_op_setle_T0_subw] = CC_O | CC_S | CC_Z,
    [INDEX_op_setle_T0_subl] = CC_O | CC_S | CC_Z,

    [INDEX_op_movl_T0_eflags] = CC_OSZAPC,
    [INDEX_op_movl_T0_eflags_vm] = CC_OSZAPC,
    [INDEX_op_cmc] = CC_C,
    [INDEX_op_salc] = CC_C,

    [INDEX_op_rclb_T0_T1_cc] = CC_C,
    [INDEX_op_rclw_T0_T1_cc] = CC_C,
    [INDEX_op_rcll_T0_T1_cc] = CC_C,
    [INDEX_op_rcrb_T0_T1_cc] = CC_C,
    [INDEX_op_rcrw_T0_T1_cc] = CC_C,
    [INDEX_op_rcrl_T0_T1_cc] = CC_C,
};

/* flags written by an operation */
/* 这里以数组的方式记录了每条指令可能修改的标志 */
static uint16_t opc_write_flags[NB_OPS] = {
    [INDEX_op_addl_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_orl_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_adcb_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_adcw_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_adcl_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_sbbb_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_sbbw_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_sbbl_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_andl_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_subl_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_xorl_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_cmpl_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_negl_T0_cc] = CC_OSZAPC,
    [INDEX_op_incl_T0_cc] = CC_OSZAP,
    [INDEX_op_decl_T0_cc] = CC_OSZAP,
    [INDEX_op_testl_T0_T1_cc] = CC_OSZAPC,

    [INDEX_op_mulb_AL_T0] = CC_OSZAPC,
    [INDEX_op_imulb_AL_T0] = CC_OSZAPC,
    [INDEX_op_mulw_AX_T0] = CC_OSZAPC,
    [INDEX_op_imulw_AX_T0] = CC_OSZAPC,
    [INDEX_op_mull_EAX_T0] = CC_OSZAPC,
    [INDEX_op_imull_EAX_T0] = CC_OSZAPC,
    [INDEX_op_imulw_T0_T1] = CC_OSZAPC,
    [INDEX_op_imull_T0_T1] = CC_OSZAPC,

    /* bcd */
    [INDEX_op_aam] = CC_OSZAPC,
    [INDEX_op_aad] = CC_OSZAPC,
    [INDEX_op_aas] = CC_OSZAPC,
    [INDEX_op_aaa] = CC_OSZAPC,
    [INDEX_op_das] = CC_OSZAPC,
    [INDEX_op_daa] = CC_OSZAPC,

    [INDEX_op_movb_eflags_T0] = CC_S | CC_Z | CC_A | CC_P | CC_C,
    [INDEX_op_movw_eflags_T0] = CC_OSZAPC,
    [INDEX_op_movw_eflags_T0_vm] = CC_OSZAPC,
    [INDEX_op_movl_eflags_T0] = CC_OSZAPC,
    [INDEX_op_movl_eflags_T0_vm] = CC_OSZAPC,
    [INDEX_op_clc] = CC_C,
    [INDEX_op_stc] = CC_C,
    [INDEX_op_cmc] = CC_C,

    [INDEX_op_rolb_T0_T1_cc] = CC_O | CC_C,
    [INDEX_op_rolw_T0_T1_cc] = CC_O | CC_C,
    [INDEX_op_roll_T0_T1_cc] = CC_O | CC_C,
    [INDEX_op_rorb_T0_T1_cc] = CC_O | CC_C,
    [INDEX_op_rorw_T0_T1_cc] = CC_O | CC_C,
    [INDEX_op_rorl_T0_T1_cc] = CC_O | CC_C,

    [INDEX_op_rclb_T0_T1_cc] = CC_O | CC_C,
    [INDEX_op_rclw_T0_T1_cc] = CC_O | CC_C,
    [INDEX_op_rcll_T0_T1_cc] = CC_O | CC_C,
    [INDEX_op_rcrb_T0_T1_cc] = CC_O | CC_C,
    [INDEX_op_rcrw_T0_T1_cc] = CC_O | CC_C,
    [INDEX_op_rcrl_T0_T1_cc] = CC_O | CC_C,

    [INDEX_op_shlb_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_shlw_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_shll_T0_T1_cc] = CC_OSZAPC,

    [INDEX_op_shrb_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_shrw_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_shrl_T0_T1_cc] = CC_OSZAPC,

    [INDEX_op_sarb_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_sarw_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_sarl_T0_T1_cc] = CC_OSZAPC,

    [INDEX_op_shldw_T0_T1_ECX_cc] = CC_OSZAPC,
    [INDEX_op_shldl_T0_T1_ECX_cc] = CC_OSZAPC,
    [INDEX_op_shldw_T0_T1_im_cc] = CC_OSZAPC,
    [INDEX_op_shldl_T0_T1_im_cc] = CC_OSZAPC,

    [INDEX_op_shrdw_T0_T1_ECX_cc] = CC_OSZAPC,
    [INDEX_op_shrdl_T0_T1_ECX_cc] = CC_OSZAPC,
    [INDEX_op_shrdw_T0_T1_im_cc] = CC_OSZAPC,
    [INDEX_op_shrdl_T0_T1_im_cc] = CC_OSZAPC,

    [INDEX_op_btw_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_btl_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_btsw_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_btsl_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_btrw_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_btrl_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_btcw_T0_T1_cc] = CC_OSZAPC,
    [INDEX_op_btcl_T0_T1_cc] = CC_OSZAPC,

    [INDEX_op_bsfw_T0_cc] = CC_OSZAPC,
    [INDEX_op_bsfl_T0_cc] = CC_OSZAPC,
    [INDEX_op_bsrw_T0_cc] = CC_OSZAPC,
    [INDEX_op_bsrl_T0_cc] = CC_OSZAPC,

#undef STRINGOP
#define STRINGOP(x) \
    [INDEX_op_ ## x ## b_fast] = CC_OSZAPC, \
    [INDEX_op_ ## x ## w_fast] = CC_OSZAPC, \
    [INDEX_op_ ## x ## l_fast] = CC_OSZAPC, \
    [INDEX_op_ ## x ## b_a32] = CC_OSZAPC, \
    [INDEX_op_ ## x ## w_a32] = CC_OSZAPC, \
    [INDEX_op_ ## x ## l_a32] = CC_OSZAPC, \
    [INDEX_op_ ## x ## b_a16] = CC_OSZAPC, \
    [INDEX_op_ ## x ## w_a16] = CC_OSZAPC, \
    [INDEX_op_ ## x ## l_a16] = CC_OSZAPC,

    STRINGOP(scas)
    STRINGOP(repz_scas)
    STRINGOP(repnz_scas)
    STRINGOP(cmps)
    STRINGOP(repz_cmps)
    STRINGOP(repnz_cmps)

    [INDEX_op_cmpxchgb_T0_T1_EAX_cc] = CC_OSZAPC,
    [INDEX_op_cmpxchgw_T0_T1_EAX_cc] = CC_OSZAPC,
    [INDEX_op_cmpxchgl_T0_T1_EAX_cc] = CC_OSZAPC,

    [INDEX_op_cmpxchg8b] = CC_Z,
};

/* simpler form of an operation if no flags need to be generated */
static uint16_t opc_simpler[NB_OPS] = {
    [INDEX_op_addl_T0_T1_cc] = INDEX_op_addl_T0_T1,
    [INDEX_op_orl_T0_T1_cc] = INDEX_op_orl_T0_T1,
    [INDEX_op_andl_T0_T1_cc] = INDEX_op_andl_T0_T1,
    [INDEX_op_subl_T0_T1_cc] = INDEX_op_subl_T0_T1,
    [INDEX_op_xorl_T0_T1_cc] = INDEX_op_xorl_T0_T1,
    [INDEX_op_negl_T0_cc] = INDEX_op_negl_T0,
    [INDEX_op_incl_T0_cc] = INDEX_op_incl_T0,
    [INDEX_op_decl_T0_cc] = INDEX_op_decl_T0,

    [INDEX_op_rolb_T0_T1_cc] = INDEX_op_rolb_T0_T1,
    [INDEX_op_rolw_T0_T1_cc] = INDEX_op_rolw_T0_T1,
    [INDEX_op_roll_T0_T1_cc] = INDEX_op_roll_T0_T1,

    [INDEX_op_rorb_T0_T1_cc] = INDEX_op_rorb_T0_T1,
    [INDEX_op_rorw_T0_T1_cc] = INDEX_op_rorw_T0_T1,
    [INDEX_op_rorl_T0_T1_cc] = INDEX_op_rorl_T0_T1,

    [INDEX_op_shlb_T0_T1_cc] = INDEX_op_shlb_T0_T1,
    [INDEX_op_shlw_T0_T1_cc] = INDEX_op_shlw_T0_T1,
    [INDEX_op_shll_T0_T1_cc] = INDEX_op_shll_T0_T1,

    [INDEX_op_shrb_T0_T1_cc] = INDEX_op_shrb_T0_T1,
    [INDEX_op_shrw_T0_T1_cc] = INDEX_op_shrw_T0_T1,
    [INDEX_op_shrl_T0_T1_cc] = INDEX_op_shrl_T0_T1,

    [INDEX_op_sarb_T0_T1_cc] = INDEX_op_sarb_T0_T1,
    [INDEX_op_sarw_T0_T1_cc] = INDEX_op_sarw_T0_T1,
    [INDEX_op_sarl_T0_T1_cc] = INDEX_op_sarl_T0_T1,
};

static void optimize_flags_init(void)
{
    int i;
    /* put default values in arrays */
    for(i = 0; i < NB_OPS; i++) {
        if (opc_simpler[i] == 0)
            opc_simpler[i] = i;
    }
}

/* CPU flags computation optimization: we move backward thru the
   generated code to see which flags are needed. The operation is
   modified if suitable */
/* CPU标志(flags)计算优化,这个函数属于优化,从功能的角度,可以省略掉 */
static void optimize_flags(uint16_t *opc_buf, int opc_buf_len)
{
    uint16_t *opc_ptr;
    int live_flags, write_flags, op;

    opc_ptr = opc_buf + opc_buf_len; /* 指向最后一条指令 */
    /* live_flags contains the flags needed by the next instructions
       in the code. At the end of the bloc, we consider that all the
       flags are live. */
    /* live_flags包含被下一条指令所需的标志,在bloc的最后,我们认为所有的标志都需要 */
    live_flags = CC_OSZAPC;
    while (opc_ptr > opc_buf) {
        op = *--opc_ptr; /* 从后往前遍历 */
        /* if none of the flags written by the instruction is used,
           then we can try to find a simpler instruction */
        /* 如果指令不会更改任何标志,那么我们可以尝试将其替换为一条更加简单的指令
         * live_flags & write_flags为0表示本条指令不会更改下一条指令所读取的标志
         * 更加直白一点,那就是本条指令和下一条指令无关联
         */
        write_flags = opc_write_flags[op];
        if ((live_flags & write_flags) == 0) {
            *opc_ptr = opc_simpler[op];
        }
        /* compute the live flags before the instruction */
        /* 计算该指令的前一条指令所需要的live flags */
        live_flags &= ~write_flags;
        /* 指令需要读取的标志,记住,这个live_flags供上一条指令使用,它表示下一条指令(也就是
         * 本指令)所需要的标志
         */
        live_flags |= opc_read_flags[op];
    }
}


#ifdef DEBUG_DISAS
static const char *op_str[] = {
#define DEF(s, n) #s,
#include "opc-i386.h"
#undef DEF
};

static uint8_t op_nb_args[] = {
#define DEF(s, n) n,
#include "opc-i386.h"
#undef DEF
};

static void dump_ops(const uint16_t *opc_buf, const uint32_t *opparam_buf)
{
    const uint16_t *opc_ptr;
    const uint32_t *opparam_ptr;
    int c, n, i;

    opc_ptr = opc_buf;
    opparam_ptr = opparam_buf;
    for(;;) {
        c = *opc_ptr++;
        n = op_nb_args[c];
        fprintf(logfile, "0x%04x: %s", opc_ptr - opc_buf - 1, op_str[c]);
        for(i = 0; i < n; i++) {
            fprintf(logfile, " 0x%x", opparam_ptr[i]);
        }
        fprintf(logfile, "\n");
        if (c == INDEX_op_end)
            break;
        opparam_ptr += n;
    }
}

#endif

/* XXX: make this buffer thread safe */
/* XXX: make safe guess about sizes */
#define MAX_OP_PER_INSTR 32
#define OPC_BUF_SIZE 512
#define OPC_MAX_SIZE (OPC_BUF_SIZE - MAX_OP_PER_INSTR)

#define OPPARAM_BUF_SIZE (OPC_BUF_SIZE * 3)

static uint16_t gen_opc_buf[OPC_BUF_SIZE];
static uint32_t gen_opparam_buf[OPPARAM_BUF_SIZE];

/* return non zero if the very first instruction is invalid so that
   the virtual CPU can trigger an exception. */
int cpu_x86_gen_code(uint8_t *gen_code_buf, int max_code_size,
                     int *gen_code_size_ptr,
                     uint8_t *pc_start,  uint8_t *cs_base, int flags)
{
    DisasContext dc1, *dc = &dc1;
    uint8_t *pc_ptr;
    uint16_t *gen_opc_end;
    int gen_code_size;
    long ret;
#ifdef DEBUG_DISAS
    struct disassemble_info disasm_info;
#endif

    /* generate intermediate code */
    /* 产生中间代码 */
    dc->code32 = (flags >> GEN_FLAG_CODE32_SHIFT) & 1; /* 代码段 */
    dc->ss32 = (flags >> GEN_FLAG_SS32_SHIFT) & 1; /* 栈段 */
    dc->addseg = (flags >> GEN_FLAG_ADDSEG_SHIFT) & 1;
    dc->f_st = (flags >> GEN_FLAG_ST_SHIFT) & 7;
    dc->vm86 = (flags >> GEN_FLAG_VM_SHIFT) & 1;
    dc->cc_op = CC_OP_DYNAMIC; /* 动态获取flags */
    dc->cs_base = cs_base;

    gen_opc_ptr = gen_opc_buf;
    gen_opc_end = gen_opc_buf + OPC_MAX_SIZE;
    gen_opparam_ptr = gen_opparam_buf;

    dc->is_jmp = 0;
    pc_ptr = pc_start;
    do {
        ret = disas_insn(dc, pc_ptr); /* 反汇编指令 */
        if (ret == -1) {
            /* we trigger an illegal instruction operation only if it
               is the first instruction. Otherwise, we simply stop
               generating the code just before it */
            if (pc_ptr == pc_start)
                return -1;
            else
                break;
        }
        pc_ptr = (void *)ret;
    } while (!dc->is_jmp && gen_opc_ptr < gen_opc_end);
    /* we must store the eflags state if it is not already done */
    if (dc->cc_op != CC_OP_DYNAMIC)
        gen_op_set_cc_op(dc->cc_op);
    /* 更新模拟cpu的eip寄存器的值 */
    if (dc->is_jmp != 1) {
        /* we add an additionnal jmp to update the simulated PC */
        gen_op_jmp_im(ret - (unsigned long)dc->cs_base);
    }
    *gen_opc_ptr = INDEX_op_end;

    /* optimize flag computations */
#ifdef DEBUG_DISAS
    if (loglevel) {
        uint8_t *pc;
        int count;

        INIT_DISASSEMBLE_INFO(disasm_info, logfile, fprintf);
#if 0
        disasm_info.flavour = bfd_get_flavour (abfd);
        disasm_info.arch = bfd_get_arch (abfd);
        disasm_info.mach = bfd_get_mach (abfd);
#endif
        disasm_info.endian = BFD_ENDIAN_LITTLE;
        if (dc->code32)
            disasm_info.mach = bfd_mach_i386_i386;
        else
            disasm_info.mach = bfd_mach_i386_i8086;
        fprintf(logfile, "----------------\n");
        fprintf(logfile, "IN:\n");
        disasm_info.buffer = pc_start;
        disasm_info.buffer_vma = (unsigned long)pc_start;
        disasm_info.buffer_length = pc_ptr - pc_start;
        pc = pc_start;
        while (pc < pc_ptr) {
            fprintf(logfile, "0x%08lx:  ", (long)pc);
			/* 打印出i386指令 */
            count = print_insn_i386((unsigned long)pc, &disasm_info);
            fprintf(logfile, "\n");
            pc += count;
        }
        fprintf(logfile, "\n");

        fprintf(logfile, "OP:\n");
        dump_ops(gen_opc_buf, gen_opparam_buf);
        fprintf(logfile, "\n");
    }
#endif

    /* optimize flag computations */
    optimize_flags(gen_opc_buf, gen_opc_ptr - gen_opc_buf);

#ifdef DEBUG_DISAS
    if (loglevel) {
        fprintf(logfile, "AFTER FLAGS OPT:\n");
        dump_ops(gen_opc_buf, gen_opparam_buf);
        fprintf(logfile, "\n");
    }
#endif

    /* generate machine code */
	/* 生成机器码 */
    gen_code_size = dyngen_code(gen_code_buf, gen_opc_buf, gen_opparam_buf);
    flush_icache_range((unsigned long)gen_code_buf, (unsigned long)(gen_code_buf + gen_code_size));
    *gen_code_size_ptr = gen_code_size;

#ifdef DEBUG_DISAS
    if (loglevel) {
        uint8_t *pc;
        int count;

        INIT_DISASSEMBLE_INFO(disasm_info, logfile, fprintf);
#if 0
        disasm_info.flavour = bfd_get_flavour (abfd);
        disasm_info.arch = bfd_get_arch (abfd);
        disasm_info.mach = bfd_get_mach (abfd);
#endif
#ifdef WORDS_BIGENDIAN
        disasm_info.endian = BFD_ENDIAN_BIG;
#else
        disasm_info.endian = BFD_ENDIAN_LITTLE;
#endif
        disasm_info.mach = bfd_mach_i386_i386;

        pc = gen_code_buf; /* pc指针指向第一条生成的代码 */
        disasm_info.buffer = pc;
        disasm_info.buffer_vma = (unsigned long)pc;
        disasm_info.buffer_length = *gen_code_size_ptr;
        fprintf(logfile, "OUT: [size=%d]\n", *gen_code_size_ptr);
        while (pc < gen_code_buf + *gen_code_size_ptr) {
            fprintf(logfile, "0x%08lx:  ", (long)pc);
			/* 打印出转换后的i386指令 */
            count = print_insn_i386((unsigned long)pc, &disasm_info);
            fprintf(logfile, "\n");
            pc += count;
        }
        fprintf(logfile, "\n");
        fflush(logfile);
    }
#endif
    return 0;
}

/* 设置运行环境 */
CPUX86State *cpu_x86_init(void)
{
    CPUX86State *env;
    int i;
    static int inited;

    cpu_x86_tblocks_init();

    env = malloc(sizeof(CPUX86State));
    if (!env)
        return NULL;
    memset(env, 0, sizeof(CPUX86State));
    /* basic FPU init */
    for(i = 0;i < 8; i++)
        env->fptags[i] = 1;
    env->fpuc = 0x37f;
    /* flags setup : we activate the IRQs by default as in user mode */
    env->eflags = 0x2 | IF_MASK;

    /* init various static tables */
    if (!inited) {
        inited = 1;
        optimize_flags_init();
    }
    return env;
}

void cpu_x86_close(CPUX86State *env)
{
    free(env);
}
