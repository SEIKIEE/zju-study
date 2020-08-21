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
max:
	move $t5,$a0
	move $t6,$a1
	sgt $t7,$t5,$t6
	beq $t7,$zero,L0
	move $t0,$t5
L0:
	bne $t7,$zero,L1
	move $t0,$t6
L1:
	add $t7,$t0,$t1
	move $t2,$t7
	move $v0,$t2
	jr $ra
main:
	li $t3,100
	li $t4,200
	move $t7,$t3
	move $t8,$a0
	move $a0,$t7
	move $t7,$t4
	move $t9,$a1
	move $a1,$t7
	addi $sp,$sp,-24
	sw $t8,0($sp)
	sw $t9,4($sp)
	sw $ra,8($sp)
	sw $t5,12($sp)
	sw $t6,16($sp)
	sw $t7,20($sp)
	jal max
	lw $a0,0($sp)
	lw $a1,4($sp)
	lw $ra,8($sp)
	lw $t5,12($sp)
	lw $t6,16($sp)
	lw $t7,20($sp)
	addi $sp,$sp,24
	move $t7 $v0
	move $t1,$t7
	move $t7,$t1
	move $s0,$a0
	move $a0,$t7
	addi $sp,$sp,-8
	sw $a0,0($sp)
	sw $ra,4($sp)
	jal WRITE
	lw $a0,0($sp)
	lw $ra,4($sp)
	addi $sp,$sp,8
	move $v0,$zero
	jr $ra
