    .text
.globl _brk
_brk:
    pushq %rbp
    movq %rsp, %rbp
    
    movq $12, %rax
    syscall
    
    movq %rbp, %rsp
    popq %rbp 
    ret
