ECHO=@echo

.PHONY: help clean hls all

PLATFORM := xilinx_u250_gen3x16_xdma_4_1_202210_1
DEVICE := xcu250-figd2104-2L-e
TARGET := hw_emu

all: hls

help:
	$(ECHO) "Makefile Usage:"
	$(ECHO) "  make all"
	$(ECHO) ""
	$(ECHO) "  make clean"
	$(ECHO) "      Remove all the generated files."
	$(ECHO) ""

################## call other makefiles
HLS_BUILD_COMMAND := $(MAKE) -C hls xo PLATFORM=$(PLATFORM) DEVICE=$(DEVICE) TARGET=$(TARGET)

hls:
	$(HLS_BUILD_COMMAND) KERNEL=mem2stream
	$(HLS_BUILD_COMMAND) KERNEL=passthrough
	$(HLS_BUILD_COMMAND) KERNEL=stream2mem

################## clean up
clean:
	$(MAKE) -C hls clean