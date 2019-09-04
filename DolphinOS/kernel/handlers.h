void inthandler00_divide_error(uint8_t vec_num);
void inthandler01_debug(uint8_t vec_num);
void inthandler02_NMI_interrupt(uint8_t vec_num);
void inthandler03_breakpoint(uint8_t vec_num);
void inthandler04_overflow(uint8_t vec_num);
void inthandler05_bound_range_exceeded(uint8_t vec_num);
void inthandler06_invalid_opcode(uint8_t vec_num);
void inthandler07_device_not_available(uint8_t vec_num);
void inthandler08_double_fault(uint8_t vec_num);
void inthandler09_coprocess_segment_overrun(uint8_t vec_num);
void inthandler10_invalid_TSS(uint8_t vec_num);
void inthandler11_segment_not_present(uint8_t vec_num);
void inthandler12_stack_segment_fault(uint8_t vec_num);
void inthandler13_general_protection(uint8_t vec_num);
void inthandler14_page_fault(uint8_t vec_num);

void inthandler16_floating_point_error(uint8_t vec_num);
void inthandler17_alignment_check(uint8_t vec_num);
void inthandler18_machine_check(uint8_t vec_num);
void inthandler19_SIMD_floating_point_exception(uint8_t vec_num);



void inthandler21_keyboard(int32_t *esp);
void inthandler20_timer(int32_t *esp);
void general_handler(uint8_t vec_num);

