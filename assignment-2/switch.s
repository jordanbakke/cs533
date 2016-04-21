.globl thread_switch
.globl thread_start

thread_switch:
    movq  %rsp, (%rdi)
    movq  (%rsi), %rsp
    ret

thread_start:
    pushq %rbx
    pushq %rbp
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
    
    movq  %rsp, (%rdi)
    movq  (%rsi), %rsp
    
    call thread_wrap
