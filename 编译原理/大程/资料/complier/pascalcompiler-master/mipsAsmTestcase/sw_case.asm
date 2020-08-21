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
checkcase0:
sw $ra, 0($fp)
addi $v0, $zero, 65
add $t0, $zero, $fp
addi $t0, $t0, 8
sw $v0, 0($t0)
add $t0, $zero, $fp
lw $v0, 8($t0)
addi $t1, $zero, 65
bne  $v0, $t1 nextcaseaddr_2
print_str("A")
addi $t0, $zero, 10
print_char($t0)
j endcaseaddr_1
nextcaseaddr_2:
addi $t1, $zero, 66
bne  $v0, $t1 nextcaseaddr_3
print_str("B")
addi $t0, $zero, 10
print_char($t0)
j endcaseaddr_1
nextcaseaddr_3:
endcaseaddr_1:
addi $sp, $sp, 100
addi $v0, $zero, 17
syscall

