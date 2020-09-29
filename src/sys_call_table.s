# 1 "sys_call_table.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "sys_call_table.S"
# 1 "include/asm.h" 1
# 2 "sys_call_table.S" 2
# 1 "include/segment.h" 1
# 3 "sys_call_table.S" 2

.globl sys_call_table; .type sys_call_table, @function; .align 0; sys_call_table:
 .long sys_ni_syscall
 .long sys_exit
 .long sys_fork
 .long sys_read
 .long sys_write
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_gettime
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_yield
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_set_sched_policy
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_getpid
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_ni_syscall
 .long sys_get_stats
.globl MAX_SYSCALL
MAX_SYSCALL = (. - sys_call_table)/4
