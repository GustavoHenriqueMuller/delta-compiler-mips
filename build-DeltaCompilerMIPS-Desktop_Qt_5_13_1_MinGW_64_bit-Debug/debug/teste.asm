.data
	i_2: .word 0
	j_3: .word 0

.text
	subi $sp, $sp, 4
	addi $t0, $zero, 0
	sw $t0, 0($sp)
	lw $t0, 0($sp)
	sw $t0, i_2
	addi $sp, $sp, 4
for_start_0:
	subi $sp, $sp, 4
	lw $t0, i_2
	sw $t0, 0($sp)
	subi $sp, $sp, 4
	addi $t0, $zero, 10
	sw $t0, 0($sp)
	lw $t0, 4($sp)
	lw $t1, 0($sp)
	sub $t2, $t0, $t1
	addi $sp, $sp, 8
	subi $sp, $sp, 4
	slt $t0, $t2, $zero
	sw $t0, 0($sp)
	lw $t0, 0($sp)
	beq $t0, $zero, for_end_0
	addi $sp, $sp, 4
	subi $sp, $sp, 4
	addi $t0, $zero, 0
	sw $t0, 0($sp)
	lw $t0, 0($sp)
	sw $t0, j_3
	addi $sp, $sp, 4
for_start_1:
	subi $sp, $sp, 4
	lw $t0, j_3
	sw $t0, 0($sp)
	subi $sp, $sp, 4
	addi $t0, $zero, 20
	sw $t0, 0($sp)
	lw $t0, 4($sp)
	lw $t1, 0($sp)
	sub $t2, $t0, $t1
	addi $sp, $sp, 8
	subi $sp, $sp, 4
	slt $t0, $t2, $zero
	sw $t0, 0($sp)
	lw $t0, 0($sp)
	beq $t0, $zero, for_end_1
	addi $sp, $sp, 4
	subi $sp, $sp, 4
	lw $t0, j_3
	sw $t0, 0($sp)
	li $v0, 1
	lw $a0, 0($sp)
	syscall
	addi $sp, $sp, 4
	li $v0, 11
	li $a0, 10
	syscall
	lw $t0, j_3
	subi $sp, $sp, 4
	sw $t0, 0($sp)
	addi $t0, $t0, 1
	sw $t0, j_3
	j for_start_1
for_end_1:
	lw $t0, i_2
	subi $sp, $sp, 4
	sw $t0, 0($sp)
	addi $t0, $t0, 1
	sw $t0, i_2
	j for_start_0
for_end_0:
	li $v0, 10
	syscall
