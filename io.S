	.text
	.global inb, outb

inb:
	mov 4(%esp), %edx
	mov $0, %eax
	in %dx, %al
	ret

outb:
	mov 4(%esp), %edx
	mov 8(%esp), %eax
	out %al, %dx
	ret