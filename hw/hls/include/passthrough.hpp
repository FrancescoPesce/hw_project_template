#ifndef PASSTHROUGH_HPP
#define PASSTHROUGH_HPP

#include <ap_int.h>
#include <cstdint>
#include <hls_stream.h>
#include "defines.hpp"

// Free-running kernel that copies data from s_axis to m_axis.

extern "C" {
    void passthrough(hls::stream<ap_uint<WIDTH>>& s_axis, hls::stream<ap_uint<WIDTH>>& m_axis);
}

#endif // PASSTHROUGH_HPP