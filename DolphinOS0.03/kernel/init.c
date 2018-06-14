/*(C) 2018 Future-Technology
 *design by Olaf 2018/6
 *this is the entry of DolphinOS
 */

int Kernel_Init(){
	char *v = (char *)0x800a0000;
	v[0] = 0xff;
	v[1] = 0xee;
	v[2] = 0xdd;
	v[3] = 0xcc;
	v[4] = 0xbb;
	
	while(1){
	}
	
	
	
}
