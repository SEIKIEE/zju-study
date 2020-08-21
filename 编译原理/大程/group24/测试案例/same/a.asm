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
go:
	move $t3,$a0
	move $t4,$a1
	li $t5,0
	seq $t5,$t4,$t5
	beq $t5,$zero,L0
	move $t6,$t3
	move $t7,$a0
	move $a0,$t6
	li $t6,1
	sub $t6,$t4,$t6
	move $t8,$a1
	move $a1,$t6
	addi $sp,$sp,-28
	sw $t7,0($sp)
	sw $t8,4($sp)
	sw $ra,8($sp)
	sw $t3,12($sp)
	sw $t4,16($sp)
	sw $t5,20($sp)
	sw $t6,24($sp)
	jal go
	lw $a0,0($sp)
	lw $a1,4($sp)
	lw $ra,8($sp)
	lw $t3,12($sp)
	lw $t4,16($sp)
	lw $t5,20($sp)
	lw $t6,24($sp)
	addi $sp,$sp,28
	move $t6 $v0
	mul $t6,$t4,$t6
	move $t0,$t6
L0:
	bne $t5,$zero,L1
	li $t0,1
L1:
	add $t5,$t3,$t0
	move $t3,$t5
	add $t5,$t1,$t0
	move $t1,$t5
	move $v0,$t0
	jr $ra
main:
	li $t1,0
	move $t5,$t1
	move $t6,$a0
	move $a0,$t5
	li $t5,5
	move $t9,$a1
	move $a1,$t5
	addi $sp,$sp,-32
	sw $t6,0($sp)
	sw $t9,4($sp)
	sw $ra,8($sp)
	sw $t3,12($sp)
	sw $t4,16($sp)
	sw $t5,20($sp)
	sw $t7,24($sp)
	sw $t8,28($sp)
	jal go
	lw $a0,0($sp)
	lw $a1,4($sp)
	lw $ra,8($sp)
	lw $t3,12($sp)
	lw $t4,16($sp)
	lw $t5,20($sp)
	lw $t7,24($sp)
	lw $t8,28($sp)
	addi $sp,$sp,32
	move $t5 $v0
	move $t2,$t5
	move $t5,$t2
	move $s0,$a0
	move $a0,$t5
	addi $sp,$sp,-8
	sw $a0,0($sp)
	sw $ra,4($sp)
	jal WRITELN
	lw $a0,0($sp)
	lw $ra,4($sp)
	addi $sp,$sp,8
	move $t5,$t1
	move $s1,$a0
	move $a0,$t5
	addi $sp,$sp,-8
	sw $a0,0($sp)
	sw $ra,4($sp)
	jal WRITELN
	lw $a0,0($sp)
	lw $ra,4($sp)
	addi $sp,$sp,8
	move $v0,$zero
	jr $ra
