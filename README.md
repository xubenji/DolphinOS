# This is DolphinOS source code
	DolphinOS is a 32-bits Operating system, I plan to support 64-bits CPU. 
	I use ubuntu OS to write the C code.
	GCC version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9).
	Ensure the version of software is the same as me.
	The OS can run on the qemu virual machine(X86 platform).
	The OS be install in floppy disk. you need to pay attention to the bochsrc file, if you can't run DolphinOS.
	In version 0.03B, the OS do not enter the vbe2.0 display mode. 
	Version 0.05a------The character lib has been completed.
	Version 0.06 the stack checked function of gcc is disable.
	In version 0.04 i change the virual box to qemu, because the qemu runs faster than bochs.
# How to run DolphinOS?
	First, you need install a linux operating system like ubuntu, CentOS. 
	And then you need install qemu, gcc(V5.40) & nasm.
	Finally you open the terminal in DolphinOS folder and enter the command: make run (make sure you are root.) 
# New 0.07 version
	In this version, i change the paging to 0x100000(low physical memory address) in order to implenment the memory mangment system.
