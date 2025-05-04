	.file	"test_hash.cpp"
	.intel_syntax noprefix
	.text
	.section .rdata,"dr"
.LC0:
	.ascii "int main()\0"
.LC1:
	.ascii "\12%llu\12\0"
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	push	rsi
	.seh_pushreg	rsi
	push	rbx
	.seh_pushreg	rbx
	sub	rsp, 56
	.seh_stackalloc	56
	.seh_endprologue
	lea	rbx, .LC1[rip]
	movabs	rsi, -2438256281324008058
	call	__main
	mov	ecx, 1
	call	[QWORD PTR __imp___acrt_iob_func[rip]]
	mov	r8d, 1
	mov	edx, 11
	lea	rcx, .LC0[rip]
	mov	r9, rax
	call	fwrite
	mov	rdx, rsi
	mov	rcx, rbx
	call	__mingw_printf
	mov	rdx, rsi
	mov	rcx, rbx
	call	__mingw_printf
	mov	rcx, rbx
	movabs	rdx, -7070675565921358487
	call	__mingw_printf
	mov	rcx, rbx
	movabs	rdx, -1497396947089030911
	call	__mingw_printf
	mov	rcx, rbx
	movabs	rdx, -1497396944457176568
	call	__mingw_printf
	mov	rcx, rbx
	mov	QWORD PTR 40[rsp], 0
	movabs	rax, -7070675565921424023
	mov	DWORD PTR 40[rsp], 1717859169
	mov	rdx, QWORD PTR 40[rsp]
	sal	rdx, 47
	xor	rdx, rax
	call	__mingw_printf
	xor	eax, eax
	add	rsp, 56
	pop	rbx
	pop	rsi
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev2, Built by MSYS2 project) 14.2.0"
	.def	fwrite;	.scl	2;	.type	32;	.endef
