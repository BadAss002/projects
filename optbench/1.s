	.file	"1.c"
	.text
	.globl	dead_code
	.type	dead_code, @function
dead_code:
.LFB1:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE1:
	.size	dead_code, .-dead_code
	.globl	unnecessary_loop
	.type	unnecessary_loop, @function
unnecessary_loop:
.LFB2:
	.cfi_startproc
	movl	$5, i(%rip)
	movl	j5(%rip), %eax
	movl	%eax, k5(%rip)
	ret
	.cfi_endproc
.LFE2:
	.size	unnecessary_loop, .-unnecessary_loop
	.globl	loop_jamming
	.type	loop_jamming, @function
loop_jamming:
.LFB3:
	.cfi_startproc
	movl	$5, i(%rip)
	movl	j5(%rip), %eax
	leal	(%rdi,%rax,4), %eax
	movl	%eax, k5(%rip)
	imull	%edi, %eax
	sall	$2, %eax
	movl	%eax, i5(%rip)
	ret
	.cfi_endproc
.LFE3:
	.size	loop_jamming, .-loop_jamming
	.globl	loop_unrolling
	.type	loop_unrolling, @function
loop_unrolling:
.LFB4:
	.cfi_startproc
	movl	$6, i(%rip)
	andq	$0, ivector4(%rip)
	andl	$0, 8+ivector4(%rip)
	ret
	.cfi_endproc
.LFE4:
	.size	loop_unrolling, .-loop_unrolling
	.globl	jump_compression
	.type	jump_compression, @function
jump_compression:
.LFB5:
	.cfi_startproc
.L6:
	cmpl	%edi, %esi
	jle	.L7
	cmpl	%edx, %esi
	jge	.L8
	cmpl	%ecx, %edx
	jge	.L9
	cmpl	%r8d, %ecx
	jge	.L6
	addl	%r8d, %ecx
	jmp	.L11
.L9:
	addl	%ecx, %edx
	jmp	.L11
.L8:
	addl	%edx, %esi
	jmp	.L6
.L7:
	addl	%esi, %edi
.L11:
	leal	(%rdi,%rsi), %eax
	addl	%edx, %eax
	addl	%ecx, %eax
	addl	%r8d, %eax
	ret
	.cfi_endproc
.LFE5:
	.size	jump_compression, .-jump_compression
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"a"
.LC1:
	.string	"stats.txt"
.LC2:
	.string	"%ld\n"
	.section	.text.startup,"ax",@progbits
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$56, %rsp
	.cfi_def_cfa_offset 80
	movq	%fs:40, %rsi
	movq	%rsi, 40(%rsp)
	leaq	8(%rsp), %rsi
	pushq	$1
	popq	%rdi
	call	clock_gettime@PLT
	pushq	$5
	popq	%r8
	pushq	$4
	popq	%rcx
	pushq	$3
	popq	%rdx
	pushq	$2
	popq	%rsi
	pushq	$1
	popq	%rdi
	call	jump_compression
	leaq	24(%rsp), %rsi
	pushq	$1
	popq	%rdi
	call	clock_gettime@PLT
	leaq	.LC0(%rip), %rsi
	movq	32(%rsp), %rbx
	leaq	.LC1(%rip), %rdi
	subq	16(%rsp), %rbx
	call	fopen@PLT
	movq	%rbx, %rdx
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rbp
	xchgq	%rax, %rdi
	xorl	%eax, %eax
	call	fprintf@PLT
	movq	%rbp, %rdi
	call	fclose@PLT
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	je	.L14
	call	__stack_chk_fail@PLT
.L14:
	addq	$56, %rsp
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	ivector5
	.bss
	.align 32
	.type	ivector5, @object
	.size	ivector5, 400
ivector5:
	.zero	400
	.globl	ivector4
	.align 8
	.type	ivector4, @object
	.size	ivector4, 12
ivector4:
	.zero	12
	.globl	ivector2
	.type	ivector2, @object
	.size	ivector2, 3
ivector2:
	.zero	3
	.globl	ivector
	.align 8
	.type	ivector, @object
	.size	ivector, 12
ivector:
	.zero	12
	.globl	flt_6
	.align 8
	.type	flt_6, @object
	.size	flt_6, 8
flt_6:
	.zero	8
	.globl	flt_5
	.align 8
	.type	flt_5, @object
	.size	flt_5, 8
flt_5:
	.zero	8
	.globl	flt_4
	.align 8
	.type	flt_4, @object
	.size	flt_4, 8
flt_4:
	.zero	8
	.globl	flt_3
	.align 8
	.type	flt_3, @object
	.size	flt_3, 8
flt_3:
	.zero	8
	.globl	flt_2
	.align 8
	.type	flt_2, @object
	.size	flt_2, 8
flt_2:
	.zero	8
	.globl	flt_1
	.align 8
	.type	flt_1, @object
	.size	flt_1, 8
flt_1:
	.zero	8
	.globl	k5
	.align 4
	.type	k5, @object
	.size	k5, 4
k5:
	.zero	4
	.globl	j5
	.align 4
	.type	j5, @object
	.size	j5, 4
j5:
	.zero	4
	.globl	i5
	.align 4
	.type	i5, @object
	.size	i5, 4
i5:
	.zero	4
	.globl	j4
	.align 4
	.type	j4, @object
	.size	j4, 4
j4:
	.zero	4
	.globl	i4
	.align 4
	.type	i4, @object
	.size	i4, 4
i4:
	.zero	4
	.globl	m3
	.align 4
	.type	m3, @object
	.size	m3, 4
m3:
	.zero	4
	.globl	k3
	.align 4
	.type	k3, @object
	.size	k3, 4
k3:
	.zero	4
	.globl	i3
	.align 4
	.type	i3, @object
	.size	i3, 4
i3:
	.zero	4
	.globl	h3
	.align 4
	.type	h3, @object
	.size	h3, 4
h3:
	.zero	4
	.globl	g3
	.align 4
	.type	g3, @object
	.size	g3, 4
g3:
	.zero	4
	.globl	k2
	.align 4
	.type	k2, @object
	.size	k2, 4
k2:
	.zero	4
	.globl	j2
	.align 4
	.type	j2, @object
	.size	j2, 4
j2:
	.zero	4
	.globl	i2
	.align 4
	.type	i2, @object
	.size	i2, 4
i2:
	.zero	4
	.globl	m
	.align 4
	.type	m, @object
	.size	m, 4
m:
	.zero	4
	.globl	l
	.align 4
	.type	l, @object
	.size	l, 4
l:
	.zero	4
	.globl	k
	.align 4
	.type	k, @object
	.size	k, 4
k:
	.zero	4
	.globl	j
	.align 4
	.type	j, @object
	.size	j, 4
j:
	.zero	4
	.globl	i
	.align 4
	.type	i, @object
	.size	i, 4
i:
	.zero	4
	.ident	"GCC: (GNU) 15.2.0"
	.section	.note.GNU-stack,"",@progbits
