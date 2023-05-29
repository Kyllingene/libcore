.text
.globl _print
.type _print, @function
_print:
    push %rbp
    mov %rsp, %rbp
    
	mov %rsi, %rdx /* count */
	mov %rdi, %rsi /* buf */
    mov $1, %rdi   /* fd (stdout) */
	mov $1, %rax   /* write */
    syscall

    mov %rbp, %rsp
    pop %rbp 
    ret
