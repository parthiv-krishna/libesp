
# Toolchain
TOOLCHAIN = riscv-none-embed
CC = $(TOOLCHAIN)-gcc
OBJDUMP = $(TOOLCHAIN)-objdump
OBJCOPY = $(TOOLCHAIN)-objcopy
AR = $(TOOLCHAIN)-ar

# Library files
LIBESP = $(LIBESP_PATH)/libesp.a
MEMMAP = $(LIBESP_PATH)/memmap
INCLUDES += -I$(LIBESP_PATH)/include

# Flags
WARNFLAGS = -W -Wall -Wextra -Werror -Wundef -Wshadow -Wdouble-promotion -fno-common -Wconversion
OPTFLAGS = -Os -g3 -ffunction-sections -fdata-sections
MCUFLAGS = -march=rv32imc -mabi=ilp32
LINKFLAGS = -T$(MEMMAP) -L$(LIBESP_PATH) -l:libesp.a -nostdlib -nostartfiles -Wl,--gc-sections

# Merged
CFLAGS = $(WARNFLAGS) $(OPTFLAGS) $(MCUFLAGS) $(INCLUDES) $(EXTRA_CFLAGS)
DEPS = $(SOURCES) $(HEADERS) $(LIBESP) Makefile

# Flash offset default to 0
OFFSET ?= 0

all: $(LIBESP) $(PROG).bin $(PROG).list

$(PROG).list: $(PROG).elf $(DEPS)
	$(OBJDUMP) -d $(PROG).elf > $(PROG).list

$(PROG).elf: $(SOURCES) $(HEADERS) $(DEPS)
	$(CC) $(CFLAGS) $(SOURCES) $(LINKFLAGS) -o $@

$(PROG).bin: $(PROG).elf $(DEPS)
	esp-install mkbin $< $@

$(LIBESP):
	make -C $(LIBESP_PATH)

clean:
	rm -rf *.bin *.elf *.o *.list

install: all
	esp-install flash $(OFFSET) $(PROG).bin

monitor:
	screen /dev/ttyUSB0 115200

.PHONY : all clean install monitor