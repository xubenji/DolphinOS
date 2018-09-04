/*(C) Olaf 8/2018 ards.c
 *read memory information
 *the memory information is saved in ards data structure, the ards address be define in load.asm
 *this function return a number which is memory size
 */

#include "../com/types.h"
#include "printk.h"
#include "ards.h"

pArds ards1;
uint32_t get_ards_infor()
{
	uint32_t memory_total_size=0;
	uint16_t ards_nr =  *((uint16_t *)ARDS_NR);
	ards1 = (pArds)ARDS_ADDR;		
	int i;
	for(i = 0; i < ards_nr; i++){
		if(ards1->type == 1){
			if(ards1->base_low+ards1->length_low > memory_total_size){
				memory_total_size = ards1->base_low+ards1->length_low;
			}
		}
		ards1++;
	}
	return memory_total_size;
}
