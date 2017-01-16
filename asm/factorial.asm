BITS 64

section .text
global _start

fact:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 0x20
    cmp     rdi, 0x0
    jz      fact_base
    mov     [rbp-0x8], rdi
    sub     rdi, 1 
    call    fact
    imul    rax, [rbp-0x8]
    mov     rsp, rbp
    pop     rbp
    ret

fact_base:
    mov     rax, 1
    mov     rsp, rbp
    pop     rbp
    ret

_start:
    mov     rdi, 5
    call    fact
    mov     rdi, rax
    mov     rax, 60
    syscall
