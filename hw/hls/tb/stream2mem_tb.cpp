#include "stream2mem.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
    // Create test inputs.
    const uint32_t size = 32;

    ap_uint<WIDTH> input[size];
    for (uint32_t i = 0; i < size; i++) {
        input[i] = i + 1;
    }

    // Create correct (golden) outputs.
    ap_uint<WIDTH> golden_output[size];
    for (uint32_t i = 0; i < size; i++) {
        golden_output[i] = input[i];
    }

    hls::stream<ap_uint<WIDTH>> input_stream;
    ap_uint<WIDTH> output[size];

    // Write the inputs into the stream.
    for (uint32_t words_written = 0; words_written < size; words_written++) {
        input_stream.write(input[words_written]);
    }

    // Run the kernel as a C++ function.
    stream2mem(output, input_stream, size);

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