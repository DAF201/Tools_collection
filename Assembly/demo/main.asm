.text
main:
    li      $s0,            1
    lw      $s0,            player_position     # init player position with 1(top left line between point 1 and point 2)

    jal     print_table

    jal     player_turn
    j       exit
