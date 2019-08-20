/*(C) Olaf 25/8/2018 varm.c
 *put varm information in screen
 */

#include "../com/types.h"
#include "printk.h"
#include "vram.h"

void vram(){
	uint32_t* var=(uint32_t*)VRAM_ADDR;
	printk("varm address:");
	put_int32(var[0]);
	printk("\n");
	
}


