#include "types.h"
#include "screen.h"
#include "printk.h"

struct screen_info info;

void show_screen_info(){

	uint32_t *vram_addr;
	int vram;
	info.color_digit = *((uint16_t *)SCREEN_INFO_ADDR);
	info.wide = (uint32_t )(*((uint16_t *)(SCREEN_INFO_ADDR+2)));
	info.high = (uint32_t )(*((uint16_t *)(SCREEN_INFO_ADDR+4)));
	
	vram_addr = (uint32_t *)(SCREEN_INFO_ADDR+6);
	info.vram = (uint8_t *) (*vram_addr);
	
	if(info.color_digit==0x00){
		printk("Now it's a text mode\n");
	}
	
}


