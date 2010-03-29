#ifndef GRAPHICS_ZBUFFER_H
#define GRAPHICS_ZBUFFER_H
//
// Graphics Framework.
// Copyright (C) 2007 Department of Computer Science, University of Copenhagen
//
// Overhauled by kaiip dec 17, 2009.
//
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include <algorithm>

#include "graphics_state.h"


namespace graphics
{

    /**
     * A Z-Buffer.
     * A z-buffer is basically a 2D array of z-values.
     * Each row of the 2D array has ``width'' values and each column has ''height'' values.
     * Notice that the (0,0) entry of the array corresponds to the lower-left corner
     * on the ``screen'' (width-1,height-1) location corresponds to the upper right corner.
     */
    template< typename math_types >
    class ZBuffer
    {
    public:
    /**
     * The basic type which is the the type of the elements of vectors and matrices.
     */
    typedef typename math_types::real_type    real_type;

    /**
     * A vector with 3 entries both of type real_type.
     */
    typedef typename math_types::vector3_type vector3_type;

    protected:

    std::vector<float> m_values;     ///< The Z-values. A row format is adopted.
    int                m_width;      ///< The number of pixels in a row.
    int                m_height;     ///< The number of pixels in a column.

    public:


    /**
     * Clear Z Buffer.
     * This method should be used to setup the z-buffer before
     * doing any kind of drawing.
     *
     * @param clear_value   The value to be used to clear the buffer. Must be in the interval [0..1] otherwise an exception is thrown.
     *
     */
    void clear(real_type const& clear_value)
    {
#ifdef KENNY_ZBUFFER
        // Original Kenny
        if (clear_value < 0 || clear_value > 1) {
        throw std::invalid_argument("graphics_zbuffer::clear(real_type&): clear value must be in [0..1]");
        }
        std::fill(m_values.begin(), m_values.end(), clear_value);
#else
        // Changed by kaiip 06.12.2008 - 01:44
        if (clear_value > 0 || clear_value < -1) {
        throw std::invalid_argument("graphics_zbuffer::clear(real_type&): clear value must be in [-1..0]");
        }
        std::fill(m_values.begin(), m_values.end(), clear_value);
#endif
    }

    /**
     * Set Resolution.
     *
     * @param width  The number of pixels in a row. Must be larger than 1 otherwise an exception is thrown.
     * @param height  The number of pixels in a colum. Must be larger than 1 otherwise an exception is thrown.
     */
    void set_resolution(int width, int height)
    {
        if (width <= 1)
        throw std::invalid_argument("graphics_zbuffer::set_resolution: width must be larger than 1");
        if (height <= 1)
        throw std::invalid_argument("graphics_zbuffer::set_resolution: height must be larger than 1");

        m_values.resize(width*height);
        m_width  = width;
        m_height = height;
    }

    /**
     * Write Z-value.
     *
     * @param x       The current x location of the pixel. Must be within [0..width-1] otherwise an exception is thrown.
     * @param y       The current y location of the pixel. Must be within [0..height-1] otherwise an exception is thrown.
     * @param value   The z-value to be written. Must be in the interval [0..1] otherwise an exception is thrown.
     *
     */
    void write(int  x, int y, real_type const& z_value)
    {
        //--- Test to see if we actually got a real depth value
#ifdef KENNY_ZBUFFER
        if (z_value < 0 || z_value > 1)
        throw std::invalid_argument("graphics_zbuffer::write: depth must be within [0...1]");
#else
        if (z_value > 0 || z_value < -1)
            throw std::invalid_argument("graphics_zbuffer::write: depth must be within [-1...0]");
#endif
        //--- Simple minded clipping against framebuffer
        if (x < 0)
        return;
        if (y < 0)
        return;
        if (x >= m_width)
        return;
        if(y >= m_height)
        return;

        //--- Determine memory location of the pixel that should be written
        int offset = (y * m_width + x);

        //--- Wtite the pixel to the frame buffer
        m_values[offset]   = z_value;
    }


    /**
     * Read Z-value.
     *
     * @param x   The current x location of the pixel. Must be within [0..width-1] otherwise an exception is thrown.
     * @param y   The current y location of the pixel. Must be within [0..height-1] otherwise an exception is thrown.
     *
     */
    real_type const& read(int  x, int y) const
    {
        static real_type const off_screen = 0.0;

        //--- Simple minded clipping against framebuffer
        if (x < 0)
        return off_screen;
        if (y < 0)
        return off_screen;
        if (x >= m_width)
        return off_screen;
        if (y >= m_height)
        return off_screen;

        //--- Determine memory location of the z-value
        int offset = (y * m_width + x);
        return m_values[offset];
    }

    };

}// end namespace graphics

// GRAPHICS_ZBUFFER_H
#endif
