section .data
    str: db "%c", 0

section .text
    extern dprintf
    global _start

_start:
    nop
    nop
    xor rbp, rbp
    mov rdx, 0x00
    mov rcx, 0x1050 ; offset encrypted symbol
    mov rdi, rcx + rdx
    and rdi, 0xff
    inc rdi
    mov rsi, $ - 110 + rdx
    and rsi, 0xff
    mov rdi, [rsp + rdi]
    and rdi, 0xff
    mov rsi, [rsp + rsi]
    and rsi, 0xff
    xor rsi, rdi
    cmp word rdx, 0x22 ; key size
    inc rdx
    jg $ - 65