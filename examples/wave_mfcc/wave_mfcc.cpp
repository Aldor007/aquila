
#include "aquila/source/WaveFile.h"
#include "aquila/global.h"
#include "aquila/transform/Mfcc.h"
#include "aquila/transform/FftFactory.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: wave_mfcc <FILENAME>" << std::endl;
        return 1;
    }
    Aquila::WaveFile wav(argv[1]);
    std::cout << "Filename: "           << wav.getFilename();
    std::cout << "\nLength: "           << wav.getAudioLength()     << " ms";
    std::cout << "\nSample frequency: " << wav.getSampleFrequency() << " Hz";
    std::cout << "\nChannels: "         << wav.getChannelsNum();
    std::cout << "\nByte rate: "        << wav.getBytesPerSec()/1024 << " kB/s";
    std::cout << "\nBits per sample: "  << wav.getBitsPerSample() << "b\n";
    std::cout << "\nSamples " << wav.getSamplesCount()<<std::endl;
    Aquila::Mfcc mfcc(wav.getSamplesCount(), Aquila::FftFactory::Method::KISS);
    auto mfccValues = mfcc.calculate(wav);
    std::cout << "MFCC coefficients: \n";
    std::copy(
        std::begin(mfccValues),
        std::end(mfccValues),
        std::ostream_iterator<double>(std::cout, " ")
    );
    std::cout << "\n";

    return 0;
}
