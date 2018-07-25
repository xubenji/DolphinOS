;load.asm  Copyright (C) 2018/6 Olaf
;base the MatchOS
;modified by wenjie, Hu
;using the nasm, the load.bin will occupy 9 sectors memory
;he kernel will occupy 256 sectors

KERNEL_SECTOR_OFFSET EQU 9		
KERNEL_SECTORS EQU 256	

KERNEL_ENTRY EQU 0x10000

PHY_KERNEL_ENTRY EQU 0x10000
VIR_KERNEL_ENTRY EQU 0x80010000

PAGE_diR_ADDR equ 0x1000
PAGE_TBL_ADDR equ 0x2000


;0x7c00~0x7e00	    boot.bin	512bytes 1sector
;0x70000~0x71000	load.bin	1kb      8sectors	
;0x71000~0x80000	kernel.bin	60kb     120sectors	
;We select the 0x0114 display mode
;Due to the inability to restore true color. We will change it in subsequent versions
;0x111 640*480*16bit 
;0x114 800*600*16bit 
;0x117 1024*768*16bit 
;0x11a 1280*1024*16bit 

MODE_640_480 EQU 0x111
MODE_800_600 EQU 0x114
MODE_10240_7680 EQU 0x117
MODE_1280_1024 EQU 0x11A

VBEMODE	EQU	MODE_800_600

;The real physical memory is 0x0000+0x00600, because the offset is 0x00600
;ards buf address (0x6004)
;the number of ards (0x6000)

ARDS_BUF	EQU		0x0004	
ARDS_NR		EQU		0x0000	

;the display information will occupy 16bytes in memory
;VCOLOR is digital of the color
;XWIDTH is the number of pixels on the x axis
;YHEIGHT is the number of pixels on the y axis
;VRAM is the memory address of vram

VCOLOR	EQU		0			
XWIDTH	EQU		2			
YHEIGHT	EQU		4			
VRAM	EQU		6			

;load was loaded at 0x10000

	org 0x70000		

	mov ax, cs
	mov ds, ax 
	mov es, ax 
	mov ss, ax 
	mov sp, 0										;ss=0x1000, sp=0
	
;display string 'OS' in screen
 
	mov ax, 0xb800
	mov es, ax 
	
	mov al, [O]
	mov byte [es:0x0c],al
	mov byte [es:0x0d],0X07
	mov al, [S]
	mov byte [es:0x0e],al
	mov byte [es:0x0f],0X07
	mov byte [es:0x10],'0'
	mov byte [es:0x11],0X04	
	mov byte [es:0x12],'.'
	mov byte [es:0x13],0X04
	mov byte [es:0x14],'0'
	mov byte [es:0x15],0X04
	mov byte [es:0x16],'2'
	mov byte [es:0x17],0X04

O: db 'O'
S: db 'S'

		
;we read load from sector 1(0 is first) width 8 sectors to 0x11000

	mov ax, 0x1000
	mov es, ax 
	
	xor bx, bx 
	mov si, KERNEL_SECTOR_OFFSET
	mov cx, 128
rd_kern1:	
	call read_floppy_sector
	add bx, 512
	inc si 
	loop rd_kern1
	
	mov ax, 0x2000
	mov es, ax 
	
	xor bx, bx 
	mov si, KERNEL_SECTOR_OFFSET+128
	mov cx, 128
rd_kern2:	
	call read_floppy_sector
	add bx, 512
	inc si 
	loop rd_kern2



;check memory information
;we save the memory information in ARDS_BUF struct

check_memory:
	xor ebx, ebx 
	mov edx, 0x534d4150
	mov di, ARDS_BUF
	mov ax, 0x600 
	mov es, ax
	mov word [es:ARDS_NR], 0
.e820_mem_get_loop:
	mov eax, 0x0000e820
	mov ecx, 20
	int 0x15
	jc .e820_check_failed
	add di, cx 
	add word [es:ARDS_NR], 1
	cmp ebx, 0
	jnz .e820_mem_get_loop
	jmp protect_set
.e820_check_failed:
	jmp $


init_vbe:

;check whether the computer supports the VBE display mode 
;the buffer from the 0x9000

	mov	ax,0x9000	
	mov	es,ax
	mov	di,0
	mov	ax,0x4f00									;check the vbe, we select the 0x4f00 mode
	int	0x10
	cmp	ax,0x004f							;if computer can't supports this mode, jmp to screen_default
	jne	screen_default
	
;check the vbe versions computer must supports vbe 2.0
	
	mov	ax,[es:di+4]
	cmp	ax,0x0200
	jb	screen_default								;if (ax < 0x0200) goto screen_default

;get the display information, 256 sectors
;cx='Enter the check mode'
;[es:di+0x00]	property of mode. if bit7 equal to 1, we add 0x4000 to bit7.
;[es:di+0x12]	the number of pixels on the x axis
;[es:di+0x14]	the number of pixels on the y axis
;[es:di+0x19]	digital of color		8bits£¬16bits£¬24bits£¬32bits
;[es:di+0x1b]	palette
;[es:di+0x28]	VRAM memory address
	
	mov	cx,VBEMODE									;cx=mode number
	mov	ax,0x4f01									;a way to get the display mode, ax=0x4f01
	int	0x10
	cmp	ax,0x004f									;ax=0x004f
	jne	screen_default

	mov	BX,VBEMODE+0x4000							;bx=mode number
	mov	ax,0x4f02									
	int	0x10
	
	mov ax, 0x610
	mov ds, ax
	
	xor ax, ax
	mov	al,[es:di+0x19]
	mov	[VCOLOR],ax 								;save the digital of color
	mov	ax,[es:di+0x12]
	mov	[XWIDTH],ax									;save the number of pixels on the x axis
	mov	ax,[es:di+0x14]
	mov	[YHEIGHT],ax								;save the number of pixels on the y axis
	mov	eax,[es:di+0x28]
	mov	[VRAM],eax									;save the vram address

	JMP	protect_set

	
screen_default:
	mov ax, 0x610
	mov ds, ax
	
	mov		al,0x13									;320*200*8 
	mov		ah,0x00
	int		0x10
	mov		BYTE [VCOLOR],8
	mov		WORD [XWIDTH],320
	mov		WORD [YHEIGHT],200
	mov		DWORD [VRAM],0x000a0000
	

protect_set:
	mov ax, cs
	mov ds, ax
	
;close the interruption

	cli
	
;load GDTR

	lgdt	[gdt48]
	lidt	[cs:IDTR]

;enable A20 line

	in		al,0x92
	or		al,0000_0010B
	out		0x92,al
	
;set CR0 bit PE

	mov		eax,cr0
	or		eax,1
	mov		cr0,eax
	
;far jump:to clean the cs

	jmp		dword 0x08:flush

	
times 1024-($-$$) db 0	

;Global Descriptor Table,GDT

gdt:

;0:void
	
	dd		0x00000000
	dd		0x00000000
	
;1:4GB(flat-mode) code segment 0

	dd		0x0000ffff
	dd		0x00cf9A00

;2:4GB(flat-mode) data segment 0

	dd		0x0000ffff
	dd		0x00cf9200
	
	dd		0x00000000
	dd		0x00000000
	
	dd		0x0000ffff
	dd		0x00cffa00
	
;0x00cffa000000ffff
	
	dd		0x0000ffff
	dd		0x00cff200
	
;DRIVER CODE

	dd		0x00000000
	dd		0x00000000
	
	dd		0x00000000
	dd		0x00000000

;DRIVER DATA

	dd		0x00000000
	dd		0x00000000
	
	dd		0x00000000
	dd		0x00000000
	
gdt48:
	.size	dw	(8*8-1)
	.offset	 dd gdt

dd		0x00000000
dd		0x00000000	
ADR_IDT	equ		0x00090000
LIMIT_IDT equ	0x000007ff

IDTR:
	.limit		dw	LIMIT_IDT						;the length of IDT
	.base		dd	ADR_IDT							;memory address of IDT
		

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


[bits 32]
flush:

;init all segment registeres
	mov ax, 0x10															;the data 
	mov ds, ax 
	mov es, ax 
	mov fs, ax 
	mov gs, ax 
	mov ss, ax 
	mov esp, stack_top_end
	
;display char 'P'
	mov dword [0xb8000+4], 'P'
	mov dword [0xb8000+5], 0X06

	call step_page
	
	mov dword [0x800b8000+4], 'q'
	mov dword [0x800b8000+5], 0X03
	;call flush
	;mov esi, PHY_KERNEL_ENTRY
	;mov edi, VIR_KERNEL_ENTRY
	;mov ecx, KERNEL_SECTORS*512
	;call cpy_kernel
	
	;jmp inio kernel with protect mode,no interrupt,high memory read and write
	;jmp $
	jmp VIR_KERNEL_ENTRY
	
cpy_kernel:
.re_cpy:
	mov al, [esi]
	mov [edi], al
	inc esi 
	inc edi
	loop .re_cpy
	ret	
	
step_page:  
    mov ecx,1024                   										  ;directory of paging
    mov ebx,PAGE_diR_ADDR               								  ;directory memory address
    xor esi,esi 
	
.clean_pdt:
    mov dword [ebx+esi],0x00000000  									  
    add esi,4
    loop .clean_pdt

    mov edi, PAGE_TBL_ADDR
    mov ebx, PAGE_diR_ADDR
    mov dword [ebx], PAGE_TBL_ADDR|0x07
    mov dword [ebx+512*4], PAGE_TBL_ADDR|0x07    
    mov dword [ebx+4092], PAGE_diR_ADDR|0x07
   	
    mov cx, 1024/4
    mov esi, 0|0x07
    
.set_pt0:
    mov [edi], esi
    add esi, 0x1000
    add edi,4
    loop .set_pt0
   	
;map vram

    mov eax, [0x6100+6]													  ;ds = 0x7000 phy 0x6108
    shr eax,22
    shl eax,2
	
;eax=0xe00
    
    mov edx,(PAGE_TBL_ADDR+0x1000)|0x07
    mov [PAGE_diR_ADDR+eax], edx
    
    mov edi, PAGE_TBL_ADDR+0x1000										  ;edi=0x3000
    mov esi, [0x6100+6]													  ;esi= 0xe0000000
    or esi, 0x07														  ;esi= 0xe0000007
    
    mov cx, 1024														  ;map of vram, the vram size is 4MB
    
.set_vram:
        mov dword [edi ], esi
	add edi, 4
	add esi, 0x1000
	loop .set_vram
	
   	mov eax , PAGE_diR_ADDR
    mov cr3,eax
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
.f:
    ret	
	
stack_top:
	times 256 db 0
stack_top_end equ $-stack_top

;Fill in 1KB memory space by 0

times (4096-($-$$)) db 0
