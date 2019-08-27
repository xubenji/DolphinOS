#include "../com/types.h"
#include "debug.h"
#include "printk.h"

uint32_t memset(void* dst_, uint8_t value, uint32_t size) {
   uint8_t* dst = (uint8_t*)dst_;
   uint32_t i=0;
   while (size-- > 0){
	   i++;
      *dst++ = value;
   }
   return i;
}

/* 将字符串从src_复制到dst_ */
/* copy src to dst*/
char* strcpy(char* dst_, const char* src_) {
   char* r = dst_;		       // 用来返回目的字符串起始地址
   while((*dst_++ = *src_++));
   return r;
}

/* 将src_起始的size个字节复制到dst_ */
void memcpy(void* dst_, const void* src_, uint32_t size) {
   printk("memcpy");

  // PAUSE(dst_ != NULL && src_ != NULL);
   uint8_t* dst = dst_;
   const uint8_t* src = src_;
  
   while (size-- > 0){
      *dst++ = *src++;
	  put_int32(*dst);
   	}
}

