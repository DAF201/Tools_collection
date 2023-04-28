.data
.globl table
table: .asciiz "\n.~. . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n"                                                                                                           # the real table

.globl table_position_usage_array
table_position_usage_array: .byte 1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1

.globl title_message 								# Dots and Squares
title_message: .asciiz " __   __  ___  __                __      __   __             __   ___  __\n|  \\ /  \\  |  /__`     /\\  |\\ | |  \\    /__` /  \\ |  |  /\\  |__) |__  /__`\n|__/ \\__/  |  .__/    /~~\\ | \\| |__/    .__/ \\__X \\__/ /~~\\ |  \\ |___ .__/ "

.globl player_position
player_position: .word 2

.globl computer
computer: .asciiz "Computer: "
.globl player
player: .asciiz "Player: "

.globl scores
scores: .byte 0,0								# scores[0] = player, scores[1] = computer

.globl horizontal_line
horizontal_line: .byte '_'

.globl vertical_line
vertical_line: .byte '|'

.globl tilde
tilde: .byte '~'

.globl colon
colon: .byte ':'

.globl dot
dot: .byte '.'

# defalut player cursor is '~'
.globl player_cursor
player_cursor: .byte '~'

.globl space
space: .byte ' '

.globl newline
newline:.byte '\n'

# store current turn,0:player,1:computer
.globl current_turn
current_turn:.word 0

.globl c_win 									# Changed from "Computer wins!"
c_win: .asciiz "\n\\ / /  \\ |  |    |    /  \\ /__` |__   /\n |  \\__/ \\__/    |___ \\__/ .__/ |___ ."

.globl p_win									# Changed from "You win!"
p_win: .asciiz "\n\\ / /  \\ |  |    |  | | |\\ |  /\n |  \\__/ \\__/    |/\\| | | \\| ."

.globl player_move_prompt
player_move_prompt:.asciiz "Move your line using 'wasd' keys. Press x to confirm move\n"

.globl player_move_invaild
player_move_invaild:.asciiz "Move invaild, please try again\n"

.globl comp_move_prompt
comp_move_prompt: .asciiz "Computer has finished its move, your turn!"
