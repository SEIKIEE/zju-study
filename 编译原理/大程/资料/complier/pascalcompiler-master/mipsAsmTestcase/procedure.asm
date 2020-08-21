.macro print_int (%x)
	li $v0, 1
	add $a0, $zero, %x
	syscall
.end_macro

.macro print_char (%x)
	li $v0, 11
	add $a0, $zero, %x
	syscall
.end_macro

.macro print_str (%str)
	.data
		myLabel: .asciiz %str

	.text
	li $v0, 4
	la $a0, myLabel
	syscall
.end_macro
addi $sp, $sp,   -100
add  $fp, $zero, $sp
exprocedure0:
sw $ra, 0($fp)
print_str(" enter three numbers: ")
addi $t0, $zero, 10
print_char($t0)
add $t0, $zero, $fp
addi $t0, $t0, 8
li $v0, 5
syscall
sw $v0, 0($t0)
add $t0, $zero, $fp
addi $t0, $t0, 12
li $v0, 5
syscall
sw $v0, 0($t0)
add $t0, $zero, $fp
addi $t0, $t0, 16
li $v0, 5
syscall
sw $v0, 0($t0)
add $t0, $zero, $fp
lw $v0, 8($t0)
sw $v0, -16($sp)
add $t0, $zero, $fp
lw $v0, 12($t0)
sw $v0, -12($sp)
add $t0, $zero, $fp
lw $v0, 16($t0)
sw $v0, -8($sp)
add $t0, $zero, $fp
lw $v0, 20($t0)
sw $v0, -4($sp)
sw $fp, -20($sp)
addi $sp, $sp, -24
add $fp, $zero, $sp
jal findmin1
lw $fp, 4($fp)
addi $sp, $sp, 24
lw $t1, -4($sp)
add $t0, $zero, $fp
sw $t1, 20($t0)
print_str(" minimum: ")
addi $t0, $zero, 10
print_char($t0)
add $t0, $zero, $fp
lw $v0, 20($t0)
add $t0, $zero, $v0
print_int($t0)
addi $t0, $zero, 10
print_char($t0)
addi $sp, $sp, 100
addi $v0, $zero, 17
syscall
findmin1:
sw $ra, 0($fp)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 12($t0)
lw $v1, 0($sp)
slt $v0, $v1, $v0
addi $sp, $sp, 4
beq $v0, $zero, else_1
add $t0, $zero, $fp
lw $v0, 8($t0)
add $t0, $zero, $fp
addi $t0, $t0, 20
sw $v0, 0($t0)
j endif_1
else_1:
add $t0, $zero, $fp
lw $v0, 12($t0)
add $t0, $zero, $fp
addi $t0, $t0, 20
sw $v0, 0($t0)
endif_1:
add $t0, $zero, $fp
lw $v0, 16($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 20($t0)
lw $v1, 0($sp)
slt $v0, $v1, $v0
addi $sp, $sp, 4
beq $v0, $zero, else_2
add $t0, $zero, $fp
lw $v0, 16($t0)
add $t0, $zero, $fp
addi $t0, $t0, 20
sw $v0, 0($t0)
j endif_2
else_2:
endif_2:
lw $ra, 0($fp)
jr $ra

