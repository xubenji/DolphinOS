#ifndef __PROCESS_H
#define __PROCESS_H

void start_process(void* filename);

#define default_prio 31
#define USER_STACK3_VADDR  (0x80000000 - 0x10000)
#define USER_VADDR_START 0x8048000

void process_execute(void* filename, char* name);
void start_process(void* filename_);
//void process_activate(struct task_struct* p_thread);
//void page_dir_activate(struct task_struct* p_thread);
uint32_t* create_page_dir(void);
//void create_user_vaddr_bitmap(struct task_struct* user_prog);
#endif


