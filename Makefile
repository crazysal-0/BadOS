ASM = nasm
CC = gcc

CFLAGS = -m16 -ffreestanding -fno-pie -fno-stack-protector \
	-fno-asynchronous-unwind-tables -fno-unwind-tables \
	-Wall -Wextra -Ikernel/inc -Ifs/inc

LDFLAGS = -m16 -nostdlib -static -T linker.ld -Wl,--oformat=binary

BIN = bin

BOOT_OBJECT = $(BIN)/boot.o

KERNEL_SOURCES = $(wildcard kernel/src/*.c)
FS_SOURCES = $(wildcard fs/src/*.c)

KERNEL_OBJECTS = $(patsubst kernel/src/%.c,$(BIN)/%.o,$(KERNEL_SOURCES))
FS_OBJECTS = $(patsubst fs/src/%.c,$(BIN)/%.o,$(FS_SOURCES))

OS_IMAGE = $(BIN)/os.img

.PHONY: all run clean

all: $(OS_IMAGE)

$(BIN):
	mkdir -p $(BIN)

$(BOOT_OBJECT): boot/main.asm | $(BIN)
	$(ASM) -f elf32 $< -o $@

$(BIN)/%.o: kernel/src/%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: fs/src/%.c | $(BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(OS_IMAGE): $(BOOT_OBJECT) $(KERNEL_OBJECTS) $(FS_OBJECTS) linker.ld
	$(CC) $(LDFLAGS) $(BOOT_OBJECT) $(KERNEL_OBJECTS) $(FS_OBJECTS) -o $@

run: $(OS_IMAGE)
	qemu-system-i386 -drive format=raw,file=$(OS_IMAGE)

clean:
	rm -rf $(BIN)