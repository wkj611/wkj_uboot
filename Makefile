all:start.o mem.o main.o
	arm-linux-ld -Twboot.lds -o wboot.elf $^
	arm-linux-objcopy -O binary wboot.elf wboot.bin
%.o:%.S
	arm-linux-gcc -g -c $^
%.o:%.c
	arm-linux-gcc -g -c $^
.PHONY:clean
clean:
	rm *.o *.elf *.bin
