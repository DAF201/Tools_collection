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
    
    
.globl print_title
print_title:
    la      $a0,    title_message
    li      $v0,    4
    syscall 
    jr      $ra

        
# alternate between vertical and horizontal cursor
.globl switch_cursor
switch_cursor:
    lb      $t0,    player_cursor
    beq     $t0, '~', switch_to_vert
    
switch_to_hor:
    lb      $t0,    tilde
    sb      $t0,    player_cursor
    jr      $ra
    
switch_to_vert:
    lb      $t0,    colon
    sb      $t0,    player_cursor
    jr      $ra


# when moving away from unplayed position, draw correct symbol before moving
.globl replace_unplayed
replace_unplayed:
    lw      $t0,    player_position			# t0 = player position
    andi    $t1, $t0, 1
    beq     $t1, 1, unused_vert

unused_hor:
    lb      $t1,    space
    sb      $t1,    table($t0)
    jr      $ra

unused_vert:
    lb      $t1,    dot
    sb      $t1,    table($t0)
    jr      $ra
    
    
# when moving away from played position, draw correct symbol before moving
.globl replace_played
replace_played:
    lw      $t0,    player_position			# t0 = player position
    andi    $t1, $t0, 1
    beq     $t1, 1, used_vert

used_hor:
    lb      $t1,    horizontal_line
    sb      $t1,    table($t0)
    jr      $ra

used_vert:
    lb      $t1,    vertical_line
    sb      $t1,    table($t0)
    jr      $ra

.globl game_over
game_over:
    lb      $t0, scores($zero)
    lb      $t1, scores+1
    blt     $t0, $t1, cpu_win
    
    la      $a0, p_win
    jal     print_str
    jal     win_sound					# Added sound here
    j       exit

cpu_win:
    la      $a0, c_win
    jal     print_str
    jal     loss_sound					# Added sound here
    j       exit

.globl exit
exit:
    addi    $v0,    $0,         10
    syscall 
