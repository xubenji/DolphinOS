/*(C) Olaf 2016/7 ards.c
 *read memory information
 *the memory information be save in ards, the ards struct address be define in load.asm
 *this function return a number which is memory size
 */

#include "types.h"
#include "printk.h"
#include "ards.h"

struct ards *ards;
uint32_t get_ards_infor()
{
	uint32_t memory_total_size=0;
	uint16_t ards_nr =  *((uint16_t *)ARDS_NR);
	ards = (struct ards *) ARDS_ADDR;		
	int i;
	for(i = 0; i < ards_nr; i++){
		if(ards->type == 1){
			if(ards->base_low+ards->length_low > memory_total_size){
				memory_total_size = ards->base_low+ards->length_low;
			}
		}
		ards++;
	}
	return memory_total_size;
}
