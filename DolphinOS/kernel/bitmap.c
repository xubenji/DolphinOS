/*(C) Olaf 27/8/2018 bitmap.c
 *At the beginning of the project, i want to abandon the bitmap, but i can't find a good way to manage the memory.
 *So, i still use the bitmap data structure.
 */

#include "../com/types.h"
#include "string.h"
#include "bitmap.h"
#include "memory.h"
#include "debug.h"

void init_bitmap(BitMap* bitmap){
	uint32_t i=memset(bitmap->bits,0,bitmap->bm_total_len);
	printk("\nNow,We have initialized the kernel memory.");
	printk("\nBecause, 0~");
	uint32_t ms=USED_MEMORY_SIZE; 
	put_dec_uint32(ms);
    printk("MB of memory has been used.\nSo, Now, The kernel program can use about: ");
	put_dec_uint32(i*8*4);
	printk("KB free memory\n"); 
	
}

/* 在位图中申请连续cnt个位,成功则返回其起始位下标，失败返回-1 
 *apply sucessive cnt bits, if success, return the location of that bit or return -1*/
int bitmap_scan(BitMap* btmp, uint32_t cnt) {
   uint32_t idx_byte = 0;	 // 用于记录空闲位所在的字节
/* 先逐字节比较,蛮力法 */
 
   while (( 0xff == btmp->bits[idx_byte]) && (idx_byte < btmp->bm_total_len)) {
/* 1表示该位已分配,所以若为0xff,则表示该字节内已无空闲位,向下一字节继续找 */ 

      idx_byte++;
   }

   if (idx_byte == btmp->bm_total_len) {  // 若该内存池找不到可用空间		
      return -1;
   }

 /* 若在位图数组范围内的某字节内找到了空闲位，
  * 在该字节内逐位比对,返回空闲位的索引。*/
   int idx_bit = 0;
 /* 和btmp->bits[idx_byte]这个字节逐位对比 */
   while ((uint8_t)(BITMAP_MASK << idx_bit) & btmp->bits[idx_byte]) { 
	  //  printk("s");
	 idx_bit++;
   }
	 
   int bit_idx_start = idx_byte * 8 + idx_bit;    // 空闲位在位图内的下标
   if (cnt == 1) {

      return bit_idx_start;
   }

   uint32_t bit_left = (btmp->bm_total_len * 8 - bit_idx_start);   // 记录还有多少位可以判断
   uint32_t next_bit = bit_idx_start + 1;
   uint32_t count = 1;	      // 用于记录找到的空闲位的个数

   bit_idx_start = -1;	      // 先将其置为-1,若找不到连续的位就直接返回
   while (bit_left-- > 0) {
      if (!(bitmap_scan_test(btmp, next_bit))) {	 // 若next_bit为0
	 count++;
      } else {
	 count = 0;
      }
      if (count == cnt) {	    // 若找到连续的cnt个空位
	 bit_idx_start = next_bit - cnt + 1;
	 break;
      }
      next_bit++;          
   }
   return bit_idx_start;
}

/* 判断bit_idx位是否为1,若为1则返回true，否则返回false 
 * check whether the bit_idx th is one, if it is 1, return true or return false.*/
bool bitmap_scan_test(BitMap* btmp, uint32_t bit_idx) {
   uint32_t byte_idx = bit_idx / 8;    // 向下取整用于索引数组下标
   uint32_t bit_odd  = bit_idx % 8;    // 取余用于索引数组内的位
   return (btmp->bits[byte_idx] & (BITMAP_MASK << bit_odd));
}

/* 将位图btmp的bit_idx位设置为value */
void bitmap_set(BitMap* btmp, uint32_t bit_idx, int8_t value) {
   PAUSE((value == 0) || (value == 1));
   uint32_t byte_idx = bit_idx / 8;    // 向下取整用于索引数组下标
   uint32_t bit_odd  = bit_idx % 8;    // 取余用于索引数组内的位

/* 一般都会用个0x1这样的数对字节中的位操作,
 * 将1任意移动后再取反,或者先取反再移位,可用来对位置0操作。*/
   if (value) {		      // 如果value为1
      btmp->bits[byte_idx] |= (BITMAP_MASK << bit_odd);
   } else {		      // 若为0
      btmp->bits[byte_idx] &= ~(BITMAP_MASK << bit_odd);
   }
}
