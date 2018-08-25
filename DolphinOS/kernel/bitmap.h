#ifndef __LIB_KERNEL_BITMAP_H
#define __LIB_KERNEL_BITMAP_H
#include "types.h"
#define BITMAP_MASK 1

typedef struct _bitmap{
	uint32_t bm_total_len;
	uint8_t* bits;
}BitMap;
#endif

