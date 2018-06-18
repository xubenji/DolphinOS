//this file is used to convert int to string
#include "types.h"
#include "asc.h"


int8_P int_to_str(int8_P str, int32_t num)
{
	int8_P	p = str;
	int8_t	ch;
	int32_t	i;
	int32_t	flag = false;
	
	*p++ = '0';
	*p++ = 'x';
	
	if(num == 0){
		*p++ = '0';
	}
	else{	
		for(i=28;i>=0;i-=4){		
			ch = (num >> i) & 0xF;	
			
			ch += '0';			
			if(ch > '9'){		
				ch += 7;		
			}
			*p++ = ch;			
			
		}
	}
	*p = 0;							
	return str;
}

char* ints_to_str(uint32_t num_hex){ //convert hex number to string 
	char* p;
	char* ch;
	char* str;
	p=&num_hex;
	for(int i=0;i<4;i++){
	ch[2*(i)]=p[i]&0x0f;
	ch[1+2*(i)]=(p[i]&0xf0)>>4;
	ch[2*(i)]=(int8_t)number_to_char(ch[2*(i)]);	
	ch[1+2*(i)]=(int8_t)number_to_char(ch[1+2*(i)]);	
	}
	for(int j=0;j<8;j++){
	str[j]=ch[7-j];
	}
	return str;
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
	
	

