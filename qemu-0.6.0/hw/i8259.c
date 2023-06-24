/*
 * QEMU 8259 interrupt controller emulation
 * 
 * Copyright (c) 2003-2004 Fabrice Bellard
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
#include "vl.h"

/* debug PIC */
//#define DEBUG_PIC

//#define DEBUG_IRQ_LATENCY
//#define DEBUG_IRQ_COUNT

typedef struct PicState {
    uint8_t last_irr; /* edge detection */
    uint8_t irr; /* interrupt request register */
    uint8_t imr; /* interrupt mask register */
    uint8_t isr; /* interrupt service register */
    uint8_t priority_add; /* highest irq priority */
    uint8_t irq_base;
    uint8_t read_reg_select;
    uint8_t poll;
    uint8_t special_mask;
    uint8_t init_state;
    uint8_t auto_eoi;
    uint8_t rotate_on_auto_eoi;
    uint8_t special_fully_nested_mode;
    uint8_t init4; /* true if 4 byte init */
    uint8_t elcr; /* PIIX edge/trigger selection*/
    uint8_t elcr_mask;
} PicState;

/* 0 is master pic, 1 is slave pic */
static PicState pics[2];

#if defined(DEBUG_PIC) || defined (DEBUG_IRQ_COUNT)
static int irq_level[16];
#endif
#ifdef DEBUG_IRQ_COUNT
static uint64_t irq_count[16];
#endif

/* set irq level. If an edge is detected, then the IRR is set to 1 */
static inline void pic_set_irq1(PicState *s, int irq, int level)
{
    int mask;
    mask = 1 << irq;
    if (s->elcr & mask) {
        /* level triggered */
        if (level) {
            s->irr |= mask;
            s->last_irr |= mask;
        } else {
            s->irr &= ~mask;
            s->last_irr &= ~mask;
        }
    } else {
        /* edge triggered */
        if (level) {
            if ((s->last_irr & mask) == 0)
                s->irr |= mask;
            s->last_irr |= mask;
        } else {
            s->last_irr &= ~mask;
        }
    }
}

/* return the highest priority found in mask (highest = smallest
   number). Return 8 if no irq */
static inline int get_priority(PicState *s, int mask)
{
    int priority;
    if (mask == 0)
        return 8;
    priority = 0;
    while ((mask & (1 << ((priority + s->priority_add) & 7))) == 0)
        priority++;
    return priority;
}

/* return the pic wanted interrupt. return -1 if none */
static int pic_get_irq(PicState *s)
{
    int mask, cur_priority, priority;

    mask = s->irr & ~s->imr;
    priority = get_priority(s, mask);
    if (priority == 8)
        return -1;
    /* compute current priority. If special fully nested mode on the
       master, the IRQ coming from the slave is not taken into account
       for the priority computation. */
    mask = s->isr;
    if (s->special_fully_nested_mode && s == &pics[0])
        mask &= ~(1 << 2);
    cur_priority = get_priority(s, mask);
    if (priority < cur_priority) {
        /* higher priority found: an irq should be generated */
        return (priority + s->priority_add) & 7;
    } else {
        return -1;
    }
}

/* raise irq to CPU if necessary. must be called every time the active
   irq may change */
static void pic_update_irq(void)
{
    int irq2, irq;

    /* first look at slave pic */
    irq2 = pic_get_irq(&pics[1]);
    if (irq2 >= 0) {
        /* if irq request by slave pic, signal master PIC */
        pic_set_irq1(&pics[0], 2, 1);
        pic_set_irq1(&pics[0], 2, 0);
    }
    /* look at requested irq */
    irq = pic_get_irq(&pics[0]);
    if (irq >= 0) {
#if defined(DEBUG_PIC)
        {
            int i;
            for(i = 0; i < 2; i++) {
                printf("pic%d: imr=%x irr=%x padd=%d\n", 
                       i, pics[i].imr, pics[i].irr, pics[i].priority_add);
                
            }
        }
        printf("pic: cpu_interrupt\n");
#endif
        cpu_interrupt(cpu_single_env, CPU_INTERRUPT_HARD);
    }
}

#ifdef DEBUG_IRQ_LATENCY
int64_t irq_time[16];
#endif

void pic_set_irq(int irq, int level)
{
#if defined(DEBUG_PIC) || defined(DEBUG_IRQ_COUNT)
    if (level != irq_level[irq]) {
#if defined(DEBUG_PIC)
        printf("pic_set_irq: irq=%d level=%d\n", irq, level);
#endif
        irq_level[irq] = level;
#ifdef DEBUG_IRQ_COUNT
	if (level == 1)
	    irq_count[irq]++;
#endif
    }
#endif
#ifdef DEBUG_IRQ_LATENCY
    if (level) {
        irq_time[irq] = qemu_get_clock(vm_clock);
    }
#endif
    pic_set_irq1(&pics[irq >> 3], irq & 7, level);
    pic_update_irq();
}

/* acknowledge interrupt 'irq' */
static inline void pic_intack(PicState *s, int irq)
{
    if (s->auto_eoi) {
        if (s->rotate_on_auto_eoi)
            s->priority_add = (irq + 1) & 7;
    } else {
        s->isr |= (1 << irq);
    }
    s->irr &= ~(1 << irq);
}

int cpu_get_pic_interrupt(CPUState *env)
{
    int irq, irq2, intno;

    /* read the irq from the PIC */

    irq = pic_get_irq(&pics[0]);
    if (irq >= 0) {
        pic_intack(&pics[0], irq);
        if (irq == 2) {
            irq2 = pic_get_irq(&pics[1]);
            if (irq2 >= 0) {
                pic_intack(&pics[1], irq2);
            } else {
                /* spurious IRQ on slave controller */
                irq2 = 7;
            }
            intno = pics[1].irq_base + irq2;
            irq = irq2 + 8;
        } else {
            intno = pics[0].irq_base + irq;
        }
    } else {
        /* spurious IRQ on host controller */
        irq = 7;
        intno = pics[0].irq_base + irq;
    }
    pic_update_irq();
        
#ifdef DEBUG_IRQ_LATENCY
    printf("IRQ%d latency=%0.3fus\n", 
           irq, 
           (double)(qemu_get_clock(vm_clock) - irq_time[irq]) * 1000000.0 / ticks_per_sec);
#endif
#if defined(DEBUG_PIC)
    printf("pic_interrupt: irq=%d\n", irq);
#endif
    return intno;
}

static void pic_reset(void *opaque)
{
    PicState *s = opaque;
    int tmp;

    tmp = s->elcr_mask;
    memset(s, 0, sizeof(PicState));
    s->elcr_mask = tmp;
}

static void pic_ioport_write(void *opaque, uint32_t addr, uint32_t val)
{
    PicState *s = opaque;
    int priority, cmd, irq;

#ifdef DEBUG_PIC
    printf("pic_write: addr=0x%02x val=0x%02x\n", addr, val);
#endif
    addr &= 1;
    if (addr == 0) {
        if (val & 0x10) {
            /* init */
            pic_reset(s);
            /* deassert a pending interrupt */
            cpu_reset_interrupt(cpu_single_env, CPU_INTERRUPT_HARD);

            s->init_state = 1;
            s->init4 = val & 1;
            if (val & 0x02)
                hw_error("single mode not supported");
            if (val & 0x08)
                hw_error("level sensitive irq not supported");
        } else if (val & 0x08) {
            if (val & 0x04)
                s->poll = 1;
            if (val & 0x02)
                s->read_reg_select = val & 1;
            if (val & 0x40)
                s->special_mask = (val >> 5) & 1;
        } else {
            cmd = val >> 5;
            switch(cmd) {
            case 0:
            case 4:
                s->rotate_on_auto_eoi = cmd >> 2;
                break;
            case 1: /* end of interrupt */
            case 5:
                priority = get_priority(s, s->isr);
                if (priority != 8) {
                    irq = (priority + s->priority_add) & 7;
                    s->isr &= ~(1 << irq);
                    if (cmd == 5)
                        s->priority_add = (irq + 1) & 7;
                    pic_update_irq();
                }
                break;
            case 3:
                irq = val & 7;
                s->isr &= ~(1 << irq);
                pic_update_irq();
                break;
            case 6:
                s->priority_add = (val + 1) & 7;
                pic_update_irq();
                break;
            case 7:
                irq = val & 7;
                s->isr &= ~(1 << irq);
                s->priority_add = (irq + 1) & 7;
                pic_update_irq();
                break;
            default:
                /* no operation */
                break;
            }
        }
    } else {
        switch(s->init_state) {
        case 0:
            /* normal mode */
            s->imr = val;
            pic_update_irq();
            break;
        case 1:
            s->irq_base = val & 0xf8;
            s->init_state = 2;
            break;
        case 2:
            if (s->init4) {
                s->init_state = 3;
            } else {
                s->init_state = 0;
            }
            break;
        case 3:
            s->special_fully_nested_mode = (val >> 4) & 1;
            s->auto_eoi = (val >> 1) & 1;
            s->init_state = 0;
            break;
        }
    }
}

static uint32_t pic_poll_read (PicState *s, uint32_t addr1)
{
    int ret;

    ret = pic_get_irq(s);
    if (ret >= 0) {
        if (addr1 >> 7) {
            pics[0].isr &= ~(1 << 2);
            pics[0].irr &= ~(1 << 2);
        }
        s->irr &= ~(1 << ret);
        s->isr &= ~(1 << ret);
        if (addr1 >> 7 || ret != 2)
            pic_update_irq();
    } else {
        ret = 0x07;
        pic_update_irq();
    }

    return ret;
}

static uint32_t pic_ioport_read(void *opaque, uint32_t addr1)
{
    PicState *s = opaque;
    unsigned int addr;
    int ret;

    addr = addr1;
    addr &= 1;
    if (s->poll) {
        ret = pic_poll_read(s, addr1);
        s->poll = 0;
    } else {
        if (addr == 0) {
            if (s->read_reg_select)
                ret = s->isr;
            else
                ret = s->irr;
        } else {
            ret = s->imr;
        }
    }
#ifdef DEBUG_PIC
    printf("pic_read: addr=0x%02x val=0x%02x\n", addr1, ret);
#endif
    return ret;
}

/* memory mapped interrupt status */
uint32_t pic_intack_read(CPUState *env)
{
    int ret;

    ret = pic_poll_read(&pics[0], 0x00);
    if (ret == 2)
        ret = pic_poll_read(&pics[1], 0x80) + 8;
    /* Prepare for ISR read */
    pics[0].read_reg_select = 1;
    
    return ret;
}

static void elcr_ioport_write(void *opaque, uint32_t addr, uint32_t val)
{
    PicState *s = opaque;
    s->elcr = val & s->elcr_mask;
}

static uint32_t elcr_ioport_read(void *opaque, uint32_t addr1)
{
    PicState *s = opaque;
    return s->elcr;
}

static void pic_save(QEMUFile *f, void *opaque)
{
    PicState *s = opaque;
    
    qemu_put_8s(f, &s->last_irr);
    qemu_put_8s(f, &s->irr);
    qemu_put_8s(f, &s->imr);
    qemu_put_8s(f, &s->isr);
    qemu_put_8s(f, &s->priority_add);
    qemu_put_8s(f, &s->irq_base);
    qemu_put_8s(f, &s->read_reg_select);
    qemu_put_8s(f, &s->poll);
    qemu_put_8s(f, &s->special_mask);
    qemu_put_8s(f, &s->init_state);
    qemu_put_8s(f, &s->auto_eoi);
    qemu_put_8s(f, &s->rotate_on_auto_eoi);
    qemu_put_8s(f, &s->special_fully_nested_mode);
    qemu_put_8s(f, &s->init4);
    qemu_put_8s(f, &s->elcr);
}

static int pic_load(QEMUFile *f, void *opaque, int version_id)
{
    PicState *s = opaque;
    
    if (version_id != 1)
        return -EINVAL;

    qemu_get_8s(f, &s->last_irr);
    qemu_get_8s(f, &s->irr);
    qemu_get_8s(f, &s->imr);
    qemu_get_8s(f, &s->isr);
    qemu_get_8s(f, &s->priority_add);
    qemu_get_8s(f, &s->irq_base);
    qemu_get_8s(f, &s->read_reg_select);
    qemu_get_8s(f, &s->poll);
    qemu_get_8s(f, &s->special_mask);
    qemu_get_8s(f, &s->init_state);
    qemu_get_8s(f, &s->auto_eoi);
    qemu_get_8s(f, &s->rotate_on_auto_eoi);
    qemu_get_8s(f, &s->special_fully_nested_mode);
    qemu_get_8s(f, &s->init4);
    qemu_get_8s(f, &s->elcr);
    return 0;
}

/* XXX: add generic master/slave system */
static void pic_init1(int io_addr, int elcr_addr, PicState *s)
{
    register_ioport_write(io_addr, 2, 1, pic_ioport_write, s);
    register_ioport_read(io_addr, 2, 1, pic_ioport_read, s);
    if (elcr_addr >= 0) {
        register_ioport_write(elcr_addr, 1, 1, elcr_ioport_write, s);
        register_ioport_read(elcr_addr, 1, 1, elcr_ioport_read, s);
    }
    register_savevm("i8259", io_addr, 1, pic_save, pic_load, s);
    qemu_register_reset(pic_reset, s);
}

void pic_info(void)
{
    int i;
    PicState *s;

    for(i=0;i<2;i++) {
        s = &pics[i];
        term_printf("pic%d: irr=%02x imr=%02x isr=%02x hprio=%d irq_base=%02x rr_sel=%d elcr=%02x fnm=%d\n",
                    i, s->irr, s->imr, s->isr, s->priority_add, 
                    s->irq_base, s->read_reg_select, s->elcr, 
                    s->special_fully_nested_mode);
    }
}

void irq_info(void)
{
#ifndef DEBUG_IRQ_COUNT
    term_printf("irq statistic code not compiled.\n");
#else
    int i;
    int64_t count;

    term_printf("IRQ statistics:\n");
    for (i = 0; i < 16; i++) {
        count = irq_count[i];
        if (count > 0)
            term_printf("%2d: %lld\n", i, count);
    }
#endif
}

void pic_init(void)
{
    pic_init1(0x20, 0x4d0, &pics[0]);
    pic_init1(0xa0, 0x4d1, &pics[1]);
    pics[0].elcr_mask = 0xf8;
    pics[1].elcr_mask = 0xde;
}

