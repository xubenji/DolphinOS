/* Copyright Benji 07/08/2019
 */

#include "lock.h"
#include "list.h"
#include "printk.h"
#include "thread.h"
#include "debug.h"
//#include "../com/types.h"

/* 每一个锁结构都需要一个单独的结构体，比如打印锁和内存锁还有硬盘锁不能混用
 * 起初我希望用链表来整合所有类型的锁，但是链表需要遍历，增加了系统开销，
 * 所以就采用传参数的方法来确认所有的锁 
 * 注册新锁需要在lock和unlock函数中填写对应的锁结构体 */
 
/* each lock struct need a unique struct. For example, print_lock, mem_lock and HD_lock can't be used by all threads
 * First of all I prefer to use linked list structure to save all lock structure. But it will be reduce the preformence
 * So, I use the function argument to ensure the correct type of struct. 
 * register a new lock. You need write the lock struct in lock() and unlock() */
 
static struct lock print_lock;  		//type=1
static struct lock mem_lock;	 		//type=2
static struct lock apply_page_lock;		//type=3
										//......

uint8_t type;


void semaphore_init(struct lock * psema, uint8_t value){
	psema->check_value=value;
	list_init(&psema->waiter_thread);
}

void lock_init(){
	printk("lock_init...\n");
	struct lock * plock=&print_lock;
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

void lock(uint8_t types_struct){
	switch (types_struct)
		{
		case 1: 
				type=1;
				lock_get(&print_lock);
				break;
		case 2: 
				type=2;
				lock_get(&mem_lock);
				break;
		case 3:
				type=3;
				lock_get(&apply_page_lock);
		}
	
}

void unlock(){
	switch (type)
		{
		case 1:
			lock_release(&print_lock);
			break;
		case 2:
			lock_release(&mem_lock);
			break;
		case 3:
			lock_release(&apply_page_lock);
			break;
		}
	
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
	PAUSE(psema->check_value==0);
	if(!list_empty(&psema->waiter_thread)){
		struct task_struct * thread_blocked = elem2entry(struct task_struct, general_tag, list_pop(&psema->waiter_thread));
		thread_unblock(thread_blocked);
	
	}
	psema->check_value=1;
	printk("released!!!");
}

void lock_release(struct lock * plock){
	PAUSE(plock->hold_thread==running_thread());
	plock->hold_thread=NULL;
	plock->apply_tiems=0;
	semaphore_up(plock);  
}
