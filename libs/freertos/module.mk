ifeq ($(USE_FREERTOS),y)

DEFINES+=USE_FREERTOS
DEFINES+=TICK_OVER_RTOS

FREERTOS_BASE=./libs/freertos

SRC+=$(wildcard $(FREERTOS_BASE)/*.c)
ifeq ($(TARGET),lpc1768)
SRC+=$(wildcard $(FREERTOS_BASE)/portable/ARM_CM3/*.c)
endif
ifeq ($(TARGET),k64f)
SRC+=$(wildcard $(FREERTOS_BASE)/portable/ARM_CM4F/*.c)
endif
SRC+=$(FREERTOS_BASE)/MemMang/heap_$(FREERTOS_HEAP_TYPE).c

INCLUDE_PATHS += -I$(FREERTOS_BASE)/include
ifeq ($(TARGET),lpc1768)
INCLUDE_PATHS += -I$(FREERTOS_BASE)/portable/ARM_CM3
endif
ifeq ($(TARGET),k64f)
INCLUDE_PATHS += -I$(FREERTOS_BASE)/portable/ARM_CM4F
endif

endif
