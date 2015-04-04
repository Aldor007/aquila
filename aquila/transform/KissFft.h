/**
 * @file KissFft.h
 *
 * A wrapper for the FFT algorithm from KissFFT packages.
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

#ifndef KISSFFT_H
#define KISSFFT_H

#include "Fft.h"

#include "kiss_fft/kissfft.hh"


namespace Aquila
{
    /**
     * A wrapper for the FFT algorithm from KissFFT lib
     */
    class AQUILA_EXPORT KissFft : public Fft
    {
    public:
        KissFft(std::size_t length);
        ~KissFft();

        virtual SpectrumType fft(const SampleType x[]);
        virtual void ifft(SpectrumType spectrum, double x[]);

    private:
        /**
         *  KissFft object
         */
        kissfft<SampleType> m_kfft;
    };
}

#endif // KISSFFT_H