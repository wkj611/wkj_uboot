#define GPNCON (volatile unsigned long *)0x7f008830
#define GPN0 0x2<<0
#define GPN1 0x2<<2
#define GPN2 0x2<<4
#define GPN3 0x2<<6
#define GPN4 0x2<<8
#define GPN5 0x2<<10
int button_init(){
	  *GPNCON = GPN0|GPN1|GPN2|GPN3|GPN4|GPN5;
}
