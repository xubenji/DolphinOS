#include "types.h"
#include "../kernel/printk.h"

uint64_t pow(uint64_t num, uint64_t power){
	uint64_t sum=num;
	for(int i=0;i<(power-1);i++){
	sum=sum*num;
	}
	return sum;
}
