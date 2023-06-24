/*
 *  PPC emulation cpu definitions for qemu.
 * 
 *  Copyright (c) 2003 Jocelyn Mayer
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
#if !defined (__CPU_PPC_H__)
#define __CPU_PPC_H__

#define TARGET_LONG_BITS 32

#include "cpu-defs.h"

//#define USE_OPEN_FIRMWARE

/***                          Sign extend constants                        ***/
/* 8 to 32 bits */
static inline int32_t s_ext8 (uint8_t value)
{
    int8_t *tmp = &value;

    return *tmp;
}

/* 16 to 32 bits */
static inline int32_t s_ext16 (uint16_t value)
{
    int16_t *tmp = &value;

    return *tmp;
}

#include "config.h"
#include <setjmp.h>

/* Instruction types */
enum {
    PPC_NONE     = 0x0000,
    PPC_INTEGER  = 0x0001, /* CPU has integer operations instructions        */
    PPC_FLOAT    = 0x0002, /* CPU has floating point operations instructions */
    PPC_FLOW     = 0x0004, /* CPU has flow control instructions              */
    PPC_MEM      = 0x0008, /* CPU has virtual memory instructions            */
    PPC_RES      = 0x0010, /* CPU has ld/st with reservation instructions    */
    PPC_CACHE    = 0x0020, /* CPU has cache control instructions             */
    PPC_MISC     = 0x0040, /* CPU has spr/msr access instructions            */
    PPC_EXTERN   = 0x0080, /* CPU has external control instructions          */
    PPC_SEGMENT  = 0x0100, /* CPU has memory segment instructions            */
    PPC_CACHE_OPT= 0x0200,
    PPC_FLOAT_OPT= 0x0400,
    PPC_MEM_OPT  = 0x0800,
};

#define PPC_COMMON  (PPC_INTEGER | PPC_FLOAT | PPC_FLOW | PPC_MEM |           \
                     PPC_RES | PPC_CACHE | PPC_MISC | PPC_SEGMENT)
/* PPC 604 */
#define PPC_604 (PPC_INTEGER | PPC_FLOAT | PPC_FLOW | PPC_MEM |               \
                 PPC_RES | PPC_CACHE | PPC_MISC | PPC_EXTERN | PPC_SEGMENT    \
                 PPC_MEM_OPT)
/* PPC 740/745/750/755 (aka G3) has external access instructions */
#define PPC_750 (PPC_INTEGER | PPC_FLOAT | PPC_FLOW | PPC_MEM |               \
                 PPC_RES | PPC_CACHE | PPC_MISC | PPC_EXTERN | PPC_SEGMENT)

typedef struct ppc_tb_t ppc_tb_t;

/* Supervisor mode registers */
/* Machine state register */
#define MSR_POW 18
#define MSR_ILE 16
#define MSR_EE  15
#define MSR_PR  14
#define MSR_FP  13
#define MSR_ME  12
#define MSR_FE0 11
#define MSR_SE  10
#define MSR_BE  9
#define MSR_FE1 8
#define MSR_IP 6
#define MSR_IR 5
#define MSR_DR 4
#define MSR_RI 1
#define MSR_LE 0
#define msr_pow env->msr[MSR_POW]
#define msr_ile env->msr[MSR_ILE]
#define msr_ee  env->msr[MSR_EE]
#define msr_pr  env->msr[MSR_PR]
#define msr_fp  env->msr[MSR_FP]
#define msr_me  env->msr[MSR_ME]
#define msr_fe0 env->msr[MSR_FE0]
#define msr_se  env->msr[MSR_SE]
#define msr_be  env->msr[MSR_BE]
#define msr_fe1 env->msr[MSR_FE1]
#define msr_ip  env->msr[MSR_IP]
#define msr_ir  env->msr[MSR_IR]
#define msr_dr  env->msr[MSR_DR]
#define msr_ri  env->msr[MSR_RI]
#define msr_le  env->msr[MSR_LE]

/* Segment registers */
typedef struct CPUPPCState {
    /* general purpose registers */
    uint32_t gpr[32];
    /* floating point registers */
    double fpr[32];
    /* segment registers */
    uint32_t sdr1;
    uint32_t sr[16];
    /* XER */
    uint8_t xer[4];
    /* Reservation address */
    uint32_t reserve;
    /* machine state register */
    uint8_t msr[32];
    /* condition register */
    uint8_t crf[8];
    /* floating point status and control register */
    uint8_t fpscr[8];
    uint32_t nip;
    /* special purpose registers */
    uint32_t lr;
    uint32_t ctr;
    /* BATs */
    uint32_t DBAT[2][8];
    uint32_t IBAT[2][8];
    /* all others */
    uint32_t spr[1024];
    /* qemu dedicated */
     /* temporary float registers */
    double ft0;
    double ft1;
    double ft2;
    int interrupt_request;
    jmp_buf jmp_env;
    int exception_index;
    int error_code;
    int access_type; /* when a memory exception occurs, the access
                        type is stored here */
    int user_mode_only; /* user mode only simulation */
    struct TranslationBlock *current_tb; /* currently executing TB */
    /* soft mmu support */
    /* in order to avoid passing too many arguments to the memory
       write helpers, we store some rarely used information in the CPU
       context) */
    unsigned long mem_write_pc; /* host pc at which the memory was
                                   written */
    unsigned long mem_write_vaddr; /* target virtual addr at which the
                                      memory was written */
    /* 0 = kernel, 1 = user (may have 2 = kernel code, 3 = user code ?) */
    CPUTLBEntry tlb_read[2][CPU_TLB_SIZE];
    CPUTLBEntry tlb_write[2][CPU_TLB_SIZE];

    /* ice debug support */
    uint32_t breakpoints[MAX_BREAKPOINTS];
    int nb_breakpoints;
    int singlestep_enabled; /* XXX: should use CPU single step mode instead */

    /* Time base and decrementer */
    ppc_tb_t *tb_env;

    /* Power management */
    int power_mode;

    /* user data */
    void *opaque;
} CPUPPCState;

CPUPPCState *cpu_ppc_init(void);
int cpu_ppc_exec(CPUPPCState *s);
void cpu_ppc_close(CPUPPCState *s);
/* you can call this signal handler from your SIGBUS and SIGSEGV
   signal handlers to inform the virtual CPU of exceptions. non zero
   is returned if the signal was handled by the virtual CPU.  */
struct siginfo;
int cpu_ppc_signal_handler(int host_signum, struct siginfo *info, 
                           void *puc);

void do_interrupt (CPUPPCState *env);
void cpu_loop_exit(void);

void cpu_ppc_dump_state(CPUPPCState *env, FILE *f, int flags);
void dump_stack (CPUPPCState *env);

uint32_t _load_xer (CPUPPCState *env);
void _store_xer (CPUPPCState *env, uint32_t value);
uint32_t _load_msr (CPUPPCState *env);
void _store_msr (CPUPPCState *env, uint32_t value);

int cpu_ppc_register (CPUPPCState *env, uint32_t pvr);

/* Time-base and decrementer management */
#ifndef NO_CPU_IO_DEFS
uint32_t cpu_ppc_load_tbl (CPUPPCState *env);
uint32_t cpu_ppc_load_tbu (CPUPPCState *env);
void cpu_ppc_store_tbu (CPUPPCState *env, uint32_t value);
void cpu_ppc_store_tbl (CPUPPCState *env, uint32_t value);
uint32_t cpu_ppc_load_decr (CPUPPCState *env);
void cpu_ppc_store_decr (CPUPPCState *env, uint32_t value);
#endif

#define TARGET_PAGE_BITS 12
#include "cpu-all.h"

#define ugpr(n) (env->gpr[n])
#define fprd(n) (env->fpr[n])
#define fprs(n) ((float)env->fpr[n])
#define fpru(n) ((uint32_t)env->fpr[n])
#define fpri(n) ((int32_t)env->fpr[n])

#define SPR_ENCODE(sprn)                               \
(((sprn) >> 5) | (((sprn) & 0x1F) << 5))

/* User mode SPR */
#define spr(n) env->spr[n]
#define XER_SO 31
#define XER_OV 30
#define XER_CA 29
#define XER_BC 0
#define xer_so env->xer[3]
#define xer_ov env->xer[2]
#define xer_ca env->xer[1]
#define xer_bc env->xer[0]

#define MQ     SPR_ENCODE(0)
#define XER    SPR_ENCODE(1)
#define RTCUR  SPR_ENCODE(4)
#define RTCLR  SPR_ENCODE(5)
#define LR     SPR_ENCODE(8)
#define CTR    SPR_ENCODE(9)
/* VEA mode SPR */
#define V_TBL  SPR_ENCODE(268)
#define V_TBU  SPR_ENCODE(269)
/* supervisor mode SPR */
#define DSISR  SPR_ENCODE(18)
#define DAR    SPR_ENCODE(19)
#define RTCUW  SPR_ENCODE(20)
#define RTCLW  SPR_ENCODE(21)
#define DECR   SPR_ENCODE(22)
#define SDR1   SPR_ENCODE(25)
#define SRR0   SPR_ENCODE(26)
#define SRR1   SPR_ENCODE(27)
#define SPRG0  SPR_ENCODE(272)
#define SPRG1  SPR_ENCODE(273)
#define SPRG2  SPR_ENCODE(274)
#define SPRG3  SPR_ENCODE(275)
#define SPRG4  SPR_ENCODE(276)
#define SPRG5  SPR_ENCODE(277)
#define SPRG6  SPR_ENCODE(278)
#define SPRG7  SPR_ENCODE(279)
#define ASR    SPR_ENCODE(280)
#define EAR    SPR_ENCODE(282)
#define O_TBL  SPR_ENCODE(284)
#define O_TBU  SPR_ENCODE(285)
#define PVR    SPR_ENCODE(287)
#define IBAT0U SPR_ENCODE(528)
#define IBAT0L SPR_ENCODE(529)
#define IBAT1U SPR_ENCODE(530)
#define IBAT1L SPR_ENCODE(531)
#define IBAT2U SPR_ENCODE(532)
#define IBAT2L SPR_ENCODE(533)
#define IBAT3U SPR_ENCODE(534)
#define IBAT3L SPR_ENCODE(535)
#define DBAT0U SPR_ENCODE(536)
#define DBAT0L SPR_ENCODE(537)
#define DBAT1U SPR_ENCODE(538)
#define DBAT1L SPR_ENCODE(539)
#define DBAT2U SPR_ENCODE(540)
#define DBAT2L SPR_ENCODE(541)
#define DBAT3U SPR_ENCODE(542)
#define DBAT3L SPR_ENCODE(543)
#define IBAT4U SPR_ENCODE(560)
#define IBAT4L SPR_ENCODE(561)
#define IBAT5U SPR_ENCODE(562)
#define IBAT5L SPR_ENCODE(563)
#define IBAT6U SPR_ENCODE(564)
#define IBAT6L SPR_ENCODE(565)
#define IBAT7U SPR_ENCODE(566)
#define IBAT7L SPR_ENCODE(567)
#define DBAT4U SPR_ENCODE(568)
#define DBAT4L SPR_ENCODE(569)
#define DBAT5U SPR_ENCODE(570)
#define DBAT5L SPR_ENCODE(571)
#define DBAT6U SPR_ENCODE(572)
#define DBAT6L SPR_ENCODE(573)
#define DBAT7U SPR_ENCODE(574)
#define DBAT7L SPR_ENCODE(575)
#define UMMCR0 SPR_ENCODE(936)
#define UPMC1  SPR_ENCODE(937)
#define UPMC2  SPR_ENCODE(938)
#define USIA   SPR_ENCODE(939)
#define UMMCR1 SPR_ENCODE(940)
#define UPMC3  SPR_ENCODE(941)
#define UPMC4  SPR_ENCODE(942)
#define MMCR0  SPR_ENCODE(952)
#define PMC1   SPR_ENCODE(953)
#define PMC2   SPR_ENCODE(954)
#define SIA    SPR_ENCODE(955)
#define MMCR1  SPR_ENCODE(956)
#define PMC3   SPR_ENCODE(957)
#define PMC4   SPR_ENCODE(958)
#define SDA    SPR_ENCODE(959)
#define DMISS  SPR_ENCODE(976)
#define DCMP   SPR_ENCODE(977)
#define DHASH1 SPR_ENCODE(978)
#define DHASH2 SPR_ENCODE(979)
#define IMISS  SPR_ENCODE(980)
#define ICMP   SPR_ENCODE(981)
#define RPA    SPR_ENCODE(982)
#define TCR    SPR_ENCODE(984)
#define IBR    SPR_ENCODE(986)
#define ESASRR SPR_ENCODE(987)
#define SEBR   SPR_ENCODE(990)
#define SER    SPR_ENCODE(991)
#define HID0   SPR_ENCODE(1008)
#define HID1   SPR_ENCODE(1009)
#define IABR   SPR_ENCODE(1010)
#define HID2   SPR_ENCODE(1011)
#define DABR   SPR_ENCODE(1013)
#define L2PM   SPR_ENCODE(1016)
#define L2CR   SPR_ENCODE(1017)
#define ICTC   SPR_ENCODE(1019)
#define THRM1  SPR_ENCODE(1020)
#define THRM2  SPR_ENCODE(1021)
#define THRM3  SPR_ENCODE(1022)
#define SP     SPR_ENCODE(1021)
#define LP     SPR_ENCODE(1022)
#define DABR_MASK 0xFFFFFFF8
#define FPECR  SPR_ENCODE(1022)
#define PIR    SPR_ENCODE(1023)

/* Memory access type :
 * may be needed for precise access rights control and precise exceptions.
 */
enum {
    /* 1 bit to define user level / supervisor access */
    ACCESS_USER  = 0x00,
    ACCESS_SUPER = 0x01,
    /* Type of instruction that generated the access */
    ACCESS_CODE  = 0x10, /* Code fetch access                */
    ACCESS_INT   = 0x20, /* Integer load/store access        */
    ACCESS_FLOAT = 0x30, /* floating point load/store access */
    ACCESS_RES   = 0x40, /* load/store with reservation      */
    ACCESS_EXT   = 0x50, /* external access                  */
    ACCESS_CACHE = 0x60, /* Cache manipulation               */
};

/*****************************************************************************/
/* Exceptions */
enum {
    EXCP_NONE          = -1,
    /* PPC hardware exceptions : exception vector / 0x100 */
    EXCP_RESET         = 0x01, /* System reset                     */
    EXCP_MACHINE_CHECK = 0x02, /* Machine check exception          */
    EXCP_DSI           = 0x03, /* Impossible memory access         */
    EXCP_ISI           = 0x04, /* Impossible instruction fetch     */
    EXCP_EXTERNAL      = 0x05, /* External interruption            */
    EXCP_ALIGN         = 0x06, /* Alignment exception              */
    EXCP_PROGRAM       = 0x07, /* Program exception                */
    EXCP_NO_FP         = 0x08, /* No floating point                */
    EXCP_DECR          = 0x09, /* Decrementer exception            */
    EXCP_RESA          = 0x0A, /* Implementation specific          */
    EXCP_RESB          = 0x0B, /* Implementation specific          */
    EXCP_SYSCALL       = 0x0C, /* System call                      */
    EXCP_TRACE         = 0x0D, /* Trace exception (optional)       */
    EXCP_FP_ASSIST     = 0x0E, /* Floating-point assist (optional) */
    /* MPC740/745/750 & IBM 750 */
    EXCP_PERF          = 0x0F,  /* Performance monitor              */
    EXCP_IABR          = 0x13,  /* Instruction address breakpoint   */
    EXCP_SMI           = 0x14,  /* System management interrupt      */
    EXCP_THRM          = 0x15,  /* Thermal management interrupt     */
    /* MPC755 */
    EXCP_TLBMISS       = 0x10,  /* Instruction TLB miss             */
    EXCP_TLBMISS_DL    = 0x11,  /* Data TLB miss for load           */
    EXCP_TLBMISS_DS    = 0x12,  /* Data TLB miss for store          */
    EXCP_PPC_MAX       = 0x16,
    /* Qemu exception */
    EXCP_OFCALL        = 0x20,  /* Call open-firmware emulator      */
    EXCP_RTASCALL      = 0x21,  /* Call RTAS emulator               */
    /* Special cases where we want to stop translation */
    EXCP_MTMSR         = 0x104, /* mtmsr instruction:               */
                                /* may change privilege level       */
    EXCP_BRANCH        = 0x108, /* branch instruction               */
    EXCP_RFI           = 0x10C, /* return from interrupt            */
    EXCP_SYSCALL_USER  = 0x110, /* System call in user mode only    */
};
/* Error codes */
enum {
    /* Exception subtypes for EXCP_DSI                              */
    EXCP_DSI_TRANSLATE = 0x01,  /* Data address can't be translated */
    EXCP_DSI_NOTSUP    = 0x02,  /* Access type not supported        */
    EXCP_DSI_PROT      = 0x03,  /* Memory protection violation      */
    EXCP_DSI_EXTERNAL  = 0x04,  /* External access disabled         */
    EXCP_DSI_DABR      = 0x05,  /* Data address breakpoint          */
    /* flags for EXCP_DSI */
    EXCP_DSI_DIRECT    = 0x10,
    EXCP_DSI_STORE     = 0x20,
    EXCP_DSI_ECXW      = 0x40,
    /* Exception subtypes for EXCP_ISI                              */
    EXCP_ISI_TRANSLATE = 0x01,  /* Code address can't be translated */
    EXCP_ISI_NOEXEC    = 0x02,  /* Try to fetch from a data segment */
    EXCP_ISI_GUARD     = 0x03,  /* Fetch from guarded memory        */
    EXCP_ISI_PROT      = 0x04,  /* Memory protection violation      */
    EXCP_ISI_DIRECT    = 0x05,  /* Trying to fetch from             *
				 * a direct store segment           */
    /* Exception subtypes for EXCP_ALIGN                            */
    EXCP_ALIGN_FP      = 0x01,  /* FP alignment exception           */
    EXCP_ALIGN_LST     = 0x02,  /* Unaligned mult/extern load/store */
    EXCP_ALIGN_LE      = 0x03,  /* Multiple little-endian access    */
    EXCP_ALIGN_PROT    = 0x04,  /* Access cross protection boundary */
    EXCP_ALIGN_BAT     = 0x05,  /* Access cross a BAT/seg boundary  */
    EXCP_ALIGN_CACHE   = 0x06,  /* Impossible dcbz access           */
    /* Exception subtypes for EXCP_PROGRAM                          */
    /* FP exceptions */
    EXCP_FP            = 0x10,
    EXCP_FP_OX         = 0x01,  /* FP overflow                      */
    EXCP_FP_UX         = 0x02,  /* FP underflow                     */
    EXCP_FP_ZX         = 0x03,  /* FP divide by zero                */
    EXCP_FP_XX         = 0x04,  /* FP inexact                       */
    EXCP_FP_VXNAN      = 0x05,  /* FP invalid SNaN op               */
    EXCP_FP_VXISI      = 0x06,  /* FP invalid infinite substraction */
    EXCP_FP_VXIDI      = 0x07,  /* FP invalid infinite divide       */
    EXCP_FP_VXZDZ      = 0x08,  /* FP invalid zero divide           */
    EXCP_FP_VXIMZ      = 0x09,  /* FP invalid infinite * zero       */
    EXCP_FP_VXVC       = 0x0A,  /* FP invalid compare               */
    EXCP_FP_VXSOFT     = 0x0B,  /* FP invalid operation             */
    EXCP_FP_VXSQRT     = 0x0C,  /* FP invalid square root           */
    EXCP_FP_VXCVI      = 0x0D,  /* FP invalid integer conversion    */
    /* Invalid instruction */
    EXCP_INVAL         = 0x20,
    EXCP_INVAL_INVAL   = 0x01,  /* Invalid instruction              */
    EXCP_INVAL_LSWX    = 0x02,  /* Invalid lswx instruction         */
    EXCP_INVAL_SPR     = 0x03,  /* Invalid SPR access               */
    EXCP_INVAL_FP      = 0x04,  /* Unimplemented mandatory fp instr */
    /* Privileged instruction */
    EXCP_PRIV          = 0x30,
    EXCP_PRIV_OPC      = 0x01,
    EXCP_PRIV_REG      = 0x02,
    /* Trap */
    EXCP_TRAP          = 0x40,
};

/*****************************************************************************/

#endif /* !defined (__CPU_PPC_H__) */
