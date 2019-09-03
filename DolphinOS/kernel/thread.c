/* copy from OS book by benji 2019/07/07
 * this is thread.c
 * function is init the thread
 */

#include "../com/types.h"
#include "memory.h"
#include "printk.h"
#include "bitmap.h"
#include "thread.h"
#include "string.h"
#include "debug.h"
#include "idt.h"
#include "list.h"
#include "process.h"

struct task_struct* main_thread;    // 主线程PCB
struct list thread_ready_list;	    // 就绪队列
struct list thread_all_list;	    // 所有任务队列
static struct list_elem* thread_tag;// 用于保存队列中的线程结点

extern void switch_to(struct task_struct* cur, struct task_struct* next);

/* get the pointer of the current thread pcb*/
/* 获取当前线程pcb指针 */
struct task_struct* running_thread() {
   uint32_t esp; 
   asm ("mov %%esp, %0" : "=g" (esp));
  /* 取esp整数部分即pcb起始地址 */
   return (struct task_struct*)(esp & 0xfffff000);
}

/* 由kernel_thread去执行function(func_arg) */
static void kernel_thread(thread_func* function, void* func_arg) {
	printk("kernel_thread\n");
	intr_enable();
	function(func_arg); 
}

/* init the stack of thread, put function to run in thread_stack */
/* 初始化线程栈thread_stack,将待执行的函数和参数放到thread_stack中相应的位置 */
void thread_create(struct task_struct* pthread, thread_func function, void* func_arg) {
	/* 先预留中断使用栈的空间,可见thread.h中定义的结构 */
	pthread->self_kstack -= sizeof(struct intr_stack);

	/* 再留出线程栈空间,可见thread.h中定义 */
	pthread->self_kstack -= sizeof(struct thread_stack);
	struct thread_stack* kthread_stack = (struct thread_stack*)pthread->self_kstack;
	kthread_stack->eip = kernel_thread;
	kthread_stack->function = function;
	kthread_stack->func_arg = func_arg;
	kthread_stack->ebp = kthread_stack->ebx = kthread_stack->esi = kthread_stack->edi = 0;
}

/* init the basic information of thread */
/* 初始化线程基本信息 */
void init_one_thread(struct task_struct* pthread, char* name, int prio) {
	memset(pthread, 0, sizeof(*pthread));
	strcpy(pthread->name, name);

	//书中原本的写法是将mian函数封装成一个线程，但是我现在已经将main函数去除，所有函数都要通过thread_start调用。
	//所以并不需要这个判断
	
	/*if (pthread == main_thread) {
		// 由于把main函数也封装成一个线程,并且它一直是运行的,故将其直接设为TASK_RUNNING 
		pthread->status = TASK_RUNNING;
	} else {
		pthread->status = TASK_READY;
	}*/

	pthread->status = TASK_READY;

	/* self_kstack是线程自己在内核态下使用的栈顶地址 */
	pthread->self_kstack = (uint32_t*)((uint32_t)pthread + PAGE_SIZE);
	pthread->priority = prio;
	pthread->ticks = prio;
	pthread->elapsed_ticks = 0;
	pthread->pgdir = NULL;
	pthread->stack_magic = 0x19870916;	
}

/* 创建一优先级为prio的线程,线程名为name,线程所执行的函数是function(func_arg) */
struct task_struct* thread_start(char* name, int prio, thread_func function, void* func_arg) {
	/* pcb都位于内核空间,包括用户进程的pcb也是在内核空间 */
	struct task_struct* thread = get_kernel_pages(1);

	
	init_one_thread(thread, name, prio);
	thread_create(thread, function, func_arg);
	/* 确保之前不在队列中 */
	PAUSE(!elem_find(&thread_ready_list, &thread->general_tag));
	
	/* 加入就绪线程队列 */
	list_append(&thread_ready_list, &thread->general_tag);

	/* 确保之前不在队列中 */
	PAUSE(!elem_find(&thread_all_list, &thread->all_list_tag));
	
	/* 加入全部线程队列 */
	list_append(&thread_all_list, &thread->all_list_tag);
	
	return thread;
}


int time=0;

/* 实现任务调度 */
void schedule() {
		
	PAUSE(intr_get_status() == INTR_OFF);

	
	
	struct task_struct* cur = running_thread(); 
	
	
	if (cur->status == TASK_RUNNING) { // 若此线程只是cpu时间片到了,将其加入到就绪队列尾
		PAUSE(!elem_find(&thread_ready_list, &cur->general_tag));
		list_append(&thread_ready_list, &cur->general_tag);
		cur->ticks = cur->priority;     // 重新将当前线程的ticks再重置为其priority;
		cur->status = TASK_READY;
	} else { 
		/* 若此线程需要某事件发生后才能继续上cpu运行,
		不需要将其加入队列,因为当前线程不在就绪队列中。*/
	}
	

//check the list of thread is empty or not.
//before that, I use the PASUE(). The result is if error coming, the machine isn't going to run.
//判断线程准备队列是否为空，之前使用PASUE宏，但是如果发生错误就不会继续运行下去

	time++;
	PAUSE(list_empty(&thread_ready_list)==false);
	if(list_empty(&thread_ready_list)==true){		
			if (time%100==0)
				{
			printk(" list is empty!!! ");
				}	
		return 0;
	}


	
	thread_tag = NULL;	  // thread_tag清空
	/* 将thread_ready_list队列中的第一个就绪线程弹出,准备将其调度上cpu. */
	thread_tag = list_pop(&thread_ready_list);  
	
	struct task_struct* next = elem2entry(struct task_struct, general_tag, thread_tag);
	next->status = TASK_RUNNING;
	put_int32(next->pgdir);
	
	
	//激活用户线程
	process_activate(next);

	
	
	switch_to(cur, next);
}

/* 线程自己把自己阻塞的函数 */
/* The thread lock itself */
void thread_block(enum task_status stat){
	printk("\nblock!!!!\n");
	PAUSE((stat == TASK_BLOCKED) || (stat == TASK_WAITING) || (stat == TASK_HANGING));
	enum intr_status old_status = intr_disable();
	struct task_struct* cur_thread = running_thread();
	cur_thread->status = stat;
	schedule();

//解除阻塞以后才能继续运行下面的函数
	intr_set_status(old_status);
}

/* 线程解除锁定 */
/* unlock the thread */
void thread_unblock(struct task_struct * pthread){
	intr_disable();
	PAUSE((pthread->status==TASK_BLOCKED)||(pthread->status==TASK_WAITING)||(pthread->status==TASK_HANGING));
	if(pthread->status != TASK_READY){
		PAUSE(!elem_find(&thread_ready_list, &pthread->general_tag));
		if(elem_find(&thread_ready_list, &pthread->general_tag)){
			PANIC("thread_unblock: blocked thread in ready_list\n");
		}
		list_push(&thread_ready_list,&pthread->general_tag);
		pthread->status=TASK_READY;
	}

	intr_enable();
}

/* 初始化线程环境 */
void thread_init(void) {
	printk("thread_init start\n");
	list_init(&thread_ready_list);
	list_init(&thread_all_list);

	//将当前main函数创建为线程 
	//操作系统真相还原书中将主函数创建为进程，但是书中main函数的pcb被保存在了一个独立的地址，
	//所以这里我将kernel_init初始化为一个线程
	//make_main_thread();
	
	printk("thread init completed\n");
}
