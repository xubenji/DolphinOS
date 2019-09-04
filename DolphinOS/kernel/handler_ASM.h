extern void _asm_inthandler00_divide_error();
extern void _asm_inthandler01_debug();
extern void _asm_inthandler02_NMI_interrupt();
extern void _asm_inthandler03_breakpoint();
extern void _asm_inthandler04_overflow();
extern void _asm_inthandler05_bound_range_exceeded();
extern void _asm_inthandler06_invalid_opcode();
extern void _asm_inthandler07_device_not_available();
extern void _asm_inthandler08_double_fault();
extern void _asm_inthandler09_coprocess_segment_overrun();
extern void _asm_inthandler10_invalid_TSS();
extern void _asm_inthandler11_segment_not_present();
extern void _asm_inthandler12_stack_segment_fault();
extern void _asm_inthandler13_general_protection();
extern void _asm_inthandler14_page_fault();

extern void _asm_inthandler16_floating_point_error();
extern void _asm_inthandler17_alignment_check();
extern void _asm_inthandler18_machine_check();
extern void _asm_inthandler19_SIMD_floating_point_exception();
extern void _asm_inthandler14_page_fault();
extern void _asm_inthandler21_keyboard();
extern void _asm_inthandler20_timer();
extern void _asm_general_handler();

//目的是为了让编辑软件识别函数自动补全，其实不写这些也行
void _asm_hlt();
void _asm_read_gdt(); //返回一个32bit数字，里面保存了gdt的地址
