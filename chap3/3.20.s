# x at %ebp + 8, y at %ebp + 12, n at %ebp + 16

	movl	8(%ebp), %eax	# get x -> %eax
	movl	12(%ebp), %ecx	# get y -> %ecx
	movl	16(%ebp), $edx	# get n -> %edx

.L2:
	addl	%edx, %eax		# x += n;
	imull	%edx, %ecx		# y *= n;
	subl	$1, %edx		# n -= 1;
	testl	%edx, %edx		# | if (n > 0) && (y < n)
	jle		.L5				# |	  goto .L2 // Loop
	cmpl	%edx, %ecx		# |	else
	jl		.L2				# |	  goto .L5

.L5:						# return x;
