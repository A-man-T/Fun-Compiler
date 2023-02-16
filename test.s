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
._text:
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
._data:
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
._format:
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
._global:
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
._severalVariables:
      push %rbp
      mov %rsp,%rbp
      add $-208,%rsp 
      mov $1,%r13
      push %r13
      pop %rdi
      mov %rdi,-8(%rbp)
      mov $2,%r13
      push %r13
      pop %rdi
      mov %rdi,-16(%rbp)
      mov $3,%r13
      push %r13
      pop %rdi
      mov %rdi,-24(%rbp)
      mov $4,%r13
      push %r13
      pop %rdi
      mov %rdi,-32(%rbp)
      mov $5,%r13
      push %r13
      pop %rdi
      mov %rdi,-40(%rbp)
      mov $6,%r13
      push %r13
      pop %rdi
      mov %rdi,-48(%rbp)
      mov $7,%r13
      push %r13
      pop %rdi
      mov %rdi,-56(%rbp)
      mov $8,%r13
      push %r13
      pop %rdi
      mov %rdi,-64(%rbp)
      mov $9,%r13
      push %r13
      pop %rdi
      mov %rdi,-72(%rbp)
      mov $10,%r13
      push %r13
      pop %rdi
      mov %rdi,-80(%rbp)
      mov $11,%r13
      push %r13
      pop %rdi
      mov %rdi,-88(%rbp)
      mov $12,%r13
      push %r13
      pop %rdi
      mov %rdi,-96(%rbp)
      mov $13,%r13
      push %r13
      pop %rdi
      mov %rdi,-104(%rbp)
      mov $14,%r13
      push %r13
      pop %rdi
      mov %rdi,-112(%rbp)
      mov $15,%r13
      push %r13
      pop %rdi
      mov %rdi,-120(%rbp)
      mov $16,%r13
      push %r13
      pop %rdi
      mov %rdi,-128(%rbp)
      mov $17,%r13
      push %r13
      pop %rdi
      mov %rdi,-136(%rbp)
      mov $18,%r13
      push %r13
      pop %rdi
      mov %rdi,-144(%rbp)
      mov $19,%r13
      push %r13
      pop %rdi
      mov %rdi,-152(%rbp)
      mov $20,%r13
      push %r13
      pop %rdi
      mov %rdi,-160(%rbp)
      mov $21,%r13
      push %r13
      pop %rdi
      mov %rdi,-168(%rbp)
      mov $22,%r13
      push %r13
      pop %rdi
      mov %rdi,-176(%rbp)
      mov $23,%r13
      push %r13
      pop %rdi
      mov %rdi,-184(%rbp)
      mov $24,%r13
      push %r13
      pop %rdi
      mov %rdi,-192(%rbp)
      mov $25,%r13
      push %r13
      pop %rdi
      mov %rdi,-200(%rbp)
      mov $26,%r13
      push %r13
      pop %rdi
      mov %rdi,-208(%rbp)
      mov $0,%rax
      sub $-208,%rsp 
      pop %rbp
      retq
._overflowPostfix:
      push %rbp
      mov %rsp,%rbp
      add $-8,%rsp 
      mov $2,%r13
      push %r13
      pop %rdi
      mov %rdi,-8(%rbp)
      mov -8(%rbp),%rdi
      push %rdi
      call ._print
      pop %r13
      mov $0,%rax
      sub $-8,%rsp 
      pop %rbp
      retq
._weirdComments:
      push %rbp
      mov %rsp,%rbp
      add $-8,%rsp 
      mov $1,%r13
      push %r13
      call ._print
      pop %r13
      mov $1,%r13
      push %r13
      pop %rdi
      test %rdi,%rdi
        jz .0
      mov $2,%r13
      push %r13
      call ._print
      pop %r13
        jmp .1
.0:
      mov $3,%r13
      push %r13
      call ._print
      pop %r13
.1:
      mov $0,%r13
      push %r13
      pop %rdi
      mov %rdi,-8(%rbp)
.2:
      mov -8(%rbp),%rdi
      push %rdi
      mov $5,%r13
      push %r13
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setb %al
      push %rax
      pop %rdi
      test %rdi,%rdi
        jz .3
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
      mov -8(%rbp),%rdi
      push %rdi
      call ._print
      pop %r13
        jmp .2
.3:
      mov $0,%rax
      sub $-8,%rsp 
      pop %rbp
      retq
._weirdVariableNames:
      push %rbp
      mov %rsp,%rbp
      add $-24,%rsp 
      mov $1,%r13
      push %r13
      pop %rdi
      mov %rdi,-8(%rbp)
      mov $2,%r13
      push %r13
      pop %rdi
      mov %rdi,-16(%rbp)
      mov -8(%rbp),%rdi
      push %rdi
      mov -16(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      add %rdx, %rax
      push %rax
      call ._print
      pop %r13
      mov $5,%r13
      push %r13
      pop %rdi
      mov %rdi,-24(%rbp)
      mov -24(%rbp),%rdi
      push %rdi
      call ._print
      pop %r13
      mov $0,%rax
      sub $-24,%rsp 
      pop %rbp
      retq
._nestedIfsAndWhiles:
      push %rbp
      mov %rsp,%rbp
      add $-8,%rsp 
      mov 16(%rbp),%rdi
      push %rdi
      mov $5,%r13
      push %r13
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setae %al
      push %rax
      pop %rdi
      test %rdi,%rdi
        jz .4
      mov $5,%r13
      push %r13
      pop %rdi
      mov %rdi,-8(%rbp)
.6:
      mov -8(%rbp),%rdi
      push %rdi
      mov $0,%r13
      push %r13
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      seta %al
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
      mov 16(%rbp),%rdi
      push %rdi
      mov $20,%r13
      push %r13
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      sete %al
      push %rax
      pop %rdi
      test %rdi,%rdi
        jz .8
      mov -8(%rbp),%rdi
      push %rdi
      mov $3,%r13
      push %r13
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      seta %al
      push %rax
      pop %rdi
      test %rdi,%rdi
        jz .10
      mov $3,%r13
      push %r13
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
        jmp .11
.10:
.11:
      mov $2,%r13
      push %r13
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
        jmp .9
.8:
.9:
      mov -8(%rbp),%rdi
      push %rdi
      mov $1,%r13
      push %r13
      pop %rdx
      pop %rax
      sub %rdx, %rax
      push %rax
      pop %rdi
      mov %rdi,-8(%rbp)
        jmp .6
.7:
        jmp .5
.4:
      mov $1,%r13
      push %r13
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
.5:
      mov $0,%r13
      push %r13
      pop %rax
      mov %rbp, %rsp
      pop %rbp
      retq
      mov $0,%rax
      sub $-8,%rsp 
      pop %rbp
      retq
._primeFactorization:
      push %rbp
      mov %rsp,%rbp
      add $-8,%rsp 
      mov $2,%r13
      push %r13
      pop %rdi
      mov %rdi,-8(%rbp)
.12:
      mov -8(%rbp),%rdi
      push %rdi
      mov -8(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      imul %rdx, %rax
      push %rax
      mov 16(%rbp),%rdi
      push %rdi
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      setbe %al
      push %rax
      pop %rdi
      test %rdi,%rdi
        jz .13
.14:
      mov 16(%rbp),%rdi
      push %rdi
      mov -8(%rbp),%rdi
      push %rdi
      xor %rdx,%rdx
      pop %rdi
      pop %rax
      divq %rdi
      push %rdx
      mov $0,%r13
      push %r13
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      sete %al
      push %rax
      pop %rdi
      test %rdi,%rdi
        jz .15
      mov -8(%rbp),%rdi
      push %rdi
      call ._print
      pop %r13
      mov 16(%rbp),%rdi
      push %rdi
      mov -8(%rbp),%rdi
      push %rdi
      xor %rdx,%rdx
      pop %rdi
      pop %rax
      divq %rdi
      push %rax
      pop %rdi
      mov %rdi,16(%rbp)
        jmp .14
.15:
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
        jmp .12
.13:
      mov 16(%rbp),%rdi
      push %rdi
      mov $1,%r13
      push %r13
      pop %rdx
      pop %rax
      cmp %rdx, %rax
      mov $0,%rax
      seta %al
      push %rax
      pop %rdi
      test %rdi,%rdi
        jz .16
      mov 16(%rbp),%rdi
      push %rdi
      call ._print
      pop %r13
        jmp .17
.16:
.17:
      mov $0,%rax
      sub $-8,%rsp 
      pop %rbp
      retq
._main:
      push %rbp
      mov %rsp,%rbp
      add $-8,%rsp 
      call ._severalVariables
      add $0,%rsp
      call ._overflowPostfix
      add $0,%rsp
      call ._weirdComments
      add $0,%rsp
      call ._weirdVariableNames
      add $0,%rsp
      mov $3,%r13
      push %r13
      call ._nestedIfsAndWhiles
      add $8,%rsp
      push %rax
      call ._print
      pop %r13
      mov $5,%r13
      push %r13
      call ._nestedIfsAndWhiles
      add $8,%rsp
      push %rax
      call ._print
      pop %r13
      mov $3,%r13
      push %r13
      call ._nestedIfsAndWhiles
      add $8,%rsp
      push %rax
      call ._print
      pop %r13
      mov $15,%r13
      push %r13
      call ._nestedIfsAndWhiles
      add $8,%rsp
      push %rax
      call ._print
      pop %r13
      mov $20,%r13
      push %r13
      call ._nestedIfsAndWhiles
      add $8,%rsp
      push %rax
      call ._print
      pop %r13
      mov $2,%r13
      push %r13
      call ._primeFactorization
      add $8,%rsp
      mov $10,%r13
      push %r13
      call ._primeFactorization
      add $8,%rsp
      mov $505,%r13
      push %r13
      call ._primeFactorization
      add $8,%rsp
      mov $65537,%r13
      push %r13
      call ._primeFactorization
      add $8,%rsp
      mov $1,%r13
      push %r13
      call ._printf
      add $8,%rsp
      mov $2,%r13
      push %r13
      call ._text
      add $8,%rsp
      mov $3,%r13
      push %r13
      call ._data
      add $8,%rsp
      mov $4,%r13
      push %r13
      call ._format
      add $8,%rsp
      mov $5,%r13
      push %r13
      call ._global
      add $8,%rsp
      mov $0,%rax
      sub $-8,%rsp 
      pop %rbp
      retq
