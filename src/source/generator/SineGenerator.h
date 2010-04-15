/**
 * @file SineGenerator.h
 *
 * Sine wave generator.
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#ifndef SINEGENERATOR_H
#define SINEGENERATOR_H

#include "Generator.h"

namespace Aquila
{
    class SineGenerator : public Generator
    {
    public:
        SineGenerator(FrequencyType sampleFrequency, std::size_t bufferSize);

        void setFrequency(FrequencyType frequency)
        {
            m_frequency = frequency;
        }

        virtual void generate();

    private:
        FrequencyType m_frequency;
    };
}

#endif // SINEGENERATOR_H
