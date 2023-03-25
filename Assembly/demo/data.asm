.data
.globl table
table: .asciiz "\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n"       # thre real table

.globl player_position
player_position: .word 1

.globl computer
computer: .asciiz "Computer:"
.globl player
player: .asciiz "Player"

.globl horizontal_line
horizontal_line: .asciiz "-"

.globl vertical_line
vertical_line: .asciiz "|"

.globl space
space: .asciiz " "

.globl newline
newline:.asciiz "\n"

# store current turn,0:player,1:computer
.globl current_turn
current_turn:.word

.globl player_move_prompt
player_move_prompt:.asciiz "Move your line using 'wasd' keys. Press x to confirm move\n"

.globl player_move_invaild
player_move_invaild:.asciiz "Move invaild, please try again\n"