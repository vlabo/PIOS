OBJ_DIR=objects
SRC_DIR=src
BUILD_DIR=../build

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC_C = $(call rwildcard,src,*.c)
SRC_ASM += $(SRC_DIR)/start.S

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_C))
OBJS += $(OBJ_DIR)/start.o
OBJS += $(OBJ_DIR)/font.o

C_TO_ASM = $(patsubst $(SRC_DIR)/%.c, asm/%.S, $(SRC_C))

INCLUDES = -I src -I src/std -I src/std/types

RES = res/font.psf

CFLAGS = -Wall -O2 -ffreestanding -fno-tree-slp-vectorize -nostdinc -nostdlib -mstrict-align -mcpu=cortex-a53+nosimd -Wno-missing-braces

all: kernel.img

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.S
	clang --target=aarch64-elf $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	clang --target=aarch64-elf $(CFLAGS) $(INCLUDES) -c $< -o $@

#asm/%.S: $(SRC_DIR)/%.c
#	mkdir -p $(@D)
#	clang -S --target=aarch64-elf $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(RES)
	ld.lld -m aarch64elf -r -b binary -o $@ $<

kernel.img: $(OBJS)
	mkdir -p $(BUILD_DIR)
	ld.lld -m aarch64elf -nostdlib $(OBJS) -T link.ld -o $(BUILD_DIR)/kernel.elf
	llvm-objcopy -O binary $(BUILD_DIR)/kernel.elf $(BUILD_DIR)/kernel.img

clean:
	rm $(BUILD_DIR)/kernel.* >/dev/null 2>/dev/null || true
	rm -fr $(OBJ_DIR) >/dev/null 2>/dev/null || true

run: kernel.img
	qemu-system-aarch64 -M raspi3 -kernel $(BUILD_DIR)/kernel.img -serial null -serial stdio -usb
