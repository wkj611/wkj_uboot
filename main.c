#define pGPMCON (volatile unsigned long*) 0xA0008820
#define pGPMDAT (volatile unsigned long*) 0xA0008824
#define ppGPMCON (volatile unsigned long*) 0x7f008820
#define ppGPMDAT (volatile unsigned long*) 0x7f008824
#define asmpGPMCON 0xA0008820
#define asmpGPMDAT 0xA0008824

#define AP (3<<10)
#define D (0<<5)
#define XN (1<<4)
#define C (1<<3)
#define B (1<<2)
#define SECTION_ID (1<<1)
#define TTB_DES     ( AP | D | XN | SECTION_ID)
#define MEM_TTB_DES ( AP | D | XN | C | B | SECTION_ID)

int set_ttb(){
	  unsigned long *ttb = (volatile unsigned long*)0x50000000;
	  unsigned long vaddr,paddr;
	  vaddr = 0xA0000000;
	  paddr = 0x7f000000;
	  *(ttb + vaddr>>20) = (paddr & 0xfff00000)|TTB_DES;
	  vaddr = 0x50000000;
    paddr = 0x50000000;
    while (vaddr < 0x54000000)
    {
        *(ttb + (vaddr >> 20)) = (paddr & 0xFFF00000) | MEM_TTB_DES;
        vaddr += 0x100000;
        paddr += 0x100000;
    }
	  return 0;
	  }
int mmu_init(){
    __asm__(
    /*set TTB address*/
    "ldr r0,=0x50000000\n"
    "mcr p15,0,r0,c2,c0,0\n"
    /*set domain manger*/
    "mvn r0,#0x0\n"
    "mcr p15,0,r0,c3,c0,0\n"
    /*enable MMU*/
    "mrc p15,0,r0,c1,c0,0\n"
    "orr r0,r0,#0x1"
    "mcr p15,0,r0,c1,c0,0\n" 
    :
    :
    );	
    return 0;
    }
int led_on_asm(){
	  __asm__(
        "ldr r1,=0x1111\n"
        "str r1,[%0]\n"
        "ldr r1,=0x0\n"   /*0b1010*/
        "str r1,[%1]\n"
	  	  :
	  	  :"r"(asmpGPMCON),"r"(asmpGPMDAT)
	  	  :"r1"
	  );
        return 0;
}
int wboot_main(){
	  int i;
	  set_ttb();
	  mmu_init();
	  //led_on();
	  //for(i=0;i<5330000/2;i++){}
	  led_on_asm();
	  for(i=0;i<5330000/2;i++){}
	  *(pGPMCON) = 0x1111;
	  while(1){
	      *(pGPMDAT) = 0xa;
	      for(i=0;i<5330000/2;i++){}
	      *(pGPMDAT) = 0x5;
	      for(i=0;i<5330000/2;i++){}
	  }
	  return 0;
}
