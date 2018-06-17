#include "types.h"

#define CHAR_DISPLAY_ADDERSS 0X800b8000
#define LINE_MAX_CHAR 80

void print_char(uint8_t ch);
void init_display_infor();
uint16_t new_line(uint16_t cursor_pos);
uint16_t backspace(uint16_t cursor_pos);
void get_cursor_pos(uint8_t ch);
void printk(uint8_t *str);
void print_char(uint8_t ch);


struct display_char{
	int8_t *vram;
	uint16_t cursor_pos;
	int8_t color; 
};


