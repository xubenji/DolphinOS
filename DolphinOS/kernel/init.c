/*(C) 2018 Future-Technology
 *design by Olaf 2018/6
 *this is the entry of DolphinOS
 */

#include "printk.h"
#include "types.h"
#include "screen.h"
#include "asc.h"

int Kernel_Init(){
	init_display_info();
	show_screen_info();

	printk("------\n");
	
	uint32_t num=0xabcd1234;
	char* ch;
	ch=ints_to_str(num);
	for(int i=0;i<8;i++){
		print_char(*(ch+i));
	}

	printk(" ");
	//puts_str(num,8);
	
	while(1){
	}
	
	
	
}
