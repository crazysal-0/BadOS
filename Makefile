ASM = nasm
CC = gcc

CFLAGS = -m16 -ffreestanding -fno-pie -fno-stack-protector -fno-asynchronous-unwind-tables -fno-unwind-tables -Wall -Wextra -Ikernel/inc
LDFLAGS = -m16 -nostdlib -static -T linker.ld -Wl,--oformat=binary

BIN = bin

BOOT_OBJECT = $(BIN)/boot.o
KERNEL_OBJECTS = $(patsubst kernel/src/%.c,$(BIN)/%.o,$(wildcard kernel/src/*.c))

OS_IMAGE = $(BIN)/os.img

.PHONY: all run clean

all: $(OS_IMAGE)

$(BIN):
	mkdir -p $(BIN)

$(BOOT_OBJECT): boot/main.asm | $(BIN)
	$(ASM) -f elf32 $< -o $@

$(BIN)/%.o: kernel/src/%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(OS_IMAGE): $(BOOT_OBJECT) $(KERNEL_OBJECTS) linker.ld
	$(CC) $(LDFLAGS) $(BOOT_OBJECT) $(KERNEL_OBJECTS) -o $@

run: $(OS_IMAGE)
	qemu-system-i386 -drive format=raw,file=$(OS_IMAGE)

clean:
	rm -rf $(BIN)