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
exfunction0:
sw $ra, 0($fp)
addi $v0, $zero, 100
add $t0, $zero, $fp
addi $t0, $t0, 8
sw $v0, 0($t0)
addi $v0, $zero, 200
add $t0, $zero, $fp
addi $t0, $t0, 12
sw $v0, 0($t0)
addi $v0, $zero, 3
add $t0, $zero, $fp
addi $t0, $t0, 20
sw $v0, 0($t0)
add $t0, $zero, $fp
lw $v0, 8($t0)
sw $v0, -12($sp)
add $t0, $zero, $fp
lw $v0, 12($t0)
sw $v0, -8($sp)
sw $fp, -16($sp)
addi $sp, $sp, -20
add $fp, $zero, $sp
jal max1
lw $fp, 4($fp)
addi $sp, $sp, 20
add $t0, $zero, $fp
addi $t0, $t0, 16
sw $v0, 0($t0)
print_str("max value is :")
add $t0, $zero, $fp
lw $v0, 16($t0)
add $t0, $zero, $v0
print_int($t0)
addi $t0, $zero, 10
print_char($t0)
addi $sp, $sp, 100
addi $v0, $zero, 17
syscall
max1:
sw $ra, 0($fp)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 12($t0)
lw $v1, 0($sp)
sgt $v0, $v1, $v0
addi $sp, $sp, 4
beq $v0, $zero, else_1
add $t0, $zero, $fp
lw $v0, 8($t0)
add $t0, $zero, $fp
addi $t0, $t0, 16
sw $v0, 0($t0)
j endif_1
else_1:
add $t0, $zero, $fp
lw $v0, 12($t0)
add $t0, $zero, $fp
addi $t0, $t0, 16
sw $v0, 0($t0)
endif_1:
add $t0, $zero, $fp
lw $v0, 16($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $t0, 4($t0)
lw $v0, 20($t0)
lw $t1, 0($sp)
add $v0, $t1, $v0
addi $sp, $sp, 4
lw $ra, 0($fp)
jr $ra

