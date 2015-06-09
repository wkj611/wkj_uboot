obj = start.o mem.o main.o mmu.o led.o button.o interrupt.o
all:$(obj)
	arm-linux-ld -Twboot.lds -o wboot.elf $^
	arm-linux-objcopy -O binary wboot.elf wboot.bin
%.o:%.S
	arm-linux-gcc -g -c $^
%.o:%.c
	arm-linux-gcc -g -c $^
.PHONY:clean
clean:
	rm *.o *.elf *.bin
