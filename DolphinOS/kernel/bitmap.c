#include "../com/types.h"
#include "string.h"
#include "bitmap.h"

void init_bitmap(BitMap* bitmap){
	uint32_t i=memset(bitmap->bits,0,bitmap->bm_total_len);
	printk("\nNow,We have initialized the kernel memory.");
	printk("\nBecause, 0~5MB of memory has been used.\nSo, Now, The kernel can use about ");
	puts_int32(i*8*4);
	printk("KB of free memory\n"); 
}
