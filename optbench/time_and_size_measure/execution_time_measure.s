	.file	"execution_time_measure.c"
	.text
	.p2align 4
	.globl	function_to_measure
	.def	function_to_measure;	.scl	2;	.type	32;	.endef
	.seh_proc	function_to_measure
function_to_measure:
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$184, %rsp
	.seh_stackalloc	184
	movups	%xmm6, 32(%rsp)
	.seh_savexmm	%xmm6, 32
	movups	%xmm7, 48(%rsp)
	.seh_savexmm	%xmm7, 48
	movups	%xmm8, 64(%rsp)
	.seh_savexmm	%xmm8, 64
	movups	%xmm9, 80(%rsp)
	.seh_savexmm	%xmm9, 80
	movups	%xmm10, 96(%rsp)
	.seh_savexmm	%xmm10, 96
	movups	%xmm11, 112(%rsp)
	.seh_savexmm	%xmm11, 112
	movups	%xmm12, 128(%rsp)
	.seh_savexmm	%xmm12, 128
	movups	%xmm13, 144(%rsp)
	.seh_savexmm	%xmm13, 144
	movups	%xmm14, 160(%rsp)
	.seh_savexmm	%xmm14, 160
	.seh_endprologue
	movl	$3, %r13d
	movl	$1, %esi
	pxor	%xmm7, %xmm7
	movsd	.LC0(%rip), %xmm0
	movl	$3, %edi
	movsd	.LC7(%rip), %xmm8
	movabsq	$2635249153387078803, %r12
	movsd	.LC2(%rip), %xmm12
	movsd	.LC3(%rip), %xmm11
	movabsq	$5675921253449092805, %rbp
	movsd	.LC4(%rip), %xmm10
	movsd	.LC5(%rip), %xmm9
	.p2align 4
	.p2align 3
.L12:
	movl	%edi, %eax
	cmpq	%rsi, %rax
	je	.L22
	movq	%rsi, %rax
	movl	$1, %ebx
	mulq	%r12
	movq	%rsi, %rax
	subq	%rdx, %rax
	shrq	%rax
	leaq	(%rdx,%rax), %rcx
	movq	%rsi, %rax
	mulq	%rbp
	shrq	$2, %rcx
	shrq	$2, %rdx
	cmpq	%rcx, %rdx
	jnb	.L4
	movq	%rcx, %rax
	subq	%rdx, %rax
	testb	$1, %al
	je	.L5
	movq	%rcx, %rbx
	subq	$1, %rcx
	cmpq	%rdx, %rcx
	je	.L4
	.p2align 5
	.p2align 4
	.p2align 3
.L5:
	imulq	%rcx, %rbx
	leaq	-1(%rcx), %rax
	subq	$2, %rcx
	imulq	%rax, %rbx
	cmpq	%rdx, %rcx
	jne	.L5
.L4:
	testq	%rsi, %rsi
	js	.L6
	pxor	%xmm13, %xmm13
	cvtsi2sdq	%rsi, %xmm13
.L7:
	movapd	%xmm13, %xmm1
	movapd	%xmm12, %xmm0
	call	pow
	movapd	%xmm0, %xmm6
	testq	%r13, %r13
	js	.L8
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%r13, %xmm1
.L9:
	movapd	%xmm11, %xmm0
	call	pow
	mulsd	%xmm10, %xmm13
	movapd	%xmm0, %xmm14
	mulsd	%xmm14, %xmm6
	movapd	%xmm13, %xmm0
	divsd	%xmm9, %xmm0
	call	cos
	mulsd	%xmm6, %xmm0
	testq	%rbx, %rbx
	js	.L10
	pxor	%xmm1, %xmm1
	cvtsi2sdq	%rbx, %xmm1
.L11:
	divsd	%xmm1, %xmm0
	addsd	%xmm0, %xmm7
.L3:
	movapd	%xmm0, %xmm1
	andpd	.LC6(%rip), %xmm1
	addq	$1, %rsi
	addq	$2, %r13
	comisd	%xmm8, %xmm1
	jnb	.L12
	pxor	%xmm0, %xmm0
	movups	32(%rsp), %xmm6
	movups	64(%rsp), %xmm8
	cvtsd2ss	%xmm7, %xmm0
	movups	80(%rsp), %xmm9
	movups	48(%rsp), %xmm7
	movups	96(%rsp), %xmm10
	movups	112(%rsp), %xmm11
	movups	128(%rsp), %xmm12
	movups	144(%rsp), %xmm13
	movups	160(%rsp), %xmm14
	addq	$184, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	ret
	.p2align 4,,10
	.p2align 3
.L22:
	addl	$6, %edi
	jmp	.L3
	.p2align 4,,10
	.p2align 3
.L6:
	movq	%rsi, %rax
	movq	%rsi, %rdx
	pxor	%xmm13, %xmm13
	shrq	%rax
	andl	$1, %edx
	orq	%rdx, %rax
	cvtsi2sdq	%rax, %xmm13
	addsd	%xmm13, %xmm13
	jmp	.L7
	.p2align 4,,10
	.p2align 3
.L10:
	movq	%rbx, %rax
	andl	$1, %ebx
	pxor	%xmm1, %xmm1
	shrq	%rax
	orq	%rbx, %rax
	cvtsi2sdq	%rax, %xmm1
	addsd	%xmm1, %xmm1
	jmp	.L11
	.p2align 4,,10
	.p2align 3
.L8:
	movq	%r13, %rax
	movq	%r13, %rdx
	pxor	%xmm1, %xmm1
	shrq	%rax
	andl	$1, %edx
	orq	%rdx, %rax
	cvtsi2sdq	%rax, %xmm1
	addsd	%xmm1, %xmm1
	jmp	.L9
	.seh_endproc
	.section .rdata,"dr"
.LC8:
	.ascii "%f\12\0"
.LC11:
	.ascii "execution time = %f ns\12\0"
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$72, %rsp
	.seh_stackalloc	72
	.seh_endprologue
	movl	$10000000, %ebx
	call	__main
	leaq	40(%rsp), %rcx
	call	*__imp_QueryPerformanceFrequency(%rip)
	movq	__imp_QueryPerformanceCounter(%rip), %rsi
	leaq	48(%rsp), %rcx
	call	*%rsi
	.p2align 4
	.p2align 3
.L24:
	call	function_to_measure
	subl	$1, %ebx
	jne	.L24
	pxor	%xmm1, %xmm1
	leaq	.LC8(%rip), %rcx
	cvtss2sd	%xmm0, %xmm1
	movq	%xmm1, %rdx
	call	printf
	leaq	56(%rsp), %rcx
	call	*%rsi
	movq	56(%rsp), %rax
	pxor	%xmm1, %xmm1
	subq	48(%rsp), %rax
	cvtsi2sdq	%rax, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	40(%rsp), %xmm0
	leaq	.LC11(%rip), %rcx
	mulsd	.LC9(%rip), %xmm1
	divsd	%xmm0, %xmm1
	divsd	.LC10(%rip), %xmm1
	movq	%xmm1, %rdx
	call	printf
	xorl	%eax, %eax
	addq	$72, %rsp
	popq	%rbx
	popq	%rsi
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC0:
	.long	0
	.long	1072693248
	.align 8
.LC2:
	.long	0
	.long	-1074790400
	.align 8
.LC3:
	.long	1889785610
	.long	1072630333
	.align 8
.LC4:
	.long	1413754136
	.long	1074340347
	.align 8
.LC5:
	.long	0
	.long	1075314688
	.align 16
.LC6:
	.long	-1
	.long	2147483647
	.long	0
	.long	0
	.align 8
.LC7:
	.long	0
	.long	1018167296
	.align 8
.LC9:
	.long	0
	.long	1104006501
	.align 8
.LC10:
	.long	0
	.long	1097011920
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev5, Built by MSYS2 project) 16.1.0"
	.def	pow;	.scl	2;	.type	32;	.endef
	.def	cos;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
