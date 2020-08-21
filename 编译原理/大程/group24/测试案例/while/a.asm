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
main:
	li $t0,1
L0:
	li $t1,5
	slt $t1,$t0,$t1
	beq $t1,$zero,L1
	li $t1,1
	add $t1,$t0,$t1
	move $t0,$t1
	j L0
L1:
	move $t1,$t0
	move $t2,$a0
	move $a0,$t1
	addi $sp,$sp,-8
	sw $a0,0($sp)
	sw $ra,4($sp)
	jal WRITELN
	lw $a0,0($sp)
	lw $ra,4($sp)
	addi $sp,$sp,8
	move $v0,$zero
	jr $ra
