#include "io_ASM.h"
#include "../com/types.h"
#include "printk.h"
#include "handler_ASM.h"
#include "pic.h"
#include "io_ASM.h"
#include "handlers.h"
#include "thread.h"
#include "debug.h"

/*It is very difficult to find this mistake, because the textbook is aslo worry!!!!
 *At the beginning, my os can only accept the interupt once!!!
 *First, I suspicious of the IDT, but the IDT is work. because the os can accept the interupt once.
 *And then, I study the 8259A, but I found it is not 8259A problem. Even you have inform the pic that the interupt has been finished.
 *Finally, I was surprised to find that the Intel 8042. you need read the data from the Intel 8042! beacuse if you haven't read the data, the 8042 still think the interupt hasn't be completed.
 *It cost me about three weeks to solve the problem. OMG!!!
 */

uint32_t ticks;

void inthandler21_keyboard(int32_t *esp){
	printk("  INT21 (IRQ-1)  ");
	io_out8_ASM(PIC0_OCW2,0x61);
	io_in8_ASM(0x60); //It is very important sentence in the function. If you haven't read the data, the 8042 still think the interupt hasn't be completed.
}

uint32_t times=0;

/*time hander function*/ 
void inthandler20_timer(int32_t *esp){	
	io_out8_ASM(PIC0_OCW2, 0x60);
	struct task_struct* cur_thread = running_thread();
	
//	PAUSE(cur_thread->stack_magic == 0x19870916);
	if(cur_thread->stack_magic == 0x19870916){
		printk("inthandler20_timer error!");
		while(1){}
	}
	cur_thread->elapsed_ticks++;
	ticks++;
	
	if(cur_thread->ticks==0){
		schedule();
	}else{
		cur_thread->ticks--;
	}
	
	//times++;
	//print * per second
	if(ticks%100==0){
		printk(" A ");
		//thread_start("k_thread_a", 31, k_thread_a, "argA ");
	}
}
