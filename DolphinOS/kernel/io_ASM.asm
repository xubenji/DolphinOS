;(C) 2018 Olaf
;io.asm
;there are so many nasm assembly function
;If you see the "io" character, this function involves the I/O operation.

global io_in8_ASM
global io_out8_ASM

[section .text]
[bits 32]
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
