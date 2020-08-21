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
	move $t2,$a0
	li $t3,1
	seq $t3,$t2,$t3
	beq $t3,$zero,L0
	li $t0,1
L0:
	bne $t3,$zero,L1
	li $t3,2
	seq $t3,$t2,$t3
	beq $t3,$zero,L2
	li $t0,1
L2:
	bne $t3,$zero,L3
	li $t3,1
	sub $t3,$t2,$t3
	move $t4,$a0
	move $a0,$t3
	addi $sp,$sp,-16
	sw $t4,0($sp)
	sw $ra,4($sp)
	sw $t2,8($sp)
	sw $t3,12($sp)
	jal go
	lw $a0,0($sp)
	lw $ra,4($sp)
	lw $t2,8($sp)
	lw $t3,12($sp)
	addi $sp,$sp,16
	move $t3 $v0
	li $t5,2
	sub $t5,$t2,$t5
	move $t6,$a0
	move $a0,$t5
	addi $sp,$sp,-24
	sw $t6,0($sp)
	sw $ra,4($sp)
	sw $t2,8($sp)
	sw $t3,12($sp)
	sw $t4,16($sp)
	sw $t5,20($sp)
	jal go
	lw $a0,0($sp)
	lw $ra,4($sp)
	lw $t2,8($sp)
	lw $t3,12($sp)
	lw $t4,16($sp)
	lw $t5,20($sp)
	addi $sp,$sp,24
	move $t5 $v0
	add $t3,$t3,$t5
	move $t0,$t3
L3:
L1:
	move $v0,$t0
	jr $ra
main:
	li $t3,10
	move $t5,$a0
	move $a0,$t3
	addi $sp,$sp,-24
	sw $t5,0($sp)
	sw $ra,4($sp)
	sw $t2,8($sp)
	sw $t3,12($sp)
	sw $t4,16($sp)
	sw $t6,20($sp)
	jal go
	lw $a0,0($sp)
	lw $ra,4($sp)
	lw $t2,8($sp)
	lw $t3,12($sp)
	lw $t4,16($sp)
	lw $t6,20($sp)
	addi $sp,$sp,24
	move $t3 $v0
	move $t1,$t3
	move $t3,$t1
	move $t7,$a0
	move $a0,$t3
	addi $sp,$sp,-8
	sw $a0,0($sp)
	sw $ra,4($sp)
	jal WRITELN
	lw $a0,0($sp)
	lw $ra,4($sp)
	addi $sp,$sp,8
	move $v0,$zero
	jr $ra
