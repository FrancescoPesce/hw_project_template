#include "passthrough.hpp"
    
extern "C" {

void passthrough(hls::stream<ap_uint<WIDTH>>& s_axis, hls::stream<ap_uint<WIDTH>>& m_axis) {
#pragma HLS interface mode=ap_ctrl_none port=return
#pragma HLS interface axis port=s_axis
#pragma HLS interface axis port=m_axis

    while (true) {
#pragma HLS pipeline II=1
    m_axis.write(s_axis.read());
    }
}

}