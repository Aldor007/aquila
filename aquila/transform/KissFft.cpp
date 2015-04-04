/**
 * @file KissFft.cpp
 *
 * A wrapper for the FFT algorithm from KissFFT lib.
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2007-2014
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#include "KissFft.h"
#include <cmath>

namespace Aquila
{

    KissFft::KissFft(std::size_t length) :Fft(length), m_kfft(length, false), m_kfft_inverse(length, true) {

    }

    KissFft::~KissFft() {

    }

    SpectrumType KissFft::fft(const SampleType x[]) {

        static_assert(
            sizeof(ComplexType[2]) == sizeof(double[4]),
            "complex<double> has the same memory layout as two consecutive doubles"
        );
        // create a temporary storage array and copy input to even elements
        // of the array (real values), leaving imaginary components at 0
        ComplexType* a = new ComplexType[N];
        ComplexType* dst = new ComplexType[N];
        for (std::size_t i = 0; i < N; ++i)
        {
            a[i] = x[i];
        }

        // let's call the C function from  KissFFT libary
        m_kfft.transform(a, dst);

        // convert the array back to complex values and return as vector
        SpectrumType spectrum(dst, dst + N);
        delete [] a;
        delete [] dst;

        return spectrum;       


    }

    void KissFft::ifft(SpectrumType spectrum, double x[]) {
        static_assert(
            sizeof(ComplexType[2]) == sizeof(double[4]),
            "complex<double> has the same memory layout as two consecutive doubles"
        );
        ComplexType* a = new ComplexType[N];
        m_kfft_inverse.transform(&spectrum[0], a);
        for (std::size_t i = 0; i < N; ++i)
        {
            x[i] = a[i].real() / static_cast<double>(N);
        }
        delete [] a;


    }
}