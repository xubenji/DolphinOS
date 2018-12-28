#include "../com/types.h"
#include "idt.h"
#include "handler_ASM.h"
#include "io_ASM.h"

void init_idt(){
	
	IDT_Gate_Descriptor *idt=(IDT_Gate_Descriptor*)IDT_ADDR;
	
	for (int i = 0; i <= IDT_LIMIT / 8; i++) {
		set_idt_gatedesc(idt + i, 0, 0, 0, 0);
	}
	
	load_idtr(IDT_LIMIT, IDT_ADDR);
	
	//set_idt_gatedesc(idt + 0x21, (int)&_asm_inthandler21_keyboard, 2 * 8, AR_INTGATE32);
	set_idt_gatedesc(idt + 0x21, (int)&_asm_inthandler21_keyboard, 0x08, AR_INTGATE32,0);
	
	set_idt_gatedesc(idt + 0x20, (int)&_asm_inthandler20_timer, 0x08, AR_INTGATE32,0);
	
}

void set_idt_gatedesc(IDT_Gate_Descriptor *gd, uint32_t offset, uint32_t selector, uint32_t ar, uint8_t privilege){
	
	gd->offset_low   = offset & 0xffff;
	
	gd->selector     = selector;
	gd->datacount     = (ar >> 8) & 0xff;
	gd->attr		= ar | (privilege << 5);
	gd->offset_high  = (offset >> 16) & 0xffff;
		
}
