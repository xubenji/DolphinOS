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
#include "lock.h"

void main(void*);
void k_thread_b(void *);
void k_thread_C(void *);


int Kernel_Init(){


	init_display_info();
		
	show_screen_info();
	printk("Hello, this is DolphinOS, welcome to my Operating System\n");
	printk("------\n");
	vram();
	uint32_t memory=get_ards_infor();
	uint32_t mem_mb=memory/(1024*1024);
	printk("your machine's memory size:");
	put_dec_uint32(mem_mb);
	printk("MB\n");
	init_memory();
	
	console_lock();

	init_idt();
	init_pic();
	thread_init();
	//init_timer();
	//io_out8_ASM(PIC0_IMR, 0xfd);
	io_sti();
	
	thread_start("main",5, main, "argA ");

	//You can open time interrupt after init main thread or appear some errors
	//注册完主线程信息以后再开启时钟中断，否则会出现问题
	init_timer();

//You can use this code to check the irruglar handle ability of OS
//你可以使用以下代码来测试系统的异常处理能力
/*

	 int * p = 0x1000010;
		*p=111;           
	*/	
	while(1){
	}
	
}

/* 在线程中运行的函数 */
void main(void* arg) { 

//I don't know why I need open interrupt after thread calling in each time
//每一次线程调用都需要打开一次中断，我不知道为什么
	
	
      printk(" I am the main_thread ");
	  thread_start("k_thread_b", 1, k_thread_b, "argB ");
	  thread_start("k_thread_C", 10, k_thread_C, "argC ");
	  int time;
	  while(1){}
	/* 
	  while(1){
	  	
//处理器暂停，节省资源
//proess pasue, save the computer performance
	    

		time++;
		if (time%10000000==0)
			{
			__asm__ volatile("hlt");
			
			printk(" Main ");
			
			}
	  }*/

}

void k_thread_b(void* arg) {     
      printk(" I am the K_thread_b ");
	  int time;
	  
	  while(1){
	//	time++;
		
		if (time%1000000==0)
			{
			 __asm__ volatile("hlt");	
			lock();
			int i;
			for (i = 0;  i < 100000000; i++)
				{
				}
				printk(" BB ");
				
		
			
			unlock();
			} 
	  }
	 
}

void k_thread_C(void* arg) {     
      printk(" I am the K_thread_c ");

		int time;
	  printk("\n>:");
	  while(1){
		time++;
		//  __asm__ volatile("hlt");
		if (time%1000000==0)
			{
			__asm__ volatile("hlt");	
			lock();
				for (int i = 0;  i < 100000000; i++)
				{
				}
			printk(" CC ");
			unlock();
		    }
	  }
}

