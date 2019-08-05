extern int io_in8_ASM(int port);
extern void io_out8_ASM(int port, int data);
extern void io_sti();
extern void load_idtr(int limit, int addr);
extern int read_cr3_ASM();
