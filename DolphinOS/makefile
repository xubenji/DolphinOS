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

NASM32		= nasm
NASM		= nasm 
CC		= gcc -std=gnu99 -m32 -fno-pic -no-pie -g $(NOSTACK)
LD 		= ld -m elf_i386 

BOOT_BIN	= boot/boot.bin
LOAD_BIN	= boot/load.bin
KERNEL_BIN	= kernel/kernel.bin
SYSTEM_BIN	= kernel/system.bin
KERNEL_ELF	= kelf
KERNEL_OBJ	= kernel/kernel.o

#stack
NOSTACK         = -fno-stack-protector -shared

C_KERNEL_FLAGS	= -I -wall -c -fno-builtin 

ASM_KERNEL_FLAGS= -f elf

LDFLAGS		= --oformat binary -N -e Kernel_Init -Ttext $(KERNEL_INIT_ADDERSS) $(NOSTACK) 
LDFLAGSELF	= -N   -e Kernel_Init -Ttext $(KERNEL_INIT_ADDERSS) $(NOSTACK) 

OBJS =  kernel/init.o \
	kernel/printk.o \
	kernel/screen.o \
	kernel/asc.o \
	kernel/ards.o \
	kernel/memory.o \
	kernel/io_ASM.o \
	kernel/bitmap.o \
	kernel/string.o \
	kernel/handler_ASM.o \
	kernel/pic.o \
	kernel/idt.o \
	com/math.o \
	kernel/handlers.o \
	kernel/timer.o \
	kernel/vram.o \
	kernel/thread.o \
	kernel/switch_ASM.o \
	kernel/debug.o \
	kernel/list.o \
	driver/keyboard.o \
	kernel/lock.o \
	kernel/tss.o \
	kernel/process.o
 
#there are kernel/printk.o
.PHONY: all


all: compile_bin write_disk
alls: compile_all write_disk

compile_bin: $(BOOT_BIN) $(LOAD_BIN) $(KERNEL_BIN) 

compile_all: $(BOOT_BIN) $(LOAD_BIN) $(KERNEL_BIN) $(KERNEL_ELF)

write_disk:
	dd if=$(BOOT_BIN) of=$(DolphinOS_IMG) bs=512 count=1 conv=notrunc
	dd if=$(LOAD_BIN) of=$(DolphinOS_IMG) bs=512 seek=$(LOAD_SECTOR_OFFSET) count=$(LOAD_SECTORS) conv=notrunc
	dd if=$(KERNEL_BIN) of=$(DolphinOS_IMG) bs=512 seek=$(KERNEL_SECTOR_OFFEST) count=$(KERNEL_SECTORS) conv=notrunc

run: all
	qemu-system-i386 -m 64 -fda $(DolphinOS_IMG) -boot a
	#qemu-system-i386 -m 64 -fda $(DolphinOS_IMG) -gdb tcp::1234 -S -boot a
	#qemu-system-i386 -bios "OVMF.fd" -m 32 -fda $(DolphinOS_IMG) -boot a
	#bochs -f bochsrc

s: alls
	qemu-system-i386 -m 64 -fda $(DolphinOS_IMG) -gdb tcp::1234 -S -boot a
	

runb: alls
	bochs -f bochsrc

clean:
	-rm  */*.bin
	-rm  */*.o
	-rm -f */*.elf
	-rm  ./kelf
	-rm -f ./*.sym
	-rm -f ./kernel.map
	-rm -f bochsout.txt
	

$(LOAD_BIN):boot/load.asm
	$(NASM32)  -o $@ $<

$(BOOT_BIN):boot/boot.asm
	$(NASM32)  -o $@ $<

$(KERNEL_BIN):$(OBJS)
	$(LD) $(LDFLAGS) -o $(KERNEL_BIN) $(OBJS)

$(KERNEL_ELF):$(OBJS)
	$(LD) $(LDFLAGSELF) -o $(KERNEL_ELF) $(OBJS)
	


#$(KERNEL_BIN):$(OBJS)
	#$(LD) $(LDFLAGSELF) -o $(KERNEL_ELF) $(OBJS) -Map kernel.map
	#objcopy --only-keep-debug $(KERNEL_ELF) kernel.sym
	#objcopy -S -O binary $(KERNEL_ELF) $(KERNEL_BIN)

#$(KERNEL_BIN):$(KERNEL_OBJ)
#	objcopy -R .note -R .comment -S -O binary $(KERNEL_OBJ) $(KERNEL_BIN)

#$(KERNEL_OBJ): $(OBJS)
#	$(LD) $(LDFLAGS) -o $(KERNEL_OBJ) $(OBJS)

#kernel
init.o : kernel/init.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

printk.o:kernel/printk.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

screen.o:kernel/screen.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

asc.o:kernel/asc.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

ards.o:kernel/ards.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

memory.o:kernel/memory.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

bitmap.o:kernel/bitmap.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

string.o:kernel/string.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

idt.o:kernel/idt.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

pic.o:kernel/pic.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

timer.o:kernel/timer.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

kernel/io_ASM.o : kernel/io_ASM.asm
	$(NASM) $(ASM_KERNEL_FLAGS) -o $@ $<

kernel/handler_ASM.o:kernel/handler_ASM.asm
	$(NASM) $(ASM_KERNEL_FLAGS) -o $@ $<

kernel/switch_ASM.o:kernel/switch_ASM.asm
	$(NASM) $(ASM_KERNEL_FLAGS) -o $@ $<

handlers.o:kernel/handlers.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

vram.o:kernel/vram.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

thread.o:kernel/thread.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

debug.o:kernel/debug.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

list.o:kernel/list.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

lock.o:kernel/lock.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

tss.o:kernel/tss.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

process.o:kernel/process.c 
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 	
	
#com
math.o:com/math.c
	$(CC) $(C_KERNEL_FLAGS)  $@ $<
#driver
keyboard.o:driver/keyboard.c 
	$(CC) $(C_KERNEL_FLAGS)  $@ $< 

#_stack_chk_fail.o:kernel/_stack_chk_fail.c
#	$(CC) $(C_KERNEL_FLAGS) -O $@ $< 


