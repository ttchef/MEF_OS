
CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)

GCCFLAGS = -Wall -g -ffreestanding -nostdlib -nostartfiles -o2

GCCPATH = $(PWD)/cross_compiler/arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-elf/bin

all: clean kernel8.img

boot.o: boot.S
	$(GCCPATH)/aarch64-none-elf-gcc $(GCCFLAGS) -c boot.S -o boot.o

mmu.o: mmu.S
	$(GCCPATH)/aarch64-none-elf-gcc $(GCCFLAGS) -c mmu.S -o mmu.o


%.o: %.c
	$(GCCPATH)/aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@


kernel8.img: boot.o mmu.o $(OFILES)
	$(GCCPATH)/aarch64-none-elf-ld -nostdlib -g boot.o mmu.o $(OFILES) -T linker.ld -o kernel8.elf # -g is only for debug symbols remove later
	$(GCCPATH)/aarch64-none-elf-objcopy -O binary kernel8.elf kernel8.img

clean:
	/bin/rm kernel8.elf *.o *.img > /dev/null 2> /dev/null || true

