# HW Project template

Template for projects for AMD Alveo boards using the Vitis flow. Strongly inspired by voted[https://github.com/necst/voted], with Versal-specific features removed and additional features for RTL sources.

## Content

- `sw`: Host code sources and Makefile. Hardware execution and hardware emulation environment.
- `hw`: FPGA design sources and relative unit tests and Makefiles. It contains sources from `hls`, `rtl` and `tcl`.
- `link`: Options and Makefile to link different FPGA kernels and generate the `.xclbin` for Vitis.
- `common`: C/C++ include files to be accessed by multiple targets.
