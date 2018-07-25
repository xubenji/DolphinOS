#########################
#       DolphinOS       #
#########################

# Made by Olaf
# Copyright (C) 2018 Future-Fechnology
#This operating system run X86 platform
#the kernel entry

KERNEL_INIT_ADDERSS = 80010000

#load is on the 1st sector
#Now, we use 8 sectors for load.it's 1kb(4096 bytes)
LOAD_SECTOR_OFFSET = 1		
LOAD_SECTORS = 8

#kernel in the 9th sector
#kernel only use 256 sector(256*512/1024 = 128KB)
KERNEL_SECTOR_OFFEST = 9
KERNEL_SECTORS = 256

ASM_BOOT_PATH	= -I

DolphinOS_IMG	= DolphinOS.img


NASM		= nasm
CC		= gcc $(NOSTACK)
LD 		= ld

BOOT_BIN	= boot/boot.bin
LOAD_BIN	= boot/load.bin
KERNEL_BIN	= kernel/kernel.bin
KERNEL_OBJ	= kernel/kernel.o

#stack
NOSTACK         = -fno-stack-protector -shared

C_KERNEL_FLAGS	= -I -wall -c -fno-builtin 

LDFLAGS		= --oformat binary -N -e Kernel_Init -Ttext $(KERNEL_INIT_ADDERSS) $(NOSTACK)

OBJS = kernel/init.o kernel/printk.o kernel/screen.o kernel/asc.o kernel/ards.o kernel/memory.o

#there are kernel/printk.o
.PHONY: all


all: compile_bin write_disk

compile_bin: $(BOOT_BIN) $(LOAD_BIN) $(KERNEL_BIN)

write_disk:
	dd if=$(BOOT_BIN) of=$(DolphinOS_IMG) bs=512 count=1 conv=notrunc
	dd if=$(LOAD_BIN) of=$(DolphinOS_IMG) bs=512 seek=$(LOAD_SECTOR_OFFSET) count=$(LOAD_SECTORS) conv=notrunc
	dd if=$(KERNEL_BIN) of=$(DolphinOS_IMG) bs=512 seek=$(KERNEL_SECTOR_OFFEST) count=$(KERNEL_SECTORS) conv=notrunc

run: all
	#qemu-system-i386 -bios "OVMF.fd" -m 32 -fda $(DolphinOS_IMG) -boot a
	qemu-system-i386 -m 32 -fda $(DolphinOS_IMG) -boot a
	#bochs -f bochsrc

clean:
	-rm  boot/load.bin	
	-rm  boot/boot.bin
	-rm  bochsout.txt
	-rm  kernel/init.o
	-rm  $(KERNEL_BIN)
	-rm  kernel/*.o
	-rm  *.o

$(LOAD_BIN):boot/load.asm
	$(NASM)  -o $@ $<

$(BOOT_BIN):boot/boot.asm
	$(NASM)  -o $@ $<

$(KERNEL_BIN):$(OBJS)
	$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(OBJS)

#$(KERNEL_BIN):$(KERNEL_OBJ)
#	objcopy -R .note -R .comment -S -O binary $(KERNEL_OBJ) $(KERNEL_BIN)

#$(KERNEL_OBJ): $(OBJS)
#	$(LD) $(LDFLAGS) -o $(KERNEL_OBJ) $(OBJS)

#kernel
init.o : kernel/init.c
	$(CC) $(C_KERNEL_FLAGS) -o $@ $< 

printk.o:kernel/printk.c
	$(CC) $(C_KERNEL_FLAGS) -O $@ $< 

screen.o:kernel/screen.c
	$(CC) $(C_KERNEL_FLAGS) -O $@ $< 

asc.o:kernel/asc.c
	$(CC) $(C_KERNEL_FLAGS) -O $@ $< 

ards.o:kernel/ards.c
	$(CC) $(C_KERNEL_FLAGS) -O $@ $< 

memory.o:kernel/memory.c
	$(CC) $(C_KERNEL_FLAGS) -O $@ $< 
#_stack_chk_fail.o:kernel/_stack_chk_fail.c
#	$(CC) $(C_KERNEL_FLAGS) -O $@ $< 


