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
testconst0:
sw $ra, 0($fp)
add $t0, $zero, $fp
addi $v0, $zero, -104842656
addi $t0, $zero, 10
print_char($t0)
add $t0, $zero, $fp
addi $v0, $zero, 1
add $t0, $zero, $v0
print_int($t0)
addi $t0, $zero, 10
print_char($t0)
add $t0, $zero, $fp
addi $v0, $zero, 97
add $t0, $zero, $v0
print_char($t0)
addi $t0, $zero, 10
print_char($t0)
add $t0, $zero, $fp
.data
data_1:
.float 1.240000
.text
lwc1 $f0, data_1
add.s $f12, $f31, $f0
li $v0, 2
syscall
addi $t0, $zero, 10
print_char($t0)
addi $sp, $sp, 100
addi $v0, $zero, 17
syscall

