.globl check_square
check_square:
	
	# get args
	move	$t0, $a0							# t0 = index played
	
	# check if move played was vertical or horizontal
	andi	$t1, $t0, 1
	beqz	$t1, check_horizontal_square
	j	check_vertical_square

check_horizontal_square:							# check squares that are part of horizontal line moves
	
	blt	$t0, 16, check_bottom_square					# dont check top square if top lines played
	
	addi	$t1, $t0, -16							# check top line
	lb	$t1, table_position_usage_array($t1)
	beqz	$t1, check_bottom_square
	
	addi	$t1, $t0, -1							# check left line
	lb	$t1, table_position_usage_array($t1)
	beqz	$t1, check_bottom_square
	
	addi	$t1, $t0, 1							# check right line
	lb	$t1, table_position_usage_array($t1)
	beqz	$t1, check_bottom_square
	
	lw	$t2, current_turn
	lb	$t3, scores($t2)						# gets score of whoever's turn it is
	addi	$t3, $t3, 1							# score++
	sb	$t3, scores($t2)						# save updated score

check_bottom_square:

	bgt	$t0, 80, finish_score_update					# dont check bottom square if bottom lines played
	
	addi	$t1, $t0, 16							# check bottom line
	lb	$t1, table_position_usage_array($t1)
	beqz	$t1, finish_score_update
	
	addi	$t1, $t0, 15							# check left line
	lb	$t1, table_position_usage_array($t1)
	beqz	$t1, finish_score_update
	
	addi	$t1, $t0, 17							# check right line
	lb	$t1, table_position_usage_array($t1)
	beqz	$t1, finish_score_update
	
	lw	$t2, current_turn
	lb	$t3, scores($t2)						# gets score of whoever's turn it is
	addi	$t3, $t3, 1							# score++
	sb	$t3, scores($t2)						# save updated score
	
	j	finish_score_update

check_vertical_square:								# check squares that are part of vertical line moves
 
	beq     $t0, 17, check_right_square
	beq     $t0, 33, check_right_square
	beq     $t0, 49, check_right_square
	beq     $t0, 65, check_right_square
	beq     $t0, 81, check_right_square					# dont check left square if left lines played
	
	addi	$t1, $t0, -17							# check top line
	lb	$t1, table_position_usage_array($t1)
	beqz	$t1, check_right_square
	
	addi	$t1, $t0, -2							# check left line
	lb	$t1, table_position_usage_array($t1)
	beqz	$t1, check_right_square
	
	addi	$t1, $t0, -1							# check right line
	lb	$t1, table_position_usage_array($t1)
	beqz	$t1, check_right_square
	
	lw	$t2, current_turn
	lb	$t3, scores($t2)						# gets score of whoever's turn it is
	addi	$t3, $t3, 1							# score++
	sb	$t3, scores($t2)						# save updated score

check_right_square:

	beq	$t0, 31, finish_score_update
	beq	$t0, 47, finish_score_update
	beq	$t0, 63, finish_score_update
	beq	$t0, 79, finish_score_update
	beq	$t0, 95, finish_score_update					# dont check right square if right lines played
	
	addi	$t1, $t0, -15							# check top line
	lb	$t1, table_position_usage_array($t1)
	beqz	$t1, finish_score_update
	
	addi	$t1, $t0, 2							# check right line
	lb	$t1, table_position_usage_array($t1)
	beqz	$t1, finish_score_update
	
	addi	$t1, $t0, 1							# check bottom line
	lb	$t1, table_position_usage_array($t1)
	beqz	$t1, finish_score_update
	
	lw	$t2, current_turn
	lb	$t3, scores($t2)						# gets score of whoever's turn it is
	addi	$t3, $t3, 1							# score++
	sb	$t3, scores($t2)						# save updated score

finish_score_update:

	jr	$ra