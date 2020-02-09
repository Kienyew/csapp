	.file	"cmp.c"
	.text
	.globl	cmp_le
	.type	cmp_le, @function
cmp_le:
.LFB0:
	.cfi_startproc
	cmpl	%esi, %edi
	setle	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	cmp_le, .-cmp_le
	.globl	cmp_l
	.type	cmp_l, @function
cmp_l:
.LFB1:
	.cfi_startproc
	cmpl	%esi, %edi
	setl	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	cmp_l, .-cmp_l
	.globl	cmp_g
	.type	cmp_g, @function
cmp_g:
.LFB2:
	.cfi_startproc
	cmpl	%esi, %edi
	setg	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE2:
	.size	cmp_g, .-cmp_g
	.globl	cmp_ge
	.type	cmp_ge, @function
cmp_ge:
.LFB3:
	.cfi_startproc
	cmpl	%esi, %edi
	setge	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE3:
	.size	cmp_ge, .-cmp_ge
	.globl	cmp_ui_l
	.type	cmp_ui_l, @function
cmp_ui_l:
.LFB4:
	.cfi_startproc
	cmpl	%edi, %esi
	seta	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE4:
	.size	cmp_ui_l, .-cmp_ui_l
	.globl	cmp_u_l
	.type	cmp_u_l, @function
cmp_u_l:
.LFB5:
	.cfi_startproc
	cmpl	%esi, %edi
	setb	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE5:
	.size	cmp_u_l, .-cmp_u_l
	.globl	cmp_uc_l
	.type	cmp_uc_l, @function
cmp_uc_l:
.LFB6:
	.cfi_startproc
	movzbl	%dil, %edi
	movsbl	%sil, %esi
	cmpl	%esi, %edi
	setl	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE6:
	.size	cmp_uc_l, .-cmp_uc_l
	.ident	"GCC: (GNU) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
