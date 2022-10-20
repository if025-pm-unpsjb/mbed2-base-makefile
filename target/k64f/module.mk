###############################################################################
#
# Other object files required.
#
SYS_OBJECTS += $(wildcard ./target/k64f/TOOLCHAIN_GCC_ARM/*.o)

###############################################################################
#
# Paths to the required headers.
#
INCLUDE_PATHS += -I./libs/mbed
INCLUDE_PATHS += -I./libs/mbed/drivers
INCLUDE_PATHS += -I./libs/mbed/hal
INCLUDE_PATHS += -I./libs/mbed/platform
INCLUDE_PATHS += -I./target/k64f
INCLUDE_PATHS += -I./target/k64f/TARGET_Freescale
INCLUDE_PATHS += -I./target/k64f/TARGET_Freescale/TARGET_KSDK2_MCUS
INCLUDE_PATHS += -I./target/k64f/TARGET_Freescale/TARGET_KSDK2_MCUS/api
INCLUDE_PATHS += -I./target/k64f/TARGET_Freescale/TARGET_KSDK2_MCUS/TARGET_MCU_K64F
INCLUDE_PATHS += -I./target/k64f/TARGET_Freescale/TARGET_KSDK2_MCUS/TARGET_MCU_K64F/device
INCLUDE_PATHS += -I./target/k64f/TARGET_Freescale/TARGET_KSDK2_MCUS/TARGET_MCU_K64F/drivers
INCLUDE_PATHS += -I./target/k64f/TARGET_Freescale/TARGET_KSDK2_MCUS/TARGET_MCU_K64F/TARGET_FRDM

###############################################################################
#
# Paths to the required libraries.
#
LIBRARY_PATHS += -L./target/k64f/TOOLCHAIN_GCC_ARM
LIBRARIES = -lmbed

###############################################################################
#
# Linker script used to build the binary.
#
LINKER_SCRIPT = ./target/k64f/TOOLCHAIN_GCC_ARM/MK64FN1M0xxx12.ld

###############################################################################
#
# Floating point
#
ifeq ($(HARDFP),1)
	FLOAT_ABI = hard
else
	FLOAT_ABI = softfp
endif

###############################################################################
#
# CPU info.
#
CPU = -mcpu=cortex-m4 \
	-mthumb \
	-mfpu=fpv4-sp-d16 \
	-mfloat-abi=$(FLOAT_ABI)

###############################################################################
#
# Common flags and symbols used by the compiler for all the examples.
#
COMMON_FLAGS += $(CPU) \
	-c \
	-g \
	-Wall \
	-fno-common \
	-fmessage-length=0 \
	-fno-exceptions \
	-fno-builtin \
	-ffunction-sections \
	-fdata-sections \
	-funsigned-char \
	-fno-delete-null-pointer-checks \
	-fomit-frame-pointer \
	-MMD \
	-MP

C_COMMON_FLAGS += -std=gnu99

CPP_COMMON_FLAGS += -fno-rtti \
	-include mbed_config.h \
	-std=gnu++98

###############################################################################
#
# Flags and symbols required by the compiler.
#
CC_SYMBOLS += -D__MBED__=1 
CC_SYMBOLS += -DDEVICE_I2CSLAVE=1
CC_SYMBOLS += -D__FPU_PRESENT=1
CC_SYMBOLS += -DTARGET_Freescale
CC_SYMBOLS += -DDEVICE_PORTINOUT=1
CC_SYMBOLS += -DTARGET_RTOS_M4_M7
CC_SYMBOLS += -DDEVICE_LOWPOWERTIMER=1
CC_SYMBOLS += -DDEVICE_RTC=1
CC_SYMBOLS += -DTOOLCHAIN_object
CC_SYMBOLS += -D__CMSIS_RTOS
CC_SYMBOLS += -DFSL_RTOS_MBED
CC_SYMBOLS += -DDEVICE_STORAGE=1
CC_SYMBOLS += -DMBEDTLS_ENTROPY_HARDWARE_ALT
CC_SYMBOLS += -DTARGET_KPSDK_MCUS
CC_SYMBOLS += -DTOOLCHAIN_GCC
CC_SYMBOLS += -DTARGET_CORTEX_M
CC_SYMBOLS += -DTARGET_KSDK2_MCUS
CC_SYMBOLS += -DTARGET_LIKE_CORTEX_M4
CC_SYMBOLS += -DDEVICE_ANALOGOUT=1
CC_SYMBOLS += -DTARGET_M4
CC_SYMBOLS += -DTARGET_UVISOR_UNSUPPORTED
CC_SYMBOLS += -DTARGET_K64F
CC_SYMBOLS += -DDEVICE_SERIAL=1
CC_SYMBOLS += -DMBED_BUILD_TIMESTAMP=1482431125.39
CC_SYMBOLS += -DDEVICE_INTERRUPTIN=1
CC_SYMBOLS += -DDEVICE_I2C=1
CC_SYMBOLS += -DDEVICE_PORTOUT=1
CC_SYMBOLS += -D__CORTEX_M4
CC_SYMBOLS += -DDEVICE_STDIO_MESSAGES=1
CC_SYMBOLS += -DCPU_MK64FN1M0VMD12
CC_SYMBOLS += -DFEATURE_IPV4=1
CC_SYMBOLS += -DTARGET_LIKE_MBED
CC_SYMBOLS += -DTARGET_FF_ARDUINO
CC_SYMBOLS += -DTARGET_KPSDK_CODE
CC_SYMBOLS += -DTARGET_RELEASE
CC_SYMBOLS += -DDEVICE_SERIAL_FC=1
CC_SYMBOLS += -DFEATURE_STORAGE=1
CC_SYMBOLS += -D__MBED_CMSIS_RTOS_CM
CC_SYMBOLS += -DDEVICE_SLEEP=1
CC_SYMBOLS += -DTOOLCHAIN_GCC_ARM
CC_SYMBOLS += -DTARGET_FRDM
CC_SYMBOLS += -DDEVICE_SPI=1
CC_SYMBOLS += -DDEVICE_ERROR_RED=1
CC_SYMBOLS += -DDEVICE_SPISLAVE=1
CC_SYMBOLS += -DDEVICE_ANALOGIN=1
CC_SYMBOLS += -DDEVICE_PWMOUT=1
CC_SYMBOLS += -DDEVICE_PORTIN=1
CC_SYMBOLS += -DTARGET_MCU_K64F
CC_SYMBOLS += -DARM_MATH_CM4 

###############################################################################
#
# Flags and symbols required by the linker.
#
LD_FLAGS += $(CPU) \
	-Wl,--gc-sections \
	-Wl,--wrap,main \
	-u _printf_float \
	-u _scanf_float

LD_SYS_LIBS += -lstdc++ \
	-lsupc++ \
	-lm \
	-lc \
	-lgcc \
	-lnosys 

