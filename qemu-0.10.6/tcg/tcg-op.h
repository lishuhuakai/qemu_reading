/*
 * Tiny Code Generator for QEMU
 *
 * Copyright (c) 2008 Fabrice Bellard
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
#include "tcg.h"

int gen_new_label(void);
/* 为单操作数操作符生成代码
 * @param opc 操作
 * @param arg1 操作数1
 */
static inline void tcg_gen_op1_i32(int opc, TCGv_i32 arg1)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I32(arg1);
}

static inline void tcg_gen_op1_i64(int opc, TCGv_i64 arg1)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(arg1);
}
/* op1i 表示第一个参数是立即数 */
static inline void tcg_gen_op1i(int opc, TCGArg arg1)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = arg1;
}
/* 为双操作数操作符生成源码
 * @param opc 操作码
 * @param arg1, arg2 两个操作数
 */
static inline void tcg_gen_op2_i32(int opc, TCGv_i32 arg1, TCGv_i32 arg2)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I32(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg2);
}

static inline void tcg_gen_op2_i64(int opc, TCGv_i64 arg1, TCGv_i64 arg2)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg2);
}

static inline void tcg_gen_op2i_i32(int opc, TCGv_i32 arg1, TCGArg arg2)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I32(arg1);
    *gen_opparam_ptr++ = arg2;
}

static inline void tcg_gen_op2i_i64(int opc, TCGv_i64 arg1, TCGArg arg2)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(arg1);
    *gen_opparam_ptr++ = arg2;
}

static inline void tcg_gen_op2ii(int opc, TCGArg arg1, TCGArg arg2)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = arg1;
    *gen_opparam_ptr++ = arg2;
}
/* 为三操作数操作符生成源码
 * @param opc 操作码
 * @param arg1,arg2,arg3 操作数
 */
static inline void tcg_gen_op3_i32(int opc, TCGv_i32 arg1, TCGv_i32 arg2,
                                   TCGv_i32 arg3)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I32(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg2);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg3);
}

static inline void tcg_gen_op3_i64(int opc, TCGv_i64 arg1, TCGv_i64 arg2,
                                   TCGv_i64 arg3)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg2);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg3);
}

static inline void tcg_gen_op3i_i32(int opc, TCGv_i32 arg1, TCGv_i32 arg2,
                                    TCGArg arg3)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I32(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg2);
    *gen_opparam_ptr++ = arg3;
}

static inline void tcg_gen_op3i_i64(int opc, TCGv_i64 arg1, TCGv_i64 arg2,
                                    TCGArg arg3)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg2);
    *gen_opparam_ptr++ = arg3;
}

static inline void tcg_gen_ldst_op_i32(int opc, TCGv_i32 val, TCGv_ptr base,
                                       TCGArg offset)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I32(val);
    *gen_opparam_ptr++ = GET_TCGV_PTR(base);
    *gen_opparam_ptr++ = offset;
}

static inline void tcg_gen_ldst_op_i64(int opc, TCGv_i64 val, TCGv_ptr base,
                                       TCGArg offset)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(val);
    *gen_opparam_ptr++ = GET_TCGV_PTR(base);
    *gen_opparam_ptr++ = offset;
}

static inline void tcg_gen_qemu_ldst_op_i64_i32(int opc, TCGv_i64 val, TCGv_i32 addr,
                                                TCGArg mem_index)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(val);
    *gen_opparam_ptr++ = GET_TCGV_I32(addr);
    *gen_opparam_ptr++ = mem_index;
}

static inline void tcg_gen_qemu_ldst_op_i64_i64(int opc, TCGv_i64 val, TCGv_i64 addr,
                                                TCGArg mem_index)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(val);
    *gen_opparam_ptr++ = GET_TCGV_I64(addr);
    *gen_opparam_ptr++ = mem_index;
}

static inline void tcg_gen_op4_i32(int opc, TCGv_i32 arg1, TCGv_i32 arg2,
                                   TCGv_i32 arg3, TCGv_i32 arg4)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I32(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg2);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg3);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg4);
}

static inline void tcg_gen_op4_i64(int opc, TCGv_i64 arg1, TCGv_i64 arg2,
                                   TCGv_i64 arg3, TCGv_i64 arg4)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg2);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg3);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg4);
}

static inline void tcg_gen_op4i_i32(int opc, TCGv_i32 arg1, TCGv_i32 arg2,
                                    TCGv_i32 arg3, TCGArg arg4)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I32(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg2);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg3);
    *gen_opparam_ptr++ = arg4;
}

static inline void tcg_gen_op4i_i64(int opc, TCGv_i64 arg1, TCGv_i64 arg2,
                                    TCGv_i64 arg3, TCGArg arg4)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg2);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg3);
    *gen_opparam_ptr++ = arg4;
}

static inline void tcg_gen_op4ii_i32(int opc, TCGv_i32 arg1, TCGv_i32 arg2,
                                     TCGArg arg3, TCGArg arg4)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I32(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg2);
    *gen_opparam_ptr++ = arg3;
    *gen_opparam_ptr++ = arg4;
}

static inline void tcg_gen_op4ii_i64(int opc, TCGv_i64 arg1, TCGv_i64 arg2,
                                     TCGArg arg3, TCGArg arg4)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg2);
    *gen_opparam_ptr++ = arg3;
    *gen_opparam_ptr++ = arg4;
}

static inline void tcg_gen_op5_i32(int opc, TCGv_i32 arg1, TCGv_i32 arg2,
                                   TCGv_i32 arg3, TCGv_i32 arg4, TCGv_i32 arg5)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I32(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg2);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg3);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg4);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg5);
}

static inline void tcg_gen_op5_i64(int opc, TCGv_i64 arg1, TCGv_i64 arg2,
                                   TCGv_i64 arg3, TCGv_i64 arg4, TCGv_i64 arg5)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg2);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg3);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg4);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg5);
}

static inline void tcg_gen_op5i_i32(int opc, TCGv_i32 arg1, TCGv_i32 arg2,
                                    TCGv_i32 arg3, TCGv_i32 arg4, TCGArg arg5)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I32(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg2);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg3);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg4);
    *gen_opparam_ptr++ = arg5;
}

static inline void tcg_gen_op5i_i64(int opc, TCGv_i64 arg1, TCGv_i64 arg2,
                                    TCGv_i64 arg3, TCGv_i64 arg4, TCGArg arg5)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg2);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg3);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg4);
    *gen_opparam_ptr++ = arg5;
}

static inline void tcg_gen_op6_i32(int opc, TCGv_i32 arg1, TCGv_i32 arg2,
                                   TCGv_i32 arg3, TCGv_i32 arg4, TCGv_i32 arg5,
                                   TCGv_i32 arg6)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I32(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg2);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg3);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg4);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg5);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg6);
}
/* 为6操作数操作码生成源码
 * @param opc 操作码
 * @param arg1 ~ arg6 操作码
 */
static inline void tcg_gen_op6_i64(int opc, TCGv_i64 arg1, TCGv_i64 arg2,
                                   TCGv_i64 arg3, TCGv_i64 arg4, TCGv_i64 arg5,
                                   TCGv_i64 arg6)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg2);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg3);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg4);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg5);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg6);
}

static inline void tcg_gen_op6ii_i32(int opc, TCGv_i32 arg1, TCGv_i32 arg2,
                                     TCGv_i32 arg3, TCGv_i32 arg4, TCGArg arg5,
                                     TCGArg arg6)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I32(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg2);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg3);
    *gen_opparam_ptr++ = GET_TCGV_I32(arg4);
    *gen_opparam_ptr++ = arg5;
    *gen_opparam_ptr++ = arg6;
}

static inline void tcg_gen_op6ii_i64(int opc, TCGv_i64 arg1, TCGv_i64 arg2,
                                     TCGv_i64 arg3, TCGv_i64 arg4, TCGArg arg5,
                                     TCGArg arg6)
{
    *gen_opc_ptr++ = opc;
    *gen_opparam_ptr++ = GET_TCGV_I64(arg1);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg2);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg3);
    *gen_opparam_ptr++ = GET_TCGV_I64(arg4);
    *gen_opparam_ptr++ = arg5;
    *gen_opparam_ptr++ = arg6;
}
/* 打上跳转标记
* @param n 标记号
 */
static inline void gen_set_label(int n)
{
    tcg_gen_op1i(INDEX_op_set_label, n);
}

static inline void tcg_gen_br(int label)
{
    tcg_gen_op1i(INDEX_op_br, label);
}

/* mov_i32 t0, t1 ==> t0 = t1 */
static inline void tcg_gen_mov_i32(TCGv_i32 ret, TCGv_i32 arg)
{
    if (GET_TCGV_I32(ret) != GET_TCGV_I32(arg))
        tcg_gen_op2_i32(INDEX_op_mov_i32, ret, arg);
}

/* 为move指令生成字节码
 * mov_i32 t0, t1 ==> t0 = t1
 */
static inline void tcg_gen_movi_i32(TCGv_i32 ret, int32_t arg)
{
    tcg_gen_op2i_i32(INDEX_op_movi_i32, ret, arg);
}

/* helper calls */
static inline void tcg_gen_helperN(void *func, int flags, int sizemask,
                                   TCGArg ret, int nargs, TCGArg *args)
{
    TCGv_ptr fn;
    fn = tcg_const_ptr((tcg_target_long)func);
    tcg_gen_callN(&tcg_ctx, fn, flags, sizemask, ret,
                  nargs, args);
    tcg_temp_free_ptr(fn);
}

/* FIXME: Should this be pure?  */
static inline void tcg_gen_helper64(void *func, TCGv_i64 ret,
                                    TCGv_i64 a, TCGv_i64 b)
{
    TCGv_ptr fn;
    TCGArg args[2];
    fn = tcg_const_ptr((tcg_target_long)func);
    args[0] = GET_TCGV_I64(a);
    args[1] = GET_TCGV_I64(b);
    tcg_gen_callN(&tcg_ctx, fn, 0, 7, GET_TCGV_I64(ret), 2, args);
    tcg_temp_free_ptr(fn);
}

/* 32 bit ops */
/* ld8u_i32 t0, t1, offset ==> t0 = read(t1 + offset) */
static inline void tcg_gen_ld8u_i32(TCGv_i32 ret, TCGv_ptr arg2, tcg_target_long offset)
{
    tcg_gen_ldst_op_i32(INDEX_op_ld8u_i32, ret, arg2, offset);
}
/* ld8s_i32 t0, t1, offset ==> t0 = read(t1 + offset) */
static inline void tcg_gen_ld8s_i32(TCGv_i32 ret, TCGv_ptr arg2, tcg_target_long offset)
{
    tcg_gen_ldst_op_i32(INDEX_op_ld8s_i32, ret, arg2, offset);
}
/* ld16u_i32 t0, t1, offset ==> t0 = read(t1 + offset) */
static inline void tcg_gen_ld16u_i32(TCGv_i32 ret, TCGv_ptr arg2, tcg_target_long offset)
{
    tcg_gen_ldst_op_i32(INDEX_op_ld16u_i32, ret, arg2, offset);
}
/* ld16s_i32 t0, t1, offset ==> t0 = read(t1 + offset) */
static inline void tcg_gen_ld16s_i32(TCGv_i32 ret, TCGv_ptr arg2, tcg_target_long offset)
{
    tcg_gen_ldst_op_i32(INDEX_op_ld16s_i32, ret, arg2, offset);
}
/* ld_i32 t0, t1, offset ==> t0 = read(t1 + offset) */
static inline void tcg_gen_ld_i32(TCGv_i32 ret, TCGv_ptr arg2, tcg_target_long offset)
{
    tcg_gen_ldst_op_i32(INDEX_op_ld_i32, ret, arg2, offset);
}
/* st8_i32 t0, t1, offset ==> write(t0, t1 + offset) */
static inline void tcg_gen_st8_i32(TCGv_i32 arg1, TCGv_ptr arg2, tcg_target_long offset)
{
    tcg_gen_ldst_op_i32(INDEX_op_st8_i32, arg1, arg2, offset);
}
/* st16_i32 t0, t1, offset ==> write(t0, t1 + offset) */
static inline void tcg_gen_st16_i32(TCGv_i32 arg1, TCGv_ptr arg2, tcg_target_long offset)
{
    tcg_gen_ldst_op_i32(INDEX_op_st16_i32, arg1, arg2, offset);
}

/* st_i32 t0, t1, 0ffset ==> write(t0, t1 + offset) 写32bit到t1+offset指示的内存去 */
static inline void tcg_gen_st_i32(TCGv_i32 arg1, TCGv_ptr arg2, tcg_target_long offset)
{
    tcg_gen_ldst_op_i32(INDEX_op_st_i32, arg1, arg2, offset);
}
/* add_i32 t0, t1, t2 ==> t0 = t1 + t2 */
static inline void tcg_gen_add_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    tcg_gen_op3_i32(INDEX_op_add_i32, ret, arg1, arg2);
}
/* addi_i32 t0, t1, t2 ==> t0 = t1 + t2 */
static inline void tcg_gen_addi_i32(TCGv_i32 ret, TCGv_i32 arg1, int32_t arg2)
{
    /* some cases can be optimized here */
    if (arg2 == 0) {
        tcg_gen_mov_i32(ret, arg1);
    } else {
        TCGv_i32 t0 = tcg_const_i32(arg2);
        tcg_gen_add_i32(ret, arg1, t0);
        tcg_temp_free_i32(t0);
    }
}
/* sub_i32 t0, t1, t2 ==> t0 = t1 - t2 */
static inline void tcg_gen_sub_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    tcg_gen_op3_i32(INDEX_op_sub_i32, ret, arg1, arg2);
}
/* subfi_i32 t0, t1, t2 ==> t0 = t1 - t2 */
static inline void tcg_gen_subfi_i32(TCGv_i32 ret, int32_t arg1, TCGv_i32 arg2)
{
    TCGv_i32 t0 = tcg_const_i32(arg1);
    tcg_gen_sub_i32(ret, t0, arg2);
    tcg_temp_free_i32(t0);
}
/* subi_i32 t0, t1, t2 ==> t0 = t1 - t2 */ */
static inline void tcg_gen_subi_i32(TCGv_i32 ret, TCGv_i32 arg1, int32_t arg2)
{
    /* some cases can be optimized here */
    if (arg2 == 0) {
        tcg_gen_mov_i32(ret, arg1);
    } else {
        TCGv_i32 t0 = tcg_const_i32(arg2);
        tcg_gen_sub_i32(ret, arg1, t0);
        tcg_temp_free_i32(t0);
    }
}
/* and_i32 t0, t1, t2 ==> t0 = t1 & t2 */
static inline void tcg_gen_and_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    tcg_gen_op3_i32(INDEX_op_and_i32, ret, arg1, arg2);
}
/* andi_i32 t0, t1, t2 ==> t0 = t1 & t2 */
static inline void tcg_gen_andi_i32(TCGv_i32 ret, TCGv_i32 arg1, int32_t arg2)
{
    /* some cases can be optimized here */
    if (arg2 == 0) {
        tcg_gen_movi_i32(ret, 0);
    } else if (arg2 == 0xffffffff) {
        tcg_gen_mov_i32(ret, arg1);
    } else {
        TCGv_i32 t0 = tcg_const_i32(arg2);
        tcg_gen_and_i32(ret, arg1, t0);
        tcg_temp_free_i32(t0);
    }
}
/* or_i32/i64 t0, t1, t2 ==> t0 = t1 | t2 */
static inline void tcg_gen_or_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    tcg_gen_op3_i32(INDEX_op_or_i32, ret, arg1, arg2);
}

static inline void tcg_gen_ori_i32(TCGv_i32 ret, TCGv_i32 arg1, int32_t arg2)
{
    /* some cases can be optimized here */
    if (arg2 == 0xffffffff) {
        tcg_gen_movi_i32(ret, 0xffffffff);
    } else if (arg2 == 0) {
        tcg_gen_mov_i32(ret, arg1);
    } else {
        TCGv_i32 t0 = tcg_const_i32(arg2);
        tcg_gen_or_i32(ret, arg1, t0);
        tcg_temp_free_i32(t0);
    }
}
/* xor_i32/i64 t0, t1, t2 ==> t0 = t1 ^ t2 */
static inline void tcg_gen_xor_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    tcg_gen_op3_i32(INDEX_op_xor_i32, ret, arg1, arg2);
}

static inline void tcg_gen_xori_i32(TCGv_i32 ret, TCGv_i32 arg1, int32_t arg2)
{
    /* some cases can be optimized here */
    if (arg2 == 0) {
        tcg_gen_mov_i32(ret, arg1);
    } else {
        TCGv_i32 t0 = tcg_const_i32(arg2);
        tcg_gen_xor_i32(ret, arg1, t0);
        tcg_temp_free_i32(t0);
    }
}

static inline void tcg_gen_shl_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    tcg_gen_op3_i32(INDEX_op_shl_i32, ret, arg1, arg2);
}

static inline void tcg_gen_shli_i32(TCGv_i32 ret, TCGv_i32 arg1, int32_t arg2)
{
    if (arg2 == 0) {
        tcg_gen_mov_i32(ret, arg1);
    } else {
        TCGv_i32 t0 = tcg_const_i32(arg2);
        tcg_gen_shl_i32(ret, arg1, t0);
        tcg_temp_free_i32(t0);
    }
}

static inline void tcg_gen_shr_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    tcg_gen_op3_i32(INDEX_op_shr_i32, ret, arg1, arg2);
}
/* shr_i32/i64 t0, t1, t2 ==> t0 = t1 >> t2 (unsigned)
 * Undefined behavior if t2 < 0 or t2 >= 32 (resp 64)
 */
static inline void tcg_gen_shri_i32(TCGv_i32 ret, TCGv_i32 arg1, int32_t arg2)
{
    if (arg2 == 0) {
        tcg_gen_mov_i32(ret, arg1);
    } else {
        TCGv_i32 t0 = tcg_const_i32(arg2);
        tcg_gen_shr_i32(ret, arg1, t0);
        tcg_temp_free_i32(t0);
    }
}

/* sar_i32/i64 t0, t1, t2 ==> t0 = t1 >> t2 (signed)
 * Undefined behavior if t2 < 0 or t2 >= 32 (resp 64)
 */
static inline void tcg_gen_sar_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    tcg_gen_op3_i32(INDEX_op_sar_i32, ret, arg1, arg2);
}

static inline void tcg_gen_sari_i32(TCGv_i32 ret, TCGv_i32 arg1, int32_t arg2)
{
    if (arg2 == 0) {
        tcg_gen_mov_i32(ret, arg1);
    } else {
        TCGv_i32 t0 = tcg_const_i32(arg2);
        tcg_gen_sar_i32(ret, arg1, t0);
        tcg_temp_free_i32(t0);
    }
}

/* brcond_i32/i64 cond, t0, t1, label
 * Conditional jump if t0 cond t1 is true. cond can be:
 *  TCG_COND_EQ
 *  TCG_COND_NE
 *  TCG_COND_LT   (signed)
 *  TCG_COND_GE   (signed)
 *  TCG_COND_LE   (signed)
 *  TCG_COND_GT   (signed)
 *  TCG_COND_LTU  (unsigned)
 *  TCG_COND_GEU  (unsigned)
 *  TCG_COND_LEU  (unsigned)
 *  TCG_COND_GTU  (unsigned)
 */
static inline void tcg_gen_brcond_i32(int cond, TCGv_i32 arg1, TCGv_i32 arg2,
                                      int label_index)
{
    tcg_gen_op4ii_i32(INDEX_op_brcond_i32, arg1, arg2, cond, label_index);
}

static inline void tcg_gen_brcondi_i32(int cond, TCGv_i32 arg1, int32_t arg2,
                                       int label_index)
{
    TCGv_i32 t0 = tcg_const_i32(arg2);
    tcg_gen_brcond_i32(cond, arg1, t0, label_index);
    tcg_temp_free_i32(t0);
}
/* mul_i32/i64 t0, t1, t2 ==> t0 = t1 * t2 */
static inline void tcg_gen_mul_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    tcg_gen_op3_i32(INDEX_op_mul_i32, ret, arg1, arg2);
}
/* mul_i32/i64 t0, t1, t2 ==> t0 = t1 * t2 */
static inline void tcg_gen_muli_i32(TCGv_i32 ret, TCGv_i32 arg1, int32_t arg2)
{
    TCGv_i32 t0 = tcg_const_i32(arg2);
    tcg_gen_mul_i32(ret, arg1, t0);
    tcg_temp_free_i32(t0);
}

#ifdef TCG_TARGET_HAS_div_i32
static inline void tcg_gen_div_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    tcg_gen_op3_i32(INDEX_op_div_i32, ret, arg1, arg2);
}

static inline void tcg_gen_rem_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    tcg_gen_op3_i32(INDEX_op_rem_i32, ret, arg1, arg2);
}

static inline void tcg_gen_divu_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    tcg_gen_op3_i32(INDEX_op_divu_i32, ret, arg1, arg2);
}

static inline void tcg_gen_remu_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    tcg_gen_op3_i32(INDEX_op_remu_i32, ret, arg1, arg2);
}
#else
/* div_i32/i64 t0, t1, t2 ==> t0 = t1 / t2 (signed) */
static inline void tcg_gen_div_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    TCGv_i32 t0;
    t0 = tcg_temp_new_i32();
    tcg_gen_sari_i32(t0, arg1, 31);
    tcg_gen_op5_i32(INDEX_op_div2_i32, ret, t0, arg1, t0, arg2);
    tcg_temp_free_i32(t0);
}
/* rem_i32/i64 t0, t1, t2 ==> t0 = t1 % t2 (signed) */
static inline void tcg_gen_rem_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    TCGv_i32 t0;
    t0 = tcg_temp_new_i32();
    tcg_gen_sari_i32(t0, arg1, 31);
    tcg_gen_op5_i32(INDEX_op_div2_i32, t0, ret, arg1, t0, arg2);
    tcg_temp_free_i32(t0);
}
/* divu_i32/i64 t0, t1, t2 ==> t0 = t1 / t2 (unsigned) */
static inline void tcg_gen_divu_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    TCGv_i32 t0;
    t0 = tcg_temp_new_i32();
    tcg_gen_movi_i32(t0, 0);
    tcg_gen_op5_i32(INDEX_op_divu2_i32, ret, t0, arg1, t0, arg2);
    tcg_temp_free_i32(t0);
}
/* remu_i32/i64 t0, t1, t2 ==> t0 = t1 % t2 (signed) */
static inline void tcg_gen_remu_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    TCGv_i32 t0;
    t0 = tcg_temp_new_i32();
    tcg_gen_movi_i32(t0, 0);
    tcg_gen_op5_i32(INDEX_op_divu2_i32, t0, ret, arg1, t0, arg2);
    tcg_temp_free_i32(t0);
}
#endif

#if TCG_TARGET_REG_BITS == 32

static inline void tcg_gen_mov_i64(TCGv_i64 ret, TCGv_i64 arg)
{
    if (GET_TCGV_I64(ret) != GET_TCGV_I64(arg)) {
        tcg_gen_mov_i32(TCGV_LOW(ret), TCGV_LOW(arg));
        tcg_gen_mov_i32(TCGV_HIGH(ret), TCGV_HIGH(arg));
    }
}

static inline void tcg_gen_movi_i64(TCGv_i64 ret, int64_t arg)
{
    tcg_gen_movi_i32(TCGV_LOW(ret), arg);
    tcg_gen_movi_i32(TCGV_HIGH(ret), arg >> 32);
}

static inline void tcg_gen_ld8u_i64(TCGv_i64 ret, TCGv_ptr arg2,
                                    tcg_target_long offset)
{
    tcg_gen_ld8u_i32(TCGV_LOW(ret), arg2, offset);
    tcg_gen_movi_i32(TCGV_HIGH(ret), 0);
}

static inline void tcg_gen_ld8s_i64(TCGv_i64 ret, TCGv_ptr arg2,
                                    tcg_target_long offset)
{
    tcg_gen_ld8s_i32(TCGV_LOW(ret), arg2, offset);
    tcg_gen_sari_i32(TCGV_HIGH(ret), TCGV_HIGH(ret), 31);
}

static inline void tcg_gen_ld16u_i64(TCGv_i64 ret, TCGv_ptr arg2,
                                     tcg_target_long offset)
{
    tcg_gen_ld16u_i32(TCGV_LOW(ret), arg2, offset);
    tcg_gen_movi_i32(TCGV_HIGH(ret), 0);
}

static inline void tcg_gen_ld16s_i64(TCGv_i64 ret, TCGv_ptr arg2,
                                     tcg_target_long offset)
{
    tcg_gen_ld16s_i32(TCGV_LOW(ret), arg2, offset);
    tcg_gen_sari_i32(TCGV_HIGH(ret), TCGV_LOW(ret), 31);
}

static inline void tcg_gen_ld32u_i64(TCGv_i64 ret, TCGv_ptr arg2,
                                     tcg_target_long offset)
{
    tcg_gen_ld_i32(TCGV_LOW(ret), arg2, offset);
    tcg_gen_movi_i32(TCGV_HIGH(ret), 0);
}

static inline void tcg_gen_ld32s_i64(TCGv_i64 ret, TCGv_ptr arg2,
                                     tcg_target_long offset)
{
    tcg_gen_ld_i32(TCGV_LOW(ret), arg2, offset);
    tcg_gen_sari_i32(TCGV_HIGH(ret), TCGV_LOW(ret), 31);
}
/* ld_i32/i64 t0, t1, offset ==> t0 = read(t1 + offset) */
static inline void tcg_gen_ld_i64(TCGv_i64 ret, TCGv_ptr arg2,
                                  tcg_target_long offset)
{
    /* since arg2 and ret have different types, they cannot be the
       same temporary */
#ifdef TCG_TARGET_WORDS_BIGENDIAN
    tcg_gen_ld_i32(TCGV_HIGH(ret), arg2, offset);
    tcg_gen_ld_i32(TCGV_LOW(ret), arg2, offset + 4);
#else
    tcg_gen_ld_i32(TCGV_LOW(ret), arg2, offset);
    tcg_gen_ld_i32(TCGV_HIGH(ret), arg2, offset + 4);
#endif
}
/* st8_i32/i64 t0, t1, offset ==> write(t0, t1 + offset) */
static inline void tcg_gen_st8_i64(TCGv_i64 arg1, TCGv_ptr arg2,
                                   tcg_target_long offset)
{
    tcg_gen_st8_i32(TCGV_LOW(arg1), arg2, offset);
}
/* st16_i32/i64 t0, t1, offset ==> write(t0, t1 + offset) */
static inline void tcg_gen_st16_i64(TCGv_i64 arg1, TCGv_ptr arg2,
                                    tcg_target_long offset)
{
    tcg_gen_st16_i32(TCGV_LOW(arg1), arg2, offset);
}
/* st16_i32/i64 t0, t1, offset ==> write(t0, t1 + offset) */
static inline void tcg_gen_st32_i64(TCGv_i64 arg1, TCGv_ptr arg2,
                                    tcg_target_long offset)
{
    tcg_gen_st_i32(TCGV_LOW(arg1), arg2, offset);
}
/* st16_i32/i64 t0, t1, offset ==> write(t0, t1 + offset) */
static inline void tcg_gen_st_i64(TCGv_i64 arg1, TCGv_ptr arg2,
                                  tcg_target_long offset)
{
#ifdef TCG_TARGET_WORDS_BIGENDIAN
    tcg_gen_st_i32(TCGV_HIGH(arg1), arg2, offset);
    tcg_gen_st_i32(TCGV_LOW(arg1), arg2, offset + 4);
#else
    tcg_gen_st_i32(TCGV_LOW(arg1), arg2, offset);
    tcg_gen_st_i32(TCGV_HIGH(arg1), arg2, offset + 4);
#endif
}

static inline void tcg_gen_add_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op6_i32(INDEX_op_add2_i32, TCGV_LOW(ret), TCGV_HIGH(ret),
                    TCGV_LOW(arg1), TCGV_HIGH(arg1), TCGV_LOW(arg2),
                    TCGV_HIGH(arg2));
}

static inline void tcg_gen_sub_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op6_i32(INDEX_op_sub2_i32, TCGV_LOW(ret), TCGV_HIGH(ret),
                    TCGV_LOW(arg1), TCGV_HIGH(arg1), TCGV_LOW(arg2),
                    TCGV_HIGH(arg2));
}

static inline void tcg_gen_and_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_and_i32(TCGV_LOW(ret), TCGV_LOW(arg1), TCGV_LOW(arg2));
    tcg_gen_and_i32(TCGV_HIGH(ret), TCGV_HIGH(arg1), TCGV_HIGH(arg2));
}

static inline void tcg_gen_andi_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    tcg_gen_andi_i32(TCGV_LOW(ret), TCGV_LOW(arg1), arg2);
    tcg_gen_andi_i32(TCGV_HIGH(ret), TCGV_HIGH(arg1), arg2 >> 32);
}

static inline void tcg_gen_or_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_or_i32(TCGV_LOW(ret), TCGV_LOW(arg1), TCGV_LOW(arg2));
    tcg_gen_or_i32(TCGV_HIGH(ret), TCGV_HIGH(arg1), TCGV_HIGH(arg2));
}

static inline void tcg_gen_ori_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    tcg_gen_ori_i32(TCGV_LOW(ret), TCGV_LOW(arg1), arg2);
    tcg_gen_ori_i32(TCGV_HIGH(ret), TCGV_HIGH(arg1), arg2 >> 32);
}

static inline void tcg_gen_xor_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_xor_i32(TCGV_LOW(ret), TCGV_LOW(arg1), TCGV_LOW(arg2));
    tcg_gen_xor_i32(TCGV_HIGH(ret), TCGV_HIGH(arg1), TCGV_HIGH(arg2));
}

static inline void tcg_gen_xori_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    tcg_gen_xori_i32(TCGV_LOW(ret), TCGV_LOW(arg1), arg2);
    tcg_gen_xori_i32(TCGV_HIGH(ret), TCGV_HIGH(arg1), arg2 >> 32);
}

/* XXX: use generic code when basic block handling is OK or CPU
   specific code (x86) */
static inline void tcg_gen_shl_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_helper64(tcg_helper_shl_i64, ret, arg1, arg2);
}

static inline void tcg_gen_shli_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    tcg_gen_shifti_i64(ret, arg1, arg2, 0, 0);
}

static inline void tcg_gen_shr_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_helper64(tcg_helper_shr_i64, ret, arg1, arg2);
}

static inline void tcg_gen_shri_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    tcg_gen_shifti_i64(ret, arg1, arg2, 1, 0);
}

static inline void tcg_gen_sar_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_helper64(tcg_helper_sar_i64, ret, arg1, arg2);
}

static inline void tcg_gen_sari_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    tcg_gen_shifti_i64(ret, arg1, arg2, 1, 1);
}

static inline void tcg_gen_brcond_i64(int cond, TCGv_i64 arg1, TCGv_i64 arg2,
                                      int label_index)
{
    tcg_gen_op6ii_i32(INDEX_op_brcond2_i32,
                      TCGV_LOW(arg1), TCGV_HIGH(arg1), TCGV_LOW(arg2),
                      TCGV_HIGH(arg2), cond, label_index);
}

static inline void tcg_gen_mul_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    TCGv_i64 t0;
    TCGv_i32 t1;

    t0 = tcg_temp_new_i64();
    t1 = tcg_temp_new_i32();

    tcg_gen_op4_i32(INDEX_op_mulu2_i32, TCGV_LOW(t0), TCGV_HIGH(t0),
                    TCGV_LOW(arg1), TCGV_LOW(arg2));

    tcg_gen_mul_i32(t1, TCGV_LOW(arg1), TCGV_HIGH(arg2));
    tcg_gen_add_i32(TCGV_HIGH(t0), TCGV_HIGH(t0), t1);
    tcg_gen_mul_i32(t1, TCGV_HIGH(arg1), TCGV_LOW(arg2));
    tcg_gen_add_i32(TCGV_HIGH(t0), TCGV_HIGH(t0), t1);

    tcg_gen_mov_i64(ret, t0);
    tcg_temp_free_i64(t0);
    tcg_temp_free_i32(t1);
}

static inline void tcg_gen_div_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_helper64(tcg_helper_div_i64, ret, arg1, arg2);
}

static inline void tcg_gen_rem_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_helper64(tcg_helper_rem_i64, ret, arg1, arg2);
}

static inline void tcg_gen_divu_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_helper64(tcg_helper_divu_i64, ret, arg1, arg2);
}

static inline void tcg_gen_remu_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_helper64(tcg_helper_remu_i64, ret, arg1, arg2);
}

#else

static inline void tcg_gen_mov_i64(TCGv_i64 ret, TCGv_i64 arg)
{
    if (GET_TCGV_I64(ret) != GET_TCGV_I64(arg))
        tcg_gen_op2_i64(INDEX_op_mov_i64, ret, arg);
}

static inline void tcg_gen_movi_i64(TCGv_i64 ret, int64_t arg)
{
    tcg_gen_op2i_i64(INDEX_op_movi_i64, ret, arg);
}

static inline void tcg_gen_ld8u_i64(TCGv_i64 ret, TCGv_i64 arg2,
                                    tcg_target_long offset)
{
    tcg_gen_ldst_op_i64(INDEX_op_ld8u_i64, ret, arg2, offset);
}

static inline void tcg_gen_ld8s_i64(TCGv_i64 ret, TCGv_i64 arg2,
                                    tcg_target_long offset)
{
    tcg_gen_ldst_op_i64(INDEX_op_ld8s_i64, ret, arg2, offset);
}

static inline void tcg_gen_ld16u_i64(TCGv_i64 ret, TCGv_i64 arg2,
                                     tcg_target_long offset)
{
    tcg_gen_ldst_op_i64(INDEX_op_ld16u_i64, ret, arg2, offset);
}

static inline void tcg_gen_ld16s_i64(TCGv_i64 ret, TCGv_i64 arg2,
                                     tcg_target_long offset)
{
    tcg_gen_ldst_op_i64(INDEX_op_ld16s_i64, ret, arg2, offset);
}

static inline void tcg_gen_ld32u_i64(TCGv_i64 ret, TCGv_i64 arg2,
                                     tcg_target_long offset)
{
    tcg_gen_ldst_op_i64(INDEX_op_ld32u_i64, ret, arg2, offset);
}

static inline void tcg_gen_ld32s_i64(TCGv_i64 ret, TCGv_i64 arg2,
                                     tcg_target_long offset)
{
    tcg_gen_ldst_op_i64(INDEX_op_ld32s_i64, ret, arg2, offset);
}

static inline void tcg_gen_ld_i64(TCGv_i64 ret, TCGv_i64 arg2, tcg_target_long offset)
{
    tcg_gen_ldst_op_i64(INDEX_op_ld_i64, ret, arg2, offset);
}

static inline void tcg_gen_st8_i64(TCGv_i64 arg1, TCGv_i64 arg2,
                                   tcg_target_long offset)
{
    tcg_gen_ldst_op_i64(INDEX_op_st8_i64, arg1, arg2, offset);
}

static inline void tcg_gen_st16_i64(TCGv_i64 arg1, TCGv_i64 arg2,
                                    tcg_target_long offset)
{
    tcg_gen_ldst_op_i64(INDEX_op_st16_i64, arg1, arg2, offset);
}

static inline void tcg_gen_st32_i64(TCGv_i64 arg1, TCGv_i64 arg2,
                                    tcg_target_long offset)
{
    tcg_gen_ldst_op_i64(INDEX_op_st32_i64, arg1, arg2, offset);
}

static inline void tcg_gen_st_i64(TCGv_i64 arg1, TCGv_i64 arg2, tcg_target_long offset)
{
    tcg_gen_ldst_op_i64(INDEX_op_st_i64, arg1, arg2, offset);
}

static inline void tcg_gen_add_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op3_i64(INDEX_op_add_i64, ret, arg1, arg2);
}

static inline void tcg_gen_sub_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op3_i64(INDEX_op_sub_i64, ret, arg1, arg2);
}

static inline void tcg_gen_and_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op3_i64(INDEX_op_and_i64, ret, arg1, arg2);
}

static inline void tcg_gen_andi_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    TCGv_i64 t0 = tcg_const_i64(arg2);
    tcg_gen_and_i64(ret, arg1, t0);
    tcg_temp_free_i64(t0);
}

static inline void tcg_gen_or_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op3_i64(INDEX_op_or_i64, ret, arg1, arg2);
}

static inline void tcg_gen_ori_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    TCGv_i64 t0 = tcg_const_i64(arg2);
    tcg_gen_or_i64(ret, arg1, t0);
    tcg_temp_free_i64(t0);
}

static inline void tcg_gen_xor_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op3_i64(INDEX_op_xor_i64, ret, arg1, arg2);
}

static inline void tcg_gen_xori_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    TCGv_i64 t0 = tcg_const_i64(arg2);
    tcg_gen_xor_i64(ret, arg1, t0);
    tcg_temp_free_i64(t0);
}

static inline void tcg_gen_shl_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op3_i64(INDEX_op_shl_i64, ret, arg1, arg2);
}

static inline void tcg_gen_shli_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    if (arg2 == 0) {
        tcg_gen_mov_i64(ret, arg1);
    } else {
        TCGv_i64 t0 = tcg_const_i64(arg2);
        tcg_gen_shl_i64(ret, arg1, t0);
        tcg_temp_free_i64(t0);
    }
}

static inline void tcg_gen_shr_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op3_i64(INDEX_op_shr_i64, ret, arg1, arg2);
}

static inline void tcg_gen_shri_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    if (arg2 == 0) {
        tcg_gen_mov_i64(ret, arg1);
    } else {
        TCGv_i64 t0 = tcg_const_i64(arg2);
        tcg_gen_shr_i64(ret, arg1, t0);
        tcg_temp_free_i64(t0);
    }
}

static inline void tcg_gen_sar_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op3_i64(INDEX_op_sar_i64, ret, arg1, arg2);
}

static inline void tcg_gen_sari_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    if (arg2 == 0) {
        tcg_gen_mov_i64(ret, arg1);
    } else {
        TCGv_i64 t0 = tcg_const_i64(arg2);
        tcg_gen_sar_i64(ret, arg1, t0);
        tcg_temp_free_i64(t0);
    }
}

static inline void tcg_gen_brcond_i64(int cond, TCGv_i64 arg1, TCGv_i64 arg2,
                                      int label_index)
{
    tcg_gen_op4ii_i64(INDEX_op_brcond_i64, arg1, arg2, cond, label_index);
}

static inline void tcg_gen_mul_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op3_i64(INDEX_op_mul_i64, ret, arg1, arg2);
}

#ifdef TCG_TARGET_HAS_div_i64
static inline void tcg_gen_div_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op3_i64(INDEX_op_div_i64, ret, arg1, arg2);
}

static inline void tcg_gen_rem_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op3_i64(INDEX_op_rem_i64, ret, arg1, arg2);
}

static inline void tcg_gen_divu_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op3_i64(INDEX_op_divu_i64, ret, arg1, arg2);
}

static inline void tcg_gen_remu_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    tcg_gen_op3_i64(INDEX_op_remu_i64, ret, arg1, arg2);
}
#else
static inline void tcg_gen_div_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    TCGv_i64 t0;
    t0 = tcg_temp_new_i64();
    tcg_gen_sari_i64(t0, arg1, 63);
    tcg_gen_op5_i64(INDEX_op_div2_i64, ret, t0, arg1, t0, arg2);
    tcg_temp_free_i64(t0);
}

static inline void tcg_gen_rem_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    TCGv_i64 t0;
    t0 = tcg_temp_new_i64();
    tcg_gen_sari_i64(t0, arg1, 63);
    tcg_gen_op5_i64(INDEX_op_div2_i64, t0, ret, arg1, t0, arg2);
    tcg_temp_free_i64(t0);
}

static inline void tcg_gen_divu_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    TCGv_i64 t0;
    t0 = tcg_temp_new_i64();
    tcg_gen_movi_i64(t0, 0);
    tcg_gen_op5_i64(INDEX_op_divu2_i64, ret, t0, arg1, t0, arg2);
    tcg_temp_free_i64(t0);
}

static inline void tcg_gen_remu_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    TCGv_i64 t0;
    t0 = tcg_temp_new_i64();
    tcg_gen_movi_i64(t0, 0);
    tcg_gen_op5_i64(INDEX_op_divu2_i64, t0, ret, arg1, t0, arg2);
    tcg_temp_free_i64(t0);
}
#endif

#endif

static inline void tcg_gen_addi_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    /* some cases can be optimized here */
    if (arg2 == 0) {
        tcg_gen_mov_i64(ret, arg1);
    } else {
        TCGv_i64 t0 = tcg_const_i64(arg2);
        tcg_gen_add_i64(ret, arg1, t0);
        tcg_temp_free_i64(t0);
    }
}

static inline void tcg_gen_subfi_i64(TCGv_i64 ret, int64_t arg1, TCGv_i64 arg2)
{
    TCGv_i64 t0 = tcg_const_i64(arg1);
    tcg_gen_sub_i64(ret, t0, arg2);
    tcg_temp_free_i64(t0);
}

static inline void tcg_gen_subi_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    /* some cases can be optimized here */
    if (arg2 == 0) {
        tcg_gen_mov_i64(ret, arg1);
    } else {
        TCGv_i64 t0 = tcg_const_i64(arg2);
        tcg_gen_sub_i64(ret, arg1, t0);
        tcg_temp_free_i64(t0);
    }
}
static inline void tcg_gen_brcondi_i64(int cond, TCGv_i64 arg1, int64_t arg2,
                                       int label_index)
{
    TCGv_i64 t0 = tcg_const_i64(arg2);
    tcg_gen_brcond_i64(cond, arg1, t0, label_index);
    tcg_temp_free_i64(t0);
}

static inline void tcg_gen_muli_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    TCGv_i64 t0 = tcg_const_i64(arg2);
    tcg_gen_mul_i64(ret, arg1, t0);
    tcg_temp_free_i64(t0);
}


/***************************************/
/* optional operations */

static inline void tcg_gen_ext8s_i32(TCGv_i32 ret, TCGv_i32 arg)
{
#ifdef TCG_TARGET_HAS_ext8s_i32
    tcg_gen_op2_i32(INDEX_op_ext8s_i32, ret, arg);
#else
    tcg_gen_shli_i32(ret, arg, 24);
    tcg_gen_sari_i32(ret, ret, 24);
#endif
}

static inline void tcg_gen_ext16s_i32(TCGv_i32 ret, TCGv_i32 arg)
{
#ifdef TCG_TARGET_HAS_ext16s_i32
    tcg_gen_op2_i32(INDEX_op_ext16s_i32, ret, arg);
#else
    tcg_gen_shli_i32(ret, arg, 16);
    tcg_gen_sari_i32(ret, ret, 16);
#endif
}

/* These are currently just for convenience.
   We assume a target will recognise these automatically .  */
static inline void tcg_gen_ext8u_i32(TCGv_i32 ret, TCGv_i32 arg)
{
    tcg_gen_andi_i32(ret, arg, 0xffu);
}

static inline void tcg_gen_ext16u_i32(TCGv_i32 ret, TCGv_i32 arg)
{
    tcg_gen_andi_i32(ret, arg, 0xffffu);
}

/* Note: we assume the two high bytes are set to zero */
static inline void tcg_gen_bswap16_i32(TCGv_i32 ret, TCGv_i32 arg)
{
#ifdef TCG_TARGET_HAS_bswap16_i32
    tcg_gen_op2_i32(INDEX_op_bswap16_i32, ret, arg);
#else
    TCGv_i32 t0, t1;
    t0 = tcg_temp_new_i32();
    t1 = tcg_temp_new_i32();
    
    tcg_gen_shri_i32(t0, arg, 8);
    tcg_gen_andi_i32(t1, arg, 0x000000ff);
    tcg_gen_shli_i32(t1, t1, 8);
    tcg_gen_or_i32(ret, t0, t1);
    tcg_temp_free_i32(t0);
    tcg_temp_free_i32(t1);
#endif
}

static inline void tcg_gen_bswap_i32(TCGv_i32 ret, TCGv_i32 arg)
{
#ifdef TCG_TARGET_HAS_bswap_i32
    tcg_gen_op2_i32(INDEX_op_bswap_i32, ret, arg);
#else
    TCGv_i32 t0, t1;
    t0 = tcg_temp_new_i32();
    t1 = tcg_temp_new_i32();
    
    tcg_gen_shli_i32(t0, arg, 24);
    
    tcg_gen_andi_i32(t1, arg, 0x0000ff00);
    tcg_gen_shli_i32(t1, t1, 8);
    tcg_gen_or_i32(t0, t0, t1);
    
    tcg_gen_shri_i32(t1, arg, 8);
    tcg_gen_andi_i32(t1, t1, 0x0000ff00);
    tcg_gen_or_i32(t0, t0, t1);
    
    tcg_gen_shri_i32(t1, arg, 24);
    tcg_gen_or_i32(ret, t0, t1);
    tcg_temp_free_i32(t0);
    tcg_temp_free_i32(t1);
#endif
}

#if TCG_TARGET_REG_BITS == 32
static inline void tcg_gen_ext8s_i64(TCGv_i64 ret, TCGv_i64 arg)
{
    tcg_gen_ext8s_i32(TCGV_LOW(ret), TCGV_LOW(arg));
    tcg_gen_sari_i32(TCGV_HIGH(ret), TCGV_LOW(ret), 31);
}

static inline void tcg_gen_ext16s_i64(TCGv_i64 ret, TCGv_i64 arg)
{
    tcg_gen_ext16s_i32(TCGV_LOW(ret), TCGV_LOW(arg));
    tcg_gen_sari_i32(TCGV_HIGH(ret), TCGV_LOW(ret), 31);
}

static inline void tcg_gen_ext32s_i64(TCGv_i64 ret, TCGv_i64 arg)
{
    tcg_gen_mov_i32(TCGV_LOW(ret), TCGV_LOW(arg));
    tcg_gen_sari_i32(TCGV_HIGH(ret), TCGV_LOW(ret), 31);
}

static inline void tcg_gen_ext8u_i64(TCGv_i64 ret, TCGv_i64 arg)
{
    tcg_gen_ext8u_i32(TCGV_LOW(ret), TCGV_LOW(arg));
    tcg_gen_movi_i32(TCGV_HIGH(ret), 0);
}

static inline void tcg_gen_ext16u_i64(TCGv_i64 ret, TCGv_i64 arg)
{
    tcg_gen_ext16u_i32(TCGV_LOW(ret), TCGV_LOW(arg));
    tcg_gen_movi_i32(TCGV_HIGH(ret), 0);
}

static inline void tcg_gen_ext32u_i64(TCGv_i64 ret, TCGv_i64 arg)
{
    tcg_gen_mov_i32(TCGV_LOW(ret), TCGV_LOW(arg));
    tcg_gen_movi_i32(TCGV_HIGH(ret), 0);
}

static inline void tcg_gen_trunc_i64_i32(TCGv_i32 ret, TCGv_i64 arg)
{
    tcg_gen_mov_i32(ret, TCGV_LOW(arg));
}

static inline void tcg_gen_extu_i32_i64(TCGv_i64 ret, TCGv_i32 arg)
{
    tcg_gen_mov_i32(TCGV_LOW(ret), arg);
    tcg_gen_movi_i32(TCGV_HIGH(ret), 0);
}

static inline void tcg_gen_ext_i32_i64(TCGv_i64 ret, TCGv_i32 arg)
{
    tcg_gen_mov_i32(TCGV_LOW(ret), arg);
    tcg_gen_sari_i32(TCGV_HIGH(ret), TCGV_LOW(ret), 31);
}

static inline void tcg_gen_bswap_i64(TCGv_i64 ret, TCGv_i64 arg)
{
    TCGv_i32 t0, t1;
    t0 = tcg_temp_new_i32();
    t1 = tcg_temp_new_i32();

    tcg_gen_bswap_i32(t0, TCGV_LOW(arg));
    tcg_gen_bswap_i32(t1, TCGV_HIGH(arg));
    tcg_gen_mov_i32(TCGV_LOW(ret), t1);
    tcg_gen_mov_i32(TCGV_HIGH(ret), t0);
    tcg_temp_free_i32(t0);
    tcg_temp_free_i32(t1);
}
#else

static inline void tcg_gen_ext8s_i64(TCGv_i64 ret, TCGv_i64 arg)
{
#ifdef TCG_TARGET_HAS_ext8s_i64
    tcg_gen_op2_i64(INDEX_op_ext8s_i64, ret, arg);
#else
    tcg_gen_shli_i64(ret, arg, 56);
    tcg_gen_sari_i64(ret, ret, 56);
#endif
}

static inline void tcg_gen_ext16s_i64(TCGv_i64 ret, TCGv_i64 arg)
{
#ifdef TCG_TARGET_HAS_ext16s_i64
    tcg_gen_op2_i64(INDEX_op_ext16s_i64, ret, arg);
#else
    tcg_gen_shli_i64(ret, arg, 48);
    tcg_gen_sari_i64(ret, ret, 48);
#endif
}

static inline void tcg_gen_ext32s_i64(TCGv_i64 ret, TCGv_i64 arg)
{
#ifdef TCG_TARGET_HAS_ext32s_i64
    tcg_gen_op2_i64(INDEX_op_ext32s_i64, ret, arg);
#else
    tcg_gen_shli_i64(ret, arg, 32);
    tcg_gen_sari_i64(ret, ret, 32);
#endif
}

static inline void tcg_gen_ext8u_i64(TCGv_i64 ret, TCGv_i64 arg)
{
    tcg_gen_andi_i64(ret, arg, 0xffu);
}

static inline void tcg_gen_ext16u_i64(TCGv_i64 ret, TCGv_i64 arg)
{
    tcg_gen_andi_i64(ret, arg, 0xffffu);
}

static inline void tcg_gen_ext32u_i64(TCGv_i64 ret, TCGv_i64 arg)
{
    tcg_gen_andi_i64(ret, arg, 0xffffffffu);
}

/* Note: we assume the target supports move between 32 and 64 bit
   registers.  This will probably break MIPS64 targets.  */
static inline void tcg_gen_trunc_i64_i32(TCGv_i32 ret, TCGv_i64 arg)
{
    tcg_gen_mov_i32(ret, MAKE_TCGV_I32(GET_TCGV_I64(arg)));
}

/* Note: we assume the target supports move between 32 and 64 bit
   registers */
static inline void tcg_gen_extu_i32_i64(TCGv_i64 ret, TCGv_i32 arg)
{
    tcg_gen_andi_i64(ret, MAKE_TCGV_I64(GET_TCGV_I32(arg)), 0xffffffffu);
}

/* Note: we assume the target supports move between 32 and 64 bit
   registers */
static inline void tcg_gen_ext_i32_i64(TCGv_i64 ret, TCGv_i32 arg)
{
    tcg_gen_ext32s_i64(ret, MAKE_TCGV_I64(GET_TCGV_I32(arg)));
}

static inline void tcg_gen_bswap_i64(TCGv_i64 ret, TCGv_i64 arg)
{
#ifdef TCG_TARGET_HAS_bswap_i64
    tcg_gen_op2_i64(INDEX_op_bswap_i64, ret, arg);
#else
    TCGv_i32 t0, t1;
    t0 = tcg_temp_new_i32();
    t1 = tcg_temp_new_i32();
    
    tcg_gen_shli_i64(t0, arg, 56);
    
    tcg_gen_andi_i64(t1, arg, 0x0000ff00);
    tcg_gen_shli_i64(t1, t1, 40);
    tcg_gen_or_i64(t0, t0, t1);
    
    tcg_gen_andi_i64(t1, arg, 0x00ff0000);
    tcg_gen_shli_i64(t1, t1, 24);
    tcg_gen_or_i64(t0, t0, t1);

    tcg_gen_andi_i64(t1, arg, 0xff000000);
    tcg_gen_shli_i64(t1, t1, 8);
    tcg_gen_or_i64(t0, t0, t1);

    tcg_gen_shri_i64(t1, arg, 8);
    tcg_gen_andi_i64(t1, t1, 0xff000000);
    tcg_gen_or_i64(t0, t0, t1);
    
    tcg_gen_shri_i64(t1, arg, 24);
    tcg_gen_andi_i64(t1, t1, 0x00ff0000);
    tcg_gen_or_i64(t0, t0, t1);

    tcg_gen_shri_i64(t1, arg, 40);
    tcg_gen_andi_i64(t1, t1, 0x0000ff00);
    tcg_gen_or_i64(t0, t0, t1);

    tcg_gen_shri_i64(t1, arg, 56);
    tcg_gen_or_i64(ret, t0, t1);
    tcg_temp_free_i32(t0);
    tcg_temp_free_i32(t1);
#endif
}

#endif
/* neg_i32/i64 t0, t1 ==> t0 = -t1 (two's complement) */
static inline void tcg_gen_neg_i32(TCGv_i32 ret, TCGv_i32 arg)
{
#ifdef TCG_TARGET_HAS_neg_i32
    tcg_gen_op2_i32(INDEX_op_neg_i32, ret, arg);
#else
    TCGv_i32 t0 = tcg_const_i32(0);
    tcg_gen_sub_i32(ret, t0, arg);
    tcg_temp_free_i32(t0);
#endif
}

static inline void tcg_gen_neg_i64(TCGv_i64 ret, TCGv_i64 arg)
{
#ifdef TCG_TARGET_HAS_neg_i64
    tcg_gen_op2_i64(INDEX_op_neg_i64, ret, arg);
#else
    TCGv_i64 t0 = tcg_const_i64(0);
    tcg_gen_sub_i64(ret, t0, arg);
    tcg_temp_free_i64(t0);
#endif
}
/* not_i32/i64 t0, t1 ==> t0 = ~t1 */
static inline void tcg_gen_not_i32(TCGv_i32 ret, TCGv_i32 arg)
{
    tcg_gen_xori_i32(ret, arg, -1);
}
/* not_i32/i64 t0, t1 ==> t0 = ~t1 */
static inline void tcg_gen_not_i64(TCGv_i64 ret, TCGv_i64 arg)
{
    tcg_gen_xori_i64(ret, arg, -1);
}
/* discard_i32/i64 t0 ==> Indicate that the value of t0 won't be used later. 
 * It is useful to force dead code elimination.
 */
static inline void tcg_gen_discard_i32(TCGv_i32 arg)
{
    tcg_gen_op1_i32(INDEX_op_discard, arg);
}

#if TCG_TARGET_REG_BITS == 32
static inline void tcg_gen_discard_i64(TCGv_i64 arg)
{
    tcg_gen_discard_i32(TCGV_LOW(arg));
    tcg_gen_discard_i32(TCGV_HIGH(arg));
}
#else
static inline void tcg_gen_discard_i64(TCGv_i64 arg)
{
    tcg_gen_op1_i64(INDEX_op_discard, arg);
}
#endif

static inline void tcg_gen_concat_i32_i64(TCGv_i64 dest, TCGv_i32 low, TCGv_i32 high)
{
#if TCG_TARGET_REG_BITS == 32
    tcg_gen_mov_i32(TCGV_LOW(dest), low);
    tcg_gen_mov_i32(TCGV_HIGH(dest), high);
#else
    TCGv_i64 tmp = tcg_temp_new_i64();
    /* This extension is only needed for type correctness.
       We may be able to do better given target specific information.  */
    tcg_gen_extu_i32_i64(tmp, high);
    tcg_gen_shli_i64(tmp, tmp, 32);
    tcg_gen_extu_i32_i64(dest, low);
    tcg_gen_or_i64(dest, dest, tmp);
    tcg_temp_free_i64(tmp);
#endif
}

static inline void tcg_gen_concat32_i64(TCGv_i64 dest, TCGv_i64 low, TCGv_i64 high)
{
#if TCG_TARGET_REG_BITS == 32
    tcg_gen_concat_i32_i64(dest, TCGV_LOW(low), TCGV_LOW(high));
#else
    TCGv_i64 tmp = tcg_temp_new_i64();
    tcg_gen_ext32u_i64(dest, low);
    tcg_gen_shli_i64(tmp, high, 32);
    tcg_gen_or_i64(dest, dest, tmp);
    tcg_temp_free_i64(tmp);
#endif
}

static inline void tcg_gen_andc_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    TCGv_i32 t0;
    t0 = tcg_temp_new_i32();
    tcg_gen_not_i32(t0, arg2);
    tcg_gen_and_i32(ret, arg1, t0);
    tcg_temp_free_i32(t0);
}

static inline void tcg_gen_andc_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    TCGv_i64 t0;
    t0 = tcg_temp_new_i64();
    tcg_gen_not_i64(t0, arg2);
    tcg_gen_and_i64(ret, arg1, t0);
    tcg_temp_free_i64(t0);
}

static inline void tcg_gen_eqv_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    TCGv_i32 t0;
    t0 = tcg_temp_new_i32();
    tcg_gen_xor_i32(t0, arg1, arg2);
    tcg_gen_not_i32(ret, t0);
    tcg_temp_free_i32(t0);
}

static inline void tcg_gen_eqv_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    TCGv_i64 t0;
    t0 = tcg_temp_new_i64();
    tcg_gen_xor_i64(t0, arg1, arg2);
    tcg_gen_not_i64(ret, t0);
    tcg_temp_free_i64(t0);
}

static inline void tcg_gen_nand_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    TCGv_i32 t0;
    t0 = tcg_temp_new_i32();
    tcg_gen_and_i32(t0, arg1, arg2);
    tcg_gen_not_i32(ret, t0);
    tcg_temp_free_i32(t0);
}

static inline void tcg_gen_nand_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    TCGv_i64 t0;
    t0 = tcg_temp_new_i64();
    tcg_gen_and_i64(t0, arg1, arg2);
    tcg_gen_not_i64(ret, t0);
    tcg_temp_free_i64(t0);
}

static inline void tcg_gen_nor_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    TCGv_i32 t0;
    t0 = tcg_temp_new_i32();
    tcg_gen_or_i32(t0, arg1, arg2);
    tcg_gen_not_i32(ret, t0);
    tcg_temp_free_i32(t0);
}

static inline void tcg_gen_nor_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    TCGv_i64 t0;
    t0 = tcg_temp_new_i64();
    tcg_gen_or_i64(t0, arg1, arg2);
    tcg_gen_not_i64(ret, t0);
    tcg_temp_free_i64(t0);
}

static inline void tcg_gen_orc_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    TCGv_i32 t0;
    t0 = tcg_temp_new_i32();
    tcg_gen_not_i32(t0, arg2);
    tcg_gen_or_i32(ret, arg1, t0);
    tcg_temp_free_i32(t0);
}

static inline void tcg_gen_orc_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    TCGv_i64 t0;
    t0 = tcg_temp_new_i64();
    tcg_gen_not_i64(t0, arg2);
    tcg_gen_or_i64(ret, arg1, t0);
    tcg_temp_free_i64(t0);
}

static inline void tcg_gen_rotl_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    TCGv_i32 t0, t1;

    t0 = tcg_temp_new_i32();
    t1 = tcg_temp_new_i32();
    tcg_gen_shl_i32(t0, arg1, arg2);
    tcg_gen_subfi_i32(t1, 32, arg2);
    tcg_gen_shr_i32(t1, arg1, t1);
    tcg_gen_or_i32(ret, t0, t1);
    tcg_temp_free_i32(t0);
    tcg_temp_free_i32(t1);
}

static inline void tcg_gen_rotl_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    TCGv_i64 t0, t1;

    t0 = tcg_temp_new_i64();
    t1 = tcg_temp_new_i64();
    tcg_gen_shl_i64(t0, arg1, arg2);
    tcg_gen_subfi_i64(t1, 64, arg2);
    tcg_gen_shr_i64(t1, arg1, t1);
    tcg_gen_or_i64(ret, t0, t1);
    tcg_temp_free_i64(t0);
    tcg_temp_free_i64(t1);
}

static inline void tcg_gen_rotli_i32(TCGv_i32 ret, TCGv_i32 arg1, int32_t arg2)
{
    /* some cases can be optimized here */
    if (arg2 == 0) {
        tcg_gen_mov_i32(ret, arg1);
    } else {
        TCGv_i32 t0, t1;
        t0 = tcg_temp_new_i32();
        t1 = tcg_temp_new_i32();
        tcg_gen_shli_i32(t0, arg1, arg2);
        tcg_gen_shri_i32(t1, arg1, 32 - arg2);
        tcg_gen_or_i32(ret, t0, t1);
        tcg_temp_free_i32(t0);
        tcg_temp_free_i32(t1);
    }
}

static inline void tcg_gen_rotli_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    /* some cases can be optimized here */
    if (arg2 == 0) {
        tcg_gen_mov_i64(ret, arg1);
    } else {
        TCGv_i64 t0, t1;
        t0 = tcg_temp_new_i64();
        t1 = tcg_temp_new_i64();
        tcg_gen_shli_i64(t0, arg1, arg2);
        tcg_gen_shri_i64(t1, arg1, 64 - arg2);
        tcg_gen_or_i64(ret, t0, t1);
        tcg_temp_free_i64(t0);
        tcg_temp_free_i64(t1);
    }
}

static inline void tcg_gen_rotr_i32(TCGv_i32 ret, TCGv_i32 arg1, TCGv_i32 arg2)
{
    TCGv_i32 t0, t1;

    t0 = tcg_temp_new_i32();
    t1 = tcg_temp_new_i32();
    tcg_gen_shr_i32(t0, arg1, arg2);
    tcg_gen_subfi_i32(t1, 32, arg2);
    tcg_gen_shl_i32(t1, arg1, t1);
    tcg_gen_or_i32(ret, t0, t1);
    tcg_temp_free_i32(t0);
    tcg_temp_free_i32(t1);
}

static inline void tcg_gen_rotr_i64(TCGv_i64 ret, TCGv_i64 arg1, TCGv_i64 arg2)
{
    TCGv_i64 t0, t1;

    t0 = tcg_temp_new_i64();
    t1 = tcg_temp_new_i64();
    tcg_gen_shl_i64(t0, arg1, arg2);
    tcg_gen_subfi_i64(t1, 64, arg2);
    tcg_gen_shl_i64(t1, arg1, t1);
    tcg_gen_or_i64(ret, t0, t1);
    tcg_temp_free_i64(t0);
    tcg_temp_free_i64(t1);
}

static inline void tcg_gen_rotri_i32(TCGv_i32 ret, TCGv_i32 arg1, int32_t arg2)
{
    /* some cases can be optimized here */
    if (arg2 == 0) {
        tcg_gen_mov_i32(ret, arg1);
    } else {
        tcg_gen_rotli_i32(ret, arg1, 32 - arg2);
    }
}

static inline void tcg_gen_rotri_i64(TCGv_i64 ret, TCGv_i64 arg1, int64_t arg2)
{
    /* some cases can be optimized here */
    if (arg2 == 0) {
        tcg_gen_mov_i64(ret, arg1);
    } else {
        tcg_gen_rotli_i64(ret, arg1, 64 - arg2);
    }
}

/***************************************/
/* QEMU specific operations. Their type depend on the QEMU CPU
   type. */
#ifndef TARGET_LONG_BITS
#error must include QEMU headers
#endif

#if TARGET_LONG_BITS == 32
#define TCGv TCGv_i32
#define tcg_temp_new() tcg_temp_new_i32()
#define tcg_global_reg_new tcg_global_reg_new_i32
#define tcg_global_mem_new tcg_global_mem_new_i32
#define tcg_temp_local_new() tcg_temp_local_new_i32()
#define tcg_temp_free tcg_temp_free_i32
#define tcg_gen_qemu_ldst_op tcg_gen_op3i_i32
#define tcg_gen_qemu_ldst_op_i64 tcg_gen_qemu_ldst_op_i64_i32
#define TCGV_UNUSED(x) TCGV_UNUSED_I32(x)
#define TCGV_EQUAL(a, b) (GET_TCGV_I32(a) == GET_TCGV_I32(b))
#else
#define TCGv TCGv_i64
#define tcg_temp_new() tcg_temp_new_i64()
#define tcg_global_reg_new tcg_global_reg_new_i64
#define tcg_global_mem_new tcg_global_mem_new_i64
#define tcg_temp_local_new() tcg_temp_local_new_i64()
#define tcg_temp_free tcg_temp_free_i64
#define tcg_gen_qemu_ldst_op tcg_gen_op3i_i64
#define tcg_gen_qemu_ldst_op_i64 tcg_gen_qemu_ldst_op_i64_i64
#define TCGV_UNUSED(x) TCGV_UNUSED_I64(x)
#define TCGV_EQUAL(a, b) (GET_TCGV_I64(a) == GET_TCGV_I64(b))
#endif

/* debug info: write the PC of the corresponding QEMU CPU instruction */
static inline void tcg_gen_debug_insn_start(uint64_t pc)
{
    /* XXX: must really use a 32 bit size for TCGArg in all cases */
#if TARGET_LONG_BITS > TCG_TARGET_REG_BITS
    tcg_gen_op2ii(INDEX_op_debug_insn_start, 
                  (uint32_t)(pc), (uint32_t)(pc >> 32));
#else
    tcg_gen_op1i(INDEX_op_debug_insn_start, pc);
#endif
}

static inline void tcg_gen_exit_tb(tcg_target_long val)
{
    tcg_gen_op1i(INDEX_op_exit_tb, val);
}

static inline void tcg_gen_goto_tb(int idx)
{
    tcg_gen_op1i(INDEX_op_goto_tb, idx);
}

#if TCG_TARGET_REG_BITS == 32
/* qemu_ld8u t0, t1, flags ==>
 * Load data at the QEMU CPU address t1 into t0. t1 has the QEMU CPU
 * address type. 'flags' contains the QEMU memory index (selects user or
 * kernel access) for example.
 * 将t1指向的值加载到t0中去.
 */
static inline void tcg_gen_qemu_ld8u(TCGv ret, TCGv addr, int mem_index)
{
#if TARGET_LONG_BITS == 32
    tcg_gen_op3i_i32(INDEX_op_qemu_ld8u, ret, addr, mem_index);
#else
    tcg_gen_op4i_i32(INDEX_op_qemu_ld8u, TCGV_LOW(ret), TCGV_LOW(addr),
                     TCGV_HIGH(addr), mem_index);
    tcg_gen_movi_i32(TCGV_HIGH(ret), 0);
#endif
}

static inline void tcg_gen_qemu_ld8s(TCGv ret, TCGv addr, int mem_index)
{
#if TARGET_LONG_BITS == 32
    tcg_gen_op3i_i32(INDEX_op_qemu_ld8s, ret, addr, mem_index);
#else
    tcg_gen_op4i_i32(INDEX_op_qemu_ld8s, TCGV_LOW(ret), TCGV_LOW(addr),
                     TCGV_HIGH(addr), mem_index);
    tcg_gen_sari_i32(TCGV_HIGH(ret), TCGV_LOW(ret), 31);
#endif
}

static inline void tcg_gen_qemu_ld16u(TCGv ret, TCGv addr, int mem_index)
{
#if TARGET_LONG_BITS == 32
    tcg_gen_op3i_i32(INDEX_op_qemu_ld16u, ret, addr, mem_index);
#else
    tcg_gen_op4i_i32(INDEX_op_qemu_ld16u, TCGV_LOW(ret), TCGV_LOW(addr),
                     TCGV_HIGH(addr), mem_index);
    tcg_gen_movi_i32(TCGV_HIGH(ret), 0);
#endif
}

static inline void tcg_gen_qemu_ld16s(TCGv ret, TCGv addr, int mem_index)
{
#if TARGET_LONG_BITS == 32
    tcg_gen_op3i_i32(INDEX_op_qemu_ld16s, ret, addr, mem_index);
#else
    tcg_gen_op4i_i32(INDEX_op_qemu_ld16s, TCGV_LOW(ret), TCGV_LOW(addr),
                     TCGV_HIGH(addr), mem_index);
    tcg_gen_sari_i32(TCGV_HIGH(ret), TCGV_LOW(ret), 31);
#endif
}

static inline void tcg_gen_qemu_ld32u(TCGv ret, TCGv addr, int mem_index)
{
#if TARGET_LONG_BITS == 32
    tcg_gen_op3i_i32(INDEX_op_qemu_ld32u, ret, addr, mem_index);
#else
    tcg_gen_op4i_i32(INDEX_op_qemu_ld32u, TCGV_LOW(ret), TCGV_LOW(addr),
                     TCGV_HIGH(addr), mem_index);
    tcg_gen_movi_i32(TCGV_HIGH(ret), 0);
#endif
}

static inline void tcg_gen_qemu_ld32s(TCGv ret, TCGv addr, int mem_index)
{
#if TARGET_LONG_BITS == 32
    tcg_gen_op3i_i32(INDEX_op_qemu_ld32u, ret, addr, mem_index);
#else
    tcg_gen_op4i_i32(INDEX_op_qemu_ld32u, TCGV_LOW(ret), TCGV_LOW(addr),
                     TCGV_HIGH(addr), mem_index);
    tcg_gen_sari_i32(TCGV_HIGH(ret), TCGV_LOW(ret), 31);
#endif
}

static inline void tcg_gen_qemu_ld64(TCGv_i64 ret, TCGv addr, int mem_index)
{
#if TARGET_LONG_BITS == 32
    tcg_gen_op4i_i32(INDEX_op_qemu_ld64, TCGV_LOW(ret), TCGV_HIGH(ret), addr, mem_index);
#else
    tcg_gen_op5i_i32(INDEX_op_qemu_ld64, TCGV_LOW(ret), TCGV_HIGH(ret),
                     TCGV_LOW(addr), TCGV_HIGH(addr), mem_index);
#endif
}

static inline void tcg_gen_qemu_st8(TCGv arg, TCGv addr, int mem_index)
{
#if TARGET_LONG_BITS == 32
    tcg_gen_op3i_i32(INDEX_op_qemu_st8, arg, addr, mem_index);
#else
    tcg_gen_op4i_i32(INDEX_op_qemu_st8, TCGV_LOW(arg), TCGV_LOW(addr),
                     TCGV_HIGH(addr), mem_index);
#endif
}

static inline void tcg_gen_qemu_st16(TCGv arg, TCGv addr, int mem_index)
{
#if TARGET_LONG_BITS == 32
    tcg_gen_op3i_i32(INDEX_op_qemu_st16, arg, addr, mem_index);
#else
    tcg_gen_op4i_i32(INDEX_op_qemu_st16, TCGV_LOW(arg), TCGV_LOW(addr),
                     TCGV_HIGH(addr), mem_index);
#endif
}

static inline void tcg_gen_qemu_st32(TCGv arg, TCGv addr, int mem_index)
{
#if TARGET_LONG_BITS == 32
    tcg_gen_op3i_i32(INDEX_op_qemu_st32, arg, addr, mem_index);
#else
    tcg_gen_op4i_i32(INDEX_op_qemu_st32, TCGV_LOW(arg), TCGV_LOW(addr),
                     TCGV_HIGH(addr), mem_index);
#endif
}

static inline void tcg_gen_qemu_st64(TCGv_i64 arg, TCGv addr, int mem_index)
{
#if TARGET_LONG_BITS == 32
    tcg_gen_op4i_i32(INDEX_op_qemu_st64, TCGV_LOW(arg), TCGV_HIGH(arg), addr,
                     mem_index);
#else
    tcg_gen_op5i_i32(INDEX_op_qemu_st64, TCGV_LOW(arg), TCGV_HIGH(arg),
                     TCGV_LOW(addr), TCGV_HIGH(addr), mem_index);
#endif
}

#define tcg_gen_ld_ptr tcg_gen_ld_i32
#define tcg_gen_discard_ptr tcg_gen_discard_i32

#else /* TCG_TARGET_REG_BITS == 32 */

static inline void tcg_gen_qemu_ld8u(TCGv ret, TCGv addr, int mem_index)
{
    tcg_gen_qemu_ldst_op(INDEX_op_qemu_ld8u, ret, addr, mem_index);
}

static inline void tcg_gen_qemu_ld8s(TCGv ret, TCGv addr, int mem_index)
{
    tcg_gen_qemu_ldst_op(INDEX_op_qemu_ld8s, ret, addr, mem_index);
}

static inline void tcg_gen_qemu_ld16u(TCGv ret, TCGv addr, int mem_index)
{
    tcg_gen_qemu_ldst_op(INDEX_op_qemu_ld16u, ret, addr, mem_index);
}

static inline void tcg_gen_qemu_ld16s(TCGv ret, TCGv addr, int mem_index)
{
    tcg_gen_qemu_ldst_op(INDEX_op_qemu_ld16s, ret, addr, mem_index);
}

static inline void tcg_gen_qemu_ld32u(TCGv ret, TCGv addr, int mem_index)
{
    tcg_gen_qemu_ldst_op(INDEX_op_qemu_ld32u, ret, addr, mem_index);
}

static inline void tcg_gen_qemu_ld32s(TCGv ret, TCGv addr, int mem_index)
{
    tcg_gen_qemu_ldst_op(INDEX_op_qemu_ld32s, ret, addr, mem_index);
}

static inline void tcg_gen_qemu_ld64(TCGv_i64 ret, TCGv addr, int mem_index)
{
    tcg_gen_qemu_ldst_op_i64(INDEX_op_qemu_ld64, ret, addr, mem_index);
}

static inline void tcg_gen_qemu_st8(TCGv arg, TCGv addr, int mem_index)
{
    tcg_gen_qemu_ldst_op(INDEX_op_qemu_st8, arg, addr, mem_index);
}

static inline void tcg_gen_qemu_st16(TCGv arg, TCGv addr, int mem_index)
{
    tcg_gen_qemu_ldst_op(INDEX_op_qemu_st16, arg, addr, mem_index);
}

static inline void tcg_gen_qemu_st32(TCGv arg, TCGv addr, int mem_index)
{
    tcg_gen_qemu_ldst_op(INDEX_op_qemu_st32, arg, addr, mem_index);
}

static inline void tcg_gen_qemu_st64(TCGv_i64 arg, TCGv addr, int mem_index)
{
    tcg_gen_qemu_ldst_op_i64(INDEX_op_qemu_st64, arg, addr, mem_index);
}

#define tcg_gen_ld_ptr tcg_gen_ld_i64
#define tcg_gen_discard_ptr tcg_gen_discard_i64

#endif /* TCG_TARGET_REG_BITS != 32 */

#if TARGET_LONG_BITS == 64
#define TCG_TYPE_TL TCG_TYPE_I64
#define tcg_gen_movi_tl tcg_gen_movi_i64
#define tcg_gen_mov_tl tcg_gen_mov_i64
#define tcg_gen_ld8u_tl tcg_gen_ld8u_i64
#define tcg_gen_ld8s_tl tcg_gen_ld8s_i64
#define tcg_gen_ld16u_tl tcg_gen_ld16u_i64
#define tcg_gen_ld16s_tl tcg_gen_ld16s_i64
#define tcg_gen_ld32u_tl tcg_gen_ld32u_i64
#define tcg_gen_ld32s_tl tcg_gen_ld32s_i64
#define tcg_gen_ld_tl tcg_gen_ld_i64
#define tcg_gen_st8_tl tcg_gen_st8_i64
#define tcg_gen_st16_tl tcg_gen_st16_i64
#define tcg_gen_st32_tl tcg_gen_st32_i64
#define tcg_gen_st_tl tcg_gen_st_i64
#define tcg_gen_add_tl tcg_gen_add_i64
#define tcg_gen_addi_tl tcg_gen_addi_i64
#define tcg_gen_sub_tl tcg_gen_sub_i64
#define tcg_gen_neg_tl tcg_gen_neg_i64
#define tcg_gen_subfi_tl tcg_gen_subfi_i64
#define tcg_gen_subi_tl tcg_gen_subi_i64
#define tcg_gen_and_tl tcg_gen_and_i64
#define tcg_gen_andi_tl tcg_gen_andi_i64
#define tcg_gen_or_tl tcg_gen_or_i64
#define tcg_gen_ori_tl tcg_gen_ori_i64
#define tcg_gen_xor_tl tcg_gen_xor_i64
#define tcg_gen_xori_tl tcg_gen_xori_i64
#define tcg_gen_not_tl tcg_gen_not_i64
#define tcg_gen_shl_tl tcg_gen_shl_i64
#define tcg_gen_shli_tl tcg_gen_shli_i64
#define tcg_gen_shr_tl tcg_gen_shr_i64
#define tcg_gen_shri_tl tcg_gen_shri_i64
#define tcg_gen_sar_tl tcg_gen_sar_i64
#define tcg_gen_sari_tl tcg_gen_sari_i64
#define tcg_gen_brcond_tl tcg_gen_brcond_i64
#define tcg_gen_brcondi_tl tcg_gen_brcondi_i64
#define tcg_gen_mul_tl tcg_gen_mul_i64
#define tcg_gen_muli_tl tcg_gen_muli_i64
#define tcg_gen_discard_tl tcg_gen_discard_i64
#define tcg_gen_trunc_tl_i32 tcg_gen_trunc_i64_i32
#define tcg_gen_trunc_i64_tl tcg_gen_mov_i64
#define tcg_gen_extu_i32_tl tcg_gen_extu_i32_i64
#define tcg_gen_ext_i32_tl tcg_gen_ext_i32_i64
#define tcg_gen_extu_tl_i64 tcg_gen_mov_i64
#define tcg_gen_ext_tl_i64 tcg_gen_mov_i64
#define tcg_gen_ext8u_tl tcg_gen_ext8u_i64
#define tcg_gen_ext8s_tl tcg_gen_ext8s_i64
#define tcg_gen_ext16u_tl tcg_gen_ext16u_i64
#define tcg_gen_ext16s_tl tcg_gen_ext16s_i64
#define tcg_gen_ext32u_tl tcg_gen_ext32u_i64
#define tcg_gen_ext32s_tl tcg_gen_ext32s_i64
#define tcg_gen_concat_tl_i64 tcg_gen_concat32_i64
#define tcg_gen_andc_tl tcg_gen_andc_i64
#define tcg_gen_eqv_tl tcg_gen_eqv_i64
#define tcg_gen_nand_tl tcg_gen_nand_i64
#define tcg_gen_nor_tl tcg_gen_nor_i64
#define tcg_gen_orc_tl tcg_gen_orc_i64
#define tcg_gen_rotl_tl tcg_gen_rotl_i64
#define tcg_gen_rotli_tl tcg_gen_rotli_i64
#define tcg_gen_rotr_tl tcg_gen_rotr_i64
#define tcg_gen_rotri_tl tcg_gen_rotri_i64
#define tcg_const_tl tcg_const_i64
#define tcg_const_local_tl tcg_const_local_i64
#else
#define TCG_TYPE_TL TCG_TYPE_I32
#define tcg_gen_movi_tl tcg_gen_movi_i32
#define tcg_gen_mov_tl tcg_gen_mov_i32
#define tcg_gen_ld8u_tl tcg_gen_ld8u_i32
#define tcg_gen_ld8s_tl tcg_gen_ld8s_i32
#define tcg_gen_ld16u_tl tcg_gen_ld16u_i32
#define tcg_gen_ld16s_tl tcg_gen_ld16s_i32
#define tcg_gen_ld32u_tl tcg_gen_ld_i32
#define tcg_gen_ld32s_tl tcg_gen_ld_i32
#define tcg_gen_ld_tl tcg_gen_ld_i32
#define tcg_gen_st8_tl tcg_gen_st8_i32
#define tcg_gen_st16_tl tcg_gen_st16_i32
#define tcg_gen_st32_tl tcg_gen_st_i32
#define tcg_gen_st_tl tcg_gen_st_i32
#define tcg_gen_add_tl tcg_gen_add_i32
#define tcg_gen_addi_tl tcg_gen_addi_i32
#define tcg_gen_sub_tl tcg_gen_sub_i32
#define tcg_gen_neg_tl tcg_gen_neg_i32
#define tcg_gen_subfi_tl tcg_gen_subfi_i32
#define tcg_gen_subi_tl tcg_gen_subi_i32
#define tcg_gen_and_tl tcg_gen_and_i32
#define tcg_gen_andi_tl tcg_gen_andi_i32
#define tcg_gen_or_tl tcg_gen_or_i32
#define tcg_gen_ori_tl tcg_gen_ori_i32
#define tcg_gen_xor_tl tcg_gen_xor_i32
#define tcg_gen_xori_tl tcg_gen_xori_i32
#define tcg_gen_not_tl tcg_gen_not_i32
#define tcg_gen_shl_tl tcg_gen_shl_i32
#define tcg_gen_shli_tl tcg_gen_shli_i32
#define tcg_gen_shr_tl tcg_gen_shr_i32
#define tcg_gen_shri_tl tcg_gen_shri_i32
#define tcg_gen_sar_tl tcg_gen_sar_i32
#define tcg_gen_sari_tl tcg_gen_sari_i32
#define tcg_gen_brcond_tl tcg_gen_brcond_i32
#define tcg_gen_brcondi_tl tcg_gen_brcondi_i32
#define tcg_gen_mul_tl tcg_gen_mul_i32
#define tcg_gen_muli_tl tcg_gen_muli_i32
#define tcg_gen_discard_tl tcg_gen_discard_i32
#define tcg_gen_trunc_tl_i32 tcg_gen_mov_i32
#define tcg_gen_trunc_i64_tl tcg_gen_trunc_i64_i32
#define tcg_gen_extu_i32_tl tcg_gen_mov_i32
#define tcg_gen_ext_i32_tl tcg_gen_mov_i32
#define tcg_gen_extu_tl_i64 tcg_gen_extu_i32_i64
#define tcg_gen_ext_tl_i64 tcg_gen_ext_i32_i64
#define tcg_gen_ext8u_tl tcg_gen_ext8u_i32
#define tcg_gen_ext8s_tl tcg_gen_ext8s_i32
#define tcg_gen_ext16u_tl tcg_gen_ext16u_i32
#define tcg_gen_ext16s_tl tcg_gen_ext16s_i32
#define tcg_gen_ext32u_tl tcg_gen_mov_i32
#define tcg_gen_ext32s_tl tcg_gen_mov_i32
#define tcg_gen_concat_tl_i64 tcg_gen_concat_i32_i64
#define tcg_gen_andc_tl tcg_gen_andc_i32
#define tcg_gen_eqv_tl tcg_gen_eqv_i32
#define tcg_gen_nand_tl tcg_gen_nand_i32
#define tcg_gen_nor_tl tcg_gen_nor_i32
#define tcg_gen_orc_tl tcg_gen_orc_i32
#define tcg_gen_rotl_tl tcg_gen_rotl_i32
#define tcg_gen_rotli_tl tcg_gen_rotli_i32
#define tcg_gen_rotr_tl tcg_gen_rotr_i32
#define tcg_gen_rotri_tl tcg_gen_rotri_i32
#define tcg_const_tl tcg_const_i32
#define tcg_const_local_tl tcg_const_local_i32
#endif

#if TCG_TARGET_REG_BITS == 32
#define tcg_gen_add_ptr tcg_gen_add_i32
#define tcg_gen_addi_ptr tcg_gen_addi_i32
#define tcg_gen_ext_i32_ptr tcg_gen_mov_i32
#else /* TCG_TARGET_REG_BITS == 32 */
#define tcg_gen_add_ptr tcg_gen_add_i64
#define tcg_gen_addi_ptr tcg_gen_addi_i64
#define tcg_gen_ext_i32_ptr tcg_gen_ext_i32_i64
#endif /* TCG_TARGET_REG_BITS != 32 */
