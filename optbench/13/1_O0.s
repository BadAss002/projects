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
	.globl	"loop_jamming"
	.def	"loop_jamming";	.scl	2;	.type	32;	.endef
	.seh_proc	"loop_jamming"
"loop_jamming":
	push	rbp
	.seh_pushreg	rbp
	mov	rbp, rsp
	.seh_setframe	rbp, 0
	.seh_endprologue
	mov	DWORD PTR 16[rbp], ecx
	mov	DWORD PTR "i"[rip], 0
	jmp	.L2
.L3:
	mov	edx, DWORD PTR "j5"[rip]
	mov	eax, DWORD PTR "i"[rip]
	imul	edx, eax
	mov	eax, DWORD PTR 16[rbp]
	add	eax, edx
	mov	DWORD PTR "k5"[rip], eax
	mov	eax, DWORD PTR "i"[rip]
	add	eax, 1
	mov	DWORD PTR "i"[rip], eax
.L2:
	mov	eax, DWORD PTR "i"[rip]
	cmp	eax, 4
	jle	.L3
	mov	DWORD PTR "i"[rip], 0
	jmp	.L4
.L5:
	mov	eax, DWORD PTR "k5"[rip]
	imul	eax, DWORD PTR 16[rbp]
	mov	edx, eax
	mov	eax, DWORD PTR "i"[rip]
	imul	eax, edx
	mov	DWORD PTR "i5"[rip], eax
	mov	eax, DWORD PTR "i"[rip]
	add	eax, 1
	mov	DWORD PTR "i"[rip], eax
.L4:
	mov	eax, DWORD PTR "i"[rip]
	cmp	eax, 4
	jle	.L5
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
	mov	DWORD PTR 16[rbp], ecx
	mov	QWORD PTR 24[rbp], rdx
	call	"__main"
	call	"loop_jamming"
	mov	eax, 0
	add	rsp, 32
	pop	rbp
	ret
	.seh_endproc
	.def	"__main";	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev5, Built by MSYS2 project) 16.1.0"
