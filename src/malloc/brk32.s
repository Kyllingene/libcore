    .text
.globl _brk
.type _brk, @function
_brk:
    push %ebp
    mov %esp, %ebp
    
    mov $12, %eax
    syscall
    
    mov %ebp, %esp
    pop %ebp
    ret
