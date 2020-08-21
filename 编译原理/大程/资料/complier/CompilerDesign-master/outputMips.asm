#Prolog: 
.text 
.globl  main 
main: 
move  $fp  $sp 		 
la  $a0  ProgBegin 
li  $v0 4 
syscall 
#End of Prolog
	#all code will go below here...
li $t0  999 
sw $t0  0 ($fp)
l.s  $f0  Label0 
s.s $f0  -4 ($fp)
li $t0 0 
l.s $f0 0 ($fp)
l.s $f2 -4 ($fp)
cvt.s.w $f4 $f0 
mov.s $f0 $f4 
c.lt.s  $f2 $f0
bc1f endIf1  
li $t0 1 
endIf1 :  
sw $t0 0 ($fp)
lw $t0 0 ($fp)
beqz  $t0  endIf0 
la $a0 Label1 
li $v0 4 
syscall   
la $a0 CR 
li $v0 4 
syscall   
endIf0 :  

#Postlog:
la  $a0  ProgEnd
li  $v0  4
syscall
li  $v0  10
syscall

.data
ProgBegin:  .asciiz "Program Begin\n"
ProgEnd:   .asciiz "\nProgram End\n"
CR: .asciiz "\n"
Label0: .float 998.0
Label1: .asciiz "A"
