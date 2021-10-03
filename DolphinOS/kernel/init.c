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
void u_prog_a(void);
int test_num=0;

int Kernel_Init(){

	init_display_info();
		
	show_screen_info();
	
	vram();
	
	check_memory();
	
	init_memory();
	
	init_idt();
	
	init_pic();
	
	thread_init();

	init_tss();
	
	lock_init();

	uint32_t addr = get_phy_addr(0x80013910);
	printk("\nThis is real phy address!!!:");
	put_int32(addr);
	printk("\n~~");

	//uint32_t *p = 0x807fffff;
	//*p=0;
	//put_int32(*p);
	printk("\n");
	

	
	thread_start("main",5, main, "argA ");
	process_execute(u_prog_a, "u_prog_a");
	io_sti();

	//You can open time interrupt after init main thread or appear some errors
	//注册完主线程信息以后再开启时钟中断，否则会出现问��
	init_timer();
	
//You can use this code to check the irruglar handle ability of OS
//你可以使用以下代码来测试系统的异常处理能��
/*
	 int * p = 0x1000010;
		*p=111;           
	*/	
	while(1);
	
}

/* 在线程中运行的函��*/
void main(void* arg) { 

//I don't know why I need open interrupt after thread calling in each time
//每一次线程调用都需要打开一次中断，我不知道为什��
	
	
      printk(" I am the main_thread ");
	  intr_disable();
	  thread_start("k_thread_b", 1, k_thread_b, "argB ");
	  thread_start("k_thread_C", 10, k_thread_C, "argC ");
	   
	   intr_enable();
	  int time;
	  while(1){
	  	
//处理器暂停，节省资源
//proess pasue, save the computer performance
	    
		_asm_hlt();

		time++;
		if (time%10000000==0)
			{
		
			
			printk(" Main ");
			
			}
	  }

}

void k_thread_b(void* arg) {     
      printk(" I am the K_thread_b ");
	  int time;
	  
	  while(1){
		time++;
		
		//if (time%10000000==0)
			//{
			
			lock(1);
		
			
			//	printk(" BB ");
				//put_int32(test_num);
				_asm_hlt();
		
			
			unlock();
			//} 
			
	  }
	 
}

void k_thread_C(void* arg) {     
      printk(" I am the K_thread_c ");

		int time;
	  printk("\n>:");
	 
	  while(1){
		time++;
	  	_asm_hlt();	
		if (time%10000000==0)
			{
				
				intr_disable();
				
				printk(" CC ");
				intr_enable();
		    }
		
	  }
}

void u_prog_a(void){
	
	//printk("q");
		//__asm__ volatile("hlt"); 

		while(1){
		test_num++;
		}
	
	
}

