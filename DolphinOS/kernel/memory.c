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
#include "lock.h"
#include "thread.h"
#include "debug.h"

/*I am not familiar the memory management of linux, So I manage the memory by myself.
 *It is very important file in kernel
 *You can see in DolphinOS, 0~12mb of memory is not avaiable for user.
 *Why? because 0~1mb of memory is occupied by kernel, and 1~5mb of memory is occupied by paging & paging directoy.
 *5~8MB are free memory space. I will make kernel program to use this memory(5~8MB). 8~12mb is vram.
 *memory_total_size means that the memory of machine.
 *unit of USED_MEMORY_SIZE is 'bytes'. 12x1024x1024 bytes=12mb.
 */

/*我并不熟悉Linux系统的内存管理，所以这套内存管理是自己创建的
 *对于系统内核来说这是一个非常重要的文件
 *对于用户空间来说，0~12mb是无法使用的
 *因为0~1mb被内核占领，1~5mb被页表和页目录表占领
 *5~8mb是可以使用的，但是未来我会添加一些内核程序在这段内存(5~8MB)，8~12mb是vram。
 *memory_total_size是您的机器内存的总大小
 *USED_MEMORY_SIZE的单位是bytes，12x1024x1024 bytes=12mb
 */

Pool kernel_pool, user_pool;
Virtual_Addr_BitMap kernel_vaddr;

void init_memory(){
	
	refresh();
	               
	uint64_t memory_total_size;
	memory_total_size=get_ards_infor();
	uint64_t total_pages=memory_total_size/PAGE_SIZE;

	//used_phy_pages是已经使用了的页的数量
	uint64_t used_memory_size=USED_MEMORY_SIZE*1024*1024;
	uint64_t used_phy_pages=used_memory_size/PAGE_SIZE;

	//free_pages是可以使用的页的数量
	uint64_t free_pages=total_pages-used_phy_pages;

	//put_int32(free_pages*4096);
	uint64_t kernel_pages=free_pages/2;
	uint64_t kbm_length=kernel_pages/8;
	uint64_t kp_start_address=used_memory_size;
	uint64_t ubm_length=(free_pages-kernel_pages)/8;

	/*set the kernel pool bit map*/
	/*设置内核内存位图*/
	kernel_pool.phy_addr_start=kp_start_address;
	kernel_pool.pool_bitmap.bits = (void*)MEM_BITMAP_BASE;	
	kernel_pool.pool_size = kernel_pages * PAGE_SIZE;
	kernel_pool.pool_bitmap.bm_total_len = kbm_length;  //内核空间的大小

	/*set the user pool bit map */
	/*设置用户内存位图 */
	user_pool.pool_bitmap.bm_total_len = ubm_length;	//用户空间的大小
	user_pool.pool_bitmap.bits=(void*)(kernel_pool.pool_bitmap.bits+kbm_length);
	user_pool.phy_addr_start=kp_start_address+kernel_pages*PAGE_SIZE;
	user_pool.pool_size=kernel_pages*PAGE_SIZE; //因为用户空间和内核空间的大小是一样的，所以这里使用kernel_pages是可以的
												//because the user space as well as the kernel space, we use the kernel_pages.
	

/*
	printk("  user bitmap start:");
	put_int32(user_pool.pool_bitmap.bits); */
	
	init_bitmap(&kernel_pool.pool_bitmap);
	
	/* this is bitmap of kernel virtual address, the array up to real machine physical address.
	 * 下面初始化内核虚拟地址的位图,按实际物理内存大小生成数组。
	 */
	kernel_vaddr.vaddr_bitmap.bm_total_len = kbm_length;      // 用于维护内核堆的虚拟地址,所以要和内核内存池大小一致
	
	/* 位图的数组指向一块未使用的内存,目前定位在内核内存池和用户内存池之外*/
	kernel_vaddr.vaddr_bitmap.bits = (void*)(kernel_pool.pool_bitmap.bits + kbm_length + ubm_length);

	//位图管理的虚拟地址，因为0~12mb被设定为无法使用，所以K_HEAP_START是2GB+12MB;
	kernel_vaddr.vaddr_start=K_HEAP_START;

	
	printk("memory init......\n");
	
	//BitMap* bm = &kernel_vaddr.vaddr_bitmap;
	//bm->bits[0]=0xff;		
	//char * p=0x880000;
	//*p=1;
	
	enum pool_flags pk=PF_KERNEL;
	
//apply three pages memory in kernel pool
	//malloc_page(pk,2);
	//malloc_page(pk,1);
	get_kernel_pages(4000);
	//get_user_pages(4000);
//printk("finish");
//int * p=0x83100000;
//*p=1;
/*	Pool* mp = &kernel_pool;
	BitMap* mt = &mp->pool_bitmap;
	mt->bits[0]=0;
	malloc_page(pk,2);
	char* p = 0x80c02001;
	*p=0x00;*/

	
}

/*Allocated pg_cnt pages, if success, return start of virtual address, or retuen NULL 
 *分配pg_cnt个页空间,成功则返回起始虚拟地址,失败时返回NULL */

void* malloc_page(enum pool_flags pf, uint32_t pg_cnt) {
/***********   malloc_page include three steps ************
	  1. Using vaddr_get() to apply virtual address in virtual memory pool
	  2. Using palloc() to apply real physical address in physical pool
	  3. Using link_vir_phy() to created a mapping between virtual address and real physical address.
***************************************************************/

/***********   malloc_page的原理是三个动作的合成:   ************
      1通过vaddr_get在虚拟内存池中申请虚拟地址
      2通过palloc在物理内存池中申请物理页
      3通过link_vir_phy将以上得到的虚拟地址和物理地址在页表中完成映射
***************************************************************/

   void* vaddr_start = vaddr_get(pf, pg_cnt);
   if (vaddr_start == NULL) {
      return NULL;
   }

   uint32_t vaddr = (uint32_t)vaddr_start;
   
  // printk("\nkernel_pool_adder_vir_:");

 //  put_int32(vaddr );

/*************************************************************************************
   You need to declare unsigned integer variables When you using the shift operation.
**************************************************************************************/
 
    /*unsigned int * p=&vaddr;
	*p=(10<<*p)>>22;
	unsigned short q=0x8080;
	q=q>>6;
	put_int16(q);
	printk("_:");
	put_int16(*p);
	put_dec_uint32(*p);*/
   
   uint32_t cnt = pg_cnt;
   Pool* mem_pool = pf & PF_KERNEL ? &kernel_pool : &user_pool;
   
   /* 因为虚拟地址是连续的,但物理地址可以是不连续的,所以逐个做映射*/
   while (cnt-- > 0) {
	   
/* 在m_pool指向的物理内存池中分配1个物理页,
 * 成功则返回页框的物理地址,失败则返回NULL */
      void* page_phyaddr = palloc(mem_pool);

	 printk("kernel_adder_phy:");
	  put_int32(page_phyaddr);

	 
      if (page_phyaddr == NULL) {  // 失败时要将曾经已申请的虚拟地址和物理页全部回滚，在将来完成内存回收时再补充
		return NULL;
      }
	 link_vir_phy(pf, vaddr, page_phyaddr, KERNEL_PAGE_DIR_TABLE, KERNEL_PAGE_TABLE);
	 vaddr += PAGE_SIZE;	// 下一个虚拟页
   }
   return vaddr_start;
}

/*将虚拟地址和物理地址对应起来
 *connection the virtual address to physical address*/
void link_vir_phy(enum pool_flags flags, uint32_t viraddr, uint32_t phyaddr, uint32_t pdt_addr_phy, uint32_t pd_addr_phy){

/*这部分就是将需要用到的页表地址写入到页目录表的表项当中
 *write address of page table to page direct table*/
	uint32_t amount_page_dir = viraddr>>22;
	uint32_t* local_in_pdt_addr = pdt_addr_phy+amount_page_dir*4;	
	*local_in_pdt_addr=pd_addr_phy+amount_page_dir*PAGE_SIZE+0x07;

/*在页表中找到对应的表项
 *fine page table entry in page table*/
	uint32_t p = viraddr<<10;
	uint32_t* local_in_pd_addr = pd_addr_phy + amount_page_dir*PAGE_SIZE +(p>>22)*4;
	
/*将真实的物理地址写入对应的页表
 *write physical address in page table*/
	*local_in_pd_addr=phyaddr+0x07;
	

}

//输入一个虚拟地址，输出一个真实的物理地址
//input a virtuall address, output a real address.
uint32_t get_phy_addr(uint32_t vaddr){
	uint32_t* high = (vaddr>>22)*4+KERNEL_PAGE_DIR_TABLE;
	printk("dir:");
	put_int32(high);
	printk(" ");
	put_int32(*high&0xfffff000);
	uint32_t* middle =((vaddr<<10)>>22)*4+(*high&0xfffff000);
	printk("table:");
	uint32_t p = ((vaddr<<10)>>22)*4;
	//put_int32(p);
	put_int32(middle);
	printk(" ");
	put_int32(*middle&0xfffff000);
	uint32_t phy_addr=(*middle&0xfffff000)+((vaddr<<20)>>20);  //不知道为什么vaddr&&0xfff会出错
	
	return phy_addr;
}


/* 在pf表示的虚拟内存池中申请pg_cnt个虚拟页,
 * 成功则返回虚拟页的起始地址, 失败则返回NULL */
static void* vaddr_get(enum pool_flags pf, uint32_t pg_cnt) {
   int vaddr_start = 0, bit_idx_start = -1;
   uint32_t cnt = 0;
   if (pf == PF_KERNEL) {
   	  //内核内存池
   	  //kernel pool
      bit_idx_start  = bitmap_scan(&kernel_vaddr.vaddr_bitmap, pg_cnt);
      if (bit_idx_start == -1) {
	 return NULL;
      }
      while(cnt < pg_cnt) {
	 bitmap_set(&kernel_vaddr.vaddr_bitmap, bit_idx_start + cnt++, 1);
      }
      vaddr_start = kernel_vaddr.vaddr_start + bit_idx_start * PAGE_SIZE;
   } else {	
   	//用户内存池
   	//user pool
   	struct task_struct * cur=running_thread();
	bit_idx_start=bitmap_scan(&cur->userprog_vaddr.vaddr_bitmap, pg_cnt);
	if (bit_idx_start==-1)
		{
		return NULL;
		}
		while (cnt<pg_cnt)
			{
			bitmap_set(&cur->userprog_vaddr.vaddr_bitmap, bit_idx_start+cnt++, 1);
			}
			vaddr_start=cur->userprog_vaddr.vaddr_start+bit_idx_start*PAGE_SIZE;

			PAUSE((uint32_t)vaddr_start<(VIRTUAL_START_ADDER-PAGE_SIZE));
	
   }
   
   // printk(" $ ");
   return (void*)vaddr_start;
}

/* 在m_pool指向的物理内存池中分配1个物理页,
 * 成功则返回页框的物理地址,失败则返回NULL */
static void* palloc(Pool* m_pool) {
   /* 扫描或设置位图要保证原子操作 */
   int bit_idx = bitmap_scan(&m_pool->pool_bitmap, 1);    // 找一个物理页面
   if (bit_idx == -1 ) {
      return NULL;
   }
   bitmap_set(&m_pool->pool_bitmap, bit_idx, 1);	// 将此位bit_idx置1
   uint32_t page_phyaddr = ((bit_idx * PAGE_SIZE) + m_pool->phy_addr_start); //这里是位图下标乘以4KB，然后加上物理内存池的起始地址
   																			  //如果说这里传进来的是内核物理内存池，那么就是内核物理内存池的起始地址，如果是用户的那么就是用户物理内存池的起始地址
   return (void*)page_phyaddr;
}

//刷新4kb内存，因为不刷新内存就会出现乱码，未来bitmap的地址将会加载到这里
void refresh(){

	char* rf=MEM_BITMAP_BASE+4674;
	//printk("ERROR:");
	//put_int32(MEM_BITMAP_BASE+4674);
	rf[0]=0x00;
	
	char* rf2=MEM_BITMAP_BASE+4675;
	for(uint32_t j=0;j<500;j++){
		rf2[j]=0x00;
	}
}

/* 从内核物理内存池中申请pg_cnt页内存,成功则返回其虚拟地址,失败则返回NULL */
void* get_kernel_pages(uint32_t pg_cnt) {
   void* vaddr =  malloc_page(PF_KERNEL, pg_cnt);
   if (vaddr != NULL) {	   // 若分配的地址不为空,将页框清0后返回
      memset(vaddr, 0, pg_cnt * PAGE_SIZE);
   }
   printk(" ");
   return vaddr;
}

//与之对应，申请用户空间内存
void* get_user_pages(uint32_t pg_cnt){
//	lock(3);
	void* vaddr=malloc_page(PF_USER,pg_cnt);
	memset(vaddr, 0, pg_cnt*PAGE_SIZE);
	printk(" ");
//	unlock();  
	return vaddr;
}

void* get_cert_pages(enum pool_flags pf, uint32_t vaddr){
	Pool* mem_pool=pf&PF_KERNEL? &kernel_pool:&user_pool;
	lock(3);  //struct apply_mem_lock

	//现将虚拟地址位图置为1
	struct task_struct* cur = running_thread();
	int32_t bit_idx=-1;

	if(cur->pgdir!=NULL&&pf==PF_KERNEL){
	//如果内核线程申请内核，就能修改kernel_vaddr
	bit_idx=(vaddr - cur->userprog_vaddr.vaddr_start)/PAGE_SIZE;
	PAUSE(bit_idx>0);
	bitmap_set(&cur->userprog_vaddr.vaddr_bitmap, bit_idx, 1);
	}else if(cur->pgdir==NULL&&pf==PF_KERNEL){

	bit_idx=(vaddr-kernel_vaddr.vaddr_start)/PAGE_SIZE;
	PAUSE(bit_idx>0);
	bitmap_set(&kernel_vaddr.vaddr_bitmap, bit_idx,1 );
	}else{
	PANIC("get_cert_page:not allow kernel alloc userspace or user alloc kernelspace bu get_cert_page");
	}
	void * page_phyaddr=palloc(mem_pool);
	if(page_phyaddr==NULL){
		return NULL;
	}
	//link_vir_phy(enum pool_flags flags, uint32_t viraddr, uint32_t phyaddr, uint32_t pdt_addr_phy, uint32_t pd_addr_phy);
	
}


void check_memory(){
	uint32_t memory=get_ards_infor();
	uint32_t mem_mb=memory/(1024*1024);
	printk("your machine's memory size:");
	put_dec_uint32(mem_mb);
	printk("MB"); 
	
	uint32_t gdt_addr = _asm_read_gdt();
	printk(" gdt_addr:");
	put_int32(gdt_addr);
	printk("\n");
}

