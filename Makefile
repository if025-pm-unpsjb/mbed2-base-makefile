# This file is based on the Makefile automagically generated by mbed.org.

BUILD_DIR = ./build

PROJ = blink

SRC=$(wildcard ./app/$(PROJ)/*.c)
CXXSRC=$(wildcard ./app/$(PROJ)/*.cpp)
OBJECTS += $(CXXSRC:%.cpp=%.o) $(SRC:%.c=%.o)

OBJECTS += ./funcs.o

SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/analogin_api.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/analogout_api.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/can_api.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/cmsis_nvic.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/ethernet_api.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/gpio_api.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/gpio_irq_api.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/i2c_api.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/mbed_board.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/mbed_retarget.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/pinmap.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/port_api.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/pwmout_api.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/rtc_api.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/serial_api.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/sleep.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/spi_api.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/startup_LPC17xx.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/system_LPC17xx.o
SYS_OBJECTS += ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/us_ticker.o

MBED_INCLUDE_PATHS += -I./mbed
MBED_INCLUDE_PATHS += -I./mbed/drivers
MBED_INCLUDE_PATHS += -I./mbed/hal
MBED_INCLUDE_PATHS += -I./mbed/platform

MBED_INCLUDE_PATHS += -I./mbed/TARGET_LPC1768
MBED_INCLUDE_PATHS += -I./mbed/TARGET_LPC1768/TARGET_NXP
MBED_INCLUDE_PATHS += -I./mbed/TARGET_LPC1768/TARGET_NXP/TARGET_LPC176X/
MBED_INCLUDE_PATHS += -I./mbed/TARGET_LPC1768/TARGET_NXP/TARGET_LPC176X/device
MBED_INCLUDE_PATHS += -I./mbed/TARGET_LPC1768/TARGET_NXP/TARGET_LPC176X/TARGET_MBED_LPC1768

INCLUDE_PATHS += -I./
INCLUDE_PATHS += $(MBED_INCLUDE_PATHS) 

LIBRARY_PATHS += -L./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM
LIBRARIES = -lmbed

LINKER_SCRIPT = ./mbed/TARGET_LPC1768/TOOLCHAIN_GCC_ARM/LPC1768.ld

CPU += -mcpu=cortex-m3 
CPU += -mthumb

CC_FLAGS += $(CPU) 
CC_FLAGS += -c
CC_FLAGS += -g
CC_FLAGS += -fno-common
CC_FLAGS += -fmessage-length=0
CC_FLAGS += -Wall
CC_FLAGS += -fno-exceptions
CC_FLAGS += -ffunction-sections
CC_FLAGS += -fdata-sections
CC_FLAGS += -fomit-frame-pointer
CC_FLAGS += -fno-rtti
CC_FLAGS += -include mbed_config.h
CC_FLAGS += -MMD
CC_FLAGS += -MP

CC_SYMBOLS += -DTARGET_LPC1768
CC_SYMBOLS += -DTARGET_M3
CC_SYMBOLS += -DTARGET_NXP
CC_SYMBOLS += -DTARGET_LPC176X
CC_SYMBOLS += -DTARGET_MBED_LPC1768
CC_SYMBOLS += -DTOOLCHAIN_GCC_ARM
CC_SYMBOLS += -DTOOLCHAIN_GCC
CC_SYMBOLS += -D__CORTEX_M3
CC_SYMBOLS += -DARM_MATH_CM3
CC_SYMBOLS += -DMBED_BUILD_TIMESTAMP=1414254042.69
CC_SYMBOLS += -D__MBED__=1

LD_FLAGS += $(CPU)
LD_FLAGS += -Wl,--gc-sections
LD_FLAGS += -u _printf_float
LD_FLAGS += -u _scanf_float

LD_SYS_LIBS += -lstdc++
LD_SYS_LIBS += -lsupc++
LD_SYS_LIBS += -lm
LD_SYS_LIBS += -lc
LD_SYS_LIBS += -lgcc
LD_SYS_LIBS += -lnosys

ifeq ($(DEBUG), 1)
  CC_FLAGS += -DDEBUG -O0
else
  CC_FLAGS += -DNDEBUG -Os
endif

############################################################################### 
GCC_BIN =
AS      = $(GCC_BIN)arm-none-eabi-as
CC      = $(GCC_BIN)arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy
SIZE    = $(GCC_BIN)arm-none-eabi-size

all: $(BUILD_DIR)/$(PROJ).bin size

clean:
	+@echo "Cleaning files..."	
	@rm -f $(BUILD_DIR)/$(PROJ).bin $(BUILD_DIR)/$(PROJ).elf $(OBJECTS) $(DEPS)

.cpp.o:
	+@echo "Compile: $<"
	@$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++98 $(INCLUDE_PATHS) -g -o $@ $<	

$(BUILD_DIR)/$(PROJ).elf: $(OBJECTS) $(SYS_OBJECTS)
	+@echo "Linking: $@"
	@$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS)

$(BUILD_DIR)/$(PROJ).bin: $(BUILD_DIR)/$(PROJ).elf
	+@echo "Binary: $@"	
	@$(OBJCOPY) -O binary $< $@
	
size: $(BUILD_DIR)/$(PROJ).elf
	$(SIZE) $<

DEPS = $(OBJECTS:.o=.d) $(SYS_OBJECTS:.o=.d)
-include $(DEPS)
