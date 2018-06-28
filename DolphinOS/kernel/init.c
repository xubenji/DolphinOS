/*(C) 2018 Future-Technology
 *design by Olaf 2018/6
 *this is the entry of DolphinOS
 */

#include "_stack_chk_fail.h"
#include "printk.h"
#include "types.h"
#include "screen.h"
#include "asc.h"


int Kernel_Init(){
	init_display_info();
	show_screen_info();
	printk("------\n");
	int32_t num_hex=0xabcd1234;
	
	puts_int32(num_hex);
	printk("\n------\n");
	int16_t n16=0xabcd;
	puts_int16(n16);
	printk("\n------\n");
	int8_t n8=0xab;
	puts_int8(n8);
	printk("\n------\n");
	int64_t n64=0x12345678abcdabcd;
	puts_int64(n64);
	
	/*
	puts_str(num_hex,8);
	uint16_t num=0x1234;
	char ch[32];
	char p[32];
	int16_to_str(num,ch);
	for(int i=0;i<4;i++){
		print_char(*(ch+i));
	}
	char chs[32];
	printk("\n");
	int64_t a=0x12345678abcdabcd;
	int64_to_str(a,chs);
	for(int i=0;i<16;i++){
		print_char(*(chs+i));
	}
	
	char* qq=&a;
	int i=0;
	while(qq[i]!=0){
	i++;
	}
	
	int q=sizeof(*qq);
	printk("\n");
	puts_str(i,8);
	*/
	
	while(1){
	}
}
