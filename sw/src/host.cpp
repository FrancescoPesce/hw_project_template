#include <ap_int.h>
#include "KernelMem2Stream.hpp"
#include "KernelStream2Mem.hpp"
#include "utils.hpp"

int checkResult(ap_uint<WIDTH>* input, ap_uint<WIDTH>* output, int size) {
    for (int i = 0; i < size; i++) {
        if (input[i] != output[i]) {
            std::cout << "Error at index " << i
                      << ": " << input[i]
                      << " != " << output[i] << std::endl;
            return EXIT_FAILURE;
        }
    }
    std::cout << "Test passed!" << std::endl;
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
    // 1. Initialize the device and load the xclbin.
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <XCLBIN_PATH>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string xclbin_file = argv[1];

    char *env_emu = getenv("XCL_EMULATION_MODE");
    if (env_emu && std::string(env_emu) == "hw_emu") {
        std::cout << utils::bold_on << "Program running in hardware emulation mode" << utils::bold_off << std::endl;
    }
    else {
        std::cout << utils::bold_on << "Program running in hardware mode" << utils::bold_off << std::endl;
    }

    constexpr int device_id = 0;
    std::cout << "1. Loading bitstream (" << xclbin_file << ") on device " << device_id << "... ";
    xrt::device device = xrt::device(device_id);
    xrt::uuid xclbin_uuid = device.load_xclbin(xclbin_file);

    // 2. Set up the kernels (passthrough is free-running, so no need to do anything for it).
    std::cout << "Preparing the kernels" << std::endl;
    KernelMem2Stream mem2stream(device, xclbin_uuid);
    KernelStream2Mem stream2mem(device, xclbin_uuid);

    // 3. Prepare kernel inputs.
    std::cout << "Preparing kernel inputs" << std::endl;
    const uint32_t size = 32;
    ap_uint<WIDTH> input[size];
    for (uint32_t i = 0; i < size; i++) {
        input[i] = i * 2;
    }

    // 4. Transfer data to the kernels.
    std::cout << "Transferring data to the kernels" << std::endl;
    mem2stream.set_inputs(input, size);
    stream2mem.set_inputs(size);

    // 5. Launch the kernels.
    std::cout << "Launching the kernels" << std::endl;
    mem2stream.launch();
    stream2mem.launch();

    // 6. Wait for the kernels to finish.
    std::cout << "Waiting for kernel runs to finish" << std::endl;
    mem2stream.wait_on_run();
    stream2mem.wait_on_run();
    
    // 6. Transfer results from the kernel.
    std::cout << "Transferring results from the kernels" << std::endl;
    ap_uint<WIDTH> output[size];
    stream2mem.get_outputs(output);

    // 7. Check the results.
    std::cout << "Checking results" << std::endl;
    return checkResult(input, output, size);
}