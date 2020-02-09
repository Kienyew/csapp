# a at (%ebp + 8), b at (%ebp + 12)

	movl	8(%ebp), %ecx		# get a
	movl	12(%ebp), %ebx		# get b
	movl	$1, %eax			# set result = 1
	cmpl	%ebx, %ecx			# compare a:b
	jge		.L11				# jump to .L1 if a >= b
	leal	(%ebx, %ecx), %edx	# set tmp = a + b
	movl	$1, %eax			# set result = 1

.L12:
	imull	%edx, %eax			# result *= tmp
	addl	$1, %ecx			# a += 1
	addl	$1, %edx			# tmp += 1
	cmpl	%ecx, %ebx			# compare b:a
	jg		.L12				# jump to .L12 if b > a

.L11:

/*
int loop_while_goto(int a, int b) {
	int result = 1;
	if (!(b > a)) {
		goto DONE;
	}
	int tmp = a + b;
	result = 1;

LOOP:
	result *= tmp;
	a += 1;
	tmp += 1;
	if (b > a) {
		goto LOOP;
	}

DONE:
	return result;

}
*/
