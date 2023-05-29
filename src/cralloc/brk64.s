    .text
.globl _brk
.type _brk, @function
_brk:
    push %rbp
    mov %rsp, %rbp
    
    mov $12, %rax
    syscall
    
    mov %rbp, %rsp
    pop %rbp
    ret
