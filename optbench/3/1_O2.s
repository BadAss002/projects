	.file	"1.c"
	.intel_syntax noprefix
	.text
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
	xor	eax, eax
	mov	DWORD PTR "k3"[rip], 1
	add	rsp, 40
	ret
	.seh_endproc
	.globl	"flt_6"
	.bss
	.align 8
"flt_6":
	.space 8
	.globl	"flt_5"
	.align 8
"flt_5":
	.space 8
	.globl	"flt_4"
	.align 8
"flt_4":
	.space 8
	.globl	"flt_3"
	.align 8
"flt_3":
	.space 8
	.globl	"flt_2"
	.align 8
"flt_2":
	.space 8
	.globl	"flt_1"
	.align 8
"flt_1":
	.space 8
	.globl	"k5"
	.align 4
"k5":
	.space 4
	.globl	"j5"
	.align 4
"j5":
	.space 4
	.globl	"i5"
	.align 4
"i5":
	.space 4
	.globl	"j4"
	.align 4
"j4":
	.space 4
	.globl	"i4"
	.align 4
"i4":
	.space 4
	.globl	"m3"
	.align 4
"m3":
	.space 4
	.globl	"k3"
	.align 4
"k3":
	.space 4
	.globl	"i3"
	.align 4
"i3":
	.space 4
	.globl	"h3"
	.align 4
"h3":
	.space 4
	.globl	"g3"
	.align 4
"g3":
	.space 4
	.globl	"k2"
	.align 4
"k2":
	.space 4
	.globl	"j2"
	.align 4
"j2":
	.space 4
	.globl	"i2"
	.align 4
"i2":
	.space 4
	.globl	"m"
	.align 4
"m":
	.space 4
	.globl	"l"
	.align 4
"l":
	.space 4
	.globl	"k"
	.align 4
"k":
	.space 4
	.globl	"j"
	.align 4
"j":
	.space 4
	.globl	"i"
	.align 4
"i":
	.space 4
	.def	"__main";	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev5, Built by MSYS2 project) 16.1.0"
