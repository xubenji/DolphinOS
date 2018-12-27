/*(C) 2018 Future-Technology
 *design by Olaf 
 *this is the entry of DolphinOS
 */

#include "../com/_stack_chk_fail.h"
#include "printk.h"
#include "../com/types.h"
#include "screen.h"
#include "asc.h"
#include "memory.h"
#include "../com/math.h"
#include "idt.h"
#include "pic.h"
#include "io_ASM.h"
#include "handler_ASM.h"
#include "timer.h"
#include "vram.h"

int Kernel_Init(){
	init_display_info();
	show_screen_info();
	printk("Hello, this is DolphinOS0.07, welcome to my Operating System\n");
	printk("------\n");
	vram();
	uint32_t memory=get_ards_infor();
	uint32_t mem_mb=memory/(1024*1024);
	printk("your machine's memory size:");
	put_dec_uint32(mem_mb);
	printk("MB\n");
	init_memory();
	
	init_idt();
	
	init_pic();
	init_timer();
	//io_out8_ASM(PIC0_IMR, 0xfd);
	io_sti();
	
	while(1){}
}
