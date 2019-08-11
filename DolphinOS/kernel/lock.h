#include "../com/types.h"
#include "list.h"

/* struct of lock */
struct lock{
	struct task_struct * hold_thread;
	uint32_t apply_tiems;
	
	//semaphore
	//信号量
	uint8_t check_value;
	struct list waiter_thread;
	
};


void semaphore_init(struct lock * psema, uint8_t value);
void lock_init();
void semaphore_up(struct lock * psema);
void lock_get(struct lock * plock);
void semaphore_down(struct lock * psema);
void lock_release(struct lock * plock);
void lock(uint8_t types_struct);
void unlock();


