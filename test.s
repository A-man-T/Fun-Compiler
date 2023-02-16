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
._format:
      push %rbp
      mov %rsp,%rbp
      add $-8,%rsp 
      mov $0,%r13
      push %r13
      pop %rdi
      test %rdi,%rdi
        jz .0
      mov $2,%r13
      push %r13
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
        jmp .1
.0:
.1:
.2:
      mov $1,%r13
      push %r13
      pop %rdi
      test %rdi,%rdi
        jz .3
      mov $1,%r13
      push %r13
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
        jmp .2
.3:
      mov $0,%rax
      sub $-8,%rsp 
      pop %rbp
      retq
._a:
      push %rbp
      mov %rsp,%rbp
      add $-8,%rsp 
      mov $5,%r13
      push %r13
      pop %rdi
      mov %rdi,-8(%rbp)
      mov -8(%rbp),%rdi
      push %rdi
      pop %rdi
      mov %rdi,24(%rbp)
      mov 16(%rbp),%rdi
      push %rdi
      pop %rdi
      test %rdi,%rdi
        jz .4
      mov 24(%rbp),%rdi
      push %rdi
      mov -8(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      add %rdx, %rax
      push %rax
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
        jmp .5
.4:
      mov -8(%rbp),%rdi
      push %rdi
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
.5:
      mov $0,%rax
      sub $-8,%rsp 
      pop %rbp
      retq
._b:
      push %rbp
      mov %rsp,%rbp
      add $0,%rsp 
      mov 16(%rbp),%rdi
      push %rdi
      mov $3,%r13
      push %r13
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setbe %al
      push %rax
      pop %rdi
      test %rdi,%rdi
        jz .6
      mov $3,%r13
      push %r13
      mov 16(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      imul %rdx, %rax
      push %rax
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
        jmp .7
.6:
.7:
      mov 16(%rbp),%rdi
      push %rdi
      mov $1,%r13
      push %r13
      pop %rdx
      pop %rax
      sub %rdx, %rax
      push %rax
      call ._c
      add $8,%rsp
      push %rax
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
      mov $0,%rax
      sub $0,%rsp 
      pop %rbp
      retq
._c:
      push %rbp
      mov %rsp,%rbp
      add $0,%rsp 
      mov 16(%rbp),%rdi
      push %rdi
      mov $2,%r13
      push %r13
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setbe %al
      push %rax
      pop %rdi
      test %rdi,%rdi
        jz .8
      mov $2,%r13
      push %r13
      mov 16(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      imul %rdx, %rax
      push %rax
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
        jmp .9
.8:
.9:
      mov 16(%rbp),%rdi
      push %rdi
      mov $1,%r13
      push %r13
      pop %rdx
      pop %rax
      sub %rdx, %rax
      push %rax
      call ._b
      add $8,%rsp
      push %rax
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
      mov $0,%rax
      sub $0,%rsp 
      pop %rbp
      retq
._main:
      push %rbp
      mov %rsp,%rbp
      add $-16,%rsp 
      call ._format
      add $0,%rsp
      push %rax
      call ._print
      pop %r13
      mov $1,%r13
      push %r13
      mov $2,%r13
      push %r13
      call ._a
      add $16,%rsp
      push %rax
      call ._print
      pop %r13
      mov $2,%r13
      push %r13
      mov $0,%r13
      push %r13
      call ._a
      add $16,%rsp
      push %rax
      call ._print
      pop %r13
      mov $3,%r13
      push %r13
      pop %rdi
      mov %rdi,-8(%rbp)
      mov $5,%r13
      push %r13
      pop %rdi
      mov %rdi,-16(%rbp)
      mov -16(%rbp),%rdi
      push %rdi
      mov -8(%rbp),%rdi
      push %rdi
      mov -16(%rbp),%rdi
      push %rdi
      mov $2,%r13
      push %r13
      xor %rdx,%rdx
      pop %rdi
      pop %rax
      divq %rdi
      push %rax
      xor %rdx,%rdx
      pop %rdi
      pop %rax
      divq %rdi
      push %rdx
      pop %rdx
      pop %rax
      sub %rdx, %rax
      push %rax
      call ._print
      pop %r13
      mov -16(%rbp),%rdi
      push %rdi
      mov -8(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setb %al
      push %rax
      mov -16(%rbp),%rdi
      push %rdi
      mov -16(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      sub %rdx, %rax
      push %rax
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setae %al
      push %rax
      call ._print
      pop %r13
      mov $1,%r13
      push %r13
      mov $1,%r13
      push %r13
      call ._a
      add $16,%rsp
      push %rax
      mov -16(%rbp),%rdi
      push %rdi
      mov -8(%rbp),%rdi
      push %rdi
      xor %rdx,%rdx
      pop %rdi
      pop %rax
      divq %rdi
      push %rdx
      pop %rdx
      pop %rax
      sub %rdx, %rax
      push %rax
      call ._print
      pop %r13
      mov $1,%r13
      push %r13
      mov $1,%r13
      push %r13
      call ._a
      add $16,%rsp
      push %rax
      mov $2,%r13
      push %r13
      call ._format
      add $0,%rsp
      push %rax
      pop %rdx
      pop %rax
      imul %rdx, %rax
      push %rax
      mov -16(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      add %rdx, %rax
      push %rax
      xor %rdx,%rdx
      pop %rdi
      pop %rax
      divq %rdi
      push %rdx
      call ._print
      pop %r13
      mov $5,%r13
      push %r13
      call ._b
      add $8,%rsp
      push %rax
      call ._print
      pop %r13
      mov $6,%r13
      push %r13
      call ._b
      add $8,%rsp
      push %rax
      call ._print
      pop %r13
      mov $0,%rax
      sub $-16,%rsp 
      pop %rbp
      retq
