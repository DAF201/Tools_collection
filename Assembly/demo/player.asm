.globl player_turn
player_turn:
    la      $a0,                        player_move_prompt                                  # print how to do
    jal     print_str

    j       player_read_char                                                                # get a char

# for get char jump back
.globl player_finish_read_char
player_finish_read_char:

    j       player_move_verify                                                              # check if vaild

# for jump back after verify passed
.globl player_finish_move_verify
player_finish_move_verify:

    lw      $t2,                        player_position                                     # load player position to t2

    li      $t0,                        0                                                   # check if is a
    beq     $t0,                        $t1,                    move_a
    li      $t0,                        1                                                   # check if is w
    beq     $t0,                        $t1,                    move_w
    li      $t0,                        2                                                   # check if is s
    beq     $t0,                        $t1,                    move_s
    li      $t0,                        3                                                   # check if is d
    beq     $t0,                        $t1,                    move_d

.globl move_a
move_a:
    addi    $t2,                        $t2,                    -2                          # position-2
    j       player_finish_move
.globl move_w
move_w:
    addi    $t2,                        $t2,                    -16                         # position-16
    j       player_finish_move
.globl move_s
move_s:
    addi    $t2,                        $t2,                    16                          # position+16
    j       player_finish_move
.globl move_d
move_d:
    addi    $t2,                        $t2,                    2                           # position+2
    j       player_finish_move

# player finished move, then do the display
.globl player_finish_move
player_finish_move:
    sw      $t2,                        player_position                                     # save new position
    li      $t0,                        126                                                 # load ~
    sb      $t0,                        table($t2)
    jal     print_table

    j       player_turn                                                                     # jump to player_turn


.globl player_move_verify
player_move_verify:
    li      $t0,                        97                                                  # t0=a
    li      $t1,                        0                                                   # t1=0 for a
    beq     $v1,                        $t0,                    player_finish_move_verify   # if entered char equal a, jump back, same as below

    li      $t0,                        119                                                 # t0=w
    li      $t1,                        1                                                   # t1=1 for w
    beq     $v1,                        $t0,                    player_finish_move_verify

    li      $t0,                        115                                                 # t0=s
    li      $t1,                        2                                                   # t1=2 for s
    beq     $v1,                        $t0,                    player_finish_move_verify

    li      $t0,                        100                                                 # t0=d
    li      $t1,                        3                                                   # t1=3 for d
    beq     $v1,                        $t0,                    player_finish_move_verify

    li      $t0,                        101                                                 # t0=e
    beq     $v1,                        $t0,                    exit                        # if equal to e, exit

# other case
    j       player_invaild_input                                                            # invaild input


.globl player_invaild_input
player_invaild_input:
    la      $a0,                        player_move_invaild                                 # print invaild
    jal     print_str
    j       player_turn                                                                     # jump back to a new player_turn

.globl player_read_char
player_read_char:
    li      $v0,                        12                                                  # read a char from keyboard
    syscall 
    move    $v1,                        $v0                                                 # move read result to v1


    la      $a0,                        newline                                             # print a newline
    li      $v0,                        4
    syscall 

    j       player_finish_read_char                                                         # jump to target
