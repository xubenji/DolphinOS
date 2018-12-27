#include "io_ASM.h"
#include "../com/types.h"
#include "printk.h"
#include "handler_ASM.h"
#include "pic.h"
#include "io_ASM.h"

void init_pic(){
	io_out8_ASM(PIC0_IMR,  0xff  ); /* Prohibition of all of master PIC's interupt */
	io_out8_ASM(PIC1_IMR,  0xff  ); /* Prohibition of all of slave PIC's interupt */

	io_out8_ASM(PIC0_ICW1, 0x11  ); /* we need ICW4, so many pic series connection*/
	io_out8_ASM(PIC0_ICW2, 0x20  ); /* IRQ0-7, INT 0x20~0x27 accept */
	io_out8_ASM(PIC0_ICW3, 1 << 2); /* PIC1 IRQ2 connect */
	io_out8_ASM(PIC0_ICW4, 0x01  ); /* A model, interupt complete model */

	io_out8_ASM(PIC1_ICW1, 0x11  ); /* we need ICW4, so many pic series connection*/
	io_out8_ASM(PIC1_ICW2, 0x28  ); /* IRQ8-15, INT 0x28~0x2f accept */
	io_out8_ASM(PIC1_ICW3, 2     ); /* PIC1, IRQ2 connect */
	io_out8_ASM(PIC1_ICW4, 0x01  ); /* A model, interupt complete model */

	io_out8_ASM(PIC0_IMR,  0xfc  ); /* 0xfc = 11111100. Prohibition of all of PIC's interupt except PIC1*/
	io_out8_ASM(PIC1_IMR,  0xff  ); /* 0xff = 11111111. Prohibition of all of slave PIC's interupt */
	
}

