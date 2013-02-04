#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/source/Sum.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"
#include <algorithm>
#include <functional>
#include <memory>

int main()
{
    // input signal parameters
    const std::size_t SIZE = 64;
    const Aquila::FrequencyType sampleFreq = 2000;
    const Aquila::FrequencyType f1 = 96, f2 = 813;
    const Aquila::FrequencyType f_lp = 500;

    Aquila::SineGenerator sineGenerator1 = Aquila::SineGenerator(sampleFreq);
    sineGenerator1.setAmplitude(32).setFrequency(f1).generate(SIZE);
    Aquila::SineGenerator sineGenerator2 = Aquila::SineGenerator(sampleFreq);
    sineGenerator2.setAmplitude(8).setFrequency(f2).setPhase(0.75).generate(SIZE);
    Aquila::Sum sum(sineGenerator1, sineGenerator2);

    Aquila::TextPlot plt("Signal waveform before filtration");
    plt.plot(sum);

    // calculate the FFT
    auto fft = Aquila::FftFactory::getFft(SIZE);
    Aquila::ComplexType spectrum[SIZE];
    fft->fft(sum.toArray(), spectrum);
    plt.setTitle("Signal spectrum before filtration");
    plt.plotSpectrum(spectrum, SIZE);

    // generate a low-pass filter spectrum
    Aquila::ComplexType filterSpectrum[SIZE];
    for (std::size_t i = 0; i < SIZE; ++i)
    {
        if (i < (SIZE * f_lp / sampleFreq))
        {
            // passband
            filterSpectrum[i] = 1.0;
        }
        else
        {
            // stopband
            filterSpectrum[i] = 0.0;
        }
    }
    plt.setTitle("Filter spectrum");
    plt.plotSpectrum(filterSpectrum, SIZE);

    // the following line does the multiplication of two spectra
    // (which is complementary to convolution in time domain)
    typedef Aquila::ComplexType cplx;
    std::transform(spectrum, spectrum + SIZE, filterSpectrum, spectrum,
                   [] (cplx x, cplx y) { return x * y; });
    plt.setTitle("Signal spectrum after filtration");
    plt.plotSpectrum(spectrum, SIZE);

    // Inverse FFT moves us back to time domain
    double x1[SIZE];
    fft->ifft(spectrum, x1);
    plt.setTitle("Signal waveform after filtration");
    plt.plot(x1, SIZE);

    return 0;
}
