	.file	"3.17.c"
	.text
	.p2align 4,,15
	.globl	absdiff
	.type	absdiff, @function
absdiff:
.LFB0:
	.cfi_startproc
	movl	%edi, %edx
	movl	%esi, %eax
	subl	%esi, %edx
	subl	%edi, %eax
	cmpl	%esi, %edi
	cmovg	%edx, %eax
	ret
.L3:
	.cfi_endproc
.LFE0:
	.size	absdiff, .-absdiff
	.p2align 4,,15
	.globl	test
	.type	test, @function
test:
.LFB1:
	.cfi_startproc
	cmpl	$-3, %edi
	jl	.L6
	movl	%edi, %eax
	subl	%esi, %eax
	xorl	%edi, %esi
	cmpl	$3, %edi
	cmovl	%esi, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L6:
	leal	(%rdi,%rsi), %eax
	cmpl	%esi, %edi
	jle	.L5
	movl	%edi, %eax
	imull	%esi, %eax
.L5:
	ret
	.cfi_endproc
.LFE1:
	.size	test, .-test
	.p2align 4,,15
	.globl	test2
	.type	test2, @function
test2:
.LFB2:
	.cfi_startproc
	cmpl	$-3, %edi
	jge	.L11
	leal	(%rdi,%rsi), %eax
	cmpl	%esi, %edi
	jle	.L10
	movl	%edi, %eax
	imull	%esi, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L11:
	movl	%edi, %edx
	movl	%edi, %eax
	xorl	%esi, %edx
	subl	%esi, %eax
	cmpl	$2, %edi
	cmovle	%edx, %eax
.L10:
	ret
	.cfi_endproc
.LFE2:
	.size	test2, .-test2
	.ident	"GCC: (GNU) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
