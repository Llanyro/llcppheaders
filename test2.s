	.file	"test2.cpp"
	.intel_syntax noprefix
	.text
	.section .rdata,"dr"
.LC1:
	.ascii "%i, \0"
.LC4:
	.ascii "(%i)'%c', \0"
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	push	r13
	.seh_pushreg	r13
	push	r12
	.seh_pushreg	r12
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
	lea	rbp, 120[rsp]
	mov	rdx, QWORD PTR .LC0[rip]
	lea	rax, 88[rsp]
	mov	QWORD PTR [rbx], rdx
.L2:
	mov	QWORD PTR [rax], rdx
	add	rax, 16
	mov	QWORD PTR -8[rax], rdx
	cmp	rax, rbp
	jne	.L2
	mov	rsi, rbx
	lea	rdi, .LC1[rip]
	.p2align 4
	.p2align 3
.L3:
	mov	edx, DWORD PTR [rsi]
	mov	rcx, rdi
	add	rsi, 4
	call	__mingw_printf
	cmp	rsi, rbp
	jne	.L3
	mov	ecx, 10
	call	putchar
	mov	rax, rbx
	movq	xmm1, QWORD PTR .LC2[rip]
.L4:
	movq	xmm0, QWORD PTR [rax]
	add	rax, 8
	paddd	xmm0, xmm1
	movq	QWORD PTR -8[rax], xmm0
	cmp	rax, rbp
	jne	.L4
	mov	edx, DWORD PTR .LC3[rip]
	lea	r13, 48[rsp]
	lea	r12, 68[rsp]
	movabs	rax, 7016996765293437281
	mov	QWORD PTR 38[rsp], rax
	mov	eax, 24929
	mov	rsi, r13
	mov	DWORD PTR 0[r13], edx
	mov	WORD PTR 46[rsp], ax
	lea	rax, 52[rsp]
.L5:
	mov	DWORD PTR [rax], edx
	add	rax, 8
	mov	DWORD PTR -4[rax], edx
	cmp	rax, r12
	jne	.L5
	.p2align 4
	.p2align 3
.L6:
	mov	edx, DWORD PTR [rbx]
	mov	rcx, rdi
	add	rbx, 4
	call	__mingw_printf
	cmp	rbx, rbp
	jne	.L6
	mov	ecx, 10
	lea	rbx, 38[rsp]
	lea	rbp, .LC4[rip]
	call	putchar
	.p2align 4
	.p2align 3
.L7:
	movsx	edx, BYTE PTR [rbx]
	mov	rcx, rbp
	add	rbx, 1
	mov	r8d, edx
	call	__mingw_printf
	cmp	rbx, r13
	jne	.L7
	mov	ecx, 10
	call	putchar
	.p2align 4
	.p2align 3
.L8:
	movsx	edx, WORD PTR [rsi]
	mov	rcx, rdi
	add	rsi, 2
	call	__mingw_printf
	cmp	rsi, r12
	jne	.L8
	mov	ecx, 10
	call	putchar
	xor	eax, eax
	add	rsp, 136
	pop	rbx
	pop	rsi
	pop	rdi
	pop	rbp
	pop	r12
	pop	r13
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC0:
	.long	99
	.long	99
	.align 8
.LC2:
	.long	1
	.long	1
	.align 4
.LC3:
	.word	88
	.word	88
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev2, Built by MSYS2 project) 14.2.0"
	.def	putchar;	.scl	2;	.type	32;	.endef
