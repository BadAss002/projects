	.file	"1.c"
	.intel_syntax noprefix
	.text
	.globl	"x"
	.bss
	.align 4
"x":
	.space 4
	.globl	"y"
	.align 4
"y":
	.space 4
	.globl	"k"
	.align 4
"k":
	.space 4
	.text
	.globl	"func"
	.def	"func";	.scl	2;	.type	32;	.endef
	.seh_proc	"func"
"func":
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	.seh_endprologue
	mov	DWORD PTR "k"[rip], 100
	mov	DWORD PTR "x"[rip], 10
	mov	DWORD PTR "y"[rip], 15
	jmp	.L2
.L4:
	mov	edx, DWORD PTR "x"[rip]
	mov	eax, DWORD PTR "y"[rip]
	cmp	edx, eax
	jne	.L3
	mov	eax, DWORD PTR "k"[rip]
	sub	eax, 1
	mov	DWORD PTR "k"[rip], eax
	jmp	.L2
.L3:
	mov	edx, DWORD PTR "k"[rip]
	mov	eax, DWORD PTR "x"[rip]
	sub	edx, eax
	mov	DWORD PTR "k"[rip], edx
.L2:
	mov	eax, DWORD PTR "k"[rip]
	test	eax, eax
	jg	.L4
	nop
	nop
	pop	rbp
	ret
	.seh_endproc
	.globl	"main"
	.def	"main";	.scl	2;	.type	32;	.endef
	.seh_proc	"main"
"main":
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 32
	.seh_stackalloc	32
	.seh_endprologue
	call	"__main"
	call	"func"
	mov	eax, 0
	add	rsp, 32
	pop	rbp
	ret
	.seh_endproc
	.def	"__main";	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev5, Built by MSYS2 project) 16.1.0"
