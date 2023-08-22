section .data
    str: db "%x%c", 0

section .text
    extern dprintf
    global _start

_print:
    push rbp
    ; mov rbp, rsp

    leave
    ret

_loop:
    push rbp
    mov rbp, rsp
    mov word [rsp - 0x8 - 0x1c], 0xF
    sub word [rsp - 0x8 - 0x1c], 1
    mov r8, [rsp - 0x8 - 0x1c]
    mov rax, 0
    mov rdi, 1
    lea rsi, [str]
    mov rdx, [rsp - 0x8 - 0x1]
    mov rcx, 10
    call dprintf
    cmp word [rsp - 0x8 - 0x1c], 0x0
    jg _loop + 0xa
    leave
    ret

_start:
    xor rbp, rbp
    add rsp, 0x20
    mov word [rsp - 1], 0x61
    mov word [rsp - 2], 0x62
    mov word [rsp - 3], 0x63
    mov word [rsp - 4], 0x64
    mov word [rsp - 5], 0x65
    mov word [rsp - 6], 0x66
    mov word [rsp - 7], 0x67
    mov word [rsp - 8], 0x68
    mov word [rsp - 9], 0x69
    mov word [rsp - 10], 0x6a
    mov word [rsp - 11], 0x6b
    mov word [rsp - 12], 0x6c
    mov word [rsp - 13], 0x6d
    mov word [rsp - 14], 0x6e
    mov word [rsp - 15], 0x6f
    mov word [rsp - 16], 0x70
    call _loop


_exit:
    sub rsp, 0x20
    mov rax, 60
    xor rdi, rdi
    syscall