	.file	"cmov.c"
	.text
	.globl	absdiff
	.type	absdiff, @function
absdiff:
.LFB0:
	.cfi_startproc
	movl	%esi, %edx
	subl	%edi, %edx
	movl	%edi, %eax
	subl	%esi, %eax
	cmpl	%esi, %edi
	cmovl	%edx, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	absdiff, .-absdiff
	.ident	"GCC: (GNU) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
