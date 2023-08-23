section .data
    str: db "%c", 0

section .text
    extern dprintf
    global _start

_start:
    xor rbp, rbp
    sub rsp, 0x20 ; offset de c
    mov byte [rsp + 0], 0x60 ; i, offset de buf + st_size + i
    mov byte [rsp + 1], 0x61 ; i, offset de buf + st_size + i
    mov byte [rsp + 2], 0x62 ; i, offset de buf + st_size + i
    mov byte [rsp + 3], 0x63 ; i, offset de buf + st_size + i
    mov byte [rsp + 4], 0x64 ; i, offset de buf + st_size + i
    mov byte [rsp + 5], 0x65 ; i, offset de buf + st_size + i
    mov byte [rsp + 6], 0x66 ; i, offset de buf + st_size + i
    mov byte [rsp + 7], 0x67 ; i, offset de buf + st_size + i
    mov byte [rsp + 8], 0x68 ; i, offset de buf + st_size + i
    mov byte [rsp + 9], 0x69 ; i, offset de buf + st_size + i
    mov byte [rsp + 10], 0x6a ; i, offset de buf + st_size + i
    mov byte [rsp + 11], 0x6b ; i, offset de buf + st_size + i
    mov byte [rsp + 12], 0x6c ; i, offset de buf + st_size + i
    mov byte [rsp + 13], 0x6d ; i, offset de buf + st_size + i
    mov byte [rsp + 14], 0x6e ; i, offset de buf + st_size + i
    mov byte [rsp + 15], 0x6f ; i, offset de buf + st_size + i
    mov byte [rsp + 16], 0x70 ; i, offset de buf + st_size + i
    mov word [rsp + 0x1d], 0xF ; offset c - 4
    mov r8, [rsp + 0x1d]
    and r8, 0xff
    mov rax, 0
    mov rdi, 1
    lea rsi, [str]
    mov rdx, [rsp + r8]
    call dprintf
    sub word [rsp + 0x1d], 1
    cmp word [rsp + 0x1d], 0x0
    jg $ - 51

_exit:
    add rsp, 0x20
    mov rax, 60
    xor rdi, rdi
    syscall