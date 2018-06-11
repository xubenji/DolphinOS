#########################
#       FutureOS        #
#########################

# Made by Olaf
# Copyright (C) 2018 Future-Fechnology

#This operating system run X86 platform

#the kernel entry
KERNEL_INIT_ADDERSS = 0x80010000

#load is on the 1st sector
#Now, we use 8 sectors for load.it's 1kb(4096 bytes)
LOAD_SECTOR_OFFSET = 1		
LOAD_SECTORS = 8

#kernel in the 9th sector
#kernel only use 256 sector(256*512/1024 = 128KB)
KERNEL_SECTOR_OFFEST = 9
KERNEL_SECTORS = 256

ASM_BOOT_PATH	= -I

FutureOS_IMG	= FutureOS.img


NASM		= nasm
CC		= gcc
LD 		= ld

BOOT_BIN	= boot.bin
LOAD_BIN	= load.bin
KERNEL_BIN	= kernel.bin


C_KERNEL_FLAGS	= -I -Wall -c -fno-builtin

LDFLAGS		= --oformat binary -N -e Kernel_Init -Ttext $(KERNEL_INIT_ADDERSS) 

OBJS = init.o


.PHONY: all


all: compile_bin write_disk

compile_bin: $(BOOT_BIN) $(LOAD_BIN) $(KERNEL_BIN)

write_disk:
	dd if=$(BOOT_BIN) of=$(FutureOS_IMG) bs=512 count=1 conv=notrunc
	dd if=$(LOAD_BIN) of=$(FutureOS_IMG) bs=512 seek=$(LOAD_SECTOR_OFFSET) count=$(LOAD_SECTORS) conv=notrunc
	dd if=$(KERNEL_BIN) of=$(FutureOS_IMG) bs=512 seek=$(KERNEL_SECTOR_OFFEST) count=$(KERNEL_SECTORS) conv=notrunc

run: all
	#qemu-system-i386 -m 32 -fda $(FutureOS_IMG) -boot a
	bochs -f bochsrc

clean:
	-rm -f load.bin	
	-rm -f boot.bin
	-rm -f bochsout.txt
	-rm -f init.o
	-rm kernel.bin



$(LOAD_BIN):load.asm
	$(NASM)  -o $@ $<

$(BOOT_BIN):boot.asm
	$(NASM)  -o $@ $<

init.o : init.c
	$(CC) $(C_KERNEL_FLAGS) -o $@ $<

$(KERNEL_BIN): init.o
	$(LD) $(LDFLAGS) -o $(KERNEL_BIN) init.o

