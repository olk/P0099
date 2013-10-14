.struct 0
OFF_RBX: .quad 0
OFF_R12: .quad 0
OFF_R13: .quad 0
OFF_R14: .quad 0
OFF_R15: .quad 0
OFF_RBP: .quad 0
OFF_RSP: .quad 0
OFF_RIP: .quad 0

.text
jump:
    /* first argument, RDI, points to control-block (X) from which we jump */
    /* second argument, RSI, points to control-block (Y) to which we jump */
    /* third argument, RDX, parameter we want to pass to jumped context */

    /* save current non-volatile registers into X */
    movq  %rbx,  OFF_RBX(%rdi)  /* save RBX */    
    movq  %r12,  OFF_R12(%rdi)  /* save R12 */ 
    movq  %r13,  OFF_R13(%rdi)  /* save R13 */
    movq  %r14,  OFF_R14(%rdi)  /* save R14 */
    movq  %r15,  OFF_R15(%rdi)  /* save R15 */
    movq  %rbp,  OFF_RBP(%rdi)  /* save RBP */

    /* save stack pointer and return address */
    /* (offset saved stack pointer by 8 to skip return address) */
    leaq  0x8(%rsp), %rax  /* extract stack pointer */
    movq  %rax,      OFF_RSP(%rdi)  /* save stack pointer */
    movq  (%rsp),    %rax  /* extract return address */
    movq  %rax,      OFF_RIP(%rdi)  /* save return address */

    /* restore non-volatile registers from Y */
    movq  OFF_RBX(%rsi), %rbx   /* restore RBX */
    movq  OFF_R12(%rsi), %r12   /* restore R12 */
    movq  OFF_R13(%rsi), %r13   /* restore R13 */
    movq  OFF_R14(%rsi), %r14   /* restore R14 */
    movq  OFF_R15(%rsi), %r15   /* restore R15 */
    movq  OFF_RBP(%rsi), %rbp   /* restore RBP */

    /* switch stacks, prepare to jump */
    movq  OFF_RSP(%rsi), %rsp  /* restore stack pointer */
    movq  OFF_RIP(%rsi), %rcx  /* restore return address */

    /* data passing */
    movq  %rdx,  %rax  /* use third arg as return value after jump */
    movq  %rdx,  %rdi  /* use third arg as first arg in context function */

    /* context switch */
    jmp   *%rcx  /* indirect jump to context via restored return address */
