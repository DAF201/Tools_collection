.globl print_table
print_table:
    la      $a0,            table
    li      $v0,            4
    syscall 
    jr      $ra

.globl print_table_and_exit
print_table_and_exit:
    jal     print_table
    j       exit
