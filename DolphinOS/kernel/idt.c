#include "../com/types.h"
#include "idt.h"
#include "handler_ASM.h"
#include "io_ASM.h"

#define EFLAGS_IF   0x00000200       // eflags寄存器中的if位为1
#define GET_EFLAGS(EFLAG_VAR) asm volatile("pushfl; popl %0" : "=g" (EFLAG_VAR))

void init_idt(){
	
	IDT_Gate_Descriptor *idt=(IDT_Gate_Descriptor*)IDT_ADDR;

	//将所有的异常都指向通用异常处理程序
	for (int i = 0; i <= IDT_LIMIT / 8; i++) {
		set_idt_gatedesc(idt + i, (int)&_asm_general_handler, 0x08, AR_INTGATE32, 0);
		//set_idt_gatedesc(idt + i, 0, 0x0, 0, 0);
	}

	load_idtr(IDT_LIMIT, IDT_ADDR);
	//set_idt_gatedesc(idt + 0xe, (int)&_asm_general_handler, 0x08, AR_INTGATE32, 0);
	//set_idt_gatedesc(idt + 0x21, (int)&_asm_inthandler21_keyboard, 2 * 8, AR_INTGATE32);
	set_idt_gatedesc(idt + 0x00, (int)&_asm_inthandler00_divide_error, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x01, (int)&_asm_inthandler01_debug, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x02, (int)&_asm_inthandler02_NMI_interrupt, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x03, (int)&_asm_inthandler03_breakpoint, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x04, (int)&_asm_inthandler04_overflow, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x05, (int)&_asm_inthandler05_bound_range_exceeded, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x06, (int)&_asm_inthandler06_invalid_opcode, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x07, (int)&_asm_inthandler07_device_not_available, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x08, (int)&_asm_inthandler08_double_fault, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x09, (int)&_asm_inthandler09_coprocess_segment_overrun, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x0a, (int)&_asm_inthandler10_invalid_TSS, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x0b, (int)&_asm_inthandler11_segment_not_present, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x0c, (int)&_asm_inthandler12_stack_segment_fault, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x0d, (int)&_asm_inthandler13_general_protection, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x0e, (int)&_asm_inthandler14_page_fault, 0x08, AR_INTGATE32,0);
	//15 is reserved
	set_idt_gatedesc(idt + 0x10, (int)&_asm_inthandler16_floating_point_error, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x11, (int)&_asm_inthandler17_alignment_check, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x12, (int)&_asm_inthandler18_machine_check, 0x08, AR_INTGATE32,0);
	set_idt_gatedesc(idt + 0x13, (int)&_asm_inthandler19_SIMD_floating_point_exception, 0x08, AR_INTGATE32,0);
	//20~32 inthandler is reserved
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
