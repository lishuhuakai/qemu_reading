/* common syscall defines for all architectures */

/* Note: although the syscall numbers change between architectures,
   most of them stay the same, so we handle it by puting ifdefs if
   necessary */

#include "syscall_nr.h"

#define SOCKOP_socket           1
#define SOCKOP_bind             2
#define SOCKOP_connect          3
#define SOCKOP_listen           4
#define SOCKOP_accept           5
#define SOCKOP_getsockname      6
#define SOCKOP_getpeername      7
#define SOCKOP_socketpair       8
#define SOCKOP_send             9
#define SOCKOP_recv             10
#define SOCKOP_sendto           11
#define SOCKOP_recvfrom         12
#define SOCKOP_shutdown         13
#define SOCKOP_setsockopt       14
#define SOCKOP_getsockopt       15
#define SOCKOP_sendmsg          16
#define SOCKOP_recvmsg          17

#define IPCOP_semop		1
#define IPCOP_semget		2
#define IPCOP_semctl		3
#define IPCOP_semtimedop	4
#define IPCOP_msgsnd		11
#define IPCOP_msgrcv		12
#define IPCOP_msgget		13
#define IPCOP_msgctl		14
#define IPCOP_shmat		21
#define IPCOP_shmdt		22
#define IPCOP_shmget		23
#define IPCOP_shmctl		24

/*
 * The following is for compatibility across the various Linux
 * platforms.  The i386 ioctl numbering scheme doesn't really enforce
 * a type field.  De facto, however, the top 8 bits of the lower 16
 * bits are indeed used as a type field, so we might just as well make
 * this explicit here.  Please be sure to use the decoding macros
 * below from now on.
 */
#define TARGET_IOC_NRBITS	8
#define TARGET_IOC_TYPEBITS	8

#if defined(TARGET_I386) || defined(TARGET_ARM)

#define TARGET_IOC_SIZEBITS	14
#define TARGET_IOC_DIRBITS	2

#define TARGET_IOC_NONE	  0U
#define TARGET_IOC_WRITE  1U
#define TARGET_IOC_READ	  2U

#elif defined(TARGET_PPC) || defined(TARGET_ALPHA) || defined(TARGET_SPARC)

#define TARGET_IOC_SIZEBITS	13
#define TARGET_IOC_DIRBITS	3

#define TARGET_IOC_NONE	  1U
#define TARGET_IOC_READ	  2U
#define TARGET_IOC_WRITE  4U

#else
#error unsupported CPU
#endif

#define TARGET_IOC_NRMASK	((1 << TARGET_IOC_NRBITS)-1)
#define TARGET_IOC_TYPEMASK	((1 << TARGET_IOC_TYPEBITS)-1)
#define TARGET_IOC_SIZEMASK	((1 << TARGET_IOC_SIZEBITS)-1)
#define TARGET_IOC_DIRMASK	((1 << TARGET_IOC_DIRBITS)-1)

#define TARGET_IOC_NRSHIFT	0
#define TARGET_IOC_TYPESHIFT	(TARGET_IOC_NRSHIFT+TARGET_IOC_NRBITS)
#define TARGET_IOC_SIZESHIFT	(TARGET_IOC_TYPESHIFT+TARGET_IOC_TYPEBITS)
#define TARGET_IOC_DIRSHIFT	(TARGET_IOC_SIZESHIFT+TARGET_IOC_SIZEBITS)

#define TARGET_IOC(dir,type,nr,size) \
	(((dir)  << TARGET_IOC_DIRSHIFT) | \
	 ((type) << TARGET_IOC_TYPESHIFT) | \
	 ((nr)   << TARGET_IOC_NRSHIFT) | \
	 ((size) << TARGET_IOC_SIZESHIFT))

/* used to create numbers */
#define TARGET_IO(type,nr)		TARGET_IOC(TARGET_IOC_NONE,(type),(nr),0)
#define TARGET_IOR(type,nr,size)	TARGET_IOC(TARGET_IOC_READ,(type),(nr),sizeof(size))
#define TARGET_IOW(type,nr,size)	TARGET_IOC(TARGET_IOC_WRITE,(type),(nr),sizeof(size))
#define TARGET_IOWR(type,nr,size)	TARGET_IOC(TARGET_IOC_READ|TARGET_IOC_WRITE,(type),(nr),sizeof(size))

/* the size is automatically computed for these defines */
#define TARGET_IORU(type,nr)	TARGET_IOC(TARGET_IOC_READ,(type),(nr),TARGET_IOC_SIZEMASK)
#define TARGET_IOWU(type,nr)	TARGET_IOC(TARGET_IOC_WRITE,(type),(nr),TARGET_IOC_SIZEMASK)
#define TARGET_IOWRU(type,nr)	TARGET_IOC(TARGET_IOC_READ|TARGET_IOC_WRITE,(type),(nr),TARGET_IOC_SIZEMASK)

struct target_sockaddr {
    uint16_t sa_family;
    uint8_t sa_data[14];
};

struct target_timeval {
    target_long tv_sec;
    target_long tv_usec;
};

struct target_timespec {
    target_long tv_sec;
    target_long tv_nsec;
};

struct target_itimerval {
    struct target_timeval it_interval;
    struct target_timeval it_value;
};

typedef target_long target_clock_t;

#define TARGET_HZ 100

struct target_tms {
    target_clock_t tms_utime;
    target_clock_t tms_stime;
    target_clock_t tms_cutime;
    target_clock_t tms_cstime;
};

struct target_utimbuf {
    target_long actime;
    target_long modtime;
};

struct target_sel_arg_struct {
    target_long n;
    target_long inp, outp, exp;
    target_long tvp;
};

struct target_iovec {
    target_long iov_base;   /* Starting address */
    target_long iov_len;   /* Number of bytes */
};

struct target_msghdr {
    target_long	 msg_name;	/* Socket name			*/
    int		 msg_namelen;	/* Length of name		*/
    target_long	 msg_iov;	/* Data blocks			*/
    target_long	 msg_iovlen;	/* Number of blocks		*/
    target_long  msg_control;	/* Per protocol magic (eg BSD file descriptor passing) */
    target_long	 msg_controllen;	/* Length of cmsg list */
    unsigned int msg_flags;
};

struct target_cmsghdr {
    target_long  cmsg_len;
    int          cmsg_level;
    int          cmsg_type;
};

#define TARGET_CMSG_DATA(cmsg) ((unsigned char *) ((struct target_cmsghdr *) (cmsg) + 1))
#define TARGET_CMSG_NXTHDR(mhdr, cmsg) __target_cmsg_nxthdr (mhdr, cmsg)
#define TARGET_CMSG_FIRSTHDR(mhdr) \
  ((size_t) tswapl((mhdr)->msg_controllen) >= sizeof (struct target_cmsghdr) \
   ? (struct target_cmsghdr *) tswapl((mhdr)->msg_control) : (struct target_cmsghdr *) NULL)
#define TARGET_CMSG_ALIGN(len) (((len) + sizeof (target_long) - 1) \
                               & (size_t) ~(sizeof (target_long) - 1))
#define TARGET_CMSG_SPACE(len) (TARGET_CMSG_ALIGN (len) \
                               + TARGET_CMSG_ALIGN (sizeof (struct target_cmsghdr)))
#define TARGET_CMSG_LEN(len)   (TARGET_CMSG_ALIGN (sizeof (struct target_cmsghdr)) + (len))

static __inline__ struct target_cmsghdr *
__target_cmsg_nxthdr (struct target_msghdr *__mhdr, struct target_cmsghdr *__cmsg)
{
  if (tswapl(__cmsg->cmsg_len) < sizeof (struct target_cmsghdr))
    /* The kernel header does this so there may be a reason.  */
    return 0;

  __cmsg = (struct target_cmsghdr *) ((unsigned char *) __cmsg
                               + TARGET_CMSG_ALIGN (tswapl(__cmsg->cmsg_len)));
  if ((unsigned char *) (__cmsg + 1) > ((unsigned char *) tswapl(__mhdr->msg_control)
                                        + tswapl(__mhdr->msg_controllen))
      || ((unsigned char *) __cmsg + TARGET_CMSG_ALIGN (tswapl(__cmsg->cmsg_len))
          > ((unsigned char *) tswapl(__mhdr->msg_control) 
             + tswapl(__mhdr->msg_controllen))))
    /* No more entries.  */
    return 0;
  return __cmsg;
}


struct  target_rusage {
        struct target_timeval ru_utime;        /* user time used */
        struct target_timeval ru_stime;        /* system time used */
        target_long    ru_maxrss;              /* maximum resident set size */
        target_long    ru_ixrss;               /* integral shared memory size */
        target_long    ru_idrss;               /* integral unshared data size */
        target_long    ru_isrss;               /* integral unshared stack size */
        target_long    ru_minflt;              /* page reclaims */
        target_long    ru_majflt;              /* page faults */
        target_long    ru_nswap;               /* swaps */
        target_long    ru_inblock;             /* block input operations */
        target_long    ru_oublock;             /* block output operations */
        target_long    ru_msgsnd;              /* messages sent */
        target_long    ru_msgrcv;              /* messages received */
        target_long    ru_nsignals;            /* signals received */
        target_long    ru_nvcsw;               /* voluntary context switches */
        target_long    ru_nivcsw;              /* involuntary " */
};

typedef struct {
        int     val[2];
} kernel_fsid_t;

struct kernel_statfs {
	int f_type;
	int f_bsize;
	int f_blocks;
	int f_bfree;
	int f_bavail;
	int f_files;
	int f_ffree;
        kernel_fsid_t f_fsid;
	int f_namelen;
	int f_spare[6];
};

struct target_dirent {
	target_long	d_ino;
	target_long	d_off;
	unsigned short	d_reclen;
	char		d_name[256]; /* We must not include limits.h! */
};

struct target_dirent64 {
	uint64_t	d_ino;
	int64_t		d_off;
	unsigned short	d_reclen;
	unsigned char	d_type;
	char		d_name[256];
};


/* mostly generic signal stuff */
#define TARGET_SIG_DFL	((target_long)0)	/* default signal handling */
#define TARGET_SIG_IGN	((target_long)1)	/* ignore signal */
#define TARGET_SIG_ERR	((target_long)-1)	/* error return from signal */

#ifdef TARGET_MIPS
#define TARGET_NSIG	   128
#else
#define TARGET_NSIG	   64
#endif
#define TARGET_NSIG_BPW	   TARGET_LONG_BITS
#define TARGET_NSIG_WORDS  (TARGET_NSIG / TARGET_NSIG_BPW)

typedef struct {
    target_ulong sig[TARGET_NSIG_WORDS];
} target_sigset_t;

#ifdef BSWAP_NEEDED
static inline void tswap_sigset(target_sigset_t *d, const target_sigset_t *s)
{
    int i;
    for(i = 0;i < TARGET_NSIG_WORDS; i++)
        d->sig[i] = tswapl(s->sig[i]);
}
#else
static inline void tswap_sigset(target_sigset_t *d, const target_sigset_t *s)
{
    *d = *s;
}
#endif

static inline void target_siginitset(target_sigset_t *d, target_ulong set)
{
    int i;
    d->sig[0] = set;
    for(i = 1;i < TARGET_NSIG_WORDS; i++)
        d->sig[i] = 0;
}

void host_to_target_sigset(target_sigset_t *d, const sigset_t *s);
void target_to_host_sigset(sigset_t *d, const target_sigset_t *s);
void host_to_target_old_sigset(target_ulong *old_sigset, 
                               const sigset_t *sigset);
void target_to_host_old_sigset(sigset_t *sigset, 
                               const target_ulong *old_sigset);
struct target_sigaction;
int do_sigaction(int sig, const struct target_sigaction *act,
                 struct target_sigaction *oact);

#if defined(TARGET_I386) || defined(TARGET_ARM) || defined(TARGET_SPARC) || defined(TARGET_PPC)

#define TARGET_SA_NOCLDSTOP	0x00000001
#define TARGET_SA_NOCLDWAIT	0x00000002 /* not supported yet */
#define TARGET_SA_SIGINFO	0x00000004
#define TARGET_SA_ONSTACK	0x08000000
#define TARGET_SA_RESTART	0x10000000
#define TARGET_SA_NODEFER	0x40000000
#define TARGET_SA_RESETHAND	0x80000000
#define TARGET_SA_RESTORER	0x04000000

#define TARGET_SIGHUP		 1
#define TARGET_SIGINT		 2
#define TARGET_SIGQUIT		 3
#define TARGET_SIGILL		 4
#define TARGET_SIGTRAP		 5
#define TARGET_SIGABRT		 6
#define TARGET_SIGIOT		 6
#define TARGET_SIGBUS		 7
#define TARGET_SIGFPE		 8
#define TARGET_SIGKILL		 9
#define TARGET_SIGUSR1		10
#define TARGET_SIGSEGV		11
#define TARGET_SIGUSR2		12
#define TARGET_SIGPIPE		13
#define TARGET_SIGALRM		14
#define TARGET_SIGTERM		15
#define TARGET_SIGSTKFLT	16
#define TARGET_SIGCHLD		17
#define TARGET_SIGCONT		18
#define TARGET_SIGSTOP		19
#define TARGET_SIGTSTP		20
#define TARGET_SIGTTIN		21
#define TARGET_SIGTTOU		22
#define TARGET_SIGURG		23
#define TARGET_SIGXCPU		24
#define TARGET_SIGXFSZ		25
#define TARGET_SIGVTALRM	26
#define TARGET_SIGPROF		27
#define TARGET_SIGWINCH	        28
#define TARGET_SIGIO		29
#define TARGET_SIGPWR		30
#define TARGET_SIGSYS		31
#define TARGET_SIGRTMIN         32

#define TARGET_SIG_BLOCK          0    /* for blocking signals */
#define TARGET_SIG_UNBLOCK        1    /* for unblocking signals */
#define TARGET_SIG_SETMASK        2    /* for setting the signal mask */

struct target_old_sigaction {
        target_ulong _sa_handler;
        target_ulong sa_mask;
        target_ulong sa_flags;
        target_ulong sa_restorer;
};

struct target_sigaction {
        target_ulong _sa_handler;
        target_ulong sa_flags;
        target_ulong sa_restorer;
        target_sigset_t sa_mask;
};

typedef union target_sigval {
	int sival_int;
        target_ulong sival_ptr;
} target_sigval_t;

#define TARGET_SI_MAX_SIZE	128
#define TARGET_SI_PAD_SIZE	((TARGET_SI_MAX_SIZE/sizeof(int)) - 3)

typedef struct target_siginfo {
	int si_signo;
	int si_errno;
	int si_code;

	union {
		int _pad[TARGET_SI_PAD_SIZE];

		/* kill() */
		struct {
			pid_t _pid;		/* sender's pid */
			uid_t _uid;		/* sender's uid */
		} _kill;

		/* POSIX.1b timers */
		struct {
			unsigned int _timer1;
			unsigned int _timer2;
		} _timer;

		/* POSIX.1b signals */
		struct {
			pid_t _pid;		/* sender's pid */
			uid_t _uid;		/* sender's uid */
			target_sigval_t _sigval;
		} _rt;

		/* SIGCHLD */
		struct {
			pid_t _pid;		/* which child */
			uid_t _uid;		/* sender's uid */
			int _status;		/* exit code */
			target_clock_t _utime;
                        target_clock_t _stime;
		} _sigchld;

		/* SIGILL, SIGFPE, SIGSEGV, SIGBUS */
		struct {
			target_ulong _addr; /* faulting insn/memory ref. */
		} _sigfault;

		/* SIGPOLL */
		struct {
			int _band;	/* POLL_IN, POLL_OUT, POLL_MSG */
			int _fd;
		} _sigpoll;
	} _sifields;
} target_siginfo_t;

/*
 * si_code values
 * Digital reserves positive values for kernel-generated signals.
 */
#define TARGET_SI_USER		0	/* sent by kill, sigsend, raise */
#define TARGET_SI_KERNEL	0x80	/* sent by the kernel from somewhere */
#define TARGET_SI_QUEUE	-1		/* sent by sigqueue */
#define TARGET_SI_TIMER -2              /* sent by timer expiration */
#define TARGET_SI_MESGQ	-3		/* sent by real time mesq state change */
#define TARGET_SI_ASYNCIO	-4	/* sent by AIO completion */
#define TARGET_SI_SIGIO	-5		/* sent by queued SIGIO */

/*
 * SIGILL si_codes
 */
#define TARGET_ILL_ILLOPC	(1)	/* illegal opcode */
#define TARGET_ILL_ILLOPN	(2)	/* illegal operand */
#define TARGET_ILL_ILLADR	(3)	/* illegal addressing mode */
#define TARGET_ILL_ILLTRP	(4)	/* illegal trap */
#define TARGET_ILL_PRVOPC	(5)	/* privileged opcode */
#define TARGET_ILL_PRVREG	(6)	/* privileged register */
#define TARGET_ILL_COPROC	(7)	/* coprocessor error */
#define TARGET_ILL_BADSTK	(8)	/* internal stack error */

/*
 * SIGFPE si_codes
 */
#define TARGET_FPE_INTDIV      (1)  /* integer divide by zero */
#define TARGET_FPE_INTOVF      (2)  /* integer overflow */
#define TARGET_FPE_FLTDIV      (3)  /* floating point divide by zero */
#define TARGET_FPE_FLTOVF      (4)  /* floating point overflow */
#define TARGET_FPE_FLTUND      (5)  /* floating point underflow */
#define TARGET_FPE_FLTRES      (6)  /* floating point inexact result */
#define TARGET_FPE_FLTINV      (7)  /* floating point invalid operation */
#define TARGET_FPE_FLTSUB      (8)  /* subscript out of range */
#define TARGET_NSIGFPE         8

/*
 * SIGSEGV si_codes
 */
#define TARGET_SEGV_MAPERR     (1)  /* address not mapped to object */
#define TARGET_SEGV_ACCERR     (2)  /* invalid permissions for mapped object */

/*
 * SIGBUS si_codes
 */
#define TARGET_BUS_ADRALN       (1)	/* invalid address alignment */
#define TARGET_BUS_ADRERR       (2)	/* non-existant physical address */
#define TARGET_BUS_OBJERR       (3)	/* object specific hardware error */

/*
 * SIGTRAP si_codes
 */
#define TARGET_TRAP_BRKPT	(1)	/* process breakpoint */
#define TARGET_TRAP_TRACE	(2)	/* process trace trap */

#endif /* defined(TARGET_I386) || defined(TARGET_ARM) */

struct target_rlimit {
        target_ulong   rlim_cur;
        target_ulong   rlim_max;
};

struct target_pollfd {
    int fd;           /* file descriptor */
    short events;     /* requested events */
    short revents;    /* returned events */
};

/* virtual terminal ioctls */
#define TARGET_KIOCSOUND       0x4B2F	/* start sound generation (0 for off) */
#define TARGET_KDMKTONE	       0x4B30	/* generate tone */
#define TARGET_KDGKBTYPE       0x4b33
#define TARGET_KDGKBENT	       0x4B46	/* gets one entry in translation table */
#define TARGET_KDGKBSENT       0x4B48	/* gets one function key string entry */

#define TARGET_SIOCATMARK      0x8905

/* Networking ioctls */
#define TARGET_SIOCADDRT       0x890B          /* add routing table entry */
#define TARGET_SIOCDELRT       0x890C          /* delete routing table entry */
#define TARGET_SIOCGIFNAME     0x8910          /* get iface name               */
#define TARGET_SIOCSIFLINK     0x8911          /* set iface channel            */
#define TARGET_SIOCGIFCONF     0x8912          /* get iface list               */
#define TARGET_SIOCGIFFLAGS    0x8913          /* get flags                    */
#define TARGET_SIOCSIFFLAGS    0x8914          /* set flags                    */
#define TARGET_SIOCGIFADDR     0x8915          /* get PA address               */
#define TARGET_SIOCSIFADDR     0x8916          /* set PA address               */
#define TARGET_SIOCGIFDSTADDR  0x8917          /* get remote PA address        */
#define TARGET_SIOCSIFDSTADDR  0x8918          /* set remote PA address        */
#define TARGET_SIOCGIFBRDADDR  0x8919          /* get broadcast PA address     */
#define TARGET_SIOCSIFBRDADDR  0x891a          /* set broadcast PA address     */
#define TARGET_SIOCGIFNETMASK  0x891b          /* get network PA mask          */
#define TARGET_SIOCSIFNETMASK  0x891c          /* set network PA mask          */
#define TARGET_SIOCGIFMETRIC   0x891d          /* get metric                   */
#define TARGET_SIOCSIFMETRIC   0x891e          /* set metric                   */
#define TARGET_SIOCGIFMEM      0x891f          /* get memory address (BSD)     */
#define TARGET_SIOCSIFMEM      0x8920          /* set memory address (BSD)     */
#define TARGET_SIOCGIFMTU      0x8921          /* get MTU size                 */
#define TARGET_SIOCSIFMTU      0x8922          /* set MTU size                 */
#define TARGET_SIOCSIFHWADDR   0x8924          /* set hardware address (NI)    */
#define TARGET_SIOCGIFENCAP    0x8925          /* get/set slip encapsulation   */
#define TARGET_SIOCSIFENCAP    0x8926
#define TARGET_SIOCGIFHWADDR   0x8927          /* Get hardware address         */
#define TARGET_SIOCGIFSLAVE    0x8929          /* Driver slaving support       */
#define TARGET_SIOCSIFSLAVE    0x8930
#define TARGET_SIOCADDMULTI    0x8931          /* Multicast address lists      */
#define TARGET_SIOCDELMULTI    0x8932

/* Bridging control calls */
#define TARGET_SIOCGIFBR       0x8940          /* Bridging support             */
#define TARGET_SIOCSIFBR       0x8941          /* Set bridging options         */

#define TARGET_SIOCGIFTXQLEN   0x8942          /* Get the tx queue length      */
#define TARGET_SIOCSIFTXQLEN   0x8943          /* Set the tx queue length      */

/* ARP cache control calls. */
#define TARGET_OLD_SIOCDARP    0x8950          /* old delete ARP table entry   */
#define TARGET_OLD_SIOCGARP    0x8951          /* old get ARP table entry      */
#define TARGET_OLD_SIOCSARP    0x8952          /* old set ARP table entry      */
#define TARGET_SIOCDARP        0x8953          /* delete ARP table entry       */
#define TARGET_SIOCGARP        0x8954          /* get ARP table entry          */
#define TARGET_SIOCSARP        0x8955          /* set ARP table entry          */

/* RARP cache control calls. */
#define TARGET_SIOCDRARP       0x8960          /* delete RARP table entry      */
#define TARGET_SIOCGRARP       0x8961          /* get RARP table entry         */
#define TARGET_SIOCSRARP       0x8962          /* set RARP table entry         */

/* Driver configuration calls */
#define TARGET_SIOCGIFMAP      0x8970          /* Get device parameters        */
#define TARGET_SIOCSIFMAP      0x8971          /* Set device parameters        */

/* DLCI configuration calls */
#define TARGET_SIOCADDDLCI     0x8980          /* Create new DLCI device       */
#define TARGET_SIOCDELDLCI     0x8981          /* Delete DLCI device           */


/* From <linux/fs.h> */

#define TARGET_BLKROSET   TARGET_IO(0x12,93) /* set device read-only (0 = read-write) */
#define TARGET_BLKROGET   TARGET_IO(0x12,94) /* get read-only status (0 = read_write) */
#define TARGET_BLKRRPART  TARGET_IO(0x12,95) /* re-read partition table */
#define TARGET_BLKGETSIZE TARGET_IO(0x12,96) /* return device size /512 (long *arg) */
#define TARGET_BLKFLSBUF  TARGET_IO(0x12,97) /* flush buffer cache */
#define TARGET_BLKRASET   TARGET_IO(0x12,98) /* Set read ahead for block device */
#define TARGET_BLKRAGET   TARGET_IO(0x12,99) /* get current read ahead setting */
#define TARGET_BLKFRASET  TARGET_IO(0x12,100)/* set filesystem (mm/filemap.c) read-ahead */
#define TARGET_BLKFRAGET  TARGET_IO(0x12,101)/* get filesystem (mm/filemap.c) read-ahead */
#define TARGET_BLKSECTSET TARGET_IO(0x12,102)/* set max sectors per request (ll_rw_blk.c) */
#define TARGET_BLKSECTGET TARGET_IO(0x12,103)/* get max sectors per request (ll_rw_blk.c) */
#define TARGET_BLKSSZGET  TARGET_IO(0x12,104)/* get block device sector size */
/* A jump here: 108-111 have been used for various private purposes. */
#define TARGET_BLKBSZGET  TARGET_IOR(0x12,112,sizeof(int))
#define TARGET_BLKBSZSET  TARGET_IOW(0x12,113,sizeof(int))
#define TARGET_BLKGETSIZE64 TARGET_IOR(0x12,114,sizeof(uint64_t)) /* return device size in bytes (u64 *arg) */
#define TARGET_FIBMAP     TARGET_IO(0x00,1)  /* bmap access */
#define TARGET_FIGETBSZ   TARGET_IO(0x00,2)  /* get the block size used for bmap */

/* cdrom commands */
#define TARGET_CDROMPAUSE		0x5301 /* Pause Audio Operation */ 
#define TARGET_CDROMRESUME		0x5302 /* Resume paused Audio Operation */
#define TARGET_CDROMPLAYMSF		0x5303 /* Play Audio MSF (struct cdrom_msf) */
#define TARGET_CDROMPLAYTRKIND		0x5304 /* Play Audio Track/index 
                                           (struct cdrom_ti) */
#define TARGET_CDROMREADTOCHDR		0x5305 /* Read TOC header 
                                           (struct cdrom_tochdr) */
#define TARGET_CDROMREADTOCENTRY	0x5306 /* Read TOC entry 
                                           (struct cdrom_tocentry) */
#define TARGET_CDROMSTOP		0x5307 /* Stop the cdrom drive */
#define TARGET_CDROMSTART		0x5308 /* Start the cdrom drive */
#define TARGET_CDROMEJECT		0x5309 /* Ejects the cdrom media */
#define TARGET_CDROMVOLCTRL		0x530a /* Control output volume 
                                           (struct cdrom_volctrl) */
#define TARGET_CDROMSUBCHNL		0x530b /* Read subchannel data 
                                           (struct cdrom_subchnl) */
#define TARGET_CDROMREADMODE2		0x530c /* Read TARGET_CDROM mode 2 data (2336 Bytes) 
                                           (struct cdrom_read) */
#define TARGET_CDROMREADMODE1		0x530d /* Read TARGET_CDROM mode 1 data (2048 Bytes)
                                           (struct cdrom_read) */
#define TARGET_CDROMREADAUDIO		0x530e /* (struct cdrom_read_audio) */
#define TARGET_CDROMEJECT_SW		0x530f /* enable(1)/disable(0) auto-ejecting */
#define TARGET_CDROMMULTISESSION	0x5310 /* Obtain the start-of-last-session 
                                           address of multi session disks 
                                           (struct cdrom_multisession) */
#define TARGET_CDROM_GET_MCN		0x5311 /* Obtain the "Universal Product Code" 
                                           if available (struct cdrom_mcn) */
#define TARGET_CDROM_GET_UPC		TARGET_CDROM_GET_MCN  /* This one is depricated, 
                                          but here anyway for compatability */
#define TARGET_CDROMRESET		0x5312 /* hard-reset the drive */
#define TARGET_CDROMVOLREAD		0x5313 /* Get the drive's volume setting 
                                          (struct cdrom_volctrl) */
#define TARGET_CDROMREADRAW		0x5314	/* read data in raw mode (2352 Bytes)
                                           (struct cdrom_read) */
/* 
 * These ioctls are used only used in aztcd.c and optcd.c
 */
#define TARGET_CDROMREADCOOKED		0x5315	/* read data in cooked mode */
#define TARGET_CDROMSEEK		0x5316  /* seek msf address */
  
/*
 * This ioctl is only used by the scsi-cd driver.  
   It is for playing audio in logical block addressing mode.
 */
#define TARGET_CDROMPLAYBLK		0x5317	/* (struct cdrom_blk) */

/* 
 * These ioctls are only used in optcd.c
 */
#define TARGET_CDROMREADALL		0x5318	/* read all 2646 bytes */

/* 
 * These ioctls are (now) only in ide-cd.c for controlling 
 * drive spindown time.  They should be implemented in the
 * Uniform driver, via generic packet commands, GPCMD_MODE_SELECT_10,
 * GPCMD_MODE_SENSE_10 and the GPMODE_POWER_PAGE...
 *  -Erik
 */
#define TARGET_CDROMGETSPINDOWN        0x531d
#define TARGET_CDROMSETSPINDOWN        0x531e

/* 
 * These ioctls are implemented through the uniform CD-ROM driver
 * They _will_ be adopted by all CD-ROM drivers, when all the CD-ROM
 * drivers are eventually ported to the uniform CD-ROM driver interface.
 */
#define TARGET_CDROMCLOSETRAY		0x5319	/* pendant of CDROMEJECT */
#define TARGET_CDROM_SET_OPTIONS	0x5320  /* Set behavior options */
#define TARGET_CDROM_CLEAR_OPTIONS	0x5321  /* Clear behavior options */
#define TARGET_CDROM_SELECT_SPEED	0x5322  /* Set the CD-ROM speed */
#define TARGET_CDROM_SELECT_DISC	0x5323  /* Select disc (for juke-boxes) */
#define TARGET_CDROM_MEDIA_CHANGED	0x5325  /* Check is media changed  */
#define TARGET_CDROM_DRIVE_STATUS	0x5326  /* Get tray position, etc. */
#define TARGET_CDROM_DISC_STATUS	0x5327  /* Get disc type, etc. */
#define TARGET_CDROM_CHANGER_NSLOTS    0x5328  /* Get number of slots */
#define TARGET_CDROM_LOCKDOOR		0x5329  /* lock or unlock door */
#define TARGET_CDROM_DEBUG		0x5330	/* Turn debug messages on/off */
#define TARGET_CDROM_GET_CAPABILITY	0x5331	/* get capabilities */

/* Note that scsi/scsi_ioctl.h also uses 0x5382 - 0x5386.
 * Future CDROM ioctls should be kept below 0x537F
 */

/* This ioctl is only used by sbpcd at the moment */
#define TARGET_CDROMAUDIOBUFSIZ        0x5382	/* set the audio buffer size */
					/* conflict with SCSI_IOCTL_GET_IDLUN */

/* DVD-ROM Specific ioctls */
#define TARGET_DVD_READ_STRUCT		0x5390  /* Read structure */
#define TARGET_DVD_WRITE_STRUCT	0x5391  /* Write structure */
#define TARGET_DVD_AUTH		0x5392  /* Authentication */

#define TARGET_CDROM_SEND_PACKET	0x5393	/* send a packet to the drive */
#define TARGET_CDROM_NEXT_WRITABLE	0x5394	/* get next writable block */
#define TARGET_CDROM_LAST_WRITTEN	0x5395	/* get last block written on disc */

/* HD commands */

/* hd/ide ctl's that pass (arg) ptrs to user space are numbered 0x030n/0x031n */
#define TARGET_HDIO_GETGEO            0x0301  /* get device geometry */
#define TARGET_HDIO_GET_UNMASKINTR    0x0302  /* get current unmask setting */
#define TARGET_HDIO_GET_MULTCOUNT     0x0304  /* get current IDE blockmode setting */
#define TARGET_HDIO_GET_KEEPSETTINGS  0x0308  /* get keep-settings-on-reset flag */
#define TARGET_HDIO_GET_32BIT         0x0309  /* get current io_32bit setting */
#define TARGET_HDIO_GET_NOWERR        0x030a  /* get ignore-write-error flag */
#define TARGET_HDIO_GET_DMA           0x030b  /* get use-dma flag */
#define TARGET_HDIO_GET_IDENTITY      0x030d  /* get IDE identification info */
#define TARGET_HDIO_DRIVE_CMD         0x031f  /* execute a special drive command */

/* hd/ide ctl's that pass (arg) non-ptr values are numbered 0x032n/0x033n */
#define TARGET_HDIO_SET_MULTCOUNT     0x0321  /* change IDE blockmode */
#define TARGET_HDIO_SET_UNMASKINTR    0x0322  /* permit other irqs during I/O */
#define TARGET_HDIO_SET_KEEPSETTINGS  0x0323  /* keep ioctl settings on reset */
#define TARGET_HDIO_SET_32BIT         0x0324  /* change io_32bit flags */
#define TARGET_HDIO_SET_NOWERR        0x0325  /* change ignore-write-error flag */
#define TARGET_HDIO_SET_DMA           0x0326  /* change use-dma flag */
#define TARGET_HDIO_SET_PIO_MODE      0x0327  /* reconfig interface to new speed */


/* from asm/termbits.h */

#define TARGET_NCC 8
struct target_termio {
	unsigned short c_iflag;		/* input mode flags */
	unsigned short c_oflag;		/* output mode flags */
	unsigned short c_cflag;		/* control mode flags */
	unsigned short c_lflag;		/* local mode flags */
	unsigned char c_line;		/* line discipline */
	unsigned char c_cc[TARGET_NCC];	/* control characters */
};

struct target_winsize {
	unsigned short ws_row;
	unsigned short ws_col;
	unsigned short ws_xpixel;
	unsigned short ws_ypixel;
};

#include "termbits.h"

#define TARGET_MAP_SHARED	0x01		/* Share changes */
#define TARGET_MAP_PRIVATE	0x02		/* Changes are private */
#define TARGET_MAP_TYPE	0x0f		/* Mask for type of mapping */
#define TARGET_MAP_FIXED	0x10		/* Interpret addr exactly */
#define TARGET_MAP_ANONYMOUS	0x20		/* don't use a file */

#define TARGET_MAP_GROWSDOWN	0x0100		/* stack-like segment */
#define TARGET_MAP_DENYWRITE	0x0800		/* ETXTBSY */
#define TARGET_MAP_EXECUTABLE	0x1000		/* mark it as an executable */
#define TARGET_MAP_LOCKED	0x2000		/* pages are locked */
#define TARGET_MAP_NORESERVE	0x4000		/* don't check for reservations */

#if defined(TARGET_I386) || defined(TARGET_ARM)
struct target_stat {
	unsigned short st_dev;
	unsigned short __pad1;
	target_ulong st_ino;
	unsigned short st_mode;
	unsigned short st_nlink;
	unsigned short st_uid;
	unsigned short st_gid;
	unsigned short st_rdev;
	unsigned short __pad2;
	target_ulong  st_size;
	target_ulong  st_blksize;
	target_ulong  st_blocks;
	target_ulong  target_st_atime;
	target_ulong  __unused1;
	target_ulong  target_st_mtime;
	target_ulong  __unused2;
	target_ulong  target_st_ctime;
	target_ulong  __unused3;
	target_ulong  __unused4;
	target_ulong  __unused5;
};

/* This matches struct stat64 in glibc2.1, hence the absolutely
 * insane amounts of padding around dev_t's.
 */
struct target_stat64 {
	unsigned short	st_dev;
	unsigned char	__pad0[10];

#define TARGET_STAT64_HAS_BROKEN_ST_INO	1
	target_ulong	__st_ino;

	unsigned int	st_mode;
	unsigned int	st_nlink;

	target_ulong	st_uid;
	target_ulong	st_gid;

	unsigned short	st_rdev;
	unsigned char	__pad3[10];

	long long	st_size;
	target_ulong	st_blksize;

	target_ulong	st_blocks;	/* Number 512-byte blocks allocated. */
	target_ulong	__pad4;		/* future possible st_blocks high bits */

	target_ulong	target_st_atime;
	target_ulong	__pad5;

	target_ulong	target_st_mtime;
	target_ulong	__pad6;

	target_ulong	target_st_ctime;
	target_ulong	__pad7;		/* will be high 32 bits of ctime someday */

	unsigned long long	st_ino;
} __attribute__((packed));

#elif defined(TARGET_SPARC)

struct target_stat {
	unsigned short	st_dev;
	target_ulong	st_ino;
	unsigned short	st_mode;
	short		st_nlink;
	unsigned short	st_uid;
	unsigned short	st_gid;
	unsigned short	st_rdev;
	target_long	st_size;
	target_long	target_st_atime;
	target_ulong	__unused1;
	target_long	target_st_mtime;
	target_ulong	__unused2;
	target_long	target_st_ctime;
	target_ulong	__unused3;
	target_long	st_blksize;
	target_long	st_blocks;
	target_ulong	__unused4[2];
};

struct target_stat64 {
	unsigned char	__pad0[6];
	unsigned short	st_dev;

	uint64_t st_ino;

	unsigned int	st_mode;
	unsigned int	st_nlink;

	unsigned int	st_uid;
	unsigned int	st_gid;

	unsigned char	__pad2[6];
	unsigned short	st_rdev;

	unsigned char	__pad3[8];

        int64_t	st_size;
	unsigned int	st_blksize;

	unsigned char	__pad4[8];
	unsigned int	st_blocks;

	unsigned int	target_st_atime;
	unsigned int	__unused1;

	unsigned int	target_st_mtime;
	unsigned int	__unused2;

	unsigned int	target_st_ctime;
	unsigned int	__unused3;

	unsigned int	__unused4;
	unsigned int	__unused5;
};

#elif defined(TARGET_PPC)

struct target_stat {
	unsigned short st_dev;
	target_ulong st_ino;
	unsigned int st_mode;
	unsigned short st_nlink;
	unsigned int st_uid;
	unsigned int st_gid;
	unsigned short st_rdev;
	target_ulong  st_size;
	target_ulong  st_blksize;
	target_ulong  st_blocks;
	target_ulong  target_st_atime;
	target_ulong  __unused1;
	target_ulong  target_st_mtime;
	target_ulong  __unused2;
	target_ulong  target_st_ctime;
	target_ulong  __unused3;
	target_ulong  __unused4;
	target_ulong  __unused5;
};

struct target_stat64 {
	unsigned long long st_dev;
        unsigned long long st_ino;
	unsigned int st_mode;
	unsigned int st_nlink;
	unsigned int st_uid;
	unsigned int st_gid;
	unsigned long long st_rdev;
	long long pad0;
	long long st_size;
	target_ulong	st_blksize;
	target_ulong	pad1;
	long long	st_blocks;	/* Number 512-byte blocks allocated. */
	target_ulong	target_st_atime;
        target_ulong    target_st_atime_nsec;
	target_ulong	target_st_mtime;
        target_ulong    target_st_mtime_nsec;
	target_ulong	target_st_ctime;
        target_ulong    target_st_ctime_nsec;
        target_ulong    __unused4;
        target_ulong    __unused5;
};

#endif /* defined(TARGET_PPC) */

#define TARGET_F_DUPFD         0       /* dup */
#define TARGET_F_GETFD         1       /* get close_on_exec */
#define TARGET_F_SETFD         2       /* set/clear close_on_exec */
#define TARGET_F_GETFL         3       /* get file->f_flags */
#define TARGET_F_SETFL         4       /* set file->f_flags */

#if defined(TARGET_ALPHA)
#define TARGET_F_GETLK         7
#define TARGET_F_SETLK         8
#define TARGET_F_SETLKW        9
#define TARGET_F_SETOWN        5       /*  for sockets. */
#define TARGET_F_GETOWN        6       /*  for sockets. */
#else
#define TARGET_F_GETLK         5
#define TARGET_F_SETLK         6
#define TARGET_F_SETLKW        7
#define TARGET_F_SETOWN        8       /*  for sockets. */
#define TARGET_F_GETOWN        9       /*  for sockets. */
#endif

#define TARGET_F_SETSIG        10      /*  for sockets. */
#define TARGET_F_GETSIG        11      /*  for sockets. */

#define TARGET_F_GETLK64       12      /*  using 'struct flock64' */
#define TARGET_F_SETLK64       13
#define TARGET_F_SETLKW64      14

#if defined (TARGET_ARM)
#define TARGET_O_ACCMODE          0003
#define TARGET_O_RDONLY             00
#define TARGET_O_WRONLY             01
#define TARGET_O_RDWR               02
#define TARGET_O_CREAT            0100 /* not fcntl */
#define TARGET_O_EXCL             0200 /* not fcntl */
#define TARGET_O_NOCTTY           0400 /* not fcntl */
#define TARGET_O_TRUNC           01000 /* not fcntl */
#define TARGET_O_APPEND          02000
#define TARGET_O_NONBLOCK        04000
#define TARGET_O_NDELAY        O_NONBLOCK
#define TARGET_O_SYNC           010000
#define TARGET_FASYNC           020000 /* fcntl, for BSD compatibility */
#define TARGET_O_DIRECTORY      040000 /* must be a directory */
#define TARGET_O_NOFOLLOW      0100000 /* don't follow links */
#define TARGET_O_DIRECT        0200000 /* direct disk access hint */
#define TARGET_O_LARGEFILE     0400000
#elif defined (TARGET_PPC)
#define TARGET_O_ACCMODE          0003
#define TARGET_O_RDONLY             00
#define TARGET_O_WRONLY             01
#define TARGET_O_RDWR               02
#define TARGET_O_CREAT            0100 /* not fcntl */
#define TARGET_O_EXCL             0200 /* not fcntl */
#define TARGET_O_NOCTTY           0400 /* not fcntl */
#define TARGET_O_TRUNC           01000 /* not fcntl */
#define TARGET_O_APPEND          02000
#define TARGET_O_NONBLOCK        04000
#define TARGET_O_NDELAY        O_NONBLOCK
#define TARGET_O_SYNC           010000
#define TARGET_FASYNC           020000 /* fcntl, for BSD compatibility */
#define TARGET_O_DIRECTORY      040000 /* must be a directory */
#define TARGET_O_NOFOLLOW      0100000 /* don't follow links */
#define TARGET_O_LARGEFILE     0200000
#define TARGET_O_DIRECT        0400000 /* direct disk access hint */
#else
#define TARGET_O_ACCMODE          0003
#define TARGET_O_RDONLY             00
#define TARGET_O_WRONLY             01
#define TARGET_O_RDWR               02
#define TARGET_O_CREAT            0100 /* not fcntl */
#define TARGET_O_EXCL             0200 /* not fcntl */
#define TARGET_O_NOCTTY           0400 /* not fcntl */
#define TARGET_O_TRUNC           01000 /* not fcntl */
#define TARGET_O_APPEND          02000
#define TARGET_O_NONBLOCK        04000
#define TARGET_O_NDELAY        O_NONBLOCK
#define TARGET_O_SYNC           010000
#define TARGET_FASYNC           020000 /* fcntl, for BSD compatibility */
#define TARGET_O_DIRECT         040000 /* direct disk access hint */
#define TARGET_O_LARGEFILE     0100000
#define TARGET_O_DIRECTORY     0200000 /* must be a directory */
#define TARGET_O_NOFOLLOW      0400000 /* don't follow links */
#endif

struct target_flock {
	short l_type;
	short l_whence;
	target_ulong l_start;
	target_ulong l_len;
	int l_pid;
};

struct target_flock64 {
	short  l_type;
	short  l_whence;
	unsigned long long l_start;
	unsigned long long l_len;
	int  l_pid;
};


/* soundcard defines */
/* XXX: convert them all to arch indepedent entries */
#define TARGET_SNDCTL_COPR_HALT           TARGET_IOWR('C',  7, int);
#define TARGET_SNDCTL_COPR_LOAD           0xcfb04301
#define TARGET_SNDCTL_COPR_RCODE          0xc0144303
#define TARGET_SNDCTL_COPR_RCVMSG         0x8fa44309
#define TARGET_SNDCTL_COPR_RDATA          0xc0144302
#define TARGET_SNDCTL_COPR_RESET          0x00004300
#define TARGET_SNDCTL_COPR_RUN            0xc0144306
#define TARGET_SNDCTL_COPR_SENDMSG        0xcfa44308
#define TARGET_SNDCTL_COPR_WCODE          0x40144305
#define TARGET_SNDCTL_COPR_WDATA          0x40144304
#define TARGET_SNDCTL_DSP_RESET           TARGET_IO('P', 0)
#define TARGET_SNDCTL_DSP_SYNC            TARGET_IO('P', 1)
#define TARGET_SNDCTL_DSP_SPEED           TARGET_IOWR('P', 2, int)
#define TARGET_SNDCTL_DSP_STEREO          TARGET_IOWR('P', 3, int)
#define TARGET_SNDCTL_DSP_GETBLKSIZE      TARGET_IOWR('P', 4, int)
#define TARGET_SNDCTL_DSP_SETFMT          TARGET_IOWR('P', 5, int)
#define TARGET_SNDCTL_DSP_CHANNELS        TARGET_IOWR('P', 6, int)
#define TARGET_SOUND_PCM_WRITE_FILTER     TARGET_IOWR('P', 7, int)
#define TARGET_SNDCTL_DSP_POST            TARGET_IO('P', 8)
#define TARGET_SNDCTL_DSP_SUBDIVIDE       TARGET_IOWR('P', 9, int)
#define TARGET_SNDCTL_DSP_SETFRAGMENT     TARGET_IOWR('P',10, int)
#define TARGET_SNDCTL_DSP_GETFMTS         TARGET_IOR('P', 11, int)
#define TARGET_SNDCTL_DSP_GETOSPACE       TARGET_IORU('P',12)
#define TARGET_SNDCTL_DSP_GETISPACE       TARGET_IORU('P',13)
#define TARGET_SNDCTL_DSP_GETCAPS         TARGET_IOR('P', 15, int)
#define TARGET_SNDCTL_DSP_GETTRIGGER      TARGET_IOR('P',16, int)
#define TARGET_SNDCTL_DSP_GETIPTR         TARGET_IORU('P',17)
#define TARGET_SNDCTL_DSP_GETOPTR         TARGET_IORU('P',18)
#define TARGET_SNDCTL_DSP_MAPINBUF        0x80085013
#define TARGET_SNDCTL_DSP_MAPOUTBUF       0x80085014
#define TARGET_SNDCTL_DSP_NONBLOCK        0x0000500e
#define TARGET_SNDCTL_DSP_SAMPLESIZE      0xc0045005
#define TARGET_SNDCTL_DSP_SETDUPLEX       0x00005016
#define TARGET_SNDCTL_DSP_SETSYNCRO       0x00005015
#define TARGET_SNDCTL_DSP_SETTRIGGER      0x40045010
#define TARGET_SNDCTL_FM_4OP_ENABLE       0x4004510f
#define TARGET_SNDCTL_FM_LOAD_INSTR       0x40285107
#define TARGET_SNDCTL_MIDI_INFO           0xc074510c
#define TARGET_SNDCTL_MIDI_MPUCMD         0xc0216d02
#define TARGET_SNDCTL_MIDI_MPUMODE        0xc0046d01
#define TARGET_SNDCTL_MIDI_PRETIME        0xc0046d00
#define TARGET_SNDCTL_PMGR_ACCESS         0xcfb85110
#define TARGET_SNDCTL_PMGR_IFACE          0xcfb85001
#define TARGET_SNDCTL_SEQ_CTRLRATE        0xc0045103
#define TARGET_SNDCTL_SEQ_GETINCOUNT      0x80045105
#define TARGET_SNDCTL_SEQ_GETOUTCOUNT     0x80045104
#define TARGET_SNDCTL_SEQ_NRMIDIS         0x8004510b
#define TARGET_SNDCTL_SEQ_NRSYNTHS        0x8004510a
#define TARGET_SNDCTL_SEQ_OUTOFBAND       0x40085112
#define TARGET_SNDCTL_SEQ_PANIC           0x00005111
#define TARGET_SNDCTL_SEQ_PERCMODE        0x40045106
#define TARGET_SNDCTL_SEQ_RESET           0x00005100
#define TARGET_SNDCTL_SEQ_RESETSAMPLES    0x40045109
#define TARGET_SNDCTL_SEQ_SYNC            0x00005101
#define TARGET_SNDCTL_SEQ_TESTMIDI        0x40045108
#define TARGET_SNDCTL_SEQ_THRESHOLD       0x4004510d
#define TARGET_SNDCTL_SEQ_TRESHOLD        0x4004510d
#define TARGET_SNDCTL_SYNTH_INFO          0xc08c5102
#define TARGET_SNDCTL_SYNTH_MEMAVL        0xc004510e
#define TARGET_SNDCTL_TMR_CONTINUE        0x00005404
#define TARGET_SNDCTL_TMR_METRONOME       0x40045407
#define TARGET_SNDCTL_TMR_SELECT          0x40045408
#define TARGET_SNDCTL_TMR_SOURCE          0xc0045406
#define TARGET_SNDCTL_TMR_START           0x00005402
#define TARGET_SNDCTL_TMR_STOP            0x00005403
#define TARGET_SNDCTL_TMR_TEMPO           0xc0045405
#define TARGET_SNDCTL_TMR_TIMEBASE        0xc0045401
#define TARGET_SOUND_PCM_READ_RATE        0x80045002
#define TARGET_SOUND_PCM_READ_CHANNELS    0x80045006
#define TARGET_SOUND_PCM_READ_BITS        0x80045005
#define TARGET_SOUND_PCM_READ_FILTER      0x80045007
#define TARGET_SOUND_MIXER_INFO           TARGET_IOR ('M', 101, mixer_info)
#define TARGET_SOUND_MIXER_ACCESS         0xc0804d66
#define TARGET_SOUND_MIXER_PRIVATE1       TARGET_IOWR('M', 111, int)
#define TARGET_SOUND_MIXER_PRIVATE2       TARGET_IOWR('M', 112, int)
#define TARGET_SOUND_MIXER_PRIVATE3       TARGET_IOWR('M', 113, int)
#define TARGET_SOUND_MIXER_PRIVATE4       TARGET_IOWR('M', 114, int)
#define TARGET_SOUND_MIXER_PRIVATE5       TARGET_IOWR('M', 115, int)

#define TARGET_MIXER_READ(dev)	TARGET_IOR('M', dev, int)

#define TARGET_SOUND_MIXER_READ_VOLUME		TARGET_MIXER_READ(SOUND_MIXER_VOLUME)
#define TARGET_SOUND_MIXER_READ_BASS		TARGET_MIXER_READ(SOUND_MIXER_BASS)
#define TARGET_SOUND_MIXER_READ_TREBLE		TARGET_MIXER_READ(SOUND_MIXER_TREBLE)
#define TARGET_SOUND_MIXER_READ_SYNTH		TARGET_MIXER_READ(SOUND_MIXER_SYNTH)
#define TARGET_SOUND_MIXER_READ_PCM		TARGET_MIXER_READ(SOUND_MIXER_PCM)
#define TARGET_SOUND_MIXER_READ_SPEAKER	        TARGET_MIXER_READ(SOUND_MIXER_SPEAKER)
#define TARGET_SOUND_MIXER_READ_LINE		TARGET_MIXER_READ(SOUND_MIXER_LINE)
#define TARGET_SOUND_MIXER_READ_MIC		TARGET_MIXER_READ(SOUND_MIXER_MIC)
#define TARGET_SOUND_MIXER_READ_CD		TARGET_MIXER_READ(SOUND_MIXER_CD)
#define TARGET_SOUND_MIXER_READ_IMIX		TARGET_MIXER_READ(SOUND_MIXER_IMIX)
#define TARGET_SOUND_MIXER_READ_ALTPCM		TARGET_MIXER_READ(SOUND_MIXER_ALTPCM)
#define TARGET_SOUND_MIXER_READ_RECLEV		TARGET_MIXER_READ(SOUND_MIXER_RECLEV)
#define TARGET_SOUND_MIXER_READ_IGAIN		TARGET_MIXER_READ(SOUND_MIXER_IGAIN)
#define TARGET_SOUND_MIXER_READ_OGAIN		TARGET_MIXER_READ(SOUND_MIXER_OGAIN)
#define TARGET_SOUND_MIXER_READ_LINE1		TARGET_MIXER_READ(SOUND_MIXER_LINE1)
#define TARGET_SOUND_MIXER_READ_LINE2		TARGET_MIXER_READ(SOUND_MIXER_LINE2)
#define TARGET_SOUND_MIXER_READ_LINE3		TARGET_MIXER_READ(SOUND_MIXER_LINE3)

/* Obsolete macros */
#define TARGET_SOUND_MIXER_READ_MUTE		TARGET_MIXER_READ(SOUND_MIXER_MUTE)
#define TARGET_SOUND_MIXER_READ_ENHANCE	        TARGET_MIXER_READ(SOUND_MIXER_ENHANCE)
#define TARGET_SOUND_MIXER_READ_LOUD		TARGET_MIXER_READ(SOUND_MIXER_LOUD)

#define TARGET_SOUND_MIXER_READ_RECSRC		TARGET_MIXER_READ(SOUND_MIXER_RECSRC)
#define TARGET_SOUND_MIXER_READ_DEVMASK	        TARGET_MIXER_READ(SOUND_MIXER_DEVMASK)
#define TARGET_SOUND_MIXER_READ_RECMASK	        TARGET_MIXER_READ(SOUND_MIXER_RECMASK)
#define TARGET_SOUND_MIXER_READ_STEREODEVS	TARGET_MIXER_READ(SOUND_MIXER_STEREODEVS)
#define TARGET_SOUND_MIXER_READ_CAPS		TARGET_MIXER_READ(SOUND_MIXER_CAPS)

#define TARGET_MIXER_WRITE(dev)		TARGET_IOWR('M', dev, int)

#define TARGET_SOUND_MIXER_WRITE_VOLUME	TARGET_MIXER_WRITE(SOUND_MIXER_VOLUME)
#define TARGET_SOUND_MIXER_WRITE_BASS		TARGET_MIXER_WRITE(SOUND_MIXER_BASS)
#define TARGET_SOUND_MIXER_WRITE_TREBLE	TARGET_MIXER_WRITE(SOUND_MIXER_TREBLE)
#define TARGET_SOUND_MIXER_WRITE_SYNTH		TARGET_MIXER_WRITE(SOUND_MIXER_SYNTH)
#define TARGET_SOUND_MIXER_WRITE_PCM		TARGET_MIXER_WRITE(SOUND_MIXER_PCM)
#define TARGET_SOUND_MIXER_WRITE_SPEAKER	TARGET_MIXER_WRITE(SOUND_MIXER_SPEAKER)
#define TARGET_SOUND_MIXER_WRITE_LINE		TARGET_MIXER_WRITE(SOUND_MIXER_LINE)
#define TARGET_SOUND_MIXER_WRITE_MIC		TARGET_MIXER_WRITE(SOUND_MIXER_MIC)
#define TARGET_SOUND_MIXER_WRITE_CD		TARGET_MIXER_WRITE(SOUND_MIXER_CD)
#define TARGET_SOUND_MIXER_WRITE_IMIX		TARGET_MIXER_WRITE(SOUND_MIXER_IMIX)
#define TARGET_SOUND_MIXER_WRITE_ALTPCM	TARGET_MIXER_WRITE(SOUND_MIXER_ALTPCM)
#define TARGET_SOUND_MIXER_WRITE_RECLEV	TARGET_MIXER_WRITE(SOUND_MIXER_RECLEV)
#define TARGET_SOUND_MIXER_WRITE_IGAIN		TARGET_MIXER_WRITE(SOUND_MIXER_IGAIN)
#define TARGET_SOUND_MIXER_WRITE_OGAIN		TARGET_MIXER_WRITE(SOUND_MIXER_OGAIN)
#define TARGET_SOUND_MIXER_WRITE_LINE1		TARGET_MIXER_WRITE(SOUND_MIXER_LINE1)
#define TARGET_SOUND_MIXER_WRITE_LINE2		TARGET_MIXER_WRITE(SOUND_MIXER_LINE2)
#define TARGET_SOUND_MIXER_WRITE_LINE3		TARGET_MIXER_WRITE(SOUND_MIXER_LINE3)

/* Obsolete macros */
#define TARGET_SOUND_MIXER_WRITE_MUTE		TARGET_MIXER_WRITE(SOUND_MIXER_MUTE)
#define TARGET_SOUND_MIXER_WRITE_ENHANCE	TARGET_MIXER_WRITE(SOUND_MIXER_ENHANCE)
#define TARGET_SOUND_MIXER_WRITE_LOUD		TARGET_MIXER_WRITE(SOUND_MIXER_LOUD)

#define TARGET_SOUND_MIXER_WRITE_RECSRC	TARGET_MIXER_WRITE(SOUND_MIXER_RECSRC)

/* vfat ioctls */
#define TARGET_VFAT_IOCTL_READDIR_BOTH    TARGET_IORU('r', 1)
#define TARGET_VFAT_IOCTL_READDIR_SHORT   TARGET_IORU('r', 2)

struct target_sysinfo {
    target_long uptime;             /* Seconds since boot */
    target_ulong loads[3];          /* 1, 5, and 15 minute load averages */
    target_ulong totalram;          /* Total usable main memory size */
    target_ulong freeram;           /* Available memory size */
    target_ulong sharedram;         /* Amount of shared memory */
    target_ulong bufferram;         /* Memory used by buffers */
    target_ulong totalswap;         /* Total swap space size */
    target_ulong freeswap;          /* swap space still available */
    unsigned short procs;           /* Number of current processes */
    unsigned short pad;             /* explicit padding for m68k */
    target_ulong totalhigh;         /* Total high memory size */
    target_ulong freehigh;          /* Available high memory size */
    unsigned int mem_unit;          /* Memory unit size in bytes */
    char _f[20-2*sizeof(target_long)-sizeof(int)]; /* Padding: libc5 uses this.. */
};
