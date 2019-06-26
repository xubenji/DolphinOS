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
#include "thread.h"
#include "debug.h"
#include "thread.h"

void k_thread_a(void*);
void k_thread_b(void*);

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
	
	//char abc='p';
	//print_char(abc);
	//while(1);
	thread_init();
	init_timer();
	//io_out8_ASM(PIC0_IMR, 0xfd);
	io_sti();
	//PAUSE(1==2);
	thread_start("k_thread_a", 0, k_thread_a, "argA ");
	thread_start("k_thread_b", 0, k_thread_b, "argB ");
	
	
	//get_kernel_pages(2);
	//get_kernel_pages(2);
	while(1){
	   // printk(" B ");
	}
}

/* 在线程中运行的函数 */
void k_thread_a(void* arg) {     
/* 用void*来通用表示参数,被调用的函数知道自己需要什么类型的参数,自己转换再用 */
   char* para = arg;
 
      printk(" K_thread_a ");

	  while(1){}
}

/* 在线程中运行的函数 */
void k_thread_b(void* arg) {     
/* 用void*来通用表示参数,被调用的函数知道自己需要什么类型的参数,自己转换再用 */
   char* para = arg;
 
      printk(" K_thread_b ");

	  while(1){}
}

