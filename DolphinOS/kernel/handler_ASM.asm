global _asm_general_handler
global _asm_inthandler00_divide_error
global _asm_inthandler01_debug
global _asm_inthandler02_NMI_interrupt
global _asm_inthandler03_breakpoint
global _asm_inthandler04_overflow
global _asm_inthandler05_bound_range_exceeded
global _asm_inthandler06_invalid_opcode
global _asm_inthandler07_device_not_available
global _asm_inthandler08_double_fault
global _asm_inthandler09_coprocess_segment_overrun
global _asm_inthandler10_invalid_TSS
global _asm_inthandler11_segment_not_present
global _asm_inthandler12_stack_segment_fault
global _asm_inthandler13_general_protection
global _asm_inthandler14_page_fault

global _asm_inthandler16_floating_point_error
global _asm_inthandler17_alignment_check
global _asm_inthandler18_machine_check
global _asm_inthandler19_SIMD_floating_point_exception
global _asm_inthandler20_timer
global _asm_inthandler21_keyboard


global _asm_read_cr3
global _asm_hlt
global _asm_read_gdt
global _asm_intr_exit

extern inthandler00_divide_error
extern inthandler01_debug
extern inthandler02_NMI_interrupt
extern inthandler03_breakpoint
extern inthandler04_overflow
extern inthandler05_bound_range_exceeded
extern inthandler06_invalid_opcode
extern inthandler07_device_not_available
extern inthandler08_double_fault
extern inthandler09_coprocess_segment_overrun
extern inthandler10_invalid_TSS
extern inthandler11_segment_not_present
extern inthandler12_stack_segment_fault
extern inthandler13_general_protection
extern inthandler14_page_fault

extern inthandler16_floating_point_error
extern inthandler17_alignment_check
extern inthandler18_machine_check
extern inthandler19_SIMD_floating_point_exception
extern inthandler21_keyboard
extern inthandler20_timer
extern general_handler

INT_M_CTL EQU 0X20
EOI EQU 0X20

[section .text]
[bits 32]
;.code32 'worry label

_asm_inthandler00_divide_error:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler00_divide_error
	pop eax
	popad
	pop ds
	pop es
	iretd

_asm_inthandler01_debug:
		push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler01_debug
	pop eax
	popad
	pop ds
	pop es
	iretd
	
_asm_inthandler02_NMI_interrupt:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler02_NMI_interrupt
	pop eax
	popad
	pop ds
	pop es
	iretd
	
_asm_inthandler03_breakpoint:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler03_breakpoint
	pop eax
	popad
	pop ds
	pop es
	iretd
	
_asm_inthandler04_overflow:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler04_overflow
	pop eax
	popad
	pop ds
	pop es
	iretd
	
_asm_inthandler05_bound_range_exceeded:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler05_bound_range_exceeded
	pop eax
	popad
	pop ds
	pop es
	iretd
	
_asm_inthandler06_invalid_opcode:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler06_invalid_opcode
	pop eax
	popad
	pop ds
	pop es
	iretd
	
_asm_inthandler07_device_not_available:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler07_device_not_available
	pop eax
	popad
	pop ds
	pop es
	iretd

_asm_inthandler08_double_fault:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler08_double_fault
	pop eax
	popad
	pop ds
	pop es
	iretd
	
_asm_inthandler09_coprocess_segment_overrun:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler09_coprocess_segment_overrun
	pop eax
	popad
	pop ds
	pop es
	iretd
	
_asm_inthandler10_invalid_TSS:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler10_invalid_TSS
	pop eax
	popad
	pop ds
	pop es
	iretd
	
_asm_inthandler11_segment_not_present:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler11_segment_not_present
	pop eax
	popad
	pop ds
	pop es
	iretd
	
_asm_inthandler12_stack_segment_fault:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler12_stack_segment_fault
	pop eax
	popad
	pop ds
	pop es
	iretd
	
_asm_inthandler13_general_protection:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler13_general_protection
	pop eax
	popad
	pop ds
	pop es
	iretd

_asm_inthandler14_page_fault:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler14_page_fault
	pop eax
	popad
	pop ds
	pop es
	iretd
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
_asm_inthandler16_floating_point_error:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler16_floating_point_error
	pop eax
	popad
	pop ds
	pop es
	iretd
	

_asm_inthandler17_alignment_check:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler17_alignment_check
	pop eax
	popad
	pop ds
	pop es
	iretd
	

_asm_inthandler18_machine_check:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler18_machine_check
	pop eax
	popad
	pop ds
	pop es
	iretd
	

_asm_inthandler19_SIMD_floating_point_exception:
	push es
	push ds
	pushad
	mov eax,esp
	push eax
	mov ax,ss
	mov ds,ax
	mov es,ax
	call inthandler19_SIMD_floating_point_exception
	pop eax
	popad
	pop ds
	pop es
	iretd

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
	

