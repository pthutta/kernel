	.extern gdtr
	
	.text
	.global setGdt, setTss, setIdt, sysCall, interruptHandler, sysCallHandler, runModule, goBackToKernelSpaceHandler
	
setGdt:
	lgdt gdtr
    mov $0x10, %ax 	# 0x10 is the offset in the GDT to our data segment
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss 
	jmp $0x08, $flush	# 0x08 is the offset to our code segment: Far jump!
flush:
	ret

setTss:
	mov $0x2b, %ax 	# Load the index of our TSS structure, 6th entry of gdt
	ltr %ax		# Load 0x18 into the task state register
	ret

setIdt:
	mov 4(%esp), %eax
	lidtl (%eax)
	ret

interruptHandler:
	push %gs
    push %fs
    push %es
    push %ds
    push %ebp
    push %edi
    push %esi
    push %edx
    push %ecx
    push %ebx
    push %esp

	push %edx
	push %ecx
	push %eax

	call sysCallHandler

	add $12, %esp
	pop %esp
	pop %ebx
	pop %ecx
	pop %edx
	pop %esi
	pop %edi
	pop %ebp
	pop %ds
	pop %es
	pop %fs
	pop %gs
	iret

goBackToKernelSpaceHandler:
	add $20, %esp

	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs

    pop %edi
    pop %esi
	pop %ebx
	pop %ebp

	ret

runModule:
	mov $0x23, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    mov 12(%esp), %eax
    mov %esp, %edx

    push %ebp
    push %ebx
    push %esi
    push %edi

    mov %esp, (%eax)

    pushl $0x23
    push 8(%edx)
    pushf
    pushl $0x1B    
	push 4(%edx)
	iret