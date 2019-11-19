OBJ_DIR=objects
SRC_DIR=src
BUILD_DIR=../build

SRCS = $(wildcard $(SRC_DIR)/*.c)
SRCS += $(wildcard $(SRC_DIR)/io/*.c)
SRCS += $(wildcard $(SRC_DIR)/std/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
OBJS += $(OBJ_DIR)/start.o
OBJS += $(OBJ_DIR)/font.o
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -mcpu=cortex-a53+nosimd

INCLUDES = -I src -I src/std

all: kernel.img

$(OBJ_DIR)/start.o: start.S
	clang --target=aarch64-elf $(CFLAGS) -c start.S -o $(OBJ_DIR)/start.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	clang --target=aarch64-elf $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/font.o: res/font.psf
	ld.lld -m aarch64elf -r -b binary -o $(OBJ_DIR)/font.o res/font.psf

kernel.img: clean $(OBJS) $(OBJ_DIR)/font.o
	mkdir -p $(BUILD_DIR)
	ld.lld -m aarch64elf -nostdlib $(OBJS) -T link.ld -o $(BUILD_DIR)/kernel.elf
	llvm-objcopy -O binary $(BUILD_DIR)/kernel.elf $(BUILD_DIR)/kernel.img

clean:
	rm $(BUILD_DIR)/kernel.* $(OBJ_DIR)/*.o $(OBJ_DIR)/*/*.o >/dev/null 2>/dev/null || true

run: kernel.img
	qemu-system-aarch64 -M raspi3 -kernel $(BUILD_DIR)/kernel.img -serial null -serial stdio 
