#define IDT_ADDR 0x00090000
#define IDT_LIMIT 0X000007ff
#define AR_INTGATE32  0x008e

/*typedef struct _idt_gate_descriptor {
	short offset_low, selector;
	char dw_count, access_right;
	short offset_high;
}IDT_Gate_Descriptor;
*/

//64bits, 8Bytes, 16+16+8+8+16=64
typedef struct _idt_gate_descriptor{
	uint16_t offset_low, selector;
	uint8_t datacount;
	uint8_t attr;		/* P(1) DPL(2) DT(1) TYPE(4) */
	uint16_t offset_high;
}IDT_Gate_Descriptor;

/* 定义中断的两种状态:
 * INTR_OFF值为0,表示关中断,
 * INTR_ON值为1,表示开中断 */

/* define two kinds of status
 * INTR_OFF = 0, interrupt is disable
 * INTR_ON = 1, interrupt is able
 */
enum intr_status {		 // 中断状态, status of interrupt
    INTR_OFF,			 // 中断关闭, interrupt close
    INTR_ON		         // 中断打开, interrupt open
};

enum intr_status intr_get_status(void);
enum intr_status intr_set_status (enum intr_status);
enum intr_status intr_enable (void);
enum intr_status intr_disable (void);
