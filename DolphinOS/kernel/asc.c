//this file is used to convert int to string
#include "../com/types.h"
#include "asc.h"

void int32_to_str(uint32_t num_hex,char* ch){ //convert hex number to string 
	char* p=&num_hex;
	for(int i=0;i<4;i++){
	ch[7-2*i]=(int8_t)number_to_char((p[i]&0x0f));	
	ch[6-2*i]=(int8_t)number_to_char(((p[i]&0xf0)>>4));	
	}
}

void int16_to_str(uint16_t num_hex,char* ch){
	char* p=&num_hex;
	for(int i=0;i<2;i++){
		ch[3-2*i]=(int8_t)number_to_char((p[i]&0x0f));	
		ch[2-2*i]=(int8_t)number_to_char(((p[i]&0xf0)>>4));	
	}
}

void int8_to_str(uint8_t num_hex,char* ch){
	char* p=&num_hex;
	ch[1]=(int8_t)number_to_char((p[0]&0x0f));	
	ch[0]=(int8_t)number_to_char(((p[0]&0xf0)>>4));	
}

void int64_to_str(uint64_t num_hex,char* ch){
	char* p=&num_hex;
	for(int i=0;i<8;i++){
		ch[15-2*i]=(int8_t)number_to_char((p[i]&0x0f));	
		ch[14-2*i]=(int8_t)number_to_char(((p[i]&0xf0)>>4));	
	}
}

int8_t number_to_char(int8_t num){
	if(num>=0&&num<=9){
		num=num+0x30;
		return num;
	}else if(num>0x09&&num<=0x0f){
		num=num+0x57;
		return num;
	}else{
		num=0;
		return num;
	}
}
	
	

