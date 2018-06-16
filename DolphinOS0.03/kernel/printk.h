#include "types.h"

#define CHAR_DISPLAY_ADDERSS 0X800b8000

void print_char(uint8_t ch);
void show_infor();

struct display_char{
	int8_t *vram;
	uint16_t cursor_pos;
	int8_t color; 
};


