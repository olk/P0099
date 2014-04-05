.text
.globl jump
.type jump,@function
jump:
    /* first argument, RDI, points to stack (X) from which we jump */
    /* second argument, RSI, points to stack (Y) to which we jump */
    /* third argument, RDX, parameter we want to pass to jumped context */

    /* save current non-volatile registers to stack X */
    pushq  %rbp  /* save RBP */
    pushq  %rbx  /* save RBX */
    pushq  %r15  /* save R15 */
    pushq  %r14  /* save R14 */
    pushq  %r13  /* save R13 */
    pushq  %r12  /* save R12 */

    /* switch stacks, prepare to jump */
    /* store RSP (pointing to context-data) in RDI */
    movq  %rsp, (%rdi)
    /* restore RSP (pointing to context-data) from RSI */
    movq  %rsi, %rsp

    /* restore non-volatile registers from stack Y */
    popq  %r12  /* restrore R12 */
    popq  %r13  /* restrore R13 */
    popq  %r14  /* restrore R14 */
    popq  %r15  /* restrore R15 */
    popq  %rbx  /* restrore RBX */
    popq  %rbp  /* restrore RBP */

    /* restore return-address */
    popq  %r8

    /* data passing */
    movq  %rdx,  %rax  /* use third arg as return value after jump */
    movq  %rdx,  %rdi  /* use third arg as first arg in context function */

    /* context switch */
    jmp   *%r8  /* indirect jump to context via restored return address */
.size jump,.-jump
