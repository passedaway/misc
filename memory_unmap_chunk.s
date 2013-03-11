	.file	"memory_unmap_chunk.c"
	.text
.Ltext0:
	.section	.rodata
.LC0:
	.string	"error"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.file 1 "memory_unmap_chunk.c"
	.loc 1 23 0
	.cfi_startproc
	pushl	%ebp
.LCFI0:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
.LCFI1:
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%ebx
	andl	$-16, %esp
	subl	$32, %esp
	.loc 1 24 0
	movl	$0, 28(%esp)
	.loc 1 26 0
	movl	$64, (%esp)
	.cfi_offset 3, -16
	.cfi_offset 7, -12
	call	malloc
	movl	%eax, 28(%esp)
	.loc 1 27 0
	cmpl	$0, 28(%esp)
	jne	.L2
	.loc 1 29 0
	movl	$.LC0, (%esp)
	call	puts
	.loc 1 30 0
	movl	$-1, %eax
	jmp	.L3
.L2:
	.loc 1 33 0
	movl	28(%esp), %eax
	movl	%eax, %edx
	movl	$64, %ebx
	movl	$0, %eax
	movl	%edx, %ecx
	andl	$1, %ecx
	testl	%ecx, %ecx
	je	.L4
	movb	%al, (%edx)
	addl	$1, %edx
	subl	$1, %ebx
.L4:
	movl	%edx, %ecx
	andl	$2, %ecx
	testl	%ecx, %ecx
	je	.L5
	movw	%ax, (%edx)
	addl	$2, %edx
	subl	$2, %ebx
.L5:
	movl	%ebx, %ecx
	shrl	$2, %ecx
	movl	%edx, %edi
	rep stosl
	movl	%edi, %edx
	movl	%ebx, %ecx
	andl	$2, %ecx
	testl	%ecx, %ecx
	je	.L6
	movw	%ax, (%edx)
	addl	$2, %edx
.L6:
	movl	%ebx, %ecx
	andl	$1, %ecx
	testl	%ecx, %ecx
	je	.L7
	movb	%al, (%edx)
	addl	$1, %edx
.L7:
	.loc 1 35 0
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	je	.L8
	.loc 1 36 0
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	free
.L8:
	.loc 1 38 0
	movl	28(%esp), %eax
	addl	$4, %eax
	movl	%eax, (%esp)
	call	free
	.loc 1 40 0
	movl	$0, %eax
.L3:
	.loc 1 41 0
	leal	-8(%ebp), %esp
	popl	%ebx
	.cfi_restore 3
	popl	%edi
	.cfi_restore 7
	popl	%ebp
.LCFI2:
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0xc3
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF12
	.byte	0x1
	.long	.LASF13
	.long	.LASF14
	.long	.Ltext0
	.long	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF7
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF8
	.uleb128 0x4
	.byte	0x4
	.long	0x71
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF9
	.uleb128 0x5
	.byte	0x1
	.long	.LASF15
	.byte	0x1
	.byte	0x16
	.byte	0x1
	.long	0x4f
	.long	.LFB0
	.long	.LFE0
	.long	.LLST0
	.long	0xc0
	.uleb128 0x6
	.long	.LASF10
	.byte	0x1
	.byte	0x16
	.long	0x4f
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x6
	.long	.LASF11
	.byte	0x1
	.byte	0x16
	.long	0xc0
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x7
	.string	"buf"
	.byte	0x1
	.byte	0x18
	.long	0x6b
	.byte	0x2
	.byte	0x74
	.sleb128 28
	.byte	0
	.uleb128 0x4
	.byte	0x4
	.long	0x6b
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LFB0-.Ltext0
	.long	.LCFI0-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI0-.Ltext0
	.long	.LCFI1-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI1-.Ltext0
	.long	.LCFI2-.Ltext0
	.value	0x2
	.byte	0x75
	.sleb128 8
	.long	.LCFI2-.Ltext0
	.long	.LFE0-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.value	0
	.value	0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF6:
	.string	"long long int"
.LASF0:
	.string	"unsigned int"
.LASF15:
	.string	"main"
.LASF14:
	.string	"/opt/src/misc"
.LASF3:
	.string	"long unsigned int"
.LASF7:
	.string	"long long unsigned int"
.LASF1:
	.string	"unsigned char"
.LASF9:
	.string	"char"
.LASF8:
	.string	"long int"
.LASF13:
	.string	"memory_unmap_chunk.c"
.LASF12:
	.string	"GNU C 4.6.3"
.LASF10:
	.string	"argc"
.LASF2:
	.string	"short unsigned int"
.LASF4:
	.string	"signed char"
.LASF11:
	.string	"argv"
.LASF5:
	.string	"short int"
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
