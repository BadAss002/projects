	.file	"1.c"
	.text
	.globl	i
	.bss
	.align 4
i:
	.space 4
	.globl	j
	.align 4
j:
	.space 4
	.globl	k
	.align 4
k:
	.space 4
	.globl	l
	.align 4
l:
	.space 4
	.globl	m
	.align 4
m:
	.space 4
	.globl	i2
	.align 4
i2:
	.space 4
	.globl	j2
	.align 4
j2:
	.space 4
	.globl	k2
	.align 4
k2:
	.space 4
	.globl	g3
	.align 4
g3:
	.space 4
	.globl	h3
	.align 4
h3:
	.space 4
	.globl	i3
	.align 4
i3:
	.space 4
	.globl	k3
	.align 4
k3:
	.space 4
	.globl	m3
	.align 4
m3:
	.space 4
	.globl	i4
	.align 4
i4:
	.space 4
	.globl	j4
	.align 4
j4:
	.space 4
	.globl	i5
	.align 4
i5:
	.space 4
	.globl	j5
	.align 4
j5:
	.space 4
	.globl	k5
	.align 4
k5:
	.space 4
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
	movl	$2, j4(%rip)
	movl	i2(%rip), %edx
	movl	j4(%rip), %eax
	cmpl	%eax, %edx
	jge	.L2
	movl	i4(%rip), %edx
	movl	j4(%rip), %eax
	cmpl	%eax, %edx
	jge	.L2
	movl	$2, i2(%rip)
.L2:
	movl	k5(%rip), %eax
	movl	%eax, j4(%rip)
	movl	i2(%rip), %edx
	movl	j4(%rip), %eax
	cmpl	%eax, %edx
	jge	.L3
	movl	i4(%rip), %edx
	movl	j4(%rip), %eax
	cmpl	%eax, %edx
	jge	.L3
	movl	$3, i5(%rip)
.L3:
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev5, Built by MSYS2 project) 16.1.0"
