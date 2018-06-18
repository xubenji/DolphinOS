#include "printk.h"
#include "types.h"
#include "asc.h"

struct display_char CHAR;

//Now, you can use this function to output char in screen

void init_display_info(){
	CHAR.vram=CHAR_DISPLAY_ADDERSS;
	CHAR.cursor_pos=0;
	CHAR.color=0x07;
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
		CHAR.cursor_pos = new_line(CHAR.cursor_pos); //line feed
	}else if(ch==0xa){
		CHAR.cursor_pos = new_line(CHAR.cursor_pos);
	}else if(ch==0x8){
		CHAR.cursor_pos = backspace(CHAR.cursor_pos);
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

void puts_str(int32_t num_hex,int32_t length){ //this fuction has some problems 
	char* ch;
	ch=ints_to_str(num_hex);
	for(int i=0;i<length;i++){
		print_char(*(ch+i));
	}
}


void print_char(uint8_t ch){
	CHAR.vram[CHAR.cursor_pos*2] = ch;
	CHAR.vram[CHAR.cursor_pos*2+1] = CHAR.color;
	CHAR.cursor_pos++;	
}
 



