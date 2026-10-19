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
	push	rbx
	.seh_pushreg	rbx
	sub	rsp, 32
	.seh_stackalloc	32
	.seh_endprologue
	mov	eax, DWORD PTR "x"[rip]
	mov	edx, DWORD PTR "y"[rip]
	mov	ebx, 100
	jmp	.L4
	.p2align 4
	.p2align 4,,10
	.p2align 3
.L2:
	sub	ebx, eax
	test	ebx, ebx
	jle	.L7
.L4:
	cmp	eax, edx
	jne	.L2
	lea	rcx, .LC0[rip]
	sub	ebx, 1
	call	"puts"
	mov	eax, DWORD PTR "x"[rip]
	mov	edx, DWORD PTR "y"[rip]
	test	ebx, ebx
	jg	.L4
.L7:
	add	eax, edx
	add	eax, ebx
	add	rsp, 32
	pop	rbx
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC1:
	.ascii "%d\12\0"
	.section	.text.startup,"x"
	.p2align 4
	.globl	"main"
	.def	"main";	.scl	2;	.type	32;	.endef
	.seh_proc	"main"
"main":
	push	rbx
	.seh_pushreg	rbx
	sub	rsp, 32
	.seh_stackalloc	32
	.seh_endprologue
	mov	ebx, 100
	call	"__main"
	mov	edx, DWORD PTR "x"[rip]
	mov	eax, DWORD PTR "y"[rip]
	jmp	.L11
	.p2align 4
	.p2align 4,,10
	.p2align 3
.L9:
	sub	ebx, edx
	test	ebx, ebx
	jle	.L13
.L11:
	cmp	edx, eax
	jne	.L9
	lea	rcx, .LC0[rip]
	sub	ebx, 1
	call	"puts"
	mov	edx, DWORD PTR "x"[rip]
	mov	eax, DWORD PTR "y"[rip]
	test	ebx, ebx
	jg	.L11
.L13:
	add	edx, eax
	lea	rcx, .LC1[rip]
	add	edx, ebx
	call	"printf"
	xor	eax, eax
	add	rsp, 32
	pop	rbx
	ret
	.seh_endproc
	.globl	"y"
	.data
	.align 4
"y":
	.long	15
	.globl	"x"
	.align 4
"x":
	.long	10
	.def	"__main";	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev5, Built by MSYS2 project) 16.1.0"
	.def	"puts";	.scl	2;	.type	32;	.endef
	.def	"printf";	.scl	2;	.type	32;	.endef
