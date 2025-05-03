	.file	"test_lljeaiii.cpp"
	.text
	.section	.text$_ZN5llcpp4meta6jeaiii16integral_to_textIicLb0EEEPT0_NS0_6traits11ConditionalIXaa10is_class_vIT_Ent12is_pointer_vIS7_EERKS7_S8_E4typeES4_,"x"
	.linkonce discard
	.p2align 4
	.globl	_ZN5llcpp4meta6jeaiii16integral_to_textIicLb0EEEPT0_NS0_6traits11ConditionalIXaa10is_class_vIT_Ent12is_pointer_vIS7_EERKS7_S8_E4typeES4_
	.def	_ZN5llcpp4meta6jeaiii16integral_to_textIicLb0EEEPT0_NS0_6traits11ConditionalIXaa10is_class_vIT_Ent12is_pointer_vIS7_EERKS7_S8_E4typeES4_;	.scl	2;	.type	32;	.endef
	.seh_proc	_ZN5llcpp4meta6jeaiii16integral_to_textIicLb0EEEPT0_NS0_6traits11ConditionalIXaa10is_class_vIT_Ent12is_pointer_vIS7_EERKS7_S8_E4typeES4_
_ZN5llcpp4meta6jeaiii16integral_to_textIicLb0EEEPT0_NS0_6traits11ConditionalIXaa10is_class_vIT_Ent12is_pointer_vIS7_EERKS7_S8_E4typeES4_:
.LFB5829:
	pushq	%rbx
	.seh_pushreg	%rbx
	.seh_endprologue
	movq	%rdx, %r8
	movl	%ecx, %eax
	testl	%ecx, %ecx
	jns	.L2
	movb	$45, (%rdx)
	negl	%eax
	addq	$1, %r8
.L2:
	cmpl	$99, %eax
	jbe	.L11
	movq	%r8, %rdx
	cmpl	$999999, %eax
	ja	.L1
	leaq	1(%r8), %r9
	cmpl	$9999, %eax
	ja	.L6
	imull	$167773, %eax, %ecx
	movl	%ecx, %edx
	andl	$16777215, %ecx
	leaq	(%rcx,%rcx,4), %rcx
	shrl	$24, %edx
	leaq	(%rcx,%rcx,4), %r10
	addq	$96, %rdx
	leaq	_ZN5llcpp4meta6jeaiii3MAPIcEE(%rip), %rcx
	movzbl	8(%rcx,%rdx,2), %r11d
	shrq	$22, %r10
	movb	%r11b, (%r8)
	cmpl	$1000, %eax
	jbe	.L7
	movzbl	9(%rcx,%rdx,2), %eax
	leaq	2(%r8), %r9
	movb	%al, 1(%r8)
.L7:
	movzwl	(%rcx,%r10,2), %eax
	leaq	2(%r9), %rdx
	movw	%ax, (%r9)
.L1:
	movq	%rdx, %rax
	popq	%rbx
	ret
	.p2align 4,,10
	.p2align 3
.L11:
	movl	%eax, %ecx
	leaq	_ZN5llcpp4meta6jeaiii3MAPIcEE(%rip), %r9
	addq	$96, %rcx
	movzbl	8(%r9,%rcx,2), %edx
	movb	%dl, (%r8)
	leaq	1(%r8), %rdx
	cmpl	$10, %eax
	jbe	.L1
	movzbl	9(%r9,%rcx,2), %eax
	leaq	2(%r8), %rdx
	movb	%al, 1(%r8)
	movq	%rdx, %rax
	popq	%rbx
	ret
	.p2align 4,,10
	.p2align 3
.L6:
	movl	%eax, %edx
	imulq	$429497, %rdx, %rdx
	movl	%edx, %ecx
	shrq	$32, %rdx
	leaq	(%rcx,%rcx,4), %rcx
	addq	$96, %rdx
	leaq	(%rcx,%rcx,4), %rcx
	movq	%rcx, %r11
	leal	0(,%rcx,4), %ecx
	leaq	(%rcx,%rcx,4), %rcx
	shrq	$30, %r11
	leaq	(%rcx,%rcx,4), %r10
	leaq	_ZN5llcpp4meta6jeaiii3MAPIcEE(%rip), %rcx
	movzbl	8(%rcx,%rdx,2), %ebx
	shrq	$30, %r10
	movb	%bl, (%r8)
	cmpl	$100000, %eax
	jbe	.L8
	movzbl	9(%rcx,%rdx,2), %eax
	leaq	2(%r8), %r9
	movb	%al, 1(%r8)
.L8:
	movzbl	1(%rcx,%r10,2), %eax
	movzbl	(%rcx,%r10,2), %r8d
	leaq	4(%r9), %rdx
	sall	$8, %eax
	orl	%r8d, %eax
	movzbl	1(%rcx,%r11,2), %r8d
	movzbl	(%rcx,%r11,2), %ecx
	sall	$8, %eax
	orl	%r8d, %eax
	sall	$8, %eax
	orl	%ecx, %eax
	movl	%eax, (%r9)
	movq	%rdx, %rax
	popq	%rbx
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "[%u] '%.*s'\0"
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB5332:
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$120, %rsp
	.seh_stackalloc	120
	.seh_endprologue
	call	__main
	leaq	48(%rsp), %rsi
	movl	$64, %ecx
	movq	%rsi, %rdx
	call	_ZN5llcpp4meta6jeaiii16integral_to_textIicLb0EEEPT0_NS0_6traits11ConditionalIXaa10is_class_vIT_Ent12is_pointer_vIS7_EERKS7_S8_E4typeES4_
	movl	$1, %ecx
	subq	%rsi, %rax
	movq	%rax, %rbx
	call	*__imp___acrt_iob_func(%rip)
	movq	%rsi, 32(%rsp)
	movq	%rbx, %r9
	movq	%rbx, %r8
	movq	%rax, %rcx
	leaq	.LC0(%rip), %rdx
	call	__mingw_fprintf
	xorl	%eax, %eax
	addq	$120, %rsp
	popq	%rbx
	popq	%rsi
	ret
	.seh_endproc
	.globl	_ZN5llcpp4meta6jeaiii3MAPIcEE
	.section	.rdata$_ZN5llcpp4meta6jeaiii3MAPIcEE,"dr"
	.linkonce same_size
	.align 32
_ZN5llcpp4meta6jeaiii3MAPIcEE:
	.byte	48
	.byte	48
	.byte	48
	.byte	49
	.byte	48
	.byte	50
	.byte	48
	.byte	51
	.byte	48
	.byte	52
	.byte	48
	.byte	53
	.byte	48
	.byte	54
	.byte	48
	.byte	55
	.byte	48
	.byte	56
	.byte	48
	.byte	57
	.byte	49
	.byte	48
	.byte	49
	.byte	49
	.byte	49
	.byte	50
	.byte	49
	.byte	51
	.byte	49
	.byte	52
	.byte	49
	.byte	53
	.byte	49
	.byte	54
	.byte	49
	.byte	55
	.byte	49
	.byte	56
	.byte	49
	.byte	57
	.byte	50
	.byte	48
	.byte	50
	.byte	49
	.byte	50
	.byte	50
	.byte	50
	.byte	51
	.byte	50
	.byte	52
	.byte	50
	.byte	53
	.byte	50
	.byte	54
	.byte	50
	.byte	55
	.byte	50
	.byte	56
	.byte	50
	.byte	57
	.byte	51
	.byte	48
	.byte	51
	.byte	49
	.byte	51
	.byte	50
	.byte	51
	.byte	51
	.byte	51
	.byte	52
	.byte	51
	.byte	53
	.byte	51
	.byte	54
	.byte	51
	.byte	55
	.byte	51
	.byte	56
	.byte	51
	.byte	57
	.byte	52
	.byte	48
	.byte	52
	.byte	49
	.byte	52
	.byte	50
	.byte	52
	.byte	51
	.byte	52
	.byte	52
	.byte	52
	.byte	53
	.byte	52
	.byte	54
	.byte	52
	.byte	55
	.byte	52
	.byte	56
	.byte	52
	.byte	57
	.byte	53
	.byte	48
	.byte	53
	.byte	49
	.byte	53
	.byte	50
	.byte	53
	.byte	51
	.byte	53
	.byte	52
	.byte	53
	.byte	53
	.byte	53
	.byte	54
	.byte	53
	.byte	55
	.byte	53
	.byte	56
	.byte	53
	.byte	57
	.byte	54
	.byte	48
	.byte	54
	.byte	49
	.byte	54
	.byte	50
	.byte	54
	.byte	51
	.byte	54
	.byte	52
	.byte	54
	.byte	53
	.byte	54
	.byte	54
	.byte	54
	.byte	55
	.byte	54
	.byte	56
	.byte	54
	.byte	57
	.byte	55
	.byte	48
	.byte	55
	.byte	49
	.byte	55
	.byte	50
	.byte	55
	.byte	51
	.byte	55
	.byte	52
	.byte	55
	.byte	53
	.byte	55
	.byte	54
	.byte	55
	.byte	55
	.byte	55
	.byte	56
	.byte	55
	.byte	57
	.byte	56
	.byte	48
	.byte	56
	.byte	49
	.byte	56
	.byte	50
	.byte	56
	.byte	51
	.byte	56
	.byte	52
	.byte	56
	.byte	53
	.byte	56
	.byte	54
	.byte	56
	.byte	55
	.byte	56
	.byte	56
	.byte	56
	.byte	57
	.byte	57
	.byte	48
	.byte	57
	.byte	49
	.byte	57
	.byte	50
	.byte	57
	.byte	51
	.byte	57
	.byte	52
	.byte	57
	.byte	53
	.byte	57
	.byte	54
	.byte	57
	.byte	55
	.byte	57
	.byte	56
	.byte	57
	.byte	57
	.byte	52
	.byte	56
	.byte	52
	.byte	57
	.byte	53
	.byte	48
	.byte	53
	.byte	49
	.byte	53
	.byte	50
	.byte	53
	.byte	51
	.byte	53
	.byte	52
	.byte	53
	.byte	53
	.byte	53
	.byte	54
	.byte	53
	.byte	55
	.byte	49
	.byte	48
	.byte	49
	.byte	49
	.byte	49
	.byte	50
	.byte	49
	.byte	51
	.byte	49
	.byte	52
	.byte	49
	.byte	53
	.byte	49
	.byte	54
	.byte	49
	.byte	55
	.byte	49
	.byte	56
	.byte	49
	.byte	57
	.byte	50
	.byte	48
	.byte	50
	.byte	49
	.byte	50
	.byte	50
	.byte	50
	.byte	51
	.byte	50
	.byte	52
	.byte	50
	.byte	53
	.byte	50
	.byte	54
	.byte	50
	.byte	55
	.byte	50
	.byte	56
	.byte	50
	.byte	57
	.byte	51
	.byte	48
	.byte	51
	.byte	49
	.byte	51
	.byte	50
	.byte	51
	.byte	51
	.byte	51
	.byte	52
	.byte	51
	.byte	53
	.byte	51
	.byte	54
	.byte	51
	.byte	55
	.byte	51
	.byte	56
	.byte	51
	.byte	57
	.byte	52
	.byte	48
	.byte	52
	.byte	49
	.byte	52
	.byte	50
	.byte	52
	.byte	51
	.byte	52
	.byte	52
	.byte	52
	.byte	53
	.byte	52
	.byte	54
	.byte	52
	.byte	55
	.byte	52
	.byte	56
	.byte	52
	.byte	57
	.byte	53
	.byte	48
	.byte	53
	.byte	49
	.byte	53
	.byte	50
	.byte	53
	.byte	51
	.byte	53
	.byte	52
	.byte	53
	.byte	53
	.byte	53
	.byte	54
	.byte	53
	.byte	55
	.byte	53
	.byte	56
	.byte	53
	.byte	57
	.byte	54
	.byte	48
	.byte	54
	.byte	49
	.byte	54
	.byte	50
	.byte	54
	.byte	51
	.byte	54
	.byte	52
	.byte	54
	.byte	53
	.byte	54
	.byte	54
	.byte	54
	.byte	55
	.byte	54
	.byte	56
	.byte	54
	.byte	57
	.byte	55
	.byte	48
	.byte	55
	.byte	49
	.byte	55
	.byte	50
	.byte	55
	.byte	51
	.byte	55
	.byte	52
	.byte	55
	.byte	53
	.byte	55
	.byte	54
	.byte	55
	.byte	55
	.byte	55
	.byte	56
	.byte	55
	.byte	57
	.byte	56
	.byte	48
	.byte	56
	.byte	49
	.byte	56
	.byte	50
	.byte	56
	.byte	51
	.byte	56
	.byte	52
	.byte	56
	.byte	53
	.byte	56
	.byte	54
	.byte	56
	.byte	55
	.byte	56
	.byte	56
	.byte	56
	.byte	57
	.byte	57
	.byte	48
	.byte	57
	.byte	49
	.byte	57
	.byte	50
	.byte	57
	.byte	51
	.byte	57
	.byte	52
	.byte	57
	.byte	53
	.byte	57
	.byte	54
	.byte	57
	.byte	55
	.byte	57
	.byte	56
	.byte	57
	.byte	57
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev2, Built by MSYS2 project) 14.2.0"
