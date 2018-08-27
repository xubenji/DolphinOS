/*(C) Olaf 25/8/2018 memory.c
 *init the memory, design the physical & virtual memory bitmap
 *design a function which is used to convert virtual memory address to phsical memory address
 *prepare for Operating System paging
 *prepare for malloc function
 */

#include "../com/types.h"
#include "memory.h"
#include "printk.h"
#include "bitmap.h"

Pool kernel_pool, user_pool;

/*I don't know the memory management of linux, So I manage the memory by myself.
 *It is very important file in kernel
 *You can see in DolphinOS, 0~5mb of memory is not avaiable for user.
 *Why? because 0~1mb of memory is occupied by kernel and 1~5mb of memory is occupied by paging & paging directoy.
 *memory_total_size means that the memory of machine.
 *unit of 5242880 is 'bytes'. 5x1024x1024 bytes=5mb.
 */

void init_memory(){
	uint32_t memory_total_size;
	memory_total_size=get_ards_infor();
	uint32_t total_pages=memory_total_size/PAGE_SIZE;
	uint32_t used_phy_pages=5242880/PAGE_SIZE;
	uint32_t free_pages=total_pages-used_phy_pages;
	uint32_t kernel_pages=free_pages/2;
	uint32_t kbm_length=kernel_pages/8;
	uint32_t kp_start_address=USED_MEMORY_SIZE;
	
	kernel_pool.phy_addr_start=kp_start_address;
	kernel_pool.pool_bitmap.bits = (void*)MEM_BITMAP_BASE;
	kernel_pool.pool_size = kernel_pages * PAGE_SIZE;
	kernel_pool.pool_bitmap.bm_total_len = kbm_length;
	init_bitmap(&kernel_pool.pool_bitmap);
	
	printk("memory init......\n");
}
