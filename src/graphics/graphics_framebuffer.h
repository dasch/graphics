#ifndef GRAPHICS_FRAME_BUFFER_H
#define GRAPHICS_FRAME_BUFFER_H
//
// Graphics Framework.
// Copyright (C) 2007 Department of Computer Science, University of Copenhagen.
// Extremely overhauled by kaiip@diku.dk 2009.
//

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>

#include "graphics_state.h"

#ifdef WIN32
#  define WIN32_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#  undef WIN32_LEAN_AND_MEAN
#  undef NOMINMAX
#endif


//For MAC OS X
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#else
#  include <GL/gl.h>
#endif


#include <vector>

namespace graphics
{

    /**
     * A Frame Buffer.
     * A framebuffer is basically a 2D array of pixel colors.
     * Each row of the 2D array has ``width'' pixels and each column has ''height'' pixels. 
     * Each pixel consist of three color components: red, green, and blue.
     * Notice that the (0,0) entry of the array corresponds to the lower-left corner
     * on the ``screen'' (width-1,height-1) location corresponds to upper right corner.
     */
    template< typename math_types >
    class FrameBuffer
    {
    public:
    /// The actual type of the elements of vectors and matrices.
    typedef typename math_types::real_type    real_type;

    /// The actual type of a vector2.
    typedef typename math_types::vector2_type vector2_type;

    /// The actual type of a vector3.
    typedef typename math_types::vector3_type vector3_type;

    public:
    /**
     * Creates a clean FrameBuffer.
     */
    FrameBuffer()
    {}

    /**
     * Destroys the Framebuffer and cleans up.
     */
    virtual ~FrameBuffer()
        {
        // The pixels are stored in a std::vector<real_type>, so there is nothing to clean up.
    }

    /**
     * Clear Framebuffer.
     * This method should be used to setup the background color before
     * doing any kind of drawing.
     *
     * @param clear_color   The color to be used to clear the buffer. Each color component must be in the interval [0..1] otherwise an exception is thrown.
     *
     */
    void clear(vector3_type const& clear_color)
    {
        if(clear_color[1] < 0 || clear_color[1] > 1)
        throw std::invalid_argument("red color must be within [0..1]");
        if(clear_color[2] < 0 || clear_color[2] > 1)
        throw std::invalid_argument("green color must be within [0..1]");
        if(clear_color[3] < 0 || clear_color[3] > 1)
        throw std::invalid_argument("blue color must be within [0..1]");

        for(std::vector<float>::iterator c = m_pixels.begin(); c!= m_pixels.end();)
        {
        *c = clear_color[1];
        ++c;
        *c = clear_color[2];
        ++c;
        *c = clear_color[3];
        ++c;
        }
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
        throw std::invalid_argument("width must be larger than 1");
        if (height <= 1)
        throw std::invalid_argument("height must be larger than 1");

        this->m_pixels.resize(width*height*3);
        this->m_width  = width;
        this->m_height = height;
    }

    /**
     * Get Resolution.
     *
     * @return the resulutions in the x- and y-directions.
     */
    vector2_type get_resolution() const
    {
        vector2_type resolution;
        resolution[1] = this->width();
        resolution[2] = this->height();
    }

    /**
     * The width of the FrameBuffer.
     * @return the width (in pixels) of the FrameBuffer.
     */
    int width() const
    {
        return this->m_width;
    }

    /**
     * The height of the FrameBuffer.
     * @return the height (in pixels) of the FrameBuffer.
     */
    int height() const
    {
        return this->m_height;
    }

    /**
     * Write Pixel.
     *
     * @param x       The current x location of the pixel.
     * @param y       The current y location of the pixel.
     * @param value   The color to be written. Each color component must be in the interval [0..1] otherwise an exception is thrown.
     *
     */
    void write_pixel(int  x, int y, vector3_type const& value)
    {
        //--- Test to see if we actually got a real color
        if(value[1] < 0 || value[1] > 1)
        throw std::invalid_argument("red color must be within [0..1]");
        if(value[2] < 0 || value[2] > 1)
        throw std::invalid_argument("green color must be within [0..1]");
        if(value[3] < 0 || value[3] > 1)
        throw std::invalid_argument("blue color must be within [0..1]");
        
        //--- Simple minded clipping against framebuffer
        if(x < 0)
        return;
        if(y < 0)
        return;
        if(x >= this->m_width)
        return;
        if(y >= this->m_height)
        return;

        //--- Determine memory location of the pixel that should be written
        int offset = (y * m_width + x) * 3;

        //--- Wtite the pixel to the frame buffer
        m_pixels[offset]   = value[1];
        m_pixels[offset+1] = value[2];
        m_pixels[offset+2] = value[3];
    }


    /**
     * Read Pixel
     *
     * @param x the x-coordinate of the pixel to be read.
     * @param y the y-coordinate of the pixel to be read.
     * @return  the pixel value stored at location (x, y) in the FrameBuffer.
     */
    vector3_type read_pixel(int x, int y) const
        {
        vector3_type value;
        if(x < 0)
        return value;
        if(y < 0)
        return value;
        if(x >= this->m_width)
        return value;
        if(y >= this->m_height)
        return value;

        //--- Determine memory location of the pixel that should be written
        int offset = (y * m_width + x) * 3;

        // Get the pixel from the frame buffer
        value[1] = m_pixels[offset];
        value[2] = m_pixels[offset+1]; 
        value[3] = m_pixels[offset+2];

        return value;
    }

    /**
     * Flush to Screen.
     * When this method is invoked whatever content of
     * the framebuffer will be shown on the screen.
     *
     * This method should be invoked when finished
     * drawing all triangles.
     */
    void flush() 
    {
        //--- Ask OpenGL to draw our pixel array into the the
        //--- real-thing, the frame buffer in the graphics hardware.
        glDrawPixels( m_width, m_height,  GL_RGB, GL_FLOAT, &(m_pixels[0]) );
    }

    protected:
    std::vector<float> m_pixels;     ///< Pixel memory. Pixels are stored as 3-tuples of red, green and blue color. A row format is adopted.
    int                m_width;      ///< The number of pixels in a row.
    int                m_height;     ///< The number of pixels in a column.


    };

}// end namespace graphics

// GRAPHICS_FRAME_BUFFER_H
#endif
