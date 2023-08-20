section .data
    str: db "%x%c", 0

section .text
    extern dprintf
    global _start

_make_xor:

    mov rax, 0
    mov rdi, 1
    lea rsi, [str]
    mov rdx, [rsp + 5]
    mov rcx, 10
    call dprintf
    jmp _exit

_start:
    xor rbp, rbp
    sub rsp, 0xF
    mov word [rsp + 1], 0x61
    mov word [rsp + 2], 0x62
    mov word [rsp + 3], 0x63
    mov word [rsp + 4], 0x64
    mov word [rsp + 5], 0x65


_exit:
    add rsp, 0xF
    mov rax, 60
    xor rdi, rdi
    syscall