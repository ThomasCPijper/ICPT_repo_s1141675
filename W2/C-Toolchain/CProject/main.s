    .file   "main.c"
    .text
    .globl  add
    .type   add, @function
add:
.LFBO:
    .cfi_startproc
    endbr64
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi    offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6
    movl    %edi, -4(%rbp)
    movl    %esi, -8(%rbp)
    movl    -4(%rbp), %edx
    movl    -8(%rbp), %eax
    addl    %edx, %eax
    popq    %rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.LFEO:
    .size   add, .-add
    .globl  subtract
    .type   subtract, @function
subtract:
.LFB1:
    .cfi_startproc
    endbr64
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi    offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6
    movl    %edi, -4(%rbp)
    movl    %esi, -8(%rbp)
    movl    -4(%rbp), %eax
    subl    -8(%rbp), %eax
    popq    %rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.LFE1:
    .size   subtract, .-subtract
    .globl  multiply
    type    multiply, @function
multiply:
.LFB2:
    .cfi_startproc
    endbr64
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6
    movl    %edi, -4(%rbp)
    movl    %esi, -8(%rbp)
    movl    -4(%rbp), %eax
    imull   -8(%rbp), %eax
    popq    %rbp
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.LFE2:
    .size   multiply, .-multiply
    .section    .rodata
.LCO:
    .string "Kies 2 getallen:
.LC1:
    .string "%d"
    .align 8
.LC2:
    .string "Difference of addtion and multiplication: %d\n"
    .text
    .globl  main
    .type   main, @function
main:
.LFB3:
    .cfi_startproc
    endbr64
    pushq   %rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    movq    %rsp, %rbp
    .cfi_def_cfa_register 6
    subq    $32, %rsp
    movq    %fs:40, %rax
    movq    %rax, -8(%rbp)
    xorl    %eax, %eax
    leaq    .LCO(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    printf@PLT
    leaq    -28(%rbp), %rax
    movq    %rax, %rsi
    leaq    .LC1(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    __isoc99_scanf@PLT
    leaq    -24(%rbp), %rax
    movq    %rax, %rsi
    leaq    .LC1(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    __isoc99 scanf@PLT
    movl    -24(%rbp), %edx
    movl    -28(%rbp), %eax
    movl    %edx, %esi
    movl    %eax, %edi
    call    add
    movl    %eax, -20(%rbp)
    movl    -24(%rbp), %edx
    movl    -28(%rbp), %eax
    movl    %edx, %esi
    movl    %eax, %edi
    call    multiply
    movl    %eax, -16(%rbp)
    movl    -16 (%rbp), %edx
    movl    -20(%rbp), %eax
    movl    %edx, %esi
    movl    %eax, %edi
    call    subtract
    movl    %eax, -12(%rbp)
    movl    -12(%rbp), %eax
    movl    %eax, %esi
    leaq    .LC2(%rip), %rax
    movq    %rax, %rdi
    movl    $0, %eax
    call    printf@PLT
    movl    $0, %eax
    movq    -8(%rbp), %rdx
    subq    %fs:40, %rdx
    je .L9
    call    __stack_chk_fail@PLT
.L9:
    leave
    .cfi_def_cfa 7, 8
    ret
    .cfi_endproc
.LFE3:
    .size main, .-main
    .ident "GCC: (Ubuntu 13.2.0-23ubuntu4) 13.2.0"
    .section    .note.GNU-stack,"",@progbits
    .section    .note.gnu.property, "a"
    .align 8
    .long   1f - 0f
    .long   4f - 1f
    .long   5
0:
    .string "GNU"
1:
    .align 8
    .long   0xc0000002
    .long   3f - 2f
2:
    .long   0x3
3:
    .align 8
4:
