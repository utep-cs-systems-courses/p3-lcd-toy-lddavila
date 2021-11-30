	.arch msp430
	.p2align 1,0

button:	 .word 0x00
	
jt:	 .word #case_0
	 .word #case_1
	.global change
change:
	mov #1, r12
	cmp &state, r12
	jc end_case
	move &button, r12
case_0:
	mov #-10, r12
	jmp end_case
case_1:
	mov #10, r12
	jmp end_case
end_case:
	pop r0
