###############################################################################
#
# Other object files required.
#
OBJECTS += ./libs/mbed/funcs.o
SYS_OBJECTS += $(wildcard ./target/lpc1768/TOOLCHAIN_GCC_ARM/*.o)

###############################################################################
#
# Paths to the required headers.
#
INCLUDE_PATHS += -I./libs/mbed
INCLUDE_PATHS += -I./libs/mbed/drivers
INCLUDE_PATHS += -I./libs/mbed/hal
INCLUDE_PATHS += -I./libs/mbed/platform
INCLUDE_PATHS += -I./target/lpc1768
INCLUDE_PATHS += -I./target/lpc1768/TARGET_NXP
INCLUDE_PATHS += -I./target/lpc1768/TARGET_NXP/TARGET_LPC176X/
INCLUDE_PATHS += -I./target/lpc1768/TARGET_NXP/TARGET_LPC176X/device
INCLUDE_PATHS += -I./target/lpc1768/TARGET_NXP/TARGET_LPC176X/TARGET_MBED_LPC1768

###############################################################################
#
# Paths to the required libraries.
#
LIBRARY_PATHS += -L./target/lpc1768/TOOLCHAIN_GCC_ARM
LIBRARIES = -lmbed

###############################################################################
#
# Linker script used to build the binary.
#
LINKER_SCRIPT = ./target/lpc1768/TOOLCHAIN_GCC_ARM/LPC1768.ld

###############################################################################
#
# CPU info.
#
CPU += -mcpu=cortex-m3 
CPU += -mthumb

###############################################################################
#
# Common flags and symbols used by the compiler for all the examples.
#
COMMON_FLAGS += $(CPU)
COMMON_FLAGS += -c
COMMON_FLAGS += -g
COMMON_FLAGS += -Wall
COMMON_FLAGS += -fno-common
COMMON_FLAGS += -fmessage-length=0
COMMON_FLAGS += -fno-exceptions
COMMON_FLAGS += -fno-builtin
COMMON_FLAGS += -ffunction-sections
COMMON_FLAGS += -fdata-sections
COMMON_FLAGS += -funsigned-char
COMMON_FLAGS += -fno-delete-null-pointer-checks
COMMON_FLAGS += -fomit-frame-pointer
COMMON_FLAGS += -MMD
COMMON_FLAGS += -MP

C_COMMON_FLAGS += -std=gnu99
CPP_COMMON_FLAGS += -fno-rtti
CPP_COMMON_FLAGS += -include mbed_config.h
CPP_COMMON_FLAGS += -std=gnu++98

###############################################################################
#
# Flags and symbols required by the compiler.
#
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

###############################################################################
#
# Flags and symbols required by the linker.
#
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

