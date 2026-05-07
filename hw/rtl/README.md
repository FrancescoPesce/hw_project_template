# RTL

Sources and builds for RTL kernels. RTL kernels can be used for both:
- the Vitis flow (`make xo`) 
- the Vivado flow (no need to build)
Currently, `make xo` creates a kernel with the same name as the specified module, which must be named in the same way as the `.v` file where it is defined. `make xo` assumes that the kernel is `ap_ctrl_none`, and that it has a slave AXIS interface named `s_axis` and a master AXIS interface named `m_axis`.