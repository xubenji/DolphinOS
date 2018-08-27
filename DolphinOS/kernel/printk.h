#include "../com/types.h"

#define CHAR_DISPLAY_ADDERSS 0X800b8000
#define LINE_MAX_CHAR 80

void __stack_chk_fail();
void puts_int64(int64_t num_hex);
void puts_int32(int32_t num_hex);
void puts_int16(int16_t num_hex);
void puts_int8(int8_t num_hex);

void print_char(uint8_t ch);
void init_display_info();
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


