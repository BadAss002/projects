	.file	"execution_time_measure.c"
	.text
	.section .rdata,"dr"
.LC8:
	.ascii "%f\12\0"
.LC11:
	.ascii "execution time = %f ns\12\0"
	.section	.text.startup,"x"
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%r14
	.seh_pushreg	%r14
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
	subq	$96, %rsp
	.seh_stackalloc	96
	movups	%xmm6, 64(%rsp)
	.seh_savexmm	%xmm6, 64
	movups	%xmm7, 80(%rsp)
	.seh_savexmm	%xmm7, 80
	.seh_endprologue
	movl	$10000000, %edi
	call	__main
	leaq	40(%rsp), %rcx
	call	*__imp_QueryPerformanceFrequency(%rip)
	movq	__imp_QueryPerformanceCounter(%rip), %rbp
	leaq	48(%rsp), %rcx
	call	*%rbp
.L2:
	movsd	.LC0(%rip), %xmm0
	movl	$1, %r13d
	xorps	%xmm7, %xmm7
	movl	$1, %ebx
	movl	$3, %esi
.L13:
	movl	%esi, %eax
	cmpq	%rbx, %rax
	jne	.L3
	addl	$6, %esi
	jmp	.L4
.L3:
	movl	$7, %ecx
	movq	%rbx, %rax
	xorl	%edx, %edx
	movl	$13, %r8d
	divq	%rcx
	xorl	%edx, %edx
	movq	%rax, %rcx
	movq	%rbx, %rax
	divq	%r8
.L5:
	cmpq	%rcx, %rax
	jnb	.L17
	imulq	%rcx, %r13
	decq	%rcx
	jmp	.L5
.L17:
	testq	%rbx, %rbx
	js	.L7
	cvtsi2sdq	%rbx, %xmm6
	jmp	.L8
.L7:
	movq	%rbx, %rax
	movq	%rbx, %rdx
	shrq	%rax
	andl	$1, %edx
	orq	%rdx, %rax
	cvtsi2sdq	%rax, %xmm6
	addsd	%xmm6, %xmm6
.L8:
	movsd	.LC2(%rip), %xmm0
	movaps	%xmm6, %xmm1
	call	pow
	leaq	(%rbx,%rbx), %rax
	movq	%xmm0, %r12
	incq	%rax
	js	.L9
	cvtsi2sdq	%rax, %xmm1
	jmp	.L10
.L9:
	movq	%rax, %rdx
	andl	$1, %eax
	shrq	%rdx
	orq	%rax, %rdx
	cvtsi2sdq	%rdx, %xmm1
	addsd	%xmm1, %xmm1
.L10:
	movsd	.LC3(%rip), %xmm0
	call	pow
	mulsd	.LC4(%rip), %xmm6
	movq	%xmm0, %r14
	movaps	%xmm6, %xmm0
	divsd	.LC5(%rip), %xmm0
	call	cos
	movq	%r14, %xmm2
	movaps	%xmm0, %xmm1
	movq	%r12, %xmm0
	mulsd	%xmm2, %xmm0
	mulsd	%xmm1, %xmm0
	testq	%r13, %r13
	js	.L11
	cvtsi2sdq	%r13, %xmm1
	jmp	.L12
.L11:
	movq	%r13, %rax
	movq	%r13, %rdx
	shrq	%rax
	andl	$1, %edx
	orq	%rdx, %rax
	cvtsi2sdq	%rax, %xmm1
	addsd	%xmm1, %xmm1
.L12:
	divsd	%xmm1, %xmm0
	addsd	%xmm0, %xmm7
.L4:
	incq	%rbx
	movaps	%xmm0, %xmm1
	andps	.LC6(%rip), %xmm1
	comisd	.LC7(%rip), %xmm1
	jnb	.L13
	decl	%edi
	jne	.L2
	leaq	.LC8(%rip), %rcx
	cvtsd2ss	%xmm7, %xmm7
	cvtss2sd	%xmm7, %xmm3
	movq	%xmm3, %rdx
	movaps	%xmm3, %xmm1
	call	printf
	leaq	56(%rsp), %rcx
	call	*%rbp
	movq	56(%rsp), %rax
	subq	48(%rsp), %rax
	leaq	.LC11(%rip), %rcx
	cvtsi2sdq	%rax, %xmm1
	mulsd	.LC9(%rip), %xmm1
	cvtsi2sdq	40(%rsp), %xmm0
	divsd	%xmm0, %xmm1
	divsd	.LC10(%rip), %xmm1
	movq	%xmm1, %rdx
	call	printf
	nop
	movups	64(%rsp), %xmm6
	movups	80(%rsp), %xmm7
	xorl	%eax, %eax
	addq	$96, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
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
