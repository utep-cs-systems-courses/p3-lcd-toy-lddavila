	.arch msp430
	.p2align 1,0
	
button:		 .word 0x00
	
jt:
	.word case_0
	.word case_1
	
	.global change
	
change:
	mov #1, r12
	cmp &button, r12
	jc end_case
	
	mov &button, r12
	add r12, r12
	mov jt(r12), r0

case_0:
	mov #-10, r12
	jmp end_case
case_1:
	mov #10, r12
	jmp end_case
end_case:
	pop r0
