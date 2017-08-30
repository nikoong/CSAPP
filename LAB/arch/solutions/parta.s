	.file	"parta.c"
	.text
	.globl	sum_list
	.type	sum_list, @function
sum_list:
.LFB0:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L4
	movl	$0, %eax
.L3:
	addq	(%rdi), %rax
	movq	8(%rdi), %rdi
	testq	%rdi, %rdi
	jne	.L3
	rep ret
.L4:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	sum_list, .-sum_list
	.globl	rsum_list
	.type	rsum_list, @function
rsum_list:
.LFB1:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movl	$0, %eax
	testq	%rdi, %rdi
	je	.L6
	movq	8(%rdi), %rdi
	call	rsum_list
	addq	(%rbx), %rax
.L6:
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1:
	.size	rsum_list, .-rsum_list
	.globl	copy_block
	.type	copy_block, @function
copy_block:
.LFB2:
	.cfi_startproc
	testq	%rdx, %rdx
	jle	.L12
	movl	$0, %ecx
	movl	$0, %eax
.L11:
	movq	(%rdi,%rcx,8), %r8
	movq	%r8, (%rsi,%rcx,8)
	xorq	%r8, %rax
	addq	$1, %rcx
	cmpq	%rdx, %rcx
	jne	.L11
	rep ret
.L12:
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE2:
	.size	copy_block, .-copy_block
	.ident	"GCC: (Ubuntu 4.8.4-1ubuntu15) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
