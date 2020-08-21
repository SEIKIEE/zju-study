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
opcode0:
sw $ra, 0($fp)
addi $v0, $zero, 123
add $t0, $zero, $fp
addi $t0, $t0, 8
sw $v0, 0($t0)
addi $v0, $zero, 456
add $t0, $zero, $fp
addi $t0, $t0, 12
sw $v0, 0($t0)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 12($t0)
lw $t1, 0($sp)
add $v0, $t1, $v0
addi $sp, $sp, 4
add $t0, $zero, $fp
addi $t0, $t0, 16
sw $v0, 0($t0)
add $t0, $zero, $fp
lw $v0, 16($t0)
add $t0, $zero, $v0
print_int($t0)
addi $t0, $zero, 10
print_char($t0)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 12($t0)
lw $t1, 0($sp)
sub $v0, $t1, $v0
addi $sp, $sp, 4
add $t0, $zero, $fp
addi $t0, $t0, 16
sw $v0, 0($t0)
add $t0, $zero, $fp
lw $v0, 16($t0)
add $t0, $zero, $v0
print_int($t0)
addi $t0, $zero, 10
print_char($t0)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 12($t0)
lw $t1, 0($sp)
mult $t1, $v0
mflo $v0
addi $sp, $sp, 4
add $t0, $zero, $fp
addi $t0, $t0, 16
sw $v0, 0($t0)
add $t0, $zero, $fp
lw $v0, 16($t0)
add $t0, $zero, $v0
print_int($t0)
addi $t0, $zero, 10
print_char($t0)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 12($t0)
lw $t1, 0($sp)
div $t1, $v0
mflo $v0
addi $sp, $sp, 4
add $t0, $zero, $fp
addi $t0, $t0, 16
sw $v0, 0($t0)
add $t0, $zero, $fp
lw $v0, 16($t0)
add $t0, $zero, $v0
print_int($t0)
addi $t0, $zero, 10
print_char($t0)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 12($t0)
lw $t1, 0($sp)
div $v0, $t1, $v0
mfhi $v0
addi $sp, $sp, 4
add $t0, $zero, $fp
addi $t0, $t0, 16
sw $v0, 0($t0)
add $t0, $zero, $fp
lw $v0, 16($t0)
add $t0, $zero, $v0
print_int($t0)
addi $t0, $zero, 10
print_char($t0)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 12($t0)
lw $t1, 0($sp)
or $v0, $t1, $v0
addi $sp, $sp, 4
add $t0, $zero, $fp
addi $t0, $t0, 16
sw $v0, 0($t0)
add $t0, $zero, $fp
lw $v0, 16($t0)
add $t0, $zero, $v0
print_int($t0)
addi $t0, $zero, 10
print_char($t0)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 12($t0)
lw $t1, 0($sp)
and $v0, $t1, $v0
addi $sp, $sp, 4
add $t0, $zero, $fp
addi $t0, $t0, 16
sw $v0, 0($t0)
add $t0, $zero, $fp
lw $v0, 16($t0)
add $t0, $zero, $v0
print_int($t0)
addi $t0, $zero, 10
print_char($t0)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 12($t0)
lw $t1, 0($sp)
add $v0, $t1, $v0
addi $sp, $sp, 4
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 16($t0)
lw $t1, 0($sp)
sub $v0, $t1, $v0
addi $sp, $sp, 4
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 12($t0)
lw $t1, 0($sp)
and $v0, $t1, $v0
addi $sp, $sp, 4
lw $t1, 0($sp)
add $v0, $t1, $v0
addi $sp, $sp, 4
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 16($t0)
lw $t1, 0($sp)
or $v0, $t1, $v0
addi $sp, $sp, 4
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lw $v0, 16($t0)
lw $t1, 0($sp)
add $v0, $t1, $v0
addi $sp, $sp, 4
lw $t1, 0($sp)
sub $v0, $t1, $v0
addi $sp, $sp, 4
add $t0, $zero, $fp
addi $t0, $t0, 16
sw $v0, 0($t0)
add $t0, $zero, $fp
lw $v0, 16($t0)
add $t0, $zero, $v0
print_int($t0)
addi $t0, $zero, 10
print_char($t0)
addi $sp, $sp, 100
addi $v0, $zero, 17
syscall

