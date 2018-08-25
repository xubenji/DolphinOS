/*(C) 2018 Future-Technology
 *design by Olaf 2018/6
 *this is the entry of DolphinOS
 */

#include "_stack_chk_fail.h"
#include "printk.h"
#include "types.h"
#include "screen.h"
#include "asc.h"
#include "memory.h"


int Kernel_Init(){
	init_display_info();
	show_screen_info();
	printk("Hello,this is DolphinOS0.07c,welcome my Operating System\n");
	printk("------\n");
	uint32_t memory=get_ards_infor();
	uint32_t mem_mb=memory/(1024*1024);
	printk("your machine's memory size is :");
	puts_int32(mem_mb);
	printk("MB\n");
	init_memory();
	while(1){
	}
}
