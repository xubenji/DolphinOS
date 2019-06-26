#include "debug.h"
#include "printk.h"
#include "idt.h"
#include "../com/types.h"

/* 打印文件名,行号,函数名,条件并使程序悬停 */
void panic_spin(char* filename,	       \
	        int line,	       \
		const char* func,      \
		const char* condition) \
{
   intr_disable();	// 因为有时候会单独调用panic_spin,所以在此处关中断。
   printk("\n\n!!!!!!ERROR!!!!!!\n");
 //  put_str("\n\n\n!!!!! error !!!!!\n");
   printk("filename:");puts_int8(filename);printk("\n");
   printk("line:0x");puts_int32(line);printk("\n");
   printk("function:");puts_int8((char*)func);printk("\n");
   printk("condition:");puts_int8((char*)condition);printk("\n");
   while(1);
}

