#define TARGET_NR_exit                 1 /* Common                                      */
#define TARGET_NR_fork                 2 /* Common                                      */
#define TARGET_NR_read                 3 /* Common                                      */
#define TARGET_NR_write                4 /* Common                                      */
#define TARGET_NR_open                 5 /* Common                                      */
#define TARGET_NR_close                6 /* Common                                      */
#define TARGET_NR_wait4                7 /* Common                                      */
#define TARGET_NR_creat                8 /* Common                                      */
#define TARGET_NR_link                 9 /* Common                                      */
#define TARGET_NR_unlink              10 /* Common                                      */
#define TARGET_NR_execv               11 /* SunOS Specific                              */
#define TARGET_NR_chdir               12 /* Common                                      */
#define TARGET_NR_chown		 13 /* Common					   */
#define TARGET_NR_mknod               14 /* Common                                      */
#define TARGET_NR_chmod               15 /* Common                                      */
#define TARGET_NR_lchown              16 /* Common                                      */
#define TARGET_NR_brk                 17 /* Common                                      */
#define TARGET_NR_perfctr             18 /* Performance counter operations              */
#define TARGET_NR_lseek               19 /* Common                                      */
#define TARGET_NR_getpid              20 /* Common                                      */
#define TARGET_NR_capget		 21 /* Linux Specific				   */
#define TARGET_NR_capset		 22 /* Linux Specific				   */
#define TARGET_NR_setuid              23 /* Implemented via setreuid in SunOS           */
#define TARGET_NR_getuid              24 /* Common                                      */
#define TARGET_NR_ptrace              26 /* Common                                      */
#define TARGET_NR_alarm               27 /* Implemented via setitimer in SunOS          */
#define TARGET_NR_sigaltstack	 28 /* Common					   */
#define TARGET_NR_pause               29 /* Is sigblock(0)->sigpause() in SunOS         */
#define TARGET_NR_utime               30 /* Implemented via utimes() under SunOS        */
#define TARGET_NR_lchown32            31 /* Linux sparc32 specific                      */
#define TARGET_NR_fchown32            32 /* Linux sparc32 specific                      */
#define TARGET_NR_access              33 /* Common                                      */
#define TARGET_NR_nice                34 /* Implemented via get/setpriority() in SunOS  */
#define TARGET_NR_chown32             35 /* Linux sparc32 specific                      */
#define TARGET_NR_sync                36 /* Common                                      */
#define TARGET_NR_kill                37 /* Common                                      */
#define TARGET_NR_stat                38 /* Common                                      */
#define TARGET_NR_sendfile		 39 /* Linux Specific				   */
#define TARGET_NR_lstat               40 /* Common                                      */
#define TARGET_NR_dup                 41 /* Common                                      */
#define TARGET_NR_pipe                42 /* Common                                      */
#define TARGET_NR_times               43 /* Implemented via getrusage() in SunOS        */
#define TARGET_NR_getuid32            44 /* Linux sparc32 specific                      */
#define TARGET_NR_umount2             45 /* Linux Specific                              */
#define TARGET_NR_setgid              46 /* Implemented via setregid() in SunOS         */
#define TARGET_NR_getgid              47 /* Common                                      */
#define TARGET_NR_signal              48 /* Implemented via sigvec() in SunOS           */
#define TARGET_NR_geteuid             49 /* SunOS calls getuid()                        */
#define TARGET_NR_getegid             50 /* SunOS calls getgid()                        */
#define TARGET_NR_acct                51 /* Common                                      */
#define TARGET_NR_getgid32            53 /* Linux sparc32 specific                      */
#define TARGET_NR_ioctl               54 /* Common                                      */
#define TARGET_NR_reboot              55 /* Common                                      */
#define TARGET_NR_mmap2		 56 /* Linux sparc32 Specific			   */
#define TARGET_NR_symlink             57 /* Common                                      */
#define TARGET_NR_readlink            58 /* Common                                      */
#define TARGET_NR_execve              59 /* Common                                      */
#define TARGET_NR_umask               60 /* Common                                      */
#define TARGET_NR_chroot              61 /* Common                                      */
#define TARGET_NR_fstat               62 /* Common                                      */
#define TARGET_NR_fstat64		 63 /* Linux sparc32 Specific			   */
#define TARGET_NR_getpagesize         64 /* Common                                      */
#define TARGET_NR_msync               65 /* Common in newer 1.3.x revs...               */
#define TARGET_NR_vfork               66 /* Common                                      */
#define TARGET_NR_pread               67 /* Linux Specific                              */
#define TARGET_NR_pwrite              68 /* Linux Specific                              */
#define TARGET_NR_geteuid32           69 /* Linux sparc32, sbrk under SunOS             */
#define TARGET_NR_getegid32           70 /* Linux sparc32, sstk under SunOS             */
#define TARGET_NR_mmap                71 /* Common                                      */
#define TARGET_NR_setreuid32          72 /* Linux sparc32, vadvise under SunOS          */
#define TARGET_NR_munmap              73 /* Common                                      */
#define TARGET_NR_mprotect            74 /* Common                                      */
#define TARGET_NR_madvise             75 /* Common                                      */
#define TARGET_NR_vhangup             76 /* Common                                      */
#define TARGET_NR_truncate64		 77 /* Linux sparc32 Specific			   */
#define TARGET_NR_mincore             78 /* Common                                      */
#define TARGET_NR_getgroups           79 /* Common                                      */
#define TARGET_NR_setgroups           80 /* Common                                      */
#define TARGET_NR_getpgrp             81 /* Common                                      */
#define TARGET_NR_setgroups32         82 /* Linux sparc32, setpgrp under SunOS          */
#define TARGET_NR_setitimer           83 /* Common                                      */
#define TARGET_NR_ftruncate64	 84 /* Linux sparc32 Specific			   */
#define TARGET_NR_swapon              85 /* Common                                      */
#define TARGET_NR_getitimer           86 /* Common                                      */
#define TARGET_NR_setuid32            87 /* Linux sparc32, gethostname under SunOS      */
#define TARGET_NR_sethostname         88 /* Common                                      */
#define TARGET_NR_setgid32            89 /* Linux sparc32, getdtablesize under SunOS    */
#define TARGET_NR_dup2                90 /* Common                                      */
#define TARGET_NR_setfsuid32          91 /* Linux sparc32, getdopt under SunOS          */
#define TARGET_NR_fcntl               92 /* Common                                      */
#define TARGET_NR_select              93 /* Common                                      */
#define TARGET_NR_setfsgid32          94 /* Linux sparc32, setdopt under SunOS          */
#define TARGET_NR_fsync               95 /* Common                                      */
#define TARGET_NR_setpriority         96 /* Common                                      */
#define TARGET_NR_socket              97 /* Common                                      */
#define TARGET_NR_connect             98 /* Common                                      */
#define TARGET_NR_accept              99 /* Common                                      */
#define TARGET_NR_getpriority        100 /* Common                                      */
#define TARGET_NR_rt_sigreturn       101 /* Linux Specific                              */
#define TARGET_NR_rt_sigaction       102 /* Linux Specific                              */
#define TARGET_NR_rt_sigprocmask     103 /* Linux Specific                              */
#define TARGET_NR_rt_sigpending      104 /* Linux Specific                              */
#define TARGET_NR_rt_sigtimedwait    105 /* Linux Specific                              */
#define TARGET_NR_rt_sigqueueinfo    106 /* Linux Specific                              */
#define TARGET_NR_rt_sigsuspend      107 /* Linux Specific                              */
#define TARGET_NR_setresuid32        108 /* Linux Specific, sigvec under SunOS	   */
#define TARGET_NR_getresuid32        109 /* Linux Specific, sigblock under SunOS	   */
#define TARGET_NR_setresgid32        110 /* Linux Specific, sigsetmask under SunOS	   */
#define TARGET_NR_getresgid32        111 /* Linux Specific, sigpause under SunOS	   */
#define TARGET_NR_setregid32         112 /* Linux sparc32, sigstack under SunOS         */
#define TARGET_NR_recvmsg            113 /* Common                                      */
#define TARGET_NR_sendmsg            114 /* Common                                      */
#define TARGET_NR_getgroups32        115 /* Linux sparc32, vtrace under SunOS           */
#define TARGET_NR_gettimeofday       116 /* Common                                      */
#define TARGET_NR_getrusage          117 /* Common                                      */
#define TARGET_NR_getsockopt         118 /* Common                                      */
#define TARGET_NR_getcwd		119 /* Linux Specific				   */
#define TARGET_NR_readv              120 /* Common                                      */
#define TARGET_NR_writev             121 /* Common                                      */
#define TARGET_NR_settimeofday       122 /* Common                                      */
#define TARGET_NR_fchown             123 /* Common                                      */
#define TARGET_NR_fchmod             124 /* Common                                      */
#define TARGET_NR_recvfrom           125 /* Common                                      */
#define TARGET_NR_setreuid           126 /* Common                                      */
#define TARGET_NR_setregid           127 /* Common                                      */
#define TARGET_NR_rename             128 /* Common                                      */
#define TARGET_NR_truncate           129 /* Common                                      */
#define TARGET_NR_ftruncate          130 /* Common                                      */
#define TARGET_NR_flock              131 /* Common                                      */
#define TARGET_NR_lstat64		132 /* Linux sparc32 Specific			   */
#define TARGET_NR_sendto             133 /* Common                                      */
#define TARGET_NR_shutdown           134 /* Common                                      */
#define TARGET_NR_socketpair         135 /* Common                                      */
#define TARGET_NR_mkdir              136 /* Common                                      */
#define TARGET_NR_rmdir              137 /* Common                                      */
#define TARGET_NR_utimes             138 /* SunOS Specific                              */
#define TARGET_NR_stat64		139 /* Linux sparc32 Specific			   */
#define TARGET_NR_getpeername        141 /* Common                                      */
#define TARGET_NR_gettid             143 /* ENOSYS under SunOS                          */
#define TARGET_NR_getrlimit          144 /* Common                                      */
#define TARGET_NR_setrlimit          145 /* Common                                      */
#define TARGET_NR_pivot_root		146 /* Linux Specific, killpg under SunOS          */
#define TARGET_NR_prctl		147 /* ENOSYS under SunOS                          */
#define TARGET_NR_pciconfig_read	148 /* ENOSYS under SunOS                          */
#define TARGET_NR_pciconfig_write	149 /* ENOSYS under SunOS                          */
#define TARGET_NR_getsockname        150 /* Common                                      */
#define TARGET_NR_poll               153 /* Common                                      */
#define TARGET_NR_getdents64		154 /* Linux specific				   */
#define TARGET_NR_fcntl64		155 /* Linux sparc32 Specific                      */
#define TARGET_NR_statfs             157 /* Common                                      */
#define TARGET_NR_fstatfs            158 /* Common                                      */
#define TARGET_NR_umount             159 /* Common                                      */
#define TARGET_NR_getdomainname      162 /* SunOS Specific                              */
#define TARGET_NR_setdomainname      163 /* Common                                      */
#define TARGET_NR_quotactl           165 /* Common                                      */
#define TARGET_NR_mount              167 /* Common                                      */
#define TARGET_NR_ustat              168 /* Common                                      */
#define TARGET_NR_getdents           174 /* Common                                      */
#define TARGET_NR_setsid             175 /* Common                                      */
#define TARGET_NR_fchdir             176 /* Common                                      */
#define TARGET_NR_sigpending         183 /* Common                                      */
#define TARGET_NR_query_module	184 /* Linux Specific				   */
#define TARGET_NR_setpgid            185 /* Common                                      */
#define TARGET_NR_tkill              187 /* SunOS: fpathconf                            */
#define TARGET_NR_exit_group	     188 /* Linux specific, sysconf undef SunOS         */
#define TARGET_NR_uname              189 /* Linux Specific                              */
#define TARGET_NR_init_module        190 /* Linux Specific                              */
#define TARGET_NR_personality        191 /* Linux Specific                              */
#define TARGET_NR_getppid            197 /* Linux Specific                              */
#define TARGET_NR_sigaction          198 /* Linux Specific                              */
#define TARGET_NR_sgetmask           199 /* Linux Specific                              */
#define TARGET_NR_ssetmask           200 /* Linux Specific                              */
#define TARGET_NR_sigsuspend         201 /* Linux Specific                              */
#define TARGET_NR_oldlstat           202 /* Linux Specific                              */
#define TARGET_NR_uselib             203 /* Linux Specific                              */
#define TARGET_NR_readdir            204 /* Linux Specific                              */
#define TARGET_NR_readahead          205 /* Linux Specific                              */
#define TARGET_NR_socketcall         206 /* Linux Specific                              */
#define TARGET_NR_syslog             207 /* Linux Specific                              */
#define TARGET_NR_waitpid            212 /* Linux Specific                              */
#define TARGET_NR_swapoff            213 /* Linux Specific                              */
#define TARGET_NR_sysinfo            214 /* Linux Specific                              */
#define TARGET_NR_ipc                215 /* Linux Specific                              */
#define TARGET_NR_sigreturn          216 /* Linux Specific                              */
#define TARGET_NR_clone              217 /* Linux Specific                              */
#define TARGET_NR_adjtimex           219 /* Linux Specific                              */
#define TARGET_NR_sigprocmask        220 /* Linux Specific                              */
#define TARGET_NR_create_module      221 /* Linux Specific                              */
#define TARGET_NR_delete_module      222 /* Linux Specific                              */
#define TARGET_NR_get_kernel_syms    223 /* Linux Specific                              */
#define TARGET_NR_getpgid            224 /* Linux Specific                              */
#define TARGET_NR_bdflush            225 /* Linux Specific                              */
#define TARGET_NR_sysfs              226 /* Linux Specific                              */
#define TARGET_NR_afs_syscall        227 /* Linux Specific                              */
#define TARGET_NR_setfsuid           228 /* Linux Specific                              */
#define TARGET_NR_setfsgid           229 /* Linux Specific                              */
#define TARGET_NR__newselect         230 /* Linux Specific                              */
#define TARGET_NR_time               231 /* Linux Specific                              */
#define TARGET_NR_stime              233 /* Linux Specific                              */
#define TARGET_NR__llseek            236 /* Linux Specific                              */
#define TARGET_NR_mlock              237
#define TARGET_NR_munlock            238
#define TARGET_NR_mlockall           239
#define TARGET_NR_munlockall         240
#define TARGET_NR_sched_setparam     241
#define TARGET_NR_sched_getparam     242
#define TARGET_NR_sched_setscheduler 243
#define TARGET_NR_sched_getscheduler 244
#define TARGET_NR_sched_yield        245
#define TARGET_NR_sched_get_priority_max 246
#define TARGET_NR_sched_get_priority_min 247
#define TARGET_NR_sched_rr_get_interval  248
#define TARGET_NR_nanosleep          249
#define TARGET_NR_mremap             250
#define TARGET_NR__sysctl            251
#define TARGET_NR_getsid             252
#define TARGET_NR_fdatasync          253
#define TARGET_NR_nfsservctl         254
#define TARGET_NR_aplib              255
#define TARGET_NR__exit TARGET_NR_exit
