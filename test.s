	.file	"test.cpp"
	.intel_syntax noprefix
	.text
	.section .rdata,"dr"
.LC1:
	.ascii "%i, \0"
.LC2:
	.ascii "(%i)'%c', \0"
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	push	rbp
	.seh_pushreg	rbp
	push	rdi
	.seh_pushreg	rdi
	push	rsi
	.seh_pushreg	rsi
	push	rbx
	.seh_pushreg	rbx
	sub	rsp, 136
	.seh_stackalloc	136
	.seh_endprologue
	call	__main
	lea	rbx, 80[rsp]
	lea	rdi, 120[rsp]
	mov	rdx, QWORD PTR .LC0[rip]
	lea	rax, 88[rsp]
	mov	QWORD PTR [rbx], rdx
.L2:
	mov	QWORD PTR [rax], rdx
	add	rax, 16
	mov	QWORD PTR -8[rax], rdx
	cmp	rdi, rax
	jne	.L2
	mov	rsi, rbx
	lea	rbp, .LC1[rip]
	.p2align 4
	.p2align 3
.L3:
	mov	edx, DWORD PTR [rsi]
	mov	rcx, rbp
	add	rsi, 4
	call	__mingw_printf
	cmp	rsi, rdi
	jne	.L3
	mov	ecx, 10
	lea	rsi, 48[rsp]
	call	putchar
	mov	rdx, rsi
	mov	rax, rbx
	.p2align 5
	.p2align 4
	.p2align 3
.L4:
	add	DWORD PTR [rax], 1
	mov	ecx, 88
	add	rax, 4
	add	rdx, 2
	mov	WORD PTR -2[rdx], cx
	cmp	rax, rdi
	jne	.L4
	movabs	rax, 7016996765293437281
	mov	QWORD PTR 38[rsp], rax
	mov	eax, 24929
	mov	WORD PTR 46[rsp], ax
	.p2align 4
	.p2align 3
.L5:
	mov	edx, DWORD PTR [rbx]
	mov	rcx, rbp
	add	rbx, 4
	call	__mingw_printf
	cmp	rbx, rdi
	jne	.L5
	mov	ecx, 10
	lea	rbx, 38[rsp]
	lea	rdi, .LC2[rip]
	call	putchar
	.p2align 4
	.p2align 3
.L6:
	movsx	edx, BYTE PTR [rbx]
	mov	rcx, rdi
	add	rbx, 1
	mov	r8d, edx
	call	__mingw_printf
	cmp	rbx, rsi
	jne	.L6
	mov	ecx, 10
	lea	rsi, 68[rsp]
	call	putchar
	.p2align 4
	.p2align 3
.L7:
	movsx	edx, WORD PTR [rbx]
	mov	rcx, rbp
	add	rbx, 2
	call	__mingw_printf
	cmp	rbx, rsi
	jne	.L7
	mov	ecx, 10
	call	putchar
	xor	eax, eax
	add	rsp, 136
	pop	rbx
	pop	rsi
	pop	rdi
	pop	rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC0:
	.long	99
	.long	99
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev2, Built by MSYS2 project) 14.2.0"
	.def	putchar;	.scl	2;	.type	32;	.endef
