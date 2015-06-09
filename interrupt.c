#define VIC0INTENABLE (volatile unsigned long*)0x71200010
#define VIC0VECTADDR0 (volatile unsigned long*)0x71200100
#define VIC0VECTADDR1 (volatile unsigned long*)0x71200104
#define VIC0ADDRESS   (volatile unsigned long*)0x71200f00
#define EINT0CON0 (volatile unsigned long*)0x7f008900
#define EINT0MASK (volatile unsigned long*)0x7f008920
#define EINT0PEND (volatile unsigned long*)0x7f008924
int int_handler();
int key1_handler();
int key2_handler();
int key3_handler();
int key4_handler();
int key5_handler();
int key6_handler();

int irq_init(){
	  *EINT0CON0 = (3<<0)|(3<<4)|(3<<8);
	  *EINT0MASK = 0xfffffc0; 
	  *VIC0INTENABLE = 0x3;
	
	  *VIC0VECTADDR0 = (int)int_handler;
	  *VIC0VECTADDR1 = (int)int_handler;
	  __asm__(
	  "mrc p15,0,r0,c1,c0,0\n"
    "orr r0,r0,#(1<<24)\n"
    "mcr p15,0,r0,c1,c0,0\n"
    
	  "mrs r0,cpsr\n"
	  "bic r0,r0,#0x80\n"
	  "msr cpsr_c,r0\n"
	  :
	  :  
	  );
	  return 0;
}
int int_handler(){
	int i;
	  unsigned long value;
	  __asm__(
	  "sub lr,lr,#4\n"
	  "stmfd sp!,{r0-r12,lr}\n"
	  :
	  :
	  );
	  value = *EINT0PEND;
	  switch(value){
	  	case 1:
	  		key1_handler();
	  		break;
	  	case 0x2:
	  		key2_handler();
	  		break;
	  	case 0x4:
	  		key3_handler();
	  		break;
	  	case 0x8:
	  		key4_handler();
	  		break;
	  	case 0x10:
	  		key5_handler();
	  		break;
	  	case 0x20:
	  		key6_handler();
	  		break;
	  	default:
	  		break;
	  		
	  	}
	  //led_off();
	  
	  *EINT0PEND = 0b111111;
	  *VIC0ADDRESS = 0;
//	  *VIC0VECTADDR0 = 0; 
//    *VIC0VECTADDR1 = 0;
	  
	  __asm__(
	  "ldmfd sp!,{r0-r12,pc}^"
	  :
	  :
	  );
	  return 0;
	  
}
/*int int_handler2(){
	int i;
	  unsigned long value;
	  __asm__(
	  "sub lr,lr,#4\n"
	  "stmfd sp!,{r0-r12,lr}\n"
	  :
	  :
	  );
	  value = *EINT0PEND;
	  switch(value){
	  	case 1:
	  		key1_handler();
	  		break;
	  	case 0x2:
	  		key2_handler();
	  		break;
	  	case 0x4:
	  		key3_handler();
	  		break;
	  	case 0x8:
	  		key4_handler();
	  		break;
	  	case 0x10:
	  		key5_handler();
	  		break;
	  	case 0x20:
	  		key6_handler();
	  		break;
	  	default:
	  		break;
	  		
	  	}
//	  led_light();
//	  for(i=0;i<5330000/2;i++){}
	  *EINT0PEND = 0b111111;
	  *VIC0ADDRESS = 0;
//	  *VIC0VECTADDR0 = 0; 
//    *VIC0VECTADDR1 = 0;
	  
	  __asm__(
	  "ldmfd sp!,{r0-r12,pc}^"
	  :
	  :
	  );
	  return 0;
	  
}*/
int key1_handler(){
	led_light();
	return 0;
}
int key2_handler(){
	led_off();
	return 0;
}
int key3_handler(){
	led_light();
	return 0;
}
int key4_handler(){
	led_off();
	return 0;
}
int key5_handler(){
	led_light();
	return 0;
}
int key6_handler(){
	led_off();
	return 0;
}
