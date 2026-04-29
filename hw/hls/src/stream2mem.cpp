#include "stream2mem.hpp"
    
extern "C" {

void stream2mem(ap_uint<WIDTH>* m_axi, hls::stream<ap_uint<WIDTH>>& s_axis, uint32_t size) {
#pragma HLS interface m_axi port=m_axi depth=32 offset=slave bundle=gmem0
#pragma HLS interface axis port=s_axis
#pragma HLS interface s_axilite port=m_axi bundle=control
#pragma HLS interface s_axilite port=size bundle=control
#pragma HLS interface s_axilite port=return bundle=control

    for (uint32_t i = 0; i < size; i++) {
#pragma HLS pipeline II=1
        m_axi[i] = s_axis.read();
    }
}

}