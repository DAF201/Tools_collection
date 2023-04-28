.globl player_turn
player_turn:

    addi    $sp,                    $sp,                                -4
    sw      $ra,                    ($sp)                                               # save $ra for upcoming jal instructions

    la      $a0,                    player_move_prompt                                  # print how to do

    jal     print_str
    jal     player_read_char                                                            # get a char

    lw      $t2,                    player_position                                     # load player position to t2

    li      $t0,                    97                                                  # check if is a
    beq     $t0,                    $v1,                                move_a
    li      $t0,                    119                                                 # check if is w
    beq     $t0,                    $v1,                                move_w
    li      $t0,                    115                                                 # check if is s
    beq     $t0,                    $v1,                                move_s
    li      $t0,                    100                                                 # check if is d
    beq     $t0,                    $v1,                                move_d
    li      $t0,                    120                                                 # check if is x
    beq     $t0,                    $v1,                                move_x
    li      $t0,                    101                                                 # t0=e
    beq     $t0,                    $v1,                                exit            # if equal to e, exit
                                                                                        # other case
    j       player_invalid_input                                                        # invaild input

# end of player_turn segment


.globl move_a
move_a:

# dont move player cursor if already in leftmost position
    beq     $t2,                    2,                                  leftmost_pos
    beq     $t2,                    17,                                 leftmost_pos
    beq     $t2,                    33,                                 leftmost_pos
    beq     $t2,                    49,                                 leftmost_pos
    beq     $t2,                    65,                                 leftmost_pos
    beq     $t2,                    81,                                 leftmost_pos

    lw      $a0,                    player_position                                     # get player index
    lb      $a0,                    table_position_usage_array($a0)                     # load that byte
    bne     $zero,                  $a0,                                used_reset_a    # not 0, which mean used, dont reset
    
unused_reset_a:
    jal     replace_unplayed
    j       finish_move_a
used_reset_a:
    jal     replace_played

finish_move_a:

    lw      $t4, player_position							    # get player position
    li      $t3, -2									    # offset to move by
    blt     $t4, 16, left_offset_done
    li      $t3, -1									    # if not on top row, move left by 1
    jal     switch_cursor								    # switch betwen vertical and horizontal moves
    
left_offset_done:
    
    add     $t2,                    $t2,                                $t3             # position-offset

    sw      $t2,                    player_position                                     # save new position
    lb      $t0,                    player_cursor                                       # load player cursor
    sb      $t0,                    table($t2)

leftmost_pos:
    jal     print_table

    j       player_return

.globl move_w
move_w:
    
    li      $t3, -16                                                                    # movement offset
    
# dont move up if already at the top
    blt     $t2,                    15,                                 topmost_pos
    
# prevent player from moving to topmost vertical lines
    
    bgt     $t2, 31, up_offset_done                                                     # adjust offset if trying to move to top row
    beq     $t2, 18, up_offset_done
    beq     $t2, 20, up_offset_done
    beq     $t2, 22, up_offset_done
    beq     $t2, 24, up_offset_done
    beq     $t2, 26, up_offset_done
    beq     $t2, 28, up_offset_done
    beq     $t2, 30, up_offset_done
    
# special offsets:

    jal     switch_cursor								    # switch betwen vertical and horizontal moves
    
    li      $t3, -17
    beq     $t2, 31, up_offset_done                                                     # avoid top left corner
    
    li      $t3, -15                                                                    # avoid top verticals

up_offset_done:

    lw      $a0,                    player_position                                     # get player index
    lb      $a0,                    table_position_usage_array($a0)                     # load that byte
    bne     $zero,                  $a0,                                used_reset_w    # not 0, which mean used, dont reset
    
unused_reset_w:
    jal     replace_unplayed
    j       finish_move_w
used_reset_w:
    jal     replace_played

finish_move_w:

    add     $t2,                    $t2,                                $t3             # position-offset

    sw      $t2,                    player_position                                     # save new position
    lb      $t0,                    player_cursor                                       # load player cursor
    sb      $t0,                    table($t2)

topmost_pos:
    jal     print_table

    j       player_return

.globl move_s
move_s:

# dont move down if already at the bottom
    bgt     $t2,                    80,                                 bottommost_pos

    lw      $a0,                    player_position                                     # get player index
    lb      $a0,                    table_position_usage_array($a0)                     # load that byte
    bne     $zero,                  $a0,                                used_reset_s    # not 0, which mean used, dont reset
    
unused_reset_s:
    jal     replace_unplayed
    j       finish_move_s
used_reset_s:
    jal     replace_played

finish_move_s:

    addi    $t2,                    $t2,                                16              # position+16

    sw      $t2,                    player_position                                     # save new position
    lb      $t0,                    player_cursor                                       # load player cursor
    sb      $t0,                    table($t2)

bottommost_pos:
    jal     print_table

    j       player_return

.globl move_d
move_d:

# dont move player cursor if already in rightmost position
    beq     $t2,                    14,                                 rightmost_pos
    beq     $t2,                    31,                                 rightmost_pos
    beq     $t2,                    47,                                 rightmost_pos
    beq     $t2,                    63,                                 rightmost_pos
    beq     $t2,                    79,                                 rightmost_pos
    beq     $t2,                    95,                                 rightmost_pos

    lw      $a0,                    player_position                                     # get player index
    lb      $a0,                    table_position_usage_array($a0)                     # load that byte
    bne     $zero,                  $a0,                                used_reset_d    # not 0, which mean used, dont reset
    
unused_reset_d:
    jal     replace_unplayed
    j       finish_move_d
used_reset_d:
    jal     replace_played

finish_move_d:
    
    lw      $t4, player_position							    # get player position
    li      $t3, 2									    # offset to move by
    blt     $t4, 16, right_offset_done
    li      $t3, 1									    # if not on top row, move left by 1
    jal     switch_cursor								    # switch betwen vertical and horizontal moves
    
right_offset_done:
    
    add    $t2,                    $t2,                                $t3              # position+1

    sw      $t2,                    player_position                                     # save new position
    lb      $t0,                    player_cursor                                       # load player cursor
    sb      $t0,                    table($t2)

rightmost_pos:
    jal     print_table

    j       player_return

# save value
.globl move_x
move_x:

# to get an index corresponding in the array of storing which positions are used
    lw      $a0,                    player_position
    lb      $t0,                    table_position_usage_array($a0)
    beq     $t0, 1, player_invalid_input						# invalid input if move has already been played
    
    addi    $a1,                    $zero,                              1               # get a one in a1
    sb      $a1,                    table_position_usage_array($a0)                     # set thie index to 1

    li      $t0,                    '*'                                               # load *
    sb      $t0,                    table($a0)
    
    lw      $a0, player_position
    jal     check_square								# check if a square was completed
    
    li      $t0, 1
    sw      $t0, current_turn								# switch to computer turn

    j       player_return

# player finished move, return to main
.globl player_return
player_return:
    
    lw      $ra,                    ($sp)
    addi    $sp,                    $sp,                                4

    jr      $ra                                                                         # jump to main loop


.globl player_invalid_input
player_invalid_input:
    la      $a0,                    player_move_invaild                                 # print invalid

    addi    $sp,                    $sp,                                -4
    sw      $ra,                    ($sp)                                               # save $ra for jal jump

    jal     print_str

    lw      $ra,                    ($sp)
    addi    $sp,                    $sp,                                4

    j       player_turn                                                                 # jump back to a new player_turn

.globl player_read_char
player_read_char:
    li      $v0,                    12                                                  # read a char from keyboard
    syscall 
    move    $v1,                    $v0                                                 # move read result to v1

# Added code here
    addi    $sp,		    $sp,				-4
    sw	    $ra,                    ($sp)
    
    jal	    move_sound
    
    lw	    $ra,		    ($sp)
    addi    $sp,		    $sp,				4
# End added code


    lb      $a0,                    newline                                             # print a newline
    li      $v0,                    11
    syscall 

    jr      $ra                                                                         # jump to return address
