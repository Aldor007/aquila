#include "Fft.h"
#include "aquila/global.h"
#include "aquila/transform/Dft.h"
#include <unittestpp.h>


SUITE(Dft)
{
    TEST(Delta)
    {
        deltaSpectrumTest<Aquila::Dft>();
        deltaSpectrumTest<Aquila::Dft, 16>();
        deltaSpectrumTest<Aquila::Dft, 128>();
        deltaSpectrumTest<Aquila::Dft, 1024>();
    }

    TEST(ConstSignal)
    {
        constSpectrumTest<Aquila::Dft>();
        constSpectrumTest<Aquila::Dft, 16>();
        constSpectrumTest<Aquila::Dft, 128>();
        constSpectrumTest<Aquila::Dft, 1024>();
    }

    TEST(DeltaInverse)
    {
        deltaInverseTest<Aquila::Dft>();
        deltaInverseTest<Aquila::Dft, 16>();
        deltaInverseTest<Aquila::Dft, 128>();
        deltaInverseTest<Aquila::Dft, 1024>();
    }

    TEST(ConstInverse)
    {
        constInverseTest<Aquila::Dft>();
        constInverseTest<Aquila::Dft, 16>();
        constInverseTest<Aquila::Dft, 128>();
        constInverseTest<Aquila::Dft, 1024>();
    }
}
