/*(C) 2018 Future-Technology
 *design by Olaf 2018/6
 *this is the entry of DolphinOS
 */

#include "_stack_chk_fail.h"
#include "printk.h"
#include "types.h"
#include "screen.h"
#include "asc.h"


int Kernel_Init(){
	init_display_info();
	show_screen_info();
	printk("------\n");
	uint32_t num=0xabcd1234;
	printk(" ");
	puts_str(num,8);
	
	while(1){
	}
}
