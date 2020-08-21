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
const_circle0:
sw $ra, 0($fp)
print_str("enter the radius of the circle")
addi $t0, $zero, 10
print_char($t0)
add $t0, $zero, $fp
addi $t0, $t0, 8
li $v0, 6
syscall
swc1 $f0, 0($t0)
.data
data_1:
.float 2.000000
.text
lwc1 $f0, data_1
addi $sp, $sp, -4
swc1 $f0, 0($sp)
add $t0, $zero, $fp
lwc1 $f0, 8($t0)
lwc1 $f1, 0($sp)
mul.s $f0, $f1, $f0
addi $sp, $sp, 4
add $t0, $zero, $fp
addi $t0, $t0, 12
swc1 $f0, 0($t0)
add $t0, $zero, $fp
.data
data_2:
.float 3.100000
.text
lwc1 $f0, data_2
addi $sp, $sp, -4
swc1 $f0, 0($sp)
add $t0, $zero, $fp
lwc1 $f0, 12($t0)
lwc1 $f1, 0($sp)
mul.s $f0, $f1, $f0
addi $sp, $sp, 4
add $t0, $zero, $fp
addi $t0, $t0, 16
swc1 $f0, 0($t0)
print_str("the circumference of the circle is")
add $t0, $zero, $fp
lwc1 $f0, 16($t0)
add.s $f12, $f31, $f0
li $v0, 2
syscall
addi $t0, $zero, 10
print_char($t0)
addi $sp, $sp, 100
addi $v0, $zero, 17
syscall

