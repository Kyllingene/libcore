.text
.globl _print
.type _print, @function
_print:
    push %ebp
    mov %esp, %ebp
    
	mov %esi, %edx /* count */
	mov %edi, %esi /* buf */
    mov $1, %edi   /* fd (stdout) */
	mov $1, %eax   /* write */
    syscall

    mov %ebp, %esp
    pop %ebp 
    ret
