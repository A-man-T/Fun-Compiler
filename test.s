    .data
format: .byte '%', 'l', 'u', 10, 0
    .text
._print:
      push %rbp
      mov %rsp, %rbp
      and $-16,%rsp
      mov 16(%rbp), %rsi
      lea format(%rip),%rdi
      xor %rax,%rax
      .extern printf
      call printf
      mov %rbp,%rsp
      pop %rbp
      retq
    .global main
main:
      push %rbp
      push %rbx
      push %r12
      push %r13
      push %r14
      push %r15
      call ._main
      pop %r15
      pop %r14
      pop %r13
      pop %r12
      pop %rbx
      pop %rbp
      retq
._main:
      push %rbp
      mov %rsp,%rbp
      add $-8,%rsp 
      mov $7422,%r13
      push %r13
      call ._print
      pop %r13
      mov $0,%rax
      sub $-8,%rsp 
      pop %rbp
      retq
