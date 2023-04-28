.globl print_table
print_table:

    addi    $sp, $sp, -4
    sw      $ra, ($sp)
    
    la      $a0,            table
    li      $v0,            4
    syscall
    
    la      $a0,            player
    jal     print_str
    lb      $a0,            scores($zero)
    jal     print_int
    jal     print_newline									# print the player's score
    
    la      $a0,            computer
    jal     print_str
    li      $t0,            1
    lb      $a0,            scores($t0)
    jal     print_int
    jal     print_newline									# print the computer's score
    
    lw      $ra, ($sp)
    addi    $sp, $sp, 4
    jr      $ra

.globl print_table_and_exit
print_table_and_exit:
    jal     print_table
    j       exit
