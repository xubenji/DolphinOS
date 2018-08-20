/*init the memory, design the physical & virtual memory bitmap
 *design a function which is used to convert virtual memory address to phsical memory address
 *prepare for Operating System paging
 *prepare for malloc function
 */
#include "types.h"
#include "memory.h"
#include "printk.h"
//#include "bitmap.h"

void init_memory(){
	uint32_t memory_total_size;
	memory_total_size=get_ards_infor();
	uint32_t pages=memory_total_size/PAGE_SIZE;
	printk("memory init......\n");
}
