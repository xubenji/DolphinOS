/* Copyright Benji 07/08/2019
 */

//#include "idt.h"
#include "lock.h"
#include "list.h"
#include "printk.h"
//#include "../com/types.h"

void semaphore_init(){
	printk("seampgore\n");
	struct semaphore* psema =NULL;
	psema->value=0;
}



