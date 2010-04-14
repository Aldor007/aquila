/**
 * @file TextPlot.h
 *
 * A simple console-based data plotter.
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

#ifndef TEXTPLOT_H
#define TEXTPLOT_H

#include "../source/SignalSource.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

namespace Aquila
{
    /**
     * A utility class to "draw" data plots in the console applications.
     */
    class TextPlot
    {
    public:
        TextPlot(const std::string& title = "Data plot",
                 std::ostream& out = std::cout);

        /**
         * Returns the title of the plot.
         *
         * @return plot title
         */
        std::string getTitle() const
        {
            return m_title;
        }

        /**
         * Sets the title of the plot.
         *
         * @param title plot title
         */
        void setTitle(const std::string& title)
        {
            m_title = title;
        }

        void plot(const SignalSource& source);

        template<typename Numeric>
        void plot(const std::vector<Numeric> data)
        {
            PlotMatrixType plot(data.size());
            doPlot(plot, data.begin(), data.end());
        }

    private:
        /**
         * The internal representation of the plot.
         */
        typedef std::vector< std::vector<char> > PlotMatrixType;

        /**
         * Prepares an internal "pixel" matrix and calls drawPlotMatrix().
         *
         * The template parameter is an iterator type, therefore the plotter
         * can be more generic.
         *
         * @param plot reference to the plot matrix
         * @param begin an iterator pointing to the beginning of plotted data
         * @param end an iterator pointing "one past end" of plotted data
         */
        template <typename Iterator>
        void doPlot(PlotMatrixType& plot, Iterator begin, Iterator end)
        {
            const double max = *std::max_element(begin, end);
            const double min = *std::min_element(begin, end);
            const double range = max - min;
            const std::size_t columnSize = 16; // todo: make this customizable

            for (std::size_t xPos = 0; xPos < plot.size(); ++xPos)
            {
                plot[xPos].resize(columnSize, ' ');
                double normalizedValue = (*begin++ - min) / range;
                std::size_t yPos = columnSize - static_cast<std::size_t>(
                    std::ceil(columnSize * normalizedValue));

                // bound the value so it stays within vector dimension
                if (yPos >= columnSize)
                    yPos = columnSize - 1;
                plot[xPos][yPos] = '*';
            }

            drawPlotMatrix(plot);
        }

        void drawPlotMatrix(const PlotMatrixType& plot);

        /**
         * Plot title.
         */
        std::string m_title;

        /**
         * Output stream.
         */
        std::ostream& m_out;
    };
}

#endif // TEXTPLOT_H
