#ifndef FFT_H
#define FFT_H

#include "libesp.h"

typedef int16_t q15_t;

int32_t fft_fixed_cfft(q15_t *real, q15_t *imag, unsigned log2_len, bool inverse);

#endif // FFT_H