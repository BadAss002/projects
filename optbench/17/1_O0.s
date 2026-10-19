	.file	"1.c"
	.intel_syntax noprefix
	.text
	.globl	"x"
	.data
	.align 4
"x":
	.long	10
	.globl	"y"
	.align 4
"y":
	.long	15
	.section .rdata,"dr"
.LC0:
	.ascii "okak\0"
	.text
	.globl	"func"
	.def	"func";	.scl	2;	.type	32;	.endef
	.seh_proc	"func"
"func":
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 48
	.seh_stackalloc	48
	.seh_endprologue
	mov	DWORD PTR -4[rbp], 100
	jmp	.L2
.L4:
	mov	edx, DWORD PTR "x"[rip]
	mov	eax, DWORD PTR "y"[rip]
	cmp	edx, eax
	jne	.L3
	sub	DWORD PTR -4[rbp], 1
	lea	rax, .LC0[rip]
	mov	rcx, rax
	call	"puts"
	jmp	.L2
.L3:
	mov	eax, DWORD PTR "x"[rip]
	sub	DWORD PTR -4[rbp], eax
.L2:
	cmp	DWORD PTR -4[rbp], 0
	jg	.L4
	mov	edx, DWORD PTR "x"[rip]
	mov	eax, DWORD PTR "y"[rip]
	add	edx, eax
	mov	eax, DWORD PTR -4[rbp]
	add	eax, edx
	add	rsp, 48
	pop	rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC1:
	.ascii "%d\12\0"
	.text
	.globl	"main"
	.def	"main";	.scl	2;	.type	32;	.endef
	.seh_proc	"main"
"main":
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 48
	.seh_stackalloc	48
	.seh_endprologue
	call	"__main"
	call	"func"
	mov	DWORD PTR -4[rbp], eax
	mov	eax, DWORD PTR -4[rbp]
	lea	rcx, .LC1[rip]
	mov	edx, eax
	call	"printf"
	mov	eax, 0
	add	rsp, 48
	pop	rbp
	ret
	.seh_endproc
	.def	"__main";	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev5, Built by MSYS2 project) 16.1.0"
	.def	"puts";	.scl	2;	.type	32;	.endef
	.def	"printf";	.scl	2;	.type	32;	.endef
