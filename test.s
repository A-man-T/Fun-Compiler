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
      add $-32,%rsp 
      mov $1,%r13
      push %r13
      pop %rdi
      mov %rdi,-8(%rbp)
      mov $5,%r13
      push %r13
      pop %rdi
      mov %rdi,-16(%rbp)
      mov $3,%r13
      push %r13
      pop %rdi
      mov %rdi,-24(%rbp)
      mov $0,%r13
      push %r13
      pop %rdi
      mov %rdi,-32(%rbp)
.0:
      mov -8(%rbp),%rdi
      push %rdi
      mov $20000000,%r13
      push %r13
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setb %al
      push %rax
      pop %rdi
      test %rdi,%rdi
        jz .1
      mov -8(%rbp),%rdi
      push %rdi
      mov $1,%r13
      push %r13
      pop %rdx
      pop %rax
      add %rdx, %rax
      push %rax
      pop %rdi
      mov %rdi,-8(%rbp)
      mov $7,%r13
      push %r13
      pop %rdi
      mov %rdi,-16(%rbp)
      mov -16(%rbp),%rdi
      push %rdi
      mov $1,%r13
      push %r13
      pop %rdx
      pop %rax
      add %rdx, %rax
      push %rax
      pop %rdi
      mov %rdi,-16(%rbp)
      mov -8(%rbp),%rdi
      push %rdi
      mov -24(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      add %rdx, %rax
      push %rax
      pop %rdi
      mov %rdi,-24(%rbp)
      mov -8(%rbp),%rdi
      push %rdi
      mov $2,%r13
      push %r13
      pop %rdx
      pop %rax
      add %rdx, %rax
      push %rax
      pop %rdi
      mov %rdi,-32(%rbp)
        jmp .0
.1:
      mov -8(%rbp),%rdi
      push %rdi
      call ._print
      pop %r13
      mov $0,%rax
      sub $-32,%rsp 
      pop %rbp
      retq
