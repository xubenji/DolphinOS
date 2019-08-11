/* Copyright Benji 07/08/2019
 */

//#include "idt.h"
#include "lock.h"
#include "list.h"
#include "printk.h"
#include "thread.h"
#include "debug.h"
//#include "../com/types.h"

static struct lock lock_control;

void semaphore_init(struct lock * psema, uint8_t value){
	psema->check_value=value;
	list_init(&psema->waiter_thread);
}

void console_lock(){
	lock_init(&lock_control);
}
void lock_init(){
	printk("lock_init...\n");
	struct lock * plock=&lock_control;
	plock->hold_thread = NULL;
	plock->apply_tiems = 0;
	semaphore_init(plock,1);    
}

/* 对信号量进行操作 */
/* operation of semaphore */
void semaphore_down(struct lock * psema){
	 intr_disable();            //close the interruption
	
	 while (psema->check_value==0)
		 {
			PAUSE(!elem_find(&psema->waiter_thread, &running_thread()->general_tag));

			if(elem_find(&psema->waiter_thread, &running_thread()->general_tag)){
				PANIC("functin semaphore_down:thread blocked has been in waiters_list\n");
			}
			list_append(&psema->waiter_thread,&running_thread()->general_tag);
			thread_block(TASK_BLOCKED);		 
		 }

//获得锁
	 psema->check_value=0;
	 printk("<<<<<");
	 intr_enable();				//open the interruption
}

void lock(){
	lock_get(&lock_control);
}

void unlock(){
	lock_release(&lock_control);
}

//线程通过这个函数获得锁
void lock_get(struct lock * plock){
		
		if(plock->hold_thread == running_thread()){
			plock->apply_tiems=1;
		}else{
		    semaphore_down(plock);
			plock->hold_thread=running_thread();
			PAUSE(plock->apply_tiems==0);
			plock->apply_tiems=1;
		}
}

void semaphore_up(struct lock * psema){
	intr_disable();
	PAUSE(psema->check_value==0);
	if(!list_empty(&psema->waiter_thread)){
		struct task_struct * thread_blocked = elem2entry(struct task_struct, general_tag, list_pop(&psema->waiter_thread));
		thread_unblock(thread_blocked);
	
	}
	psema->check_value=1;
	printk("released!!!");
	intr_enable();
}

void lock_release(struct lock * plock){
	PAUSE(plock->hold_thread==running_thread());
	plock->hold_thread=NULL;
	plock->apply_tiems=0;
	semaphore_up(plock);  
}
