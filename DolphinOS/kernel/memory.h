#include "bitmap.h"
#include "../com/types.h"

#define PAGE_SIZE 4096
#define USED_MEMORY_SIZE 12 //12x1024x1024, 12MB memory, unit: bytes, 
#define MEM_BITMAP_BASE 0x80502000  //bitmap memory address, 5MB+8KB.
#define TOTAL_REFRESH_MEMORY_SIZE 4190208 //4X1024X1024-4096(4kb)
#define K_HEAP_START 0x80c00000  // 0x80000000是内核从虚拟地址2G起. 0xc00000意指跨过低端12M内存,使虚拟地址在逻辑上连续
#define KERNEL_PAGE_DIR_TABLE 0x100000
#define KERNEL_PAGE_TABLE 0X101000

typedef struct _pool {
	BitMap pool_bitmap;	 
	uint32_t phy_addr_start;	 
	uint32_t pool_size;		 
}Pool;

/* 用于虚拟地址管理 */
typedef struct _virtual_addr {
/* 虚拟地址用到的位图结构，用于记录哪些虚拟地址被占用了。以页为单位。*/
   BitMap vaddr_bitmap;  //uint32_t BitMap.bm_total_len;
						 //uint8_t* BitMap.bits;
/* 管理的虚拟地址 */
   uint32_t vaddr_start;
}Virtual_Addr_BitMap;

/* 内存池标记,用于判断用哪个内存池 */
enum pool_flags {
   PF_KERNEL = 1,    // 内核内存池
   PF_USER = 2	     // 用户内存池
};

void init_memory();
void* malloc_page(enum pool_flags pf, uint32_t pg_cnt);
static void* vaddr_get(enum pool_flags pf, uint32_t pg_cnt);
static void* palloc(Pool* m_pool);
void refresh();
void* get_kernel_pages(uint32_t pg_cnt); 
uint32_t get_ards_infor();
void check_memory();



