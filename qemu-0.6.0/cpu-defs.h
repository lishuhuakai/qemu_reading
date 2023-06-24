/*
 * common defines for all CPUs
 * 
 * Copyright (c) 2003 Fabrice Bellard
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
#ifndef CPU_DEFS_H
#define CPU_DEFS_H

#include "config.h"
#include <setjmp.h>
#include <inttypes.h>
#include "osdep.h"

#ifndef TARGET_LONG_BITS
#error TARGET_LONG_BITS must be defined before including this header
#endif

#if defined(__alpha__) || defined (__ia64__) || defined(__x86_64__)
#define HOST_LONG_BITS 64
#else
#define HOST_LONG_BITS 32
#endif

#ifndef TARGET_PHYS_ADDR_BITS 
#if TARGET_LONG_BITS >= HOST_LONG_BITS
#define TARGET_PHYS_ADDR_BITS TARGET_LONG_BITS
#else
#define TARGET_PHYS_ADDR_BITS HOST_LONG_BITS
#endif
#endif

#define TARGET_LONG_SIZE (TARGET_LONG_BITS / 8)

/* target_ulong is the type of a virtual address */
#if TARGET_LONG_SIZE == 4
typedef int32_t target_long;
typedef uint32_t target_ulong;
#elif TARGET_LONG_SIZE == 8
typedef int64_t target_long;
typedef uint64_t target_ulong;
#else
#error TARGET_LONG_SIZE undefined
#endif

/* target_phys_addr_t is the type of a physical address (its size can
   be different from 'target_ulong'). We have sizeof(target_phys_addr)
   = max(sizeof(unsigned long),
   sizeof(size_of_target_physical_address)) because we must pass a
   host pointer to memory operations in some cases */

#if TARGET_PHYS_ADDR_BITS == 32
typedef uint32_t target_phys_addr_t;
#elif TARGET_PHYS_ADDR_BITS == 64
typedef uint64_t target_phys_addr_t;
#else
#error TARGET_PHYS_ADDR_BITS undefined
#endif

#define HOST_LONG_SIZE (HOST_LONG_BITS / 8)

#define EXCP_INTERRUPT 	256 /* async interruption */
#define EXCP_HLT        257 /* hlt instruction reached */
#define EXCP_DEBUG      258 /* cpu stopped after a breakpoint or singlestep */

#define MAX_BREAKPOINTS 32

#define CPU_TLB_SIZE 256

typedef struct CPUTLBEntry {
    /* bit 31 to TARGET_PAGE_BITS : virtual address 
       bit TARGET_PAGE_BITS-1..IO_MEM_SHIFT : if non zero, memory io
                                              zone number
       bit 3                      : indicates that the entry is invalid
       bit 2..0                   : zero
    */
    target_ulong address; 
    /* addend to virtual address to get physical address */
    target_phys_addr_t addend; 
} CPUTLBEntry;

#endif
