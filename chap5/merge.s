	.file	"merge.c"
	.text
	.p2align 4
	.globl	merge
	.type	merge, @function
merge:
.LFB0:
	.cfi_startproc
	testl	%ecx, %ecx
	jle	.L13
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$1, %r9d
	xorl	%eax, %eax
	xorl	%r8d, %r8d
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L18:
	addl	$1, %r8d
.L4:
	movl	%r10d, -4(%rdx,%r9,4)
	cmpl	%eax, %r8d
	movl	%eax, %r10d
	movslq	%r9d, %r11
	cmovge	%r8d, %r10d
	leaq	1(%r9), %rbx
	cmpl	%ecx, %r10d
	jge	.L17
	movq	%rbx, %r9
.L5:
	movslq	%r8d, %r10
	movslq	%eax, %r11
	movl	(%rdi,%r10,4), %r10d
	movl	(%rsi,%r11,4), %r11d
	cmpl	%r11d, %r10d
	jl	.L18
	addl	$1, %eax
	movl	%r11d, %r10d
	jmp	.L4
	.p2align 4,,10
	.p2align 3
.L17:
	cmpl	%ecx, %r8d
	jge	.L6
	movslq	%r8d, %rsi
	subq	%rsi, %r11
	leaq	(%rdx,%r11,4), %r11
	.p2align 4,,10
	.p2align 3
.L7:
	movl	(%rdi,%rsi,4), %r10d
	movl	%r10d, (%r11,%rsi,4)
	addq	$1, %rsi
	cmpl	%esi, %ecx
	jg	.L7
	leal	(%rcx,%r9), %r11d
	subl	%r8d, %r11d
.L6:
	cmpl	%ecx, %eax
	jge	.L1
	cltq
	movslq	%r11d, %r11
	subq	%rax, %r11
	leaq	(%rdx,%r11,4), %rsi
	.p2align 4,,10
	.p2align 3
.L8:
	movl	(%rdi,%rax,4), %edx
	movl	%edx, (%rsi,%rax,4)
	addq	$1, %rax
	cmpl	%eax, %ecx
	jg	.L8
.L1:
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L13:
	.cfi_restore 3
	ret
	.cfi_endproc
.LFE0:
	.size	merge, .-merge
	.ident	"GCC: (GNU) 9.2.0"
	.section	.note.GNU-stack,"",@progbits
