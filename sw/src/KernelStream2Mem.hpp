#ifndef KERNEL_STREAM_2_MEM_HPP
#define KERNEL_STREAM_2_MEM_HPP

#include <string>
#include "experimental/xrt_kernel.h"
#include "experimental/xrt_uuid.h"
#include "../../common/defines.hpp"

class KernelStream2Mem {
    public:
        // Create XRT objects for device, kernel and run.
        KernelStream2Mem(xrt::device device, xrt::uuid xclbin_uuid)
            : device(device) {
            // Create kernel object from the xclbin.
            krnl = xrt::kernel(device, xclbin_uuid, kernel_name.c_str());

            // Create a run object for the kernel.
            run = xrt::run(krnl);
        }

        // Set kernel arguments and write input data to the device.
        void set_inputs(uint32_t size) {
            // Set banks for the output buffer.
            xrtMemoryGroup bank_output = krnl.group_id(arg_output);

            // Create the output buffer.
            buf_out = xrt::bo(device, size * WIDTH / 8, xrt::bo::flags::normal, bank_output);
            
            // Set kernel arguments.
            run.set_arg(arg_output, buf_out);
            run.set_arg(arg_size, size);
        }

        // Get output data from the device.
        void get_outputs(ap_uint<WIDTH>* output) {
            buf_out.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
            buf_out.read(output);
        }

        // Launch the kernel (non-blocking).
        void launch() {
            run.start();
        }

        // Wait for the kernel to finish.
        void wait_on_run() {
            run.wait();
        }

    private:
        // Name of the kernel, must match the name chosen in hw.
        inline static const std::string kernel_name = "stream2mem";

        // Indices of kernel arguments, must match the order in hw.
        static constexpr int arg_output = 0;
        static constexpr int arg_size   = 2;

        // XRT objects for device, kernel, buffers, and run.
        xrt::device device;
        xrt::kernel krnl;
        xrt::bo buf_out;
        xrt::run run;
};

#endif // KERNEL_STREAM_2_MEM_HPP