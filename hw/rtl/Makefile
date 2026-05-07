# MIT License

# Copyright (c) 2023 Paolo Salvatore Galfano, Giuseppe Sorrentino

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

ECHO=@echo

.PHONY: help clean xo

PLATFORM := xilinx_u250_gen3x16_xdma_4_1_202210_1
DEVICE := xcu250-figd2104-2L-e
KERNEL := passthrough_rtl
	
help:
	$(ECHO) "Makefile Usage:"
	$(ECHO) ""
	$(ECHO) "  make xo"
	$(ECHO) "      Generate the xo kernel file."
	$(ECHO) ""
	$(ECHO) "  make clean"
	$(ECHO) "      Remove all the generated files."



KERNEL_SRC     := src/$(KERNEL).v

################## Vitis build

KERNEL_XO_BASE := $(KERNEL).xo
PACKAGING_DIR := build/package
KERNEL_XO := $(PACKAGING_DIR)/$(KERNEL_XO_BASE)

PACKAGING_PROJ_NAME := $(KERNEL)_prj
PACKAGING_PROJ_DIR := $(PACKAGING_DIR)/$(PACKAGING_PROJ_NAME)

# Prepare project directory for Vivado, as expected by the build.tcl script.
$(PACKAGING_PROJ_DIR): $(KERNEL_SRC)
	@mkdir -p $(PACKAGING_PROJ_DIR)
	cp $(KERNEL_SRC) $(PACKAGING_PROJ_DIR)
	cp build.tcl $(PACKAGING_DIR);

# Create a .xo for the RTL kernel.
$(KERNEL_XO): $(PACKAGING_PROJ_DIR)
	@cd $(PACKAGING_DIR); \
	    CMD="vivado -mode batch -source build.tcl -tclargs $(KERNEL) $(PACKAGING_PROJ_NAME) $(DEVICE)"; \
	    echo $$CMD; \
	    $$CMD

xo: $(KERNEL_XO)

################## clean up
clean:
	$(RM) -rf build