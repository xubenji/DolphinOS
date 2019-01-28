#include "../com/types.h"

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
