#include "../kernel/printk.h"

void keyborad_map(uint8_t ch){
	switch (ch)
		{
			case 0x1e: printk("A");
			break;
		}
}
