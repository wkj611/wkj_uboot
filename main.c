#define pGPMCON (volatile unsigned long*) 0x7f008820
#define pGPMDAT (volatile unsigned long*) 0x7f008824
#define asmpGPMCON 0x7f008820
#define asmpGPMDAT 0x7f008824
int mmu_init(){
    __asm__(
    "ldr r0,=0x50000000\n"
    "mcr p15,0,r0,c2,c0,0\n"
    "mvn r0,#0x0\n"
    "mcr p15,0,r0,c3,c0,0\n"
    "mrc p15,0,r0,c1,c0,0\n"
    "orr r0,r0,#0x1"
    "mcr p15,0,r0,c1,c0,0\n" 
    :
    :
    );	
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
	  led_on();
	  for(i=0;i<5330000/2;i++){}
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
