	.text
	.global sysCall, exitToKernel

sysCall:
	mov 4(%esp), %eax
	mov 8(%esp), %ecx
	mov 12(%esp), %edx
	int $128
	ret

exitToKernel:
	int $142