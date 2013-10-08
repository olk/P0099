    .type   bar, @function
bar:
    pushq   %rbp
    movq    %rsp, %rbp
    movq    %rdi, -4(%rbp)
    movq    -4(%rbp), %rax
    popq    %rbp
    ret
