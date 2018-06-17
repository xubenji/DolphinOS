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



