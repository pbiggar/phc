# 1 "net/ipv6/tcp_ipv6.c"
# 1 "/export/sc1/bhackett/linux-2.6.13.2//"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "net/ipv6/tcp_ipv6.c"
# 28 "net/ipv6/tcp_ipv6.c"
# 1 "include/linux/module.h" 1
# 9 "include/linux/module.h"
# 1 "include/linux/config.h" 1



# 1 "include/linux/autoconf.h" 1
# 5 "include/linux/config.h" 2
# 10 "include/linux/module.h" 2
# 1 "include/linux/sched.h" 1



# 1 "include/asm/param.h" 1
# 5 "include/linux/sched.h" 2


# 1 "include/linux/capability.h" 1
# 16 "include/linux/capability.h"
# 1 "include/linux/types.h" 1
# 13 "include/linux/types.h"
# 1 "include/linux/posix_types.h" 1



# 1 "include/linux/stddef.h" 1



# 1 "include/linux/compiler.h" 1
# 42 "include/linux/compiler.h"
# 1 "include/linux/compiler-gcc4.h" 1



# 1 "include/linux/compiler-gcc.h" 1
# 5 "include/linux/compiler-gcc4.h" 2
# 43 "include/linux/compiler.h" 2
# 5 "include/linux/stddef.h" 2
# 5 "include/linux/posix_types.h" 2
# 36 "include/linux/posix_types.h"
typedef struct {
 unsigned long fds_bits [(1024/(8 * sizeof(unsigned long)))];
} __kernel_fd_set;


typedef void (*__kernel_sighandler_t)(int);


typedef int __kernel_key_t;
typedef int __kernel_mqd_t;

# 1 "include/asm/posix_types.h" 1
# 10 "include/asm/posix_types.h"
typedef unsigned long __kernel_ino_t;
typedef unsigned short __kernel_mode_t;
typedef unsigned short __kernel_nlink_t;
typedef long __kernel_off_t;
typedef int __kernel_pid_t;
typedef unsigned short __kernel_ipc_pid_t;
typedef unsigned short __kernel_uid_t;
typedef unsigned short __kernel_gid_t;
typedef unsigned int __kernel_size_t;
typedef int __kernel_ssize_t;
typedef int __kernel_ptrdiff_t;
typedef long __kernel_time_t;
typedef long __kernel_suseconds_t;
typedef long __kernel_clock_t;
typedef int __kernel_timer_t;
typedef int __kernel_clockid_t;
typedef int __kernel_daddr_t;
typedef char * __kernel_caddr_t;
typedef unsigned short __kernel_uid16_t;
typedef unsigned short __kernel_gid16_t;
typedef unsigned int __kernel_uid32_t;
typedef unsigned int __kernel_gid32_t;

typedef unsigned short __kernel_old_uid_t;
typedef unsigned short __kernel_old_gid_t;
typedef unsigned short __kernel_old_dev_t;


typedef long long __kernel_loff_t;


typedef struct {

 int val[2];



} __kernel_fsid_t;
# 48 "include/linux/posix_types.h" 2
# 14 "include/linux/types.h" 2
# 1 "include/asm/types.h" 1





typedef unsigned short umode_t;






typedef __signed__ char __s8;
typedef unsigned char __u8;

typedef __signed__ short __s16;
typedef unsigned short __u16;

typedef __signed__ int __s32;
typedef unsigned int __u32;


typedef __signed__ long long __s64;
typedef unsigned long long __u64;
# 40 "include/asm/types.h"
typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long long s64;
typedef unsigned long long u64;






typedef u32 dma_addr_t;

typedef u64 dma64_addr_t;


typedef u64 sector_t;



typedef unsigned short kmem_bufctl_t;
# 15 "include/linux/types.h" 2



typedef __u32 __kernel_dev_t;

typedef __kernel_fd_set fd_set;
typedef __kernel_dev_t dev_t;
typedef __kernel_ino_t ino_t;
typedef __kernel_mode_t mode_t;
typedef __kernel_nlink_t nlink_t;
typedef __kernel_off_t off_t;
typedef __kernel_pid_t pid_t;
typedef __kernel_daddr_t daddr_t;
typedef __kernel_key_t key_t;
typedef __kernel_suseconds_t suseconds_t;
typedef __kernel_timer_t timer_t;
typedef __kernel_clockid_t clockid_t;
typedef __kernel_mqd_t mqd_t;


typedef __kernel_uid32_t uid_t;
typedef __kernel_gid32_t gid_t;
typedef __kernel_uid16_t uid16_t;
typedef __kernel_gid16_t gid16_t;



typedef __kernel_old_uid_t old_uid_t;
typedef __kernel_old_gid_t old_gid_t;
# 55 "include/linux/types.h"
typedef __kernel_loff_t loff_t;
# 64 "include/linux/types.h"
typedef __kernel_size_t size_t;




typedef __kernel_ssize_t ssize_t;




typedef __kernel_ptrdiff_t ptrdiff_t;




typedef __kernel_time_t time_t;




typedef __kernel_clock_t clock_t;




typedef __kernel_caddr_t caddr_t;



typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;


typedef unsigned char unchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;




typedef __u8 u_int8_t;
typedef __s8 int8_t;
typedef __u16 u_int16_t;
typedef __s16 int16_t;
typedef __u32 u_int32_t;
typedef __s32 int32_t;



typedef __u8 uint8_t;
typedef __u16 uint16_t;
typedef __u32 uint32_t;


typedef __u64 uint64_t;
typedef __u64 u_int64_t;
typedef __s64 int64_t;
# 156 "include/linux/types.h"
typedef __u16 __le16;
typedef __u16 __be16;
typedef __u32 __le32;
typedef __u32 __be32;

typedef __u64 __le64;
typedef __u64 __be64;


struct ustat {
 __kernel_daddr_t f_tfree;
 __kernel_ino_t f_tinode;
 char f_fname[6];
 char f_fpack[6];
};
# 17 "include/linux/capability.h" 2
# 32 "include/linux/capability.h"
typedef struct __user_cap_header_struct {
 __u32 version;
 int pid;
} *cap_user_header_t;

typedef struct __user_cap_data_struct {
        __u32 effective;
        __u32 permitted;
        __u32 inheritable;
} *cap_user_data_t;



# 1 "include/linux/spinlock.h" 1
# 9 "include/linux/spinlock.h"
# 1 "include/linux/preempt.h" 1
# 10 "include/linux/preempt.h"
# 1 "include/linux/linkage.h" 1




# 1 "include/asm/linkage.h" 1
# 6 "include/linux/linkage.h" 2
# 11 "include/linux/preempt.h" 2
# 10 "include/linux/spinlock.h" 2


# 1 "include/linux/thread_info.h" 1
# 13 "include/linux/thread_info.h"
struct restart_block {
 long (*fn)(struct restart_block *);
 unsigned long arg0, arg1, arg2, arg3;
};

extern long do_no_restart_syscall(struct restart_block *parm);

# 1 "include/linux/bitops.h" 1
# 11 "include/linux/bitops.h"
static inline __attribute__((always_inline)) int generic_ffs(int x)
{
 int r = 1;

 if (!x)
  return 0;
 if (!(x & 0xffff)) {
  x >>= 16;
  r += 16;
 }
 if (!(x & 0xff)) {
  x >>= 8;
  r += 8;
 }
 if (!(x & 0xf)) {
  x >>= 4;
  r += 4;
 }
 if (!(x & 3)) {
  x >>= 2;
  r += 2;
 }
 if (!(x & 1)) {
  x >>= 1;
  r += 1;
 }
 return r;
}





static __inline__ __attribute__((always_inline)) int generic_fls(int x)
{
 int r = 32;

 if (!x)
  return 0;
 if (!(x & 0xffff0000u)) {
  x <<= 16;
  r -= 16;
 }
 if (!(x & 0xff000000u)) {
  x <<= 8;
  r -= 8;
 }
 if (!(x & 0xf0000000u)) {
  x <<= 4;
  r -= 4;
 }
 if (!(x & 0xc0000000u)) {
  x <<= 2;
  r -= 2;
 }
 if (!(x & 0x80000000u)) {
  x <<= 1;
  r -= 1;
 }
 return r;
}





# 1 "include/asm/bitops.h" 1
# 42 "include/asm/bitops.h"
static inline __attribute__((always_inline)) void set_bit(int nr, volatile unsigned long * addr)
{
 __asm__ __volatile__( "lock ; "
  "btsl %1,%0"
  :"=m" ((*(volatile long *) addr))
  :"Ir" (nr));
}
# 59 "include/asm/bitops.h"
static inline __attribute__((always_inline)) void __set_bit(int nr, volatile unsigned long * addr)
{
 __asm__(
  "btsl %1,%0"
  :"=m" ((*(volatile long *) addr))
  :"Ir" (nr));
}
# 77 "include/asm/bitops.h"
static inline __attribute__((always_inline)) void clear_bit(int nr, volatile unsigned long * addr)
{
 __asm__ __volatile__( "lock ; "
  "btrl %1,%0"
  :"=m" ((*(volatile long *) addr))
  :"Ir" (nr));
}

static inline __attribute__((always_inline)) void __clear_bit(int nr, volatile unsigned long * addr)
{
 __asm__ __volatile__(
  "btrl %1,%0"
  :"=m" ((*(volatile long *) addr))
  :"Ir" (nr));
}
# 104 "include/asm/bitops.h"
static inline __attribute__((always_inline)) void __change_bit(int nr, volatile unsigned long * addr)
{
 __asm__ __volatile__(
  "btcl %1,%0"
  :"=m" ((*(volatile long *) addr))
  :"Ir" (nr));
}
# 122 "include/asm/bitops.h"
static inline __attribute__((always_inline)) void change_bit(int nr, volatile unsigned long * addr)
{
 __asm__ __volatile__( "lock ; "
  "btcl %1,%0"
  :"=m" ((*(volatile long *) addr))
  :"Ir" (nr));
}
# 139 "include/asm/bitops.h"
static inline __attribute__((always_inline)) int test_and_set_bit(int nr, volatile unsigned long * addr)
{
 int oldbit;

 __asm__ __volatile__( "lock ; "
  "btsl %2,%1\n\tsbbl %0,%0"
  :"=r" (oldbit),"=m" ((*(volatile long *) addr))
  :"Ir" (nr) : "memory");
 return oldbit;
}
# 159 "include/asm/bitops.h"
static inline __attribute__((always_inline)) int __test_and_set_bit(int nr, volatile unsigned long * addr)
{
 int oldbit;

 __asm__(
  "btsl %2,%1\n\tsbbl %0,%0"
  :"=r" (oldbit),"=m" ((*(volatile long *) addr))
  :"Ir" (nr));
 return oldbit;
}
# 179 "include/asm/bitops.h"
static inline __attribute__((always_inline)) int test_and_clear_bit(int nr, volatile unsigned long * addr)
{
 int oldbit;

 __asm__ __volatile__( "lock ; "
  "btrl %2,%1\n\tsbbl %0,%0"
  :"=r" (oldbit),"=m" ((*(volatile long *) addr))
  :"Ir" (nr) : "memory");
 return oldbit;
}
# 199 "include/asm/bitops.h"
static inline __attribute__((always_inline)) int __test_and_clear_bit(int nr, volatile unsigned long *addr)
{
 int oldbit;

 __asm__(
  "btrl %2,%1\n\tsbbl %0,%0"
  :"=r" (oldbit),"=m" ((*(volatile long *) addr))
  :"Ir" (nr));
 return oldbit;
}


static inline __attribute__((always_inline)) int __test_and_change_bit(int nr, volatile unsigned long *addr)
{
 int oldbit;

 __asm__ __volatile__(
  "btcl %2,%1\n\tsbbl %0,%0"
  :"=r" (oldbit),"=m" ((*(volatile long *) addr))
  :"Ir" (nr) : "memory");
 return oldbit;
}
# 230 "include/asm/bitops.h"
static inline __attribute__((always_inline)) int test_and_change_bit(int nr, volatile unsigned long* addr)
{
 int oldbit;

 __asm__ __volatile__( "lock ; "
  "btcl %2,%1\n\tsbbl %0,%0"
  :"=r" (oldbit),"=m" ((*(volatile long *) addr))
  :"Ir" (nr) : "memory");
 return oldbit;
}
# 250 "include/asm/bitops.h"
static inline __attribute__((always_inline)) int constant_test_bit(int nr, const volatile unsigned long *addr)
{
 return ((1UL << (nr & 31)) & (addr[nr >> 5])) != 0;
}

static inline __attribute__((always_inline)) int variable_test_bit(int nr, const volatile unsigned long * addr)
{
 int oldbit;

 __asm__ __volatile__(
  "btl %2,%1\n\tsbbl %0,%0"
  :"=r" (oldbit)
  :"m" ((*(volatile long *) addr)),"Ir" (nr));
 return oldbit;
}
# 281 "include/asm/bitops.h"
static inline __attribute__((always_inline)) int find_first_zero_bit(const unsigned long *addr, unsigned size)
{
 int d0, d1, d2;
 int res;

 if (!size)
  return 0;

 __asm__ __volatile__(
  "movl $-1,%%eax\n\t"
  "xorl %%edx,%%edx\n\t"
  "repe; scasl\n\t"
  "je 1f\n\t"
  "xorl -4(%%edi),%%eax\n\t"
  "subl $4,%%edi\n\t"
  "bsfl %%eax,%%edx\n"
  "1:\tsubl %%ebx,%%edi\n\t"
  "shll $3,%%edi\n\t"
  "addl %%edi,%%edx"
  :"=d" (res), "=&c" (d0), "=&D" (d1), "=&a" (d2)
  :"1" ((size + 31) >> 5), "2" (addr), "b" (addr) : "memory");
 return res;
}







int find_next_zero_bit(const unsigned long *addr, int size, int offset);







static inline __attribute__((always_inline)) unsigned long __ffs(unsigned long word)
{
 __asm__("bsfl %1,%0"
  :"=r" (word)
  :"rm" (word));
 return word;
}
# 335 "include/asm/bitops.h"
static inline __attribute__((always_inline)) int find_first_bit(const unsigned long *addr, unsigned size)
{
 int x = 0;

 while (x < size) {
  unsigned long val = *addr++;
  if (val)
   return __ffs(val) + x;
  x += (sizeof(*addr)<<3);
 }
 return x;
}







int find_next_bit(const unsigned long *addr, int size, int offset);







static inline __attribute__((always_inline)) unsigned long ffz(unsigned long word)
{
 __asm__("bsfl %1,%0"
  :"=r" (word)
  :"r" (~word));
 return word;
}
# 384 "include/asm/bitops.h"
static inline __attribute__((always_inline)) int sched_find_first_bit(const unsigned long *b)
{
 if (__builtin_expect(!!(b[0]), 0))
  return __ffs(b[0]);
 if (__builtin_expect(!!(b[1]), 0))
  return __ffs(b[1]) + 32;
 if (__builtin_expect(!!(b[2]), 0))
  return __ffs(b[2]) + 64;
 if (b[3])
  return __ffs(b[3]) + 96;
 return __ffs(b[4]) + 128;
}
# 405 "include/asm/bitops.h"
static inline __attribute__((always_inline)) int ffs(int x)
{
 int r;

 __asm__("bsfl %1,%0\n\t"
  "jnz 1f\n\t"
  "movl $-1,%0\n"
  "1:" : "=r" (r) : "rm" (x));
 return r+1;
}
# 78 "include/linux/bitops.h" 2

static __inline__ __attribute__((always_inline)) int get_bitmask_order(unsigned int count)
{
 int order;

 order = generic_fls(count);
 return order;
}






static inline __attribute__((always_inline)) unsigned int generic_hweight32(unsigned int w)
{
        unsigned int res = (w & 0x55555555) + ((w >> 1) & 0x55555555);
        res = (res & 0x33333333) + ((res >> 2) & 0x33333333);
        res = (res & 0x0F0F0F0F) + ((res >> 4) & 0x0F0F0F0F);
        res = (res & 0x00FF00FF) + ((res >> 8) & 0x00FF00FF);
        return (res & 0x0000FFFF) + ((res >> 16) & 0x0000FFFF);
}

static inline __attribute__((always_inline)) unsigned int generic_hweight16(unsigned int w)
{
        unsigned int res = (w & 0x5555) + ((w >> 1) & 0x5555);
        res = (res & 0x3333) + ((res >> 2) & 0x3333);
        res = (res & 0x0F0F) + ((res >> 4) & 0x0F0F);
        return (res & 0x00FF) + ((res >> 8) & 0x00FF);
}

static inline __attribute__((always_inline)) unsigned int generic_hweight8(unsigned int w)
{
        unsigned int res = (w & 0x55) + ((w >> 1) & 0x55);
        res = (res & 0x33) + ((res >> 2) & 0x33);
        return (res & 0x0F) + ((res >> 4) & 0x0F);
}

static inline __attribute__((always_inline)) unsigned long generic_hweight64(__u64 w)
{

 return generic_hweight32((unsigned int)(w >> 32)) +
    generic_hweight32((unsigned int)w);
# 130 "include/linux/bitops.h"
}

static inline __attribute__((always_inline)) unsigned long hweight_long(unsigned long w)
{
 return sizeof(w) == 4 ? generic_hweight32(w) : generic_hweight64(w);
}







static inline __attribute__((always_inline)) __u32 rol32(__u32 word, unsigned int shift)
{
 return (word << shift) | (word >> (32 - shift));
}







static inline __attribute__((always_inline)) __u32 ror32(__u32 word, unsigned int shift)
{
 return (word >> shift) | (word << (32 - shift));
}
# 21 "include/linux/thread_info.h" 2
# 1 "include/asm/thread_info.h" 1
# 14 "include/asm/thread_info.h"
# 1 "include/asm/page.h" 1
# 45 "include/asm/page.h"
extern int nx_enabled;
# 57 "include/asm/page.h"
typedef struct { unsigned long pte_low; } pte_t;
typedef struct { unsigned long pgd; } pgd_t;
typedef struct { unsigned long pgprot; } pgprot_t;
# 105 "include/asm/page.h"
extern unsigned int __VMALLOC_RESERVE;


static __inline__ __attribute__((always_inline)) int get_order(unsigned long size)
{
 int order;

 size = (size-1) >> (12 -1);
 order = -1;
 do {
  size >>= 1;
  order++;
 } while (size);
 return order;
}

extern int sysctl_legacy_va_layout;

extern int page_is_ram(unsigned long pagenr);
# 15 "include/asm/thread_info.h" 2


# 1 "include/asm/processor.h" 1
# 10 "include/asm/processor.h"
# 1 "include/asm/vm86.h" 1
# 68 "include/asm/vm86.h"
struct vm86_regs {



 long ebx;
 long ecx;
 long edx;
 long esi;
 long edi;
 long ebp;
 long eax;
 long __null_ds;
 long __null_es;
 long __null_fs;
 long __null_gs;
 long orig_eax;
 long eip;
 unsigned short cs, __csh;
 long eflags;
 long esp;
 unsigned short ss, __ssh;



 unsigned short es, __esh;
 unsigned short ds, __dsh;
 unsigned short fs, __fsh;
 unsigned short gs, __gsh;
};

struct revectored_struct {
 unsigned long __map[8];
};

struct vm86_struct {
 struct vm86_regs regs;
 unsigned long flags;
 unsigned long screen_bitmap;
 unsigned long cpu_type;
 struct revectored_struct int_revectored;
 struct revectored_struct int21_revectored;
};






struct vm86plus_info_struct {
 unsigned long force_return_for_pic:1;
 unsigned long vm86dbg_active:1;
 unsigned long vm86dbg_TFpendig:1;
 unsigned long unused:28;
 unsigned long is_vm86pus:1;
 unsigned char vm86dbg_intxxtab[32];
};

struct vm86plus_struct {
 struct vm86_regs regs;
 unsigned long flags;
 unsigned long screen_bitmap;
 unsigned long cpu_type;
 struct revectored_struct int_revectored;
 struct revectored_struct int21_revectored;
 struct vm86plus_info_struct vm86plus;
};
# 145 "include/asm/vm86.h"
struct kernel_vm86_regs {



 long ebx;
 long ecx;
 long edx;
 long esi;
 long edi;
 long ebp;
 long eax;
 long __null_ds;
 long __null_es;
 long orig_eax;
 long eip;
 unsigned short cs, __csh;
 long eflags;
 long esp;
 unsigned short ss, __ssh;



 unsigned short es, __esh;
 unsigned short ds, __dsh;
 unsigned short fs, __fsh;
 unsigned short gs, __gsh;
};

struct kernel_vm86_struct {
 struct kernel_vm86_regs regs;
# 184 "include/asm/vm86.h"
 unsigned long flags;
 unsigned long screen_bitmap;
 unsigned long cpu_type;
 struct revectored_struct int_revectored;
 struct revectored_struct int21_revectored;
 struct vm86plus_info_struct vm86plus;
 struct pt_regs *regs32;
# 201 "include/asm/vm86.h"
};

void handle_vm86_fault(struct kernel_vm86_regs *, long);
int handle_vm86_trap(struct kernel_vm86_regs *, long, int);
# 11 "include/asm/processor.h" 2
# 1 "include/asm/math_emu.h" 1



# 1 "include/asm/sigcontext.h" 1
# 20 "include/asm/sigcontext.h"
struct _fpreg {
 unsigned short significand[4];
 unsigned short exponent;
};

struct _fpxreg {
 unsigned short significand[4];
 unsigned short exponent;
 unsigned short padding[3];
};

struct _xmmreg {
 unsigned long element[4];
};

struct _fpstate {

 unsigned long cw;
 unsigned long sw;
 unsigned long tag;
 unsigned long ipoff;
 unsigned long cssel;
 unsigned long dataoff;
 unsigned long datasel;
 struct _fpreg _st[8];
 unsigned short status;
 unsigned short magic;


 unsigned long _fxsr_env[6];
 unsigned long mxcsr;
 unsigned long reserved;
 struct _fpxreg _fxsr_st[8];
 struct _xmmreg _xmm[8];
 unsigned long padding[56];
};



struct sigcontext {
 unsigned short gs, __gsh;
 unsigned short fs, __fsh;
 unsigned short es, __esh;
 unsigned short ds, __dsh;
 unsigned long edi;
 unsigned long esi;
 unsigned long ebp;
 unsigned long esp;
 unsigned long ebx;
 unsigned long edx;
 unsigned long ecx;
 unsigned long eax;
 unsigned long trapno;
 unsigned long err;
 unsigned long eip;
 unsigned short cs, __csh;
 unsigned long eflags;
 unsigned long esp_at_signal;
 unsigned short ss, __ssh;
 struct _fpstate * fpstate;
 unsigned long oldmask;
 unsigned long cr2;
};
# 5 "include/asm/math_emu.h" 2

int restore_i387_soft(void *s387, struct _fpstate *buf);
int save_i387_soft(void *s387, struct _fpstate *buf);





struct info {
 long ___orig_eip;
 long ___ebx;
 long ___ecx;
 long ___edx;
 long ___esi;
 long ___edi;
 long ___ebp;
 long ___eax;
 long ___ds;
 long ___es;
 long ___orig_eax;
 long ___eip;
 long ___cs;
 long ___eflags;
 long ___esp;
 long ___ss;
 long ___vm86_es;
 long ___vm86_ds;
 long ___vm86_fs;
 long ___vm86_gs;
};
# 12 "include/asm/processor.h" 2
# 1 "include/asm/segment.h" 1
# 13 "include/asm/processor.h" 2



# 1 "include/asm/cpufeature.h" 1
# 17 "include/asm/processor.h" 2
# 1 "include/asm/msr.h" 1
# 27 "include/asm/msr.h"
static inline __attribute__((always_inline)) void wrmsrl (unsigned long msr, unsigned long long val)
{
 unsigned long lo, hi;
 lo = (unsigned long) val;
 hi = val >> 32;
 __asm__ __volatile__("wrmsr" : : "c" (msr), "a" (lo), "d" (hi));
}
# 18 "include/asm/processor.h" 2
# 1 "include/asm/system.h" 1




# 1 "include/linux/kernel.h" 1
# 10 "include/linux/kernel.h"
# 1 "/usr/lib/gcc/i386-redhat-linux/4.0.2/include/stdarg.h" 1 3 4
# 43 "/usr/lib/gcc/i386-redhat-linux/4.0.2/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 105 "/usr/lib/gcc/i386-redhat-linux/4.0.2/include/stdarg.h" 3 4
typedef __gnuc_va_list va_list;
# 11 "include/linux/kernel.h" 2





# 1 "include/asm/byteorder.h" 1
# 14 "include/asm/byteorder.h"
static __inline__ __attribute__((always_inline)) __attribute__((__const__)) __u32 ___arch__swab32(__u32 x)
{

 __asm__("bswap %0" : "=r" (x) : "0" (x));







 return x;
}

static __inline__ __attribute__((always_inline)) __attribute__((__const__)) __u64 ___arch__swab64(__u64 val)
{
 union {
  struct { __u32 a,b; } s;
  __u64 u;
 } v;
 v.u = val;

 asm("bswapl %0 ; bswapl %1 ; xchgl %0,%1"
     : "=r" (v.s.a), "=r" (v.s.b)
     : "0" (v.s.a), "1" (v.s.b));





 return v.u;
}
# 57 "include/asm/byteorder.h"
# 1 "include/linux/byteorder/little_endian.h" 1
# 12 "include/linux/byteorder/little_endian.h"
# 1 "include/linux/byteorder/swab.h" 1
# 133 "include/linux/byteorder/swab.h"
static __inline__ __attribute__((always_inline)) __attribute__((__const__)) __u16 __fswab16(__u16 x)
{
 return ({ __u16 __tmp = (x) ; ({ __u16 __x = (__tmp); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }); });
}
static __inline__ __attribute__((always_inline)) __u16 __swab16p(const __u16 *x)
{
 return ({ __u16 __tmp = (*(x)) ; ({ __u16 __x = (__tmp); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }); });
}
static __inline__ __attribute__((always_inline)) void __swab16s(__u16 *addr)
{
 do { *(addr) = ({ __u16 __tmp = (*((addr))) ; ({ __u16 __x = (__tmp); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }); }); } while (0);
}

static __inline__ __attribute__((always_inline)) __attribute__((__const__)) __u32 __fswab32(__u32 x)
{
 return ___arch__swab32(x);
}
static __inline__ __attribute__((always_inline)) __u32 __swab32p(const __u32 *x)
{
 return ___arch__swab32(*(x));
}
static __inline__ __attribute__((always_inline)) void __swab32s(__u32 *addr)
{
 do { *(addr) = ___arch__swab32(*((addr))); } while (0);
}


static __inline__ __attribute__((always_inline)) __attribute__((__const__)) __u64 __fswab64(__u64 x)
{





 return ___arch__swab64(x);

}
static __inline__ __attribute__((always_inline)) __u64 __swab64p(const __u64 *x)
{
 return ___arch__swab64(*(x));
}
static __inline__ __attribute__((always_inline)) void __swab64s(__u64 *addr)
{
 do { *(addr) = ___arch__swab64(*((addr))); } while (0);
}
# 13 "include/linux/byteorder/little_endian.h" 2
# 43 "include/linux/byteorder/little_endian.h"
static inline __attribute__((always_inline)) __le64 __cpu_to_le64p(const __u64 *p)
{
 return ( __le64)*p;
}
static inline __attribute__((always_inline)) __u64 __le64_to_cpup(const __le64 *p)
{
 return ( __u64)*p;
}
static inline __attribute__((always_inline)) __le32 __cpu_to_le32p(const __u32 *p)
{
 return ( __le32)*p;
}
static inline __attribute__((always_inline)) __u32 __le32_to_cpup(const __le32 *p)
{
 return ( __u32)*p;
}
static inline __attribute__((always_inline)) __le16 __cpu_to_le16p(const __u16 *p)
{
 return ( __le16)*p;
}
static inline __attribute__((always_inline)) __u16 __le16_to_cpup(const __le16 *p)
{
 return ( __u16)*p;
}
static inline __attribute__((always_inline)) __be64 __cpu_to_be64p(const __u64 *p)
{
 return ( __be64)__swab64p(p);
}
static inline __attribute__((always_inline)) __u64 __be64_to_cpup(const __be64 *p)
{
 return __swab64p((__u64 *)p);
}
static inline __attribute__((always_inline)) __be32 __cpu_to_be32p(const __u32 *p)
{
 return ( __be32)__swab32p(p);
}
static inline __attribute__((always_inline)) __u32 __be32_to_cpup(const __be32 *p)
{
 return __swab32p((__u32 *)p);
}
static inline __attribute__((always_inline)) __be16 __cpu_to_be16p(const __u16 *p)
{
 return ( __be16)__swab16p(p);
}
static inline __attribute__((always_inline)) __u16 __be16_to_cpup(const __be16 *p)
{
 return __swab16p((__u16 *)p);
}
# 104 "include/linux/byteorder/little_endian.h"
# 1 "include/linux/byteorder/generic.h" 1
# 150 "include/linux/byteorder/generic.h"
extern __u32 ntohl(__be32);
extern __be32 htonl(__u32);
extern __u16 ntohs(__be16);
extern __be16 htons(__u16);
# 105 "include/linux/byteorder/little_endian.h" 2
# 58 "include/asm/byteorder.h" 2
# 17 "include/linux/kernel.h" 2
# 1 "include/asm/bug.h" 1
# 26 "include/asm/bug.h"
static inline __attribute__((always_inline)) void __BUG() { __asm__ __volatile__("ud2\n"); }



# 1 "include/asm-generic/bug.h" 1
# 31 "include/asm/bug.h" 2
# 18 "include/linux/kernel.h" 2

extern const char linux_banner[];
# 42 "include/linux/kernel.h"
extern int console_printk[];






struct completion;
# 69 "include/linux/kernel.h"
  void __might_sleep(char *file, int line);
# 88 "include/linux/kernel.h"
extern struct notifier_block *panic_notifier_list;
extern long (*panic_blink)(long time);
 void panic(const char * fmt, ...)
 __attribute__ ((noreturn, format (printf, 1, 2)));
__attribute__((regparm(3))) void do_exit(long error_code)
 __attribute__((noreturn));
 void complete_and_exit(struct completion *, long)
 __attribute__((noreturn));
extern unsigned long simple_strtoul(const char *,char **,unsigned int);
extern long simple_strtol(const char *,char **,unsigned int);
extern unsigned long long simple_strtoull(const char *,char **,unsigned int);
extern long long simple_strtoll(const char *,char **,unsigned int);
extern int sprintf(char * buf, const char * fmt, ...)
 __attribute__ ((format (printf, 2, 3)));
extern int vsprintf(char *buf, const char *, va_list)
 __attribute__ ((format (printf, 2, 0)));
extern int snprintf(char * buf, size_t size, const char * fmt, ...)
 __attribute__ ((format (printf, 3, 4)));
extern int vsnprintf(char *buf, size_t size, const char *fmt, va_list args)
 __attribute__ ((format (printf, 3, 0)));
extern int scnprintf(char * buf, size_t size, const char * fmt, ...)
 __attribute__ ((format (printf, 3, 4)));
extern int vscnprintf(char *buf, size_t size, const char *fmt, va_list args)
 __attribute__ ((format (printf, 3, 0)));

extern int sscanf(const char *, const char *, ...)
 __attribute__ ((format (scanf, 2, 3)));
extern int vsscanf(const char *, const char *, va_list)
 __attribute__ ((format (scanf, 2, 0)));

extern int get_option(char **str, int *pint);
extern char *get_options(const char *str, int nints, int *ints);
extern unsigned long long memparse(char *ptr, char **retptr);

extern int __kernel_text_address(unsigned long addr);
extern int kernel_text_address(unsigned long addr);
extern int session_of_pgrp(int pgrp);


 __attribute__((regparm(0))) int vprintk(const char *fmt, va_list args)
 __attribute__ ((format (printf, 1, 0)));
 __attribute__((regparm(0))) int printk(const char * fmt, ...)
 __attribute__ ((format (printf, 1, 2)));
# 140 "include/linux/kernel.h"
unsigned long int_sqrt(unsigned long);

static inline __attribute__((always_inline)) int __attribute__((pure)) long_log2(unsigned long x)
{
 int r = 0;
 for (x >>= 1; x > 0; x >>= 1)
  r++;
 return r;
}

static inline __attribute__((always_inline)) unsigned long __attribute__((__const__)) roundup_pow_of_two(unsigned long x)
{
 return (1UL << generic_fls(x - 1));
}

extern int printk_ratelimit(void);
extern int __printk_ratelimit(int ratelimit_jiffies, int ratelimit_burst);

static inline __attribute__((always_inline)) void console_silent(void)
{
 (console_printk[0]) = 0;
}

static inline __attribute__((always_inline)) void console_verbose(void)
{
 if ((console_printk[0]))
  (console_printk[0]) = 15;
}

extern void bust_spinlocks(int yes);
extern int oops_in_progress;
extern int panic_timeout;
extern int panic_on_oops;
extern int tainted;
extern const char *print_tainted(void);
extern void add_taint(unsigned);


extern enum system_states {
 SYSTEM_BOOTING,
 SYSTEM_RUNNING,
 SYSTEM_HALT,
 SYSTEM_POWER_OFF,
 SYSTEM_RESTART,
} system_state;
# 193 "include/linux/kernel.h"
extern void dump_stack(void);
# 293 "include/linux/kernel.h"
struct sysinfo {
 long uptime;
 unsigned long loads[3];
 unsigned long totalram;
 unsigned long freeram;
 unsigned long sharedram;
 unsigned long bufferram;
 unsigned long totalswap;
 unsigned long freeswap;
 unsigned short procs;
 unsigned short pad;
 unsigned long totalhigh;
 unsigned long freehigh;
 unsigned int mem_unit;
 char _f[20-2*sizeof(long)-sizeof(int)];
};

extern void BUILD_BUG(void);



extern int randomize_va_space;
# 6 "include/asm/system.h" 2






struct task_struct;
extern struct task_struct * __switch_to(struct task_struct *prev, struct task_struct *next) __attribute__((regparm(3)));
# 61 "include/asm/system.h"
static inline __attribute__((always_inline)) unsigned long _get_base(char * addr)
{
 unsigned long __base;
 __asm__("movb %3,%%dh\n\t"
  "movb %2,%%dl\n\t"
  "shll $16,%%edx\n\t"
  "movw %1,%%dx"
  :"=&d" (__base)
  :"m" (*((addr)+2)),
   "m" (*((addr)+4)),
   "m" (*((addr)+7)));
 return __base;
}
# 134 "include/asm/system.h"
static inline __attribute__((always_inline)) unsigned long get_limit(unsigned long segment)
{
 unsigned long __limit;
 __asm__("lsll %1,%0"
  :"=r" (__limit):"r" (segment));
 return __limit+1;
}







struct __xchg_dummy { unsigned long a[100]; };
# 166 "include/asm/system.h"
static inline __attribute__((always_inline)) void __set_64bit (unsigned long long * ptr,
  unsigned int low, unsigned int high)
{
 __asm__ __volatile__ (
  "\n1:\t"
  "movl (%0), %%eax\n\t"
  "movl 4(%0), %%edx\n\t"
  "lock cmpxchg8b (%0)\n\t"
  "jnz 1b"
  :
  : "D"(ptr),
   "b"(low),
   "c"(high)
  : "ax","dx","memory");
}

static inline __attribute__((always_inline)) void __set_64bit_constant (unsigned long long *ptr,
       unsigned long long value)
{
 __set_64bit(ptr,(unsigned int)(value), (unsigned int)((value)>>32ULL));
}



static inline __attribute__((always_inline)) void __set_64bit_var (unsigned long long *ptr,
    unsigned long long value)
{
 __set_64bit(ptr,*(((unsigned int*)&(value))+0), *(((unsigned int*)&(value))+1));
}
# 211 "include/asm/system.h"
static inline __attribute__((always_inline)) unsigned long __xchg(unsigned long x, volatile void * ptr, int size)
{
 switch (size) {
  case 1:
   __asm__ __volatile__("xchgb %b0,%1"
    :"=q" (x)
    :"m" (*((struct __xchg_dummy *)(ptr))), "0" (x)
    :"memory");
   break;
  case 2:
   __asm__ __volatile__("xchgw %w0,%1"
    :"=r" (x)
    :"m" (*((struct __xchg_dummy *)(ptr))), "0" (x)
    :"memory");
   break;
  case 4:
   __asm__ __volatile__("xchgl %0,%1"
    :"=r" (x)
    :"m" (*((struct __xchg_dummy *)(ptr))), "0" (x)
    :"memory");
   break;
 }
 return x;
}
# 246 "include/asm/system.h"
static inline __attribute__((always_inline)) unsigned long __cmpxchg(volatile void *ptr, unsigned long old,
          unsigned long new, int size)
{
 unsigned long prev;
 switch (size) {
 case 1:
  __asm__ __volatile__("lock ; " "cmpxchgb %b1,%2"
         : "=a"(prev)
         : "q"(new), "m"(*((struct __xchg_dummy *)(ptr))), "0"(old)
         : "memory");
  return prev;
 case 2:
  __asm__ __volatile__("lock ; " "cmpxchgw %w1,%2"
         : "=a"(prev)
         : "q"(new), "m"(*((struct __xchg_dummy *)(ptr))), "0"(old)
         : "memory");
  return prev;
 case 4:
  __asm__ __volatile__("lock ; " "cmpxchgl %1,%2"
         : "=a"(prev)
         : "q"(new), "m"(*((struct __xchg_dummy *)(ptr))), "0"(old)
         : "memory");
  return prev;
 }
 return old;
}






struct alt_instr {
 __u8 *instr;
 __u8 *replacement;
 __u8 cpuid;
 __u8 instrlen;
 __u8 replacementlen;
 __u8 pad;
};
# 465 "include/asm/system.h"
void disable_hlt(void);
void enable_hlt(void);

extern int es7000_plat;
void cpu_idle_wait(void);

extern unsigned long arch_align_stack(unsigned long sp);
# 19 "include/asm/processor.h" 2
# 1 "include/linux/cache.h" 1





# 1 "include/asm/cache.h" 1
# 7 "include/linux/cache.h" 2
# 20 "include/asm/processor.h" 2

# 1 "include/linux/threads.h" 1
# 22 "include/asm/processor.h" 2
# 1 "include/asm/percpu.h" 1



# 1 "include/asm-generic/percpu.h" 1







extern unsigned long __per_cpu_offset[8];
# 5 "include/asm/percpu.h" 2
# 23 "include/asm/processor.h" 2


extern int tsc_disable;

struct desc_struct {
 unsigned long a,b;
};
# 48 "include/asm/processor.h"
struct cpuinfo_x86 {
 __u8 x86;
 __u8 x86_vendor;
 __u8 x86_model;
 __u8 x86_mask;
 char wp_works_ok;
 char hlt_works_ok;
 char hard_math;
 char rfu;
        int cpuid_level;
 unsigned long x86_capability[7];
 char x86_vendor_id[16];
 char x86_model_id[64];
 int x86_cache_size;

 int x86_cache_alignment;
 int fdiv_bug;
 int f00f_bug;
 int coma_bug;
 unsigned long loops_per_jiffy;
 unsigned char x86_num_cores;
} __attribute__((__aligned__((1 << (7)))));
# 87 "include/asm/processor.h"
extern struct cpuinfo_x86 boot_cpu_data;
extern struct cpuinfo_x86 new_cpu_data;
extern struct tss_struct doublefault_tss;
extern __typeof__(struct tss_struct) per_cpu__init_tss;


extern struct cpuinfo_x86 cpu_data[];






extern int phys_proc_id[8];
extern int cpu_core_id[8];
extern char ignore_fpu_irq;

extern void identify_cpu(struct cpuinfo_x86 *);
extern void print_cpu_info(struct cpuinfo_x86 *);
extern unsigned int init_intel_cacheinfo(struct cpuinfo_x86 *c);


extern void detect_ht(struct cpuinfo_x86 *c);
# 140 "include/asm/processor.h"
static inline __attribute__((always_inline)) void cpuid(unsigned int op, unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
{
 __asm__("cpuid"
  : "=a" (*eax),
    "=b" (*ebx),
    "=c" (*ecx),
    "=d" (*edx)
  : "0" (op), "c"(0));
}


static inline __attribute__((always_inline)) void cpuid_count(int op, int count, int *eax, int *ebx, int *ecx,
         int *edx)
{
 __asm__("cpuid"
  : "=a" (*eax),
    "=b" (*ebx),
    "=c" (*ecx),
    "=d" (*edx)
  : "0" (op), "c" (count));
}




static inline __attribute__((always_inline)) unsigned int cpuid_eax(unsigned int op)
{
 unsigned int eax;

 __asm__("cpuid"
  : "=a" (eax)
  : "0" (op)
  : "bx", "cx", "dx");
 return eax;
}
static inline __attribute__((always_inline)) unsigned int cpuid_ebx(unsigned int op)
{
 unsigned int eax, ebx;

 __asm__("cpuid"
  : "=a" (eax), "=b" (ebx)
  : "0" (op)
  : "cx", "dx" );
 return ebx;
}
static inline __attribute__((always_inline)) unsigned int cpuid_ecx(unsigned int op)
{
 unsigned int eax, ecx;

 __asm__("cpuid"
  : "=a" (eax), "=c" (ecx)
  : "0" (op)
  : "bx", "dx" );
 return ecx;
}
static inline __attribute__((always_inline)) unsigned int cpuid_edx(unsigned int op)
{
 unsigned int eax, edx;

 __asm__("cpuid"
  : "=a" (eax), "=d" (edx)
  : "0" (op)
  : "bx", "cx");
 return edx;
}
# 231 "include/asm/processor.h"
extern unsigned long mmu_cr4_features;

static inline __attribute__((always_inline)) void set_in_cr4 (unsigned long mask)
{
 mmu_cr4_features |= mask;
 __asm__("movl %%cr4,%%eax\n\t"
  "orl %0,%%eax\n\t"
  "movl %%eax,%%cr4\n"
  : : "irg" (mask)
  :"ax");
}

static inline __attribute__((always_inline)) void clear_in_cr4 (unsigned long mask)
{
 mmu_cr4_features &= ~mask;
 __asm__("movl %%cr4,%%eax\n\t"
  "andl %0,%%eax\n\t"
  "movl %%eax,%%cr4\n"
  : : "irg" (~mask)
  :"ax");
}
# 284 "include/asm/processor.h"
static inline __attribute__((always_inline)) void __monitor(const void *eax, unsigned long ecx,
  unsigned long edx)
{

 asm volatile(
  ".byte 0x0f,0x01,0xc8;"
  : :"a" (eax), "c" (ecx), "d"(edx));
}

static inline __attribute__((always_inline)) void __mwait(unsigned long eax, unsigned long ecx)
{

 asm volatile(
  ".byte 0x0f,0x01,0xc9;"
  : :"a" (eax), "c" (ecx));
}



extern unsigned int machine_id;
extern unsigned int machine_submodel_id;
extern unsigned int BIOS_revision;
extern unsigned int mca_pentium_flag;


extern int bootloader_type;
# 333 "include/asm/processor.h"
struct i387_fsave_struct {
 long cwd;
 long swd;
 long twd;
 long fip;
 long fcs;
 long foo;
 long fos;
 long st_space[20];
 long status;
};

struct i387_fxsave_struct {
 unsigned short cwd;
 unsigned short swd;
 unsigned short twd;
 unsigned short fop;
 long fip;
 long fcs;
 long foo;
 long fos;
 long mxcsr;
 long mxcsr_mask;
 long st_space[32];
 long xmm_space[32];
 long padding[56];
} __attribute__ ((aligned (16)));

struct i387_soft_struct {
 long cwd;
 long swd;
 long twd;
 long fip;
 long fcs;
 long foo;
 long fos;
 long st_space[20];
 unsigned char ftop, changed, lookahead, no_update, rm, alimit;
 struct info *info;
 unsigned long entry_eip;
};

union i387_union {
 struct i387_fsave_struct fsave;
 struct i387_fxsave_struct fxsave;
 struct i387_soft_struct soft;
};

typedef struct {
 unsigned long seg;
} mm_segment_t;

struct thread_struct;

struct tss_struct {
 unsigned short back_link,__blh;
 unsigned long esp0;
 unsigned short ss0,__ss0h;
 unsigned long esp1;
 unsigned short ss1,__ss1h;
 unsigned long esp2;
 unsigned short ss2,__ss2h;
 unsigned long __cr3;
 unsigned long eip;
 unsigned long eflags;
 unsigned long eax,ecx,edx,ebx;
 unsigned long esp;
 unsigned long ebp;
 unsigned long esi;
 unsigned long edi;
 unsigned short es, __esh;
 unsigned short cs, __csh;
 unsigned short ss, __ssh;
 unsigned short ds, __dsh;
 unsigned short fs, __fsh;
 unsigned short gs, __gsh;
 unsigned short ldt, __ldth;
 unsigned short trace, io_bitmap_base;






 unsigned long io_bitmap[((65536/8)/sizeof(long)) + 1];



 unsigned long io_bitmap_max;
 struct thread_struct *io_bitmap_owner;



 unsigned long __cacheline_filler[35];



 unsigned long stack[64];
} __attribute__((packed));



struct thread_struct {

 struct desc_struct tls_array[3];
 unsigned long esp0;
 unsigned long sysenter_cs;
 unsigned long eip;
 unsigned long esp;
 unsigned long fs;
 unsigned long gs;

 unsigned long debugreg[8];

 unsigned long cr2, trap_no, error_code;

 union i387_union i387;

 struct vm86_struct * vm86_info;
 unsigned long screen_bitmap;
 unsigned long v86flags, v86mask, saved_esp0;
 unsigned int saved_fs, saved_gs;

 unsigned long *io_bitmap_ptr;

 unsigned long io_bitmap_max;
};
# 482 "include/asm/processor.h"
static inline __attribute__((always_inline)) void load_esp0(struct tss_struct *tss, struct thread_struct *thread)
{
 tss->esp0 = thread->esp0;

 if (__builtin_expect(!!(tss->ss1 != thread->sysenter_cs), 0)) {
  tss->ss1 = thread->sysenter_cs;
  __asm__ __volatile__("wrmsr" : : "c" (0x174), "a" (thread->sysenter_cs), "d" (0));
 }
}
# 516 "include/asm/processor.h"
struct task_struct;
struct mm_struct;


extern void release_thread(struct task_struct *);


extern void prepare_to_copy(struct task_struct *tsk);




extern int kernel_thread(int (*fn)(void *), void * arg, unsigned long flags);

extern unsigned long thread_saved_pc(struct task_struct *tsk);
void show_trace(struct task_struct *task, unsigned long *stack);

unsigned long get_wchan(struct task_struct *p);
# 553 "include/asm/processor.h"
struct microcode_header {
 unsigned int hdrver;
 unsigned int rev;
 unsigned int date;
 unsigned int sig;
 unsigned int cksum;
 unsigned int ldrver;
 unsigned int pf;
 unsigned int datasize;
 unsigned int totalsize;
 unsigned int reserved[3];
};

struct microcode {
 struct microcode_header hdr;
 unsigned int bits[0];
};

typedef struct microcode microcode_t;
typedef struct microcode_header microcode_header_t;


struct extended_signature {
 unsigned int sig;
 unsigned int pf;
 unsigned int cksum;
};

struct extended_sigtable {
 unsigned int count;
 unsigned int cksum;
 unsigned int reserved[3];
 struct extended_signature sigs[0];
};




static inline __attribute__((always_inline)) void rep_nop(void)
{
 __asm__ __volatile__("rep;nop": : :"memory");
}
# 666 "include/asm/processor.h"
extern inline __attribute__((always_inline)) void prefetch(const void *x)
{
 asm volatile ("661:\n\t" ".byte 0x8d,0x74,0x26,0x00\n" "\n662:\n" ".section .altinstructions,\"a\"\n" "  .align 4\n" "  .long 661b\n" "  .long 663f\n" "  .byte %c0\n" "  .byte 662b-661b\n" "  .byte 664f-663f\n" ".previous\n" ".section .altinstr_replacement,\"ax\"\n" "663:\n\t" "prefetchnta (%1)" "\n664:\n" ".previous" :: "i" ((0*32+25)), "r" (x));



}







extern inline __attribute__((always_inline)) void prefetchw(const void *x)
{
 asm volatile ("661:\n\t" ".byte 0x8d,0x74,0x26,0x00\n" "\n662:\n" ".section .altinstructions,\"a\"\n" "  .align 4\n" "  .long 661b\n" "  .long 663f\n" "  .byte %c0\n" "  .byte 662b-661b\n" "  .byte 664f-663f\n" ".previous\n" ".section .altinstr_replacement,\"ax\"\n" "663:\n\t" "prefetchw (%1)" "\n664:\n" ".previous" :: "i" ((1*32+31)), "r" (x));



}


extern void select_idle_routine(const struct cpuinfo_x86 *c);



extern unsigned long boot_option_idle_override;
extern void enable_sep_cpu(void);
extern int sysenter_setup(void);


extern void mtrr_ap_init(void);
extern void mtrr_bp_init(void);
# 18 "include/asm/thread_info.h" 2
# 28 "include/asm/thread_info.h"
struct thread_info {
 struct task_struct *task;
 struct exec_domain *exec_domain;
 unsigned long flags;
 unsigned long status;
 __u32 cpu;
 int preempt_count;


 mm_segment_t addr_limit;



 struct restart_block restart_block;

 unsigned long previous_esp;


 __u8 supervisor_stack[0];
};
# 88 "include/asm/thread_info.h"
static inline __attribute__((always_inline)) struct thread_info *current_thread_info(void)
{
 struct thread_info *ti;
 __asm__("andl %%esp,%0; ":"=r" (ti) : "0" (~((4096) - 1)));
 return ti;
}


register unsigned long current_stack_pointer asm("esp") __attribute__((__used__));
# 22 "include/linux/thread_info.h" 2
# 30 "include/linux/thread_info.h"
static inline __attribute__((always_inline)) void set_thread_flag(int flag)
{
 set_bit(flag,&current_thread_info()->flags);
}

static inline __attribute__((always_inline)) void clear_thread_flag(int flag)
{
 clear_bit(flag,&current_thread_info()->flags);
}

static inline __attribute__((always_inline)) int test_and_set_thread_flag(int flag)
{
 return test_and_set_bit(flag,&current_thread_info()->flags);
}

static inline __attribute__((always_inline)) int test_and_clear_thread_flag(int flag)
{
 return test_and_clear_bit(flag,&current_thread_info()->flags);
}

static inline __attribute__((always_inline)) int test_thread_flag(int flag)
{
 return (__builtin_constant_p(flag) ? constant_test_bit((flag),(&current_thread_info()->flags)) : variable_test_bit((flag),(&current_thread_info()->flags)));
}

static inline __attribute__((always_inline)) void set_ti_thread_flag(struct thread_info *ti, int flag)
{
 set_bit(flag,&ti->flags);
}

static inline __attribute__((always_inline)) void clear_ti_thread_flag(struct thread_info *ti, int flag)
{
 clear_bit(flag,&ti->flags);
}

static inline __attribute__((always_inline)) int test_and_set_ti_thread_flag(struct thread_info *ti, int flag)
{
 return test_and_set_bit(flag,&ti->flags);
}

static inline __attribute__((always_inline)) int test_and_clear_ti_thread_flag(struct thread_info *ti, int flag)
{
 return test_and_clear_bit(flag,&ti->flags);
}

static inline __attribute__((always_inline)) int test_ti_thread_flag(struct thread_info *ti, int flag)
{
 return (__builtin_constant_p(flag) ? constant_test_bit((flag),(&ti->flags)) : variable_test_bit((flag),(&ti->flags)));
}

static inline __attribute__((always_inline)) void set_need_resched(void)
{
 set_thread_flag(3);
}

static inline __attribute__((always_inline)) void clear_need_resched(void)
{
 clear_thread_flag(3);
}
# 13 "include/linux/spinlock.h" 2

# 1 "include/linux/stringify.h" 1
# 15 "include/linux/spinlock.h" 2
# 43 "include/linux/spinlock.h"
# 1 "include/asm/spinlock.h" 1



# 1 "include/asm/atomic.h" 1
# 24 "include/asm/atomic.h"
typedef struct { volatile int counter; } atomic_t;
# 52 "include/asm/atomic.h"
static __inline__ __attribute__((always_inline)) void atomic_add(int i, atomic_t *v)
{
 __asm__ __volatile__(
  "lock ; " "addl %1,%0"
  :"=m" (v->counter)
  :"ir" (i), "m" (v->counter));
}
# 67 "include/asm/atomic.h"
static __inline__ __attribute__((always_inline)) void atomic_sub(int i, atomic_t *v)
{
 __asm__ __volatile__(
  "lock ; " "subl %1,%0"
  :"=m" (v->counter)
  :"ir" (i), "m" (v->counter));
}
# 84 "include/asm/atomic.h"
static __inline__ __attribute__((always_inline)) int atomic_sub_and_test(int i, atomic_t *v)
{
 unsigned char c;

 __asm__ __volatile__(
  "lock ; " "subl %2,%0; sete %1"
  :"=m" (v->counter), "=qm" (c)
  :"ir" (i), "m" (v->counter) : "memory");
 return c;
}







static __inline__ __attribute__((always_inline)) void atomic_inc(atomic_t *v)
{
 __asm__ __volatile__(
  "lock ; " "incl %0"
  :"=m" (v->counter)
  :"m" (v->counter));
}







static __inline__ __attribute__((always_inline)) void atomic_dec(atomic_t *v)
{
 __asm__ __volatile__(
  "lock ; " "decl %0"
  :"=m" (v->counter)
  :"m" (v->counter));
}
# 131 "include/asm/atomic.h"
static __inline__ __attribute__((always_inline)) int atomic_dec_and_test(atomic_t *v)
{
 unsigned char c;

 __asm__ __volatile__(
  "lock ; " "decl %0; sete %1"
  :"=m" (v->counter), "=qm" (c)
  :"m" (v->counter) : "memory");
 return c != 0;
}
# 150 "include/asm/atomic.h"
static __inline__ __attribute__((always_inline)) int atomic_inc_and_test(atomic_t *v)
{
 unsigned char c;

 __asm__ __volatile__(
  "lock ; " "incl %0; sete %1"
  :"=m" (v->counter), "=qm" (c)
  :"m" (v->counter) : "memory");
 return c != 0;
}
# 170 "include/asm/atomic.h"
static __inline__ __attribute__((always_inline)) int atomic_add_negative(int i, atomic_t *v)
{
 unsigned char c;

 __asm__ __volatile__(
  "lock ; " "addl %2,%0; sets %1"
  :"=m" (v->counter), "=qm" (c)
  :"ir" (i), "m" (v->counter) : "memory");
 return c;
}
# 188 "include/asm/atomic.h"
static __inline__ __attribute__((always_inline)) int atomic_add_return(int i, atomic_t *v)
{
 int __i;





 __i = i;
 __asm__ __volatile__(
  "lock ; " "xaddl %0, %1;"
  :"=r"(i)
  :"m"(v->counter), "0"(i));
 return i + __i;
# 211 "include/asm/atomic.h"
}

static __inline__ __attribute__((always_inline)) int atomic_sub_return(int i, atomic_t *v)
{
 return atomic_add_return(-i,v);
}
# 5 "include/asm/spinlock.h" 2
# 1 "include/asm/rwlock.h" 1
# 6 "include/asm/spinlock.h" 2




 __attribute__((regparm(0))) int printk(const char * fmt, ...)
 __attribute__ ((format (printf, 1, 2)));





typedef struct {
 volatile unsigned int slock;

 unsigned magic;




} spinlock_t;
# 107 "include/asm/spinlock.h"
static inline __attribute__((always_inline)) void _raw_spin_unlock(spinlock_t *lock)
{
 char oldval = 1;

 do { if (__builtin_expect(!!((lock->magic != 0xdead4ead)!=0), 0)) __BUG(); } while(0);
 do { if (__builtin_expect(!!((!(*(volatile signed char *)(&(lock)->slock) <= 0))!=0), 0)) __BUG(); } while(0);

 __asm__ __volatile__(
  "xchgb %b0, %1" :"=q" (oldval), "=m" (lock->slock) :"0" (oldval) : "memory"
 );
}



static inline __attribute__((always_inline)) int _raw_spin_trylock(spinlock_t *lock)
{
 char oldval;
 __asm__ __volatile__(
  "xchgb %b0,%1"
  :"=q" (oldval), "=m" (lock->slock)
  :"0" (0) : "memory");
 return oldval > 0;
}

static inline __attribute__((always_inline)) void _raw_spin_lock(spinlock_t *lock)
{

 if (__builtin_expect(!!(lock->magic != 0xdead4ead), 0)) {
  printk("eip: %p\n", __builtin_return_address(0));
  __BUG();
 }

 __asm__ __volatile__(
  "\n1:\t" "lock ; decb %0\n\t" "jns 3f\n" "2:\t" "rep;nop\n\t" "cmpb $0,%0\n\t" "jle 2b\n\t" "jmp 1b\n" "3:\n\t"
  :"=m" (lock->slock) : : "memory");
}

static inline __attribute__((always_inline)) void _raw_spin_lock_flags (spinlock_t *lock, unsigned long flags)
{

 if (__builtin_expect(!!(lock->magic != 0xdead4ead), 0)) {
  printk("eip: %p\n", __builtin_return_address(0));
  __BUG();
 }

 __asm__ __volatile__(
  "\n1:\t" "lock ; decb %0\n\t" "jns 4f\n\t" "2:\t" "testl $0x200, %1\n\t" "jz 3f\n\t" "sti\n\t" "3:\t" "rep;nop\n\t" "cmpb $0, %0\n\t" "jle 3b\n\t" "cli\n\t" "jmp 1b\n" "4:\n\t"
  :"=m" (lock->slock) : "r" (flags) : "memory");
}
# 167 "include/asm/spinlock.h"
typedef struct {
 volatile unsigned int lock;

 unsigned magic;




} rwlock_t;
# 212 "include/asm/spinlock.h"
static inline __attribute__((always_inline)) void _raw_read_lock(rwlock_t *rw)
{

 do { if (__builtin_expect(!!((rw->magic != 0xdeaf1eed)!=0), 0)) __BUG(); } while(0);

 do { if (__builtin_constant_p(rw)) asm volatile("lock ; " "subl $1,%0\n\t" "jns 1f\n" "pushl %%eax\n\t" "leal %0,%%eax\n\t" "call " "__read_lock_failed" "\n\t" "popl %%eax\n\t" "1:\n" :"=m" (*(volatile int *)rw) : : "memory"); else asm volatile("lock ; " "subl $1,(%0)\n\t" "jns 1f\n" "call " "__read_lock_failed" "\n\t" "1:\n" ::"a" (rw) : "memory"); } while (0);
}

static inline __attribute__((always_inline)) void _raw_write_lock(rwlock_t *rw)
{

 do { if (__builtin_expect(!!((rw->magic != 0xdeaf1eed)!=0), 0)) __BUG(); } while(0);

 do { if (__builtin_constant_p(rw)) asm volatile("lock ; " "subl $" "0x01000000" ",%0\n\t" "jz 1f\n" "pushl %%eax\n\t" "leal %0,%%eax\n\t" "call " "__write_lock_failed" "\n\t" "popl %%eax\n\t" "1:\n" :"=m" (*(volatile int *)rw) : : "memory"); else asm volatile("lock ; " "subl $" "0x01000000" ",(%0)\n\t" "jz 1f\n" "call " "__write_lock_failed" "\n\t" "1:\n" ::"a" (rw) : "memory"); } while (0);
}




static inline __attribute__((always_inline)) int _raw_read_trylock(rwlock_t *lock)
{
 atomic_t *count = (atomic_t *)lock;
 atomic_dec(count);
 if (((count)->counter) >= 0)
  return 1;
 atomic_inc(count);
 return 0;
}

static inline __attribute__((always_inline)) int _raw_write_trylock(rwlock_t *lock)
{
 atomic_t *count = (atomic_t *)lock;
 if (atomic_sub_and_test(0x01000000, count))
  return 1;
 atomic_add(0x01000000, count);
 return 0;
}
# 44 "include/linux/spinlock.h" 2

int __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _spin_trylock(spinlock_t *lock);
int __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _read_trylock(rwlock_t *lock);
int __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _write_trylock(rwlock_t *lock);

void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _spin_lock(spinlock_t *lock) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _read_lock(rwlock_t *lock) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _write_lock(rwlock_t *lock) ;

void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _spin_unlock(spinlock_t *lock) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _read_unlock(rwlock_t *lock) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _write_unlock(rwlock_t *lock) ;

unsigned long __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _spin_lock_irqsave(spinlock_t *lock) ;
unsigned long __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _read_lock_irqsave(rwlock_t *lock) ;
unsigned long __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _write_lock_irqsave(rwlock_t *lock) ;

void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _spin_lock_irq(spinlock_t *lock) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _spin_lock_bh(spinlock_t *lock) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _read_lock_irq(rwlock_t *lock) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _read_lock_bh(rwlock_t *lock) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _write_lock_irq(rwlock_t *lock) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _write_lock_bh(rwlock_t *lock) ;

void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _spin_unlock_irqrestore(spinlock_t *lock, unsigned long flags) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _spin_unlock_irq(spinlock_t *lock) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _spin_unlock_bh(spinlock_t *lock) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _read_unlock_irqrestore(rwlock_t *lock, unsigned long flags) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _read_unlock_irq(rwlock_t *lock) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _read_unlock_bh(rwlock_t *lock) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _write_unlock_irqrestore(rwlock_t *lock, unsigned long flags) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _write_unlock_irq(rwlock_t *lock) ;
void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _write_unlock_bh(rwlock_t *lock) ;

int __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) _spin_trylock_bh(spinlock_t *lock);
int __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) generic_raw_read_trylock(rwlock_t *lock);
int in_lock_functions(unsigned long addr);
# 520 "include/linux/spinlock.h"
extern int _atomic_dec_and_lock(atomic_t *atomic, spinlock_t *lock);
# 531 "include/linux/spinlock.h"
static inline __attribute__((always_inline)) void bit_spin_lock(int bitnum, unsigned long *addr)
{







 do { } while (0);

 while (test_and_set_bit(bitnum, addr)) {
  while ((__builtin_constant_p(bitnum) ? constant_test_bit((bitnum),(addr)) : variable_test_bit((bitnum),(addr)))) {
   do { } while (0);
   rep_nop();
   do { } while (0);
  }
 }

 (void)0;
}




static inline __attribute__((always_inline)) int bit_spin_trylock(int bitnum, unsigned long *addr)
{
 do { } while (0);

 if (test_and_set_bit(bitnum, addr)) {
  do { } while (0);
  return 0;
 }

 (void)0;
 return 1;
}




static inline __attribute__((always_inline)) void bit_spin_unlock(int bitnum, unsigned long *addr)
{

 do { if (__builtin_expect(!!((!(__builtin_constant_p(bitnum) ? constant_test_bit((bitnum),(addr)) : variable_test_bit((bitnum),(addr))))!=0), 0)) __BUG(); } while(0);
 __asm__ __volatile__("": : :"memory");
 clear_bit(bitnum, addr);

 do { } while (0);
 (void)0;
}




static inline __attribute__((always_inline)) int bit_spin_is_locked(int bitnum, unsigned long *addr)
{

 return (__builtin_constant_p(bitnum) ? constant_test_bit((bitnum),(addr)) : variable_test_bit((bitnum),(addr)));





}
# 46 "include/linux/capability.h" 2
# 57 "include/linux/capability.h"
typedef __u32 kernel_cap_t;
# 293 "include/linux/capability.h"
extern kernel_cap_t cap_bset;
# 321 "include/linux/capability.h"
static inline __attribute__((always_inline)) kernel_cap_t cap_combine(kernel_cap_t a, kernel_cap_t b)
{
     kernel_cap_t dest;
     (dest) = (a) | (b);
     return dest;
}

static inline __attribute__((always_inline)) kernel_cap_t cap_intersect(kernel_cap_t a, kernel_cap_t b)
{
     kernel_cap_t dest;
     (dest) = (a) & (b);
     return dest;
}

static inline __attribute__((always_inline)) kernel_cap_t cap_drop(kernel_cap_t a, kernel_cap_t drop)
{
     kernel_cap_t dest;
     (dest) = (a) & ~(drop);
     return dest;
}

static inline __attribute__((always_inline)) kernel_cap_t cap_invert(kernel_cap_t c)
{
     kernel_cap_t dest;
     (dest) = ~(c);
     return dest;
}
# 8 "include/linux/sched.h" 2



# 1 "include/linux/timex.h" 1
# 58 "include/linux/timex.h"
# 1 "include/linux/time.h" 1






# 1 "include/linux/seqlock.h" 1
# 33 "include/linux/seqlock.h"
typedef struct {
 unsigned sequence;
 spinlock_t lock;
} seqlock_t;
# 50 "include/linux/seqlock.h"
static inline __attribute__((always_inline)) void write_seqlock(seqlock_t *sl)
{
 _spin_lock(&sl->lock);
 ++sl->sequence;
 __asm__ __volatile__ ("": : :"memory");
}

static inline __attribute__((always_inline)) void write_sequnlock(seqlock_t *sl)
{
 __asm__ __volatile__ ("": : :"memory");
 sl->sequence++;
 _spin_unlock(&sl->lock);
}

static inline __attribute__((always_inline)) int write_tryseqlock(seqlock_t *sl)
{
 int ret = (_spin_trylock(&sl->lock));

 if (ret) {
  ++sl->sequence;
  __asm__ __volatile__ ("": : :"memory");
 }
 return ret;
}


static inline __attribute__((always_inline)) unsigned read_seqbegin(const seqlock_t *sl)
{
 unsigned ret = sl->sequence;
 asm volatile ("661:\n\t" "lock; addl $0,0(%%esp)" "\n662:\n" ".section .altinstructions,\"a\"\n" "  .align 4\n" "  .long 661b\n" "  .long 663f\n" "  .byte %c0\n" "  .byte 662b-661b\n" "  .byte 664f-663f\n" ".previous\n" ".section .altinstr_replacement,\"ax\"\n" "663:\n\t" "lfence" "\n664:\n" ".previous" :: "i" ((0*32+26)) : "memory");
 return ret;
}
# 91 "include/linux/seqlock.h"
static inline __attribute__((always_inline)) int read_seqretry(const seqlock_t *sl, unsigned iv)
{
 asm volatile ("661:\n\t" "lock; addl $0,0(%%esp)" "\n662:\n" ".section .altinstructions,\"a\"\n" "  .align 4\n" "  .long 661b\n" "  .long 663f\n" "  .byte %c0\n" "  .byte 662b-661b\n" "  .byte 664f-663f\n" ".previous\n" ".section .altinstr_replacement,\"ax\"\n" "663:\n\t" "lfence" "\n664:\n" ".previous" :: "i" ((0*32+26)) : "memory");
 return (iv & 1) | (sl->sequence ^ iv);
}
# 105 "include/linux/seqlock.h"
typedef struct seqcount {
 unsigned sequence;
} seqcount_t;





static inline __attribute__((always_inline)) unsigned read_seqcount_begin(const seqcount_t *s)
{
 unsigned ret = s->sequence;
 asm volatile ("661:\n\t" "lock; addl $0,0(%%esp)" "\n662:\n" ".section .altinstructions,\"a\"\n" "  .align 4\n" "  .long 661b\n" "  .long 663f\n" "  .byte %c0\n" "  .byte 662b-661b\n" "  .byte 664f-663f\n" ".previous\n" ".section .altinstr_replacement,\"ax\"\n" "663:\n\t" "lfence" "\n664:\n" ".previous" :: "i" ((0*32+26)) : "memory");
 return ret;
}






static inline __attribute__((always_inline)) int read_seqcount_retry(const seqcount_t *s, unsigned iv)
{
 asm volatile ("661:\n\t" "lock; addl $0,0(%%esp)" "\n662:\n" ".section .altinstructions,\"a\"\n" "  .align 4\n" "  .long 661b\n" "  .long 663f\n" "  .byte %c0\n" "  .byte 662b-661b\n" "  .byte 664f-663f\n" ".previous\n" ".section .altinstr_replacement,\"ax\"\n" "663:\n\t" "lfence" "\n664:\n" ".previous" :: "i" ((0*32+26)) : "memory");
 return (iv & 1) | (s->sequence ^ iv);
}






static inline __attribute__((always_inline)) void write_seqcount_begin(seqcount_t *s)
{
 s->sequence++;
 __asm__ __volatile__ ("": : :"memory");
}

static inline __attribute__((always_inline)) void write_seqcount_end(seqcount_t *s)
{
 __asm__ __volatile__ ("": : :"memory");
 s->sequence++;
}
# 8 "include/linux/time.h" 2




struct timespec {
 time_t tv_sec;
 long tv_nsec;
};


struct timeval {
 time_t tv_sec;
 suseconds_t tv_usec;
};

struct timezone {
 int tz_minuteswest;
 int tz_dsttime;
};
# 43 "include/linux/time.h"
static __inline__ __attribute__((always_inline)) int timespec_equal(struct timespec *a, struct timespec *b)
{
 return (a->tv_sec == b->tv_sec) && (a->tv_nsec == b->tv_nsec);
}
# 63 "include/linux/time.h"
static inline __attribute__((always_inline)) unsigned long
mktime (unsigned int year, unsigned int mon,
 unsigned int day, unsigned int hour,
 unsigned int min, unsigned int sec)
{
 if (0 >= (int) (mon -= 2)) {
  mon += 12;
  year -= 1;
 }

 return (((
  (unsigned long) (year/4 - year/100 + year/400 + 367*mon/12 + day) +
   year*365 - 719499
     )*24 + hour
   )*60 + min
 )*60 + sec;
}

extern struct timespec xtime;
extern struct timespec wall_to_monotonic;
extern seqlock_t xtime_lock;

static inline __attribute__((always_inline)) unsigned long get_seconds(void)
{
 return xtime.tv_sec;
}

struct timespec current_kernel_time(void);




extern void do_gettimeofday(struct timeval *tv);
extern int do_settimeofday(struct timespec *tv);
extern int do_sys_settimeofday(struct timespec *tv, struct timezone *tz);
extern void clock_was_set(void);
extern int do_posix_clock_monotonic_gettime(struct timespec *tp);
extern long do_nanosleep(struct timespec *t);
extern long do_utimes(char * filename, struct timeval * times);
struct itimerval;
extern int do_setitimer(int which, struct itimerval *value, struct itimerval *ovalue);
extern int do_getitimer(int which, struct itimerval *value);
extern void getnstimeofday (struct timespec *tv);

extern struct timespec timespec_trunc(struct timespec t, unsigned gran);

static inline __attribute__((always_inline)) void
set_normalized_timespec (struct timespec *ts, time_t sec, long nsec)
{
 while (nsec > (1000000000L)) {
  nsec -= (1000000000L);
  ++sec;
 }
 while (nsec < 0) {
  nsec += (1000000000L);
  --sec;
 }
 ts->tv_sec = sec;
 ts->tv_nsec = nsec;
}
# 142 "include/linux/time.h"
struct itimerspec {
        struct timespec it_interval;
        struct timespec it_value;
};

struct itimerval {
 struct timeval it_interval;
 struct timeval it_value;
};
# 59 "include/linux/timex.h" 2

# 1 "include/asm/param.h" 1
# 61 "include/linux/timex.h" 2
# 1 "include/asm/timex.h" 1
# 33 "include/asm/timex.h"
typedef unsigned long long cycles_t;

static inline __attribute__((always_inline)) cycles_t get_cycles (void)
{
 unsigned long long ret=0;







 __asm__ __volatile__("rdtsc" : "=A" (ret));

 return ret;
}

extern unsigned int cpu_khz;

extern int read_current_timer(unsigned long *timer_value);
# 62 "include/linux/timex.h" 2
# 135 "include/linux/timex.h"
struct timex {
 unsigned int modes;
 long offset;
 long freq;
 long maxerror;
 long esterror;
 int status;
 long constant;
 long precision;
 long tolerance;


 struct timeval time;
 long tick;

 long ppsfreq;
 long jitter;
 int shift;
 long stabil;
 long jitcnt;
 long calcnt;
 long errcnt;
 long stbcnt;

 int :32; int :32; int :32; int :32;
 int :32; int :32; int :32; int :32;
 int :32; int :32; int :32; int :32;
};
# 227 "include/linux/timex.h"
extern unsigned long tick_usec;
extern unsigned long tick_nsec;
extern int tickadj;




extern int time_state;
extern int time_status;
extern long time_offset;
extern long time_constant;
extern long time_tolerance;
extern long time_precision;
extern long time_maxerror;
extern long time_esterror;

extern long time_freq;
extern long time_reftime;

extern long time_adjust;
extern long time_next_adjust;


extern long pps_offset;
extern long pps_jitter;
extern long pps_freq;
extern long pps_stabil;
extern long pps_valid;


extern int pps_shift;
extern long pps_jitcnt;
extern long pps_calcnt;
extern long pps_errcnt;
extern long pps_stbcnt;
# 311 "include/linux/timex.h"
static inline __attribute__((always_inline)) void
time_interpolator_reset(void)
{
}
# 12 "include/linux/sched.h" 2
# 1 "include/linux/jiffies.h" 1







# 1 "include/asm/param.h" 1
# 9 "include/linux/jiffies.h" 2
# 1 "include/asm/div64.h" 1
# 38 "include/asm/div64.h"
extern inline __attribute__((always_inline)) long
div_ll_X_l_rem(long long divs, long div, long *rem)
{
 long dum2;
      __asm__("divl %2":"=a"(dum2), "=d"(*rem)
      : "rm"(div), "A"(divs));

 return dum2;

}
# 10 "include/linux/jiffies.h" 2
# 84 "include/linux/jiffies.h"
extern u64 __attribute__((section(".data"))) jiffies_64;
extern unsigned long volatile __attribute__((section(".data"))) jiffies;


u64 get_jiffies_64(void);
# 255 "include/linux/jiffies.h"
static inline __attribute__((always_inline)) unsigned int jiffies_to_msecs(const unsigned long j)
{

 return (1000 / 250) * j;





}

static inline __attribute__((always_inline)) unsigned int jiffies_to_usecs(const unsigned long j)
{

 return (1000000 / 250) * j;





}

static inline __attribute__((always_inline)) unsigned long msecs_to_jiffies(const unsigned int m)
{
 if (m > jiffies_to_msecs(((~0UL >> 1)-1)))
  return ((~0UL >> 1)-1);

 return (m + (1000 / 250) - 1) / (1000 / 250);





}

static inline __attribute__((always_inline)) unsigned long usecs_to_jiffies(const unsigned int u)
{
 if (u > jiffies_to_usecs(((~0UL >> 1)-1)))
  return ((~0UL >> 1)-1);

 return (u + (1000000 / 250) - 1) / (1000000 / 250);





}
# 314 "include/linux/jiffies.h"
static __inline__ __attribute__((always_inline)) unsigned long
timespec_to_jiffies(const struct timespec *value)
{
 unsigned long sec = value->tv_sec;
 long nsec = value->tv_nsec + (( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))))) - 1;

 if (sec >= (long)((u64)((u64)((~0UL >> 1)-1) * (( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))))) / (1000000000L))){
  sec = (long)((u64)((u64)((~0UL >> 1)-1) * (( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))))) / (1000000000L));
  nsec = 0;
 }
 return (((u64)sec * ((unsigned long)((((u64)(1000000000L) << (32 - 8)) + (( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))))) -1) / (u64)(( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))))))) +
  (((u64)nsec * ((unsigned long)((((u64)1 << ((32 - 8) + 29)) + (( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))))) -1) / (u64)(( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))))))) >>
   (((32 - 8) + 29) - (32 - 8)))) >> (32 - 8);

}

static __inline__ __attribute__((always_inline)) void
jiffies_to_timespec(const unsigned long jiffies, struct timespec *value)
{




 u64 nsec = (u64)jiffies * (( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))));
 value->tv_sec = div_ll_X_l_rem(nsec,(1000000000L),&value->tv_nsec);
}
# 353 "include/linux/jiffies.h"
static __inline__ __attribute__((always_inline)) unsigned long
timeval_to_jiffies(const struct timeval *value)
{
 unsigned long sec = value->tv_sec;
 long usec = value->tv_usec;

 if (sec >= (long)((u64)((u64)((~0UL >> 1)-1) * (( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))))) / (1000000000L))){
  sec = (long)((u64)((u64)((~0UL >> 1)-1) * (( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))))) / (1000000000L));
  usec = 0;
 }
 return (((u64)sec * ((unsigned long)((((u64)(1000000000L) << (32 - 8)) + (( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))))) -1) / (u64)(( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))))))) +
  (((u64)usec * ((unsigned long)((((u64)(1000L) << ((32 - 8) + 19)) + (( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))))) -1) / (u64)(( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))))))) + (u64)(((u64)1 << ((32 - 8) + 19)) - 1)) >>
   (((32 - 8) + 19) - (32 - 8)))) >> (32 - 8);
}

static __inline__ __attribute__((always_inline)) void
jiffies_to_timeval(const unsigned long jiffies, struct timeval *value)
{




 u64 nsec = (u64)jiffies * (( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))));
 value->tv_sec = div_ll_X_l_rem(nsec,(1000000000L),&value->tv_usec);
 value->tv_usec /= (1000L);
}




static inline __attribute__((always_inline)) clock_t jiffies_to_clock_t(long x)
{



 u64 tmp = (u64)x * (( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))));
 ({ unsigned long __upper, __low, __high, __mod, __base; __base = (((1000000000L) / 100)); asm("":"=a" (__low), "=d" (__high):"A" (tmp)); __upper = __high; if (__high) { __upper = __high % (__base); __high = __high / (__base); } asm("divl %2":"=a" (__low), "=d" (__mod):"rm" (__base), "0" (__low), "1" (__upper)); asm("":"=A" (tmp):"a" (__low),"d" (__high)); __mod; });
 return (long)tmp;

}

static inline __attribute__((always_inline)) unsigned long clock_t_to_jiffies(unsigned long x)
{





 u64 jif;


 if (x >= ~0UL / 250 * 100)
  return ~0UL;


 jif = x * (u64) 250;
 ({ unsigned long __upper, __low, __high, __mod, __base; __base = (100); asm("":"=a" (__low), "=d" (__high):"A" (jif)); __upper = __high; if (__high) { __upper = __high % (__base); __high = __high / (__base); } asm("divl %2":"=a" (__low), "=d" (__mod):"rm" (__base), "0" (__low), "1" (__upper)); asm("":"=A" (jif):"a" (__low),"d" (__high)); __mod; });
 return jif;

}

static inline __attribute__((always_inline)) u64 jiffies_64_to_clock_t(u64 x)
{
# 424 "include/linux/jiffies.h"
 x *= (( ((1000000UL * 1000 / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (((1000000UL * 1000 % (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))) << 8) + (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250))) / 2) / (( ((1193182 / ((1193182 + 250/2) / 250)) << 8) + (((1193182 % ((1193182 + 250/2) / 250)) << 8) + ((1193182 + 250/2) / 250) / 2) / ((1193182 + 250/2) / 250)))));
 ({ unsigned long __upper, __low, __high, __mod, __base; __base = (((1000000000L) / 100)); asm("":"=a" (__low), "=d" (__high):"A" (x)); __upper = __high; if (__high) { __upper = __high % (__base); __high = __high / (__base); } asm("divl %2":"=a" (__low), "=d" (__mod):"rm" (__base), "0" (__low), "1" (__upper)); asm("":"=A" (x):"a" (__low),"d" (__high)); __mod; });

 return x;
}

static inline __attribute__((always_inline)) u64 nsec_to_clock_t(u64 x)
{

 ({ unsigned long __upper, __low, __high, __mod, __base; __base = (((1000000000L) / 100)); asm("":"=a" (__low), "=d" (__high):"A" (x)); __upper = __high; if (__high) { __upper = __high % (__base); __high = __high / (__base); } asm("divl %2":"=a" (__low), "=d" (__mod):"rm" (__base), "0" (__low), "1" (__upper)); asm("":"=A" (x):"a" (__low),"d" (__high)); __mod; });
# 447 "include/linux/jiffies.h"
 return x;
}
# 13 "include/linux/sched.h" 2
# 1 "include/linux/rbtree.h" 1
# 100 "include/linux/rbtree.h"
struct rb_node
{
 struct rb_node *rb_parent;
 int rb_color;


 struct rb_node *rb_right;
 struct rb_node *rb_left;
};

struct rb_root
{
 struct rb_node *rb_node;
};




extern void rb_insert_color(struct rb_node *, struct rb_root *);
extern void rb_erase(struct rb_node *, struct rb_root *);


extern struct rb_node *rb_next(struct rb_node *);
extern struct rb_node *rb_prev(struct rb_node *);
extern struct rb_node *rb_first(struct rb_root *);
extern struct rb_node *rb_last(struct rb_root *);


extern void rb_replace_node(struct rb_node *victim, struct rb_node *new,
       struct rb_root *root);

static inline __attribute__((always_inline)) void rb_link_node(struct rb_node * node, struct rb_node * parent,
    struct rb_node ** rb_link)
{
 node->rb_parent = parent;
 node->rb_color = 0;
 node->rb_left = node->rb_right = ((void *)0);

 *rb_link = node;
}
# 14 "include/linux/sched.h" 2

# 1 "include/linux/cpumask.h" 1
# 82 "include/linux/cpumask.h"
# 1 "include/linux/bitmap.h" 1







# 1 "include/linux/string.h" 1
# 16 "include/linux/string.h"
extern char * strpbrk(const char *,const char *);
extern char * strsep(char **,const char *);
extern __kernel_size_t strspn(const char *,const char *);
extern __kernel_size_t strcspn(const char *,const char *);




# 1 "include/asm/string.h" 1
# 30 "include/asm/string.h"
static inline __attribute__((always_inline)) char * strcpy(char * dest,const char *src)
{
int d0, d1, d2;
__asm__ __volatile__(
 "1:\tlodsb\n\t"
 "stosb\n\t"
 "testb %%al,%%al\n\t"
 "jne 1b"
 : "=&S" (d0), "=&D" (d1), "=&a" (d2)
 :"0" (src),"1" (dest) : "memory");
return dest;
}


static inline __attribute__((always_inline)) char * strncpy(char * dest,const char *src,size_t count)
{
int d0, d1, d2, d3;
__asm__ __volatile__(
 "1:\tdecl %2\n\t"
 "js 2f\n\t"
 "lodsb\n\t"
 "stosb\n\t"
 "testb %%al,%%al\n\t"
 "jne 1b\n\t"
 "rep\n\t"
 "stosb\n"
 "2:"
 : "=&S" (d0), "=&D" (d1), "=&c" (d2), "=&a" (d3)
 :"0" (src),"1" (dest),"2" (count) : "memory");
return dest;
}


static inline __attribute__((always_inline)) char * strcat(char * dest,const char * src)
{
int d0, d1, d2, d3;
__asm__ __volatile__(
 "repne\n\t"
 "scasb\n\t"
 "decl %1\n"
 "1:\tlodsb\n\t"
 "stosb\n\t"
 "testb %%al,%%al\n\t"
 "jne 1b"
 : "=&S" (d0), "=&D" (d1), "=&a" (d2), "=&c" (d3)
 : "0" (src), "1" (dest), "2" (0), "3" (0xffffffffu):"memory");
return dest;
}


static inline __attribute__((always_inline)) char * strncat(char * dest,const char * src,size_t count)
{
int d0, d1, d2, d3;
__asm__ __volatile__(
 "repne\n\t"
 "scasb\n\t"
 "decl %1\n\t"
 "movl %8,%3\n"
 "1:\tdecl %3\n\t"
 "js 2f\n\t"
 "lodsb\n\t"
 "stosb\n\t"
 "testb %%al,%%al\n\t"
 "jne 1b\n"
 "2:\txorl %2,%2\n\t"
 "stosb"
 : "=&S" (d0), "=&D" (d1), "=&a" (d2), "=&c" (d3)
 : "0" (src),"1" (dest),"2" (0),"3" (0xffffffffu), "g" (count)
 : "memory");
return dest;
}


static inline __attribute__((always_inline)) int strcmp(const char * cs,const char * ct)
{
int d0, d1;
register int __res;
__asm__ __volatile__(
 "1:\tlodsb\n\t"
 "scasb\n\t"
 "jne 2f\n\t"
 "testb %%al,%%al\n\t"
 "jne 1b\n\t"
 "xorl %%eax,%%eax\n\t"
 "jmp 3f\n"
 "2:\tsbbl %%eax,%%eax\n\t"
 "orb $1,%%al\n"
 "3:"
 :"=a" (__res), "=&S" (d0), "=&D" (d1)
 :"1" (cs),"2" (ct)
 :"memory");
return __res;
}


static inline __attribute__((always_inline)) int strncmp(const char * cs,const char * ct,size_t count)
{
register int __res;
int d0, d1, d2;
__asm__ __volatile__(
 "1:\tdecl %3\n\t"
 "js 2f\n\t"
 "lodsb\n\t"
 "scasb\n\t"
 "jne 3f\n\t"
 "testb %%al,%%al\n\t"
 "jne 1b\n"
 "2:\txorl %%eax,%%eax\n\t"
 "jmp 4f\n"
 "3:\tsbbl %%eax,%%eax\n\t"
 "orb $1,%%al\n"
 "4:"
 :"=a" (__res), "=&S" (d0), "=&D" (d1), "=&c" (d2)
 :"1" (cs),"2" (ct),"3" (count)
 :"memory");
return __res;
}


static inline __attribute__((always_inline)) char * strchr(const char * s, int c)
{
int d0;
register char * __res;
__asm__ __volatile__(
 "movb %%al,%%ah\n"
 "1:\tlodsb\n\t"
 "cmpb %%ah,%%al\n\t"
 "je 2f\n\t"
 "testb %%al,%%al\n\t"
 "jne 1b\n\t"
 "movl $1,%1\n"
 "2:\tmovl %1,%0\n\t"
 "decl %0"
 :"=a" (__res), "=&S" (d0)
 :"1" (s),"0" (c)
 :"memory");
return __res;
}


static inline __attribute__((always_inline)) char * strrchr(const char * s, int c)
{
int d0, d1;
register char * __res;
__asm__ __volatile__(
 "movb %%al,%%ah\n"
 "1:\tlodsb\n\t"
 "cmpb %%ah,%%al\n\t"
 "jne 2f\n\t"
 "leal -1(%%esi),%0\n"
 "2:\ttestb %%al,%%al\n\t"
 "jne 1b"
 :"=g" (__res), "=&S" (d0), "=&a" (d1)
 :"0" (0),"1" (s),"2" (c)
 :"memory");
return __res;
}


static inline __attribute__((always_inline)) size_t strlen(const char * s)
{
int d0;
register int __res;
__asm__ __volatile__(
 "repne\n\t"
 "scasb\n\t"
 "notl %0\n\t"
 "decl %0"
 :"=c" (__res), "=&D" (d0)
 :"1" (s),"a" (0), "0" (0xffffffffu)
 :"memory");
return __res;
}

static inline __attribute__((always_inline)) void * __memcpy(void * to, const void * from, size_t n)
{
int d0, d1, d2;
__asm__ __volatile__(
 "rep ; movsl\n\t"
 "movl %4,%%ecx\n\t"
 "andl $3,%%ecx\n\t"

 "jz 1f\n\t"

 "rep ; movsb\n\t"
 "1:"
 : "=&c" (d0), "=&D" (d1), "=&S" (d2)
 : "0" (n/4), "g" (n), "1" ((long) to), "2" ((long) from)
 : "memory");
return (to);
}





static inline __attribute__((always_inline)) void * __constant_memcpy(void * to, const void * from, size_t n)
{
 long esi, edi;
 if (!n) return to;

 switch (n) {
  case 1: *(char*)to = *(char*)from; return to;
  case 2: *(short*)to = *(short*)from; return to;
  case 4: *(int*)to = *(int*)from; return to;

  case 3: *(short*)to = *(short*)from;
   *((char*)to+2) = *((char*)from+2); return to;
  case 5: *(int*)to = *(int*)from;
   *((char*)to+4) = *((char*)from+4); return to;
  case 6: *(int*)to = *(int*)from;
   *((short*)to+2) = *((short*)from+2); return to;
  case 8: *(int*)to = *(int*)from;
   *((int*)to+1) = *((int*)from+1); return to;

 }

 esi = (long) from;
 edi = (long) to;
 if (n >= 5*4) {

  int ecx;
  __asm__ __volatile__(
   "rep ; movsl"
   : "=&c" (ecx), "=&D" (edi), "=&S" (esi)
   : "0" (n/4), "1" (edi),"2" (esi)
   : "memory"
  );
 } else {

  if (n >= 4*4) __asm__ __volatile__("movsl"
   :"=&D"(edi),"=&S"(esi):"0"(edi),"1"(esi):"memory");
  if (n >= 3*4) __asm__ __volatile__("movsl"
   :"=&D"(edi),"=&S"(esi):"0"(edi),"1"(esi):"memory");
  if (n >= 2*4) __asm__ __volatile__("movsl"
   :"=&D"(edi),"=&S"(esi):"0"(edi),"1"(esi):"memory");
  if (n >= 1*4) __asm__ __volatile__("movsl"
   :"=&D"(edi),"=&S"(esi):"0"(edi),"1"(esi):"memory");
 }
 switch (n % 4) {

  case 0: return to;
  case 1: __asm__ __volatile__("movsb"
   :"=&D"(edi),"=&S"(esi):"0"(edi),"1"(esi):"memory");
   return to;
  case 2: __asm__ __volatile__("movsw"
   :"=&D"(edi),"=&S"(esi):"0"(edi),"1"(esi):"memory");
   return to;
  default: __asm__ __volatile__("movsw\n\tmovsb"
   :"=&D"(edi),"=&S"(esi):"0"(edi),"1"(esi):"memory");
   return to;
 }
}
# 331 "include/asm/string.h"
void *memmove(void * dest,const void * src, size_t n);




static inline __attribute__((always_inline)) void * memchr(const void * cs,int c,size_t count)
{
int d0;
register void * __res;
if (!count)
 return ((void *)0);
__asm__ __volatile__(
 "repne\n\t"
 "scasb\n\t"
 "je 1f\n\t"
 "movl $1,%0\n"
 "1:\tdecl %0"
 :"=D" (__res), "=&c" (d0)
 :"a" (c),"0" (cs),"1" (count)
 :"memory");
return __res;
}

static inline __attribute__((always_inline)) void * __memset_generic(void * s, char c,size_t count)
{
int d0, d1;
__asm__ __volatile__(
 "rep\n\t"
 "stosb"
 : "=&c" (d0), "=&D" (d1)
 :"a" (c),"1" (s),"0" (count)
 :"memory");
return s;
}
# 374 "include/asm/string.h"
static inline __attribute__((always_inline)) void * __constant_c_memset(void * s, unsigned long c, size_t count)
{
int d0, d1;
__asm__ __volatile__(
 "rep ; stosl\n\t"
 "testb $2,%b3\n\t"
 "je 1f\n\t"
 "stosw\n"
 "1:\ttestb $1,%b3\n\t"
 "je 2f\n\t"
 "stosb\n"
 "2:"
 :"=&c" (d0), "=&D" (d1)
 :"a" (c), "q" (count), "0" (count/4), "1" ((long) s)
 :"memory");
return (s);
}



static inline __attribute__((always_inline)) size_t strnlen(const char * s, size_t count)
{
int d0;
register int __res;
__asm__ __volatile__(
 "movl %2,%0\n\t"
 "jmp 2f\n"
 "1:\tcmpb $0,(%0)\n\t"
 "je 3f\n\t"
 "incl %0\n"
 "2:\tdecl %1\n\t"
 "cmpl $-1,%1\n\t"
 "jne 1b\n"
 "3:\tsubl %2,%0"
 :"=a" (__res), "=&d" (d0)
 :"c" (s),"1" (count)
 :"memory");
return __res;
}




extern char *strstr(const char *cs, const char *ct);





static inline __attribute__((always_inline)) void * __constant_c_and_count_memset(void * s, unsigned long pattern, size_t count)
{
 switch (count) {
  case 0:
   return s;
  case 1:
   *(unsigned char *)s = pattern;
   return s;
  case 2:
   *(unsigned short *)s = pattern;
   return s;
  case 3:
   *(unsigned short *)s = pattern;
   *(2+(unsigned char *)s) = pattern;
   return s;
  case 4:
   *(unsigned long *)s = pattern;
   return s;
 }







{
 int d0, d1;
 switch (count % 4) {
  case 0: __asm__ __volatile__( "rep ; stosl" "" : "=&c" (d0), "=&D" (d1) : "a" (pattern),"0" (count/4),"1" ((long) s) : "memory"); return s;
  case 1: __asm__ __volatile__( "rep ; stosl" "\n\tstosb" : "=&c" (d0), "=&D" (d1) : "a" (pattern),"0" (count/4),"1" ((long) s) : "memory"); return s;
  case 2: __asm__ __volatile__( "rep ; stosl" "\n\tstosw" : "=&c" (d0), "=&D" (d1) : "a" (pattern),"0" (count/4),"1" ((long) s) : "memory"); return s;
  default: __asm__ __volatile__( "rep ; stosl" "\n\tstosw\n\tstosb" : "=&c" (d0), "=&D" (d1) : "a" (pattern),"0" (count/4),"1" ((long) s) : "memory"); return s;
 }
}


}
# 486 "include/asm/string.h"
static inline __attribute__((always_inline)) void * memscan(void * addr, int c, size_t size)
{
 if (!size)
  return addr;
 __asm__("repnz; scasb\n\t"
  "jnz 1f\n\t"
  "dec %%edi\n"
  "1:"
  : "=D" (addr), "=c" (size)
  : "0" (addr), "1" (size), "a" (c)
  : "memory");
 return addr;
}
# 25 "include/linux/string.h" 2
# 33 "include/linux/string.h"
size_t strlcpy(char *, const char *, size_t);
# 42 "include/linux/string.h"
extern size_t strlcat(char *, const char *, __kernel_size_t);
# 51 "include/linux/string.h"
extern int strnicmp(const char *, const char *, __kernel_size_t);





extern char * strnchr(const char *, size_t, int);
# 85 "include/linux/string.h"
extern int __builtin_memcmp(const void *,const void *,__kernel_size_t);





extern char *kstrdup(const char *s, unsigned int gfp);
# 9 "include/linux/bitmap.h" 2
# 75 "include/linux/bitmap.h"
extern int __bitmap_empty(const unsigned long *bitmap, int bits);
extern int __bitmap_full(const unsigned long *bitmap, int bits);
extern int __bitmap_equal(const unsigned long *bitmap1,
                 const unsigned long *bitmap2, int bits);
extern void __bitmap_complement(unsigned long *dst, const unsigned long *src,
   int bits);
extern void __bitmap_shift_right(unsigned long *dst,
                        const unsigned long *src, int shift, int bits);
extern void __bitmap_shift_left(unsigned long *dst,
                        const unsigned long *src, int shift, int bits);
extern void __bitmap_and(unsigned long *dst, const unsigned long *bitmap1,
   const unsigned long *bitmap2, int bits);
extern void __bitmap_or(unsigned long *dst, const unsigned long *bitmap1,
   const unsigned long *bitmap2, int bits);
extern void __bitmap_xor(unsigned long *dst, const unsigned long *bitmap1,
   const unsigned long *bitmap2, int bits);
extern void __bitmap_andnot(unsigned long *dst, const unsigned long *bitmap1,
   const unsigned long *bitmap2, int bits);
extern int __bitmap_intersects(const unsigned long *bitmap1,
   const unsigned long *bitmap2, int bits);
extern int __bitmap_subset(const unsigned long *bitmap1,
   const unsigned long *bitmap2, int bits);
extern int __bitmap_weight(const unsigned long *bitmap, int bits);

extern int bitmap_scnprintf(char *buf, unsigned int len,
   const unsigned long *src, int nbits);
extern int bitmap_parse(const char *ubuf, unsigned int ulen,
   unsigned long *dst, int nbits);
extern int bitmap_scnlistprintf(char *buf, unsigned int len,
   const unsigned long *src, int nbits);
extern int bitmap_parselist(const char *buf, unsigned long *maskp,
   int nmaskbits);
extern int bitmap_find_free_region(unsigned long *bitmap, int bits, int order);
extern void bitmap_release_region(unsigned long *bitmap, int pos, int order);
extern int bitmap_allocate_region(unsigned long *bitmap, int pos, int order);







static inline __attribute__((always_inline)) void bitmap_zero(unsigned long *dst, int nbits)
{
 if (nbits <= 32)
  *dst = 0UL;
 else {
  int len = (((nbits)+32 -1)/32) * sizeof(unsigned long);
  __memset_generic((dst),(0),(len));
 }
}

static inline __attribute__((always_inline)) void bitmap_fill(unsigned long *dst, int nbits)
{
 size_t nlongs = (((nbits)+32 -1)/32);
 if (nlongs > 1) {
  int len = (nlongs - 1) * sizeof(unsigned long);
  __memset_generic((dst),(0xff),(len));
 }
 dst[nlongs - 1] = ( ((nbits) % 32) ? (1UL<<((nbits) % 32))-1 : ~0UL );
}

static inline __attribute__((always_inline)) void bitmap_copy(unsigned long *dst, const unsigned long *src,
   int nbits)
{
 if (nbits <= 32)
  *dst = *src;
 else {
  int len = (((nbits)+32 -1)/32) * sizeof(unsigned long);
  __memcpy(dst,src,len);
 }
}

static inline __attribute__((always_inline)) void bitmap_and(unsigned long *dst, const unsigned long *src1,
   const unsigned long *src2, int nbits)
{
 if (nbits <= 32)
  *dst = *src1 & *src2;
 else
  __bitmap_and(dst, src1, src2, nbits);
}

static inline __attribute__((always_inline)) void bitmap_or(unsigned long *dst, const unsigned long *src1,
   const unsigned long *src2, int nbits)
{
 if (nbits <= 32)
  *dst = *src1 | *src2;
 else
  __bitmap_or(dst, src1, src2, nbits);
}

static inline __attribute__((always_inline)) void bitmap_xor(unsigned long *dst, const unsigned long *src1,
   const unsigned long *src2, int nbits)
{
 if (nbits <= 32)
  *dst = *src1 ^ *src2;
 else
  __bitmap_xor(dst, src1, src2, nbits);
}

static inline __attribute__((always_inline)) void bitmap_andnot(unsigned long *dst, const unsigned long *src1,
   const unsigned long *src2, int nbits)
{
 if (nbits <= 32)
  *dst = *src1 & ~(*src2);
 else
  __bitmap_andnot(dst, src1, src2, nbits);
}

static inline __attribute__((always_inline)) void bitmap_complement(unsigned long *dst, const unsigned long *src,
   int nbits)
{
 if (nbits <= 32)
  *dst = ~(*src) & ( ((nbits) % 32) ? (1UL<<((nbits) % 32))-1 : ~0UL );
 else
  __bitmap_complement(dst, src, nbits);
}

static inline __attribute__((always_inline)) int bitmap_equal(const unsigned long *src1,
   const unsigned long *src2, int nbits)
{
 if (nbits <= 32)
  return ! ((*src1 ^ *src2) & ( ((nbits) % 32) ? (1UL<<((nbits) % 32))-1 : ~0UL ));
 else
  return __bitmap_equal(src1, src2, nbits);
}

static inline __attribute__((always_inline)) int bitmap_intersects(const unsigned long *src1,
   const unsigned long *src2, int nbits)
{
 if (nbits <= 32)
  return ((*src1 & *src2) & ( ((nbits) % 32) ? (1UL<<((nbits) % 32))-1 : ~0UL )) != 0;
 else
  return __bitmap_intersects(src1, src2, nbits);
}

static inline __attribute__((always_inline)) int bitmap_subset(const unsigned long *src1,
   const unsigned long *src2, int nbits)
{
 if (nbits <= 32)
  return ! ((*src1 & ~(*src2)) & ( ((nbits) % 32) ? (1UL<<((nbits) % 32))-1 : ~0UL ));
 else
  return __bitmap_subset(src1, src2, nbits);
}

static inline __attribute__((always_inline)) int bitmap_empty(const unsigned long *src, int nbits)
{
 if (nbits <= 32)
  return ! (*src & ( ((nbits) % 32) ? (1UL<<((nbits) % 32))-1 : ~0UL ));
 else
  return __bitmap_empty(src, nbits);
}

static inline __attribute__((always_inline)) int bitmap_full(const unsigned long *src, int nbits)
{
 if (nbits <= 32)
  return ! (~(*src) & ( ((nbits) % 32) ? (1UL<<((nbits) % 32))-1 : ~0UL ));
 else
  return __bitmap_full(src, nbits);
}

static inline __attribute__((always_inline)) int bitmap_weight(const unsigned long *src, int nbits)
{
 return __bitmap_weight(src, nbits);
}

static inline __attribute__((always_inline)) void bitmap_shift_right(unsigned long *dst,
   const unsigned long *src, int n, int nbits)
{
 if (nbits <= 32)
  *dst = *src >> n;
 else
  __bitmap_shift_right(dst, src, n, nbits);
}

static inline __attribute__((always_inline)) void bitmap_shift_left(unsigned long *dst,
   const unsigned long *src, int n, int nbits)
{
 if (nbits <= 32)
  *dst = (*src << n) & ( ((nbits) % 32) ? (1UL<<((nbits) % 32))-1 : ~0UL );
 else
  __bitmap_shift_left(dst, src, n, nbits);
}
# 83 "include/linux/cpumask.h" 2


typedef struct { unsigned long bits[(((8)+32 -1)/32)]; } cpumask_t;
extern cpumask_t _unused_cpumask_arg_;


static inline __attribute__((always_inline)) void __cpu_set(int cpu, volatile cpumask_t *dstp)
{
 set_bit(cpu, dstp->bits);
}


static inline __attribute__((always_inline)) void __cpu_clear(int cpu, volatile cpumask_t *dstp)
{
 clear_bit(cpu, dstp->bits);
}


static inline __attribute__((always_inline)) void __cpus_setall(cpumask_t *dstp, int nbits)
{
 bitmap_fill(dstp->bits, nbits);
}


static inline __attribute__((always_inline)) void __cpus_clear(cpumask_t *dstp, int nbits)
{
 bitmap_zero(dstp->bits, nbits);
}





static inline __attribute__((always_inline)) int __cpu_test_and_set(int cpu, cpumask_t *addr)
{
 return test_and_set_bit(cpu, addr->bits);
}


static inline __attribute__((always_inline)) void __cpus_and(cpumask_t *dstp, const cpumask_t *src1p,
     const cpumask_t *src2p, int nbits)
{
 bitmap_and(dstp->bits, src1p->bits, src2p->bits, nbits);
}


static inline __attribute__((always_inline)) void __cpus_or(cpumask_t *dstp, const cpumask_t *src1p,
     const cpumask_t *src2p, int nbits)
{
 bitmap_or(dstp->bits, src1p->bits, src2p->bits, nbits);
}


static inline __attribute__((always_inline)) void __cpus_xor(cpumask_t *dstp, const cpumask_t *src1p,
     const cpumask_t *src2p, int nbits)
{
 bitmap_xor(dstp->bits, src1p->bits, src2p->bits, nbits);
}



static inline __attribute__((always_inline)) void __cpus_andnot(cpumask_t *dstp, const cpumask_t *src1p,
     const cpumask_t *src2p, int nbits)
{
 bitmap_andnot(dstp->bits, src1p->bits, src2p->bits, nbits);
}


static inline __attribute__((always_inline)) void __cpus_complement(cpumask_t *dstp,
     const cpumask_t *srcp, int nbits)
{
 bitmap_complement(dstp->bits, srcp->bits, nbits);
}


static inline __attribute__((always_inline)) int __cpus_equal(const cpumask_t *src1p,
     const cpumask_t *src2p, int nbits)
{
 return bitmap_equal(src1p->bits, src2p->bits, nbits);
}


static inline __attribute__((always_inline)) int __cpus_intersects(const cpumask_t *src1p,
     const cpumask_t *src2p, int nbits)
{
 return bitmap_intersects(src1p->bits, src2p->bits, nbits);
}


static inline __attribute__((always_inline)) int __cpus_subset(const cpumask_t *src1p,
     const cpumask_t *src2p, int nbits)
{
 return bitmap_subset(src1p->bits, src2p->bits, nbits);
}


static inline __attribute__((always_inline)) int __cpus_empty(const cpumask_t *srcp, int nbits)
{
 return bitmap_empty(srcp->bits, nbits);
}


static inline __attribute__((always_inline)) int __cpus_full(const cpumask_t *srcp, int nbits)
{
 return bitmap_full(srcp->bits, nbits);
}


static inline __attribute__((always_inline)) int __cpus_weight(const cpumask_t *srcp, int nbits)
{
 return bitmap_weight(srcp->bits, nbits);
}



static inline __attribute__((always_inline)) void __cpus_shift_right(cpumask_t *dstp,
     const cpumask_t *srcp, int n, int nbits)
{
 bitmap_shift_right(dstp->bits, srcp->bits, n, nbits);
}



static inline __attribute__((always_inline)) void __cpus_shift_left(cpumask_t *dstp,
     const cpumask_t *srcp, int n, int nbits)
{
 bitmap_shift_left(dstp->bits, srcp->bits, n, nbits);
}


static inline __attribute__((always_inline)) int __first_cpu(const cpumask_t *srcp, int nbits)
{
 return ({ int __x = (nbits); int __y = (find_first_bit(srcp->bits, nbits)); __x < __y ? __x: __y; });
}


static inline __attribute__((always_inline)) int __next_cpu(int n, const cpumask_t *srcp, int nbits)
{
 return ({ int __x = (nbits); int __y = (find_next_bit(srcp->bits, nbits, n+1)); __x < __y ? __x: __y; });
}
# 269 "include/linux/cpumask.h"
static inline __attribute__((always_inline)) int __cpumask_scnprintf(char *buf, int len,
     const cpumask_t *srcp, int nbits)
{
 return bitmap_scnprintf(buf, len, srcp->bits, nbits);
}



static inline __attribute__((always_inline)) int __cpumask_parse(const char *buf, int len,
     cpumask_t *dstp, int nbits)
{
 return bitmap_parse(buf, len, dstp->bits, nbits);
}



static inline __attribute__((always_inline)) int __cpulist_scnprintf(char *buf, int len,
     const cpumask_t *srcp, int nbits)
{
 return bitmap_scnlistprintf(buf, len, srcp->bits, nbits);
}


static inline __attribute__((always_inline)) int __cpulist_parse(const char *buf, cpumask_t *dstp, int nbits)
{
 return bitmap_parselist(buf, dstp->bits, nbits);
}
# 362 "include/linux/cpumask.h"
extern cpumask_t cpu_possible_map;
extern cpumask_t cpu_online_map;
extern cpumask_t cpu_present_map;
# 16 "include/linux/sched.h" 2
# 1 "include/linux/errno.h" 1



# 1 "include/asm/errno.h" 1



# 1 "include/asm-generic/errno.h" 1



# 1 "include/asm-generic/errno-base.h" 1
# 5 "include/asm-generic/errno.h" 2
# 5 "include/asm/errno.h" 2
# 5 "include/linux/errno.h" 2
# 17 "include/linux/sched.h" 2
# 1 "include/linux/nodemask.h" 1
# 82 "include/linux/nodemask.h"
# 1 "include/linux/numa.h" 1
# 83 "include/linux/nodemask.h" 2


typedef struct { unsigned long bits[((((1 << 0))+32 -1)/32)]; } nodemask_t;
extern nodemask_t _unused_nodemask_arg_;


static inline __attribute__((always_inline)) void __node_set(int node, volatile nodemask_t *dstp)
{
 set_bit(node, dstp->bits);
}


static inline __attribute__((always_inline)) void __node_clear(int node, volatile nodemask_t *dstp)
{
 clear_bit(node, dstp->bits);
}


static inline __attribute__((always_inline)) void __nodes_setall(nodemask_t *dstp, int nbits)
{
 bitmap_fill(dstp->bits, nbits);
}


static inline __attribute__((always_inline)) void __nodes_clear(nodemask_t *dstp, int nbits)
{
 bitmap_zero(dstp->bits, nbits);
}






static inline __attribute__((always_inline)) int __node_test_and_set(int node, nodemask_t *addr)
{
 return test_and_set_bit(node, addr->bits);
}



static inline __attribute__((always_inline)) void __nodes_and(nodemask_t *dstp, const nodemask_t *src1p,
     const nodemask_t *src2p, int nbits)
{
 bitmap_and(dstp->bits, src1p->bits, src2p->bits, nbits);
}



static inline __attribute__((always_inline)) void __nodes_or(nodemask_t *dstp, const nodemask_t *src1p,
     const nodemask_t *src2p, int nbits)
{
 bitmap_or(dstp->bits, src1p->bits, src2p->bits, nbits);
}



static inline __attribute__((always_inline)) void __nodes_xor(nodemask_t *dstp, const nodemask_t *src1p,
     const nodemask_t *src2p, int nbits)
{
 bitmap_xor(dstp->bits, src1p->bits, src2p->bits, nbits);
}



static inline __attribute__((always_inline)) void __nodes_andnot(nodemask_t *dstp, const nodemask_t *src1p,
     const nodemask_t *src2p, int nbits)
{
 bitmap_andnot(dstp->bits, src1p->bits, src2p->bits, nbits);
}



static inline __attribute__((always_inline)) void __nodes_complement(nodemask_t *dstp,
     const nodemask_t *srcp, int nbits)
{
 bitmap_complement(dstp->bits, srcp->bits, nbits);
}



static inline __attribute__((always_inline)) int __nodes_equal(const nodemask_t *src1p,
     const nodemask_t *src2p, int nbits)
{
 return bitmap_equal(src1p->bits, src2p->bits, nbits);
}



static inline __attribute__((always_inline)) int __nodes_intersects(const nodemask_t *src1p,
     const nodemask_t *src2p, int nbits)
{
 return bitmap_intersects(src1p->bits, src2p->bits, nbits);
}



static inline __attribute__((always_inline)) int __nodes_subset(const nodemask_t *src1p,
     const nodemask_t *src2p, int nbits)
{
 return bitmap_subset(src1p->bits, src2p->bits, nbits);
}


static inline __attribute__((always_inline)) int __nodes_empty(const nodemask_t *srcp, int nbits)
{
 return bitmap_empty(srcp->bits, nbits);
}


static inline __attribute__((always_inline)) int __nodes_full(const nodemask_t *srcp, int nbits)
{
 return bitmap_full(srcp->bits, nbits);
}


static inline __attribute__((always_inline)) int __nodes_weight(const nodemask_t *srcp, int nbits)
{
 return bitmap_weight(srcp->bits, nbits);
}



static inline __attribute__((always_inline)) void __nodes_shift_right(nodemask_t *dstp,
     const nodemask_t *srcp, int n, int nbits)
{
 bitmap_shift_right(dstp->bits, srcp->bits, n, nbits);
}



static inline __attribute__((always_inline)) void __nodes_shift_left(nodemask_t *dstp,
     const nodemask_t *srcp, int n, int nbits)
{
 bitmap_shift_left(dstp->bits, srcp->bits, n, nbits);
}





static inline __attribute__((always_inline)) int __first_node(const nodemask_t *srcp)
{
 return ({ int __x = ((1 << 0)); int __y = (find_first_bit(srcp->bits, (1 << 0))); __x < __y ? __x: __y; });
}


static inline __attribute__((always_inline)) int __next_node(int n, const nodemask_t *srcp)
{
 return ({ int __x = ((1 << 0)); int __y = (find_next_bit(srcp->bits, (1 << 0), n+1)); __x < __y ? __x: __y; });
}
# 248 "include/linux/nodemask.h"
static inline __attribute__((always_inline)) int __first_unset_node(const nodemask_t *maskp)
{
 return ({ int __x = ((1 << 0)); int __y = (find_first_zero_bit(maskp->bits, (1 << 0))); __x < __y ? __x: __y; });

}
# 282 "include/linux/nodemask.h"
static inline __attribute__((always_inline)) int __nodemask_scnprintf(char *buf, int len,
     const nodemask_t *srcp, int nbits)
{
 return bitmap_scnprintf(buf, len, srcp->bits, nbits);
}



static inline __attribute__((always_inline)) int __nodemask_parse(const char *buf, int len,
     nodemask_t *dstp, int nbits)
{
 return bitmap_parse(buf, len, dstp->bits, nbits);
}



static inline __attribute__((always_inline)) int __nodelist_scnprintf(char *buf, int len,
     const nodemask_t *srcp, int nbits)
{
 return bitmap_scnlistprintf(buf, len, srcp->bits, nbits);
}


static inline __attribute__((always_inline)) int __nodelist_parse(const char *buf, nodemask_t *dstp, int nbits)
{
 return bitmap_parselist(buf, dstp->bits, nbits);
}
# 326 "include/linux/nodemask.h"
extern nodemask_t node_online_map;
extern nodemask_t node_possible_map;
# 18 "include/linux/sched.h" 2


# 1 "include/asm/semaphore.h" 1
# 41 "include/asm/semaphore.h"
# 1 "include/linux/wait.h" 1
# 23 "include/linux/wait.h"
# 1 "include/linux/list.h" 1






# 1 "include/linux/prefetch.h" 1
# 58 "include/linux/prefetch.h"
static inline __attribute__((always_inline)) void prefetch_range(void *addr, size_t len)
{

 char *cp;
 char *end = addr + len;

 for (cp = addr; cp < end; cp += (4*(1 << (7))))
  prefetch(cp);

}
# 8 "include/linux/list.h" 2
# 28 "include/linux/list.h"
struct list_head {
 struct list_head *next, *prev;
};
# 47 "include/linux/list.h"
static inline __attribute__((always_inline)) void __list_add(struct list_head *new,
         struct list_head *prev,
         struct list_head *next)
{
 next->prev = new;
 new->next = next;
 new->prev = prev;
 prev->next = new;
}
# 65 "include/linux/list.h"
static inline __attribute__((always_inline)) void list_add(struct list_head *new, struct list_head *head)
{
 __list_add(new, head, head->next);
}
# 78 "include/linux/list.h"
static inline __attribute__((always_inline)) void list_add_tail(struct list_head *new, struct list_head *head)
{
 __list_add(new, head->prev, head);
}







static inline __attribute__((always_inline)) void __list_add_rcu(struct list_head * new,
  struct list_head * prev, struct list_head * next)
{
 new->next = next;
 new->prev = prev;
 __asm__ __volatile__ ("": : :"memory");
 next->prev = new;
 prev->next = new;
}
# 115 "include/linux/list.h"
static inline __attribute__((always_inline)) void list_add_rcu(struct list_head *new, struct list_head *head)
{
 __list_add_rcu(new, head, head->next);
}
# 136 "include/linux/list.h"
static inline __attribute__((always_inline)) void list_add_tail_rcu(struct list_head *new,
     struct list_head *head)
{
 __list_add_rcu(new, head->prev, head);
}
# 149 "include/linux/list.h"
static inline __attribute__((always_inline)) void __list_del(struct list_head * prev, struct list_head * next)
{
 next->prev = prev;
 prev->next = next;
}







static inline __attribute__((always_inline)) void list_del(struct list_head *entry)
{
 __list_del(entry->prev, entry->next);
 entry->next = ((void *) 0x00100100);
 entry->prev = ((void *) 0x00200200);
}
# 192 "include/linux/list.h"
static inline __attribute__((always_inline)) void list_del_rcu(struct list_head *entry)
{
 __list_del(entry->prev, entry->next);
 entry->prev = ((void *) 0x00200200);
}
# 205 "include/linux/list.h"
static inline __attribute__((always_inline)) void list_replace_rcu(struct list_head *old, struct list_head *new){
 new->next = old->next;
 new->prev = old->prev;
 __asm__ __volatile__ ("": : :"memory");
 new->next->prev = new;
 new->prev->next = new;
}





static inline __attribute__((always_inline)) void list_del_init(struct list_head *entry)
{
 __list_del(entry->prev, entry->next);
 do { (entry)->next = (entry); (entry)->prev = (entry); } while (0);
}






static inline __attribute__((always_inline)) void list_move(struct list_head *list, struct list_head *head)
{
        __list_del(list->prev, list->next);
        list_add(list, head);
}






static inline __attribute__((always_inline)) void list_move_tail(struct list_head *list,
      struct list_head *head)
{
        __list_del(list->prev, list->next);
        list_add_tail(list, head);
}





static inline __attribute__((always_inline)) int list_empty(const struct list_head *head)
{
 return head->next == head;
}
# 267 "include/linux/list.h"
static inline __attribute__((always_inline)) int list_empty_careful(const struct list_head *head)
{
 struct list_head *next = head->next;
 return (next == head) && (next == head->prev);
}

static inline __attribute__((always_inline)) void __list_splice(struct list_head *list,
     struct list_head *head)
{
 struct list_head *first = list->next;
 struct list_head *last = list->prev;
 struct list_head *at = head->next;

 first->prev = head;
 head->next = first;

 last->next = at;
 at->prev = last;
}






static inline __attribute__((always_inline)) void list_splice(struct list_head *list, struct list_head *head)
{
 if (!list_empty(list))
  __list_splice(list, head);
}
# 305 "include/linux/list.h"
static inline __attribute__((always_inline)) void list_splice_init(struct list_head *list,
        struct list_head *head)
{
 if (!list_empty(list)) {
  __list_splice(list, head);
  do { (list)->next = (list); (list)->prev = (list); } while (0);
 }
}
# 491 "include/linux/list.h"
struct hlist_head {
 struct hlist_node *first;
};

struct hlist_node {
 struct hlist_node *next, **pprev;
};






static inline __attribute__((always_inline)) int hlist_unhashed(const struct hlist_node *h)
{
 return !h->pprev;
}

static inline __attribute__((always_inline)) int hlist_empty(const struct hlist_head *h)
{
 return !h->first;
}

static inline __attribute__((always_inline)) void __hlist_del(struct hlist_node *n)
{
 struct hlist_node *next = n->next;
 struct hlist_node **pprev = n->pprev;
 *pprev = next;
 if (next)
  next->pprev = pprev;
}

static inline __attribute__((always_inline)) void hlist_del(struct hlist_node *n)
{
 __hlist_del(n);
 n->next = ((void *) 0x00100100);
 n->pprev = ((void *) 0x00200200);
}
# 549 "include/linux/list.h"
static inline __attribute__((always_inline)) void hlist_del_rcu(struct hlist_node *n)
{
 __hlist_del(n);
 n->pprev = ((void *) 0x00200200);
}

static inline __attribute__((always_inline)) void hlist_del_init(struct hlist_node *n)
{
 if (n->pprev) {
  __hlist_del(n);
  ((n)->next = ((void *)0), (n)->pprev = ((void *)0));
 }
}

static inline __attribute__((always_inline)) void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
 struct hlist_node *first = h->first;
 n->next = first;
 if (first)
  first->pprev = &n->next;
 h->first = n;
 n->pprev = &h->first;
}
# 590 "include/linux/list.h"
static inline __attribute__((always_inline)) void hlist_add_head_rcu(struct hlist_node *n,
     struct hlist_head *h)
{
 struct hlist_node *first = h->first;
 n->next = first;
 n->pprev = &h->first;
 __asm__ __volatile__ ("": : :"memory");
 if (first)
  first->pprev = &n->next;
 h->first = n;
}


static inline __attribute__((always_inline)) void hlist_add_before(struct hlist_node *n,
     struct hlist_node *next)
{
 n->pprev = next->pprev;
 n->next = next;
 next->pprev = &n->next;
 *(n->pprev) = n;
}

static inline __attribute__((always_inline)) void hlist_add_after(struct hlist_node *n,
     struct hlist_node *next)
{
 next->next = n->next;
 n->next = next;
 next->pprev = &n->next;

 if(next->next)
  next->next->pprev = &next->next;
}
# 24 "include/linux/wait.h" 2



# 1 "include/asm/current.h" 1





struct task_struct;

static inline __attribute__((always_inline)) struct task_struct * get_current(void)
{
 return current_thread_info()->task;
}
# 28 "include/linux/wait.h" 2

typedef struct __wait_queue wait_queue_t;
typedef int (*wait_queue_func_t)(wait_queue_t *wait, unsigned mode, int sync, void *key);
int default_wake_function(wait_queue_t *wait, unsigned mode, int sync, void *key);

struct __wait_queue {
 unsigned int flags;

 void *private;
 wait_queue_func_t func;
 struct list_head task_list;
};

struct wait_bit_key {
 void *flags;
 int bit_nr;
};

struct wait_bit_queue {
 struct wait_bit_key key;
 wait_queue_t wait;
};

struct __wait_queue_head {
 spinlock_t lock;
 struct list_head task_list;
};
typedef struct __wait_queue_head wait_queue_head_t;
# 80 "include/linux/wait.h"
static inline __attribute__((always_inline)) void init_waitqueue_head(wait_queue_head_t *q)
{
 do { *(&q->lock) = (spinlock_t) { 1 , 0xdead4ead }; } while(0);
 do { (&q->task_list)->next = (&q->task_list); (&q->task_list)->prev = (&q->task_list); } while (0);
}

static inline __attribute__((always_inline)) void init_waitqueue_entry(wait_queue_t *q, struct task_struct *p)
{
 q->flags = 0;
 q->private = p;
 q->func = default_wake_function;
}

static inline __attribute__((always_inline)) void init_waitqueue_func_entry(wait_queue_t *q,
     wait_queue_func_t func)
{
 q->flags = 0;
 q->private = ((void *)0);
 q->func = func;
}

static inline __attribute__((always_inline)) int waitqueue_active(wait_queue_head_t *q)
{
 return !list_empty(&q->task_list);
}
# 115 "include/linux/wait.h"
extern void add_wait_queue(wait_queue_head_t *q, wait_queue_t * wait) __attribute__((regparm(3)));
extern void add_wait_queue_exclusive(wait_queue_head_t *q, wait_queue_t * wait) __attribute__((regparm(3)));
extern void remove_wait_queue(wait_queue_head_t *q, wait_queue_t * wait) __attribute__((regparm(3)));

static inline __attribute__((always_inline)) void __add_wait_queue(wait_queue_head_t *head, wait_queue_t *new)
{
 list_add(&new->task_list, &head->task_list);
}




static inline __attribute__((always_inline)) void __add_wait_queue_tail(wait_queue_head_t *head,
      wait_queue_t *new)
{
 list_add_tail(&new->task_list, &head->task_list);
}

static inline __attribute__((always_inline)) void __remove_wait_queue(wait_queue_head_t *head,
       wait_queue_t *old)
{
 list_del(&old->task_list);
}

void __wake_up(wait_queue_head_t *q, unsigned int mode, int nr, void *key) __attribute__((regparm(3)));
extern void __wake_up_locked(wait_queue_head_t *q, unsigned int mode) __attribute__((regparm(3)));
extern void __wake_up_sync(wait_queue_head_t *q, unsigned int mode, int nr) __attribute__((regparm(3)));
void __wake_up_bit(wait_queue_head_t *, void *, int) __attribute__((regparm(3)));
int __wait_on_bit(wait_queue_head_t *, struct wait_bit_queue *, int (*)(void *), unsigned) __attribute__((regparm(3)));
int __wait_on_bit_lock(wait_queue_head_t *, struct wait_bit_queue *, int (*)(void *), unsigned) __attribute__((regparm(3)));
void wake_up_bit(void *, int) __attribute__((regparm(3)));
int out_of_line_wait_on_bit(void *, int, int (*)(void *), unsigned) __attribute__((regparm(3)));
int out_of_line_wait_on_bit_lock(void *, int, int (*)(void *), unsigned) __attribute__((regparm(3)));
wait_queue_head_t *bit_waitqueue(void *, int) __attribute__((regparm(3)));
# 346 "include/linux/wait.h"
static inline __attribute__((always_inline)) void add_wait_queue_exclusive_locked(wait_queue_head_t *q,
         wait_queue_t * wait)
{
 wait->flags |= 0x01;
 __add_wait_queue_tail(q, wait);
}




static inline __attribute__((always_inline)) void remove_wait_queue_locked(wait_queue_head_t *q,
         wait_queue_t * wait)
{
 __remove_wait_queue(q, wait);
}






extern void sleep_on(wait_queue_head_t *q) __attribute__((regparm(3)));
extern long sleep_on_timeout(wait_queue_head_t *q, signed long timeout) __attribute__((regparm(3)));

extern void interruptible_sleep_on(wait_queue_head_t *q) __attribute__((regparm(3)));
extern long interruptible_sleep_on_timeout(wait_queue_head_t *q, signed long timeout) __attribute__((regparm(3)));





void prepare_to_wait(wait_queue_head_t *q, wait_queue_t *wait, int state) __attribute__((regparm(3)));

void prepare_to_wait_exclusive(wait_queue_head_t *q, wait_queue_t *wait, int state) __attribute__((regparm(3)));

void finish_wait(wait_queue_head_t *q, wait_queue_t *wait) __attribute__((regparm(3)));
int autoremove_wake_function(wait_queue_t *wait, unsigned mode, int sync, void *key);
int wake_bit_function(wait_queue_t *wait, unsigned mode, int sync, void *key);
# 424 "include/linux/wait.h"
static inline __attribute__((always_inline)) int wait_on_bit(void *word, int bit,
    int (*action)(void *), unsigned mode)
{
 if (!(__builtin_constant_p(bit) ? constant_test_bit((bit),(word)) : variable_test_bit((bit),(word))))
  return 0;
 return out_of_line_wait_on_bit(word, bit, action, mode);
}
# 448 "include/linux/wait.h"
static inline __attribute__((always_inline)) int wait_on_bit_lock(void *word, int bit,
    int (*action)(void *), unsigned mode)
{
 if (!test_and_set_bit(bit, word))
  return 0;
 return out_of_line_wait_on_bit_lock(word, bit, action, mode);
}
# 42 "include/asm/semaphore.h" 2
# 1 "include/linux/rwsem.h" 1
# 22 "include/linux/rwsem.h"
struct rw_semaphore;




# 1 "include/asm/rwsem.h" 1
# 44 "include/asm/rwsem.h"
struct rwsem_waiter;

extern struct rw_semaphore *rwsem_down_read_failed(struct rw_semaphore *sem) __attribute__((regparm(3)));
extern struct rw_semaphore *rwsem_down_write_failed(struct rw_semaphore *sem) __attribute__((regparm(3)));
extern struct rw_semaphore *rwsem_wake(struct rw_semaphore *) __attribute__((regparm(3)));
extern struct rw_semaphore *rwsem_downgrade_wake(struct rw_semaphore *sem) __attribute__((regparm(3)));




struct rw_semaphore {
 signed long count;






 spinlock_t wait_lock;
 struct list_head wait_list;



};
# 85 "include/asm/rwsem.h"
static inline __attribute__((always_inline)) void init_rwsem(struct rw_semaphore *sem)
{
 sem->count = 0x00000000;
 do { *(&sem->wait_lock) = (spinlock_t) { 1 , 0xdead4ead }; } while(0);
 do { (&sem->wait_list)->next = (&sem->wait_list); (&sem->wait_list)->prev = (&sem->wait_list); } while (0);



}




static inline __attribute__((always_inline)) void __down_read(struct rw_semaphore *sem)
{
 __asm__ __volatile__(
  "# beginning down_read\n\t"
"lock ; " "  incl      (%%eax)\n\t"
  "  js        2f\n\t"
  "1:\n\t"
  ".subsection 1\n\t" "" ".ifndef " ".text.lock." "tcp_ipv6" "\n\t" ".text.lock." "tcp_ipv6" ":\n\t" ".endif\n"
  "2:\n\t"
  "  pushl     %%ecx\n\t"
  "  pushl     %%edx\n\t"
  "  call      rwsem_down_read_failed\n\t"
  "  popl      %%edx\n\t"
  "  popl      %%ecx\n\t"
  "  jmp       1b\n"
  ".previous\n\t"
  "# ending down_read\n\t"
  : "=m"(sem->count)
  : "a"(sem), "m"(sem->count)
  : "memory", "cc");
}




static inline __attribute__((always_inline)) int __down_read_trylock(struct rw_semaphore *sem)
{
 __s32 result, tmp;
 __asm__ __volatile__(
  "# beginning __down_read_trylock\n\t"
  "  movl      %0,%1\n\t"
  "1:\n\t"
  "  movl	     %1,%2\n\t"
  "  addl      %3,%2\n\t"
  "  jle	     2f\n\t"
"lock ; " "  cmpxchgl  %2,%0\n\t"
  "  jnz	     1b\n\t"
  "2:\n\t"
  "# ending __down_read_trylock\n\t"
  : "+m"(sem->count), "=&a"(result), "=&r"(tmp)
  : "i"(0x00000001)
  : "memory", "cc");
 return result>=0 ? 1 : 0;
}




static inline __attribute__((always_inline)) void __down_write(struct rw_semaphore *sem)
{
 int tmp;

 tmp = ((-0x00010000) + 0x00000001);
 __asm__ __volatile__(
  "# beginning down_write\n\t"
"lock ; " "  xadd      %%edx,(%%eax)\n\t"
  "  testl     %%edx,%%edx\n\t"
  "  jnz       2f\n\t"
  "1:\n\t"
  ".subsection 1\n\t" "" ".ifndef " ".text.lock." "tcp_ipv6" "\n\t" ".text.lock." "tcp_ipv6" ":\n\t" ".endif\n"
  "2:\n\t"
  "  pushl     %%ecx\n\t"
  "  call      rwsem_down_write_failed\n\t"
  "  popl      %%ecx\n\t"
  "  jmp       1b\n"
  ".previous\n\t"
  "# ending down_write"
  : "=m"(sem->count), "=d"(tmp)
  : "a"(sem), "1"(tmp), "m"(sem->count)
  : "memory", "cc");
}




static inline __attribute__((always_inline)) int __down_write_trylock(struct rw_semaphore *sem)
{
 signed long ret = ((__typeof__(*(&sem->count)))__cmpxchg((&sem->count),(unsigned long)(0x00000000), (unsigned long)(((-0x00010000) + 0x00000001)),sizeof(*(&sem->count))));


 if (ret == 0x00000000)
  return 1;
 return 0;
}




static inline __attribute__((always_inline)) void __up_read(struct rw_semaphore *sem)
{
 __s32 tmp = -0x00000001;
 __asm__ __volatile__(
  "# beginning __up_read\n\t"
"lock ; " "  xadd      %%edx,(%%eax)\n\t"
  "  js        2f\n\t"
  "1:\n\t"
  ".subsection 1\n\t" "" ".ifndef " ".text.lock." "tcp_ipv6" "\n\t" ".text.lock." "tcp_ipv6" ":\n\t" ".endif\n"
  "2:\n\t"
  "  decw      %%dx\n\t"
  "  jnz       1b\n\t"
  "  pushl     %%ecx\n\t"
  "  call      rwsem_wake\n\t"
  "  popl      %%ecx\n\t"
  "  jmp       1b\n"
  ".previous\n\t"
  "# ending __up_read\n"
  : "=m"(sem->count), "=d"(tmp)
  : "a"(sem), "1"(tmp), "m"(sem->count)
  : "memory", "cc");
}




static inline __attribute__((always_inline)) void __up_write(struct rw_semaphore *sem)
{
 __asm__ __volatile__(
  "# beginning __up_write\n\t"
  "  movl      %2,%%edx\n\t"
"lock ; " "  xaddl     %%edx,(%%eax)\n\t"
  "  jnz       2f\n\t"
  "1:\n\t"
  ".subsection 1\n\t" "" ".ifndef " ".text.lock." "tcp_ipv6" "\n\t" ".text.lock." "tcp_ipv6" ":\n\t" ".endif\n"
  "2:\n\t"
  "  decw      %%dx\n\t"
  "  jnz       1b\n\t"
  "  pushl     %%ecx\n\t"
  "  call      rwsem_wake\n\t"
  "  popl      %%ecx\n\t"
  "  jmp       1b\n"
  ".previous\n\t"
  "# ending __up_write\n"
  : "=m"(sem->count)
  : "a"(sem), "i"(-((-0x00010000) + 0x00000001)), "m"(sem->count)
  : "memory", "cc", "edx");
}




static inline __attribute__((always_inline)) void __downgrade_write(struct rw_semaphore *sem)
{
 __asm__ __volatile__(
  "# beginning __downgrade_write\n\t"
"lock ; " "  addl      %2,(%%eax)\n\t"
  "  js        2f\n\t"
  "1:\n\t"
  ".subsection 1\n\t" "" ".ifndef " ".text.lock." "tcp_ipv6" "\n\t" ".text.lock." "tcp_ipv6" ":\n\t" ".endif\n"
  "2:\n\t"
  "  pushl     %%ecx\n\t"
  "  pushl     %%edx\n\t"
  "  call      rwsem_downgrade_wake\n\t"
  "  popl      %%edx\n\t"
  "  popl      %%ecx\n\t"
  "  jmp       1b\n"
  ".previous\n\t"
  "# ending __downgrade_write\n"
  : "=m"(sem->count)
  : "a"(sem), "i"(-(-0x00010000)), "m"(sem->count)
  : "memory", "cc");
}




static inline __attribute__((always_inline)) void rwsem_atomic_add(int delta, struct rw_semaphore *sem)
{
 __asm__ __volatile__(
"lock ; " "addl %1,%0"
  : "=m"(sem->count)
  : "ir"(delta), "m"(sem->count));
}




static inline __attribute__((always_inline)) int rwsem_atomic_update(int delta, struct rw_semaphore *sem)
{
 int tmp = delta;

 __asm__ __volatile__(
"lock ; " "xadd %0,(%2)"
  : "+r"(tmp), "=m"(sem->count)
  : "r"(sem), "m"(sem->count)
  : "memory");

 return tmp+delta;
}
# 28 "include/linux/rwsem.h" 2
# 41 "include/linux/rwsem.h"
static inline __attribute__((always_inline)) void down_read(struct rw_semaphore *sem)
{
 do { __might_sleep("include/linux/rwsem.h", 43); do { } while (0); } while (0);
 ;
 __down_read(sem);
 ;
}




static inline __attribute__((always_inline)) int down_read_trylock(struct rw_semaphore *sem)
{
 int ret;
 ;
 ret = __down_read_trylock(sem);
 ;
 return ret;
}




static inline __attribute__((always_inline)) void down_write(struct rw_semaphore *sem)
{
 do { __might_sleep("include/linux/rwsem.h", 66); do { } while (0); } while (0);
 ;
 __down_write(sem);
 ;
}




static inline __attribute__((always_inline)) int down_write_trylock(struct rw_semaphore *sem)
{
 int ret;
 ;
 ret = __down_write_trylock(sem);
 ;
 return ret;
}




static inline __attribute__((always_inline)) void up_read(struct rw_semaphore *sem)
{
 ;
 __up_read(sem);
 ;
}




static inline __attribute__((always_inline)) void up_write(struct rw_semaphore *sem)
{
 ;
 __up_write(sem);
 ;
}




static inline __attribute__((always_inline)) void downgrade_write(struct rw_semaphore *sem)
{
 ;
 __downgrade_write(sem);
 ;
}
# 43 "include/asm/semaphore.h" 2

struct semaphore {
 atomic_t count;
 int sleepers;
 wait_queue_head_t wait;
};
# 67 "include/asm/semaphore.h"
static inline __attribute__((always_inline)) void sema_init (struct semaphore *sem, int val)
{






 (((&sem->count)->counter) = (val));
 sem->sleepers = 0;
 init_waitqueue_head(&sem->wait);
}

static inline __attribute__((always_inline)) void init_MUTEX (struct semaphore *sem)
{
 sema_init(sem, 1);
}

static inline __attribute__((always_inline)) void init_MUTEX_LOCKED (struct semaphore *sem)
{
 sema_init(sem, 0);
}

__attribute__((regparm(3))) void __down_failed(void );
__attribute__((regparm(3))) int __down_failed_interruptible(void );
__attribute__((regparm(3))) int __down_failed_trylock(void );
__attribute__((regparm(3))) void __up_wakeup(void );






static inline __attribute__((always_inline)) void down(struct semaphore * sem)
{
 do { __might_sleep("include/asm/semaphore.h", 102); do { } while (0); } while (0);
 __asm__ __volatile__(
  "# atomic down operation\n\t"
  "lock ; " "decl %0\n\t"
  "js 2f\n"
  "1:\n"
  ".subsection 1\n\t" "" ".ifndef " ".text.lock." "tcp_ipv6" "\n\t" ".text.lock." "tcp_ipv6" ":\n\t" ".endif\n"
  "2:\tlea %0,%%eax\n\t"
  "call __down_failed\n\t"
  "jmp 1b\n"
  ".previous\n\t"
  :"=m" (sem->count)
  :
  :"memory","ax");
}





static inline __attribute__((always_inline)) int down_interruptible(struct semaphore * sem)
{
 int result;

 do { __might_sleep("include/asm/semaphore.h", 126); do { } while (0); } while (0);
 __asm__ __volatile__(
  "# atomic interruptible down operation\n\t"
  "lock ; " "decl %1\n\t"
  "js 2f\n\t"
  "xorl %0,%0\n"
  "1:\n"
  ".subsection 1\n\t" "" ".ifndef " ".text.lock." "tcp_ipv6" "\n\t" ".text.lock." "tcp_ipv6" ":\n\t" ".endif\n"
  "2:\tlea %1,%%eax\n\t"
  "call __down_failed_interruptible\n\t"
  "jmp 1b\n"
  ".previous\n\t"
  :"=a" (result), "=m" (sem->count)
  :
  :"memory");
 return result;
}





static inline __attribute__((always_inline)) int down_trylock(struct semaphore * sem)
{
 int result;

 __asm__ __volatile__(
  "# atomic interruptible down operation\n\t"
  "lock ; " "decl %1\n\t"
  "js 2f\n\t"
  "xorl %0,%0\n"
  "1:\n"
  ".subsection 1\n\t" "" ".ifndef " ".text.lock." "tcp_ipv6" "\n\t" ".text.lock." "tcp_ipv6" ":\n\t" ".endif\n"
  "2:\tlea %1,%%eax\n\t"
  "call __down_failed_trylock\n\t"
  "jmp 1b\n"
  ".previous\n\t"
  :"=a" (result), "=m" (sem->count)
  :
  :"memory");
 return result;
}







static inline __attribute__((always_inline)) void up(struct semaphore * sem)
{
 __asm__ __volatile__(
  "# atomic up operation\n\t"
  "lock ; " "incl %0\n\t"
  "jle 2f\n"
  "1:\n"
  ".subsection 1\n\t" "" ".ifndef " ".text.lock." "tcp_ipv6" "\n\t" ".text.lock." "tcp_ipv6" ":\n\t" ".endif\n"
  "2:\tlea %0,%%eax\n\t"
  "call __up_wakeup\n\t"
  "jmp 1b\n"
  ".previous\n\t"
  ".subsection 0\n"
  :"=m" (sem->count)
  :
  :"memory","ax");
}
# 21 "include/linux/sched.h" 2

# 1 "include/asm/ptrace.h" 1
# 26 "include/asm/ptrace.h"
struct pt_regs {
 long ebx;
 long ecx;
 long edx;
 long esi;
 long edi;
 long ebp;
 long eax;
 int xds;
 int xes;
 long orig_eax;
 long eip;
 int xcs;
 long eflags;
 long esp;
 int xss;
};
# 61 "include/asm/ptrace.h"
struct task_struct;
extern void send_sigtrap(struct task_struct *tsk, struct pt_regs *regs, int error_code);

static inline __attribute__((always_inline)) int user_mode(struct pt_regs *regs)
{
 return (regs->xcs & 3) != 0;
}
static inline __attribute__((always_inline)) int user_mode_vm(struct pt_regs *regs)
{
 return ((regs->xcs & 3) | (regs->eflags & 0x00020000)) != 0;
}


extern unsigned long profile_pc(struct pt_regs *regs);
# 23 "include/linux/sched.h" 2
# 1 "include/asm/mmu.h" 1
# 11 "include/asm/mmu.h"
typedef struct {
 int size;
 struct semaphore sem;
 void *ldt;
} mm_context_t;
# 24 "include/linux/sched.h" 2
# 1 "include/asm/cputime.h" 1



# 1 "include/asm-generic/cputime.h" 1






typedef unsigned long cputime_t;
# 23 "include/asm-generic/cputime.h"
typedef u64 cputime64_t;
# 5 "include/asm/cputime.h" 2
# 25 "include/linux/sched.h" 2

# 1 "include/linux/smp.h" 1
# 11 "include/linux/smp.h"
extern void cpu_idle(void);







# 1 "include/asm/smp.h" 1
# 16 "include/asm/smp.h"
# 1 "include/asm/fixmap.h" 1
# 27 "include/asm/fixmap.h"
# 1 "include/asm/acpi.h" 1
# 31 "include/asm/acpi.h"
# 1 "include/acpi/pdc_intel.h" 1
# 32 "include/asm/acpi.h" 2
# 60 "include/asm/acpi.h"
static inline __attribute__((always_inline)) int
__acpi_acquire_global_lock (unsigned int *lock)
{
 unsigned int old, new, val;
 do {
  old = *lock;
  new = (((old & ~0x3) + 2) + ((old >> 1) & 0x1));
  val = ((__typeof__(*(lock)))__cmpxchg((lock),(unsigned long)(old), (unsigned long)(new),sizeof(*(lock))));
 } while (__builtin_expect(!!(val != old), 0));
 return (new < 3) ? -1 : 0;
}

static inline __attribute__((always_inline)) int
__acpi_release_global_lock (unsigned int *lock)
{
 unsigned int old, new, val;
 do {
  old = *lock;
  new = old & ~0x3;
  val = ((__typeof__(*(lock)))__cmpxchg((lock),(unsigned long)(old), (unsigned long)(new),sizeof(*(lock))));
 } while (__builtin_expect(!!(val != old), 0));
 return old & 0x1;
}
# 107 "include/asm/acpi.h"
extern int acpi_lapic;
extern int acpi_ioapic;
extern int acpi_noirq;
extern int acpi_strict;
extern int acpi_disabled;
extern int acpi_ht;
extern int acpi_pci_disabled;
static inline __attribute__((always_inline)) void disable_acpi(void)
{
 acpi_disabled = 1;
 acpi_ht = 0;
 acpi_pci_disabled = 1;
 acpi_noirq = 1;
}




extern int acpi_gsi_to_irq(u32 gsi, unsigned int *irq);


extern int skip_ioapic_setup;
extern int acpi_skip_timer_override;

extern void check_acpi_pci(void);

static inline __attribute__((always_inline)) void disable_ioapic_setup(void)
{
 skip_ioapic_setup = 1;
}

static inline __attribute__((always_inline)) int ioapic_setup_disabled(void)
{
 return skip_ioapic_setup;
}
# 156 "include/asm/acpi.h"
static inline __attribute__((always_inline)) void acpi_noirq_set(void) { acpi_noirq = 1; }
static inline __attribute__((always_inline)) void acpi_disable_pci(void)
{
 acpi_pci_disabled = 1;
 acpi_noirq_set();
}
extern int acpi_irq_balance_set(char *str);
# 172 "include/asm/acpi.h"
extern int acpi_save_state_mem(void);
extern void acpi_restore_state_mem(void);

extern unsigned long acpi_wakeup_address;


extern void acpi_reserve_bootmem(void);



extern u8 x86_acpiid_to_apicid[];
# 28 "include/asm/fixmap.h" 2
# 1 "include/asm/apicdef.h" 1
# 124 "include/asm/apicdef.h"
struct local_apic {

        struct { unsigned int __reserved[4]; } __reserved_01;

        struct { unsigned int __reserved[4]; } __reserved_02;

        struct {
  unsigned int __reserved_1 : 24,
   phys_apic_id : 4,
   __reserved_2 : 4;
  unsigned int __reserved[3];
 } id;

        const
 struct {
  unsigned int version : 8,
   __reserved_1 : 8,
   max_lvt : 8,
   __reserved_2 : 8;
  unsigned int __reserved[3];
 } version;

        struct { unsigned int __reserved[4]; } __reserved_03;

        struct { unsigned int __reserved[4]; } __reserved_04;

        struct { unsigned int __reserved[4]; } __reserved_05;

        struct { unsigned int __reserved[4]; } __reserved_06;

        struct {
  unsigned int priority : 8,
   __reserved_1 : 24;
  unsigned int __reserved_2[3];
 } tpr;

        const
 struct {
  unsigned int priority : 8,
   __reserved_1 : 24;
  unsigned int __reserved_2[3];
 } apr;

        const
 struct {
  unsigned int priority : 8,
   __reserved_1 : 24;
  unsigned int __reserved_2[3];
 } ppr;

        struct {
  unsigned int eoi;
  unsigned int __reserved[3];
 } eoi;

        struct { unsigned int __reserved[4]; } __reserved_07;

        struct {
  unsigned int __reserved_1 : 24,
   logical_dest : 8;
  unsigned int __reserved_2[3];
 } ldr;

        struct {
  unsigned int __reserved_1 : 28,
   model : 4;
  unsigned int __reserved_2[3];
 } dfr;

        struct {
  unsigned int spurious_vector : 8,
   apic_enabled : 1,
   focus_cpu : 1,
   __reserved_2 : 22;
  unsigned int __reserved_3[3];
 } svr;

        struct {
         unsigned int bitfield;
  unsigned int __reserved[3];
 } isr [8];

        struct {
         unsigned int bitfield;
  unsigned int __reserved[3];
 } tmr [8];

        struct {
         unsigned int bitfield;
  unsigned int __reserved[3];
 } irr [8];

        union {
  struct {
   unsigned int send_cs_error : 1,
    receive_cs_error : 1,
    send_accept_error : 1,
    receive_accept_error : 1,
    __reserved_1 : 1,
    send_illegal_vector : 1,
    receive_illegal_vector : 1,
    illegal_register_address : 1,
    __reserved_2 : 24;
   unsigned int __reserved_3[3];
  } error_bits;
  struct {
   unsigned int errors;
   unsigned int __reserved_3[3];
  } all_errors;
 } esr;

        struct { unsigned int __reserved[4]; } __reserved_08;

        struct { unsigned int __reserved[4]; } __reserved_09;

        struct { unsigned int __reserved[4]; } __reserved_10;

        struct { unsigned int __reserved[4]; } __reserved_11;

        struct { unsigned int __reserved[4]; } __reserved_12;

        struct { unsigned int __reserved[4]; } __reserved_13;

        struct { unsigned int __reserved[4]; } __reserved_14;

        struct {
  unsigned int vector : 8,
   delivery_mode : 3,
   destination_mode : 1,
   delivery_status : 1,
   __reserved_1 : 1,
   level : 1,
   trigger : 1,
   __reserved_2 : 2,
   shorthand : 2,
   __reserved_3 : 12;
  unsigned int __reserved_4[3];
 } icr1;

        struct {
  union {
   unsigned int __reserved_1 : 24,
    phys_dest : 4,
    __reserved_2 : 4;
   unsigned int __reserved_3 : 24,
    logical_dest : 8;
  } dest;
  unsigned int __reserved_4[3];
 } icr2;

        struct {
  unsigned int vector : 8,
   __reserved_1 : 4,
   delivery_status : 1,
   __reserved_2 : 3,
   mask : 1,
   timer_mode : 1,
   __reserved_3 : 14;
  unsigned int __reserved_4[3];
 } lvt_timer;

        struct {
  unsigned int vector : 8,
   delivery_mode : 3,
   __reserved_1 : 1,
   delivery_status : 1,
   __reserved_2 : 3,
   mask : 1,
   __reserved_3 : 15;
  unsigned int __reserved_4[3];
 } lvt_thermal;

        struct {
  unsigned int vector : 8,
   delivery_mode : 3,
   __reserved_1 : 1,
   delivery_status : 1,
   __reserved_2 : 3,
   mask : 1,
   __reserved_3 : 15;
  unsigned int __reserved_4[3];
 } lvt_pc;

        struct {
  unsigned int vector : 8,
   delivery_mode : 3,
   __reserved_1 : 1,
   delivery_status : 1,
   polarity : 1,
   remote_irr : 1,
   trigger : 1,
   mask : 1,
   __reserved_2 : 15;
  unsigned int __reserved_3[3];
 } lvt_lint0;

        struct {
  unsigned int vector : 8,
   delivery_mode : 3,
   __reserved_1 : 1,
   delivery_status : 1,
   polarity : 1,
   remote_irr : 1,
   trigger : 1,
   mask : 1,
   __reserved_2 : 15;
  unsigned int __reserved_3[3];
 } lvt_lint1;

        struct {
  unsigned int vector : 8,
   __reserved_1 : 4,
   delivery_status : 1,
   __reserved_2 : 3,
   mask : 1,
   __reserved_3 : 15;
  unsigned int __reserved_4[3];
 } lvt_error;

        struct {
  unsigned int initial_count;
  unsigned int __reserved_2[3];
 } timer_icr;

        const
 struct {
  unsigned int curr_count;
  unsigned int __reserved_2[3];
 } timer_ccr;

        struct { unsigned int __reserved[4]; } __reserved_16;

        struct { unsigned int __reserved[4]; } __reserved_17;

        struct { unsigned int __reserved[4]; } __reserved_18;

        struct { unsigned int __reserved[4]; } __reserved_19;

        struct {
  unsigned int divisor : 4,
   __reserved_1 : 28;
  unsigned int __reserved_2[3];
 } timer_dcr;

        struct { unsigned int __reserved[4]; } __reserved_20;

} __attribute__ ((packed));
# 29 "include/asm/fixmap.h" 2
# 53 "include/asm/fixmap.h"
enum fixed_addresses {
 FIX_HOLE,
 FIX_VSYSCALL,

 FIX_APIC_BASE,


 FIX_IO_APIC_BASE_0,
 FIX_IO_APIC_BASE_END = FIX_IO_APIC_BASE_0 + 64 -1,
# 80 "include/asm/fixmap.h"
 FIX_ACPI_BEGIN,
 FIX_ACPI_END = FIX_ACPI_BEGIN + 4 - 1,


 FIX_PCIE_MCFG,

 __end_of_permanent_fixed_addresses,


 FIX_BTMAP_END = __end_of_permanent_fixed_addresses,
 FIX_BTMAP_BEGIN = FIX_BTMAP_END + 16 - 1,
 FIX_WP_TEST,
 __end_of_fixed_addresses
};

extern void __set_fixmap (enum fixed_addresses idx,
     unsigned long phys, pgprot_t flags);
# 127 "include/asm/fixmap.h"
extern void __this_fixmap_does_not_exist(void);






static inline __attribute__((always_inline)) unsigned long fix_to_virt(const unsigned int idx)
{
# 145 "include/asm/fixmap.h"
 if (idx >= __end_of_fixed_addresses)
  __this_fixmap_does_not_exist();

        return (((unsigned long)0xfffff000) - ((idx) << 12));
}

static inline __attribute__((always_inline)) unsigned long virt_to_fix(const unsigned long vaddr)
{
 do { if (__builtin_expect(!!((vaddr >= ((unsigned long)0xfffff000) || vaddr < (((unsigned long)0xfffff000) - (__end_of_permanent_fixed_addresses << 12)))!=0), 0)) __BUG(); } while(0);
 return ((((unsigned long)0xfffff000) - ((vaddr)&(~((1UL << 12)-1)))) >> 12);
}
# 17 "include/asm/smp.h" 2

# 1 "include/asm/mpspec.h" 1




# 1 "include/asm/mpspec_def.h" 1
# 19 "include/asm/mpspec_def.h"
struct intel_mp_floating
{
 char mpf_signature[4];
 unsigned long mpf_physptr;
 unsigned char mpf_length;
 unsigned char mpf_specification;
 unsigned char mpf_checksum;
 unsigned char mpf_feature1;
 unsigned char mpf_feature2;
 unsigned char mpf_feature3;
 unsigned char mpf_feature4;
 unsigned char mpf_feature5;
};

struct mp_config_table
{
 char mpc_signature[4];

 unsigned short mpc_length;
 char mpc_spec;
 char mpc_checksum;
 char mpc_oem[8];
 char mpc_productid[12];
 unsigned long mpc_oemptr;
 unsigned short mpc_oemsize;
 unsigned short mpc_oemcount;
 unsigned long mpc_lapic;
 unsigned long reserved;
};
# 58 "include/asm/mpspec_def.h"
struct mpc_config_processor
{
 unsigned char mpc_type;
 unsigned char mpc_apicid;
 unsigned char mpc_apicver;
 unsigned char mpc_cpuflag;


 unsigned long mpc_cpufeature;



 unsigned long mpc_featureflag;
 unsigned long mpc_reserved[2];
};

struct mpc_config_bus
{
 unsigned char mpc_type;
 unsigned char mpc_busid;
 unsigned char mpc_bustype[6] __attribute((packed));
};
# 102 "include/asm/mpspec_def.h"
struct mpc_config_ioapic
{
 unsigned char mpc_type;
 unsigned char mpc_apicid;
 unsigned char mpc_apicver;
 unsigned char mpc_flags;

 unsigned long mpc_apicaddr;
};

struct mpc_config_intsrc
{
 unsigned char mpc_type;
 unsigned char mpc_irqtype;
 unsigned short mpc_irqflag;
 unsigned char mpc_srcbus;
 unsigned char mpc_srcbusirq;
 unsigned char mpc_dstapic;
 unsigned char mpc_dstirq;
};

enum mp_irq_source_types {
 mp_INT = 0,
 mp_NMI = 1,
 mp_SMI = 2,
 mp_ExtINT = 3
};






struct mpc_config_lintsrc
{
 unsigned char mpc_type;
 unsigned char mpc_irqtype;
 unsigned short mpc_irqflag;
 unsigned char mpc_srcbusid;
 unsigned char mpc_srcbusirq;
 unsigned char mpc_destapic;

 unsigned char mpc_destapiclint;
};

struct mp_config_oemtable
{
 char oem_signature[4];

 unsigned short oem_length;
 char oem_rev;
 char oem_checksum;
 char mpc_oem[8];
};

struct mpc_config_translation
{
        unsigned char mpc_type;
        unsigned char trans_len;
        unsigned char trans_type;
        unsigned char trans_quad;
        unsigned char trans_global;
        unsigned char trans_local;
        unsigned short trans_reserved;
};
# 180 "include/asm/mpspec_def.h"
enum mp_bustype {
 MP_BUS_ISA = 1,
 MP_BUS_EISA,
 MP_BUS_PCI,
 MP_BUS_MCA,
 MP_BUS_NEC98
};
# 6 "include/asm/mpspec.h" 2
# 1 "include/asm-i386/mach-default/mach_mpspec.h" 1
# 7 "include/asm/mpspec.h" 2

extern int mp_bus_id_to_type [32];
extern int mp_bus_id_to_node [32];
extern int mp_bus_id_to_local [32];
extern int quad_local_to_mp_bus_id [8/4][4];
extern int mp_bus_id_to_pci_bus [32];

extern unsigned int boot_cpu_physical_apicid;
extern int smp_found_config;
extern void find_smp_config (void);
extern void get_smp_config (void);
extern int nr_ioapics;
extern int apic_version [256];
extern int mp_bus_id_to_type [32];
extern int mp_irq_entries;
extern struct mpc_config_intsrc mp_irqs [256];
extern int mpc_default_type;
extern int mp_bus_id_to_pci_bus [32];
extern unsigned long mp_lapic_addr;
extern int pic_mode;
extern int using_apic_timer;


extern void mp_register_lapic (u8 id, u8 enabled);
extern void mp_register_lapic_address (u64 address);
extern void mp_register_ioapic (u8 id, u32 address, u32 gsi_base);
extern void mp_override_legacy_irq (u8 bus_irq, u8 polarity, u8 trigger, u32 gsi);
extern void mp_config_acpi_legacy_irqs (void);
extern int mp_register_gsi (u32 gsi, int edge_level, int active_high_low);




struct physid_mask
{
 unsigned long mask[(((256)+32 -1)/32)];
};

typedef struct physid_mask physid_mask_t;
# 80 "include/asm/mpspec.h"
extern physid_mask_t phys_cpu_present_map;
# 19 "include/asm/smp.h" 2

# 1 "include/asm/io_apic.h" 1
# 17 "include/asm/io_apic.h"
static inline __attribute__((always_inline)) int use_pci_vector(void) {return 1;}
static inline __attribute__((always_inline)) void disable_edge_ioapic_vector(unsigned int vector) { }
static inline __attribute__((always_inline)) void mask_and_ack_level_ioapic_vector(unsigned int vector) { }
static inline __attribute__((always_inline)) void end_edge_ioapic_vector (unsigned int vector) { }
# 63 "include/asm/io_apic.h"
union IO_APIC_reg_00 {
 u32 raw;
 struct {
  u32 __reserved_2 : 14,
   LTS : 1,
   delivery_type : 1,
   __reserved_1 : 8,
   ID : 8;
 } __attribute__ ((packed)) bits;
};

union IO_APIC_reg_01 {
 u32 raw;
 struct {
  u32 version : 8,
   __reserved_2 : 7,
   PRQ : 1,
   entries : 8,
   __reserved_1 : 8;
 } __attribute__ ((packed)) bits;
};

union IO_APIC_reg_02 {
 u32 raw;
 struct {
  u32 __reserved_2 : 24,
   arbitration : 4,
   __reserved_1 : 4;
 } __attribute__ ((packed)) bits;
};

union IO_APIC_reg_03 {
 u32 raw;
 struct {
  u32 boot_DT : 1,
   __reserved_1 : 31;
 } __attribute__ ((packed)) bits;
};




extern int nr_ioapics;
extern int nr_ioapic_registers[64];

enum ioapic_irq_destination_types {
 dest_Fixed = 0,
 dest_LowestPrio = 1,
 dest_SMI = 2,
 dest__reserved_1 = 3,
 dest_NMI = 4,
 dest_INIT = 5,
 dest__reserved_2 = 6,
 dest_ExtINT = 7
};

struct IO_APIC_route_entry {
 __u32 vector : 8,
  delivery_mode : 3,



  dest_mode : 1,
  delivery_status : 1,
  polarity : 1,
  irr : 1,
  trigger : 1,
  mask : 1,
  __reserved_2 : 15;

 union { struct { __u32
     __reserved_1 : 24,
     physical_dest : 4,
     __reserved_2 : 4;
   } physical;

   struct { __u32
     __reserved_1 : 24,
     logical_dest : 8;
   } logical;
 } dest;

} __attribute__ ((packed));






extern struct mpc_config_ioapic mp_ioapics[64];


extern int mp_irq_entries;


extern struct mpc_config_intsrc mp_irqs[256];


extern int mpc_default_type;

static inline __attribute__((always_inline)) unsigned int io_apic_read(unsigned int apic, unsigned int reg)
{
 *((volatile int *)((((unsigned long)0xfffff000) - ((FIX_IO_APIC_BASE_0 + apic) << 12)) + (mp_ioapics[apic].mpc_apicaddr & ~(~((1UL << 12)-1))))) = reg;
 return *(((volatile int *)((((unsigned long)0xfffff000) - ((FIX_IO_APIC_BASE_0 + apic) << 12)) + (mp_ioapics[apic].mpc_apicaddr & ~(~((1UL << 12)-1)))))+4);
}

static inline __attribute__((always_inline)) void io_apic_write(unsigned int apic, unsigned int reg, unsigned int value)
{
 *((volatile int *)((((unsigned long)0xfffff000) - ((FIX_IO_APIC_BASE_0 + apic) << 12)) + (mp_ioapics[apic].mpc_apicaddr & ~(~((1UL << 12)-1))))) = reg;
 *(((volatile int *)((((unsigned long)0xfffff000) - ((FIX_IO_APIC_BASE_0 + apic) << 12)) + (mp_ioapics[apic].mpc_apicaddr & ~(~((1UL << 12)-1)))))+4) = value;
}







extern int sis_apic_bug;
static inline __attribute__((always_inline)) void io_apic_modify(unsigned int apic, unsigned int reg, unsigned int value)
{
 if (sis_apic_bug)
  *((volatile int *)((((unsigned long)0xfffff000) - ((FIX_IO_APIC_BASE_0 + apic) << 12)) + (mp_ioapics[apic].mpc_apicaddr & ~(~((1UL << 12)-1))))) = reg;
 *(((volatile int *)((((unsigned long)0xfffff000) - ((FIX_IO_APIC_BASE_0 + apic) << 12)) + (mp_ioapics[apic].mpc_apicaddr & ~(~((1UL << 12)-1)))))+4) = value;
}


extern int skip_ioapic_setup;
# 199 "include/asm/io_apic.h"
extern int io_apic_get_unique_id (int ioapic, int apic_id);
extern int io_apic_get_version (int ioapic);
extern int io_apic_get_redir_entries (int ioapic);
extern int io_apic_set_pci_routing (int ioapic, int pin, int irq, int edge_level, int active_high_low);


extern int (*ioapic_renumber_irq)(int ioapic, int irq);





extern int assign_irq_vector(int irq);
# 21 "include/asm/smp.h" 2

# 1 "include/asm/apic.h" 1




# 1 "include/linux/pm.h" 1
# 35 "include/linux/pm.h"
typedef int pm_request_t;
# 44 "include/linux/pm.h"
typedef int pm_dev_t;
# 57 "include/linux/pm.h"
enum
{
 PM_SYS_UNKNOWN = 0x00000000,
 PM_SYS_KBC = 0x41d00303,
 PM_SYS_COM = 0x41d00500,
 PM_SYS_IRDA = 0x41d00510,
 PM_SYS_FDC = 0x41d00700,
 PM_SYS_VGA = 0x41d00900,
 PM_SYS_PCMCIA = 0x41d00e00,
};
# 76 "include/linux/pm.h"
struct pm_dev;

typedef int (*pm_callback)(struct pm_dev *dev, pm_request_t rqst, void *data);




struct pm_dev
{
 pm_dev_t type;
 unsigned long id;
 pm_callback callback;
 void *data;

 unsigned long flags;
 unsigned long state;
 unsigned long prev_state;

 struct list_head entry;
};



extern int pm_active;






struct pm_dev __attribute__((deprecated)) *
pm_register(pm_dev_t type, unsigned long id, pm_callback callback);




void __attribute__((deprecated)) pm_unregister(struct pm_dev *dev);




void __attribute__((deprecated)) pm_unregister_all(pm_callback callback);




int __attribute__((deprecated)) pm_send_all(pm_request_t rqst, void *data);
# 152 "include/linux/pm.h"
extern void (*pm_idle)(void);
extern void (*pm_power_off)(void);

typedef int suspend_state_t;







typedef int suspend_disk_method_t;







struct pm_ops {
 suspend_disk_method_t pm_disk_mode;
 int (*prepare)(suspend_state_t state);
 int (*enter)(suspend_state_t state);
 int (*finish)(suspend_state_t state);
};

extern void pm_set_ops(struct pm_ops *);
extern struct pm_ops *pm_ops;
extern int pm_suspend(suspend_state_t state);






struct device;

typedef u32 pm_message_t;
# 214 "include/linux/pm.h"
struct dev_pm_info {
 pm_message_t power_state;

 pm_message_t prev_state;
 void * saved_state;
 atomic_t pm_users;
 struct device * pm_parent;
 struct list_head entry;

};

extern void device_pm_set_parent(struct device * dev, struct device * parent);

extern int device_power_down(pm_message_t state);
extern void device_power_up(void);
extern void device_resume(void);


extern int device_suspend(pm_message_t state);
# 6 "include/asm/apic.h" 2
# 20 "include/asm/apic.h"
extern int enable_local_apic;
extern int apic_verbosity;

static inline __attribute__((always_inline)) void lapic_disable(void)
{
 enable_local_apic = -1;
 clear_bit((0*32+ 9), boot_cpu_data.x86_capability);
}

static inline __attribute__((always_inline)) void lapic_enable(void)
{
 enable_local_apic = 1;
}
# 52 "include/asm/apic.h"
static __inline __attribute__((always_inline)) void apic_write(unsigned long reg, unsigned long v)
{
 *((volatile unsigned long *)((fix_to_virt(FIX_APIC_BASE))+reg)) = v;
}

static __inline __attribute__((always_inline)) void apic_write_atomic(unsigned long reg, unsigned long v)
{
 ((__typeof__(*((volatile unsigned long *)((fix_to_virt(FIX_APIC_BASE))+reg))))__xchg((unsigned long)(v),((volatile unsigned long *)((fix_to_virt(FIX_APIC_BASE))+reg)),sizeof(*((volatile unsigned long *)((fix_to_virt(FIX_APIC_BASE))+reg)))));
}

static __inline __attribute__((always_inline)) unsigned long apic_read(unsigned long reg)
{
 return *((volatile unsigned long *)((fix_to_virt(FIX_APIC_BASE))+reg));
}

static __inline__ __attribute__((always_inline)) void apic_wait_icr_idle(void)
{
 while ( apic_read( 0x300 ) & 0x01000 )
  rep_nop();
}

int get_physical_broadcast(void);
# 85 "include/asm/apic.h"
static inline __attribute__((always_inline)) void ack_APIC_irq(void)
{
# 95 "include/asm/apic.h"
 apic_write((0xB0),(0));
}

extern void (*wait_timer_tick)(void);

extern int get_maxlvt(void);
extern void clear_local_APIC(void);
extern void connect_bsp_APIC (void);
extern void disconnect_bsp_APIC (int virt_wire_setup);
extern void disable_local_APIC (void);
extern void lapic_shutdown (void);
extern int verify_local_APIC (void);
extern void cache_APIC_registers (void);
extern void sync_Arb_IDs (void);
extern void init_bsp_APIC (void);
extern void setup_local_APIC (void);
extern void init_apic_mappings (void);
extern void smp_local_timer_interrupt (struct pt_regs * regs);
extern void setup_boot_APIC_clock (void);
extern void setup_secondary_APIC_clock (void);
extern void setup_apic_nmi_watchdog (void);
extern int reserve_lapic_nmi(void);
extern void release_lapic_nmi(void);
extern void disable_timer_nmi_watchdog(void);
extern void enable_timer_nmi_watchdog(void);
extern void nmi_watchdog_tick (struct pt_regs * regs);
extern int APIC_init_uniprocessor (void);
extern void disable_APIC_timer(void);
extern void enable_APIC_timer(void);

extern void enable_NMI_through_LVT0 (void * dummy);

extern unsigned int nmi_watchdog;
# 23 "include/asm/smp.h" 2
# 34 "include/asm/smp.h"
extern void smp_alloc_memory(void);
extern int pic_mode;
extern int smp_num_siblings;
extern cpumask_t cpu_sibling_map[];
extern cpumask_t cpu_core_map[];

extern void (*mtrr_hook) (void);
extern void zap_low_mappings (void);
extern void lock_ipi_call_lock(void);
extern void unlock_ipi_call_lock(void);


extern u8 x86_cpu_to_apicid[];


extern void cpu_exit_clear(void);
extern void cpu_uninit(void);
# 60 "include/asm/smp.h"
extern cpumask_t cpu_callout_map;
extern cpumask_t cpu_callin_map;



static inline __attribute__((always_inline)) int num_booting_cpus(void)
{
 return __cpus_weight(&(cpu_callout_map), 8);
}






# 1 "include/asm-i386/mach-default/mach_apicdef.h" 1





static inline __attribute__((always_inline)) unsigned get_apic_id(unsigned long x)
{
 return (((x)>>24)&0xF);
}
# 76 "include/asm/smp.h" 2
static inline __attribute__((always_inline)) int hard_smp_processor_id(void)
{

 return get_apic_id(*(unsigned long *)((fix_to_virt(FIX_APIC_BASE))+0x20));
}


static __inline __attribute__((always_inline)) int logical_smp_processor_id(void)
{

 return (((*(unsigned long *)((fix_to_virt(FIX_APIC_BASE))+0xD0))>>24)&0xFF);
}



extern int __cpu_disable(void);
extern void __cpu_die(unsigned int cpu);
# 20 "include/linux/smp.h" 2
# 30 "include/linux/smp.h"
extern void smp_send_stop(void);




extern void smp_send_reschedule(int cpu);





extern void smp_prepare_cpus(unsigned int max_cpus);




extern int __cpu_up(unsigned int cpunum);




extern void smp_cpus_done(unsigned int max_cpus);




extern int smp_call_function (void (*func) (void *info), void *info,
         int retry, int wait);




static inline __attribute__((always_inline)) int on_each_cpu(void (*func) (void *info), void *info,
         int retry, int wait)
{
 int ret = 0;

 do { } while (0);
 ret = smp_call_function(func, info, retry, wait);
 func(info);
 do { } while (0);
 return ret;
}
# 88 "include/linux/smp.h"
void smp_prepare_boot_cpu(void);
# 27 "include/linux/sched.h" 2
# 1 "include/linux/sem.h" 1



# 1 "include/linux/ipc.h" 1
# 9 "include/linux/ipc.h"
struct ipc_perm
{
 __kernel_key_t key;
 __kernel_uid_t uid;
 __kernel_gid_t gid;
 __kernel_uid_t cuid;
 __kernel_gid_t cgid;
 __kernel_mode_t mode;
 unsigned short seq;
};


# 1 "include/asm/ipcbuf.h" 1
# 14 "include/asm/ipcbuf.h"
struct ipc64_perm
{
 __kernel_key_t key;
 __kernel_uid32_t uid;
 __kernel_gid32_t gid;
 __kernel_uid32_t cuid;
 __kernel_gid32_t cgid;
 __kernel_mode_t mode;
 unsigned short __pad1;
 unsigned short seq;
 unsigned short __pad2;
 unsigned long __unused1;
 unsigned long __unused2;
};
# 22 "include/linux/ipc.h" 2
# 57 "include/linux/ipc.h"
struct kern_ipc_perm
{
 spinlock_t lock;
 int deleted;
 key_t key;
 uid_t uid;
 gid_t gid;
 uid_t cuid;
 gid_t cgid;
 mode_t mode;
 unsigned long seq;
 void *security;
};
# 5 "include/linux/sem.h" 2
# 24 "include/linux/sem.h"
struct semid_ds {
 struct ipc_perm sem_perm;
 __kernel_time_t sem_otime;
 __kernel_time_t sem_ctime;
 struct sem *sem_base;
 struct sem_queue *sem_pending;
 struct sem_queue **sem_pending_last;
 struct sem_undo *undo;
 unsigned short sem_nsems;
};


# 1 "include/asm/sembuf.h" 1
# 14 "include/asm/sembuf.h"
struct semid64_ds {
 struct ipc64_perm sem_perm;
 __kernel_time_t sem_otime;
 unsigned long __unused1;
 __kernel_time_t sem_ctime;
 unsigned long __unused2;
 unsigned long sem_nsems;
 unsigned long __unused3;
 unsigned long __unused4;
};
# 37 "include/linux/sem.h" 2


struct sembuf {
 unsigned short sem_num;
 short sem_op;
 short sem_flg;
};


union semun {
 int val;
 struct semid_ds *buf;
 unsigned short *array;
 struct seminfo *__buf;
 void *__pad;
};

struct seminfo {
 int semmap;
 int semmni;
 int semmns;
 int semmnu;
 int semmsl;
 int semopm;
 int semume;
 int semusz;
 int semvmx;
 int semaem;
};
# 83 "include/linux/sem.h"
struct sem {
 int semval;
 int sempid;
};


struct sem_array {
 struct kern_ipc_perm sem_perm;
 time_t sem_otime;
 time_t sem_ctime;
 struct sem *sem_base;
 struct sem_queue *sem_pending;
 struct sem_queue **sem_pending_last;
 struct sem_undo *undo;
 unsigned long sem_nsems;
};


struct sem_queue {
 struct sem_queue * next;
 struct sem_queue ** prev;
 struct task_struct* sleeper;
 struct sem_undo * undo;
 int pid;
 int status;
 struct sem_array * sma;
 int id;
 struct sembuf * sops;
 int nsops;
 int alter;
};




struct sem_undo {
 struct sem_undo * proc_next;
 struct sem_undo * id_next;
 int semid;
 short * semadj;
};




struct sem_undo_list {
 atomic_t refcnt;
 spinlock_t lock;
 struct sem_undo *proc_list;
};

struct sysv_sem {
 struct sem_undo_list *undo_list;
};



extern int copy_semundo(unsigned long clone_flags, struct task_struct *tsk);
extern void exit_sem(struct task_struct *tsk);
# 28 "include/linux/sched.h" 2
# 1 "include/linux/signal.h" 1





# 1 "include/asm/signal.h" 1
# 10 "include/asm/signal.h"
struct siginfo;
# 20 "include/asm/signal.h"
typedef unsigned long old_sigset_t;

typedef struct {
 unsigned long sig[(64 / 32)];
} sigset_t;
# 113 "include/asm/signal.h"
# 1 "include/asm-generic/signal.h" 1
# 12 "include/asm-generic/signal.h"
typedef void __signalfn_t(int);
typedef __signalfn_t *__sighandler_t;

typedef void __restorefn_t(void);
typedef __restorefn_t *__sigrestore_t;
# 114 "include/asm/signal.h" 2


struct old_sigaction {
 __sighandler_t sa_handler;
 old_sigset_t sa_mask;
 unsigned long sa_flags;
 __sigrestore_t sa_restorer;
};

struct sigaction {
 __sighandler_t sa_handler;
 unsigned long sa_flags;
 __sigrestore_t sa_restorer;
 sigset_t sa_mask;
};

struct k_sigaction {
 struct sigaction sa;
};
# 151 "include/asm/signal.h"
typedef struct sigaltstack {
 void *ss_sp;
 int ss_flags;
 size_t ss_size;
} stack_t;






static __inline__ __attribute__((always_inline)) void sigaddset(sigset_t *set, int _sig)
{
 __asm__("btsl %1,%0" : "=m"(*set) : "Ir"(_sig - 1) : "cc");
}

static __inline__ __attribute__((always_inline)) void sigdelset(sigset_t *set, int _sig)
{
 __asm__("btrl %1,%0" : "=m"(*set) : "Ir"(_sig - 1) : "cc");
}

static __inline__ __attribute__((always_inline)) int __const_sigismember(sigset_t *set, int _sig)
{
 unsigned long sig = _sig - 1;
 return 1 & (set->sig[sig / 32] >> (sig % 32));
}

static __inline__ __attribute__((always_inline)) int __gen_sigismember(sigset_t *set, int _sig)
{
 int ret;
 __asm__("btl %2,%1\n\tsbbl %0,%0"
  : "=r"(ret) : "m"(*set), "Ir"(_sig-1) : "cc");
 return ret;
}






static __inline__ __attribute__((always_inline)) int sigfindinword(unsigned long word)
{
 __asm__("bsfl %1,%0" : "=r"(word) : "rm"(word) : "cc");
 return word;
}

struct pt_regs;
extern int do_signal(struct pt_regs *regs, sigset_t *oldset) __attribute__((regparm(3)));
# 7 "include/linux/signal.h" 2
# 1 "include/asm/siginfo.h" 1



# 1 "include/asm-generic/siginfo.h" 1






typedef union sigval {
 int sival_int;
 void *sival_ptr;
} sigval_t;
# 40 "include/asm-generic/siginfo.h"
typedef struct siginfo {
 int si_signo;
 int si_errno;
 int si_code;

 union {
  int _pad[((128 - (3 * sizeof(int))) / sizeof(int))];


  struct {
   pid_t _pid;
   uid_t _uid;
  } _kill;


  struct {
   timer_t _tid;
   int _overrun;
   char _pad[sizeof( uid_t) - sizeof(int)];
   sigval_t _sigval;
   int _sys_private;
  } _timer;


  struct {
   pid_t _pid;
   uid_t _uid;
   sigval_t _sigval;
  } _rt;


  struct {
   pid_t _pid;
   uid_t _uid;
   int _status;
   clock_t _utime;
   clock_t _stime;
  } _sigchld;


  struct {
   void *_addr;



  } _sigfault;


  struct {
   long _band;
   int _fd;
  } _sigpoll;
 } _sifields;
} siginfo_t;
# 251 "include/asm-generic/siginfo.h"
typedef struct sigevent {
 sigval_t sigev_value;
 int sigev_signo;
 int sigev_notify;
 union {
  int _pad[((64 - (sizeof(int) * 2 + sizeof(sigval_t))) / sizeof(int))];
   int _tid;

  struct {
   void (*_function)(sigval_t);
   void *_attribute;
  } _sigev_thread;
 } _sigev_un;
} sigevent_t;







struct siginfo;
void do_schedule_next_timer(struct siginfo *info);





static inline __attribute__((always_inline)) void copy_siginfo(struct siginfo *to, struct siginfo *from)
{
 if (from->si_code < 0)
  __memcpy(to,from,sizeof(*to));
 else

  __memcpy(to,from,(3 * sizeof(int)) + sizeof(from->_sifields._sigchld));
}



extern int copy_siginfo_to_user(struct siginfo *to, struct siginfo *from);
# 5 "include/asm/siginfo.h" 2
# 8 "include/linux/signal.h" 2
# 26 "include/linux/signal.h"
struct sigqueue {
 struct list_head list;
 spinlock_t *lock;
 int flags;
 siginfo_t info;
 struct user_struct *user;
};




struct sigpending {
 struct list_head list;
 sigset_t signal;
};
# 115 "include/linux/signal.h"
static inline __attribute__((always_inline)) void sigorsets(sigset_t *r, const sigset_t *a, const sigset_t *b) { extern void _NSIG_WORDS_is_unsupported_size(void); unsigned long a0, a1, a2, a3, b0, b1, b2, b3; switch ((64 / 32)) { case 4: a3 = a->sig[3]; a2 = a->sig[2]; b3 = b->sig[3]; b2 = b->sig[2]; r->sig[3] = ((a3) | (b3)); r->sig[2] = ((a2) | (b2)); case 2: a1 = a->sig[1]; b1 = b->sig[1]; r->sig[1] = ((a1) | (b1)); case 1: a0 = a->sig[0]; b0 = b->sig[0]; r->sig[0] = ((a0) | (b0)); break; default: _NSIG_WORDS_is_unsupported_size(); } }


static inline __attribute__((always_inline)) void sigandsets(sigset_t *r, const sigset_t *a, const sigset_t *b) { extern void _NSIG_WORDS_is_unsupported_size(void); unsigned long a0, a1, a2, a3, b0, b1, b2, b3; switch ((64 / 32)) { case 4: a3 = a->sig[3]; a2 = a->sig[2]; b3 = b->sig[3]; b2 = b->sig[2]; r->sig[3] = ((a3) & (b3)); r->sig[2] = ((a2) & (b2)); case 2: a1 = a->sig[1]; b1 = b->sig[1]; r->sig[1] = ((a1) & (b1)); case 1: a0 = a->sig[0]; b0 = b->sig[0]; r->sig[0] = ((a0) & (b0)); break; default: _NSIG_WORDS_is_unsupported_size(); } }


static inline __attribute__((always_inline)) void signandsets(sigset_t *r, const sigset_t *a, const sigset_t *b) { extern void _NSIG_WORDS_is_unsupported_size(void); unsigned long a0, a1, a2, a3, b0, b1, b2, b3; switch ((64 / 32)) { case 4: a3 = a->sig[3]; a2 = a->sig[2]; b3 = b->sig[3]; b2 = b->sig[2]; r->sig[3] = ((a3) & ~(b3)); r->sig[2] = ((a2) & ~(b2)); case 2: a1 = a->sig[1]; b1 = b->sig[1]; r->sig[1] = ((a1) & ~(b1)); case 1: a0 = a->sig[0]; b0 = b->sig[0]; r->sig[0] = ((a0) & ~(b0)); break; default: _NSIG_WORDS_is_unsupported_size(); } }
# 145 "include/linux/signal.h"
static inline __attribute__((always_inline)) void signotset(sigset_t *set) { extern void _NSIG_WORDS_is_unsupported_size(void); switch ((64 / 32)) { case 4: set->sig[3] = (~(set->sig[3])); set->sig[2] = (~(set->sig[2])); case 2: set->sig[1] = (~(set->sig[1])); case 1: set->sig[0] = (~(set->sig[0])); break; default: _NSIG_WORDS_is_unsupported_size(); } }




static inline __attribute__((always_inline)) void sigemptyset(sigset_t *set)
{
 switch ((64 / 32)) {
 default:
  __memset_generic((set),(0),(sizeof(sigset_t)));
  break;
 case 2: set->sig[1] = 0;
 case 1: set->sig[0] = 0;
  break;
 }
}

static inline __attribute__((always_inline)) void sigfillset(sigset_t *set)
{
 switch ((64 / 32)) {
 default:
  __memset_generic((set),(-1),(sizeof(sigset_t)));
  break;
 case 2: set->sig[1] = -1;
 case 1: set->sig[0] = -1;
  break;
 }
}



static inline __attribute__((always_inline)) void sigaddsetmask(sigset_t *set, unsigned long mask)
{
 set->sig[0] |= mask;
}

static inline __attribute__((always_inline)) void sigdelsetmask(sigset_t *set, unsigned long mask)
{
 set->sig[0] &= ~mask;
}

static inline __attribute__((always_inline)) int sigtestsetmask(sigset_t *set, unsigned long mask)
{
 return (set->sig[0] & mask) != 0;
}

static inline __attribute__((always_inline)) void siginitset(sigset_t *set, unsigned long mask)
{
 set->sig[0] = mask;
 switch ((64 / 32)) {
 default:
  __memset_generic((&set->sig[1]),(0),(sizeof(long)*((64 / 32)-1)));
  break;
 case 2: set->sig[1] = 0;
 case 1: ;
 }
}

static inline __attribute__((always_inline)) void siginitsetinv(sigset_t *set, unsigned long mask)
{
 set->sig[0] = ~mask;
 switch ((64 / 32)) {
 default:
  __memset_generic((&set->sig[1]),(-1),(sizeof(long)*((64 / 32)-1)));
  break;
 case 2: set->sig[1] = -1;
 case 1: ;
 }
}



static inline __attribute__((always_inline)) void init_sigpending(struct sigpending *sig)
{
 sigemptyset(&sig->signal);
 do { (&sig->list)->next = (&sig->list); (&sig->list)->prev = (&sig->list); } while (0);
}


static inline __attribute__((always_inline)) int valid_signal(unsigned long sig)
{
 return sig <= 64 ? 1 : 0;
}

extern int group_send_sig_info(int sig, struct siginfo *info, struct task_struct *p);
extern int __group_send_sig_info(int, struct siginfo *, struct task_struct *);
extern long do_sigpending(void *, unsigned long);
extern int sigprocmask(int, sigset_t *, sigset_t *);

struct pt_regs;
extern int get_signal_to_deliver(siginfo_t *info, struct k_sigaction *return_ka, struct pt_regs *regs, void *cookie);
# 29 "include/linux/sched.h" 2
# 1 "include/linux/securebits.h" 1





extern unsigned securebits;
# 30 "include/linux/sched.h" 2
# 1 "include/linux/fs_struct.h" 1



struct dentry;
struct vfsmount;

struct fs_struct {
 atomic_t count;
 rwlock_t lock;
 int umask;
 struct dentry * root, * pwd, * altroot;
 struct vfsmount * rootmnt, * pwdmnt, * altrootmnt;
};







extern void exit_fs(struct task_struct *);
extern void set_fs_altroot(void);
extern void set_fs_root(struct fs_struct *, struct vfsmount *, struct dentry *);
extern void set_fs_pwd(struct fs_struct *, struct vfsmount *, struct dentry *);
extern struct fs_struct *copy_fs_struct(struct fs_struct *);
extern void put_fs_struct(struct fs_struct *);
# 31 "include/linux/sched.h" 2

# 1 "include/linux/completion.h" 1
# 13 "include/linux/completion.h"
struct completion {
 unsigned int done;
 wait_queue_head_t wait;
};







static inline __attribute__((always_inline)) void init_completion(struct completion *x)
{
 x->done = 0;
 init_waitqueue_head(&x->wait);
}

extern void wait_for_completion(struct completion *) __attribute__((regparm(3)));
extern int wait_for_completion_interruptible(struct completion *x) __attribute__((regparm(3)));
extern unsigned long wait_for_completion_timeout(struct completion *x, unsigned long timeout) __attribute__((regparm(3)));

extern unsigned long wait_for_completion_interruptible_timeout( struct completion *x, unsigned long timeout) __attribute__((regparm(3)));


extern void complete(struct completion *) __attribute__((regparm(3)));
extern void complete_all(struct completion *) __attribute__((regparm(3)));
# 33 "include/linux/sched.h" 2
# 1 "include/linux/pid.h" 1



enum pid_type
{
 PIDTYPE_PID,
 PIDTYPE_TGID,
 PIDTYPE_PGID,
 PIDTYPE_SID,
 PIDTYPE_MAX
};

struct pid
{

 int nr;
 struct hlist_node pid_chain;

 struct list_head pid_list;
};
# 29 "include/linux/pid.h"
extern int attach_pid(struct task_struct *task, enum pid_type type, int nr) __attribute__((regparm(3)));

extern void detach_pid(struct task_struct *task, enum pid_type) __attribute__((regparm(3)));





extern struct pid *find_pid(enum pid_type, int) __attribute__((regparm(3)));

extern int alloc_pidmap(void);
extern void free_pidmap(int) __attribute__((regparm(3)));
extern void switch_exec_pids(struct task_struct *leader, struct task_struct *thread);
# 34 "include/linux/sched.h" 2
# 1 "include/linux/percpu.h" 1



# 1 "include/linux/slab.h" 1
# 12 "include/linux/slab.h"
typedef struct kmem_cache_s kmem_cache_t;


# 1 "include/linux/gfp.h" 1



# 1 "include/linux/mmzone.h" 1
# 14 "include/linux/mmzone.h"
# 1 "include/linux/init.h" 1
# 64 "include/linux/init.h"
typedef int (*initcall_t)(void);
typedef void (*exitcall_t)(void);

extern initcall_t __con_initcall_start[], __con_initcall_end[];
extern initcall_t __security_initcall_start[], __security_initcall_end[];


extern char saved_command_line[];
# 110 "include/linux/init.h"
struct obs_kernel_param {
 const char *str;
 int (*setup_func)(char *);
 int early;
};
# 145 "include/linux/init.h"
void __attribute__ ((__section__ (".init.text"))) parse_early_param(void);
# 15 "include/linux/mmzone.h" 2
# 24 "include/linux/mmzone.h"
struct free_area {
 struct list_head free_list;
 unsigned long nr_free;
};

struct pglist_data;
# 38 "include/linux/mmzone.h"
struct zone_padding {
 char x[0];
} __attribute__((__aligned__(1 << (7))));





struct per_cpu_pages {
 int count;
 int low;
 int high;
 int batch;
 struct list_head list;
};

struct per_cpu_pageset {
 struct per_cpu_pages pcp[2];
# 64 "include/linux/mmzone.h"
} __attribute__((__aligned__((1 << (7)))));
# 117 "include/linux/mmzone.h"
struct zone {

 unsigned long free_pages;
 unsigned long pages_min, pages_low, pages_high;
# 129 "include/linux/mmzone.h"
 unsigned long lowmem_reserve[3];




 struct per_cpu_pageset pageset[8];




 spinlock_t lock;
 struct free_area free_area[11];


 struct zone_padding _pad1_;


 spinlock_t lru_lock;
 struct list_head active_list;
 struct list_head inactive_list;
 unsigned long nr_scan_active;
 unsigned long nr_scan_inactive;
 unsigned long nr_active;
 unsigned long nr_inactive;
 unsigned long pages_scanned;
 int all_unreclaimable;





 int reclaim_pages;

 atomic_t reclaim_in_progress;
# 180 "include/linux/mmzone.h"
 int temp_priority;
 int prev_priority;


 struct zone_padding _pad2_;
# 211 "include/linux/mmzone.h"
 wait_queue_head_t * wait_table;
 unsigned long wait_table_size;
 unsigned long wait_table_bits;




 struct pglist_data *zone_pgdat;
 struct page *zone_mem_map;

 unsigned long zone_start_pfn;

 unsigned long spanned_pages;
 unsigned long present_pages;




 char *name;
} __attribute__((__aligned__(1 << (7))));
# 251 "include/linux/mmzone.h"
struct zonelist {
 struct zone *zones[(1 << 0) * 3 + 1];
};
# 267 "include/linux/mmzone.h"
struct bootmem_data;
typedef struct pglist_data {
 struct zone node_zones[3];
 struct zonelist node_zonelists[((0x03 + 1) / 2 + 1)];
 int nr_zones;

 struct page *node_mem_map;

 struct bootmem_data *bdata;
 unsigned long node_start_pfn;
 unsigned long node_present_pages;
 unsigned long node_spanned_pages;

 int node_id;
 struct pglist_data *pgdat_next;
 wait_queue_head_t kswapd_wait;
 struct task_struct *kswapd;
 int kswapd_max_order;
} pg_data_t;
# 296 "include/linux/mmzone.h"
extern struct pglist_data *pgdat_list;

void __get_zone_counts(unsigned long *active, unsigned long *inactive,
   unsigned long *free, struct pglist_data *pgdat);
void get_zone_counts(unsigned long *active, unsigned long *inactive,
   unsigned long *free);
void build_all_zonelists(void);
void wakeup_kswapd(struct zone *zone, int order);
int zone_watermark_ok(struct zone *z, int order, unsigned long mark,
  int alloc_type, int can_try_harder, int gfp_high);




static inline __attribute__((always_inline)) void memory_present(int nid, unsigned long start, unsigned long end) {}
# 340 "include/linux/mmzone.h"
static inline __attribute__((always_inline)) struct zone *next_zone(struct zone *zone)
{
 pg_data_t *pgdat = zone->zone_pgdat;

 if (zone < pgdat->node_zones + 3 - 1)
  zone++;
 else if (pgdat->pgdat_next) {
  pgdat = pgdat->pgdat_next;
  zone = pgdat->node_zones;
 } else
  zone = ((void *)0);

 return zone;
}
# 373 "include/linux/mmzone.h"
static inline __attribute__((always_inline)) int is_highmem_idx(int idx)
{
 return (idx == 2);
}

static inline __attribute__((always_inline)) int is_normal_idx(int idx)
{
 return (idx == 1);
}






static inline __attribute__((always_inline)) int is_highmem(struct zone *zone)
{
 return zone == zone->zone_pgdat->node_zones + 2;
}

static inline __attribute__((always_inline)) int is_normal(struct zone *zone)
{
 return zone == zone->zone_pgdat->node_zones + 1;
}


struct ctl_table;
struct file;
int min_free_kbytes_sysctl_handler(struct ctl_table *, int, struct file *,
     void *, size_t *, loff_t *);
extern int sysctl_lowmem_reserve_ratio[3 -1];
int lowmem_reserve_ratio_sysctl_handler(struct ctl_table *, int, struct file *,
     void *, size_t *, loff_t *);

# 1 "include/linux/topology.h" 1
# 32 "include/linux/topology.h"
# 1 "include/linux/mmzone.h" 1
# 33 "include/linux/topology.h" 2

# 1 "include/asm/topology.h" 1
# 103 "include/asm/topology.h"
# 1 "include/asm-generic/topology.h" 1
# 104 "include/asm/topology.h" 2
# 35 "include/linux/topology.h" 2
# 408 "include/linux/mmzone.h" 2





extern struct pglist_data contig_page_data;
# 587 "include/linux/mmzone.h"
void memory_present(int nid, unsigned long start, unsigned long end);
unsigned long __attribute__ ((__section__ (".init.text"))) node_memmap_size_bytes(int, unsigned long, unsigned long);
# 5 "include/linux/gfp.h" 2




struct vm_area_struct;
# 82 "include/linux/gfp.h"
static inline __attribute__((always_inline)) void arch_free_page(struct page *page, int order) { }


extern struct page *
__alloc_pages(unsigned int, unsigned int, struct zonelist *) __attribute__((regparm(3)));

static inline __attribute__((always_inline)) struct page *alloc_pages_node(int nid, unsigned int gfp_mask,
      unsigned int order)
{
 if (__builtin_expect(!!(order >= 11), 0))
  return ((void *)0);

 return __alloc_pages(gfp_mask, order,
  (&contig_page_data)->node_zonelists + (gfp_mask & 0x03));
}
# 118 "include/linux/gfp.h"
extern unsigned long __get_free_pages(unsigned int gfp_mask, unsigned int order) __attribute__((regparm(3)));
extern unsigned long get_zeroed_page(unsigned int gfp_mask) __attribute__((regparm(3)));







extern void __free_pages(struct page *page, unsigned int order) __attribute__((regparm(3)));
extern void free_pages(unsigned long addr, unsigned int order) __attribute__((regparm(3)));
extern void free_hot_page(struct page *page) __attribute__((regparm(3)));
extern void free_cold_page(struct page *page) __attribute__((regparm(3)));




void page_alloc_init(void);



static inline __attribute__((always_inline)) void drain_remote_pages(void) { };
# 16 "include/linux/slab.h" 2
# 57 "include/linux/slab.h"
extern void __attribute__ ((__section__ (".init.text"))) kmem_cache_init(void);

extern kmem_cache_t *kmem_cache_create(const char *, size_t, size_t, unsigned long,
           void (*)(void *, kmem_cache_t *, unsigned long),
           void (*)(void *, kmem_cache_t *, unsigned long));
extern int kmem_cache_destroy(kmem_cache_t *);
extern int kmem_cache_shrink(kmem_cache_t *);
extern void *kmem_cache_alloc(kmem_cache_t *, unsigned int );
extern void kmem_cache_free(kmem_cache_t *, void *);
extern unsigned int kmem_cache_size(kmem_cache_t *);
extern const char *kmem_cache_name(kmem_cache_t *);
extern kmem_cache_t *kmem_find_general_cachep(size_t size, unsigned int gfpflags);


struct cache_sizes {
 size_t cs_size;
 kmem_cache_t *cs_cachep;
 kmem_cache_t *cs_dmacachep;
};
extern struct cache_sizes malloc_sizes[];
extern void *__kmalloc(size_t, unsigned int );

static inline __attribute__((always_inline)) void *kmalloc(size_t size, unsigned int flags)
{
 if (__builtin_constant_p(size)) {
  int i = 0;





# 1 "include/linux/kmalloc_sizes.h" 1

 if (size <= 32) goto found; else i++;

 if (size <= 64) goto found; else i++;



 if (size <= 128) goto found; else i++;



 if (size <= 256) goto found; else i++;
 if (size <= 512) goto found; else i++;
 if (size <= 1024) goto found; else i++;
 if (size <= 2048) goto found; else i++;
 if (size <= 4096) goto found; else i++;
 if (size <= 8192) goto found; else i++;
 if (size <= 16384) goto found; else i++;
 if (size <= 32768) goto found; else i++;
 if (size <= 65536) goto found; else i++;
 if (size <= 131072) goto found; else i++;
# 89 "include/linux/slab.h" 2

  {
   extern void __you_cannot_kmalloc_that_much(void);
   __you_cannot_kmalloc_that_much();
  }
found:
  return kmem_cache_alloc((flags & 0x01u) ?
   malloc_sizes[i].cs_dmacachep :
   malloc_sizes[i].cs_cachep, flags);
 }
 return __kmalloc(size, flags);
}

extern void *kcalloc(size_t, size_t, unsigned int );
extern void kfree(const void *);
extern unsigned int ksize(const void *);





static inline __attribute__((always_inline)) void *kmem_cache_alloc_node(kmem_cache_t *cachep, int flags, int node)
{
 return kmem_cache_alloc(cachep, flags);
}
static inline __attribute__((always_inline)) void *kmalloc_node(size_t size, unsigned int flags, int node)
{
 return kmalloc(size, flags);
}


extern int kmem_cache_reap(int) __attribute__((regparm(3)));
extern int kmem_ptr_validate(kmem_cache_t *cachep, void *ptr) __attribute__((regparm(3)));


extern kmem_cache_t *vm_area_cachep;
extern kmem_cache_t *names_cachep;
extern kmem_cache_t *files_cachep;
extern kmem_cache_t *filp_cachep;
extern kmem_cache_t *fs_cachep;
extern kmem_cache_t *signal_cachep;
extern kmem_cache_t *sighand_cachep;
extern kmem_cache_t *bio_cachep;

extern atomic_t slab_reclaim_pages;
# 5 "include/linux/percpu.h" 2
# 20 "include/linux/percpu.h"
struct percpu_data {
 void *ptrs[8];
 void *blkp;
};
# 36 "include/linux/percpu.h"
extern void *__alloc_percpu(size_t size, size_t align);
extern void free_percpu(const void *);
# 35 "include/linux/sched.h" 2

# 1 "include/linux/seccomp.h" 1
# 11 "include/linux/seccomp.h"
# 1 "include/asm/seccomp.h" 1
# 9 "include/asm/seccomp.h"
# 1 "include/linux/unistd.h" 1



extern int errno;




# 1 "include/asm/unistd.h" 1
# 10 "include/linux/unistd.h" 2
# 10 "include/asm/seccomp.h" 2
# 12 "include/linux/seccomp.h" 2

typedef struct { int mode; } seccomp_t;

extern void __secure_computing(int);
static inline __attribute__((always_inline)) void secure_computing(int this_syscall)
{
 if (__builtin_expect(!!(test_thread_flag(8)), 0))
  __secure_computing(this_syscall);
}

static inline __attribute__((always_inline)) int has_secure_computing(struct thread_info *ti)
{
 return __builtin_expect(!!(test_ti_thread_flag(ti, 8)), 0);
}
# 37 "include/linux/sched.h" 2

struct exec_domain;
# 78 "include/linux/sched.h"
extern unsigned long avenrun[];
# 92 "include/linux/sched.h"
extern unsigned long total_forks;
extern int nr_threads;
extern int last_pid;
extern __typeof__(unsigned long) per_cpu__process_counts;
extern int nr_processes(void);
extern unsigned long nr_running(void);
extern unsigned long nr_uninterruptible(void);
extern unsigned long nr_iowait(void);


# 1 "include/linux/param.h" 1



# 1 "include/asm/param.h" 1
# 5 "include/linux/param.h" 2
# 103 "include/linux/sched.h" 2
# 1 "include/linux/resource.h" 1
# 21 "include/linux/resource.h"
struct rusage {
 struct timeval ru_utime;
 struct timeval ru_stime;
 long ru_maxrss;
 long ru_ixrss;
 long ru_idrss;
 long ru_isrss;
 long ru_minflt;
 long ru_majflt;
 long ru_nswap;
 long ru_inblock;
 long ru_oublock;
 long ru_msgsnd;
 long ru_msgrcv;
 long ru_nsignals;
 long ru_nvcsw;
 long ru_nivcsw;
};

struct rlimit {
 unsigned long rlim_cur;
 unsigned long rlim_max;
};
# 68 "include/linux/resource.h"
# 1 "include/asm/resource.h" 1



# 1 "include/asm-generic/resource.h" 1
# 5 "include/asm/resource.h" 2
# 69 "include/linux/resource.h" 2
# 104 "include/linux/sched.h" 2
# 1 "include/linux/timer.h" 1
# 9 "include/linux/timer.h"
struct timer_base_s;

struct timer_list {
 struct list_head entry;
 unsigned long expires;

 unsigned long magic;

 void (*function)(unsigned long);
 unsigned long data;

 struct timer_base_s *base;
};



extern struct timer_base_s __init_timer_base;
# 35 "include/linux/timer.h"
void __attribute__((regparm(3))) init_timer(struct timer_list * timer);
# 47 "include/linux/timer.h"
static inline __attribute__((always_inline)) int timer_pending(const struct timer_list * timer)
{
 return timer->entry.next != ((void *)0);
}

extern void add_timer_on(struct timer_list *timer, int cpu);
extern int del_timer(struct timer_list * timer);
extern int __mod_timer(struct timer_list *timer, unsigned long expires);
extern int mod_timer(struct timer_list *timer, unsigned long expires);

extern unsigned long next_timer_interrupt(void);
# 73 "include/linux/timer.h"
static inline __attribute__((always_inline)) void add_timer(struct timer_list * timer)
{
 __mod_timer(timer, timer->expires);
}


  extern int try_to_del_timer_sync(struct timer_list *timer);
  extern int del_timer_sync(struct timer_list *timer);







extern void init_timers(void);
extern void run_local_timers(void);
extern void it_real_fn(unsigned long);
# 105 "include/linux/sched.h" 2
# 136 "include/linux/sched.h"
struct sched_param {
 int sched_priority;
};
# 150 "include/linux/sched.h"
extern rwlock_t tasklist_lock;
extern spinlock_t mmlist_lock;

typedef struct task_struct task_t;

extern void sched_init(void);
extern void sched_init_smp(void);
extern void init_idle(task_t *idle, int cpu);

extern cpumask_t nohz_cpu_mask;

extern void show_state(void);
extern void show_regs(struct pt_regs *);






extern void show_stack(struct task_struct *task, unsigned long *sp);

void io_schedule(void);
long io_schedule_timeout(long timeout);

extern void cpu_init (void);
extern void trap_init(void);
extern void update_process_times(int user);
extern void scheduler_tick(void);




extern int in_sched_functions(unsigned long addr);


extern signed long schedule_timeout(signed long timeout) __attribute__((regparm(3)));
 __attribute__((regparm(0))) void schedule(void);

struct namespace;




extern int sysctl_max_map_count;

# 1 "include/linux/aio.h" 1




# 1 "include/linux/workqueue.h" 1
# 12 "include/linux/workqueue.h"
struct workqueue_struct;

struct work_struct {
 unsigned long pending;
 struct list_head entry;
 void (*func)(void *);
 void *data;
 void *wq_data;
 struct timer_list timer;
};
# 53 "include/linux/workqueue.h"
extern struct workqueue_struct *__create_workqueue(const char *name,
          int singlethread);



extern void destroy_workqueue(struct workqueue_struct *wq);

extern int queue_work(struct workqueue_struct *wq, struct work_struct *work) __attribute__((regparm(3)));
extern int queue_delayed_work(struct workqueue_struct *wq, struct work_struct *work, unsigned long delay) __attribute__((regparm(3)));
extern void flush_workqueue(struct workqueue_struct *wq) __attribute__((regparm(3)));

extern int schedule_work(struct work_struct *work) __attribute__((regparm(3)));
extern int schedule_delayed_work(struct work_struct *work, unsigned long delay) __attribute__((regparm(3)));

extern int schedule_delayed_work_on(int cpu, struct work_struct *work, unsigned long delay);
extern void flush_scheduled_work(void);
extern int current_is_keventd(void);
extern int keventd_up(void);

extern void init_workqueues(void);
void cancel_rearming_delayed_work(struct work_struct *work);
void cancel_rearming_delayed_workqueue(struct workqueue_struct *,
           struct work_struct *);






static inline __attribute__((always_inline)) int cancel_delayed_work(struct work_struct *work)
{
 int ret;

 ret = del_timer_sync(&work->timer);
 if (ret)
  clear_bit(0, &work->pending);
 return ret;
}
# 6 "include/linux/aio.h" 2
# 1 "include/linux/aio_abi.h" 1
# 32 "include/linux/aio_abi.h"
typedef unsigned long aio_context_t;

enum {
 IOCB_CMD_PREAD = 0,
 IOCB_CMD_PWRITE = 1,
 IOCB_CMD_FSYNC = 2,
 IOCB_CMD_FDSYNC = 3,




 IOCB_CMD_NOOP = 6,
};


struct io_event {
 __u64 data;
 __u64 obj;
 __s64 res;
 __s64 res2;
};
# 68 "include/linux/aio_abi.h"
struct iocb {

 __u64 aio_data;
 __u32 aio_key, aio_reserved1;



 __u16 aio_lio_opcode;
 __s16 aio_reqprio;
 __u32 aio_fildes;

 __u64 aio_buf;
 __u64 aio_nbytes;
 __s64 aio_offset;


 __u64 aio_reserved2;
 __u64 aio_reserved3;
};
# 7 "include/linux/aio.h" 2






struct kioctx;
# 46 "include/linux/aio.h"
struct kiocb {
 struct list_head ki_run_list;
 long ki_flags;
 int ki_users;
 unsigned ki_key;

 struct file *ki_filp;
 struct kioctx *ki_ctx;
 int (*ki_cancel)(struct kiocb *, struct io_event *);
 ssize_t (*ki_retry)(struct kiocb *);
 void (*ki_dtor)(struct kiocb *);

 struct list_head ki_list;


 union {
  void *user;
  struct task_struct *tsk;
 } ki_obj;
 __u64 ki_user_data;
 loff_t ki_pos;

 unsigned short ki_opcode;
 size_t ki_nbytes;
 char *ki_buf;
 size_t ki_left;
 wait_queue_t ki_wait;
 long ki_retried;
 long ki_kicked;
 long ki_queued;

 void *private;
};
# 99 "include/linux/aio.h"
struct aio_ring {
 unsigned id;
 unsigned nr;
 unsigned head;
 unsigned tail;

 unsigned magic;
 unsigned compat_features;
 unsigned incompat_features;
 unsigned header_length;


 struct io_event io_events[0];
};




struct aio_ring_info {
 unsigned long mmap_base;
 unsigned long mmap_size;

 struct page **ring_pages;
 spinlock_t ring_lock;
 long nr_pages;

 unsigned nr, tail;

 struct page *internal_pages[8];
};

struct kioctx {
 atomic_t users;
 int dead;
 struct mm_struct *mm;


 unsigned long user_id;
 struct kioctx *next;

 wait_queue_head_t wait;

 spinlock_t ctx_lock;

 int reqs_active;
 struct list_head active_reqs;
 struct list_head run_list;

 unsigned max_reqs;

 struct aio_ring_info ring_info;

 struct work_struct wq;
};


extern unsigned aio_max_size;

extern ssize_t wait_on_sync_kiocb(struct kiocb *iocb) __attribute__((regparm(3)));
extern int aio_put_req(struct kiocb *iocb) __attribute__((regparm(3)));
extern void kick_iocb(struct kiocb *iocb) __attribute__((regparm(3)));
extern int aio_complete(struct kiocb *iocb, long res, long res2) __attribute__((regparm(3)));
extern void __put_ioctx(struct kioctx *ctx) __attribute__((regparm(3)));
struct mm_struct;
extern void exit_aio(struct mm_struct *mm) __attribute__((regparm(3)));
extern struct kioctx *lookup_ioctx(unsigned long ctx_id);
extern int io_submit_one(struct kioctx *ctx, struct iocb *user_iocb, struct iocb *iocb) __attribute__((regparm(3)));



struct kioctx *lookup_ioctx(unsigned long ctx_id);
int io_submit_one(struct kioctx *ctx, struct iocb *user_iocb, struct iocb *iocb) __attribute__((regparm(3)));
# 192 "include/linux/aio.h"
static inline __attribute__((always_inline)) struct kiocb *list_kiocb(struct list_head *h)
{
 return ({ const typeof( ((struct kiocb *)0)->ki_list ) *__mptr = (h); (struct kiocb *)( (char *)__mptr - __builtin_offsetof(struct kiocb,ki_list) );});
}


extern atomic_t aio_nr;
extern unsigned aio_max_nr;
# 196 "include/linux/sched.h" 2

extern unsigned long
arch_get_unmapped_area(struct file *, unsigned long, unsigned long,
         unsigned long, unsigned long);
extern unsigned long
arch_get_unmapped_area_topdown(struct file *filp, unsigned long addr,
     unsigned long len, unsigned long pgoff,
     unsigned long flags);
extern void arch_unmap_area(struct mm_struct *, unsigned long);
extern void arch_unmap_area_topdown(struct mm_struct *, unsigned long);






typedef unsigned long mm_counter_t;

struct mm_struct {
 struct vm_area_struct * mmap;
 struct rb_root mm_rb;
 struct vm_area_struct * mmap_cache;
 unsigned long (*get_unmapped_area) (struct file *filp,
    unsigned long addr, unsigned long len,
    unsigned long pgoff, unsigned long flags);
 void (*unmap_area) (struct mm_struct *mm, unsigned long addr);
        unsigned long mmap_base;
        unsigned long cached_hole_size;
 unsigned long free_area_cache;
 pgd_t * pgd;
 atomic_t mm_users;
 atomic_t mm_count;
 int map_count;
 struct rw_semaphore mmap_sem;
 spinlock_t page_table_lock;

 struct list_head mmlist;




 unsigned long start_code, end_code, start_data, end_data;
 unsigned long start_brk, brk, start_stack;
 unsigned long arg_start, arg_end, env_start, env_end;
 unsigned long total_vm, locked_vm, shared_vm;
 unsigned long exec_vm, stack_vm, reserved_vm, def_flags, nr_ptes;


 mm_counter_t _rss;
 mm_counter_t _anon_rss;

 unsigned long saved_auxv[42];

 unsigned dumpable:2;
 cpumask_t cpu_vm_mask;


 mm_context_t context;


 unsigned long swap_token_time;
 char recent_pagein;


 int core_waiters;
 struct completion *core_startup_done, core_done;


 rwlock_t ioctx_list_lock;
 struct kioctx *ioctx_list;

 struct kioctx default_kioctx;

 unsigned long hiwater_rss;
 unsigned long hiwater_vm;
};

struct sighand_struct {
 atomic_t count;
 struct k_sigaction action[64];
 spinlock_t siglock;
};
# 286 "include/linux/sched.h"
struct signal_struct {
 atomic_t count;
 atomic_t live;

 wait_queue_head_t wait_chldexit;


 task_t *curr_target;


 struct sigpending shared_pending;


 int group_exit_code;





 struct task_struct *group_exit_task;
 int notify_count;


 int group_stop_count;
 unsigned int flags;


 struct list_head posix_timers;


 struct timer_list real_timer;
 unsigned long it_real_value, it_real_incr;


 cputime_t it_prof_expires, it_virt_expires;
 cputime_t it_prof_incr, it_virt_incr;


 pid_t pgrp;
 pid_t tty_old_pgrp;
 pid_t session;

 int leader;

 struct tty_struct *tty;







 cputime_t utime, stime, cutime, cstime;
 unsigned long nvcsw, nivcsw, cnvcsw, cnivcsw;
 unsigned long min_flt, maj_flt, cmin_flt, cmaj_flt;







 unsigned long long sched_time;
# 359 "include/linux/sched.h"
 struct rlimit rlim[15];

 struct list_head cpu_timers[3];




 struct key *session_keyring;
 struct key *process_keyring;

};
# 408 "include/linux/sched.h"
struct user_struct {
 atomic_t __count;
 atomic_t processes;
 atomic_t files;
 atomic_t sigpending;

 atomic_t inotify_watches;
 atomic_t inotify_devs;


 unsigned long mq_bytes;
 unsigned long locked_shm;


 struct key *uid_keyring;
 struct key *session_keyring;



 struct list_head uidhash_list;
 uid_t uid;
};

extern struct user_struct *find_user(uid_t);

extern struct user_struct root_user;


typedef struct prio_array prio_array_t;
struct backing_dev_info;
struct reclaim_state;


struct sched_info {

 unsigned long cpu_time,
   run_delay,
   pcnt;


 unsigned long last_arrival,
   last_queued;
};

extern struct file_operations proc_schedstat_operations;


enum idle_type
{
 SCHED_IDLE,
 NOT_IDLE,
 NEWLY_IDLE,
 MAX_IDLE_TYPES
};
# 478 "include/linux/sched.h"
struct sched_group {
 struct sched_group *next;
 cpumask_t cpumask;





 unsigned long cpu_power;
};

struct sched_domain {

 struct sched_domain *parent;
 struct sched_group *groups;
 cpumask_t span;
 unsigned long min_interval;
 unsigned long max_interval;
 unsigned int busy_factor;
 unsigned int imbalance_pct;
 unsigned long long cache_hot_time;
 unsigned int cache_nice_tries;
 unsigned int per_cpu_gain;
 unsigned int busy_idx;
 unsigned int idle_idx;
 unsigned int newidle_idx;
 unsigned int wake_idx;
 unsigned int forkexec_idx;
 int flags;


 unsigned long last_balance;
 unsigned int balance_interval;
 unsigned int nr_balance_failed;



 unsigned long lb_cnt[MAX_IDLE_TYPES];
 unsigned long lb_failed[MAX_IDLE_TYPES];
 unsigned long lb_balanced[MAX_IDLE_TYPES];
 unsigned long lb_imbalance[MAX_IDLE_TYPES];
 unsigned long lb_gained[MAX_IDLE_TYPES];
 unsigned long lb_hot_gained[MAX_IDLE_TYPES];
 unsigned long lb_nobusyg[MAX_IDLE_TYPES];
 unsigned long lb_nobusyq[MAX_IDLE_TYPES];


 unsigned long alb_cnt;
 unsigned long alb_failed;
 unsigned long alb_pushed;


 unsigned long sbe_cnt;
 unsigned long sbe_balanced;
 unsigned long sbe_pushed;


 unsigned long sbf_cnt;
 unsigned long sbf_balanced;
 unsigned long sbf_pushed;


 unsigned long ttwu_wake_remote;
 unsigned long ttwu_move_affine;
 unsigned long ttwu_move_balance;

};

extern void partition_sched_domains(cpumask_t *partition1,
        cpumask_t *partition2);
# 558 "include/linux/sched.h"
struct io_context;
void exit_io_context(void);
struct cpuset;



struct group_info {
 int ngroups;
 atomic_t usage;
 gid_t small_block[32];
 int nblocks;
 gid_t *blocks[0];
};
# 587 "include/linux/sched.h"
extern struct group_info *groups_alloc(int gidsetsize);
extern void groups_free(struct group_info *group_info);
extern int set_current_groups(struct group_info *group_info);
extern int groups_search(struct group_info *group_info, gid_t grp);





struct audit_context;
struct mempolicy;

struct task_struct {
 volatile long state;
 struct thread_info *thread_info;
 atomic_t usage;
 unsigned long flags;
 unsigned long ptrace;

 int lock_depth;




 int prio, static_prio;
 struct list_head run_list;
 prio_array_t *array;

 unsigned short ioprio;

 unsigned long sleep_avg;
 unsigned long long timestamp, last_ran;
 unsigned long long sched_time;
 int activated;

 unsigned long policy;
 cpumask_t cpus_allowed;
 unsigned int time_slice, first_time_slice;


 struct sched_info sched_info;


 struct list_head tasks;




 struct list_head ptrace_children;
 struct list_head ptrace_list;

 struct mm_struct *mm, *active_mm;


 struct linux_binfmt *binfmt;
 long exit_state;
 int exit_code, exit_signal;
 int pdeath_signal;

 unsigned long personality;
 unsigned did_exec:1;
 pid_t pid;
 pid_t tgid;





 struct task_struct *real_parent;
 struct task_struct *parent;




 struct list_head children;
 struct list_head sibling;
 struct task_struct *group_leader;


 struct pid pids[PIDTYPE_MAX];

 struct completion *vfork_done;
 int *set_child_tid;
 int *clear_child_tid;

 unsigned long rt_priority;
 cputime_t utime, stime;
 unsigned long nvcsw, nivcsw;
 struct timespec start_time;

 unsigned long min_flt, maj_flt;

   cputime_t it_prof_expires, it_virt_expires;
 unsigned long long it_sched_expires;
 struct list_head cpu_timers[3];


 uid_t uid,euid,suid,fsuid;
 gid_t gid,egid,sgid,fsgid;
 struct group_info *group_info;
 kernel_cap_t cap_effective, cap_inheritable, cap_permitted;
 unsigned keep_capabilities:1;
 struct user_struct *user;

 struct key *thread_keyring;
 unsigned char jit_keyring;

 int oomkilladj;
 char comm[16];




 int link_count, total_link_count;

 struct sysv_sem sysvsem;

 struct thread_struct thread;

 struct fs_struct *fs;

 struct files_struct *files;

 struct namespace *namespace;

 struct signal_struct *signal;
 struct sighand_struct *sighand;

 sigset_t blocked, real_blocked;
 struct sigpending pending;

 unsigned long sas_ss_sp;
 size_t sas_ss_size;
 int (*notifier)(void *priv);
 void *notifier_data;
 sigset_t *notifier_mask;

 void *security;
 struct audit_context *audit_context;
 seccomp_t seccomp;


    u32 parent_exec_id;
    u32 self_exec_id;

 spinlock_t alloc_lock;

 spinlock_t proc_lock;


 void *journal_info;


 struct reclaim_state *reclaim_state;

 struct dentry *proc_dentry;
 struct backing_dev_info *backing_dev_info;

 struct io_context *io_context;

 unsigned long ptrace_message;
 siginfo_t *last_siginfo;






 wait_queue_t *io_wait;

 u64 rchar, wchar, syscr, syscw;

 u64 acct_rss_mem1;
 u64 acct_vm_mem1;
 clock_t acct_stimexpd;






 struct cpuset *cpuset;
 nodemask_t mems_allowed;
 int cpuset_mems_generation;

 atomic_t fs_excl;
};

static inline __attribute__((always_inline)) pid_t process_group(struct task_struct *tsk)
{
 return tsk->signal->pgrp;
}
# 788 "include/linux/sched.h"
static inline __attribute__((always_inline)) int pid_alive(struct task_struct *p)
{
 return p->pids[PIDTYPE_PID].nr != 0;
}

extern void free_task(struct task_struct *tsk);
extern void __put_task_struct(struct task_struct *tsk);
# 851 "include/linux/sched.h"
extern int set_cpus_allowed(task_t *p, cpumask_t new_mask);
# 861 "include/linux/sched.h"
extern unsigned long long sched_clock(void);
extern unsigned long long current_sched_time(const task_t *current_task);



extern void sched_exec(void);





extern void idle_task_exit(void);




extern void sched_idle_next(void);
extern void set_user_nice(task_t *p, long nice);
extern int task_prio(const task_t *p);
extern int task_nice(const task_t *p);
extern int can_nice(const task_t *p, const int nice);
extern int task_curr(const task_t *p);
extern int idle_cpu(int cpu);
extern int sched_setscheduler(struct task_struct *, int, struct sched_param *);
extern task_t *idle_task(int cpu);

void yield(void);




extern struct exec_domain default_exec_domain;

union thread_union {
 struct thread_info thread_info;
 unsigned long stack[(4096)/sizeof(long)];
};


static inline __attribute__((always_inline)) int kstack_end(void *addr)
{



 return !(((unsigned long)addr+sizeof(void*)-1) & ((4096)-sizeof(void*)));
}


extern union thread_union init_thread_union;
extern struct task_struct init_task;

extern struct mm_struct init_mm;


extern struct task_struct *find_task_by_pid_type(int type, int pid);
extern void set_special_pids(pid_t session, pid_t pgrp);
extern void __set_special_pids(pid_t session, pid_t pgrp);


extern struct user_struct * alloc_uid(uid_t);
static inline __attribute__((always_inline)) struct user_struct *get_uid(struct user_struct *u)
{
 atomic_inc(&u->__count);
 return u;
}
extern void free_uid(struct user_struct *);
extern void switch_uid(struct user_struct *);



extern void do_timer(struct pt_regs *);

extern int wake_up_state(struct task_struct * tsk, unsigned int state) __attribute__((regparm(3)));
extern int wake_up_process(struct task_struct * tsk) __attribute__((regparm(3)));
extern void wake_up_new_task(struct task_struct * tsk, unsigned long clone_flags) __attribute__((regparm(3)));


 extern void kick_process(struct task_struct *tsk);



extern void sched_fork(task_t * p, int clone_flags) __attribute__((regparm(3)));
extern void sched_exit(task_t * p) __attribute__((regparm(3)));

extern int in_group_p(gid_t);
extern int in_egroup_p(gid_t);

extern void proc_caches_init(void);
extern void flush_signals(struct task_struct *);
extern void flush_signal_handlers(struct task_struct *, int force_default);
extern int dequeue_signal(struct task_struct *tsk, sigset_t *mask, siginfo_t *info);

static inline __attribute__((always_inline)) int dequeue_signal_lock(struct task_struct *tsk, sigset_t *mask, siginfo_t *info)
{
 unsigned long flags;
 int ret;

 flags = _spin_lock_irqsave(&tsk->sighand->siglock);
 ret = dequeue_signal(tsk, mask, info);
 _spin_unlock_irqrestore(&tsk->sighand->siglock, flags);

 return ret;
}

extern void block_all_signals(int (*notifier)(void *priv), void *priv,
         sigset_t *mask);
extern void unblock_all_signals(void);
extern void release_task(struct task_struct * p);
extern int send_sig_info(int, struct siginfo *, struct task_struct *);
extern int send_group_sig_info(int, struct siginfo *, struct task_struct *);
extern int force_sigsegv(int, struct task_struct *);
extern int force_sig_info(int, struct siginfo *, struct task_struct *);
extern int __kill_pg_info(int sig, struct siginfo *info, pid_t pgrp);
extern int kill_pg_info(int, struct siginfo *, pid_t);
extern int kill_proc_info(int, struct siginfo *, pid_t);
extern void do_notify_parent(struct task_struct *, int);
extern void force_sig(int, struct task_struct *);
extern void force_sig_specific(int, struct task_struct *);
extern int send_sig(int, struct task_struct *, int);
extern void zap_other_threads(struct task_struct *p);
extern int kill_pg(pid_t, int, int);
extern int kill_sl(pid_t, int, int);
extern int kill_proc(pid_t, int, int);
extern struct sigqueue *sigqueue_alloc(void);
extern void sigqueue_free(struct sigqueue *);
extern int send_sigqueue(int, struct sigqueue *, struct task_struct *);
extern int send_group_sigqueue(int, struct sigqueue *, struct task_struct *);
extern int do_sigaction(int, const struct k_sigaction *, struct k_sigaction *);
extern int do_sigaltstack(const stack_t *, stack_t *, unsigned long);
# 998 "include/linux/sched.h"
static inline __attribute__((always_inline)) int on_sig_stack(unsigned long sp)
{
 return (sp - get_current()->sas_ss_sp < get_current()->sas_ss_size);
}

static inline __attribute__((always_inline)) int sas_ss_flags(unsigned long sp)
{
 return (get_current()->sas_ss_size == 0 ? 2
  : on_sig_stack(sp) ? 1 : 0);
}




extern int capable(int cap);
# 1027 "include/linux/sched.h"
extern struct mm_struct * mm_alloc(void);


extern void __mmdrop(struct mm_struct *) __attribute__((regparm(3)));
static inline __attribute__((always_inline)) void mmdrop(struct mm_struct * mm)
{
 if (atomic_dec_and_test(&mm->mm_count))
  __mmdrop(mm);
}


extern void mmput(struct mm_struct *);

extern struct mm_struct *get_task_mm(struct task_struct *task);

extern void mm_release(struct task_struct *, struct mm_struct *);

extern int copy_thread(int, unsigned long, unsigned long, unsigned long, struct task_struct *, struct pt_regs *);
extern void flush_thread(void);
extern void exit_thread(void);

extern void exit_files(struct task_struct *);
extern void exit_signal(struct task_struct *);
extern void __exit_signal(struct task_struct *);
extern void exit_sighand(struct task_struct *);
extern void __exit_sighand(struct task_struct *);
extern void exit_itimers(struct signal_struct *);

extern void do_group_exit(int);

extern void daemonize(const char *, ...);
extern int allow_signal(int);
extern int disallow_signal(int);
extern task_t *child_reaper;

extern int do_execve(char *, char * *, char * *, struct pt_regs *);
extern long do_fork(unsigned long, unsigned long, struct pt_regs *, unsigned long, int *, int *);
task_t *fork_idle(int);

extern void set_task_comm(struct task_struct *tsk, char *from);
extern void get_task_comm(char *to, struct task_struct *tsk);


extern void wait_task_inactive(task_t * p);
# 1106 "include/linux/sched.h"
extern task_t * next_thread(const task_t *p) __attribute__((regparm(3)));



static inline __attribute__((always_inline)) int thread_group_empty(task_t *p)
{
 return list_empty(&p->pids[PIDTYPE_TGID].pid_list);
}




extern void unhash_process(struct task_struct *p);
# 1129 "include/linux/sched.h"
static inline __attribute__((always_inline)) void task_lock(struct task_struct *p)
{
 _spin_lock(&p->alloc_lock);
}

static inline __attribute__((always_inline)) void task_unlock(struct task_struct *p)
{
 _spin_unlock(&p->alloc_lock);
}




static inline __attribute__((always_inline)) void set_tsk_thread_flag(struct task_struct *tsk, int flag)
{
 set_ti_thread_flag(tsk->thread_info,flag);
}

static inline __attribute__((always_inline)) void clear_tsk_thread_flag(struct task_struct *tsk, int flag)
{
 clear_ti_thread_flag(tsk->thread_info,flag);
}

static inline __attribute__((always_inline)) int test_and_set_tsk_thread_flag(struct task_struct *tsk, int flag)
{
 return test_and_set_ti_thread_flag(tsk->thread_info,flag);
}

static inline __attribute__((always_inline)) int test_and_clear_tsk_thread_flag(struct task_struct *tsk, int flag)
{
 return test_and_clear_ti_thread_flag(tsk->thread_info,flag);
}

static inline __attribute__((always_inline)) int test_tsk_thread_flag(struct task_struct *tsk, int flag)
{
 return test_ti_thread_flag(tsk->thread_info,flag);
}

static inline __attribute__((always_inline)) void set_tsk_need_resched(struct task_struct *tsk)
{
 set_tsk_thread_flag(tsk,3);
}

static inline __attribute__((always_inline)) void clear_tsk_need_resched(struct task_struct *tsk)
{
 clear_tsk_thread_flag(tsk,3);
}

static inline __attribute__((always_inline)) int signal_pending(struct task_struct *p)
{
 return __builtin_expect(!!(test_tsk_thread_flag(p,2)), 0);
}

static inline __attribute__((always_inline)) int need_resched(void)
{
 return __builtin_expect(!!(test_thread_flag(3)), 0);
}
# 1194 "include/linux/sched.h"
extern int cond_resched(void);
extern int cond_resched_lock(spinlock_t * lock);
extern int cond_resched_softirq(void);
# 1212 "include/linux/sched.h"
static inline __attribute__((always_inline)) int lock_need_resched(spinlock_t *lock)
{
 if (0 || need_resched())
  return 1;
 return 0;
}





extern void recalc_sigpending_tsk(struct task_struct *t) __attribute__((regparm(3)));
extern void recalc_sigpending(void);

extern void signal_wake_up(struct task_struct *t, int resume_stopped);






static inline __attribute__((always_inline)) unsigned int task_cpu(const struct task_struct *p)
{
 return p->thread_info->cpu;
}

static inline __attribute__((always_inline)) void set_task_cpu(struct task_struct *p, unsigned int cpu)
{
 p->thread_info->cpu = cpu;
}
# 1257 "include/linux/sched.h"
extern void arch_pick_mmap_layout(struct mm_struct *mm);
# 1267 "include/linux/sched.h"
extern long sched_setaffinity(pid_t pid, cpumask_t new_mask);
extern long sched_getaffinity(pid_t pid, cpumask_t *mask);



extern void normalize_rt_tasks(void);







static inline __attribute__((always_inline)) int frozen(struct task_struct *p)
{
 return p->flags & 0x00010000;
}




static inline __attribute__((always_inline)) int freezing(struct task_struct *p)
{
 return p->flags & 0x00004000;
}





static inline __attribute__((always_inline)) void freeze(struct task_struct *p)
{
 p->flags |= 0x00004000;
}




static inline __attribute__((always_inline)) int thaw_process(struct task_struct *p)
{
 if (frozen(p)) {
  p->flags &= ~0x00010000;
  wake_up_process(p);
  return 1;
 }
 return 0;
}




static inline __attribute__((always_inline)) void frozen_process(struct task_struct *p)
{
 p->flags = (p->flags & ~0x00004000) | 0x00010000;
}

extern void refrigerator(void);
extern int freeze_processes(void);
extern void thaw_processes(void);

static inline __attribute__((always_inline)) int try_to_freeze(void)
{
 if (freezing(get_current())) {
  refrigerator();
  return 1;
 } else
  return 0;
}
# 11 "include/linux/module.h" 2


# 1 "include/linux/stat.h" 1





# 1 "include/asm/stat.h" 1



struct __old_kernel_stat {
 unsigned short st_dev;
 unsigned short st_ino;
 unsigned short st_mode;
 unsigned short st_nlink;
 unsigned short st_uid;
 unsigned short st_gid;
 unsigned short st_rdev;
 unsigned long st_size;
 unsigned long st_atime;
 unsigned long st_mtime;
 unsigned long st_ctime;
};

struct stat {
 unsigned long st_dev;
 unsigned long st_ino;
 unsigned short st_mode;
 unsigned short st_nlink;
 unsigned short st_uid;
 unsigned short st_gid;
 unsigned long st_rdev;
 unsigned long st_size;
 unsigned long st_blksize;
 unsigned long st_blocks;
 unsigned long st_atime;
 unsigned long st_atime_nsec;
 unsigned long st_mtime;
 unsigned long st_mtime_nsec;
 unsigned long st_ctime;
 unsigned long st_ctime_nsec;
 unsigned long __unused4;
 unsigned long __unused5;
};




struct stat64 {
 unsigned long long st_dev;
 unsigned char __pad0[4];


 unsigned long __st_ino;

 unsigned int st_mode;
 unsigned int st_nlink;

 unsigned long st_uid;
 unsigned long st_gid;

 unsigned long long st_rdev;
 unsigned char __pad3[4];

 long long st_size;
 unsigned long st_blksize;

 unsigned long st_blocks;
 unsigned long __pad4;

 unsigned long st_atime;
 unsigned long st_atime_nsec;

 unsigned long st_mtime;
 unsigned int st_mtime_nsec;

 unsigned long st_ctime;
 unsigned long st_ctime_nsec;

 unsigned long long st_ino;
};
# 7 "include/linux/stat.h" 2
# 59 "include/linux/stat.h"
struct kstat {
 unsigned long ino;
 dev_t dev;
 umode_t mode;
 unsigned int nlink;
 uid_t uid;
 gid_t gid;
 dev_t rdev;
 loff_t size;
 struct timespec atime;
 struct timespec mtime;
 struct timespec ctime;
 unsigned long blksize;
 unsigned long blocks;
};
# 14 "include/linux/module.h" 2


# 1 "include/linux/kmod.h" 1
# 32 "include/linux/kmod.h"
extern int request_module(const char * name, ...) __attribute__ ((format (printf, 1, 2)));






struct key;
extern int call_usermodehelper_keys(char *path, char *argv[], char *envp[],
        struct key *session_keyring, int wait);

static inline __attribute__((always_inline)) int
call_usermodehelper(char *path, char **argv, char **envp, int wait)
{
 return call_usermodehelper_keys(path, argv, envp, ((void *)0), wait);
}

extern void usermodehelper_init(void);
# 17 "include/linux/module.h" 2
# 1 "include/linux/elf.h" 1




# 1 "include/asm/elf.h" 1
# 9 "include/asm/elf.h"
# 1 "include/asm/user.h" 1
# 44 "include/asm/user.h"
struct user_i387_struct {
 long cwd;
 long swd;
 long twd;
 long fip;
 long fcs;
 long foo;
 long fos;
 long st_space[20];
};

struct user_fxsr_struct {
 unsigned short cwd;
 unsigned short swd;
 unsigned short twd;
 unsigned short fop;
 long fip;
 long fcs;
 long foo;
 long fos;
 long mxcsr;
 long reserved;
 long st_space[32];
 long xmm_space[32];
 long padding[56];
};







struct user_regs_struct {
 long ebx, ecx, edx, esi, edi, ebp, eax;
 unsigned short ds, __ds, es, __es;
 unsigned short fs, __fs, gs, __gs;
 long orig_eax, eip;
 unsigned short cs, __cs;
 long eflags, esp;
 unsigned short ss, __ss;
};




struct user{


  struct user_regs_struct regs;

  int u_fpvalid;

  struct user_i387_struct i387;

  unsigned long int u_tsize;
  unsigned long int u_dsize;
  unsigned long int u_ssize;
  unsigned long start_code;
  unsigned long start_stack;



  long int signal;
  int reserved;
  struct user_pt_regs * u_ar0;

  struct user_i387_struct* u_fpstate;
  unsigned long magic;
  char u_comm[32];
  int u_debugreg[8];
};
# 10 "include/asm/elf.h" 2



# 1 "include/linux/utsname.h" 1





struct oldold_utsname {
 char sysname[9];
 char nodename[9];
 char release[9];
 char version[9];
 char machine[9];
};



struct old_utsname {
 char sysname[65];
 char nodename[65];
 char release[65];
 char version[65];
 char machine[65];
};

struct new_utsname {
 char sysname[65];
 char nodename[65];
 char release[65];
 char version[65];
 char machine[65];
 char domainname[65];
};

extern struct new_utsname system_utsname;

extern struct rw_semaphore uts_sem;
# 14 "include/asm/elf.h" 2
# 28 "include/asm/elf.h"
typedef unsigned long elf_greg_t;


typedef elf_greg_t elf_gregset_t[(sizeof (struct user_regs_struct) / sizeof(elf_greg_t))];

typedef struct user_i387_struct elf_fpregset_t;
typedef struct user_fxsr_struct elf_fpxregset_t;
# 128 "include/asm/elf.h"
extern int dump_task_regs (struct task_struct *, elf_gregset_t *);
extern int dump_task_fpu (struct task_struct *, elf_fpregset_t *);
extern int dump_task_extended_fpu (struct task_struct *, struct user_fxsr_struct *);
# 139 "include/asm/elf.h"
extern void __kernel_vsyscall;
# 6 "include/linux/elf.h" 2
# 15 "include/linux/elf.h"
typedef __u32 Elf32_Addr;
typedef __u16 Elf32_Half;
typedef __u32 Elf32_Off;
typedef __s32 Elf32_Sword;
typedef __u32 Elf32_Word;


typedef __u64 Elf64_Addr;
typedef __u16 Elf64_Half;
typedef __s16 Elf64_SHalf;
typedef __u64 Elf64_Off;
typedef __s32 Elf64_Sword;
typedef __u32 Elf64_Word;
typedef __u64 Elf64_Xword;
typedef __s64 Elf64_Sxword;
# 184 "include/linux/elf.h"
typedef struct dynamic{
  Elf32_Sword d_tag;
  union{
    Elf32_Sword d_val;
    Elf32_Addr d_ptr;
  } d_un;
} Elf32_Dyn;

typedef struct {
  Elf64_Sxword d_tag;
  union {
    Elf64_Xword d_val;
    Elf64_Addr d_ptr;
  } d_un;
} Elf64_Dyn;
# 207 "include/linux/elf.h"
typedef struct elf32_rel {
  Elf32_Addr r_offset;
  Elf32_Word r_info;
} Elf32_Rel;

typedef struct elf64_rel {
  Elf64_Addr r_offset;
  Elf64_Xword r_info;
} Elf64_Rel;

typedef struct elf32_rela{
  Elf32_Addr r_offset;
  Elf32_Word r_info;
  Elf32_Sword r_addend;
} Elf32_Rela;

typedef struct elf64_rela {
  Elf64_Addr r_offset;
  Elf64_Xword r_info;
  Elf64_Sxword r_addend;
} Elf64_Rela;

typedef struct elf32_sym{
  Elf32_Word st_name;
  Elf32_Addr st_value;
  Elf32_Word st_size;
  unsigned char st_info;
  unsigned char st_other;
  Elf32_Half st_shndx;
} Elf32_Sym;

typedef struct elf64_sym {
  Elf64_Word st_name;
  unsigned char st_info;
  unsigned char st_other;
  Elf64_Half st_shndx;
  Elf64_Addr st_value;
  Elf64_Xword st_size;
} Elf64_Sym;




typedef struct elf32_hdr{
  unsigned char e_ident[16];
  Elf32_Half e_type;
  Elf32_Half e_machine;
  Elf32_Word e_version;
  Elf32_Addr e_entry;
  Elf32_Off e_phoff;
  Elf32_Off e_shoff;
  Elf32_Word e_flags;
  Elf32_Half e_ehsize;
  Elf32_Half e_phentsize;
  Elf32_Half e_phnum;
  Elf32_Half e_shentsize;
  Elf32_Half e_shnum;
  Elf32_Half e_shstrndx;
} Elf32_Ehdr;

typedef struct elf64_hdr {
  unsigned char e_ident[16];
  Elf64_Half e_type;
  Elf64_Half e_machine;
  Elf64_Word e_version;
  Elf64_Addr e_entry;
  Elf64_Off e_phoff;
  Elf64_Off e_shoff;
  Elf64_Word e_flags;
  Elf64_Half e_ehsize;
  Elf64_Half e_phentsize;
  Elf64_Half e_phnum;
  Elf64_Half e_shentsize;
  Elf64_Half e_shnum;
  Elf64_Half e_shstrndx;
} Elf64_Ehdr;







typedef struct elf32_phdr{
  Elf32_Word p_type;
  Elf32_Off p_offset;
  Elf32_Addr p_vaddr;
  Elf32_Addr p_paddr;
  Elf32_Word p_filesz;
  Elf32_Word p_memsz;
  Elf32_Word p_flags;
  Elf32_Word p_align;
} Elf32_Phdr;

typedef struct elf64_phdr {
  Elf64_Word p_type;
  Elf64_Word p_flags;
  Elf64_Off p_offset;
  Elf64_Addr p_vaddr;
  Elf64_Addr p_paddr;
  Elf64_Xword p_filesz;
  Elf64_Xword p_memsz;
  Elf64_Xword p_align;
} Elf64_Phdr;
# 346 "include/linux/elf.h"
typedef struct {
  Elf32_Word sh_name;
  Elf32_Word sh_type;
  Elf32_Word sh_flags;
  Elf32_Addr sh_addr;
  Elf32_Off sh_offset;
  Elf32_Word sh_size;
  Elf32_Word sh_link;
  Elf32_Word sh_info;
  Elf32_Word sh_addralign;
  Elf32_Word sh_entsize;
} Elf32_Shdr;

typedef struct elf64_shdr {
  Elf64_Word sh_name;
  Elf64_Word sh_type;
  Elf64_Xword sh_flags;
  Elf64_Addr sh_addr;
  Elf64_Off sh_offset;
  Elf64_Xword sh_size;
  Elf64_Word sh_link;
  Elf64_Word sh_info;
  Elf64_Xword sh_addralign;
  Elf64_Xword sh_entsize;
} Elf64_Shdr;
# 419 "include/linux/elf.h"
typedef struct elf32_note {
  Elf32_Word n_namesz;
  Elf32_Word n_descsz;
  Elf32_Word n_type;
} Elf32_Nhdr;


typedef struct elf64_note {
  Elf64_Word n_namesz;
  Elf64_Word n_descsz;
  Elf64_Word n_type;
} Elf64_Nhdr;



extern Elf32_Dyn _DYNAMIC [];
# 18 "include/linux/module.h" 2

# 1 "include/linux/kobject.h" 1
# 22 "include/linux/kobject.h"
# 1 "include/linux/sysfs.h" 1
# 15 "include/linux/sysfs.h"
struct kobject;
struct module;

struct attribute {
 const char * name;
 struct module * owner;
 mode_t mode;
};

struct attribute_group {
 const char * name;
 struct attribute ** attrs;
};
# 51 "include/linux/sysfs.h"
struct vm_area_struct;

struct bin_attribute {
 struct attribute attr;
 size_t size;
 void *private;
 ssize_t (*read)(struct kobject *, char *, loff_t, size_t);
 ssize_t (*write)(struct kobject *, char *, loff_t, size_t);
 int (*mmap)(struct kobject *, struct bin_attribute *attr,
      struct vm_area_struct *vma);
};

struct sysfs_ops {
 ssize_t (*show)(struct kobject *, struct attribute *,char *);
 ssize_t (*store)(struct kobject *,struct attribute *,const char *, size_t);
};

struct sysfs_dirent {
 atomic_t s_count;
 struct list_head s_sibling;
 struct list_head s_children;
 void * s_element;
 int s_type;
 umode_t s_mode;
 struct dentry * s_dentry;
 struct iattr * s_iattr;
};
# 88 "include/linux/sysfs.h"
extern int
sysfs_create_dir(struct kobject *);

extern void
sysfs_remove_dir(struct kobject *);

extern int
sysfs_rename_dir(struct kobject *, const char *new_name);

extern int
sysfs_create_file(struct kobject *, const struct attribute *);

extern int
sysfs_update_file(struct kobject *, const struct attribute *);

extern int
sysfs_chmod_file(struct kobject *kobj, struct attribute *attr, mode_t mode);

extern void
sysfs_remove_file(struct kobject *, const struct attribute *);

extern int
sysfs_create_link(struct kobject * kobj, struct kobject * target, const char * name);

extern void
sysfs_remove_link(struct kobject *, const char * name);

int sysfs_create_bin_file(struct kobject * kobj, struct bin_attribute * attr);
int sysfs_remove_bin_file(struct kobject * kobj, struct bin_attribute * attr);

int sysfs_create_group(struct kobject *, const struct attribute_group *);
void sysfs_remove_group(struct kobject *, const struct attribute_group *);
# 23 "include/linux/kobject.h" 2


# 1 "include/linux/kref.h" 1
# 23 "include/linux/kref.h"
struct kref {
 atomic_t refcount;
};

void kref_init(struct kref *kref);
void kref_get(struct kref *kref);
int kref_put(struct kref *kref, void (*release) (struct kref *kref));
# 26 "include/linux/kobject.h" 2
# 1 "include/linux/kobject_uevent.h" 1
# 17 "include/linux/kobject_uevent.h"
extern char hotplug_path[];





typedef int kobject_action_t;
enum kobject_action {
 KOBJ_ADD = ( kobject_action_t) 0x01,
 KOBJ_REMOVE = ( kobject_action_t) 0x02,
 KOBJ_CHANGE = ( kobject_action_t) 0x03,
 KOBJ_MOUNT = ( kobject_action_t) 0x04,
 KOBJ_UMOUNT = ( kobject_action_t) 0x05,
 KOBJ_OFFLINE = ( kobject_action_t) 0x06,
 KOBJ_ONLINE = ( kobject_action_t) 0x07,
};



int kobject_uevent(struct kobject *kobj,
     enum kobject_action action,
     struct attribute *attr);
int kobject_uevent_atomic(struct kobject *kobj,
     enum kobject_action action,
     struct attribute *attr);
# 27 "include/linux/kobject.h" 2






extern u64 hotplug_seqnum;

struct kobject {
 const char * k_name;
 char name[20];
 struct kref kref;
 struct list_head entry;
 struct kobject * parent;
 struct kset * kset;
 struct kobj_type * ktype;
 struct dentry * dentry;
};

extern int kobject_set_name(struct kobject *, const char *, ...)
 __attribute__((format(printf,2,3)));

static inline __attribute__((always_inline)) const char * kobject_name(const struct kobject * kobj)
{
 return kobj->k_name;
}

extern void kobject_init(struct kobject *);
extern void kobject_cleanup(struct kobject *);

extern int kobject_add(struct kobject *);
extern void kobject_del(struct kobject *);

extern int kobject_rename(struct kobject *, const char *new_name);

extern int kobject_register(struct kobject *);
extern void kobject_unregister(struct kobject *);

extern struct kobject * kobject_get(struct kobject *);
extern void kobject_put(struct kobject *);

extern char * kobject_get_path(struct kobject *, int);

struct kobj_type {
 void (*release)(struct kobject *);
 struct sysfs_ops * sysfs_ops;
 struct attribute ** default_attrs;
};
# 95 "include/linux/kobject.h"
struct kset_hotplug_ops {
 int (*filter)(struct kset *kset, struct kobject *kobj);
 const char *(*name)(struct kset *kset, struct kobject *kobj);
 int (*hotplug)(struct kset *kset, struct kobject *kobj, char **envp,
   int num_envp, char *buffer, int buffer_size);
};

struct kset {
 struct subsystem * subsys;
 struct kobj_type * ktype;
 struct list_head list;
 spinlock_t list_lock;
 struct kobject kobj;
 struct kset_hotplug_ops * hotplug_ops;
};


extern void kset_init(struct kset * k);
extern int kset_add(struct kset * k);
extern int kset_register(struct kset * k);
extern void kset_unregister(struct kset * k);

static inline __attribute__((always_inline)) struct kset * to_kset(struct kobject * kobj)
{
 return kobj ? ({ const typeof( ((struct kset *)0)->kobj ) *__mptr = (kobj); (struct kset *)( (char *)__mptr - __builtin_offsetof(struct kset,kobj) );}) : ((void *)0);
}

static inline __attribute__((always_inline)) struct kset * kset_get(struct kset * k)
{
 return k ? to_kset(kobject_get(&k->kobj)) : ((void *)0);
}

static inline __attribute__((always_inline)) void kset_put(struct kset * k)
{
 kobject_put(&k->kobj);
}

static inline __attribute__((always_inline)) struct kobj_type * get_ktype(struct kobject * k)
{
 if (k->kset && k->kset->ktype)
  return k->kset->ktype;
 else
  return k->ktype;
}

extern struct kobject * kset_find_obj(struct kset *, const char *);
# 151 "include/linux/kobject.h"
struct subsystem {
 struct kset kset;
 struct rw_semaphore rwsem;
};
# 174 "include/linux/kobject.h"
extern struct subsystem kernel_subsys;
# 221 "include/linux/kobject.h"
extern void subsystem_init(struct subsystem *);
extern int subsystem_register(struct subsystem *);
extern void subsystem_unregister(struct subsystem *);

static inline __attribute__((always_inline)) struct subsystem * subsys_get(struct subsystem * s)
{
 return s ? ({ const typeof( ((struct subsystem *)0)->kset ) *__mptr = (kset_get(&s->kset)); (struct subsystem *)( (char *)__mptr - __builtin_offsetof(struct subsystem,kset) );}) : ((void *)0);
}

static inline __attribute__((always_inline)) void subsys_put(struct subsystem * s)
{
 kset_put(&s->kset);
}

struct subsys_attribute {
 struct attribute attr;
 ssize_t (*show)(struct subsystem *, char *);
 ssize_t (*store)(struct subsystem *, const char *, size_t);
};

extern int subsys_create_file(struct subsystem * , struct subsys_attribute *);
extern void subsys_remove_file(struct subsystem * , struct subsys_attribute *);


void kobject_hotplug(struct kobject *kobj, enum kobject_action action);
int add_hotplug_env_var(char **envp, int num_envp, int *cur_index,
   char *buffer, int buffer_size, int *cur_len,
   const char *format, ...)
 __attribute__((format (printf, 7, 8)));
# 20 "include/linux/module.h" 2
# 1 "include/linux/moduleparam.h" 1
# 29 "include/linux/moduleparam.h"
struct kernel_param;


typedef int (*param_set_fn)(const char *val, struct kernel_param *kp);

typedef int (*param_get_fn)(char *buffer, struct kernel_param *kp);

struct kernel_param {
 const char *name;
 unsigned int perm;
 param_set_fn set;
 param_get_fn get;
 void *arg;
};


struct kparam_string {
 unsigned int maxlen;
 char *string;
};


struct kparam_array
{
 unsigned int max;
 unsigned int *num;
 param_set_fn set;
 param_get_fn get;
 unsigned int elemsize;
 void *elem;
};
# 95 "include/linux/moduleparam.h"
extern int parse_args(const char *name,
        char *args,
        struct kernel_param *params,
        unsigned num,
        int (*unknown)(char *param, char *val));







extern int param_set_byte(const char *val, struct kernel_param *kp);
extern int param_get_byte(char *buffer, struct kernel_param *kp);


extern int param_set_short(const char *val, struct kernel_param *kp);
extern int param_get_short(char *buffer, struct kernel_param *kp);


extern int param_set_ushort(const char *val, struct kernel_param *kp);
extern int param_get_ushort(char *buffer, struct kernel_param *kp);


extern int param_set_int(const char *val, struct kernel_param *kp);
extern int param_get_int(char *buffer, struct kernel_param *kp);


extern int param_set_uint(const char *val, struct kernel_param *kp);
extern int param_get_uint(char *buffer, struct kernel_param *kp);


extern int param_set_long(const char *val, struct kernel_param *kp);
extern int param_get_long(char *buffer, struct kernel_param *kp);


extern int param_set_ulong(const char *val, struct kernel_param *kp);
extern int param_get_ulong(char *buffer, struct kernel_param *kp);


extern int param_set_charp(const char *val, struct kernel_param *kp);
extern int param_get_charp(char *buffer, struct kernel_param *kp);


extern int param_set_bool(const char *val, struct kernel_param *kp);
extern int param_get_bool(char *buffer, struct kernel_param *kp);


extern int param_set_invbool(const char *val, struct kernel_param *kp);
extern int param_get_invbool(char *buffer, struct kernel_param *kp);
# 159 "include/linux/moduleparam.h"
extern int param_array_set(const char *val, struct kernel_param *kp);
extern int param_array_get(char *buffer, struct kernel_param *kp);

extern int param_set_copystring(const char *val, struct kernel_param *kp);
extern int param_get_string(char *buffer, struct kernel_param *kp);

int param_array(const char *name,
  const char *val,
  unsigned int min, unsigned int max,
  void *elem, int elemsize,
  int (*set)(const char *, struct kernel_param *kp),
  int *num);



struct module;

extern int module_param_sysfs_setup(struct module *mod,
        struct kernel_param *kparam,
        unsigned int num_params);

extern void module_param_sysfs_remove(struct module *mod);
# 21 "include/linux/module.h" 2
# 1 "include/asm/local.h" 1





typedef struct
{
 volatile unsigned long counter;
} local_t;






static __inline__ __attribute__((always_inline)) void local_inc(local_t *v)
{
 __asm__ __volatile__(
  "incl %0"
  :"=m" (v->counter)
  :"m" (v->counter));
}

static __inline__ __attribute__((always_inline)) void local_dec(local_t *v)
{
 __asm__ __volatile__(
  "decl %0"
  :"=m" (v->counter)
  :"m" (v->counter));
}

static __inline__ __attribute__((always_inline)) void local_add(unsigned long i, local_t *v)
{
 __asm__ __volatile__(
  "addl %1,%0"
  :"=m" (v->counter)
  :"ir" (i), "m" (v->counter));
}

static __inline__ __attribute__((always_inline)) void local_sub(unsigned long i, local_t *v)
{
 __asm__ __volatile__(
  "subl %1,%0"
  :"=m" (v->counter)
  :"ir" (i), "m" (v->counter));
}
# 22 "include/linux/module.h" 2

# 1 "include/asm/module.h" 1




struct mod_arch_specific
{
};
# 24 "include/linux/module.h" 2
# 35 "include/linux/module.h"
struct kernel_symbol
{
 unsigned long value;
 const char *name;
};

struct modversion_info
{
 unsigned long crc;
 char name[(64 - sizeof(unsigned long))];
};

struct module;

struct module_attribute {
        struct attribute attr;
        ssize_t (*show)(struct module_attribute *, struct module *, char *);
        ssize_t (*store)(struct module_attribute *, struct module *,
    const char *, size_t count);
 void (*setup)(struct module *, const char *);
 int (*test)(struct module *);
 void (*free)(struct module *);
};

struct module_kobject
{
 struct kobject kobj;
 struct module *mod;
};


extern int init_module(void);
extern void cleanup_module(void);


struct exception_table_entry;

const struct exception_table_entry *
search_extable(const struct exception_table_entry *first,
        const struct exception_table_entry *last,
        unsigned long value);
void sort_extable(struct exception_table_entry *start,
    struct exception_table_entry *finish);
void sort_main_extable(void);

extern struct subsystem module_subsys;
# 159 "include/linux/module.h"
const struct exception_table_entry *search_exception_tables(unsigned long add);

struct notifier_block;




void *__symbol_get(const char *symbol);
void *__symbol_get_gpl(const char *symbol);
# 203 "include/linux/module.h"
struct module_ref
{
 local_t count;
} __attribute__((__aligned__((1 << (7)))));

enum module_state
{
 MODULE_STATE_LIVE,
 MODULE_STATE_COMING,
 MODULE_STATE_GOING,
};



struct module_sect_attr
{
 struct module_attribute mattr;
 char name[32];
 unsigned long address;
};

struct module_sect_attrs
{
 struct attribute_group grp;
 struct module_sect_attr attrs[0];
};

struct module_param_attrs;

struct module
{
 enum module_state state;


 struct list_head list;


 char name[(64 - sizeof(unsigned long))];


 struct module_kobject mkobj;
 struct module_param_attrs *param_attrs;
 const char *version;
 const char *srcversion;


 const struct kernel_symbol *syms;
 unsigned int num_syms;
 const unsigned long *crcs;


 const struct kernel_symbol *gpl_syms;
 unsigned int num_gpl_syms;
 const unsigned long *gpl_crcs;


 unsigned int num_exentries;
 const struct exception_table_entry *extable;


 int (*init)(void);


 void *module_init;


 void *module_core;


 unsigned long init_size, core_size;


 unsigned long init_text_size, core_text_size;


 struct mod_arch_specific arch;


 int unsafe;


 int license_gplok;



 struct module_ref ref[8];


 struct list_head modules_which_use_me;


 struct task_struct *waiter;


 void (*exit)(void);




 Elf32_Sym *symtab;
 unsigned long num_symtab;
 char *strtab;


 struct module_sect_attrs *sect_attrs;



 void *percpu;



 char *args;
};




static inline __attribute__((always_inline)) int module_is_live(struct module *mod)
{
 return mod->state != MODULE_STATE_GOING;
}


struct module *module_text_address(unsigned long addr);
struct module *__module_text_address(unsigned long addr);



struct module *module_get_kallsym(unsigned int symnum,
      unsigned long *value,
      char *type,
      char namebuf[128]);


unsigned long module_kallsyms_lookup_name(const char *name);

int is_exported(const char *name, const struct module *mod);

extern void __module_put_and_exit(struct module *mod, long code)
 __attribute__((noreturn));



unsigned int module_refcount(struct module *mod);
void __symbol_put(const char *symbol);

void symbol_put_addr(void *addr);



static inline __attribute__((always_inline)) void __module_get(struct module *module)
{
 if (module) {
  do { if (__builtin_expect(!!((module_refcount(module) == 0)!=0), 0)) __BUG(); } while(0);
  local_inc(&module->ref[({ do { } while (0); (current_thread_info()->cpu); })].count);
  do { } while (0);
 }
}

static inline __attribute__((always_inline)) int try_module_get(struct module *module)
{
 int ret = 1;

 if (module) {
  unsigned int cpu = ({ do { } while (0); (current_thread_info()->cpu); });
  if (__builtin_expect(!!(module_is_live(module)), 1))
   local_inc(&module->ref[cpu].count);
  else
   ret = 0;
  do { } while (0);
 }
 return ret;
}

static inline __attribute__((always_inline)) void module_put(struct module *module)
{
 if (module) {
  unsigned int cpu = ({ do { } while (0); (current_thread_info()->cpu); });
  local_dec(&module->ref[cpu].count);

  if (__builtin_expect(!!(!module_is_live(module)), 0))
   wake_up_process(module->waiter);
  do { } while (0);
 }
}
# 424 "include/linux/module.h"
const char *module_address_lookup(unsigned long addr,
      unsigned long *symbolsize,
      unsigned long *offset,
      char **modname);


const struct exception_table_entry *search_module_extables(unsigned long addr);

int register_module_notifier(struct notifier_block * nb);
int unregister_module_notifier(struct notifier_block * nb);

extern void print_modules(void);

struct device_driver;
void module_add_driver(struct module *, struct device_driver *);
void module_remove_driver(struct device_driver *);
# 547 "include/linux/module.h"
struct obsolete_modparm {
 char name[64];
 char type[64-sizeof(void *)];
 void *addr;
};

static inline __attribute__((always_inline)) void MODULE_PARM_(void) { }
# 568 "include/linux/module.h"
extern void __attribute__((deprecated)) inter_module_register(const char *,
  struct module *, const void *);
extern void __attribute__((deprecated)) inter_module_unregister(const char *);
extern const void * __attribute__((deprecated)) inter_module_get_request(const char *,
  const char *);
extern void __attribute__((deprecated)) inter_module_put(const char *);
# 29 "net/ipv6/tcp_ipv6.c" 2



# 1 "include/linux/socket.h" 1
# 11 "include/linux/socket.h"
struct __kernel_sockaddr_storage {
 unsigned short ss_family;

 char __data[128 - sizeof(unsigned short)];


} __attribute__ ((aligned((__alignof__ (struct sockaddr *)))));





# 1 "include/asm/socket.h" 1



# 1 "include/asm/sockios.h" 1
# 5 "include/asm/socket.h" 2
# 24 "include/linux/socket.h" 2
# 1 "include/linux/sockios.h" 1
# 25 "include/linux/socket.h" 2
# 1 "include/linux/uio.h" 1
# 20 "include/linux/uio.h"
struct iovec
{
 void *iov_base;
 __kernel_size_t iov_len;
};



struct kvec {
 void *iov_base;
 size_t iov_len;
};
# 54 "include/linux/uio.h"
static inline __attribute__((always_inline)) size_t iov_length(const struct iovec *iov, unsigned long nr_segs)
{
 unsigned long seg;
 size_t ret = 0;

 for (seg = 0; seg < nr_segs; seg++)
  ret += iov[seg].iov_len;
 return ret;
}

unsigned long iov_shorten(struct iovec *iov, unsigned long nr_segs, size_t to);
# 26 "include/linux/socket.h" 2



typedef unsigned short sa_family_t;





struct sockaddr {
 sa_family_t sa_family;
 char sa_data[14];
};

struct linger {
 int l_onoff;
 int l_linger;
};
# 53 "include/linux/socket.h"
struct msghdr {
 void * msg_name;
 int msg_namelen;
 struct iovec * msg_iov;
 __kernel_size_t msg_iovlen;
 void * msg_control;
 __kernel_size_t msg_controllen;
 unsigned msg_flags;
};







struct cmsghdr {
 __kernel_size_t cmsg_len;
        int cmsg_level;
        int cmsg_type;
};
# 126 "include/linux/socket.h"
static inline __attribute__((always_inline)) struct cmsghdr * __cmsg_nxthdr(void *__ctl, __kernel_size_t __size,
            struct cmsghdr *__cmsg)
{
 struct cmsghdr * __ptr;

 __ptr = (struct cmsghdr*)(((unsigned char *) __cmsg) + ( ((__cmsg->cmsg_len)+sizeof(long)-1) & ~(sizeof(long)-1) ));
 if ((unsigned long)((char*)(__ptr+1) - (char *) __ctl) > __size)
  return (struct cmsghdr *)0;

 return __ptr;
}

static inline __attribute__((always_inline)) struct cmsghdr * cmsg_nxthdr (struct msghdr *__msg, struct cmsghdr *__cmsg)
{
 return __cmsg_nxthdr(__msg->msg_control, __msg->msg_controllen, __cmsg);
}






struct ucred {
 __u32 pid;
 __u32 uid;
 __u32 gid;
};
# 279 "include/linux/socket.h"
extern int memcpy_fromiovec(unsigned char *kdata, struct iovec *iov, int len);
extern int memcpy_fromiovecend(unsigned char *kdata, struct iovec *iov,
    int offset, int len);
extern int csum_partial_copy_fromiovecend(unsigned char *kdata,
       struct iovec *iov,
       int offset,
       unsigned int len, int *csump);

extern int verify_iovec(struct msghdr *m, struct iovec *iov, char *address, int mode);
extern int memcpy_toiovec(struct iovec *v, unsigned char *kdata, int len);
extern int move_addr_to_user(void *kaddr, int klen, void *uaddr, int *ulen);
extern int move_addr_to_kernel(void *uaddr, int ulen, void *kaddr);
extern int put_cmsg(struct msghdr*, int level, int type, int len, void *data);
# 33 "net/ipv6/tcp_ipv6.c" 2

# 1 "include/linux/net.h" 1
# 26 "include/linux/net.h"
struct poll_table_struct;
struct inode;
# 49 "include/linux/net.h"
typedef enum {
 SS_FREE = 0,
 SS_UNCONNECTED,
 SS_CONNECTING,
 SS_CONNECTED,
 SS_DISCONNECTING
} socket_state;
# 81 "include/linux/net.h"
enum sock_type {
 SOCK_STREAM = 1,
 SOCK_DGRAM = 2,
 SOCK_RAW = 3,
 SOCK_RDM = 4,
 SOCK_SEQPACKET = 5,
 SOCK_PACKET = 10,
};
# 105 "include/linux/net.h"
struct socket {
 socket_state state;
 unsigned long flags;
 struct proto_ops *ops;
 struct fasync_struct *fasync_list;
 struct file *file;
 struct sock *sk;
 wait_queue_head_t wait;
 short type;
};

struct vm_area_struct;
struct page;
struct kiocb;
struct sockaddr;
struct msghdr;
struct module;

struct proto_ops {
 int family;
 struct module *owner;
 int (*release) (struct socket *sock);
 int (*bind) (struct socket *sock,
          struct sockaddr *myaddr,
          int sockaddr_len);
 int (*connect) (struct socket *sock,
          struct sockaddr *vaddr,
          int sockaddr_len, int flags);
 int (*socketpair)(struct socket *sock1,
          struct socket *sock2);
 int (*accept) (struct socket *sock,
          struct socket *newsock, int flags);
 int (*getname) (struct socket *sock,
          struct sockaddr *addr,
          int *sockaddr_len, int peer);
 unsigned int (*poll) (struct file *file, struct socket *sock,
          struct poll_table_struct *wait);
 int (*ioctl) (struct socket *sock, unsigned int cmd,
          unsigned long arg);
 int (*listen) (struct socket *sock, int len);
 int (*shutdown) (struct socket *sock, int flags);
 int (*setsockopt)(struct socket *sock, int level,
          int optname, char *optval, int optlen);
 int (*getsockopt)(struct socket *sock, int level,
          int optname, char *optval, int *optlen);
 int (*sendmsg) (struct kiocb *iocb, struct socket *sock,
          struct msghdr *m, size_t total_len);
 int (*recvmsg) (struct kiocb *iocb, struct socket *sock,
          struct msghdr *m, size_t total_len,
          int flags);
 int (*mmap) (struct file *file, struct socket *sock,
          struct vm_area_struct * vma);
 ssize_t (*sendpage) (struct socket *sock, struct page *page,
          int offset, size_t size, int flags);
};

struct net_proto_family {
 int family;
 int (*create)(struct socket *sock, int protocol);


 short authentication;
 short encryption;
 short encrypt_net;
 struct module *owner;
};

struct iovec;
struct kvec;

extern int sock_wake_async(struct socket *sk, int how, int band);
extern int sock_register(struct net_proto_family *fam);
extern int sock_unregister(int family);
extern int sock_create(int family, int type, int proto,
     struct socket **res);
extern int sock_create_kern(int family, int type, int proto,
          struct socket **res);
extern int sock_create_lite(int family, int type, int proto,
          struct socket **res);
extern void sock_release(struct socket *sock);
extern int sock_sendmsg(struct socket *sock, struct msghdr *msg,
      size_t len);
extern int sock_recvmsg(struct socket *sock, struct msghdr *msg,
      size_t size, int flags);
extern int sock_map_fd(struct socket *sock);
extern struct socket *sockfd_lookup(int fd, int *err);

extern int net_ratelimit(void);
extern unsigned long net_random(void);
extern void net_srandom(unsigned long);
extern void net_random_init(void);

extern int kernel_sendmsg(struct socket *sock, struct msghdr *msg,
        struct kvec *vec, size_t num, size_t len);
extern int kernel_recvmsg(struct socket *sock, struct msghdr *msg,
        struct kvec *vec, size_t num,
        size_t len, int flags);
# 35 "net/ipv6/tcp_ipv6.c" 2

# 1 "include/linux/in.h" 1
# 25 "include/linux/in.h"
enum {
  IPPROTO_IP = 0,
  IPPROTO_ICMP = 1,
  IPPROTO_IGMP = 2,
  IPPROTO_IPIP = 4,
  IPPROTO_TCP = 6,
  IPPROTO_EGP = 8,
  IPPROTO_PUP = 12,
  IPPROTO_UDP = 17,
  IPPROTO_IDP = 22,
  IPPROTO_RSVP = 46,
  IPPROTO_GRE = 47,

  IPPROTO_IPV6 = 41,

  IPPROTO_ESP = 50,
  IPPROTO_AH = 51,
  IPPROTO_PIM = 103,

  IPPROTO_COMP = 108,
  IPPROTO_SCTP = 132,

  IPPROTO_RAW = 255,
  IPPROTO_MAX
};



struct in_addr {
 __u32 s_addr;
};
# 110 "include/linux/in.h"
struct ip_mreq
{
 struct in_addr imr_multiaddr;
 struct in_addr imr_interface;
};

struct ip_mreqn
{
 struct in_addr imr_multiaddr;
 struct in_addr imr_address;
 int imr_ifindex;
};

struct ip_mreq_source {
 __u32 imr_multiaddr;
 __u32 imr_interface;
 __u32 imr_sourceaddr;
};

struct ip_msfilter {
 __u32 imsf_multiaddr;
 __u32 imsf_interface;
 __u32 imsf_fmode;
 __u32 imsf_numsrc;
 __u32 imsf_slist[1];
};





struct group_req
{
 __u32 gr_interface;
 struct __kernel_sockaddr_storage gr_group;
};

struct group_source_req
{
 __u32 gsr_interface;
 struct __kernel_sockaddr_storage gsr_group;
 struct __kernel_sockaddr_storage gsr_source;
};

struct group_filter
{
 __u32 gf_interface;
 struct __kernel_sockaddr_storage gf_group;
 __u32 gf_fmode;
 __u32 gf_numsrc;
 struct __kernel_sockaddr_storage gf_slist[1];
};





struct in_pktinfo
{
 int ipi_ifindex;
 struct in_addr ipi_spec_dst;
 struct in_addr ipi_addr;
};



struct sockaddr_in {
  sa_family_t sin_family;
  unsigned short int sin_port;
  struct in_addr sin_addr;


  unsigned char __pad[16 - sizeof(short int) -
   sizeof(unsigned short int) - sizeof(struct in_addr)];
};
# 37 "net/ipv6/tcp_ipv6.c" 2
# 1 "include/linux/in6.h" 1
# 30 "include/linux/in6.h"
struct in6_addr
{
 union
 {
  __u8 u6_addr8[16];
  __u16 u6_addr16[8];
  __u32 u6_addr32[4];
 } in6_u;



};
# 51 "include/linux/in6.h"
extern const struct in6_addr in6addr_loopback;


struct sockaddr_in6 {
 unsigned short int sin6_family;
 __u16 sin6_port;
 __u32 sin6_flowinfo;
 struct in6_addr sin6_addr;
 __u32 sin6_scope_id;
};

struct ipv6_mreq {

 struct in6_addr ipv6mr_multiaddr;


 int ipv6mr_ifindex;
};



struct in6_flowlabel_req
{
 struct in6_addr flr_dst;
 __u32 flr_label;
 __u8 flr_action;
 __u8 flr_share;
 __u16 flr_flags;
 __u16 flr_expires;
 __u16 flr_linger;
 __u32 __flr_pad;

};
# 38 "net/ipv6/tcp_ipv6.c" 2
# 1 "include/linux/netdevice.h" 1
# 28 "include/linux/netdevice.h"
# 1 "include/linux/if.h" 1
# 27 "include/linux/if.h"
# 1 "include/linux/hdlc/ioctl.h" 1



typedef struct {
 unsigned int clock_rate;
 unsigned int clock_type;
 unsigned short loopback;
} sync_serial_settings;

typedef struct {
 unsigned int clock_rate;
 unsigned int clock_type;
 unsigned short loopback;
 unsigned int slot_map;
} te1_settings;

typedef struct {
 unsigned short encoding;
 unsigned short parity;
} raw_hdlc_proto;

typedef struct {
 unsigned int t391;
 unsigned int t392;
 unsigned int n391;
 unsigned int n392;
 unsigned int n393;
 unsigned short lmi;
 unsigned short dce;
} fr_proto;

typedef struct {
 unsigned int dlci;
} fr_proto_pvc;

typedef struct {
 unsigned int dlci;
 char master[16];
}fr_proto_pvc_info;

typedef struct {
    unsigned int interval;
    unsigned int timeout;
} cisco_proto;
# 28 "include/linux/if.h" 2
# 94 "include/linux/if.h"
struct ifmap
{
 unsigned long mem_start;
 unsigned long mem_end;
 unsigned short base_addr;
 unsigned char irq;
 unsigned char dma;
 unsigned char port;

};

struct if_settings
{
 unsigned int type;
 unsigned int size;
 union {

  raw_hdlc_proto *raw_hdlc;
  cisco_proto *cisco;
  fr_proto *fr;
  fr_proto_pvc *fr_pvc;
  fr_proto_pvc_info *fr_pvc_info;


  sync_serial_settings *sync;
  te1_settings *te1;
 } ifs_ifsu;
};
# 130 "include/linux/if.h"
struct ifreq
{

 union
 {
  char ifrn_name[16];
 } ifr_ifrn;

 union {
  struct sockaddr ifru_addr;
  struct sockaddr ifru_dstaddr;
  struct sockaddr ifru_broadaddr;
  struct sockaddr ifru_netmask;
  struct sockaddr ifru_hwaddr;
  short ifru_flags;
  int ifru_ivalue;
  int ifru_mtu;
  struct ifmap ifru_map;
  char ifru_slave[16];
  char ifru_newname[16];
  void * ifru_data;
  struct if_settings ifru_settings;
 } ifr_ifru;
};
# 180 "include/linux/if.h"
struct ifconf
{
 int ifc_len;
 union
 {
  char *ifcu_buf;
  struct ifreq *ifcu_req;
 } ifc_ifcu;
};
# 29 "include/linux/netdevice.h" 2
# 1 "include/linux/if_ether.h" 1
# 100 "include/linux/if_ether.h"
struct ethhdr {
 unsigned char h_dest[6];
 unsigned char h_source[6];
 unsigned short h_proto;
} __attribute__((packed));


# 1 "include/linux/skbuff.h" 1
# 26 "include/linux/skbuff.h"
# 1 "include/linux/mm.h" 1
# 14 "include/linux/mm.h"
# 1 "include/linux/prio_tree.h" 1
# 14 "include/linux/prio_tree.h"
struct raw_prio_tree_node {
 struct prio_tree_node *left;
 struct prio_tree_node *right;
 struct prio_tree_node *parent;
};

struct prio_tree_node {
 struct prio_tree_node *left;
 struct prio_tree_node *right;
 struct prio_tree_node *parent;
 unsigned long start;
 unsigned long last;
};

struct prio_tree_root {
 struct prio_tree_node *prio_tree_node;
 unsigned short index_bits;
 unsigned short raw;




};

struct prio_tree_iter {
 struct prio_tree_node *cur;
 unsigned long mask;
 unsigned long value;
 int size_level;

 struct prio_tree_root *root;
 unsigned long r_index;
 unsigned long h_index;
};

static inline __attribute__((always_inline)) void prio_tree_iter_init(struct prio_tree_iter *iter,
  struct prio_tree_root *root, unsigned long r_index, unsigned long h_index)
{
 iter->root = root;
 iter->r_index = r_index;
 iter->h_index = h_index;
 iter->cur = ((void *)0);
}
# 84 "include/linux/prio_tree.h"
static inline __attribute__((always_inline)) int prio_tree_empty(const struct prio_tree_root *root)
{
 return root->prio_tree_node == ((void *)0);
}

static inline __attribute__((always_inline)) int prio_tree_root(const struct prio_tree_node *node)
{
 return node->parent == node;
}

static inline __attribute__((always_inline)) int prio_tree_left_empty(const struct prio_tree_node *node)
{
 return node->left == node;
}

static inline __attribute__((always_inline)) int prio_tree_right_empty(const struct prio_tree_node *node)
{
 return node->right == node;
}


struct prio_tree_node *prio_tree_replace(struct prio_tree_root *root,
                struct prio_tree_node *old, struct prio_tree_node *node);
struct prio_tree_node *prio_tree_insert(struct prio_tree_root *root,
                struct prio_tree_node *node);
void prio_tree_remove(struct prio_tree_root *root, struct prio_tree_node *node);
struct prio_tree_node *prio_tree_next(struct prio_tree_iter *iter);
# 15 "include/linux/mm.h" 2
# 1 "include/linux/fs.h" 1
# 10 "include/linux/fs.h"
# 1 "include/linux/limits.h" 1
# 11 "include/linux/fs.h" 2
# 1 "include/linux/ioctl.h" 1



# 1 "include/asm/ioctl.h" 1
# 56 "include/asm/ioctl.h"
extern unsigned int __invalid_size_argument_for_IOC;
# 5 "include/linux/ioctl.h" 2
# 12 "include/linux/fs.h" 2
# 32 "include/linux/fs.h"
struct files_stat_struct {
 int nr_files;
 int nr_free_files;
 int max_files;
};
extern struct files_stat_struct files_stat;

struct inodes_stat_t {
 int nr_inodes;
 int nr_unused;
 int dummy[5];
};
extern struct inodes_stat_t inodes_stat;

extern int leases_enable, lease_break_time;


extern int dir_notify_enable;
# 207 "include/linux/fs.h"
# 1 "include/linux/kdev_t.h" 1
# 21 "include/linux/kdev_t.h"
static inline __attribute__((always_inline)) int old_valid_dev(dev_t dev)
{
 return ((unsigned int) ((dev) >> 20)) < 256 && ((unsigned int) ((dev) & ((1U << 20) - 1))) < 256;
}

static inline __attribute__((always_inline)) u16 old_encode_dev(dev_t dev)
{
 return (((unsigned int) ((dev) >> 20)) << 8) | ((unsigned int) ((dev) & ((1U << 20) - 1)));
}

static inline __attribute__((always_inline)) dev_t old_decode_dev(u16 val)
{
 return ((((val >> 8) & 255) << 20) | (val & 255));
}

static inline __attribute__((always_inline)) int new_valid_dev(dev_t dev)
{
 return 1;
}

static inline __attribute__((always_inline)) u32 new_encode_dev(dev_t dev)
{
 unsigned major = ((unsigned int) ((dev) >> 20));
 unsigned minor = ((unsigned int) ((dev) & ((1U << 20) - 1)));
 return (minor & 0xff) | (major << 8) | ((minor & ~0xff) << 12);
}

static inline __attribute__((always_inline)) dev_t new_decode_dev(u32 dev)
{
 unsigned major = (dev & 0xfff00) >> 8;
 unsigned minor = (dev & 0xff) | ((dev >> 12) & 0xfff00);
 return (((major) << 20) | (minor));
}

static inline __attribute__((always_inline)) int huge_valid_dev(dev_t dev)
{
 return 1;
}

static inline __attribute__((always_inline)) u64 huge_encode_dev(dev_t dev)
{
 return new_encode_dev(dev);
}

static inline __attribute__((always_inline)) dev_t huge_decode_dev(u64 dev)
{
 return new_decode_dev(dev);
}

static inline __attribute__((always_inline)) int sysv_valid_dev(dev_t dev)
{
 return ((unsigned int) ((dev) >> 20)) < (1<<14) && ((unsigned int) ((dev) & ((1U << 20) - 1))) < (1<<18);
}

static inline __attribute__((always_inline)) u32 sysv_encode_dev(dev_t dev)
{
 return ((unsigned int) ((dev) & ((1U << 20) - 1))) | (((unsigned int) ((dev) >> 20)) << 18);
}

static inline __attribute__((always_inline)) unsigned sysv_major(u32 dev)
{
 return (dev >> 18) & 0x3fff;
}

static inline __attribute__((always_inline)) unsigned sysv_minor(u32 dev)
{
 return dev & 0x3ffff;
}
# 208 "include/linux/fs.h" 2
# 1 "include/linux/dcache.h" 1
# 10 "include/linux/dcache.h"
# 1 "include/linux/rcupdate.h" 1
# 50 "include/linux/rcupdate.h"
struct rcu_head {
 struct rcu_head *next;
 void (*func)(struct rcu_head *head);
};
# 64 "include/linux/rcupdate.h"
struct rcu_ctrlblk {
 long cur;
 long completed;
 int next_pending;
} __attribute__((__aligned__(1 << (7))));


static inline __attribute__((always_inline)) int rcu_batch_before(long a, long b)
{
        return (a - b) < 0;
}


static inline __attribute__((always_inline)) int rcu_batch_after(long a, long b)
{
        return (a - b) > 0;
}






struct rcu_data {

 long quiescbatch;
 int passed_quiesc;
 int qs_pending;


 long batch;
 struct rcu_head *nxtlist;
 struct rcu_head **nxttail;
 struct rcu_head *curlist;
 struct rcu_head **curtail;
 struct rcu_head *donelist;
 struct rcu_head **donetail;
 int cpu;
};

extern __typeof__(struct rcu_data) per_cpu__rcu_data;
extern __typeof__(struct rcu_data) per_cpu__rcu_bh_data;
extern struct rcu_ctrlblk rcu_ctrlblk;
extern struct rcu_ctrlblk rcu_bh_ctrlblk;







static inline __attribute__((always_inline)) void rcu_qsctr_inc(int cpu)
{
 struct rcu_data *rdp = &(*({ unsigned long __ptr; __asm__ ("" : "=g"(__ptr) : "0"(&per_cpu__rcu_data)); (typeof(&per_cpu__rcu_data)) (__ptr + (__per_cpu_offset[cpu])); }));
 rdp->passed_quiesc = 1;
}
static inline __attribute__((always_inline)) void rcu_bh_qsctr_inc(int cpu)
{
 struct rcu_data *rdp = &(*({ unsigned long __ptr; __asm__ ("" : "=g"(__ptr) : "0"(&per_cpu__rcu_bh_data)); (typeof(&per_cpu__rcu_bh_data)) (__ptr + (__per_cpu_offset[cpu])); }));
 rdp->passed_quiesc = 1;
}

static inline __attribute__((always_inline)) int __rcu_pending(struct rcu_ctrlblk *rcp,
      struct rcu_data *rdp)
{



 if (rdp->curlist && !rcu_batch_before(rcp->completed, rdp->batch))
  return 1;


 if (!rdp->curlist && rdp->nxtlist)
  return 1;


 if (rdp->donelist)
  return 1;


 if (rdp->quiescbatch != rcp->cur || rdp->qs_pending)
  return 1;


 return 0;
}

static inline __attribute__((always_inline)) int rcu_pending(int cpu)
{
 return __rcu_pending(&rcu_ctrlblk, &(*({ unsigned long __ptr; __asm__ ("" : "=g"(__ptr) : "0"(&per_cpu__rcu_data)); (typeof(&per_cpu__rcu_data)) (__ptr + (__per_cpu_offset[cpu])); }))) ||
  __rcu_pending(&rcu_bh_ctrlblk, &(*({ unsigned long __ptr; __asm__ ("" : "=g"(__ptr) : "0"(&per_cpu__rcu_bh_data)); (typeof(&per_cpu__rcu_bh_data)) (__ptr + (__per_cpu_offset[cpu])); })));
}
# 274 "include/linux/rcupdate.h"
extern void rcu_init(void);
extern void rcu_check_callbacks(int cpu, int user);
extern void rcu_restart_cpu(int cpu);


extern void call_rcu(struct rcu_head *head, void (*func)(struct rcu_head *head)) __attribute__((regparm(3)));

extern void call_rcu_bh(struct rcu_head *head, void (*func)(struct rcu_head *head)) __attribute__((regparm(3)));

extern void synchronize_kernel(void);
extern void synchronize_rcu(void);
void synchronize_idle(void);
# 11 "include/linux/dcache.h" 2


struct nameidata;
struct vfsmount;
# 34 "include/linux/dcache.h"
struct qstr {
 unsigned int hash;
 unsigned int len;
 const unsigned char *name;
};

struct dentry_stat_t {
 int nr_dentry;
 int nr_unused;
 int age_limit;
 int want_pages;
 int dummy[2];
};
extern struct dentry_stat_t dentry_stat;






static inline __attribute__((always_inline)) unsigned long
partial_name_hash(unsigned long c, unsigned long prevhash)
{
 return (prevhash + (c << 4) + (c >> 4)) * 11;
}





static inline __attribute__((always_inline)) unsigned long end_name_hash(unsigned long hash)
{
 return (unsigned int) hash;
}


static inline __attribute__((always_inline)) unsigned int
full_name_hash(const unsigned char *name, unsigned int len)
{
 unsigned long hash = 0;
 while (len--)
  hash = partial_name_hash(*name++, hash);
 return end_name_hash(hash);
}

struct dcookie_struct;



struct dentry {
 atomic_t d_count;
 unsigned int d_flags;
 spinlock_t d_lock;
 struct inode *d_inode;





 struct dentry *d_parent;
 struct qstr d_name;

 struct list_head d_lru;
 struct list_head d_child;
 struct list_head d_subdirs;
 struct list_head d_alias;
 unsigned long d_time;
 struct dentry_operations *d_op;
 struct super_block *d_sb;
 void *d_fsdata;
  struct rcu_head d_rcu;
 struct dcookie_struct *d_cookie;
 struct hlist_node d_hash;
 int d_mounted;
 unsigned char d_iname[36];
};

struct dentry_operations {
 int (*d_revalidate)(struct dentry *, struct nameidata *);
 int (*d_hash) (struct dentry *, struct qstr *);
 int (*d_compare) (struct dentry *, struct qstr *, struct qstr *);
 int (*d_delete)(struct dentry *);
 void (*d_release)(struct dentry *);
 void (*d_iput)(struct dentry *, struct inode *);
};
# 159 "include/linux/dcache.h"
extern spinlock_t dcache_lock;
# 177 "include/linux/dcache.h"
static inline __attribute__((always_inline)) void __d_drop(struct dentry *dentry)
{
 if (!(dentry->d_flags & 0x0010)) {
  dentry->d_flags |= 0x0010;
  hlist_del_rcu(&dentry->d_hash);
 }
}

static inline __attribute__((always_inline)) void d_drop(struct dentry *dentry)
{
 _spin_lock(&dcache_lock);
 _spin_lock(&dentry->d_lock);
  __d_drop(dentry);
 _spin_unlock(&dentry->d_lock);
 _spin_unlock(&dcache_lock);
}

static inline __attribute__((always_inline)) int dname_external(struct dentry *dentry)
{
 return dentry->d_name.name != dentry->d_iname;
}




extern void d_instantiate(struct dentry *, struct inode *);
extern struct dentry * d_instantiate_unique(struct dentry *, struct inode *);
extern void d_delete(struct dentry *);


extern struct dentry * d_alloc(struct dentry *, const struct qstr *);
extern struct dentry * d_alloc_anon(struct inode *);
extern struct dentry * d_splice_alias(struct inode *, struct dentry *);
extern void shrink_dcache_sb(struct super_block *);
extern void shrink_dcache_parent(struct dentry *);
extern void shrink_dcache_anon(struct hlist_head *);
extern int d_invalidate(struct dentry *);


extern struct dentry * d_alloc_root(struct inode *);


extern void d_genocide(struct dentry *);

extern struct dentry *d_find_alias(struct inode *);
extern void d_prune_aliases(struct inode *);


extern int have_submounts(struct dentry *);




extern void d_rehash(struct dentry *);
# 241 "include/linux/dcache.h"
static inline __attribute__((always_inline)) void d_add(struct dentry *entry, struct inode *inode)
{
 d_instantiate(entry, inode);
 d_rehash(entry);
}
# 255 "include/linux/dcache.h"
static inline __attribute__((always_inline)) struct dentry *d_add_unique(struct dentry *entry, struct inode *inode)
{
 struct dentry *res;

 res = d_instantiate_unique(entry, inode);
 d_rehash(res != ((void *)0) ? res : entry);
 return res;
}


extern void d_move(struct dentry *, struct dentry *);


extern struct dentry * d_lookup(struct dentry *, struct qstr *);
extern struct dentry * __d_lookup(struct dentry *, struct qstr *);


extern int d_validate(struct dentry *, struct dentry *);

extern char * d_path(struct dentry *, struct vfsmount *, char *, int);
# 291 "include/linux/dcache.h"
static inline __attribute__((always_inline)) struct dentry *dget(struct dentry *dentry)
{
 if (dentry) {
  do { if (__builtin_expect(!!((!((&dentry->d_count)->counter))!=0), 0)) __BUG(); } while(0);
  atomic_inc(&dentry->d_count);
 }
 return dentry;
}

extern struct dentry * dget_locked(struct dentry *);
# 309 "include/linux/dcache.h"
static inline __attribute__((always_inline)) int d_unhashed(struct dentry *dentry)
{
 return (dentry->d_flags & 0x0010);
}

static inline __attribute__((always_inline)) struct dentry *dget_parent(struct dentry *dentry)
{
 struct dentry *ret;

 _spin_lock(&dentry->d_lock);
 ret = dget(dentry->d_parent);
 _spin_unlock(&dentry->d_lock);
 return ret;
}

extern void dput(struct dentry *);

static inline __attribute__((always_inline)) int d_mountpoint(struct dentry *dentry)
{
 return dentry->d_mounted;
}

extern struct vfsmount *lookup_mnt(struct vfsmount *, struct dentry *);
extern struct dentry *lookup_create(struct nameidata *nd, int is_dir);

extern int sysctl_vfs_cache_pressure;
# 209 "include/linux/fs.h" 2




# 1 "include/linux/radix-tree.h" 1
# 25 "include/linux/radix-tree.h"
struct radix_tree_root {
 unsigned int height;
 int gfp_mask;
 struct radix_tree_node *rnode;
};
# 47 "include/linux/radix-tree.h"
int radix_tree_insert(struct radix_tree_root *, unsigned long, void *);
void *radix_tree_lookup(struct radix_tree_root *, unsigned long);
void *radix_tree_delete(struct radix_tree_root *, unsigned long);
unsigned int
radix_tree_gang_lookup(struct radix_tree_root *root, void **results,
   unsigned long first_index, unsigned int max_items);
int radix_tree_preload(int gfp_mask);
void radix_tree_init(void);
void *radix_tree_tag_set(struct radix_tree_root *root,
   unsigned long index, int tag);
void *radix_tree_tag_clear(struct radix_tree_root *root,
   unsigned long index, int tag);
int radix_tree_tag_get(struct radix_tree_root *root,
   unsigned long index, int tag);
unsigned int
radix_tree_gang_lookup_tag(struct radix_tree_root *root, void **results,
  unsigned long first_index, unsigned int max_items, int tag);
int radix_tree_tagged(struct radix_tree_root *root, int tag);

static inline __attribute__((always_inline)) void radix_tree_preload_end(void)
{
 do { } while (0);
}
# 214 "include/linux/fs.h" 2
# 222 "include/linux/fs.h"
struct iovec;
struct nameidata;
struct kiocb;
struct pipe_inode_info;
struct poll_table_struct;
struct kstatfs;
struct vm_area_struct;
struct vfsmount;


extern void update_atime (struct inode *);

extern void __attribute__ ((__section__ (".init.text"))) inode_init(unsigned long);
extern void __attribute__ ((__section__ (".init.text"))) inode_init_early(void);
extern void __attribute__ ((__section__ (".init.text"))) mnt_init(unsigned long);
extern void __attribute__ ((__section__ (".init.text"))) files_init(unsigned long);

struct buffer_head;
typedef int (get_block_t)(struct inode *inode, sector_t iblock,
   struct buffer_head *bh_result, int create);
typedef int (get_blocks_t)(struct inode *inode, sector_t iblock,
   unsigned long max_blocks,
   struct buffer_head *bh_result, int create);
typedef void (dio_iodone_t)(struct kiocb *iocb, loff_t offset,
   ssize_t bytes, void *private);
# 275 "include/linux/fs.h"
struct iattr {
 unsigned int ia_valid;
 umode_t ia_mode;
 uid_t ia_uid;
 gid_t ia_gid;
 loff_t ia_size;
 struct timespec ia_atime;
 struct timespec ia_mtime;
 struct timespec ia_ctime;
 unsigned int ia_attr_flags;
};
# 299 "include/linux/fs.h"
# 1 "include/linux/quota.h" 1
# 45 "include/linux/quota.h"
typedef __kernel_uid32_t qid_t;
typedef __u64 qsize_t;

extern spinlock_t dq_data_lock;
# 106 "include/linux/quota.h"
struct if_dqblk {
 __u64 dqb_bhardlimit;
 __u64 dqb_bsoftlimit;
 __u64 dqb_curspace;
 __u64 dqb_ihardlimit;
 __u64 dqb_isoftlimit;
 __u64 dqb_curinodes;
 __u64 dqb_btime;
 __u64 dqb_itime;
 __u32 dqb_valid;
};
# 127 "include/linux/quota.h"
struct if_dqinfo {
 __u64 dqi_bgrace;
 __u64 dqi_igrace;
 __u32 dqi_flags;
 __u32 dqi_valid;
};



# 1 "include/linux/dqblk_xfs.h" 1
# 52 "include/linux/dqblk_xfs.h"
typedef struct fs_disk_quota {
 __s8 d_version;
 __s8 d_flags;
 __u16 d_fieldmask;
 __u32 d_id;
 __u64 d_blk_hardlimit;
 __u64 d_blk_softlimit;
 __u64 d_ino_hardlimit;
 __u64 d_ino_softlimit;
 __u64 d_bcount;
 __u64 d_icount;
 __s32 d_itimer;

 __s32 d_btimer;
 __u16 d_iwarns;
 __u16 d_bwarns;
 __s32 d_padding2;
 __u64 d_rtb_hardlimit;
 __u64 d_rtb_softlimit;
 __u64 d_rtbcount;
 __s32 d_rtbtimer;
 __u16 d_rtbwarns;
 __s16 d_padding3;
 char d_padding4[8];
} fs_disk_quota_t;
# 139 "include/linux/dqblk_xfs.h"
typedef struct fs_qfilestat {
 __u64 qfs_ino;
 __u64 qfs_nblks;
 __u32 qfs_nextents;
} fs_qfilestat_t;

typedef struct fs_quota_stat {
 __s8 qs_version;
 __u16 qs_flags;
 __s8 qs_pad;
 fs_qfilestat_t qs_uquota;
 fs_qfilestat_t qs_gquota;
 __u32 qs_incoredqs;
 __s32 qs_btimelimit;
 __s32 qs_itimelimit;
 __s32 qs_rtbtimelimit;
 __u16 qs_bwarnlimit;
 __u16 qs_iwarnlimit;
} fs_quota_stat_t;
# 137 "include/linux/quota.h" 2
# 1 "include/linux/dqblk_v1.h" 1
# 21 "include/linux/dqblk_v1.h"
struct v1_mem_dqinfo {
};
# 138 "include/linux/quota.h" 2
# 1 "include/linux/dqblk_v2.h" 1
# 20 "include/linux/dqblk_v2.h"
struct v2_mem_dqinfo {
 unsigned int dqi_blocks;
 unsigned int dqi_free_blk;
 unsigned int dqi_free_entry;
};
# 139 "include/linux/quota.h" 2
# 150 "include/linux/quota.h"
struct mem_dqblk {
 __u32 dqb_bhardlimit;
 __u32 dqb_bsoftlimit;
 qsize_t dqb_curspace;
 __u32 dqb_ihardlimit;
 __u32 dqb_isoftlimit;
 __u32 dqb_curinodes;
 time_t dqb_btime;
 time_t dqb_itime;
};




struct quota_format_type;

struct mem_dqinfo {
 struct quota_format_type *dqi_format;
 struct list_head dqi_dirty_list;
 unsigned long dqi_flags;
 unsigned int dqi_bgrace;
 unsigned int dqi_igrace;
 union {
  struct v1_mem_dqinfo v1_i;
  struct v2_mem_dqinfo v2_i;
 } u;
};

struct super_block;





extern void mark_info_dirty(struct super_block *sb, int type);







struct dqstats {
 int lookups;
 int drops;
 int reads;
 int writes;
 int cache_hits;
 int allocated_dquots;
 int free_dquots;
 int syncs;
};

extern struct dqstats dqstats;
# 213 "include/linux/quota.h"
struct dquot {
 struct hlist_node dq_hash;
 struct list_head dq_inuse;
 struct list_head dq_free;
 struct list_head dq_dirty;
 struct semaphore dq_lock;
 atomic_t dq_count;
 wait_queue_head_t dq_wait_unused;
 struct super_block *dq_sb;
 unsigned int dq_id;
 loff_t dq_off;
 unsigned long dq_flags;
 short dq_type;
 struct mem_dqblk dq_dqb;
};







struct quota_format_ops {
 int (*check_quota_file)(struct super_block *sb, int type);
 int (*read_file_info)(struct super_block *sb, int type);
 int (*write_file_info)(struct super_block *sb, int type);
 int (*free_file_info)(struct super_block *sb, int type);
 int (*read_dqblk)(struct dquot *dquot);
 int (*commit_dqblk)(struct dquot *dquot);
 int (*release_dqblk)(struct dquot *dquot);
};


struct dquot_operations {
 int (*initialize) (struct inode *, int);
 int (*drop) (struct inode *);
 int (*alloc_space) (struct inode *, qsize_t, int);
 int (*alloc_inode) (const struct inode *, unsigned long);
 int (*free_space) (struct inode *, qsize_t);
 int (*free_inode) (const struct inode *, unsigned long);
 int (*transfer) (struct inode *, struct iattr *);
 int (*write_dquot) (struct dquot *);
 int (*acquire_dquot) (struct dquot *);
 int (*release_dquot) (struct dquot *);
 int (*mark_dirty) (struct dquot *);
 int (*write_info) (struct super_block *, int);
};


struct quotactl_ops {
 int (*quota_on)(struct super_block *, int, int, char *);
 int (*quota_off)(struct super_block *, int);
 int (*quota_sync)(struct super_block *, int);
 int (*get_info)(struct super_block *, int, struct if_dqinfo *);
 int (*set_info)(struct super_block *, int, struct if_dqinfo *);
 int (*get_dqblk)(struct super_block *, int, qid_t, struct if_dqblk *);
 int (*set_dqblk)(struct super_block *, int, qid_t, struct if_dqblk *);
 int (*get_xstate)(struct super_block *, struct fs_quota_stat *);
 int (*set_xstate)(struct super_block *, unsigned int, int);
 int (*get_xquota)(struct super_block *, int, qid_t, struct fs_disk_quota *);
 int (*set_xquota)(struct super_block *, int, qid_t, struct fs_disk_quota *);
};

struct quota_format_type {
 int qf_fmt_id;
 struct quota_format_ops *qf_ops;
 struct module *qf_owner;
 struct quota_format_type *qf_next;
};




struct quota_info {
 unsigned int flags;
 struct semaphore dqio_sem;
 struct semaphore dqonoff_sem;
 struct rw_semaphore dqptr_sem;
 struct inode *files[2];
 struct vfsmount *mnt[2];
 struct mem_dqinfo info[2];
 struct quota_format_ops *ops[2];
};


int mark_dquot_dirty(struct dquot *dquot);
# 308 "include/linux/quota.h"
int register_quota_format(struct quota_format_type *fmt);
void unregister_quota_format(struct quota_format_type *fmt);

struct quota_module_name {
 int qm_fmt_id;
 char *qm_mod_name;
};
# 300 "include/linux/fs.h" 2




struct page;
struct address_space;
struct writeback_control;

struct address_space_operations {
 int (*writepage)(struct page *page, struct writeback_control *wbc);
 int (*readpage)(struct file *, struct page *);
 int (*sync_page)(struct page *);


 int (*writepages)(struct address_space *, struct writeback_control *);


 int (*set_page_dirty)(struct page *page);

 int (*readpages)(struct file *filp, struct address_space *mapping,
   struct list_head *pages, unsigned nr_pages);





 int (*prepare_write)(struct file *, struct page *, unsigned, unsigned);
 int (*commit_write)(struct file *, struct page *, unsigned, unsigned);

 sector_t (*bmap)(struct address_space *, sector_t);
 int (*invalidatepage) (struct page *, unsigned long);
 int (*releasepage) (struct page *, int);
 ssize_t (*direct_IO)(int, struct kiocb *, const struct iovec *iov,
   loff_t offset, unsigned long nr_segs);
 struct page* (*get_xip_page)(struct address_space *, sector_t,
   int);
};

struct backing_dev_info;
struct address_space {
 struct inode *host;
 struct radix_tree_root page_tree;
 rwlock_t tree_lock;
 unsigned int i_mmap_writable;
 struct prio_tree_root i_mmap;
 struct list_head i_mmap_nonlinear;
 spinlock_t i_mmap_lock;
 unsigned int truncate_count;
 unsigned long nrpages;
 unsigned long writeback_index;
 struct address_space_operations *a_ops;
 unsigned long flags;
 struct backing_dev_info *backing_dev_info;
 spinlock_t private_lock;
 struct list_head private_list;
 struct address_space *assoc_mapping;
} __attribute__((aligned(sizeof(long))));






struct block_device {
 dev_t bd_dev;
 struct inode * bd_inode;
 int bd_openers;
 struct semaphore bd_sem;
 struct semaphore bd_mount_sem;
 struct list_head bd_inodes;
 void * bd_holder;
 int bd_holders;
 struct block_device * bd_contains;
 unsigned bd_block_size;
 struct hd_struct * bd_part;

 unsigned bd_part_count;
 int bd_invalidated;
 struct gendisk * bd_disk;
 struct list_head bd_list;
 struct backing_dev_info *bd_inode_backing_dev_info;






 unsigned long bd_private;
};
# 397 "include/linux/fs.h"
int mapping_tagged(struct address_space *mapping, int tag);




static inline __attribute__((always_inline)) int mapping_mapped(struct address_space *mapping)
{
 return !prio_tree_empty(&mapping->i_mmap) ||
  !list_empty(&mapping->i_mmap_nonlinear);
}







static inline __attribute__((always_inline)) int mapping_writably_mapped(struct address_space *mapping)
{
 return mapping->i_mmap_writable != 0;
}
# 430 "include/linux/fs.h"
struct inode {
 struct hlist_node i_hash;
 struct list_head i_list;
 struct list_head i_sb_list;
 struct list_head i_dentry;
 unsigned long i_ino;
 atomic_t i_count;
 umode_t i_mode;
 unsigned int i_nlink;
 uid_t i_uid;
 gid_t i_gid;
 dev_t i_rdev;
 loff_t i_size;
 struct timespec i_atime;
 struct timespec i_mtime;
 struct timespec i_ctime;
 unsigned int i_blkbits;
 unsigned long i_blksize;
 unsigned long i_version;
 unsigned long i_blocks;
 unsigned short i_bytes;
 spinlock_t i_lock;
 struct semaphore i_sem;
 struct rw_semaphore i_alloc_sem;
 struct inode_operations *i_op;
 struct file_operations *i_fop;
 struct super_block *i_sb;
 struct file_lock *i_flock;
 struct address_space *i_mapping;
 struct address_space i_data;

 struct dquot *i_dquot[2];


 struct list_head i_devices;
 struct pipe_inode_info *i_pipe;
 struct block_device *i_bdev;
 struct cdev *i_cdev;
 int i_cindex;

 __u32 i_generation;


 unsigned long i_dnotify_mask;
 struct dnotify_struct *i_dnotify;



 struct list_head inotify_watches;
 struct semaphore inotify_sem;


 unsigned long i_state;
 unsigned long dirtied_when;

 unsigned int i_flags;

 atomic_t i_writecount;
 void *i_security;
 union {
  void *generic_ip;
 } u;

 seqcount_t i_size_seqcount;

};
# 507 "include/linux/fs.h"
static inline __attribute__((always_inline)) loff_t i_size_read(struct inode *inode)
{

 loff_t i_size;
 unsigned int seq;

 do {
  seq = read_seqcount_begin(&inode->i_size_seqcount);
  i_size = inode->i_size;
 } while (read_seqcount_retry(&inode->i_size_seqcount, seq));
 return i_size;
# 528 "include/linux/fs.h"
}


static inline __attribute__((always_inline)) void i_size_write(struct inode *inode, loff_t i_size)
{

 write_seqcount_begin(&inode->i_size_seqcount);
 inode->i_size = i_size;
 write_seqcount_end(&inode->i_size_seqcount);







}

static inline __attribute__((always_inline)) unsigned iminor(struct inode *inode)
{
 return ((unsigned int) ((inode->i_rdev) & ((1U << 20) - 1)));
}

static inline __attribute__((always_inline)) unsigned imajor(struct inode *inode)
{
 return ((unsigned int) ((inode->i_rdev) >> 20));
}

extern struct block_device *I_BDEV(struct inode *inode);

struct fown_struct {
 rwlock_t lock;
 int pid;
 uid_t uid, euid;
 void *security;
 int signum;
};




struct file_ra_state {
 unsigned long start;
 unsigned long size;
 unsigned long flags;
 unsigned long cache_hit;
 unsigned long prev_page;
 unsigned long ahead_start;
 unsigned long ahead_size;
 unsigned long ra_pages;
 unsigned long mmap_hit;
 unsigned long mmap_miss;
};



struct file {
 struct list_head f_list;
 struct dentry *f_dentry;
 struct vfsmount *f_vfsmnt;
 struct file_operations *f_op;
 atomic_t f_count;
 unsigned int f_flags;
 mode_t f_mode;
 loff_t f_pos;
 struct fown_struct f_owner;
 unsigned int f_uid, f_gid;
 struct file_ra_state f_ra;

 size_t f_maxcount;
 unsigned long f_version;
 void *f_security;


 void *private_data;



 struct list_head f_ep_links;
 spinlock_t f_ep_lock;

 struct address_space *f_mapping;
};
extern spinlock_t files_lock;
# 642 "include/linux/fs.h"
typedef struct files_struct *fl_owner_t;

struct file_lock_operations {
 void (*fl_insert)(struct file_lock *);
 void (*fl_remove)(struct file_lock *);
 void (*fl_copy_lock)(struct file_lock *, struct file_lock *);
 void (*fl_release_private)(struct file_lock *);
};

struct lock_manager_operations {
 int (*fl_compare_owner)(struct file_lock *, struct file_lock *);
 void (*fl_notify)(struct file_lock *);
 void (*fl_copy_lock)(struct file_lock *, struct file_lock *);
 void (*fl_release_private)(struct file_lock *);
 void (*fl_break)(struct file_lock *);
 int (*fl_mylease)(struct file_lock *, struct file_lock *);
 int (*fl_change)(struct file_lock **, int);
};


# 1 "include/linux/nfs_fs_i.h" 1





# 1 "include/linux/nfs.h" 1
# 10 "include/linux/nfs.h"
# 1 "include/linux/sunrpc/msg_prot.h" 1
# 15 "include/linux/sunrpc/msg_prot.h"
typedef u32 rpc_authflavor_t;

enum rpc_auth_flavors {
 RPC_AUTH_NULL = 0,
 RPC_AUTH_UNIX = 1,
 RPC_AUTH_SHORT = 2,
 RPC_AUTH_DES = 3,
 RPC_AUTH_KRB = 4,
 RPC_AUTH_GSS = 6,
 RPC_AUTH_MAXFLAVOR = 8,

 RPC_AUTH_GSS_KRB5 = 390003,
 RPC_AUTH_GSS_KRB5I = 390004,
 RPC_AUTH_GSS_KRB5P = 390005,
 RPC_AUTH_GSS_LKEY = 390006,
 RPC_AUTH_GSS_LKEYI = 390007,
 RPC_AUTH_GSS_LKEYP = 390008,
 RPC_AUTH_GSS_SPKM = 390009,
 RPC_AUTH_GSS_SPKMI = 390010,
 RPC_AUTH_GSS_SPKMP = 390011,
};

enum rpc_msg_type {
 RPC_CALL = 0,
 RPC_REPLY = 1
};

enum rpc_reply_stat {
 RPC_MSG_ACCEPTED = 0,
 RPC_MSG_DENIED = 1
};

enum rpc_accept_stat {
 RPC_SUCCESS = 0,
 RPC_PROG_UNAVAIL = 1,
 RPC_PROG_MISMATCH = 2,
 RPC_PROC_UNAVAIL = 3,
 RPC_GARBAGE_ARGS = 4,
 RPC_SYSTEM_ERR = 5
};

enum rpc_reject_stat {
 RPC_MISMATCH = 0,
 RPC_AUTH_ERROR = 1
};

enum rpc_auth_stat {
 RPC_AUTH_OK = 0,
 RPC_AUTH_BADCRED = 1,
 RPC_AUTH_REJECTEDCRED = 2,
 RPC_AUTH_BADVERF = 3,
 RPC_AUTH_REJECTEDVERF = 4,
 RPC_AUTH_TOOWEAK = 5,

 RPCSEC_GSS_CREDPROBLEM = 13,
 RPCSEC_GSS_CTXPROBLEM = 14
};
# 11 "include/linux/nfs.h" 2
# 42 "include/linux/nfs.h"
 enum nfs_stat {
 NFS_OK = 0,
 NFSERR_PERM = 1,
 NFSERR_NOENT = 2,
 NFSERR_IO = 5,
 NFSERR_NXIO = 6,
 NFSERR_EAGAIN = 11,
 NFSERR_ACCES = 13,
 NFSERR_EXIST = 17,
 NFSERR_XDEV = 18,
 NFSERR_NODEV = 19,
 NFSERR_NOTDIR = 20,
 NFSERR_ISDIR = 21,
 NFSERR_INVAL = 22,
 NFSERR_FBIG = 27,
 NFSERR_NOSPC = 28,
 NFSERR_ROFS = 30,
 NFSERR_MLINK = 31,
 NFSERR_OPNOTSUPP = 45,
 NFSERR_NAMETOOLONG = 63,
 NFSERR_NOTEMPTY = 66,
 NFSERR_DQUOT = 69,
 NFSERR_STALE = 70,
 NFSERR_REMOTE = 71,
 NFSERR_WFLUSH = 99,
 NFSERR_BADHANDLE = 10001,
 NFSERR_NOT_SYNC = 10002,
 NFSERR_BAD_COOKIE = 10003,
 NFSERR_NOTSUPP = 10004,
 NFSERR_TOOSMALL = 10005,
 NFSERR_SERVERFAULT = 10006,
 NFSERR_BADTYPE = 10007,
 NFSERR_JUKEBOX = 10008,
 NFSERR_SAME = 10009,
 NFSERR_DENIED = 10010,
 NFSERR_EXPIRED = 10011,
 NFSERR_LOCKED = 10012,
 NFSERR_GRACE = 10013,
 NFSERR_FHEXPIRED = 10014,
 NFSERR_SHARE_DENIED = 10015,
 NFSERR_WRONGSEC = 10016,
 NFSERR_CLID_INUSE = 10017,
 NFSERR_RESOURCE = 10018,
 NFSERR_MOVED = 10019,
 NFSERR_NOFILEHANDLE = 10020,
 NFSERR_MINOR_VERS_MISMATCH = 10021,
 NFSERR_STALE_CLIENTID = 10022,
 NFSERR_STALE_STATEID = 10023,
 NFSERR_OLD_STATEID = 10024,
 NFSERR_BAD_STATEID = 10025,
 NFSERR_BAD_SEQID = 10026,
 NFSERR_NOT_SAME = 10027,
 NFSERR_LOCK_RANGE = 10028,
 NFSERR_SYMLINK = 10029,
 NFSERR_RESTOREFH = 10030,
 NFSERR_LEASE_MOVED = 10031,
 NFSERR_ATTRNOTSUPP = 10032,
 NFSERR_NO_GRACE = 10033,
 NFSERR_RECLAIM_BAD = 10034,
 NFSERR_RECLAIM_CONFLICT = 10035,
 NFSERR_BAD_XDR = 10036,
 NFSERR_LOCKS_HELD = 10037,
 NFSERR_OPENMODE = 10038,
 NFSERR_BADOWNER = 10039,
 NFSERR_BADCHAR = 10040,
 NFSERR_BADNAME = 10041,
 NFSERR_BAD_RANGE = 10042,
 NFSERR_LOCK_NOTSUPP = 10043,
 NFSERR_OP_ILLEGAL = 10044,
 NFSERR_DEADLOCK = 10045,
 NFSERR_FILE_OPEN = 10046,
 NFSERR_ADMIN_REVOKED = 10047,
 NFSERR_CB_PATH_DOWN = 10048,
 NFSERR_REPLAY_ME = 10049
};



enum nfs_ftype {
 NFNON = 0,
 NFREG = 1,
 NFDIR = 2,
 NFBLK = 3,
 NFCHR = 4,
 NFLNK = 5,
 NFSOCK = 6,
 NFBAD = 7,
 NFFIFO = 8
};






struct nfs_fh {
 unsigned short size;
 unsigned char data[128];
};





static inline __attribute__((always_inline)) int nfs_compare_fh(const struct nfs_fh *a, const struct nfs_fh *b)
{
 return a->size != b->size || __builtin_memcmp(a->data, b->data, a->size) != 0;
}

static inline __attribute__((always_inline)) void nfs_copy_fh(struct nfs_fh *target, const struct nfs_fh *source)
{
 target->size = source->size;
 __memcpy(target->data,source->data,source->size);
}
# 165 "include/linux/nfs.h"
enum nfs3_stable_how {
 NFS_UNSTABLE = 0,
 NFS_DATA_SYNC = 1,
 NFS_FILE_SYNC = 2
};
# 7 "include/linux/nfs_fs_i.h" 2

struct nlm_lockowner;




struct nfs_lock_info {
 u32 state;
 u32 flags;
 struct nlm_lockowner *owner;
};

struct nfs4_lock_state;
struct nfs4_lock_info {
 struct nfs4_lock_state *owner;
};
# 663 "include/linux/fs.h" 2

struct file_lock {
 struct file_lock *fl_next;
 struct list_head fl_link;
 struct list_head fl_block;
 fl_owner_t fl_owner;
 unsigned int fl_pid;
 wait_queue_head_t fl_wait;
 struct file *fl_file;
 unsigned char fl_flags;
 unsigned char fl_type;
 loff_t fl_start;
 loff_t fl_end;

 struct fasync_struct * fl_fasync;
 unsigned long fl_break_time;

 struct file_lock_operations *fl_ops;
 struct lock_manager_operations *fl_lmops;
 union {
  struct nfs_lock_info nfs_fl;
  struct nfs4_lock_info nfs4_fl;
 } fl_u;
};
# 695 "include/linux/fs.h"
extern struct list_head file_lock_list;

# 1 "include/linux/fcntl.h" 1



# 1 "include/asm/fcntl.h" 1
# 70 "include/asm/fcntl.h"
struct flock {
 short l_type;
 short l_whence;
 off_t l_start;
 off_t l_len;
 pid_t l_pid;
};

struct flock64 {
 short l_type;
 short l_whence;
 loff_t l_start;
 loff_t l_len;
 pid_t l_pid;
};
# 5 "include/linux/fcntl.h" 2
# 698 "include/linux/fs.h" 2

extern int fcntl_getlk(struct file *, struct flock *);
extern int fcntl_setlk(unsigned int, struct file *, unsigned int,
   struct flock *);


extern int fcntl_getlk64(struct file *, struct flock64 *);
extern int fcntl_setlk64(unsigned int, struct file *, unsigned int,
   struct flock64 *);


extern void send_sigio(struct fown_struct *fown, int fd, int band);
extern int fcntl_setlease(unsigned int fd, struct file *filp, long arg);
extern int fcntl_getlease(struct file *filp);


extern void locks_init_lock(struct file_lock *);
extern void locks_copy_lock(struct file_lock *, struct file_lock *);
extern void locks_remove_posix(struct file *, fl_owner_t);
extern void locks_remove_flock(struct file *);
extern struct file_lock *posix_test_lock(struct file *, struct file_lock *);
extern int posix_lock_file(struct file *, struct file_lock *);
extern int posix_lock_file_wait(struct file *, struct file_lock *);
extern void posix_block_lock(struct file_lock *, struct file_lock *);
extern void posix_unblock_lock(struct file *, struct file_lock *);
extern int posix_locks_deadlock(struct file_lock *, struct file_lock *);
extern int flock_lock_file_wait(struct file *filp, struct file_lock *fl);
extern int __break_lease(struct inode *inode, unsigned int flags);
extern void lease_get_mtime(struct inode *, struct timespec *time);
extern int setlease(struct file *, long, struct file_lock **);
extern int lease_modify(struct file_lock **, int);
extern int lock_may_read(struct inode *, loff_t start, unsigned long count);
extern int lock_may_write(struct inode *, loff_t start, unsigned long count);
extern void steal_locks(fl_owner_t from);

struct fasync_struct {
 int magic;
 int fa_fd;
 struct fasync_struct *fa_next;
 struct file *fa_file;
};




extern int fasync_helper(int, struct file *, int, struct fasync_struct **);

extern void kill_fasync(struct fasync_struct **, int, int);

extern void __kill_fasync(struct fasync_struct *, int, int);

extern int f_setown(struct file *filp, unsigned long arg, int force);
extern void f_delown(struct file *filp);
extern int send_sigurg(struct fown_struct *fown);
# 761 "include/linux/fs.h"
extern struct list_head super_blocks;
extern spinlock_t sb_lock;



struct super_block {
 struct list_head s_list;
 dev_t s_dev;
 unsigned long s_blocksize;
 unsigned long s_old_blocksize;
 unsigned char s_blocksize_bits;
 unsigned char s_dirt;
 unsigned long long s_maxbytes;
 struct file_system_type *s_type;
 struct super_operations *s_op;
 struct dquot_operations *dq_op;
  struct quotactl_ops *s_qcop;
 struct export_operations *s_export_op;
 unsigned long s_flags;
 unsigned long s_magic;
 struct dentry *s_root;
 struct rw_semaphore s_umount;
 struct semaphore s_lock;
 int s_count;
 int s_syncing;
 int s_need_sync_fs;
 atomic_t s_active;
 void *s_security;
 struct xattr_handler **s_xattr;

 struct list_head s_inodes;
 struct list_head s_dirty;
 struct list_head s_io;
 struct hlist_head s_anon;
 struct list_head s_files;

 struct block_device *s_bdev;
 struct list_head s_instances;
 struct quota_info s_dquot;

 int s_frozen;
 wait_queue_head_t s_wait_unfrozen;

 char s_id[32];

 void *s_fs_info;





 struct semaphore s_vfs_rename_sem;



 u32 s_time_gran;
};

extern struct timespec current_fs_time(struct super_block *sb);




enum {
 SB_UNFROZEN = 0,
 SB_FREEZE_WRITE = 1,
 SB_FREEZE_TRANS = 2,
};




static inline __attribute__((always_inline)) void get_fs_excl(void)
{
 atomic_inc(&get_current()->fs_excl);
}

static inline __attribute__((always_inline)) void put_fs_excl(void)
{
 atomic_dec(&get_current()->fs_excl);
}

static inline __attribute__((always_inline)) int has_fs_excl(void)
{
 return ((&get_current()->fs_excl)->counter);
}





static inline __attribute__((always_inline)) void lock_super(struct super_block * sb)
{
 get_fs_excl();
 down(&sb->s_lock);
}

static inline __attribute__((always_inline)) void unlock_super(struct super_block * sb)
{
 put_fs_excl();
 up(&sb->s_lock);
}




extern int vfs_create(struct inode *, struct dentry *, int, struct nameidata *);
extern int vfs_mkdir(struct inode *, struct dentry *, int);
extern int vfs_mknod(struct inode *, struct dentry *, int, dev_t);
extern int vfs_symlink(struct inode *, struct dentry *, const char *, int);
extern int vfs_link(struct dentry *, struct inode *, struct dentry *);
extern int vfs_rmdir(struct inode *, struct dentry *);
extern int vfs_unlink(struct inode *, struct dentry *);
extern int vfs_rename(struct inode *, struct dentry *, struct inode *, struct dentry *);




extern void dentry_unhash(struct dentry *dentry);
# 900 "include/linux/fs.h"
int generic_osync_inode(struct inode *, struct address_space *, int);







typedef int (*filldir_t)(void *, const char *, int, loff_t, ino_t, unsigned);

struct block_device_operations {
 int (*open) (struct inode *, struct file *);
 int (*release) (struct inode *, struct file *);
 int (*ioctl) (struct inode *, struct file *, unsigned, unsigned long);
 long (*unlocked_ioctl) (struct file *, unsigned, unsigned long);
 long (*compat_ioctl) (struct file *, unsigned, unsigned long);
 int (*direct_access) (struct block_device *, sector_t, unsigned long *);
 int (*media_changed) (struct gendisk *);
 int (*revalidate_disk) (struct gendisk *);
 struct module *owner;
};
# 931 "include/linux/fs.h"
typedef struct {
 size_t written;
 size_t count;
 union {
  char * buf;
  void *data;
 } arg;
 int error;
} read_descriptor_t;

typedef int (*read_actor_t)(read_descriptor_t *, struct page *, unsigned long, unsigned long);
# 954 "include/linux/fs.h"
struct file_operations {
 struct module *owner;
 loff_t (*llseek) (struct file *, loff_t, int);
 ssize_t (*read) (struct file *, char *, size_t, loff_t *);
 ssize_t (*aio_read) (struct kiocb *, char *, size_t, loff_t);
 ssize_t (*write) (struct file *, const char *, size_t, loff_t *);
 ssize_t (*aio_write) (struct kiocb *, const char *, size_t, loff_t);
 int (*readdir) (struct file *, void *, filldir_t);
 unsigned int (*poll) (struct file *, struct poll_table_struct *);
 int (*ioctl) (struct inode *, struct file *, unsigned int, unsigned long);
 long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
 long (*compat_ioctl) (struct file *, unsigned int, unsigned long);
 int (*mmap) (struct file *, struct vm_area_struct *);
 int (*open) (struct inode *, struct file *);
 int (*flush) (struct file *);
 int (*release) (struct inode *, struct file *);
 int (*fsync) (struct file *, struct dentry *, int datasync);
 int (*aio_fsync) (struct kiocb *, int datasync);
 int (*fasync) (int, struct file *, int);
 int (*lock) (struct file *, int, struct file_lock *);
 ssize_t (*readv) (struct file *, const struct iovec *, unsigned long, loff_t *);
 ssize_t (*writev) (struct file *, const struct iovec *, unsigned long, loff_t *);
 ssize_t (*sendfile) (struct file *, loff_t *, size_t, read_actor_t, void *);
 ssize_t (*sendpage) (struct file *, struct page *, int, size_t, loff_t *, int);
 unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
 int (*check_flags)(int);
 int (*dir_notify)(struct file *filp, unsigned long arg);
 int (*flock) (struct file *, int, struct file_lock *);
};

struct inode_operations {
 int (*create) (struct inode *,struct dentry *,int, struct nameidata *);
 struct dentry * (*lookup) (struct inode *,struct dentry *, struct nameidata *);
 int (*link) (struct dentry *,struct inode *,struct dentry *);
 int (*unlink) (struct inode *,struct dentry *);
 int (*symlink) (struct inode *,struct dentry *,const char *);
 int (*mkdir) (struct inode *,struct dentry *,int);
 int (*rmdir) (struct inode *,struct dentry *);
 int (*mknod) (struct inode *,struct dentry *,int,dev_t);
 int (*rename) (struct inode *, struct dentry *,
   struct inode *, struct dentry *);
 int (*readlink) (struct dentry *, char *,int);
 void * (*follow_link) (struct dentry *, struct nameidata *);
 void (*put_link) (struct dentry *, struct nameidata *, void *);
 void (*truncate) (struct inode *);
 int (*permission) (struct inode *, int, struct nameidata *);
 int (*setattr) (struct dentry *, struct iattr *);
 int (*getattr) (struct vfsmount *mnt, struct dentry *, struct kstat *);
 int (*setxattr) (struct dentry *, const char *,const void *,size_t,int);
 ssize_t (*getxattr) (struct dentry *, const char *, void *, size_t);
 ssize_t (*listxattr) (struct dentry *, char *, size_t);
 int (*removexattr) (struct dentry *, const char *);
};

struct seq_file;

extern ssize_t vfs_read(struct file *, char *, size_t, loff_t *);
extern ssize_t vfs_write(struct file *, const char *, size_t, loff_t *);
extern ssize_t vfs_readv(struct file *, const struct iovec *,
  unsigned long, loff_t *);
extern ssize_t vfs_writev(struct file *, const struct iovec *,
  unsigned long, loff_t *);





struct super_operations {
    struct inode *(*alloc_inode)(struct super_block *sb);
 void (*destroy_inode)(struct inode *);

 void (*read_inode) (struct inode *);

    void (*dirty_inode) (struct inode *);
 int (*write_inode) (struct inode *, int);
 void (*put_inode) (struct inode *);
 void (*drop_inode) (struct inode *);
 void (*delete_inode) (struct inode *);
 void (*put_super) (struct super_block *);
 void (*write_super) (struct super_block *);
 int (*sync_fs)(struct super_block *sb, int wait);
 void (*write_super_lockfs) (struct super_block *);
 void (*unlockfs) (struct super_block *);
 int (*statfs) (struct super_block *, struct kstatfs *);
 int (*remount_fs) (struct super_block *, int *, char *);
 void (*clear_inode) (struct inode *);
 void (*umount_begin) (struct super_block *);

 int (*show_options)(struct seq_file *, struct vfsmount *);

 ssize_t (*quota_read)(struct super_block *, int, char *, size_t, loff_t);
 ssize_t (*quota_write)(struct super_block *, int, const char *, size_t, loff_t);
};
# 1061 "include/linux/fs.h"
extern void __mark_inode_dirty(struct inode *, int);
static inline __attribute__((always_inline)) void mark_inode_dirty(struct inode *inode)
{
 __mark_inode_dirty(inode, (1 | 2 | 4));
}

static inline __attribute__((always_inline)) void mark_inode_dirty_sync(struct inode *inode)
{
 __mark_inode_dirty(inode, 1);
}

static inline __attribute__((always_inline)) void touch_atime(struct vfsmount *mnt, struct dentry *dentry)
{

 update_atime(dentry->d_inode);
}

static inline __attribute__((always_inline)) void file_accessed(struct file *file)
{
 if (!(file->f_flags & 01000000))
  touch_atime(file->f_vfsmnt, file->f_dentry);
}

int sync_inode(struct inode *inode, struct writeback_control *wbc);
# 1170 "include/linux/fs.h"
struct export_operations {
 struct dentry *(*decode_fh)(struct super_block *sb, __u32 *fh, int fh_len, int fh_type,
    int (*acceptable)(void *context, struct dentry *de),
    void *context);
 int (*encode_fh)(struct dentry *de, __u32 *fh, int *max_len,
    int connectable);


 int (*get_name)(struct dentry *parent, char *name,
   struct dentry *child);
 struct dentry * (*get_parent)(struct dentry *child);
 struct dentry * (*get_dentry)(struct super_block *sb, void *inump);


 struct dentry * (*find_exported_dentry)(
  struct super_block *sb, void *obj, void *parent,
  int (*acceptable)(void *context, struct dentry *de),
  void *context);


};

extern struct dentry *
find_exported_dentry(struct super_block *sb, void *obj, void *parent,
       int (*acceptable)(void *context, struct dentry *de),
       void *context);

struct file_system_type {
 const char *name;
 int fs_flags;
 struct super_block *(*get_sb) (struct file_system_type *, int,
           const char *, void *);
 void (*kill_sb) (struct super_block *);
 struct module *owner;
 struct file_system_type * next;
 struct list_head fs_supers;
};

struct super_block *get_sb_bdev(struct file_system_type *fs_type,
 int flags, const char *dev_name, void *data,
 int (*fill_super)(struct super_block *, void *, int));
struct super_block *get_sb_single(struct file_system_type *fs_type,
 int flags, void *data,
 int (*fill_super)(struct super_block *, void *, int));
struct super_block *get_sb_nodev(struct file_system_type *fs_type,
 int flags, void *data,
 int (*fill_super)(struct super_block *, void *, int));
void generic_shutdown_super(struct super_block *sb);
void kill_block_super(struct super_block *sb);
void kill_anon_super(struct super_block *sb);
void kill_litter_super(struct super_block *sb);
void deactivate_super(struct super_block *sb);
int set_anon_super(struct super_block *s, void *data);
struct super_block *sget(struct file_system_type *type,
   int (*test)(struct super_block *,void *),
   int (*set)(struct super_block *,void *),
   void *data);
struct super_block *get_sb_pseudo(struct file_system_type *, char *,
   struct super_operations *ops, unsigned long);
int __put_super(struct super_block *sb);
int __put_super_and_need_restart(struct super_block *sb);
void unnamed_dev_init(void);







extern int register_filesystem(struct file_system_type *);
extern int unregister_filesystem(struct file_system_type *);
extern struct vfsmount *kern_mount(struct file_system_type *);
extern int may_umount_tree(struct vfsmount *);
extern int may_umount(struct vfsmount *);
extern long do_mount(char *, char *, char *, unsigned long, void *);

extern int vfs_statfs(struct super_block *, struct kstatfs *);




extern int locks_mandatory_locked(struct inode *);
extern int locks_mandatory_area(int, struct inode *, struct file *, loff_t, size_t);
# 1261 "include/linux/fs.h"
static inline __attribute__((always_inline)) int locks_verify_locked(struct inode *inode)
{
 if ((((inode)->i_sb->s_flags & (64)) && ((inode)->i_mode & (0002000 | 00010)) == 0002000))
  return locks_mandatory_locked(inode);
 return 0;
}

extern int rw_verify_area(int, struct file *, loff_t *, size_t);

static inline __attribute__((always_inline)) int locks_verify_truncate(struct inode *inode,
        struct file *filp,
        loff_t size)
{
 if (inode->i_flock && (((inode)->i_sb->s_flags & (64)) && ((inode)->i_mode & (0002000 | 00010)) == 0002000))
  return locks_mandatory_area(
   2, inode, filp,
   size < inode->i_size ? size : inode->i_size,
   (size < inode->i_size ? inode->i_size - size
    : size - inode->i_size)
  );
 return 0;
}

static inline __attribute__((always_inline)) int break_lease(struct inode *inode, unsigned int mode)
{
 if (inode->i_flock)
  return __break_lease(inode, mode);
 return 0;
}



extern int do_truncate(struct dentry *, loff_t start);
extern struct file *filp_open(const char *, int, int);
extern struct file * dentry_open(struct dentry *, struct vfsmount *, int);
extern int filp_close(struct file *, fl_owner_t id);
extern char * getname(const char *);


extern void __attribute__ ((__section__ (".init.text"))) vfs_caches_init_early(void);
extern void __attribute__ ((__section__ (".init.text"))) vfs_caches_init(unsigned long);






extern void putname(const char *name);


extern int register_blkdev(unsigned int, const char *);
extern int unregister_blkdev(unsigned int, const char *);
extern struct block_device *bdget(dev_t);
extern void bd_set_size(struct block_device *, loff_t size);
extern void bd_forget(struct inode *inode);
extern void bdput(struct block_device *);
extern struct block_device *open_by_devnum(dev_t, unsigned);
extern struct file_operations def_blk_fops;
extern struct address_space_operations def_blk_aops;
extern struct file_operations def_chr_fops;
extern struct file_operations bad_sock_fops;
extern struct file_operations def_fifo_fops;
extern int ioctl_by_bdev(struct block_device *, unsigned, unsigned long);
extern int blkdev_ioctl(struct inode *, struct file *, unsigned, unsigned long);
extern long compat_blkdev_ioctl(struct file *, unsigned, unsigned long);
extern int blkdev_get(struct block_device *, mode_t, unsigned);
extern int blkdev_put(struct block_device *);
extern int bd_claim(struct block_device *, void *);
extern void bd_release(struct block_device *);


extern int alloc_chrdev_region(dev_t *, unsigned, unsigned, const char *);
extern int register_chrdev_region(dev_t, unsigned, const char *);
extern int register_chrdev(unsigned int, const char *,
      struct file_operations *);
extern int unregister_chrdev(unsigned int, const char *);
extern void unregister_chrdev_region(dev_t, unsigned);
extern int chrdev_open(struct inode *, struct file *);



extern const char *__bdevname(dev_t, char *buffer);
extern const char *bdevname(struct block_device *bdev, char *buffer);
extern struct block_device *lookup_bdev(const char *);
extern struct block_device *open_bdev_excl(const char *, int, void *);
extern void close_bdev_excl(struct block_device *);

extern void init_special_inode(struct inode *, umode_t, dev_t);


extern void make_bad_inode(struct inode *);
extern int is_bad_inode(struct inode *);

extern struct file_operations read_fifo_fops;
extern struct file_operations write_fifo_fops;
extern struct file_operations rdwr_fifo_fops;
extern struct file_operations read_pipe_fops;
extern struct file_operations write_pipe_fops;
extern struct file_operations rdwr_pipe_fops;

extern int fs_may_remount_ro(struct super_block *);
# 1373 "include/linux/fs.h"
extern int check_disk_change(struct block_device *);
extern int invalidate_inodes(struct super_block *);
extern int __invalidate_device(struct block_device *);
extern int invalidate_partition(struct gendisk *, int);
unsigned long invalidate_mapping_pages(struct address_space *mapping,
     unsigned long start, unsigned long end);
unsigned long invalidate_inode_pages(struct address_space *mapping);
static inline __attribute__((always_inline)) void invalidate_remote_inode(struct inode *inode)
{
 if ((((inode->i_mode) & 00170000) == 0100000) || (((inode->i_mode) & 00170000) == 0040000) ||
     (((inode->i_mode) & 00170000) == 0120000))
  invalidate_inode_pages(inode->i_mapping);
}
extern int invalidate_inode_pages2(struct address_space *mapping);
extern int invalidate_inode_pages2_range(struct address_space *mapping,
      unsigned long start, unsigned long end);
extern int write_inode_now(struct inode *, int);
extern int filemap_fdatawrite(struct address_space *);
extern int filemap_flush(struct address_space *);
extern int filemap_fdatawait(struct address_space *);
extern int filemap_write_and_wait(struct address_space *mapping);
extern int filemap_write_and_wait_range(struct address_space *mapping,
            loff_t lstart, loff_t lend);
extern void sync_supers(void);
extern void sync_filesystems(int wait);
extern void emergency_sync(void);
extern void emergency_remount(void);
extern int do_remount_sb(struct super_block *sb, int flags,
    void *data, int force);
extern sector_t bmap(struct inode *, sector_t);
extern int notify_change(struct dentry *, struct iattr *);
extern int permission(struct inode *, int, struct nameidata *);
extern int generic_permission(struct inode *, int,
  int (*check_acl)(struct inode *, int));

extern int get_write_access(struct inode *);
extern int deny_write_access(struct file *);
static inline __attribute__((always_inline)) void put_write_access(struct inode * inode)
{
 atomic_dec(&inode->i_writecount);
}
static inline __attribute__((always_inline)) void allow_write_access(struct file *file)
{
 if (file)
  atomic_inc(&file->f_dentry->d_inode->i_writecount);
}
extern int do_pipe(int *);

extern int open_namei(const char *, int, int, struct nameidata *);
extern int may_open(struct nameidata *, int, int);

extern int kernel_read(struct file *, unsigned long, char *, unsigned long);
extern struct file * open_exec(const char *);


extern int is_subdir(struct dentry *, struct dentry *);
extern ino_t find_inode_number(struct dentry *, struct qstr *);

# 1 "include/linux/err.h" 1
# 18 "include/linux/err.h"
static inline __attribute__((always_inline)) void *ERR_PTR(long error)
{
 return (void *) error;
}

static inline __attribute__((always_inline)) long PTR_ERR(const void *ptr)
{
 return (long) ptr;
}

static inline __attribute__((always_inline)) long IS_ERR(const void *ptr)
{
 return __builtin_expect(!!(((unsigned long)ptr) > (unsigned long)-1000L), 0);
}
# 1432 "include/linux/fs.h" 2


extern loff_t default_llseek(struct file *file, loff_t offset, int origin);

extern loff_t vfs_llseek(struct file *file, loff_t offset, int origin);

extern void inode_init_once(struct inode *);
extern void iput(struct inode *);
extern struct inode * igrab(struct inode *);
extern ino_t iunique(struct super_block *, ino_t);
extern int inode_needs_sync(struct inode *inode);
extern void generic_delete_inode(struct inode *inode);
extern void generic_drop_inode(struct inode *inode);

extern struct inode *ilookup5_nowait(struct super_block *sb,
  unsigned long hashval, int (*test)(struct inode *, void *),
  void *data);
extern struct inode *ilookup5(struct super_block *sb, unsigned long hashval,
  int (*test)(struct inode *, void *), void *data);
extern struct inode *ilookup(struct super_block *sb, unsigned long ino);

extern struct inode * iget5_locked(struct super_block *, unsigned long, int (*test)(struct inode *, void *), int (*set)(struct inode *, void *), void *);
extern struct inode * iget_locked(struct super_block *, unsigned long);
extern void unlock_new_inode(struct inode *);

static inline __attribute__((always_inline)) struct inode *iget(struct super_block *sb, unsigned long ino)
{
 struct inode *inode = iget_locked(sb, ino);

 if (inode && (inode->i_state & 64)) {
  sb->s_op->read_inode(inode);
  unlock_new_inode(inode);
 }

 return inode;
}

extern void __iget(struct inode * inode);
extern void clear_inode(struct inode *);
extern void destroy_inode(struct inode *);
extern struct inode *new_inode(struct super_block *);
extern int remove_suid(struct dentry *);
extern void remove_dquot_ref(struct super_block *, int, struct list_head *);
extern struct semaphore iprune_sem;

extern void __insert_inode_hash(struct inode *, unsigned long hashval);
extern void remove_inode_hash(struct inode *);
static inline __attribute__((always_inline)) void insert_inode_hash(struct inode *inode) {
 __insert_inode_hash(inode, inode->i_ino);
}

extern struct file * get_empty_filp(void);
extern void file_move(struct file *f, struct list_head *list);
extern void file_kill(struct file *f);
struct bio;
extern void submit_bio(int, struct bio *);
extern int bdev_read_only(struct block_device *);
extern int set_blocksize(struct block_device *, int);
extern int sb_set_blocksize(struct super_block *, int);
extern int sb_min_blocksize(struct super_block *, int);

extern int generic_file_mmap(struct file *, struct vm_area_struct *);
extern int generic_file_readonly_mmap(struct file *, struct vm_area_struct *);
extern int file_read_actor(read_descriptor_t * desc, struct page *page, unsigned long offset, unsigned long size);
extern int file_send_actor(read_descriptor_t * desc, struct page *page, unsigned long offset, unsigned long size);
extern ssize_t generic_file_read(struct file *, char *, size_t, loff_t *);
int generic_write_checks(struct file *file, loff_t *pos, size_t *count, int isblk);
extern ssize_t generic_file_write(struct file *, const char *, size_t, loff_t *);
extern ssize_t generic_file_aio_read(struct kiocb *, char *, size_t, loff_t);
extern ssize_t __generic_file_aio_read(struct kiocb *, const struct iovec *, unsigned long, loff_t *);
extern ssize_t generic_file_aio_write(struct kiocb *, const char *, size_t, loff_t);
extern ssize_t generic_file_aio_write_nolock(struct kiocb *, const struct iovec *,
  unsigned long, loff_t *);
extern ssize_t generic_file_direct_write(struct kiocb *, const struct iovec *,
  unsigned long *, loff_t, loff_t *, size_t, size_t);
extern ssize_t generic_file_buffered_write(struct kiocb *, const struct iovec *,
  unsigned long, loff_t, loff_t *, size_t, ssize_t);
extern ssize_t do_sync_read(struct file *filp, char *buf, size_t len, loff_t *ppos);
extern ssize_t do_sync_write(struct file *filp, const char *buf, size_t len, loff_t *ppos);
ssize_t generic_file_write_nolock(struct file *file, const struct iovec *iov,
    unsigned long nr_segs, loff_t *ppos);
extern ssize_t generic_file_sendfile(struct file *, loff_t *, size_t, read_actor_t, void *);
extern void do_generic_mapping_read(struct address_space *mapping,
        struct file_ra_state *, struct file *,
        loff_t *, read_descriptor_t *, read_actor_t);
extern void
file_ra_state_init(struct file_ra_state *ra, struct address_space *mapping);
extern ssize_t generic_file_direct_IO(int rw, struct kiocb *iocb,
 const struct iovec *iov, loff_t offset, unsigned long nr_segs);
extern ssize_t generic_file_readv(struct file *filp, const struct iovec *iov,
 unsigned long nr_segs, loff_t *ppos);
ssize_t generic_file_writev(struct file *filp, const struct iovec *iov,
   unsigned long nr_segs, loff_t *ppos);
extern loff_t no_llseek(struct file *file, loff_t offset, int origin);
extern loff_t generic_file_llseek(struct file *file, loff_t offset, int origin);
extern loff_t remote_llseek(struct file *file, loff_t offset, int origin);
extern int generic_file_open(struct inode * inode, struct file * filp);
extern int nonseekable_open(struct inode * inode, struct file * filp);


extern ssize_t xip_file_read(struct file *filp, char *buf, size_t len,
        loff_t *ppos);
extern ssize_t xip_file_sendfile(struct file *in_file, loff_t *ppos,
     size_t count, read_actor_t actor,
     void *target);
extern int xip_file_mmap(struct file * file, struct vm_area_struct * vma);
extern ssize_t xip_file_write(struct file *filp, const char *buf,
         size_t len, loff_t *ppos);
extern int xip_truncate_page(struct address_space *mapping, loff_t from);







static inline __attribute__((always_inline)) void do_generic_file_read(struct file * filp, loff_t *ppos,
     read_descriptor_t * desc,
     read_actor_t actor)
{
 do_generic_mapping_read(filp->f_mapping,
    &filp->f_ra,
    filp,
    ppos,
    desc,
    actor);
}

ssize_t __blockdev_direct_IO(int rw, struct kiocb *iocb, struct inode *inode,
 struct block_device *bdev, const struct iovec *iov, loff_t offset,
 unsigned long nr_segs, get_blocks_t get_blocks, dio_iodone_t end_io,
 int lock_type);

enum {
 DIO_LOCKING = 1,
 DIO_NO_LOCKING,
 DIO_OWN_LOCKING,
};

static inline __attribute__((always_inline)) ssize_t blockdev_direct_IO(int rw, struct kiocb *iocb,
 struct inode *inode, struct block_device *bdev, const struct iovec *iov,
 loff_t offset, unsigned long nr_segs, get_blocks_t get_blocks,
 dio_iodone_t end_io)
{
 return __blockdev_direct_IO(rw, iocb, inode, bdev, iov, offset,
    nr_segs, get_blocks, end_io, DIO_LOCKING);
}

static inline __attribute__((always_inline)) ssize_t blockdev_direct_IO_no_locking(int rw, struct kiocb *iocb,
 struct inode *inode, struct block_device *bdev, const struct iovec *iov,
 loff_t offset, unsigned long nr_segs, get_blocks_t get_blocks,
 dio_iodone_t end_io)
{
 return __blockdev_direct_IO(rw, iocb, inode, bdev, iov, offset,
    nr_segs, get_blocks, end_io, DIO_NO_LOCKING);
}

static inline __attribute__((always_inline)) ssize_t blockdev_direct_IO_own_locking(int rw, struct kiocb *iocb,
 struct inode *inode, struct block_device *bdev, const struct iovec *iov,
 loff_t offset, unsigned long nr_segs, get_blocks_t get_blocks,
 dio_iodone_t end_io)
{
 return __blockdev_direct_IO(rw, iocb, inode, bdev, iov, offset,
    nr_segs, get_blocks, end_io, DIO_OWN_LOCKING);
}

extern struct file_operations generic_ro_fops;



extern int vfs_readlink(struct dentry *, char *, int, const char *);
extern int vfs_follow_link(struct nameidata *, const char *);
extern int page_readlink(struct dentry *, char *, int);
extern void *page_follow_link_light(struct dentry *, struct nameidata *);
extern void page_put_link(struct dentry *, struct nameidata *, void *);
extern int page_symlink(struct inode *inode, const char *symname, int len);
extern struct inode_operations page_symlink_inode_operations;
extern int generic_readlink(struct dentry *, char *, int);
extern void generic_fillattr(struct inode *, struct kstat *);
extern int vfs_getattr(struct vfsmount *, struct dentry *, struct kstat *);
void inode_add_bytes(struct inode *inode, loff_t bytes);
void inode_sub_bytes(struct inode *inode, loff_t bytes);
loff_t inode_get_bytes(struct inode *inode);
void inode_set_bytes(struct inode *inode, loff_t bytes);

extern int vfs_readdir(struct file *, filldir_t, void *);

extern int vfs_stat(char *, struct kstat *);
extern int vfs_lstat(char *, struct kstat *);
extern int vfs_fstat(unsigned int, struct kstat *);

extern int vfs_ioctl(struct file *, unsigned int, unsigned int, unsigned long);

extern struct file_system_type *get_fs_type(const char *name);
extern struct super_block *get_super(struct block_device *);
extern struct super_block *user_get_super(dev_t);
extern void drop_super(struct super_block *sb);

extern int dcache_dir_open(struct inode *, struct file *);
extern int dcache_dir_close(struct inode *, struct file *);
extern loff_t dcache_dir_lseek(struct file *, loff_t, int);
extern int dcache_readdir(struct file *, void *, filldir_t);
extern int simple_getattr(struct vfsmount *, struct dentry *, struct kstat *);
extern int simple_statfs(struct super_block *, struct kstatfs *);
extern int simple_link(struct dentry *, struct inode *, struct dentry *);
extern int simple_unlink(struct inode *, struct dentry *);
extern int simple_rmdir(struct inode *, struct dentry *);
extern int simple_rename(struct inode *, struct dentry *, struct inode *, struct dentry *);
extern int simple_sync_file(struct file *, struct dentry *, int);
extern int simple_empty(struct dentry *);
extern int simple_readpage(struct file *file, struct page *page);
extern int simple_prepare_write(struct file *file, struct page *page,
   unsigned offset, unsigned to);
extern int simple_commit_write(struct file *file, struct page *page,
    unsigned offset, unsigned to);

extern struct dentry *simple_lookup(struct inode *, struct dentry *, struct nameidata *);
extern ssize_t generic_read_dir(struct file *, char *, size_t, loff_t *);
extern struct file_operations simple_dir_operations;
extern struct inode_operations simple_dir_inode_operations;
struct tree_descr { char *name; struct file_operations *ops; int mode; };
struct dentry *d_alloc_name(struct dentry *, const char *);
extern int simple_fill_super(struct super_block *, int, struct tree_descr *);
extern int simple_pin_fs(char *name, struct vfsmount **mount, int *count);
extern void simple_release_fs(struct vfsmount **mount, int *count);

extern ssize_t simple_read_from_buffer(void *, size_t, loff_t *, const void *, size_t);

extern int inode_change_ok(struct inode *, struct iattr *);
extern int __attribute__((warn_unused_result)) inode_setattr(struct inode *, struct iattr *);

extern void inode_update_time(struct inode *inode, int ctime_too);

static inline __attribute__((always_inline)) ino_t parent_ino(struct dentry *dentry)
{
 ino_t res;

 _spin_lock(&dentry->d_lock);
 res = dentry->d_parent->d_inode->i_ino;
 _spin_unlock(&dentry->d_lock);
 return res;
}


extern int unshare_files(void);







struct simple_transaction_argresp {
 ssize_t size;
 char data[0];
};



char *simple_transaction_get(struct file *file, const char *buf,
    size_t size);
ssize_t simple_transaction_read(struct file *file, char *buf,
    size_t size, loff_t *pos);
int simple_transaction_release(struct inode *inode, struct file *file);

static inline __attribute__((always_inline)) void simple_transaction_set(struct file *file, size_t n)
{
 struct simple_transaction_argresp *ar = file->private_data;

 do { if (__builtin_expect(!!((n > ((1UL << 12) - sizeof(struct simple_transaction_argresp)))!=0), 0)) __BUG(); } while(0);





 asm volatile ("661:\n\t" "lock; addl $0,0(%%esp)" "\n662:\n" ".section .altinstructions,\"a\"\n" "  .align 4\n" "  .long 661b\n" "  .long 663f\n" "  .byte %c0\n" "  .byte 662b-661b\n" "  .byte 664f-663f\n" ".previous\n" ".section .altinstr_replacement,\"ax\"\n" "663:\n\t" "mfence" "\n664:\n" ".previous" :: "i" ((0*32+26)) : "memory");
 ar->size = n;
}
# 1741 "include/linux/fs.h"
static inline __attribute__((always_inline)) void __attribute__((format(printf, 1, 2)))
__simple_attr_check_format(const char *fmt, ...)
{

}

int simple_attr_open(struct inode *inode, struct file *file,
       u64 (*get)(void *), void (*set)(void *, u64),
       const char *fmt);
int simple_attr_close(struct inode *inode, struct file *file);
ssize_t simple_attr_read(struct file *file, char *buf,
    size_t len, loff_t *ppos);
ssize_t simple_attr_write(struct file *file, const char *buf,
     size_t len, loff_t *ppos);



static inline __attribute__((always_inline)) char *alloc_secdata(void)
{
 return (char *)get_zeroed_page((0x10u | 0x40u | 0x80u));
}

static inline __attribute__((always_inline)) void free_secdata(void *secdata)
{
 free_pages(((unsigned long)secdata),0);
}
# 16 "include/linux/mm.h" 2

struct mempolicy;
struct anon_vma;


extern unsigned long max_mapnr;


extern unsigned long num_physpages;
extern void * high_memory;
extern unsigned long vmalloc_earlyreserve;
extern int page_cluster;


extern int sysctl_legacy_va_layout;





# 1 "include/asm/pgtable.h" 1
# 33 "include/asm/pgtable.h"
extern unsigned long empty_zero_page[1024];
extern pgd_t swapper_pg_dir[1024];
extern kmem_cache_t *pgd_cache;
extern kmem_cache_t *pmd_cache;
extern spinlock_t pgd_lock;
extern struct page *pgd_list;

void pmd_ctor(void *, kmem_cache_t *, unsigned long);
void pgd_ctor(void *, kmem_cache_t *, unsigned long);
void pgd_dtor(void *, kmem_cache_t *, unsigned long);
void pgtable_cache_init(void);
void paging_init(void);
# 56 "include/asm/pgtable.h"
# 1 "include/asm/pgtable-2level-defs.h" 1
# 57 "include/asm/pgtable.h" 2
# 157 "include/asm/pgtable.h"
extern unsigned long long __PAGE_KERNEL, __PAGE_KERNEL_EXEC;
# 201 "include/asm/pgtable.h"
extern unsigned long pg0[];
# 218 "include/asm/pgtable.h"
static inline __attribute__((always_inline)) int pte_user(pte_t pte) { return (pte).pte_low & 0x004; }
static inline __attribute__((always_inline)) int pte_read(pte_t pte) { return (pte).pte_low & 0x004; }
static inline __attribute__((always_inline)) int pte_dirty(pte_t pte) { return (pte).pte_low & 0x040; }
static inline __attribute__((always_inline)) int pte_young(pte_t pte) { return (pte).pte_low & 0x020; }
static inline __attribute__((always_inline)) int pte_write(pte_t pte) { return (pte).pte_low & 0x002; }




static inline __attribute__((always_inline)) int pte_file(pte_t pte) { return (pte).pte_low & 0x040; }

static inline __attribute__((always_inline)) pte_t pte_rdprotect(pte_t pte) { (pte).pte_low &= ~0x004; return pte; }
static inline __attribute__((always_inline)) pte_t pte_exprotect(pte_t pte) { (pte).pte_low &= ~0x004; return pte; }
static inline __attribute__((always_inline)) pte_t pte_mkclean(pte_t pte) { (pte).pte_low &= ~0x040; return pte; }
static inline __attribute__((always_inline)) pte_t pte_mkold(pte_t pte) { (pte).pte_low &= ~0x020; return pte; }
static inline __attribute__((always_inline)) pte_t pte_wrprotect(pte_t pte) { (pte).pte_low &= ~0x002; return pte; }
static inline __attribute__((always_inline)) pte_t pte_mkread(pte_t pte) { (pte).pte_low |= 0x004; return pte; }
static inline __attribute__((always_inline)) pte_t pte_mkexec(pte_t pte) { (pte).pte_low |= 0x004; return pte; }
static inline __attribute__((always_inline)) pte_t pte_mkdirty(pte_t pte) { (pte).pte_low |= 0x040; return pte; }
static inline __attribute__((always_inline)) pte_t pte_mkyoung(pte_t pte) { (pte).pte_low |= 0x020; return pte; }
static inline __attribute__((always_inline)) pte_t pte_mkwrite(pte_t pte) { (pte).pte_low |= 0x002; return pte; }
static inline __attribute__((always_inline)) pte_t pte_mkhuge(pte_t pte) { (pte).pte_low |= 0x001 | 0x080; return pte; }




# 1 "include/asm/pgtable-2level.h" 1



# 1 "include/asm-generic/pgtable-nopmd.h" 1





# 1 "include/asm-generic/pgtable-nopud.h" 1
# 13 "include/asm-generic/pgtable-nopud.h"
typedef struct { pgd_t pgd; } pud_t;
# 25 "include/asm-generic/pgtable-nopud.h"
static inline __attribute__((always_inline)) int pgd_none(pgd_t pgd) { return 0; }
static inline __attribute__((always_inline)) int pgd_bad(pgd_t pgd) { return 0; }
static inline __attribute__((always_inline)) int pgd_present(pgd_t pgd) { return 1; }
static inline __attribute__((always_inline)) void pgd_clear(pgd_t *pgd) { }
# 38 "include/asm-generic/pgtable-nopud.h"
static inline __attribute__((always_inline)) pud_t * pud_offset(pgd_t * pgd, unsigned long address)
{
 return (pud_t *)pgd;
}
# 7 "include/asm-generic/pgtable-nopmd.h" 2
# 15 "include/asm-generic/pgtable-nopmd.h"
typedef struct { pud_t pud; } pmd_t;
# 27 "include/asm-generic/pgtable-nopmd.h"
static inline __attribute__((always_inline)) int pud_none(pud_t pud) { return 0; }
static inline __attribute__((always_inline)) int pud_bad(pud_t pud) { return 0; }
static inline __attribute__((always_inline)) int pud_present(pud_t pud) { return 1; }
static inline __attribute__((always_inline)) void pud_clear(pud_t *pud) { }
# 41 "include/asm-generic/pgtable-nopmd.h"
static inline __attribute__((always_inline)) pmd_t * pmd_offset(pud_t * pud, unsigned long address)
{
 return (pmd_t *)pud;
}
# 5 "include/asm/pgtable-2level.h" 2
# 37 "include/asm/pgtable-2level.h"
static inline __attribute__((always_inline)) int pte_exec(pte_t pte)
{
 return pte_user(pte);
}




static inline __attribute__((always_inline)) int pte_exec_kernel(pte_t pte)
{
 return 1;
}
# 245 "include/asm/pgtable.h" 2


static inline __attribute__((always_inline)) int ptep_test_and_clear_dirty(struct vm_area_struct *vma, unsigned long addr, pte_t *ptep)
{
 if (!pte_dirty(*ptep))
  return 0;
 return test_and_clear_bit(6, &ptep->pte_low);
}

static inline __attribute__((always_inline)) int ptep_test_and_clear_young(struct vm_area_struct *vma, unsigned long addr, pte_t *ptep)
{
 if (!pte_young(*ptep))
  return 0;
 return test_and_clear_bit(5, &ptep->pte_low);
}

static inline __attribute__((always_inline)) void ptep_set_wrprotect(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
{
 clear_bit(1, &ptep->pte_low);
}
# 280 "include/asm/pgtable.h"
static inline __attribute__((always_inline)) pte_t pte_modify(pte_t pte, pgprot_t newprot)
{
 pte.pte_low &= ((~((1UL << 12)-1)) | 0x020 | 0x040);
 pte.pte_low |= ((newprot).pgprot);
# 293 "include/asm/pgtable.h"
 return pte;
}
# 348 "include/asm/pgtable.h"
extern pte_t *lookup_address(unsigned long address);
# 359 "include/asm/pgtable.h"
 static inline __attribute__((always_inline)) int set_kernel_exec(unsigned long vaddr, int enable) { return 0;}


extern void noexec_setup(const char *str);
# 420 "include/asm/pgtable.h"
# 1 "include/asm-generic/pgtable.h" 1
# 176 "include/asm-generic/pgtable.h"
void pgd_clear_bad(pgd_t *);
void pud_clear_bad(pud_t *);
void pmd_clear_bad(pmd_t *);

static inline __attribute__((always_inline)) int pgd_none_or_clear_bad(pgd_t *pgd)
{
 if (pgd_none(*pgd))
  return 1;
 if (__builtin_expect(!!(pgd_bad(*pgd)), 0)) {
  pgd_clear_bad(pgd);
  return 1;
 }
 return 0;
}

static inline __attribute__((always_inline)) int pud_none_or_clear_bad(pud_t *pud)
{
 if (pud_none(*pud))
  return 1;
 if (__builtin_expect(!!(pud_bad(*pud)), 0)) {
  pud_clear_bad(pud);
  return 1;
 }
 return 0;
}

static inline __attribute__((always_inline)) int pmd_none_or_clear_bad(pmd_t *pmd)
{
 if ((!((((((*pmd).pud).pgd).pgd)))))
  return 1;
 if (__builtin_expect(!!(((((((((*pmd).pud).pgd).pgd))) & (~(~((1UL << 12)-1)) & ~0x004)) != (0x001 | 0x002 | 0x020 | 0x040))), 0)) {
  pmd_clear_bad(pmd);
  return 1;
 }
 return 0;
}
# 421 "include/asm/pgtable.h" 2
# 37 "include/linux/mm.h" 2
# 57 "include/linux/mm.h"
struct vm_area_struct {
 struct mm_struct * vm_mm;
 unsigned long vm_start;
 unsigned long vm_end;



 struct vm_area_struct *vm_next;

 pgprot_t vm_page_prot;
 unsigned long vm_flags;

 struct rb_node vm_rb;







 union {
  struct {
   struct list_head list;
   void *parent;
   struct vm_area_struct *head;
  } vm_set;

  struct raw_prio_tree_node prio_tree_node;
 } shared;







 struct list_head anon_vma_node;
 struct anon_vma *anon_vma;


 struct vm_operations_struct * vm_ops;


 unsigned long vm_pgoff;

 struct file * vm_file;
 void * vm_private_data;
 unsigned long vm_truncate_count;







};






struct vm_list_struct {
 struct vm_list_struct *next;
 struct vm_area_struct *vma;
};
# 185 "include/linux/mm.h"
extern pgprot_t protection_map[16];







struct vm_operations_struct {
 void (*open)(struct vm_area_struct * area);
 void (*close)(struct vm_area_struct * area);
 struct page * (*nopage)(struct vm_area_struct * area, unsigned long address, int *type);
 int (*populate)(struct vm_area_struct * area, unsigned long address, unsigned long len, pgprot_t prot, unsigned long pgoff, int nonblock);





};

struct mmu_gather;
struct inode;




typedef unsigned long page_flags_t;
# 220 "include/linux/mm.h"
struct page {
 page_flags_t flags;

 atomic_t _count;
 atomic_t _mapcount;



 unsigned long private;






 struct address_space *mapping;






 unsigned long index;
 struct list_head lru;
# 260 "include/linux/mm.h"
};





# 1 "include/linux/page-flags.h" 1
# 83 "include/linux/page-flags.h"
struct page_state {
 unsigned long nr_dirty;
 unsigned long nr_writeback;
 unsigned long nr_unstable;
 unsigned long nr_page_table_pages;
 unsigned long nr_mapped;
 unsigned long nr_slab;






 unsigned long pgpgin;
 unsigned long pgpgout;
 unsigned long pswpin;
 unsigned long pswpout;
 unsigned long pgalloc_high;

 unsigned long pgalloc_normal;
 unsigned long pgalloc_dma;
 unsigned long pgfree;
 unsigned long pgactivate;
 unsigned long pgdeactivate;

 unsigned long pgfault;
 unsigned long pgmajfault;
 unsigned long pgrefill_high;
 unsigned long pgrefill_normal;
 unsigned long pgrefill_dma;

 unsigned long pgsteal_high;
 unsigned long pgsteal_normal;
 unsigned long pgsteal_dma;
 unsigned long pgscan_kswapd_high;
 unsigned long pgscan_kswapd_normal;

 unsigned long pgscan_kswapd_dma;
 unsigned long pgscan_direct_high;
 unsigned long pgscan_direct_normal;
 unsigned long pgscan_direct_dma;
 unsigned long pginodesteal;

 unsigned long slabs_scanned;
 unsigned long kswapd_steal;
 unsigned long kswapd_inodesteal;
 unsigned long pageoutrun;
 unsigned long allocstall;

 unsigned long pgrotated;
 unsigned long nr_bounce;
};

extern void get_page_state(struct page_state *ret);
extern void get_full_page_state(struct page_state *ret);
extern unsigned long __read_page_state(unsigned long offset);
extern void __mod_page_state(unsigned long offset, unsigned long delta);
# 308 "include/linux/page-flags.h"
struct page;

int test_clear_page_dirty(struct page *page);
int test_clear_page_writeback(struct page *page);
int test_set_page_writeback(struct page *page);

static inline __attribute__((always_inline)) void clear_page_dirty(struct page *page)
{
 test_clear_page_dirty(page);
}

static inline __attribute__((always_inline)) void set_page_writeback(struct page *page)
{
 test_set_page_writeback(page);
}
# 267 "include/linux/mm.h" 2
# 309 "include/linux/mm.h"
extern void __page_cache_release(struct page *) __attribute__((regparm(3)));



static inline __attribute__((always_inline)) int page_count(struct page *p)
{
 if ((__builtin_constant_p(14) ? constant_test_bit((14),(&(p)->flags)) : variable_test_bit((14),(&(p)->flags))))
  p = (struct page *)p->private;
 return ((&(p)->_count)->counter) + 1;
}

static inline __attribute__((always_inline)) void get_page(struct page *page)
{
 if (__builtin_expect(!!((__builtin_constant_p(14) ? constant_test_bit((14),(&(page)->flags)) : variable_test_bit((14),(&(page)->flags)))), 0))
  page = (struct page *)page->private;
 atomic_inc(&page->_count);
}

void put_page(struct page *page);
# 470 "include/linux/mm.h"
static inline __attribute__((always_inline)) unsigned long page_zonenum(struct page *page)
{
 return (page->flags >> (((((sizeof(page_flags_t)*8) - 0) - 0) - 2) * (2 != 0))) & ((1UL << 2) - 1);
}

struct zone;
extern struct zone *zone_table[];

static inline __attribute__((always_inline)) struct zone *page_zone(struct page *page)
{
 return zone_table[(page->flags >> (((((sizeof(page_flags_t)*8) - 0) - 0) - 2) * (2 != 0))) &
   ((1UL << (0 + 2)) - 1)];
}

static inline __attribute__((always_inline)) unsigned long page_to_nid(struct page *page)
{
 if ((0 > 0 || 0 == 0))
  return (page->flags >> ((((sizeof(page_flags_t)*8) - 0) - 0) * (0 != 0))) & ((1UL << 0) - 1);
 else
  return page_zone(page)->zone_pgdat->node_id;
}
static inline __attribute__((always_inline)) unsigned long page_to_section(struct page *page)
{
 return (page->flags >> (((sizeof(page_flags_t)*8) - 0) * (0 != 0))) & ((1UL << 0) - 1);
}

static inline __attribute__((always_inline)) void set_page_zone(struct page *page, unsigned long zone)
{
 page->flags &= ~(((1UL << 2) - 1) << (((((sizeof(page_flags_t)*8) - 0) - 0) - 2) * (2 != 0)));
 page->flags |= (zone & ((1UL << 2) - 1)) << (((((sizeof(page_flags_t)*8) - 0) - 0) - 2) * (2 != 0));
}
static inline __attribute__((always_inline)) void set_page_node(struct page *page, unsigned long node)
{
 page->flags &= ~(((1UL << 0) - 1) << ((((sizeof(page_flags_t)*8) - 0) - 0) * (0 != 0)));
 page->flags |= (node & ((1UL << 0) - 1)) << ((((sizeof(page_flags_t)*8) - 0) - 0) * (0 != 0));
}
static inline __attribute__((always_inline)) void set_page_section(struct page *page, unsigned long section)
{
 page->flags &= ~(((1UL << 0) - 1) << (((sizeof(page_flags_t)*8) - 0) * (0 != 0)));
 page->flags |= (section & ((1UL << 0) - 1)) << (((sizeof(page_flags_t)*8) - 0) * (0 != 0));
}

static inline __attribute__((always_inline)) void set_page_links(struct page *page, unsigned long zone,
 unsigned long node, unsigned long pfn)
{
 set_page_zone(page, zone);
 set_page_node(page, node);
 set_page_section(page, ((pfn) >> 0));
}



extern struct page *mem_map;


static inline __attribute__((always_inline)) void *lowmem_page_address(struct page *page)
{
 return ((void *)((unsigned long)(((unsigned long)((page) - mem_map)) << 12)+((unsigned long)(0xC0000000UL))));
}
# 566 "include/linux/mm.h"
extern struct address_space swapper_space;
static inline __attribute__((always_inline)) struct address_space *page_mapping(struct page *page)
{
 struct address_space *mapping = page->mapping;

 if (__builtin_expect(!!((__builtin_constant_p(15) ? constant_test_bit((15),(&(page)->flags)) : variable_test_bit((15),(&(page)->flags)))), 0))
  mapping = &swapper_space;
 else if (__builtin_expect(!!((unsigned long)mapping & 1), 0))
  mapping = ((void *)0);
 return mapping;
}

static inline __attribute__((always_inline)) int PageAnon(struct page *page)
{
 return ((unsigned long)page->mapping & 1) != 0;
}





static inline __attribute__((always_inline)) unsigned long page_index(struct page *page)
{
 if (__builtin_expect(!!((__builtin_constant_p(15) ? constant_test_bit((15),(&(page)->flags)) : variable_test_bit((15),(&(page)->flags)))), 0))
  return page->private;
 return page->index;
}






static inline __attribute__((always_inline)) void reset_page_mapcount(struct page *page)
{
 (((&(page)->_mapcount)->counter) = (-1));
}

static inline __attribute__((always_inline)) int page_mapcount(struct page *page)
{
 return ((&(page)->_mapcount)->counter) + 1;
}




static inline __attribute__((always_inline)) int page_mapped(struct page *page)
{
 return ((&(page)->_mapcount)->counter) >= 0;
}
# 641 "include/linux/mm.h"
extern void show_free_areas(void);


struct page *shmem_nopage(struct vm_area_struct *vma,
   unsigned long address, int *type);
int shmem_set_policy(struct vm_area_struct *vma, struct mempolicy *new);
struct mempolicy *shmem_get_policy(struct vm_area_struct *vma,
     unsigned long addr);
int shmem_lock(struct file *file, int lock, struct user_struct *user);






struct file *shmem_file_setup(char *name, loff_t size, unsigned long flags);

int shmem_zero_setup(struct vm_area_struct *);

static inline __attribute__((always_inline)) int can_do_mlock(void)
{
 if (capable(14))
  return 1;
 if (get_current()->signal->rlim[8].rlim_cur != 0)
  return 1;
 return 0;
}
extern int user_shm_lock(size_t, struct user_struct *);
extern void user_shm_unlock(size_t, struct user_struct *);




struct zap_details {
 struct vm_area_struct *nonlinear_vma;
 struct address_space *check_mapping;
 unsigned long first_index;
 unsigned long last_index;
 spinlock_t *i_mmap_lock;
 unsigned long truncate_count;
};

unsigned long zap_page_range(struct vm_area_struct *vma, unsigned long address,
  unsigned long size, struct zap_details *);
unsigned long unmap_vmas(struct mmu_gather **tlb, struct mm_struct *mm,
  struct vm_area_struct *start_vma, unsigned long start_addr,
  unsigned long end_addr, unsigned long *nr_accounted,
  struct zap_details *);
void free_pgd_range(struct mmu_gather **tlb, unsigned long addr,
  unsigned long end, unsigned long floor, unsigned long ceiling);
void free_pgtables(struct mmu_gather **tlb, struct vm_area_struct *start_vma,
  unsigned long floor, unsigned long ceiling);
int copy_page_range(struct mm_struct *dst, struct mm_struct *src,
   struct vm_area_struct *vma);
int zeromap_page_range(struct vm_area_struct *vma, unsigned long from,
   unsigned long size, pgprot_t prot);
void unmap_mapping_range(struct address_space *mapping,
  loff_t const holebegin, loff_t const holelen, int even_cows);

static inline __attribute__((always_inline)) void unmap_shared_mapping_range(struct address_space *mapping,
  loff_t const holebegin, loff_t const holelen)
{
 unmap_mapping_range(mapping, holebegin, holelen, 0);
}

extern int vmtruncate(struct inode * inode, loff_t offset);
extern pud_t *__pud_alloc(struct mm_struct *mm, pgd_t *pgd, unsigned long address) __attribute__((regparm(3)));
extern pmd_t *__pmd_alloc(struct mm_struct *mm, pud_t *pud, unsigned long address) __attribute__((regparm(3)));
extern pte_t *pte_alloc_kernel(struct mm_struct *mm, pmd_t *pmd, unsigned long address) __attribute__((regparm(3)));
extern pte_t *pte_alloc_map(struct mm_struct *mm, pmd_t *pmd, unsigned long address) __attribute__((regparm(3)));
extern int install_page(struct mm_struct *mm, struct vm_area_struct *vma, unsigned long addr, struct page *page, pgprot_t prot);
extern int install_file_pte(struct mm_struct *mm, struct vm_area_struct *vma, unsigned long addr, unsigned long pgoff, pgprot_t prot);
extern int __handle_mm_fault(struct mm_struct *mm,struct vm_area_struct *vma, unsigned long address, int write_access);

static inline __attribute__((always_inline)) int handle_mm_fault(struct mm_struct *mm, struct vm_area_struct *vma, unsigned long address, int write_access)
{
 return __handle_mm_fault(mm, vma, address, write_access) & (~0x10);
}

extern int make_pages_present(unsigned long addr, unsigned long end);
extern int access_process_vm(struct task_struct *tsk, unsigned long addr, void *buf, int len, int write);
void install_arg_page(struct vm_area_struct *, struct page *, unsigned long);

int get_user_pages(struct task_struct *tsk, struct mm_struct *mm, unsigned long start,
  int len, int write, int force, struct page **pages, struct vm_area_struct **vmas);

int __set_page_dirty_buffers(struct page *page);
int __set_page_dirty_nobuffers(struct page *page);
int redirty_page_for_writepage(struct writeback_control *wbc,
    struct page *page);
int set_page_dirty(struct page *page) __attribute__((regparm(3)));
int set_page_dirty_lock(struct page *page);
int clear_page_dirty_for_io(struct page *page);

extern unsigned long do_mremap(unsigned long addr,
          unsigned long old_len, unsigned long new_len,
          unsigned long flags, unsigned long new_addr);
# 750 "include/linux/mm.h"
typedef int (*shrinker_t)(int nr_to_scan, unsigned int gfp_mask);







struct shrinker;
extern struct shrinker *set_shrinker(int, shrinker_t);
extern void remove_shrinker(struct shrinker *shrinker);
# 773 "include/linux/mm.h"
static inline __attribute__((always_inline)) pud_t *pud_alloc(struct mm_struct *mm, pgd_t *pgd, unsigned long address)
{
 if (pgd_none(*pgd))
  return __pud_alloc(mm, pgd, address);
 return pud_offset(pgd, address);
}

static inline __attribute__((always_inline)) pmd_t *pmd_alloc(struct mm_struct *mm, pud_t *pud, unsigned long address)
{
 if (pud_none(*pud))
  return __pmd_alloc(mm, pud, address);
 return pmd_offset(pud, address);
}



extern void free_area_init(unsigned long * zones_size);
extern void free_area_init_node(int nid, pg_data_t *pgdat,
 unsigned long * zones_size, unsigned long zone_start_pfn,
 unsigned long *zholes_size);
extern void memmap_init_zone(unsigned long, int, unsigned long, unsigned long);
extern void mem_init(void);
extern void show_mem(void);
extern void si_meminfo(struct sysinfo * val);
extern void si_meminfo_node(struct sysinfo *val, int nid);




static inline __attribute__((always_inline)) void setup_per_cpu_pageset(void) {}



void vma_prio_tree_add(struct vm_area_struct *, struct vm_area_struct *old);
void vma_prio_tree_insert(struct vm_area_struct *, struct prio_tree_root *);
void vma_prio_tree_remove(struct vm_area_struct *, struct prio_tree_root *);
struct vm_area_struct *vma_prio_tree_next(struct vm_area_struct *vma,
 struct prio_tree_iter *iter);





static inline __attribute__((always_inline)) void vma_nonlinear_insert(struct vm_area_struct *vma,
     struct list_head *list)
{
 vma->shared.vm_set.parent = ((void *)0);
 list_add_tail(&vma->shared.vm_set.list, list);
}


extern int __vm_enough_memory(long pages, int cap_sys_admin);
extern void vma_adjust(struct vm_area_struct *vma, unsigned long start,
 unsigned long end, unsigned long pgoff, struct vm_area_struct *insert);
extern struct vm_area_struct *vma_merge(struct mm_struct *,
 struct vm_area_struct *prev, unsigned long addr, unsigned long end,
 unsigned long vm_flags, struct anon_vma *, struct file *, unsigned long,
 struct mempolicy *);
extern struct anon_vma *find_mergeable_anon_vma(struct vm_area_struct *);
extern int split_vma(struct mm_struct *,
 struct vm_area_struct *, unsigned long addr, int new_below);
extern int insert_vm_struct(struct mm_struct *, struct vm_area_struct *);
extern void __vma_link_rb(struct mm_struct *, struct vm_area_struct *,
 struct rb_node **, struct rb_node *);
extern struct vm_area_struct *copy_vma(struct vm_area_struct **,
 unsigned long addr, unsigned long len, unsigned long pgoff);
extern void exit_mmap(struct mm_struct *);
extern int may_expand_vm(struct mm_struct *mm, unsigned long npages);

extern unsigned long get_unmapped_area(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);

extern unsigned long do_mmap_pgoff(struct file *file, unsigned long addr,
 unsigned long len, unsigned long prot,
 unsigned long flag, unsigned long pgoff);

static inline __attribute__((always_inline)) unsigned long do_mmap(struct file *file, unsigned long addr,
 unsigned long len, unsigned long prot,
 unsigned long flag, unsigned long offset)
{
 unsigned long ret = -22;
 if ((offset + (((len)+(1UL << 12)-1)&(~((1UL << 12)-1)))) < offset)
  goto out;
 if (!(offset & ~(~((1UL << 12)-1))))
  ret = do_mmap_pgoff(file, addr, len, prot, flag, offset >> 12);
out:
 return ret;
}

extern int do_munmap(struct mm_struct *, unsigned long, size_t);

extern unsigned long do_brk(unsigned long, unsigned long);


extern unsigned long page_unuse(struct page *);
extern void truncate_inode_pages(struct address_space *, loff_t);


extern struct page *filemap_nopage(struct vm_area_struct *, unsigned long, int *);
extern int filemap_populate(struct vm_area_struct *, unsigned long,
  unsigned long, pgprot_t, unsigned long, int);


int write_one_page(struct page *page, int wait);







int do_page_cache_readahead(struct address_space *mapping, struct file *filp,
   unsigned long offset, unsigned long nr_to_read);
int force_page_cache_readahead(struct address_space *mapping, struct file *filp,
   unsigned long offset, unsigned long nr_to_read);
unsigned long page_cache_readahead(struct address_space *mapping,
     struct file_ra_state *ra,
     struct file *filp,
     unsigned long offset,
     unsigned long size);
void handle_ra_miss(struct address_space *mapping,
      struct file_ra_state *ra, unsigned long offset);
unsigned long max_sane_readahead(unsigned long nr);


extern int expand_stack(struct vm_area_struct * vma, unsigned long address);


extern struct vm_area_struct * find_vma(struct mm_struct * mm, unsigned long addr);
extern struct vm_area_struct * find_vma_prev(struct mm_struct * mm, unsigned long addr,
          struct vm_area_struct **pprev);



static inline __attribute__((always_inline)) struct vm_area_struct * find_vma_intersection(struct mm_struct * mm, unsigned long start_addr, unsigned long end_addr)
{
 struct vm_area_struct * vma = find_vma(mm,start_addr);

 if (vma && end_addr <= vma->vm_start)
  vma = ((void *)0);
 return vma;
}

static inline __attribute__((always_inline)) unsigned long vma_pages(struct vm_area_struct *vma)
{
 return (vma->vm_end - vma->vm_start) >> 12;
}

extern struct vm_area_struct *find_extend_vma(struct mm_struct *mm, unsigned long addr);

extern struct page * vmalloc_to_page(void *addr);
extern unsigned long vmalloc_to_pfn(void *addr);
extern struct page * follow_page(struct mm_struct *mm, unsigned long address,
  int write);
extern int check_user_page_readable(struct mm_struct *mm, unsigned long address);
int remap_pfn_range(struct vm_area_struct *, unsigned long,
  unsigned long, unsigned long, pgprot_t);


void __vm_stat_account(struct mm_struct *, unsigned long, struct file *, long);







static inline __attribute__((always_inline)) void vm_stat_account(struct vm_area_struct *vma)
{
 __vm_stat_account(vma->vm_mm, vma->vm_flags, vma->vm_file,
       vma_pages(vma));
}

static inline __attribute__((always_inline)) void vm_stat_unaccount(struct vm_area_struct *vma)
{
 __vm_stat_account(vma->vm_mm, vma->vm_flags, vma->vm_file,
       -vma_pages(vma));
}


extern void update_mem_hiwater(struct task_struct *tsk);


static inline __attribute__((always_inline)) void
kernel_map_pages(struct page *page, int numpages, int enable)
{
}


extern struct vm_area_struct *get_gate_vma(struct task_struct *tsk);




int in_gate_area_no_task(unsigned long addr);
# 27 "include/linux/skbuff.h" 2
# 1 "include/linux/highmem.h" 1







# 1 "include/asm/cacheflush.h" 1
# 26 "include/asm/cacheflush.h"
void global_flush_tlb(void);
int change_page_attr(struct page *page, int numpages, pgprot_t prot);
# 9 "include/linux/highmem.h" 2
# 19 "include/linux/highmem.h"
static inline __attribute__((always_inline)) unsigned int nr_free_highpages(void) { return 0; }

static inline __attribute__((always_inline)) void *kmap(struct page *page)
{
 do { __might_sleep("include/linux/highmem.h", 23); do { } while (0); } while (0);
 return lowmem_page_address(page);
}
# 37 "include/linux/highmem.h"
static inline __attribute__((always_inline)) void clear_user_highpage(struct page *page, unsigned long vaddr)
{
 void *addr = lowmem_page_address(page);
 __memset_generic(((void *)(addr)),(0),((1UL << 12)));
 do { } while (0);

 __asm__ __volatile__ ("": : :"memory");
}
# 59 "include/linux/highmem.h"
static inline __attribute__((always_inline)) void clear_highpage(struct page *page)
{
 void *kaddr = lowmem_page_address(page);
 __memset_generic(((void *)(kaddr)),(0),((1UL << 12)));
 do { } while (0);
}




static inline __attribute__((always_inline)) void memclear_highpage_flush(struct page *page, unsigned int offset, unsigned int size)
{
 void *kaddr;

 do { if (__builtin_expect(!!((offset + size > (1UL << 12))!=0), 0)) __BUG(); } while(0);

 kaddr = lowmem_page_address(page);
 __memset_generic(((char *)kaddr + offset),(0),(size));
 do { } while (0);
 do { } while (0);
}

static inline __attribute__((always_inline)) void copy_user_highpage(struct page *to, struct page *from, unsigned long vaddr)
{
 char *vfrom, *vto;

 vfrom = lowmem_page_address(from);
 vto = lowmem_page_address(to);
 __memcpy((void *)(vto),(void *)(vfrom),(1UL << 12));
 do { } while (0);
 do { } while (0);

 __asm__ __volatile__ ("": : :"memory");
}

static inline __attribute__((always_inline)) void copy_highpage(struct page *to, struct page *from)
{
 char *vfrom, *vto;

 vfrom = lowmem_page_address(from);
 vto = lowmem_page_address(to);
 __memcpy((void *)(vto),(void *)(vfrom),(1UL << 12));
 do { } while (0);
 do { } while (0);
}
# 28 "include/linux/skbuff.h" 2
# 1 "include/linux/poll.h" 1



# 1 "include/asm/poll.h" 1
# 20 "include/asm/poll.h"
struct pollfd {
 int fd;
 short events;
 short revents;
};
# 5 "include/linux/poll.h" 2







# 1 "include/asm/uaccess.h" 1
# 41 "include/asm/uaccess.h"
extern struct movsl_mask {
 int mask;
} __attribute__((__aligned__((1 << (7))))) movsl_mask;
# 86 "include/asm/uaccess.h"
static inline __attribute__((always_inline)) int access_ok(int type, const void *addr, unsigned long size) {
        return __builtin_expect(!!(({ unsigned long flag,sum; (void)0; asm("addl %3,%1 ; sbbl %0,%0; cmpl %1,%4; sbbl $0,%0" :"=&r" (flag), "=r" (sum) :"1" (addr),"g" ((int)(size)),"g" (current_thread_info()->addr_limit.seg)); flag; }) == 0), 1);
}
# 108 "include/asm/uaccess.h"
static inline __attribute__((always_inline)) int __attribute__((deprecated)) verify_area(int type, const void * addr, unsigned long size)
{
 return access_ok(type,addr,size) ? 0 : -14;
}
# 127 "include/asm/uaccess.h"
struct exception_table_entry
{
 unsigned long insn, fixup;
};

extern int fixup_exception(struct pt_regs *regs);
# 149 "include/asm/uaccess.h"
extern void __get_user_1(void);
extern void __get_user_2(void);
extern void __get_user_4(void);
# 191 "include/asm/uaccess.h"
extern void __put_user_bad(void);





extern void __put_user_1(void);
extern void __put_user_2(void);
extern void __put_user_4(void);
extern void __put_user_8(void);
# 352 "include/asm/uaccess.h"
struct __large_struct { unsigned long buf[100]; };
# 385 "include/asm/uaccess.h"
extern long __get_user_bad(void);
# 416 "include/asm/uaccess.h"
unsigned long __attribute__((warn_unused_result)) __copy_to_user_ll(void *to,
    const void *from, unsigned long n);
unsigned long __attribute__((warn_unused_result)) __copy_from_user_ll(void *to,
    const void *from, unsigned long n);
# 442 "include/asm/uaccess.h"
static inline __attribute__((always_inline)) unsigned long __attribute__((warn_unused_result))
__copy_to_user_inatomic(void *to, const void *from, unsigned long n)
{
 if (__builtin_constant_p(n)) {
  unsigned long ret;

  switch (n) {
  case 1:
   do { ret = 0; (void)0; switch (1) { case 1: __asm__ __volatile__( "1:	mov""b"" %""b""1,%2\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret) : "iq" (*(u8 *)from), "m"((*(struct __large_struct *)((u8 *)to))), "i"(1), "0"(ret));break; case 2: __asm__ __volatile__( "1:	mov""w"" %""w""1,%2\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret) : "ir" (*(u8 *)from), "m"((*(struct __large_struct *)((u8 *)to))), "i"(1), "0"(ret));break; case 4: __asm__ __volatile__( "1:	mov""l"" %""""1,%2\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret) : "ir" (*(u8 *)from), "m"((*(struct __large_struct *)((u8 *)to))), "i"(1), "0"(ret)); break; case 8: __asm__ __volatile__( "1:	movl %%eax,0(%2)\n" "2:	movl %%edx,4(%2)\n" "3:\n" ".section .fixup,\"ax\"\n" "4:	movl %3,%0\n" "	jmp 3b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,4b\n" "	.long 2b,4b\n" ".previous" : "=r"(ret) : "A" ((__typeof__(*(u8 *)to))(*(u8 *)from)), "r" ((u8 *)to), "i"(-14), "0"(ret)); break; default: __put_user_bad(); } } while (0);
   return ret;
  case 2:
   do { ret = 0; (void)0; switch (2) { case 1: __asm__ __volatile__( "1:	mov""b"" %""b""1,%2\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret) : "iq" (*(u16 *)from), "m"((*(struct __large_struct *)((u16 *)to))), "i"(2), "0"(ret));break; case 2: __asm__ __volatile__( "1:	mov""w"" %""w""1,%2\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret) : "ir" (*(u16 *)from), "m"((*(struct __large_struct *)((u16 *)to))), "i"(2), "0"(ret));break; case 4: __asm__ __volatile__( "1:	mov""l"" %""""1,%2\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret) : "ir" (*(u16 *)from), "m"((*(struct __large_struct *)((u16 *)to))), "i"(2), "0"(ret)); break; case 8: __asm__ __volatile__( "1:	movl %%eax,0(%2)\n" "2:	movl %%edx,4(%2)\n" "3:\n" ".section .fixup,\"ax\"\n" "4:	movl %3,%0\n" "	jmp 3b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,4b\n" "	.long 2b,4b\n" ".previous" : "=r"(ret) : "A" ((__typeof__(*(u16 *)to))(*(u16 *)from)), "r" ((u16 *)to), "i"(-14), "0"(ret)); break; default: __put_user_bad(); } } while (0);
   return ret;
  case 4:
   do { ret = 0; (void)0; switch (4) { case 1: __asm__ __volatile__( "1:	mov""b"" %""b""1,%2\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret) : "iq" (*(u32 *)from), "m"((*(struct __large_struct *)((u32 *)to))), "i"(4), "0"(ret));break; case 2: __asm__ __volatile__( "1:	mov""w"" %""w""1,%2\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret) : "ir" (*(u32 *)from), "m"((*(struct __large_struct *)((u32 *)to))), "i"(4), "0"(ret));break; case 4: __asm__ __volatile__( "1:	mov""l"" %""""1,%2\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret) : "ir" (*(u32 *)from), "m"((*(struct __large_struct *)((u32 *)to))), "i"(4), "0"(ret)); break; case 8: __asm__ __volatile__( "1:	movl %%eax,0(%2)\n" "2:	movl %%edx,4(%2)\n" "3:\n" ".section .fixup,\"ax\"\n" "4:	movl %3,%0\n" "	jmp 3b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,4b\n" "	.long 2b,4b\n" ".previous" : "=r"(ret) : "A" ((__typeof__(*(u32 *)to))(*(u32 *)from)), "r" ((u32 *)to), "i"(-14), "0"(ret)); break; default: __put_user_bad(); } } while (0);
   return ret;
  }
 }
 return __copy_to_user_ll(to, from, n);
}

static inline __attribute__((always_inline)) unsigned long __attribute__((warn_unused_result))
__copy_to_user(void *to, const void *from, unsigned long n)
{
       do { __might_sleep("include/asm/uaccess.h", 466); do { } while (0); } while (0);
       return __copy_to_user_inatomic(to, from, n);
}
# 487 "include/asm/uaccess.h"
static inline __attribute__((always_inline)) unsigned long
__copy_from_user_inatomic(void *to, const void *from, unsigned long n)
{
 if (__builtin_constant_p(n)) {
  unsigned long ret;

  switch (n) {
  case 1:
   do { ret = 0; (void)0; switch (1) { case 1: __asm__ __volatile__( "1:	mov""b"" %2,%""b""1\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	xor""b"" %""b""1,%""b""1\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret), "=q" (*(u8 *)to) : "m"((*(struct __large_struct *)(from))), "i"(1), "0"(ret));break; case 2: __asm__ __volatile__( "1:	mov""w"" %2,%""w""1\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	xor""w"" %""w""1,%""w""1\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret), "=r" (*(u8 *)to) : "m"((*(struct __large_struct *)(from))), "i"(1), "0"(ret));break; case 4: __asm__ __volatile__( "1:	mov""l"" %2,%""""1\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	xor""l"" %""""1,%""""1\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret), "=r" (*(u8 *)to) : "m"((*(struct __large_struct *)(from))), "i"(1), "0"(ret));break; default: (*(u8 *)to) = __get_user_bad(); } } while (0);
   return ret;
  case 2:
   do { ret = 0; (void)0; switch (2) { case 1: __asm__ __volatile__( "1:	mov""b"" %2,%""b""1\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	xor""b"" %""b""1,%""b""1\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret), "=q" (*(u16 *)to) : "m"((*(struct __large_struct *)(from))), "i"(2), "0"(ret));break; case 2: __asm__ __volatile__( "1:	mov""w"" %2,%""w""1\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	xor""w"" %""w""1,%""w""1\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret), "=r" (*(u16 *)to) : "m"((*(struct __large_struct *)(from))), "i"(2), "0"(ret));break; case 4: __asm__ __volatile__( "1:	mov""l"" %2,%""""1\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	xor""l"" %""""1,%""""1\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret), "=r" (*(u16 *)to) : "m"((*(struct __large_struct *)(from))), "i"(2), "0"(ret));break; default: (*(u16 *)to) = __get_user_bad(); } } while (0);
   return ret;
  case 4:
   do { ret = 0; (void)0; switch (4) { case 1: __asm__ __volatile__( "1:	mov""b"" %2,%""b""1\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	xor""b"" %""b""1,%""b""1\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret), "=q" (*(u32 *)to) : "m"((*(struct __large_struct *)(from))), "i"(4), "0"(ret));break; case 2: __asm__ __volatile__( "1:	mov""w"" %2,%""w""1\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	xor""w"" %""w""1,%""w""1\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret), "=r" (*(u32 *)to) : "m"((*(struct __large_struct *)(from))), "i"(4), "0"(ret));break; case 4: __asm__ __volatile__( "1:	mov""l"" %2,%""""1\n" "2:\n" ".section .fixup,\"ax\"\n" "3:	movl %3,%0\n" "	xor""l"" %""""1,%""""1\n" "	jmp 2b\n" ".previous\n" ".section __ex_table,\"a\"\n" "	.align 4\n" "	.long 1b,3b\n" ".previous" : "=r"(ret), "=r" (*(u32 *)to) : "m"((*(struct __large_struct *)(from))), "i"(4), "0"(ret));break; default: (*(u32 *)to) = __get_user_bad(); } } while (0);
   return ret;
  }
 }
 return __copy_from_user_ll(to, from, n);
}

static inline __attribute__((always_inline)) unsigned long
__copy_from_user(void *to, const void *from, unsigned long n)
{
       do { __might_sleep("include/asm/uaccess.h", 511); do { } while (0); } while (0);
       return __copy_from_user_inatomic(to, from, n);
}
unsigned long __attribute__((warn_unused_result)) copy_to_user(void *to,
    const void *from, unsigned long n);
unsigned long __attribute__((warn_unused_result)) copy_from_user(void *to,
    const void *from, unsigned long n);
long __attribute__((warn_unused_result)) strncpy_from_user(char *dst, const char *src,
    long count);
long __attribute__((warn_unused_result)) __strncpy_from_user(char *dst,
    const char *src, long count);
# 539 "include/asm/uaccess.h"
long strnlen_user(const char *str, long n);
unsigned long __attribute__((warn_unused_result)) clear_user(void *mem, unsigned long len);
unsigned long __attribute__((warn_unused_result)) __clear_user(void *mem, unsigned long len);
# 13 "include/linux/poll.h" 2

struct poll_table_struct;




typedef void (*poll_queue_proc)(struct file *, wait_queue_head_t *, struct poll_table_struct *);

typedef struct poll_table_struct {
 poll_queue_proc qproc;
} poll_table;

static inline __attribute__((always_inline)) void poll_wait(struct file * filp, wait_queue_head_t * wait_address, poll_table *p)
{
 if (p && wait_address)
  p->qproc(filp, wait_address, p);
}

static inline __attribute__((always_inline)) void init_poll_funcptr(poll_table *pt, poll_queue_proc qproc)
{
 pt->qproc = qproc;
}




struct poll_wqueues {
 poll_table pt;
 struct poll_table_page * table;
 int error;
};

extern void poll_initwait(struct poll_wqueues *pwq);
extern void poll_freewait(struct poll_wqueues *pwq);





typedef struct {
 unsigned long *in, *out, *ex;
 unsigned long *res_in, *res_out, *res_ex;
} fd_set_bits;
# 70 "include/linux/poll.h"
static inline __attribute__((always_inline))
int get_fd_set(unsigned long nr, void *ufdset, unsigned long *fdset)
{
 nr = ((((nr)+(8*sizeof(long))-1)/(8*sizeof(long)))*sizeof(long));
 if (ufdset)
  return copy_from_user(fdset, ufdset, nr) ? -14 : 0;

 __memset_generic((fdset),(0),(nr));
 return 0;
}

static inline __attribute__((always_inline)) unsigned long __attribute__((warn_unused_result))
set_fd_set(unsigned long nr, void *ufdset, unsigned long *fdset)
{
 if (ufdset)
  return __copy_to_user(ufdset, fdset, ((((nr)+(8*sizeof(long))-1)/(8*sizeof(long)))*sizeof(long)));
 return 0;
}

static inline __attribute__((always_inline))
void zero_fd_set(unsigned long nr, unsigned long *fdset)
{
 __memset_generic((fdset),(0),(((((nr)+(8*sizeof(long))-1)/(8*sizeof(long)))*sizeof(long))));
}

extern int do_select(int n, fd_set_bits *fds, long *timeout);
# 29 "include/linux/skbuff.h" 2

# 1 "include/linux/textsearch.h" 1
# 12 "include/linux/textsearch.h"
struct ts_config;
# 24 "include/linux/textsearch.h"
struct ts_state
{
 unsigned int offset;
 char cb[40];
};
# 40 "include/linux/textsearch.h"
struct ts_ops
{
 const char *name;
 struct ts_config * (*init)(const void *, unsigned int, int);
 unsigned int (*find)(struct ts_config *,
     struct ts_state *);
 void (*destroy)(struct ts_config *);
 void * (*get_pattern)(struct ts_config *);
 unsigned int (*get_pattern_len)(struct ts_config *);
 struct module *owner;
 struct list_head list;
};







struct ts_config
{
 struct ts_ops *ops;
# 75 "include/linux/textsearch.h"
 unsigned int (*get_next_block)(unsigned int consumed,
        const u8 **dst,
        struct ts_config *conf,
        struct ts_state *state);
# 88 "include/linux/textsearch.h"
 void (*finish)(struct ts_config *conf,
       struct ts_state *state);
};
# 104 "include/linux/textsearch.h"
static inline __attribute__((always_inline)) unsigned int textsearch_next(struct ts_config *conf,
        struct ts_state *state)
{
 unsigned int ret = conf->ops->find(conf, state);

 if (conf->finish)
  conf->finish(conf, state);

 return ret;
}
# 123 "include/linux/textsearch.h"
static inline __attribute__((always_inline)) unsigned int textsearch_find(struct ts_config *conf,
        struct ts_state *state)
{
 state->offset = 0;
 return textsearch_next(conf, state);
}





static inline __attribute__((always_inline)) void *textsearch_get_pattern(struct ts_config *conf)
{
 return conf->ops->get_pattern(conf);
}





static inline __attribute__((always_inline)) unsigned int textsearch_get_pattern_len(struct ts_config *conf)
{
 return conf->ops->get_pattern_len(conf);
}

extern int textsearch_register(struct ts_ops *);
extern int textsearch_unregister(struct ts_ops *);
extern struct ts_config *textsearch_prepare(const char *, const void *,
         unsigned int, int, int);
extern void textsearch_destroy(struct ts_config *conf);
extern unsigned int textsearch_find_continuous(struct ts_config *,
            struct ts_state *,
            const void *, unsigned int);





static inline __attribute__((always_inline)) struct ts_config *alloc_ts_config(size_t payload, int gfp_mask)
{
 struct ts_config *conf;

 conf = kmalloc((((sizeof(*conf)) + 8 -1) & ~(8 -1)) + payload, gfp_mask);
 if (conf == ((void *)0))
  return ERR_PTR(-12);

 __memset_generic((conf),(0),((((sizeof(*conf)) + 8 -1) & ~(8 -1)) + payload));
 return conf;
}

static inline __attribute__((always_inline)) void *ts_config_priv(struct ts_config *conf)
{
 return ((u8 *) conf + (((sizeof(struct ts_config)) + 8 -1) & ~(8 -1)));
}
# 31 "include/linux/skbuff.h" 2
# 1 "include/net/checksum.h" 1
# 26 "include/net/checksum.h"
# 1 "include/asm/checksum.h" 1
# 20 "include/asm/checksum.h"
 __attribute__((regparm(0))) unsigned int csum_partial(const unsigned char * buff, int len, unsigned int sum);
# 30 "include/asm/checksum.h"
 __attribute__((regparm(0))) unsigned int csum_partial_copy_generic(const unsigned char *src, unsigned char *dst,
        int len, int sum, int *src_err_ptr, int *dst_err_ptr);
# 40 "include/asm/checksum.h"
static __inline__ __attribute__((always_inline))
unsigned int csum_partial_copy_nocheck (const unsigned char *src, unsigned char *dst,
     int len, int sum)
{
 return csum_partial_copy_generic ( src, dst, len, sum, ((void *)0), ((void *)0));
}

static __inline__ __attribute__((always_inline))
unsigned int csum_partial_copy_from_user(const unsigned char *src, unsigned char *dst,
      int len, int sum, int *err_ptr)
{
 do { __might_sleep("include/asm/checksum.h", 51); do { } while (0); } while (0);
 return csum_partial_copy_generic(( unsigned char *)src, dst,
     len, sum, err_ptr, ((void *)0));
}
# 63 "include/asm/checksum.h"
static inline __attribute__((always_inline)) unsigned short ip_fast_csum(unsigned char * iph,
       unsigned int ihl)
{
 unsigned int sum;

 __asm__ __volatile__(
     "movl (%1), %0	;\n"
     "subl $4, %2	;\n"
     "jbe 2f		;\n"
     "addl 4(%1), %0	;\n"
     "adcl 8(%1), %0	;\n"
     "adcl 12(%1), %0	;\n"
"1:	    adcl 16(%1), %0	;\n"
     "lea 4(%1), %1	;\n"
     "decl %2		;\n"
     "jne 1b		;\n"
     "adcl $0, %0	;\n"
     "movl %0, %2	;\n"
     "shrl $16, %0	;\n"
     "addw %w2, %w0	;\n"
     "adcl $0, %0	;\n"
     "notl %0		;\n"
"2:				;\n"



 : "=r" (sum), "=r" (iph), "=r" (ihl)
 : "1" (iph), "2" (ihl)
 : "memory");
 return(sum);
}





static inline __attribute__((always_inline)) unsigned int csum_fold(unsigned int sum)
{
 __asm__(
  "addl %1, %0		;\n"
  "adcl $0xffff, %0	;\n"
  : "=r" (sum)
  : "r" (sum << 16), "0" (sum & 0xffff0000)
 );
 return (~sum) >> 16;
}

static inline __attribute__((always_inline)) unsigned long csum_tcpudp_nofold(unsigned long saddr,
         unsigned long daddr,
         unsigned short len,
         unsigned short proto,
         unsigned int sum)
{
    __asm__(
 "addl %1, %0	;\n"
 "adcl %2, %0	;\n"
 "adcl %3, %0	;\n"
 "adcl $0, %0	;\n"
 : "=r" (sum)
 : "g" (daddr), "g"(saddr), "g"(((__builtin_constant_p((__u16)(( __u16)(__be16)(len))) ? ({ __u16 __x = ((( __u16)(__be16)(len))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16((( __u16)(__be16)(len))))<<16)+proto*256), "0"(sum));
    return sum;
}





static inline __attribute__((always_inline)) unsigned short int csum_tcpudp_magic(unsigned long saddr,
         unsigned long daddr,
         unsigned short len,
         unsigned short proto,
         unsigned int sum)
{
 return csum_fold(csum_tcpudp_nofold(saddr,daddr,len,proto,sum));
}






static inline __attribute__((always_inline)) unsigned short ip_compute_csum(unsigned char * buff, int len)
{
    return csum_fold (csum_partial(buff, len, 0));
}


static __inline__ __attribute__((always_inline)) unsigned short int csum_ipv6_magic(struct in6_addr *saddr,
           struct in6_addr *daddr,
           __u32 len,
           unsigned short proto,
           unsigned int sum)
{
 __asm__(
  "addl 0(%1), %0		;\n"
  "adcl 4(%1), %0		;\n"
  "adcl 8(%1), %0		;\n"
  "adcl 12(%1), %0	;\n"
  "adcl 0(%2), %0		;\n"
  "adcl 4(%2), %0		;\n"
  "adcl 8(%2), %0		;\n"
  "adcl 12(%2), %0	;\n"
  "adcl %3, %0		;\n"
  "adcl %4, %0		;\n"
  "adcl $0, %0		;\n"
  : "=&r" (sum)
  : "r" (saddr), "r" (daddr),
    "r"((( __be32)(__builtin_constant_p((__u32)((len))) ? ({ __u32 __x = (((len))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((len)))))), "r"((( __be32)(__builtin_constant_p((__u32)((proto))) ? ({ __u32 __x = (((proto))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((proto)))))), "0"(sum));

 return csum_fold(sum);
}





static __inline__ __attribute__((always_inline)) unsigned int csum_and_copy_to_user(const unsigned char *src,
           unsigned char *dst,
           int len, int sum,
           int *err_ptr)
{
 do { __might_sleep("include/asm/checksum.h", 184); do { } while (0); } while (0);
 if (access_ok(1, dst, len))
  return csum_partial_copy_generic(src, ( unsigned char *)dst, len, sum, ((void *)0), err_ptr);

 if (len)
  *err_ptr = -14;

 return -1;
}
# 27 "include/net/checksum.h" 2


static inline __attribute__((always_inline))
unsigned int csum_and_copy_from_user (const unsigned char *src, unsigned char *dst,
          int len, int sum, int *err_ptr)
{
 if (access_ok(0, src, len))
  return csum_partial_copy_from_user(src, dst, len, sum, err_ptr);

 if (len)
  *err_ptr = -14;

 return sum;
}
# 60 "include/net/checksum.h"
static inline __attribute__((always_inline)) unsigned int csum_add(unsigned int csum, unsigned int addend)
{
 csum += addend;
 return csum + (csum < addend);
}

static inline __attribute__((always_inline)) unsigned int csum_sub(unsigned int csum, unsigned int addend)
{
 return csum_add(csum, ~addend);
}

static inline __attribute__((always_inline)) unsigned int
csum_block_add(unsigned int csum, unsigned int csum2, int offset)
{
 if (offset&1)
  csum2 = ((csum2&0xFF00FF)<<8)+((csum2>>8)&0xFF00FF);
 return csum_add(csum, csum2);
}

static inline __attribute__((always_inline)) unsigned int
csum_block_sub(unsigned int csum, unsigned int csum2, int offset)
{
 if (offset&1)
  csum2 = ((csum2&0xFF00FF)<<8)+((csum2>>8)&0xFF00FF);
 return csum_sub(csum, csum2);
}
# 32 "include/linux/skbuff.h" 2
# 87 "include/linux/skbuff.h"
struct net_device;


struct nf_conntrack {
 atomic_t use;
 void (*destroy)(struct nf_conntrack *);
};


struct nf_bridge_info {
 atomic_t use;
 struct net_device *physindev;
 struct net_device *physoutdev;

 struct net_device *netoutdev;

 unsigned int mask;
 unsigned long data[32 / sizeof(unsigned long)];
};




struct sk_buff_head {

 struct sk_buff *next;
 struct sk_buff *prev;

 __u32 qlen;
 spinlock_t lock;
};

struct sk_buff;




typedef struct skb_frag_struct skb_frag_t;

struct skb_frag_struct {
 struct page *page;
 __u16 page_offset;
 __u16 size;
};




struct skb_shared_info {
 atomic_t dataref;
 unsigned int nr_frags;
 unsigned short tso_size;
 unsigned short tso_segs;
 struct sk_buff *frag_list;
 skb_frag_t frags[(65536/(1UL << 12) + 2)];
};
# 203 "include/linux/skbuff.h"
struct sk_buff {

 struct sk_buff *next;
 struct sk_buff *prev;

 struct sk_buff_head *list;
 struct sock *sk;
 struct timeval stamp;
 struct net_device *dev;
 struct net_device *input_dev;
 struct net_device *real_dev;

 union {
  struct tcphdr *th;
  struct udphdr *uh;
  struct icmphdr *icmph;
  struct igmphdr *igmph;
  struct iphdr *ipiph;
  struct ipv6hdr *ipv6h;
  unsigned char *raw;
 } h;

 union {
  struct iphdr *iph;
  struct ipv6hdr *ipv6h;
  struct arphdr *arph;
  unsigned char *raw;
 } nh;

 union {
    unsigned char *raw;
 } mac;

 struct dst_entry *dst;
 struct sec_path *sp;







 char cb[40];

 unsigned int len,
    data_len,
    mac_len,
    csum;
 __u32 priority;
 __u8 local_df:1,
    cloned:1,
    ip_summed:2,
    nohdr:1;

 __u8 pkt_type;
 __be16 protocol;

 void (*destructor)(struct sk_buff *skb);

 unsigned long nfmark;
 __u32 nfcache;
 __u32 nfctinfo;
 struct nf_conntrack *nfct;

 struct nf_bridge_info *nf_bridge;



 union {
  __u32 ifield;
 } private;


       __u32 tc_index;

 __u32 tc_verd;
 __u32 tc_classid;






 unsigned int truesize;
 atomic_t users;
 unsigned char *head,
    *data,
    *tail,
    *end;
};
# 302 "include/linux/skbuff.h"
extern void __kfree_skb(struct sk_buff *skb);
extern struct sk_buff *alloc_skb(unsigned int size,
     unsigned int priority);
extern struct sk_buff *alloc_skb_from_cache(kmem_cache_t *cp,
         unsigned int size,
         unsigned int priority);
extern void kfree_skbmem(struct sk_buff *skb);
extern struct sk_buff *skb_clone(struct sk_buff *skb,
     unsigned int priority);
extern struct sk_buff *skb_copy(const struct sk_buff *skb,
    unsigned int priority);
extern struct sk_buff *pskb_copy(struct sk_buff *skb,
     unsigned int gfp_mask);
extern int pskb_expand_head(struct sk_buff *skb,
     int nhead, int ntail,
     unsigned int gfp_mask);
extern struct sk_buff *skb_realloc_headroom(struct sk_buff *skb,
         unsigned int headroom);
extern struct sk_buff *skb_copy_expand(const struct sk_buff *skb,
           int newheadroom, int newtailroom,
           unsigned int priority);
extern struct sk_buff * skb_pad(struct sk_buff *skb, int pad);

extern void skb_over_panic(struct sk_buff *skb, int len,
         void *here);
extern void skb_under_panic(struct sk_buff *skb, int len,
          void *here);

struct skb_seq_state
{
 __u32 lower_offset;
 __u32 upper_offset;
 __u32 frag_idx;
 __u32 stepped_offset;
 struct sk_buff *root_skb;
 struct sk_buff *cur_skb;
 __u8 *frag_data;
};

extern void skb_prepare_seq_read(struct sk_buff *skb,
        unsigned int from, unsigned int to,
        struct skb_seq_state *st);
extern unsigned int skb_seq_read(unsigned int consumed, const u8 **data,
       struct skb_seq_state *st);
extern void skb_abort_seq_read(struct skb_seq_state *st);

extern unsigned int skb_find_text(struct sk_buff *skb, unsigned int from,
        unsigned int to, struct ts_config *config,
        struct ts_state *state);
# 361 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) int skb_queue_empty(const struct sk_buff_head *list)
{
 return list->next == (struct sk_buff *)list;
}
# 373 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) struct sk_buff *skb_get(struct sk_buff *skb)
{
 atomic_inc(&skb->users);
 return skb;
}
# 391 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) void kfree_skb(struct sk_buff *skb)
{
 if (__builtin_expect(!!(((&skb->users)->counter) == 1), 1))
  asm volatile ("661:\n\t" "lock; addl $0,0(%%esp)" "\n662:\n" ".section .altinstructions,\"a\"\n" "  .align 4\n" "  .long 661b\n" "  .long 663f\n" "  .byte %c0\n" "  .byte 662b-661b\n" "  .byte 664f-663f\n" ".previous\n" ".section .altinstr_replacement,\"ax\"\n" "663:\n\t" "lfence" "\n664:\n" ".previous" :: "i" ((0*32+26)) : "memory");
 else if (__builtin_expect(!!(!atomic_dec_and_test(&skb->users)), 1))
  return;
 __kfree_skb(skb);
}
# 408 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) int skb_cloned(const struct sk_buff *skb)
{
 return skb->cloned &&
        (((&((struct skb_shared_info *)((skb)->end))->dataref)->counter) & ((1 << 16) - 1)) != 1;
}
# 421 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) int skb_header_cloned(const struct sk_buff *skb)
{
 int dataref;

 if (!skb->cloned)
  return 0;

 dataref = ((&((struct skb_shared_info *)((skb)->end))->dataref)->counter);
 dataref = (dataref & ((1 << 16) - 1)) - (dataref >> 16);
 return dataref != 1;
}
# 441 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) void skb_header_release(struct sk_buff *skb)
{
 do { if (__builtin_expect(!!((skb->nohdr)!=0), 0)) __BUG(); } while(0);
 skb->nohdr = 1;
 atomic_add(1 << 16, &((struct skb_shared_info *)((skb)->end))->dataref);
}
# 455 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) int skb_shared(const struct sk_buff *skb)
{
 return ((&skb->users)->counter) != 1;
}
# 473 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) struct sk_buff *skb_share_check(struct sk_buff *skb,
           unsigned int pri)
{
 do { if (__builtin_expect(!!(pri & 0x10u), 0)) do { __might_sleep("include/linux/skbuff.h", 476); do { } while (0); } while (0); } while (0);
 if (skb_shared(skb)) {
  struct sk_buff *nskb = skb_clone(skb, pri);
  kfree_skb(skb);
  skb = nskb;
 }
 return skb;
}
# 505 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) struct sk_buff *skb_unshare(struct sk_buff *skb,
       unsigned int pri)
{
 do { if (__builtin_expect(!!(pri & 0x10u), 0)) do { __might_sleep("include/linux/skbuff.h", 508); do { } while (0); } while (0); } while (0);
 if (skb_cloned(skb)) {
  struct sk_buff *nskb = skb_copy(skb, pri);
  kfree_skb(skb);
  skb = nskb;
 }
 return skb;
}
# 530 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) struct sk_buff *skb_peek(struct sk_buff_head *list_)
{
 struct sk_buff *list = ((struct sk_buff *)list_)->next;
 if (list == (struct sk_buff *)list_)
  list = ((void *)0);
 return list;
}
# 551 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) struct sk_buff *skb_peek_tail(struct sk_buff_head *list_)
{
 struct sk_buff *list = ((struct sk_buff *)list_)->prev;
 if (list == (struct sk_buff *)list_)
  list = ((void *)0);
 return list;
}







static inline __attribute__((always_inline)) __u32 skb_queue_len(const struct sk_buff_head *list_)
{
 return list_->qlen;
}

static inline __attribute__((always_inline)) void skb_queue_head_init(struct sk_buff_head *list)
{
 do { *(&list->lock) = (spinlock_t) { 1 , 0xdead4ead }; } while(0);
 list->prev = list->next = (struct sk_buff *)list;
 list->qlen = 0;
}
# 594 "include/linux/skbuff.h"
extern void skb_queue_head(struct sk_buff_head *list, struct sk_buff *newsk);
static inline __attribute__((always_inline)) void __skb_queue_head(struct sk_buff_head *list,
        struct sk_buff *newsk)
{
 struct sk_buff *prev, *next;

 newsk->list = list;
 list->qlen++;
 prev = (struct sk_buff *)list;
 next = prev->next;
 newsk->next = next;
 newsk->prev = prev;
 next->prev = prev->next = newsk;
}
# 619 "include/linux/skbuff.h"
extern void skb_queue_tail(struct sk_buff_head *list, struct sk_buff *newsk);
static inline __attribute__((always_inline)) void __skb_queue_tail(struct sk_buff_head *list,
       struct sk_buff *newsk)
{
 struct sk_buff *prev, *next;

 newsk->list = list;
 list->qlen++;
 next = (struct sk_buff *)list;
 prev = next->prev;
 newsk->next = next;
 newsk->prev = prev;
 next->prev = prev->next = newsk;
}
# 643 "include/linux/skbuff.h"
extern struct sk_buff *skb_dequeue(struct sk_buff_head *list);
static inline __attribute__((always_inline)) struct sk_buff *__skb_dequeue(struct sk_buff_head *list)
{
 struct sk_buff *next, *prev, *result;

 prev = (struct sk_buff *) list;
 next = prev->next;
 result = ((void *)0);
 if (next != prev) {
  result = next;
  next = next->next;
  list->qlen--;
  next->prev = prev;
  prev->next = next;
  result->next = result->prev = ((void *)0);
  result->list = ((void *)0);
 }
 return result;
}





extern void skb_insert(struct sk_buff *old, struct sk_buff *newsk);
static inline __attribute__((always_inline)) void __skb_insert(struct sk_buff *newsk,
    struct sk_buff *prev, struct sk_buff *next,
    struct sk_buff_head *list)
{
 newsk->next = next;
 newsk->prev = prev;
 next->prev = prev->next = newsk;
 newsk->list = list;
 list->qlen++;
}




extern void skb_append(struct sk_buff *old, struct sk_buff *newsk);
static inline __attribute__((always_inline)) void __skb_append(struct sk_buff *old, struct sk_buff *newsk)
{
 __skb_insert(newsk, old, old->next, old->list);
}





extern void skb_unlink(struct sk_buff *skb);
static inline __attribute__((always_inline)) void __skb_unlink(struct sk_buff *skb, struct sk_buff_head *list)
{
 struct sk_buff *next, *prev;

 list->qlen--;
 next = skb->next;
 prev = skb->prev;
 skb->next = skb->prev = ((void *)0);
 skb->list = ((void *)0);
 next->prev = prev;
 prev->next = next;
}
# 717 "include/linux/skbuff.h"
extern struct sk_buff *skb_dequeue_tail(struct sk_buff_head *list);
static inline __attribute__((always_inline)) struct sk_buff *__skb_dequeue_tail(struct sk_buff_head *list)
{
 struct sk_buff *skb = skb_peek_tail(list);
 if (skb)
  __skb_unlink(skb, list);
 return skb;
}


static inline __attribute__((always_inline)) int skb_is_nonlinear(const struct sk_buff *skb)
{
 return skb->data_len;
}

static inline __attribute__((always_inline)) unsigned int skb_headlen(const struct sk_buff *skb)
{
 return skb->len - skb->data_len;
}

static inline __attribute__((always_inline)) int skb_pagelen(const struct sk_buff *skb)
{
 int i, len = 0;

 for (i = (int)((struct skb_shared_info *)((skb)->end))->nr_frags - 1; i >= 0; i--)
  len += ((struct skb_shared_info *)((skb)->end))->frags[i].size;
 return len + skb_headlen(skb);
}

static inline __attribute__((always_inline)) void skb_fill_page_desc(struct sk_buff *skb, int i,
          struct page *page, int off, int size)
{
 skb_frag_t *frag = &((struct skb_shared_info *)((skb)->end))->frags[i];

 frag->page = page;
 frag->page_offset = off;
 frag->size = size;
 ((struct skb_shared_info *)((skb)->end))->nr_frags = i + 1;
}
# 764 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) unsigned char *__skb_put(struct sk_buff *skb, unsigned int len)
{
 unsigned char *tmp = skb->tail;
 do { if (__builtin_expect(!!((skb_is_nonlinear(skb))!=0), 0)) __BUG(); } while(0);
 skb->tail += len;
 skb->len += len;
 return tmp;
}
# 782 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) unsigned char *skb_put(struct sk_buff *skb, unsigned int len)
{
 unsigned char *tmp = skb->tail;
 do { if (__builtin_expect(!!((skb_is_nonlinear(skb))!=0), 0)) __BUG(); } while(0);
 skb->tail += len;
 skb->len += len;
 if (__builtin_expect(!!(skb->tail>skb->end), 0))
  skb_over_panic(skb, len, ({ void *pc; __asm__("movl $1f,%0\n1:":"=g" (pc)); pc; }));
 return tmp;
}

static inline __attribute__((always_inline)) unsigned char *__skb_push(struct sk_buff *skb, unsigned int len)
{
 skb->data -= len;
 skb->len += len;
 return skb->data;
}
# 809 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) unsigned char *skb_push(struct sk_buff *skb, unsigned int len)
{
 skb->data -= len;
 skb->len += len;
 if (__builtin_expect(!!(skb->data<skb->head), 0))
  skb_under_panic(skb, len, ({ void *pc; __asm__("movl $1f,%0\n1:":"=g" (pc)); pc; }));
 return skb->data;
}

static inline __attribute__((always_inline)) unsigned char *__skb_pull(struct sk_buff *skb, unsigned int len)
{
 skb->len -= len;
 do { if (__builtin_expect(!!((skb->len < skb->data_len)!=0), 0)) __BUG(); } while(0);
 return skb->data += len;
}
# 835 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) unsigned char *skb_pull(struct sk_buff *skb, unsigned int len)
{
 return __builtin_expect(!!(len > skb->len), 0) ? ((void *)0) : __skb_pull(skb, len);
}

extern unsigned char *__pskb_pull_tail(struct sk_buff *skb, int delta);

static inline __attribute__((always_inline)) unsigned char *__pskb_pull(struct sk_buff *skb, unsigned int len)
{
 if (len > skb_headlen(skb) &&
     !__pskb_pull_tail(skb, len-skb_headlen(skb)))
  return ((void *)0);
 skb->len -= len;
 return skb->data += len;
}

static inline __attribute__((always_inline)) unsigned char *pskb_pull(struct sk_buff *skb, unsigned int len)
{
 return __builtin_expect(!!(len > skb->len), 0) ? ((void *)0) : __pskb_pull(skb, len);
}

static inline __attribute__((always_inline)) int pskb_may_pull(struct sk_buff *skb, unsigned int len)
{
 if (__builtin_expect(!!(len <= skb_headlen(skb)), 1))
  return 1;
 if (__builtin_expect(!!(len > skb->len), 0))
  return 0;
 return __pskb_pull_tail(skb, len-skb_headlen(skb)) != ((void *)0);
}







static inline __attribute__((always_inline)) int skb_headroom(const struct sk_buff *skb)
{
 return skb->data - skb->head;
}







static inline __attribute__((always_inline)) int skb_tailroom(const struct sk_buff *skb)
{
 return skb_is_nonlinear(skb) ? 0 : skb->end - skb->tail;
}
# 895 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) void skb_reserve(struct sk_buff *skb, unsigned int len)
{
 skb->data += len;
 skb->tail += len;
}
# 925 "include/linux/skbuff.h"
extern int ___pskb_trim(struct sk_buff *skb, unsigned int len, int realloc);

static inline __attribute__((always_inline)) void __skb_trim(struct sk_buff *skb, unsigned int len)
{
 if (!skb->data_len) {
  skb->len = len;
  skb->tail = skb->data + len;
 } else
  ___pskb_trim(skb, len, 0);
}
# 944 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) void skb_trim(struct sk_buff *skb, unsigned int len)
{
 if (skb->len > len)
  __skb_trim(skb, len);
}


static inline __attribute__((always_inline)) int __pskb_trim(struct sk_buff *skb, unsigned int len)
{
 if (!skb->data_len) {
  skb->len = len;
  skb->tail = skb->data+len;
  return 0;
 }
 return ___pskb_trim(skb, len, 1);
}

static inline __attribute__((always_inline)) int pskb_trim(struct sk_buff *skb, unsigned int len)
{
 return (len < skb->len) ? __pskb_trim(skb, len) : 0;
}
# 974 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) void skb_orphan(struct sk_buff *skb)
{
 if (skb->destructor)
  skb->destructor(skb);
 skb->destructor = ((void *)0);
 skb->sk = ((void *)0);
}
# 990 "include/linux/skbuff.h"
extern void skb_queue_purge(struct sk_buff_head *list);
static inline __attribute__((always_inline)) void __skb_queue_purge(struct sk_buff_head *list)
{
 struct sk_buff *skb;
 while ((skb = __skb_dequeue(list)) != ((void *)0))
  kfree_skb(skb);
}
# 1011 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) struct sk_buff *__dev_alloc_skb(unsigned int length,
           unsigned int gfp_mask)
{
 struct sk_buff *skb = alloc_skb(length + 16, gfp_mask);
 if (__builtin_expect(!!(skb), 1))
  skb_reserve(skb, 16);
 return skb;
}
# 1035 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) struct sk_buff *dev_alloc_skb(unsigned int length)
{
 return __dev_alloc_skb(length, (0x20u));
}
# 1052 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) int skb_cow(struct sk_buff *skb, unsigned int headroom)
{
 int delta = (headroom > 16 ? headroom : 16) - skb_headroom(skb);

 if (delta < 0)
  delta = 0;

 if (delta || skb_cloned(skb))
  return pskb_expand_head(skb, (delta + 15) & ~15, 0, (0x20u));
 return 0;
}
# 1076 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) struct sk_buff *skb_padto(struct sk_buff *skb, unsigned int len)
{
 unsigned int size = skb->len;
 if (__builtin_expect(!!(size >= len), 1))
  return skb;
 return skb_pad(skb, len-size);
}

static inline __attribute__((always_inline)) int skb_add_data(struct sk_buff *skb,
          char *from, int copy)
{
 const int off = skb->len;

 if (skb->ip_summed == 0) {
  int err = 0;
  unsigned int csum = csum_and_copy_from_user(from,
           skb_put(skb, copy),
           copy, 0, &err);
  if (!err) {
   skb->csum = csum_block_add(skb->csum, csum, off);
   return 0;
  }
 } else if (!copy_from_user(skb_put(skb, copy), from, copy))
  return 0;

 __skb_trim(skb, off);
 return -14;
}

static inline __attribute__((always_inline)) int skb_can_coalesce(struct sk_buff *skb, int i,
       struct page *page, int off)
{
 if (i) {
  struct skb_frag_struct *frag = &((struct skb_shared_info *)((skb)->end))->frags[i - 1];

  return page == frag->page &&
         off == frag->page_offset + frag->size;
 }
 return 0;
}
# 1125 "include/linux/skbuff.h"
extern int __skb_linearize(struct sk_buff *skb, unsigned int gfp);
static inline __attribute__((always_inline)) int skb_linearize(struct sk_buff *skb, unsigned int gfp)
{
 return __skb_linearize(skb, gfp);
}
# 1142 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) void skb_postpull_rcsum(struct sk_buff *skb,
      const void *start, int len)
{
 if (skb->ip_summed == 1)
  skb->csum = csum_sub(skb->csum, csum_partial(start, len, 0));
}
# 1158 "include/linux/skbuff.h"
static inline __attribute__((always_inline)) int pskb_trim_rcsum(struct sk_buff *skb, unsigned int len)
{
 if (len >= skb->len)
  return 0;
 if (skb->ip_summed == 1)
  skb->ip_summed = 0;
 return __pskb_trim(skb, len);
}

static inline __attribute__((always_inline)) void *kmap_skb_frag(const skb_frag_t *frag)
{





 return lowmem_page_address(frag->page);
}

static inline __attribute__((always_inline)) void kunmap_skb_frag(void *vaddr)
{
 do { } while (0);



}







extern struct sk_buff *skb_recv_datagram(struct sock *sk, unsigned flags,
      int noblock, int *err);
extern unsigned int datagram_poll(struct file *file, struct socket *sock,
         struct poll_table_struct *wait);
extern int skb_copy_datagram_iovec(const struct sk_buff *from,
            int offset, struct iovec *to,
            int size);
extern int skb_copy_and_csum_datagram_iovec(const
       struct sk_buff *skb,
       int hlen,
       struct iovec *iov);
extern void skb_free_datagram(struct sock *sk, struct sk_buff *skb);
extern unsigned int skb_checksum(const struct sk_buff *skb, int offset,
        int len, unsigned int csum);
extern int skb_copy_bits(const struct sk_buff *skb, int offset,
         void *to, int len);
extern int skb_store_bits(const struct sk_buff *skb, int offset,
          void *from, int len);
extern unsigned int skb_copy_and_csum_bits(const struct sk_buff *skb,
           int offset, u8 *to, int len,
           unsigned int csum);
extern void skb_copy_and_csum_dev(const struct sk_buff *skb, u8 *to);
extern void skb_split(struct sk_buff *skb,
     struct sk_buff *skb1, const u32 len);

static inline __attribute__((always_inline)) void *skb_header_pointer(const struct sk_buff *skb, int offset,
           int len, void *buffer)
{
 int hlen = skb_headlen(skb);

 if (hlen - offset >= len)
  return skb->data + offset;

 if (skb_copy_bits(skb, offset, buffer, len) < 0)
  return ((void *)0);

 return buffer;
}

extern void skb_init(void);
extern void skb_add_mtu(int mtu);


static inline __attribute__((always_inline)) void nf_conntrack_put(struct nf_conntrack *nfct)
{
 if (nfct && atomic_dec_and_test(&nfct->use))
  nfct->destroy(nfct);
}
static inline __attribute__((always_inline)) void nf_conntrack_get(struct nf_conntrack *nfct)
{
 if (nfct)
  atomic_inc(&nfct->use);
}
static inline __attribute__((always_inline)) void nf_reset(struct sk_buff *skb)
{
 nf_conntrack_put(skb->nfct);
 skb->nfct = ((void *)0);
}


static inline __attribute__((always_inline)) void nf_bridge_put(struct nf_bridge_info *nf_bridge)
{
 if (nf_bridge && atomic_dec_and_test(&nf_bridge->use))
  kfree(nf_bridge);
}
static inline __attribute__((always_inline)) void nf_bridge_get(struct nf_bridge_info *nf_bridge)
{
 if (nf_bridge)
  atomic_inc(&nf_bridge->use);
}
# 108 "include/linux/if_ether.h" 2

static inline __attribute__((always_inline)) struct ethhdr *eth_hdr(const struct sk_buff *skb)
{
 return (struct ethhdr *)skb->mac.raw;
}
# 30 "include/linux/netdevice.h" 2
# 1 "include/linux/if_packet.h" 1



struct sockaddr_pkt
{
 unsigned short spkt_family;
 unsigned char spkt_device[14];
 unsigned short spkt_protocol;
};

struct sockaddr_ll
{
 unsigned short sll_family;
 unsigned short sll_protocol;
 int sll_ifindex;
 unsigned short sll_hatype;
 unsigned char sll_pkttype;
 unsigned char sll_halen;
 unsigned char sll_addr[8];
};
# 43 "include/linux/if_packet.h"
struct tpacket_stats
{
 unsigned int tp_packets;
 unsigned int tp_drops;
};

struct tpacket_hdr
{
 unsigned long tp_status;





 unsigned int tp_len;
 unsigned int tp_snaplen;
 unsigned short tp_mac;
 unsigned short tp_net;
 unsigned int tp_sec;
 unsigned int tp_usec;
};
# 82 "include/linux/if_packet.h"
struct tpacket_req
{
 unsigned int tp_block_size;
 unsigned int tp_block_nr;
 unsigned int tp_frame_size;
 unsigned int tp_frame_nr;
};

struct packet_mreq
{
 int mr_ifindex;
 unsigned short mr_type;
 unsigned short mr_alen;
 unsigned char mr_address[8];
};
# 31 "include/linux/netdevice.h" 2







# 1 "include/linux/device.h" 1
# 15 "include/linux/device.h"
# 1 "include/linux/ioport.h" 1
# 16 "include/linux/ioport.h"
struct resource {
 const char *name;
 unsigned long start, end;
 unsigned long flags;
 struct resource *parent, *sibling, *child;
};

struct resource_list {
 struct resource_list *next;
 struct resource *res;
 struct pci_dev *dev;
};
# 91 "include/linux/ioport.h"
extern struct resource ioport_resource;
extern struct resource iomem_resource;

extern int request_resource(struct resource *root, struct resource *new);
extern struct resource * ____request_resource(struct resource *root, struct resource *new);
extern int release_resource(struct resource *new);
extern int insert_resource(struct resource *parent, struct resource *new);
extern int allocate_resource(struct resource *root, struct resource *new,
        unsigned long size,
        unsigned long min, unsigned long max,
        unsigned long align,
        void (*alignf)(void *, struct resource *,
         unsigned long, unsigned long),
        void *alignf_data);
int adjust_resource(struct resource *res, unsigned long start,
      unsigned long size);






extern struct resource * __request_region(struct resource *, unsigned long start, unsigned long n, const char *name);






extern int __check_region(struct resource *, unsigned long, unsigned long);
extern void __release_region(struct resource *, unsigned long, unsigned long);

static inline __attribute__((always_inline)) int __attribute__((deprecated)) check_region(unsigned long s, unsigned long n)
{
 return __check_region(&ioport_resource, s, n);
}
# 16 "include/linux/device.h" 2

# 1 "include/linux/klist.h" 1
# 18 "include/linux/klist.h"
struct klist {
 spinlock_t k_lock;
 struct list_head k_list;
};


extern void klist_init(struct klist * k);


struct klist_node {
 struct klist * n_klist;
 struct list_head n_node;
 struct kref n_ref;
 struct completion n_removed;
};

extern void klist_add_tail(struct klist * k, struct klist_node * n);
extern void klist_add_head(struct klist * k, struct klist_node * n);

extern void klist_del(struct klist_node * n);
extern void klist_remove(struct klist_node * n);

extern int klist_node_attached(struct klist_node * n);


struct klist_iter {
 struct klist * i_klist;
 struct list_head * i_head;
 struct klist_node * i_cur;
};


extern void klist_iter_init(struct klist * k, struct klist_iter * i);
extern void klist_iter_init_node(struct klist * k, struct klist_iter * i,
     struct klist_node * n);
extern void klist_iter_exit(struct klist_iter * i);
extern struct klist_node * klist_next(struct klist_iter * i);
# 18 "include/linux/device.h" 2
# 31 "include/linux/device.h"
enum {
 SUSPEND_NOTIFY,
 SUSPEND_SAVE_STATE,
 SUSPEND_DISABLE,
 SUSPEND_POWER_DOWN,
};

enum {
 RESUME_POWER_ON,
 RESUME_RESTORE_STATE,
 RESUME_ENABLE,
};

struct device;
struct device_driver;
struct class;
struct class_device;

struct bus_type {
 const char * name;

 struct subsystem subsys;
 struct kset drivers;
 struct kset devices;
 struct klist klist_devices;
 struct klist klist_drivers;

 struct bus_attribute * bus_attrs;
 struct device_attribute * dev_attrs;
 struct driver_attribute * drv_attrs;

 int (*match)(struct device * dev, struct device_driver * drv);
 int (*hotplug) (struct device *dev, char **envp,
        int num_envp, char *buffer, int buffer_size);
 int (*suspend)(struct device * dev, pm_message_t state);
 int (*resume)(struct device * dev);
};

extern int bus_register(struct bus_type * bus);
extern void bus_unregister(struct bus_type * bus);

extern void bus_rescan_devices(struct bus_type * bus);

extern struct bus_type * get_bus(struct bus_type * bus);
extern void put_bus(struct bus_type * bus);

extern struct bus_type * find_bus(char * name);



int bus_for_each_dev(struct bus_type * bus, struct device * start, void * data,
       int (*fn)(struct device *, void *));
struct device * bus_find_device(struct bus_type *bus, struct device *start,
    void *data, int (*match)(struct device *, void *));

int bus_for_each_drv(struct bus_type * bus, struct device_driver * start,
       void * data, int (*fn)(struct device_driver *, void *));




struct bus_attribute {
 struct attribute attr;
 ssize_t (*show)(struct bus_type *, char * buf);
 ssize_t (*store)(struct bus_type *, const char * buf, size_t count);
};




extern int bus_create_file(struct bus_type *, struct bus_attribute *);
extern void bus_remove_file(struct bus_type *, struct bus_attribute *);

struct device_driver {
 const char * name;
 struct bus_type * bus;

 struct completion unloaded;
 struct kobject kobj;
 struct klist klist_devices;
 struct klist_node knode_bus;

 struct module * owner;

 int (*probe) (struct device * dev);
 int (*remove) (struct device * dev);
 void (*shutdown) (struct device * dev);
 int (*suspend) (struct device * dev, pm_message_t state, u32 level);
 int (*resume) (struct device * dev, u32 level);
};


extern int driver_register(struct device_driver * drv);
extern void driver_unregister(struct device_driver * drv);

extern struct device_driver * get_driver(struct device_driver * drv);
extern void put_driver(struct device_driver * drv);
extern struct device_driver *driver_find(const char *name, struct bus_type *bus);




struct driver_attribute {
 struct attribute attr;
 ssize_t (*show)(struct device_driver *, char * buf);
 ssize_t (*store)(struct device_driver *, const char * buf, size_t count);
};




extern int driver_create_file(struct device_driver *, struct driver_attribute *);
extern void driver_remove_file(struct device_driver *, struct driver_attribute *);

extern int driver_for_each_device(struct device_driver * drv, struct device * start,
      void * data, int (*fn)(struct device *, void *));
struct device * driver_find_device(struct device_driver *drv,
       struct device *start, void *data,
       int (*match)(struct device *, void *));





struct class {
 const char * name;
 struct module * owner;

 struct subsystem subsys;
 struct list_head children;
 struct list_head interfaces;
 struct semaphore sem;

 struct class_attribute * class_attrs;
 struct class_device_attribute * class_dev_attrs;

 int (*hotplug)(struct class_device *dev, char **envp,
      int num_envp, char *buffer, int buffer_size);

 void (*release)(struct class_device *dev);
 void (*class_release)(struct class *class);
};

extern int class_register(struct class *);
extern void class_unregister(struct class *);

extern struct class * class_get(struct class *);
extern void class_put(struct class *);


struct class_attribute {
 struct attribute attr;
 ssize_t (*show)(struct class *, char * buf);
 ssize_t (*store)(struct class *, const char * buf, size_t count);
};




extern int class_create_file(struct class *, const struct class_attribute *);
extern void class_remove_file(struct class *, const struct class_attribute *);


struct class_device {
 struct list_head node;

 struct kobject kobj;
 struct class * class;
 dev_t devt;
 struct class_device_attribute *devt_attr;
 struct device * dev;
 void * class_data;

 char class_id[20];
};

static inline __attribute__((always_inline)) void *
class_get_devdata (struct class_device *dev)
{
 return dev->class_data;
}

static inline __attribute__((always_inline)) void
class_set_devdata (struct class_device *dev, void *data)
{
 dev->class_data = data;
}


extern int class_device_register(struct class_device *);
extern void class_device_unregister(struct class_device *);
extern void class_device_initialize(struct class_device *);
extern int class_device_add(struct class_device *);
extern void class_device_del(struct class_device *);

extern int class_device_rename(struct class_device *, char *);

extern struct class_device * class_device_get(struct class_device *);
extern void class_device_put(struct class_device *);

struct class_device_attribute {
 struct attribute attr;
 ssize_t (*show)(struct class_device *, char * buf);
 ssize_t (*store)(struct class_device *, const char * buf, size_t count);
};





extern int class_device_create_file(struct class_device *,
        const struct class_device_attribute *);
extern void class_device_remove_file(struct class_device *,
         const struct class_device_attribute *);
extern int class_device_create_bin_file(struct class_device *,
     struct bin_attribute *);
extern void class_device_remove_bin_file(struct class_device *,
      struct bin_attribute *);

struct class_interface {
 struct list_head node;
 struct class *class;

 int (*add) (struct class_device *);
 void (*remove) (struct class_device *);
};

extern int class_interface_register(struct class_interface *);
extern void class_interface_unregister(struct class_interface *);

extern struct class *class_create(struct module *owner, char *name);
extern void class_destroy(struct class *cls);
extern struct class_device *class_device_create(struct class *cls, dev_t devt,
      struct device *device, char *fmt, ...)
     __attribute__((format(printf,4,5)));
extern void class_device_destroy(struct class *cls, dev_t devt);


struct device {
 struct klist klist_children;
 struct klist_node knode_parent;
 struct klist_node knode_driver;
 struct klist_node knode_bus;
 struct device * parent;

 struct kobject kobj;
 char bus_id[20];

 struct semaphore sem;



 struct bus_type * bus;
 struct device_driver *driver;

 void *driver_data;
 void *platform_data;

 void *firmware_data;

 struct dev_pm_info power;

 u64 *dma_mask;
 u64 coherent_dma_mask;





 struct list_head dma_pools;

 struct dma_coherent_mem *dma_mem;


 void (*release)(struct device * dev);
};

static inline __attribute__((always_inline)) void *
dev_get_drvdata (struct device *dev)
{
 return dev->driver_data;
}

static inline __attribute__((always_inline)) void
dev_set_drvdata (struct device *dev, void *data)
{
 dev->driver_data = data;
}




extern int device_register(struct device * dev);
extern void device_unregister(struct device * dev);
extern void device_initialize(struct device * dev);
extern int device_add(struct device * dev);
extern void device_del(struct device * dev);
extern int device_for_each_child(struct device *, void *,
       int (*fn)(struct device *, void *));





extern void device_bind_driver(struct device * dev);
extern void device_release_driver(struct device * dev);
extern int device_attach(struct device * dev);
extern void driver_attach(struct device_driver * drv);




struct device_attribute {
 struct attribute attr;
 ssize_t (*show)(struct device *dev, struct device_attribute *attr,
   char *buf);
 ssize_t (*store)(struct device *dev, struct device_attribute *attr,
    const char *buf, size_t count);
};





extern int device_create_file(struct device *device, struct device_attribute * entry);
extern void device_remove_file(struct device * dev, struct device_attribute * attr);







extern int (*platform_notify)(struct device * dev);

extern int (*platform_notify_remove)(struct device * dev);






extern struct device * get_device(struct device * dev);
extern void put_device(struct device * dev);




struct platform_device {
 const char * name;
 u32 id;
 struct device dev;
 u32 num_resources;
 struct resource * resource;
};



extern int platform_device_register(struct platform_device *);
extern void platform_device_unregister(struct platform_device *);

extern struct bus_type platform_bus_type;
extern struct device platform_bus;

extern struct resource *platform_get_resource(struct platform_device *, unsigned int, unsigned int);
extern int platform_get_irq(struct platform_device *, unsigned int);
extern struct resource *platform_get_resource_byname(struct platform_device *, unsigned int, char *);
extern int platform_get_irq_byname(struct platform_device *, char *);
extern int platform_add_devices(struct platform_device **, int);

extern struct platform_device *platform_device_register_simple(char *, unsigned int, struct resource *, unsigned int);


extern void device_shutdown(void);



extern int firmware_register(struct subsystem *);
extern void firmware_unregister(struct subsystem *);
# 39 "include/linux/netdevice.h" 2


struct divert_blk;
struct vlan_group;
struct ethtool_ops;
struct netpoll_info;
# 108 "include/linux/netdevice.h"
struct net_device_stats
{
 unsigned long rx_packets;
 unsigned long tx_packets;
 unsigned long rx_bytes;
 unsigned long tx_bytes;
 unsigned long rx_errors;
 unsigned long tx_errors;
 unsigned long rx_dropped;
 unsigned long tx_dropped;
 unsigned long multicast;
 unsigned long collisions;


 unsigned long rx_length_errors;
 unsigned long rx_over_errors;
 unsigned long rx_crc_errors;
 unsigned long rx_frame_errors;
 unsigned long rx_fifo_errors;
 unsigned long rx_missed_errors;


 unsigned long tx_aborted_errors;
 unsigned long tx_carrier_errors;
 unsigned long tx_fifo_errors;
 unsigned long tx_heartbeat_errors;
 unsigned long tx_window_errors;


 unsigned long rx_compressed;
 unsigned long tx_compressed;
};



enum {
        IF_PORT_UNKNOWN = 0,
        IF_PORT_10BASE2,
        IF_PORT_10BASET,
        IF_PORT_AUI,
        IF_PORT_100BASET,
        IF_PORT_100BASETX,
        IF_PORT_100BASEFX
};






struct neighbour;
struct neigh_parms;
struct sk_buff;

struct netif_rx_stats
{
 unsigned total;
 unsigned dropped;
 unsigned time_squeeze;
 unsigned cpu_collision;
};

extern __typeof__(struct netif_rx_stats) per_cpu__netdev_rx_stat;






struct dev_mc_list
{
 struct dev_mc_list *next;
 __u8 dmi_addr[32];
 unsigned char dmi_addrlen;
 int dmi_users;
 int dmi_gusers;
};

struct hh_cache
{
 struct hh_cache *hh_next;
 atomic_t hh_refcnt;
 unsigned short hh_type;



 int hh_len;
 int (*hh_output)(struct sk_buff *skb);
 rwlock_t hh_lock;







 unsigned long hh_data[(((96)+(16 -1))&~(16 - 1)) / sizeof(long)];
};
# 225 "include/linux/netdevice.h"
enum netdev_state_t
{
 __LINK_STATE_XOFF=0,
 __LINK_STATE_START,
 __LINK_STATE_PRESENT,
 __LINK_STATE_SCHED,
 __LINK_STATE_NOCARRIER,
 __LINK_STATE_RX_SCHED,
 __LINK_STATE_LINKWATCH_PENDING
};






struct netdev_boot_setup {
 char name[16];
 struct ifmap map;
};
# 258 "include/linux/netdevice.h"
struct net_device
{






 char name[16];





 unsigned long mem_end;
 unsigned long mem_start;
 unsigned long base_addr;
 unsigned int irq;






 unsigned char if_port;
 unsigned char dma;

 unsigned long state;

 struct net_device *next;


 int (*init)(struct net_device *dev);



 struct net_device *next_sched;


 int ifindex;
 int iflink;


 struct net_device_stats* (*get_stats)(struct net_device *dev);
 struct iw_statistics* (*get_wireless_stats)(struct net_device *dev);



 const struct iw_handler_def * wireless_handlers;

 struct iw_public_data * wireless_data;

 struct ethtool_ops *ethtool_ops;
# 319 "include/linux/netdevice.h"
 unsigned long trans_start;
 unsigned long last_rx;

 unsigned short flags;
 unsigned short gflags;
        unsigned short priv_flags;
 unsigned short padded;

 unsigned mtu;
 unsigned short type;
 unsigned short hard_header_len;
 void *priv;

 struct net_device *master;




 unsigned char broadcast[32];
 unsigned char dev_addr[32];
 unsigned char addr_len;
 unsigned short dev_id;

 struct dev_mc_list *mc_list;
 int mc_count;
 int promiscuity;
 int allmulti;

 int watchdog_timeo;
 struct timer_list watchdog_timer;



 void *atalk_ptr;
 void *ip_ptr;
 void *dn_ptr;
 void *ip6_ptr;
 void *ec_ptr;
 void *ax25_ptr;

 struct list_head poll_list;
 int quota;
 int weight;

 struct Qdisc *qdisc;
 struct Qdisc *qdisc_sleeping;
 struct Qdisc *qdisc_ingress;
 struct list_head qdisc_list;
 unsigned long tx_queue_len;


 spinlock_t ingress_lock;

 spinlock_t xmit_lock;



 int xmit_lock_owner;

 spinlock_t queue_lock;

 atomic_t refcnt;

 struct list_head todo_list;

 struct hlist_node name_hlist;

 struct hlist_node index_hlist;


 enum { NETREG_UNINITIALIZED=0,
        NETREG_REGISTERING,
        NETREG_REGISTERED,
        NETREG_UNREGISTERING,
        NETREG_UNREGISTERED,
        NETREG_RELEASED,
 } reg_state;


 unsigned long features;
# 413 "include/linux/netdevice.h"
 void (*uninit)(struct net_device *dev);

 void (*destructor)(struct net_device *dev);


 int (*open)(struct net_device *dev);
 int (*stop)(struct net_device *dev);
 int (*hard_start_xmit) (struct sk_buff *skb,
          struct net_device *dev);

 int (*poll) (struct net_device *dev, int *quota);
 int (*hard_header) (struct sk_buff *skb,
      struct net_device *dev,
      unsigned short type,
      void *daddr,
      void *saddr,
      unsigned len);
 int (*rebuild_header)(struct sk_buff *skb);

 void (*set_multicast_list)(struct net_device *dev);

 int (*set_mac_address)(struct net_device *dev,
         void *addr);

 int (*do_ioctl)(struct net_device *dev,
         struct ifreq *ifr, int cmd);

 int (*set_config)(struct net_device *dev,
           struct ifmap *map);

 int (*hard_header_cache)(struct neighbour *neigh,
           struct hh_cache *hh);
 void (*header_cache_update)(struct hh_cache *hh,
             struct net_device *dev,
             unsigned char * haddr);

 int (*change_mtu)(struct net_device *dev, int new_mtu);


 void (*tx_timeout) (struct net_device *dev);

 void (*vlan_rx_register)(struct net_device *dev,
          struct vlan_group *grp);
 void (*vlan_rx_add_vid)(struct net_device *dev,
         unsigned short vid);
 void (*vlan_rx_kill_vid)(struct net_device *dev,
          unsigned short vid);

 int (*hard_header_parse)(struct sk_buff *skb,
           unsigned char *haddr);
 int (*neigh_setup)(struct net_device *dev, struct neigh_parms *);

 struct netpoll_info *npinfo;


 void (*poll_controller)(struct net_device *dev);



 struct net_bridge_port *br_port;



 struct divert_blk *divert;



 struct class_device class_dev;
};




static inline __attribute__((always_inline)) void *netdev_priv(struct net_device *dev)
{
 return (char *)dev + ((sizeof(struct net_device)
     + (32 - 1))
    & ~(32 - 1));
}







struct packet_type {
 __be16 type;
 struct net_device *dev;
 int (*func) (struct sk_buff *, struct net_device *,
      struct packet_type *);
 void *af_packet_priv;
 struct list_head list;
};

# 1 "include/linux/interrupt.h" 1
# 11 "include/linux/interrupt.h"
# 1 "include/linux/hardirq.h" 1





# 1 "include/linux/smp_lock.h" 1
# 12 "include/linux/smp_lock.h"
extern int __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) __reacquire_kernel_lock(void);
extern void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) __release_kernel_lock(void);
# 35 "include/linux/smp_lock.h"
static inline __attribute__((always_inline)) int reacquire_kernel_lock(struct task_struct *task)
{
 if (__builtin_expect(!!(task->lock_depth >= 0), 0))
  __reacquire_kernel_lock();
 return 0;
}

extern void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) lock_kernel(void) ;
extern void __attribute__((regparm(3))) __attribute__((section(".spinlock.text"))) unlock_kernel(void) ;
# 7 "include/linux/hardirq.h" 2
# 1 "include/asm/hardirq.h" 1





# 1 "include/linux/irq.h" 1
# 21 "include/linux/irq.h"
# 1 "include/asm/irq.h" 1
# 16 "include/asm/irq.h"
# 1 "include/asm-i386/mach-default/irq_vectors.h" 1
# 87 "include/asm-i386/mach-default/irq_vectors.h"
# 1 "include/asm-i386/mach-default/irq_vectors_limits.h" 1
# 88 "include/asm-i386/mach-default/irq_vectors.h" 2
# 17 "include/asm/irq.h" 2


static __inline__ __attribute__((always_inline)) int irq_canonicalize(int irq)
{
 return ((irq == 2) ? 9 : irq);
}

extern void release_vm86_irqs(struct task_struct *);






  extern void irq_ctx_init(int cpu);
  extern void irq_ctx_exit(int cpu);







extern int irqbalance_disable(char *str);



extern void fixup_irqs(cpumask_t map);
# 22 "include/linux/irq.h" 2
# 41 "include/linux/irq.h"
struct hw_interrupt_type {
 const char * typename;
 unsigned int (*startup)(unsigned int irq);
 void (*shutdown)(unsigned int irq);
 void (*enable)(unsigned int irq);
 void (*disable)(unsigned int irq);
 void (*ack)(unsigned int irq);
 void (*end)(unsigned int irq);
 void (*set_affinity)(unsigned int irq, cpumask_t dest);




};

typedef struct hw_interrupt_type hw_irq_controller;
# 65 "include/linux/irq.h"
typedef struct irq_desc {
 hw_irq_controller *handler;
 void *handler_data;
 struct irqaction *action;
 unsigned int status;
 unsigned int depth;
 unsigned int irq_count;
 unsigned int irqs_unhandled;
 spinlock_t lock;
} __attribute__((__aligned__((1 << (7))))) irq_desc_t;

extern irq_desc_t irq_desc [0xef];

# 1 "include/asm/hw_irq.h" 1
# 16 "include/asm/hw_irq.h"
# 1 "include/linux/profile.h" 1
# 15 "include/linux/profile.h"
struct proc_dir_entry;
struct pt_regs;


void __attribute__ ((__section__ (".init.text"))) profile_init(void);
void profile_tick(int, struct pt_regs *);
void profile_hit(int, void *);

void create_prof_cpu_mask(struct proc_dir_entry *);




enum profile_type {
 PROFILE_TASK_EXIT,
 PROFILE_MUNMAP
};



struct notifier_block;
struct task_struct;
struct mm_struct;


void profile_task_exit(struct task_struct * task);




int profile_handoff_task(struct task_struct * task);


void profile_munmap(unsigned long addr);

int task_handoff_register(struct notifier_block * n);
int task_handoff_unregister(struct notifier_block * n);

int profile_event_register(enum profile_type, struct notifier_block * n);
int profile_event_unregister(enum profile_type, struct notifier_block * n);

int register_timer_hook(int (*hook)(struct pt_regs *));
void unregister_timer_hook(int (*hook)(struct pt_regs *));


extern int (*timer_hook)(struct pt_regs *);

struct pt_regs;
# 17 "include/asm/hw_irq.h" 2


# 1 "include/asm/sections.h" 1




# 1 "include/asm-generic/sections.h" 1





extern char _text[], _stext[], _etext[];
extern char _data[], _sdata[], _edata[];
extern char __bss_start[], __bss_stop[];
extern char __init_begin[], __init_end[];
extern char _sinittext[], _einittext[];
extern char _sextratext[] __attribute__((weak));
extern char _eextratext[] __attribute__((weak));
extern char _end[];
extern char __per_cpu_start[], __per_cpu_end[];
# 6 "include/asm/sections.h" 2
# 20 "include/asm/hw_irq.h" 2
# 28 "include/asm/hw_irq.h"
extern u8 irq_vector[0xef];



extern void (*interrupt[0xef])(void);


__attribute__((regparm(3))) void reschedule_interrupt(void);
__attribute__((regparm(3))) void invalidate_interrupt(void);
__attribute__((regparm(3))) void call_function_interrupt(void);



__attribute__((regparm(3))) void apic_timer_interrupt(void);
__attribute__((regparm(3))) void error_interrupt(void);
__attribute__((regparm(3))) void spurious_interrupt(void);
__attribute__((regparm(3))) void thermal_interrupt(struct pt_regs *);



void disable_8259A_irq(unsigned int irq);
void enable_8259A_irq(unsigned int irq);
int i8259A_irq_pending(unsigned int irq);
void make_8259A_irq(unsigned int irq);
void init_8259A(int aeoi);
void send_IPI_self(int vector) __attribute__((regparm(3)));
void init_VISWS_APIC_irqs(void);
void setup_IO_APIC(void);
void disable_IO_APIC(void);
void print_IO_APIC(void);
int IO_APIC_get_PCI_irq_vector(int bus, int slot, int fn);
void send_IPI(int dest, int vector);
void setup_ioapic_dest(void);

extern unsigned long io_apic_irqs;

extern atomic_t irq_err_count;
extern atomic_t irq_mis_count;




static inline __attribute__((always_inline)) void hw_resend_irq(struct hw_interrupt_type *h, unsigned int i)
{
 if ((((i) >= 16) || ((1<<(i)) & io_apic_irqs)))
  send_IPI_self((irq_vector[i]));
}
# 79 "include/linux/irq.h" 2

extern int setup_irq(unsigned int irq, struct irqaction * new);


extern cpumask_t irq_affinity[0xef];
extern int no_irq_affinity;
extern int noirqdebug_setup(char *str);

extern __attribute__((regparm(3))) int handle_IRQ_event(unsigned int irq, struct pt_regs *regs,
     struct irqaction *action);
extern __attribute__((regparm(3))) unsigned int __do_IRQ(unsigned int irq, struct pt_regs *regs);
extern void note_interrupt(unsigned int irq, irq_desc_t *desc,
     int action_ret, struct pt_regs *regs);
extern int can_request_irq(unsigned int irq, unsigned long irqflags);

extern void init_irq_proc(void);


extern hw_irq_controller no_irq_type;
# 7 "include/asm/hardirq.h" 2

typedef struct {
 unsigned int __softirq_pending;
 unsigned long idle_timestamp;
 unsigned int __nmi_count;
 unsigned int apic_timer_irqs;
} __attribute__((__aligned__((1 << (7))))) irq_cpustat_t;

extern __typeof__(irq_cpustat_t) per_cpu__irq_stat;
extern irq_cpustat_t irq_stat[];




void ack_bad_irq(unsigned int irq);
# 1 "include/linux/irq_cpustat.h" 1
# 23 "include/asm/hardirq.h" 2
# 8 "include/linux/hardirq.h" 2
# 85 "include/linux/hardirq.h"
extern void synchronize_irq(unsigned int irq);
# 94 "include/linux/hardirq.h"
static inline __attribute__((always_inline)) void account_user_vtime(struct task_struct *tsk)
{
}

static inline __attribute__((always_inline)) void account_system_vtime(struct task_struct *tsk)
{
}
# 109 "include/linux/hardirq.h"
extern void irq_exit(void);
# 12 "include/linux/interrupt.h" 2
# 30 "include/linux/interrupt.h"
typedef int irqreturn_t;





struct irqaction {
 irqreturn_t (*handler)(int, void *, struct pt_regs *);
 unsigned long flags;
 cpumask_t mask;
 const char *name;
 void *dev_id;
 struct irqaction *next;
 int irq;
 struct proc_dir_entry *dir;
};

extern irqreturn_t no_action(int cpl, void *dev_id, struct pt_regs *regs);
extern int request_irq(unsigned int,
         irqreturn_t (*handler)(int, void *, struct pt_regs *),
         unsigned long, const char *, void *);
extern void free_irq(unsigned int, void *);



extern void disable_irq_nosync(unsigned int irq);
extern void disable_irq(unsigned int irq);
extern void enable_irq(unsigned int irq);
# 95 "include/linux/interrupt.h"
extern void local_bh_enable(void);







enum
{
 HI_SOFTIRQ=0,
 TIMER_SOFTIRQ,
 NET_TX_SOFTIRQ,
 NET_RX_SOFTIRQ,
 SCSI_SOFTIRQ,
 TASKLET_SOFTIRQ
};





struct softirq_action
{
 void (*action)(struct softirq_action *);
 void *data;
};

 __attribute__((regparm(0))) void do_softirq(void);
extern void open_softirq(int nr, void (*action)(struct softirq_action*), void *data);
extern void softirq_init(void);

extern void raise_softirq_irqoff(unsigned int nr) __attribute__((regparm(3)));
extern void raise_softirq(unsigned int nr) __attribute__((regparm(3)));
# 151 "include/linux/interrupt.h"
struct tasklet_struct
{
 struct tasklet_struct *next;
 unsigned long state;
 atomic_t count;
 void (*func)(unsigned long);
 unsigned long data;
};
# 167 "include/linux/interrupt.h"
enum
{
 TASKLET_STATE_SCHED,
 TASKLET_STATE_RUN
};


static inline __attribute__((always_inline)) int tasklet_trylock(struct tasklet_struct *t)
{
 return !test_and_set_bit(TASKLET_STATE_RUN, &(t)->state);
}

static inline __attribute__((always_inline)) void tasklet_unlock(struct tasklet_struct *t)
{
 __asm__ __volatile__("": : :"memory");
 clear_bit(TASKLET_STATE_RUN, &(t)->state);
}

static inline __attribute__((always_inline)) void tasklet_unlock_wait(struct tasklet_struct *t)
{
 while ((__builtin_constant_p(TASKLET_STATE_RUN) ? constant_test_bit((TASKLET_STATE_RUN),(&(t)->state)) : variable_test_bit((TASKLET_STATE_RUN),(&(t)->state)))) { __asm__ __volatile__("": : :"memory"); }
}






extern void __tasklet_schedule(struct tasklet_struct *t) __attribute__((regparm(3)));

static inline __attribute__((always_inline)) void tasklet_schedule(struct tasklet_struct *t)
{
 if (!test_and_set_bit(TASKLET_STATE_SCHED, &t->state))
  __tasklet_schedule(t);
}

extern void __tasklet_hi_schedule(struct tasklet_struct *t) __attribute__((regparm(3)));

static inline __attribute__((always_inline)) void tasklet_hi_schedule(struct tasklet_struct *t)
{
 if (!test_and_set_bit(TASKLET_STATE_SCHED, &t->state))
  __tasklet_hi_schedule(t);
}


static inline __attribute__((always_inline)) void tasklet_disable_nosync(struct tasklet_struct *t)
{
 atomic_inc(&t->count);
 __asm__ __volatile__("": : :"memory");
}

static inline __attribute__((always_inline)) void tasklet_disable(struct tasklet_struct *t)
{
 tasklet_disable_nosync(t);
 tasklet_unlock_wait(t);
 asm volatile ("661:\n\t" "lock; addl $0,0(%%esp)" "\n662:\n" ".section .altinstructions,\"a\"\n" "  .align 4\n" "  .long 661b\n" "  .long 663f\n" "  .byte %c0\n" "  .byte 662b-661b\n" "  .byte 664f-663f\n" ".previous\n" ".section .altinstr_replacement,\"ax\"\n" "663:\n\t" "mfence" "\n664:\n" ".previous" :: "i" ((0*32+26)) : "memory");
}

static inline __attribute__((always_inline)) void tasklet_enable(struct tasklet_struct *t)
{
 __asm__ __volatile__("": : :"memory");
 atomic_dec(&t->count);
}

static inline __attribute__((always_inline)) void tasklet_hi_enable(struct tasklet_struct *t)
{
 __asm__ __volatile__("": : :"memory");
 atomic_dec(&t->count);
}

extern void tasklet_kill(struct tasklet_struct *t);
extern void tasklet_kill_immediate(struct tasklet_struct *t, unsigned int cpu);
extern void tasklet_init(struct tasklet_struct *t,
    void (*func)(unsigned long), unsigned long data);
# 284 "include/linux/interrupt.h"
extern unsigned long probe_irq_on(void);
extern int probe_irq_off(unsigned long);
extern unsigned int probe_irq_mask(unsigned long);
# 509 "include/linux/netdevice.h" 2
# 1 "include/linux/notifier.h" 1
# 14 "include/linux/notifier.h"
struct notifier_block
{
 int (*notifier_call)(struct notifier_block *self, unsigned long, void *);
 struct notifier_block *next;
 int priority;
};




extern int notifier_chain_register(struct notifier_block **list, struct notifier_block *n);
extern int notifier_chain_unregister(struct notifier_block **nl, struct notifier_block *n);
extern int notifier_call_chain(struct notifier_block **n, unsigned long val, void *v);
# 510 "include/linux/netdevice.h" 2

extern struct net_device loopback_dev;
extern struct net_device *dev_base;
extern rwlock_t dev_base_lock;

extern int netdev_boot_setup_check(struct net_device *dev);
extern unsigned long netdev_boot_base(const char *prefix, int unit);
extern struct net_device *dev_getbyhwaddr(unsigned short type, char *hwaddr);
extern struct net_device *dev_getfirstbyhwtype(unsigned short type);
extern void dev_add_pack(struct packet_type *pt);
extern void dev_remove_pack(struct packet_type *pt);
extern void __dev_remove_pack(struct packet_type *pt);

extern struct net_device *dev_get_by_flags(unsigned short flags,
        unsigned short mask);
extern struct net_device *dev_get_by_name(const char *name);
extern struct net_device *__dev_get_by_name(const char *name);
extern int dev_alloc_name(struct net_device *dev, const char *name);
extern int dev_open(struct net_device *dev);
extern int dev_close(struct net_device *dev);
extern int dev_queue_xmit(struct sk_buff *skb);
extern int register_netdevice(struct net_device *dev);
extern int unregister_netdevice(struct net_device *dev);
extern void free_netdev(struct net_device *dev);
extern void synchronize_net(void);
extern int register_netdevice_notifier(struct notifier_block *nb);
extern int unregister_netdevice_notifier(struct notifier_block *nb);
extern int call_netdevice_notifiers(unsigned long val, void *v);
extern struct net_device *dev_get_by_index(int ifindex);
extern struct net_device *__dev_get_by_index(int ifindex);
extern int dev_restart(struct net_device *dev);

extern int netpoll_trap(void);


typedef int gifconf_func_t(struct net_device * dev, char * bufptr, int len);
extern int register_gifconf(unsigned int family, gifconf_func_t * gifconf);
static inline __attribute__((always_inline)) int unregister_gifconf(unsigned int family)
{
 return register_gifconf(family, ((void *)0));
}






struct softnet_data
{
 struct net_device *output_queue;
 struct sk_buff_head input_pkt_queue;
 struct list_head poll_list;
 struct sk_buff *completion_queue;

 struct net_device backlog_dev;
};

extern __typeof__(struct softnet_data) per_cpu__softnet_data;



static inline __attribute__((always_inline)) void __netif_schedule(struct net_device *dev)
{
 if (!test_and_set_bit(__LINK_STATE_SCHED, &dev->state)) {
  unsigned long flags;
  struct softnet_data *sd;

  __asm__ __volatile__("pushfl ; popl %0 ; cli":"=g" (flags): :"memory");
  sd = &(*({ unsigned long __ptr; __asm__ ("" : "=g"(__ptr) : "0"(&per_cpu__softnet_data)); (typeof(&per_cpu__softnet_data)) (__ptr + (__per_cpu_offset[(current_thread_info()->cpu)])); }));
  dev->next_sched = sd->output_queue;
  sd->output_queue = dev;
  raise_softirq_irqoff(NET_TX_SOFTIRQ);
  do { ({ unsigned long __dummy; typeof(flags) __dummy2; (void)(&__dummy == &__dummy2); 1; }); __asm__ __volatile__("pushl %0 ; popfl": :"g" (flags):"memory", "cc"); } while (0);
 }
}

static inline __attribute__((always_inline)) void netif_schedule(struct net_device *dev)
{
 if (!(__builtin_constant_p(__LINK_STATE_XOFF) ? constant_test_bit((__LINK_STATE_XOFF),(&dev->state)) : variable_test_bit((__LINK_STATE_XOFF),(&dev->state))))
  __netif_schedule(dev);
}

static inline __attribute__((always_inline)) void netif_start_queue(struct net_device *dev)
{
 clear_bit(__LINK_STATE_XOFF, &dev->state);
}

static inline __attribute__((always_inline)) void netif_wake_queue(struct net_device *dev)
{

 if (netpoll_trap())
  return;

 if (test_and_clear_bit(__LINK_STATE_XOFF, &dev->state))
  __netif_schedule(dev);
}

static inline __attribute__((always_inline)) void netif_stop_queue(struct net_device *dev)
{

 if (netpoll_trap())
  return;

 set_bit(__LINK_STATE_XOFF, &dev->state);
}

static inline __attribute__((always_inline)) int netif_queue_stopped(const struct net_device *dev)
{
 return (__builtin_constant_p(__LINK_STATE_XOFF) ? constant_test_bit((__LINK_STATE_XOFF),(&dev->state)) : variable_test_bit((__LINK_STATE_XOFF),(&dev->state)));
}

static inline __attribute__((always_inline)) int netif_running(const struct net_device *dev)
{
 return (__builtin_constant_p(__LINK_STATE_START) ? constant_test_bit((__LINK_STATE_START),(&dev->state)) : variable_test_bit((__LINK_STATE_START),(&dev->state)));
}





static inline __attribute__((always_inline)) void dev_kfree_skb_irq(struct sk_buff *skb)
{
 if (atomic_dec_and_test(&skb->users)) {
  struct softnet_data *sd;
  unsigned long flags;

  __asm__ __volatile__("pushfl ; popl %0 ; cli":"=g" (flags): :"memory");
  sd = &(*({ unsigned long __ptr; __asm__ ("" : "=g"(__ptr) : "0"(&per_cpu__softnet_data)); (typeof(&per_cpu__softnet_data)) (__ptr + (__per_cpu_offset[(current_thread_info()->cpu)])); }));
  skb->next = sd->completion_queue;
  sd->completion_queue = skb;
  raise_softirq_irqoff(NET_TX_SOFTIRQ);
  do { ({ unsigned long __dummy; typeof(flags) __dummy2; (void)(&__dummy == &__dummy2); 1; }); __asm__ __volatile__("pushl %0 ; popfl": :"g" (flags):"memory", "cc"); } while (0);
 }
}




static inline __attribute__((always_inline)) void dev_kfree_skb_any(struct sk_buff *skb)
{
 if ((((current_thread_info()->preempt_count) & (((1UL << (12))-1) << ((0 + 8) + 8)))) || ({ unsigned long flags; do { ({ unsigned long __dummy; typeof(flags) __dummy2; (void)(&__dummy == &__dummy2); 1; }); __asm__ __volatile__("pushfl ; popl %0":"=g" (flags): ); } while (0); !(flags & (1<<9)); }))
  dev_kfree_skb_irq(skb);
 else
  kfree_skb(skb);
}


extern int netif_rx(struct sk_buff *skb);
extern int netif_rx_ni(struct sk_buff *skb);

extern int netif_receive_skb(struct sk_buff *skb);
extern int dev_ioctl(unsigned int cmd, void *);
extern int dev_ethtool(struct ifreq *);
extern unsigned dev_get_flags(const struct net_device *);
extern int dev_change_flags(struct net_device *, unsigned);
extern int dev_change_name(struct net_device *, char *);
extern int dev_set_mtu(struct net_device *, int);
extern int dev_set_mac_address(struct net_device *,
         struct sockaddr *);
extern void dev_queue_xmit_nit(struct sk_buff *skb, struct net_device *dev);

extern void dev_init(void);

extern int netdev_nit;


extern void netdev_run_todo(void);

static inline __attribute__((always_inline)) void dev_put(struct net_device *dev)
{
 atomic_dec(&dev->refcnt);
}
# 691 "include/linux/netdevice.h"
extern void linkwatch_fire_event(struct net_device *dev);

static inline __attribute__((always_inline)) int netif_carrier_ok(const struct net_device *dev)
{
 return !(__builtin_constant_p(__LINK_STATE_NOCARRIER) ? constant_test_bit((__LINK_STATE_NOCARRIER),(&dev->state)) : variable_test_bit((__LINK_STATE_NOCARRIER),(&dev->state)));
}

extern void __netdev_watchdog_up(struct net_device *dev);

static inline __attribute__((always_inline)) void netif_carrier_on(struct net_device *dev)
{
 if (test_and_clear_bit(__LINK_STATE_NOCARRIER, &dev->state))
  linkwatch_fire_event(dev);
 if (netif_running(dev))
  __netdev_watchdog_up(dev);
}

static inline __attribute__((always_inline)) void netif_carrier_off(struct net_device *dev)
{
 if (!test_and_set_bit(__LINK_STATE_NOCARRIER, &dev->state))
  linkwatch_fire_event(dev);
}


static inline __attribute__((always_inline)) int netif_device_present(struct net_device *dev)
{
 return (__builtin_constant_p(__LINK_STATE_PRESENT) ? constant_test_bit((__LINK_STATE_PRESENT),(&dev->state)) : variable_test_bit((__LINK_STATE_PRESENT),(&dev->state)));
}

static inline __attribute__((always_inline)) void netif_device_detach(struct net_device *dev)
{
 if (test_and_clear_bit(__LINK_STATE_PRESENT, &dev->state) &&
     netif_running(dev)) {
  netif_stop_queue(dev);
 }
}

static inline __attribute__((always_inline)) void netif_device_attach(struct net_device *dev)
{
 if (!test_and_set_bit(__LINK_STATE_PRESENT, &dev->state) &&
     netif_running(dev)) {
  netif_wake_queue(dev);
   __netdev_watchdog_up(dev);
 }
}






enum {
 NETIF_MSG_DRV = 0x0001,
 NETIF_MSG_PROBE = 0x0002,
 NETIF_MSG_LINK = 0x0004,
 NETIF_MSG_TIMER = 0x0008,
 NETIF_MSG_IFDOWN = 0x0010,
 NETIF_MSG_IFUP = 0x0020,
 NETIF_MSG_RX_ERR = 0x0040,
 NETIF_MSG_TX_ERR = 0x0080,
 NETIF_MSG_TX_QUEUED = 0x0100,
 NETIF_MSG_INTR = 0x0200,
 NETIF_MSG_TX_DONE = 0x0400,
 NETIF_MSG_RX_STATUS = 0x0800,
 NETIF_MSG_PKTDATA = 0x1000,
 NETIF_MSG_HW = 0x2000,
 NETIF_MSG_WOL = 0x4000,
};
# 776 "include/linux/netdevice.h"
static inline __attribute__((always_inline)) u32 netif_msg_init(int debug_value, int default_msg_enable_bits)
{

 if (debug_value < 0 || debug_value >= (sizeof(u32) * 8))
  return default_msg_enable_bits;
 if (debug_value == 0)
  return 0;

 return (1 << debug_value) - 1;
}



static inline __attribute__((always_inline)) int netif_rx_schedule_prep(struct net_device *dev)
{
 return netif_running(dev) &&
  !test_and_set_bit(__LINK_STATE_RX_SCHED, &dev->state);
}





static inline __attribute__((always_inline)) void __netif_rx_schedule(struct net_device *dev)
{
 unsigned long flags;

 __asm__ __volatile__("pushfl ; popl %0 ; cli":"=g" (flags): :"memory");
 atomic_inc(&(dev)->refcnt);
 list_add_tail(&dev->poll_list, &(*({ unsigned long __ptr; __asm__ ("" : "=g"(__ptr) : "0"(&per_cpu__softnet_data)); (typeof(&per_cpu__softnet_data)) (__ptr + (__per_cpu_offset[(current_thread_info()->cpu)])); })).poll_list);
 if (dev->quota < 0)
  dev->quota += dev->weight;
 else
  dev->quota = dev->weight;
 do { ((*({ unsigned long __ptr; __asm__ ("" : "=g"(__ptr) : "0"(&per_cpu__irq_stat)); (typeof(&per_cpu__irq_stat)) (__ptr + (__per_cpu_offset[(current_thread_info()->cpu)])); })).__softirq_pending) |= 1UL << (NET_RX_SOFTIRQ); } while (0);
 do { ({ unsigned long __dummy; typeof(flags) __dummy2; (void)(&__dummy == &__dummy2); 1; }); __asm__ __volatile__("pushl %0 ; popfl": :"g" (flags):"memory", "cc"); } while (0);
}



static inline __attribute__((always_inline)) void netif_rx_schedule(struct net_device *dev)
{
 if (netif_rx_schedule_prep(dev))
  __netif_rx_schedule(dev);
}




static inline __attribute__((always_inline)) int netif_rx_reschedule(struct net_device *dev, int undo)
{
 if (netif_rx_schedule_prep(dev)) {
  unsigned long flags;

  dev->quota += undo;

  __asm__ __volatile__("pushfl ; popl %0 ; cli":"=g" (flags): :"memory");
  list_add_tail(&dev->poll_list, &(*({ unsigned long __ptr; __asm__ ("" : "=g"(__ptr) : "0"(&per_cpu__softnet_data)); (typeof(&per_cpu__softnet_data)) (__ptr + (__per_cpu_offset[(current_thread_info()->cpu)])); })).poll_list);
  do { ((*({ unsigned long __ptr; __asm__ ("" : "=g"(__ptr) : "0"(&per_cpu__irq_stat)); (typeof(&per_cpu__irq_stat)) (__ptr + (__per_cpu_offset[(current_thread_info()->cpu)])); })).__softirq_pending) |= 1UL << (NET_RX_SOFTIRQ); } while (0);
  do { ({ unsigned long __dummy; typeof(flags) __dummy2; (void)(&__dummy == &__dummy2); 1; }); __asm__ __volatile__("pushl %0 ; popfl": :"g" (flags):"memory", "cc"); } while (0);
  return 1;
 }
 return 0;
}






static inline __attribute__((always_inline)) void netif_rx_complete(struct net_device *dev)
{
 unsigned long flags;

 __asm__ __volatile__("pushfl ; popl %0 ; cli":"=g" (flags): :"memory");
 do { if (__builtin_expect(!!((!(__builtin_constant_p(__LINK_STATE_RX_SCHED) ? constant_test_bit((__LINK_STATE_RX_SCHED),(&dev->state)) : variable_test_bit((__LINK_STATE_RX_SCHED),(&dev->state))))!=0), 0)) __BUG(); } while(0);
 list_del(&dev->poll_list);
 __asm__ __volatile__("": : :"memory");
 clear_bit(__LINK_STATE_RX_SCHED, &dev->state);
 do { ({ unsigned long __dummy; typeof(flags) __dummy2; (void)(&__dummy == &__dummy2); 1; }); __asm__ __volatile__("pushl %0 ; popfl": :"g" (flags):"memory", "cc"); } while (0);
}

static inline __attribute__((always_inline)) void netif_poll_disable(struct net_device *dev)
{
 while (test_and_set_bit(__LINK_STATE_RX_SCHED, &dev->state)) {

  get_current()->state = 1;
  schedule_timeout(1);
 }
}

static inline __attribute__((always_inline)) void netif_poll_enable(struct net_device *dev)
{
 clear_bit(__LINK_STATE_RX_SCHED, &dev->state);
}




static inline __attribute__((always_inline)) void __netif_rx_complete(struct net_device *dev)
{
 do { if (__builtin_expect(!!((!(__builtin_constant_p(__LINK_STATE_RX_SCHED) ? constant_test_bit((__LINK_STATE_RX_SCHED),(&dev->state)) : variable_test_bit((__LINK_STATE_RX_SCHED),(&dev->state))))!=0), 0)) __BUG(); } while(0);
 list_del(&dev->poll_list);
 __asm__ __volatile__("": : :"memory");
 clear_bit(__LINK_STATE_RX_SCHED, &dev->state);
}

static inline __attribute__((always_inline)) void netif_tx_disable(struct net_device *dev)
{
 _spin_lock_bh(&dev->xmit_lock);
 netif_stop_queue(dev);
 _spin_unlock_bh(&dev->xmit_lock);
}



extern void ether_setup(struct net_device *dev);


extern struct net_device *alloc_netdev(int sizeof_priv, const char *name,
           void (*setup)(struct net_device *));
extern int register_netdev(struct net_device *dev);
extern void unregister_netdev(struct net_device *dev);

extern void dev_mc_upload(struct net_device *dev);
extern int dev_mc_delete(struct net_device *dev, void *addr, int alen, int all);
extern int dev_mc_add(struct net_device *dev, void *addr, int alen, int newonly);
extern void dev_mc_discard(struct net_device *dev);
extern void dev_set_promiscuity(struct net_device *dev, int inc);
extern void dev_set_allmulti(struct net_device *dev, int inc);
extern void netdev_state_change(struct net_device *dev);
extern void netdev_features_change(struct net_device *dev);

extern void dev_load(const char *name);
extern void dev_mcast_init(void);
extern int netdev_max_backlog;
extern int weight_p;
extern int netdev_set_master(struct net_device *dev, struct net_device *master);
extern int skb_checksum_help(struct sk_buff *skb, int inward);

extern void net_enable_timestamp(void);
extern void net_disable_timestamp(void);
# 39 "net/ipv6/tcp_ipv6.c" 2

# 1 "include/linux/jhash.h" 1
# 44 "include/linux/jhash.h"
static inline __attribute__((always_inline)) u32 jhash(const void *key, u32 length, u32 initval)
{
 u32 a, b, c, len;
 const u8 *k = key;

 len = length;
 a = b = 0x9e3779b9;
 c = initval;

 while (len >= 12) {
  a += (k[0] +((u32)k[1]<<8) +((u32)k[2]<<16) +((u32)k[3]<<24));
  b += (k[4] +((u32)k[5]<<8) +((u32)k[6]<<16) +((u32)k[7]<<24));
  c += (k[8] +((u32)k[9]<<8) +((u32)k[10]<<16)+((u32)k[11]<<24));

  { a -= b; a -= c; a ^= (c>>13); b -= c; b -= a; b ^= (a<<8); c -= a; c -= b; c ^= (b>>13); a -= b; a -= c; a ^= (c>>12); b -= c; b -= a; b ^= (a<<16); c -= a; c -= b; c ^= (b>>5); a -= b; a -= c; a ^= (c>>3); b -= c; b -= a; b ^= (a<<10); c -= a; c -= b; c ^= (b>>15); };

  k += 12;
  len -= 12;
 }

 c += length;
 switch (len) {
 case 11: c += ((u32)k[10]<<24);
 case 10: c += ((u32)k[9]<<16);
 case 9 : c += ((u32)k[8]<<8);
 case 8 : b += ((u32)k[7]<<24);
 case 7 : b += ((u32)k[6]<<16);
 case 6 : b += ((u32)k[5]<<8);
 case 5 : b += k[4];
 case 4 : a += ((u32)k[3]<<24);
 case 3 : a += ((u32)k[2]<<16);
 case 2 : a += ((u32)k[1]<<8);
 case 1 : a += k[0];
 };

 { a -= b; a -= c; a ^= (c>>13); b -= c; b -= a; b ^= (a<<8); c -= a; c -= b; c ^= (b>>13); a -= b; a -= c; a ^= (c>>12); b -= c; b -= a; b ^= (a<<16); c -= a; c -= b; c ^= (b>>5); a -= b; a -= c; a ^= (c>>3); b -= c; b -= a; b ^= (a<<10); c -= a; c -= b; c ^= (b>>15); };

 return c;
}




static inline __attribute__((always_inline)) u32 jhash2(u32 *k, u32 length, u32 initval)
{
 u32 a, b, c, len;

 a = b = 0x9e3779b9;
 c = initval;
 len = length;

 while (len >= 3) {
  a += k[0];
  b += k[1];
  c += k[2];
  { a -= b; a -= c; a ^= (c>>13); b -= c; b -= a; b ^= (a<<8); c -= a; c -= b; c ^= (b>>13); a -= b; a -= c; a ^= (c>>12); b -= c; b -= a; b ^= (a<<16); c -= a; c -= b; c ^= (b>>5); a -= b; a -= c; a ^= (c>>3); b -= c; b -= a; b ^= (a<<10); c -= a; c -= b; c ^= (b>>15); };
  k += 3; len -= 3;
 }

 c += length * 4;

 switch (len) {
 case 2 : b += k[1];
 case 1 : a += k[0];
 };

 { a -= b; a -= c; a ^= (c>>13); b -= c; b -= a; b ^= (a<<8); c -= a; c -= b; c ^= (b>>13); a -= b; a -= c; a ^= (c>>12); b -= c; b -= a; b ^= (a<<16); c -= a; c -= b; c ^= (b>>5); a -= b; a -= c; a ^= (c>>3); b -= c; b -= a; b ^= (a<<10); c -= a; c -= b; c ^= (b>>15); };

 return c;
}
# 122 "include/linux/jhash.h"
static inline __attribute__((always_inline)) u32 jhash_3words(u32 a, u32 b, u32 c, u32 initval)
{
 a += 0x9e3779b9;
 b += 0x9e3779b9;
 c += initval;

 { a -= b; a -= c; a ^= (c>>13); b -= c; b -= a; b ^= (a<<8); c -= a; c -= b; c ^= (b>>13); a -= b; a -= c; a ^= (c>>12); b -= c; b -= a; b ^= (a<<16); c -= a; c -= b; c ^= (b>>5); a -= b; a -= c; a ^= (c>>3); b -= c; b -= a; b ^= (a<<10); c -= a; c -= b; c ^= (b>>15); };

 return c;
}

static inline __attribute__((always_inline)) u32 jhash_2words(u32 a, u32 b, u32 initval)
{
 return jhash_3words(a, b, 0, initval);
}

static inline __attribute__((always_inline)) u32 jhash_1word(u32 a, u32 initval)
{
 return jhash_3words(a, 0, 0, initval);
}
# 41 "net/ipv6/tcp_ipv6.c" 2
# 1 "include/linux/ipsec.h" 1





# 1 "include/linux/pfkeyv2.h" 1
# 14 "include/linux/pfkeyv2.h"
struct sadb_msg {
 uint8_t sadb_msg_version;
 uint8_t sadb_msg_type;
 uint8_t sadb_msg_errno;
 uint8_t sadb_msg_satype;
 uint16_t sadb_msg_len;
 uint16_t sadb_msg_reserved;
 uint32_t sadb_msg_seq;
 uint32_t sadb_msg_pid;
} __attribute__((packed));


struct sadb_ext {
 uint16_t sadb_ext_len;
 uint16_t sadb_ext_type;
} __attribute__((packed));


struct sadb_sa {
 uint16_t sadb_sa_len;
 uint16_t sadb_sa_exttype;
 uint32_t sadb_sa_spi;
 uint8_t sadb_sa_replay;
 uint8_t sadb_sa_state;
 uint8_t sadb_sa_auth;
 uint8_t sadb_sa_encrypt;
 uint32_t sadb_sa_flags;
} __attribute__((packed));


struct sadb_lifetime {
 uint16_t sadb_lifetime_len;
 uint16_t sadb_lifetime_exttype;
 uint32_t sadb_lifetime_allocations;
 uint64_t sadb_lifetime_bytes;
 uint64_t sadb_lifetime_addtime;
 uint64_t sadb_lifetime_usetime;
} __attribute__((packed));


struct sadb_address {
 uint16_t sadb_address_len;
 uint16_t sadb_address_exttype;
 uint8_t sadb_address_proto;
 uint8_t sadb_address_prefixlen;
 uint16_t sadb_address_reserved;
} __attribute__((packed));


struct sadb_key {
 uint16_t sadb_key_len;
 uint16_t sadb_key_exttype;
 uint16_t sadb_key_bits;
 uint16_t sadb_key_reserved;
} __attribute__((packed));


struct sadb_ident {
 uint16_t sadb_ident_len;
 uint16_t sadb_ident_exttype;
 uint16_t sadb_ident_type;
 uint16_t sadb_ident_reserved;
 uint64_t sadb_ident_id;
} __attribute__((packed));


struct sadb_sens {
 uint16_t sadb_sens_len;
 uint16_t sadb_sens_exttype;
 uint32_t sadb_sens_dpd;
 uint8_t sadb_sens_sens_level;
 uint8_t sadb_sens_sens_len;
 uint8_t sadb_sens_integ_level;
 uint8_t sadb_sens_integ_len;
 uint32_t sadb_sens_reserved;
} __attribute__((packed));






struct sadb_prop {
 uint16_t sadb_prop_len;
 uint16_t sadb_prop_exttype;
 uint8_t sadb_prop_replay;
 uint8_t sadb_prop_reserved[3];
} __attribute__((packed));







struct sadb_comb {
 uint8_t sadb_comb_auth;
 uint8_t sadb_comb_encrypt;
 uint16_t sadb_comb_flags;
 uint16_t sadb_comb_auth_minbits;
 uint16_t sadb_comb_auth_maxbits;
 uint16_t sadb_comb_encrypt_minbits;
 uint16_t sadb_comb_encrypt_maxbits;
 uint32_t sadb_comb_reserved;
 uint32_t sadb_comb_soft_allocations;
 uint32_t sadb_comb_hard_allocations;
 uint64_t sadb_comb_soft_bytes;
 uint64_t sadb_comb_hard_bytes;
 uint64_t sadb_comb_soft_addtime;
 uint64_t sadb_comb_hard_addtime;
 uint64_t sadb_comb_soft_usetime;
 uint64_t sadb_comb_hard_usetime;
} __attribute__((packed));


struct sadb_supported {
 uint16_t sadb_supported_len;
 uint16_t sadb_supported_exttype;
 uint32_t sadb_supported_reserved;
} __attribute__((packed));







struct sadb_alg {
 uint8_t sadb_alg_id;
 uint8_t sadb_alg_ivlen;
 uint16_t sadb_alg_minbits;
 uint16_t sadb_alg_maxbits;
 uint16_t sadb_alg_reserved;
} __attribute__((packed));


struct sadb_spirange {
 uint16_t sadb_spirange_len;
 uint16_t sadb_spirange_exttype;
 uint32_t sadb_spirange_min;
 uint32_t sadb_spirange_max;
 uint32_t sadb_spirange_reserved;
} __attribute__((packed));


struct sadb_x_kmprivate {
 uint16_t sadb_x_kmprivate_len;
 uint16_t sadb_x_kmprivate_exttype;
 u_int32_t sadb_x_kmprivate_reserved;
} __attribute__((packed));


struct sadb_x_sa2 {
 uint16_t sadb_x_sa2_len;
 uint16_t sadb_x_sa2_exttype;
 uint8_t sadb_x_sa2_mode;
 uint8_t sadb_x_sa2_reserved1;
 uint16_t sadb_x_sa2_reserved2;
 uint32_t sadb_x_sa2_sequence;
 uint32_t sadb_x_sa2_reqid;
} __attribute__((packed));


struct sadb_x_policy {
 uint16_t sadb_x_policy_len;
 uint16_t sadb_x_policy_exttype;
 uint16_t sadb_x_policy_type;
 uint8_t sadb_x_policy_dir;
 uint8_t sadb_x_policy_reserved;
 uint32_t sadb_x_policy_id;
 uint32_t sadb_x_policy_priority;
} __attribute__((packed));


struct sadb_x_ipsecrequest {
 uint16_t sadb_x_ipsecrequest_len;
 uint16_t sadb_x_ipsecrequest_proto;
 uint8_t sadb_x_ipsecrequest_mode;
 uint8_t sadb_x_ipsecrequest_level;
 uint16_t sadb_x_ipsecrequest_reserved1;
 uint32_t sadb_x_ipsecrequest_reqid;
 uint32_t sadb_x_ipsecrequest_reserved2;
} __attribute__((packed));





struct sadb_x_nat_t_type {
 uint16_t sadb_x_nat_t_type_len;
 uint16_t sadb_x_nat_t_type_exttype;
 uint8_t sadb_x_nat_t_type_type;
 uint8_t sadb_x_nat_t_type_reserved[3];
} __attribute__((packed));



struct sadb_x_nat_t_port {
 uint16_t sadb_x_nat_t_port_len;
 uint16_t sadb_x_nat_t_port_exttype;
 uint16_t sadb_x_nat_t_port_port;
 uint16_t sadb_x_nat_t_port_reserved;
} __attribute__((packed));
# 7 "include/linux/ipsec.h" 2





enum {
 IPSEC_MODE_ANY = 0,
 IPSEC_MODE_TRANSPORT = 1,
 IPSEC_MODE_TUNNEL = 2
};

enum {
 IPSEC_DIR_ANY = 0,
 IPSEC_DIR_INBOUND = 1,
 IPSEC_DIR_OUTBOUND = 2,
 IPSEC_DIR_FWD = 3,
 IPSEC_DIR_MAX = 4,
 IPSEC_DIR_INVALID = 5
};

enum {
 IPSEC_POLICY_DISCARD = 0,
 IPSEC_POLICY_NONE = 1,
 IPSEC_POLICY_IPSEC = 2,
 IPSEC_POLICY_ENTRUST = 3,
 IPSEC_POLICY_BYPASS = 4
};

enum {
 IPSEC_LEVEL_DEFAULT = 0,
 IPSEC_LEVEL_USE = 1,
 IPSEC_LEVEL_REQUIRE = 2,
 IPSEC_LEVEL_UNIQUE = 3
};
# 42 "net/ipv6/tcp_ipv6.c" 2
# 1 "include/linux/times.h" 1





struct tms {
 clock_t tms_utime;
 clock_t tms_stime;
 clock_t tms_cutime;
 clock_t tms_cstime;
};
# 43 "net/ipv6/tcp_ipv6.c" 2

# 1 "include/linux/ipv6.h" 1
# 19 "include/linux/ipv6.h"
struct in6_pktinfo {
 struct in6_addr ipi6_addr;
 int ipi6_ifindex;
};


struct in6_ifreq {
 struct in6_addr ifr6_addr;
 __u32 ifr6_prefixlen;
 int ifr6_ifindex;
};







struct ipv6_rt_hdr {
 __u8 nexthdr;
 __u8 hdrlen;
 __u8 type;
 __u8 segments_left;





};


struct ipv6_opt_hdr {
 __u8 nexthdr;
 __u8 hdrlen;



};
# 69 "include/linux/ipv6.h"
struct rt0_hdr {
 struct ipv6_rt_hdr rt_hdr;
 __u32 bitmap;
 struct in6_addr addr[0];


};

struct ipv6_auth_hdr {
 __u8 nexthdr;
 __u8 hdrlen;
 __u16 reserved;
 __u32 spi;
 __u32 seq_no;
 __u8 auth_data[0];
};

struct ipv6_esp_hdr {
 __u32 spi;
 __u32 seq_no;
 __u8 enc_data[0];
};

struct ipv6_comp_hdr {
 __u8 nexthdr;
 __u8 flags;
 __u16 cpi;
};
# 105 "include/linux/ipv6.h"
struct ipv6hdr {

 __u8 priority:4,
    version:4;






 __u8 flow_lbl[3];

 __u16 payload_len;
 __u8 nexthdr;
 __u8 hop_limit;

 struct in6_addr saddr;
 struct in6_addr daddr;
};




struct ipv6_devconf {
 __s32 forwarding;
 __s32 hop_limit;
 __s32 mtu6;
 __s32 accept_ra;
 __s32 accept_redirects;
 __s32 autoconf;
 __s32 dad_transmits;
 __s32 rtr_solicits;
 __s32 rtr_solicit_interval;
 __s32 rtr_solicit_delay;
 __s32 force_mld_version;

 __s32 use_tempaddr;
 __s32 temp_valid_lft;
 __s32 temp_prefered_lft;
 __s32 regen_max_retry;
 __s32 max_desync_factor;

 __s32 max_addresses;
 void *sysctl;
};


enum {
 DEVCONF_FORWARDING = 0,
 DEVCONF_HOPLIMIT,
 DEVCONF_MTU6,
 DEVCONF_ACCEPT_RA,
 DEVCONF_ACCEPT_REDIRECTS,
 DEVCONF_AUTOCONF,
 DEVCONF_DAD_TRANSMITS,
 DEVCONF_RTR_SOLICITS,
 DEVCONF_RTR_SOLICIT_INTERVAL,
 DEVCONF_RTR_SOLICIT_DELAY,
 DEVCONF_USE_TEMPADDR,
 DEVCONF_TEMP_VALID_LFT,
 DEVCONF_TEMP_PREFERED_LFT,
 DEVCONF_REGEN_MAX_RETRY,
 DEVCONF_MAX_DESYNC_FACTOR,
 DEVCONF_MAX_ADDRESSES,
 DEVCONF_FORCE_MLD_VERSION,
 DEVCONF_MAX
};



# 1 "include/linux/icmpv6.h" 1





struct icmp6hdr {

 __u8 icmp6_type;
 __u8 icmp6_code;
 __u16 icmp6_cksum;


 union {
  __u32 un_data32[1];
  __u16 un_data16[2];
  __u8 un_data8[4];

  struct icmpv6_echo {
   __u16 identifier;
   __u16 sequence;
  } u_echo;

                struct icmpv6_nd_advt {

                        __u32 reserved:5,
                          override:1,
                          solicited:1,
                          router:1,
     reserved2:24;
# 38 "include/linux/icmpv6.h"
                } u_nd_advt;

                struct icmpv6_nd_ra {
   __u8 hop_limit;

   __u8 reserved:6,
     other:1,
     managed:1;
# 54 "include/linux/icmpv6.h"
   __u16 rt_lifetime;
                } u_nd_ra;

 } icmp6_dataun;
# 73 "include/linux/icmpv6.h"
};
# 136 "include/linux/icmpv6.h"
struct icmp6_filter {
 __u32 data[8];
};
# 158 "include/linux/icmpv6.h"
extern void icmpv6_send(struct sk_buff *skb,
          int type, int code,
          __u32 info,
          struct net_device *dev);

extern int icmpv6_init(struct net_proto_family *ops);
extern int icmpv6_err_convert(int type, int code,
          int *err);
extern void icmpv6_cleanup(void);
extern void icmpv6_param_prob(struct sk_buff *skb,
         int code, int pos);
# 176 "include/linux/ipv6.h" 2
# 1 "include/net/if_inet6.h" 1
# 18 "include/net/if_inet6.h"
# 1 "include/net/snmp.h" 1
# 25 "include/net/snmp.h"
# 1 "include/linux/snmp.h" 1
# 18 "include/linux/snmp.h"
enum
{
 IPSTATS_MIB_NUM = 0,
 IPSTATS_MIB_INRECEIVES,
 IPSTATS_MIB_INHDRERRORS,
 IPSTATS_MIB_INTOOBIGERRORS,
 IPSTATS_MIB_INNOROUTES,
 IPSTATS_MIB_INADDRERRORS,
 IPSTATS_MIB_INUNKNOWNPROTOS,
 IPSTATS_MIB_INTRUNCATEDPKTS,
 IPSTATS_MIB_INDISCARDS,
 IPSTATS_MIB_INDELIVERS,
 IPSTATS_MIB_OUTFORWDATAGRAMS,
 IPSTATS_MIB_OUTREQUESTS,
 IPSTATS_MIB_OUTDISCARDS,
 IPSTATS_MIB_OUTNOROUTES,
 IPSTATS_MIB_REASMTIMEOUT,
 IPSTATS_MIB_REASMREQDS,
 IPSTATS_MIB_REASMOKS,
 IPSTATS_MIB_REASMFAILS,
 IPSTATS_MIB_FRAGOKS,
 IPSTATS_MIB_FRAGFAILS,
 IPSTATS_MIB_FRAGCREATES,
 IPSTATS_MIB_INMCASTPKTS,
 IPSTATS_MIB_OUTMCASTPKTS,
 __IPSTATS_MIB_MAX
};






enum
{
 ICMP_MIB_NUM = 0,
 ICMP_MIB_INMSGS,
 ICMP_MIB_INERRORS,
 ICMP_MIB_INDESTUNREACHS,
 ICMP_MIB_INTIMEEXCDS,
 ICMP_MIB_INPARMPROBS,
 ICMP_MIB_INSRCQUENCHS,
 ICMP_MIB_INREDIRECTS,
 ICMP_MIB_INECHOS,
 ICMP_MIB_INECHOREPS,
 ICMP_MIB_INTIMESTAMPS,
 ICMP_MIB_INTIMESTAMPREPS,
 ICMP_MIB_INADDRMASKS,
 ICMP_MIB_INADDRMASKREPS,
 ICMP_MIB_OUTMSGS,
 ICMP_MIB_OUTERRORS,
 ICMP_MIB_OUTDESTUNREACHS,
 ICMP_MIB_OUTTIMEEXCDS,
 ICMP_MIB_OUTPARMPROBS,
 ICMP_MIB_OUTSRCQUENCHS,
 ICMP_MIB_OUTREDIRECTS,
 ICMP_MIB_OUTECHOS,
 ICMP_MIB_OUTECHOREPS,
 ICMP_MIB_OUTTIMESTAMPS,
 ICMP_MIB_OUTTIMESTAMPREPS,
 ICMP_MIB_OUTADDRMASKS,
 ICMP_MIB_OUTADDRMASKREPS,
 __ICMP_MIB_MAX
};





enum
{
 ICMP6_MIB_NUM = 0,
 ICMP6_MIB_INMSGS,
 ICMP6_MIB_INERRORS,
 ICMP6_MIB_INDESTUNREACHS,
 ICMP6_MIB_INPKTTOOBIGS,
 ICMP6_MIB_INTIMEEXCDS,
 ICMP6_MIB_INPARMPROBLEMS,
 ICMP6_MIB_INECHOS,
 ICMP6_MIB_INECHOREPLIES,
 ICMP6_MIB_INGROUPMEMBQUERIES,
 ICMP6_MIB_INGROUPMEMBRESPONSES,
 ICMP6_MIB_INGROUPMEMBREDUCTIONS,
 ICMP6_MIB_INROUTERSOLICITS,
 ICMP6_MIB_INROUTERADVERTISEMENTS,
 ICMP6_MIB_INNEIGHBORSOLICITS,
 ICMP6_MIB_INNEIGHBORADVERTISEMENTS,
 ICMP6_MIB_INREDIRECTS,
 ICMP6_MIB_OUTMSGS,
 ICMP6_MIB_OUTDESTUNREACHS,
 ICMP6_MIB_OUTPKTTOOBIGS,
 ICMP6_MIB_OUTTIMEEXCDS,
 ICMP6_MIB_OUTPARMPROBLEMS,
 ICMP6_MIB_OUTECHOREPLIES,
 ICMP6_MIB_OUTROUTERSOLICITS,
 ICMP6_MIB_OUTNEIGHBORSOLICITS,
 ICMP6_MIB_OUTNEIGHBORADVERTISEMENTS,
 ICMP6_MIB_OUTREDIRECTS,
 ICMP6_MIB_OUTGROUPMEMBRESPONSES,
 ICMP6_MIB_OUTGROUPMEMBREDUCTIONS,
 __ICMP6_MIB_MAX
};






enum
{
 TCP_MIB_NUM = 0,
 TCP_MIB_RTOALGORITHM,
 TCP_MIB_RTOMIN,
 TCP_MIB_RTOMAX,
 TCP_MIB_MAXCONN,
 TCP_MIB_ACTIVEOPENS,
 TCP_MIB_PASSIVEOPENS,
 TCP_MIB_ATTEMPTFAILS,
 TCP_MIB_ESTABRESETS,
 TCP_MIB_CURRESTAB,
 TCP_MIB_INSEGS,
 TCP_MIB_OUTSEGS,
 TCP_MIB_RETRANSSEGS,
 TCP_MIB_INERRS,
 TCP_MIB_OUTRSTS,
 __TCP_MIB_MAX
};






enum
{
 UDP_MIB_NUM = 0,
 UDP_MIB_INDATAGRAMS,
 UDP_MIB_NOPORTS,
 UDP_MIB_INERRORS,
 UDP_MIB_OUTDATAGRAMS,
 __UDP_MIB_MAX
};





enum
{
 SCTP_MIB_NUM = 0,
 SCTP_MIB_CURRESTAB,
 SCTP_MIB_ACTIVEESTABS,
 SCTP_MIB_PASSIVEESTABS,
 SCTP_MIB_ABORTEDS,
 SCTP_MIB_SHUTDOWNS,
 SCTP_MIB_OUTOFBLUES,
 SCTP_MIB_CHECKSUMERRORS,
 SCTP_MIB_OUTCTRLCHUNKS,
 SCTP_MIB_OUTORDERCHUNKS,
 SCTP_MIB_OUTUNORDERCHUNKS,
 SCTP_MIB_INCTRLCHUNKS,
 SCTP_MIB_INORDERCHUNKS,
 SCTP_MIB_INUNORDERCHUNKS,
 SCTP_MIB_FRAGUSRMSGS,
 SCTP_MIB_REASMUSRMSGS,
 SCTP_MIB_OUTSCTPPACKS,
 SCTP_MIB_INSCTPPACKS,
 SCTP_MIB_RTOALGORITHM,
 SCTP_MIB_RTOMIN,
 SCTP_MIB_RTOMAX,
 SCTP_MIB_RTOINITIAL,
 SCTP_MIB_VALCOOKIELIFE,
 SCTP_MIB_MAXINITRETR,
 __SCTP_MIB_MAX
};


enum
{
 LINUX_MIB_NUM = 0,
 LINUX_MIB_SYNCOOKIESSENT,
 LINUX_MIB_SYNCOOKIESRECV,
 LINUX_MIB_SYNCOOKIESFAILED,
 LINUX_MIB_EMBRYONICRSTS,
 LINUX_MIB_PRUNECALLED,
 LINUX_MIB_RCVPRUNED,
 LINUX_MIB_OFOPRUNED,
 LINUX_MIB_OUTOFWINDOWICMPS,
 LINUX_MIB_LOCKDROPPEDICMPS,
 LINUX_MIB_ARPFILTER,
 LINUX_MIB_TIMEWAITED,
 LINUX_MIB_TIMEWAITRECYCLED,
 LINUX_MIB_TIMEWAITKILLED,
 LINUX_MIB_PAWSPASSIVEREJECTED,
 LINUX_MIB_PAWSACTIVEREJECTED,
 LINUX_MIB_PAWSESTABREJECTED,
 LINUX_MIB_DELAYEDACKS,
 LINUX_MIB_DELAYEDACKLOCKED,
 LINUX_MIB_DELAYEDACKLOST,
 LINUX_MIB_LISTENOVERFLOWS,
 LINUX_MIB_LISTENDROPS,
 LINUX_MIB_TCPPREQUEUED,
 LINUX_MIB_TCPDIRECTCOPYFROMBACKLOG,
 LINUX_MIB_TCPDIRECTCOPYFROMPREQUEUE,
 LINUX_MIB_TCPPREQUEUEDROPPED,
 LINUX_MIB_TCPHPHITS,
 LINUX_MIB_TCPHPHITSTOUSER,
 LINUX_MIB_TCPPUREACKS,
 LINUX_MIB_TCPHPACKS,
 LINUX_MIB_TCPRENORECOVERY,
 LINUX_MIB_TCPSACKRECOVERY,
 LINUX_MIB_TCPSACKRENEGING,
 LINUX_MIB_TCPFACKREORDER,
 LINUX_MIB_TCPSACKREORDER,
 LINUX_MIB_TCPRENOREORDER,
 LINUX_MIB_TCPTSREORDER,
 LINUX_MIB_TCPFULLUNDO,
 LINUX_MIB_TCPPARTIALUNDO,
 LINUX_MIB_TCPDSACKUNDO,
 LINUX_MIB_TCPLOSSUNDO,
 LINUX_MIB_TCPLOSS,
 LINUX_MIB_TCPLOSTRETRANSMIT,
 LINUX_MIB_TCPRENOFAILURES,
 LINUX_MIB_TCPSACKFAILURES,
 LINUX_MIB_TCPLOSSFAILURES,
 LINUX_MIB_TCPFASTRETRANS,
 LINUX_MIB_TCPFORWARDRETRANS,
 LINUX_MIB_TCPSLOWSTARTRETRANS,
 LINUX_MIB_TCPTIMEOUTS,
 LINUX_MIB_TCPRENORECOVERYFAIL,
 LINUX_MIB_TCPSACKRECOVERYFAIL,
 LINUX_MIB_TCPSCHEDULERFAILED,
 LINUX_MIB_TCPRCVCOLLAPSED,
 LINUX_MIB_TCPDSACKOLDSENT,
 LINUX_MIB_TCPDSACKOFOSENT,
 LINUX_MIB_TCPDSACKRECV,
 LINUX_MIB_TCPDSACKOFORECV,
 LINUX_MIB_TCPABORTONSYN,
 LINUX_MIB_TCPABORTONDATA,
 LINUX_MIB_TCPABORTONCLOSE,
 LINUX_MIB_TCPABORTONMEMORY,
 LINUX_MIB_TCPABORTONTIMEOUT,
 LINUX_MIB_TCPABORTONLINGER,
 LINUX_MIB_TCPABORTFAILED,
 LINUX_MIB_TCPMEMORYPRESSURES,
 __LINUX_MIB_MAX
};
# 26 "include/net/snmp.h" 2
# 35 "include/net/snmp.h"
struct snmp_mib {
 char *name;
 int entry;
};
# 73 "include/net/snmp.h"
struct ipstats_mib {
 unsigned long mibs[__IPSTATS_MIB_MAX];
} __attribute__((__aligned__((1 << (7)))));





struct icmp_mib {
 unsigned long mibs[(__ICMP_MIB_MAX + 1)];
} __attribute__((__aligned__((1 << (7)))));



struct icmpv6_mib {
 unsigned long mibs[__ICMP6_MIB_MAX];
} __attribute__((__aligned__((1 << (7)))));



struct tcp_mib {
 unsigned long mibs[__TCP_MIB_MAX];
} __attribute__((__aligned__((1 << (7)))));



struct udp_mib {
 unsigned long mibs[__UDP_MIB_MAX];
} __attribute__((__aligned__((1 << (7)))));



struct sctp_mib {
 unsigned long mibs[__SCTP_MIB_MAX];
} __attribute__((__aligned__((1 << (7)))));



struct linux_mib {
 unsigned long mibs[__LINUX_MIB_MAX];
};
# 19 "include/net/if_inet6.h" 2
# 1 "include/linux/ipv6.h" 1
# 20 "include/net/if_inet6.h" 2
# 34 "include/net/if_inet6.h"
struct inet6_ifaddr
{
 struct in6_addr addr;
 __u32 prefix_len;

 __u32 valid_lft;
 __u32 prefered_lft;
 unsigned long cstamp;
 unsigned long tstamp;
 atomic_t refcnt;
 spinlock_t lock;

 __u8 probes;
 __u8 flags;

 __u16 scope;

 struct timer_list timer;

 struct inet6_dev *idev;
 struct rt6_info *rt;

 struct inet6_ifaddr *lst_next;
 struct inet6_ifaddr *if_next;


 struct inet6_ifaddr *tmp_next;
 struct inet6_ifaddr *ifpub;
 int regen_count;


 int dead;
};

struct ip6_sf_socklist
{
 unsigned int sl_max;
 unsigned int sl_count;
 struct in6_addr sl_addr[0];
};






struct ipv6_mc_socklist
{
 struct in6_addr addr;
 int ifindex;
 struct ipv6_mc_socklist *next;
 unsigned int sfmode;
 struct ip6_sf_socklist *sflist;
};

struct ip6_sf_list
{
 struct ip6_sf_list *sf_next;
 struct in6_addr sf_addr;
 unsigned long sf_count[2];
 unsigned char sf_gsresp;
 unsigned char sf_oldin;
 unsigned char sf_crcount;
};







struct ifmcaddr6
{
 struct in6_addr mca_addr;
 struct inet6_dev *idev;
 struct ifmcaddr6 *next;
 struct ip6_sf_list *mca_sources;
 struct ip6_sf_list *mca_tomb;
 unsigned int mca_sfmode;
 unsigned long mca_sfcount[2];
 struct timer_list mca_timer;
 unsigned mca_flags;
 int mca_users;
 atomic_t mca_refcnt;
 spinlock_t mca_lock;
 unsigned char mca_crcount;
 unsigned long mca_cstamp;
 unsigned long mca_tstamp;
};



struct ipv6_ac_socklist
{
 struct in6_addr acl_addr;
 int acl_ifindex;
 struct ipv6_ac_socklist *acl_next;
};

struct ifacaddr6
{
 struct in6_addr aca_addr;
 struct inet6_dev *aca_idev;
 struct rt6_info *aca_rt;
 struct ifacaddr6 *aca_next;
 int aca_users;
 atomic_t aca_refcnt;
 spinlock_t aca_lock;
 unsigned long aca_cstamp;
 unsigned long aca_tstamp;
};






struct ipv6_devstat {
 struct proc_dir_entry *proc_dir_entry;
 __typeof__(struct icmpv6_mib) *icmpv6[2];
};

struct inet6_dev
{
 struct net_device *dev;

 struct inet6_ifaddr *addr_list;

 struct ifmcaddr6 *mc_list;
 struct ifmcaddr6 *mc_tomb;
 rwlock_t mc_lock;
 unsigned long mc_v1_seen;
 unsigned long mc_maxdelay;
 unsigned char mc_qrv;
 unsigned char mc_gq_running;
 unsigned char mc_ifc_count;
 struct timer_list mc_gq_timer;
 struct timer_list mc_ifc_timer;

 struct ifacaddr6 *ac_list;
 rwlock_t lock;
 atomic_t refcnt;
 __u32 if_flags;
 int dead;


 u8 rndid[8];
 u8 entropy[8];
 struct timer_list regen_timer;
 struct inet6_ifaddr *tempaddr_list;
 __u8 work_eui64[8];
 __u8 work_digest[16];


 struct neigh_parms *nd_parms;
 struct inet6_dev *next;
 struct ipv6_devconf cnf;
 struct ipv6_devstat stats;
 unsigned long tstamp;
};

extern struct ipv6_devconf ipv6_devconf;

static inline __attribute__((always_inline)) void ipv6_eth_mc_map(struct in6_addr *addr, char *buf)
{






 buf[0]= 0x33;
 buf[1]= 0x33;

 __memcpy(buf + 2,&addr->in6_u.u6_addr32[3],sizeof(__u32));
}

static inline __attribute__((always_inline)) void ipv6_tr_mc_map(struct in6_addr *addr, char *buf)
{


 if (((addr->in6_u.u6_addr8[0] == 0xFF) &&
     ((addr->in6_u.u6_addr8[1] == 0x01) || (addr->in6_u.u6_addr8[1] == 0x02)) &&
      (addr->in6_u.u6_addr16[1] == 0) &&
      (addr->in6_u.u6_addr32[1] == 0) &&
      (addr->in6_u.u6_addr32[2] == 0) &&
      (addr->in6_u.u6_addr16[6] == 0) &&
      (addr->in6_u.u6_addr8[15] == 1)) ||
     ((addr->in6_u.u6_addr8[0] == 0xFF) &&
      (addr->in6_u.u6_addr8[1] == 0x02) &&
      (addr->in6_u.u6_addr16[1] == 0) &&
      (addr->in6_u.u6_addr32[1] == 0) &&
      (addr->in6_u.u6_addr16[4] == 0) &&
      (addr->in6_u.u6_addr8[10] == 0) &&
      (addr->in6_u.u6_addr8[11] == 1) &&
      (addr->in6_u.u6_addr8[12] == 0xff)))
 {
  buf[0]=0xC0;
  buf[1]=0x00;
  buf[2]=0x01;
  buf[3]=0x00;
  buf[4]=0x00;
  buf[5]=0x00;

 } else if ((addr->in6_u.u6_addr8[0] ==0xff) &&
  ((addr->in6_u.u6_addr8[1] & 0xF0) == 0) &&
  (addr->in6_u.u6_addr16[1] == 0) &&
  (addr->in6_u.u6_addr32[1] == 0) &&
  (addr->in6_u.u6_addr32[2] == 0) &&
  (addr->in6_u.u6_addr16[6] == 0) &&
  (addr->in6_u.u6_addr8[15] == 2))
 {
  buf[0]=0xC0;
  buf[1]=0x00;
  buf[2]=0x02;
  buf[3]=0x00;
  buf[4]=0x00;
  buf[5]=0x00;
 } else {
  unsigned char i ;

  i = addr->in6_u.u6_addr8[15] & 7 ;
  buf[0]=0xC0;
  buf[1]=0x00;
  buf[2]=0x00;
  buf[3]=0x01 << i ;
  buf[4]=0x00;
  buf[5]=0x00;
 }
}

static inline __attribute__((always_inline)) void ipv6_arcnet_mc_map(const struct in6_addr *addr, char *buf)
{
 buf[0] = 0x00;
}

static inline __attribute__((always_inline)) void ipv6_ib_mc_map(struct in6_addr *addr, char *buf)
{
 buf[0] = 0;
 buf[1] = 0xff;
 buf[2] = 0xff;
 buf[3] = 0xff;
 buf[4] = 0xff;
 buf[5] = 0x12;
 buf[6] = 0x60;
 buf[7] = 0x1b;
 buf[8] = 0;
 buf[9] = 0;
 __memcpy(buf + 10,addr->in6_u.u6_addr8 + 6,10);
}
# 177 "include/linux/ipv6.h" 2
# 1 "include/linux/tcp.h" 1
# 23 "include/linux/tcp.h"
struct tcphdr {
 __u16 source;
 __u16 dest;
 __u32 seq;
 __u32 ack_seq;

 __u16 res1:4,
  doff:4,
  fin:1,
  syn:1,
  rst:1,
  psh:1,
  ack:1,
  urg:1,
  ece:1,
  cwr:1;
# 53 "include/linux/tcp.h"
 __u16 window;
 __u16 check;
 __u16 urg_ptr;
};


enum {
  TCP_ESTABLISHED = 1,
  TCP_SYN_SENT,
  TCP_SYN_RECV,
  TCP_FIN_WAIT1,
  TCP_FIN_WAIT2,
  TCP_TIME_WAIT,
  TCP_CLOSE,
  TCP_CLOSE_WAIT,
  TCP_LAST_ACK,
  TCP_LISTEN,
  TCP_CLOSING,

  TCP_MAX_STATES
};




enum {
  TCPF_ESTABLISHED = (1 << 1),
  TCPF_SYN_SENT = (1 << 2),
  TCPF_SYN_RECV = (1 << 3),
  TCPF_FIN_WAIT1 = (1 << 4),
  TCPF_FIN_WAIT2 = (1 << 5),
  TCPF_TIME_WAIT = (1 << 6),
  TCPF_CLOSE = (1 << 7),
  TCPF_CLOSE_WAIT = (1 << 8),
  TCPF_LAST_ACK = (1 << 9),
  TCPF_LISTEN = (1 << 10),
  TCPF_CLOSING = (1 << 11)
};






union tcp_word_hdr {
 struct tcphdr hdr;
 __u32 words[5];
};



enum {
 TCP_FLAG_CWR = (( __be32)((__u32)( (((__u32)((0x00800000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x00800000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x00800000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x00800000)) & (__u32)0xff000000UL) >> 24) ))),
 TCP_FLAG_ECE = (( __be32)((__u32)( (((__u32)((0x00400000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x00400000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x00400000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x00400000)) & (__u32)0xff000000UL) >> 24) ))),
 TCP_FLAG_URG = (( __be32)((__u32)( (((__u32)((0x00200000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x00200000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x00200000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x00200000)) & (__u32)0xff000000UL) >> 24) ))),
 TCP_FLAG_ACK = (( __be32)((__u32)( (((__u32)((0x00100000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x00100000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x00100000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x00100000)) & (__u32)0xff000000UL) >> 24) ))),
 TCP_FLAG_PSH = (( __be32)((__u32)( (((__u32)((0x00080000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x00080000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x00080000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x00080000)) & (__u32)0xff000000UL) >> 24) ))),
 TCP_FLAG_RST = (( __be32)((__u32)( (((__u32)((0x00040000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x00040000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x00040000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x00040000)) & (__u32)0xff000000UL) >> 24) ))),
 TCP_FLAG_SYN = (( __be32)((__u32)( (((__u32)((0x00020000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x00020000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x00020000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x00020000)) & (__u32)0xff000000UL) >> 24) ))),
 TCP_FLAG_FIN = (( __be32)((__u32)( (((__u32)((0x00010000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x00010000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x00010000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x00010000)) & (__u32)0xff000000UL) >> 24) ))),
 TCP_RESERVED_BITS = (( __be32)((__u32)( (((__u32)((0x0F000000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x0F000000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x0F000000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x0F000000)) & (__u32)0xff000000UL) >> 24) ))),
 TCP_DATA_OFFSET = (( __be32)((__u32)( (((__u32)((0xF0000000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0xF0000000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0xF0000000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0xF0000000)) & (__u32)0xff000000UL) >> 24) )))
};
# 137 "include/linux/tcp.h"
enum tcp_ca_state
{
 TCP_CA_Open = 0,

 TCP_CA_Disorder = 1,

 TCP_CA_CWR = 2,

 TCP_CA_Recovery = 3,

 TCP_CA_Loss = 4

};

struct tcp_info
{
 __u8 tcpi_state;
 __u8 tcpi_ca_state;
 __u8 tcpi_retransmits;
 __u8 tcpi_probes;
 __u8 tcpi_backoff;
 __u8 tcpi_options;
 __u8 tcpi_snd_wscale : 4, tcpi_rcv_wscale : 4;

 __u32 tcpi_rto;
 __u32 tcpi_ato;
 __u32 tcpi_snd_mss;
 __u32 tcpi_rcv_mss;

 __u32 tcpi_unacked;
 __u32 tcpi_sacked;
 __u32 tcpi_lost;
 __u32 tcpi_retrans;
 __u32 tcpi_fackets;


 __u32 tcpi_last_data_sent;
 __u32 tcpi_last_ack_sent;
 __u32 tcpi_last_data_recv;
 __u32 tcpi_last_ack_recv;


 __u32 tcpi_pmtu;
 __u32 tcpi_rcv_ssthresh;
 __u32 tcpi_rtt;
 __u32 tcpi_rttvar;
 __u32 tcpi_snd_ssthresh;
 __u32 tcpi_snd_cwnd;
 __u32 tcpi_advmss;
 __u32 tcpi_reordering;

 __u32 tcpi_rcv_rtt;
 __u32 tcpi_rcv_space;

 __u32 tcpi_total_retrans;
};





# 1 "include/linux/ip.h" 1
# 84 "include/linux/ip.h"
# 1 "include/net/request_sock.h" 1
# 22 "include/net/request_sock.h"
# 1 "include/net/sock.h" 1
# 50 "include/net/sock.h"
# 1 "include/linux/security.h" 1
# 26 "include/linux/security.h"
# 1 "include/linux/binfmts.h" 1





struct pt_regs;
# 23 "include/linux/binfmts.h"
struct linux_binprm{
 char buf[128];
 struct page *page[32];
 struct mm_struct *mm;
 unsigned long p;
 int sh_bang;
 struct file * file;
 int e_uid, e_gid;
 kernel_cap_t cap_inheritable, cap_permitted, cap_effective;
 void *security;
 int argc, envc;
 char * filename;
 char * interp;


 unsigned interp_flags;
 unsigned interp_data;
 unsigned long loader, exec;
};
# 55 "include/linux/binfmts.h"
struct linux_binfmt {
 struct linux_binfmt * next;
 struct module *module;
 int (*load_binary)(struct linux_binprm *, struct pt_regs * regs);
 int (*load_shlib)(struct file *);
 int (*core_dump)(long signr, struct pt_regs * regs, struct file * file);
 unsigned long min_coredump;
};

extern int register_binfmt(struct linux_binfmt *);
extern int unregister_binfmt(struct linux_binfmt *);

extern int prepare_binprm(struct linux_binprm *);
extern void remove_arg_zero(struct linux_binprm *);
extern int search_binary_handler(struct linux_binprm *,struct pt_regs *);
extern int flush_old_exec(struct linux_binprm * bprm);

extern int suid_dumpable;
# 82 "include/linux/binfmts.h"
extern int setup_arg_pages(struct linux_binprm * bprm,
      unsigned long stack_top,
      int executable_stack);
extern int copy_strings_kernel(int argc,char ** argv,struct linux_binprm *bprm);
extern void compute_creds(struct linux_binprm *binprm);
extern int do_coredump(long signr, int exit_code, struct pt_regs * regs);
extern int set_binfmt(struct linux_binfmt *new);
# 27 "include/linux/security.h" 2



# 1 "include/linux/shm.h" 1
# 19 "include/linux/shm.h"
# 1 "include/asm/shmparam.h" 1
# 20 "include/linux/shm.h" 2


struct shmid_ds {
 struct ipc_perm shm_perm;
 int shm_segsz;
 __kernel_time_t shm_atime;
 __kernel_time_t shm_dtime;
 __kernel_time_t shm_ctime;
 __kernel_ipc_pid_t shm_cpid;
 __kernel_ipc_pid_t shm_lpid;
 unsigned short shm_nattch;
 unsigned short shm_unused;
 void *shm_unused2;
 void *shm_unused3;
};


# 1 "include/asm/shmbuf.h" 1
# 14 "include/asm/shmbuf.h"
struct shmid64_ds {
 struct ipc64_perm shm_perm;
 size_t shm_segsz;
 __kernel_time_t shm_atime;
 unsigned long __unused1;
 __kernel_time_t shm_dtime;
 unsigned long __unused2;
 __kernel_time_t shm_ctime;
 unsigned long __unused3;
 __kernel_pid_t shm_cpid;
 __kernel_pid_t shm_lpid;
 unsigned long shm_nattch;
 unsigned long __unused4;
 unsigned long __unused5;
};

struct shminfo64 {
 unsigned long shmmax;
 unsigned long shmmin;
 unsigned long shmmni;
 unsigned long shmseg;
 unsigned long shmall;
 unsigned long __unused1;
 unsigned long __unused2;
 unsigned long __unused3;
 unsigned long __unused4;
};
# 38 "include/linux/shm.h" 2
# 58 "include/linux/shm.h"
struct shminfo {
 int shmmax;
 int shmmin;
 int shmmni;
 int shmseg;
 int shmall;
};

struct shm_info {
 int used_ids;
 unsigned long shm_tot;
 unsigned long shm_rss;
 unsigned long shm_swp;
 unsigned long swap_attempts;
 unsigned long swap_successes;
};


struct shmid_kernel
{
 struct kern_ipc_perm shm_perm;
 struct file * shm_file;
 int id;
 unsigned long shm_nattch;
 unsigned long shm_segsz;
 time_t shm_atim;
 time_t shm_dtim;
 time_t shm_ctim;
 pid_t shm_cprid;
 pid_t shm_lprid;
 struct user_struct *mlock_user;
};







long do_shmat(int shmid, char *shmaddr, int shmflg, unsigned long *addr);
# 31 "include/linux/security.h" 2
# 1 "include/linux/msg.h" 1
# 16 "include/linux/msg.h"
struct msqid_ds {
 struct ipc_perm msg_perm;
 struct msg *msg_first;
 struct msg *msg_last;
 __kernel_time_t msg_stime;
 __kernel_time_t msg_rtime;
 __kernel_time_t msg_ctime;
 unsigned long msg_lcbytes;
 unsigned long msg_lqbytes;
 unsigned short msg_cbytes;
 unsigned short msg_qnum;
 unsigned short msg_qbytes;
 __kernel_ipc_pid_t msg_lspid;
 __kernel_ipc_pid_t msg_lrpid;
};


# 1 "include/asm/msgbuf.h" 1
# 14 "include/asm/msgbuf.h"
struct msqid64_ds {
 struct ipc64_perm msg_perm;
 __kernel_time_t msg_stime;
 unsigned long __unused1;
 __kernel_time_t msg_rtime;
 unsigned long __unused2;
 __kernel_time_t msg_ctime;
 unsigned long __unused3;
 unsigned long msg_cbytes;
 unsigned long msg_qnum;
 unsigned long msg_qbytes;
 __kernel_pid_t msg_lspid;
 __kernel_pid_t msg_lrpid;
 unsigned long __unused4;
 unsigned long __unused5;
};
# 34 "include/linux/msg.h" 2


struct msgbuf {
 long mtype;
 char mtext[1];
};


struct msginfo {
 int msgpool;
 int msgmap;
 int msgmax;
 int msgmnb;
 int msgmni;
 int msgssz;
 int msgtql;
 unsigned short msgseg;
};
# 68 "include/linux/msg.h"
struct msg_msg {
 struct list_head m_list;
 long m_type;
 int m_ts;
 struct msg_msgseg* next;
 void *security;

};


struct msg_queue {
 struct kern_ipc_perm q_perm;
 time_t q_stime;
 time_t q_rtime;
 time_t q_ctime;
 unsigned long q_cbytes;
 unsigned long q_qnum;
 unsigned long q_qbytes;
 pid_t q_lspid;
 pid_t q_lrpid;

 struct list_head q_messages;
 struct list_head q_receivers;
 struct list_head q_senders;
};
# 32 "include/linux/security.h" 2


struct ctl_table;





extern int cap_capable (struct task_struct *tsk, int cap);
extern int cap_settime (struct timespec *ts, struct timezone *tz);
extern int cap_ptrace (struct task_struct *parent, struct task_struct *child);
extern int cap_capget (struct task_struct *target, kernel_cap_t *effective, kernel_cap_t *inheritable, kernel_cap_t *permitted);
extern int cap_capset_check (struct task_struct *target, kernel_cap_t *effective, kernel_cap_t *inheritable, kernel_cap_t *permitted);
extern void cap_capset_set (struct task_struct *target, kernel_cap_t *effective, kernel_cap_t *inheritable, kernel_cap_t *permitted);
extern int cap_bprm_set_security (struct linux_binprm *bprm);
extern void cap_bprm_apply_creds (struct linux_binprm *bprm, int unsafe);
extern int cap_bprm_secureexec(struct linux_binprm *bprm);
extern int cap_inode_setxattr(struct dentry *dentry, char *name, void *value, size_t size, int flags);
extern int cap_inode_removexattr(struct dentry *dentry, char *name);
extern int cap_task_post_setuid (uid_t old_ruid, uid_t old_euid, uid_t old_suid, int flags);
extern void cap_task_reparent_to_init (struct task_struct *p);
extern int cap_syslog (int type);
extern int cap_vm_enough_memory (long pages);

struct msghdr;
struct sk_buff;
struct sock;
struct sockaddr;
struct socket;

extern int cap_netlink_send(struct sock *sk, struct sk_buff *skb);
extern int cap_netlink_recv(struct sk_buff *skb);
# 81 "include/linux/security.h"
struct nfsctl_arg;
struct sched_param;
struct swap_info_struct;
# 1029 "include/linux/security.h"
struct security_operations {
 int (*ptrace) (struct task_struct * parent, struct task_struct * child);
 int (*capget) (struct task_struct * target,
         kernel_cap_t * effective,
         kernel_cap_t * inheritable, kernel_cap_t * permitted);
 int (*capset_check) (struct task_struct * target,
        kernel_cap_t * effective,
        kernel_cap_t * inheritable,
        kernel_cap_t * permitted);
 void (*capset_set) (struct task_struct * target,
       kernel_cap_t * effective,
       kernel_cap_t * inheritable,
       kernel_cap_t * permitted);
 int (*acct) (struct file * file);
 int (*sysctl) (struct ctl_table * table, int op);
 int (*capable) (struct task_struct * tsk, int cap);
 int (*quotactl) (int cmds, int type, int id, struct super_block * sb);
 int (*quota_on) (struct dentry * dentry);
 int (*syslog) (int type);
 int (*settime) (struct timespec *ts, struct timezone *tz);
 int (*vm_enough_memory) (long pages);

 int (*bprm_alloc_security) (struct linux_binprm * bprm);
 void (*bprm_free_security) (struct linux_binprm * bprm);
 void (*bprm_apply_creds) (struct linux_binprm * bprm, int unsafe);
 void (*bprm_post_apply_creds) (struct linux_binprm * bprm);
 int (*bprm_set_security) (struct linux_binprm * bprm);
 int (*bprm_check_security) (struct linux_binprm * bprm);
 int (*bprm_secureexec) (struct linux_binprm * bprm);

 int (*sb_alloc_security) (struct super_block * sb);
 void (*sb_free_security) (struct super_block * sb);
 int (*sb_copy_data)(struct file_system_type *type,
       void *orig, void *copy);
 int (*sb_kern_mount) (struct super_block *sb, void *data);
 int (*sb_statfs) (struct super_block * sb);
 int (*sb_mount) (char *dev_name, struct nameidata * nd,
    char *type, unsigned long flags, void *data);
 int (*sb_check_sb) (struct vfsmount * mnt, struct nameidata * nd);
 int (*sb_umount) (struct vfsmount * mnt, int flags);
 void (*sb_umount_close) (struct vfsmount * mnt);
 void (*sb_umount_busy) (struct vfsmount * mnt);
 void (*sb_post_remount) (struct vfsmount * mnt,
     unsigned long flags, void *data);
 void (*sb_post_mountroot) (void);
 void (*sb_post_addmount) (struct vfsmount * mnt,
      struct nameidata * mountpoint_nd);
 int (*sb_pivotroot) (struct nameidata * old_nd,
        struct nameidata * new_nd);
 void (*sb_post_pivotroot) (struct nameidata * old_nd,
       struct nameidata * new_nd);

 int (*inode_alloc_security) (struct inode *inode);
 void (*inode_free_security) (struct inode *inode);
 int (*inode_create) (struct inode *dir,
                      struct dentry *dentry, int mode);
 void (*inode_post_create) (struct inode *dir,
                            struct dentry *dentry, int mode);
 int (*inode_link) (struct dentry *old_dentry,
                    struct inode *dir, struct dentry *new_dentry);
 void (*inode_post_link) (struct dentry *old_dentry,
                          struct inode *dir, struct dentry *new_dentry);
 int (*inode_unlink) (struct inode *dir, struct dentry *dentry);
 int (*inode_symlink) (struct inode *dir,
                       struct dentry *dentry, const char *old_name);
 void (*inode_post_symlink) (struct inode *dir,
                             struct dentry *dentry,
                             const char *old_name);
 int (*inode_mkdir) (struct inode *dir, struct dentry *dentry, int mode);
 void (*inode_post_mkdir) (struct inode *dir, struct dentry *dentry,
       int mode);
 int (*inode_rmdir) (struct inode *dir, struct dentry *dentry);
 int (*inode_mknod) (struct inode *dir, struct dentry *dentry,
                     int mode, dev_t dev);
 void (*inode_post_mknod) (struct inode *dir, struct dentry *dentry,
                           int mode, dev_t dev);
 int (*inode_rename) (struct inode *old_dir, struct dentry *old_dentry,
                      struct inode *new_dir, struct dentry *new_dentry);
 void (*inode_post_rename) (struct inode *old_dir,
                            struct dentry *old_dentry,
                            struct inode *new_dir,
                            struct dentry *new_dentry);
 int (*inode_readlink) (struct dentry *dentry);
 int (*inode_follow_link) (struct dentry *dentry, struct nameidata *nd);
 int (*inode_permission) (struct inode *inode, int mask, struct nameidata *nd);
 int (*inode_setattr) (struct dentry *dentry, struct iattr *attr);
 int (*inode_getattr) (struct vfsmount *mnt, struct dentry *dentry);
        void (*inode_delete) (struct inode *inode);
 int (*inode_setxattr) (struct dentry *dentry, char *name, void *value,
          size_t size, int flags);
 void (*inode_post_setxattr) (struct dentry *dentry, char *name, void *value,
         size_t size, int flags);
 int (*inode_getxattr) (struct dentry *dentry, char *name);
 int (*inode_listxattr) (struct dentry *dentry);
 int (*inode_removexattr) (struct dentry *dentry, char *name);
   int (*inode_getsecurity)(struct inode *inode, const char *name, void *buffer, size_t size);
   int (*inode_setsecurity)(struct inode *inode, const char *name, const void *value, size_t size, int flags);
   int (*inode_listsecurity)(struct inode *inode, char *buffer, size_t buffer_size);

 int (*file_permission) (struct file * file, int mask);
 int (*file_alloc_security) (struct file * file);
 void (*file_free_security) (struct file * file);
 int (*file_ioctl) (struct file * file, unsigned int cmd,
      unsigned long arg);
 int (*file_mmap) (struct file * file,
     unsigned long reqprot,
     unsigned long prot, unsigned long flags);
 int (*file_mprotect) (struct vm_area_struct * vma,
         unsigned long reqprot,
         unsigned long prot);
 int (*file_lock) (struct file * file, unsigned int cmd);
 int (*file_fcntl) (struct file * file, unsigned int cmd,
      unsigned long arg);
 int (*file_set_fowner) (struct file * file);
 int (*file_send_sigiotask) (struct task_struct * tsk,
        struct fown_struct * fown, int sig);
 int (*file_receive) (struct file * file);

 int (*task_create) (unsigned long clone_flags);
 int (*task_alloc_security) (struct task_struct * p);
 void (*task_free_security) (struct task_struct * p);
 int (*task_setuid) (uid_t id0, uid_t id1, uid_t id2, int flags);
 int (*task_post_setuid) (uid_t old_ruid ,
     uid_t old_euid, uid_t old_suid, int flags);
 int (*task_setgid) (gid_t id0, gid_t id1, gid_t id2, int flags);
 int (*task_setpgid) (struct task_struct * p, pid_t pgid);
 int (*task_getpgid) (struct task_struct * p);
 int (*task_getsid) (struct task_struct * p);
 int (*task_setgroups) (struct group_info *group_info);
 int (*task_setnice) (struct task_struct * p, int nice);
 int (*task_setrlimit) (unsigned int resource, struct rlimit * new_rlim);
 int (*task_setscheduler) (struct task_struct * p, int policy,
      struct sched_param * lp);
 int (*task_getscheduler) (struct task_struct * p);
 int (*task_kill) (struct task_struct * p,
     struct siginfo * info, int sig);
 int (*task_wait) (struct task_struct * p);
 int (*task_prctl) (int option, unsigned long arg2,
      unsigned long arg3, unsigned long arg4,
      unsigned long arg5);
 void (*task_reparent_to_init) (struct task_struct * p);
 void (*task_to_inode)(struct task_struct *p, struct inode *inode);

 int (*ipc_permission) (struct kern_ipc_perm * ipcp, short flag);

 int (*msg_msg_alloc_security) (struct msg_msg * msg);
 void (*msg_msg_free_security) (struct msg_msg * msg);

 int (*msg_queue_alloc_security) (struct msg_queue * msq);
 void (*msg_queue_free_security) (struct msg_queue * msq);
 int (*msg_queue_associate) (struct msg_queue * msq, int msqflg);
 int (*msg_queue_msgctl) (struct msg_queue * msq, int cmd);
 int (*msg_queue_msgsnd) (struct msg_queue * msq,
     struct msg_msg * msg, int msqflg);
 int (*msg_queue_msgrcv) (struct msg_queue * msq,
     struct msg_msg * msg,
     struct task_struct * target,
     long type, int mode);

 int (*shm_alloc_security) (struct shmid_kernel * shp);
 void (*shm_free_security) (struct shmid_kernel * shp);
 int (*shm_associate) (struct shmid_kernel * shp, int shmflg);
 int (*shm_shmctl) (struct shmid_kernel * shp, int cmd);
 int (*shm_shmat) (struct shmid_kernel * shp,
     char *shmaddr, int shmflg);

 int (*sem_alloc_security) (struct sem_array * sma);
 void (*sem_free_security) (struct sem_array * sma);
 int (*sem_associate) (struct sem_array * sma, int semflg);
 int (*sem_semctl) (struct sem_array * sma, int cmd);
 int (*sem_semop) (struct sem_array * sma,
     struct sembuf * sops, unsigned nsops, int alter);

 int (*netlink_send) (struct sock * sk, struct sk_buff * skb);
 int (*netlink_recv) (struct sk_buff * skb);


 int (*register_security) (const char *name,
                           struct security_operations *ops);
 int (*unregister_security) (const char *name,
                             struct security_operations *ops);

 void (*d_instantiate) (struct dentry *dentry, struct inode *inode);

  int (*getprocattr)(struct task_struct *p, char *name, void *value, size_t size);
  int (*setprocattr)(struct task_struct *p, char *name, void *value, size_t size);


 int (*unix_stream_connect) (struct socket * sock,
        struct socket * other, struct sock * newsk);
 int (*unix_may_send) (struct socket * sock, struct socket * other);

 int (*socket_create) (int family, int type, int protocol, int kern);
 void (*socket_post_create) (struct socket * sock, int family,
        int type, int protocol, int kern);
 int (*socket_bind) (struct socket * sock,
       struct sockaddr * address, int addrlen);
 int (*socket_connect) (struct socket * sock,
          struct sockaddr * address, int addrlen);
 int (*socket_listen) (struct socket * sock, int backlog);
 int (*socket_accept) (struct socket * sock, struct socket * newsock);
 void (*socket_post_accept) (struct socket * sock,
        struct socket * newsock);
 int (*socket_sendmsg) (struct socket * sock,
          struct msghdr * msg, int size);
 int (*socket_recvmsg) (struct socket * sock,
          struct msghdr * msg, int size, int flags);
 int (*socket_getsockname) (struct socket * sock);
 int (*socket_getpeername) (struct socket * sock);
 int (*socket_getsockopt) (struct socket * sock, int level, int optname);
 int (*socket_setsockopt) (struct socket * sock, int level, int optname);
 int (*socket_shutdown) (struct socket * sock, int how);
 int (*socket_sock_rcv_skb) (struct sock * sk, struct sk_buff * skb);
 int (*socket_getpeersec) (struct socket *sock, char *optval, int *optlen, unsigned len);
 int (*sk_alloc_security) (struct sock *sk, int family, int priority);
 void (*sk_free_security) (struct sock *sk);

};


extern struct security_operations *security_ops;


static inline __attribute__((always_inline)) int security_ptrace (struct task_struct * parent, struct task_struct * child)
{
 return security_ops->ptrace (parent, child);
}

static inline __attribute__((always_inline)) int security_capget (struct task_struct *target,
       kernel_cap_t *effective,
       kernel_cap_t *inheritable,
       kernel_cap_t *permitted)
{
 return security_ops->capget (target, effective, inheritable, permitted);
}

static inline __attribute__((always_inline)) int security_capset_check (struct task_struct *target,
      kernel_cap_t *effective,
      kernel_cap_t *inheritable,
      kernel_cap_t *permitted)
{
 return security_ops->capset_check (target, effective, inheritable, permitted);
}

static inline __attribute__((always_inline)) void security_capset_set (struct task_struct *target,
     kernel_cap_t *effective,
     kernel_cap_t *inheritable,
     kernel_cap_t *permitted)
{
 security_ops->capset_set (target, effective, inheritable, permitted);
}

static inline __attribute__((always_inline)) int security_acct (struct file *file)
{
 return security_ops->acct (file);
}

static inline __attribute__((always_inline)) int security_sysctl(struct ctl_table *table, int op)
{
 return security_ops->sysctl(table, op);
}

static inline __attribute__((always_inline)) int security_quotactl (int cmds, int type, int id,
         struct super_block *sb)
{
 return security_ops->quotactl (cmds, type, id, sb);
}

static inline __attribute__((always_inline)) int security_quota_on (struct dentry * dentry)
{
 return security_ops->quota_on (dentry);
}

static inline __attribute__((always_inline)) int security_syslog(int type)
{
 return security_ops->syslog(type);
}

static inline __attribute__((always_inline)) int security_settime(struct timespec *ts, struct timezone *tz)
{
 return security_ops->settime(ts, tz);
}


static inline __attribute__((always_inline)) int security_vm_enough_memory(long pages)
{
 return security_ops->vm_enough_memory(pages);
}

static inline __attribute__((always_inline)) int security_bprm_alloc (struct linux_binprm *bprm)
{
 return security_ops->bprm_alloc_security (bprm);
}
static inline __attribute__((always_inline)) void security_bprm_free (struct linux_binprm *bprm)
{
 security_ops->bprm_free_security (bprm);
}
static inline __attribute__((always_inline)) void security_bprm_apply_creds (struct linux_binprm *bprm, int unsafe)
{
 security_ops->bprm_apply_creds (bprm, unsafe);
}
static inline __attribute__((always_inline)) void security_bprm_post_apply_creds (struct linux_binprm *bprm)
{
 security_ops->bprm_post_apply_creds (bprm);
}
static inline __attribute__((always_inline)) int security_bprm_set (struct linux_binprm *bprm)
{
 return security_ops->bprm_set_security (bprm);
}

static inline __attribute__((always_inline)) int security_bprm_check (struct linux_binprm *bprm)
{
 return security_ops->bprm_check_security (bprm);
}

static inline __attribute__((always_inline)) int security_bprm_secureexec (struct linux_binprm *bprm)
{
 return security_ops->bprm_secureexec (bprm);
}

static inline __attribute__((always_inline)) int security_sb_alloc (struct super_block *sb)
{
 return security_ops->sb_alloc_security (sb);
}

static inline __attribute__((always_inline)) void security_sb_free (struct super_block *sb)
{
 security_ops->sb_free_security (sb);
}

static inline __attribute__((always_inline)) int security_sb_copy_data (struct file_system_type *type,
      void *orig, void *copy)
{
 return security_ops->sb_copy_data (type, orig, copy);
}

static inline __attribute__((always_inline)) int security_sb_kern_mount (struct super_block *sb, void *data)
{
 return security_ops->sb_kern_mount (sb, data);
}

static inline __attribute__((always_inline)) int security_sb_statfs (struct super_block *sb)
{
 return security_ops->sb_statfs (sb);
}

static inline __attribute__((always_inline)) int security_sb_mount (char *dev_name, struct nameidata *nd,
        char *type, unsigned long flags,
        void *data)
{
 return security_ops->sb_mount (dev_name, nd, type, flags, data);
}

static inline __attribute__((always_inline)) int security_sb_check_sb (struct vfsmount *mnt,
     struct nameidata *nd)
{
 return security_ops->sb_check_sb (mnt, nd);
}

static inline __attribute__((always_inline)) int security_sb_umount (struct vfsmount *mnt, int flags)
{
 return security_ops->sb_umount (mnt, flags);
}

static inline __attribute__((always_inline)) void security_sb_umount_close (struct vfsmount *mnt)
{
 security_ops->sb_umount_close (mnt);
}

static inline __attribute__((always_inline)) void security_sb_umount_busy (struct vfsmount *mnt)
{
 security_ops->sb_umount_busy (mnt);
}

static inline __attribute__((always_inline)) void security_sb_post_remount (struct vfsmount *mnt,
          unsigned long flags, void *data)
{
 security_ops->sb_post_remount (mnt, flags, data);
}

static inline __attribute__((always_inline)) void security_sb_post_mountroot (void)
{
 security_ops->sb_post_mountroot ();
}

static inline __attribute__((always_inline)) void security_sb_post_addmount (struct vfsmount *mnt,
           struct nameidata *mountpoint_nd)
{
 security_ops->sb_post_addmount (mnt, mountpoint_nd);
}

static inline __attribute__((always_inline)) int security_sb_pivotroot (struct nameidata *old_nd,
      struct nameidata *new_nd)
{
 return security_ops->sb_pivotroot (old_nd, new_nd);
}

static inline __attribute__((always_inline)) void security_sb_post_pivotroot (struct nameidata *old_nd,
            struct nameidata *new_nd)
{
 security_ops->sb_post_pivotroot (old_nd, new_nd);
}

static inline __attribute__((always_inline)) int security_inode_alloc (struct inode *inode)
{
 if (__builtin_expect(!!(((inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_alloc_security (inode);
}

static inline __attribute__((always_inline)) void security_inode_free (struct inode *inode)
{
 if (__builtin_expect(!!(((inode)->i_flags & 512)), 0))
  return;
 security_ops->inode_free_security (inode);
}

static inline __attribute__((always_inline)) int security_inode_create (struct inode *dir,
      struct dentry *dentry,
      int mode)
{
 if (__builtin_expect(!!(((dir)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_create (dir, dentry, mode);
}

static inline __attribute__((always_inline)) void security_inode_post_create (struct inode *dir,
            struct dentry *dentry,
            int mode)
{
 if (dentry->d_inode && __builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return;
 security_ops->inode_post_create (dir, dentry, mode);
}

static inline __attribute__((always_inline)) int security_inode_link (struct dentry *old_dentry,
           struct inode *dir,
           struct dentry *new_dentry)
{
 if (__builtin_expect(!!(((old_dentry->d_inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_link (old_dentry, dir, new_dentry);
}

static inline __attribute__((always_inline)) void security_inode_post_link (struct dentry *old_dentry,
          struct inode *dir,
          struct dentry *new_dentry)
{
 if (new_dentry->d_inode && __builtin_expect(!!(((new_dentry->d_inode)->i_flags & 512)), 0))
  return;
 security_ops->inode_post_link (old_dentry, dir, new_dentry);
}

static inline __attribute__((always_inline)) int security_inode_unlink (struct inode *dir,
      struct dentry *dentry)
{
 if (__builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_unlink (dir, dentry);
}

static inline __attribute__((always_inline)) int security_inode_symlink (struct inode *dir,
       struct dentry *dentry,
       const char *old_name)
{
 if (__builtin_expect(!!(((dir)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_symlink (dir, dentry, old_name);
}

static inline __attribute__((always_inline)) void security_inode_post_symlink (struct inode *dir,
      struct dentry *dentry,
      const char *old_name)
{
 if (dentry->d_inode && __builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return;
 security_ops->inode_post_symlink (dir, dentry, old_name);
}

static inline __attribute__((always_inline)) int security_inode_mkdir (struct inode *dir,
     struct dentry *dentry,
     int mode)
{
 if (__builtin_expect(!!(((dir)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_mkdir (dir, dentry, mode);
}

static inline __attribute__((always_inline)) void security_inode_post_mkdir (struct inode *dir,
           struct dentry *dentry,
           int mode)
{
 if (dentry->d_inode && __builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return;
 security_ops->inode_post_mkdir (dir, dentry, mode);
}

static inline __attribute__((always_inline)) int security_inode_rmdir (struct inode *dir,
     struct dentry *dentry)
{
 if (__builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_rmdir (dir, dentry);
}

static inline __attribute__((always_inline)) int security_inode_mknod (struct inode *dir,
     struct dentry *dentry,
     int mode, dev_t dev)
{
 if (__builtin_expect(!!(((dir)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_mknod (dir, dentry, mode, dev);
}

static inline __attribute__((always_inline)) void security_inode_post_mknod (struct inode *dir,
           struct dentry *dentry,
           int mode, dev_t dev)
{
 if (dentry->d_inode && __builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return;
 security_ops->inode_post_mknod (dir, dentry, mode, dev);
}

static inline __attribute__((always_inline)) int security_inode_rename (struct inode *old_dir,
      struct dentry *old_dentry,
      struct inode *new_dir,
      struct dentry *new_dentry)
{
        if (__builtin_expect(!!(((old_dentry->d_inode)->i_flags & 512) || (new_dentry->d_inode && ((new_dentry->d_inode)->i_flags & 512))), 0))

  return 0;
 return security_ops->inode_rename (old_dir, old_dentry,
        new_dir, new_dentry);
}

static inline __attribute__((always_inline)) void security_inode_post_rename (struct inode *old_dir,
            struct dentry *old_dentry,
            struct inode *new_dir,
            struct dentry *new_dentry)
{
 if (__builtin_expect(!!(((old_dentry->d_inode)->i_flags & 512) || (new_dentry->d_inode && ((new_dentry->d_inode)->i_flags & 512))), 0))

  return;
 security_ops->inode_post_rename (old_dir, old_dentry,
      new_dir, new_dentry);
}

static inline __attribute__((always_inline)) int security_inode_readlink (struct dentry *dentry)
{
 if (__builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_readlink (dentry);
}

static inline __attribute__((always_inline)) int security_inode_follow_link (struct dentry *dentry,
           struct nameidata *nd)
{
 if (__builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_follow_link (dentry, nd);
}

static inline __attribute__((always_inline)) int security_inode_permission (struct inode *inode, int mask,
          struct nameidata *nd)
{
 if (__builtin_expect(!!(((inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_permission (inode, mask, nd);
}

static inline __attribute__((always_inline)) int security_inode_setattr (struct dentry *dentry,
       struct iattr *attr)
{
 if (__builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_setattr (dentry, attr);
}

static inline __attribute__((always_inline)) int security_inode_getattr (struct vfsmount *mnt,
       struct dentry *dentry)
{
 if (__builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_getattr (mnt, dentry);
}

static inline __attribute__((always_inline)) void security_inode_delete (struct inode *inode)
{
 if (__builtin_expect(!!(((inode)->i_flags & 512)), 0))
  return;
 security_ops->inode_delete (inode);
}

static inline __attribute__((always_inline)) int security_inode_setxattr (struct dentry *dentry, char *name,
        void *value, size_t size, int flags)
{
 if (__builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_setxattr (dentry, name, value, size, flags);
}

static inline __attribute__((always_inline)) void security_inode_post_setxattr (struct dentry *dentry, char *name,
      void *value, size_t size, int flags)
{
 if (__builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return;
 security_ops->inode_post_setxattr (dentry, name, value, size, flags);
}

static inline __attribute__((always_inline)) int security_inode_getxattr (struct dentry *dentry, char *name)
{
 if (__builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_getxattr (dentry, name);
}

static inline __attribute__((always_inline)) int security_inode_listxattr (struct dentry *dentry)
{
 if (__builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_listxattr (dentry);
}

static inline __attribute__((always_inline)) int security_inode_removexattr (struct dentry *dentry, char *name)
{
 if (__builtin_expect(!!(((dentry->d_inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_removexattr (dentry, name);
}

static inline __attribute__((always_inline)) int security_inode_getsecurity(struct inode *inode, const char *name, void *buffer, size_t size)
{
 if (__builtin_expect(!!(((inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_getsecurity(inode, name, buffer, size);
}

static inline __attribute__((always_inline)) int security_inode_setsecurity(struct inode *inode, const char *name, const void *value, size_t size, int flags)
{
 if (__builtin_expect(!!(((inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_setsecurity(inode, name, value, size, flags);
}

static inline __attribute__((always_inline)) int security_inode_listsecurity(struct inode *inode, char *buffer, size_t buffer_size)
{
 if (__builtin_expect(!!(((inode)->i_flags & 512)), 0))
  return 0;
 return security_ops->inode_listsecurity(inode, buffer, buffer_size);
}

static inline __attribute__((always_inline)) int security_file_permission (struct file *file, int mask)
{
 return security_ops->file_permission (file, mask);
}

static inline __attribute__((always_inline)) int security_file_alloc (struct file *file)
{
 return security_ops->file_alloc_security (file);
}

static inline __attribute__((always_inline)) void security_file_free (struct file *file)
{
 security_ops->file_free_security (file);
}

static inline __attribute__((always_inline)) int security_file_ioctl (struct file *file, unsigned int cmd,
           unsigned long arg)
{
 return security_ops->file_ioctl (file, cmd, arg);
}

static inline __attribute__((always_inline)) int security_file_mmap (struct file *file, unsigned long reqprot,
          unsigned long prot,
          unsigned long flags)
{
 return security_ops->file_mmap (file, reqprot, prot, flags);
}

static inline __attribute__((always_inline)) int security_file_mprotect (struct vm_area_struct *vma,
       unsigned long reqprot,
       unsigned long prot)
{
 return security_ops->file_mprotect (vma, reqprot, prot);
}

static inline __attribute__((always_inline)) int security_file_lock (struct file *file, unsigned int cmd)
{
 return security_ops->file_lock (file, cmd);
}

static inline __attribute__((always_inline)) int security_file_fcntl (struct file *file, unsigned int cmd,
           unsigned long arg)
{
 return security_ops->file_fcntl (file, cmd, arg);
}

static inline __attribute__((always_inline)) int security_file_set_fowner (struct file *file)
{
 return security_ops->file_set_fowner (file);
}

static inline __attribute__((always_inline)) int security_file_send_sigiotask (struct task_struct *tsk,
      struct fown_struct *fown,
      int sig)
{
 return security_ops->file_send_sigiotask (tsk, fown, sig);
}

static inline __attribute__((always_inline)) int security_file_receive (struct file *file)
{
 return security_ops->file_receive (file);
}

static inline __attribute__((always_inline)) int security_task_create (unsigned long clone_flags)
{
 return security_ops->task_create (clone_flags);
}

static inline __attribute__((always_inline)) int security_task_alloc (struct task_struct *p)
{
 return security_ops->task_alloc_security (p);
}

static inline __attribute__((always_inline)) void security_task_free (struct task_struct *p)
{
 security_ops->task_free_security (p);
}

static inline __attribute__((always_inline)) int security_task_setuid (uid_t id0, uid_t id1, uid_t id2,
     int flags)
{
 return security_ops->task_setuid (id0, id1, id2, flags);
}

static inline __attribute__((always_inline)) int security_task_post_setuid (uid_t old_ruid, uid_t old_euid,
          uid_t old_suid, int flags)
{
 return security_ops->task_post_setuid (old_ruid, old_euid, old_suid, flags);
}

static inline __attribute__((always_inline)) int security_task_setgid (gid_t id0, gid_t id1, gid_t id2,
     int flags)
{
 return security_ops->task_setgid (id0, id1, id2, flags);
}

static inline __attribute__((always_inline)) int security_task_setpgid (struct task_struct *p, pid_t pgid)
{
 return security_ops->task_setpgid (p, pgid);
}

static inline __attribute__((always_inline)) int security_task_getpgid (struct task_struct *p)
{
 return security_ops->task_getpgid (p);
}

static inline __attribute__((always_inline)) int security_task_getsid (struct task_struct *p)
{
 return security_ops->task_getsid (p);
}

static inline __attribute__((always_inline)) int security_task_setgroups (struct group_info *group_info)
{
 return security_ops->task_setgroups (group_info);
}

static inline __attribute__((always_inline)) int security_task_setnice (struct task_struct *p, int nice)
{
 return security_ops->task_setnice (p, nice);
}

static inline __attribute__((always_inline)) int security_task_setrlimit (unsigned int resource,
        struct rlimit *new_rlim)
{
 return security_ops->task_setrlimit (resource, new_rlim);
}

static inline __attribute__((always_inline)) int security_task_setscheduler (struct task_struct *p,
           int policy,
           struct sched_param *lp)
{
 return security_ops->task_setscheduler (p, policy, lp);
}

static inline __attribute__((always_inline)) int security_task_getscheduler (struct task_struct *p)
{
 return security_ops->task_getscheduler (p);
}

static inline __attribute__((always_inline)) int security_task_kill (struct task_struct *p,
          struct siginfo *info, int sig)
{
 return security_ops->task_kill (p, info, sig);
}

static inline __attribute__((always_inline)) int security_task_wait (struct task_struct *p)
{
 return security_ops->task_wait (p);
}

static inline __attribute__((always_inline)) int security_task_prctl (int option, unsigned long arg2,
           unsigned long arg3,
           unsigned long arg4,
           unsigned long arg5)
{
 return security_ops->task_prctl (option, arg2, arg3, arg4, arg5);
}

static inline __attribute__((always_inline)) void security_task_reparent_to_init (struct task_struct *p)
{
 security_ops->task_reparent_to_init (p);
}

static inline __attribute__((always_inline)) void security_task_to_inode(struct task_struct *p, struct inode *inode)
{
 security_ops->task_to_inode(p, inode);
}

static inline __attribute__((always_inline)) int security_ipc_permission (struct kern_ipc_perm *ipcp,
        short flag)
{
 return security_ops->ipc_permission (ipcp, flag);
}

static inline __attribute__((always_inline)) int security_msg_msg_alloc (struct msg_msg * msg)
{
 return security_ops->msg_msg_alloc_security (msg);
}

static inline __attribute__((always_inline)) void security_msg_msg_free (struct msg_msg * msg)
{
 security_ops->msg_msg_free_security(msg);
}

static inline __attribute__((always_inline)) int security_msg_queue_alloc (struct msg_queue *msq)
{
 return security_ops->msg_queue_alloc_security (msq);
}

static inline __attribute__((always_inline)) void security_msg_queue_free (struct msg_queue *msq)
{
 security_ops->msg_queue_free_security (msq);
}

static inline __attribute__((always_inline)) int security_msg_queue_associate (struct msg_queue * msq,
      int msqflg)
{
 return security_ops->msg_queue_associate (msq, msqflg);
}

static inline __attribute__((always_inline)) int security_msg_queue_msgctl (struct msg_queue * msq, int cmd)
{
 return security_ops->msg_queue_msgctl (msq, cmd);
}

static inline __attribute__((always_inline)) int security_msg_queue_msgsnd (struct msg_queue * msq,
          struct msg_msg * msg, int msqflg)
{
 return security_ops->msg_queue_msgsnd (msq, msg, msqflg);
}

static inline __attribute__((always_inline)) int security_msg_queue_msgrcv (struct msg_queue * msq,
          struct msg_msg * msg,
          struct task_struct * target,
          long type, int mode)
{
 return security_ops->msg_queue_msgrcv (msq, msg, target, type, mode);
}

static inline __attribute__((always_inline)) int security_shm_alloc (struct shmid_kernel *shp)
{
 return security_ops->shm_alloc_security (shp);
}

static inline __attribute__((always_inline)) void security_shm_free (struct shmid_kernel *shp)
{
 security_ops->shm_free_security (shp);
}

static inline __attribute__((always_inline)) int security_shm_associate (struct shmid_kernel * shp,
       int shmflg)
{
 return security_ops->shm_associate(shp, shmflg);
}

static inline __attribute__((always_inline)) int security_shm_shmctl (struct shmid_kernel * shp, int cmd)
{
 return security_ops->shm_shmctl (shp, cmd);
}

static inline __attribute__((always_inline)) int security_shm_shmat (struct shmid_kernel * shp,
          char *shmaddr, int shmflg)
{
 return security_ops->shm_shmat(shp, shmaddr, shmflg);
}

static inline __attribute__((always_inline)) int security_sem_alloc (struct sem_array *sma)
{
 return security_ops->sem_alloc_security (sma);
}

static inline __attribute__((always_inline)) void security_sem_free (struct sem_array *sma)
{
 security_ops->sem_free_security (sma);
}

static inline __attribute__((always_inline)) int security_sem_associate (struct sem_array * sma, int semflg)
{
 return security_ops->sem_associate (sma, semflg);
}

static inline __attribute__((always_inline)) int security_sem_semctl (struct sem_array * sma, int cmd)
{
 return security_ops->sem_semctl(sma, cmd);
}

static inline __attribute__((always_inline)) int security_sem_semop (struct sem_array * sma,
          struct sembuf * sops, unsigned nsops,
          int alter)
{
 return security_ops->sem_semop(sma, sops, nsops, alter);
}

static inline __attribute__((always_inline)) void security_d_instantiate (struct dentry *dentry, struct inode *inode)
{
 if (__builtin_expect(!!(inode && ((inode)->i_flags & 512)), 0))
  return;
 security_ops->d_instantiate (dentry, inode);
}

static inline __attribute__((always_inline)) int security_getprocattr(struct task_struct *p, char *name, void *value, size_t size)
{
 return security_ops->getprocattr(p, name, value, size);
}

static inline __attribute__((always_inline)) int security_setprocattr(struct task_struct *p, char *name, void *value, size_t size)
{
 return security_ops->setprocattr(p, name, value, size);
}

static inline __attribute__((always_inline)) int security_netlink_send(struct sock *sk, struct sk_buff * skb)
{
 return security_ops->netlink_send(sk, skb);
}

static inline __attribute__((always_inline)) int security_netlink_recv(struct sk_buff * skb)
{
 return security_ops->netlink_recv(skb);
}


extern int security_init (void);
extern int register_security (struct security_operations *ops);
extern int unregister_security (struct security_operations *ops);
extern int mod_reg_security (const char *name, struct security_operations *ops);
extern int mod_unreg_security (const char *name, struct security_operations *ops);
# 2618 "include/linux/security.h"
static inline __attribute__((always_inline)) int security_unix_stream_connect(struct socket * sock,
            struct socket * other,
            struct sock * newsk)
{
 return security_ops->unix_stream_connect(sock, other, newsk);
}


static inline __attribute__((always_inline)) int security_unix_may_send(struct socket * sock,
      struct socket * other)
{
 return security_ops->unix_may_send(sock, other);
}

static inline __attribute__((always_inline)) int security_socket_create (int family, int type,
       int protocol, int kern)
{
 return security_ops->socket_create(family, type, protocol, kern);
}

static inline __attribute__((always_inline)) void security_socket_post_create(struct socket * sock,
            int family,
            int type,
            int protocol, int kern)
{
 security_ops->socket_post_create(sock, family, type,
      protocol, kern);
}

static inline __attribute__((always_inline)) int security_socket_bind(struct socket * sock,
           struct sockaddr * address,
           int addrlen)
{
 return security_ops->socket_bind(sock, address, addrlen);
}

static inline __attribute__((always_inline)) int security_socket_connect(struct socket * sock,
       struct sockaddr * address,
       int addrlen)
{
 return security_ops->socket_connect(sock, address, addrlen);
}

static inline __attribute__((always_inline)) int security_socket_listen(struct socket * sock, int backlog)
{
 return security_ops->socket_listen(sock, backlog);
}

static inline __attribute__((always_inline)) int security_socket_accept(struct socket * sock,
      struct socket * newsock)
{
 return security_ops->socket_accept(sock, newsock);
}

static inline __attribute__((always_inline)) void security_socket_post_accept(struct socket * sock,
            struct socket * newsock)
{
 security_ops->socket_post_accept(sock, newsock);
}

static inline __attribute__((always_inline)) int security_socket_sendmsg(struct socket * sock,
       struct msghdr * msg, int size)
{
 return security_ops->socket_sendmsg(sock, msg, size);
}

static inline __attribute__((always_inline)) int security_socket_recvmsg(struct socket * sock,
       struct msghdr * msg, int size,
       int flags)
{
 return security_ops->socket_recvmsg(sock, msg, size, flags);
}

static inline __attribute__((always_inline)) int security_socket_getsockname(struct socket * sock)
{
 return security_ops->socket_getsockname(sock);
}

static inline __attribute__((always_inline)) int security_socket_getpeername(struct socket * sock)
{
 return security_ops->socket_getpeername(sock);
}

static inline __attribute__((always_inline)) int security_socket_getsockopt(struct socket * sock,
          int level, int optname)
{
 return security_ops->socket_getsockopt(sock, level, optname);
}

static inline __attribute__((always_inline)) int security_socket_setsockopt(struct socket * sock,
          int level, int optname)
{
 return security_ops->socket_setsockopt(sock, level, optname);
}

static inline __attribute__((always_inline)) int security_socket_shutdown(struct socket * sock, int how)
{
 return security_ops->socket_shutdown(sock, how);
}

static inline __attribute__((always_inline)) int security_sock_rcv_skb (struct sock * sk,
      struct sk_buff * skb)
{
 return security_ops->socket_sock_rcv_skb (sk, skb);
}

static inline __attribute__((always_inline)) int security_socket_getpeersec(struct socket *sock, char *optval,
          int *optlen, unsigned len)
{
 return security_ops->socket_getpeersec(sock, optval, optlen, len);
}

static inline __attribute__((always_inline)) int security_sk_alloc(struct sock *sk, int family, int priority)
{
 return security_ops->sk_alloc_security(sk, family, priority);
}

static inline __attribute__((always_inline)) void security_sk_free(struct sock *sk)
{
 return security_ops->sk_free_security(sk);
}
# 51 "include/net/sock.h" 2

# 1 "include/linux/filter.h" 1
# 26 "include/linux/filter.h"
struct sock_filter
{
        __u16 code;
        __u8 jt;
        __u8 jf;
        __u32 k;
};

struct sock_fprog
{
 unsigned short len;
 struct sock_filter *filter;
};


struct sk_filter
{
 atomic_t refcnt;
        unsigned int len;
        struct sock_filter insns[0];
};

static inline __attribute__((always_inline)) unsigned int sk_filter_len(struct sk_filter *fp)
{
 return fp->len*sizeof(struct sock_filter) + sizeof(*fp);
}
# 143 "include/linux/filter.h"
struct sk_buff;
struct sock;

extern int sk_run_filter(struct sk_buff *skb, struct sock_filter *filter, int flen);
extern int sk_attach_filter(struct sock_fprog *fprog, struct sock *sk);
extern int sk_chk_filter(struct sock_filter *filter, int flen);
# 53 "include/net/sock.h" 2


# 1 "include/net/dst.h" 1
# 12 "include/net/dst.h"
# 1 "include/linux/rtnetlink.h" 1



# 1 "include/linux/netlink.h" 1
# 25 "include/linux/netlink.h"
struct sockaddr_nl
{
 sa_family_t nl_family;
 unsigned short nl_pad;
 __u32 nl_pid;
        __u32 nl_groups;
};

struct nlmsghdr
{
 __u32 nlmsg_len;
 __u16 nlmsg_type;
 __u16 nlmsg_flags;
 __u32 nlmsg_seq;
 __u32 nlmsg_pid;
};
# 87 "include/linux/netlink.h"
struct nlmsgerr
{
 int error;
 struct nlmsghdr msg;
};



enum {
 NETLINK_UNCONNECTED = 0,
 NETLINK_CONNECTED,
};






struct netlink_skb_parms
{
 struct ucred creds;
 __u32 pid;
 __u32 groups;
 __u32 dst_pid;
 __u32 dst_groups;
 kernel_cap_t eff_cap;
 __u32 loginuid;
};





extern struct sock *netlink_kernel_create(int unit, void (*input)(struct sock *sk, int len));
extern void netlink_ack(struct sk_buff *in_skb, struct nlmsghdr *nlh, int err);
extern int netlink_unicast(struct sock *ssk, struct sk_buff *skb, __u32 pid, int nonblock);
extern int netlink_broadcast(struct sock *ssk, struct sk_buff *skb, __u32 pid,
        __u32 group, int allocation);
extern void netlink_set_err(struct sock *ssk, __u32 pid, __u32 group, int code);
extern int netlink_register_notifier(struct notifier_block *nb);
extern int netlink_unregister_notifier(struct notifier_block *nb);


struct sock *netlink_getsockbyfilp(struct file *filp);
int netlink_attachskb(struct sock *sk, struct sk_buff *skb, int nonblock, long timeo);
void netlink_detachskb(struct sock *sk, struct sk_buff *skb);
int netlink_sendskb(struct sock *sk, struct sk_buff *skb, int protocol);
# 142 "include/linux/netlink.h"
struct netlink_callback
{
 struct sk_buff *skb;
 struct nlmsghdr *nlh;
 int (*dump)(struct sk_buff * skb, struct netlink_callback *cb);
 int (*done)(struct netlink_callback *cb);
 int family;
 long args[5];
};

struct netlink_notify
{
 int pid;
 int protocol;
};

static __inline__ __attribute__((always_inline)) struct nlmsghdr *
__nlmsg_put(struct sk_buff *skb, u32 pid, u32 seq, int type, int len, int flags)
{
 struct nlmsghdr *nlh;
 int size = ((len)+( ((sizeof(struct nlmsghdr))+4 -1) & ~(4 -1) ));

 nlh = (struct nlmsghdr*)skb_put(skb, ( ((size)+4 -1) & ~(4 -1) ));
 nlh->nlmsg_type = type;
 nlh->nlmsg_len = size;
 nlh->nlmsg_flags = flags;
 nlh->nlmsg_pid = pid;
 nlh->nlmsg_seq = seq;
 __memset_generic((((void*)(((char*)nlh) + ((0)+( ((sizeof(struct nlmsghdr))+4 -1) & ~(4 -1) )))) + len),(0),(( ((size)+4 -1) & ~(4 -1) ) - size));
 return nlh;
}
# 194 "include/linux/netlink.h"
extern int netlink_dump_start(struct sock *ssk, struct sk_buff *skb,
         struct nlmsghdr *nlh,
         int (*dump)(struct sk_buff *skb, struct netlink_callback*),
         int (*done)(struct netlink_callback*));




extern void netlink_set_nonroot(int protocol, unsigned flag);
# 5 "include/linux/rtnetlink.h" 2







enum {
 RTM_BASE = 16,


 RTM_NEWLINK = 16,

 RTM_DELLINK,

 RTM_GETLINK,

 RTM_SETLINK,


 RTM_NEWADDR = 20,

 RTM_DELADDR,

 RTM_GETADDR,


 RTM_NEWROUTE = 24,

 RTM_DELROUTE,

 RTM_GETROUTE,


 RTM_NEWNEIGH = 28,

 RTM_DELNEIGH,

 RTM_GETNEIGH,


 RTM_NEWRULE = 32,

 RTM_DELRULE,

 RTM_GETRULE,


 RTM_NEWQDISC = 36,

 RTM_DELQDISC,

 RTM_GETQDISC,


 RTM_NEWTCLASS = 40,

 RTM_DELTCLASS,

 RTM_GETTCLASS,


 RTM_NEWTFILTER = 44,

 RTM_DELTFILTER,

 RTM_GETTFILTER,


 RTM_NEWACTION = 48,

 RTM_DELACTION,

 RTM_GETACTION,


 RTM_NEWPREFIX = 52,

 RTM_GETPREFIX = 54,


 RTM_GETMULTICAST = 58,


 RTM_GETANYCAST = 62,


 RTM_NEWNEIGHTBL = 64,

 RTM_GETNEIGHTBL = 66,

 RTM_SETNEIGHTBL,


 __RTM_MAX,

};
# 113 "include/linux/rtnetlink.h"
struct rtattr
{
 unsigned short rta_len;
 unsigned short rta_type;
};
# 140 "include/linux/rtnetlink.h"
struct rtmsg
{
 unsigned char rtm_family;
 unsigned char rtm_dst_len;
 unsigned char rtm_src_len;
 unsigned char rtm_tos;

 unsigned char rtm_table;
 unsigned char rtm_protocol;
 unsigned char rtm_scope;
 unsigned char rtm_type;

 unsigned rtm_flags;
};



enum
{
 RTN_UNSPEC,
 RTN_UNICAST,
 RTN_LOCAL,
 RTN_BROADCAST,

 RTN_ANYCAST,

 RTN_MULTICAST,
 RTN_BLACKHOLE,
 RTN_UNREACHABLE,
 RTN_PROHIBIT,
 RTN_THROW,
 RTN_NAT,
 RTN_XRESOLVE,
 __RTN_MAX
};
# 214 "include/linux/rtnetlink.h"
enum rt_scope_t
{
 RT_SCOPE_UNIVERSE=0,

 RT_SCOPE_SITE=200,
 RT_SCOPE_LINK=253,
 RT_SCOPE_HOST=254,
 RT_SCOPE_NOWHERE=255
};
# 233 "include/linux/rtnetlink.h"
enum rt_class_t
{
 RT_TABLE_UNSPEC=0,

 RT_TABLE_DEFAULT=253,
 RT_TABLE_MAIN=254,
 RT_TABLE_LOCAL=255,
 __RT_TABLE_MAX
};






enum rtattr_type_t
{
 RTA_UNSPEC,
 RTA_DST,
 RTA_SRC,
 RTA_IIF,
 RTA_OIF,
 RTA_GATEWAY,
 RTA_PRIORITY,
 RTA_PREFSRC,
 RTA_METRICS,
 RTA_MULTIPATH,
 RTA_PROTOINFO,
 RTA_FLOW,
 RTA_CACHEINFO,
 RTA_SESSION,
 RTA_MP_ALGO,
 __RTA_MAX
};
# 282 "include/linux/rtnetlink.h"
struct rtnexthop
{
 unsigned short rtnh_len;
 unsigned char rtnh_flags;
 unsigned char rtnh_hops;
 int rtnh_ifindex;
};
# 309 "include/linux/rtnetlink.h"
struct rta_cacheinfo
{
 __u32 rta_clntref;
 __u32 rta_lastuse;
 __s32 rta_expires;
 __u32 rta_error;
 __u32 rta_used;


 __u32 rta_id;
 __u32 rta_ts;
 __u32 rta_tsage;
};



enum
{
 RTAX_UNSPEC,

 RTAX_LOCK,

 RTAX_MTU,

 RTAX_WINDOW,

 RTAX_RTT,

 RTAX_RTTVAR,

 RTAX_SSTHRESH,

 RTAX_CWND,

 RTAX_ADVMSS,

 RTAX_REORDERING,

 RTAX_HOPLIMIT,

 RTAX_INITCWND,

 RTAX_FEATURES,

 __RTAX_MAX
};
# 363 "include/linux/rtnetlink.h"
struct rta_session
{
 __u8 proto;
 __u8 pad1;
 __u16 pad2;

 union {
  struct {
   __u16 sport;
   __u16 dport;
  } ports;

  struct {
   __u8 type;
   __u8 code;
   __u16 ident;
  } icmpt;

  __u32 spi;
 } u;
};






struct ifaddrmsg
{
 unsigned char ifa_family;
 unsigned char ifa_prefixlen;
 unsigned char ifa_flags;
 unsigned char ifa_scope;
 int ifa_index;
};

enum
{
 IFA_UNSPEC,
 IFA_ADDRESS,
 IFA_LOCAL,
 IFA_LABEL,
 IFA_BROADCAST,
 IFA_ANYCAST,
 IFA_CACHEINFO,
 IFA_MULTICAST,
 __IFA_MAX
};
# 423 "include/linux/rtnetlink.h"
struct ifa_cacheinfo
{
 __u32 ifa_prefered;
 __u32 ifa_valid;
 __u32 cstamp;
 __u32 tstamp;
};
# 447 "include/linux/rtnetlink.h"
struct ndmsg
{
 unsigned char ndm_family;
 unsigned char ndm_pad1;
 unsigned short ndm_pad2;
 int ndm_ifindex;
 __u16 ndm_state;
 __u8 ndm_flags;
 __u8 ndm_type;
};

enum
{
 NDA_UNSPEC,
 NDA_DST,
 NDA_LLADDR,
 NDA_CACHEINFO,
 NDA_PROBES,
 __NDA_MAX
};
# 497 "include/linux/rtnetlink.h"
struct nda_cacheinfo
{
 __u32 ndm_confirmed;
 __u32 ndm_used;
 __u32 ndm_updated;
 __u32 ndm_refcnt;
};
# 531 "include/linux/rtnetlink.h"
struct ndt_stats
{
 __u64 ndts_allocs;
 __u64 ndts_destroys;
 __u64 ndts_hash_grows;
 __u64 ndts_res_failed;
 __u64 ndts_lookups;
 __u64 ndts_hits;
 __u64 ndts_rcv_probes_mcast;
 __u64 ndts_rcv_probes_ucast;
 __u64 ndts_periodic_gc_runs;
 __u64 ndts_forced_gc_runs;
};

enum {
 NDTPA_UNSPEC,
 NDTPA_IFINDEX,
 NDTPA_REFCNT,
 NDTPA_REACHABLE_TIME,
 NDTPA_BASE_REACHABLE_TIME,
 NDTPA_RETRANS_TIME,
 NDTPA_GC_STALETIME,
 NDTPA_DELAY_PROBE_TIME,
 NDTPA_QUEUE_LEN,
 NDTPA_APP_PROBES,
 NDTPA_UCAST_PROBES,
 NDTPA_MCAST_PROBES,
 NDTPA_ANYCAST_DELAY,
 NDTPA_PROXY_DELAY,
 NDTPA_PROXY_QLEN,
 NDTPA_LOCKTIME,
 __NDTPA_MAX
};


struct ndtmsg
{
 __u8 ndtm_family;
 __u8 ndtm_pad1;
 __u16 ndtm_pad2;
};

struct ndt_config
{
 __u16 ndtc_key_len;
 __u16 ndtc_entry_size;
 __u32 ndtc_entries;
 __u32 ndtc_last_flush;
 __u32 ndtc_last_rand;
 __u32 ndtc_hash_rnd;
 __u32 ndtc_hash_mask;
 __u32 ndtc_hash_chain_gc;
 __u32 ndtc_proxy_qlen;
};

enum {
 NDTA_UNSPEC,
 NDTA_NAME,
 NDTA_THRESH1,
 NDTA_THRESH2,
 NDTA_THRESH3,
 NDTA_CONFIG,
 NDTA_PARMS,
 NDTA_STATS,
 NDTA_GC_INTERVAL,
 __NDTA_MAX
};
# 609 "include/linux/rtnetlink.h"
struct rtgenmsg
{
 unsigned char rtgen_family;
};
# 623 "include/linux/rtnetlink.h"
struct ifinfomsg
{
 unsigned char ifi_family;
 unsigned char __ifi_pad;
 unsigned short ifi_type;
 int ifi_index;
 unsigned ifi_flags;
 unsigned ifi_change;
};





struct prefixmsg
{
 unsigned char prefix_family;
 unsigned char prefix_pad1;
 unsigned short prefix_pad2;
 int prefix_ifindex;
 unsigned char prefix_type;
 unsigned char prefix_len;
 unsigned char prefix_flags;
 unsigned char prefix_pad3;
};

enum
{
 PREFIX_UNSPEC,
 PREFIX_ADDRESS,
 PREFIX_CACHEINFO,
 __PREFIX_MAX
};



struct prefix_cacheinfo
{
 __u32 preferred_time;
 __u32 valid_time;
};


struct rtnl_link_stats
{
 __u32 rx_packets;
 __u32 tx_packets;
 __u32 rx_bytes;
 __u32 tx_bytes;
 __u32 rx_errors;
 __u32 tx_errors;
 __u32 rx_dropped;
 __u32 tx_dropped;
 __u32 multicast;
 __u32 collisions;


 __u32 rx_length_errors;
 __u32 rx_over_errors;
 __u32 rx_crc_errors;
 __u32 rx_frame_errors;
 __u32 rx_fifo_errors;
 __u32 rx_missed_errors;


 __u32 tx_aborted_errors;
 __u32 tx_carrier_errors;
 __u32 tx_fifo_errors;
 __u32 tx_heartbeat_errors;
 __u32 tx_window_errors;


 __u32 rx_compressed;
 __u32 tx_compressed;
};


struct rtnl_link_ifmap
{
 __u64 mem_start;
 __u64 mem_end;
 __u64 base_addr;
 __u16 irq;
 __u8 dma;
 __u8 port;
};

enum
{
 IFLA_UNSPEC,
 IFLA_ADDRESS,
 IFLA_BROADCAST,
 IFLA_IFNAME,
 IFLA_MTU,
 IFLA_LINK,
 IFLA_QDISC,
 IFLA_STATS,
 IFLA_COST,

 IFLA_PRIORITY,

 IFLA_MASTER,

 IFLA_WIRELESS,

 IFLA_PROTINFO,

 IFLA_TXQLEN,

 IFLA_MAP,

 IFLA_WEIGHT,

 __IFLA_MAX
};
# 775 "include/linux/rtnetlink.h"
enum
{
 IFLA_INET6_UNSPEC,
 IFLA_INET6_FLAGS,
 IFLA_INET6_CONF,
 IFLA_INET6_STATS,
 IFLA_INET6_MCAST,
 IFLA_INET6_CACHEINFO,
 __IFLA_INET6_MAX
};



struct ifla_cacheinfo
{
 __u32 max_reasm_len;
 __u32 tstamp;
 __u32 reachable_time;
 __u32 retrans_time;
};





struct tcmsg
{
 unsigned char tcm_family;
 unsigned char tcm__pad1;
 unsigned short tcm__pad2;
 int tcm_ifindex;
 __u32 tcm_handle;
 __u32 tcm_parent;
 __u32 tcm_info;
};

enum
{
 TCA_UNSPEC,
 TCA_KIND,
 TCA_OPTIONS,
 TCA_STATS,
 TCA_XSTATS,
 TCA_RATE,
 TCA_FCNT,
 TCA_STATS2,
 __TCA_MAX
};
# 852 "include/linux/rtnetlink.h"
struct tcamsg
{
 unsigned char tca_family;
 unsigned char tca__pad1;
 unsigned short tca__pad2;
};
# 869 "include/linux/rtnetlink.h"
extern size_t rtattr_strlcpy(char *dest, const struct rtattr *rta, size_t size);
static __inline__ __attribute__((always_inline)) int rtattr_strcmp(const struct rtattr *rta, const char *str)
{
 int len = strlen(str) + 1;
 return len > rta->rta_len || __builtin_memcmp(((void*)(((char*)(rta)) + (( ((sizeof(struct rtattr))+4 -1) & ~(4 -1) ) + (0)))), str, len);
}

extern int rtattr_parse(struct rtattr *tb[], int maxattr, struct rtattr *rta, int len);




extern struct sock *rtnl;

struct rtnetlink_link
{
 int (*doit)(struct sk_buff *, struct nlmsghdr*, void *attr);
 int (*dumpit)(struct sk_buff *, struct netlink_callback *cb);
};

extern struct rtnetlink_link * rtnetlink_links[32];
extern int rtnetlink_send(struct sk_buff *skb, u32 pid, u32 group, int echo);
extern int rtnetlink_put_metrics(struct sk_buff *skb, u32 *metrics);

extern void __rta_fill(struct sk_buff *skb, int attrtype, int attrlen, const void *data);
# 979 "include/linux/rtnetlink.h"
static inline __attribute__((always_inline)) struct rtattr *
__rta_reserve(struct sk_buff *skb, int attrtype, int attrlen)
{
 struct rtattr *rta;
 int size = (( ((sizeof(struct rtattr))+4 -1) & ~(4 -1) ) + (attrlen));

 rta = (struct rtattr*)skb_put(skb, ( ((size)+4 -1) & ~(4 -1) ));
 rta->rta_type = attrtype;
 rta->rta_len = size;
 __memset_generic((((void*)(((char*)(rta)) + (( ((sizeof(struct rtattr))+4 -1) & ~(4 -1) ) + (0)))) + attrlen),(0),(( ((size)+4 -1) & ~(4 -1) ) - size));
 return rta;
}






extern void rtmsg_ifinfo(int type, struct net_device *dev, unsigned change);

extern struct semaphore rtnl_sem;
# 1009 "include/linux/rtnetlink.h"
extern void rtnl_lock(void);
extern int rtnl_lock_interruptible(void);
extern void rtnl_unlock(void);
extern void rtnetlink_init(void);
# 13 "include/net/dst.h" 2


# 1 "include/net/neighbour.h" 1
# 55 "include/net/neighbour.h"
# 1 "include/linux/seq_file.h" 1
# 9 "include/linux/seq_file.h"
struct seq_operations;
struct file;
struct vfsmount;
struct dentry;
struct inode;

struct seq_file {
 char *buf;
 size_t size;
 size_t from;
 size_t count;
 loff_t index;
 loff_t version;
 struct semaphore sem;
 struct seq_operations *op;
 void *private;
};

struct seq_operations {
 void * (*start) (struct seq_file *m, loff_t *pos);
 void (*stop) (struct seq_file *m, void *v);
 void * (*next) (struct seq_file *m, void *v, loff_t *pos);
 int (*show) (struct seq_file *m, void *v);
};

int seq_open(struct file *, struct seq_operations *);
ssize_t seq_read(struct file *, char *, size_t, loff_t *);
loff_t seq_lseek(struct file *, loff_t, int);
int seq_release(struct inode *, struct file *);
int seq_escape(struct seq_file *, const char *, const char *);
int seq_putc(struct seq_file *m, char c);
int seq_puts(struct seq_file *m, const char *s);

int seq_printf(struct seq_file *, const char *, ...)
 __attribute__ ((format (printf,2,3)));

int seq_path(struct seq_file *, struct vfsmount *, struct dentry *, char *);

int single_open(struct file *, int (*)(struct seq_file *, void *), void *);
int single_release(struct inode *, struct file *);
int seq_release_private(struct inode *, struct file *);
# 56 "include/net/neighbour.h" 2


# 1 "include/linux/sysctl.h" 1
# 26 "include/linux/sysctl.h"
struct file;






struct __sysctl_args {
 int *name;
 int nlen;
 void *oldval;
 size_t *oldlenp;
 void *newval;
 size_t newlen;
 unsigned long __unused[4];
};
# 53 "include/linux/sysctl.h"
enum
{
 CTL_KERN=1,
 CTL_VM=2,
 CTL_NET=3,
 CTL_PROC=4,
 CTL_FS=5,
 CTL_DEBUG=6,
 CTL_DEV=7,
 CTL_BUS=8,
 CTL_ABI=9,
 CTL_CPU=10
};


enum
{
 CTL_BUS_ISA=1
};


enum
{
 INOTIFY_MAX_USER_INSTANCES=1,
 INOTIFY_MAX_USER_WATCHES=2,
 INOTIFY_MAX_QUEUED_EVENTS=3
};


enum
{
 KERN_OSTYPE=1,
 KERN_OSRELEASE=2,
 KERN_OSREV=3,
 KERN_VERSION=4,
 KERN_SECUREMASK=5,
 KERN_PROF=6,
 KERN_NODENAME=7,
 KERN_DOMAINNAME=8,

 KERN_CAP_BSET=14,
 KERN_PANIC=15,
 KERN_REALROOTDEV=16,

 KERN_SPARC_REBOOT=21,
 KERN_CTLALTDEL=22,
 KERN_PRINTK=23,
 KERN_NAMETRANS=24,
 KERN_PPC_HTABRECLAIM=25,
 KERN_PPC_ZEROPAGED=26,
 KERN_PPC_POWERSAVE_NAP=27,
 KERN_MODPROBE=28,
 KERN_SG_BIG_BUFF=29,
 KERN_ACCT=30,
 KERN_PPC_L2CR=31,

 KERN_RTSIGNR=32,
 KERN_RTSIGMAX=33,

 KERN_SHMMAX=34,
 KERN_MSGMAX=35,
 KERN_MSGMNB=36,
 KERN_MSGPOOL=37,
 KERN_SYSRQ=38,
 KERN_MAX_THREADS=39,
  KERN_RANDOM=40,
  KERN_SHMALL=41,
  KERN_MSGMNI=42,
  KERN_SEM=43,
  KERN_SPARC_STOP_A=44,
  KERN_SHMMNI=45,
 KERN_OVERFLOWUID=46,
 KERN_OVERFLOWGID=47,
 KERN_SHMPATH=48,
 KERN_HOTPLUG=49,
 KERN_IEEE_EMULATION_WARNINGS=50,
 KERN_S390_USER_DEBUG_LOGGING=51,
 KERN_CORE_USES_PID=52,
 KERN_TAINTED=53,
 KERN_CADPID=54,
 KERN_PIDMAX=55,
   KERN_CORE_PATTERN=56,
 KERN_PANIC_ON_OOPS=57,
 KERN_HPPA_PWRSW=58,
 KERN_HPPA_UNALIGNED=59,
 KERN_PRINTK_RATELIMIT=60,
 KERN_PRINTK_RATELIMIT_BURST=61,
 KERN_PTY=62,
 KERN_NGROUPS_MAX=63,
 KERN_SPARC_SCONS_PWROFF=64,
 KERN_HZ_TIMER=65,
 KERN_UNKNOWN_NMI_PANIC=66,
 KERN_BOOTLOADER_TYPE=67,
 KERN_RANDOMIZE=68,
 KERN_SETUID_DUMPABLE=69,
 KERN_SPIN_RETRY=70,
};



enum
{
 VM_UNUSED1=1,
 VM_UNUSED2=2,
 VM_UNUSED3=3,
 VM_UNUSED4=4,
 VM_OVERCOMMIT_MEMORY=5,
 VM_UNUSED5=6,
 VM_UNUSED7=7,
 VM_UNUSED8=8,
 VM_UNUSED9=9,
 VM_PAGE_CLUSTER=10,
 VM_DIRTY_BACKGROUND=11,
 VM_DIRTY_RATIO=12,
 VM_DIRTY_WB_CS=13,
 VM_DIRTY_EXPIRE_CS=14,
 VM_NR_PDFLUSH_THREADS=15,
 VM_OVERCOMMIT_RATIO=16,
 VM_PAGEBUF=17,
 VM_HUGETLB_PAGES=18,
 VM_SWAPPINESS=19,
 VM_LOWMEM_RESERVE_RATIO=20,
 VM_MIN_FREE_KBYTES=21,
 VM_MAX_MAP_COUNT=22,
 VM_LAPTOP_MODE=23,
 VM_BLOCK_DUMP=24,
 VM_HUGETLB_GROUP=25,
 VM_VFS_CACHE_PRESSURE=26,
 VM_LEGACY_VA_LAYOUT=27,
 VM_SWAP_TOKEN_TIMEOUT=28,
};



enum
{
 NET_CORE=1,
 NET_ETHER=2,
 NET_802=3,
 NET_UNIX=4,
 NET_IPV4=5,
 NET_IPX=6,
 NET_ATALK=7,
 NET_NETROM=8,
 NET_AX25=9,
 NET_BRIDGE=10,
 NET_ROSE=11,
 NET_IPV6=12,
 NET_X25=13,
 NET_TR=14,
 NET_DECNET=15,
 NET_ECONET=16,
 NET_SCTP=17,
};


enum
{
 RANDOM_POOLSIZE=1,
 RANDOM_ENTROPY_COUNT=2,
 RANDOM_READ_THRESH=3,
 RANDOM_WRITE_THRESH=4,
 RANDOM_BOOT_ID=5,
 RANDOM_UUID=6
};


enum
{
 PTY_MAX=1,
 PTY_NR=2
};


enum
{
 BUS_ISA_MEM_BASE=1,
 BUS_ISA_PORT_BASE=2,
 BUS_ISA_PORT_SHIFT=3
};


enum
{
 NET_CORE_WMEM_MAX=1,
 NET_CORE_RMEM_MAX=2,
 NET_CORE_WMEM_DEFAULT=3,
 NET_CORE_RMEM_DEFAULT=4,

 NET_CORE_MAX_BACKLOG=6,
 NET_CORE_FASTROUTE=7,
 NET_CORE_MSG_COST=8,
 NET_CORE_MSG_BURST=9,
 NET_CORE_OPTMEM_MAX=10,
 NET_CORE_HOT_LIST_LENGTH=11,
 NET_CORE_DIVERT_VERSION=12,
 NET_CORE_NO_CONG_THRESH=13,
 NET_CORE_NO_CONG=14,
 NET_CORE_LO_CONG=15,
 NET_CORE_MOD_CONG=16,
 NET_CORE_DEV_WEIGHT=17,
 NET_CORE_SOMAXCONN=18,
 NET_CORE_BUDGET=19,
};







enum
{
 NET_UNIX_DESTROY_DELAY=1,
 NET_UNIX_DELETE_DELAY=2,
 NET_UNIX_MAX_DGRAM_QLEN=3,
};


enum
{

 NET_IPV4_FORWARD=8,
 NET_IPV4_DYNADDR=9,

 NET_IPV4_CONF=16,
 NET_IPV4_NEIGH=17,
 NET_IPV4_ROUTE=18,
 NET_IPV4_FIB_HASH=19,
 NET_IPV4_NETFILTER=20,

 NET_IPV4_TCP_TIMESTAMPS=33,
 NET_IPV4_TCP_WINDOW_SCALING=34,
 NET_IPV4_TCP_SACK=35,
 NET_IPV4_TCP_RETRANS_COLLAPSE=36,
 NET_IPV4_DEFAULT_TTL=37,
 NET_IPV4_AUTOCONFIG=38,
 NET_IPV4_NO_PMTU_DISC=39,
 NET_IPV4_TCP_SYN_RETRIES=40,
 NET_IPV4_IPFRAG_HIGH_THRESH=41,
 NET_IPV4_IPFRAG_LOW_THRESH=42,
 NET_IPV4_IPFRAG_TIME=43,
 NET_IPV4_TCP_MAX_KA_PROBES=44,
 NET_IPV4_TCP_KEEPALIVE_TIME=45,
 NET_IPV4_TCP_KEEPALIVE_PROBES=46,
 NET_IPV4_TCP_RETRIES1=47,
 NET_IPV4_TCP_RETRIES2=48,
 NET_IPV4_TCP_FIN_TIMEOUT=49,
 NET_IPV4_IP_MASQ_DEBUG=50,
 NET_TCP_SYNCOOKIES=51,
 NET_TCP_STDURG=52,
 NET_TCP_RFC1337=53,
 NET_TCP_SYN_TAILDROP=54,
 NET_TCP_MAX_SYN_BACKLOG=55,
 NET_IPV4_LOCAL_PORT_RANGE=56,
 NET_IPV4_ICMP_ECHO_IGNORE_ALL=57,
 NET_IPV4_ICMP_ECHO_IGNORE_BROADCASTS=58,
 NET_IPV4_ICMP_SOURCEQUENCH_RATE=59,
 NET_IPV4_ICMP_DESTUNREACH_RATE=60,
 NET_IPV4_ICMP_TIMEEXCEED_RATE=61,
 NET_IPV4_ICMP_PARAMPROB_RATE=62,
 NET_IPV4_ICMP_ECHOREPLY_RATE=63,
 NET_IPV4_ICMP_IGNORE_BOGUS_ERROR_RESPONSES=64,
 NET_IPV4_IGMP_MAX_MEMBERSHIPS=65,
 NET_TCP_TW_RECYCLE=66,
 NET_IPV4_ALWAYS_DEFRAG=67,
 NET_IPV4_TCP_KEEPALIVE_INTVL=68,
 NET_IPV4_INET_PEER_THRESHOLD=69,
 NET_IPV4_INET_PEER_MINTTL=70,
 NET_IPV4_INET_PEER_MAXTTL=71,
 NET_IPV4_INET_PEER_GC_MINTIME=72,
 NET_IPV4_INET_PEER_GC_MAXTIME=73,
 NET_TCP_ORPHAN_RETRIES=74,
 NET_TCP_ABORT_ON_OVERFLOW=75,
 NET_TCP_SYNACK_RETRIES=76,
 NET_TCP_MAX_ORPHANS=77,
 NET_TCP_MAX_TW_BUCKETS=78,
 NET_TCP_FACK=79,
 NET_TCP_REORDERING=80,
 NET_TCP_ECN=81,
 NET_TCP_DSACK=82,
 NET_TCP_MEM=83,
 NET_TCP_WMEM=84,
 NET_TCP_RMEM=85,
 NET_TCP_APP_WIN=86,
 NET_TCP_ADV_WIN_SCALE=87,
 NET_IPV4_NONLOCAL_BIND=88,
 NET_IPV4_ICMP_RATELIMIT=89,
 NET_IPV4_ICMP_RATEMASK=90,
 NET_TCP_TW_REUSE=91,
 NET_TCP_FRTO=92,
 NET_TCP_LOW_LATENCY=93,
 NET_IPV4_IPFRAG_SECRET_INTERVAL=94,
 NET_IPV4_IGMP_MAX_MSF=96,
 NET_TCP_NO_METRICS_SAVE=97,
 NET_TCP_DEFAULT_WIN_SCALE=105,
 NET_TCP_MODERATE_RCVBUF=106,
 NET_TCP_TSO_WIN_DIVISOR=107,
 NET_TCP_BIC_BETA=108,
 NET_IPV4_ICMP_ERRORS_USE_INBOUND_IFADDR=109,
 NET_TCP_CONG_CONTROL=110,
};

enum {
 NET_IPV4_ROUTE_FLUSH=1,
 NET_IPV4_ROUTE_MIN_DELAY=2,
 NET_IPV4_ROUTE_MAX_DELAY=3,
 NET_IPV4_ROUTE_GC_THRESH=4,
 NET_IPV4_ROUTE_MAX_SIZE=5,
 NET_IPV4_ROUTE_GC_MIN_INTERVAL=6,
 NET_IPV4_ROUTE_GC_TIMEOUT=7,
 NET_IPV4_ROUTE_GC_INTERVAL=8,
 NET_IPV4_ROUTE_REDIRECT_LOAD=9,
 NET_IPV4_ROUTE_REDIRECT_NUMBER=10,
 NET_IPV4_ROUTE_REDIRECT_SILENCE=11,
 NET_IPV4_ROUTE_ERROR_COST=12,
 NET_IPV4_ROUTE_ERROR_BURST=13,
 NET_IPV4_ROUTE_GC_ELASTICITY=14,
 NET_IPV4_ROUTE_MTU_EXPIRES=15,
 NET_IPV4_ROUTE_MIN_PMTU=16,
 NET_IPV4_ROUTE_MIN_ADVMSS=17,
 NET_IPV4_ROUTE_SECRET_INTERVAL=18,
 NET_IPV4_ROUTE_GC_MIN_INTERVAL_MS=19,
};

enum
{
 NET_PROTO_CONF_ALL=-2,
 NET_PROTO_CONF_DEFAULT=-3


};

enum
{
 NET_IPV4_CONF_FORWARDING=1,
 NET_IPV4_CONF_MC_FORWARDING=2,
 NET_IPV4_CONF_PROXY_ARP=3,
 NET_IPV4_CONF_ACCEPT_REDIRECTS=4,
 NET_IPV4_CONF_SECURE_REDIRECTS=5,
 NET_IPV4_CONF_SEND_REDIRECTS=6,
 NET_IPV4_CONF_SHARED_MEDIA=7,
 NET_IPV4_CONF_RP_FILTER=8,
 NET_IPV4_CONF_ACCEPT_SOURCE_ROUTE=9,
 NET_IPV4_CONF_BOOTP_RELAY=10,
 NET_IPV4_CONF_LOG_MARTIANS=11,
 NET_IPV4_CONF_TAG=12,
 NET_IPV4_CONF_ARPFILTER=13,
 NET_IPV4_CONF_MEDIUM_ID=14,
 NET_IPV4_CONF_NOXFRM=15,
 NET_IPV4_CONF_NOPOLICY=16,
 NET_IPV4_CONF_FORCE_IGMP_VERSION=17,
 NET_IPV4_CONF_ARP_ANNOUNCE=18,
 NET_IPV4_CONF_ARP_IGNORE=19,
 NET_IPV4_CONF_PROMOTE_SECONDARIES=20,
 __NET_IPV4_CONF_MAX
};


enum
{
 NET_IPV4_NF_CONNTRACK_MAX=1,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_SYN_SENT=2,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_SYN_RECV=3,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_ESTABLISHED=4,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_FIN_WAIT=5,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_CLOSE_WAIT=6,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_LAST_ACK=7,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_TIME_WAIT=8,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_CLOSE=9,
 NET_IPV4_NF_CONNTRACK_UDP_TIMEOUT=10,
 NET_IPV4_NF_CONNTRACK_UDP_TIMEOUT_STREAM=11,
 NET_IPV4_NF_CONNTRACK_ICMP_TIMEOUT=12,
 NET_IPV4_NF_CONNTRACK_GENERIC_TIMEOUT=13,
 NET_IPV4_NF_CONNTRACK_BUCKETS=14,
 NET_IPV4_NF_CONNTRACK_LOG_INVALID=15,
 NET_IPV4_NF_CONNTRACK_TCP_TIMEOUT_MAX_RETRANS=16,
 NET_IPV4_NF_CONNTRACK_TCP_LOOSE=17,
 NET_IPV4_NF_CONNTRACK_TCP_BE_LIBERAL=18,
 NET_IPV4_NF_CONNTRACK_TCP_MAX_RETRANS=19,
  NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_CLOSED=20,
  NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_COOKIE_WAIT=21,
  NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_COOKIE_ECHOED=22,
  NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_ESTABLISHED=23,
  NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_SHUTDOWN_SENT=24,
  NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_SHUTDOWN_RECD=25,
  NET_IPV4_NF_CONNTRACK_SCTP_TIMEOUT_SHUTDOWN_ACK_SENT=26,
 NET_IPV4_NF_CONNTRACK_COUNT=27,
};


enum {
 NET_IPV6_CONF=16,
 NET_IPV6_NEIGH=17,
 NET_IPV6_ROUTE=18,
 NET_IPV6_ICMP=19,
 NET_IPV6_BINDV6ONLY=20,
 NET_IPV6_IP6FRAG_HIGH_THRESH=21,
 NET_IPV6_IP6FRAG_LOW_THRESH=22,
 NET_IPV6_IP6FRAG_TIME=23,
 NET_IPV6_IP6FRAG_SECRET_INTERVAL=24,
 NET_IPV6_MLD_MAX_MSF=25,
};

enum {
 NET_IPV6_ROUTE_FLUSH=1,
 NET_IPV6_ROUTE_GC_THRESH=2,
 NET_IPV6_ROUTE_MAX_SIZE=3,
 NET_IPV6_ROUTE_GC_MIN_INTERVAL=4,
 NET_IPV6_ROUTE_GC_TIMEOUT=5,
 NET_IPV6_ROUTE_GC_INTERVAL=6,
 NET_IPV6_ROUTE_GC_ELASTICITY=7,
 NET_IPV6_ROUTE_MTU_EXPIRES=8,
 NET_IPV6_ROUTE_MIN_ADVMSS=9,
 NET_IPV6_ROUTE_GC_MIN_INTERVAL_MS=10
};

enum {
 NET_IPV6_FORWARDING=1,
 NET_IPV6_HOP_LIMIT=2,
 NET_IPV6_MTU=3,
 NET_IPV6_ACCEPT_RA=4,
 NET_IPV6_ACCEPT_REDIRECTS=5,
 NET_IPV6_AUTOCONF=6,
 NET_IPV6_DAD_TRANSMITS=7,
 NET_IPV6_RTR_SOLICITS=8,
 NET_IPV6_RTR_SOLICIT_INTERVAL=9,
 NET_IPV6_RTR_SOLICIT_DELAY=10,
 NET_IPV6_USE_TEMPADDR=11,
 NET_IPV6_TEMP_VALID_LFT=12,
 NET_IPV6_TEMP_PREFERED_LFT=13,
 NET_IPV6_REGEN_MAX_RETRY=14,
 NET_IPV6_MAX_DESYNC_FACTOR=15,
 NET_IPV6_MAX_ADDRESSES=16,
 NET_IPV6_FORCE_MLD_VERSION=17,
 __NET_IPV6_MAX
};


enum {
 NET_IPV6_ICMP_RATELIMIT=1
};


enum {
 NET_NEIGH_MCAST_SOLICIT=1,
 NET_NEIGH_UCAST_SOLICIT=2,
 NET_NEIGH_APP_SOLICIT=3,
 NET_NEIGH_RETRANS_TIME=4,
 NET_NEIGH_REACHABLE_TIME=5,
 NET_NEIGH_DELAY_PROBE_TIME=6,
 NET_NEIGH_GC_STALE_TIME=7,
 NET_NEIGH_UNRES_QLEN=8,
 NET_NEIGH_PROXY_QLEN=9,
 NET_NEIGH_ANYCAST_DELAY=10,
 NET_NEIGH_PROXY_DELAY=11,
 NET_NEIGH_LOCKTIME=12,
 NET_NEIGH_GC_INTERVAL=13,
 NET_NEIGH_GC_THRESH1=14,
 NET_NEIGH_GC_THRESH2=15,
 NET_NEIGH_GC_THRESH3=16,
 NET_NEIGH_RETRANS_TIME_MS=17,
 NET_NEIGH_REACHABLE_TIME_MS=18,
 __NET_NEIGH_MAX
};


enum {
 NET_IPX_PPROP_BROADCASTING=1,
 NET_IPX_FORWARDING=2
};



enum {
 NET_ATALK_AARP_EXPIRY_TIME=1,
 NET_ATALK_AARP_TICK_TIME=2,
 NET_ATALK_AARP_RETRANSMIT_LIMIT=3,
 NET_ATALK_AARP_RESOLVE_TIME=4
};



enum {
 NET_NETROM_DEFAULT_PATH_QUALITY=1,
 NET_NETROM_OBSOLESCENCE_COUNT_INITIALISER=2,
 NET_NETROM_NETWORK_TTL_INITIALISER=3,
 NET_NETROM_TRANSPORT_TIMEOUT=4,
 NET_NETROM_TRANSPORT_MAXIMUM_TRIES=5,
 NET_NETROM_TRANSPORT_ACKNOWLEDGE_DELAY=6,
 NET_NETROM_TRANSPORT_BUSY_DELAY=7,
 NET_NETROM_TRANSPORT_REQUESTED_WINDOW_SIZE=8,
 NET_NETROM_TRANSPORT_NO_ACTIVITY_TIMEOUT=9,
 NET_NETROM_ROUTING_CONTROL=10,
 NET_NETROM_LINK_FAILS_COUNT=11
};


enum {
 NET_AX25_IP_DEFAULT_MODE=1,
 NET_AX25_DEFAULT_MODE=2,
 NET_AX25_BACKOFF_TYPE=3,
 NET_AX25_CONNECT_MODE=4,
 NET_AX25_STANDARD_WINDOW=5,
 NET_AX25_EXTENDED_WINDOW=6,
 NET_AX25_T1_TIMEOUT=7,
 NET_AX25_T2_TIMEOUT=8,
 NET_AX25_T3_TIMEOUT=9,
 NET_AX25_IDLE_TIMEOUT=10,
 NET_AX25_N2=11,
 NET_AX25_PACLEN=12,
 NET_AX25_PROTOCOL=13,
 NET_AX25_DAMA_SLAVE_TIMEOUT=14
};


enum {
 NET_ROSE_RESTART_REQUEST_TIMEOUT=1,
 NET_ROSE_CALL_REQUEST_TIMEOUT=2,
 NET_ROSE_RESET_REQUEST_TIMEOUT=3,
 NET_ROSE_CLEAR_REQUEST_TIMEOUT=4,
 NET_ROSE_ACK_HOLD_BACK_TIMEOUT=5,
 NET_ROSE_ROUTING_CONTROL=6,
 NET_ROSE_LINK_FAIL_TIMEOUT=7,
 NET_ROSE_MAX_VCS=8,
 NET_ROSE_WINDOW_SIZE=9,
 NET_ROSE_NO_ACTIVITY_TIMEOUT=10
};


enum {
 NET_X25_RESTART_REQUEST_TIMEOUT=1,
 NET_X25_CALL_REQUEST_TIMEOUT=2,
 NET_X25_RESET_REQUEST_TIMEOUT=3,
 NET_X25_CLEAR_REQUEST_TIMEOUT=4,
 NET_X25_ACK_HOLD_BACK_TIMEOUT=5
};


enum
{
 NET_TR_RIF_TIMEOUT=1
};


enum {
 NET_DECNET_NODE_TYPE = 1,
 NET_DECNET_NODE_ADDRESS = 2,
 NET_DECNET_NODE_NAME = 3,
 NET_DECNET_DEFAULT_DEVICE = 4,
 NET_DECNET_TIME_WAIT = 5,
 NET_DECNET_DN_COUNT = 6,
 NET_DECNET_DI_COUNT = 7,
 NET_DECNET_DR_COUNT = 8,
 NET_DECNET_DST_GC_INTERVAL = 9,
 NET_DECNET_CONF = 10,
 NET_DECNET_NO_FC_MAX_CWND = 11,
 NET_DECNET_DEBUG_LEVEL = 255
};


enum {
 NET_DECNET_CONF_LOOPBACK = -2,
 NET_DECNET_CONF_DDCMP = -3,
 NET_DECNET_CONF_PPP = -4,
 NET_DECNET_CONF_X25 = -5,
 NET_DECNET_CONF_GRE = -6,
 NET_DECNET_CONF_ETHER = -7


};


enum {
 NET_DECNET_CONF_DEV_PRIORITY = 1,
 NET_DECNET_CONF_DEV_T1 = 2,
 NET_DECNET_CONF_DEV_T2 = 3,
 NET_DECNET_CONF_DEV_T3 = 4,
 NET_DECNET_CONF_DEV_FORWARDING = 5,
 NET_DECNET_CONF_DEV_BLKSIZE = 6,
 NET_DECNET_CONF_DEV_STATE = 7
};


enum {
 NET_SCTP_RTO_INITIAL = 1,
 NET_SCTP_RTO_MIN = 2,
 NET_SCTP_RTO_MAX = 3,
 NET_SCTP_RTO_ALPHA = 4,
 NET_SCTP_RTO_BETA = 5,
 NET_SCTP_VALID_COOKIE_LIFE = 6,
 NET_SCTP_ASSOCIATION_MAX_RETRANS = 7,
 NET_SCTP_PATH_MAX_RETRANS = 8,
 NET_SCTP_MAX_INIT_RETRANSMITS = 9,
 NET_SCTP_HB_INTERVAL = 10,
 NET_SCTP_PRESERVE_ENABLE = 11,
 NET_SCTP_MAX_BURST = 12,
 NET_SCTP_ADDIP_ENABLE = 13,
 NET_SCTP_PRSCTP_ENABLE = 14,
 NET_SCTP_SNDBUF_POLICY = 15,
 NET_SCTP_SACK_TIMEOUT = 16,
};


enum {
 NET_BRIDGE_NF_CALL_ARPTABLES = 1,
 NET_BRIDGE_NF_CALL_IPTABLES = 2,
 NET_BRIDGE_NF_CALL_IP6TABLES = 3,
 NET_BRIDGE_NF_FILTER_VLAN_TAGGED = 4,
};




enum
{
 FS_NRINODE=1,
 FS_STATINODE=2,
 FS_MAXINODE=3,
 FS_NRDQUOT=4,
 FS_MAXDQUOT=5,
 FS_NRFILE=6,
 FS_MAXFILE=7,
 FS_DENTRY=8,
 FS_NRSUPER=9,
 FS_MAXSUPER=10,
 FS_OVERFLOWUID=11,
 FS_OVERFLOWGID=12,
 FS_LEASES=13,
 FS_DIR_NOTIFY=14,
 FS_LEASE_TIME=15,
 FS_DQSTATS=16,
 FS_XFS=17,
 FS_AIO_NR=18,
 FS_AIO_MAX_NR=19,
 FS_INOTIFY=20,
};


enum {
 FS_DQ_LOOKUPS = 1,
 FS_DQ_DROPS = 2,
 FS_DQ_READS = 3,
 FS_DQ_WRITES = 4,
 FS_DQ_CACHE_HITS = 5,
 FS_DQ_ALLOCATED = 6,
 FS_DQ_FREE = 7,
 FS_DQ_SYNCS = 8,
 FS_DQ_WARNINGS = 9,
};




enum {
 DEV_CDROM=1,
 DEV_HWMON=2,
 DEV_PARPORT=3,
 DEV_RAID=4,
 DEV_MAC_HID=5,
 DEV_SCSI=6,
};


enum {
 DEV_CDROM_INFO=1,
 DEV_CDROM_AUTOCLOSE=2,
 DEV_CDROM_AUTOEJECT=3,
 DEV_CDROM_DEBUG=4,
 DEV_CDROM_LOCK=5,
 DEV_CDROM_CHECK_MEDIA=6
};


enum {
 DEV_PARPORT_DEFAULT=-3
};


enum {
 DEV_RAID_SPEED_LIMIT_MIN=1,
 DEV_RAID_SPEED_LIMIT_MAX=2
};


enum {
 DEV_PARPORT_DEFAULT_TIMESLICE=1,
 DEV_PARPORT_DEFAULT_SPINTIME=2
};


enum {
 DEV_PARPORT_SPINTIME=1,
 DEV_PARPORT_BASE_ADDR=2,
 DEV_PARPORT_IRQ=3,
 DEV_PARPORT_DMA=4,
 DEV_PARPORT_MODES=5,
 DEV_PARPORT_DEVICES=6,
 DEV_PARPORT_AUTOPROBE=16
};


enum {
 DEV_PARPORT_DEVICES_ACTIVE=-3,
};


enum {
 DEV_PARPORT_DEVICE_TIMESLICE=1,
};


enum {
 DEV_MAC_HID_KEYBOARD_SENDS_LINUX_KEYCODES=1,
 DEV_MAC_HID_KEYBOARD_LOCK_KEYCODES=2,
 DEV_MAC_HID_MOUSE_BUTTON_EMULATION=3,
 DEV_MAC_HID_MOUSE_BUTTON2_KEYCODE=4,
 DEV_MAC_HID_MOUSE_BUTTON3_KEYCODE=5,
 DEV_MAC_HID_ADB_MOUSE_SENDS_KEYCODES=6
};


enum {
 DEV_SCSI_LOGGING_LEVEL=1,
};


enum
{
 ABI_DEFHANDLER_COFF=1,
 ABI_DEFHANDLER_ELF=2,
 ABI_DEFHANDLER_LCALL7=3,
 ABI_DEFHANDLER_LIBCSO=4,
 ABI_TRACE=5,
 ABI_FAKE_UTSNAME=6,
};



extern void sysctl_init(void);

typedef struct ctl_table ctl_table;

typedef int ctl_handler (ctl_table *table, int *name, int nlen,
    void *oldval, size_t *oldlenp,
    void *newval, size_t newlen,
    void **context);

typedef int proc_handler (ctl_table *ctl, int write, struct file * filp,
     void *buffer, size_t *lenp, loff_t *ppos);

extern int proc_dostring(ctl_table *, int, struct file *,
    void *, size_t *, loff_t *);
extern int proc_dointvec(ctl_table *, int, struct file *,
    void *, size_t *, loff_t *);
extern int proc_dointvec_bset(ctl_table *, int, struct file *,
         void *, size_t *, loff_t *);
extern int proc_dointvec_minmax(ctl_table *, int, struct file *,
    void *, size_t *, loff_t *);
extern int proc_dointvec_jiffies(ctl_table *, int, struct file *,
     void *, size_t *, loff_t *);
extern int proc_dointvec_userhz_jiffies(ctl_table *, int, struct file *,
     void *, size_t *, loff_t *);
extern int proc_dointvec_ms_jiffies(ctl_table *, int, struct file *,
        void *, size_t *, loff_t *);
extern int proc_doulongvec_minmax(ctl_table *, int, struct file *,
      void *, size_t *, loff_t *);
extern int proc_doulongvec_ms_jiffies_minmax(ctl_table *table, int,
          struct file *, void *, size_t *, loff_t *);

extern int do_sysctl (int *name, int nlen,
        void *oldval, size_t *oldlenp,
        void *newval, size_t newlen);

extern int do_sysctl_strategy (ctl_table *table,
          int *name, int nlen,
          void *oldval, size_t *oldlenp,
          void *newval, size_t newlen, void ** context);

extern ctl_handler sysctl_string;
extern ctl_handler sysctl_intvec;
extern ctl_handler sysctl_jiffies;
extern ctl_handler sysctl_ms_jiffies;
# 876 "include/linux/sysctl.h"
struct ctl_table
{
 int ctl_name;
 const char *procname;
 void *data;
 int maxlen;
 mode_t mode;
 ctl_table *child;
 proc_handler *proc_handler;
 ctl_handler *strategy;
 struct proc_dir_entry *de;
 void *extra1;
 void *extra2;
};



struct ctl_table_header
{
 ctl_table *ctl_table;
 struct list_head ctl_entry;
};

struct ctl_table_header * register_sysctl_table(ctl_table * table,
      int insert_at_head);
void unregister_sysctl_table(struct ctl_table_header * table);
# 59 "include/net/neighbour.h" 2





struct neighbour;

struct neigh_parms
{
 struct net_device *dev;
 struct neigh_parms *next;
 int (*neigh_setup)(struct neighbour *);
 struct neigh_table *tbl;

 void *sysctl_table;

 int dead;
 atomic_t refcnt;
 struct rcu_head rcu_head;

 int base_reachable_time;
 int retrans_time;
 int gc_staletime;
 int reachable_time;
 int delay_probe_time;

 int queue_len;
 int ucast_probes;
 int app_probes;
 int mcast_probes;
 int anycast_delay;
 int proxy_delay;
 int proxy_qlen;
 int locktime;
};

struct neigh_statistics
{
 unsigned long allocs;
 unsigned long destroys;
 unsigned long hash_grows;

 unsigned long res_failed;

 unsigned long lookups;
 unsigned long hits;

 unsigned long rcv_probes_mcast;
 unsigned long rcv_probes_ucast;

 unsigned long periodic_gc_runs;
 unsigned long forced_gc_runs;
};
# 120 "include/net/neighbour.h"
struct neighbour
{
 struct neighbour *next;
 struct neigh_table *tbl;
 struct neigh_parms *parms;
 struct net_device *dev;
 unsigned long used;
 unsigned long confirmed;
 unsigned long updated;
 __u8 flags;
 __u8 nud_state;
 __u8 type;
 __u8 dead;
 atomic_t probes;
 rwlock_t lock;
 unsigned char ha[(32 +sizeof(unsigned long)-1)&~(sizeof(unsigned long)-1)];
 struct hh_cache *hh;
 atomic_t refcnt;
 int (*output)(struct sk_buff *skb);
 struct sk_buff_head arp_queue;
 struct timer_list timer;
 struct neigh_ops *ops;
 u8 primary_key[0];
};

struct neigh_ops
{
 int family;
 void (*destructor)(struct neighbour *);
 void (*solicit)(struct neighbour *, struct sk_buff*);
 void (*error_report)(struct neighbour *, struct sk_buff*);
 int (*output)(struct sk_buff*);
 int (*connected_output)(struct sk_buff*);
 int (*hh_output)(struct sk_buff*);
 int (*queue_xmit)(struct sk_buff*);
};

struct pneigh_entry
{
 struct pneigh_entry *next;
 struct net_device *dev;
 u8 key[0];
};






struct neigh_table
{
 struct neigh_table *next;
 int family;
 int entry_size;
 int key_len;
 __u32 (*hash)(const void *pkey, const struct net_device *);
 int (*constructor)(struct neighbour *);
 int (*pconstructor)(struct pneigh_entry *);
 void (*pdestructor)(struct pneigh_entry *);
 void (*proxy_redo)(struct sk_buff *skb);
 char *id;
 struct neigh_parms parms;

 int gc_interval;
 int gc_thresh1;
 int gc_thresh2;
 int gc_thresh3;
 unsigned long last_flush;
 struct timer_list gc_timer;
 struct timer_list proxy_timer;
 struct sk_buff_head proxy_queue;
 atomic_t entries;
 rwlock_t lock;
 unsigned long last_rand;
 kmem_cache_t *kmem_cachep;
 struct neigh_statistics *stats;
 struct neighbour **hash_buckets;
 unsigned int hash_mask;
 __u32 hash_rnd;
 unsigned int hash_chain_gc;
 struct pneigh_entry **phash_buckets;

 struct proc_dir_entry *pde;

};
# 213 "include/net/neighbour.h"
extern void neigh_table_init(struct neigh_table *tbl);
extern int neigh_table_clear(struct neigh_table *tbl);
extern struct neighbour * neigh_lookup(struct neigh_table *tbl,
          const void *pkey,
          struct net_device *dev);
extern struct neighbour * neigh_lookup_nodev(struct neigh_table *tbl,
         const void *pkey);
extern struct neighbour * neigh_create(struct neigh_table *tbl,
          const void *pkey,
          struct net_device *dev);
extern void neigh_destroy(struct neighbour *neigh);
extern int __neigh_event_send(struct neighbour *neigh, struct sk_buff *skb);
extern int neigh_update(struct neighbour *neigh, const u8 *lladdr, u8 new,
          u32 flags);
extern void neigh_changeaddr(struct neigh_table *tbl, struct net_device *dev);
extern int neigh_ifdown(struct neigh_table *tbl, struct net_device *dev);
extern int neigh_resolve_output(struct sk_buff *skb);
extern int neigh_connected_output(struct sk_buff *skb);
extern int neigh_compat_output(struct sk_buff *skb);
extern struct neighbour *neigh_event_ns(struct neigh_table *tbl,
      u8 *lladdr, void *saddr,
      struct net_device *dev);

extern struct neigh_parms *neigh_parms_alloc(struct net_device *dev, struct neigh_table *tbl);
extern void neigh_parms_release(struct neigh_table *tbl, struct neigh_parms *parms);
extern void neigh_parms_destroy(struct neigh_parms *parms);
extern unsigned long neigh_rand_reach_time(unsigned long base);

extern void pneigh_enqueue(struct neigh_table *tbl, struct neigh_parms *p,
            struct sk_buff *skb);
extern struct pneigh_entry *pneigh_lookup(struct neigh_table *tbl, const void *key, struct net_device *dev, int creat);
extern int pneigh_delete(struct neigh_table *tbl, const void *key, struct net_device *dev);

struct netlink_callback;
struct nlmsghdr;
extern int neigh_dump_info(struct sk_buff *skb, struct netlink_callback *cb);
extern int neigh_add(struct sk_buff *skb, struct nlmsghdr *nlh, void *arg);
extern int neigh_delete(struct sk_buff *skb, struct nlmsghdr *nlh, void *arg);
extern void neigh_app_ns(struct neighbour *n);

extern int neightbl_dump_info(struct sk_buff *skb, struct netlink_callback *cb);
extern int neightbl_set(struct sk_buff *skb, struct nlmsghdr *nlh, void *arg);

extern void neigh_for_each(struct neigh_table *tbl, void (*cb)(struct neighbour *, void *), void *cookie);
extern void __neigh_for_each_release(struct neigh_table *tbl, int (*cb)(struct neighbour *));
extern void pneigh_for_each(struct neigh_table *tbl, void (*cb)(struct pneigh_entry *));

struct neigh_seq_state {
 struct neigh_table *tbl;
 void *(*neigh_sub_iter)(struct neigh_seq_state *state,
    struct neighbour *n, loff_t *pos);
 unsigned int bucket;
 unsigned int flags;



};
extern void *neigh_seq_start(struct seq_file *, loff_t *, struct neigh_table *, unsigned int);
extern void *neigh_seq_next(struct seq_file *, void *, loff_t *);
extern void neigh_seq_stop(struct seq_file *, void *);

extern int neigh_sysctl_register(struct net_device *dev,
            struct neigh_parms *p,
            int p_id, int pdev_id,
            char *p_name,
            proc_handler *proc_handler,
            ctl_handler *strategy);
extern void neigh_sysctl_unregister(struct neigh_parms *p);

static inline __attribute__((always_inline)) void __neigh_parms_put(struct neigh_parms *parms)
{
 atomic_dec(&parms->refcnt);
}

static inline __attribute__((always_inline)) void neigh_parms_put(struct neigh_parms *parms)
{
 if (atomic_dec_and_test(&parms->refcnt))
  neigh_parms_destroy(parms);
}

static inline __attribute__((always_inline)) struct neigh_parms *neigh_parms_clone(struct neigh_parms *parms)
{
 atomic_inc(&parms->refcnt);
 return parms;
}





static inline __attribute__((always_inline)) void neigh_release(struct neighbour *neigh)
{
 if (atomic_dec_and_test(&neigh->refcnt))
  neigh_destroy(neigh);
}

static inline __attribute__((always_inline)) struct neighbour * neigh_clone(struct neighbour *neigh)
{
 if (neigh)
  atomic_inc(&neigh->refcnt);
 return neigh;
}



static inline __attribute__((always_inline)) void neigh_confirm(struct neighbour *neigh)
{
 if (neigh)
  neigh->confirmed = jiffies;
}

static inline __attribute__((always_inline)) int neigh_is_connected(struct neighbour *neigh)
{
 return neigh->nud_state&(0x80|0x40|0x02);
}

static inline __attribute__((always_inline)) int neigh_is_valid(struct neighbour *neigh)
{
 return neigh->nud_state&(0x80|0x40|0x02|0x10|0x04|0x08);
}

static inline __attribute__((always_inline)) int neigh_event_send(struct neighbour *neigh, struct sk_buff *skb)
{
 neigh->used = jiffies;
 if (!(neigh->nud_state&((0x80|0x40|0x02)|0x08|0x10)))
  return __neigh_event_send(neigh, skb);
 return 0;
}

static inline __attribute__((always_inline)) struct neighbour *
__neigh_lookup(struct neigh_table *tbl, const void *pkey, struct net_device *dev, int creat)
{
 struct neighbour *n = neigh_lookup(tbl, pkey, dev);

 if (n || !creat)
  return n;

 n = neigh_create(tbl, pkey, dev);
 return IS_ERR(n) ? ((void *)0) : n;
}

static inline __attribute__((always_inline)) struct neighbour *
__neigh_lookup_errno(struct neigh_table *tbl, const void *pkey,
  struct net_device *dev)
{
 struct neighbour *n = neigh_lookup(tbl, pkey, dev);

 if (n)
  return n;

 return neigh_create(tbl, pkey, dev);
}
# 16 "include/net/dst.h" 2
# 36 "include/net/dst.h"
struct sk_buff;

struct dst_entry
{
 struct dst_entry *next;
 atomic_t __refcnt;
 int __use;
 struct dst_entry *child;
 struct net_device *dev;
 short error;
 short obsolete;
 int flags;





 unsigned long lastuse;
 unsigned long expires;

 unsigned short header_len;
 unsigned short trailer_len;

 u32 metrics[(__RTAX_MAX - 1)];
 struct dst_entry *path;

 unsigned long rate_last;
 unsigned long rate_tokens;

 struct neighbour *neighbour;
 struct hh_cache *hh;
 struct xfrm_state *xfrm;

 int (*input)(struct sk_buff*);
 int (*output)(struct sk_buff*);


 __u32 tclassid;


 struct dst_ops *ops;
 struct rcu_head rcu_head;

 char info[0];
};


struct dst_ops
{
 unsigned short family;
 unsigned short protocol;
 unsigned gc_thresh;

 int (*gc)(void);
 struct dst_entry * (*check)(struct dst_entry *, __u32 cookie);
 void (*destroy)(struct dst_entry *);
 void (*ifdown)(struct dst_entry *,
       struct net_device *dev, int how);
 struct dst_entry * (*negative_advice)(struct dst_entry *);
 void (*link_failure)(struct sk_buff *);
 void (*update_pmtu)(struct dst_entry *dst, u32 mtu);
 int (*get_mss)(struct dst_entry *dst, u32 mtu);
 int entry_size;

 atomic_t entries;
 kmem_cache_t *kmem_cachep;
};



static inline __attribute__((always_inline)) u32
dst_metric(const struct dst_entry *dst, int metric)
{
 return dst->metrics[metric-1];
}

static inline __attribute__((always_inline)) u32 dst_mtu(const struct dst_entry *dst)
{
 u32 mtu = dst_metric(dst, RTAX_MTU);



 __asm__ __volatile__("": : :"memory");
 return mtu;
}

static inline __attribute__((always_inline)) u32
dst_allfrag(const struct dst_entry *dst)
{
 int ret = dst_metric(dst, RTAX_FEATURES) & 0x00000008;

 __asm__ __volatile__("": : :"memory");
 return ret;
}

static inline __attribute__((always_inline)) int
dst_metric_locked(struct dst_entry *dst, int metric)
{
 return dst_metric(dst, RTAX_LOCK) & (1<<metric);
}

static inline __attribute__((always_inline)) void dst_hold(struct dst_entry * dst)
{
 atomic_inc(&dst->__refcnt);
}

static inline __attribute__((always_inline))
struct dst_entry * dst_clone(struct dst_entry * dst)
{
 if (dst)
  atomic_inc(&dst->__refcnt);
 return dst;
}

static inline __attribute__((always_inline))
void dst_release(struct dst_entry * dst)
{
 if (dst) {
  do { if (__builtin_expect(!!((((&dst->__refcnt)->counter) < 1)!=0), 0)) { printk("Badness in %s at %s:%d\n", (__func__), "include/net/dst.h", 154); dump_stack(); } } while (0);
  __asm__ __volatile__("": : :"memory");
  atomic_dec(&dst->__refcnt);
 }
}





static inline __attribute__((always_inline)) struct dst_entry *dst_pop(struct dst_entry *dst)
{
 struct dst_entry *child = dst_clone(dst->child);

 dst_release(dst);
 return child;
}

extern void * dst_alloc(struct dst_ops * ops);
extern void __dst_free(struct dst_entry * dst);
extern struct dst_entry *dst_destroy(struct dst_entry * dst);

static inline __attribute__((always_inline)) void dst_free(struct dst_entry * dst)
{
 if (dst->obsolete > 1)
  return;
 if (!((&dst->__refcnt)->counter)) {
  dst = dst_destroy(dst);
  if (!dst)
   return;
 }
 __dst_free(dst);
}

static inline __attribute__((always_inline)) void dst_rcu_free(struct rcu_head *head)
{
 struct dst_entry *dst = ({ const typeof( ((struct dst_entry *)0)->rcu_head ) *__mptr = (head); (struct dst_entry *)( (char *)__mptr - __builtin_offsetof(struct dst_entry,rcu_head) );});
 dst_free(dst);
}

static inline __attribute__((always_inline)) void dst_confirm(struct dst_entry *dst)
{
 if (dst)
  neigh_confirm(dst->neighbour);
}

static inline __attribute__((always_inline)) void dst_negative_advice(struct dst_entry **dst_p)
{
 struct dst_entry * dst = *dst_p;
 if (dst && dst->ops->negative_advice)
  *dst_p = dst->ops->negative_advice(dst);
}

static inline __attribute__((always_inline)) void dst_link_failure(struct sk_buff *skb)
{
 struct dst_entry * dst = skb->dst;
 if (dst && dst->ops && dst->ops->link_failure)
  dst->ops->link_failure(skb);
}

static inline __attribute__((always_inline)) void dst_set_expires(struct dst_entry *dst, int timeout)
{
 unsigned long expires = jiffies + timeout;

 if (expires == 0)
  expires = 1;

 if (dst->expires == 0 || (({ unsigned long __dummy; typeof(dst->expires) __dummy2; (void)(&__dummy == &__dummy2); 1; }) && ({ unsigned long __dummy; typeof(expires) __dummy2; (void)(&__dummy == &__dummy2); 1; }) && ((long)(expires) - (long)(dst->expires) < 0)))
  dst->expires = expires;
}


static inline __attribute__((always_inline)) int dst_output(struct sk_buff *skb)
{
 int err;

 for (;;) {
  err = skb->dst->output(skb);

  if (__builtin_expect(!!(err == 0), 1))
   return err;
  if (__builtin_expect(!!(err != 4), 0))
   return err;
 }
}


static inline __attribute__((always_inline)) int dst_input(struct sk_buff *skb)
{
 int err;

 for (;;) {
  err = skb->dst->input(skb);

  if (__builtin_expect(!!(err == 0), 1))
   return err;

  if (__builtin_expect(!!(err != 4), 0))
   return err;
 }
}

static inline __attribute__((always_inline)) struct dst_entry *dst_check(struct dst_entry *dst, u32 cookie)
{
 if (dst->obsolete)
  dst = dst->ops->check(dst, cookie);
 return dst;
}

extern void dst_init(void);

struct flowi;







extern int xfrm_lookup(struct dst_entry **dst_p, struct flowi *fl,
         struct sock *sk, int flags);
# 56 "include/net/sock.h" 2
# 77 "include/net/sock.h"
struct sock_iocb;
typedef struct {
 spinlock_t slock;
 struct sock_iocb *owner;
 wait_queue_head_t wq;
} socket_lock_t;







struct sock;
# 105 "include/net/sock.h"
struct sock_common {
 unsigned short skc_family;
 volatile unsigned char skc_state;
 unsigned char skc_reuse;
 int skc_bound_dev_if;
 struct hlist_node skc_node;
 struct hlist_node skc_bind_node;
 atomic_t skc_refcnt;
};
# 174 "include/net/sock.h"
struct sock {




 struct sock_common __sk_common;







 unsigned char sk_shutdown : 2,
    sk_no_check : 2,
    sk_userlocks : 4;
 unsigned char sk_protocol;
 unsigned short sk_type;
 int sk_rcvbuf;
 socket_lock_t sk_lock;
 wait_queue_head_t *sk_sleep;
 struct dst_entry *sk_dst_cache;
 struct xfrm_policy *sk_policy[2];
 rwlock_t sk_dst_lock;
 atomic_t sk_rmem_alloc;
 atomic_t sk_wmem_alloc;
 atomic_t sk_omem_alloc;
 struct sk_buff_head sk_receive_queue;
 struct sk_buff_head sk_write_queue;
 int sk_wmem_queued;
 int sk_forward_alloc;
 unsigned int sk_allocation;
 int sk_sndbuf;
 int sk_route_caps;
 int sk_hashent;
 unsigned long sk_flags;
 unsigned long sk_lingertime;





 struct {
  struct sk_buff *head;
  struct sk_buff *tail;
 } sk_backlog;
 struct sk_buff_head sk_error_queue;
 struct proto *sk_prot;
 struct proto *sk_prot_creator;
 rwlock_t sk_callback_lock;
 int sk_err,
    sk_err_soft;
 unsigned short sk_ack_backlog;
 unsigned short sk_max_ack_backlog;
 __u32 sk_priority;
 struct ucred sk_peercred;
 int sk_rcvlowat;
 long sk_rcvtimeo;
 long sk_sndtimeo;
 struct sk_filter *sk_filter;
 void *sk_protinfo;
 struct timer_list sk_timer;
 struct timeval sk_stamp;
 struct socket *sk_socket;
 void *sk_user_data;
 struct page *sk_sndmsg_page;
 struct sk_buff *sk_send_head;
 __u32 sk_sndmsg_off;
 int sk_write_pending;
 void *sk_security;
 void (*sk_state_change)(struct sock *sk);
 void (*sk_data_ready)(struct sock *sk, int bytes);
 void (*sk_write_space)(struct sock *sk);
 void (*sk_error_report)(struct sock *sk);
   int (*sk_backlog_rcv)(struct sock *sk,
        struct sk_buff *skb);
 void (*sk_destruct)(struct sock *sk);
};




static inline __attribute__((always_inline)) struct sock *__sk_head(struct hlist_head *head)
{
 return ({ const typeof( ((struct sock *)0)->__sk_common.skc_node ) *__mptr = (head->first); (struct sock *)( (char *)__mptr - __builtin_offsetof(struct sock,__sk_common.skc_node) );});
}

static inline __attribute__((always_inline)) struct sock *sk_head(struct hlist_head *head)
{
 return hlist_empty(head) ? ((void *)0) : __sk_head(head);
}

static inline __attribute__((always_inline)) struct sock *sk_next(struct sock *sk)
{
 return sk->__sk_common.skc_node.next ?
  ({ const typeof( ((struct sock *)0)->__sk_common.skc_node ) *__mptr = (sk->__sk_common.skc_node.next); (struct sock *)( (char *)__mptr - __builtin_offsetof(struct sock,__sk_common.skc_node) );}) : ((void *)0);
}

static inline __attribute__((always_inline)) int sk_unhashed(struct sock *sk)
{
 return hlist_unhashed(&sk->__sk_common.skc_node);
}

static inline __attribute__((always_inline)) int sk_hashed(struct sock *sk)
{
 return sk->__sk_common.skc_node.pprev != ((void *)0);
}

static __inline__ __attribute__((always_inline)) void sk_node_init(struct hlist_node *node)
{
 node->pprev = ((void *)0);
}

static __inline__ __attribute__((always_inline)) void __sk_del_node(struct sock *sk)
{
 __hlist_del(&sk->__sk_common.skc_node);
}

static __inline__ __attribute__((always_inline)) int __sk_del_node_init(struct sock *sk)
{
 if (sk_hashed(sk)) {
  __sk_del_node(sk);
  sk_node_init(&sk->__sk_common.skc_node);
  return 1;
 }
 return 0;
}







static inline __attribute__((always_inline)) void sock_hold(struct sock *sk)
{
 atomic_inc(&sk->__sk_common.skc_refcnt);
}




static inline __attribute__((always_inline)) void __sock_put(struct sock *sk)
{
 atomic_dec(&sk->__sk_common.skc_refcnt);
}

static __inline__ __attribute__((always_inline)) int sk_del_node_init(struct sock *sk)
{
 int rc = __sk_del_node_init(sk);

 if (rc) {

  do { if (__builtin_expect(!!((((&sk->__sk_common.skc_refcnt)->counter) == 1)!=0), 0)) { printk("Badness in %s at %s:%d\n", (__func__), "include/net/sock.h", 327); dump_stack(); } } while (0);
  __sock_put(sk);
 }
 return rc;
}

static __inline__ __attribute__((always_inline)) void __sk_add_node(struct sock *sk, struct hlist_head *list)
{
 hlist_add_head(&sk->__sk_common.skc_node, list);
}

static __inline__ __attribute__((always_inline)) void sk_add_node(struct sock *sk, struct hlist_head *list)
{
 sock_hold(sk);
 __sk_add_node(sk, list);
}

static __inline__ __attribute__((always_inline)) void __sk_del_bind_node(struct sock *sk)
{
 __hlist_del(&sk->__sk_common.skc_bind_node);
}

static __inline__ __attribute__((always_inline)) void sk_add_bind_node(struct sock *sk,
     struct hlist_head *list)
{
 hlist_add_head(&sk->__sk_common.skc_bind_node, list);
}
# 369 "include/net/sock.h"
enum sock_flags {
 SOCK_DEAD,
 SOCK_DONE,
 SOCK_URGINLINE,
 SOCK_KEEPOPEN,
 SOCK_LINGER,
 SOCK_DESTROY,
 SOCK_BROADCAST,
 SOCK_TIMESTAMP,
 SOCK_ZAPPED,
 SOCK_USE_WRITE_QUEUE,
 SOCK_DBG,
 SOCK_RCVTSTAMP,
 SOCK_NO_LARGESEND,
 SOCK_LOCALROUTE,
 SOCK_QUEUE_SHRUNK,
};

static inline __attribute__((always_inline)) void sock_copy_flags(struct sock *nsk, struct sock *osk)
{
 nsk->sk_flags = osk->sk_flags;
}

static inline __attribute__((always_inline)) void sock_set_flag(struct sock *sk, enum sock_flags flag)
{
 __set_bit(flag, &sk->sk_flags);
}

static inline __attribute__((always_inline)) void sock_reset_flag(struct sock *sk, enum sock_flags flag)
{
 __clear_bit(flag, &sk->sk_flags);
}

static inline __attribute__((always_inline)) int sock_flag(struct sock *sk, enum sock_flags flag)
{
 return (__builtin_constant_p(flag) ? constant_test_bit((flag),(&sk->sk_flags)) : variable_test_bit((flag),(&sk->sk_flags)));
}

static inline __attribute__((always_inline)) void sk_acceptq_removed(struct sock *sk)
{
 sk->sk_ack_backlog--;
}

static inline __attribute__((always_inline)) void sk_acceptq_added(struct sock *sk)
{
 sk->sk_ack_backlog++;
}

static inline __attribute__((always_inline)) int sk_acceptq_is_full(struct sock *sk)
{
 return sk->sk_ack_backlog > sk->sk_max_ack_backlog;
}




static inline __attribute__((always_inline)) int sk_stream_min_wspace(struct sock *sk)
{
 return sk->sk_wmem_queued / 2;
}

static inline __attribute__((always_inline)) int sk_stream_wspace(struct sock *sk)
{
 return sk->sk_sndbuf - sk->sk_wmem_queued;
}

extern void sk_stream_write_space(struct sock *sk);

static inline __attribute__((always_inline)) int sk_stream_memory_free(struct sock *sk)
{
 return sk->sk_wmem_queued < sk->sk_sndbuf;
}

extern void sk_stream_rfree(struct sk_buff *skb);

static inline __attribute__((always_inline)) void sk_stream_set_owner_r(struct sk_buff *skb, struct sock *sk)
{
 skb->sk = sk;
 skb->destructor = sk_stream_rfree;
 atomic_add(skb->truesize, &sk->sk_rmem_alloc);
 sk->sk_forward_alloc -= skb->truesize;
}

static inline __attribute__((always_inline)) void sk_stream_free_skb(struct sock *sk, struct sk_buff *skb)
{
 sock_set_flag(sk, SOCK_QUEUE_SHRUNK);
 sk->sk_wmem_queued -= skb->truesize;
 sk->sk_forward_alloc += skb->truesize;
 __kfree_skb(skb);
}
# 484 "include/net/sock.h"
extern int sk_stream_wait_connect(struct sock *sk, long *timeo_p);
extern int sk_stream_wait_memory(struct sock *sk, long *timeo_p);
extern void sk_stream_wait_close(struct sock *sk, long timeo_p);
extern int sk_stream_error(struct sock *sk, int flags, int err);
extern void sk_stream_kill_queues(struct sock *sk);

extern int sk_wait_data(struct sock *sk, long *timeo);

struct request_sock_ops;





struct proto {
 void (*close)(struct sock *sk,
     long timeout);
 int (*connect)(struct sock *sk,
            struct sockaddr *uaddr,
     int addr_len);
 int (*disconnect)(struct sock *sk, int flags);

 struct sock * (*accept) (struct sock *sk, int flags, int *err);

 int (*ioctl)(struct sock *sk, int cmd,
      unsigned long arg);
 int (*init)(struct sock *sk);
 int (*destroy)(struct sock *sk);
 void (*shutdown)(struct sock *sk, int how);
 int (*setsockopt)(struct sock *sk, int level,
     int optname, char *optval,
     int optlen);
 int (*getsockopt)(struct sock *sk, int level,
     int optname, char *optval,
     int *option);
 int (*sendmsg)(struct kiocb *iocb, struct sock *sk,
        struct msghdr *msg, size_t len);
 int (*recvmsg)(struct kiocb *iocb, struct sock *sk,
        struct msghdr *msg,
     size_t len, int noblock, int flags,
     int *addr_len);
 int (*sendpage)(struct sock *sk, struct page *page,
     int offset, size_t size, int flags);
 int (*bind)(struct sock *sk,
     struct sockaddr *uaddr, int addr_len);

 int (*backlog_rcv) (struct sock *sk,
      struct sk_buff *skb);


 void (*hash)(struct sock *sk);
 void (*unhash)(struct sock *sk);
 int (*get_port)(struct sock *sk, unsigned short snum);


 void (*enter_memory_pressure)(void);
 atomic_t *memory_allocated;
 atomic_t *sockets_allocated;






 int *memory_pressure;
 int *sysctl_mem;
 int *sysctl_wmem;
 int *sysctl_rmem;
 int max_header;

 kmem_cache_t *slab;
 unsigned int obj_size;

 struct request_sock_ops *rsk_prot;

 struct module *owner;

 char name[32];

 struct list_head node;

 struct {
  int inuse;
  u8 __pad[(1 << (7)) - sizeof(int)];
 } stats[8];
};

extern int proto_register(struct proto *prot, int alloc_slab);
extern void proto_unregister(struct proto *prot);


static __inline__ __attribute__((always_inline)) void sock_prot_inc_use(struct proto *prot)
{
 prot->stats[(current_thread_info()->cpu)].inuse++;
}

static __inline__ __attribute__((always_inline)) void sock_prot_dec_use(struct proto *prot)
{
 prot->stats[(current_thread_info()->cpu)].inuse--;
}
# 601 "include/net/sock.h"
struct sock_iocb {
 struct list_head list;

 int flags;
 int size;
 struct socket *sock;
 struct sock *sk;
 struct scm_cookie *scm;
 struct msghdr *msg, async_msg;
 struct iovec async_iov;
 struct kiocb *kiocb;
};

static inline __attribute__((always_inline)) struct sock_iocb *kiocb_to_siocb(struct kiocb *iocb)
{
 return (struct sock_iocb *)iocb->private;
}

static inline __attribute__((always_inline)) struct kiocb *siocb_to_kiocb(struct sock_iocb *si)
{
 return si->kiocb;
}

struct socket_alloc {
 struct socket socket;
 struct inode vfs_inode;
};

static inline __attribute__((always_inline)) struct socket *SOCKET_I(struct inode *inode)
{
 return &({ const typeof( ((struct socket_alloc *)0)->vfs_inode ) *__mptr = (inode); (struct socket_alloc *)( (char *)__mptr - __builtin_offsetof(struct socket_alloc,vfs_inode) );})->socket;
}

static inline __attribute__((always_inline)) struct inode *SOCK_INODE(struct socket *socket)
{
 return &({ const typeof( ((struct socket_alloc *)0)->socket ) *__mptr = (socket); (struct socket_alloc *)( (char *)__mptr - __builtin_offsetof(struct socket_alloc,socket) );})->vfs_inode;
}

extern void __sk_stream_mem_reclaim(struct sock *sk);
extern int sk_stream_mem_schedule(struct sock *sk, int size, int kind);



static inline __attribute__((always_inline)) int sk_stream_pages(int amt)
{
 return (amt + ((int)(1UL << 12)) - 1) / ((int)(1UL << 12));
}

static inline __attribute__((always_inline)) void sk_stream_mem_reclaim(struct sock *sk)
{
 if (sk->sk_forward_alloc >= ((int)(1UL << 12)))
  __sk_stream_mem_reclaim(sk);
}

static inline __attribute__((always_inline)) void sk_stream_writequeue_purge(struct sock *sk)
{
 struct sk_buff *skb;

 while ((skb = __skb_dequeue(&sk->sk_write_queue)) != ((void *)0))
  sk_stream_free_skb(sk, skb);
 sk_stream_mem_reclaim(sk);
}

static inline __attribute__((always_inline)) int sk_stream_rmem_schedule(struct sock *sk, struct sk_buff *skb)
{
 return (int)skb->truesize <= sk->sk_forward_alloc ||
  sk_stream_mem_schedule(sk, skb->truesize, 1);
}
# 685 "include/net/sock.h"
extern void lock_sock(struct sock *sk) __attribute__((regparm(3)));
extern void release_sock(struct sock *sk) __attribute__((regparm(3)));





extern struct sock *sk_alloc(int family,
       unsigned int priority,
       struct proto *prot, int zero_it);
extern void sk_free(struct sock *sk);

extern struct sk_buff *sock_wmalloc(struct sock *sk,
           unsigned long size, int force,
           unsigned int priority);
extern struct sk_buff *sock_rmalloc(struct sock *sk,
           unsigned long size, int force,
           unsigned int priority);
extern void sock_wfree(struct sk_buff *skb);
extern void sock_rfree(struct sk_buff *skb);

extern int sock_setsockopt(struct socket *sock, int level,
      int op, char *optval,
      int optlen);

extern int sock_getsockopt(struct socket *sock, int level,
      int op, char *optval,
      int *optlen);
extern struct sk_buff *sock_alloc_send_skb(struct sock *sk,
           unsigned long size,
           int noblock,
           int *errcode);
extern void *sock_kmalloc(struct sock *sk, int size,
     unsigned int priority);
extern void sock_kfree_s(struct sock *sk, void *mem, int size);
extern void sk_send_sigurg(struct sock *sk);





extern int sock_no_bind(struct socket *,
          struct sockaddr *, int);
extern int sock_no_connect(struct socket *,
      struct sockaddr *, int, int);
extern int sock_no_socketpair(struct socket *,
         struct socket *);
extern int sock_no_accept(struct socket *,
            struct socket *, int);
extern int sock_no_getname(struct socket *,
      struct sockaddr *, int *, int);
extern unsigned int sock_no_poll(struct file *, struct socket *,
          struct poll_table_struct *);
extern int sock_no_ioctl(struct socket *, unsigned int,
           unsigned long);
extern int sock_no_listen(struct socket *, int);
extern int sock_no_shutdown(struct socket *, int);
extern int sock_no_getsockopt(struct socket *, int , int,
         char *, int *);
extern int sock_no_setsockopt(struct socket *, int, int,
         char *, int);
extern int sock_no_sendmsg(struct kiocb *, struct socket *,
      struct msghdr *, size_t);
extern int sock_no_recvmsg(struct kiocb *, struct socket *,
      struct msghdr *, size_t, int);
extern int sock_no_mmap(struct file *file,
          struct socket *sock,
          struct vm_area_struct *vma);
extern ssize_t sock_no_sendpage(struct socket *sock,
      struct page *page,
      int offset, size_t size,
      int flags);





extern int sock_common_getsockopt(struct socket *sock, int level, int optname,
      char *optval, int *optlen);
extern int sock_common_recvmsg(struct kiocb *iocb, struct socket *sock,
          struct msghdr *msg, size_t size, int flags);
extern int sock_common_setsockopt(struct socket *sock, int level, int optname,
      char *optval, int optlen);

extern void sk_common_release(struct sock *sk);






extern void sock_init_data(struct socket *sock, struct sock *sk);
# 792 "include/net/sock.h"
static inline __attribute__((always_inline)) int sk_filter(struct sock *sk, struct sk_buff *skb, int needlock)
{
 int err;

 err = security_sock_rcv_skb(sk, skb);
 if (err)
  return err;

 if (sk->sk_filter) {
  struct sk_filter *filter;

  if (needlock)
   _spin_lock(&((sk)->sk_lock.slock));

  filter = sk->sk_filter;
  if (filter) {
   int pkt_len = sk_run_filter(skb, filter->insns,
          filter->len);
   if (!pkt_len)
    err = -1;
   else
    skb_trim(skb, pkt_len);
  }

  if (needlock)
   _spin_unlock(&((sk)->sk_lock.slock));
 }
 return err;
}
# 830 "include/net/sock.h"
static inline __attribute__((always_inline)) void sk_filter_release(struct sock *sk, struct sk_filter *fp)
{
 unsigned int size = sk_filter_len(fp);

 atomic_sub(size, &sk->sk_omem_alloc);

 if (atomic_dec_and_test(&fp->refcnt))
  kfree(fp);
}

static inline __attribute__((always_inline)) void sk_filter_charge(struct sock *sk, struct sk_filter *fp)
{
 atomic_inc(&fp->refcnt);
 atomic_add(sk_filter_len(fp), &sk->sk_omem_alloc);
}
# 872 "include/net/sock.h"
static inline __attribute__((always_inline)) void sock_put(struct sock *sk)
{
 if (atomic_dec_and_test(&sk->__sk_common.skc_refcnt))
  sk_free(sk);
}
# 885 "include/net/sock.h"
static inline __attribute__((always_inline)) void sock_orphan(struct sock *sk)
{
 _write_lock_bh(&sk->sk_callback_lock);
 sock_set_flag(sk, SOCK_DEAD);
 sk->sk_socket = ((void *)0);
 sk->sk_sleep = ((void *)0);
 _write_unlock_bh(&sk->sk_callback_lock);
}

static inline __attribute__((always_inline)) void sock_graft(struct sock *sk, struct socket *parent)
{
 _write_lock_bh(&sk->sk_callback_lock);
 sk->sk_sleep = &parent->wait;
 parent->sk = sk;
 sk->sk_socket = parent;
 _write_unlock_bh(&sk->sk_callback_lock);
}

extern int sock_i_uid(struct sock *sk);
extern unsigned long sock_i_ino(struct sock *sk);

static inline __attribute__((always_inline)) struct dst_entry *
__sk_dst_get(struct sock *sk)
{
 return sk->sk_dst_cache;
}

static inline __attribute__((always_inline)) struct dst_entry *
sk_dst_get(struct sock *sk)
{
 struct dst_entry *dst;

 _read_lock(&sk->sk_dst_lock);
 dst = sk->sk_dst_cache;
 if (dst)
  dst_hold(dst);
 _read_unlock(&sk->sk_dst_lock);
 return dst;
}

static inline __attribute__((always_inline)) void
__sk_dst_set(struct sock *sk, struct dst_entry *dst)
{
 struct dst_entry *old_dst;

 old_dst = sk->sk_dst_cache;
 sk->sk_dst_cache = dst;
 dst_release(old_dst);
}

static inline __attribute__((always_inline)) void
sk_dst_set(struct sock *sk, struct dst_entry *dst)
{
 _write_lock(&sk->sk_dst_lock);
 __sk_dst_set(sk, dst);
 _write_unlock(&sk->sk_dst_lock);
}

static inline __attribute__((always_inline)) void
__sk_dst_reset(struct sock *sk)
{
 struct dst_entry *old_dst;

 old_dst = sk->sk_dst_cache;
 sk->sk_dst_cache = ((void *)0);
 dst_release(old_dst);
}

static inline __attribute__((always_inline)) void
sk_dst_reset(struct sock *sk)
{
 _write_lock(&sk->sk_dst_lock);
 __sk_dst_reset(sk);
 _write_unlock(&sk->sk_dst_lock);
}

static inline __attribute__((always_inline)) struct dst_entry *
__sk_dst_check(struct sock *sk, u32 cookie)
{
 struct dst_entry *dst = sk->sk_dst_cache;

 if (dst && dst->obsolete && dst->ops->check(dst, cookie) == ((void *)0)) {
  sk->sk_dst_cache = ((void *)0);
  dst_release(dst);
  return ((void *)0);
 }

 return dst;
}

static inline __attribute__((always_inline)) struct dst_entry *
sk_dst_check(struct sock *sk, u32 cookie)
{
 struct dst_entry *dst = sk_dst_get(sk);

 if (dst && dst->obsolete && dst->ops->check(dst, cookie) == ((void *)0)) {
  sk_dst_reset(sk);
  dst_release(dst);
  return ((void *)0);
 }

 return dst;
}

static inline __attribute__((always_inline)) void sk_charge_skb(struct sock *sk, struct sk_buff *skb)
{
 sk->sk_wmem_queued += skb->truesize;
 sk->sk_forward_alloc -= skb->truesize;
}

static inline __attribute__((always_inline)) int skb_copy_to_page(struct sock *sk, char *from,
       struct sk_buff *skb, struct page *page,
       int off, int copy)
{
 if (skb->ip_summed == 0) {
  int err = 0;
  unsigned int csum = csum_and_copy_from_user(from,
           lowmem_page_address(page) + off,
           copy, 0, &err);
  if (err)
   return err;
  skb->csum = csum_block_add(skb->csum, csum, skb->len);
 } else if (copy_from_user(lowmem_page_address(page) + off, from, copy))
  return -14;

 skb->len += copy;
 skb->data_len += copy;
 skb->truesize += copy;
 sk->sk_wmem_queued += copy;
 sk->sk_forward_alloc -= copy;
 return 0;
}
# 1027 "include/net/sock.h"
static inline __attribute__((always_inline)) void skb_set_owner_w(struct sk_buff *skb, struct sock *sk)
{
 sock_hold(sk);
 skb->sk = sk;
 skb->destructor = sock_wfree;
 atomic_add(skb->truesize, &sk->sk_wmem_alloc);
}

static inline __attribute__((always_inline)) void skb_set_owner_r(struct sk_buff *skb, struct sock *sk)
{
 skb->sk = sk;
 skb->destructor = sock_rfree;
 atomic_add(skb->truesize, &sk->sk_rmem_alloc);
}

extern void sk_reset_timer(struct sock *sk, struct timer_list* timer,
      unsigned long expires);

extern void sk_stop_timer(struct sock *sk, struct timer_list* timer);

static inline __attribute__((always_inline)) int sock_queue_rcv_skb(struct sock *sk, struct sk_buff *skb)
{
 int err = 0;
 int skb_len;




 if (((&sk->sk_rmem_alloc)->counter) + skb->truesize >=
     (unsigned)sk->sk_rcvbuf) {
  err = -12;
  goto out;
 }





 err = sk_filter(sk, skb, 1);
 if (err)
  goto out;

 skb->dev = ((void *)0);
 skb_set_owner_r(skb, sk);






 skb_len = skb->len;

 skb_queue_tail(&sk->sk_receive_queue, skb);

 if (!sock_flag(sk, SOCK_DEAD))
  sk->sk_data_ready(sk, skb_len);
out:
 return err;
}

static inline __attribute__((always_inline)) int sock_queue_err_skb(struct sock *sk, struct sk_buff *skb)
{



 if (((&sk->sk_rmem_alloc)->counter) + skb->truesize >=
     (unsigned)sk->sk_rcvbuf)
  return -12;
 skb_set_owner_r(skb, sk);
 skb_queue_tail(&sk->sk_error_queue, skb);
 if (!sock_flag(sk, SOCK_DEAD))
  sk->sk_data_ready(sk, skb->len);
 return 0;
}





static inline __attribute__((always_inline)) int sock_error(struct sock *sk)
{
 int err = ((__typeof__(*(&sk->sk_err)))__xchg((unsigned long)(0),(&sk->sk_err),sizeof(*(&sk->sk_err))));
 return -err;
}

static inline __attribute__((always_inline)) unsigned long sock_wspace(struct sock *sk)
{
 int amt = 0;

 if (!(sk->sk_shutdown & 2)) {
  amt = sk->sk_sndbuf - ((&sk->sk_wmem_alloc)->counter);
  if (amt < 0)
   amt = 0;
 }
 return amt;
}

static inline __attribute__((always_inline)) void sk_wake_async(struct sock *sk, int how, int band)
{
 if (sk->sk_socket && sk->sk_socket->fasync_list)
  sock_wake_async(sk->sk_socket, how, band);
}




static inline __attribute__((always_inline)) void sk_stream_moderate_sndbuf(struct sock *sk)
{
 if (!(sk->sk_userlocks & 1)) {
  sk->sk_sndbuf = ({ typeof(sk->sk_sndbuf) _x = (sk->sk_sndbuf); typeof(sk->sk_wmem_queued / 2) _y = (sk->sk_wmem_queued / 2); (void) (&_x == &_y); _x < _y ? _x : _y; });
  sk->sk_sndbuf = ({ typeof(sk->sk_sndbuf) _x = (sk->sk_sndbuf); typeof(2048) _y = (2048); (void) (&_x == &_y); _x > _y ? _x : _y; });
 }
}

static inline __attribute__((always_inline)) struct sk_buff *sk_stream_alloc_pskb(struct sock *sk,
         int size, int mem,
         unsigned int gfp)
{
 struct sk_buff *skb;
 int hdr_len;

 hdr_len = (((sk->sk_prot->max_header) + ((1 << (7)) - 1)) & ~((1 << (7)) - 1));
 skb = alloc_skb(size + hdr_len, gfp);
 if (skb) {
  skb->truesize += mem;
  if (sk->sk_forward_alloc >= (int)skb->truesize ||
      sk_stream_mem_schedule(sk, skb->truesize, 0)) {
   skb_reserve(skb, hdr_len);
   return skb;
  }
  __kfree_skb(skb);
 } else {
  sk->sk_prot->enter_memory_pressure();
  sk_stream_moderate_sndbuf(sk);
 }
 return ((void *)0);
}

static inline __attribute__((always_inline)) struct sk_buff *sk_stream_alloc_skb(struct sock *sk,
        int size,
        unsigned int gfp)
{
 return sk_stream_alloc_pskb(sk, size, 0, gfp);
}

static inline __attribute__((always_inline)) struct page *sk_stream_alloc_page(struct sock *sk)
{
 struct page *page = ((void *)0);

 if (sk->sk_forward_alloc >= (int)(1UL << 12) ||
     sk_stream_mem_schedule(sk, (1UL << 12), 0))
  page = alloc_pages_node(((0)), sk->sk_allocation, 0);
 else {
  sk->sk_prot->enter_memory_pressure();
  sk_stream_moderate_sndbuf(sk);
 }
 return page;
}
# 1195 "include/net/sock.h"
static inline __attribute__((always_inline)) int sock_writeable(const struct sock *sk)
{
 return ((&sk->sk_wmem_alloc)->counter) < (sk->sk_sndbuf / 2);
}

static inline __attribute__((always_inline)) unsigned int gfp_any(void)
{
 return (((current_thread_info()->preempt_count) & (((1UL << (8))-1) << (0 + 8)))) ? (0x20u) : (0x10u | 0x40u | 0x80u);
}

static inline __attribute__((always_inline)) long sock_rcvtimeo(const struct sock *sk, int noblock)
{
 return noblock ? 0 : sk->sk_rcvtimeo;
}

static inline __attribute__((always_inline)) long sock_sndtimeo(const struct sock *sk, int noblock)
{
 return noblock ? 0 : sk->sk_sndtimeo;
}

static inline __attribute__((always_inline)) int sock_rcvlowat(const struct sock *sk, int waitall, int len)
{
 return (waitall ? len : ({ int __x = (sk->sk_rcvlowat); int __y = (len); __x < __y ? __x: __y; })) ? : 1;
}




static inline __attribute__((always_inline)) int sock_intr_errno(long timeo)
{
 return timeo == ((long)(~0UL>>1)) ? -512 : -4;
}

static __inline__ __attribute__((always_inline)) void
sock_recv_timestamp(struct msghdr *msg, struct sock *sk, struct sk_buff *skb)
{
 struct timeval *stamp = &skb->stamp;
 if (sock_flag(sk, SOCK_RCVTSTAMP)) {


  if (stamp->tv_sec == 0)
   do_gettimeofday(stamp);
  put_cmsg(msg, 1, 29, sizeof(struct timeval),
    stamp);
 } else
  sk->sk_stamp = *stamp;
}
# 1251 "include/net/sock.h"
static inline __attribute__((always_inline)) void sk_eat_skb(struct sock *sk, struct sk_buff *skb)
{
 __skb_unlink(skb, &sk->sk_receive_queue);
 __kfree_skb(skb);
}

extern void sock_enable_timestamp(struct sock *sk);
extern int sock_get_timestamp(struct sock *, struct timeval *);
# 1296 "include/net/sock.h"
static inline __attribute__((always_inline)) void sock_valbool_flag(struct sock *sk, int bit, int valbool)
{
 if (valbool)
  sock_set_flag(sk, bit);
 else
  sock_reset_flag(sk, bit);
}

extern __u32 sysctl_wmem_max;
extern __u32 sysctl_rmem_max;


int siocdevprivate_ioctl(unsigned int fd, unsigned int cmd, unsigned long arg);
# 23 "include/net/request_sock.h" 2

struct request_sock;
struct sk_buff;
struct dst_entry;
struct proto;

struct request_sock_ops {
 int family;
 kmem_cache_t *slab;
 int obj_size;
 int (*rtx_syn_ack)(struct sock *sk,
           struct request_sock *req,
           struct dst_entry *dst);
 void (*send_ack)(struct sk_buff *skb,
        struct request_sock *req);
 void (*send_reset)(struct sk_buff *skb);
 void (*destructor)(struct request_sock *req);
};



struct request_sock {
 struct request_sock *dl_next;
 u16 mss;
 u8 retrans;
 u8 __pad;

 u32 window_clamp;
 u32 rcv_wnd;
 u32 ts_recent;
 unsigned long expires;
 struct request_sock_ops *rsk_ops;
 struct sock *sk;
};

static inline __attribute__((always_inline)) struct request_sock *reqsk_alloc(struct request_sock_ops *ops)
{
 struct request_sock *req = kmem_cache_alloc(ops->slab, (0x20u));

 if (req != ((void *)0))
  req->rsk_ops = ops;

 return req;
}

static inline __attribute__((always_inline)) void __reqsk_free(struct request_sock *req)
{
 kmem_cache_free(req->rsk_ops->slab, req);
}

static inline __attribute__((always_inline)) void reqsk_free(struct request_sock *req)
{
 req->rsk_ops->destructor(req);
 __reqsk_free(req);
}

extern int sysctl_max_syn_backlog;





struct listen_sock {
 u8 max_qlen_log;

 int qlen;
 int qlen_young;
 int clock_hand;
 u32 hash_rnd;
 struct request_sock *syn_table[0];
};
# 110 "include/net/request_sock.h"
struct request_sock_queue {
 struct request_sock *rskq_accept_head;
 struct request_sock *rskq_accept_tail;
 rwlock_t syn_wait_lock;
 struct listen_sock *listen_opt;
};

extern int reqsk_queue_alloc(struct request_sock_queue *queue,
        const int nr_table_entries);

static inline __attribute__((always_inline)) struct listen_sock *reqsk_queue_yank_listen_sk(struct request_sock_queue *queue)
{
 struct listen_sock *lopt;

 _write_lock_bh(&queue->syn_wait_lock);
 lopt = queue->listen_opt;
 queue->listen_opt = ((void *)0);
 _write_unlock_bh(&queue->syn_wait_lock);

 return lopt;
}

static inline __attribute__((always_inline)) void reqsk_queue_destroy(struct request_sock_queue *queue)
{
 kfree(reqsk_queue_yank_listen_sk(queue));
}

static inline __attribute__((always_inline)) struct request_sock *
 reqsk_queue_yank_acceptq(struct request_sock_queue *queue)
{
 struct request_sock *req = queue->rskq_accept_head;

 queue->rskq_accept_head = queue->rskq_accept_head = ((void *)0);
 return req;
}

static inline __attribute__((always_inline)) int reqsk_queue_empty(struct request_sock_queue *queue)
{
 return queue->rskq_accept_head == ((void *)0);
}

static inline __attribute__((always_inline)) void reqsk_queue_unlink(struct request_sock_queue *queue,
          struct request_sock *req,
          struct request_sock **prev_req)
{
 _write_lock(&queue->syn_wait_lock);
 *prev_req = req->dl_next;
 _write_unlock(&queue->syn_wait_lock);
}

static inline __attribute__((always_inline)) void reqsk_queue_add(struct request_sock_queue *queue,
       struct request_sock *req,
       struct sock *parent,
       struct sock *child)
{
 req->sk = child;
 sk_acceptq_added(parent);

 if (queue->rskq_accept_head == ((void *)0))
  queue->rskq_accept_head = req;
 else
  queue->rskq_accept_tail->dl_next = req;

 queue->rskq_accept_tail = req;
 req->dl_next = ((void *)0);
}

static inline __attribute__((always_inline)) struct request_sock *reqsk_queue_remove(struct request_sock_queue *queue)
{
 struct request_sock *req = queue->rskq_accept_head;

 do { if (__builtin_expect(!!(!(req != ((void *)0))), 0)) { printk("<3>" "KERNEL: assertion (%s) failed at %s (%d)\n", "req != NULL", "include/net/request_sock.h" , 181); } } while(0);

 queue->rskq_accept_head = req->dl_next;
 if (queue->rskq_accept_head == ((void *)0))
  queue->rskq_accept_tail = ((void *)0);

 return req;
}

static inline __attribute__((always_inline)) struct sock *reqsk_queue_get_child(struct request_sock_queue *queue,
       struct sock *parent)
{
 struct request_sock *req = reqsk_queue_remove(queue);
 struct sock *child = req->sk;

 do { if (__builtin_expect(!!(!(child != ((void *)0))), 0)) { printk("<3>" "KERNEL: assertion (%s) failed at %s (%d)\n", "child != NULL", "include/net/request_sock.h" , 196); } } while(0);

 sk_acceptq_removed(parent);
 __reqsk_free(req);
 return child;
}

static inline __attribute__((always_inline)) int reqsk_queue_removed(struct request_sock_queue *queue,
          struct request_sock *req)
{
 struct listen_sock *lopt = queue->listen_opt;

 if (req->retrans == 0)
  --lopt->qlen_young;

 return --lopt->qlen;
}

static inline __attribute__((always_inline)) int reqsk_queue_added(struct request_sock_queue *queue)
{
 struct listen_sock *lopt = queue->listen_opt;
 const int prev_qlen = lopt->qlen;

 lopt->qlen_young++;
 lopt->qlen++;
 return prev_qlen;
}

static inline __attribute__((always_inline)) int reqsk_queue_len(struct request_sock_queue *queue)
{
 return queue->listen_opt != ((void *)0) ? queue->listen_opt->qlen : 0;
}

static inline __attribute__((always_inline)) int reqsk_queue_len_young(struct request_sock_queue *queue)
{
 return queue->listen_opt->qlen_young;
}

static inline __attribute__((always_inline)) int reqsk_queue_is_full(struct request_sock_queue *queue)
{
 return queue->listen_opt->qlen >> queue->listen_opt->max_qlen_log;
}

static inline __attribute__((always_inline)) void reqsk_queue_hash_req(struct request_sock_queue *queue,
     u32 hash, struct request_sock *req,
     unsigned timeout)
{
 struct listen_sock *lopt = queue->listen_opt;

 req->expires = jiffies + timeout;
 req->retrans = 0;
 req->sk = ((void *)0);
 req->dl_next = lopt->syn_table[hash];

 _write_lock(&queue->syn_wait_lock);
 lopt->syn_table[hash] = req;
 _write_unlock(&queue->syn_wait_lock);
}
# 85 "include/linux/ip.h" 2

# 1 "include/linux/igmp.h" 1
# 29 "include/linux/igmp.h"
struct igmphdr
{
 __u8 type;
 __u8 code;
 __u16 csum;
 __u32 group;
};
# 45 "include/linux/igmp.h"
struct igmpv3_grec {
 __u8 grec_type;
 __u8 grec_auxwords;
 __u16 grec_nsrcs;
 __u32 grec_mca;
 __u32 grec_src[0];
};

struct igmpv3_report {
 __u8 type;
 __u8 resv1;
 __u16 csum;
 __u16 resv2;
 __u16 ngrec;
 struct igmpv3_grec grec[0];
};

struct igmpv3_query {
 __u8 type;
 __u8 code;
 __u16 csum;
 __u32 group;

 __u8 qrv:3,
      suppress:1,
      resv:4;







 __u8 qqic;
 __u16 nsrcs;
 __u32 srcs[0];
};
# 132 "include/linux/igmp.h"
struct ip_sf_socklist
{
 unsigned int sl_max;
 unsigned int sl_count;
 __u32 sl_addr[0];
};
# 148 "include/linux/igmp.h"
struct ip_mc_socklist
{
 struct ip_mc_socklist *next;
 struct ip_mreqn multi;
 unsigned int sfmode;
 struct ip_sf_socklist *sflist;
};

struct ip_sf_list
{
 struct ip_sf_list *sf_next;
 __u32 sf_inaddr;
 unsigned long sf_count[2];
 unsigned char sf_gsresp;
 unsigned char sf_oldin;
 unsigned char sf_crcount;
};

struct ip_mc_list
{
 struct in_device *interface;
 unsigned long multiaddr;
 struct ip_sf_list *sources;
 struct ip_sf_list *tomb;
 unsigned int sfmode;
 unsigned long sfcount[2];
 struct ip_mc_list *next;
 struct timer_list timer;
 int users;
 atomic_t refcnt;
 spinlock_t lock;
 char tm_running;
 char reporter;
 char unsolicit_count;
 char loaded;
 unsigned char gsquery;
 unsigned char crcount;
};
# 197 "include/linux/igmp.h"
extern int ip_check_mc(struct in_device *dev, u32 mc_addr, u32 src_addr, u16 proto);
extern int igmp_rcv(struct sk_buff *);
extern int ip_mc_join_group(struct sock *sk, struct ip_mreqn *imr);
extern int ip_mc_leave_group(struct sock *sk, struct ip_mreqn *imr);
extern void ip_mc_drop_socket(struct sock *sk);
extern int ip_mc_source(int add, int omode, struct sock *sk,
  struct ip_mreq_source *mreqs, int ifindex);
extern int ip_mc_msfilter(struct sock *sk, struct ip_msfilter *msf,int ifindex);
extern int ip_mc_msfget(struct sock *sk, struct ip_msfilter *msf,
  struct ip_msfilter *optval, int *optlen);
extern int ip_mc_gsfget(struct sock *sk, struct group_filter *gsf,
  struct group_filter *optval, int *optlen);
extern int ip_mc_sf_allow(struct sock *sk, u32 local, u32 rmt, int dif);
extern void ip_mr_init(void);
extern void ip_mc_init_dev(struct in_device *);
extern void ip_mc_destroy_dev(struct in_device *);
extern void ip_mc_up(struct in_device *);
extern void ip_mc_down(struct in_device *);
extern void ip_mc_dec_group(struct in_device *in_dev, u32 addr);
extern void ip_mc_inc_group(struct in_device *in_dev, u32 addr);
# 87 "include/linux/ip.h" 2
# 1 "include/net/flow.h" 1
# 13 "include/net/flow.h"
struct flowi {
 int oif;
 int iif;

 union {
  struct {
   __u32 daddr;
   __u32 saddr;
   __u32 fwmark;
   __u8 tos;
   __u8 scope;
  } ip4_u;

  struct {
   struct in6_addr daddr;
   struct in6_addr saddr;
   __u32 flowlabel;
  } ip6_u;

  struct {
   __u16 daddr;
   __u16 saddr;
   __u32 fwmark;
   __u8 scope;
  } dn_u;
 } nl_u;
# 52 "include/net/flow.h"
 __u8 proto;
 __u8 flags;

 union {
  struct {
   __u16 sport;
   __u16 dport;
  } ports;

  struct {
   __u8 type;
   __u8 code;
  } icmpt;

  struct {
   __u16 sport;
   __u16 dport;
   __u8 objnum;
   __u8 objnamel;
   __u8 objname[16];
  } dnports;

  __u32 spi;
 } uli_u;





} __attribute__((__aligned__(32/8)));





typedef void (*flow_resolve_t)(struct flowi *key, u16 family, u8 dir,
          void **objp, atomic_t **obj_refp);

extern void *flow_cache_lookup(struct flowi *key, u16 family, u8 dir,
          flow_resolve_t resolver);
extern void flow_cache_flush(void);
extern atomic_t flow_cache_genid;
# 88 "include/linux/ip.h" 2

struct ip_options {
  __u32 faddr;
  unsigned char optlen;
  unsigned char srr;
  unsigned char rr;
  unsigned char ts;
  unsigned char is_setbyuser:1,
                is_data:1,
                is_strictroute:1,
                srr_is_hit:1,
                is_changed:1,
                rr_needaddr:1,
                ts_needtime:1,
                ts_needaddr:1;
  unsigned char router_alert;
  unsigned char __pad1;
  unsigned char __pad2;
  unsigned char __data[0];
};



struct inet_request_sock {
 struct request_sock req;
 u32 loc_addr;
 u32 rmt_addr;
 u16 rmt_port;
 u16 snd_wscale : 4,
    rcv_wscale : 4,
    tstamp_ok : 1,
    sack_ok : 1,
    wscale_ok : 1,
    ecn_ok : 1,
    acked : 1;
 struct ip_options *opt;
};

static inline __attribute__((always_inline)) struct inet_request_sock *inet_rsk(const struct request_sock *sk)
{
 return (struct inet_request_sock *)sk;
}

struct ipv6_pinfo;

struct inet_sock {

 struct sock sk;

 struct ipv6_pinfo *pinet6;


 __u32 daddr;
 __u32 rcv_saddr;
 __u16 dport;
 __u16 num;
 __u32 saddr;
 __s16 uc_ttl;
 __u16 cmsg_flags;
 struct ip_options *opt;
 __u16 sport;
 __u16 id;
 __u8 tos;
 __u8 mc_ttl;
 __u8 pmtudisc;
 unsigned recverr : 1,
    freebind : 1,
    hdrincl : 1,
    mc_loop : 1;
 int mc_index;
 __u32 mc_addr;
 struct ip_mc_socklist *mc_list;




 struct {
  unsigned int flags;
  unsigned int fragsize;
  struct ip_options *opt;
  struct rtable *rt;
  int length;
  u32 addr;
  struct flowi fl;
 } cork;
};




static inline __attribute__((always_inline)) struct inet_sock *inet_sk(const struct sock *sk)
{
 return (struct inet_sock *)sk;
}

static inline __attribute__((always_inline)) void __inet_sk_copy_descendant(struct sock *sk_to,
          const struct sock *sk_from,
          const int ancestor_size)
{
 __memcpy(inet_sk(sk_to) + 1,inet_sk(sk_from) + 1,sk_from->sk_prot->obj_size - ancestor_size);

}
# 199 "include/linux/ip.h"
struct iphdr {

 __u8 ihl:4,
  version:4;






 __u8 tos;
 __u16 tot_len;
 __u16 id;
 __u16 frag_off;
 __u8 ttl;
 __u8 protocol;
 __u16 check;
 __u32 saddr;
 __u32 daddr;

};

struct ip_auth_hdr {
 __u8 nexthdr;
 __u8 hdrlen;
 __u16 reserved;
 __u32 spi;
 __u32 seq_no;
 __u8 auth_data[0];
};

struct ip_esp_hdr {
 __u32 spi;
 __u32 seq_no;
 __u8 enc_data[0];
};

struct ip_comp_hdr {
 __u8 nexthdr;
 __u8 flags;
 __u16 cpi;
};
# 199 "include/linux/tcp.h" 2



struct tcp_sack_block {
 __u32 start_seq;
 __u32 end_seq;
};

struct tcp_options_received {

 long ts_recent_stamp;
 __u32 ts_recent;
 __u32 rcv_tsval;
 __u32 rcv_tsecr;
 __u16 saw_tstamp : 1,
  tstamp_ok : 1,
  dsack : 1,
  wscale_ok : 1,
  sack_ok : 4,
  snd_wscale : 4,
  rcv_wscale : 4;

 __u8 eff_sacks;
 __u8 num_sacks;
 __u16 user_mss;
 __u16 mss_clamp;
};

struct tcp_request_sock {
 struct inet_request_sock req;
 __u32 rcv_isn;
 __u32 snt_isn;
};

static inline __attribute__((always_inline)) struct tcp_request_sock *tcp_rsk(const struct request_sock *req)
{
 return (struct tcp_request_sock *)req;
}

struct tcp_sock {

 struct inet_sock inet;
 int tcp_header_len;





 __u32 pred_flags;






  __u32 rcv_nxt;
  __u32 snd_nxt;

  __u32 snd_una;
  __u32 snd_sml;
 __u32 rcv_tstamp;
 __u32 lsndtime;
 struct tcp_bind_bucket *bind_hash;

 struct {
  __u8 pending;
  __u8 quick;
  __u8 pingpong;
  __u8 blocked;
  __u32 ato;
  unsigned long timeout;
  __u32 lrcvtime;
  __u16 last_seg_size;
  __u16 rcv_mss;
 } ack;


 struct {
  struct sk_buff_head prequeue;
  struct task_struct *task;
  struct iovec *iov;
  int memory;
  int len;
 } ucopy;

 __u32 snd_wl1;
 __u32 snd_wnd;
 __u32 max_window;
 __u32 pmtu_cookie;
 __u32 mss_cache;
 __u16 xmit_size_goal;
 __u16 ext_header_len;
 __u8 ca_state;
 __u8 retransmits;

 __u16 advmss;
 __u32 window_clamp;
 __u32 rcv_ssthresh;

 __u32 frto_highmark;
 __u8 reordering;
 __u8 frto_counter;

 __u8 unused;
 __u8 defer_accept;


 __u32 srtt;
 __u32 mdev;
 __u32 mdev_max;
 __u32 rttvar;
 __u32 rtt_seq;
 __u32 rto;

 __u32 packets_out;
 __u32 left_out;
 __u32 retrans_out;
 __u8 backoff;



 __u8 nonagle;
 __u8 keepalive_probes;

 __u8 probes_out;
 struct tcp_options_received rx_opt;




  __u32 snd_ssthresh;
  __u32 snd_cwnd;
  __u16 snd_cwnd_cnt;
 __u16 snd_cwnd_clamp;
 __u32 snd_cwnd_used;
 __u32 snd_cwnd_stamp;


 unsigned long timeout;
  struct timer_list retransmit_timer;
  struct timer_list delack_timer;

 struct sk_buff_head out_of_order_queue;

 struct tcp_func *af_specific;

  __u32 rcv_wnd;
 __u32 rcv_wup;
 __u32 write_seq;
 __u32 pushed_seq;
 __u32 copied_seq;


 struct tcp_sack_block duplicate_sack[1];
 struct tcp_sack_block selective_acks[4];

 __u8 syn_retries;
 __u8 ecn_flags;
 __u16 prior_ssthresh;
 __u32 lost_out;
 __u32 sacked_out;
 __u32 fackets_out;
 __u32 high_seq;

 __u32 retrans_stamp;


 __u32 undo_marker;
 int undo_retrans;
 __u32 urg_seq;
 __u16 urg_data;
 __u8 pending;
 __u8 urg_mode;
 __u32 snd_up;

 __u32 total_retrans;

 struct request_sock_queue accept_queue;

 unsigned int keepalive_time;
 unsigned int keepalive_intvl;
 int linger2;

 unsigned long last_synq_overflow;


 struct {
  __u32 rtt;
  __u32 seq;
  __u32 time;
 } rcv_rtt_est;


 struct {
  int space;
  __u32 seq;
  __u32 time;
 } rcvq_space;


 struct tcp_congestion_ops *ca_ops;
 u32 ca_priv[16];

};

static inline __attribute__((always_inline)) struct tcp_sock *tcp_sk(const struct sock *sk)
{
 return (struct tcp_sock *)sk;
}

static inline __attribute__((always_inline)) void *tcp_ca(const struct tcp_sock *tp)
{
 return (void *) tp->ca_priv;
}
# 178 "include/linux/ipv6.h" 2
# 1 "include/linux/udp.h" 1
# 22 "include/linux/udp.h"
struct udphdr {
 __u16 source;
 __u16 dest;
 __u16 len;
 __u16 check;
};
# 43 "include/linux/udp.h"
struct udp_sock {

 struct inet_sock inet;
 int pending;
 unsigned int corkflag;
   __u16 encap_type;




 __u16 len;
};

static inline __attribute__((always_inline)) struct udp_sock *udp_sk(const struct sock *sk)
{
 return (struct udp_sock *)sk;
}
# 179 "include/linux/ipv6.h" 2






struct inet6_skb_parm {
 int iif;
 __u16 ra;
 __u16 hop;
 __u16 dst0;
 __u16 srcrt;
 __u16 dst1;
};



struct tcp6_request_sock {
 struct tcp_request_sock req;
 struct in6_addr loc_addr;
 struct in6_addr rmt_addr;
 struct sk_buff *pktopts;
 int iif;
};

static inline __attribute__((always_inline)) struct tcp6_request_sock *tcp6_rsk(const struct request_sock *sk)
{
 return (struct tcp6_request_sock *)sk;
}
# 217 "include/linux/ipv6.h"
struct ipv6_pinfo {
 struct in6_addr saddr;
 struct in6_addr rcv_saddr;
 struct in6_addr daddr;
 struct in6_addr *daddr_cache;

 __u32 flow_label;
 __u32 frag_size;
 __s16 hop_limit;
 __s16 mcast_hops;
 int mcast_oif;


 union {
  struct {
   __u8 srcrt:2,
           rxinfo:1,
    rxhlim:1,
    hopopts:1,
    dstopts:1,
                                rxflow:1;
  } bits;
  __u8 all;
 } rxopt;


 __u8 mc_loop:1,
                         recverr:1,
                         sndflow:1,
    pmtudisc:2,
    ipv6only:1;

 __u32 dst_cookie;

 struct ipv6_mc_socklist *ipv6_mc_list;
 struct ipv6_ac_socklist *ipv6_ac_list;
 struct ipv6_fl_socklist *ipv6_fl_list;

 struct ipv6_txoptions *opt;
 struct sk_buff *pktoptions;
 struct {
  struct ipv6_txoptions *opt;
  struct rt6_info *rt;
  int hop_limit;
 } cork;
};


struct raw6_sock {

 struct inet_sock inet;
 __u32 checksum;
 __u32 offset;
 struct icmp6_filter filter;

 struct ipv6_pinfo inet6;
};

struct udp6_sock {
 struct udp_sock udp;

 struct ipv6_pinfo inet6;
};

struct tcp6_sock {
 struct tcp_sock tcp;

 struct ipv6_pinfo inet6;
};


static inline __attribute__((always_inline)) struct ipv6_pinfo * inet6_sk(const struct sock *__sk)
{
 return inet_sk(__sk)->pinet6;
}

static inline __attribute__((always_inline)) struct raw6_sock *raw6_sk(const struct sock *sk)
{
 return (struct raw6_sock *)sk;
}

static inline __attribute__((always_inline)) void inet_sk_copy_descendant(struct sock *sk_to,
        const struct sock *sk_from)
{
 int ancestor_size = sizeof(struct inet_sock);

 if (sk_from->__sk_common.skc_family == 10)
  ancestor_size += sizeof(struct ipv6_pinfo);

 __inet_sk_copy_descendant(sk_to, sk_from, ancestor_size);
}
# 45 "net/ipv6/tcp_ipv6.c" 2

# 1 "include/linux/random.h" 1
# 35 "include/linux/random.h"
struct rand_pool_info {
 int entropy_count;
 int buf_size;
 __u32 buf[0];
};





extern void rand_initialize_irq(int irq);

extern void add_input_randomness(unsigned int type, unsigned int code,
     unsigned int value);
extern void add_interrupt_randomness(int irq);

extern void get_random_bytes(void *buf, int nbytes);
void generate_random_uuid(unsigned char uuid_out[16]);

extern __u32 secure_ip_id(__u32 daddr);
extern u32 secure_tcp_port_ephemeral(__u32 saddr, __u32 daddr, __u16 dport);
extern u32 secure_tcpv6_port_ephemeral(const __u32 *saddr, const __u32 *daddr,
           __u16 dport);
extern __u32 secure_tcp_sequence_number(__u32 saddr, __u32 daddr,
     __u16 sport, __u16 dport);
extern __u32 secure_tcpv6_sequence_number(__u32 *saddr, __u32 *daddr,
       __u16 sport, __u16 dport);


extern struct file_operations random_fops, urandom_fops;


unsigned int get_random_int(void);
unsigned long randomize_range(unsigned long start, unsigned long end, unsigned long len);
# 47 "net/ipv6/tcp_ipv6.c" 2

# 1 "include/net/tcp.h" 1
# 37 "include/net/tcp.h"
# 1 "include/net/ip.h" 1
# 31 "include/net/ip.h"
# 1 "include/linux/inetdevice.h" 1
# 11 "include/linux/inetdevice.h"
struct ipv4_devconf
{
 int accept_redirects;
 int send_redirects;
 int secure_redirects;
 int shared_media;
 int accept_source_route;
 int rp_filter;
 int proxy_arp;
 int bootp_relay;
 int log_martians;
 int forwarding;
 int mc_forwarding;
 int tag;
 int arp_filter;
 int arp_announce;
 int arp_ignore;
 int medium_id;
 int no_xfrm;
 int no_policy;
 int force_igmp_version;
 int promote_secondaries;
 void *sysctl;
};

extern struct ipv4_devconf ipv4_devconf;

struct in_device
{
 struct net_device *dev;
 atomic_t refcnt;
 int dead;
 struct in_ifaddr *ifa_list;
 rwlock_t mc_list_lock;
 struct ip_mc_list *mc_list;
 spinlock_t mc_tomb_lock;
 struct ip_mc_list *mc_tomb;
 unsigned long mr_v1_seen;
 unsigned long mr_v2_seen;
 unsigned long mr_maxdelay;
 unsigned char mr_qrv;
 unsigned char mr_gq_running;
 unsigned char mr_ifc_count;
 struct timer_list mr_gq_timer;
 struct timer_list mr_ifc_timer;

 struct neigh_parms *arp_parms;
 struct ipv4_devconf cnf;
 struct rcu_head rcu_head;
};
# 87 "include/linux/inetdevice.h"
struct in_ifaddr
{
 struct in_ifaddr *ifa_next;
 struct in_device *ifa_dev;
 struct rcu_head rcu_head;
 u32 ifa_local;
 u32 ifa_address;
 u32 ifa_mask;
 u32 ifa_broadcast;
 u32 ifa_anycast;
 unsigned char ifa_scope;
 unsigned char ifa_flags;
 unsigned char ifa_prefixlen;
 char ifa_label[16];
};

extern int register_inetaddr_notifier(struct notifier_block *nb);
extern int unregister_inetaddr_notifier(struct notifier_block *nb);

extern struct net_device *ip_dev_find(u32 addr);
extern int inet_addr_onlink(struct in_device *in_dev, u32 a, u32 b);
extern int devinet_ioctl(unsigned int cmd, void *);
extern void devinet_init(void);
extern struct in_device *inetdev_init(struct net_device *dev);
extern struct in_device *inetdev_by_index(int);
extern u32 inet_select_addr(const struct net_device *dev, u32 dst, int scope);
extern u32 inet_confirm_addr(const struct net_device *dev, u32 dst, u32 local, int scope);
extern struct in_ifaddr *inet_ifa_byprefix(struct in_device *in_dev, u32 prefix, u32 mask);
extern void inet_forward_change(void);

static __inline__ __attribute__((always_inline)) int inet_ifa_match(u32 addr, struct in_ifaddr *ifa)
{
 return !((addr^ifa->ifa_address)&ifa->ifa_mask);
}





static __inline__ __attribute__((always_inline)) int bad_mask(u32 mask, u32 addr)
{
 if (addr & (mask = ~mask))
  return 1;
 mask = (__builtin_constant_p((__u32)(( __u32)(__be32)(mask))) ? ({ __u32 __x = ((( __u32)(__be32)(mask))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(mask))));
 if (mask & (mask+1))
  return 1;
 return 0;
}
# 145 "include/linux/inetdevice.h"
static __inline__ __attribute__((always_inline)) struct in_device *
in_dev_get(const struct net_device *dev)
{
 struct in_device *in_dev;

 do { } while (0);
 in_dev = dev->ip_ptr;
 if (in_dev)
  atomic_inc(&in_dev->refcnt);
 do { } while (0);
 return in_dev;
}

static __inline__ __attribute__((always_inline)) struct in_device *
__in_dev_get(const struct net_device *dev)
{
 return (struct in_device*)dev->ip_ptr;
}

extern void in_dev_finish_destroy(struct in_device *idev);

static inline __attribute__((always_inline)) void in_dev_put(struct in_device *idev)
{
 if (atomic_dec_and_test(&idev->refcnt))
  in_dev_finish_destroy(idev);
}






static __inline__ __attribute__((always_inline)) __u32 inet_make_mask(int logmask)
{
 if (logmask)
  return (( __be32)(__builtin_constant_p((__u32)((~((1<<(32-logmask))-1)))) ? ({ __u32 __x = (((~((1<<(32-logmask))-1)))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((~((1<<(32-logmask))-1))))));
 return 0;
}

static __inline__ __attribute__((always_inline)) int inet_mask_len(__u32 mask)
{
 if (!(mask = (__builtin_constant_p((__u32)(( __u32)(__be32)(mask))) ? ({ __u32 __x = ((( __u32)(__be32)(mask))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(mask))))))
  return 0;
 return 32 - ffz(~mask);
}
# 32 "include/net/ip.h" 2
# 1 "include/linux/in_route.h" 1
# 33 "include/net/ip.h" 2
# 1 "include/net/route.h" 1
# 29 "include/net/route.h"
# 1 "include/net/inetpeer.h" 1
# 18 "include/net/inetpeer.h"
struct inet_peer
{
 struct inet_peer *avl_left, *avl_right;
 struct inet_peer *unused_next, **unused_prevp;
 unsigned long dtime;

 atomic_t refcnt;
 __u32 v4daddr;
 __u16 avl_height;
 __u16 ip_id_count;
 __u32 tcp_ts;
 unsigned long tcp_ts_stamp;
};

void inet_initpeers(void) __attribute__ ((__section__ (".init.text")));


struct inet_peer *inet_getpeer(__u32 daddr, int create);

extern spinlock_t inet_peer_unused_lock;
extern struct inet_peer **inet_peer_unused_tailp;

static inline __attribute__((always_inline)) void inet_putpeer(struct inet_peer *p)
{
 _spin_lock_bh(&inet_peer_unused_lock);
 if (atomic_dec_and_test(&p->refcnt)) {
  p->unused_prevp = inet_peer_unused_tailp;
  p->unused_next = ((void *)0);
  *inet_peer_unused_tailp = p;
  inet_peer_unused_tailp = &p->unused_next;
  p->dtime = jiffies;
 }
 _spin_unlock_bh(&inet_peer_unused_lock);
}

extern spinlock_t inet_peer_idlock;

static inline __attribute__((always_inline)) __u16 inet_getid(struct inet_peer *p, int more)
{
 __u16 id;

 _spin_lock_bh(&inet_peer_idlock);
 id = p->ip_id_count;
 p->ip_id_count += 1 + more;
 _spin_unlock_bh(&inet_peer_idlock);
 return id;
}
# 30 "include/net/route.h" 2



# 1 "include/linux/route.h" 1
# 30 "include/linux/route.h"
struct rtentry
{
 unsigned long rt_pad1;
 struct sockaddr rt_dst;
 struct sockaddr rt_gateway;
 struct sockaddr rt_genmask;
 unsigned short rt_flags;
 short rt_pad2;
 unsigned long rt_pad3;
 void *rt_pad4;
 short rt_metric;
 char *rt_dev;
 unsigned long rt_mtu;



 unsigned long rt_window;
 unsigned short rt_irtt;
};
# 34 "include/net/route.h" 2
# 49 "include/net/route.h"
struct fib_nh;
struct inet_peer;
struct rtable
{
 union
 {
  struct dst_entry dst;
  struct rtable *rt_next;
 } u;

 struct in_device *idev;

 unsigned rt_flags;
 __u16 rt_type;
 __u16 rt_multipath_alg;

 __u32 rt_dst;
 __u32 rt_src;
 int rt_iif;


 __u32 rt_gateway;


 struct flowi fl;


 __u32 rt_spec_dst;
 struct inet_peer *peer;
};

struct ip_rt_acct
{
 __u32 o_bytes;
 __u32 o_packets;
 __u32 i_bytes;
 __u32 i_packets;
};

struct rt_cache_stat
{
        unsigned int in_hit;
        unsigned int in_slow_tot;
        unsigned int in_slow_mc;
        unsigned int in_no_route;
        unsigned int in_brd;
        unsigned int in_martian_dst;
        unsigned int in_martian_src;
        unsigned int out_hit;
        unsigned int out_slow_tot;
        unsigned int out_slow_mc;
        unsigned int gc_total;
        unsigned int gc_ignored;
        unsigned int gc_goal_miss;
        unsigned int gc_dst_overflow;
        unsigned int in_hlist_search;
        unsigned int out_hlist_search;
};

extern struct rt_cache_stat *rt_cache_stat;



extern struct ip_rt_acct *ip_rt_acct;

struct in_device;
extern int ip_rt_init(void);
extern void ip_rt_redirect(u32 old_gw, u32 dst, u32 new_gw,
           u32 src, u8 tos, struct net_device *dev);
extern void ip_rt_advice(struct rtable **rp, int advice);
extern void rt_cache_flush(int how);
extern int __ip_route_output_key(struct rtable **, const struct flowi *flp);
extern int ip_route_output_key(struct rtable **, struct flowi *flp);
extern int ip_route_output_flow(struct rtable **rp, struct flowi *flp, struct sock *sk, int flags);
extern int ip_route_input(struct sk_buff*, u32 dst, u32 src, u8 tos, struct net_device *devin);
extern unsigned short ip_rt_frag_needed(struct iphdr *iph, unsigned short new_mtu);
extern void ip_rt_send_redirect(struct sk_buff *skb);

extern unsigned inet_addr_type(u32 addr);
extern void ip_rt_multicast_event(struct in_device *);
extern int ip_rt_ioctl(unsigned int cmd, void *arg);
extern void ip_rt_get_source(u8 *src, struct rtable *rt);
extern int ip_rt_dump(struct sk_buff *skb, struct netlink_callback *cb);

static inline __attribute__((always_inline)) void ip_rt_put(struct rtable * rt)
{
 if (rt)
  dst_release(&rt->u.dst);
}



extern __u8 ip_tos2prio[16];

static inline __attribute__((always_inline)) char rt_tos2priority(u8 tos)
{
 return ip_tos2prio[((tos)&0x1E)>>1];
}

static inline __attribute__((always_inline)) int ip_route_connect(struct rtable **rp, u32 dst,
       u32 src, u32 tos, int oif, u8 protocol,
       u16 sport, u16 dport, struct sock *sk)
{
 struct flowi fl = { .oif = oif,
       .nl_u = { .ip4_u = { .daddr = dst,
       .saddr = src,
       .tos = tos } },
       .proto = protocol,
       .uli_u = { .ports =
           { .sport = sport,
      .dport = dport } } };

 int err;
 if (!dst || !src) {
  err = __ip_route_output_key(rp, &fl);
  if (err)
   return err;
  fl.nl_u.ip4_u.daddr = (*rp)->rt_dst;
  fl.nl_u.ip4_u.saddr = (*rp)->rt_src;
  ip_rt_put(*rp);
  *rp = ((void *)0);
 }
 return ip_route_output_flow(rp, &fl, sk, 0);
}

static inline __attribute__((always_inline)) int ip_route_newports(struct rtable **rp, u16 sport, u16 dport,
        struct sock *sk)
{
 if (sport != (*rp)->fl.uli_u.ports.sport ||
     dport != (*rp)->fl.uli_u.ports.dport) {
  struct flowi fl;

  __memcpy(&fl,&(*rp)->fl,sizeof(fl));
  fl.uli_u.ports.sport = sport;
  fl.uli_u.ports.dport = dport;
  ip_rt_put(*rp);
  *rp = ((void *)0);
  return ip_route_output_flow(rp, &fl, sk, 0);
 }
 return 0;
}

extern void rt_bind_peer(struct rtable *rt, int create);

static inline __attribute__((always_inline)) struct inet_peer *rt_get_peer(struct rtable *rt)
{
 if (rt->peer)
  return rt->peer;

 rt_bind_peer(rt, 0);
 return rt->peer;
}
# 34 "include/net/ip.h" 2
# 1 "include/net/arp.h" 1




# 1 "include/linux/if_arp.h" 1
# 102 "include/linux/if_arp.h"
struct arpreq {
  struct sockaddr arp_pa;
  struct sockaddr arp_ha;
  int arp_flags;
  struct sockaddr arp_netmask;
  char arp_dev[16];
};

struct arpreq_old {
  struct sockaddr arp_pa;
  struct sockaddr arp_ha;
  int arp_flags;
  struct sockaddr arp_netmask;
};
# 130 "include/linux/if_arp.h"
struct arphdr
{
 unsigned short ar_hrd;
 unsigned short ar_pro;
 unsigned char ar_hln;
 unsigned char ar_pln;
 unsigned short ar_op;
# 148 "include/linux/if_arp.h"
};
# 6 "include/net/arp.h" 2




extern struct neigh_table arp_tbl;

extern void arp_init(void);
extern int arp_rcv(struct sk_buff *skb, struct net_device *dev,
   struct packet_type *pt);
extern int arp_find(unsigned char *haddr, struct sk_buff *skb);
extern int arp_ioctl(unsigned int cmd, void *arg);
extern void arp_send(int type, int ptype, u32 dest_ip,
    struct net_device *dev, u32 src_ip,
    unsigned char *dest_hw, unsigned char *src_hw, unsigned char *th);
extern int arp_bind_neighbour(struct dst_entry *dst);
extern int arp_mc_map(u32 addr, u8 *haddr, struct net_device *dev, int dir);
extern void arp_ifdown(struct net_device *dev);

extern struct sk_buff *arp_create(int type, int ptype, u32 dest_ip,
      struct net_device *dev, u32 src_ip,
      unsigned char *dest_hw, unsigned char *src_hw,
      unsigned char *target_hw);
extern void arp_xmit(struct sk_buff *skb);

extern struct neigh_ops arp_broken_ops;
# 35 "include/net/ip.h" 2


struct sock;

struct inet_skb_parm
{
 struct ip_options opt;
 unsigned char flags;





};

struct ipcm_cookie
{
 u32 addr;
 int oif;
 struct ip_options *opt;
};



struct ip_ra_chain
{
 struct ip_ra_chain *next;
 struct sock *sk;
 void (*destructor)(struct sock *);
};

extern struct ip_ra_chain *ip_ra_chain;
extern rwlock_t ip_ra_lock;
# 77 "include/net/ip.h"
extern void ip_mc_dropsocket(struct sock *);
extern void ip_mc_dropdevice(struct net_device *dev);
extern int igmp_mc_proc_init(void);





extern int ip_build_and_send_pkt(struct sk_buff *skb, struct sock *sk,
           u32 saddr, u32 daddr,
           struct ip_options *opt);
extern int ip_rcv(struct sk_buff *skb, struct net_device *dev,
          struct packet_type *pt);
extern int ip_local_deliver(struct sk_buff *skb);
extern int ip_mr_input(struct sk_buff *skb);
extern int ip_output(struct sk_buff *skb);
extern int ip_mc_output(struct sk_buff *skb);
extern int ip_fragment(struct sk_buff *skb, int (*out)(struct sk_buff*));
extern int ip_do_nat(struct sk_buff *skb);
extern void ip_send_check(struct iphdr *ip);
extern int ip_queue_xmit(struct sk_buff *skb, int ipfragok);
extern void ip_init(void);
extern int ip_append_data(struct sock *sk,
           int getfrag(void *from, char *to, int offset, int len,
         int odd, struct sk_buff *skb),
    void *from, int len, int protolen,
    struct ipcm_cookie *ipc,
    struct rtable *rt,
    unsigned int flags);
extern int ip_generic_getfrag(void *from, char *to, int offset, int len, int odd, struct sk_buff *skb);
extern ssize_t ip_append_page(struct sock *sk, struct page *page,
    int offset, size_t size, int flags);
extern int ip_push_pending_frames(struct sock *sk);
extern void ip_flush_pending_frames(struct sock *sk);


extern int ip4_datagram_connect(struct sock *sk,
          struct sockaddr *uaddr, int addr_len);
# 123 "include/net/ip.h"
static inline __attribute__((always_inline)) void ip_tr_mc_map(u32 addr, char *buf)
{
 buf[0]=0xC0;
 buf[1]=0x00;
 buf[2]=0x00;
 buf[3]=0x04;
 buf[4]=0x00;
 buf[5]=0x00;
}

struct ip_reply_arg {
 struct kvec iov[1];
 u32 csum;
 int csumoffset;

};

void ip_send_reply(struct sock *sk, struct sk_buff *skb, struct ip_reply_arg *arg,
     unsigned int len);

extern int ip_finish_output(struct sk_buff *skb);

struct ipv4_config
{
 int log_martians;
 int autoconfig;
 int no_pmtu_disc;
};

extern struct ipv4_config ipv4_config;
extern __typeof__(struct ipstats_mib) *ip_statistics[2];



extern __typeof__(struct linux_mib) *net_statistics[2];






extern int sysctl_local_port_range[2];
extern int sysctl_ip_default_ttl;
extern int sysctl_ip_nonlocal_bind;




static inline __attribute__((always_inline))
int ip_decrease_ttl(struct iphdr *iph)
{
 u32 check = iph->check;
 check += (( __be16)(__builtin_constant_p((__u16)((0x0100))) ? ({ __u16 __x = (((0x0100))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((0x0100)))));
 iph->check = check + (check>=0xFFFF);
 return --iph->ttl;
}

static inline __attribute__((always_inline))
int ip_dont_fragment(struct sock *sk, struct dst_entry *dst)
{
 return (inet_sk(sk)->pmtudisc == 2 ||
  (inet_sk(sk)->pmtudisc == 1 &&
   !(dst_metric(dst, RTAX_LOCK)&(1<<RTAX_MTU))));
}

extern void __ip_select_ident(struct iphdr *iph, struct dst_entry *dst, int more);

static inline __attribute__((always_inline)) void ip_select_ident(struct iphdr *iph, struct dst_entry *dst, struct sock *sk)
{
 if (iph->frag_off & (( __be16)(__builtin_constant_p((__u16)((0x4000))) ? ({ __u16 __x = (((0x4000))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((0x4000)))))) {





  iph->id = (sk && inet_sk(sk)->daddr) ?
     (( __be16)(__builtin_constant_p((__u16)((inet_sk(sk)->id++))) ? ({ __u16 __x = (((inet_sk(sk)->id++))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((inet_sk(sk)->id++))))) : 0;
 } else
  __ip_select_ident(iph, dst, 0);
}

static inline __attribute__((always_inline)) void ip_select_ident_more(struct iphdr *iph, struct dst_entry *dst, struct sock *sk, int more)
{
 if (iph->frag_off & (( __be16)(__builtin_constant_p((__u16)((0x4000))) ? ({ __u16 __x = (((0x4000))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((0x4000)))))) {
  if (sk && inet_sk(sk)->daddr) {
   iph->id = (( __be16)(__builtin_constant_p((__u16)((inet_sk(sk)->id))) ? ({ __u16 __x = (((inet_sk(sk)->id))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((inet_sk(sk)->id)))));
   inet_sk(sk)->id += 1 + more;
  } else
   iph->id = 0;
 } else
  __ip_select_ident(iph, dst, more);
}





static inline __attribute__((always_inline)) void ip_eth_mc_map(u32 addr, char *buf)
{
 addr=(__builtin_constant_p((__u32)(( __u32)(__be32)(addr))) ? ({ __u32 __x = ((( __u32)(__be32)(addr))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(addr))));
 buf[0]=0x01;
 buf[1]=0x00;
 buf[2]=0x5e;
 buf[5]=addr&0xFF;
 addr>>=8;
 buf[4]=addr&0xFF;
 addr>>=8;
 buf[3]=addr&0x7F;
}






static inline __attribute__((always_inline)) void ip_ib_mc_map(u32 addr, char *buf)
{
 buf[0] = 0;
 buf[1] = 0xff;
 buf[2] = 0xff;
 buf[3] = 0xff;
 addr = (__builtin_constant_p((__u32)(( __u32)(__be32)(addr))) ? ({ __u32 __x = ((( __u32)(__be32)(addr))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(addr))));
 buf[4] = 0xff;
 buf[5] = 0x12;
 buf[6] = 0x40;
 buf[7] = 0x1b;
 buf[8] = 0;
 buf[9] = 0;
 buf[10] = 0;
 buf[11] = 0;
 buf[12] = 0;
 buf[13] = 0;
 buf[14] = 0;
 buf[15] = 0;
 buf[19] = addr & 0xff;
 addr >>= 8;
 buf[18] = addr & 0xff;
 addr >>= 8;
 buf[17] = addr & 0xff;
 addr >>= 8;
 buf[16] = addr & 0x0f;
}





static __inline__ __attribute__((always_inline)) void inet_reset_saddr(struct sock *sk)
{
 inet_sk(sk)->rcv_saddr = inet_sk(sk)->saddr = 0;

 if (sk->__sk_common.skc_family == 10) {
  struct ipv6_pinfo *np = inet6_sk(sk);

  __memset_generic((&np->saddr),(0),(sizeof(np->saddr)));
  __memset_generic((&np->rcv_saddr),(0),(sizeof(np->rcv_saddr)));
 }

}



extern int ip_call_ra_chain(struct sk_buff *skb);





enum ip_defrag_users
{
 IP_DEFRAG_LOCAL_DELIVER,
 IP_DEFRAG_CALL_RA_CHAIN,
 IP_DEFRAG_CONNTRACK_IN,
 IP_DEFRAG_CONNTRACK_OUT,
 IP_DEFRAG_NAT_OUT,
 IP_DEFRAG_VS_IN,
 IP_DEFRAG_VS_OUT,
 IP_DEFRAG_VS_FWD
};

struct sk_buff *ip_defrag(struct sk_buff *skb, u32 user);
extern int ip_frag_nqueues;
extern atomic_t ip_frag_mem;





extern int ip_forward(struct sk_buff *skb);
extern int ip_net_unreachable(struct sk_buff *skb);





extern void ip_options_build(struct sk_buff *skb, struct ip_options *opt, u32 daddr, struct rtable *rt, int is_frag);
extern int ip_options_echo(struct ip_options *dopt, struct sk_buff *skb);
extern void ip_options_fragment(struct sk_buff *skb);
extern int ip_options_compile(struct ip_options *opt, struct sk_buff *skb);
extern int ip_options_get(struct ip_options **optp, unsigned char *data, int optlen, int user);
extern void ip_options_undo(struct ip_options * opt);
extern void ip_forward_options(struct sk_buff *skb);
extern int ip_options_rcv_srr(struct sk_buff *skb);





extern void ip_cmsg_recv(struct msghdr *msg, struct sk_buff *skb);
extern int ip_cmsg_send(struct msghdr *msg, struct ipcm_cookie *ipc);
extern int ip_setsockopt(struct sock *sk, int level, int optname, char *optval, int optlen);
extern int ip_getsockopt(struct sock *sk, int level, int optname, char *optval, int *optlen);
extern int ip_ra_control(struct sock *sk, unsigned char on, void (*destructor)(struct sock *));

extern int ip_recv_error(struct sock *sk, struct msghdr *msg, int len);
extern void ip_icmp_error(struct sock *sk, struct sk_buff *skb, int err,
         u16 port, u32 info, u8 *payload);
extern void ip_local_error(struct sock *sk, int err, u32 daddr, u16 dport,
          u32 info);




int ipv4_doint_and_flush(ctl_table *ctl, int write,
    struct file* filp, void *buffer,
    size_t *lenp, loff_t *ppos);
int ipv4_doint_and_flush_strategy(ctl_table *table, int *name, int nlen,
      void *oldval, size_t *oldlenp,
      void *newval, size_t newlen,
      void **context);
# 38 "include/net/tcp.h" 2
# 47 "include/net/tcp.h"
struct tcp_ehash_bucket {
 rwlock_t lock;
 struct hlist_head chain;
} __attribute__((__aligned__(8)));
# 86 "include/net/tcp.h"
struct tcp_bind_bucket {
 unsigned short port;
 signed short fastreuse;
 struct hlist_node node;
 struct hlist_head owners;
};



struct tcp_bind_hashbucket {
 spinlock_t lock;
 struct hlist_head chain;
};

static inline __attribute__((always_inline)) struct tcp_bind_bucket *__tb_head(struct tcp_bind_hashbucket *head)
{
 return ({ const typeof( ((struct tcp_bind_bucket *)0)->node ) *__mptr = (head->chain.first); (struct tcp_bind_bucket *)( (char *)__mptr - __builtin_offsetof(struct tcp_bind_bucket,node) );});
}

static inline __attribute__((always_inline)) struct tcp_bind_bucket *tb_head(struct tcp_bind_hashbucket *head)
{
 return hlist_empty(&head->chain) ? ((void *)0) : __tb_head(head);
}

extern struct tcp_hashinfo {
# 119 "include/net/tcp.h"
 struct tcp_ehash_bucket *__tcp_ehash;




 struct tcp_bind_hashbucket *__tcp_bhash;

 int __tcp_bhash_size;
 int __tcp_ehash_size;





 struct hlist_head __tcp_listening_hash[32];







 rwlock_t __tcp_lhash_lock __attribute__((__aligned__((1 << (7)))));
 atomic_t __tcp_lhash_users;
 wait_queue_head_t __tcp_lhash_wait;
 spinlock_t __tcp_portalloc_lock;
} tcp_hashinfo;
# 157 "include/net/tcp.h"
extern kmem_cache_t *tcp_bucket_cachep;
extern struct tcp_bind_bucket *tcp_bucket_create(struct tcp_bind_hashbucket *head,
       unsigned short snum);
extern void tcp_bucket_destroy(struct tcp_bind_bucket *tb);
extern void tcp_bucket_unlock(struct sock *sk);
extern int tcp_port_rover;


static __inline__ __attribute__((always_inline)) int tcp_bhashfn(__u16 lport)
{
 return (lport & ((tcp_hashinfo.__tcp_bhash_size) - 1));
}

extern void tcp_bind_hash(struct sock *sk, struct tcp_bind_bucket *tb,
     unsigned short snum);
# 183 "include/net/tcp.h"
struct tcp_tw_bucket {




 struct sock_common __tw_common;







 volatile unsigned char tw_substate;
 unsigned char tw_rcv_wscale;
 __u16 tw_sport;


 __u32 tw_daddr
  __attribute__((aligned(4)));
 __u32 tw_rcv_saddr;
 __u16 tw_dport;
 __u16 tw_num;

 int tw_hashent;
 int tw_timeout;
 __u32 tw_rcv_nxt;
 __u32 tw_snd_nxt;
 __u32 tw_rcv_wnd;
 __u32 tw_ts_recent;
 long tw_ts_recent_stamp;
 unsigned long tw_ttd;
 struct tcp_bind_bucket *tw_tb;
 struct hlist_node tw_death_node;

 struct in6_addr tw_v6_daddr;
 struct in6_addr tw_v6_rcv_saddr;
 int tw_v6_ipv6only;

};

static __inline__ __attribute__((always_inline)) void tw_add_node(struct tcp_tw_bucket *tw,
       struct hlist_head *list)
{
 hlist_add_head(&tw->__tw_common.skc_node, list);
}

static __inline__ __attribute__((always_inline)) void tw_add_bind_node(struct tcp_tw_bucket *tw,
     struct hlist_head *list)
{
 hlist_add_head(&tw->__tw_common.skc_bind_node, list);
}

static inline __attribute__((always_inline)) int tw_dead_hashed(struct tcp_tw_bucket *tw)
{
 return tw->tw_death_node.pprev != ((void *)0);
}

static __inline__ __attribute__((always_inline)) void tw_dead_node_init(struct tcp_tw_bucket *tw)
{
 tw->tw_death_node.pprev = ((void *)0);
}

static __inline__ __attribute__((always_inline)) void __tw_del_dead_node(struct tcp_tw_bucket *tw)
{
 __hlist_del(&tw->tw_death_node);
 tw_dead_node_init(tw);
}

static __inline__ __attribute__((always_inline)) int tw_del_dead_node(struct tcp_tw_bucket *tw)
{
 if (tw_dead_hashed(tw)) {
  __tw_del_dead_node(tw);
  return 1;
 }
 return 0;
}
# 272 "include/net/tcp.h"
static inline __attribute__((always_inline)) u32 tcp_v4_rcv_saddr(const struct sock *sk)
{
 return __builtin_expect(!!(sk->__sk_common.skc_state != TCP_TIME_WAIT), 1) ?
  inet_sk(sk)->rcv_saddr : ((struct tcp_tw_bucket *)(sk))->tw_rcv_saddr;
}


static inline __attribute__((always_inline)) struct in6_addr *__tcp_v6_rcv_saddr(const struct sock *sk)
{
 return __builtin_expect(!!(sk->__sk_common.skc_state != TCP_TIME_WAIT), 1) ?
  &inet6_sk(sk)->rcv_saddr : &((struct tcp_tw_bucket *)(sk))->tw_v6_rcv_saddr;
}

static inline __attribute__((always_inline)) struct in6_addr *tcp_v6_rcv_saddr(const struct sock *sk)
{
 return sk->__sk_common.skc_family == 10 ? __tcp_v6_rcv_saddr(sk) : ((void *)0);
}



static inline __attribute__((always_inline)) int tcp_v6_ipv6only(const struct sock *sk)
{
 return __builtin_expect(!!(sk->__sk_common.skc_state != TCP_TIME_WAIT), 1) ?
  ((sk)->__sk_common.skc_family == 10 && (inet6_sk(sk)->ipv6only)) : (((struct tcp_tw_bucket *)(sk))->tw_v6_ipv6only);
}







extern kmem_cache_t *tcp_timewait_cachep;

static inline __attribute__((always_inline)) void tcp_tw_put(struct tcp_tw_bucket *tw)
{
 if (atomic_dec_and_test(&tw->__tw_common.skc_refcnt)) {



  kmem_cache_free(tcp_timewait_cachep, tw);
 }
}

extern atomic_t tcp_orphan_count;
extern int tcp_tw_count;
extern void tcp_time_wait(struct sock *sk, int state, int timeo);
extern void tcp_tw_deschedule(struct tcp_tw_bucket *tw);
# 369 "include/net/tcp.h"
static __inline__ __attribute__((always_inline)) int tcp_lhashfn(unsigned short num)
{
 return num & (32 - 1);
}

static __inline__ __attribute__((always_inline)) int tcp_sk_listen_hashfn(struct sock *sk)
{
 return tcp_lhashfn(inet_sk(sk)->num);
}
# 548 "include/net/tcp.h"
extern int sysctl_tcp_timestamps;
extern int sysctl_tcp_window_scaling;
extern int sysctl_tcp_sack;
extern int sysctl_tcp_fin_timeout;
extern int sysctl_tcp_tw_recycle;
extern int sysctl_tcp_keepalive_time;
extern int sysctl_tcp_keepalive_probes;
extern int sysctl_tcp_keepalive_intvl;
extern int sysctl_tcp_syn_retries;
extern int sysctl_tcp_synack_retries;
extern int sysctl_tcp_retries1;
extern int sysctl_tcp_retries2;
extern int sysctl_tcp_orphan_retries;
extern int sysctl_tcp_syncookies;
extern int sysctl_tcp_retrans_collapse;
extern int sysctl_tcp_stdurg;
extern int sysctl_tcp_rfc1337;
extern int sysctl_tcp_abort_on_overflow;
extern int sysctl_tcp_max_orphans;
extern int sysctl_tcp_max_tw_buckets;
extern int sysctl_tcp_fack;
extern int sysctl_tcp_reordering;
extern int sysctl_tcp_ecn;
extern int sysctl_tcp_dsack;
extern int sysctl_tcp_mem[3];
extern int sysctl_tcp_wmem[3];
extern int sysctl_tcp_rmem[3];
extern int sysctl_tcp_app_win;
extern int sysctl_tcp_adv_win_scale;
extern int sysctl_tcp_tw_reuse;
extern int sysctl_tcp_frto;
extern int sysctl_tcp_low_latency;
extern int sysctl_tcp_nometrics_save;
extern int sysctl_tcp_moderate_rcvbuf;
extern int sysctl_tcp_tso_win_divisor;

extern atomic_t tcp_memory_allocated;
extern atomic_t tcp_sockets_allocated;
extern int tcp_memory_pressure;
# 599 "include/net/tcp.h"
struct tcp_func {
 int (*queue_xmit) (struct sk_buff *skb,
        int ipfragok);

 void (*send_check) (struct sock *sk,
        struct tcphdr *th,
        int len,
        struct sk_buff *skb);

 int (*rebuild_header) (struct sock *sk);

 int (*conn_request) (struct sock *sk,
        struct sk_buff *skb);

 struct sock * (*syn_recv_sock) (struct sock *sk,
        struct sk_buff *skb,
        struct request_sock *req,
        struct dst_entry *dst);

 int (*remember_stamp) (struct sock *sk);

 __u16 net_header_len;

 int (*setsockopt) (struct sock *sk,
        int level,
        int optname,
        char *optval,
        int optlen);

 int (*getsockopt) (struct sock *sk,
        int level,
        int optname,
        char *optval,
        int *optlen);


 void (*addr2sockaddr) (struct sock *sk,
        struct sockaddr *);

 int sockaddr_len;
};






static inline __attribute__((always_inline)) int before(__u32 seq1, __u32 seq2)
{
        return (__s32)(seq1-seq2) < 0;
}

static inline __attribute__((always_inline)) int after(__u32 seq1, __u32 seq2)
{
 return (__s32)(seq2-seq1) < 0;
}



static inline __attribute__((always_inline)) int between(__u32 seq1, __u32 seq2, __u32 seq3)
{
 return seq3 - seq2 >= seq1 - seq2;
}


extern struct proto tcp_prot;

extern __typeof__(struct tcp_mib) *tcp_statistics[2];







extern void tcp_put_port(struct sock *sk);
extern void tcp_inherit_port(struct sock *sk, struct sock *child);

extern void tcp_v4_err(struct sk_buff *skb, u32);

extern void tcp_shutdown (struct sock *sk, int how);

extern int tcp_v4_rcv(struct sk_buff *skb);

extern int tcp_v4_remember_stamp(struct sock *sk);

extern int tcp_v4_tw_remember_stamp(struct tcp_tw_bucket *tw);

extern int tcp_sendmsg(struct kiocb *iocb, struct sock *sk,
         struct msghdr *msg, size_t size);
extern ssize_t tcp_sendpage(struct socket *sock, struct page *page, int offset, size_t size, int flags);

extern int tcp_ioctl(struct sock *sk,
       int cmd,
       unsigned long arg);

extern int tcp_rcv_state_process(struct sock *sk,
            struct sk_buff *skb,
            struct tcphdr *th,
            unsigned len);

extern int tcp_rcv_established(struct sock *sk,
          struct sk_buff *skb,
          struct tcphdr *th,
          unsigned len);

extern void tcp_rcv_space_adjust(struct sock *sk);

enum tcp_ack_state_t
{
 TCP_ACK_SCHED = 1,
 TCP_ACK_TIMER = 2,
 TCP_ACK_PUSHED= 4
};

static inline __attribute__((always_inline)) void tcp_schedule_ack(struct tcp_sock *tp)
{
 tp->ack.pending |= TCP_ACK_SCHED;
}

static inline __attribute__((always_inline)) int tcp_ack_scheduled(struct tcp_sock *tp)
{
 return tp->ack.pending&TCP_ACK_SCHED;
}

static __inline__ __attribute__((always_inline)) void tcp_dec_quickack_mode(struct tcp_sock *tp, unsigned int pkts)
{
 if (tp->ack.quick) {
  if (pkts >= tp->ack.quick) {
   tp->ack.quick = 0;


   tp->ack.ato = ((unsigned)(250/25));
  } else
   tp->ack.quick -= pkts;
 }
}

extern void tcp_enter_quickack_mode(struct tcp_sock *tp);

static __inline__ __attribute__((always_inline)) void tcp_delack_init(struct tcp_sock *tp)
{
 __memset_generic((&tp->ack),(0),(sizeof(tp->ack)));
}

static inline __attribute__((always_inline)) void tcp_clear_options(struct tcp_options_received *rx_opt)
{
  rx_opt->tstamp_ok = rx_opt->sack_ok = rx_opt->wscale_ok = rx_opt->snd_wscale = 0;
}

enum tcp_tw_status
{
 TCP_TW_SUCCESS = 0,
 TCP_TW_RST = 1,
 TCP_TW_ACK = 2,
 TCP_TW_SYN = 3
};


extern enum tcp_tw_status tcp_timewait_state_process(struct tcp_tw_bucket *tw,
          struct sk_buff *skb,
          struct tcphdr *th,
          unsigned len);

extern struct sock * tcp_check_req(struct sock *sk,struct sk_buff *skb,
           struct request_sock *req,
           struct request_sock **prev);
extern int tcp_child_process(struct sock *parent,
        struct sock *child,
        struct sk_buff *skb);
extern void tcp_enter_frto(struct sock *sk);
extern void tcp_enter_loss(struct sock *sk, int how);
extern void tcp_clear_retrans(struct tcp_sock *tp);
extern void tcp_update_metrics(struct sock *sk);

extern void tcp_close(struct sock *sk,
       long timeout);
extern struct sock * tcp_accept(struct sock *sk, int flags, int *err);
extern unsigned int tcp_poll(struct file * file, struct socket *sock, struct poll_table_struct *wait);

extern int tcp_getsockopt(struct sock *sk, int level,
            int optname,
            char *optval,
            int *optlen);
extern int tcp_setsockopt(struct sock *sk, int level,
            int optname, char *optval,
            int optlen);
extern void tcp_set_keepalive(struct sock *sk, int val);
extern int tcp_recvmsg(struct kiocb *iocb, struct sock *sk,
         struct msghdr *msg,
         size_t len, int nonblock,
         int flags, int *addr_len);

extern int tcp_listen_start(struct sock *sk);

extern void tcp_parse_options(struct sk_buff *skb,
        struct tcp_options_received *opt_rx,
        int estab);





extern int tcp_v4_rebuild_header(struct sock *sk);

extern int tcp_v4_build_header(struct sock *sk,
          struct sk_buff *skb);

extern void tcp_v4_send_check(struct sock *sk,
        struct tcphdr *th, int len,
        struct sk_buff *skb);

extern int tcp_v4_conn_request(struct sock *sk,
          struct sk_buff *skb);

extern struct sock * tcp_create_openreq_child(struct sock *sk,
        struct request_sock *req,
        struct sk_buff *skb);

extern struct sock * tcp_v4_syn_recv_sock(struct sock *sk,
           struct sk_buff *skb,
           struct request_sock *req,
       struct dst_entry *dst);

extern int tcp_v4_do_rcv(struct sock *sk,
           struct sk_buff *skb);

extern int tcp_v4_connect(struct sock *sk,
            struct sockaddr *uaddr,
            int addr_len);

extern int tcp_connect(struct sock *sk);

extern struct sk_buff * tcp_make_synack(struct sock *sk,
      struct dst_entry *dst,
      struct request_sock *req);

extern int tcp_disconnect(struct sock *sk, int flags);

extern void tcp_unhash(struct sock *sk);

extern int tcp_v4_hash_connecting(struct sock *sk);



extern struct sock *cookie_v4_check(struct sock *sk, struct sk_buff *skb,
        struct ip_options *opt);
extern __u32 cookie_v4_init_sequence(struct sock *sk, struct sk_buff *skb,
         __u16 *mss);



extern void __tcp_push_pending_frames(struct sock *sk, struct tcp_sock *tp,
          unsigned int cur_mss, int nonagle);
extern int tcp_may_send_now(struct sock *sk, struct tcp_sock *tp);
extern int tcp_retransmit_skb(struct sock *, struct sk_buff *);
extern void tcp_xmit_retransmit_queue(struct sock *);
extern void tcp_simple_retransmit(struct sock *);
extern int tcp_trim_head(struct sock *, struct sk_buff *, u32);

extern void tcp_send_probe0(struct sock *);
extern void tcp_send_partial(struct sock *);
extern int tcp_write_wakeup(struct sock *);
extern void tcp_send_fin(struct sock *sk);
extern void tcp_send_active_reset(struct sock *sk,
                                  unsigned int priority);
extern int tcp_send_synack(struct sock *);
extern void tcp_push_one(struct sock *, unsigned int mss_now);
extern void tcp_send_ack(struct sock *sk);
extern void tcp_send_delayed_ack(struct sock *sk);


extern void tcp_cwnd_application_limited(struct sock *sk);


extern void tcp_init_xmit_timers(struct sock *);
extern void tcp_clear_xmit_timers(struct sock *);

extern void tcp_delete_keepalive_timer(struct sock *);
extern void tcp_reset_keepalive_timer(struct sock *, unsigned long);
extern unsigned int tcp_sync_mss(struct sock *sk, u32 pmtu);
extern unsigned int tcp_current_mss(struct sock *sk, int large);


extern const char tcp_timer_bug_msg[];



extern void tcp_get_info(struct sock *, struct tcp_info *);


typedef int (*sk_read_actor_t)(read_descriptor_t *, struct sk_buff *,
    unsigned int, size_t);
extern int tcp_read_sock(struct sock *sk, read_descriptor_t *desc,
    sk_read_actor_t recv_actor);

static inline __attribute__((always_inline)) void tcp_clear_xmit_timer(struct sock *sk, int what)
{
 struct tcp_sock *tp = tcp_sk(sk);

 switch (what) {
 case 1:
 case 3:
  tp->pending = 0;




  break;
 case 2:
  tp->ack.blocked = 0;
  tp->ack.pending = 0;




  break;
 default:

  printk(tcp_timer_bug_msg);

  return;
 };

}




static inline __attribute__((always_inline)) void tcp_reset_xmit_timer(struct sock *sk, int what, unsigned long when)
{
 struct tcp_sock *tp = tcp_sk(sk);

 if (when > ((unsigned)(120*250))) {

  printk("<7>" "reset_xmit_timer sk=%p %d when=0x%lx, caller=%p\n", sk, what, when, ({ void *pc; __asm__("movl $1f,%0\n1:":"=g" (pc)); pc; }));

  when = ((unsigned)(120*250));
 }

 switch (what) {
 case 1:
 case 3:
  tp->pending = what;
  tp->timeout = jiffies+when;
  sk_reset_timer(sk, &tp->retransmit_timer, tp->timeout);
  break;

 case 2:
  tp->ack.pending |= TCP_ACK_TIMER;
  tp->ack.timeout = jiffies+when;
  sk_reset_timer(sk, &tp->delack_timer, tp->ack.timeout);
  break;

 default:

  printk(tcp_timer_bug_msg);

  return;
 };
}
# 969 "include/net/tcp.h"
static inline __attribute__((always_inline)) void tcp_initialize_rcv_mss(struct sock *sk)
{
 struct tcp_sock *tp = tcp_sk(sk);
 unsigned int hint = ({ unsigned int __x = (tp->advmss); unsigned int __y = (tp->mss_cache); __x < __y ? __x: __y; });

 hint = ({ typeof(hint) _x = (hint); typeof(tp->rcv_wnd/2) _y = (tp->rcv_wnd/2); (void) (&_x == &_y); _x < _y ? _x : _y; });
 hint = ({ typeof(hint) _x = (hint); typeof(536U) _y = (536U); (void) (&_x == &_y); _x < _y ? _x : _y; });
 hint = ({ typeof(hint) _x = (hint); typeof(88U) _y = (88U); (void) (&_x == &_y); _x > _y ? _x : _y; });

 tp->ack.rcv_mss = hint;
}

static __inline__ __attribute__((always_inline)) void __tcp_fast_path_on(struct tcp_sock *tp, u32 snd_wnd)
{
 tp->pred_flags = (( __be32)(__builtin_constant_p((__u32)(((tp->tcp_header_len << 26) | (__builtin_constant_p((__u32)(( __u32)(__be32)(TCP_FLAG_ACK))) ? ({ __u32 __x = ((( __u32)(__be32)(TCP_FLAG_ACK))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(TCP_FLAG_ACK)))) | snd_wnd))) ? ({ __u32 __x = ((((tp->tcp_header_len << 26) | (__builtin_constant_p((__u32)(( __u32)(__be32)(TCP_FLAG_ACK))) ? ({ __u32 __x = ((( __u32)(__be32)(TCP_FLAG_ACK))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(TCP_FLAG_ACK)))) | snd_wnd))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((((tp->tcp_header_len << 26) | (__builtin_constant_p((__u32)(( __u32)(__be32)(TCP_FLAG_ACK))) ? ({ __u32 __x = ((( __u32)(__be32)(TCP_FLAG_ACK))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(TCP_FLAG_ACK)))) | snd_wnd)))));


}

static __inline__ __attribute__((always_inline)) void tcp_fast_path_on(struct tcp_sock *tp)
{
 __tcp_fast_path_on(tp, tp->snd_wnd >> tp->rx_opt.snd_wscale);
}

static inline __attribute__((always_inline)) void tcp_fast_path_check(struct sock *sk, struct tcp_sock *tp)
{
 if (skb_queue_empty(&tp->out_of_order_queue) &&
     tp->rcv_wnd &&
     ((&sk->sk_rmem_alloc)->counter) < sk->sk_rcvbuf &&
     !tp->urg_data)
  tcp_fast_path_on(tp);
}





static __inline__ __attribute__((always_inline)) u32 tcp_receive_window(const struct tcp_sock *tp)
{
 s32 win = tp->rcv_wup + tp->rcv_wnd - tp->rcv_nxt;

 if (win < 0)
  win = 0;
 return (u32) win;
}





extern u32 __tcp_select_window(struct sock *sk);
# 1036 "include/net/tcp.h"
struct tcp_skb_cb {
 union {
  struct inet_skb_parm h4;

  struct inet6_skb_parm h6;

 } header;
 __u32 seq;
 __u32 end_seq;
 __u32 when;
 __u8 flags;
# 1060 "include/net/tcp.h"
 __u8 sacked;
# 1073 "include/net/tcp.h"
 __u16 urg_ptr;
 __u32 ack_seq;
};



# 1 "include/net/tcp_ecn.h" 1



# 1 "include/net/inet_ecn.h" 1




# 1 "include/net/dsfield.h" 1
# 15 "include/net/dsfield.h"
static inline __attribute__((always_inline)) __u8 ipv4_get_dsfield(struct iphdr *iph)
{
 return iph->tos;
}


static inline __attribute__((always_inline)) __u8 ipv6_get_dsfield(struct ipv6hdr *ipv6h)
{
 return (__builtin_constant_p((__u16)(( __u16)(__be16)(*(__u16 *) ipv6h))) ? ({ __u16 __x = ((( __u16)(__be16)(*(__u16 *) ipv6h))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16((( __u16)(__be16)(*(__u16 *) ipv6h)))) >> 4;
}


static inline __attribute__((always_inline)) void ipv4_change_dsfield(struct iphdr *iph,__u8 mask,
    __u8 value)
{
        __u32 check = (__builtin_constant_p((__u16)(( __u16)(__be16)(iph->check))) ? ({ __u16 __x = ((( __u16)(__be16)(iph->check))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16((( __u16)(__be16)(iph->check))));
 __u8 dsfield;

 dsfield = (iph->tos & mask) | value;
 check += iph->tos;
 if ((check+1) >> 16) check = (check+1) & 0xffff;
 check -= dsfield;
 check += check >> 16;
 iph->check = (( __be16)(__builtin_constant_p((__u16)((check))) ? ({ __u16 __x = (((check))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((check)))));
 iph->tos = dsfield;
}


static inline __attribute__((always_inline)) void ipv6_change_dsfield(struct ipv6hdr *ipv6h,__u8 mask,
    __u8 value)
{
        __u16 tmp;

 tmp = (__builtin_constant_p((__u16)(( __u16)(__be16)(*(__u16 *) ipv6h))) ? ({ __u16 __x = ((( __u16)(__be16)(*(__u16 *) ipv6h))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16((( __u16)(__be16)(*(__u16 *) ipv6h))));
 tmp = (tmp & ((mask << 4) | 0xf00f)) | (value << 4);
 *(__u16 *) ipv6h = (( __be16)(__builtin_constant_p((__u16)((tmp))) ? ({ __u16 __x = (((tmp))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((tmp)))));
}
# 6 "include/net/inet_ecn.h" 2

enum {
 INET_ECN_NOT_ECT = 0,
 INET_ECN_ECT_1 = 1,
 INET_ECN_ECT_0 = 2,
 INET_ECN_CE = 3,
 INET_ECN_MASK = 3,
};

static inline __attribute__((always_inline)) int INET_ECN_is_ce(__u8 dsfield)
{
 return (dsfield & INET_ECN_MASK) == INET_ECN_CE;
}

static inline __attribute__((always_inline)) int INET_ECN_is_not_ect(__u8 dsfield)
{
 return (dsfield & INET_ECN_MASK) == INET_ECN_NOT_ECT;
}

static inline __attribute__((always_inline)) int INET_ECN_is_capable(__u8 dsfield)
{
 return (dsfield & INET_ECN_ECT_0);
}

static inline __attribute__((always_inline)) __u8 INET_ECN_encapsulate(__u8 outer, __u8 inner)
{
 outer &= ~INET_ECN_MASK;
 outer |= !INET_ECN_is_ce(inner) ? (inner & INET_ECN_MASK) :
       INET_ECN_ECT_0;
 return outer;
}
# 51 "include/net/inet_ecn.h"
static inline __attribute__((always_inline)) void IP_ECN_set_ce(struct iphdr *iph)
{
 u32 check = iph->check;
 u32 ecn = (iph->tos + 1) & INET_ECN_MASK;
# 63 "include/net/inet_ecn.h"
 if (!(ecn & 2))
  return;






 check += (( __be16)(__builtin_constant_p((__u16)((0xFFFB))) ? ({ __u16 __x = (((0xFFFB))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((0xFFFB))))) + (( __be16)(__builtin_constant_p((__u16)((ecn))) ? ({ __u16 __x = (((ecn))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((ecn)))));

 iph->check = check + (check>=0xFFFF);
 iph->tos |= INET_ECN_CE;
}

static inline __attribute__((always_inline)) void IP_ECN_clear(struct iphdr *iph)
{
 iph->tos &= ~INET_ECN_MASK;
}

static inline __attribute__((always_inline)) void ipv4_copy_dscp(struct iphdr *outer, struct iphdr *inner)
{
 u32 dscp = ipv4_get_dsfield(outer) & ~INET_ECN_MASK;
 ipv4_change_dsfield(inner, INET_ECN_MASK, dscp);
}

struct ipv6hdr;

static inline __attribute__((always_inline)) void IP6_ECN_set_ce(struct ipv6hdr *iph)
{
 if (INET_ECN_is_not_ect(ipv6_get_dsfield(iph)))
  return;
 *(u32*)iph |= (( __be32)(__builtin_constant_p((__u32)((INET_ECN_CE << 20))) ? ({ __u32 __x = (((INET_ECN_CE << 20))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((INET_ECN_CE << 20)))));
}

static inline __attribute__((always_inline)) void IP6_ECN_clear(struct ipv6hdr *iph)
{
 *(u32*)iph &= ~(( __be32)(__builtin_constant_p((__u32)((INET_ECN_MASK << 20))) ? ({ __u32 __x = (((INET_ECN_MASK << 20))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((INET_ECN_MASK << 20)))));
}

static inline __attribute__((always_inline)) void ipv6_copy_dscp(struct ipv6hdr *outer, struct ipv6hdr *inner)
{
 u32 dscp = ipv6_get_dsfield(outer) & ~INET_ECN_MASK;
 ipv6_change_dsfield(inner, INET_ECN_MASK, dscp);
}
# 5 "include/net/tcp_ecn.h" 2
# 13 "include/net/tcp_ecn.h"
static inline __attribute__((always_inline)) void TCP_ECN_queue_cwr(struct tcp_sock *tp)
{
 if (tp->ecn_flags&1)
  tp->ecn_flags |= 2;
}




static inline __attribute__((always_inline)) void TCP_ECN_send_synack(struct tcp_sock *tp,
           struct sk_buff *skb)
{
 ((struct tcp_skb_cb *)&((skb)->cb[0]))->flags &= ~0x80;
 if (!(tp->ecn_flags&1))
  ((struct tcp_skb_cb *)&((skb)->cb[0]))->flags &= ~0x40;
}

static inline __attribute__((always_inline)) void TCP_ECN_send_syn(struct sock *sk, struct tcp_sock *tp,
        struct sk_buff *skb)
{
 tp->ecn_flags = 0;
 if (sysctl_tcp_ecn && !(sk->sk_route_caps & 2048)) {
  ((struct tcp_skb_cb *)&((skb)->cb[0]))->flags |= 0x40|0x80;
  tp->ecn_flags = 1;
  sock_set_flag(sk, SOCK_NO_LARGESEND);
 }
}

static __inline__ __attribute__((always_inline)) void
TCP_ECN_make_synack(struct request_sock *req, struct tcphdr *th)
{
 if (inet_rsk(req)->ecn_ok)
  th->ece = 1;
}

static inline __attribute__((always_inline)) void TCP_ECN_send(struct sock *sk, struct tcp_sock *tp,
    struct sk_buff *skb, int tcp_header_len)
{
 if (tp->ecn_flags & 1) {

  if (skb->len != tcp_header_len &&
      !before(((struct tcp_skb_cb *)&((skb)->cb[0]))->seq, tp->snd_nxt)) {
   do { inet_sk(sk)->tos |= INET_ECN_ECT_0; } while (0);
   if (tp->ecn_flags&2) {
    tp->ecn_flags &= ~2;
    skb->h.th->cwr = 1;
   }
  } else {

   do { inet_sk(sk)->tos &= ~INET_ECN_MASK; } while (0);
  }
  if (tp->ecn_flags & 4)
   skb->h.th->ece = 1;
 }
}



static inline __attribute__((always_inline)) void TCP_ECN_accept_cwr(struct tcp_sock *tp, struct sk_buff *skb)
{
 if (skb->h.th->cwr)
  tp->ecn_flags &= ~4;
}

static inline __attribute__((always_inline)) void TCP_ECN_withdraw_cwr(struct tcp_sock *tp)
{
 tp->ecn_flags &= ~4;
}

static inline __attribute__((always_inline)) void TCP_ECN_check_ce(struct tcp_sock *tp, struct sk_buff *skb)
{
 if (tp->ecn_flags&1) {
  if (INET_ECN_is_ce(((struct tcp_skb_cb *)&((skb)->cb[0]))->flags))
   tp->ecn_flags |= 4;



  else if (INET_ECN_is_not_ect((((struct tcp_skb_cb *)&((skb)->cb[0]))->flags)))
   tcp_enter_quickack_mode(tp);
 }
}

static inline __attribute__((always_inline)) void TCP_ECN_rcv_synack(struct tcp_sock *tp, struct tcphdr *th)
{
 if ((tp->ecn_flags&1) && (!th->ece || th->cwr))
  tp->ecn_flags &= ~1;
}

static inline __attribute__((always_inline)) void TCP_ECN_rcv_syn(struct tcp_sock *tp, struct tcphdr *th)
{
 if ((tp->ecn_flags&1) && (!th->ece || !th->cwr))
  tp->ecn_flags &= ~1;
}

static inline __attribute__((always_inline)) int TCP_ECN_rcv_ecn_echo(struct tcp_sock *tp, struct tcphdr *th)
{
 if (th->ece && !th->syn && (tp->ecn_flags&1))
  return 1;
 return 0;
}

static inline __attribute__((always_inline)) void TCP_ECN_openreq_child(struct tcp_sock *tp,
      struct request_sock *req)
{
 tp->ecn_flags = inet_rsk(req)->ecn_ok ? 1 : 0;
}

static __inline__ __attribute__((always_inline)) void
TCP_ECN_create_request(struct request_sock *req, struct tcphdr *th)
{
 if (sysctl_tcp_ecn && th->ece && th->cwr)
  inet_rsk(req)->ecn_ok = 1;
}
# 1080 "include/net/tcp.h" 2




static inline __attribute__((always_inline)) int tcp_skb_pcount(const struct sk_buff *skb)
{
 return ((struct skb_shared_info *)((skb)->end))->tso_segs;
}


static inline __attribute__((always_inline)) int tcp_skb_mss(const struct sk_buff *skb)
{
 return ((struct skb_shared_info *)((skb)->end))->tso_size;
}

static inline __attribute__((always_inline)) void tcp_dec_pcount_approx(__u32 *count,
      const struct sk_buff *skb)
{
 if (*count) {
  *count -= tcp_skb_pcount(skb);
  if ((int)*count < 0)
   *count = 0;
 }
}

static inline __attribute__((always_inline)) void tcp_packets_out_inc(struct sock *sk,
           struct tcp_sock *tp,
           const struct sk_buff *skb)
{
 int orig = tp->packets_out;

 tp->packets_out += tcp_skb_pcount(skb);
 if (!orig)
  tcp_reset_xmit_timer(sk, 1, tp->rto);
}

static inline __attribute__((always_inline)) void tcp_packets_out_dec(struct tcp_sock *tp,
           const struct sk_buff *skb)
{
 tp->packets_out -= tcp_skb_pcount(skb);
}


enum tcp_ca_event {
 CA_EVENT_TX_START,
 CA_EVENT_CWND_RESTART,
 CA_EVENT_COMPLETE_CWR,
 CA_EVENT_FRTO,
 CA_EVENT_LOSS,
 CA_EVENT_FAST_ACK,
 CA_EVENT_SLOW_ACK,
};





struct tcp_congestion_ops {
 struct list_head list;


 void (*init)(struct tcp_sock *tp);

 void (*release)(struct tcp_sock *tp);


 u32 (*ssthresh)(struct tcp_sock *tp);

 u32 (*min_cwnd)(struct tcp_sock *tp);

 void (*cong_avoid)(struct tcp_sock *tp, u32 ack,
      u32 rtt, u32 in_flight, int good_ack);

 void (*rtt_sample)(struct tcp_sock *tp, u32 usrtt);

 void (*set_state)(struct tcp_sock *tp, u8 new_state);

 void (*cwnd_event)(struct tcp_sock *tp, enum tcp_ca_event ev);

 u32 (*undo_cwnd)(struct tcp_sock *tp);

 void (*pkts_acked)(struct tcp_sock *tp, u32 num_acked);

 void (*get_info)(struct tcp_sock *tp, u32 ext, struct sk_buff *skb);

 char name[16];
 struct module *owner;
};

extern int tcp_register_congestion_control(struct tcp_congestion_ops *type);
extern void tcp_unregister_congestion_control(struct tcp_congestion_ops *type);

extern void tcp_init_congestion_control(struct tcp_sock *tp);
extern void tcp_cleanup_congestion_control(struct tcp_sock *tp);
extern int tcp_set_default_congestion_control(const char *name);
extern void tcp_get_default_congestion_control(char *name);
extern int tcp_set_congestion_control(struct tcp_sock *tp, const char *name);

extern struct tcp_congestion_ops tcp_init_congestion_ops;
extern u32 tcp_reno_ssthresh(struct tcp_sock *tp);
extern void tcp_reno_cong_avoid(struct tcp_sock *tp, u32 ack,
    u32 rtt, u32 in_flight, int flag);
extern u32 tcp_reno_min_cwnd(struct tcp_sock *tp);
extern struct tcp_congestion_ops tcp_reno;

static inline __attribute__((always_inline)) void tcp_set_ca_state(struct tcp_sock *tp, u8 ca_state)
{
 if (tp->ca_ops->set_state)
  tp->ca_ops->set_state(tp, ca_state);
 tp->ca_state = ca_state;
}

static inline __attribute__((always_inline)) void tcp_ca_event(struct tcp_sock *tp, enum tcp_ca_event event)
{
 if (tp->ca_ops->cwnd_event)
  tp->ca_ops->cwnd_event(tp, event);
}
# 1212 "include/net/tcp.h"
static __inline__ __attribute__((always_inline)) unsigned int tcp_packets_in_flight(const struct tcp_sock *tp)
{
 return (tp->packets_out - tp->left_out + tp->retrans_out);
}





static inline __attribute__((always_inline)) __u32 tcp_current_ssthresh(struct tcp_sock *tp)
{
 if ((1<<tp->ca_state)&((1<<TCP_CA_CWR)|(1<<TCP_CA_Recovery)))
  return tp->snd_ssthresh;
 else
  return ({ typeof(tp->snd_ssthresh) _x = (tp->snd_ssthresh); typeof(((tp->snd_cwnd >> 1) + (tp->snd_cwnd >> 2))) _y = (((tp->snd_cwnd >> 1) + (tp->snd_cwnd >> 2))); (void) (&_x == &_y); _x > _y ? _x : _y; });


}

static inline __attribute__((always_inline)) void tcp_sync_left_out(struct tcp_sock *tp)
{
 if (tp->rx_opt.sack_ok &&
     (tp->sacked_out >= tp->packets_out - tp->lost_out))
  tp->sacked_out = tp->packets_out - tp->lost_out;
 tp->left_out = tp->sacked_out + tp->lost_out;
}


static inline __attribute__((always_inline)) void __tcp_enter_cwr(struct tcp_sock *tp)
{
 tp->undo_marker = 0;
 tp->snd_ssthresh = tp->ca_ops->ssthresh(tp);
 tp->snd_cwnd = ({ typeof(tp->snd_cwnd) _x = (tp->snd_cwnd); typeof(tcp_packets_in_flight(tp) + 1U) _y = (tcp_packets_in_flight(tp) + 1U); (void) (&_x == &_y); _x < _y ? _x : _y; });

 tp->snd_cwnd_cnt = 0;
 tp->high_seq = tp->snd_nxt;
 tp->snd_cwnd_stamp = ((__u32)(jiffies));
 TCP_ECN_queue_cwr(tp);
}

static inline __attribute__((always_inline)) void tcp_enter_cwr(struct tcp_sock *tp)
{
 tp->prior_ssthresh = 0;
 if (tp->ca_state < TCP_CA_CWR) {
  __tcp_enter_cwr(tp);
  tcp_set_ca_state(tp, TCP_CA_CWR);
 }
}

extern __u32 tcp_init_cwnd(struct tcp_sock *tp, struct dst_entry *dst);




static __inline__ __attribute__((always_inline)) __u32 tcp_max_burst(const struct tcp_sock *tp)
{
 return 3;
}

static __inline__ __attribute__((always_inline)) void tcp_minshall_update(struct tcp_sock *tp, int mss,
        const struct sk_buff *skb)
{
 if (skb->len < mss)
  tp->snd_sml = ((struct tcp_skb_cb *)&((skb)->cb[0]))->end_seq;
}

static __inline__ __attribute__((always_inline)) void tcp_check_probe_timer(struct sock *sk, struct tcp_sock *tp)
{
 if (!tp->packets_out && !tp->pending)
  tcp_reset_xmit_timer(sk, 3, tp->rto);
}

static __inline__ __attribute__((always_inline)) void tcp_push_pending_frames(struct sock *sk,
            struct tcp_sock *tp)
{
 __tcp_push_pending_frames(sk, tp, tcp_current_mss(sk, 1), tp->nonagle);
}

static __inline__ __attribute__((always_inline)) void tcp_init_wl(struct tcp_sock *tp, u32 ack, u32 seq)
{
 tp->snd_wl1 = seq;
}

static __inline__ __attribute__((always_inline)) void tcp_update_wl(struct tcp_sock *tp, u32 ack, u32 seq)
{
 tp->snd_wl1 = seq;
}

extern void tcp_destroy_sock(struct sock *sk);





static __inline__ __attribute__((always_inline)) u16 tcp_v4_check(struct tcphdr *th, int len,
       unsigned long saddr, unsigned long daddr,
       unsigned long base)
{
 return csum_tcpudp_magic(saddr,daddr,len,IPPROTO_TCP,base);
}

static __inline__ __attribute__((always_inline)) int __tcp_checksum_complete(struct sk_buff *skb)
{
 return (unsigned short)csum_fold(skb_checksum(skb, 0, skb->len, skb->csum));
}

static __inline__ __attribute__((always_inline)) int tcp_checksum_complete(struct sk_buff *skb)
{
 return skb->ip_summed != 2 &&
  __tcp_checksum_complete(skb);
}



static __inline__ __attribute__((always_inline)) void tcp_prequeue_init(struct tcp_sock *tp)
{
 tp->ucopy.task = ((void *)0);
 tp->ucopy.len = 0;
 tp->ucopy.memory = 0;
 skb_queue_head_init(&tp->ucopy.prequeue);
}
# 1342 "include/net/tcp.h"
static __inline__ __attribute__((always_inline)) int tcp_prequeue(struct sock *sk, struct sk_buff *skb)
{
 struct tcp_sock *tp = tcp_sk(sk);

 if (!sysctl_tcp_low_latency && tp->ucopy.task) {
  __skb_queue_tail(&tp->ucopy.prequeue, skb);
  tp->ucopy.memory += skb->truesize;
  if (tp->ucopy.memory > sk->sk_rcvbuf) {
   struct sk_buff *skb1;

   do { if (__builtin_expect(!!((((sk)->sk_lock.owner))!=0), 0)) __BUG(); } while(0);

   while ((skb1 = __skb_dequeue(&tp->ucopy.prequeue)) != ((void *)0)) {
    sk->sk_backlog_rcv(sk, skb1);
    (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(net_statistics[0]); (__typeof__(net_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[LINUX_MIB_TCPPREQUEUEDROPPED]++);
   }

   tp->ucopy.memory = 0;
  } else if (skb_queue_len(&tp->ucopy.prequeue) == 1) {
   __wake_up(sk->sk_sleep, 1, 1, ((void *)0));
   if (!tcp_ack_scheduled(tp))
    tcp_reset_xmit_timer(sk, 2, (3*((unsigned)(250/5)))/4);
  }
  return 1;
 }
 return 0;
}
# 1381 "include/net/tcp.h"
static __inline__ __attribute__((always_inline)) void tcp_set_state(struct sock *sk, int state)
{
 int oldstate = sk->__sk_common.skc_state;

 switch (state) {
 case TCP_ESTABLISHED:
  if (oldstate != TCP_ESTABLISHED)
   (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[!(((current_thread_info()->preempt_count) & (((1UL << (8))-1) << (0 + 8))))]); (__typeof__(tcp_statistics[!(((current_thread_info()->preempt_count) & (((1UL << (8))-1) << (0 + 8))))]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_CURRESTAB]++);
  break;

 case TCP_CLOSE:
  if (oldstate == TCP_CLOSE_WAIT || oldstate == TCP_ESTABLISHED)
   (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[!(((current_thread_info()->preempt_count) & (((1UL << (8))-1) << (0 + 8))))]); (__typeof__(tcp_statistics[!(((current_thread_info()->preempt_count) & (((1UL << (8))-1) << (0 + 8))))]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_ESTABRESETS]++);

  sk->sk_prot->unhash(sk);
  if (tcp_sk(sk)->bind_hash &&
      !(sk->sk_userlocks & 8))
   tcp_put_port(sk);

 default:
  if (oldstate==TCP_ESTABLISHED)
   (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[!(((current_thread_info()->preempt_count) & (((1UL << (8))-1) << (0 + 8))))]); (__typeof__(tcp_statistics[!(((current_thread_info()->preempt_count) & (((1UL << (8))-1) << (0 + 8))))]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_CURRESTAB]--);
 }




 sk->__sk_common.skc_state = state;




}

static __inline__ __attribute__((always_inline)) void tcp_done(struct sock *sk)
{
 tcp_set_state(sk, TCP_CLOSE);
 tcp_clear_xmit_timers(sk);

 sk->sk_shutdown = 3;

 if (!sock_flag(sk, SOCK_DEAD))
  sk->sk_state_change(sk);
 else
  tcp_destroy_sock(sk);
}

static __inline__ __attribute__((always_inline)) void tcp_sack_reset(struct tcp_options_received *rx_opt)
{
 rx_opt->dsack = 0;
 rx_opt->eff_sacks = 0;
 rx_opt->num_sacks = 0;
}

static __inline__ __attribute__((always_inline)) void tcp_build_and_update_options(__u32 *ptr, struct tcp_sock *tp, __u32 tstamp)
{
 if (tp->rx_opt.tstamp_ok) {
  *ptr++ = (( __be32)((__u32)( (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x000000ffUL) << 24) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0xff000000UL) >> 24) )));



  *ptr++ = (( __be32)(__builtin_constant_p((__u32)((tstamp))) ? ({ __u32 __x = (((tstamp))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((tstamp)))));
  *ptr++ = (( __be32)(__builtin_constant_p((__u32)((tp->rx_opt.ts_recent))) ? ({ __u32 __x = (((tp->rx_opt.ts_recent))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((tp->rx_opt.ts_recent)))));
 }
 if (tp->rx_opt.eff_sacks) {
  struct tcp_sack_block *sp = tp->rx_opt.dsack ? tp->duplicate_sack : tp->selective_acks;
  int this_sack;

  *ptr++ = (( __be32)((__u32)( (((__u32)(((1 << 24) | (1 << 16) | (5 << 8) | (2 + (tp->rx_opt.eff_sacks * 8)))) & (__u32)0x000000ffUL) << 24) | (((__u32)(((1 << 24) | (1 << 16) | (5 << 8) | (2 + (tp->rx_opt.eff_sacks * 8)))) & (__u32)0x0000ff00UL) << 8) | (((__u32)(((1 << 24) | (1 << 16) | (5 << 8) | (2 + (tp->rx_opt.eff_sacks * 8)))) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(((1 << 24) | (1 << 16) | (5 << 8) | (2 + (tp->rx_opt.eff_sacks * 8)))) & (__u32)0xff000000UL) >> 24) )));




  for(this_sack = 0; this_sack < tp->rx_opt.eff_sacks; this_sack++) {
   *ptr++ = (( __be32)(__builtin_constant_p((__u32)((sp[this_sack].start_seq))) ? ({ __u32 __x = (((sp[this_sack].start_seq))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((sp[this_sack].start_seq)))));
   *ptr++ = (( __be32)(__builtin_constant_p((__u32)((sp[this_sack].end_seq))) ? ({ __u32 __x = (((sp[this_sack].end_seq))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((sp[this_sack].end_seq)))));
  }
  if (tp->rx_opt.dsack) {
   tp->rx_opt.dsack = 0;
   tp->rx_opt.eff_sacks--;
  }
 }
}






static inline __attribute__((always_inline)) void tcp_syn_build_options(__u32 *ptr, int mss, int ts, int sack,
          int offer_wscale, int wscale, __u32 tstamp, __u32 ts_recent)
{
# 1486 "include/net/tcp.h"
 *ptr++ = (( __be32)(__builtin_constant_p((__u32)(((2 << 24) | (4 << 16) | mss))) ? ({ __u32 __x = ((((2 << 24) | (4 << 16) | mss))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((((2 << 24) | (4 << 16) | mss)))));
 if (ts) {
  if(sack)
   *ptr++ = (( __be32)((__u32)( (((__u32)(((4 << 24) | (2 << 16) | (8 << 8) | 10)) & (__u32)0x000000ffUL) << 24) | (((__u32)(((4 << 24) | (2 << 16) | (8 << 8) | 10)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(((4 << 24) | (2 << 16) | (8 << 8) | 10)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(((4 << 24) | (2 << 16) | (8 << 8) | 10)) & (__u32)0xff000000UL) >> 24) )));

  else
   *ptr++ = (( __be32)((__u32)( (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x000000ffUL) << 24) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10)) & (__u32)0xff000000UL) >> 24) )));

  *ptr++ = (( __be32)(__builtin_constant_p((__u32)((tstamp))) ? ({ __u32 __x = (((tstamp))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((tstamp)))));
  *ptr++ = (( __be32)(__builtin_constant_p((__u32)((ts_recent))) ? ({ __u32 __x = (((ts_recent))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((ts_recent)))));
 } else if(sack)
  *ptr++ = (( __be32)((__u32)( (((__u32)(((1 << 24) | (1 << 16) | (4 << 8) | 2)) & (__u32)0x000000ffUL) << 24) | (((__u32)(((1 << 24) | (1 << 16) | (4 << 8) | 2)) & (__u32)0x0000ff00UL) << 8) | (((__u32)(((1 << 24) | (1 << 16) | (4 << 8) | 2)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(((1 << 24) | (1 << 16) | (4 << 8) | 2)) & (__u32)0xff000000UL) >> 24) )));

 if (offer_wscale)
  *ptr++ = (( __be32)(__builtin_constant_p((__u32)(((1 << 24) | (3 << 16) | (3 << 8) | (wscale)))) ? ({ __u32 __x = ((((1 << 24) | (3 << 16) | (3 << 8) | (wscale)))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((((1 << 24) | (3 << 16) | (3 << 8) | (wscale))))));
}


extern void tcp_select_initial_window(int __space, __u32 mss,
          __u32 *rcv_wnd, __u32 *window_clamp,
          int wscale_ok, __u8 *rcv_wscale);

static inline __attribute__((always_inline)) int tcp_win_from_space(int space)
{
 return sysctl_tcp_adv_win_scale<=0 ?
  (space>>(-sysctl_tcp_adv_win_scale)) :
  space - (space>>sysctl_tcp_adv_win_scale);
}


static inline __attribute__((always_inline)) int tcp_space(const struct sock *sk)
{
 return tcp_win_from_space(sk->sk_rcvbuf -
      ((&sk->sk_rmem_alloc)->counter));
}

static inline __attribute__((always_inline)) int tcp_full_space(const struct sock *sk)
{
 return tcp_win_from_space(sk->sk_rcvbuf);
}

static inline __attribute__((always_inline)) void tcp_acceptq_queue(struct sock *sk, struct request_sock *req,
      struct sock *child)
{
 reqsk_queue_add(&tcp_sk(sk)->accept_queue, req, sk, child);
}

static inline __attribute__((always_inline)) void
tcp_synq_removed(struct sock *sk, struct request_sock *req)
{
 if (reqsk_queue_removed(&tcp_sk(sk)->accept_queue, req) == 0)
  tcp_delete_keepalive_timer(sk);
}

static inline __attribute__((always_inline)) void tcp_synq_added(struct sock *sk)
{
 if (reqsk_queue_added(&tcp_sk(sk)->accept_queue) == 0)
  tcp_reset_keepalive_timer(sk, ((unsigned)(3*250)));
}

static inline __attribute__((always_inline)) int tcp_synq_len(struct sock *sk)
{
 return reqsk_queue_len(&tcp_sk(sk)->accept_queue);
}

static inline __attribute__((always_inline)) int tcp_synq_young(struct sock *sk)
{
 return reqsk_queue_len_young(&tcp_sk(sk)->accept_queue);
}

static inline __attribute__((always_inline)) int tcp_synq_is_full(struct sock *sk)
{
 return reqsk_queue_is_full(&tcp_sk(sk)->accept_queue);
}

static inline __attribute__((always_inline)) void tcp_synq_unlink(struct tcp_sock *tp, struct request_sock *req,
       struct request_sock **prev)
{
 reqsk_queue_unlink(&tp->accept_queue, req, prev);
}

static inline __attribute__((always_inline)) void tcp_synq_drop(struct sock *sk, struct request_sock *req,
         struct request_sock **prev)
{
 tcp_synq_unlink(tcp_sk(sk), req, prev);
 tcp_synq_removed(sk, req);
 reqsk_free(req);
}

static __inline__ __attribute__((always_inline)) void tcp_openreq_init(struct request_sock *req,
     struct tcp_options_received *rx_opt,
     struct sk_buff *skb)
{
 struct inet_request_sock *ireq = inet_rsk(req);

 req->rcv_wnd = 0;
 tcp_rsk(req)->rcv_isn = ((struct tcp_skb_cb *)&((skb)->cb[0]))->seq;
 req->mss = rx_opt->mss_clamp;
 req->ts_recent = rx_opt->saw_tstamp ? rx_opt->rcv_tsval : 0;
 ireq->tstamp_ok = rx_opt->tstamp_ok;
 ireq->sack_ok = rx_opt->sack_ok;
 ireq->snd_wscale = rx_opt->snd_wscale;
 ireq->wscale_ok = rx_opt->wscale_ok;
 ireq->acked = 0;
 ireq->ecn_ok = 0;
 ireq->rmt_port = skb->h.th->source;
}

extern void tcp_enter_memory_pressure(void);

extern void tcp_listen_wlock(void);






static inline __attribute__((always_inline)) void tcp_listen_lock(void)
{

 _read_lock(&(tcp_hashinfo.__tcp_lhash_lock));
 atomic_inc(&(tcp_hashinfo.__tcp_lhash_users));
 _read_unlock(&(tcp_hashinfo.__tcp_lhash_lock));
}

static inline __attribute__((always_inline)) void tcp_listen_unlock(void)
{
 if (atomic_dec_and_test(&(tcp_hashinfo.__tcp_lhash_users)))
  __wake_up(&(tcp_hashinfo.__tcp_lhash_wait), 2 | 1, 1, ((void *)0));
}

static inline __attribute__((always_inline)) int keepalive_intvl_when(const struct tcp_sock *tp)
{
 return tp->keepalive_intvl ? : sysctl_tcp_keepalive_intvl;
}

static inline __attribute__((always_inline)) int keepalive_time_when(const struct tcp_sock *tp)
{
 return tp->keepalive_time ? : sysctl_tcp_keepalive_time;
}

static inline __attribute__((always_inline)) int tcp_fin_time(const struct tcp_sock *tp)
{
 int fin_timeout = tp->linger2 ? : sysctl_tcp_fin_timeout;

 if (fin_timeout < (tp->rto<<2) - (tp->rto>>1))
  fin_timeout = (tp->rto<<2) - (tp->rto>>1);

 return fin_timeout;
}

static inline __attribute__((always_inline)) int tcp_paws_check(const struct tcp_options_received *rx_opt, int rst)
{
 if ((s32)(rx_opt->rcv_tsval - rx_opt->ts_recent) >= 0)
  return 0;
 if (xtime.tv_sec >= rx_opt->ts_recent_stamp + (60 * 60 * 24 * 24))
  return 0;
# 1656 "include/net/tcp.h"
 if (rst && xtime.tv_sec >= rx_opt->ts_recent_stamp + 60)
  return 0;
 return 1;
}

static inline __attribute__((always_inline)) void tcp_v4_setup_caps(struct sock *sk, struct dst_entry *dst)
{
 sk->sk_route_caps = dst->dev->features;
 if (sk->sk_route_caps & 2048) {
  if (sock_flag(sk, SOCK_NO_LARGESEND) || dst->header_len)
   sk->sk_route_caps &= ~2048;
 }
}



static inline __attribute__((always_inline)) int tcp_use_frto(const struct sock *sk)
{
 const struct tcp_sock *tp = tcp_sk(sk);





 return (sysctl_tcp_frto && sk->sk_send_head &&
  !after(((struct tcp_skb_cb *)&((sk->sk_send_head)->cb[0]))->end_seq,
         tp->snd_una + tp->snd_wnd));
}

static inline __attribute__((always_inline)) void tcp_mib_init(void)
{

 (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[1]); (__typeof__(tcp_statistics[1]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_RTOALGORITHM] += 1);
 (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[1]); (__typeof__(tcp_statistics[1]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_RTOMIN] += ((unsigned)(250/5))*1000/250);
 (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[1]); (__typeof__(tcp_statistics[1]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_RTOMAX] += ((unsigned)(120*250))*1000/250);
 (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[1]); (__typeof__(tcp_statistics[1]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_MAXCONN] += -1);
}


enum tcp_seq_states {
 TCP_SEQ_STATE_LISTENING,
 TCP_SEQ_STATE_OPENREQ,
 TCP_SEQ_STATE_ESTABLISHED,
 TCP_SEQ_STATE_TIME_WAIT,
};

struct tcp_seq_afinfo {
 struct module *owner;
 char *name;
 sa_family_t family;
 int (*seq_show) (struct seq_file *m, void *v);
 struct file_operations *seq_fops;
};

struct tcp_iter_state {
 sa_family_t family;
 enum tcp_seq_states state;
 struct sock *syn_wait_sk;
 int bucket, sbucket, num, uid;
 struct seq_operations seq_ops;
};

extern int tcp_proc_register(struct tcp_seq_afinfo *afinfo);
extern void tcp_proc_unregister(struct tcp_seq_afinfo *afinfo);
# 49 "net/ipv6/tcp_ipv6.c" 2
# 1 "include/net/ndisc.h" 1
# 18 "include/net/ndisc.h"
enum {
 __ND_OPT_PREFIX_INFO_END = 0,
 ND_OPT_SOURCE_LL_ADDR = 1,
 ND_OPT_TARGET_LL_ADDR = 2,
 ND_OPT_PREFIX_INFO = 3,
 ND_OPT_REDIRECT_HDR = 4,
 ND_OPT_MTU = 5,
 __ND_OPT_MAX
};
# 44 "include/net/ndisc.h"
extern struct neigh_table nd_tbl;

struct nd_msg {
        struct icmp6hdr icmph;
        struct in6_addr target;
 __u8 opt[0];
};

struct rs_msg {
 struct icmp6hdr icmph;
 __u8 opt[0];
};

struct ra_msg {
        struct icmp6hdr icmph;
 __u32 reachable_time;
 __u32 retrans_timer;
};

struct nd_opt_hdr {
 __u8 nd_opt_type;
 __u8 nd_opt_len;
} __attribute__((__packed__));


extern int ndisc_init(struct net_proto_family *ops);

extern void ndisc_cleanup(void);

extern int ndisc_rcv(struct sk_buff *skb);

extern void ndisc_send_ns(struct net_device *dev,
           struct neighbour *neigh,
           struct in6_addr *solicit,
           struct in6_addr *daddr,
           struct in6_addr *saddr);

extern void ndisc_send_rs(struct net_device *dev,
           struct in6_addr *saddr,
           struct in6_addr *daddr);

extern void ndisc_forwarding_on(void);
extern void ndisc_forwarding_off(void);

extern void ndisc_send_redirect(struct sk_buff *skb,
          struct neighbour *neigh,
          struct in6_addr *target);

extern int ndisc_mc_map(struct in6_addr *addr, char *buf, struct net_device *dev, int dir);


struct rt6_info * dflt_rt_lookup(void);




extern int igmp6_init(struct net_proto_family *ops);

extern void igmp6_cleanup(void);

extern int igmp6_event_query(struct sk_buff *skb);

extern int igmp6_event_report(struct sk_buff *skb);

extern void igmp6_cleanup(void);


extern int ndisc_ifinfo_sysctl_change(ctl_table *ctl,
          int write,
          struct file * filp,
          void *buffer,
          size_t *lenp,
          loff_t *ppos);


extern void inet6_ifinfo_notify(int event,
          struct inet6_dev *idev);

static inline __attribute__((always_inline)) struct neighbour * ndisc_get_neigh(struct net_device *dev, struct in6_addr *addr)
{

 if (dev)
  return __neigh_lookup(&nd_tbl, addr, dev, 1);

 return ((void *)0);
}
# 50 "net/ipv6/tcp_ipv6.c" 2
# 1 "include/net/ipv6.h" 1
# 96 "include/net/ipv6.h"
struct frag_hdr {
 unsigned char nexthdr;
 unsigned char reserved;
 unsigned short frag_off;
 __u32 identification;
};
# 110 "include/net/ipv6.h"
extern int sysctl_ipv6_bindv6only;
extern int sysctl_mld_max_msf;


extern __typeof__(struct ipstats_mib) *ipv6_statistics[2];



extern __typeof__(struct icmpv6_mib) *icmpv6_statistics[2];
# 144 "include/net/ipv6.h"
extern __typeof__(struct udp_mib) *udp_stats_in6[2];



extern atomic_t inet6_sock_nr;

int snmp6_register_dev(struct inet6_dev *idev);
int snmp6_unregister_dev(struct inet6_dev *idev);
int snmp6_alloc_dev(struct inet6_dev *idev);
int snmp6_free_dev(struct inet6_dev *idev);
int snmp6_mib_init(void *ptr[2], size_t mibsize, size_t mibalign);
void snmp6_mib_free(void *ptr[2]);

struct ip6_ra_chain
{
 struct ip6_ra_chain *next;
 struct sock *sk;
 int sel;
 void (*destructor)(struct sock *);
};

extern struct ip6_ra_chain *ip6_ra_chain;
extern rwlock_t ip6_ra_lock;






struct ipv6_txoptions
{

 int tot_len;



 __u16 opt_flen;
 __u16 opt_nflen;

 struct ipv6_opt_hdr *hopopt;
 struct ipv6_opt_hdr *dst0opt;
 struct ipv6_rt_hdr *srcrt;
 struct ipv6_opt_hdr *dst1opt;


};

struct ip6_flowlabel
{
 struct ip6_flowlabel *next;
 u32 label;
 struct in6_addr dst;
 struct ipv6_txoptions *opt;
 atomic_t users;
 unsigned long linger;
 u8 share;
 u32 owner;
 unsigned long lastuse;
 unsigned long expires;
};




struct ipv6_fl_socklist
{
 struct ipv6_fl_socklist *next;
 struct ip6_flowlabel *fl;
};

extern struct ip6_flowlabel *fl6_sock_lookup(struct sock *sk, u32 label);
extern struct ipv6_txoptions *fl6_merge_options(struct ipv6_txoptions * opt_space,
         struct ip6_flowlabel * fl,
         struct ipv6_txoptions * fopt);
extern void fl6_free_socklist(struct sock *sk);
extern int ipv6_flowlabel_opt(struct sock *sk, char *optval, int optlen);
extern void ip6_flowlabel_init(void);
extern void ip6_flowlabel_cleanup(void);

static inline __attribute__((always_inline)) void fl6_sock_release(struct ip6_flowlabel *fl)
{
 if (fl)
  atomic_dec(&fl->users);
}

extern int ip6_ra_control(struct sock *sk, int sel,
            void (*destructor)(struct sock *));


extern int ipv6_parse_hopopts(struct sk_buff *skb, int);

extern struct ipv6_txoptions * ipv6_dup_options(struct sock *sk, struct ipv6_txoptions *opt);

extern int ip6_frag_nqueues;
extern atomic_t ip6_frag_mem;







typedef int (*inet_getfrag_t) (const void *data,
        struct in6_addr *addr,
        char *,
        unsigned int, unsigned int);


extern int ipv6_addr_type(const struct in6_addr *addr);

static inline __attribute__((always_inline)) int ipv6_addr_scope(const struct in6_addr *addr)
{
 return ipv6_addr_type(addr) & 0x00f0U;
}

static inline __attribute__((always_inline)) int ipv6_addr_cmp(const struct in6_addr *a1, const struct in6_addr *a2)
{
 return __builtin_memcmp((const void *) a1, (const void *) a2, sizeof(struct in6_addr));
}

static inline __attribute__((always_inline)) void ipv6_addr_copy(struct in6_addr *a1, const struct in6_addr *a2)
{
 __memcpy((void *) a1,(const void *) a2,sizeof(struct in6_addr));
}

static inline __attribute__((always_inline)) void ipv6_addr_prefix(struct in6_addr *pfx,
        const struct in6_addr *addr,
        int plen)
{

 int o = plen >> 3,
     b = plen & 0x7;

 __memcpy(pfx->in6_u.u6_addr8,addr,o);
 if (b != 0) {
  pfx->in6_u.u6_addr8[o] = addr->in6_u.u6_addr8[o] & (0xff00 >> b);
  o++;
 }
 if (o < 16)
  __memset_generic((pfx->in6_u.u6_addr8 + o),(0),(16 - o));
}


static inline __attribute__((always_inline)) void ipv6_addr_set(struct in6_addr *addr,
         __u32 w1, __u32 w2,
         __u32 w3, __u32 w4)
{
 addr->in6_u.u6_addr32[0] = w1;
 addr->in6_u.u6_addr32[1] = w2;
 addr->in6_u.u6_addr32[2] = w3;
 addr->in6_u.u6_addr32[3] = w4;
}


static inline __attribute__((always_inline)) int ipv6_addr_equal(const struct in6_addr *a1,
      const struct in6_addr *a2)
{
 return (a1->in6_u.u6_addr32[0] == a2->in6_u.u6_addr32[0] &&
  a1->in6_u.u6_addr32[1] == a2->in6_u.u6_addr32[1] &&
  a1->in6_u.u6_addr32[2] == a2->in6_u.u6_addr32[2] &&
  a1->in6_u.u6_addr32[3] == a2->in6_u.u6_addr32[3]);
}

static inline __attribute__((always_inline)) int __ipv6_prefix_equal(const u32 *a1, const u32 *a2,
          unsigned int prefixlen)
{
 unsigned pdw, pbi;


 pdw = prefixlen >> 5;
 if (pdw && __builtin_memcmp(a1, a2, pdw << 2))
  return 0;


 pbi = prefixlen & 0x1f;
 if (pbi && ((a1[pdw] ^ a2[pdw]) & (( __be32)(__builtin_constant_p((__u32)(((0xffffffff) << (32 - pbi)))) ? ({ __u32 __x = ((((0xffffffff) << (32 - pbi)))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((((0xffffffff) << (32 - pbi))))))))
  return 0;

 return 1;
}

static inline __attribute__((always_inline)) int ipv6_prefix_equal(const struct in6_addr *a1,
        const struct in6_addr *a2,
        unsigned int prefixlen)
{
 return __ipv6_prefix_equal(a1->in6_u.u6_addr32, a2->in6_u.u6_addr32,
       prefixlen);
}

static inline __attribute__((always_inline)) int ipv6_addr_any(const struct in6_addr *a)
{
 return ((a->in6_u.u6_addr32[0] | a->in6_u.u6_addr32[1] |
   a->in6_u.u6_addr32[2] | a->in6_u.u6_addr32[3] ) == 0);
}
# 347 "include/net/ipv6.h"
extern int ipv6_rcv(struct sk_buff *skb,
      struct net_device *dev,
      struct packet_type *pt);




extern int ip6_xmit(struct sock *sk,
      struct sk_buff *skb,
      struct flowi *fl,
      struct ipv6_txoptions *opt,
      int ipfragok);

extern int ip6_nd_hdr(struct sock *sk,
        struct sk_buff *skb,
        struct net_device *dev,
        struct in6_addr *saddr,
        struct in6_addr *daddr,
        int proto, int len);

extern int ip6_find_1stfragopt(struct sk_buff *skb, u8 **nexthdr);

extern int ip6_append_data(struct sock *sk,
      int getfrag(void *from, char *to, int offset, int len, int odd, struct sk_buff *skb),
          void *from,
      int length,
      int transhdrlen,
            int hlimit,
      struct ipv6_txoptions *opt,
      struct flowi *fl,
      struct rt6_info *rt,
      unsigned int flags);

extern int ip6_push_pending_frames(struct sock *sk);

extern void ip6_flush_pending_frames(struct sock *sk);

extern int ip6_dst_lookup(struct sock *sk,
            struct dst_entry **dst,
            struct flowi *fl);





extern int ip6_output(struct sk_buff *skb);
extern int ip6_forward(struct sk_buff *skb);
extern int ip6_input(struct sk_buff *skb);
extern int ip6_mc_input(struct sk_buff *skb);





extern u8 * ipv6_build_nfrag_opts(struct sk_buff *skb,
            u8 *prev_hdr,
            struct ipv6_txoptions *opt,
            struct in6_addr *daddr,
            u32 jumbolen);
extern u8 * ipv6_build_frag_opts(struct sk_buff *skb,
           u8 *prev_hdr,
           struct ipv6_txoptions *opt);
extern void ipv6_push_nfrag_opts(struct sk_buff *skb,
           struct ipv6_txoptions *opt,
           u8 *proto,
           struct in6_addr **daddr_p);
extern void ipv6_push_frag_opts(struct sk_buff *skb,
          struct ipv6_txoptions *opt,
          u8 *proto);

extern int ipv6_skip_exthdr(const struct sk_buff *, int start,
              u8 *nexthdrp);

extern int ipv6_ext_hdr(u8 nexthdr);

extern struct ipv6_txoptions * ipv6_invert_rthdr(struct sock *sk,
        struct ipv6_rt_hdr *hdr);






extern int ipv6_setsockopt(struct sock *sk, int level,
      int optname,
      char *optval,
      int optlen);
extern int ipv6_getsockopt(struct sock *sk, int level,
      int optname,
      char *optval,
      int *optlen);

extern void ipv6_packet_init(void);

extern void ipv6_packet_cleanup(void);

extern int ip6_datagram_connect(struct sock *sk,
           struct sockaddr *addr, int addr_len);

extern int ipv6_recv_error(struct sock *sk, struct msghdr *msg, int len);
extern void ipv6_icmp_error(struct sock *sk, struct sk_buff *skb, int err, u16 port,
      u32 info, u8 *payload);
extern void ipv6_local_error(struct sock *sk, int err, struct flowi *fl, u32 info);

extern int inet6_release(struct socket *sock);
extern int inet6_bind(struct socket *sock, struct sockaddr *uaddr,
        int addr_len);
extern int inet6_getname(struct socket *sock, struct sockaddr *uaddr,
    int *uaddr_len, int peer);
extern int inet6_ioctl(struct socket *sock, unsigned int cmd,
         unsigned long arg);




extern int sysctl_ip6frag_high_thresh;
extern int sysctl_ip6frag_low_thresh;
extern int sysctl_ip6frag_time;
extern int sysctl_ip6frag_secret_interval;
# 51 "net/ipv6/tcp_ipv6.c" 2
# 1 "include/net/transp_v6.h" 1
# 12 "include/net/transp_v6.h"
extern struct proto rawv6_prot;
extern struct proto udpv6_prot;
extern struct proto tcpv6_prot;

struct flowi;


extern void ipv6_rthdr_init(void);
extern void ipv6_frag_init(void);
extern void ipv6_nodata_init(void);
extern void ipv6_destopt_init(void);


extern void rawv6_init(void);
extern void udpv6_init(void);
extern void tcpv6_init(void);

extern int udpv6_connect(struct sock *sk,
            struct sockaddr *uaddr,
            int addr_len);

extern int datagram_recv_ctl(struct sock *sk,
        struct msghdr *msg,
        struct sk_buff *skb);

extern int datagram_send_ctl(struct msghdr *msg,
        struct flowi *fl,
        struct ipv6_txoptions *opt,
        int *hlimit);






extern struct tcp_func ipv4_specific;

extern int inet6_destroy_sock(struct sock *sk);
# 52 "net/ipv6/tcp_ipv6.c" 2
# 1 "include/net/addrconf.h" 1
# 22 "include/net/addrconf.h"
struct prefix_info {
 __u8 type;
 __u8 length;
 __u8 prefix_len;






 __u8 reserved : 6,
    autoconf : 1,
    onlink : 1;



 __u32 valid;
 __u32 prefered;
 __u32 reserved2;

 struct in6_addr prefix;
};
# 54 "include/net/addrconf.h"
extern int addrconf_init(void);
extern void addrconf_cleanup(void);

extern int addrconf_add_ifaddr(void *arg);
extern int addrconf_del_ifaddr(void *arg);
extern int addrconf_set_dstaddr(void *arg);

extern int ipv6_chk_addr(struct in6_addr *addr,
           struct net_device *dev,
           int strict);
extern struct inet6_ifaddr * ipv6_get_ifaddr(struct in6_addr *addr,
      struct net_device *dev,
      int strict);
extern int ipv6_get_saddr(struct dst_entry *dst,
            struct in6_addr *daddr,
            struct in6_addr *saddr);
extern int ipv6_dev_get_saddr(struct net_device *dev,
            struct in6_addr *daddr,
            struct in6_addr *saddr);
extern int ipv6_get_lladdr(struct net_device *dev, struct in6_addr *);
extern int ipv6_rcv_saddr_equal(const struct sock *sk,
            const struct sock *sk2);
extern void addrconf_join_solict(struct net_device *dev,
     struct in6_addr *addr);
extern void addrconf_leave_solict(struct inet6_dev *idev,
     struct in6_addr *addr);




extern int ipv6_sock_mc_join(struct sock *sk, int ifindex,
    struct in6_addr *addr);
extern int ipv6_sock_mc_drop(struct sock *sk, int ifindex,
    struct in6_addr *addr);
extern void ipv6_sock_mc_close(struct sock *sk);
extern int inet6_mc_check(struct sock *sk, struct in6_addr *mc_addr,
  struct in6_addr *src_addr);

extern int ipv6_dev_mc_inc(struct net_device *dev, struct in6_addr *addr);
extern int __ipv6_dev_mc_dec(struct inet6_dev *idev, struct in6_addr *addr);
extern int ipv6_dev_mc_dec(struct net_device *dev, struct in6_addr *addr);
extern void ipv6_mc_up(struct inet6_dev *idev);
extern void ipv6_mc_down(struct inet6_dev *idev);
extern void ipv6_mc_init_dev(struct inet6_dev *idev);
extern void ipv6_mc_destroy_dev(struct inet6_dev *idev);
extern void addrconf_dad_failure(struct inet6_ifaddr *ifp);

extern int ipv6_chk_mcast_addr(struct net_device *dev, struct in6_addr *group,
  struct in6_addr *src_addr);
extern int ipv6_is_mld(struct sk_buff *skb, int nexthdr);

extern void addrconf_prefix_rcv(struct net_device *dev, u8 *opt, int len);

extern int ipv6_get_hoplimit(struct net_device *dev);




extern int ipv6_sock_ac_join(struct sock *sk,int ifindex,struct in6_addr *addr);
extern int ipv6_sock_ac_drop(struct sock *sk,int ifindex,struct in6_addr *addr);
extern void ipv6_sock_ac_close(struct sock *sk);
extern int inet6_ac_check(struct sock *sk, struct in6_addr *addr, int ifindex);

extern int ipv6_dev_ac_inc(struct net_device *dev, struct in6_addr *addr);
extern int __ipv6_dev_ac_dec(struct inet6_dev *idev, struct in6_addr *addr);
extern int ipv6_chk_acast_addr(struct net_device *dev, struct in6_addr *addr);



extern int register_inet6addr_notifier(struct notifier_block *nb);
extern int unregister_inet6addr_notifier(struct notifier_block *nb);

static inline __attribute__((always_inline)) struct inet6_dev *
__in6_dev_get(struct net_device *dev)
{
 return (struct inet6_dev *)dev->ip6_ptr;
}

extern rwlock_t addrconf_lock;

static inline __attribute__((always_inline)) struct inet6_dev *
in6_dev_get(struct net_device *dev)
{
 struct inet6_dev *idev = ((void *)0);
 _read_lock(&addrconf_lock);
 idev = dev->ip6_ptr;
 if (idev)
  atomic_inc(&idev->refcnt);
 _read_unlock(&addrconf_lock);
 return idev;
}

extern void in6_dev_finish_destroy(struct inet6_dev *idev);

static inline __attribute__((always_inline)) void
in6_dev_put(struct inet6_dev *idev)
{
 if (atomic_dec_and_test(&idev->refcnt))
  in6_dev_finish_destroy(idev);
}





extern void inet6_ifa_finish_destroy(struct inet6_ifaddr *ifp);

static inline __attribute__((always_inline)) void in6_ifa_put(struct inet6_ifaddr *ifp)
{
 if (atomic_dec_and_test(&ifp->refcnt))
  inet6_ifa_finish_destroy(ifp);
}





extern void addrconf_forwarding_on(void);




static __inline__ __attribute__((always_inline)) u8 ipv6_addr_hash(const struct in6_addr *addr)
{
 __u32 word;






 word = addr->in6_u.u6_addr32[2] ^ addr->in6_u.u6_addr32[3];
 word ^= (word >> 16);
 word ^= (word >> 8);

 return ((word ^ (word >> 4)) & 0x0f);
}





static inline __attribute__((always_inline)) void addrconf_addr_solict_mult(const struct in6_addr *addr,
          struct in6_addr *solicited)
{
 ipv6_addr_set(solicited,
        (( __be32)((__u32)( (((__u32)((0xFF020000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0xFF020000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0xFF020000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0xFF020000)) & (__u32)0xff000000UL) >> 24) ))), 0,
        (( __be32)((__u32)( (((__u32)((0x1)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x1)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x1)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x1)) & (__u32)0xff000000UL) >> 24) ))),
        (( __be32)((__u32)( (((__u32)((0xFF000000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0xFF000000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0xFF000000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0xFF000000)) & (__u32)0xff000000UL) >> 24) ))) | addr->in6_u.u6_addr32[3]);
}


static inline __attribute__((always_inline)) void ipv6_addr_all_nodes(struct in6_addr *addr)
{
 ipv6_addr_set(addr,
        (( __be32)((__u32)( (((__u32)((0xFF020000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0xFF020000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0xFF020000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0xFF020000)) & (__u32)0xff000000UL) >> 24) ))), 0, 0,
        (( __be32)((__u32)( (((__u32)((0x1)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x1)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x1)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x1)) & (__u32)0xff000000UL) >> 24) ))));
}

static inline __attribute__((always_inline)) void ipv6_addr_all_routers(struct in6_addr *addr)
{
 ipv6_addr_set(addr,
        (( __be32)((__u32)( (((__u32)((0xFF020000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0xFF020000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0xFF020000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0xFF020000)) & (__u32)0xff000000UL) >> 24) ))), 0, 0,
        (( __be32)((__u32)( (((__u32)((0x2)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x2)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x2)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x2)) & (__u32)0xff000000UL) >> 24) ))));
}

static inline __attribute__((always_inline)) int ipv6_addr_is_multicast(const struct in6_addr *addr)
{
 return (addr->in6_u.u6_addr32[0] & (( __be32)((__u32)( (((__u32)((0xFF000000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0xFF000000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0xFF000000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0xFF000000)) & (__u32)0xff000000UL) >> 24) )))) == (( __be32)((__u32)( (((__u32)((0xFF000000)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0xFF000000)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0xFF000000)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0xFF000000)) & (__u32)0xff000000UL) >> 24) )));
}

static inline __attribute__((always_inline)) int ipv6_addr_is_ll_all_nodes(const struct in6_addr *addr)
{
 return (addr->in6_u.u6_addr32[0] == (( __be32)(__builtin_constant_p((__u32)((0xff020000))) ? ({ __u32 __x = (((0xff020000))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((0xff020000))))) &&
  addr->in6_u.u6_addr32[1] == 0 &&
  addr->in6_u.u6_addr32[2] == 0 &&
  addr->in6_u.u6_addr32[3] == (( __be32)(__builtin_constant_p((__u32)((0x00000001))) ? ({ __u32 __x = (((0x00000001))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((0x00000001))))));
}

static inline __attribute__((always_inline)) int ipv6_addr_is_ll_all_routers(const struct in6_addr *addr)
{
 return (addr->in6_u.u6_addr32[0] == (( __be32)(__builtin_constant_p((__u32)((0xff020000))) ? ({ __u32 __x = (((0xff020000))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((0xff020000))))) &&
  addr->in6_u.u6_addr32[1] == 0 &&
  addr->in6_u.u6_addr32[2] == 0 &&
  addr->in6_u.u6_addr32[3] == (( __be32)(__builtin_constant_p((__u32)((0x00000002))) ? ({ __u32 __x = (((0x00000002))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((0x00000002))))));
}
# 53 "net/ipv6/tcp_ipv6.c" 2
# 1 "include/net/ip6_route.h" 1
# 13 "include/net/ip6_route.h"
# 1 "include/net/ip6_fib.h" 1
# 18 "include/net/ip6_fib.h"
# 1 "include/linux/ipv6_route.h" 1
# 31 "include/linux/ipv6_route.h"
struct in6_rtmsg {
 struct in6_addr rtmsg_dst;
 struct in6_addr rtmsg_src;
 struct in6_addr rtmsg_gateway;
 __u32 rtmsg_type;
 __u16 rtmsg_dst_len;
 __u16 rtmsg_src_len;
 __u32 rtmsg_metric;
 unsigned long rtmsg_info;
        __u32 rtmsg_flags;
 int rtmsg_ifindex;
};
# 19 "include/net/ip6_fib.h" 2






struct rt6_info;

struct fib6_node
{
 struct fib6_node *parent;
 struct fib6_node *left;
 struct fib6_node *right;

 struct fib6_node *subtree;

 struct rt6_info *leaf;

 __u16 fn_bit;
 __u16 fn_flags;
 __u32 fn_sernum;
};







struct rt6key
{
 struct in6_addr addr;
 int plen;
};

struct rt6_info
{
 union {
  struct dst_entry dst;
  struct rt6_info *next;
 } u;

 struct inet6_dev *rt6i_idev;





 struct fib6_node *rt6i_node;

 struct in6_addr rt6i_gateway;

 u32 rt6i_flags;
 u32 rt6i_metric;
 atomic_t rt6i_ref;

 struct rt6key rt6i_dst;
 struct rt6key rt6i_src;

 u8 rt6i_protocol;
};

struct fib6_walker_t
{
 struct fib6_walker_t *prev, *next;
 struct fib6_node *root, *node;
 struct rt6_info *leaf;
 unsigned char state;
 unsigned char prune;
 int (*func)(struct fib6_walker_t *);
 void *args;
};

extern struct fib6_walker_t fib6_walker_list;
extern rwlock_t fib6_walker_lock;

static inline __attribute__((always_inline)) void fib6_walker_link(struct fib6_walker_t *w)
{
 _write_lock_bh(&fib6_walker_lock);
 w->next = fib6_walker_list.next;
 w->prev = &fib6_walker_list;
 w->next->prev = w;
 w->prev->next = w;
 _write_unlock_bh(&fib6_walker_lock);
}

static inline __attribute__((always_inline)) void fib6_walker_unlink(struct fib6_walker_t *w)
{
 _write_lock_bh(&fib6_walker_lock);
 w->next->prev = w->prev;
 w->prev->next = w->next;
 w->prev = w->next = w;
 _write_unlock_bh(&fib6_walker_lock);
}

struct rt6_statistics {
 __u32 fib_nodes;
 __u32 fib_route_nodes;
 __u32 fib_rt_alloc;
 __u32 fib_rt_entries;
 __u32 fib_rt_cache;
 __u32 fib_discarded_routes;
};
# 144 "include/net/ip6_fib.h"
typedef void (*f_pnode)(struct fib6_node *fn, void *);

extern struct fib6_node ip6_routing_table;





extern struct fib6_node *fib6_lookup(struct fib6_node *root,
          struct in6_addr *daddr,
          struct in6_addr *saddr);

struct fib6_node *fib6_locate(struct fib6_node *root,
          struct in6_addr *daddr, int dst_len,
          struct in6_addr *saddr, int src_len);

extern void fib6_clean_tree(struct fib6_node *root,
      int (*func)(struct rt6_info *, void *arg),
      int prune, void *arg);

extern int fib6_walk(struct fib6_walker_t *w);
extern int fib6_walk_continue(struct fib6_walker_t *w);

extern int fib6_add(struct fib6_node *root,
      struct rt6_info *rt,
      struct nlmsghdr *nlh,
      void *rtattr,
      struct netlink_skb_parms *req);

extern int fib6_del(struct rt6_info *rt,
      struct nlmsghdr *nlh,
      void *rtattr,
      struct netlink_skb_parms *req);

extern void inet6_rt_notify(int event, struct rt6_info *rt,
      struct nlmsghdr *nlh,
      struct netlink_skb_parms *req);

extern void fib6_run_gc(unsigned long dummy);

extern void fib6_gc_cleanup(void);

extern void fib6_init(void);
# 14 "include/net/ip6_route.h" 2





struct pol_chain {
 int type;
 int priority;
 struct fib6_node *rules;
 struct pol_chain *next;
};

extern struct rt6_info ip6_null_entry;

extern int ip6_rt_gc_interval;

extern void ip6_route_input(struct sk_buff *skb);

extern struct dst_entry * ip6_route_output(struct sock *sk,
       struct flowi *fl);

extern int ip6_route_me_harder(struct sk_buff *skb);

extern void ip6_route_init(void);
extern void ip6_route_cleanup(void);

extern int ipv6_route_ioctl(unsigned int cmd, void *arg);

extern int ip6_route_add(struct in6_rtmsg *rtmsg,
           struct nlmsghdr *,
           void *rtattr,
           struct netlink_skb_parms *req);
extern int ip6_ins_rt(struct rt6_info *,
        struct nlmsghdr *,
        void *rtattr,
        struct netlink_skb_parms *req);
extern int ip6_del_rt(struct rt6_info *,
        struct nlmsghdr *,
        void *rtattr,
        struct netlink_skb_parms *req);

extern int ip6_rt_addr_add(struct in6_addr *addr,
      struct net_device *dev,
      int anycast);

extern int ip6_rt_addr_del(struct in6_addr *addr,
      struct net_device *dev);

extern void rt6_sndmsg(int type, struct in6_addr *dst,
        struct in6_addr *src,
        struct in6_addr *gw,
        struct net_device *dev,
        int dstlen, int srclen,
        int metric, __u32 flags);

extern struct rt6_info *rt6_lookup(struct in6_addr *daddr,
         struct in6_addr *saddr,
         int oif, int flags);

extern struct dst_entry *ndisc_dst_alloc(struct net_device *dev,
      struct neighbour *neigh,
      struct in6_addr *addr,
      int (*output)(struct sk_buff *));
extern int ndisc_dst_gc(int *more);
extern void fib6_force_start_gc(void);

extern struct rt6_info *addrconf_dst_alloc(struct inet6_dev *idev,
        const struct in6_addr *addr,
        int anycast);





extern struct rt6_info * rt6_get_dflt_router(struct in6_addr *addr,
          struct net_device *dev);
extern struct rt6_info * rt6_add_dflt_router(struct in6_addr *gwaddr,
          struct net_device *dev);

extern void rt6_purge_dflt_routers(void);

extern void rt6_reset_dflt_pointer(struct rt6_info *rt);

extern void rt6_redirect(struct in6_addr *dest,
          struct in6_addr *saddr,
          struct neighbour *neigh,
          u8 *lladdr,
          int on_link);

extern void rt6_pmtu_discovery(struct in6_addr *daddr,
         struct in6_addr *saddr,
         struct net_device *dev,
         u32 pmtu);

struct nlmsghdr;
struct netlink_callback;
extern int inet6_dump_fib(struct sk_buff *skb, struct netlink_callback *cb);
extern int inet6_rtm_newroute(struct sk_buff *skb, struct nlmsghdr* nlh, void *arg);
extern int inet6_rtm_delroute(struct sk_buff *skb, struct nlmsghdr* nlh, void *arg);
extern int inet6_rtm_getroute(struct sk_buff *skb, struct nlmsghdr* nlh, void *arg);

extern void rt6_ifdown(struct net_device *dev);
extern void rt6_mtu_change(struct net_device *dev, unsigned mtu);

extern rwlock_t rt6_lock;




static inline __attribute__((always_inline)) void ip6_dst_store(struct sock *sk, struct dst_entry *dst,
         struct in6_addr *daddr)
{
 struct ipv6_pinfo *np = inet6_sk(sk);
 struct rt6_info *rt = (struct rt6_info *) dst;

 _write_lock(&sk->sk_dst_lock);
 __sk_dst_set(sk, dst);
 np->daddr_cache = daddr;
 np->dst_cookie = rt->rt6i_node ? rt->rt6i_node->fn_sernum : 0;
 _write_unlock(&sk->sk_dst_lock);
}

static inline __attribute__((always_inline)) int ipv6_unicast_destination(struct sk_buff *skb)
{
 struct rt6_info *rt = (struct rt6_info *) skb->dst;

 return rt->rt6i_flags & 0x80000000;
}
# 54 "net/ipv6/tcp_ipv6.c" 2
# 1 "include/net/ip6_checksum.h" 1
# 55 "net/ipv6/tcp_ipv6.c" 2

# 1 "include/net/protocol.h" 1
# 37 "include/net/protocol.h"
struct net_protocol {
 int (*handler)(struct sk_buff *skb);
 void (*err_handler)(struct sk_buff *skb, u32 info);
 int no_policy;
};


struct inet6_protocol
{
 int (*handler)(struct sk_buff **skb, unsigned int *nhoffp);

 void (*err_handler)(struct sk_buff *skb,
          struct inet6_skb_parm *opt,
          int type, int code, int offset,
          __u32 info);
 unsigned int flags;
};






struct inet_protosw {
 struct list_head list;


 unsigned short type;
 int protocol;

 struct proto *prot;
 struct proto_ops *ops;

 int capability;



 char no_check;
 unsigned char flags;
};



extern struct net_protocol *inet_protocol_base;
extern struct net_protocol *inet_protos[256];


extern struct inet6_protocol *inet6_protos[256];


extern int inet_add_protocol(struct net_protocol *prot, unsigned char num);
extern int inet_del_protocol(struct net_protocol *prot, unsigned char num);
extern void inet_register_protosw(struct inet_protosw *p);
extern void inet_unregister_protosw(struct inet_protosw *p);


extern int inet6_add_protocol(struct inet6_protocol *prot, unsigned char num);
extern int inet6_del_protocol(struct inet6_protocol *prot, unsigned char num);
extern void inet6_register_protosw(struct inet_protosw *p);
extern void inet6_unregister_protosw(struct inet_protosw *p);
# 57 "net/ipv6/tcp_ipv6.c" 2
# 1 "include/net/xfrm.h" 1




# 1 "include/linux/xfrm.h" 1
# 13 "include/linux/xfrm.h"
typedef union
{
 __u32 a4;
 __u32 a6[4];
} xfrm_address_t;





struct xfrm_id
{
 xfrm_address_t daddr;
 __u32 spi;
 __u8 proto;
};



struct xfrm_selector
{
 xfrm_address_t daddr;
 xfrm_address_t saddr;
 __u16 dport;
 __u16 dport_mask;
 __u16 sport;
 __u16 sport_mask;
 __u16 family;
 __u8 prefixlen_d;
 __u8 prefixlen_s;
 __u8 proto;
 int ifindex;
 uid_t user;
};



struct xfrm_lifetime_cfg
{
 __u64 soft_byte_limit;
 __u64 hard_byte_limit;
 __u64 soft_packet_limit;
 __u64 hard_packet_limit;
 __u64 soft_add_expires_seconds;
 __u64 hard_add_expires_seconds;
 __u64 soft_use_expires_seconds;
 __u64 hard_use_expires_seconds;
};

struct xfrm_lifetime_cur
{
 __u64 bytes;
 __u64 packets;
 __u64 add_time;
 __u64 use_time;
};

struct xfrm_replay_state
{
 __u32 oseq;
 __u32 seq;
 __u32 bitmap;
};

struct xfrm_algo {
 char alg_name[64];
 int alg_key_len;
 char alg_key[0];
};

struct xfrm_stats {
 __u32 replay_window;
 __u32 replay;
 __u32 integrity_failed;
};

enum
{
 XFRM_POLICY_IN = 0,
 XFRM_POLICY_OUT = 1,
 XFRM_POLICY_FWD = 2,
 XFRM_POLICY_MAX = 3
};

enum
{
 XFRM_SHARE_ANY,
 XFRM_SHARE_SESSION,
 XFRM_SHARE_USER,
 XFRM_SHARE_UNIQUE
};


enum {
 XFRM_MSG_BASE = 0x10,

 XFRM_MSG_NEWSA = 0x10,

 XFRM_MSG_DELSA,

 XFRM_MSG_GETSA,


 XFRM_MSG_NEWPOLICY,

 XFRM_MSG_DELPOLICY,

 XFRM_MSG_GETPOLICY,


 XFRM_MSG_ALLOCSPI,

 XFRM_MSG_ACQUIRE,

 XFRM_MSG_EXPIRE,


 XFRM_MSG_UPDPOLICY,

 XFRM_MSG_UPDSA,


 XFRM_MSG_POLEXPIRE,


 XFRM_MSG_FLUSHSA,

 XFRM_MSG_FLUSHPOLICY,


 __XFRM_MSG_MAX
};




struct xfrm_user_tmpl {
 struct xfrm_id id;
 __u16 family;
 xfrm_address_t saddr;
 __u32 reqid;
 __u8 mode;
 __u8 share;
 __u8 optional;
 __u32 aalgos;
 __u32 ealgos;
 __u32 calgos;
};

struct xfrm_encap_tmpl {
 __u16 encap_type;
 __u16 encap_sport;
 __u16 encap_dport;
 xfrm_address_t encap_oa;
};


enum xfrm_attr_type_t {
 XFRMA_UNSPEC,
 XFRMA_ALG_AUTH,
 XFRMA_ALG_CRYPT,
 XFRMA_ALG_COMP,
 XFRMA_ENCAP,
 XFRMA_TMPL,
 XFRMA_SA,
 XFRMA_POLICY,
 __XFRMA_MAX


};

struct xfrm_usersa_info {
 struct xfrm_selector sel;
 struct xfrm_id id;
 xfrm_address_t saddr;
 struct xfrm_lifetime_cfg lft;
 struct xfrm_lifetime_cur curlft;
 struct xfrm_stats stats;
 __u32 seq;
 __u32 reqid;
 __u16 family;
 __u8 mode;
 __u8 replay_window;
 __u8 flags;



};

struct xfrm_usersa_id {
 xfrm_address_t daddr;
 __u32 spi;
 __u16 family;
 __u8 proto;
};

struct xfrm_userspi_info {
 struct xfrm_usersa_info info;
 __u32 min;
 __u32 max;
};

struct xfrm_userpolicy_info {
 struct xfrm_selector sel;
 struct xfrm_lifetime_cfg lft;
 struct xfrm_lifetime_cur curlft;
 __u32 priority;
 __u32 index;
 __u8 dir;
 __u8 action;


 __u8 flags;

 __u8 share;
};

struct xfrm_userpolicy_id {
 struct xfrm_selector sel;
 __u32 index;
 __u8 dir;
};

struct xfrm_user_acquire {
 struct xfrm_id id;
 xfrm_address_t saddr;
 struct xfrm_selector sel;
 struct xfrm_userpolicy_info policy;
 __u32 aalgos;
 __u32 ealgos;
 __u32 calgos;
 __u32 seq;
};

struct xfrm_user_expire {
 struct xfrm_usersa_info state;
 __u8 hard;
};

struct xfrm_user_polexpire {
 struct xfrm_userpolicy_info pol;
 __u8 hard;
};

struct xfrm_usersa_flush {
 __u8 proto;
};
# 6 "include/net/xfrm.h" 2




# 1 "include/linux/crypto.h" 1
# 63 "include/linux/crypto.h"
struct scatterlist;
struct crypto_tfm;

struct cipher_desc {
 struct crypto_tfm *tfm;
 void (*crfn)(void *ctx, u8 *dst, const u8 *src);
 unsigned int (*prfn)(const struct cipher_desc *desc, u8 *dst,
        const u8 *src, unsigned int nbytes);
 void *info;
};





struct cipher_alg {
 unsigned int cia_min_keysize;
 unsigned int cia_max_keysize;
 int (*cia_setkey)(void *ctx, const u8 *key,
                   unsigned int keylen, u32 *flags);
 void (*cia_encrypt)(void *ctx, u8 *dst, const u8 *src);
 void (*cia_decrypt)(void *ctx, u8 *dst, const u8 *src);

 unsigned int (*cia_encrypt_ecb)(const struct cipher_desc *desc,
     u8 *dst, const u8 *src,
     unsigned int nbytes);
 unsigned int (*cia_decrypt_ecb)(const struct cipher_desc *desc,
     u8 *dst, const u8 *src,
     unsigned int nbytes);
 unsigned int (*cia_encrypt_cbc)(const struct cipher_desc *desc,
     u8 *dst, const u8 *src,
     unsigned int nbytes);
 unsigned int (*cia_decrypt_cbc)(const struct cipher_desc *desc,
     u8 *dst, const u8 *src,
     unsigned int nbytes);
};

struct digest_alg {
 unsigned int dia_digestsize;
 void (*dia_init)(void *ctx);
 void (*dia_update)(void *ctx, const u8 *data, unsigned int len);
 void (*dia_final)(void *ctx, u8 *out);
 int (*dia_setkey)(void *ctx, const u8 *key,
                   unsigned int keylen, u32 *flags);
};

struct compress_alg {
 int (*coa_init)(void *ctx);
 void (*coa_exit)(void *ctx);
 int (*coa_compress)(void *ctx, const u8 *src, unsigned int slen,
                     u8 *dst, unsigned int *dlen);
 int (*coa_decompress)(void *ctx, const u8 *src, unsigned int slen,
                       u8 *dst, unsigned int *dlen);
};





struct crypto_alg {
 struct list_head cra_list;
 u32 cra_flags;
 unsigned int cra_blocksize;
 unsigned int cra_ctxsize;
 unsigned int cra_alignmask;
 const char cra_name[64];

 union {
  struct cipher_alg cipher;
  struct digest_alg digest;
  struct compress_alg compress;
 } cra_u;

 struct module *cra_module;
};




int crypto_register_alg(struct crypto_alg *alg);
int crypto_unregister_alg(struct crypto_alg *alg);





int crypto_alg_available(const char *name, u32 flags);
# 163 "include/linux/crypto.h"
struct cipher_tfm {
 void *cit_iv;
 unsigned int cit_ivsize;
 u32 cit_mode;
 int (*cit_setkey)(struct crypto_tfm *tfm,
                   const u8 *key, unsigned int keylen);
 int (*cit_encrypt)(struct crypto_tfm *tfm,
      struct scatterlist *dst,
      struct scatterlist *src,
      unsigned int nbytes);
 int (*cit_encrypt_iv)(struct crypto_tfm *tfm,
                       struct scatterlist *dst,
                       struct scatterlist *src,
                       unsigned int nbytes, u8 *iv);
 int (*cit_decrypt)(struct crypto_tfm *tfm,
      struct scatterlist *dst,
      struct scatterlist *src,
      unsigned int nbytes);
 int (*cit_decrypt_iv)(struct crypto_tfm *tfm,
      struct scatterlist *dst,
      struct scatterlist *src,
      unsigned int nbytes, u8 *iv);
 void (*cit_xor_block)(u8 *dst, const u8 *src);
};

struct digest_tfm {
 void (*dit_init)(struct crypto_tfm *tfm);
 void (*dit_update)(struct crypto_tfm *tfm,
                    struct scatterlist *sg, unsigned int nsg);
 void (*dit_final)(struct crypto_tfm *tfm, u8 *out);
 void (*dit_digest)(struct crypto_tfm *tfm, struct scatterlist *sg,
                    unsigned int nsg, u8 *out);
 int (*dit_setkey)(struct crypto_tfm *tfm,
                   const u8 *key, unsigned int keylen);

 void *dit_hmac_block;

};

struct compress_tfm {
 int (*cot_compress)(struct crypto_tfm *tfm,
                     const u8 *src, unsigned int slen,
                     u8 *dst, unsigned int *dlen);
 int (*cot_decompress)(struct crypto_tfm *tfm,
                       const u8 *src, unsigned int slen,
                       u8 *dst, unsigned int *dlen);
};





struct crypto_tfm {

 u32 crt_flags;

 union {
  struct cipher_tfm cipher;
  struct digest_tfm digest;
  struct compress_tfm compress;
 } crt_u;

 struct crypto_alg *__crt_alg;
};
# 241 "include/linux/crypto.h"
struct crypto_tfm *crypto_alloc_tfm(const char *alg_name, u32 tfm_flags);
void crypto_free_tfm(struct crypto_tfm *tfm);




static inline __attribute__((always_inline)) const char *crypto_tfm_alg_name(struct crypto_tfm *tfm)
{
 return tfm->__crt_alg->cra_name;
}

static inline __attribute__((always_inline)) const char *crypto_tfm_alg_modname(struct crypto_tfm *tfm)
{
 return ({ struct module *__mod = (tfm->__crt_alg->cra_module); __mod ? __mod->name : "kernel"; });
}

static inline __attribute__((always_inline)) u32 crypto_tfm_alg_type(struct crypto_tfm *tfm)
{
 return tfm->__crt_alg->cra_flags & 0x000000ff;
}

static inline __attribute__((always_inline)) unsigned int crypto_tfm_alg_min_keysize(struct crypto_tfm *tfm)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000001)!=0), 0)) __BUG(); } while(0);
 return tfm->__crt_alg->cra_u.cipher.cia_min_keysize;
}

static inline __attribute__((always_inline)) unsigned int crypto_tfm_alg_max_keysize(struct crypto_tfm *tfm)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000001)!=0), 0)) __BUG(); } while(0);
 return tfm->__crt_alg->cra_u.cipher.cia_max_keysize;
}

static inline __attribute__((always_inline)) unsigned int crypto_tfm_alg_ivsize(struct crypto_tfm *tfm)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000001)!=0), 0)) __BUG(); } while(0);
 return tfm->crt_u.cipher.cit_ivsize;
}

static inline __attribute__((always_inline)) unsigned int crypto_tfm_alg_blocksize(struct crypto_tfm *tfm)
{
 return tfm->__crt_alg->cra_blocksize;
}

static inline __attribute__((always_inline)) unsigned int crypto_tfm_alg_digestsize(struct crypto_tfm *tfm)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000002)!=0), 0)) __BUG(); } while(0);
 return tfm->__crt_alg->cra_u.digest.dia_digestsize;
}

static inline __attribute__((always_inline)) unsigned int crypto_tfm_alg_alignmask(struct crypto_tfm *tfm)
{
 return tfm->__crt_alg->cra_alignmask;
}

static inline __attribute__((always_inline)) void *crypto_tfm_ctx(struct crypto_tfm *tfm)
{
 return (void *)&tfm[1];
}




static inline __attribute__((always_inline)) void crypto_digest_init(struct crypto_tfm *tfm)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000002)!=0), 0)) __BUG(); } while(0);
 tfm->crt_u.digest.dit_init(tfm);
}

static inline __attribute__((always_inline)) void crypto_digest_update(struct crypto_tfm *tfm,
                                        struct scatterlist *sg,
                                        unsigned int nsg)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000002)!=0), 0)) __BUG(); } while(0);
 tfm->crt_u.digest.dit_update(tfm, sg, nsg);
}

static inline __attribute__((always_inline)) void crypto_digest_final(struct crypto_tfm *tfm, u8 *out)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000002)!=0), 0)) __BUG(); } while(0);
 tfm->crt_u.digest.dit_final(tfm, out);
}

static inline __attribute__((always_inline)) void crypto_digest_digest(struct crypto_tfm *tfm,
                                        struct scatterlist *sg,
                                        unsigned int nsg, u8 *out)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000002)!=0), 0)) __BUG(); } while(0);
 tfm->crt_u.digest.dit_digest(tfm, sg, nsg, out);
}

static inline __attribute__((always_inline)) int crypto_digest_setkey(struct crypto_tfm *tfm,
                                       const u8 *key, unsigned int keylen)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000002)!=0), 0)) __BUG(); } while(0);
 if (tfm->crt_u.digest.dit_setkey == ((void *)0))
  return -38;
 return tfm->crt_u.digest.dit_setkey(tfm, key, keylen);
}

static inline __attribute__((always_inline)) int crypto_cipher_setkey(struct crypto_tfm *tfm,
                                       const u8 *key, unsigned int keylen)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000001)!=0), 0)) __BUG(); } while(0);
 return tfm->crt_u.cipher.cit_setkey(tfm, key, keylen);
}

static inline __attribute__((always_inline)) int crypto_cipher_encrypt(struct crypto_tfm *tfm,
                                        struct scatterlist *dst,
                                        struct scatterlist *src,
                                        unsigned int nbytes)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000001)!=0), 0)) __BUG(); } while(0);
 return tfm->crt_u.cipher.cit_encrypt(tfm, dst, src, nbytes);
}

static inline __attribute__((always_inline)) int crypto_cipher_encrypt_iv(struct crypto_tfm *tfm,
                                           struct scatterlist *dst,
                                           struct scatterlist *src,
                                           unsigned int nbytes, u8 *iv)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000001)!=0), 0)) __BUG(); } while(0);
 do { if (__builtin_expect(!!((tfm->crt_u.cipher.cit_mode == 0x00000001)!=0), 0)) __BUG(); } while(0);
 return tfm->crt_u.cipher.cit_encrypt_iv(tfm, dst, src, nbytes, iv);
}

static inline __attribute__((always_inline)) int crypto_cipher_decrypt(struct crypto_tfm *tfm,
                                        struct scatterlist *dst,
                                        struct scatterlist *src,
                                        unsigned int nbytes)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000001)!=0), 0)) __BUG(); } while(0);
 return tfm->crt_u.cipher.cit_decrypt(tfm, dst, src, nbytes);
}

static inline __attribute__((always_inline)) int crypto_cipher_decrypt_iv(struct crypto_tfm *tfm,
                                           struct scatterlist *dst,
                                           struct scatterlist *src,
                                           unsigned int nbytes, u8 *iv)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000001)!=0), 0)) __BUG(); } while(0);
 do { if (__builtin_expect(!!((tfm->crt_u.cipher.cit_mode == 0x00000001)!=0), 0)) __BUG(); } while(0);
 return tfm->crt_u.cipher.cit_decrypt_iv(tfm, dst, src, nbytes, iv);
}

static inline __attribute__((always_inline)) void crypto_cipher_set_iv(struct crypto_tfm *tfm,
                                        const u8 *src, unsigned int len)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000001)!=0), 0)) __BUG(); } while(0);
 __memcpy(tfm->crt_u.cipher.cit_iv,src,len);
}

static inline __attribute__((always_inline)) void crypto_cipher_get_iv(struct crypto_tfm *tfm,
                                        u8 *dst, unsigned int len)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000001)!=0), 0)) __BUG(); } while(0);
 __memcpy(dst,tfm->crt_u.cipher.cit_iv,len);
}

static inline __attribute__((always_inline)) int crypto_comp_compress(struct crypto_tfm *tfm,
                                       const u8 *src, unsigned int slen,
                                       u8 *dst, unsigned int *dlen)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000004)!=0), 0)) __BUG(); } while(0);
 return tfm->crt_u.compress.cot_compress(tfm, src, slen, dst, dlen);
}

static inline __attribute__((always_inline)) int crypto_comp_decompress(struct crypto_tfm *tfm,
                                         const u8 *src, unsigned int slen,
                                         u8 *dst, unsigned int *dlen)
{
 do { if (__builtin_expect(!!((crypto_tfm_alg_type(tfm) != 0x00000004)!=0), 0)) __BUG(); } while(0);
 return tfm->crt_u.compress.cot_decompress(tfm, src, slen, dst, dlen);
}





void crypto_hmac_init(struct crypto_tfm *tfm, u8 *key, unsigned int *keylen);
void crypto_hmac_update(struct crypto_tfm *tfm,
                        struct scatterlist *sg, unsigned int nsg);
void crypto_hmac_final(struct crypto_tfm *tfm, u8 *key,
                       unsigned int *keylen, u8 *out);
void crypto_hmac(struct crypto_tfm *tfm, u8 *key, unsigned int *keylen,
                 struct scatterlist *sg, unsigned int nsg, u8 *out);
# 11 "include/net/xfrm.h" 2
# 22 "include/net/xfrm.h"
extern struct semaphore xfrm_cfg_sem;
# 86 "include/net/xfrm.h"
struct xfrm_state
{

 struct list_head bydst;
 struct list_head byspi;

 atomic_t refcnt;
 spinlock_t lock;

 struct xfrm_id id;
 struct xfrm_selector sel;


 struct {
  u8 state;
  u8 dying;
  u32 seq;
 } km;


 struct {
  u32 reqid;
  u8 mode;
  u8 replay_window;
  u8 aalgo, ealgo, calgo;
  u8 flags;
  u16 family;
  xfrm_address_t saddr;
  int header_len;
  int trailer_len;
 } props;

 struct xfrm_lifetime_cfg lft;


 struct xfrm_algo *aalg;
 struct xfrm_algo *ealg;
 struct xfrm_algo *calg;


 struct xfrm_encap_tmpl *encap;


 struct xfrm_state *tunnel;


 atomic_t tunnel_users;


 struct xfrm_replay_state replay;


 struct xfrm_stats stats;

 struct xfrm_lifetime_cur curlft;
 struct timer_list timer;



 struct xfrm_type *type;



 void *data;
};

enum {
 XFRM_STATE_VOID,
 XFRM_STATE_ACQ,
 XFRM_STATE_VALID,
 XFRM_STATE_ERROR,
 XFRM_STATE_EXPIRED,
 XFRM_STATE_DEAD
};


struct km_event
{
 union {
  u32 hard;
  u32 proto;
  u32 byid;
 } data;

 u32 seq;
 u32 pid;
 u32 event;
};

struct xfrm_type;
struct xfrm_dst;
struct xfrm_policy_afinfo {
 unsigned short family;
 rwlock_t lock;
 struct xfrm_type_map *type_map;
 struct dst_ops *dst_ops;
 void (*garbage_collect)(void);
 int (*dst_lookup)(struct xfrm_dst **dst, struct flowi *fl);
 struct dst_entry *(*find_bundle)(struct flowi *fl, struct xfrm_policy *policy);
 int (*bundle_create)(struct xfrm_policy *policy,
       struct xfrm_state **xfrm,
       int nx,
       struct flowi *fl,
       struct dst_entry **dst_p);
 void (*decode_session)(struct sk_buff *skb,
        struct flowi *fl);
};

extern int xfrm_policy_register_afinfo(struct xfrm_policy_afinfo *afinfo);
extern int xfrm_policy_unregister_afinfo(struct xfrm_policy_afinfo *afinfo);
extern void km_policy_notify(struct xfrm_policy *xp, int dir, struct km_event *c);
extern void km_state_notify(struct xfrm_state *x, struct km_event *c);



struct xfrm_tmpl;
struct xfrm_state_afinfo {
 unsigned short family;
 rwlock_t lock;
 struct list_head *state_bydst;
 struct list_head *state_byspi;
 int (*init_flags)(struct xfrm_state *x);
 void (*init_tempsel)(struct xfrm_state *x, struct flowi *fl,
      struct xfrm_tmpl *tmpl,
      xfrm_address_t *daddr, xfrm_address_t *saddr);
 struct xfrm_state *(*state_lookup)(xfrm_address_t *daddr, u32 spi, u8 proto);
 struct xfrm_state *(*find_acq)(u8 mode, u32 reqid, u8 proto,
          xfrm_address_t *daddr, xfrm_address_t *saddr,
          int create);
};

extern int xfrm_state_register_afinfo(struct xfrm_state_afinfo *afinfo);
extern int xfrm_state_unregister_afinfo(struct xfrm_state_afinfo *afinfo);

extern void xfrm_state_delete_tunnel(struct xfrm_state *x);

struct xfrm_decap_state;
struct xfrm_type
{
 char *description;
 struct module *owner;
 __u8 proto;

 int (*init_state)(struct xfrm_state *x);
 void (*destructor)(struct xfrm_state *);
 int (*input)(struct xfrm_state *, struct xfrm_decap_state *, struct sk_buff *skb);
 int (*post_input)(struct xfrm_state *, struct xfrm_decap_state *, struct sk_buff *skb);
 int (*output)(struct xfrm_state *, struct sk_buff *pskb);

 u32 (*get_max_size)(struct xfrm_state *, int size);
};

struct xfrm_type_map {
 rwlock_t lock;
 struct xfrm_type *map[256];
};

extern int xfrm_register_type(struct xfrm_type *type, unsigned short family);
extern int xfrm_unregister_type(struct xfrm_type *type, unsigned short family);
extern struct xfrm_type *xfrm_get_type(u8 proto, unsigned short family);
extern void xfrm_put_type(struct xfrm_type *type);

struct xfrm_tmpl
{






 struct xfrm_id id;


 xfrm_address_t saddr;

 __u32 reqid;


 __u8 mode;


 __u8 share;


 __u8 optional;


 __u32 aalgos;
 __u32 ealgos;
 __u32 calgos;
};



struct xfrm_policy
{
 struct xfrm_policy *next;
 struct list_head list;


 rwlock_t lock;
 atomic_t refcnt;
 struct timer_list timer;

 u32 priority;
 u32 index;
 struct xfrm_selector selector;
 struct xfrm_lifetime_cfg lft;
 struct xfrm_lifetime_cur curlft;
 struct dst_entry *bundles;
 __u16 family;
 __u8 action;
 __u8 flags;
 __u8 dead;
 __u8 xfrm_nr;
 struct xfrm_tmpl xfrm_vec[4];
};



struct xfrm_mgr
{
 struct list_head list;
 char *id;
 int (*notify)(struct xfrm_state *x, struct km_event *c);
 int (*acquire)(struct xfrm_state *x, struct xfrm_tmpl *, struct xfrm_policy *xp, int dir);
 struct xfrm_policy *(*compile_policy)(u16 family, int opt, u8 *data, int len, int *dir);
 int (*new_mapping)(struct xfrm_state *x, xfrm_address_t *ipaddr, u16 sport);
 int (*notify_policy)(struct xfrm_policy *x, int dir, struct km_event *c);
};

extern int xfrm_register_km(struct xfrm_mgr *km);
extern int xfrm_unregister_km(struct xfrm_mgr *km);


extern struct xfrm_policy *xfrm_policy_list[XFRM_POLICY_MAX*2];

static inline __attribute__((always_inline)) void xfrm_pol_hold(struct xfrm_policy *policy)
{
 if (__builtin_expect(!!(policy != ((void *)0)), 1))
  atomic_inc(&policy->refcnt);
}

extern void __xfrm_policy_destroy(struct xfrm_policy *policy);

static inline __attribute__((always_inline)) void xfrm_pol_put(struct xfrm_policy *policy)
{
 if (atomic_dec_and_test(&policy->refcnt))
  __xfrm_policy_destroy(policy);
}



static __inline__ __attribute__((always_inline))
unsigned __xfrm4_dst_hash(xfrm_address_t *addr)
{
 unsigned h;
 h = (__builtin_constant_p((__u32)(( __u32)(__be32)(addr->a4))) ? ({ __u32 __x = ((( __u32)(__be32)(addr->a4))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(addr->a4))));
 h = (h ^ (h>>16)) % 1024;
 return h;
}

static __inline__ __attribute__((always_inline))
unsigned __xfrm6_dst_hash(xfrm_address_t *addr)
{
 unsigned h;
 h = (__builtin_constant_p((__u32)(( __u32)(__be32)(addr->a6[2]^addr->a6[3]))) ? ({ __u32 __x = ((( __u32)(__be32)(addr->a6[2]^addr->a6[3]))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(addr->a6[2]^addr->a6[3]))));
 h = (h ^ (h>>16)) % 1024;
 return h;
}

static __inline__ __attribute__((always_inline))
unsigned xfrm_dst_hash(xfrm_address_t *addr, unsigned short family)
{
 switch (family) {
 case 2:
  return __xfrm4_dst_hash(addr);
 case 10:
  return __xfrm6_dst_hash(addr);
 }
 return 0;
}

static __inline__ __attribute__((always_inline))
unsigned __xfrm4_spi_hash(xfrm_address_t *addr, u32 spi, u8 proto)
{
 unsigned h;
 h = (__builtin_constant_p((__u32)(( __u32)(__be32)(addr->a4^spi^proto))) ? ({ __u32 __x = ((( __u32)(__be32)(addr->a4^spi^proto))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(addr->a4^spi^proto))));
 h = (h ^ (h>>10) ^ (h>>20)) % 1024;
 return h;
}

static __inline__ __attribute__((always_inline))
unsigned __xfrm6_spi_hash(xfrm_address_t *addr, u32 spi, u8 proto)
{
 unsigned h;
 h = (__builtin_constant_p((__u32)(( __u32)(__be32)(addr->a6[2]^addr->a6[3]^spi^proto))) ? ({ __u32 __x = ((( __u32)(__be32)(addr->a6[2]^addr->a6[3]^spi^proto))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(addr->a6[2]^addr->a6[3]^spi^proto))));
 h = (h ^ (h>>10) ^ (h>>20)) % 1024;
 return h;
}

static __inline__ __attribute__((always_inline))
unsigned xfrm_spi_hash(xfrm_address_t *addr, u32 spi, u8 proto, unsigned short family)
{
 switch (family) {
 case 2:
  return __xfrm4_spi_hash(addr, spi, proto);
 case 10:
  return __xfrm6_spi_hash(addr, spi, proto);
 }
 return 0;
}

extern void __xfrm_state_destroy(struct xfrm_state *);

static inline __attribute__((always_inline)) void xfrm_state_put(struct xfrm_state *x)
{
 if (atomic_dec_and_test(&x->refcnt))
  __xfrm_state_destroy(x);
}

static inline __attribute__((always_inline)) void xfrm_state_hold(struct xfrm_state *x)
{
 atomic_inc(&x->refcnt);
}

static __inline__ __attribute__((always_inline)) int addr_match(void *token1, void *token2, int prefixlen)
{
 __u32 *a1 = token1;
 __u32 *a2 = token2;
 int pdw;
 int pbi;

 pdw = prefixlen >> 5;
 pbi = prefixlen & 0x1f;

 if (pdw)
  if (__builtin_memcmp(a1, a2, pdw << 2))
   return 0;

 if (pbi) {
  __u32 mask;

  mask = (( __be32)(__builtin_constant_p((__u32)(((0xffffffff) << (32 - pbi)))) ? ({ __u32 __x = ((((0xffffffff) << (32 - pbi)))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((((0xffffffff) << (32 - pbi))))));

  if ((a1[pdw] ^ a2[pdw]) & mask)
   return 0;
 }

 return 1;
}

static __inline__ __attribute__((always_inline))
u16 xfrm_flowi_sport(struct flowi *fl)
{
 u16 port;
 switch(fl->proto) {
 case IPPROTO_TCP:
 case IPPROTO_UDP:
 case IPPROTO_SCTP:
  port = fl->uli_u.ports.sport;
  break;
 case IPPROTO_ICMP:
 case 58:
  port = (( __be16)(__builtin_constant_p((__u16)((fl->uli_u.icmpt.type))) ? ({ __u16 __x = (((fl->uli_u.icmpt.type))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((fl->uli_u.icmpt.type)))));
  break;
 default:
  port = 0;
 }
 return port;
}

static __inline__ __attribute__((always_inline))
u16 xfrm_flowi_dport(struct flowi *fl)
{
 u16 port;
 switch(fl->proto) {
 case IPPROTO_TCP:
 case IPPROTO_UDP:
 case IPPROTO_SCTP:
  port = fl->uli_u.ports.dport;
  break;
 case IPPROTO_ICMP:
 case 58:
  port = (( __be16)(__builtin_constant_p((__u16)((fl->uli_u.icmpt.code))) ? ({ __u16 __x = (((fl->uli_u.icmpt.code))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((fl->uli_u.icmpt.code)))));
  break;
 default:
  port = 0;
 }
 return port;
}

static inline __attribute__((always_inline)) int
__xfrm4_selector_match(struct xfrm_selector *sel, struct flowi *fl)
{
 return addr_match(&fl->nl_u.ip4_u.daddr, &sel->daddr, sel->prefixlen_d) &&
  addr_match(&fl->nl_u.ip4_u.saddr, &sel->saddr, sel->prefixlen_s) &&
  !((xfrm_flowi_dport(fl) ^ sel->dport) & sel->dport_mask) &&
  !((xfrm_flowi_sport(fl) ^ sel->sport) & sel->sport_mask) &&
  (fl->proto == sel->proto || !sel->proto) &&
  (fl->oif == sel->ifindex || !sel->ifindex);
}

static inline __attribute__((always_inline)) int
__xfrm6_selector_match(struct xfrm_selector *sel, struct flowi *fl)
{
 return addr_match(&fl->nl_u.ip6_u.daddr, &sel->daddr, sel->prefixlen_d) &&
  addr_match(&fl->nl_u.ip6_u.saddr, &sel->saddr, sel->prefixlen_s) &&
  !((xfrm_flowi_dport(fl) ^ sel->dport) & sel->dport_mask) &&
  !((xfrm_flowi_sport(fl) ^ sel->sport) & sel->sport_mask) &&
  (fl->proto == sel->proto || !sel->proto) &&
  (fl->oif == sel->ifindex || !sel->ifindex);
}

static inline __attribute__((always_inline)) int
xfrm_selector_match(struct xfrm_selector *sel, struct flowi *fl,
      unsigned short family)
{
 switch (family) {
 case 2:
  return __xfrm4_selector_match(sel, fl);
 case 10:
  return __xfrm6_selector_match(sel, fl);
 }
 return 0;
}
# 524 "include/net/xfrm.h"
struct xfrm_dst
{
 union {
  struct xfrm_dst *next;
  struct dst_entry dst;
  struct rtable rt;
  struct rt6_info rt6;
 } u;
 struct dst_entry *route;
 u32 route_mtu_cached;
 u32 child_mtu_cached;
 u32 route_cookie;
 u32 path_cookie;
};

static inline __attribute__((always_inline)) void xfrm_dst_destroy(struct xfrm_dst *xdst)
{
 dst_release(xdst->route);
 if (__builtin_expect(!!(xdst->u.dst.xfrm), 1))
  xfrm_state_put(xdst->u.dst.xfrm);
}

extern void xfrm_dst_ifdown(struct dst_entry *dst, struct net_device *dev);





struct xfrm_decap_state {
 char decap_data[20];
 __u16 decap_type;
};

struct sec_decap_state {
 struct xfrm_state *xvec;
 struct xfrm_decap_state decap;
};

struct sec_path
{
 atomic_t refcnt;
 int len;
 struct sec_decap_state x[4];
};

static inline __attribute__((always_inline)) struct sec_path *
secpath_get(struct sec_path *sp)
{
 if (sp)
  atomic_inc(&sp->refcnt);
 return sp;
}

extern void __secpath_destroy(struct sec_path *sp);

static inline __attribute__((always_inline)) void
secpath_put(struct sec_path *sp)
{
 if (sp && atomic_dec_and_test(&sp->refcnt))
  __secpath_destroy(sp);
}

extern struct sec_path *secpath_dup(struct sec_path *src);

static inline __attribute__((always_inline)) void
secpath_reset(struct sk_buff *skb)
{

 secpath_put(skb->sp);
 skb->sp = ((void *)0);

}

static inline __attribute__((always_inline)) int
__xfrm4_state_addr_cmp(struct xfrm_tmpl *tmpl, struct xfrm_state *x)
{
 return (tmpl->saddr.a4 &&
   tmpl->saddr.a4 != x->props.saddr.a4);
}

static inline __attribute__((always_inline)) int
__xfrm6_state_addr_cmp(struct xfrm_tmpl *tmpl, struct xfrm_state *x)
{
 return (!ipv6_addr_any((struct in6_addr*)&tmpl->saddr) &&
   ipv6_addr_cmp((struct in6_addr *)&tmpl->saddr, (struct in6_addr*)&x->props.saddr));
}

static inline __attribute__((always_inline)) int
xfrm_state_addr_cmp(struct xfrm_tmpl *tmpl, struct xfrm_state *x, unsigned short family)
{
 switch (family) {
 case 2:
  return __xfrm4_state_addr_cmp(tmpl, x);
 case 10:
  return __xfrm6_state_addr_cmp(tmpl, x);
 }
 return !0;
}



extern int __xfrm_policy_check(struct sock *, int dir, struct sk_buff *skb, unsigned short family);

static inline __attribute__((always_inline)) int xfrm_policy_check(struct sock *sk, int dir, struct sk_buff *skb, unsigned short family)
{
 if (sk && sk->sk_policy[XFRM_POLICY_IN])
  return __xfrm_policy_check(sk, dir, skb, family);

 return (!xfrm_policy_list[dir] && !skb->sp) ||
  (skb->dst->flags & 4) ||
  __xfrm_policy_check(sk, dir, skb, family);
}

static inline __attribute__((always_inline)) int xfrm4_policy_check(struct sock *sk, int dir, struct sk_buff *skb)
{
 return xfrm_policy_check(sk, dir, skb, 2);
}

static inline __attribute__((always_inline)) int xfrm6_policy_check(struct sock *sk, int dir, struct sk_buff *skb)
{
 return xfrm_policy_check(sk, dir, skb, 10);
}


extern int __xfrm_route_forward(struct sk_buff *skb, unsigned short family);

static inline __attribute__((always_inline)) int xfrm_route_forward(struct sk_buff *skb, unsigned short family)
{
 return !xfrm_policy_list[XFRM_POLICY_OUT] ||
  (skb->dst->flags & 2) ||
  __xfrm_route_forward(skb, family);
}

static inline __attribute__((always_inline)) int xfrm4_route_forward(struct sk_buff *skb)
{
 return xfrm_route_forward(skb, 2);
}

static inline __attribute__((always_inline)) int xfrm6_route_forward(struct sk_buff *skb)
{
 return xfrm_route_forward(skb, 10);
}

extern int __xfrm_sk_clone_policy(struct sock *sk);

static inline __attribute__((always_inline)) int xfrm_sk_clone_policy(struct sock *sk)
{
 if (__builtin_expect(!!(sk->sk_policy[0] || sk->sk_policy[1]), 0))
  return __xfrm_sk_clone_policy(sk);
 return 0;
}

extern int xfrm_policy_delete(struct xfrm_policy *pol, int dir);

static inline __attribute__((always_inline)) void xfrm_sk_free_policy(struct sock *sk)
{
 if (__builtin_expect(!!(sk->sk_policy[0] != ((void *)0)), 0)) {
  xfrm_policy_delete(sk->sk_policy[0], XFRM_POLICY_MAX);
  sk->sk_policy[0] = ((void *)0);
 }
 if (__builtin_expect(!!(sk->sk_policy[1] != ((void *)0)), 0)) {
  xfrm_policy_delete(sk->sk_policy[1], XFRM_POLICY_MAX+1);
  sk->sk_policy[1] = ((void *)0);
 }
}
# 710 "include/net/xfrm.h"
static __inline__ __attribute__((always_inline))
xfrm_address_t *xfrm_flowi_daddr(struct flowi *fl, unsigned short family)
{
 switch (family){
 case 2:
  return (xfrm_address_t *)&fl->nl_u.ip4_u.daddr;
 case 10:
  return (xfrm_address_t *)&fl->nl_u.ip6_u.daddr;
 }
 return ((void *)0);
}

static __inline__ __attribute__((always_inline))
xfrm_address_t *xfrm_flowi_saddr(struct flowi *fl, unsigned short family)
{
 switch (family){
 case 2:
  return (xfrm_address_t *)&fl->nl_u.ip4_u.saddr;
 case 10:
  return (xfrm_address_t *)&fl->nl_u.ip6_u.saddr;
 }
 return ((void *)0);
}

static __inline__ __attribute__((always_inline)) int
__xfrm4_state_addr_check(struct xfrm_state *x,
    xfrm_address_t *daddr, xfrm_address_t *saddr)
{
 if (daddr->a4 == x->id.daddr.a4 &&
     (saddr->a4 == x->props.saddr.a4 || !saddr->a4 || !x->props.saddr.a4))
  return 1;
 return 0;
}

static __inline__ __attribute__((always_inline)) int
__xfrm6_state_addr_check(struct xfrm_state *x,
    xfrm_address_t *daddr, xfrm_address_t *saddr)
{
 if (!ipv6_addr_cmp((struct in6_addr *)daddr, (struct in6_addr *)&x->id.daddr) &&
     (!ipv6_addr_cmp((struct in6_addr *)saddr, (struct in6_addr *)&x->props.saddr)||
      ipv6_addr_any((struct in6_addr *)saddr) ||
      ipv6_addr_any((struct in6_addr *)&x->props.saddr)))
  return 1;
 return 0;
}

static __inline__ __attribute__((always_inline)) int
xfrm_state_addr_check(struct xfrm_state *x,
        xfrm_address_t *daddr, xfrm_address_t *saddr,
        unsigned short family)
{
 switch (family) {
 case 2:
  return __xfrm4_state_addr_check(x, daddr, saddr);
 case 10:
  return __xfrm6_state_addr_check(x, daddr, saddr);
 }
 return 0;
}

static inline __attribute__((always_inline)) int xfrm_state_kern(struct xfrm_state *x)
{
 return ((&x->tunnel_users)->counter);
}




struct xfrm_algo_auth_info {
 u16 icv_truncbits;
 u16 icv_fullbits;
};

struct xfrm_algo_encr_info {
 u16 blockbits;
 u16 defkeybits;
};

struct xfrm_algo_comp_info {
 u16 threshold;
};

struct xfrm_algo_desc {
 char *name;
 u8 available:1;
 union {
  struct xfrm_algo_auth_info auth;
  struct xfrm_algo_encr_info encr;
  struct xfrm_algo_comp_info comp;
 } uinfo;
 struct sadb_alg desc;
};


struct xfrm_tunnel {
 int (*handler)(struct sk_buff *skb);
 void (*err_handler)(struct sk_buff *skb, __u32 info);
};

struct xfrm6_tunnel {
 int (*handler)(struct sk_buff **pskb, unsigned int *nhoffp);
 void (*err_handler)(struct sk_buff *skb, struct inet6_skb_parm *opt,
       int type, int code, int offset, __u32 info);
};

extern void xfrm_init(void);
extern void xfrm4_init(void);
extern void xfrm6_init(void);
extern void xfrm6_fini(void);
extern void xfrm_state_init(void);
extern void xfrm4_state_init(void);
extern void xfrm4_state_fini(void);
extern void xfrm6_state_init(void);
extern void xfrm6_state_fini(void);

extern int xfrm_state_walk(u8 proto, int (*func)(struct xfrm_state *, int, void*), void *);
extern struct xfrm_state *xfrm_state_alloc(void);
extern struct xfrm_state *xfrm_state_find(xfrm_address_t *daddr, xfrm_address_t *saddr,
       struct flowi *fl, struct xfrm_tmpl *tmpl,
       struct xfrm_policy *pol, int *err,
       unsigned short family);
extern int xfrm_state_check_expire(struct xfrm_state *x);
extern void xfrm_state_insert(struct xfrm_state *x);
extern int xfrm_state_add(struct xfrm_state *x);
extern int xfrm_state_update(struct xfrm_state *x);
extern struct xfrm_state *xfrm_state_lookup(xfrm_address_t *daddr, u32 spi, u8 proto, unsigned short family);
extern struct xfrm_state *xfrm_find_acq_byseq(u32 seq);
extern int xfrm_state_delete(struct xfrm_state *x);
extern void xfrm_state_flush(u8 proto);
extern int xfrm_replay_check(struct xfrm_state *x, u32 seq);
extern void xfrm_replay_advance(struct xfrm_state *x, u32 seq);
extern int xfrm_state_check(struct xfrm_state *x, struct sk_buff *skb);
extern int xfrm_state_mtu(struct xfrm_state *x, int mtu);
extern int xfrm_init_state(struct xfrm_state *x);
extern int xfrm4_rcv(struct sk_buff *skb);
extern int xfrm4_output(struct sk_buff *skb);
extern int xfrm4_tunnel_register(struct xfrm_tunnel *handler);
extern int xfrm4_tunnel_deregister(struct xfrm_tunnel *handler);
extern int xfrm6_rcv_spi(struct sk_buff **pskb, unsigned int *nhoffp, u32 spi);
extern int xfrm6_rcv(struct sk_buff **pskb, unsigned int *nhoffp);
extern int xfrm6_tunnel_register(struct xfrm6_tunnel *handler);
extern int xfrm6_tunnel_deregister(struct xfrm6_tunnel *handler);
extern u32 xfrm6_tunnel_alloc_spi(xfrm_address_t *saddr);
extern void xfrm6_tunnel_free_spi(xfrm_address_t *saddr);
extern u32 xfrm6_tunnel_spi_lookup(xfrm_address_t *saddr);
extern int xfrm6_output(struct sk_buff *skb);


extern int xfrm4_rcv_encap(struct sk_buff *skb, __u16 encap_type);
extern int xfrm_user_policy(struct sock *sk, int optname, u8 *optval, int optlen);
extern int xfrm_dst_lookup(struct xfrm_dst **dst, struct flowi *fl, unsigned short family);
# 879 "include/net/xfrm.h"
struct xfrm_policy *xfrm_policy_alloc(int gfp);
extern int xfrm_policy_walk(int (*func)(struct xfrm_policy *, int, int, void*), void *);
int xfrm_policy_insert(int dir, struct xfrm_policy *policy, int excl);
struct xfrm_policy *xfrm_policy_bysel(int dir, struct xfrm_selector *sel,
          int delete);
struct xfrm_policy *xfrm_policy_byid(int dir, u32 id, int delete);
void xfrm_policy_flush(void);
u32 xfrm_get_acqseq(void);
void xfrm_alloc_spi(struct xfrm_state *x, u32 minspi, u32 maxspi);
struct xfrm_state * xfrm_find_acq(u8 mode, u32 reqid, u8 proto,
      xfrm_address_t *daddr, xfrm_address_t *saddr,
      int create, unsigned short family);
extern void xfrm_policy_flush(void);
extern int xfrm_sk_policy_insert(struct sock *sk, int dir, struct xfrm_policy *pol);
extern int xfrm_flush_bundles(void);
extern int xfrm_bundle_ok(struct xfrm_dst *xdst, struct flowi *fl, int family);
extern void xfrm_init_pmtu(struct dst_entry *dst);

extern wait_queue_head_t km_waitq;
extern int km_new_mapping(struct xfrm_state *x, xfrm_address_t *ipaddr, u16 sport);
extern void km_policy_expired(struct xfrm_policy *pol, int dir, int hard);

extern void xfrm_input_init(void);
extern int xfrm_parse_spi(struct sk_buff *skb, u8 nexthdr, u32 *spi, u32 *seq);

extern void xfrm_probe_algs(void);
extern int xfrm_count_auth_supported(void);
extern int xfrm_count_enc_supported(void);
extern struct xfrm_algo_desc *xfrm_aalg_get_byidx(unsigned int idx);
extern struct xfrm_algo_desc *xfrm_ealg_get_byidx(unsigned int idx);
extern struct xfrm_algo_desc *xfrm_aalg_get_byid(int alg_id);
extern struct xfrm_algo_desc *xfrm_ealg_get_byid(int alg_id);
extern struct xfrm_algo_desc *xfrm_calg_get_byid(int alg_id);
extern struct xfrm_algo_desc *xfrm_aalg_get_byname(char *name, int probe);
extern struct xfrm_algo_desc *xfrm_ealg_get_byname(char *name, int probe);
extern struct xfrm_algo_desc *xfrm_calg_get_byname(char *name, int probe);

struct crypto_tfm;
typedef void (icv_update_fn_t)(struct crypto_tfm *, struct scatterlist *, unsigned int);

extern void skb_icv_walk(const struct sk_buff *skb, struct crypto_tfm *tfm,
    int offset, int len, icv_update_fn_t icv_update);

static inline __attribute__((always_inline)) int xfrm_addr_cmp(xfrm_address_t *a, xfrm_address_t *b,
    int family)
{
 switch (family) {
 default:
 case 2:
  return a->a4 - b->a4;
 case 10:
  return ipv6_addr_cmp((struct in6_addr *)a,
         (struct in6_addr *)b);
 }
}
# 58 "net/ipv6/tcp_ipv6.c" 2






# 1 "include/linux/proc_fs.h" 1
# 23 "include/linux/proc_fs.h"
enum {
 PROC_ROOT_INO = 1,
};
# 44 "include/linux/proc_fs.h"
typedef int (read_proc_t)(char *page, char **start, off_t off,
     int count, int *eof, void *data);
typedef int (write_proc_t)(struct file *file, const char *buffer,
      unsigned long count, void *data);
typedef int (get_info_t)(char *, char **, off_t, int);

struct proc_dir_entry {
 unsigned int low_ino;
 unsigned short namelen;
 const char *name;
 mode_t mode;
 nlink_t nlink;
 uid_t uid;
 gid_t gid;
 unsigned long size;
 struct inode_operations * proc_iops;
 struct file_operations * proc_fops;
 get_info_t *get_info;
 struct module *owner;
 struct proc_dir_entry *next, *parent, *subdir;
 void *data;
 read_proc_t *read_proc;
 write_proc_t *write_proc;
 atomic_t count;
 int deleted;
};

struct kcore_list {
 struct kcore_list *next;
 unsigned long addr;
 size_t size;
};

struct vmcore {
 struct list_head list;
 unsigned long long paddr;
 unsigned long size;
 loff_t offset;
};



extern struct proc_dir_entry proc_root;
extern struct proc_dir_entry *proc_root_fs;
extern struct proc_dir_entry *proc_net;
extern struct proc_dir_entry *proc_net_stat;
extern struct proc_dir_entry *proc_bus;
extern struct proc_dir_entry *proc_root_driver;
extern struct proc_dir_entry *proc_root_kcore;

extern void proc_root_init(void);
extern void proc_misc_init(void);

struct mm_struct;

struct dentry *proc_pid_lookup(struct inode *dir, struct dentry * dentry, struct nameidata *);
struct dentry *proc_pid_unhash(struct task_struct *p);
void proc_pid_flush(struct dentry *proc_dentry);
int proc_pid_readdir(struct file * filp, void * dirent, filldir_t filldir);
unsigned long task_vsize(struct mm_struct *);
int task_statm(struct mm_struct *, int *, int *, int *, int *);
char *task_mem(struct mm_struct *, char *);

extern struct proc_dir_entry *create_proc_entry(const char *name, mode_t mode,
      struct proc_dir_entry *parent);
extern void remove_proc_entry(const char *name, struct proc_dir_entry *parent);

extern struct vfsmount *proc_mnt;
extern int proc_fill_super(struct super_block *,void *,int);
extern struct inode *proc_get_inode(struct super_block *, unsigned int, struct proc_dir_entry *);

extern int proc_match(int, const char *,struct proc_dir_entry *);
# 124 "include/linux/proc_fs.h"
extern int proc_readdir(struct file *, void *, filldir_t);
extern struct dentry *proc_lookup(struct inode *, struct dentry *, struct nameidata *);

extern struct file_operations proc_kcore_operations;
extern struct file_operations proc_kmsg_operations;
extern struct file_operations ppc_htab_operations;




struct tty_driver;
extern void proc_tty_init(void);
extern void proc_tty_register_driver(struct tty_driver *driver);
extern void proc_tty_unregister_driver(struct tty_driver *driver);




struct device_node;
extern void proc_device_tree_init(void);



static inline __attribute__((always_inline)) void proc_device_tree_add_node(struct device_node *np, struct proc_dir_entry *pde)
{
 return;
}


extern struct proc_dir_entry *proc_symlink(const char *,
  struct proc_dir_entry *, const char *);
extern struct proc_dir_entry *proc_mkdir(const char *,struct proc_dir_entry *);
extern struct proc_dir_entry *proc_mkdir_mode(const char *name, mode_t mode,
   struct proc_dir_entry *parent);

static inline __attribute__((always_inline)) struct proc_dir_entry *create_proc_read_entry(const char *name,
 mode_t mode, struct proc_dir_entry *base,
 read_proc_t *read_proc, void * data)
{
 struct proc_dir_entry *res=create_proc_entry(name,mode,base);
 if (res) {
  res->read_proc=read_proc;
  res->data=data;
 }
 return res;
}

static inline __attribute__((always_inline)) struct proc_dir_entry *create_proc_info_entry(const char *name,
 mode_t mode, struct proc_dir_entry *base, get_info_t *get_info)
{
 struct proc_dir_entry *res=create_proc_entry(name,mode,base);
 if (res) res->get_info=get_info;
 return res;
}

static inline __attribute__((always_inline)) struct proc_dir_entry *proc_net_create(const char *name,
 mode_t mode, get_info_t *get_info)
{
 return create_proc_info_entry(name,mode,proc_net,get_info);
}

static inline __attribute__((always_inline)) struct proc_dir_entry *proc_net_fops_create(const char *name,
 mode_t mode, struct file_operations *fops)
{
 struct proc_dir_entry *res = create_proc_entry(name, mode, proc_net);
 if (res)
  res->proc_fops = fops;
 return res;
}

static inline __attribute__((always_inline)) void proc_net_remove(const char *name)
{
 remove_proc_entry(name,proc_net);
}
# 242 "include/linux/proc_fs.h"
extern void kclist_add(struct kcore_list *, void *, size_t);


struct proc_inode {
 struct task_struct *task;
 int type;
 union {
  int (*proc_get_link)(struct inode *, struct dentry **, struct vfsmount **);
  int (*proc_read)(struct task_struct *task, char *page);
 } op;
 struct proc_dir_entry *pde;
 struct inode vfs_inode;
};

static inline __attribute__((always_inline)) struct proc_inode *PROC_I(const struct inode *inode)
{
 return ({ const typeof( ((struct proc_inode *)0)->vfs_inode ) *__mptr = (inode); (struct proc_inode *)( (char *)__mptr - __builtin_offsetof(struct proc_inode,vfs_inode) );});
}

static inline __attribute__((always_inline)) struct proc_dir_entry *PDE(const struct inode *inode)
{
 return PROC_I(inode)->pde;
}
# 65 "net/ipv6/tcp_ipv6.c" 2


static void tcp_v6_send_reset(struct sk_buff *skb);
static void tcp_v6_reqsk_send_ack(struct sk_buff *skb, struct request_sock *req);
static void tcp_v6_send_check(struct sock *sk, struct tcphdr *th, int len,
      struct sk_buff *skb);

static int tcp_v6_do_rcv(struct sock *sk, struct sk_buff *skb);
static int tcp_v6_xmit(struct sk_buff *skb, int ipfragok);

static struct tcp_func ipv6_mapped;
static struct tcp_func ipv6_specific;


static __inline__ __attribute__((always_inline)) int tcp_v6_hashfn(struct in6_addr *laddr, u16 lport,
        struct in6_addr *faddr, u16 fport)
{
 int hashent = (lport ^ fport);

 hashent ^= (laddr->in6_u.u6_addr32[3] ^ faddr->in6_u.u6_addr32[3]);
 hashent ^= hashent>>16;
 hashent ^= hashent>>8;
 return (hashent & ((tcp_hashinfo.__tcp_ehash_size) - 1));
}

static __inline__ __attribute__((always_inline)) int tcp_v6_sk_hashfn(struct sock *sk)
{
 struct inet_sock *inet = inet_sk(sk);
 struct ipv6_pinfo *np = inet6_sk(sk);
 struct in6_addr *laddr = &np->rcv_saddr;
 struct in6_addr *faddr = &np->daddr;
 __u16 lport = inet->num;
 __u16 fport = inet->dport;
 return tcp_v6_hashfn(laddr, lport, faddr, fport);
}

static inline __attribute__((always_inline)) int tcp_v6_bind_conflict(struct sock *sk,
           struct tcp_bind_bucket *tb)
{
 struct sock *sk2;
 struct hlist_node *node;


 for (node = (&tb->owners)->first; node && ({ prefetch(node->next); 1;}) && ({ sk2 = ({ const typeof( ((typeof(*sk2) *)0)->__sk_common.skc_bind_node ) *__mptr = (node); (typeof(*sk2) *)( (char *)__mptr - __builtin_offsetof(typeof(*sk2),__sk_common.skc_bind_node) );}); 1;}); node = node->next) {
  if (sk != sk2 &&
      (!sk->__sk_common.skc_bound_dev_if ||
       !sk2->__sk_common.skc_bound_dev_if ||
       sk->__sk_common.skc_bound_dev_if == sk2->__sk_common.skc_bound_dev_if) &&
      (!sk->__sk_common.skc_reuse || !sk2->__sk_common.skc_reuse ||
       sk2->__sk_common.skc_state == TCP_LISTEN) &&
       ipv6_rcv_saddr_equal(sk, sk2))
   break;
 }

 return node != ((void *)0);
}






static int tcp_v6_get_port(struct sock *sk, unsigned short snum)
{
 struct tcp_bind_hashbucket *head;
 struct tcp_bind_bucket *tb;
 struct hlist_node *node;
 int ret;

 do { do { (current_thread_info()->preempt_count) += ((1UL << (0 + 8))); } while (0); __asm__ __volatile__("": : :"memory"); } while (0);
 if (snum == 0) {
  int low = sysctl_local_port_range[0];
  int high = sysctl_local_port_range[1];
  int remaining = (high - low) + 1;
  int rover;

  _spin_lock(&(tcp_hashinfo.__tcp_portalloc_lock));
  if (tcp_port_rover < low)
   rover = low;
  else
   rover = tcp_port_rover;
  do { rover++;
   if (rover > high)
    rover = low;
   head = &(tcp_hashinfo.__tcp_bhash)[tcp_bhashfn(rover)];
   _spin_lock(&head->lock);
   for (node = (&head->chain)->first; node && ({ prefetch(node->next); 1;}) && ({ tb = ({ const typeof( ((typeof(*tb) *)0)->node ) *__mptr = (node); (typeof(*tb) *)( (char *)__mptr - __builtin_offsetof(typeof(*tb),node) );}); 1;}); node = node->next)
    if (tb->port == rover)
     goto next;
   break;
  next:
   _spin_unlock(&head->lock);
  } while (--remaining > 0);
  tcp_port_rover = rover;
  _spin_unlock(&(tcp_hashinfo.__tcp_portalloc_lock));







  ret = 1;
  if (__builtin_expect(!!(remaining <= 0), 0))
   goto fail;


  snum = rover;
 } else {
  head = &(tcp_hashinfo.__tcp_bhash)[tcp_bhashfn(snum)];
  _spin_lock(&head->lock);
  for (node = (&head->chain)->first; node && ({ prefetch(node->next); 1;}) && ({ tb = ({ const typeof( ((typeof(*tb) *)0)->node ) *__mptr = (node); (typeof(*tb) *)( (char *)__mptr - __builtin_offsetof(typeof(*tb),node) );}); 1;}); node = node->next)
   if (tb->port == snum)
    goto tb_found;
 }
 tb = ((void *)0);
 goto tb_not_found;
tb_found:
 if (tb && !hlist_empty(&tb->owners)) {
  if (tb->fastreuse > 0 && sk->__sk_common.skc_reuse &&
      sk->__sk_common.skc_state != TCP_LISTEN) {
   goto success;
  } else {
   ret = 1;
   if (tcp_v6_bind_conflict(sk, tb))
    goto fail_unlock;
  }
 }
tb_not_found:
 ret = 1;
 if (!tb && (tb = tcp_bucket_create(head, snum)) == ((void *)0))
  goto fail_unlock;
 if (hlist_empty(&tb->owners)) {
  if (sk->__sk_common.skc_reuse && sk->__sk_common.skc_state != TCP_LISTEN)
   tb->fastreuse = 1;
  else
   tb->fastreuse = 0;
 } else if (tb->fastreuse &&
     (!sk->__sk_common.skc_reuse || sk->__sk_common.skc_state == TCP_LISTEN))
  tb->fastreuse = 0;

success:
 if (!tcp_sk(sk)->bind_hash)
  tcp_bind_hash(sk, tb, snum);
 do { if (__builtin_expect(!!(!(tcp_sk(sk)->bind_hash == tb)), 0)) { printk("<3>" "KERNEL: assertion (%s) failed at %s (%d)\n", "tcp_sk(sk)->bind_hash == tb", "net/ipv6/tcp_ipv6.c" , 209); } } while(0);
 ret = 0;

fail_unlock:
 _spin_unlock(&head->lock);
fail:
 local_bh_enable();
 return ret;
}

static __inline__ __attribute__((always_inline)) void __tcp_v6_hash(struct sock *sk)
{
 struct hlist_head *list;
 rwlock_t *lock;

 do { if (__builtin_expect(!!(!(sk_unhashed(sk))), 0)) { printk("<3>" "KERNEL: assertion (%s) failed at %s (%d)\n", "sk_unhashed(sk)", "net/ipv6/tcp_ipv6.c" , 224); } } while(0);

 if (sk->__sk_common.skc_state == TCP_LISTEN) {
  list = &(tcp_hashinfo.__tcp_listening_hash)[tcp_sk_listen_hashfn(sk)];
  lock = &(tcp_hashinfo.__tcp_lhash_lock);
  tcp_listen_wlock();
 } else {
  sk->sk_hashent = tcp_v6_sk_hashfn(sk);
  list = &(tcp_hashinfo.__tcp_ehash)[sk->sk_hashent].chain;
  lock = &(tcp_hashinfo.__tcp_ehash)[sk->sk_hashent].lock;
  _write_lock(lock);
 }

 __sk_add_node(sk, list);
 sock_prot_inc_use(sk->sk_prot);
 _write_unlock(lock);
}


static void tcp_v6_hash(struct sock *sk)
{
 if (sk->__sk_common.skc_state != TCP_CLOSE) {
  struct tcp_sock *tp = tcp_sk(sk);

  if (tp->af_specific == &ipv6_mapped) {
   tcp_prot.hash(sk);
   return;
  }
  do { do { (current_thread_info()->preempt_count) += ((1UL << (0 + 8))); } while (0); __asm__ __volatile__("": : :"memory"); } while (0);
  __tcp_v6_hash(sk);
  local_bh_enable();
 }
}

static struct sock *tcp_v6_lookup_listener(struct in6_addr *daddr, unsigned short hnum, int dif)
{
 struct sock *sk;
 struct hlist_node *node;
 struct sock *result = ((void *)0);
 int score, hiscore;

 hiscore=0;
 _read_lock(&(tcp_hashinfo.__tcp_lhash_lock));
 for (node = (&(tcp_hashinfo.__tcp_listening_hash)[tcp_lhashfn(hnum)])->first; node && ({ prefetch(node->next); 1;}) && ({ sk = ({ const typeof( ((typeof(*sk) *)0)->__sk_common.skc_node ) *__mptr = (node); (typeof(*sk) *)( (char *)__mptr - __builtin_offsetof(typeof(*sk),__sk_common.skc_node) );}); 1;}); node = node->next) {
  if (inet_sk(sk)->num == hnum && sk->__sk_common.skc_family == 10) {
   struct ipv6_pinfo *np = inet6_sk(sk);

   score = 1;
   if (!ipv6_addr_any(&np->rcv_saddr)) {
    if (!ipv6_addr_equal(&np->rcv_saddr, daddr))
     continue;
    score++;
   }
   if (sk->__sk_common.skc_bound_dev_if) {
    if (sk->__sk_common.skc_bound_dev_if != dif)
     continue;
    score++;
   }
   if (score == 3) {
    result = sk;
    break;
   }
   if (score > hiscore) {
    hiscore = score;
    result = sk;
   }
  }
 }
 if (result)
  sock_hold(result);
 _read_unlock(&(tcp_hashinfo.__tcp_lhash_lock));
 return result;
}







static inline __attribute__((always_inline)) struct sock *__tcp_v6_lookup_established(struct in6_addr *saddr, u16 sport,
             struct in6_addr *daddr, u16 hnum,
             int dif)
{
 struct tcp_ehash_bucket *head;
 struct sock *sk;
 struct hlist_node *node;
 __u32 ports = (((__u32)(hnum)<<16) | (__u32)(sport));
 int hash;




 hash = tcp_v6_hashfn(daddr, hnum, saddr, sport);
 head = &(tcp_hashinfo.__tcp_ehash)[hash];
 _read_lock(&head->lock);
 for (node = (&head->chain)->first; node && ({ prefetch(node->next); 1;}) && ({ sk = ({ const typeof( ((typeof(*sk) *)0)->__sk_common.skc_node ) *__mptr = (node); (typeof(*sk) *)( (char *)__mptr - __builtin_offsetof(typeof(*sk),__sk_common.skc_node) );}); 1;}); node = node->next) {

  if((((*((__u32 *)&(inet_sk(sk)->dport)))== (ports)) && ((sk)->__sk_common.skc_family == 10) && ipv6_addr_equal(&inet6_sk(sk)->daddr, (saddr)) && ipv6_addr_equal(&inet6_sk(sk)->rcv_saddr, (daddr)) && (!((sk)->__sk_common.skc_bound_dev_if) || ((sk)->__sk_common.skc_bound_dev_if == (dif)))))
   goto hit;
 }

 for (node = (&(head + (tcp_hashinfo.__tcp_ehash_size))->chain)->first; node && ({ prefetch(node->next); 1;}) && ({ sk = ({ const typeof( ((typeof(*sk) *)0)->__sk_common.skc_node ) *__mptr = (node); (typeof(*sk) *)( (char *)__mptr - __builtin_offsetof(typeof(*sk),__sk_common.skc_node) );}); 1;}); node = node->next) {

  struct tcp_tw_bucket *tw = (struct tcp_tw_bucket *)sk;

  if(*((__u32 *)&(tw->tw_dport)) == ports &&
     sk->__sk_common.skc_family == 10) {
   if(ipv6_addr_equal(&tw->tw_v6_daddr, saddr) &&
      ipv6_addr_equal(&tw->tw_v6_rcv_saddr, daddr) &&
      (!sk->__sk_common.skc_bound_dev_if || sk->__sk_common.skc_bound_dev_if == dif))
    goto hit;
  }
 }
 _read_unlock(&head->lock);
 return ((void *)0);

hit:
 sock_hold(sk);
 _read_unlock(&head->lock);
 return sk;
}


static inline __attribute__((always_inline)) struct sock *__tcp_v6_lookup(struct in6_addr *saddr, u16 sport,
        struct in6_addr *daddr, u16 hnum,
        int dif)
{
 struct sock *sk;

 sk = __tcp_v6_lookup_established(saddr, sport, daddr, hnum, dif);

 if (sk)
  return sk;

 return tcp_v6_lookup_listener(daddr, hnum, dif);
}

inline __attribute__((always_inline)) struct sock *tcp_v6_lookup(struct in6_addr *saddr, u16 sport,
      struct in6_addr *daddr, u16 dport,
      int dif)
{
 struct sock *sk;

 do { do { (current_thread_info()->preempt_count) += ((1UL << (0 + 8))); } while (0); __asm__ __volatile__("": : :"memory"); } while (0);
 sk = __tcp_v6_lookup(saddr, sport, daddr, (__builtin_constant_p((__u16)(( __u16)(__be16)(dport))) ? ({ __u16 __x = ((( __u16)(__be16)(dport))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16((( __u16)(__be16)(dport)))), dif);
 local_bh_enable();

 return sk;
}

extern void *__crc_tcp_v6_lookup __attribute__((weak)); static const unsigned long __kcrctab_tcp_v6_lookup __attribute__((__used__)) __attribute__((section("__kcrctab" "_gpl"), unused)) = (unsigned long) &__crc_tcp_v6_lookup; static const char __kstrtab_tcp_v6_lookup[] __attribute__((section("__ksymtab_strings"))) = "" "tcp_v6_lookup"; static const struct kernel_symbol __ksymtab_tcp_v6_lookup __attribute__((__used__)) __attribute__((section("__ksymtab" "_gpl"), unused)) = { (unsigned long)&tcp_v6_lookup, __kstrtab_tcp_v6_lookup };






static u32 tcp_v6_synq_hash(struct in6_addr *raddr, u16 rport, u32 rnd)
{
 u32 a, b, c;

 a = raddr->in6_u.u6_addr32[0];
 b = raddr->in6_u.u6_addr32[1];
 c = raddr->in6_u.u6_addr32[2];

 a += 0x9e3779b9;
 b += 0x9e3779b9;
 c += rnd;
 { a -= b; a -= c; a ^= (c>>13); b -= c; b -= a; b ^= (a<<8); c -= a; c -= b; c ^= (b>>13); a -= b; a -= c; a ^= (c>>12); b -= c; b -= a; b ^= (a<<16); c -= a; c -= b; c ^= (b>>5); a -= b; a -= c; a ^= (c>>3); b -= c; b -= a; b ^= (a<<10); c -= a; c -= b; c ^= (b>>15); };

 a += raddr->in6_u.u6_addr32[3];
 b += (u32) rport;
 { a -= b; a -= c; a ^= (c>>13); b -= c; b -= a; b ^= (a<<8); c -= a; c -= b; c ^= (b>>13); a -= b; a -= c; a ^= (c>>12); b -= c; b -= a; b ^= (a<<16); c -= a; c -= b; c ^= (b>>5); a -= b; a -= c; a ^= (c>>3); b -= c; b -= a; b ^= (a<<10); c -= a; c -= b; c ^= (b>>15); };

 return c & (512 - 1);
}

static struct request_sock *tcp_v6_search_req(struct tcp_sock *tp,
           struct request_sock ***prevp,
           __u16 rport,
           struct in6_addr *raddr,
           struct in6_addr *laddr,
           int iif)
{
 struct listen_sock *lopt = tp->accept_queue.listen_opt;
 struct request_sock *req, **prev;

 for (prev = &lopt->syn_table[tcp_v6_synq_hash(raddr, rport, lopt->hash_rnd)];
      (req = *prev) != ((void *)0);
      prev = &req->dl_next) {
  const struct tcp6_request_sock *treq = tcp6_rsk(req);

  if (inet_rsk(req)->rmt_port == rport &&
      req->rsk_ops->family == 10 &&
      ipv6_addr_equal(&treq->rmt_addr, raddr) &&
      ipv6_addr_equal(&treq->loc_addr, laddr) &&
      (!treq->iif || treq->iif == iif)) {
   do { if (__builtin_expect(!!(!(req->sk == ((void *)0))), 0)) { printk("<3>" "KERNEL: assertion (%s) failed at %s (%d)\n", "req->sk == NULL", "net/ipv6/tcp_ipv6.c" , 422); } } while(0);
   *prevp = prev;
   return req;
  }
 }

 return ((void *)0);
}

static __inline__ __attribute__((always_inline)) u16 tcp_v6_check(struct tcphdr *th, int len,
       struct in6_addr *saddr,
       struct in6_addr *daddr,
       unsigned long base)
{
 return csum_ipv6_magic(saddr, daddr, len, IPPROTO_TCP, base);
}

static __u32 tcp_v6_init_sequence(struct sock *sk, struct sk_buff *skb)
{
 if (skb->protocol == (( __be16)(__builtin_constant_p((__u16)((0x86DD))) ? ({ __u16 __x = (((0x86DD))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((0x86DD)))))) {
  return secure_tcpv6_sequence_number(skb->nh.ipv6h->daddr.in6_u.u6_addr32,
          skb->nh.ipv6h->saddr.in6_u.u6_addr32,
          skb->h.th->dest,
          skb->h.th->source);
 } else {
  return secure_tcp_sequence_number(skb->nh.iph->daddr,
        skb->nh.iph->saddr,
        skb->h.th->dest,
        skb->h.th->source);
 }
}

static int __tcp_v6_check_established(struct sock *sk, __u16 lport,
          struct tcp_tw_bucket **twp)
{
 struct inet_sock *inet = inet_sk(sk);
 struct ipv6_pinfo *np = inet6_sk(sk);
 struct in6_addr *daddr = &np->rcv_saddr;
 struct in6_addr *saddr = &np->daddr;
 int dif = sk->__sk_common.skc_bound_dev_if;
 u32 ports = (((__u32)(lport)<<16) | (__u32)(inet->dport));
 int hash = tcp_v6_hashfn(daddr, inet->num, saddr, inet->dport);
 struct tcp_ehash_bucket *head = &(tcp_hashinfo.__tcp_ehash)[hash];
 struct sock *sk2;
 struct hlist_node *node;
 struct tcp_tw_bucket *tw;

 _write_lock(&head->lock);


 for (node = (&(head + (tcp_hashinfo.__tcp_ehash_size))->chain)->first; node && ({ prefetch(node->next); 1;}) && ({ sk2 = ({ const typeof( ((typeof(*sk2) *)0)->__sk_common.skc_node ) *__mptr = (node); (typeof(*sk2) *)( (char *)__mptr - __builtin_offsetof(typeof(*sk2),__sk_common.skc_node) );}); 1;}); node = node->next) {
  tw = (struct tcp_tw_bucket*)sk2;

  if(*((__u32 *)&(tw->tw_dport)) == ports &&
     sk2->__sk_common.skc_family == 10 &&
     ipv6_addr_equal(&tw->tw_v6_daddr, saddr) &&
     ipv6_addr_equal(&tw->tw_v6_rcv_saddr, daddr) &&
     sk2->__sk_common.skc_bound_dev_if == sk->__sk_common.skc_bound_dev_if) {
   struct tcp_sock *tp = tcp_sk(sk);

   if (tw->tw_ts_recent_stamp &&
       (!twp || (sysctl_tcp_tw_reuse &&
          xtime.tv_sec -
          tw->tw_ts_recent_stamp > 1))) {

    tp->write_seq = tw->tw_snd_nxt + 65535 + 2;
    if (!tp->write_seq)
     tp->write_seq = 1;
    tp->rx_opt.ts_recent = tw->tw_ts_recent;
    tp->rx_opt.ts_recent_stamp = tw->tw_ts_recent_stamp;
    sock_hold(sk2);
    goto unique;
   } else
    goto not_unique;
  }
 }
 tw = ((void *)0);


 for (node = (&head->chain)->first; node && ({ prefetch(node->next); 1;}) && ({ sk2 = ({ const typeof( ((typeof(*sk2) *)0)->__sk_common.skc_node ) *__mptr = (node); (typeof(*sk2) *)( (char *)__mptr - __builtin_offsetof(typeof(*sk2),__sk_common.skc_node) );}); 1;}); node = node->next) {
  if((((*((__u32 *)&(inet_sk(sk2)->dport)))== (ports)) && ((sk2)->__sk_common.skc_family == 10) && ipv6_addr_equal(&inet6_sk(sk2)->daddr, (saddr)) && ipv6_addr_equal(&inet6_sk(sk2)->rcv_saddr, (daddr)) && (!((sk2)->__sk_common.skc_bound_dev_if) || ((sk2)->__sk_common.skc_bound_dev_if == (dif)))))
   goto not_unique;
 }

unique:
 do { if (__builtin_expect(!!(!(sk_unhashed(sk))), 0)) { printk("<3>" "KERNEL: assertion (%s) failed at %s (%d)\n", "sk_unhashed(sk)", "net/ipv6/tcp_ipv6.c" , 507); } } while(0);
 __sk_add_node(sk, &head->chain);
 sk->sk_hashent = hash;
 sock_prot_inc_use(sk->sk_prot);
 _write_unlock(&head->lock);

 if (twp) {
  *twp = tw;
  (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(net_statistics[0]); (__typeof__(net_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[LINUX_MIB_TIMEWAITRECYCLED]++);
 } else if (tw) {

  tcp_tw_deschedule(tw);
  (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(net_statistics[0]); (__typeof__(net_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[LINUX_MIB_TIMEWAITRECYCLED]++);

  tcp_tw_put(tw);
 }
 return 0;

not_unique:
 _write_unlock(&head->lock);
 return -99;
}

static inline __attribute__((always_inline)) u32 tcpv6_port_offset(const struct sock *sk)
{
 const struct inet_sock *inet = inet_sk(sk);
 const struct ipv6_pinfo *np = inet6_sk(sk);

 return secure_tcpv6_port_ephemeral(np->rcv_saddr.in6_u.u6_addr32,
        np->daddr.in6_u.u6_addr32,
        inet->dport);
}

static int tcp_v6_hash_connect(struct sock *sk)
{
 unsigned short snum = inet_sk(sk)->num;
  struct tcp_bind_hashbucket *head;
  struct tcp_bind_bucket *tb;
 int ret;

  if (!snum) {
   int low = sysctl_local_port_range[0];
   int high = sysctl_local_port_range[1];
  int range = high - low;
   int i;
  int port;
  static u32 hint;
  u32 offset = hint + tcpv6_port_offset(sk);
  struct hlist_node *node;
   struct tcp_tw_bucket *tw = ((void *)0);

   do { do { (current_thread_info()->preempt_count) += ((1UL << (0 + 8))); } while (0); __asm__ __volatile__("": : :"memory"); } while (0);
  for (i = 1; i <= range; i++) {
   port = low + (i + offset) % range;
    head = &(tcp_hashinfo.__tcp_bhash)[tcp_bhashfn(port)];
    _spin_lock(&head->lock);





   for (node = (&head->chain)->first; node && ({ prefetch(node->next); 1;}) && ({ tb = ({ const typeof( ((typeof(*tb) *)0)->node ) *__mptr = (node); (typeof(*tb) *)( (char *)__mptr - __builtin_offsetof(typeof(*tb),node) );}); 1;}); node = node->next) {
     if (tb->port == port) {
      do { if (__builtin_expect(!!(!(!hlist_empty(&tb->owners))), 0)) { printk("<3>" "KERNEL: assertion (%s) failed at %s (%d)\n", "!hlist_empty(&tb->owners)", "net/ipv6/tcp_ipv6.c" , 570); } } while(0);
      if (tb->fastreuse >= 0)
       goto next_port;
      if (!__tcp_v6_check_established(sk,
         port,
         &tw))
       goto ok;
      goto next_port;
     }
    }

    tb = tcp_bucket_create(head, port);
    if (!tb) {
     _spin_unlock(&head->lock);
     break;
    }
    tb->fastreuse = -1;
    goto ok;

   next_port:
    _spin_unlock(&head->lock);
   }
   local_bh_enable();

   return -99;

ok:
  hint += i;


   tcp_bind_hash(sk, tb, port);
  if (sk_unhashed(sk)) {
    inet_sk(sk)->sport = (( __be16)(__builtin_constant_p((__u16)((port))) ? ({ __u16 __x = (((port))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((port)))));
    __tcp_v6_hash(sk);
   }
   _spin_unlock(&head->lock);

   if (tw) {
    tcp_tw_deschedule(tw);
    tcp_tw_put(tw);
   }

  ret = 0;
  goto out;
  }

  head = &(tcp_hashinfo.__tcp_bhash)[tcp_bhashfn(snum)];
  tb = tcp_sk(sk)->bind_hash;
 _spin_lock_bh(&head->lock);

 if (sk_head(&tb->owners) == sk && !sk->__sk_common.skc_bind_node.next) {
  __tcp_v6_hash(sk);
  _spin_unlock_bh(&head->lock);
  return 0;
 } else {
  _spin_unlock(&head->lock);

  ret = __tcp_v6_check_established(sk, snum, ((void *)0));
out:
  local_bh_enable();
  return ret;
 }
}

static __inline__ __attribute__((always_inline)) int tcp_v6_iif(struct sk_buff *skb)
{
 return ((struct inet6_skb_parm*)((skb)->cb))->iif;
}

static int tcp_v6_connect(struct sock *sk, struct sockaddr *uaddr,
     int addr_len)
{
 struct sockaddr_in6 *usin = (struct sockaddr_in6 *) uaddr;
 struct inet_sock *inet = inet_sk(sk);
 struct ipv6_pinfo *np = inet6_sk(sk);
 struct tcp_sock *tp = tcp_sk(sk);
 struct in6_addr *saddr = ((void *)0), *final_p = ((void *)0), final;
 struct flowi fl;
 struct dst_entry *dst;
 int addr_type;
 int err;

 if (addr_len < 24)
  return -22;

 if (usin->sin6_family != 10)
  return(-97);

 __memset_generic((&fl),(0),(sizeof(fl)));

 if (np->sndflow) {
  fl.nl_u.ip6_u.flowlabel = usin->sin6_flowinfo&(( __be32)((__u32)( (((__u32)((0x0FFFFFFF)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x0FFFFFFF)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x0FFFFFFF)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x0FFFFFFF)) & (__u32)0xff000000UL) >> 24) )));
  do { (fl.nl_u.ip6_u.flowlabel) &= ~(( __be32)(__builtin_constant_p((__u32)((INET_ECN_MASK << 20))) ? ({ __u32 __x = (((INET_ECN_MASK << 20))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((INET_ECN_MASK << 20))))); } while (0);
  if (fl.nl_u.ip6_u.flowlabel&(( __be32)((__u32)( (((__u32)((0x000FFFFF)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x000FFFFF)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x000FFFFF)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x000FFFFF)) & (__u32)0xff000000UL) >> 24) )))) {
   struct ip6_flowlabel *flowlabel;
   flowlabel = fl6_sock_lookup(sk, fl.nl_u.ip6_u.flowlabel);
   if (flowlabel == ((void *)0))
    return -22;
   ipv6_addr_copy(&usin->sin6_addr, &flowlabel->dst);
   fl6_sock_release(flowlabel);
  }
 }





   if(ipv6_addr_any(&usin->sin6_addr))
  usin->sin6_addr.in6_u.u6_addr8[15] = 0x1;

 addr_type = ipv6_addr_type(&usin->sin6_addr);

 if(addr_type & 0x0002U)
  return -101;

 if (addr_type&0x0020U) {
  if (addr_len >= sizeof(struct sockaddr_in6) &&
      usin->sin6_scope_id) {



   if (sk->__sk_common.skc_bound_dev_if &&
       sk->__sk_common.skc_bound_dev_if != usin->sin6_scope_id)
    return -22;

   sk->__sk_common.skc_bound_dev_if = usin->sin6_scope_id;
  }


  if (!sk->__sk_common.skc_bound_dev_if)
   return -22;
 }

 if (tp->rx_opt.ts_recent_stamp &&
     !ipv6_addr_equal(&np->daddr, &usin->sin6_addr)) {
  tp->rx_opt.ts_recent = 0;
  tp->rx_opt.ts_recent_stamp = 0;
  tp->write_seq = 0;
 }

 ipv6_addr_copy(&np->daddr, &usin->sin6_addr);
 np->flow_label = fl.nl_u.ip6_u.flowlabel;





 if (addr_type == 0x1000U) {
  u32 exthdrlen = tp->ext_header_len;
  struct sockaddr_in sin;

  do { if ((sk) && sock_flag((sk), SOCK_DBG)) printk("<7>" "connect: ipv4 mapped\n"); } while (0);

  if ((inet6_sk(sk)->ipv6only))
   return -101;

  sin.sin_family = 2;
  sin.sin_port = usin->sin6_port;
  sin.sin_addr.s_addr = usin->sin6_addr.in6_u.u6_addr32[3];

  tp->af_specific = &ipv6_mapped;
  sk->sk_backlog_rcv = tcp_v4_do_rcv;

  err = tcp_v4_connect(sk, (struct sockaddr *)&sin, sizeof(sin));

  if (err) {
   tp->ext_header_len = exthdrlen;
   tp->af_specific = &ipv6_specific;
   sk->sk_backlog_rcv = tcp_v6_do_rcv;
   goto failure;
  } else {
   ipv6_addr_set(&np->saddr, 0, 0, (( __be32)(__builtin_constant_p((__u32)((0x0000FFFF))) ? ({ __u32 __x = (((0x0000FFFF))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((0x0000FFFF))))),
          inet->saddr);
   ipv6_addr_set(&np->rcv_saddr, 0, 0, (( __be32)(__builtin_constant_p((__u32)((0x0000FFFF))) ? ({ __u32 __x = (((0x0000FFFF))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((0x0000FFFF))))),
          inet->rcv_saddr);
  }

  return err;
 }

 if (!ipv6_addr_any(&np->rcv_saddr))
  saddr = &np->rcv_saddr;

 fl.proto = IPPROTO_TCP;
 ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, &np->daddr);
 ipv6_addr_copy(&fl.nl_u.ip6_u.saddr,
         (saddr ? saddr : &np->saddr));
 fl.oif = sk->__sk_common.skc_bound_dev_if;
 fl.uli_u.ports.dport = usin->sin6_port;
 fl.uli_u.ports.sport = inet->sport;

 if (np->opt && np->opt->srcrt) {
  struct rt0_hdr *rt0 = (struct rt0_hdr *)np->opt->srcrt;
  ipv6_addr_copy(&final, &fl.nl_u.ip6_u.daddr);
  ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, rt0->addr);
  final_p = &final;
 }

 err = ip6_dst_lookup(sk, &dst, &fl);
 if (err)
  goto failure;
 if (final_p)
  ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, final_p);

 if ((err = xfrm_lookup(&dst, &fl, sk, 0)) < 0) {
  dst_release(dst);
  goto failure;
 }

 if (saddr == ((void *)0)) {
  saddr = &fl.nl_u.ip6_u.saddr;
  ipv6_addr_copy(&np->rcv_saddr, saddr);
 }


 ipv6_addr_copy(&np->saddr, saddr);
 inet->rcv_saddr = (( __be32)((__u32)( (((__u32)((0x7f000006)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x7f000006)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x7f000006)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x7f000006)) & (__u32)0xff000000UL) >> 24) )));

 ip6_dst_store(sk, dst, ((void *)0));
 sk->sk_route_caps = dst->dev->features &
  ~(2 | 2048);

 tp->ext_header_len = 0;
 if (np->opt)
  tp->ext_header_len = np->opt->opt_flen + np->opt->opt_nflen;

 tp->rx_opt.mss_clamp = 1280 - sizeof(struct tcphdr) - sizeof(struct ipv6hdr);

 inet->dport = usin->sin6_port;

 tcp_set_state(sk, TCP_SYN_SENT);
 err = tcp_v6_hash_connect(sk);
 if (err)
  goto late_failure;

 if (!tp->write_seq)
  tp->write_seq = secure_tcpv6_sequence_number(np->saddr.in6_u.u6_addr32,
            np->daddr.in6_u.u6_addr32,
            inet->sport,
            inet->dport);

 err = tcp_connect(sk);
 if (err)
  goto late_failure;

 return 0;

late_failure:
 tcp_set_state(sk, TCP_CLOSE);
 __sk_dst_reset(sk);
failure:
 inet->dport = 0;
 sk->sk_route_caps = 0;
 return err;
}

static void tcp_v6_err(struct sk_buff *skb, struct inet6_skb_parm *opt,
  int type, int code, int offset, __u32 info)
{
 struct ipv6hdr *hdr = (struct ipv6hdr*)skb->data;
 struct tcphdr *th = (struct tcphdr *)(skb->data+offset);
 struct ipv6_pinfo *np;
 struct sock *sk;
 int err;
 struct tcp_sock *tp;
 __u32 seq;

 sk = tcp_v6_lookup(&hdr->daddr, th->dest, &hdr->saddr, th->source, skb->dev->ifindex);

 if (sk == ((void *)0)) {
  ({ struct inet6_dev *_idev = (__in6_dev_get(skb->dev)); if (__builtin_expect(!!(_idev != ((void *)0)), 1)) (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)((_idev)->stats.icmpv6[0]); (__typeof__((_idev)->stats.icmpv6[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[ICMP6_MIB_INERRORS]++); (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(icmpv6_statistics[0]); (__typeof__(icmpv6_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[ICMP6_MIB_INERRORS]++); });
  return;
 }

 if (sk->__sk_common.skc_state == TCP_TIME_WAIT) {
  tcp_tw_put((struct tcp_tw_bucket*)sk);
  return;
 }

 _spin_lock(&((sk)->sk_lock.slock));
 if (((sk)->sk_lock.owner))
  (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(net_statistics[0]); (__typeof__(net_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[LINUX_MIB_LOCKDROPPEDICMPS]++);

 if (sk->__sk_common.skc_state == TCP_CLOSE)
  goto out;

 tp = tcp_sk(sk);
 seq = (__builtin_constant_p((__u32)(( __u32)(__be32)(th->seq))) ? ({ __u32 __x = ((( __u32)(__be32)(th->seq))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(th->seq))));
 if (sk->__sk_common.skc_state != TCP_LISTEN &&
     !between(seq, tp->snd_una, tp->snd_nxt)) {
  (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(net_statistics[0]); (__typeof__(net_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[LINUX_MIB_OUTOFWINDOWICMPS]++);
  goto out;
 }

 np = inet6_sk(sk);

 if (type == 2) {
  struct dst_entry *dst = ((void *)0);

  if (((sk)->sk_lock.owner))
   goto out;
  if ((1 << sk->__sk_common.skc_state) & (TCPF_LISTEN | TCPF_CLOSE))
   goto out;


  dst = __sk_dst_check(sk, np->dst_cookie);

  if (dst == ((void *)0)) {
   struct inet_sock *inet = inet_sk(sk);
   struct flowi fl;





   __memset_generic((&fl),(0),(sizeof(fl)));
   fl.proto = IPPROTO_TCP;
   ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, &np->daddr);
   ipv6_addr_copy(&fl.nl_u.ip6_u.saddr, &np->saddr);
   fl.oif = sk->__sk_common.skc_bound_dev_if;
   fl.uli_u.ports.dport = inet->dport;
   fl.uli_u.ports.sport = inet->sport;

   if ((err = ip6_dst_lookup(sk, &dst, &fl))) {
    sk->sk_err_soft = -err;
    goto out;
   }

   if ((err = xfrm_lookup(&dst, &fl, sk, 0)) < 0) {
    sk->sk_err_soft = -err;
    goto out;
   }

  } else
   dst_hold(dst);

  if (tp->pmtu_cookie > dst_mtu(dst)) {
   tcp_sync_mss(sk, dst_mtu(dst));
   tcp_simple_retransmit(sk);
  }
  dst_release(dst);
  goto out;
 }

 icmpv6_err_convert(type, code, &err);


 switch (sk->__sk_common.skc_state) {
  struct request_sock *req, **prev;
 case TCP_LISTEN:
  if (((sk)->sk_lock.owner))
   goto out;

  req = tcp_v6_search_req(tp, &prev, th->dest, &hdr->daddr,
     &hdr->saddr, tcp_v6_iif(skb));
  if (!req)
   goto out;




  do { if (__builtin_expect(!!(!(req->sk == ((void *)0))), 0)) { printk("<3>" "KERNEL: assertion (%s) failed at %s (%d)\n", "req->sk == NULL", "net/ipv6/tcp_ipv6.c" , 931); } } while(0);

  if (seq != tcp_rsk(req)->snt_isn) {
   (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(net_statistics[0]); (__typeof__(net_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[LINUX_MIB_OUTOFWINDOWICMPS]++);
   goto out;
  }

  tcp_synq_drop(sk, req, prev);
  goto out;

 case TCP_SYN_SENT:
 case TCP_SYN_RECV:

  if (!((sk)->sk_lock.owner)) {
   (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[0]); (__typeof__(tcp_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_ATTEMPTFAILS]++);
   sk->sk_err = err;
   sk->sk_error_report(sk);

   tcp_done(sk);
  } else
   sk->sk_err_soft = err;
  goto out;
 }

 if (!((sk)->sk_lock.owner) && np->recverr) {
  sk->sk_err = err;
  sk->sk_error_report(sk);
 } else
  sk->sk_err_soft = err;

out:
 _spin_unlock(&((sk)->sk_lock.slock));
 sock_put(sk);
}


static int tcp_v6_send_synack(struct sock *sk, struct request_sock *req,
         struct dst_entry *dst)
{
 struct tcp6_request_sock *treq = tcp6_rsk(req);
 struct ipv6_pinfo *np = inet6_sk(sk);
 struct sk_buff * skb;
 struct ipv6_txoptions *opt = ((void *)0);
 struct in6_addr * final_p = ((void *)0), final;
 struct flowi fl;
 int err = -1;

 __memset_generic((&fl),(0),(sizeof(fl)));
 fl.proto = IPPROTO_TCP;
 ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, &treq->rmt_addr);
 ipv6_addr_copy(&fl.nl_u.ip6_u.saddr, &treq->loc_addr);
 fl.nl_u.ip6_u.flowlabel = 0;
 fl.oif = treq->iif;
 fl.uli_u.ports.dport = inet_rsk(req)->rmt_port;
 fl.uli_u.ports.sport = inet_sk(sk)->sport;

 if (dst == ((void *)0)) {
  opt = np->opt;
  if (opt == ((void *)0) &&
      np->rxopt.bits.srcrt == 2 &&
      treq->pktopts) {
   struct sk_buff *pktopts = treq->pktopts;
   struct inet6_skb_parm *rxopt = ((struct inet6_skb_parm*)((pktopts)->cb));
   if (rxopt->srcrt)
    opt = ipv6_invert_rthdr(sk, (struct ipv6_rt_hdr*)(pktopts->nh.raw + rxopt->srcrt));
  }

  if (opt && opt->srcrt) {
   struct rt0_hdr *rt0 = (struct rt0_hdr *) opt->srcrt;
   ipv6_addr_copy(&final, &fl.nl_u.ip6_u.daddr);
   ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, rt0->addr);
   final_p = &final;
  }

  err = ip6_dst_lookup(sk, &dst, &fl);
  if (err)
   goto done;
  if (final_p)
   ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, final_p);
  if ((err = xfrm_lookup(&dst, &fl, sk, 0)) < 0)
   goto done;
 }

 skb = tcp_make_synack(sk, dst, req);
 if (skb) {
  struct tcphdr *th = skb->h.th;

  th->check = tcp_v6_check(th, skb->len,
      &treq->loc_addr, &treq->rmt_addr,
      csum_partial((char *)th, skb->len, skb->csum));

  ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, &treq->rmt_addr);
  err = ip6_xmit(sk, skb, &fl, opt, 0);
  if (err == 2)
   err = 0;
 }

done:
 dst_release(dst);
        if (opt && opt != np->opt)
  sock_kfree_s(sk, opt, opt->tot_len);
 return err;
}

static void tcp_v6_reqsk_destructor(struct request_sock *req)
{
 if (tcp6_rsk(req)->pktopts)
  kfree_skb(tcp6_rsk(req)->pktopts);
}

static struct request_sock_ops tcp6_request_sock_ops = {
 .family = 10,
 .obj_size = sizeof(struct tcp6_request_sock),
 .rtx_syn_ack = tcp_v6_send_synack,
 .send_ack = tcp_v6_reqsk_send_ack,
 .destructor = tcp_v6_reqsk_destructor,
 .send_reset = tcp_v6_send_reset
};

static int ipv6_opt_accepted(struct sock *sk, struct sk_buff *skb)
{
 struct ipv6_pinfo *np = inet6_sk(sk);
 struct inet6_skb_parm *opt = ((struct inet6_skb_parm*)((skb)->cb));

 if (np->rxopt.all) {
  if ((opt->hop && np->rxopt.bits.hopopts) ||
      (((( __be32)((__u32)( (((__u32)((0x0FFFFFFF)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x0FFFFFFF)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x0FFFFFFF)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x0FFFFFFF)) & (__u32)0xff000000UL) >> 24) )))&*(u32*)skb->nh.raw) &&
       np->rxopt.bits.rxflow) ||
      (opt->srcrt && np->rxopt.bits.srcrt) ||
      ((opt->dst1 || opt->dst0) && np->rxopt.bits.dstopts))
   return 1;
 }
 return 0;
}


static void tcp_v6_send_check(struct sock *sk, struct tcphdr *th, int len,
         struct sk_buff *skb)
{
 struct ipv6_pinfo *np = inet6_sk(sk);

 if (skb->ip_summed == 1) {
  th->check = ~csum_ipv6_magic(&np->saddr, &np->daddr, len, IPPROTO_TCP, 0);
  skb->csum = __builtin_offsetof(struct tcphdr,check);
 } else {
  th->check = csum_ipv6_magic(&np->saddr, &np->daddr, len, IPPROTO_TCP,
         csum_partial((char *)th, th->doff<<2,
        skb->csum));
 }
}


static void tcp_v6_send_reset(struct sk_buff *skb)
{
 struct tcphdr *th = skb->h.th, *t1;
 struct sk_buff *buff;
 struct flowi fl;

 if (th->rst)
  return;

 if (!ipv6_unicast_destination(skb))
  return;






 buff = alloc_skb((96 + 48) + sizeof(struct ipv6hdr) + sizeof(struct tcphdr),
    (0x20u));
 if (buff == ((void *)0))
    return;

 skb_reserve(buff, (96 + 48) + sizeof(struct ipv6hdr) + sizeof(struct tcphdr));

 t1 = (struct tcphdr *) skb_push(buff,sizeof(struct tcphdr));


 __memset_generic((t1),(0),(sizeof(*t1)));
 t1->dest = th->source;
 t1->source = th->dest;
 t1->doff = sizeof(*t1)/4;
 t1->rst = 1;

 if(th->ack) {
    t1->seq = th->ack_seq;
 } else {
  t1->ack = 1;
  t1->ack_seq = (( __be32)(__builtin_constant_p((__u32)(((__builtin_constant_p((__u32)(( __u32)(__be32)(th->seq))) ? ({ __u32 __x = ((( __u32)(__be32)(th->seq))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(th->seq)))) + th->syn + th->fin + skb->len - (th->doff<<2)))) ? ({ __u32 __x = ((((__builtin_constant_p((__u32)(( __u32)(__be32)(th->seq))) ? ({ __u32 __x = ((( __u32)(__be32)(th->seq))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(th->seq)))) + th->syn + th->fin + skb->len - (th->doff<<2)))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((((__builtin_constant_p((__u32)(( __u32)(__be32)(th->seq))) ? ({ __u32 __x = ((( __u32)(__be32)(th->seq))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(th->seq)))) + th->syn + th->fin + skb->len - (th->doff<<2))))));

 }

 buff->csum = csum_partial((char *)t1, sizeof(*t1), 0);

 __memset_generic((&fl),(0),(sizeof(fl)));
 ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, &skb->nh.ipv6h->saddr);
 ipv6_addr_copy(&fl.nl_u.ip6_u.saddr, &skb->nh.ipv6h->daddr);

 t1->check = csum_ipv6_magic(&fl.nl_u.ip6_u.saddr, &fl.nl_u.ip6_u.daddr,
        sizeof(*t1), IPPROTO_TCP,
        buff->csum);

 fl.proto = IPPROTO_TCP;
 fl.oif = tcp_v6_iif(skb);
 fl.uli_u.ports.dport = t1->dest;
 fl.uli_u.ports.sport = t1->source;


 if (!ip6_dst_lookup(((void *)0), &buff->dst, &fl)) {

  if ((xfrm_lookup(&buff->dst, &fl, ((void *)0), 0)) < 0) {
   dst_release(buff->dst);
   return;
  }

  ip6_xmit(((void *)0), buff, &fl, ((void *)0), 0);
  (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[0]); (__typeof__(tcp_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_OUTSEGS]++);
  (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[0]); (__typeof__(tcp_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_OUTRSTS]++);
  return;
 }

 kfree_skb(buff);
}

static void tcp_v6_send_ack(struct sk_buff *skb, u32 seq, u32 ack, u32 win, u32 ts)
{
 struct tcphdr *th = skb->h.th, *t1;
 struct sk_buff *buff;
 struct flowi fl;
 int tot_len = sizeof(struct tcphdr);

 if (ts)
  tot_len += 3*4;

 buff = alloc_skb((96 + 48) + sizeof(struct ipv6hdr) + tot_len,
    (0x20u));
 if (buff == ((void *)0))
  return;

 skb_reserve(buff, (96 + 48) + sizeof(struct ipv6hdr) + tot_len);

 t1 = (struct tcphdr *) skb_push(buff,tot_len);


 __memset_generic((t1),(0),(sizeof(*t1)));
 t1->dest = th->source;
 t1->source = th->dest;
 t1->doff = tot_len/4;
 t1->seq = (( __be32)(__builtin_constant_p((__u32)((seq))) ? ({ __u32 __x = (((seq))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((seq)))));
 t1->ack_seq = (( __be32)(__builtin_constant_p((__u32)((ack))) ? ({ __u32 __x = (((ack))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((ack)))));
 t1->ack = 1;
 t1->window = (( __be16)(__builtin_constant_p((__u16)((win))) ? ({ __u16 __x = (((win))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((win)))));

 if (ts) {
  u32 *ptr = (u32*)(t1 + 1);
  *ptr++ = (( __be32)(__builtin_constant_p((__u32)(((1 << 24) | (1 << 16) | (8 << 8) | 10))) ? ({ __u32 __x = ((((1 << 24) | (1 << 16) | (8 << 8) | 10))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((((1 << 24) | (1 << 16) | (8 << 8) | 10)))));

  *ptr++ = (( __be32)(__builtin_constant_p((__u32)((((__u32)(jiffies))))) ? ({ __u32 __x = (((((__u32)(jiffies))))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((((__u32)(jiffies)))))));
  *ptr = (( __be32)(__builtin_constant_p((__u32)((ts))) ? ({ __u32 __x = (((ts))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((ts)))));
 }

 buff->csum = csum_partial((char *)t1, tot_len, 0);

 __memset_generic((&fl),(0),(sizeof(fl)));
 ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, &skb->nh.ipv6h->saddr);
 ipv6_addr_copy(&fl.nl_u.ip6_u.saddr, &skb->nh.ipv6h->daddr);

 t1->check = csum_ipv6_magic(&fl.nl_u.ip6_u.saddr, &fl.nl_u.ip6_u.daddr,
        tot_len, IPPROTO_TCP,
        buff->csum);

 fl.proto = IPPROTO_TCP;
 fl.oif = tcp_v6_iif(skb);
 fl.uli_u.ports.dport = t1->dest;
 fl.uli_u.ports.sport = t1->source;

 if (!ip6_dst_lookup(((void *)0), &buff->dst, &fl)) {
  if ((xfrm_lookup(&buff->dst, &fl, ((void *)0), 0)) < 0) {
   dst_release(buff->dst);
   return;
  }
  ip6_xmit(((void *)0), buff, &fl, ((void *)0), 0);
  (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[0]); (__typeof__(tcp_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_OUTSEGS]++);
  return;
 }

 kfree_skb(buff);
}

static void tcp_v6_timewait_ack(struct sock *sk, struct sk_buff *skb)
{
 struct tcp_tw_bucket *tw = (struct tcp_tw_bucket *)sk;

 tcp_v6_send_ack(skb, tw->tw_snd_nxt, tw->tw_rcv_nxt,
   tw->tw_rcv_wnd >> tw->tw_rcv_wscale, tw->tw_ts_recent);

 tcp_tw_put(tw);
}

static void tcp_v6_reqsk_send_ack(struct sk_buff *skb, struct request_sock *req)
{
 tcp_v6_send_ack(skb, tcp_rsk(req)->snt_isn + 1, tcp_rsk(req)->rcv_isn + 1, req->rcv_wnd, req->ts_recent);
}


static struct sock *tcp_v6_hnd_req(struct sock *sk,struct sk_buff *skb)
{
 struct request_sock *req, **prev;
 struct tcphdr *th = skb->h.th;
 struct tcp_sock *tp = tcp_sk(sk);
 struct sock *nsk;


 req = tcp_v6_search_req(tp, &prev, th->source, &skb->nh.ipv6h->saddr,
    &skb->nh.ipv6h->daddr, tcp_v6_iif(skb));
 if (req)
  return tcp_check_req(sk, skb, req, prev);

 nsk = __tcp_v6_lookup_established(&skb->nh.ipv6h->saddr,
       th->source,
       &skb->nh.ipv6h->daddr,
       (__builtin_constant_p((__u16)(( __u16)(__be16)(th->dest))) ? ({ __u16 __x = ((( __u16)(__be16)(th->dest))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16((( __u16)(__be16)(th->dest)))),
       tcp_v6_iif(skb));

 if (nsk) {
  if (nsk->__sk_common.skc_state != TCP_TIME_WAIT) {
   _spin_lock(&((nsk)->sk_lock.slock));
   return nsk;
  }
  tcp_tw_put((struct tcp_tw_bucket*)nsk);
  return ((void *)0);
 }





 return sk;
}

static void tcp_v6_synq_add(struct sock *sk, struct request_sock *req)
{
 struct tcp_sock *tp = tcp_sk(sk);
 struct listen_sock *lopt = tp->accept_queue.listen_opt;
 u32 h = tcp_v6_synq_hash(&tcp6_rsk(req)->rmt_addr, inet_rsk(req)->rmt_port, lopt->hash_rnd);

 reqsk_queue_hash_req(&tp->accept_queue, h, req, ((unsigned)(3*250)));
 tcp_synq_added(sk);
}





static int tcp_v6_conn_request(struct sock *sk, struct sk_buff *skb)
{
 struct tcp6_request_sock *treq;
 struct ipv6_pinfo *np = inet6_sk(sk);
 struct tcp_options_received tmp_opt;
 struct tcp_sock *tp = tcp_sk(sk);
 struct request_sock *req = ((void *)0);
 __u32 isn = ((struct tcp_skb_cb *)&((skb)->cb[0]))->when;

 if (skb->protocol == (( __be16)(__builtin_constant_p((__u16)((0x0800))) ? ({ __u16 __x = (((0x0800))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((0x0800))))))
  return tcp_v4_conn_request(sk, skb);

 if (!ipv6_unicast_destination(skb))
  goto drop;




 if (tcp_synq_is_full(sk) && !isn) {
  if (net_ratelimit())
   printk("<6>" "TCPv6: dropping request, synflood is possible\n");
  goto drop;
 }

 if (sk_acceptq_is_full(sk) && tcp_synq_young(sk) > 1)
  goto drop;

 req = reqsk_alloc(&tcp6_request_sock_ops);
 if (req == ((void *)0))
  goto drop;

 tcp_clear_options(&tmp_opt);
 tmp_opt.mss_clamp = 1280 - sizeof(struct tcphdr) - sizeof(struct ipv6hdr);
 tmp_opt.user_mss = tp->rx_opt.user_mss;

 tcp_parse_options(skb, &tmp_opt, 0);

 tmp_opt.tstamp_ok = tmp_opt.saw_tstamp;
 tcp_openreq_init(req, &tmp_opt, skb);

 treq = tcp6_rsk(req);
 ipv6_addr_copy(&treq->rmt_addr, &skb->nh.ipv6h->saddr);
 ipv6_addr_copy(&treq->loc_addr, &skb->nh.ipv6h->daddr);
 TCP_ECN_create_request(req, skb->h.th);
 treq->pktopts = ((void *)0);
 if (ipv6_opt_accepted(sk, skb) ||
     np->rxopt.bits.rxinfo ||
     np->rxopt.bits.rxhlim) {
  atomic_inc(&skb->users);
  treq->pktopts = skb;
 }
 treq->iif = sk->__sk_common.skc_bound_dev_if;


 if (!sk->__sk_common.skc_bound_dev_if &&
     ipv6_addr_type(&treq->rmt_addr) & 0x0020U)
  treq->iif = tcp_v6_iif(skb);

 if (isn == 0)
  isn = tcp_v6_init_sequence(sk,skb);

 tcp_rsk(req)->snt_isn = isn;

 if (tcp_v6_send_synack(sk, req, ((void *)0)))
  goto drop;

 tcp_v6_synq_add(sk, req);

 return 0;

drop:
 if (req)
  reqsk_free(req);

 (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[0]); (__typeof__(tcp_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_ATTEMPTFAILS]++);
 return 0;
}

static struct sock * tcp_v6_syn_recv_sock(struct sock *sk, struct sk_buff *skb,
       struct request_sock *req,
       struct dst_entry *dst)
{
 struct tcp6_request_sock *treq = tcp6_rsk(req);
 struct ipv6_pinfo *newnp, *np = inet6_sk(sk);
 struct tcp6_sock *newtcp6sk;
 struct inet_sock *newinet;
 struct tcp_sock *newtp;
 struct sock *newsk;
 struct ipv6_txoptions *opt;

 if (skb->protocol == (( __be16)(__builtin_constant_p((__u16)((0x0800))) ? ({ __u16 __x = (((0x0800))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((0x0800)))))) {




  newsk = tcp_v4_syn_recv_sock(sk, skb, req, dst);

  if (newsk == ((void *)0))
   return ((void *)0);

  newtcp6sk = (struct tcp6_sock *)newsk;
  inet_sk(newsk)->pinet6 = &newtcp6sk->inet6;

  newinet = inet_sk(newsk);
  newnp = inet6_sk(newsk);
  newtp = tcp_sk(newsk);

  __memcpy(newnp,np,sizeof(struct ipv6_pinfo));

  ipv6_addr_set(&newnp->daddr, 0, 0, (( __be32)(__builtin_constant_p((__u32)((0x0000FFFF))) ? ({ __u32 __x = (((0x0000FFFF))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((0x0000FFFF))))),
         newinet->daddr);

  ipv6_addr_set(&newnp->saddr, 0, 0, (( __be32)(__builtin_constant_p((__u32)((0x0000FFFF))) ? ({ __u32 __x = (((0x0000FFFF))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32(((0x0000FFFF))))),
         newinet->saddr);

  ipv6_addr_copy(&newnp->rcv_saddr, &newnp->saddr);

  newtp->af_specific = &ipv6_mapped;
  newsk->sk_backlog_rcv = tcp_v4_do_rcv;
  newnp->pktoptions = ((void *)0);
  newnp->opt = ((void *)0);
  newnp->mcast_oif = tcp_v6_iif(skb);
  newnp->mcast_hops = skb->nh.ipv6h->hop_limit;
# 1421 "net/ipv6/tcp_ipv6.c"
  tcp_sync_mss(newsk, newtp->pmtu_cookie);

  return newsk;
 }

 opt = np->opt;

 if (sk_acceptq_is_full(sk))
  goto out_overflow;

 if (np->rxopt.bits.srcrt == 2 &&
     opt == ((void *)0) && treq->pktopts) {
  struct inet6_skb_parm *rxopt = ((struct inet6_skb_parm*)((treq->pktopts)->cb));
  if (rxopt->srcrt)
   opt = ipv6_invert_rthdr(sk, (struct ipv6_rt_hdr *)(treq->pktopts->nh.raw + rxopt->srcrt));
 }

 if (dst == ((void *)0)) {
  struct in6_addr *final_p = ((void *)0), final;
  struct flowi fl;

  __memset_generic((&fl),(0),(sizeof(fl)));
  fl.proto = IPPROTO_TCP;
  ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, &treq->rmt_addr);
  if (opt && opt->srcrt) {
   struct rt0_hdr *rt0 = (struct rt0_hdr *) opt->srcrt;
   ipv6_addr_copy(&final, &fl.nl_u.ip6_u.daddr);
   ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, rt0->addr);
   final_p = &final;
  }
  ipv6_addr_copy(&fl.nl_u.ip6_u.saddr, &treq->loc_addr);
  fl.oif = sk->__sk_common.skc_bound_dev_if;
  fl.uli_u.ports.dport = inet_rsk(req)->rmt_port;
  fl.uli_u.ports.sport = inet_sk(sk)->sport;

  if (ip6_dst_lookup(sk, &dst, &fl))
   goto out;

  if (final_p)
   ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, final_p);

  if ((xfrm_lookup(&dst, &fl, sk, 0)) < 0)
   goto out;
 }

 newsk = tcp_create_openreq_child(sk, req, skb);
 if (newsk == ((void *)0))
  goto out;






 ip6_dst_store(newsk, dst, ((void *)0));
 newsk->sk_route_caps = dst->dev->features &
  ~(2 | 2048);

 newtcp6sk = (struct tcp6_sock *)newsk;
 inet_sk(newsk)->pinet6 = &newtcp6sk->inet6;

 newtp = tcp_sk(newsk);
 newinet = inet_sk(newsk);
 newnp = inet6_sk(newsk);

 __memcpy(newnp,np,sizeof(struct ipv6_pinfo));

 ipv6_addr_copy(&newnp->daddr, &treq->rmt_addr);
 ipv6_addr_copy(&newnp->saddr, &treq->loc_addr);
 ipv6_addr_copy(&newnp->rcv_saddr, &treq->loc_addr);
 newsk->__sk_common.skc_bound_dev_if = treq->iif;





 newinet->opt = ((void *)0);


 newnp->rxopt.all = np->rxopt.all;


 newnp->pktoptions = ((void *)0);
 if (treq->pktopts != ((void *)0)) {
  newnp->pktoptions = skb_clone(treq->pktopts, (0x20u));
  kfree_skb(treq->pktopts);
  treq->pktopts = ((void *)0);
  if (newnp->pktoptions)
   skb_set_owner_r(newnp->pktoptions, newsk);
 }
 newnp->opt = ((void *)0);
 newnp->mcast_oif = tcp_v6_iif(skb);
 newnp->mcast_hops = skb->nh.ipv6h->hop_limit;







 if (opt) {
  newnp->opt = ipv6_dup_options(newsk, opt);
  if (opt != np->opt)
   sock_kfree_s(sk, opt, opt->tot_len);
 }

 newtp->ext_header_len = 0;
 if (newnp->opt)
  newtp->ext_header_len = newnp->opt->opt_nflen +
     newnp->opt->opt_flen;

 tcp_sync_mss(newsk, dst_mtu(dst));
 newtp->advmss = dst_metric(dst, RTAX_ADVMSS);
 tcp_initialize_rcv_mss(newsk);

 newinet->daddr = newinet->saddr = newinet->rcv_saddr = (( __be32)((__u32)( (((__u32)((0x7f000006)) & (__u32)0x000000ffUL) << 24) | (((__u32)((0x7f000006)) & (__u32)0x0000ff00UL) << 8) | (((__u32)((0x7f000006)) & (__u32)0x00ff0000UL) >> 8) | (((__u32)((0x7f000006)) & (__u32)0xff000000UL) >> 24) )));

 __tcp_v6_hash(newsk);
 tcp_inherit_port(sk, newsk);

 return newsk;

out_overflow:
 (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(net_statistics[0]); (__typeof__(net_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[LINUX_MIB_LISTENOVERFLOWS]++);
out:
 (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(net_statistics[0]); (__typeof__(net_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[LINUX_MIB_LISTENDROPS]++);
 if (opt && opt != np->opt)
  sock_kfree_s(sk, opt, opt->tot_len);
 dst_release(dst);
 return ((void *)0);
}

static int tcp_v6_checksum_init(struct sk_buff *skb)
{
 if (skb->ip_summed == 1) {
  skb->ip_summed = 2;
  if (!tcp_v6_check(skb->h.th,skb->len,&skb->nh.ipv6h->saddr,
      &skb->nh.ipv6h->daddr,skb->csum))
   return 0;
  do { if (net_ratelimit()) { printk("<7>" "hw tcp v6 csum failed\n"); } } while(0);
 }
 if (skb->len <= 76) {
  if (tcp_v6_check(skb->h.th,skb->len,&skb->nh.ipv6h->saddr,
     &skb->nh.ipv6h->daddr,skb_checksum(skb, 0, skb->len, 0)))
   return -1;
  skb->ip_summed = 2;
 } else {
  skb->csum = ~tcp_v6_check(skb->h.th,skb->len,&skb->nh.ipv6h->saddr,
       &skb->nh.ipv6h->daddr,0);
 }
 return 0;
}
# 1582 "net/ipv6/tcp_ipv6.c"
static int tcp_v6_do_rcv(struct sock *sk, struct sk_buff *skb)
{
 struct ipv6_pinfo *np = inet6_sk(sk);
 struct tcp_sock *tp;
 struct sk_buff *opt_skb = ((void *)0);
# 1596 "net/ipv6/tcp_ipv6.c"
 if (skb->protocol == (( __be16)(__builtin_constant_p((__u16)((0x0800))) ? ({ __u16 __x = (((0x0800))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16(((0x0800))))))
  return tcp_v4_do_rcv(sk, skb);

 if (sk_filter(sk, skb, 0))
  goto discard;
# 1620 "net/ipv6/tcp_ipv6.c"
 if (np->rxopt.all)
  opt_skb = skb_clone(skb, (0x20u));

 if (sk->__sk_common.skc_state == TCP_ESTABLISHED) {
  do { } while (0);
  if (tcp_rcv_established(sk, skb, skb->h.th, skb->len))
   goto reset;
  do { } while (0);
  if (opt_skb)
   goto ipv6_pktoptions;
  return 0;
 }

 if (skb->len < (skb->h.th->doff<<2) || tcp_checksum_complete(skb))
  goto csum_err;

 if (sk->__sk_common.skc_state == TCP_LISTEN) {
  struct sock *nsk = tcp_v6_hnd_req(sk, skb);
  if (!nsk)
   goto discard;






   if(nsk != sk) {
   if (tcp_child_process(sk, nsk, skb))
    goto reset;
   if (opt_skb)
    __kfree_skb(opt_skb);
   return 0;
  }
 }

 do { } while (0);
 if (tcp_rcv_state_process(sk, skb, skb->h.th, skb->len))
  goto reset;
 do { } while (0);
 if (opt_skb)
  goto ipv6_pktoptions;
 return 0;

reset:
 tcp_v6_send_reset(skb);
discard:
 if (opt_skb)
  __kfree_skb(opt_skb);
 kfree_skb(skb);
 return 0;
csum_err:
 (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[0]); (__typeof__(tcp_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_INERRS]++);
 goto discard;


ipv6_pktoptions:







 tp = tcp_sk(sk);
 if (((struct tcp_skb_cb *)&((opt_skb)->cb[0]))->end_seq == tp->rcv_nxt &&
     !((1 << sk->__sk_common.skc_state) & (TCPF_CLOSE | TCPF_LISTEN))) {
  if (np->rxopt.bits.rxinfo)
   np->mcast_oif = tcp_v6_iif(opt_skb);
  if (np->rxopt.bits.rxhlim)
   np->mcast_hops = opt_skb->nh.ipv6h->hop_limit;
  if (ipv6_opt_accepted(sk, opt_skb)) {
   skb_set_owner_r(opt_skb, sk);
   opt_skb = ((__typeof__(*(&np->pktoptions)))__xchg((unsigned long)(opt_skb),(&np->pktoptions),sizeof(*(&np->pktoptions))));
  } else {
   __kfree_skb(opt_skb);
   opt_skb = ((__typeof__(*(&np->pktoptions)))__xchg((unsigned long)(((void *)0)),(&np->pktoptions),sizeof(*(&np->pktoptions))));
  }
 }

 if (opt_skb)
  kfree_skb(opt_skb);
 return 0;
}

static int tcp_v6_rcv(struct sk_buff **pskb, unsigned int *nhoffp)
{
 struct sk_buff *skb = *pskb;
 struct tcphdr *th;
 struct sock *sk;
 int ret;

 if (skb->pkt_type != 0)
  goto discard_it;




 (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[0]); (__typeof__(tcp_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_INSEGS]++);

 if (!pskb_may_pull(skb, sizeof(struct tcphdr)))
  goto discard_it;

 th = skb->h.th;

 if (th->doff < sizeof(struct tcphdr)/4)
  goto bad_packet;
 if (!pskb_may_pull(skb, th->doff*4))
  goto discard_it;

 if ((skb->ip_summed != 2 &&
      tcp_v6_checksum_init(skb) < 0))
  goto bad_packet;

 th = skb->h.th;
 ((struct tcp_skb_cb *)&((skb)->cb[0]))->seq = (__builtin_constant_p((__u32)(( __u32)(__be32)(th->seq))) ? ({ __u32 __x = ((( __u32)(__be32)(th->seq))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(th->seq))));
 ((struct tcp_skb_cb *)&((skb)->cb[0]))->end_seq = (((struct tcp_skb_cb *)&((skb)->cb[0]))->seq + th->syn + th->fin +
        skb->len - th->doff*4);
 ((struct tcp_skb_cb *)&((skb)->cb[0]))->ack_seq = (__builtin_constant_p((__u32)(( __u32)(__be32)(th->ack_seq))) ? ({ __u32 __x = ((( __u32)(__be32)(th->ack_seq))); ((__u32)( (((__u32)(__x) & (__u32)0x000000ffUL) << 24) | (((__u32)(__x) & (__u32)0x0000ff00UL) << 8) | (((__u32)(__x) & (__u32)0x00ff0000UL) >> 8) | (((__u32)(__x) & (__u32)0xff000000UL) >> 24) )); }) : __fswab32((( __u32)(__be32)(th->ack_seq))));
 ((struct tcp_skb_cb *)&((skb)->cb[0]))->when = 0;
 ((struct tcp_skb_cb *)&((skb)->cb[0]))->flags = ipv6_get_dsfield(skb->nh.ipv6h);
 ((struct tcp_skb_cb *)&((skb)->cb[0]))->sacked = 0;

 sk = __tcp_v6_lookup(&skb->nh.ipv6h->saddr, th->source,
        &skb->nh.ipv6h->daddr, (__builtin_constant_p((__u16)(( __u16)(__be16)(th->dest))) ? ({ __u16 __x = ((( __u16)(__be16)(th->dest))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16((( __u16)(__be16)(th->dest)))), tcp_v6_iif(skb));

 if (!sk)
  goto no_tcp_socket;

process:
 if (sk->__sk_common.skc_state == TCP_TIME_WAIT)
  goto do_time_wait;

 if (!xfrm6_policy_check(sk, XFRM_POLICY_IN, skb))
  goto discard_and_relse;

 if (sk_filter(sk, skb, 0))
  goto discard_and_relse;

 skb->dev = ((void *)0);

 _spin_lock(&((sk)->sk_lock.slock));
 ret = 0;
 if (!((sk)->sk_lock.owner)) {
  if (!tcp_prequeue(sk, skb))
   ret = tcp_v6_do_rcv(sk, skb);
 } else
  do { if (!(sk)->sk_backlog.tail) { (sk)->sk_backlog.head = (sk)->sk_backlog.tail = (skb); } else { ((sk)->sk_backlog.tail)->next = (skb); (sk)->sk_backlog.tail = (skb); } (skb)->next = ((void *)0); } while(0);
 _spin_unlock(&((sk)->sk_lock.slock));

 sock_put(sk);
 return ret ? -1 : 0;

no_tcp_socket:
 if (!xfrm6_policy_check(((void *)0), XFRM_POLICY_IN, skb))
  goto discard_it;

 if (skb->len < (th->doff<<2) || tcp_checksum_complete(skb)) {
bad_packet:
  (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[0]); (__typeof__(tcp_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_INERRS]++);
 } else {
  tcp_v6_send_reset(skb);
 }

discard_it:





 kfree_skb(skb);
 return 0;

discard_and_relse:
 sock_put(sk);
 goto discard_it;

do_time_wait:
 if (!xfrm6_policy_check(((void *)0), XFRM_POLICY_IN, skb)) {
  tcp_tw_put((struct tcp_tw_bucket *) sk);
  goto discard_it;
 }

 if (skb->len < (th->doff<<2) || tcp_checksum_complete(skb)) {
  (({ struct percpu_data *__p = (struct percpu_data *)~(unsigned long)(tcp_statistics[0]); (__typeof__(tcp_statistics[0]))__p->ptrs[((current_thread_info()->cpu))]; })->mibs[TCP_MIB_INERRS]++);
  tcp_tw_put((struct tcp_tw_bucket *) sk);
  goto discard_it;
 }

 switch(tcp_timewait_state_process((struct tcp_tw_bucket *)sk,
       skb, th, skb->len)) {
 case TCP_TW_SYN:
 {
  struct sock *sk2;

  sk2 = tcp_v6_lookup_listener(&skb->nh.ipv6h->daddr, (__builtin_constant_p((__u16)(( __u16)(__be16)(th->dest))) ? ({ __u16 __x = ((( __u16)(__be16)(th->dest))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16((( __u16)(__be16)(th->dest)))), tcp_v6_iif(skb));
  if (sk2 != ((void *)0)) {
   tcp_tw_deschedule((struct tcp_tw_bucket *)sk);
   tcp_tw_put((struct tcp_tw_bucket *)sk);
   sk = sk2;
   goto process;
  }

 }
 case TCP_TW_ACK:
  tcp_v6_timewait_ack(sk, skb);
  break;
 case TCP_TW_RST:
  goto no_tcp_socket;
 case TCP_TW_SUCCESS:;
 }
 goto discard_it;
}

static int tcp_v6_rebuild_header(struct sock *sk)
{
 int err;
 struct dst_entry *dst;
 struct ipv6_pinfo *np = inet6_sk(sk);

 dst = __sk_dst_check(sk, np->dst_cookie);

 if (dst == ((void *)0)) {
  struct inet_sock *inet = inet_sk(sk);
  struct in6_addr *final_p = ((void *)0), final;
  struct flowi fl;

  __memset_generic((&fl),(0),(sizeof(fl)));
  fl.proto = IPPROTO_TCP;
  ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, &np->daddr);
  ipv6_addr_copy(&fl.nl_u.ip6_u.saddr, &np->saddr);
  fl.nl_u.ip6_u.flowlabel = np->flow_label;
  fl.oif = sk->__sk_common.skc_bound_dev_if;
  fl.uli_u.ports.dport = inet->dport;
  fl.uli_u.ports.sport = inet->sport;

  if (np->opt && np->opt->srcrt) {
   struct rt0_hdr *rt0 = (struct rt0_hdr *) np->opt->srcrt;
   ipv6_addr_copy(&final, &fl.nl_u.ip6_u.daddr);
   ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, rt0->addr);
   final_p = &final;
  }

  err = ip6_dst_lookup(sk, &dst, &fl);
  if (err) {
   sk->sk_route_caps = 0;
   return err;
  }
  if (final_p)
   ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, final_p);

  if ((err = xfrm_lookup(&dst, &fl, sk, 0)) < 0) {
   sk->sk_err_soft = -err;
   dst_release(dst);
   return err;
  }

  ip6_dst_store(sk, dst, ((void *)0));
  sk->sk_route_caps = dst->dev->features &
   ~(2 | 2048);
 }

 return 0;
}

static int tcp_v6_xmit(struct sk_buff *skb, int ipfragok)
{
 struct sock *sk = skb->sk;
 struct inet_sock *inet = inet_sk(sk);
 struct ipv6_pinfo *np = inet6_sk(sk);
 struct flowi fl;
 struct dst_entry *dst;
 struct in6_addr *final_p = ((void *)0), final;

 __memset_generic((&fl),(0),(sizeof(fl)));
 fl.proto = IPPROTO_TCP;
 ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, &np->daddr);
 ipv6_addr_copy(&fl.nl_u.ip6_u.saddr, &np->saddr);
 fl.nl_u.ip6_u.flowlabel = np->flow_label;
 do { if (INET_ECN_is_capable(inet_sk(sk)->tos)) (fl.nl_u.ip6_u.flowlabel) |= (( __be16)((__u16)( (((__u16)((INET_ECN_ECT_0 << 4)) & (__u16)0x00ffU) << 8) | (((__u16)((INET_ECN_ECT_0 << 4)) & (__u16)0xff00U) >> 8) ))); } while (0);
 fl.oif = sk->__sk_common.skc_bound_dev_if;
 fl.uli_u.ports.sport = inet->sport;
 fl.uli_u.ports.dport = inet->dport;

 if (np->opt && np->opt->srcrt) {
  struct rt0_hdr *rt0 = (struct rt0_hdr *) np->opt->srcrt;
  ipv6_addr_copy(&final, &fl.nl_u.ip6_u.daddr);
  ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, rt0->addr);
  final_p = &final;
 }

 dst = __sk_dst_check(sk, np->dst_cookie);

 if (dst == ((void *)0)) {
  int err = ip6_dst_lookup(sk, &dst, &fl);

  if (err) {
   sk->sk_err_soft = -err;
   return err;
  }

  if (final_p)
   ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, final_p);

  if ((err = xfrm_lookup(&dst, &fl, sk, 0)) < 0) {
   sk->sk_route_caps = 0;
   dst_release(dst);
   return err;
  }

  ip6_dst_store(sk, dst, ((void *)0));
  sk->sk_route_caps = dst->dev->features &
   ~(2 | 2048);
 }

 skb->dst = dst_clone(dst);


 ipv6_addr_copy(&fl.nl_u.ip6_u.daddr, &np->daddr);

 return ip6_xmit(sk, skb, &fl, np->opt, 0);
}

static void v6_addr2sockaddr(struct sock *sk, struct sockaddr * uaddr)
{
 struct ipv6_pinfo *np = inet6_sk(sk);
 struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *) uaddr;

 sin6->sin6_family = 10;
 ipv6_addr_copy(&sin6->sin6_addr, &np->daddr);
 sin6->sin6_port = inet_sk(sk)->dport;

 sin6->sin6_flowinfo = 0;
 sin6->sin6_scope_id = 0;
 if (sk->__sk_common.skc_bound_dev_if &&
     ipv6_addr_type(&sin6->sin6_addr) & 0x0020U)
  sin6->sin6_scope_id = sk->__sk_common.skc_bound_dev_if;
}

static int tcp_v6_remember_stamp(struct sock *sk)
{

 return 0;
}

static struct tcp_func ipv6_specific = {
 .queue_xmit = tcp_v6_xmit,
 .send_check = tcp_v6_send_check,
 .rebuild_header = tcp_v6_rebuild_header,
 .conn_request = tcp_v6_conn_request,
 .syn_recv_sock = tcp_v6_syn_recv_sock,
 .remember_stamp = tcp_v6_remember_stamp,
 .net_header_len = sizeof(struct ipv6hdr),

 .setsockopt = ipv6_setsockopt,
 .getsockopt = ipv6_getsockopt,
 .addr2sockaddr = v6_addr2sockaddr,
 .sockaddr_len = sizeof(struct sockaddr_in6)
};





static struct tcp_func ipv6_mapped = {
 .queue_xmit = ip_queue_xmit,
 .send_check = tcp_v4_send_check,
 .rebuild_header = tcp_v4_rebuild_header,
 .conn_request = tcp_v6_conn_request,
 .syn_recv_sock = tcp_v6_syn_recv_sock,
 .remember_stamp = tcp_v4_remember_stamp,
 .net_header_len = sizeof(struct iphdr),

 .setsockopt = ipv6_setsockopt,
 .getsockopt = ipv6_getsockopt,
 .addr2sockaddr = v6_addr2sockaddr,
 .sockaddr_len = sizeof(struct sockaddr_in6)
};






static int tcp_v6_init_sock(struct sock *sk)
{
 struct tcp_sock *tp = tcp_sk(sk);

 skb_queue_head_init(&tp->out_of_order_queue);
 tcp_init_xmit_timers(sk);
 tcp_prequeue_init(tp);

 tp->rto = ((unsigned)(3*250));
 tp->mdev = ((unsigned)(3*250));






 tp->snd_cwnd = 2;




 tp->snd_ssthresh = 0x7fffffff;
 tp->snd_cwnd_clamp = ~0;
 tp->mss_cache = 536;

 tp->reordering = sysctl_tcp_reordering;

 sk->__sk_common.skc_state = TCP_CLOSE;

 tp->af_specific = &ipv6_specific;
 tp->ca_ops = &tcp_init_congestion_ops;
 sk->sk_write_space = sk_stream_write_space;
 sock_set_flag(sk, SOCK_USE_WRITE_QUEUE);

 sk->sk_sndbuf = sysctl_tcp_wmem[1];
 sk->sk_rcvbuf = sysctl_tcp_rmem[1];

 atomic_inc(&tcp_sockets_allocated);

 return 0;
}

static int tcp_v6_destroy_sock(struct sock *sk)
{
 extern int tcp_v4_destroy_sock(struct sock *sk);

 tcp_v4_destroy_sock(sk);
 return inet6_destroy_sock(sk);
}


static void get_openreq6(struct seq_file *seq,
    struct sock *sk, struct request_sock *req, int i, int uid)
{
 struct in6_addr *dest, *src;
 int ttd = req->expires - jiffies;

 if (ttd < 0)
  ttd = 0;

 src = &tcp6_rsk(req)->loc_addr;
 dest = &tcp6_rsk(req)->rmt_addr;
 seq_printf(seq,
     "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X "
     "%02X %08X:%08X %02X:%08lX %08X %5d %8d %d %d %p\n",
     i,
     src->in6_u.u6_addr32[0], src->in6_u.u6_addr32[1],
     src->in6_u.u6_addr32[2], src->in6_u.u6_addr32[3],
     (__builtin_constant_p((__u16)(( __u16)(__be16)(inet_sk(sk)->sport))) ? ({ __u16 __x = ((( __u16)(__be16)(inet_sk(sk)->sport))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16((( __u16)(__be16)(inet_sk(sk)->sport)))),
     dest->in6_u.u6_addr32[0], dest->in6_u.u6_addr32[1],
     dest->in6_u.u6_addr32[2], dest->in6_u.u6_addr32[3],
     (__builtin_constant_p((__u16)(( __u16)(__be16)(inet_rsk(req)->rmt_port))) ? ({ __u16 __x = ((( __u16)(__be16)(inet_rsk(req)->rmt_port))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16((( __u16)(__be16)(inet_rsk(req)->rmt_port)))),
     TCP_SYN_RECV,
     0,0,
     1,
     jiffies_to_clock_t(ttd),
     req->retrans,
     uid,
     0,
     0,
     0, req);
}

static void get_tcp6_sock(struct seq_file *seq, struct sock *sp, int i)
{
 struct in6_addr *dest, *src;
 __u16 destp, srcp;
 int timer_active;
 unsigned long timer_expires;
 struct inet_sock *inet = inet_sk(sp);
 struct tcp_sock *tp = tcp_sk(sp);
 struct ipv6_pinfo *np = inet6_sk(sp);

 dest = &np->daddr;
 src = &np->rcv_saddr;
 destp = (__builtin_constant_p((__u16)(( __u16)(__be16)(inet->dport))) ? ({ __u16 __x = ((( __u16)(__be16)(inet->dport))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16((( __u16)(__be16)(inet->dport))));
 srcp = (__builtin_constant_p((__u16)(( __u16)(__be16)(inet->sport))) ? ({ __u16 __x = ((( __u16)(__be16)(inet->sport))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16((( __u16)(__be16)(inet->sport))));
 if (tp->pending == 1) {
  timer_active = 1;
  timer_expires = tp->timeout;
 } else if (tp->pending == 3) {
  timer_active = 4;
  timer_expires = tp->timeout;
 } else if (timer_pending(&sp->sk_timer)) {
  timer_active = 2;
  timer_expires = sp->sk_timer.expires;
 } else {
  timer_active = 0;
  timer_expires = jiffies;
 }

 seq_printf(seq,
     "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X "
     "%02X %08X:%08X %02X:%08lX %08X %5d %8d %lu %d %p %u %u %u %u %d\n",
     i,
     src->in6_u.u6_addr32[0], src->in6_u.u6_addr32[1],
     src->in6_u.u6_addr32[2], src->in6_u.u6_addr32[3], srcp,
     dest->in6_u.u6_addr32[0], dest->in6_u.u6_addr32[1],
     dest->in6_u.u6_addr32[2], dest->in6_u.u6_addr32[3], destp,
     sp->__sk_common.skc_state,
     tp->write_seq-tp->snd_una, tp->rcv_nxt-tp->copied_seq,
     timer_active,
     jiffies_to_clock_t(timer_expires - jiffies),
     tp->retransmits,
     sock_i_uid(sp),
     tp->probes_out,
     sock_i_ino(sp),
     ((&sp->__sk_common.skc_refcnt)->counter), sp,
     tp->rto, tp->ack.ato, (tp->ack.quick<<1)|tp->ack.pingpong,
     tp->snd_cwnd, tp->snd_ssthresh>=0xFFFF?-1:tp->snd_ssthresh
     );
}

static void get_timewait6_sock(struct seq_file *seq,
          struct tcp_tw_bucket *tw, int i)
{
 struct in6_addr *dest, *src;
 __u16 destp, srcp;
 int ttd = tw->tw_ttd - jiffies;

 if (ttd < 0)
  ttd = 0;

 dest = &tw->tw_v6_daddr;
 src = &tw->tw_v6_rcv_saddr;
 destp = (__builtin_constant_p((__u16)(( __u16)(__be16)(tw->tw_dport))) ? ({ __u16 __x = ((( __u16)(__be16)(tw->tw_dport))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16((( __u16)(__be16)(tw->tw_dport))));
 srcp = (__builtin_constant_p((__u16)(( __u16)(__be16)(tw->tw_sport))) ? ({ __u16 __x = ((( __u16)(__be16)(tw->tw_sport))); ((__u16)( (((__u16)(__x) & (__u16)0x00ffU) << 8) | (((__u16)(__x) & (__u16)0xff00U) >> 8) )); }) : __fswab16((( __u16)(__be16)(tw->tw_sport))));

 seq_printf(seq,
     "%4d: %08X%08X%08X%08X:%04X %08X%08X%08X%08X:%04X "
     "%02X %08X:%08X %02X:%08lX %08X %5d %8d %d %d %p\n",
     i,
     src->in6_u.u6_addr32[0], src->in6_u.u6_addr32[1],
     src->in6_u.u6_addr32[2], src->in6_u.u6_addr32[3], srcp,
     dest->in6_u.u6_addr32[0], dest->in6_u.u6_addr32[1],
     dest->in6_u.u6_addr32[2], dest->in6_u.u6_addr32[3], destp,
     tw->tw_substate, 0, 0,
     3, jiffies_to_clock_t(ttd), 0, 0, 0, 0,
     ((&tw->__tw_common.skc_refcnt)->counter), tw);
}


static int tcp6_seq_show(struct seq_file *seq, void *v)
{
 struct tcp_iter_state *st;

 if (v == ((void *)1)) {
  seq_puts(seq,
    "  sl  "
    "local_address                         "
    "remote_address                        "
    "st tx_queue rx_queue tr tm->when retrnsmt"
    "   uid  timeout inode\n");
  goto out;
 }
 st = seq->private;

 switch (st->state) {
 case TCP_SEQ_STATE_LISTENING:
 case TCP_SEQ_STATE_ESTABLISHED:
  get_tcp6_sock(seq, v, st->num);
  break;
 case TCP_SEQ_STATE_OPENREQ:
  get_openreq6(seq, st->syn_wait_sk, v, st->num, st->uid);
  break;
 case TCP_SEQ_STATE_TIME_WAIT:
  get_timewait6_sock(seq, v, st->num);
  break;
 }
out:
 return 0;
}

static struct file_operations tcp6_seq_fops;
static struct tcp_seq_afinfo tcp6_seq_afinfo = {
 .owner = ((struct module *)0),
 .name = "tcp6",
 .family = 10,
 .seq_show = tcp6_seq_show,
 .seq_fops = &tcp6_seq_fops,
};

int __attribute__ ((__section__ (".init.text"))) tcp6_proc_init(void)
{
 return tcp_proc_register(&tcp6_seq_afinfo);
}

void tcp6_proc_exit(void)
{
 tcp_proc_unregister(&tcp6_seq_afinfo);
}


struct proto tcpv6_prot = {
 .name = "TCPv6",
 .owner = ((struct module *)0),
 .close = tcp_close,
 .connect = tcp_v6_connect,
 .disconnect = tcp_disconnect,
 .accept = tcp_accept,
 .ioctl = tcp_ioctl,
 .init = tcp_v6_init_sock,
 .destroy = tcp_v6_destroy_sock,
 .shutdown = tcp_shutdown,
 .setsockopt = tcp_setsockopt,
 .getsockopt = tcp_getsockopt,
 .sendmsg = tcp_sendmsg,
 .recvmsg = tcp_recvmsg,
 .backlog_rcv = tcp_v6_do_rcv,
 .hash = tcp_v6_hash,
 .unhash = tcp_unhash,
 .get_port = tcp_v6_get_port,
 .enter_memory_pressure = tcp_enter_memory_pressure,
 .sockets_allocated = &tcp_sockets_allocated,
 .memory_allocated = &tcp_memory_allocated,
 .memory_pressure = &tcp_memory_pressure,
 .sysctl_mem = sysctl_tcp_mem,
 .sysctl_wmem = sysctl_tcp_wmem,
 .sysctl_rmem = sysctl_tcp_rmem,
 .max_header = (128 + (96 + 48)),
 .obj_size = sizeof(struct tcp6_sock),
 .rsk_prot = &tcp6_request_sock_ops,
};

static struct inet6_protocol tcpv6_protocol = {
 .handler = tcp_v6_rcv,
 .err_handler = tcp_v6_err,
 .flags = 0x1|0x2,
};

extern struct proto_ops inet6_stream_ops;

static struct inet_protosw tcpv6_protosw = {
 .type = SOCK_STREAM,
 .protocol = IPPROTO_TCP,
 .prot = &tcpv6_prot,
 .ops = &inet6_stream_ops,
 .capability = -1,
 .no_check = 0,
 .flags = 0x02,
};

void __attribute__ ((__section__ (".init.text"))) tcpv6_init(void)
{

 if (inet6_add_protocol(&tcpv6_protocol, IPPROTO_TCP) < 0)
  printk("<3>" "tcpv6_init: Could not register protocol\n");
 inet6_register_protosw(&tcpv6_protosw);
}
