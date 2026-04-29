#ifndef STREAM_2_MEM_HPP
#define STREAM_2_MEM_HPP

#include <ap_int.h>
#include <cstdint>
#include <hls_stream.h>
#include "defines.hpp"

#define WIDTH 512

// Kernel that reads "size" words of "WIDTH" bits from s_axis and writes them to memory.

extern "C" {
    void stream2mem(ap_uint<WIDTH>* m_axi, hls::stream<ap_uint<WIDTH>>& s_axis, uint32_t size);
}

#endif // STREAM_2_MEM_HPP