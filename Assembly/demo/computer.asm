.globl computer_turn
computer_turn:
	
	lw	$t0, current_turn
	beqz	$t0, comp_return									# exit if not computer turn
	
	addi	$sp, $sp, -4										# make room to save $ra
	sw	$ra, ($sp)										# store the $ra for main
	
	li	$t0, 2											# start at table position 1
	
comp_find_move:												# loop through table until playable move is found
	lb	$t1, table_position_usage_array($t0)
	beq	$t1, 0, comp_complete_move								# if the current move hasnt been played, play it
	
	addi	$t0, $t0, 1										# index++
	j	comp_find_move
	
comp_complete_move:
	
	li	$t2, 1
	sb	$t2, table_position_usage_array($t0)							# save computer move
	
# determine which kind of line to draw
	andi	$t3, $t0, 1
	beqz	$t3, even_index										# if even index, draw horizontal line

odd_index:												# odd index = draw vertical
	lb	$t4, vertical_line
	j	draw_comp_move

even_index:
	lb	$t4, horizontal_line
	
draw_comp_move:
	sb	$t4, table($t0)										# update gameboard
	
	move    $a0, $t0
	jal     check_square										# check if a square was completed
	
	la	$a0, comp_move_prompt									# print computer move text
	jal	print_str
	jal	print_table
	jal	print_newline
	
	sw	$zero, current_turn									#switch to player turn

	lw	$ra, ($sp)										# restore $ra
	addi	$sp, $sp, 4										# pop stack
	
comp_return:
	jr	$ra											# return to main
	
