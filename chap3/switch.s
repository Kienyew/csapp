	.file	"switch.c"
	.text
	.globl	switch_impl
	.type	switch_impl, @function
switch_impl:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	cmpl	$102, -20(%rbp)
	je	.L2
	cmpl	$102, -20(%rbp)
	jg	.L3
	cmpl	$100, -20(%rbp)
	je	.L4
	cmpl	$101, -20(%rbp)
	je	.L5
	jmp	.L6
.L3:
	cmpl	$104, -20(%rbp)
	jl	.L6
	cmpl	$108, -20(%rbp)
	jle	.L7
	cmpl	$888, -20(%rbp)
	je	.L8
	jmp	.L6
.L4:
	movl	-20(%rbp), %eax
	addl	%eax, %eax
	movl	%eax, -4(%rbp)
	jmp	.L9
.L5:
	movl	-20(%rbp), %eax
	addl	$2, %eax
	movl	%eax, -4(%rbp)
	jmp	.L9
.L2:
	movl	$1, -4(%rbp)
	jmp	.L9
.L7:
	movl	-20(%rbp), %eax
	addl	%eax, %eax
	subl	$3, %eax
	movl	%eax, -4(%rbp)
	jmp	.L9
.L8:
	movl	-20(%rbp), %eax
	imull	$888, %eax, %eax
	movl	%eax, -4(%rbp)
	jmp	.L9
.L6:
	movl	$0, -4(%rbp)
	nop
.L9:
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	switch_impl, .-switch_impl
	.ident	"GCC: (GNU) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
