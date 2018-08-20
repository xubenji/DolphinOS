#include "printk.h"
#include "types.h"
#include "asc.h"
#include "io_ASM.h"

struct display_char chs;

//Now, you can use this function to output char in screen

uint16_t get_cursor(){
	uint16_t pos_low, pos_high;
	io_out8_ASM(0x03d4, 0x0e);			
	pos_high = io_in8_ASM(0x03d5);
	io_out8_ASM(0x03d4, 0x0f);			
	pos_low = io_in8_ASM(0x03d5);
	return (pos_high<<8 | pos_low);	
}

void set_cursor(){
	io_out8_ASM(0x03d4, 0x0e);			
	io_out8_ASM(0x03d5, chs.cursor_pos>>8);
	io_out8_ASM(0x03d4, 0x0f);			
	io_out8_ASM(0x03d5, chs.cursor_pos);
}

void init_display_info(){
	chs.vram=CHAR_DISPLAY_ADDERSS;
	chs.cursor_pos=0;
	chs.color=0x07;
	printk(">init kernel..\n");
}

uint16_t new_line(uint16_t cursor_pos){
	cursor_pos -= cursor_pos%LINE_MAX_CHAR;
	cursor_pos += LINE_MAX_CHAR;
	return cursor_pos;
}

uint16_t backspace(uint16_t cursor_pos){
	cursor_pos=cursor_pos-1;
	return cursor_pos;
}

void get_cursor_pos(uint8_t ch){
	chs.cursor_pos = get_cursor();
	if(ch==0xd){
		chs.cursor_pos = new_line(chs.cursor_pos); //line feed
	}else if(ch==0xa){
		chs.cursor_pos = new_line(chs.cursor_pos);
	}else if(ch==0x8){
		chs.cursor_pos = backspace(chs.cursor_pos);
	}else{
		print_char(ch);
	}
	set_cursor();
}

void printk(uint8_t *str){
	while (*str!=0x00)
		{
		get_cursor_pos(*str);
		str++;
		}
}

void puts_int64(int64_t num_hex){ 
	char ch[32];
	char p[32];
	int64_to_str(num_hex,ch);
	printk("0x");
	for(int i=0;i<16;i++){
		print_char(*(ch+i));
	}
}

void puts_int32(int32_t num_hex){ 
	char ch[32];
	char p[32];
	int32_to_str(num_hex,ch);
	printk("0x");
	for(int i=0;i<8;i++){
		print_char(*(ch+i));
	}
}

void puts_int16(int16_t num_hex){ 
	char ch[32];
	char p[32];
	int16_to_str(num_hex,ch);
	printk("0x");
	for(int i=0;i<4;i++){
		print_char(*(ch+i));
	}
}

void puts_int8(int8_t num_hex){ 
	char ch[32];
	char p[32];
	int8_to_str(num_hex,ch);
	printk("0x");
	for(int i=0;i<2;i++){
		print_char(*(ch+i));
	}
}

void print_char(uint8_t ch){
	chs.vram[chs.cursor_pos*2] = ch;
	chs.vram[chs.cursor_pos*2+1] = chs.color;
	chs.cursor_pos++;	
}
 



