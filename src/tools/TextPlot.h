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
#include <iostream>
#include <string>

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

    private:
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
