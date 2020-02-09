absSum:
	pushl	%ebp
	rrmovl	%esp, %ebp
	mrmovl	8(%ebp), %ecx	# ecx = start
	mrmovl	12(%ebp), %edx	# edx = count
	xorl	%eax, %eax		# eax = 0
	andl	%edx, %edx
	je		END

LOOP:
	mrmovl	(%ecx), %esi	# esi = *start
	irmovl	$0, %ebx
	subl	%esi, %ebx
	cmovg	%ebx, %esi
	addl	%esi, %eax
	irmovl	$1, %ebx
	subl	%ebx, %edx
	irmovl	$4, %ebx
	addl	%ebx, %ecx
	andl	%edx, %edx
	jne		LOOP

END:
	rrmovl	%ebp, %esp
	popl	%ebp
	ret


