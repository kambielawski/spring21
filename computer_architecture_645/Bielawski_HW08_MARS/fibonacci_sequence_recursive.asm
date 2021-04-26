
caller:		addi 	$a0, $zero, 18		# initialize argument register $a0 with n = 18
#######		#addi 	$a1, $zero, 0x100100A0	# this instruction is treated as a pseudo instrcution, replace it with the proper basic MIPS instructions
		lui	$a1, 0x1001
		ori	$a1, 0x00A0
		jal	fib_seq			# call fib_seq
next:		j	exit

##############################################################################
# This routine generates Fibonacci sequence fib(0), fib(1), fib(2), ... fib(n)
# and stores it into the data segment starting at memory address 0x100100A0
# which is pointed at by register $a1

# unsigned int fib_seq(unsigned int n, &fib_array){
# 	for i = 0 to n
# 		fib_array[i] = fib(i);
# 	return fib_array[n];}

# unsigned int fib(unsigned int n){
# 	if (n==0 || n==1) return n;
# 	else return fib(n−1) + fib(n−2);}

fib_seq:
####################### Insert Your Code Here ################################
		
		addi	$sp, $sp, -12		# allocate 12 bytes for stack
		sw	$ra, 8($sp)		# push return address to stack
		sw	$a0, 4($sp)		# push $a0 (n) to stack
		sw	$a1, 0($sp)		# push $a1 (fib_array ptr) to stack
		
		add	$t0, $zero, $zero	# use $t0 as i variable
		addi	$t3, $a0, 1		# store (n+1) in $t3
loop:		slt	$t2, $t0, $t3		# i < (n+1)?
		beq	$t2, $zero, ret_fib_seq	# jump to return if (i >= n)
		sll	$t1, $t0, 2		# store i*4 in $t1 (array offset)
		add	$t1, $a1, $t1		# add offset to array
		add	$a0, $zero, $t0		# ensure i is the argument
		jal	fib			# call fib(i)
		sw	$v0, 0($t1)		# store return value in current offset of array
		addi	$t0, $t0, 1		# increment i
		j	loop

ret_fib_seq:	lw	$ra, 8($sp)		# pop return address from stack
		lw	$a0, 4($sp)
		lw 	$a1, 0($sp)
		addi	$sp, $sp, 12
		jr	$ra			
		




fib:		addi	$sp, $sp, -12		# allocate 12 bytes for stack
		sw	$ra, 8($sp)		# push return address to stack
		sw	$a0, 4($sp)		# push arg 1 to stack
		sw	$s0, 0($sp)		# push a save variable to stack
		
		add	$v0, $zero, $a0		# store n in return address in case branching occurs
		beq	$a0, $zero, ret_fib	# n == 0?
		addi	$s0, $zero, 1		# store 1
		beq 	$a0, $s0, ret_fib	# n == 1?
		
		# call fib on (n-1)
		addi	$a0, $a0, -1		
		jal	fib
		
		# move return value into $s0
		add 	$s0, $zero, $v0
		
		# call fib on (n-2)
		addi	$a0, $a0, -1
		jal	fib
		
		# store fib(n-1) + fib(n-2) in return register
		add	$v0, $v0, $s0
		
		# pop from stack and return to $ra
ret_fib:	lw	$ra, 8($sp)
		lw	$a0, 4($sp)
		lw	$s0, 0($sp)
		addi	$sp, $sp, 12
		jr	$ra
		


##############################################################################

exit:		
