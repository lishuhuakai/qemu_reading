#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>

#define TEST_CMOV 0

#define xglue(x, y) x ## y
#define glue(x, y) xglue(x, y)
#define stringify(s)	tostring(s)
#define tostring(s)	#s

#define CC_C   	0x0001 /* 进位标志 */
#define CC_P 	0x0004 /* 奇偶标志,它记录相关指令执行之后,其结果的所有bit位中1个个数是否为偶数 */
#define CC_A	0x0010
#define CC_Z	0x0040 /* 零标志位,它记录相关指令执行之后,其结果是否为0 */
#define CC_S    0x0080 /* 符号标志位,它记录相关指令执行之后,其结果是否为负,如果为负,那么sf=1 */
#define CC_O    0x0800 /* 溢出标志位 */
#define DIRECTION_FLAG 0x0400 /* 方向标志 */

#define __init_call	__attribute__ ((unused,__section__ (".initcall.init")))

static void *call_start __init_call = NULL;

#define CC_MASK (CC_C | CC_P | CC_Z | CC_S | CC_O | CC_A)

#define OP add
#include "test-i386.h"

#define OP sub
#include "test-i386.h"

#define OP xor
#include "test-i386.h"

#define OP and
#include "test-i386.h"

#define OP or
#include "test-i386.h"

#define OP cmp
#include "test-i386.h"

#define OP adc
#define OP_CC
#include "test-i386.h"

#define OP sbb
#define OP_CC
#include "test-i386.h"

#define OP inc
#define OP_CC
#define OP1
#include "test-i386.h"

#define OP dec
#define OP_CC
#define OP1
#include "test-i386.h"

#define OP neg
#define OP_CC
#define OP1
#include "test-i386.h"

#define OP not
#define OP_CC
#define OP1
#include "test-i386.h"

#undef CC_MASK
#define CC_MASK (CC_C | CC_P | CC_Z | CC_S | CC_O)

#define OP shl
#include "test-i386-shift.h"

#define OP shr
#include "test-i386-shift.h"

#define OP sar
#include "test-i386-shift.h"

#define OP rol
#include "test-i386-shift.h"

#define OP ror
#include "test-i386-shift.h"

#define OP rcr
#define OP_CC
#include "test-i386-shift.h"

#define OP rcl
#define OP_CC
#include "test-i386-shift.h"

#define OP shld
#define OP_SHIFTD
#define OP_NOBYTE
#include "test-i386-shift.h"

#define OP shrd
#define OP_SHIFTD
#define OP_NOBYTE
#include "test-i386-shift.h"

/* XXX: should be more precise ? */
#undef CC_MASK
#define CC_MASK (CC_C)

#define OP bt
#define OP_NOBYTE
#include "test-i386-shift.h"

#define OP bts
#define OP_NOBYTE
#include "test-i386-shift.h"

#define OP btr
#define OP_NOBYTE
#include "test-i386-shift.h"

#define OP btc
#define OP_NOBYTE
#include "test-i386-shift.h"

/* lea test (modrm support) */
#define TEST_LEA(STR)\
{\
    asm("leal " STR ", %0"\
        : "=r" (res)\
        : "a" (eax), "b" (ebx), "c" (ecx), "d" (edx), "S" (esi), "D" (edi));\
    printf("lea %s = %08x\n", STR, res);\
}

#define TEST_LEA16(STR)\
{\
    asm(".code16 ; .byte 0x67 ; leal " STR ", %0 ; .code32"\
        : "=wq" (res)\
        : "a" (eax), "b" (ebx), "c" (ecx), "d" (edx), "S" (esi), "D" (edi));\
    printf("lea %s = %08x\n", STR, res);\
}


void test_lea(void)
{
    int eax, ebx, ecx, edx, esi, edi, res;
    eax = 0x0001;
    ebx = 0x0002;
    ecx = 0x0004;
    edx = 0x0008;
    esi = 0x0010;
    edi = 0x0020;

    TEST_LEA("0x4000");

    TEST_LEA("(%%eax)");
    TEST_LEA("(%%ebx)");
    TEST_LEA("(%%ecx)");
    TEST_LEA("(%%edx)");
    TEST_LEA("(%%esi)");
    TEST_LEA("(%%edi)");

    TEST_LEA("0x40(%%eax)");
    TEST_LEA("0x40(%%ebx)");
    TEST_LEA("0x40(%%ecx)");
    TEST_LEA("0x40(%%edx)");
    TEST_LEA("0x40(%%esi)");
    TEST_LEA("0x40(%%edi)");

    TEST_LEA("0x4000(%%eax)");
    TEST_LEA("0x4000(%%ebx)");
    TEST_LEA("0x4000(%%ecx)");
    TEST_LEA("0x4000(%%edx)");
    TEST_LEA("0x4000(%%esi)");
    TEST_LEA("0x4000(%%edi)");

    TEST_LEA("(%%eax, %%ecx)");
    TEST_LEA("(%%ebx, %%edx)");
    TEST_LEA("(%%ecx, %%ecx)");
    TEST_LEA("(%%edx, %%ecx)");
    TEST_LEA("(%%esi, %%ecx)");
    TEST_LEA("(%%edi, %%ecx)");

    TEST_LEA("0x40(%%eax, %%ecx)");
    TEST_LEA("0x4000(%%ebx, %%edx)");

    TEST_LEA("(%%ecx, %%ecx, 2)");
    TEST_LEA("(%%edx, %%ecx, 4)");
    TEST_LEA("(%%esi, %%ecx, 8)");

    TEST_LEA("(,%%eax, 2)");
    TEST_LEA("(,%%ebx, 4)");
    TEST_LEA("(,%%ecx, 8)");

    TEST_LEA("0x40(,%%eax, 2)");
    TEST_LEA("0x40(,%%ebx, 4)");
    TEST_LEA("0x40(,%%ecx, 8)");


    TEST_LEA("-10(%%ecx, %%ecx, 2)");
    TEST_LEA("-10(%%edx, %%ecx, 4)");
    TEST_LEA("-10(%%esi, %%ecx, 8)");

    TEST_LEA("0x4000(%%ecx, %%ecx, 2)");
    TEST_LEA("0x4000(%%edx, %%ecx, 4)");
    TEST_LEA("0x4000(%%esi, %%ecx, 8)");

    /* limited 16 bit addressing test */
    TEST_LEA16("0x4000");
    TEST_LEA16("(%%bx)");
    TEST_LEA16("(%%si)");
    TEST_LEA16("(%%di)");
    TEST_LEA16("0x40(%%bx)");
    TEST_LEA16("0x40(%%si)");
    TEST_LEA16("0x40(%%di)");
    TEST_LEA16("0x4000(%%bx)");
    TEST_LEA16("0x4000(%%si)");
    TEST_LEA16("(%%bx,%%si)");
    TEST_LEA16("(%%bx,%%di)");
    TEST_LEA16("0x40(%%bx,%%si)");
    TEST_LEA16("0x40(%%bx,%%di)");
    TEST_LEA16("0x4000(%%bx,%%si)");
    TEST_LEA16("0x4000(%%bx,%%di)");
}

#define TEST_JCC(JCC, v1, v2)\
{\
    int res;\
    asm("movl $1, %0\n\t"\
        "cmpl %2, %1\n\t"\
        "j" JCC " 1f\n\t"\
        "movl $0, %0\n\t"\
        "1:\n\t"\
        : "=r" (res)\
        : "r" (v1), "r" (v2));\
    printf("%-10s %d\n", "j" JCC, res);\
\
    asm("movl $0, %0\n\t"\
        "cmpl %2, %1\n\t"\
        "set" JCC " %b0\n\t"\
        : "=r" (res)\
        : "r" (v1), "r" (v2));\
    printf("%-10s %d\n", "set" JCC, res);\
 if (TEST_CMOV) {\
    asm("movl $0x12345678, %0\n\t"\
        "cmpl %2, %1\n\t"\
        "cmov" JCC "l %3, %0\n\t"\
        : "=r" (res)\
        : "r" (v1), "r" (v2), "m" (1));\
        printf("%-10s R=0x%08x\n", "cmov" JCC "l", res);\
    asm("movl $0x12345678, %0\n\t"\
        "cmpl %2, %1\n\t"\
        "cmov" JCC "w %w3, %w0\n\t"\
        : "=r" (res)\
        : "r" (v1), "r" (v2), "r" (1));\
        printf("%-10s R=0x%08x\n", "cmov" JCC "w", res);\
 } \
}

/* various jump tests */
void test_jcc(void)
{
    TEST_JCC("ne", 1, 1);
    TEST_JCC("ne", 1, 0);

    TEST_JCC("e", 1, 1);
    TEST_JCC("e", 1, 0);

    TEST_JCC("l", 1, 1);
    TEST_JCC("l", 1, 0);
    TEST_JCC("l", 1, -1);

    TEST_JCC("le", 1, 1);
    TEST_JCC("le", 1, 0);
    TEST_JCC("le", 1, -1);

    TEST_JCC("ge", 1, 1);
    TEST_JCC("ge", 1, 0);
    TEST_JCC("ge", -1, 1);

    TEST_JCC("g", 1, 1);
    TEST_JCC("g", 1, 0);
    TEST_JCC("g", 1, -1);

    TEST_JCC("b", 1, 1);
    TEST_JCC("b", 1, 0);
    TEST_JCC("b", 1, -1);

    TEST_JCC("be", 1, 1);
    TEST_JCC("be", 1, 0);
    TEST_JCC("be", 1, -1);

    TEST_JCC("ae", 1, 1);
    TEST_JCC("ae", 1, 0);
    TEST_JCC("ae", 1, -1);

    TEST_JCC("a", 1, 1);
    TEST_JCC("a", 1, 0);
    TEST_JCC("a", 1, -1);


    TEST_JCC("p", 1, 1);
    TEST_JCC("p", 1, 0);

    TEST_JCC("np", 1, 1);
    TEST_JCC("np", 1, 0);

    TEST_JCC("o", 0x7fffffff, 0);
    TEST_JCC("o", 0x7fffffff, -1);

    TEST_JCC("no", 0x7fffffff, 0);
    TEST_JCC("no", 0x7fffffff, -1);

    TEST_JCC("s", 0, 1);
    TEST_JCC("s", 0, -1);
    TEST_JCC("s", 0, 0);

    TEST_JCC("ns", 0, 1);
    TEST_JCC("ns", 0, -1);
    TEST_JCC("ns", 0, 0);
}

#undef CC_MASK
#define CC_MASK (CC_O | CC_C)

#define OP mul
#include "test-i386-muldiv.h"

#define OP imul
#include "test-i386-muldiv.h"

#undef CC_MASK
#define CC_MASK (0)

#define OP div
#include "test-i386-muldiv.h"

#define OP idiv
#include "test-i386-muldiv.h"

void test_imulw2(int op0, int op1) 
{
    int res, s1, s0, flags;
    s0 = op0;
    s1 = op1;
    res = s0;
    flags = 0;
    asm ("push %4\n\t"
         "popf\n\t"
         "imulw %w2, %w0\n\t" 
         "pushf\n\t"
         "popl %1\n\t"
         : "=q" (res), "=g" (flags)
         : "q" (s1), "0" (res), "1" (flags));
    printf("%-10s A=%08x B=%08x R=%08x CC=%04x\n",
           "imulw", s0, s1, res, flags & CC_MASK);
}

void test_imull2(int op0, int op1) 
{
    int res, s1, s0, flags;
    s0 = op0;
    s1 = op1;
    res = s0;
    flags = 0;
    asm ("push %4\n\t"
         "popf\n\t"
         "imull %2, %0\n\t" 
         "pushf\n\t"
         "popl %1\n\t"
         : "=q" (res), "=g" (flags)
         : "q" (s1), "0" (res), "1" (flags));
    printf("%-10s A=%08x B=%08x R=%08x CC=%04x\n",
           "imull", s0, s1, res, flags & CC_MASK);
}

void test_mul(void)
{
    test_imulb(0x1234561d, 4);
    test_imulb(3, -4);
    test_imulb(0x80, 0x80);
    test_imulb(0x10, 0x10);

    test_imulw(0, 0x1234001d, 45);
    test_imulw(0, 23, -45);
    test_imulw(0, 0x8000, 0x8000);
    test_imulw(0, 0x100, 0x100);

    test_imull(0, 0x1234001d, 45);
    test_imull(0, 23, -45);
    test_imull(0, 0x80000000, 0x80000000);
    test_imull(0, 0x10000, 0x10000);

    test_mulb(0x1234561d, 4);
    test_mulb(3, -4);
    test_mulb(0x80, 0x80);
    test_mulb(0x10, 0x10);

    test_mulw(0, 0x1234001d, 45);
    test_mulw(0, 23, -45);
    test_mulw(0, 0x8000, 0x8000);
    test_mulw(0, 0x100, 0x100);

    test_mull(0, 0x1234001d, 45);
    test_mull(0, 23, -45);
    test_mull(0, 0x80000000, 0x80000000);
    test_mull(0, 0x10000, 0x10000);

    test_imulw2(0x1234001d, 45);
    test_imulw2(23, -45);
    test_imulw2(0x8000, 0x8000);
    test_imulw2(0x100, 0x100);

    test_imull2(0x1234001d, 45);
    test_imull2(23, -45);
    test_imull2(0x80000000, 0x80000000);
    test_imull2(0x10000, 0x10000);

    test_idivb(0x12341678, 0x127e);
    test_idivb(0x43210123, -5);
    test_idivb(0x12340004, -1);

    test_idivw(0, 0x12345678, 12347);
    test_idivw(0, -23223, -45);
    test_idivw(0, 0x12348000, -1);
    test_idivw(0x12343, 0x12345678, 0x81238567);

    test_idivl(0, 0x12345678, 12347);
    test_idivl(0, -233223, -45);
    test_idivl(0, 0x80000000, -1);
    test_idivl(0x12343, 0x12345678, 0x81234567);

    test_divb(0x12341678, 0x127e);
    test_divb(0x43210123, -5);
    test_divb(0x12340004, -1);

    test_divw(0, 0x12345678, 12347);
    test_divw(0, -23223, -45);
    test_divw(0, 0x12348000, -1);
    test_divw(0x12343, 0x12345678, 0x81238567);

    test_divl(0, 0x12345678, 12347);
    test_divl(0, -233223, -45);
    test_divl(0, 0x80000000, -1);
    test_divl(0x12343, 0x12345678, 0x81234567);
}

#define TEST_BSX(op, size, op0)\
{\
    int res, val, resz;\
    val = op0;\
    asm("xorl %1, %1 ; " #op " %" size "2, %" size "0 ; setz %b1" \
        : "=r" (res), "=q" (resz)\
        : "g" (val));\
    printf("%-10s A=%08x R=%08x %d\n", #op, val, resz ? 0 : res, resz);\
}

void test_bsx(void)
{
    TEST_BSX(bsrw, "w", 0);
    TEST_BSX(bsrw, "w", 0x12340128);
    TEST_BSX(bsrl, "", 0);
    TEST_BSX(bsrl, "", 0x00340128);
    TEST_BSX(bsfw, "w", 0);
    TEST_BSX(bsfw, "w", 0x12340128);
    TEST_BSX(bsfl, "", 0);
    TEST_BSX(bsfl, "", 0x00340128);
}

/**********************************************/

void test_fops(double a, double b)
{
    printf("a=%f b=%f a+b=%f\n", a, b, a + b);
    printf("a=%f b=%f a-b=%f\n", a, b, a - b);
    printf("a=%f b=%f a*b=%f\n", a, b, a * b);
    printf("a=%f b=%f a/b=%f\n", a, b, a / b);
    printf("a=%f b=%f fmod(a, b)=%f\n", a, b, fmod(a, b));
    printf("a=%f sqrt(a)=%f\n", a, sqrt(a));
    printf("a=%f sin(a)=%f\n", a, sin(a));
    printf("a=%f cos(a)=%f\n", a, cos(a));
    printf("a=%f tan(a)=%f\n", a, tan(a));
    printf("a=%f log(a)=%f\n", a, log(a));
    printf("a=%f exp(a)=%f\n", a, exp(a));
    printf("a=%f b=%f atan2(a, b)=%f\n", a, b, atan2(a, b));
    /* just to test some op combining */
    printf("a=%f asin(sin(a))=%f\n", a, asin(sin(a)));
    printf("a=%f acos(cos(a))=%f\n", a, acos(cos(a)));
    printf("a=%f atan(tan(a))=%f\n", a, atan(tan(a)));

}

void test_fcmp(double a, double b)
{
    printf("(%f<%f)=%d\n",
           a, b, a < b);
    printf("(%f<=%f)=%d\n",
           a, b, a <= b);
    printf("(%f==%f)=%d\n",
           a, b, a == b);
    printf("(%f>%f)=%d\n",
           a, b, a > b);
    printf("(%f<=%f)=%d\n",
           a, b, a >= b);
}

void test_fcvt(double a)
{
    float fa;
    long double la;

    fa = a;
    la = a;
    printf("(float)%f = %f\n", a, fa);
    printf("(long double)%f = %Lf\n", a, la);
    printf("a=%016Lx\n", *(long long *)&a);
    printf("la=%016Lx %04x\n", *(long long *)&la, 
           *(unsigned short *)((char *)(&la) + 8));
    printf("a=%f floor(a)=%f\n", a, floor(a));
    printf("a=%f ceil(a)=%f\n", a, ceil(a));
    printf("a=%f rint(a)=%f\n", a, rint(a));
}

#define TEST(N) \
    asm("fld" #N : "=t" (a)); \
    printf("fld" #N "= %f\n", a);

void test_fconst(void)
{
    double a;
    TEST(1);
    TEST(l2t);
    TEST(l2e);
    TEST(pi);
    TEST(lg2);
    TEST(ln2);
    TEST(z);
}

void test_fbcd(double a)
{
    unsigned short bcd[5];
    double b;

    asm("fbstp %0" : "=m" (bcd[0]) : "t" (a) : "st");
    asm("fbld %1" : "=t" (b) : "m" (bcd[0]));
    printf("a=%f bcd=%04x%04x%04x%04x%04x b=%f\n", 
           a, bcd[4], bcd[3], bcd[2], bcd[1], bcd[0], b);
}

void test_floats(void)
{
    test_fops(2, 3);
    test_fops(1.4, -5);
    test_fcmp(2, -1);
    test_fcmp(2, 2);
    test_fcmp(2, 3);
    test_fcvt(1.0/7.0);
    test_fcvt(-1.0/9.0);
    test_fcvt(1e30);
    test_fconst();
    test_fbcd(1234567890123456);
    test_fbcd(-123451234567890);
}

/**********************************************/

#define TEST_BCD(op, op0, cc_in, cc_mask)\
{\
    int res, flags;\
    res = op0;\
    flags = cc_in;\
    asm ("push %3\n\t"\
         "popf\n\t"\
         #op "\n\t"\
         "pushf\n\t"\
         "popl %1\n\t"\
        : "=a" (res), "=g" (flags)\
        : "0" (res), "1" (flags));\
    printf("%-10s A=%08x R=%08x CCIN=%04x CC=%04x\n",\
           #op, op0, res, cc_in, flags & cc_mask);\
}

void test_bcd(void)
{
    TEST_BCD(daa, 0x12340503, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(daa, 0x12340506, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(daa, 0x12340507, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(daa, 0x12340559, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(daa, 0x12340560, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(daa, 0x1234059f, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(daa, 0x123405a0, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(daa, 0x12340503, 0, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(daa, 0x12340506, 0, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(daa, 0x12340503, CC_C, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(daa, 0x12340506, CC_C, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(daa, 0x12340503, CC_C | CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(daa, 0x12340506, CC_C | CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));

    TEST_BCD(das, 0x12340503, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(das, 0x12340506, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(das, 0x12340507, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(das, 0x12340559, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(das, 0x12340560, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(das, 0x1234059f, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(das, 0x123405a0, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(das, 0x12340503, 0, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(das, 0x12340506, 0, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(das, 0x12340503, CC_C, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(das, 0x12340506, CC_C, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(das, 0x12340503, CC_C | CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));
    TEST_BCD(das, 0x12340506, CC_C | CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_A));

    TEST_BCD(aaa, 0x12340205, CC_A, (CC_C | CC_A));
    TEST_BCD(aaa, 0x12340306, CC_A, (CC_C | CC_A));
    TEST_BCD(aaa, 0x1234040a, CC_A, (CC_C | CC_A));
    TEST_BCD(aaa, 0x123405fa, CC_A, (CC_C | CC_A));
    TEST_BCD(aaa, 0x12340205, 0, (CC_C | CC_A));
    TEST_BCD(aaa, 0x12340306, 0, (CC_C | CC_A));
    TEST_BCD(aaa, 0x1234040a, 0, (CC_C | CC_A));
    TEST_BCD(aaa, 0x123405fa, 0, (CC_C | CC_A));
    
    TEST_BCD(aas, 0x12340205, CC_A, (CC_C | CC_A));
    TEST_BCD(aas, 0x12340306, CC_A, (CC_C | CC_A));
    TEST_BCD(aas, 0x1234040a, CC_A, (CC_C | CC_A));
    TEST_BCD(aas, 0x123405fa, CC_A, (CC_C | CC_A));
    TEST_BCD(aas, 0x12340205, 0, (CC_C | CC_A));
    TEST_BCD(aas, 0x12340306, 0, (CC_C | CC_A));
    TEST_BCD(aas, 0x1234040a, 0, (CC_C | CC_A));
    TEST_BCD(aas, 0x123405fa, 0, (CC_C | CC_A));

    TEST_BCD(aam, 0x12340547, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_O | CC_A));
    TEST_BCD(aad, 0x12340407, CC_A, (CC_C | CC_P | CC_Z | CC_S | CC_O | CC_A));
}

#define TEST_XCHG(op, size, opconst)\
{\
    int op0, op1;\
    op0 = 0x12345678;\
    op1 = 0xfbca7654;\
    asm(#op " %" size "0, %" size "1" \
        : "=q" (op0), opconst (op1) \
        : "0" (op0), "1" (op1));\
    printf("%-10s A=%08x B=%08x\n",\
           #op, op0, op1);\
}

#define TEST_CMPXCHG(op, size, opconst, eax)\
{\
    int op0, op1;\
    op0 = 0x12345678;\
    op1 = 0xfbca7654;\
    asm(#op " %" size "0, %" size "1" \
        : "=q" (op0), opconst (op1) \
        : "0" (op0), "1" (op1), "a" (eax));\
    printf("%-10s EAX=%08x A=%08x C=%08x\n",\
           #op, eax, op0, op1);\
}

void test_xchg(void)
{
    TEST_XCHG(xchgl, "", "=q");
    TEST_XCHG(xchgw, "w", "=q");
    TEST_XCHG(xchgb, "b", "=q");

    TEST_XCHG(xchgl, "", "=m");
    TEST_XCHG(xchgw, "w", "=m");
    TEST_XCHG(xchgb, "b", "=m");

    TEST_XCHG(xaddl, "", "=q");
    TEST_XCHG(xaddw, "w", "=q");
    TEST_XCHG(xaddb, "b", "=q");

    TEST_XCHG(xaddl, "", "=m");
    TEST_XCHG(xaddw, "w", "=m");
    TEST_XCHG(xaddb, "b", "=m");

    TEST_CMPXCHG(cmpxchgl, "", "=q", 0xfbca7654);
    TEST_CMPXCHG(cmpxchgw, "w", "=q", 0xfbca7654);
    TEST_CMPXCHG(cmpxchgb, "b", "=q", 0xfbca7654);

    TEST_CMPXCHG(cmpxchgl, "", "=q", 0xfffefdfc);
    TEST_CMPXCHG(cmpxchgw, "w", "=q", 0xfffefdfc);
    TEST_CMPXCHG(cmpxchgb, "b", "=q", 0xfffefdfc);

    TEST_CMPXCHG(cmpxchgl, "", "=m", 0xfbca7654);
    TEST_CMPXCHG(cmpxchgw, "w", "=m", 0xfbca7654);
    TEST_CMPXCHG(cmpxchgb, "b", "=m", 0xfbca7654);

    TEST_CMPXCHG(cmpxchgl, "", "=m", 0xfffefdfc);
    TEST_CMPXCHG(cmpxchgw, "w", "=m", 0xfffefdfc);
    TEST_CMPXCHG(cmpxchgb, "b", "=m", 0xfffefdfc);
}

/**********************************************/
/* segmentation tests */

#include <asm/ldt.h>
#include <linux/unistd.h>

_syscall3(int, modify_ldt, int, func, void *, ptr, unsigned long, bytecount)

uint8_t seg_data1[4096];
uint8_t seg_data2[4096];

#define MK_SEL(n) (((n) << 3) | 7)

/* NOTE: we use Linux modify_ldt syscall */
void test_segs(void)
{
    struct modify_ldt_ldt_s ldt;
    long long ldt_table[3];
    int res, res2;
    char tmp;
    struct {
        uint32_t offset;
        uint16_t seg;
    } __attribute__((packed)) segoff;

    ldt.entry_number = 1;
    ldt.base_addr = (unsigned long)&seg_data1;
    ldt.limit = (sizeof(seg_data1) + 0xfff) >> 12;
    ldt.seg_32bit = 1;
    ldt.contents = MODIFY_LDT_CONTENTS_DATA;
    ldt.read_exec_only = 0;
    ldt.limit_in_pages = 1;
    ldt.seg_not_present = 0;
    ldt.useable = 1;
    modify_ldt(1, &ldt, sizeof(ldt)); /* write ldt entry */

    ldt.entry_number = 2;
    ldt.base_addr = (unsigned long)&seg_data2;
    ldt.limit = (sizeof(seg_data2) + 0xfff) >> 12;
    ldt.seg_32bit = 1;
    ldt.contents = MODIFY_LDT_CONTENTS_DATA;
    ldt.read_exec_only = 0;
    ldt.limit_in_pages = 1;
    ldt.seg_not_present = 0;
    ldt.useable = 1;
    modify_ldt(1, &ldt, sizeof(ldt)); /* write ldt entry */

    modify_ldt(0, &ldt_table, sizeof(ldt_table)); /* read ldt entries */
#if 0
    {
        int i;
        for(i=0;i<3;i++)
            printf("%d: %016Lx\n", i, ldt_table[i]);
    }
#endif
    /* do some tests with fs or gs */
    asm volatile ("movl %0, %%fs" : : "r" (MK_SEL(1)));
    asm volatile ("movl %0, %%gs" : : "r" (MK_SEL(2)));

    seg_data1[1] = 0xaa;
    seg_data2[1] = 0x55;

    asm volatile ("fs movzbl 0x1, %0" : "=r" (res));
    printf("FS[1] = %02x\n", res);

    asm volatile ("gs movzbl 0x1, %0" : "=r" (res));
    printf("GS[1] = %02x\n", res);

    /* tests with ds/ss (implicit segment case) */
    tmp = 0xa5;
    asm volatile ("pushl %%ebp\n\t"
                  "pushl %%ds\n\t"
                  "movl %2, %%ds\n\t"
                  "movl %3, %%ebp\n\t"
                  "movzbl 0x1, %0\n\t"
                  "movzbl (%%ebp), %1\n\t"
                  "popl %%ds\n\t"
                  "popl %%ebp\n\t"
                  : "=r" (res), "=r" (res2)
                  : "r" (MK_SEL(1)), "r" (&tmp));
    printf("DS[1] = %02x\n", res);
    printf("SS[tmp] = %02x\n", res2);

    segoff.seg = MK_SEL(2);
    segoff.offset = 0xabcdef12;
    asm volatile("lfs %2, %0\n\t" 
                 "movl %%fs, %1\n\t"
                 : "=r" (res), "=g" (res2) 
                 : "m" (segoff));
    printf("FS:reg = %04x:%08x\n", res2, res);
}

/* 16 bit code test */
extern char code16_start, code16_end;
extern char code16_func1;
extern char code16_func2;
extern char code16_func3;

void test_code16(void)
{
    struct modify_ldt_ldt_s ldt;
    int res, res2;

    /* build a code segment */
    ldt.entry_number = 1;
    ldt.base_addr = (unsigned long)&code16_start;
    ldt.limit = &code16_end - &code16_start;
    ldt.seg_32bit = 0;
    ldt.contents = MODIFY_LDT_CONTENTS_CODE;
    ldt.read_exec_only = 0;
    ldt.limit_in_pages = 0;
    ldt.seg_not_present = 0;
    ldt.useable = 1;
    modify_ldt(1, &ldt, sizeof(ldt)); /* write ldt entry */

    /* call the first function */
    asm volatile ("lcall %1, %2" 
                  : "=a" (res)
                  : "i" (MK_SEL(1)), "i" (&code16_func1): "memory", "cc");
    printf("func1() = 0x%08x\n", res);
    asm volatile ("lcall %2, %3" 
                  : "=a" (res), "=c" (res2)
                  : "i" (MK_SEL(1)), "i" (&code16_func2): "memory", "cc");
    printf("func2() = 0x%08x spdec=%d\n", res, res2);
    asm volatile ("lcall %1, %2" 
                  : "=a" (res)
                  : "i" (MK_SEL(1)), "i" (&code16_func3): "memory", "cc");
    printf("func3() = 0x%08x\n", res);
}

void test_misc(void)
{
    char table[256];
    int res, i;

    for(i=0;i<256;i++) table[i] = 256 - i;
    res = 0x12345678;
    asm ("xlat" : "=a" (res) : "b" (table), "0" (res));
    printf("xlat: EAX=%08x\n", res);
}

uint8_t str_buffer[4096];

#define TEST_STRING1(OP, size, DF, REP)\
{\
    int esi, edi, eax, ecx, eflags;\
\
    esi = (long)(str_buffer + sizeof(str_buffer) / 2);\
    edi = (long)(str_buffer + sizeof(str_buffer) / 2) + 16;\
    eax = 0x12345678;\
    ecx = 17;\
\
    asm volatile ("pushl $0\n\t"\
                  "popf\n\t"\
                  DF "\n\t"\
                  REP #OP size "\n\t"\
                  "cld\n\t"\
                  "pushf\n\t"\
                  "popl %4\n\t"\
                  : "=S" (esi), "=D" (edi), "=a" (eax), "=c" (ecx), "=g" (eflags)\
                  : "0" (esi), "1" (edi), "2" (eax), "3" (ecx));\
    printf("%-10s ESI=%08x EDI=%08x EAX=%08x ECX=%08x EFL=%04x\n",\
           REP #OP size, esi, edi, eax, ecx,\
           eflags & (CC_C | CC_P | CC_Z | CC_S | CC_O | CC_A));\
}

#define TEST_STRING(OP, REP)\
    TEST_STRING1(OP, "b", "", REP);\
    TEST_STRING1(OP, "w", "", REP);\
    TEST_STRING1(OP, "l", "", REP);\
    TEST_STRING1(OP, "b", "std", REP);\
    TEST_STRING1(OP, "w", "std", REP);\
    TEST_STRING1(OP, "l", "std", REP)

void test_string(void)
{
    int i;
    for(i = 0;i < sizeof(str_buffer); i++)
        str_buffer[i] = i + 0x56;
   TEST_STRING(stos, "");
   TEST_STRING(stos, "rep ");
   TEST_STRING(lods, ""); /* to verify stos */
   TEST_STRING(lods, "rep "); 
   TEST_STRING(movs, "");
   TEST_STRING(movs, "rep ");
   TEST_STRING(lods, ""); /* to verify stos */

   /* XXX: better tests */
   TEST_STRING(scas, "");
   TEST_STRING(scas, "repz ");
   TEST_STRING(scas, "repnz ");
   TEST_STRING(cmps, "");
   TEST_STRING(cmps, "repz ");
   TEST_STRING(cmps, "repnz ");
}

static void *call_end __init_call = NULL;

int main(int argc, char **argv)
{
    void **ptr;
    void (*func)(void);

    ptr = &call_start + 1;
    while (*ptr != NULL) {
        func = *ptr++;
        func();
    }
    test_bsx();
    test_mul();
    test_jcc();
    test_floats();
    test_bcd();
    test_xchg();
    test_string();
    test_misc();
    test_lea();
    test_segs();
    test_code16();
    return 0;
}
