    .type   foo, @function
foo:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movq    $7,  %rdi
    call    bar
    addq    $1, %rax
    ret
