#include "types.h"

#define ARDS_ADDR 0x80006004
#define ARDS_NR   0x80006000

struct ards
{
	uint32_t base_low;
	uint32_t base_high;
	uint32_t length_low;
	uint32_t length_high;			
	uint32_t type;
};

extern struct ards *ards;
uint32_t get_ards_infor();
