.globl print_str
print_str:
    li      $v0,    4
    syscall 
    jr      $ra

.globl print_newline
print_newline:
    la      $a0,    newline
    li      $v0,    4
    syscall 
    jr      $ra

.globl print_int
print_int:
    li      $v0,    1
    syscall 
    jr      $ra

.globl print_char
print_char:
    li      $v0,    11
    syscall 
    jr      $ra

.globl exit
exit:
    addi    $v0,    $0,         10
    syscall 