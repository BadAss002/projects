	.file	"1.c"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	"func"
	.def	"func";	.scl	2;	.type	32;	.endef
	.seh_proc	"func"
"func":
	.seh_endprologue
	mov	r8d, 100
	.p2align 5
	.p2align 4
	.p2align 3
.L4:
	lea	eax, -1[r8]
	sub	r8d, ecx
	cmp	ecx, edx
	cmove	r8d, eax
	test	r8d, r8d
	jg	.L4
	add	ecx, edx
	mov	DWORD PTR "k"[rip], r8d
	lea	eax, [rcx+r8]
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "%d\12\0"
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
	mov	edx, 25
	lea	rcx, .LC0[rip]
	mov	DWORD PTR "k"[rip], 0
	call	"printf"
	xor	eax, eax
	add	rsp, 40
	ret
	.seh_endproc
	.globl	"k"
	.bss
	.align 4
"k":
	.space 4
	.globl	"y"
	.align 4
"y":
	.space 4
	.globl	"x"
	.align 4
"x":
	.space 4
	.def	"__main";	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev5, Built by MSYS2 project) 16.1.0"
	.def	"printf";	.scl	2;	.type	32;	.endef
