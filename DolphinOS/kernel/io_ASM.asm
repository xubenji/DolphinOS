;(C) 2018 Olaf
;io.asm
;there are nasm assembly function
;If you see the "io" character, this function involves the I/O operation.

global io_in8_ASM
global io_out8_ASM
global io_sti
global load_idtr

[section .text]
[bits 32]
io_sti:	; void io_sti(void),open all of descripters
		STI
		RET

io_in8_ASM:	;int io_in8(int port);
	mov		edx,[esp+4]
	xor		eax,eax
	in		al,dx
	ret

io_out8_ASM:	;void io_out8(int port, int data);
	mov		edx,[esp+4]
	mov		al,[esp+8]
	out		dx,al
	ret

load_idtr:		; void load_idtr(int limit, int addr)
	MOV		AX,[ESP+4]		
	MOV		[ESP+6],AX
	LIDT	[ESP+6]
	RET
