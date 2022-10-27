ifeq ($(USE_BSP_DISCO_F746NG),y)

BSP_DISCO_F746NG_BASE=./libs/BSP_DISCO_F746NG

SRC+=$(wildcard $(BSP_DISCO_F746NG_BASE)/Drivers/BSP/Components/ft5336/*.c)
SRC+=$(wildcard $(BSP_DISCO_F746NG_BASE)/Drivers/BSP/Components/ov9655/*.c)
SRC+=$(wildcard $(BSP_DISCO_F746NG_BASE)/Drivers/BSP/Components/wm8994/*.c)
SRC+=$(wildcard $(BSP_DISCO_F746NG_BASE)/Drivers/BSP/STM32746G-Discovery/*.c)
SRC+=$(wildcard $(BSP_DISCO_F746NG_BASE)/Utilities/Fonts/*.c)
SRC+=$(wildcard $(BSP_DISCO_F746NG_BASE)/BSP/STM32*.c)

INCLUDE_PATHS += -I$(BSP_DISCO_F746NG_BASE)/Utilities/Fonts
INCLUDE_PATHS += -I$(BSP_DISCO_F746NG_BASE)/Drivers/BSP/Components/Common
INCLUDE_PATHS += -I$(BSP_DISCO_F746NG_BASE)/Drivers/BSP/Components/ft5336
INCLUDE_PATHS += -I$(BSP_DISCO_F746NG_BASE)/Drivers/BSP/Components/n25q128a
INCLUDE_PATHS += -I$(BSP_DISCO_F746NG_BASE)/Drivers/BSP/Components/ov9655
INCLUDE_PATHS += -I$(BSP_DISCO_F746NG_BASE)/Drivers/BSP/Components/rk043fn48h
INCLUDE_PATHS += -I$(BSP_DISCO_F746NG_BASE)/Drivers/BSP/Components/wm8994
INCLUDE_PATHS += -I$(BSP_DISCO_F746NG_BASE)/Drivers/BSP/STM32746G-Discovery

endif
