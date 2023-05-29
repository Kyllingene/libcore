.text

.globl _read
.type _read, @function
.globl _write
.type _write, @function
.globl _open
.type _open, @function
.globl _close
.type _close, @function

_read:
    push %ebp
    mov %esp, %ebp

	mov $0, %eax /* read */
    syscall

    mov %ebp, %esp
    pop %ebp 
    ret

_write:
    push %ebp
    mov %esp, %ebp

	mov $1, %eax /* read */
    syscall

    mov %ebp, %esp
    pop %ebp 
    ret

_open:
    push %ebp
    mov %esp, %ebp

	mov $2, %eax /* open */
    syscall

    mov %ebp, %esp
    pop %ebp
    ret

_close:
    push %ebp
    mov %esp, %ebp

	mov $3, %eax /* close */
    syscall

    mov %ebp, %esp
    pop %ebp
    ret
