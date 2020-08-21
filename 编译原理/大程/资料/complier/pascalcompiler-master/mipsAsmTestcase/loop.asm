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
xunhuan0:
sw $ra, 0($fp)
add $t0, $zero, $fp
addi $sp, $sp, -4
sw $t0, 0($sp)
addi $v0, $zero, 3
addi $v0, $v0, 1
addi $sp, $sp, -4
sw $v0, 0($sp)
addi $v0, $zero, 1
lw $t0, 4($sp)
sw $v0, 8($t0)
for_start_1:
lw   $v1, 0($sp)
slt  $t0, $v0, $v1
beq  $t0, $zero, for_end_1
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
addi $v0, $zero, 1
lw $t1, 0($sp)
add $v0, $t1, $v0
addi $sp, $sp, 4
add $t0, $zero, $fp
addi $t0, $t0, 8
sw $v0, 0($t0)
lw   $t0, 4($sp)
lw   $v0, 8($t0)
addi $v0, $v0, 1
sw   $v0, 8($t0)
j for_start_1
for_end_1:
lw $t0, 4($sp)
lw $v0, 8($t0)
addi $v0, $v0, -1
sw $v0, 8($t0)
addi $sp, $sp, 8
add $t0, $zero, $fp
lw $v0, 8($t0)
add $t0, $zero, $v0
print_int($t0)
addi $t0, $zero, 10
print_char($t0)
addi $v0, $zero, 1
add $t0, $zero, $fp
addi $t0, $t0, 8
sw $v0, 0($t0)
while_start_2:
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
addi $v0, $zero, 5
lw $v1, 0($sp)
slt $v0, $v1, $v0
addi $sp, $sp, 4
beq $v0, $zero, while_end_2
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
addi $v0, $zero, 1
lw $t1, 0($sp)
add $v0, $t1, $v0
addi $sp, $sp, 4
add $t0, $zero, $fp
addi $t0, $t0, 8
sw $v0, 0($t0)
j while_start_2
while_end_2:
add $t0, $zero, $fp
lw $v0, 8($t0)
add $t0, $zero, $v0
print_int($t0)
addi $t0, $zero, 10
print_char($t0)
addi $v0, $zero, 1
add $t0, $zero, $fp
addi $t0, $t0, 8
sw $v0, 0($t0)
until_3:
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
addi $v0, $zero, 1
lw $t1, 0($sp)
add $v0, $t1, $v0
addi $sp, $sp, 4
add $t0, $zero, $fp
addi $t0, $t0, 8
sw $v0, 0($t0)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
addi $v0, $zero, 1
lw $t1, 0($sp)
add $v0, $t1, $v0
addi $sp, $sp, 4
add $t0, $zero, $fp
addi $t0, $t0, 8
sw $v0, 0($t0)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
addi $v0, $zero, 9
lw $v1, 0($sp)
seq $v0, $v1, $v0
addi $sp, $sp, 4
beq $v0, $zero, until_3
add $t0, $zero, $fp
lw $v0, 8($t0)
add $t0, $zero, $v0
print_int($t0)
addi $t0, $zero, 10
print_char($t0)
addi $sp, $sp, 100
addi $v0, $zero, 17
syscall

