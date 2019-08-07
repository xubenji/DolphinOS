#include "../com/types.h"

struct semaphore{
	uint8_t value;
	//struct list waiters;
};

void semaphore_init();


