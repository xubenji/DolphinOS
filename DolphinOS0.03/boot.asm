;(C) 2018 Future-Technology
;2018/5/30
;boot of DolphinOS
;we use LBA address for floppy

LOAD_SECTOR_OFFSET EQU 1		;load is on the 1st sector
LOAD_SECTORS EQU 8	                ;this time we use 8 sectors for load.it's 1kb(4096 bytes)

;0x7c00~0x7e00   	boot.bin	512byte 1sector
;0x70000~0x71000	load.bin	1kb 8sector	
;0x71000~0x80000	kernel.bin	60kb 120sector	

	org 0x7c00
	[bits 16]
entry:
	mov ax, cs 
	mov ds, ax 
	mov es, ax 
	xor ax, ax
	mov ss, ax
	mov sp, 0x7c00
	
	;clean screan
	mov ax, 0x02
	int 0x10
	
	;display 'FutureOS'
	mov ax, 0xb800
	mov es, ax 
	mov al, [F]
	mov byte [es:0],al
	mov byte [es:1],0X07
	mov al, [u]
	mov byte [es:2],al
	mov byte [es:3],0X07
	mov al, [t]
	mov byte [es:4],al
	mov byte [es:5],0X07
	mov al, [u]
	mov byte [es:6],al
	mov byte [es:7],0X07
	mov al, [r]
	mov byte [es:8],al
	mov byte [es:9],0X07
	mov al, [e]
	mov byte [es:0x0a],al
	mov byte [es:0x0b],0X07
	
	;jmp entry
	
	;it seemed that bx will affect the boot, so bx=0
	xor bx, bx
	;we read load from sector 1(0 is first) width 8 sectors to 0x10000
	;es:dx=buffer address
	mov ax, 0x7000	
	mov es, ax 
	xor bx, bx 
	mov si, LOAD_SECTOR_OFFSET
	mov cx, LOAD_SECTORS
rd_load:	
	call read_floppy_sector
	add bx, 512
	inc si 
	loop rd_load
	
	;cs=0x1000 ip=0
	jmp 0x7000:0
	
;si=LBA address, from 0
;cx=sectors
;es:dx=buffer address	
;this function was borrowed from internet
read_floppy_sector:
	push ax 
	push cx 
	push dx 
	push bx 
	
	mov ax, si 
	xor dx, dx 
	mov bx, 18
	
	div bx 
	inc dx 
	mov cl, dl 
	xor dx, dx 
	mov bx, 2
	
	div bx 
	
	mov dh, dl
	xor dl, dl 
	mov ch, al 
	pop bx 
.rp:
	mov al, 0x01
	mov ah, 0x02 
	int 0x13 
	jc .rp 
	pop dx
	pop cx 
	pop ax
	ret
	
	
;char B
F: db 'F'
u: db 'u'
t: db 't'
;u: db 'u'
r: db 'r'
e: db 'e'
O: db 'O'
S: db 'S'

;make boot to be 512 bytes
times 510-($-$$) db 0
dw 	0xaa55
