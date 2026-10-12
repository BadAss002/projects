	.file	"1.c"
	.intel_syntax noprefix
	.text
	.globl	"i"
	.bss
	.align 4
"i":
	.space 4
	.globl	"j"
	.align 4
"j":
	.space 4
	.globl	"k"
	.align 4
"k":
	.space 4
	.globl	"l"
	.align 4
"l":
	.space 4
	.globl	"m"
	.align 4
"m":
	.space 4
	.globl	"i2"
	.align 4
"i2":
	.space 4
	.globl	"j2"
	.align 4
"j2":
	.space 4
	.globl	"k2"
	.align 4
"k2":
	.space 4
	.globl	"g3"
	.align 4
"g3":
	.space 4
	.globl	"h3"
	.align 4
"h3":
	.space 4
	.globl	"i3"
	.align 4
"i3":
	.space 4
	.globl	"k3"
	.align 4
"k3":
	.space 4
	.globl	"m3"
	.align 4
"m3":
	.space 4
	.globl	"i4"
	.align 4
"i4":
	.space 4
	.globl	"j4"
	.align 4
"j4":
	.space 4
	.globl	"i5"
	.align 4
"i5":
	.space 4
	.globl	"j5"
	.align 4
"j5":
	.space 4
	.globl	"k5"
	.align 4
"k5":
	.space 4
	.globl	"flt_1"
	.align 8
"flt_1":
	.space 8
	.globl	"flt_2"
	.align 8
"flt_2":
	.space 8
	.globl	"flt_3"
	.align 8
"flt_3":
	.space 8
	.globl	"flt_4"
	.align 8
"flt_4":
	.space 8
	.globl	"flt_5"
	.align 8
"flt_5":
	.space 8
	.globl	"flt_6"
	.align 8
"flt_6":
	.space 8
	.globl	"ivector"
	.align 8
"ivector":
	.space 12
	.globl	"ivector2"
"ivector2":
	.space 3
	.globl	"ivector4"
	.align 8
"ivector4":
	.space 12
	.globl	"ivector5"
	.align 32
"ivector5":
	.space 400
	.text
	.globl	"dead_code"
	.def	"dead_code";	.scl	2;	.type	32;	.endef
	.seh_proc	"dead_code"
"dead_code":
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	sub	rsp, 16
	.seh_stackalloc	16
	.seh_endprologue
	mov	DWORD PTR 16[rbp], ecx
	mov	QWORD PTR 24[rbp], rdx
	mov	eax, DWORD PTR 16[rbp]
	mov	DWORD PTR -4[rbp], eax
	nop
	add	rsp, 16
	pop	rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC0:
	.ascii "This line should not be printed\0"
	.text
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
	mov	DWORD PTR 16[rbp], ecx
	mov	QWORD PTR 24[rbp], rdx
	call	"__main"
	lea	rax, .LC0[rip]
	mov	rdx, rax
	mov	ecx, 1
	call	"dead_code"
	mov	eax, 0
	add	rsp, 32
	pop	rbp
	ret
	.seh_endproc
	.def	"__main";	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev5, Built by MSYS2 project) 16.1.0"
