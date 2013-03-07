#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include <cstdint>
#include <unittestpp.h>


SUITE(ArrayData)
{
    const int SIZE = 10;

    TEST(SampleFrequency)
    {
        Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        Aquila::ArrayData<> data(testArray, SIZE, 22050);
        CHECK_EQUAL(22050, data.getSampleFrequency());
    }

    TEST(DefaultSampleFrequency)
    {
        Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        Aquila::ArrayData<> data(testArray, SIZE);
        CHECK_EQUAL(0, data.getSampleFrequency());
        data.setSampleFrequency(22050);
        CHECK_EQUAL(22050, data.getSampleFrequency());
    }

    TEST(BitsPerSample8)
    {
        std::int8_t arr[SIZE] = {0};
        Aquila::ArrayData<std::int8_t> data(arr, SIZE, 22050);
        CHECK_EQUAL(8 * sizeof(Aquila::SampleType), data.getBitsPerSample());
    }

    TEST(BitsPerSample16)
    {
        std::int16_t arr[SIZE] = {0};
        Aquila::ArrayData<std::int16_t> data(arr, SIZE, 22050);
        CHECK_EQUAL(8 * sizeof(Aquila::SampleType), data.getBitsPerSample());
    }

    TEST(BitsPerSample32)
    {
        std::int32_t arr[SIZE] = {0};
        Aquila::ArrayData<std::int32_t> data(arr, SIZE, 22050);
        CHECK_EQUAL(8 * sizeof(Aquila::SampleType), data.getBitsPerSample());
    }

    TEST(BitsPerSample64)
    {
        std::int64_t arr[SIZE] = {0};
        Aquila::ArrayData<std::int64_t> data(arr, SIZE, 22050);
        CHECK_EQUAL(8 * sizeof(Aquila::SampleType), data.getBitsPerSample());
    }

    TEST(BitsPerSample_u8)
    {
        std::uint8_t arr[SIZE] = {0};
        Aquila::ArrayData<std::uint8_t> data(arr, SIZE, 22050);
        CHECK_EQUAL(8 * sizeof(Aquila::SampleType), data.getBitsPerSample());
    }

    TEST(BitsPerSample_u16)
    {
        std::uint16_t arr[SIZE] = {0};
        Aquila::ArrayData<std::uint16_t> data(arr, SIZE, 22050);
        CHECK_EQUAL(8 * sizeof(Aquila::SampleType), data.getBitsPerSample());
    }

    TEST(BitsPerSample_u32)
    {
        std::uint32_t arr[SIZE] = {0};
        Aquila::ArrayData<std::uint32_t> data(arr, SIZE, 22050);
        CHECK_EQUAL(8 * sizeof(Aquila::SampleType), data.getBitsPerSample());
    }

    TEST(BitsPerSample_u64)
    {
        std::uint64_t arr[SIZE] = {0};
        Aquila::ArrayData<std::uint64_t> data(arr, SIZE, 22050);
        CHECK_EQUAL(8 * sizeof(Aquila::SampleType), data.getBitsPerSample());
    }

    TEST(Iteration)
    {
        Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        Aquila::ArrayData<> data(testArray, SIZE, 22050);
        std::size_t i = 0;
        for (auto it = data.begin(); it != data.end(); it++, i++)
        {
            CHECK_EQUAL(testArray[i], *it);
        }
    }
}
