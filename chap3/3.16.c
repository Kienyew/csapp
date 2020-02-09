void cond(int a, int *p) {
	if (p == NULL || a <= 0) {
		goto L3;
	}

	*p += a;


L3:
	return;
}

/*

movl	8(%ebp), %edx	# get a;
movl	12(%ebp), %eax	# get p;
testl	%eax, %eax		# if (p == NULL):	|	if (p == NULL || a <= 0)
je		.L3				# 	goto .L3;		|	{
testl	%edx, %edx		# else if (a <= 0):	|		goto .L3;
jle		.L3				#	goto .L3;		|	}
addl	%edx, (%eax)	# else:	*p = *p + a;

L3.:
*/
