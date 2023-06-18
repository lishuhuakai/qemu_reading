/*
 *  Software MMU support
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
#define DATA_SIZE (1 << SHIFT)

#if DATA_SIZE == 8
#define SUFFIX q
#define DATA_TYPE uint64_t
#elif DATA_SIZE == 4
#define SUFFIX l
#define DATA_TYPE uint32_t
#elif DATA_SIZE == 2
#define SUFFIX w
#define DATA_TYPE uint16_t
#elif DATA_SIZE == 1
#define SUFFIX b
#define DATA_TYPE uint8_t
#else
#error unsupported data size
#endif

static DATA_TYPE glue(slow_ld, SUFFIX)(unsigned long addr, void *retaddr);
static void glue(slow_st, SUFFIX)(unsigned long addr, DATA_TYPE val,
                                  void *retaddr);

static inline DATA_TYPE glue(io_read, SUFFIX)(unsigned long physaddr, 
                                              unsigned long tlb_addr)
{
    DATA_TYPE res;
    int index;

    index = (tlb_addr >> IO_MEM_SHIFT) & (IO_MEM_NB_ENTRIES - 1);
#if SHIFT <= 2
    res = io_mem_read[index][SHIFT](physaddr);
#else
#ifdef TARGET_WORDS_BIGENDIAN
    res = (uint64_t)io_mem_read[index][2](physaddr) << 32;
    res |= io_mem_read[index][2](physaddr + 4);
#else
    res = io_mem_read[index][2](physaddr);
    res |= (uint64_t)io_mem_read[index][2](physaddr + 4) << 32;
#endif
#endif /* SHIFT > 2 */
    return res;
}

static inline void glue(io_write, SUFFIX)(unsigned long physaddr, 
                                          DATA_TYPE val,
                                          unsigned long tlb_addr)
{
    int index;

    index = (tlb_addr >> IO_MEM_SHIFT) & (IO_MEM_NB_ENTRIES - 1);
#if SHIFT <= 2
    io_mem_write[index][SHIFT](physaddr, val);
#else
#ifdef TARGET_WORDS_BIGENDIAN
    io_mem_write[index][2](physaddr, val >> 32);
    io_mem_write[index][2](physaddr + 4, val);
#else
    io_mem_write[index][2](physaddr, val);
    io_mem_write[index][2](physaddr + 4, val >> 32);
#endif
#endif /* SHIFT > 2 */
}

/* handle all cases except unaligned access which span two pages */
DATA_TYPE REGPARM(1) glue(glue(__ld, SUFFIX), _mmu)(unsigned long addr)
{
    DATA_TYPE res;
    int is_user, index;
    unsigned long physaddr, tlb_addr;
    void *retaddr;
    
    /* test if there is match for unaligned or IO access */
    /* XXX: could done more in memory macro in a non portable way */
    is_user = ((env->hflags & HF_CPL_MASK) == 3);
    /* 计算addr对应的tlb的索引 */
    index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
 redo:
    tlb_addr = env->tlb_read[is_user][index].address;
    /* tlb有效,并且addr的高32bit和tlb_addr的高32bit匹配 */
    if ((addr & TARGET_PAGE_MASK) == (tlb_addr & (TARGET_PAGE_MASK | TLB_INVALID_MASK))) {
        /* 计算获得物理地址 */
        physaddr = addr + env->tlb_read[is_user][index].addend;
        if (tlb_addr & ~TARGET_PAGE_MASK) {
            /* IO access */
            if ((addr & (DATA_SIZE - 1)) != 0)
                goto do_unaligned_access;
            res = glue(io_read, SUFFIX)(physaddr, tlb_addr);
        } else if (((addr & 0xfff) + DATA_SIZE - 1) >= TARGET_PAGE_SIZE) {
            /* slow unaligned access (it spans two pages or IO) */
        do_unaligned_access:
            retaddr = __builtin_return_address(0);
            res = glue(slow_ld, SUFFIX)(addr, retaddr);
        } else {
            /* unaligned access in the same page */
            res = glue(glue(ldu, SUFFIX), _raw)((uint8_t *)physaddr);
        }
    } else {
        /* the page is not in the TLB : fill it */
        retaddr = __builtin_return_address(0);
        tlb_fill(addr, 0, retaddr);
        goto redo;
    }
    return res;
}

/* handle all unaligned cases
 * 处理所有的不对齐的情况
 * @param addr 线性地址
 */
static DATA_TYPE glue(slow_ld, SUFFIX)(unsigned long addr, void *retaddr)
{
    DATA_TYPE res, res1, res2;
    int is_user, index, shift;
    unsigned long physaddr, tlb_addr, addr1, addr2;

    is_user = ((env->hflags & HF_CPL_MASK) == 3);
    index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
 redo:
    tlb_addr = env->tlb_read[is_user][index].address; /* 获得tlb中记录的线性地址 */
    if ((addr & TARGET_PAGE_MASK) == (tlb_addr & (TARGET_PAGE_MASK | TLB_INVALID_MASK))) {
        physaddr = addr + env->tlb_read[is_user][index].addend;
        if (tlb_addr & ~TARGET_PAGE_MASK) {
            /* IO access */
            if ((addr & (DATA_SIZE - 1)) != 0)
                goto do_unaligned_access;
            res = glue(io_read, SUFFIX)(physaddr, tlb_addr);
        } else if (((addr & 0xfff) + DATA_SIZE - 1) >= TARGET_PAGE_SIZE) {
        /* 访问addr横跨了两个page,那就读两次,然后将结果合并起来 */
        do_unaligned_access:
            /* slow unaligned access (it spans two pages) */
            addr1 = addr & ~(DATA_SIZE - 1);
            addr2 = addr1 + DATA_SIZE;
            res1 = glue(slow_ld, SUFFIX)(addr1, retaddr);
            res2 = glue(slow_ld, SUFFIX)(addr2, retaddr);
            shift = (addr & (DATA_SIZE - 1)) * 8;
#ifdef TARGET_WORDS_BIGENDIAN
            res = (res1 << shift) | (res2 >> ((DATA_SIZE * 8) - shift));
#else
            res = (res1 >> shift) | (res2 << ((DATA_SIZE * 8) - shift));
#endif
        } else {
            /* unaligned/aligned access in the same page */
            res = glue(glue(ldu, SUFFIX), _raw)((uint8_t *)physaddr);
        }
    } else {
        /* the page is not in the TLB : fill it */
        /* 使用tlb可以加快线性地址->物理地址的转换速度,仅此而已 */
        tlb_fill(addr, 0, retaddr);
        goto redo;
    }
    return res;
}


void REGPARM(2) glue(glue(__st, SUFFIX), _mmu)(unsigned long addr, DATA_TYPE val)
{
    unsigned long physaddr, tlb_addr;
    void *retaddr;
    int is_user, index;
    
    is_user = ((env->hflags & HF_CPL_MASK) == 3);
    index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
 redo:
    tlb_addr = env->tlb_write[is_user][index].address;
    if ((addr & TARGET_PAGE_MASK) == (tlb_addr & (TARGET_PAGE_MASK | TLB_INVALID_MASK))) {
        /* 为什么这里physaddr的计算这么奇怪,可以参考cpu_x86_handle_mmu_fault函数
         * env->tlb_read[is_user][index].addend实际等于physaddr - addr
         */
        physaddr = addr + env->tlb_read[is_user][index].addend;
        if (tlb_addr & ~TARGET_PAGE_MASK) {
            /* IO access */
            if ((addr & (DATA_SIZE - 1)) != 0)
                goto do_unaligned_access;
            glue(io_write, SUFFIX)(physaddr, val, tlb_addr);
        } else if (((addr & 0xfff) + DATA_SIZE - 1) >= TARGET_PAGE_SIZE) {
        do_unaligned_access:
            retaddr = __builtin_return_address(0);
            glue(slow_st, SUFFIX)(addr, val, retaddr);
        } else {
            /* aligned/unaligned access in the same page */
            glue(glue(st, SUFFIX), _raw)((uint8_t *)physaddr, val);
        }
    } else {
        /* the page is not in the TLB : fill it */
        retaddr = __builtin_return_address(0);
        tlb_fill(addr, 1, retaddr);
        goto redo;
    }
}

/* handles all unaligned cases */
static void glue(slow_st, SUFFIX)(unsigned long addr, DATA_TYPE val,
                                  void *retaddr)
{
    unsigned long physaddr, tlb_addr;
    int is_user, index, i;

    is_user = ((env->hflags & HF_CPL_MASK) == 3);
    index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
 redo:
    tlb_addr = env->tlb_write[is_user][index].address;
    if ((addr & TARGET_PAGE_MASK) == (tlb_addr & (TARGET_PAGE_MASK | TLB_INVALID_MASK))) {
        physaddr = addr + env->tlb_read[is_user][index].addend;
        if (tlb_addr & ~TARGET_PAGE_MASK) {
            /* IO access */
            if ((addr & (DATA_SIZE - 1)) != 0)
                goto do_unaligned_access;
            glue(io_write, SUFFIX)(physaddr, val, tlb_addr);
        } else if (((addr & 0xfff) + DATA_SIZE - 1) >= TARGET_PAGE_SIZE) {
        do_unaligned_access:
            /* XXX: not efficient, but simple */
            for(i = 0;i < DATA_SIZE; i++) {
#ifdef TARGET_WORDS_BIGENDIAN
                slow_stb(addr + i, val >> (((DATA_SIZE - 1) * 8) - (i * 8)), retaddr);
#else
                slow_stb(addr + i, val >> (i * 8), retaddr);
#endif
            }
        } else {
            /* aligned/unaligned access in the same page */
            glue(glue(st, SUFFIX), _raw)((uint8_t *)physaddr, val);
        }
    } else {
        /* the page is not in the TLB : fill it */
        tlb_fill(addr, 1, retaddr);
        goto redo;
    }
}

#undef SHIFT
#undef DATA_TYPE
#undef SUFFIX
#undef DATA_SIZE
