
caller:		addi 	$a0, $zero, 18		# initialize argument register $a0 with n = 18
#######		#addi 	$a1, $zero, 0x100100A0	# this instruction is treated as a pseudo instrcution, replace it with the proper basic MIPS instructions
		lui	$a1, 0x1001
		ori	$a1, $a1, 0x00A0
		jal	fib_seq			# call fib_seq
next:		j	exit

##############################################################################
# This routine generates Fibonacci sequence fib(0), fib(1), fib(2), ... fib(n)
# and stores it into the data segment starting at memory address 0x100100A0
# which is pointed at by register $a1

# unsigned int fib_seq(unsigned int n, &fib_array){
# 	fib_array[0] = 0;
# 	if (n>=1) fib_array[1] = 1;
# 	for i = 2 to n
# 		fib_array[i] = fib_array[i−1] + fib_array[i−2];
# 	return fib_array[n];}

fib_seq:	
####################### Insert Your Code Here ################################
# $a0 has 18 in it (n)
# $a1 has the base address of fib_array

		# stack setup
		addi	$sp, $sp, -20		# allocate 12 bytes for stack
		sw	$ra, 16($sp)		# push return address to stack
		sw 	$a1, 12($sp) 		# push $a1 to stack (the fib_array address)
		sw	$a0, 8($sp)		# push $a0 to stack (n)
		sw	$s0, 4($sp)		# push $s0 to stack
		sw	$s1, 0($sp)		# push $s1 to stack
		
		# start function operations
		sw 	$zero, 0($a1)		# fib_array[0] = 0
		addi	$t1, $zero, 1		# store 1 in $t1
		slt 	$t0, $a0, $t1		# store (n < 1) in $t0
		bne	$t0, $zero, loop	# go to loop if (n < 1)
		sw	$t1, 4($a1)		# store 1 in fib_array[1]
		
		# set up proper array indexing
loop:		addi	$t1, $t1, 1		# $t1 will hold our iterator i
		addi	$t2, $t1, -1		# put (n-1) in $t2
		addi	$t3, $t1, -2		# put (n-2) in $t3
		sll	$t2, $t2, 2		# multiply (n-1) by 4 in place (for indexing)
		sll	$t3, $t3, 2		# multiply (n-2) by 4 in place
		sll	$t4, $t1, 2		# store i*4 in $t4
		add	$t2, $a1, $t2		# add (n-1)*4 to array offset (for accessing)
		add	$t3, $a1, $t3		# add (n-2)*4 to array offset
		add 	$t4, $a1, $t4		# put address of a[i] in $t4
		
		# load memory and compute
		lw	$s0, 0($t2)		# load fib_array[n-1]
		lw	$s1, 0($t3)		# load fib_array[n-2]
		add	$s0, $s0, $s1		# store fib_array[n-1] + fib_array[n-2] in $s0
		sw 	$s0, 0($t4)		# store newly computed var
		
		# branch if i == n
		beq	$t1, $a0, return
		j	loop
		
		# return proper variable
return: 	add 	$v0, $zero, $s0		# store $s0 (fib[n]) in return register
		
		# pop stack
		lw	$ra, 16($sp)		# pop return address from stack
		lw 	$a1, 12($sp) 		# pop $a1 from stack (the fib_array address)
		lw	$a0, 8($sp)		# pop $a0 to stack (n)
		lw	$s0, 4($sp)		# pop $s0 to stack
		lw	$s1, 0($sp)		# pop $s1 to stack
		addi	$sp, $sp, 20		# pop stack
		
		# return
		jr	$ra


##############################################################################

exit:		
