    .text
.globl _brk
_brk:
    pushl %ebp
    movl %esp, %ebp
    
    movl $12, %eax
    syscall
    
    movl %ebp, %esp
    popl %ebp 
    ret
