NAME:=assos.bin

all: assusdanos

assusdanos: boot kernel system
	i686-elf-gcc -T linker.ld -o $(NAME) -ffreestanding -O2 -nostdlib boot.o kernel.o system.o -lgcc

boot: boot.s
	i686-elf-as boot.s -o boot.o

kernel: kernel.c
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

system: system.c
	i686-elf-gcc -c system.c -o system.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

clean:
	rm -rf *.o $(NAME)