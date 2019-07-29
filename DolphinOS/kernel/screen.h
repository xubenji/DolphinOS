#define SCREEN_INFO_ADDR 0x00006100
#define SCREEN_MODE 800*600

struct screen_info {
	uint16_t color_digit;		
	uint32_t wide, high;	
	uint8_t *vram;				
};


void show_screen_info();


