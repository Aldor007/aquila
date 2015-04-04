#include "Fft.h"
#include "aquila/global.h"
#include "aquila/transform/KissFft.h"
#include "UnitTest++/UnitTest++.h"


SUITE(KissFft)
{
    TEST(Delta)
    {
        deltaSpectrumTest<Aquila::KissFft, 8>();
        deltaSpectrumTest<Aquila::KissFft, 16>();
        deltaSpectrumTest<Aquila::KissFft, 128>();
        deltaSpectrumTest<Aquila::KissFft, 1024>();
    }

    TEST(ConstSignal)
    {
        constSpectrumTest<Aquila::KissFft, 8>();
        constSpectrumTest<Aquila::KissFft, 16>();
        constSpectrumTest<Aquila::KissFft, 128>();
        constSpectrumTest<Aquila::KissFft, 1024>();
    }

    TEST(DeltaInverse)
    {
        deltaInverseTest<Aquila::KissFft, 8>();
        deltaInverseTest<Aquila::KissFft, 16>();
        deltaInverseTest<Aquila::KissFft, 128>();
        deltaInverseTest<Aquila::KissFft, 1024>();
    }

    TEST(ConstInverse)
    {
        constInverseTest<Aquila::KissFft, 8>();
        constInverseTest<Aquila::KissFft, 16>();
        constInverseTest<Aquila::KissFft, 128>();
        constInverseTest<Aquila::KissFft, 1024>();
    }

    TEST(Identity)
    {
        identityTest<Aquila::KissFft, 8>();
        identityTest<Aquila::KissFft, 16>();
        identityTest<Aquila::KissFft, 128>();
        identityTest<Aquila::KissFft, 1024>();
    }
}