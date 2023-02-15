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
._f1:
      push %rbp
      mov %rsp,%rbp
      add $0,%rsp 
      mov 24(%rbp),%rdi
      push %rdi
      mov $0,%r13
      push %r13
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setne %al
      push %rax
      pop %rdi
      test %rdi,%rdi
        jz .0
      mov $0,%r13
      push %r13
      pop %rdi
      test %rdi,%rdi
        jz .2
      mov $419,%r13
      push %r13
      call ._print
      pop %r13
        jmp .3
.2:
.3:
      mov 32(%rbp),%rdi
      push %rdi
      mov 24(%rbp),%rdi
      push %rdi
      mov $1,%r13
      push %r13
      pop %rdx
      pop %rax
      add %rdx, %rax
      push %rax
      mov 16(%rbp),%rdi
      push %rdi
      call ._f1
      add $24,%rsp
      push %rax
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
        jmp .1
.0:
      mov $1,%r13
      push %r13
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
.1:
      mov $0,%rax
      sub $0,%rsp 
      pop %rbp
      retq
._printf:
      push %rbp
      mov %rsp,%rbp
      add $0,%rsp 
      mov 16(%rbp),%rdi
      push %rdi
      call ._print
      pop %r13
      mov $0,%rax
      sub $0,%rsp 
      pop %rbp
      retq
._f2:
      push %rbp
      mov %rsp,%rbp
      add $0,%rsp 
.4:
      mov 32(%rbp),%rdi
      push %rdi
      mov $50,%r13
      push %r13
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setne %al
      push %rax
      pop %rdi
      test %rdi,%rdi
        jz .5
      mov 32(%rbp),%rdi
      push %rdi
      mov $1,%r13
      push %r13
      pop %rdx
      pop %rax
      add %rdx, %rax
      push %rax
      pop %rdi
      mov %rdi,32(%rbp)
        jmp .4
.5:
      mov 32(%rbp),%rdi
      push %rdi
      mov 24(%rbp),%rdi
      push %rdi
      mov 16(%rbp),%rdi
      push %rdi
      call ._f1
      add $24,%rsp
      push %rax
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
      mov $0,%rax
      sub $0,%rsp 
      pop %rbp
      retq
._func3:
      push %rbp
      mov %rsp,%rbp
      add $0,%rsp 
.6:
      mov 16(%rbp),%rdi
      push %rdi
      mov $10,%r13
      push %r13
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setne %al
      push %rax
      pop %rdi
      test %rdi,%rdi
        jz .7
      mov 16(%rbp),%rdi
      push %rdi
      mov $1,%r13
      push %r13
      pop %rdx
      pop %rax
      add %rdx, %rax
      push %rax
      pop %rdi
      mov %rdi,16(%rbp)
        jmp .6
.7:
      mov 32(%rbp),%rdi
      push %rdi
      mov 24(%rbp),%rdi
      push %rdi
      mov 16(%rbp),%rdi
      push %rdi
      call ._f2
      add $24,%rsp
      push %rax
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
      mov $0,%rax
      sub $0,%rsp 
      pop %rbp
      retq
._testOperators:
      push %rbp
      mov %rsp,%rbp
      add $-8,%rsp 
      mov $1,%r13
      push %r13
      pop %rdi
      mov %rdi,32(%rbp)
      mov $1,%r13
      push %r13
      pop %rdi
      mov %rdi,24(%rbp)
      mov $1,%r13
      push %r13
      pop %rdi
      mov %rdi,16(%rbp)
      mov 32(%rbp),%rdi
      push %rdi
      pop %rax
      test %rax,%rax
      mov $0,%rax
      setz %al
      push %rax
      call ._print
      pop %r13
      mov $5,%r13
      push %r13
      mov 32(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      imul %rdx, %rax
      push %rax
      call ._print
      pop %r13
      mov $5,%r13
      push %r13
      mov $5,%r13
      push %r13
      mov 32(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      imul %rdx, %rax
      push %rax
      xor %rdx,%rdx
      pop %rdi
      pop %rax
      divq %rdi
      push %rax
      call ._print
      pop %r13
      mov $10,%r13
      push %r13
      pop %rdi
      mov %rdi,16(%rbp)
      mov $0,%r13
      push %r13
      call ._print
      pop %r13
      mov 32(%rbp),%rdi
      push %rdi
      mov 16(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setb %al
      push %rax
      call ._print
      pop %r13
      mov 32(%rbp),%rdi
      push %rdi
      mov 24(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setbe %al
      push %rax
      call ._print
      pop %r13
      mov 32(%rbp),%rdi
      push %rdi
      mov 24(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setb %al
      push %rax
      call ._print
      pop %r13
      mov 32(%rbp),%rdi
      push %rdi
      mov 24(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      seta %al
      push %rax
      call ._print
      pop %r13
      mov 32(%rbp),%rdi
      push %rdi
      mov 24(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setae %al
      push %rax
      call ._print
      pop %r13
      mov 16(%rbp),%rdi
      push %rdi
      mov 16(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      sete %al
      push %rax
      call ._print
      pop %r13
      mov 16(%rbp),%rdi
      push %rdi
      mov 16(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setne %al
      push %rax
      call ._print
      pop %r13
      mov $1,%r13
      push %r13
      call ._print
      pop %r13
      mov $1,%r13
      push %r13
      call ._print
      pop %r13
      mov $0,%r13
      push %r13
      call ._print
      pop %r13
      mov $1,%r13
      push %r13
      call ._print
      pop %r13
      mov $0,%r13
      push %r13
      call ._print
      pop %r13
      mov $0,%r13
      push %r13
      call ._print
      pop %r13
      mov $0,%r13
      push %r13
      call ._print
      pop %r13
      mov $1,%r13
      push %r13
      call ._print
      pop %r13
      mov $410,%r13
      push %r13
      pop %rdi
      mov %rdi,-8(%rbp)
      mov $0,%rax
      sub $-8,%rsp 
      pop %rbp
      retq
._main:
      push %rbp
      mov %rsp,%rbp
      add $-56,%rsp 
      mov $20,%r13
      push %r13
      pop %rdi
      mov %rdi,-8(%rbp)
      mov $0,%r13
      push %r13
      pop %rdi
      mov %rdi,-16(%rbp)
      mov $1,%r13
      push %r13
      pop %rdi
      mov %rdi,-24(%rbp)
      mov $420,%r13
      push %r13
      pop %rdi
      mov %rdi,-32(%rbp)
      mov $0,%r13
      push %r13
      pop %rdi
      mov %rdi,-40(%rbp)
      mov $0,%r13
      push %r13
      pop %rdi
      mov %rdi,-48(%rbp)
      mov $0,%r13
      push %r13
      pop %rdi
      mov %rdi,-56(%rbp)
      mov -8(%rbp),%rdi
      push %rdi
      mov -16(%rbp),%rdi
      push %rdi
      mov -8(%rbp),%rdi
      push %rdi
      mov $1,%r13
      push %r13
      pop %rdx
      pop %rax
      sub %rdx, %rax
      push %rax
      call ._f1
      add $24,%rsp
      push %rax
      call ._print
      pop %r13
      mov -8(%rbp),%rdi
      push %rdi
      mov -16(%rbp),%rdi
      push %rdi
      mov -24(%rbp),%rdi
      push %rdi
      call ._func3
      add $24,%rsp
      push %rax
      call ._print
      pop %r13
      mov -8(%rbp),%rdi
      push %rdi
      call ._print
      pop %r13
      mov -16(%rbp),%rdi
      push %rdi
      call ._print
      pop %r13
      mov -24(%rbp),%rdi
      push %rdi
      call ._print
      pop %r13
      mov -32(%rbp),%rdi
      push %rdi
      call ._print
      pop %r13
      mov -8(%rbp),%rdi
      push %rdi
      mov -16(%rbp),%rdi
      push %rdi
      mov -32(%rbp),%rdi
      push %rdi
      call ._testOperators
      add $24,%rsp
      push %rax
      call ._print
      pop %r13
      mov $0,%r13
      push %r13
      call ._print
      pop %r13
      mov $1,%r13
      push %r13
      call ._print
      pop %r13
      mov -32(%rbp),%rdi
      push %rdi
      call ._print
      pop %r13
      mov $15,%r13
      push %r13
      call ._printf
      add $8,%rsp
      mov $0,%rax
      sub $-56,%rsp 
      pop %rbp
      retq
