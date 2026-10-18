	.file	"1.c"
	.intel_syntax noprefix
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "okak\0"
	.text
	.p2align 4
	.globl	"func"
	.def	"func";	.scl	2;	.type	32;	.endef
	.seh_proc	"func"
"func":
	push	r12
	.seh_pushreg	r12
	push	rbp
	.seh_pushreg	rbp
	push	rdi
	.seh_pushreg	rdi
	push	rsi
	.seh_pushreg	rsi
	push	rbx
	.seh_pushreg	rbx
	sub	rsp, 32
	.seh_stackalloc	32
	.seh_endprologue
	lea	rsi, "A"[rip]
	xor	ebx, ebx
	lea	r12, "B"[rip]
	lea	rbp, "D"[rip]
	lea	rdi, 2[rsi]
	.p2align 4
	.p2align 3
.L2:
	movzx	eax, WORD PTR "c"[rip]
	movzx	edx, WORD PTR [rsi+rbx]
	lea	rcx, .LC0[rip]
	imul	edx, eax
	add	dx, WORD PTR "q"[rip]
	imul	ax, WORD PTR [rdi+rbx]
	mov	WORD PTR [r12+rbx], dx
	mov	WORD PTR 0[rbp+rbx], ax
	add	rbx, 2
	call	"puts"
	cmp	rbx, 20
	jne	.L2
	add	rsp, 32
	pop	rbx
	pop	rsi
	pop	rdi
	pop	rbp
	pop	r12
	ret
	.seh_endproc
	.section	.text.startup,"x"
	.p2align 4
	.globl	"main"
	.def	"main";	.scl	2;	.type	32;	.endef
	.seh_proc	"main"
"main":
	sub	rsp, 40
	.seh_stackalloc	40
	.seh_endprologue
	call	"__main"
	call	"func"
	xor	eax, eax
	add	rsp, 40
	ret
	.seh_endproc
	.globl	"t"
	.bss
	.align 2
"t":
	.space 2
	.globl	"q"
	.align 2
"q":
	.space 2
	.globl	"c"
	.align 2
"c":
	.space 2
	.globl	"D"
	.align 32
"D":
	.space 40
	.globl	"B"
	.align 16
"B":
	.space 30
	.globl	"A"
	.align 32
"A":
	.space 60
	.def	"__main";	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev5, Built by MSYS2 project) 16.1.0"
	.def	"puts";	.scl	2;	.type	32;	.endef
