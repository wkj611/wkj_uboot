int wboot_main(){
	  #ifdef MMU_ON
	  mmu_init();
	  #endif
	  led_init();
	  button_init();
	  irq_init();
          nand_cp();	  
	  led_twk();
	  return 0;
}
