#include "debug.h"
#include "printk.h"
#include "idt.h"

/* 打印文件名,行号,函数名,条件并使程序悬停 */
/* print the filename, line, function name. stop the program */
void panic_spin(char* filename,	       \
	        int line,	       \
		const char* func,      \
		const char* condition) \
{
   intr_disable();	                           // 因为有时候会单独调用panic_spin,所以在此处关中断。
   printk("\n\n!!!!!!ERROR!!!!!!\n");

   printk(filename);
   printk("\nline:");
   put_dec_uint32(line);
   printk("\nfunction:");
   printk((char*)func);
   printk("\ncondition:");
   printk((char*)condition);

   while(1);
}

