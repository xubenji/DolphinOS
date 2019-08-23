#ifndef _TSS_H
#define _TSS_H
//void update_tss_esp(struct task_struct* pthread);
void init_tss();
static Gdt_Desc make_gdt_desc(uint32_t* desc_addr, uint32_t limit, uint8_t attr_low, uint8_t attr_high);
#endif