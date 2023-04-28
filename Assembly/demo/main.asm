.text

# main loop of the program. Any other files that use the jal instruction
# need to save $ra on the stack before jumping.

    jal     print_title

    jal     print_table

main:
    lb      $t0, scores+0
    lb      $t1, scores+1
    add     $t0, $t0, $t1
    beq     $t0, 35, game_over				# if player score sum = 35, end game

    lw      $s0,            player_position     # init player position with 1(top left line between point 1 and point 2)

    jal     player_turn			  # player goes first
    jal     computer_turn
    
    j       main
