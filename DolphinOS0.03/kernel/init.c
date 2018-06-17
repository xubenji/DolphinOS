/*(C) 2018 Future-Technology
 *design by Olaf 2018/6
 *this is the entry of DolphinOS
 */
#include "printk.h"
#include "types.h"
#include "screen.h"

int Kernel_Init(){
	/*char *v = CHAR_DISPLAY_ADDERSS;
	v[0] = 0x46;
	v[1] = 0x07;
	v[2] = 'h';
	*/
	init_display_info();
	show_screen_info();
	
	
	while(1){
	}
	
	
	
}
