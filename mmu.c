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
	  *(ttb + (vaddr>>20)) = (paddr & 0xfff00000)|TTB_DES;
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
int mmu_enable(){
    __asm__(
    /*set TTB address*/
    "ldr r0,=0x50000000\n"
    "mcr p15,0,r0,c2,c0,0\n"
    /*set domain manger*/
    "mvn r0,#0x0\n"
    "mcr p15,0,r0,c3,c0,0\n"
    /*enable MMU*/
    "mrc p15,0,r0,c1,c0,0\n"
    "orr r0,r0,#0x1\n"
    "mcr p15,0,r0,c1,c0,0\n" 
    :
    :
    );	
    return 0;
    }
int mmu_init(){
	  set_ttb();
	  mmu_enable();
	  return 0;
	  }