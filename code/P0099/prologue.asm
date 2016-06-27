pushq  %rbp  /* save RBP */
pushq  %rbx  /* save RBX */
pushq  %r15  /* save R15 */
pushq  %r14  /* save R14 */
pushq  %r13  /* save R13 */
pushq  %r12  /* save R12 */

/* store RSP in RAX */
/* used to synthesize instance of suspended std::execution_context<> */
movq  %rsp, %rax

/* restore RSP from RDI */
/* stack-pointer of std::execution_context<> that has to be resumed */
movq  %rdi, %rsp

popq  %r12  /* restrore R12 */
popq  %r13  /* restrore R13 */
popq  %r14  /* restrore R14 */
popq  %r15  /* restrore R15 */
popq  %rbx  /* restrore RBX */
popq  %rbp  /* restrore RBP */

/* restore return-address */
popq  %r8

/* prepartion of returned data skipped */
...

/* indirect jump to context */
jmp  *%r8
