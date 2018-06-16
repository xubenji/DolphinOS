#include "printk.h"

struct display_char CHAR;

//Now, you can use this function to output char in screen

void show_infor(){
	CHAR.vram=CHAR_DISPLAY_ADDERSS;
	CHAR.cursor_pos=0;
	CHAR.color=0x07;
	print_char('N');
	print_char('o');
	print_char('w');
	print_char('_');
	print_char('t');
	print_char('h');
	print_char('e');
	print_char('_');
	print_char('O');
	print_char('S');
	print_char('_');
	print_char('i');
	print_char('n');
	print_char('_');
	print_char('k');
	print_char('e');
	print_char('r');
	print_char('n');
	print_char('e');
	print_char('l');	
}

void print_char(uint8_t ch){
	
	if(ch==0xd){
		
	}else if(ch==0xa){

	}else if(ch==0x8){

	}else{
	CHAR.vram[CHAR.cursor_pos*2] = ch;
	CHAR.vram[CHAR.cursor_pos*2+1] = CHAR.color;
	CHAR.cursor_pos++;	
	}
}
 
