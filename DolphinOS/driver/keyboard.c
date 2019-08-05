#include "../kernel/printk.h"

void keyborad_map(uint8_t ch){
	switch (ch)
		{
			
			case 0x02: print_keyboard("1");
			break;
			case 0x03: print_keyboard("2");
			break;
			case 0x04: print_keyboard("3");
			break;
			case 0x05: print_keyboard("4");
			break;
			case 0x06: print_keyboard("5");
			break;
			case 0x07: print_keyboard("6");
			break;
			case 0x08: print_keyboard("7");
			break;
			case 0x09: print_keyboard("8");
			break;
			case 0x0a: print_keyboard("9");
			break;
			case 0x0b: print_keyboard("0");
			break;
			case 0x0c: print_keyboard("-");
			break;
			case 0x0d: print_keyboard("=");
			break;
			case 0x0e: get_cursor_pos(0x8);
			break;
			case 0x10: print_keyboard("q");
			break;
			case 0x11: print_keyboard("w");
			break;
			case 0x12: print_keyboard("e");
			break;
			case 0x13: print_keyboard("r");
			break;
			case 0x14: print_keyboard("t");
			break;
			case 0x15: print_keyboard("y");
			break;
			case 0x16: print_keyboard("u");
			break;
			case 0x17: print_keyboard("i");
			break;
			case 0x18: print_keyboard("o");
			break;
			case 0x19: print_keyboard("p");
			break;
			case 0x1a: print_keyboard("[");
			break;
			case 0x1b: print_keyboard("]");
			break;
			case 0x1c: print_keyboard(" ");
			break;
			case 0x1e: print_keyboard("a");
			break;
			case 0x1f: print_keyboard("s");
			break;
			case 0x20: print_keyboard("d");
			break;
			case 0x21: print_keyboard("f");
			break;
			case 0x22: print_keyboard("g");
			break;
			case 0x23: print_keyboard("h");
			break;
			case 0x24: print_keyboard("j");
			break;
			case 0x25: print_keyboard("k");
			break;
			case 0x26: print_keyboard("l");
			break;
			case 0x27: print_keyboard(";");
			break;
			case 0x28: print_keyboard("'");
			break;
			case 0x2c: print_keyboard("z");
			break;
			case 0x2d: print_keyboard("x");
			break;
			case 0x2e: print_keyboard("c");
			break;
			case 0x2f: print_keyboard("v");
			break;
			case 0x30: print_keyboard("b");
			break;
			case 0x31: print_keyboard("n");
			break;
			case 0x32: print_keyboard("m");
			break;
			case 0x33: print_keyboard(",");
			break;
			case 0x34: print_keyboard(".");
			break;
			case 0x35: print_keyboard("/");
			break;
			case 0x9c: print_keyboard("\n>:");
			break;
			case 0x39: print_keyboard(" ");
			break;

		}
}

void print_keyboard(uint8_t *     str){

	while (*str!=0x00)
		{
		get_cursor_pos(*str);
		str++;
		}
}
