	.file	"1.c"
	.intel_syntax noprefix
	.text
	.globl	"A"
	.bss
	.align 32
"A":
	.space 60
	.globl	"B"
	.align 16
"B":
	.space 30
	.globl	"D"
	.align 32
"D":
	.space 40
	.globl	"c"
	.align 2
"c":
	.space 2
	.globl	"q"
	.align 2
"q":
	.space 2
	.globl	"t"
	.align 2
"t":
	.space 2
	.text
	.globl	"func"
	.def	"func";	.scl	2;	.type	32;	.endef
	.seh_proc	"func"
"func":
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 16
	.seh_stackalloc	16
	.seh_endprologue
	mov	DWORD PTR -4[rbp], 0
	jmp	.L2
.L3:
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	lea	rdx, [rax+rax]
	lea	rax, "A"[rip]
	movzx	eax, WORD PTR [rdx+rax]
	mov	edx, eax
	movzx	eax, WORD PTR "c"[rip]
	imul	eax, edx
	movzx	edx, WORD PTR "q"[rip]
	add	eax, edx
	mov	ecx, eax
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	lea	rdx, [rax+rax]
	lea	rax, "B"[rip]
	mov	WORD PTR [rdx+rax], cx
	mov	eax, DWORD PTR -4[rbp]
	add	eax, 1
	cdqe
	lea	rdx, [rax+rax]
	lea	rax, "A"[rip]
	movzx	eax, WORD PTR [rdx+rax]
	mov	edx, eax
	movzx	eax, WORD PTR "c"[rip]
	imul	eax, edx
	mov	ecx, eax
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	lea	rdx, [rax+rax]
	lea	rax, "D"[rip]
	mov	WORD PTR [rdx+rax], cx
	add	DWORD PTR -4[rbp], 1
.L2:
	cmp	DWORD PTR -4[rbp], 9
	jle	.L3
	nop
	add	rsp, 16
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
