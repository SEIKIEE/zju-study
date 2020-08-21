.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
READ:
    li $v0,4
    la $a0,_prompt
    syscall
    li $v0,5
    syscall
    jr $ra
WRITE:
    li $v0,1
    syscall
    li $v0,4
    la $a0,_ret
    syscall
    move $v0,$0
    jr $ra
WRITELN:
    li $v0,1
    syscall
    li $v0,4
    la $a0,_ret
    syscall
    move $v0,$0
    jr $ra
gcd:
	move $t2,$a0
	move $t3,$a1
	li $t4,0
	seq $t4,$t3,$t4
	beq $t4,$zero,L0
	move $t0,$t2
L0:
	bne $t4,$zero,L1
	move $t4,$t3
	move $t5,$a0
	move $a0,$t4
	div $t2,$t3
	mfhi $t4
	move $t6,$a1
	move $a1,$t4
	addi $sp,$sp,-24
	sw $t5,0($sp)
	sw $t6,4($sp)
	sw $ra,8($sp)
	sw $t2,12($sp)
	sw $t3,16($sp)
	sw $t4,20($sp)
	jal gcd
	lw $a0,0($sp)
	lw $a1,4($sp)
	lw $ra,8($sp)
	lw $t2,12($sp)
	lw $t3,16($sp)
	lw $t4,20($sp)
	addi $sp,$sp,24
	move $t4 $v0
	move $t0,$t4
L1:
	move $v0,$t0
	jr $ra
main:
	li $t4,9
	move $t7,$a0
	move $a0,$t4
	li $t4,36
	move $t8,$a1
	move $a1,$t4
	addi $sp,$sp,-32
	sw $t7,0($sp)
	sw $t8,4($sp)
	sw $ra,8($sp)
	sw $t2,12($sp)
	sw $t3,16($sp)
	sw $t4,20($sp)
	sw $t5,24($sp)
	sw $t6,28($sp)
	jal gcd
	lw $a0,0($sp)
	lw $a1,4($sp)
	lw $ra,8($sp)
	lw $t2,12($sp)
	lw $t3,16($sp)
	lw $t4,20($sp)
	lw $t5,24($sp)
	lw $t6,28($sp)
	addi $sp,$sp,32
	move $t4 $v0
	li $t9,3
	move $s0,$a0
	move $a0,$t9
	li $t9,6
	move $s1,$a1
	move $a1,$t9
	addi $sp,$sp,-44
	sw $s0,0($sp)
	sw $s1,4($sp)
	sw $ra,8($sp)
	sw $t2,12($sp)
	sw $t3,16($sp)
	sw $t4,20($sp)
	sw $t5,24($sp)
	sw $t6,28($sp)
	sw $t7,32($sp)
	sw $t8,36($sp)
	sw $t9,40($sp)
	jal gcd
	lw $a0,0($sp)
	lw $a1,4($sp)
	lw $ra,8($sp)
	lw $t2,12($sp)
	lw $t3,16($sp)
	lw $t4,20($sp)
	lw $t5,24($sp)
	lw $t6,28($sp)
	lw $t7,32($sp)
	lw $t8,36($sp)
	lw $t9,40($sp)
	addi $sp,$sp,44
	move $t9 $v0
	mul $t4,$t4,$t9
	move $t1,$t4
	move $t4,$t1
	move $t9,$a0
	move $a0,$t4
	addi $sp,$sp,-8
	sw $a0,0($sp)
	sw $ra,4($sp)
	jal WRITELN
	lw $a0,0($sp)
	lw $ra,4($sp)
	addi $sp,$sp,8
	move $v0,$zero
	jr $ra
