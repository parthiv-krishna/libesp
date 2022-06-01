# Makefile to build libesp.a

TOOLCHAIN = riscv-none-embed
CC = $(TOOLCHAIN)-gcc
OBJDUMP = $(TOOLCHAIN)-objdump
OBJCOPY = $(TOOLCHAIN)-objcopy
AR = $(TOOLCHAIN)-ar

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

INCLUDE = -I$(INCLUDE_DIR)
SRC = $(wildcard $(SRC_DIR)/*.[Sc])
OBJS := $(SRC:.c=.o)
OBJS := $(OBJS:.S=.o)
OBJS := $(foreach o, $(OBJS), $(BUILD_DIR)/$(notdir $o))

OPT_LEVEL = -O3
CFLAGS = $(OPT_LEVEL) $(INCLUDE) -g -Wall -Werror -Wno-unused-function
ASFLAGS = -march=rv32im

all: libesp.a

libesp.a: $(OBJS) Makefile
	@rm -rf $@
	$(AR) cDr $@ $(OBJS)

builddir:
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c builddir
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S builddir
	$(CC) -c $(ASFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR) libesp.a

.PHONY: all clean monitor
