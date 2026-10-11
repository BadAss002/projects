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
	mov	edx, DWORD PTR "i2"[rip]
	cmp	edx, 1
	jle	.L6
.L2:
	mov	eax, DWORD PTR "k5"[rip]
	mov	DWORD PTR "j4"[rip], eax
	cmp	edx, eax
	jge	.L4
	cmp	eax, DWORD PTR "i4"[rip]
	jg	.L3
.L4:
	xor	eax, eax
	add	rsp, 40
	ret
.L6:
	cmp	DWORD PTR "i4"[rip], 1
	jg	.L2
	mov	DWORD PTR "i2"[rip], 2
	mov	eax, DWORD PTR "k5"[rip]
	mov	DWORD PTR "j4"[rip], eax
	cmp	eax, 2
	jle	.L4
.L3:
	mov	DWORD PTR "i5"[rip], 3
	jmp	.L4
	.seh_endproc
	.globl	"k5"
	.bss
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
