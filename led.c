#define pGPMCON (volatile unsigned long*) 0xA0008820
#define pGPMDAT (volatile unsigned long*) 0xA0008824
#define ppGPMCON (volatile unsigned long*) 0x7f008820
#define ppGPMDAT (volatile unsigned long*) 0x7f008824
#define asmpGPMCON 0xA0008820
#define asmpGPMDAT 0xA0008824
#define pasmpGPMCON 0x7f008820
#define pasmpGPMDAT 0x7f008824

int led_init(){
	  *(ppGPMCON) = 0x1111;
	  return 0;
	}
int led_on_asm(){
	  __asm__(
        "ldr r1,=0x1111\n"
        "str r1,[%0]\n"
        "ldr r1,=0x0\n"   /*0b1010*/
        "str r1,[%1]\n"
	  	  :
	  	  :"r"(pasmpGPMCON),"r"(pasmpGPMDAT)
	  	  :"r1"
	  );
        return 0;
}
int led_twk(){
	  int i;
	  led_on_asm();
	  for(i=0;i<5330000/2;i++){}
	  while(1){
	      *(ppGPMDAT) = 0xa;
	      for(i=0;i<5330000/2;i++){}
	      *(ppGPMDAT) = 0x5;
	      for(i=0;i<5330000/2;i++){}
	  }
	  return 0;
}
