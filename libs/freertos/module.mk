ifeq ($(USE_FREERTOS),y)

DEFINES+=USE_FREERTOS
DEFINES+=TICK_OVER_RTOS

FREERTOS_BASE=./libs/freertos/$(FREERTOS_VERSION)

SRC+=$(wildcard $(FREERTOS_BASE)/*.c)
ifeq ($(TARGET),lpc1768)
SRC+=$(wildcard $(FREERTOS_BASE)/portable/ARM_CM3/*.c)
endif
ifeq ($(TARGET),k64f)
SRC+=$(wildcard $(FREERTOS_BASE)/portable/ARM_CM4F/*.c)
endif
ifeq ($(TARGET),f746ng)
SRC+=$(wildcard $(FREERTOS_BASE)/portable/ARM_CM7/r0p1/*.c)
endif
SRC+=$(FREERTOS_BASE)/MemMang/heap_$(FREERTOS_HEAP_TYPE).c

INCLUDE_PATHS += -I$(FREERTOS_BASE)/include
ifeq ($(TARGET),lpc1768)
INCLUDE_PATHS += -I$(FREERTOS_BASE)/portable/ARM_CM3
endif
ifeq ($(TARGET),k64f)
INCLUDE_PATHS += -I$(FREERTOS_BASE)/portable/ARM_CM4F
endif
ifeq ($(TARGET),f746ng)
INCLUDE_PATHS += -I$(FREERTOS_BASE)/portable/ARM_CM7/r0p1
endif

endif
