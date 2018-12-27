#define IDT_ADDR 0x00090000
#define IDT_LIMIT 0X000007ff
#define AR_INTGATE32  0x008e

/*typedef struct _idt_gate_descriptor {
	short offset_low, selector;
	char dw_count, access_right;
	short offset_high;
}IDT_Gate_Descriptor;
*/
typedef struct _idt_gate_descriptor{
	uint16_t offset_low, selector;
	uint8_t datacount;
	uint8_t attr;		/* P(1) DPL(2) DT(1) TYPE(4) */
	uint16_t offset_high;
}IDT_Gate_Descriptor;
