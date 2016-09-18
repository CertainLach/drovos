NAME:=drovos.bin

all: drovos

drovos: boot kernel system memory api
	i686-elf-gcc -T linker.ld -o $(NAME) -ffreestanding -Og -nostdlib boot.o kernel.o system.o memory.o api.o -lgcc

boot: boot.s
	i686-elf-as boot.s -o boot.o

kernel: kernel.c
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -Og -Wall -Wextra

memory: memory.c
	i686-elf-gcc -c memory.c -o memory.o -std=gnu99 -ffreestanding -Og -Wall -Wextra

api: api.c
	i686-elf-gcc -c api.c -o api.o -std=gnu99 -ffreestanding -Og -Wall -Wextra

system: system.c
	i686-elf-gcc -c system.c -o system.o -std=gnu99 -ffreestanding -Og -Wall -Wextra

clean:
	rm -rf *.o $(NAME)
