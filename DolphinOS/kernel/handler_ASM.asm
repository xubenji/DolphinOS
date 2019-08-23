global _asm_general_handler
global _asm_inthandler21_keyboard
global _asm_inthandler20_timer
global _asm_read_cr3
global _asm_hlt
global _asm_read_gdt
global _asm_intr_exit

extern inthandler21_keyboard
extern inthandler20_timer
extern general_handler

INT_M_CTL EQU 0X20
EOI EQU 0X20

[section .text]
[bits 32]
;.code32 'worry label

_asm_inthandler21_keyboard:	; IRQ 1		keyboard
	PUSH	ES			
	PUSH	DS
	PUSHAD					
	MOV		EAX,ESP
	PUSH	EAX
	MOV		AX,SS			
	MOV		DS,AX
	MOV		ES,AX
	CALL	inthandler21_keyboard	
	POP		EAX				
	POPAD
	POP		DS
	POP		ES
	IRETD					
	
_asm_inthandler20_timer:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler20_timer
	pop eax
	popad
	pop ds
	pop es
	iretd

_asm_general_handler:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call general_handler
	pop eax
	popad
	pop ds
	pop es
	iretd

_asm_read_cr3:
	mov eax, cr3
	ret

_asm_hlt:
	hlt
	ret

_asm_read_gdt:
	sgdt [0x500000]
	mov eax, [0x500000+2]
	ret

_asm_intr_exit:
   	add esp, 4			   ; 跳过中断号
  	popad
  	pop gs
 	pop fs
   	pop es
  	pop ds
  	add esp, 4			   ; 跳过error_code
        iretd
	

