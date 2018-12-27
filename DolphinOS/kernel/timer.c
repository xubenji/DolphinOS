#include "io_ASM.h"
#include "../com/types.h"
#include "printk.h"
#include "handler_ASM.h"
#include "pic.h"
#include "io_ASM.h"
#include "timer.h"

/*11932=0x2e9c, when we set the value equal to 11932.
 *The frequency is 100Hz.
 */
void init_timer(){
	//set PIT
	io_out8_ASM(PIT_CTRL, 0x34);
	io_out8_ASM(PIT_CNT0, 0x9c);
	io_out8_ASM(PIT_CNT0, 0x2e);
}

