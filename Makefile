ECHO=@echo

.PHONY: all help clean hw sw link

PLATFORM := xilinx_u250_gen3x16_xdma_4_1_202210_1
DEVICE := xcu250-figd2104-2L-e
TARGET := hw_emu

################## call other makefiles
all: sw hw link

help:
	$(ECHO) "Makefile Usage:"
	$(ECHO) "  make all"
	$(ECHO) ""
	$(ECHO) "  make clean"
	$(ECHO) "      Remove all the generated files."
	$(ECHO) ""

sw:
	$(MAKE) -C sw

hw:
	$(MAKE) -C hw PLATFORM=$(PLATFORM) DEVICE=$(DEVICE) TARGET=$(TARGET)

link:
	$(MAKE) -C link

################## clean up
clean:
	$(MAKE) -C sw clean
	$(MAKE) -C hw clean
	$(MAKE) -C link clean
