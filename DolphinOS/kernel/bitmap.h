#ifndef __LIB_KERNEL_BITMAP_H
#define __LIB_KERNEL_BITMAP_H
#include "../com/types.h"
#define BITMAP_MASK 1

typedef struct _bitmap{
	uint32_t bm_total_len;
	uint8_t* bits;
}BitMap;

int bitmap_scan(BitMap* btmp, uint32_t cnt);
bool bitmap_scan_test(BitMap* btmp, uint32_t bit_idx);
void bitmap_set(BitMap* btmp, uint32_t bit_idx, int8_t value);

#endif

