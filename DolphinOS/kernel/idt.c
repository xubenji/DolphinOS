#include "../com/types.h"
#include "idt.h"
#include "handler_ASM.h"
#include "io_ASM.h"

#define EFLAGS_IF   0x00000200       // eflags寄存器中的if位为1
#define GET_EFLAGS(EFLAG_VAR) asm volatile("pushfl; popl %0" : "=g" (EFLAG_VAR))

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

/* set IDT descriptor*///5CC7C5FBB253
void set_idt_gatedesc(IDT_Gate_Descriptor *gd, uint32_t offset, uint32_t selector, uint32_t ar, uint8_t privilege){	
	gd->offset_low   = offset & 0xffff;	
	gd->selector     = selector;
	gd->datacount     = (ar >> 8) & 0xff;
	gd->attr		= ar | (privilege << 5);
	gd->offset_high  = (offset >> 16) & 0xffff;		
}

/* 开中断并返回开中断前的状态*/
enum intr_status intr_enable() {
   enum intr_status old_status;
   if (INTR_ON == intr_get_status()) {
      old_status = INTR_ON;
      return old_status;
   } else {
      old_status = INTR_OFF;
      __asm__ volatile("sti");	 // 开中断,sti指令将IF位置1
      return old_status;
   }
}

/* 关中断,并且返回关中断前的状态 */
enum intr_status intr_disable() {     
   enum intr_status old_status;
   if (INTR_ON == intr_get_status()) {
      old_status = INTR_ON;
      __asm__ volatile("cli" : : : "memory"); // 关中断,cli指令将IF位置0
      return old_status;
   } else {
      old_status = INTR_OFF;
      return old_status;
   }
}

/* 将中断状态设置为status */
enum intr_status intr_set_status(enum intr_status status) {
   return status & INTR_ON ? intr_enable() : intr_disable();
}

/* 获取当前中断状态 */
enum intr_status intr_get_status() {
   uint32_t eflags = 0; 
   GET_EFLAGS(eflags);
   return (EFLAGS_IF & eflags) ? INTR_ON : INTR_OFF;
}
