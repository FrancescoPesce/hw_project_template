#include "mem2stream.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
    // Create test inputs.
    const uint32_t size = 32;

    ap_uint<WIDTH> input[size];
    for (uint32_t i = 0; i < size; i++) {
        input[i] = i * i;
    }

    // Create correct (golden) outputs.
    ap_uint<WIDTH> golden_output[size];
    for (uint32_t i = 0; i < size; i++) {
        golden_output[i] = input[i];
    }

    hls::stream<ap_uint<WIDTH>> output_stream;

    // Run the kernel as a C++ function.
    mem2stream(input, output_stream, size);

    // Read the outputs from the stream.
    ap_uint<WIDTH> output[size];
    for (uint32_t words_read = 0; words_read < size; words_read++) {
        output[words_read] = output_stream.read();
    }

    // Check the results.
    bool pass = true;
    for (uint32_t i = 0; i < size; i++) {
        if (output[i] != golden_output[i]) {
            std::cout << "Mismatch at index " << i << ": expected " << golden_output[i] << ", got " << output[i] << std::endl;
            pass = false;
        }
    }

    if (pass) {
        std::cout << "Test passed!" << std::endl;
    } else {
        std::cout << "Test failed!" << std::endl;
    }

    return 0;
}