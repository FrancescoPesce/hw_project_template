#ifndef MEM_2_STREAM_HPP
#define MEM_2_STREAM_HPP

#include <ap_int.h>
#include <cstdint>
#include <hls_stream.h>
#include "defines.hpp"

// Kernel that copies "size" words of "WIDTH" bits from the memory to m_axis.

extern "C" {
    void mem2stream(ap_uint<WIDTH>* m_axi, hls::stream<ap_uint<WIDTH>>& m_axis, uint32_t size);
}

#endif // MEM_2_STREAM_HPP