ifeq ($(USE_MAX7219),y)

MAX7219_BASE=./libs/MAX7219

CXXSRC+=$(wildcard $(MAX7219_BASE)/*.cpp)
INCLUDE_PATHS += -I$(MAX7219_BASE)

endif
