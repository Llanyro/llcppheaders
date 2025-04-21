	.file	"test2.cpp"
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
	lea	r12, 120[rsp]
	mov	rdx, QWORD PTR .LC0[rip]
	mov	rsi, rbx
	lea	rax, 88[rsp]
	mov	QWORD PTR [rbx], rdx
.L2:
	mov	QWORD PTR [rax], rdx
	add	rax, 16
	mov	QWORD PTR -8[rax], rdx
	cmp	rax, r12
	jne	.L2
	mov	rdi, rbx
	lea	rbp, .LC1[rip]
	.p2align 4
	.p2align 3
.L3:
	mov	edx, DWORD PTR [rdi]
	mov	rcx, rbp
	add	rdi, 4
	call	__mingw_printf
	cmp	rdi, r12
	jne	.L3
	mov	ecx, 10
	lea	r13, 48[rsp]
	lea	rdi, 68[rsp]
	call	putchar
	mov	rax, rbx
	mov	rdx, r13
	.p2align 5
	.p2align 4
	.p2align 3
.L4:
	mov	ecx, 88
	add	rdx, 2
	add	DWORD PTR [rax], 1
	add	rax, 4
	mov	WORD PTR -2[rdx], cx
	cmp	rdx, rdi
	jne	.L4
	movabs	rax, 7016996765293437281
	mov	QWORD PTR 38[rsp], rax
	mov	eax, 24929
	mov	WORD PTR 46[rsp], ax
	.p2align 4
	.p2align 3
.L5:
	mov	edx, DWORD PTR [rsi]
	mov	rcx, rbp
	add	rsi, 4
	call	__mingw_printf
	cmp	rsi, r12
	jne	.L5
	mov	ecx, 10
	lea	rbx, 38[rsp]
	lea	rsi, .LC2[rip]
	call	putchar
	.p2align 4
	.p2align 3
.L6:
	movsx	edx, BYTE PTR [rbx]
	mov	rcx, rsi
	add	rbx, 1
	mov	r8d, edx
	call	__mingw_printf
	cmp	rbx, r13
	jne	.L6
	mov	ecx, 10
	call	putchar
	.p2align 4
	.p2align 3
.L7:
	movsx	edx, WORD PTR [rbx]
	mov	rcx, rbp
	add	rbx, 2
	call	__mingw_printf
	cmp	rdi, rbx
	jne	.L7
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
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev2, Built by MSYS2 project) 14.2.0"
	.def	putchar;	.scl	2;	.type	32;	.endef
