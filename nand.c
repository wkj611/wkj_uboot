#define NFCONF (volatile unsigned long*)0x70200000
#define NFCONT (volatile unsigned long*)0x70200004
#define NFCMMD (volatile unsigned long*)0x70200008
#define NFDATA (volatile unsigned long*)0x70200010
#define NFADDR (volatile unsigned long*)0x7020000C
#define NFSTAT (volatile unsigned long*)0x70200028

#define TACLS  7
#define TWRPH0 7
#define TWRPH1 7
int chip_select();
int chip_disselect();
int nand_init();
int nand_reset();
int nand_cmd(unsigned char);
int wait_RnB();
int clean_RnB();
int nand_addr(unsigned char);
int clean_RnB(){
	  *NFSTAT |= (1<<4);
	  return 0;
}
int wait_RnB(){
    while(!(*NFSTAT)&(0x1)){}
    return 0;
}
int nand_init(){
	  *NFCONF &= ~((7<<12)|(7<<8)|(7<<4));
    *NFCONF |= (TACLS << 12)|(TWRPH0 << 8)|(TWRPH1 << 4);
    *NFCONT |= 0x3; 
    nand_reset();   
    return 0;
}
int chip_select(){
	  *NFCONT &= ~(1<<1) ;
	  return 0;
}
int chip_disselect(){
	  *NFCONT |= (1<<1) ;
	  return 0;
}
int nand_cmd(unsigned char cmd){
    *NFCMMD = cmd;
    return 0;
}
int nand_reset(){
    chip_select();
    clean_RnB();
    nand_cmd(0xff);
    wait_RnB();
    chip_disselect();
    return 0;
}
int nand_addr(unsigned char addr)
{
    *NFADDR = addr;
    return 0;
}

int nand_page_read(char *buff,unsigned long addr){
    int i;
    chip_select();
    clean_RnB();
    nand_cmd(0x00);
    nand_addr(0x00);
    nand_addr(0x00);
    nand_addr(addr&(0xff));
    nand_addr((addr>>8)&(0xff));
    nand_addr((addr>>16)&(0xff));
    nand_cmd(0x30);
    wait_RnB();
    for(i=0;i<4096;i++)
        *buff++ = *NFDATA;
    chip_disselect();
    return 0;
}
/*dest :内存起始地址
/*start:nandFlash的页地址
/*size :copy内容的大小
*/
int nand_to_ram(unsigned char *dest,unsigned char start,int size){
    int i;
    for(i=0;i<4;i++){
        nand_page_read(dest,i);	
        dest = dest + 2048;
    }
    size -= 1024*8;
    for(i=4;size>0;i++){
    	  nand_page_read(dest,i);
    	  dest += 4096;	 
    	  size = size - 4096; 
    }
    return 0;
}
