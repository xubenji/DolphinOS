#include "types.h"
#include "io_ASM.h"
#include "printk.h"

uint16_t get_cursor(){
	uint16_t pos_low, pos_high;
	io_out8_ASM(0x03d4, 0x0e);			
	pos_high = io_in8_ASM(0x03d5);
	io_out8_ASM(0x03d4, 0x0f);			
	pos_low = io_in8_ASM(0x03d5);
	return (pos_high<<8 | pos_low);	
}

void set_cursor(struct display_char* chs){
	io_out8_ASM(0x03d4, 0x0e);			
	io_out8_ASM(0x03d5, chs->cursor_pos>>8);
	io_out8_ASM(0x03d4, 0x0f);			
	io_out8_ASM(0x03d5, chs->cursor_pos);
}

