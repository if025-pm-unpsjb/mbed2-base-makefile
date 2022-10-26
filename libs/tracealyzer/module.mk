ifeq ($(USE_TRACEALYZER),y)

TRACE_BASE=./libs/tracealyzer

SRC+=$(wildcard $(TRACE_BASE)/*.c)
INCLUDE_PATHS += -I$(TRACE_BASE)/include
INCLUDE_PATHS += -I$(TRACE_BASE)/config

endif
