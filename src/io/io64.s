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
    push %rbp
    mov %rsp, %rbp

	mov $0, %rax /* read */
    syscall

    mov %rbp, %rsp
    pop %rbp 
    ret

_write:
    push %rbp
    mov %rsp, %rbp

	mov $1, %rax /* read */
    syscall

    mov %rbp, %rsp
    pop %rbp 
    ret

_open:
    push %rbp
    mov %rsp, %rbp

	mov $2, %rax /* open */
    syscall

    mov %rbp, %rsp
    pop %rbp
    ret

_close:
    push %rbp
    mov %rsp, %rbp

	mov $3, %rax /* close */
    syscall

    mov %rbp, %rsp
    pop %rbp
    ret
