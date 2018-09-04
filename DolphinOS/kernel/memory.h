#include "bitmap.h"

#define PAGE_SIZE 4096;
#define USED_MEMORY_SIZE 5242880; //5x1024x1024, 5MB memory, unit: bytes
#define MEM_BITMAP_BASE 0x90000; //bitmap memory address

typedef struct _pool {
	BitMap pool_bitmap;	 
	uint32_t phy_addr_start;	 
	uint32_t pool_size;		 
}Pool;

void init_memory();


