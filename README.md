# This is DolphinOS source code
	DolphinOS is a 32-bits Operating system, I plan to support 64-bits CPU. 
	I use ubuntu OS to write the C code.
	GCC version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9).
	Ensure the version of software is the same as me.
	The OS can run on the qemu virual machine(X86 platform).
	The OS be install in virtual floppy disk. 
	In version 0.03B, the OS do not enter the vbe2.0 display mode. 
	Version 0.05a------The character lib has been completed.
	Version 0.06 the stack checked function of gcc is disable.
	In version 0.04 i change the virual box to qemu, because the qemu runs faster than bochs.
# How to run DolphinOS?
	First, you need install a linux operating system like ubuntu, CentOS. 
	And then you need install qemu, gcc(V5.40) & nasm in linux.
	Finally you open the terminal in DolphinOS folder and enter the command: make run (make sure you are root.) 
# New 0.07 version
	In this version, i change the paging to 0x100000(1mb low physical memory address) in order to implenment the memory mangment system. 

# 这是DolphinOS源代码
	DolphinOS是一个32位的操作系统，未来我会计划支持64位。
	我使用Ubuntu编写的源代码。
	gcc的版本是 5.4.0 20160609 （Ubuntu 5.4.0-6ubuntu1~16.04.9）。
	确保您运行时支持软件和我的一样。
	目前操作系统运行在qemu下（x86平台）。
	操作系统被安装在虚拟软盘中。
	在0.03b版本中，操作系统将不会进入vbe2.0显示模式。
	在0.04版本中，我已经将虚拟机从bochs切换到了qemu。
	在0.05a版本中，字符库已经被完成。
	在0.06版本中，gcc的堆栈保护已经被禁用。
# 如何运行DolphinOS？
	首先，你需要安装一个Linux操作系统，类似于Ubuntu, centos。然后你需要在Linux系统中安装qemu，gcc和nasm。
	最后你需要在DolphinOS文件夹下打开terminal，输入make run命令（确保你现在已经取得root权限）。
# 0.07新版本
	在这个版本中，我将页表移动到了0x100000处（低端物理地址），目的是为了实现内存管理系统。
