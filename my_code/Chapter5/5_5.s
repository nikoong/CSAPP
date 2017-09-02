	.file	"5_5.c"
	.text
	.p2align 4,,15
	.globl	ploy
	.type	ploy, @function
ploy:
.LFB0:
	.cfi_startproc


	
	testq	%rsi, %rsi
	movsd	(%rdi), %xmm2
	jle	.L2
	leaq	8(%rdi), %rax
	leaq	8(%rdi,%rsi,8), %rdx
	movapd	%xmm0, %xmm1
	.p2align 4,,10
	.p2align 3
.L3:
	movsd	(%rax), %xmm3
	addq	$8, %rax
	cmpq	%rdx, %rax
	mulsd	%xmm1, %xmm3
	mulsd	%xmm0, %xmm1
	addsd	%xmm3, %xmm2
	jne	.L3
.L2:
	movapd	%xmm2, %xmm0
	ret
	.cfi_endproc
.LFE0:
	.size	ploy, .-ploy
	.ident	"GCC: (Ubuntu 4.8.4-1ubuntu15) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
