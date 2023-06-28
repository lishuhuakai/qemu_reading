/*
 * USB UHCI controller emulation
 * 
 * Copyright (c) 2005 Fabrice Bellard
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

//#define DEBUG
//#define DEBUG_PACKET

#define UHCI_CMD_GRESET   (1 << 2) /* Global reset */
#define UHCI_CMD_HCRESET  (1 << 1) /* Host reset */
#define UHCI_CMD_RS       (1 << 0) /* Run/Stop -- 1表示Run, 0表示Stop */

#define UHCI_STS_HCHALTED (1 << 5) /* HC Halted */
#define UHCI_STS_HCPERR   (1 << 4) /* Host Controller Process Error: the schedule is buggy */
#define UHCI_STS_HSERR    (1 << 3) /* Host System Error: PCI problems */
#define UHCI_STS_RD       (1 << 2) /* Resume Detect */
#define UHCI_STS_USBERR   (1 << 1) /* Interrupt due to error */
#define UHCI_STS_USBINT   (1 << 0) /* Interrupt due to IOC */

#define TD_CTRL_SPD     (1 << 29) /* Short Packet Detect */
#define TD_CTRL_ERROR_SHIFT  27
#define TD_CTRL_IOS     (1 << 25) /* Isochronous Select */
#define TD_CTRL_IOC     (1 << 24) /* Interrupt On Complete enable */
#define TD_CTRL_ACTIVE  (1 << 23) /* TD Active */
#define TD_CTRL_STALL   (1 << 22) /* TD Stalled */
#define TD_CTRL_BABBLE  (1 << 20) /* Babble Detected */
#define TD_CTRL_NAK     (1 << 19) /* Nak Received */
#define TD_CTRL_TIMEOUT (1 << 18) /* CRC/Time Out Error */

#define UHCI_PORT_RESET (1 << 9) /* Port Reset */
#define UHCI_PORT_LSDA  (1 << 8) /* Low Speed Device Attached */
#define UHCI_PORT_ENC   (1 << 3) /* Port Enable Change */
#define UHCI_PORT_EN    (1 << 2)  /* Port Enable */
#define UHCI_PORT_CSC   (1 << 1) /* Connect Status Change */
#define UHCI_PORT_CCS   (1 << 0) /* Current Connect Status ("device present") */

#define FRAME_TIMER_FREQ 1000

#define FRAME_MAX_LOOPS  100

#define NB_PORTS 2

typedef struct UHCIPort {
    USBPort port;
    uint16_t ctrl;
} UHCIPort;

typedef struct UHCIState {
    PCIDevice dev;
    uint16_t cmd; /* cmd register */
    uint16_t status;
    /* 中断使能寄存器 */
    uint16_t intr; /* interrupt enable register */
    uint16_t frnum; /* frame number */
    /* frame list的基址 */
    uint32_t fl_base_addr; /* frame list base address */
    uint8_t sof_timing;
    uint8_t status2; /* bit 0 and 1 are used to generate UHCI_STS_USBINT */
    QEMUTimer *frame_timer;
    UHCIPort ports[NB_PORTS];
} UHCIState;

typedef struct UHCI_TD {
    uint32_t link; /* 要么指向另外一个TD,要么指向一个QH,要么指向空(PTR_TERM) */
    uint32_t ctrl; /* see TD_CTRL_xxx */
    uint32_t token;
    uint32_t buffer;
} UHCI_TD;

/* Queue Head */
typedef struct UHCI_QH {
    uint32_t link;
    uint32_t el_link;
} UHCI_QH;

static void uhci_attach(USBPort *port1, USBDevice *dev);

static void uhci_update_irq(UHCIState *s)
{
    int level;
    if (((s->status2 & 1) && (s->intr & (1 << 2))) ||
        ((s->status2 & 2) && (s->intr & (1 << 3))) ||
        ((s->status & UHCI_STS_USBERR) && (s->intr & (1 << 0))) ||
        ((s->status & UHCI_STS_RD) && (s->intr & (1 << 1))) ||
        (s->status & UHCI_STS_HSERR) ||
        (s->status & UHCI_STS_HCPERR)) {
        level = 1;
    } else {
        level = 0;
    }
    pci_set_irq(&s->dev, 3, level);
}

static void uhci_reset(UHCIState *s)
{
    uint8_t *pci_conf;
    int i;
    UHCIPort *port;

    pci_conf = s->dev.config;

    pci_conf[0x6a] = 0x01; /* usb clock */
    pci_conf[0x6b] = 0x00;
    s->cmd = 0;
    s->status = 0;
    s->status2 = 0;
    s->intr = 0;
    s->fl_base_addr = 0;
    s->sof_timing = 64;
    for(i = 0; i < NB_PORTS; i++) {
        port = &s->ports[i];
        port->ctrl = 0x0080;
        if (port->port.dev)
            uhci_attach(&port->port, port->port.dev);
    }
}

static void uhci_ioport_writeb(void *opaque, uint32_t addr, uint32_t val)
{
    UHCIState *s = opaque;
    
    addr &= 0x1f;
    switch(addr) {
    case 0x0c:
        s->sof_timing = val;
        break;
    }
}

static uint32_t uhci_ioport_readb(void *opaque, uint32_t addr)
{
    UHCIState *s = opaque;
    uint32_t val;

    addr &= 0x1f;
    switch(addr) {
    case 0x0c:
        val = s->sof_timing;
        break;
    default:
        val = 0xff;
        break;
    }
    return val;
}

static void uhci_ioport_writew(void *opaque, uint32_t addr, uint32_t val)
{
    UHCIState *s = opaque;
    
    addr &= 0x1f;
#ifdef DEBUG
    printf("uhci writew port=0x%04x val=0x%04x\n", addr, val);
#endif
    switch(addr) {
    case 0x00:
        if ((val & UHCI_CMD_RS) && !(s->cmd & UHCI_CMD_RS)) {
            /* start frame processing */
            /* 开始处理frame */
            qemu_mod_timer(s->frame_timer, qemu_get_clock(vm_clock));
            s->status &= ~UHCI_STS_HCHALTED;
        } else if (!(val & UHCI_CMD_RS)) {
            s->status |= UHCI_STS_HCHALTED;
        }
        if (val & UHCI_CMD_GRESET) { /* 全局重置 */
            UHCIPort *port;
            USBDevice *dev;
            int i;

            /* send reset on the USB bus */
            for(i = 0; i < NB_PORTS; i++) {
                port = &s->ports[i];
                dev = port->port.dev;
                if (dev) {
                    dev->handle_packet(dev, 
                                       USB_MSG_RESET, 0, 0, NULL, 0);
                }
            }
            uhci_reset(s);
            return;
        }
        if (val & UHCI_CMD_HCRESET) {
            uhci_reset(s);
            return;
        }
        s->cmd = val;
        break;
    case 0x02:
        s->status &= ~val;
        /* XXX: the chip spec is not coherent, so we add a hidden
           register to distinguish between IOC and SPD */
        if (val & UHCI_STS_USBINT)
            s->status2 = 0;
        uhci_update_irq(s);
        break;
    case 0x04:
        s->intr = val; /* 设置中断使能寄存器 */
        uhci_update_irq(s);
        break;
    case 0x06:
        if (s->status & UHCI_STS_HCHALTED)
            s->frnum = val & 0x7ff;
        break;
    case 0x10 ... 0x1f:
        {
            UHCIPort *port;
            USBDevice *dev;
            int n;

            n = (addr >> 1) & 7;
            if (n >= NB_PORTS)
                return;
            port = &s->ports[n];
            dev = port->port.dev;
            if (dev) {
                /* port reset */
                if ( (val & UHCI_PORT_RESET) && 
                     !(port->ctrl & UHCI_PORT_RESET) ) {
                    dev->handle_packet(dev, 
                                       USB_MSG_RESET, 0, 0, NULL, 0);
                }
            }
            port->ctrl = (port->ctrl & 0x01fb) | (val & ~0x01fb);
            /* some bits are reset when a '1' is written to them */
            port->ctrl &= ~(val & 0x000a);
        }
        break;
    }
}
/* 读取数据 */
static uint32_t uhci_ioport_readw(void *opaque, uint32_t addr)
{
    UHCIState *s = opaque;
    uint32_t val;

    addr &= 0x1f;
    switch(addr) {
    case 0x00:
        val = s->cmd;
        break;
    case 0x02:
        val = s->status;
        break;
    case 0x04:
        val = s->intr; /* 中断使能寄存器 */
        break;
    case 0x06:
        val = s->frnum;
        break;
    case 0x10 ... 0x1f:
        {
            UHCIPort *port;
            int n;
            n = (addr >> 1) & 7;
            if (n >= NB_PORTS) 
                goto read_default;
            port = &s->ports[n];
            val = port->ctrl; /* 读取某个端口的控制寄存器 */
        }
        break;
    default:
    read_default:
        val = 0xff7f; /* disabled port */
        break;
    }
#ifdef DEBUG
    printf("uhci readw port=0x%04x val=0x%04x\n", addr, val);
#endif
    return val;
}

static void uhci_ioport_writel(void *opaque, uint32_t addr, uint32_t val)
{
    UHCIState *s = opaque;

    addr &= 0x1f;
#ifdef DEBUG
    printf("uhci writel port=0x%04x val=0x%08x\n", addr, val);
#endif
    switch(addr) {
    case 0x08:
        s->fl_base_addr = val & ~0xfff;
        break;
    }
}

static uint32_t uhci_ioport_readl(void *opaque, uint32_t addr)
{
    UHCIState *s = opaque;
    uint32_t val;

    addr &= 0x1f;
    switch(addr) {
    case 0x08:
        val = s->fl_base_addr;
        break;
    default:
        val = 0xffffffff;
        break;
    }
    return val;
}

/* 设备连接上端口
 * @param port1 usb端口的抽象
 * @param dev usb设备
 */
static void uhci_attach(USBPort *port1, USBDevice *dev)
{
    UHCIState *s = port1->opaque;
    UHCIPort *port = &s->ports[port1->index];

    if (dev) {
        if (port->port.dev) {
            usb_attach(port1, NULL);
        }
        /* set connect status */
        /* 连接状态发生更改 -- UHCI_PORT_CSC
         * 设备已经连接上了 -- UHCI_PORT_CCS
         */
        port->ctrl |= UHCI_PORT_CCS | UHCI_PORT_CSC;

        /* update speed */
        if (dev->speed == USB_SPEED_LOW)
            port->ctrl |= UHCI_PORT_LSDA; /* 低速设备连接上了 */
        else
            port->ctrl &= ~UHCI_PORT_LSDA;
        port->port.dev = dev;
        /* send the attach message 
         * 发送attach消息
         */
        dev->handle_packet(dev, 
                           USB_MSG_ATTACH, 0, 0, NULL, 0);
    } else {
        /* set connect status */
        if (port->ctrl & UHCI_PORT_CCS) {
            port->ctrl &= ~UHCI_PORT_CCS; /* 设备当前不存在 */
            port->ctrl |= UHCI_PORT_CSC; /* 连接状态发生了更改 */
        }
        /* disable port */
        if (port->ctrl & UHCI_PORT_EN) {
            port->ctrl &= ~UHCI_PORT_EN; /* 端口现在不使能 */
            port->ctrl |= UHCI_PORT_ENC; /* 端口使能状态发生了更改 */
        }
        dev = port->port.dev;
        if (dev) {
            /* send the detach message */
            dev->handle_packet(dev, 
                               USB_MSG_DETACH, 0, 0, NULL, 0);
        }
        port->port.dev = NULL;
    }
}

/* 广播报文
 * @param devaddr 设备号
 * @param devep 端点号
 * @param data 数据
 */
static int uhci_broadcast_packet(UHCIState *s, uint8_t pid, 
                                 uint8_t devaddr, uint8_t devep,
                                 uint8_t *data, int len)
{
    UHCIPort *port;
    USBDevice *dev;
    int i, ret;

#ifdef DEBUG_PACKET
    {
        const char *pidstr;
        switch(pid) {
        case USB_TOKEN_SETUP: pidstr = "SETUP"; break;
        case USB_TOKEN_IN: pidstr = "IN"; break;
        case USB_TOKEN_OUT: pidstr = "OUT"; break;
        default: pidstr = "?"; break;
        }
        printf("frame %d: pid=%s addr=0x%02x ep=%d len=%d\n",
               s->frnum, pidstr, devaddr, devep, len);
        if (pid != USB_TOKEN_IN) {
            printf("     data_out=");
            for(i = 0; i < len; i++) {
                printf(" %02x", data[i]);
            }
            printf("\n");
        }
    }
#endif
    for(i = 0; i < NB_PORTS; i++) { /* 遍历所有的端口 */
        port = &s->ports[i];
        dev = port->port.dev;
        if (dev && (port->ctrl & UHCI_PORT_EN)) { /* 端口使能 && 端口上存在设备 */
            ret = dev->handle_packet(dev, pid, 
                                     devaddr, devep,
                                     data, len);
            if (ret != USB_RET_NODEV) {
#ifdef DEBUG_PACKET
                {
                    printf("     ret=%d ", ret);
                    if (pid == USB_TOKEN_IN && ret > 0) {
                        printf("data_in=");
                        for(i = 0; i < ret; i++) {
                            printf(" %02x", data[i]);
                        }
                    }
                    printf("\n");
                }
#endif
                return ret;
            }
        }
    }
    return USB_RET_NODEV;
}

/* return -1 if fatal error (frame must be stopped)
          0 if TD successful
          1 if TD unsuccessful or inactive
*/
static int uhci_handle_td(UHCIState *s, UHCI_TD *td, int *int_mask)
{
    uint8_t pid;
    uint8_t buf[1280];
    int len, max_len, err, ret;

    if (td->ctrl & TD_CTRL_IOC) {
        *int_mask |= 0x01;
    }
    
    if (!(td->ctrl & TD_CTRL_ACTIVE))
        return 1;

    /* TD is active */
    max_len = ((td->token >> 21) + 1) & 0x7ff; /* 提取bit21 ~ bit31的数据 */
    /* bit0 ~ bit7 ==> PID 
     * bit8 ~ bit14 ==> 设备地址
     * bit15 ~ bit18 ==> 端点号
     * bit19 ==> data toggle
     * bit20 ==> 保留
     * bit21 ~ bit31 ==> 这次传输的最大允许字节
     */
    pid = td->token & 0xff; 
    switch(pid) {
    case USB_TOKEN_OUT:
    case USB_TOKEN_SETUP:
        cpu_physical_memory_read(td->buffer, buf, max_len);
        ret = uhci_broadcast_packet(s, pid, 
                                    (td->token >> 8) & 0x7f, /* 设备号 */
                                    (td->token >> 15) & 0xf, /* 端点号 */
                                    buf, max_len);
        len = max_len;
        break;
    case USB_TOKEN_IN: /* 读取数据 */
        ret = uhci_broadcast_packet(s, pid, 
                                    (td->token >> 8) & 0x7f,
                                    (td->token >> 15) & 0xf,
                                    buf, max_len);
        /* 这里说明一下,ret代表设备的处理结果 */
        if (ret >= 0) {
            len = ret;
            if (len > max_len) {
                len = max_len;
                ret = USB_RET_BABBLE;
            }
            if (len > 0) { /* 将设备返回的结果直接写回去 */
                /* write the data back */
                cpu_physical_memory_write(td->buffer, buf, len);
            }
        } else {
            len = 0;
        }
        break;
    default:
        /* invalid pid : frame interrupted */
        s->status |= UHCI_STS_HCPERR;
        uhci_update_irq(s);
        return -1;
    }
    if (td->ctrl & TD_CTRL_IOS)
        td->ctrl &= ~TD_CTRL_ACTIVE;
    if (ret >= 0) {
        td->ctrl = (td->ctrl & ~0x7ff) | ((len - 1) & 0x7ff);
        td->ctrl &= ~TD_CTRL_ACTIVE;
        if (pid == USB_TOKEN_IN && 
            (td->ctrl & TD_CTRL_SPD) &&
            len < max_len) {
            *int_mask |= 0x02;
            /* short packet: do not update QH */
            return 1;
        } else {
            /* success */
            return 0;
        }
    } else {
        switch(ret) {
        default:
        case USB_RET_NODEV: /* 不存在此设备 */
        do_timeout:
            td->ctrl |= TD_CTRL_TIMEOUT; /* 打上超时标记 */
            err = (td->ctrl >> TD_CTRL_ERROR_SHIFT) & 3;
            if (err != 0) { /* 获得错误标志 */
                err--;
                if (err == 0) {
                    td->ctrl &= ~TD_CTRL_ACTIVE;
                    s->status |= UHCI_STS_USBERR; /* 更新状态寄存器 */
                    uhci_update_irq(s);
                }
            }
            td->ctrl = (td->ctrl & ~(3 << TD_CTRL_ERROR_SHIFT)) | 
                (err << TD_CTRL_ERROR_SHIFT);
            return 1;
        case USB_RET_NAK:
            td->ctrl |= TD_CTRL_NAK; /* 打上标志,说明接收到了NAK */
            if (pid == USB_TOKEN_SETUP)
                goto do_timeout;
            return 1;
        case USB_RET_STALL: /* 出错 */
            td->ctrl |= TD_CTRL_STALL;
            td->ctrl &= ~TD_CTRL_ACTIVE;
            return 1;
        case USB_RET_BABBLE:
            td->ctrl |= TD_CTRL_BABBLE | TD_CTRL_STALL;
            td->ctrl &= ~TD_CTRL_ACTIVE;
            /* frame interrupted */
            return -1;
        }
    }
}

static void uhci_frame_timer(void *opaque)
{
    UHCIState *s = opaque;
    int64_t expire_time;
    uint32_t frame_addr, link, old_td_ctrl, val;
    int int_mask, cnt, ret;
    UHCI_TD td;
    UHCI_QH qh;

    if (!(s->cmd & UHCI_CMD_RS)) {
        qemu_del_timer(s->frame_timer);
        /* set hchalted bit in status - UHCI11D 2.1.2 */
        s->status |= UHCI_STS_HCHALTED;
        return;
    }
    /* 每一个frame的大小为4字节 */
    frame_addr = s->fl_base_addr + ((s->frnum & 0x3ff) << 2);
    cpu_physical_memory_read(frame_addr, (uint8_t *)&link, 4); /* 读取4字节的frame */
    le32_to_cpus(&link);
    int_mask = 0;
    cnt = FRAME_MAX_LOOPS;
    while ((link & 1) == 0) { /* 第1个bit用于表示该指针指向的是QH还是TD,如果为1,那么是QH */
        if (--cnt == 0)
            break;
        /* valid frame */
        if (link & 2) { /* 有效的帧 */
            /* QH -- queue head 队列头部, QH将多个非等时TD连接起来 */
            cpu_physical_memory_read(link & ~0xf, (uint8_t *)&qh, sizeof(qh));
            le32_to_cpus(&qh.link);
            le32_to_cpus(&qh.el_link);
        depth_first:
            if (qh.el_link & 1) {
                /* no element : go to next entry */
                link = qh.link;
            } else if (qh.el_link & 2) {
                /* QH */
                link = qh.el_link; /* 指向下一个元素 */
            } else {
                /* TD */
                if (--cnt == 0)
                    break;
                /* 读取出一个transaction descriptor */
                cpu_physical_memory_read(qh.el_link & ~0xf, 
                                         (uint8_t *)&td, sizeof(td));
                le32_to_cpus(&td.link);
                le32_to_cpus(&td.ctrl);
                le32_to_cpus(&td.token);
                le32_to_cpus(&td.buffer);
                old_td_ctrl = td.ctrl;
                ret = uhci_handle_td(s, &td, &int_mask);
                /* update the status bits of the TD */
                if (old_td_ctrl != td.ctrl) {
                    val = cpu_to_le32(td.ctrl);
                    cpu_physical_memory_write((qh.el_link & ~0xf) + 4, 
                                              (const uint8_t *)&val, 
                                              sizeof(val));
                }
                if (ret < 0)
                    break; /* interrupted frame */
                if (ret == 0) {
                    /* update qh element link */
                    qh.el_link = td.link;
                    val = cpu_to_le32(qh.el_link);
                    /* 继续读取 */
                    cpu_physical_memory_write((link & ~0xf) + 4, 
                                              (const uint8_t *)&val, 
                                              sizeof(val));
                    if (qh.el_link & 4) {
                        /* depth first */
                        goto depth_first;
                    }
                }
                /* go to next entry */
                link = qh.link;
            }
        } else {
            /* TD */
            cpu_physical_memory_read(link & ~0xf, (uint8_t *)&td, sizeof(td));
            le32_to_cpus(&td.link);
            le32_to_cpus(&td.ctrl);
            le32_to_cpus(&td.token);
            le32_to_cpus(&td.buffer);
            old_td_ctrl = td.ctrl;
            ret = uhci_handle_td(s, &td, &int_mask);
            /* update the status bits of the TD */
            if (old_td_ctrl != td.ctrl) {
                val = cpu_to_le32(td.ctrl);
                cpu_physical_memory_write((link & ~0xf) + 4, 
                                          (const uint8_t *)&val, 
                                          sizeof(val));
            }
            if (ret < 0)
                break; /* interrupted frame */
            link = td.link;
        }
    }
    s->frnum = (s->frnum + 1) & 0x7ff; /* 更新帧号 */
    if (int_mask) {
        s->status2 |= int_mask;
        s->status |= UHCI_STS_USBINT;
        uhci_update_irq(s);
    }
    /* prepare the timer for the next frame */
    expire_time = qemu_get_clock(vm_clock) + 
        (ticks_per_sec / FRAME_TIMER_FREQ);
    qemu_mod_timer(s->frame_timer, expire_time);
}

static void uhci_map(PCIDevice *pci_dev, int region_num, 
                    uint32_t addr, uint32_t size, int type)
{
    UHCIState *s = (UHCIState *)pci_dev;

    register_ioport_write(addr, 32, 2, uhci_ioport_writew, s);
    register_ioport_read(addr, 32, 2, uhci_ioport_readw, s);
    register_ioport_write(addr, 32, 4, uhci_ioport_writel, s);
    register_ioport_read(addr, 32, 4, uhci_ioport_readl, s);
    register_ioport_write(addr, 32, 1, uhci_ioport_writeb, s);
    register_ioport_read(addr, 32, 1, uhci_ioport_readb, s);
}

void usb_uhci_init(PCIBus *bus, int devfn)
{
    UHCIState *s;
    uint8_t *pci_conf;
    int i;

    s = (UHCIState *)pci_register_device(bus,
                                        "USB-UHCI", sizeof(UHCIState),
                                        devfn, NULL, NULL);
    pci_conf = s->dev.config;
    pci_conf[0x00] = 0x86;
    pci_conf[0x01] = 0x80;
    pci_conf[0x02] = 0x20;
    pci_conf[0x03] = 0x70;
    pci_conf[0x08] = 0x01; // revision number
    pci_conf[0x09] = 0x00;
    pci_conf[0x0a] = 0x03;
    pci_conf[0x0b] = 0x0c;
    pci_conf[0x0e] = 0x00; // header_type
    pci_conf[0x3d] = 4; // interrupt pin 3
    pci_conf[0x60] = 0x10; // release number
    
    for(i = 0; i < NB_PORTS; i++) { /* 注册usb端口 */
        qemu_register_usb_port(&s->ports[i].port, s, i, uhci_attach);
    }
    s->frame_timer = qemu_new_timer(vm_clock, uhci_frame_timer, s);

    uhci_reset(s);

    /* Use region 4 for consistency with real hardware.  BSD guests seem
       to rely on this.  */
    pci_register_io_region(&s->dev, 4, 0x20, 
                           PCI_ADDRESS_SPACE_IO, uhci_map);
}
