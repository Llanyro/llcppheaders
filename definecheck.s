	.file	"definecheck.cpp"
	.text
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB5301:
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	call	__main
	movl	$1, %ecx
	call	*__imp___acrt_iob_func(%rip)
	movl	$12, %r8d
	movl	$1, %edx
	leaq	arr(%rip), %rcx
	movq	%rax, %r9
	call	fwrite
	xorl	%eax, %eax
	addq	$40, %rsp
	ret
	.seh_endproc
	.globl	arr
	.section	.rdata$arr,"dr"
	.linkonce same_size
	.align 8
arr:
	.ascii "Hola mundo!\0"
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev2, Built by MSYS2 project) 14.2.0"
	.def	fwrite;	.scl	2;	.type	32;	.endef
