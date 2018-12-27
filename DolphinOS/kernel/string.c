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
