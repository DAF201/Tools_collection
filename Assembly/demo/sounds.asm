.globl move_sound
move_sound:
li $v0, 31
li $a0, 61
li $a1, 140
li $a2, 87
li $a3, 35
syscall

jr $ra


.globl loss_sound
loss_sound:
li $v0, 31
li $a0, 73 			# Pitch
li $a1, 450			# Duration
li $a2, 55			# Instrument
li $a3, 50			# Volume
syscall

li $v0, 32
li $a0, 420
syscall

li $v0, 31
li $a0, 72
li $a1, 600
li $a2, 55
li $a3, 50
syscall

jr $ra


.globl win_sound
win_sound:
li $v0, 31
li $a0, 61
li $a1, 375
li $a2, 85
li $a3, 50
syscall

li $v0, 32
li $a0, 350
syscall

li $v0, 31
li $a0, 65
li $a1, 375
li $a2, 85
li $a3, 50
syscall

li $v0, 32
li $a0, 350
syscall

li $v0, 31
li $a0, 68
li $a1, 600
li $a2, 85
li $a3, 50
syscall

jr $ra