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

.PHONY: all help

PLATFORM := xilinx_u250_gen3x16_xdma_4_1_202210_1
DEVICE := xcu250-figd2104-2L-e
TARGET := hw_emu
FREQUENCY := 200

XCLBIN  := overlay_$(TARGET).xclbin

all: $(XCLBIN)

help:
	$(ECHO) "Makefile Usage:"
	$(ECHO) "  make all"
	$(ECHO) ""
	$(ECHO) "  make clean"
	$(ECHO) "      Remove all the generated files."
	$(ECHO) ""

# Use --optimize 3 to enable post-route optimizations. This may improve the bitstream but SIGNIFICANTLY increase compilation time
XOCCLFLAGS := --kernel_frequency $(FREQUENCY) -s -g
XOS        := $(abspath $(wildcard ../hw/hls/build/$(TARGET)/*.xo))
CONFIG     := xclbin_overlay.cfg

$(XCLBIN): $(XOS)
	mkdir -p build
	cd build; \
		v++ -l $(XOCCLFLAGS) --config ../$(CONFIG) -t $(TARGET) -f $(PLATFORM) $(XOS) -o $(XCLBIN)

clean:
	$(RM) -rf build
