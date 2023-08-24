section .data
    str: db "%c", 0

section .text
    extern dprintf
    global _start

_start:
    nop
    nop
    xor rbp, rbp
    mov word rdx, 0x22; offset c - 4
    mov rdi, [rsp + 0x1d]
    and rdi, 0xff
    inc rdi
    mov rsi, [rsp + 0x1d]
    and rsi, 0xff
    mov rdi, [rsp + rdi]
    and rdi, 0xff
    mov rsi, [rsp + rsi]
    and rsi, 0xff
    xor rsi, rdi
    sub word [rsp + 0x1d], 1
    cmp word [rsp + 0x1d], 0x1
    jg $ - 65