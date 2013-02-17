#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include "aquila/source/WaveFile.h"
#include "aquila/source/FramesCollection.h"
#include "constants.h"
#include <unittestpp.h>
#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>


SUITE(WaveFile)
{
    TEST(Filename)
    {
        std::string filename(Aquila_TEST_WAVEFILE_8B_MONO);
        Aquila::WaveFile wav(filename);
        CHECK(filename == wav.getFilename());
    }

    TEST(AudioLength)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(103, wav.getAudioLength());
    }

    TEST(BitsPerSample8)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(8, wav.getBitsPerSample());
    }

    TEST(BitsPerSample16)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_MONO);
        CHECK_EQUAL(16, wav.getBitsPerSample());
    }

    TEST(BytesPerSample8Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(1, wav.getBytesPerSample());
    }

    TEST(BytesPerSample8Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_STEREO);
        CHECK_EQUAL(2, wav.getBytesPerSample());
    }

    TEST(BytesPerSample16Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_MONO);
        CHECK_EQUAL(2, wav.getBytesPerSample());
    }

    TEST(BytesPerSample16Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(4, wav.getBytesPerSample());
    }

    TEST(BytesPerSecond)
    {
        std::vector<std::string> filenames;
        filenames.push_back(Aquila_TEST_WAVEFILE_8B_MONO);
        filenames.push_back(Aquila_TEST_WAVEFILE_8B_STEREO);
        filenames.push_back(Aquila_TEST_WAVEFILE_16B_MONO);
        filenames.push_back(Aquila_TEST_WAVEFILE_16B_STEREO);
        std::for_each(
            std::begin(filenames),
            std::end(filenames),
            [] (std::string filename) {
                Aquila::WaveFile wav(filename);
                unsigned int expected = static_cast<unsigned int>(
                    wav.getSampleFrequency() * wav.getBytesPerSample()
                );
                CHECK_EQUAL(expected, wav.getBytesPerSec());
            }
        );
    }

    TEST(Channels8Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(1, wav.getChannelsNum());
        CHECK(wav.isMono());
        CHECK(!wav.isStereo());
    }

    TEST(Channels8Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_STEREO);
        CHECK_EQUAL(2, wav.getChannelsNum());
        CHECK(!wav.isMono());
        CHECK(wav.isStereo());
    }

    TEST(Channels16Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_MONO);
        CHECK_EQUAL(1, wav.getChannelsNum());
        CHECK(wav.isMono());
        CHECK(!wav.isStereo());
    }

    TEST(Channels16Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(2, wav.getChannelsNum());
        CHECK(!wav.isMono());
        CHECK(wav.isStereo());
    }

    TEST(SampleFrequency)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(44100, wav.getSampleFrequency());
    }

    TEST(WaveSize8Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(4552, wav.getWaveSize());
    }

    TEST(WaveSize16Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(18208, wav.getWaveSize());
    }

    TEST(SamplesCount8Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(4552, wav.getSamplesCount());
    }

    TEST(SamplesCount16Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(4552, wav.getSamplesCount());
    }

    TEST(ToArray)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        const Aquila::SampleType* arr = wav.toArray();
        CHECK_EQUAL(wav.sample(0), arr[0]);
    }

    TEST(SetStereoChannel)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        const Aquila::SampleType* arrLeft = wav.toArray();
        wav.setSourceChannel(Aquila::RIGHT);
        const Aquila::SampleType* arrRight = wav.toArray();
        CHECK(arrLeft != arrRight);
    }

    TEST(SetStereoChannelOnMono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        const Aquila::SampleType* arrLeft = wav.toArray();
        wav.setSourceChannel(Aquila::RIGHT);
        const Aquila::SampleType* arrRight = wav.toArray();
        CHECK(arrLeft == arrRight);
    }

    TEST(FramesCount1)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Aquila::FramesCollection::createFromDuration(wav, 0, 0);
        CHECK_EQUAL(0, frames.count());
    }

    TEST(FramesCount2)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Aquila::FramesCollection::createFromDuration(wav, 10, 0);
        CHECK_EQUAL(10, frames.count());
    }

    TEST(FramesCount3)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Aquila::FramesCollection::createFromDuration(wav, 20, 0);
        CHECK_EQUAL(5, frames.count());
    }

    TEST(FramesCount4)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Aquila::FramesCollection::createFromDuration(wav, 0, 0.5);
        CHECK_EQUAL(0, frames.count());
    }

    TEST(FramesCount5)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Aquila::FramesCollection::createFromDuration(wav, 10, 0.5);
        CHECK_EQUAL(19, frames.count());
    }

    TEST(FramesCount6)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Aquila::FramesCollection::createFromDuration(wav, 20, 0.66);
        CHECK_EQUAL(13, frames.count());
    }

    TEST(Save8bit)
    {
        Aquila::WaveFile inputWav(Aquila_TEST_WAVEFILE_8B_MONO);
        Aquila::WaveFile::save(inputWav, Aquila_TEST_WAVEFILE_OUTPUT);

        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_OUTPUT);
        CHECK_EQUAL(inputWav.getSampleFrequency(), wav.getSampleFrequency());
        CHECK_EQUAL(8, wav.getBitsPerSample());
        CHECK_EQUAL(inputWav.getSamplesCount(), wav.getSamplesCount());
    }

    TEST(Save16bit)
    {
        Aquila::WaveFile inputWav(Aquila_TEST_WAVEFILE_16B_MONO);
        Aquila::WaveFile::save(inputWav, Aquila_TEST_WAVEFILE_OUTPUT);

        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_OUTPUT);
        CHECK_EQUAL(inputWav.getSampleFrequency(), wav.getSampleFrequency());
        CHECK_EQUAL(16, wav.getBitsPerSample());
        CHECK_EQUAL(inputWav.getSamplesCount(), wav.getSamplesCount());
    }

    TEST(SaveArray)
    {
        const int SIZE = 10;
        Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        Aquila::ArrayData<> data(testArray, SIZE, 22050);
        Aquila::WaveFile::save(data, Aquila_TEST_WAVEFILE_OUTPUT);

        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_OUTPUT);
        CHECK_EQUAL(22050, wav.getSampleFrequency());
        CHECK_EQUAL(16, wav.getBitsPerSample());
        CHECK_EQUAL(SIZE, wav.getSamplesCount());
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            CHECK_EQUAL(testArray[i], wav.sample(i));
        }
    }
}
