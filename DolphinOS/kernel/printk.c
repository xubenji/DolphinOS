#include "printk.h"
#include "types.h"
#include "asc.h"

struct display_char chs;

//Now, you can use this function to output char in screen

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
	
	if(ch==0xd){
		chs.cursor_pos = new_line(chs.cursor_pos); //line feed
	}else if(ch==0xa){
		chs.cursor_pos = new_line(chs.cursor_pos);
	}else if(ch==0x8){
		chs.cursor_pos = backspace(chs.cursor_pos);
	}else{
		print_char(ch);

	}
}

void printk(uint8_t *str){
	while (*str!=0x00)
		{
		get_cursor_pos(*str);
		str++;
		}
}


void puts_str(int32_t num_hex,int32_t length){ 
	char ch[32];
	char p[32];
	ints_to_str(num_hex,ch);
	for(int i=0;i<length;i++){
		print_char(*(ch+i));
	}
}


void print_char(uint8_t ch){
	chs.vram[chs.cursor_pos*2] = ch;
	chs.vram[chs.cursor_pos*2+1] = chs.color;
	chs.cursor_pos++;	
}
 



