    .data
format: .byte '%', 'd', 10, 0
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
._fun:
      mov $0,%rax
      retq
      mov $14,%r13
      push %r13
      mov $16,%r13
      push %r13
      mov $19,%r13
      push %r13
      mov $205,%r13
      push %r13
      mov $69,%r13
      push %r13
      call ._print
      pop %r13
failed at offset 77
} 19 
    g = 205
    print(69)
}
