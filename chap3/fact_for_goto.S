	.file	"fact_for_goto.c"
	.text
	.globl	fact_for_goto
	.type	fact_for_goto, @function
fact_for_goto:
.LFB0:
	.cfi_startproc
	movl	$1, %eax
.L2:
	cmpl	$1, %edi
	jle	.L1
	addl	$1, %edi
	movl	$2, %edx
.L3:
	imull	%edx, %eax
	addl	$1, %edx
	cmpl	%edi, %edx
	jne	.L3
.L1:
	ret
	.cfi_endproc
.LFE0:
	.size	fact_for_goto, .-fact_for_goto
	.ident	"GCC: (GNU) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
