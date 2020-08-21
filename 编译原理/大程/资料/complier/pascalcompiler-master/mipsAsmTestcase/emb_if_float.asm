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
.data
data_1:
.float 1.100000
.text
lwc1 $f0, data_1
add $t0, $zero, $fp
addi $t0, $t0, 8
swc1 $f0, 0($t0)
.data
data_2:
.float 2.200000
.text
lwc1 $f0, data_2
add $t0, $zero, $fp
addi $t0, $t0, 12
swc1 $f0, 0($t0)
.data
data_3:
.float 3.300000
.text
lwc1 $f0, data_3
add $t0, $zero, $fp
addi $t0, $t0, 16
swc1 $f0, 0($t0)
add $t0, $zero, $fp
lwc1 $f0, 12($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lwc1 $f0, 8($t0)
lw $v1, 0($sp)
slt $v0, $v1, $v0
addi $sp, $sp, 4
beq $v0, $zero, else_4
print_str("b<a")
addi $t0, $zero, 10
print_char($t0)
j endif_4
else_4:
add $t0, $zero, $fp
lwc1 $f0, 16($t0)
addi $sp, $sp, -4
sw $v0, 0($sp)
add $t0, $zero, $fp
lwc1 $f0, 8($t0)
lw $v1, 0($sp)
slt $v0, $v1, $v0
addi $sp, $sp, 4
beq $v0, $zero, else_5
print_str("c<a")
addi $t0, $zero, 10
print_char($t0)
j endif_5
else_5:
print_str("c>=a")
addi $t0, $zero, 10
print_char($t0)
endif_5:
endif_4:
addi $sp, $sp, 100
addi $v0, $zero, 17
syscall

