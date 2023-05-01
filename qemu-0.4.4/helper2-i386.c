/*
 *  i386 helpers (without register variable usage)
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
#include <sys/mman.h>

#include "cpu-i386.h"
#include "exec.h"

//#define DEBUG_MMU
/* 初始化模拟的cpu */
CPUX86State *cpu_x86_init(void)
{
    CPUX86State *env;
    int i;
    static int inited;

    cpu_exec_init();

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

    tlb_flush(env);
#ifdef CONFIG_SOFTMMU
    env->hflags |= HF_SOFTMMU_MASK;
#endif
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

/***********************************************************/
/* x86 debug */

static const char *cc_op_str[] = {
    "DYNAMIC",
    "EFLAGS",
    "MUL",
    "ADDB",
    "ADDW",
    "ADDL",
    "ADCB",
    "ADCW",
    "ADCL",
    "SUBB",
    "SUBW",
    "SUBL",
    "SBBB",
    "SBBW",
    "SBBL",
    "LOGICB",
    "LOGICW",
    "LOGICL",
    "INCB",
    "INCW",
    "INCL",
    "DECB",
    "DECW",
    "DECL",
    "SHLB",
    "SHLW",
    "SHLL",
    "SARB",
    "SARW",
    "SARL",
};

void cpu_x86_dump_state(CPUX86State *env, FILE *f, int flags)
{
    int eflags;
    char cc_op_name[32];

    eflags = env->eflags;
    fprintf(f, "EAX=%08x EBX=%08x ECX=%08x EDX=%08x\n"
            "ESI=%08x EDI=%08x EBP=%08x ESP=%08x\n"
            "EIP=%08x EFL=%08x [%c%c%c%c%c%c%c]\n",
            env->regs[R_EAX], env->regs[R_EBX], env->regs[R_ECX], env->regs[R_EDX], 
            env->regs[R_ESI], env->regs[R_EDI], env->regs[R_EBP], env->regs[R_ESP], 
            env->eip, eflags,
            eflags & DF_MASK ? 'D' : '-',
            eflags & CC_O ? 'O' : '-',
            eflags & CC_S ? 'S' : '-',
            eflags & CC_Z ? 'Z' : '-',
            eflags & CC_A ? 'A' : '-',
            eflags & CC_P ? 'P' : '-',
            eflags & CC_C ? 'C' : '-');
    fprintf(f, "CS=%04x SS=%04x DS=%04x ES=%04x FS=%04x GS=%04x\n",
            env->segs[R_CS].selector,
            env->segs[R_SS].selector,
            env->segs[R_DS].selector,
            env->segs[R_ES].selector,
            env->segs[R_FS].selector,
            env->segs[R_GS].selector);
    if (flags & X86_DUMP_CCOP) {
        if ((unsigned)env->cc_op < CC_OP_NB)
            strcpy(cc_op_name, cc_op_str[env->cc_op]);
        else
            snprintf(cc_op_name, sizeof(cc_op_name), "[%d]", env->cc_op);
        fprintf(f, "CCS=%08x CCD=%08x CCO=%-8s\n",
                env->cc_src, env->cc_dst, cc_op_name);
    }
    if (flags & X86_DUMP_FPU) {
        fprintf(f, "ST0=%f ST1=%f ST2=%f ST3=%f\n", 
                (double)env->fpregs[0], 
                (double)env->fpregs[1], 
                (double)env->fpregs[2], 
                (double)env->fpregs[3]);
        fprintf(f, "ST4=%f ST5=%f ST6=%f ST7=%f\n", 
                (double)env->fpregs[4], 
                (double)env->fpregs[5], 
                (double)env->fpregs[7], 
                (double)env->fpregs[8]);
    }
}

/***********************************************************/
/* x86 mmu */
/* XXX: add PGE support */

/* called when cr3 or PG bit are modified */
static int last_pg_state = -1;
static int last_pe_state = 0;
int phys_ram_size;
int phys_ram_fd;
uint8_t *phys_ram_base; /* 虚拟的x86的物理内存的基址 */
/* 更新cr0寄存器 */
void cpu_x86_update_cr0(CPUX86State *env)
{
    int pg_state, pe_state;

#ifdef DEBUG_MMU
    printf("CR0 update: CR0=0x%08x\n", env->cr[0]);
#endif
    pg_state = env->cr[0] & CR0_PG_MASK; /* Paging Enable,用于表示芯片上的分页部件是否允许工作 */
    if (pg_state != last_pg_state) {
        page_unmap();
        tlb_flush(env);
        last_pg_state = pg_state;
    }
    pe_state = env->cr[0] & CR0_PE_MASK; /* Protedted Enable,用于启动保护模式,如果PE位置1,则表示保护模式,否则就是实模式 */
    if (last_pe_state != pe_state) {
        tb_flush();
        last_pe_state = pe_state;
    }
}

void cpu_x86_update_cr3(CPUX86State *env)
{
    if (env->cr[0] & CR0_PG_MASK) { /* 开启分页 */
#if defined(DEBUG_MMU) /* 打印页目录项基址 */
        printf("CR3 update: CR3=%08x\n", env->cr[3]);
#endif
        page_unmap();
        tlb_flush(env);
    }
}

void cpu_x86_init_mmu(CPUX86State *env)
{
    last_pg_state = -1;
    cpu_x86_update_cr0(env);
}

/* XXX: also flush 4MB pages 
 * 关于tlb, 它的实质是一个缓存,实现线性地址->物理地址的转换.
 * @param addr 线性地址
 */
void cpu_x86_flush_tlb(CPUX86State *env, uint32_t addr)
{
    int flags;
    unsigned long virt_addr;

    tlb_flush_page(env, addr);

    flags = page_get_flags(addr);
    if (flags & PAGE_VALID) { /* 页面有效 */
        /* 这里的virt_addr,其实是addr所在page的首地址 */
        virt_addr = addr & ~0xfff; 
        munmap((void *)virt_addr, 4096);
        page_set_flags(virt_addr, virt_addr + 4096, 0);
    }
}

/* return value:
   -1 = cannot handle fault 
   0  = nothing more to do 
   1  = generate PF fault
   2  = soft MMU activation required for this block
*/
/* 处理mmu映射缺失的异常
 * @param addr 线性地址
 */
int cpu_x86_handle_mmu_fault(CPUX86State *env, uint32_t addr, int is_write)
{
    uint8_t *pde_ptr, *pte_ptr;
    uint32_t pde, pte, virt_addr;
    int cpl, error_code, is_dirty, is_user, prot, page_size, ret;
    unsigned long pd;
    
    cpl = env->hflags & HF_CPL_MASK;
    is_user = (cpl == 3);
#if defined(YDEBUG_MMU)
    printf("================\n");
#endif
#if defined(DEBUG_MMU)
    printf("MMU fault: addr=0x%08x w=%d u=%d eip=%08x\n", 
           addr, is_write, is_user, env->eip);
#endif

    if (env->user_mode_only) {
        /* user mode only emulation */
        error_code = 0;
        goto do_fault;
    }
#if defined(YDEBUG_MMU)
    printf("[D] softmmu=%d, paging=%d, is_user=%d\n", !!(env->hflags & HF_SOFTMMU_MASK), 
           !!(env->cr[0] & CR0_PG_MASK), is_user);
#endif
    if (!(env->cr[0] & CR0_PG_MASK)) { /* 没有开启分页,那么物理地址其实就是线性地址 */
        pte = addr;
        virt_addr = addr & ~0xfff; /* 取高8位 */
        prot = PROT_READ | PROT_WRITE;
        page_size = 4096;
        goto do_mapping;
    }

    /* page directory entry 
     * 页目录项
     * cr[3] & ~0xfff 也就是取cr[3]的高8位,为页目录的基地址(物理地址)
     * ((addr >> 20) & ~3) 为页目录地址偏移,后面的 & ~3为保证4字节对齐
     * 两者相加,可以获得addr对应的页目录项的物理地址
     */
    pde_ptr = phys_ram_base + ((env->cr[3] & ~0xfff) + ((addr >> 20) & ~3));
    pde = ldl(pde_ptr); /* 取出页目录表项 */
#if defined(YDEBUG_MMU)
    printf("[D] pde_ptr=0x%08x, *pde=0x%08x\n", pde_ptr, pde);
#endif
    if (!(pde & PG_PRESENT_MASK)) {
        error_code = 0;
        goto do_fault;
    }
    if (is_user) {
        if (!(pde & PG_USER_MASK))
            goto do_fault_protect;
        if (is_write && !(pde & PG_RW_MASK))
            goto do_fault_protect;
    } else {
        if ((env->cr[0] & CR0_WP_MASK) && (pde & PG_USER_MASK) &&
            is_write && !(pde & PG_RW_MASK)) 
            goto do_fault_protect;
    }
    /* if PSE bit is set, then we use a 4MB page */
    if ((pde & PG_PSE_MASK) && (env->cr[4] & CR4_PSE_MASK)) {
        is_dirty = is_write && !(pde & PG_DIRTY_MASK);
        if (!(pde & PG_ACCESSED_MASK)) {
            pde |= PG_ACCESSED_MASK;
            if (is_dirty)
                pde |= PG_DIRTY_MASK;
            stl(pde_ptr, pde);
        }
        
        pte = pde & ~0x003ff000; /* align to 4MB */
        page_size = 4096 * 1024; /* 一页的大小为4MB */
        virt_addr = addr & ~0x003fffff;
    } else { /* 暂时先忽略PSE */
        if (!(pde & PG_ACCESSED_MASK)) {
            pde |= PG_ACCESSED_MASK;
            stl(pde_ptr, pde);
        }

        /* page directory entry */
        /* 页表
         * (pde & ~0xfff) 用于取高20bit,为页表基址
         *  (addr >> 10) & 0xffc 页表项在页表内的偏移
         * 两者相加,为addr对应的页表项的物理地址(需要加上偏移)
         */
        pte_ptr = phys_ram_base + ((pde & ~0xfff) + ((addr >> 10) & 0xffc));
        pte = ldl(pte_ptr); /* 取出页表项,页表项4字节 */
#if defined(YDEBUG_MMU)
        printf("[D] pte_ptr=%08x, *pte=%08x\n", pte_ptr, pte);
#endif
        if (!(pte & PG_PRESENT_MASK)) {
            error_code = 0;
            goto do_fault;
        }
        if (is_user) {
            if (!(pte & PG_USER_MASK))
                goto do_fault_protect;
            if (is_write && !(pte & PG_RW_MASK))
                goto do_fault_protect;
        } else {
            if ((env->cr[0] & CR0_WP_MASK) && (pte & PG_USER_MASK) &&
                is_write && !(pte & PG_RW_MASK)) 
                goto do_fault_protect;
        }
        is_dirty = is_write && !(pte & PG_DIRTY_MASK);
        if (!(pte & PG_ACCESSED_MASK) || is_dirty) {
            pte |= PG_ACCESSED_MASK;
            if (is_dirty)
                pte |= PG_DIRTY_MASK;
            stl(pte_ptr, pte);
        }
        /* page大小为4096,也就是4k */
        page_size = 4096;
        /* 取addr的高20位,其他位全部为0, 这里的virt_addr实际指的是addr所在page的首地址 */
        virt_addr = addr & ~0xfff;
#if defined(YDEBUG_MMU)
        printf("[D] addr=0x%08x virt_addr=0x%08x\n", addr, virt_addr);
#endif
    }
    /* the page can be put in the TLB */
    prot = PROT_READ;
    if (is_user) {
        if (pte & PG_RW_MASK)
            prot |= PROT_WRITE;
    } else {
        if (!(env->cr[0] & CR0_WP_MASK) || !(pte & PG_USER_MASK) ||
            (pte & PG_RW_MASK))
            prot |= PROT_WRITE;
    }
    
 do_mapping: /* 做映射 */
    /* softmmu不开其实影响不大,只是模拟的cpu执行效率会有所下降而已. */
    if (env->hflags & HF_SOFTMMU_MASK) { /* softmmu启用,在大多数时候,softmmu都是不会启用的 */
        unsigned long paddr, vaddr, address, addend, page_offset;
        int index;

        /* software MMU case. Even if 4MB pages, we map only one 4KB
           page in the cache to avoid filling it too fast */
        /* addr & ~0xfff 用于取线性地址的高20bit, 按照道理来说,页内偏移应该是12位
         * 页内偏移不是(addr & 0xfff) & (page_size - 1)吗?
         * 没有错,addr对应的页内偏移确实是(addr & 0xfff) & (page_size - 1).
         * 如果没有开启分页,那么vaddr等于paddr
         * page_size为4096的情况下,page_offset为0,这里说明一下,这里的映射是以page为单位的,线性地址addr
         * 并不总是和page的大小对齐,对于这样的addr,这里的tlb实际记录的是addr所在page首地址(线性地址)和
         * 物理page的物理首地址映射.
         * 如果page_size为4M, 那么page_offset不为0.
         */
        page_offset = (addr & ~0xfff) & (page_size - 1); /* 页内偏移 */
        paddr = (pte & ~0xfff) + page_offset; /* 计算物理page页的首地址(物理地址) */
        vaddr = virt_addr + page_offset; /* 计算addr所在page的首地址(线性地址) */
        /* 2^20 ==> 256,tlb必然会不断更新 */
        index = (addr >> 12) & (CPU_TLB_SIZE - 1);
        pd = physpage_find(paddr);
#if defined(YDEBUG_MMU)
        printf("[D] addr=%08x, page_size=%d, page_offset=%08x, pd=%08xd, vaddr=%08x\n", 
               addr, page_size, page_offset, pd, vaddr);
#endif
        if (pd & 0xfff) {
            /* IO memory case */
            address = vaddr | pd;
            addend = paddr;
            printf("[D] address=0x%08x, addend=0x%08x\n", address, addend);
        } else {
            /* standard memory */
            address = vaddr; /* addr所在page的首地址(线性地址) */
            addend = (unsigned long)phys_ram_base + pd; /* addr所在page映射到的物理page的首地址(物理地址) */
        }
        addend -= vaddr; /* 注意这里减去了vaddr,至于意图,可以参考tlb的使用方法 */
        env->tlb_read[is_user][index].address = address; /* tlb记录下线性地址->物理地址的映射关系 */
        env->tlb_read[is_user][index].addend = addend;
        if (prot & PROT_WRITE) {
            env->tlb_write[is_user][index].address = address;
            env->tlb_write[is_user][index].addend = addend;
        }
    }
    ret = 0;
    /* 模拟内存的映射 */
    /* XXX: incorrect for 4MB pages */
    /* pte为页表项, pd为addr所在的page对应的物理page相对于物理内存起始位置的偏移 */
    pd = physpage_find(pte & ~0xfff);
    if ((pd & 0xfff) != 0) {
        /* IO access: no mapping is done as it will be handled by the
           soft MMU */
        if (!(env->hflags & HF_SOFTMMU_MASK))
            ret = 2;
    } else {
        void *map_addr;
        /* virt_addr为本进程内的地址, pte & ~0xfff */
        map_addr = mmap((void *)virt_addr, page_size, prot, 
                        MAP_SHARED | MAP_FIXED, phys_ram_fd, pd);
        if (map_addr == MAP_FAILED) {
            fprintf(stderr, 
                    "mmap failed when mapped physical address 0x%08x to virtual address 0x%08x\n",
                    pte & ~0xfff, virt_addr);
            exit(1);
        }
#if defined(DEBUG_MMU)
        printf("mmaping 0x%08x to virt 0x%08x pse=%d pd=0x%08x\n", 
               pte & ~0xfff, virt_addr, (page_size != 4096), pd);
#endif      
        /* 一旦映射建立成功,那么就设置页描述符的PAGE_VALID和其他相关属性 */
        page_set_flags(virt_addr, virt_addr + page_size, 
                       PAGE_VALID | PAGE_EXEC | prot);
    }
    return ret;
 do_fault_protect:
    error_code = PG_ERROR_P_MASK;
 do_fault:
    env->cr[2] = addr;
    env->error_code = (is_write << PG_ERROR_W_BIT) | error_code;
    if (is_user)
        env->error_code |= PG_ERROR_U_MASK;
    return 1;
}
