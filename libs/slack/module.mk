ifeq ($(USE_SLACK),y)

DEFINES+=USE_SLACK

INCLUDE_PATHS += -I./libs/slack/
INCLUDE_PATHS += -I./libs/slack/$(FREERTOS_VERSION)

# Replace these functions
ifeq ($(FREERTOS_VERSION), 10.0.1)
WRAP = -Wl,--wrap=vTaskDelayUntil -Wl,--wrap=xTaskIncrementTick
endif
ifeq ($(FREERTOS_VERSION), 10.4.1)
WRAP = -Wl,--wrap=vTaskDelayUntil -Wl,--wrap=xTaskIncrementTick
endif
ifeq ($(FREERTOS_VERSION), 10.4.6)
WRAP = -Wl,--wrap=xTaskDelayUntil -Wl,--wrap=xTaskIncrementTick
endif

endif
