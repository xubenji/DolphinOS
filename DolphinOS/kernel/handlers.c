#include "io_ASM.h"
#include "../com/types.h"
#include "printk.h"
#include "handler_ASM.h"
#include "pic.h"
#include "io_ASM.h"
#include "handlers.h"
#include "thread.h"
#include "debug.h"
#include "../driver/keyboard.h"

int t=0;
/*It is very difficult to find this mistake, because the textbook is aslo worry!!!!
 *At the beginning, my os can only accept the interupt once!!!
 *First, I suspicious of the IDT, but the IDT is work. because the os can accept the interupt once.
 *And then, I study the 8259A, but I found it is not 8259A problem. Even you have inform the pic that the interupt has been finished.
 *Finally, I was surprised to find that the Intel 8042. you need read the data from the Intel 8042! beacuse if you haven't read the data, the 8042 still think the interupt hasn't be completed.
 *It cost me about three weeks to solve the problem. OMG!!!
 */
void inthandler21_keyboard(int32_t *esp){
	unsigned char keydata, s[4];
	//printk("  INT21 (IRQ-1)  ");
	keydata = io_in8_ASM(0x60);
	io_out8_ASM(PIC0_OCW2,0x61);
	//puts_int8(keydata);
	keyborad_map(keydata);
	//printk(" ");
	io_in8_ASM(0x60); //It is very important sentence in the function. If you haven't read the data, the 8042 still think the interupt hasn't be completed.
}

uint32_t times=0;
uint32_t ticks;   

//general  handler: register all interupption of OS. if others irrgulartion occuring, it would go this function
//一般性的中断处理程序，将所有的中断都注册了，触发其他异常都是走这个程序
void general_handler(uint8_t vec_num){
	intr_disable();
	if(vec_num == 0x27 || vec_num == 0x2f){
			return;
	}else if(vec_num == 0x9c){
			uint32_t cr3 = read_cr3_ASM();
			printk("\nPage Fault!!!   Address:"); //缺页故障
			puts_int32(cr3);
			
		} 
	printk("  Exception Number:");
	puts_int8(vec_num);					//打印异常中断码
	
	PAUSE(1==2);						//强停系统
}

void inthandler20_timer(int32_t *esp){
	io_out8_ASM(PIC0_OCW2, 0x60);
//	times++;
	//print * per second
/*	if(times%100==0){

		printk(" 1 ");
	
	}*/

//	printk(" 1 ");
	struct task_struct* cur_thread = NULL;

	cur_thread = running_thread();
//	puts_int32(sizeof(struct task_struct));

	
	//puts_int32(cur_thread->stack_magic);
		

//check the special number defined by myself. 


	
	//PAUSE(cur_thread->stack_magic == 0x19870916);         // 检查栈是否溢出
	cur_thread->elapsed_ticks++;	  // 记录此线程占用的cpu时间嘀
	ticks++;	  //从内核第一次处理时间中断后开始至今的滴哒数,内核态和用户态总共的嘀哒数
	//printk("p11");
	if (cur_thread->ticks == 0) {	  // 若进程时间片用完就开始调度新的进程上cpu
	//	puts_int32(cur_thread->stack_magic );
	schedule(); 
	if (cur_thread->stack_magic!=0x19870916){
			printk("");
			puts_int32(cur_thread->stack_magic);
			PAUSE(1==2);
		}
	
	//puts_int32(cur_thread->stack_magic );
	} else {				  // 将当前进程的时间片-1
		cur_thread->ticks--;
	}
	

}
