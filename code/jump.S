jump:
    movq  %rbx,      (%rdi)    
    movq  %r12,      0x8(%rdi) 
    movq  %r13,      0x10(%rdi)
    movq  %r14,      0x18(%rdi)
    movq  %r15,      0x20(%rdi)
    movq  %rbp,      0x28(%rdi)

    leaq  0x8(%rsp), %rax
    movq  %rax,      0x30(%rdi)
    movq  (%rsp),    %rax
    movq  %rax,      0x38(%rdi)

    movq  (%rsi),     %rbx
    movq  0x8(%rsi),  %r12
    movq  0x10(%rsi), %r13
    movq  0x18(%rsi), %r14
    movq  0x20(%rsi), %r15
    movq  0x28(%rsi), %rbp

    movq  0x30(%rsi), %rsp
    movq  0x38(%rsi), %rcx

    movq  %rdx,       %rax
    movq  %rdx,       %rdi

    jmp   *%rcx
