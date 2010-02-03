#ifndef GRAPHICS_RENDER_PIPELINE_H
#define GRAPHICS_RENDER_PIPELINE_H
//
// Graphics Framework.
// Copyright (C) 2008 Department of Computer Science, University of Copenhagen.
// Extremely overhauled by kaiip@diku.dk 2009.
//

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>

#include "graphics_vertex_program.h"
#include "graphics_rasterizer.h"
#include "graphics_fragment_program.h"
#include "graphics_zbuffer.h"
#include "graphics_framebuffer.h"
#include "graphics_state.h"

namespace graphics
{
    /**
     * Render Pipeline.
     * This class implements a simple software driven hardware render pipeline.
     *
     * It mimics the real-life hardware without too many nifty-gritty details. It
     * consist basically of the following components:
     *
     *  - vertex program
     *  - rasterizer
     *  - fragment program
     *  - framebuffer
     *  - zbuffer
     *
     * The vertex program processes vertex data (coordinates, normals and colors)
     * specified by the end user (by invoking the draw_triangle method).
     *
     * The vertex program is responsible for performing the model view projection
     * transformation. Thus upon return from a vertex program the vertex data have
     * been transformed into screen-space.
     *
     * Prior to drawing a triangle end-users are responsible for setting up the
     * transformation matrices themself. This is done using the state-method to
     * retrieve the current state information about the render pipeline and then
     * invoke the model- and projection methods on the state instance to change
     * these matrices.
     *
     * The current graphics state is passed along to the vertex program, so it
     * can extract whatever information that it may need about the current state
     * of the render pipeline.
     *
     * Once vertex data have been transformed into screen-space the rasterizer are
     * asked to convert the triangle into fragment. A fragment is an entity that
     * potential ends up on the screen as a pixel. In order to do so the fragment
     * must survive all the way through the render pipeline and be written to the
     * frame buffer.
     *
     * The render pipeline contineously extract fragment information from the
     * rasterizer until no more fragments exist. For each fragment the render
     * pipeline performs a depth test using a z-buffer. If the depth-test is
     * passed then the fragment is being processed by a fragment program.
     *
     * The fragment program is responsible for computing the final color that
     * should be used when the fragment (now it will have become a pixel) is
     * written into the framebuffer. Like the vertex program the fragment program
     * is passed the current graphcis state, such that need information about
     * light and material can be extracted in order to compute the output color.
     *
     * To instantiate a render pipeline one needs to specify what math_types
     * that should be used. This is done by creating an empty class with all
     * the needed typedefs. (The compiler will output errors if one forgets a
     * typedef). A simple-minded example would be
     *
     *
     *  class MyMathTypes
     *  {
     *  public:
     *      typedef float  real_type;
     *      typedef float  vector2_type[2];
     *      typedef float  vector3_type[3];
     *      typedef float  vector4_type[4];
     *      typedef float  matrix4x4_type[16];
     *  };
     *
     * Now one can create a render pipeline type by writting
     *
     *   RenderPipeline<MyMathTypes>  render_pipeline;
     *
     * Once the render pipeline is created one needs to setup the ``hardware'' by
     * specifying what vertex-, fragement-, and rasterizers the render pipeline
     * should use.
     *
     * First one would need to create those components by inheriting from
     * the VertexProgram, FragmentProgram and Rasterizer base classes.
     *
     *   template<typename math_types>
     *   class MyVertexProgram : public VertexProgram<math_types>
     *   {
     *       // add your implementation here
     *   };
     *
     *   template<typename math_types>
     *   class MyFragmentProgram : public FragmentProgram<math_types>
     *   {
     *       // add your implementation here
     *   };
     *
     *   template<typename math_types>
     *   class MyRasterizer : public Rasterizer<math_types>
     *   {
     *       // add your implementation here
     *   };
     *
     * Now create the objects and load them into the render pipeline.
     *
     *   MyVertexProgram<MyMathTypes>    vertex_program;
     *   MyFragmentProgram<MyMathTypes>  fragment_program;
     *   MyRasterizer<MyMathTypes>       rasterizer;
     *   render_pipeline.load_vertex_program( vertex_program );
     *   render_pipeline.load_fragment_program( fragment_program );
     *   render_pipeline.load_rasterizer( rasterizer);
     *
     * Now you have connected all the hardware the next task is to
     * allocate memory for the internal buffers of the render pipeline.
     * This is done by invoking the set_resolution method.
     *
     *  render_pipeline.set_resolution(1024, 768 );
     *
     * Before starting to render one needs to make sure that the graphics
     * state is setup correctly. In order to do so you will need to the
     * query the graphics state and modify whatever you need.
     *
     * render_pipeline.state().projection() = ....;
     * render_pipeline.state().model() = ....;
     * render_pipeline.state().light_position() = ....;
     * ...
     * render_pipeline.state().fall_off() = ....;
     *
     * Now we are ready to setup our renderloop. First we need to clear
     * the buffers, then draw the triangles and finally flush everything
     * onto the actual screen.
     *
     *  render_pipeline.clear( z_value, color );
     *  for( .... )
     *    render_pipeline.draw_triangle( .... );
     *  render_pipeline.flush();
     *
     * This is it, enjoy!
     */
    template< typename math_types >
    class RenderPipeline
    {
    /**
     * Public types.
     */
    public:
    /// The actual type of the elements of vectors and matrices.
    typedef typename math_types::real_type        real_type;

    /// The actual type of a vector2.
    typedef typename math_types::vector2_type     vector2_type;

    /// The actual type of a vector3.
    typedef typename math_types::vector3_type     vector3_type;

    /// The actual type of a vector4.
    typedef typename math_types::vector4_type     vector4_type;

    /// Tha actual type of a matrix4x4.
    typedef typename math_types::matrix4x4_type   matrix4x4_type;

    public:
    /// The type of the class which contains the actual state of the RenderPipeline.
    typedef GraphicsState<math_types>            graphics_state_type;

    /// The actual type of a VertexProgram.
    typedef VertexProgram<math_types>            vertex_program_type;

    /// The actual type of the Rasterizer.
    typedef Rasterizer<math_types>               rasterizer_type;

    /// The actual type of the FragmentProgram.
    typedef FragmentProgram<math_types>          fragment_program_type;

    /// The actual type of the ZBuffer.
    typedef ZBuffer<math_types>                  zbuffer_type;

    /// The actual type of the FrameBuffer.
    typedef FrameBuffer<math_types>              frame_buffer_type;


    public:
    /**
     * Creates a new RenderPipeline with a default state.
     * That is: A FrameBuffer of size 500 x 500, but no VertexProgram, Rasterizer nor FragmentProgram.
     */
    RenderPipeline() : m_width(500), m_height(500),
               m_vertex_program(0),
               m_rasterizer(0),
               m_fragment_program(0),
               m_unitlength(1)
    {
        this->m_frame_buffer.set_resolution(this->m_width, this->m_height);
        this->m_zbuffer.set_resolution(this->m_width, this->m_height);
    }

        /**
     * Creates a new RenderPipeline with a FrameBuffer of size width x height, and default state.
     * That is: No VertexProgram, Rasterizer nor FragmentProgram.
     * @param width  The width of the FrameBuffer.
     * @param height The height of the FrameBuffer.
     */
    RenderPipeline(int width, int height) : m_width(width), m_height(height),
                        m_vertex_program(0),
                        m_fragment_program(0),
                        m_rasterizer(0),
                        m_unitlength(1)
    {
        this->m_frame_buffer.set_resolution(this->m_width, this->m_height);
        this->m_zbuffer.set_resolution(this->m_width, this->m_height);
    }

    /**
     * Destroys the RenderPipeline.
     */
    virtual ~RenderPipeline()
    {}

    /**
     * Set Resolution.
     *
     * @param width  The number of pixels in a row. Must be larger than 1 otherwise
     *               an exception is thrown.
     * @param height The number of pixels in a colum. Must be larger than 1 otherwise
     *               an exception is thrown.
     */
    void set_resolution(int width, int height)
    {
        this->m_width  = width;
        this->m_height = height;
        this->m_frame_buffer.set_resolution(this->m_width, this->m_height);
        this->m_zbuffer.set_resolution(this->m_width, this->m_height);
    }

    /**
     * Get the resolution of the screen.
     *
     * @return the resulution in the x- and y-directions.
     */
    vector2_type get_resolution() const
    {
        vector2_type resolution;
        resolution[1] = this->m_frame_buffer.width();
        resolution[2] = this->m_frame_buffer.height();
    }

    /**
     * The width of the FrameBuffer.
     * @return the width (in pixels) of the FrameBuffer.
     */
    int width() const
    {
        return this->m_frame_buffer.width();
    }

    /**
     * The height of the FrameBuffer.
     * @return the height (in pixels) of the FrameBuffer.
     */
    int height() const
    {
        return this->m_frame_buffer.height();
    }

    /**
     * Clear Buffers.
     * This method should be used to setup the background color and z-values before
     * doing any kind of drawing.
     *
     * @param color   The color to be used to clear the buffer.
     *                Each color component must be in the interval [0..1]
     *                otherwise an exception is thrown.
     * @param depth   The value to be used to clear the buffer.
     *                Must be in the interval [0..1] otherwise an exception is thrown.
     *
     */
    void clear(real_type const& depth, vector3_type const& color)
    {
        this->m_frame_buffer.clear(color);
        this->m_zbuffer.clear(depth);
    }

    /**
     * The Graphics State.
     *
     * @return A read-only reference to the current state of the RenderPipeline.
     */
    graphics_state_type const& state() const
    {
        return this->m_state;
    }

    /**
     * The Graphics State.
     *
     * @return A writable reference to the current state of the RenderPipeline.
     */
    graphics_state_type& state()
    {
        return this->m_state;
    }

    public:
    /**
     * Load a Vertex Program.
     * @param program The VertexProgram to be loaded.
     */
    void load_vertex_program( vertex_program_type& program )
    {
        this->m_vertex_program = &program;
    }

    /**
     * Load a Rasterizer.
     * @param rasterizer The Rasterizer to be loaded.
     */
    void load_rasterizer( rasterizer_type& rasterizer )
    {
        this->m_rasterizer = &rasterizer;
    }

    /**
     * Load a Fragment Program.
     * @param program The FragmentProgram to be loaded.
     */
    void load_fragment_program( fragment_program_type& program )
    {
        this->m_fragment_program = &program;
    }


    protected:
    /**
     * This is the place where the "local variables" are declared.
     */

    /// Contains the state of the whole RenderPipeline.
    graphics_state_type    m_state;

    /// The actual VertexProgram. Initially == 0.
    vertex_program_type*   m_vertex_program;

    /// The actual Rasterizer. Initially == 0.
    rasterizer_type*       m_rasterizer;

    /// The actual FragmentProgram. Initially == 0.
    fragment_program_type* m_fragment_program;

    /// The actual FrameBuffer. Implemented with std::vector.
    frame_buffer_type      m_frame_buffer;

    /// The actual Zbuffer. Implemented with std::vector.
    zbuffer_type           m_zbuffer;

    /// The width of the actual FrameBuffer.
    int                    m_width;

    /// The height of the actual FrameBuffer.
    int                    m_height;

    /// unitlength is a Debug attribute.
    int                    m_unitlength;


    public:

    // This is all the Debug Stuff. It relates to the Contained Rasterizer.

    /**
     * Turn on the Debug Option.
     * If the Rasterizer has not been initialized, a runtime_error exception is thrown.
     */
    bool DebugOn()
    {
        if (this->m_rasterizer == 0)
        throw std::runtime_error("RenderPipeline::DebugOn(): m_rasterizer not initialized");
        else {
        bool oldvalue = this->m_rasterizer->DebugOn();
        return oldvalue;
        }
    }

    /**
     * Turn off the Debug Option.
     * If the Rasterizer has not been initialized, a runtime_error exception is thrown.y
     */
    bool DebugOff()
    {
        if (this->m_rasterizer == 0)
        throw std::runtime_error("RenderPipeline::DebugOff(): m_rasterizer not initialized");
        else {
        bool oldvalue = this->m_rasterizer->DebugOff();
        return oldvalue;
        }
    }

    /**
     * The unit length can have different values. It works like a scalefactor, used to
     * magnify the screen.
     * @return The actual unit length in pixels.
     */
    int unit_length() const
    {
        return this->m_unitlength;
    }

    /**
    * The unit length can have different values. It works like a scalefactor, used to
    * magnify the screen.
    * @param new_unitlength The new unit length (scale factor).
    * @return The previous unit length.
    */
    int unit_length(int new_unitlength)
    {
        int old_unitlength = this->m_unitlength;
        this->m_unitlength = new_unitlength;
        return old_unitlength;
    }

    /**
     * Draws a grid on the screen with a specified spacing and color.
     * The specified spacing is multiplied by the actual unit length.
     * So, if the specified spacing is equal to 4, and unit length == 2,
     * the actual spacing will be equal to: 4 * 2 = 8 pixels, because unit length
     * is just a scale factor, used to magnify the screen.
     * @param x_spacing The spacing in the x-direction.
     * @param y_spacing The spacing in the y-direction.
     * @param color The color of the grid lines.
     */
    void draw_grid(int x_spacing, int y_spacing, vector3_type const& color)
    {
        int width  = this->m_frame_buffer.width();
        int height = this->m_frame_buffer.height();
        int delta_x = x_spacing * this->m_unitlength;
        for (int x = 0; x < width; x += delta_x) {
        for (int y = 0; y < height;++y) {
            this->m_frame_buffer.write_pixel(x, y, color);
        }
        }

        int delta_y = y_spacing * this->m_unitlength;
        for (int y = 0; y < height; y += delta_y) {
        for (int x = 0; x < width; ++x) {
            this->m_frame_buffer.write_pixel(x, y, color);
        }
        }
    }


    /**
     * Draws a Disk on the the screen representing a pixel.
     * @param vertex   A vector3 which contains the coordinates of the point.
     * @param color    A vector3 which contains the color of the point.
     */
    void draw_debugpoint(vector3_type const& vertex, vector3_type const& color)
    {
        std::cout << "-->draw_debugpoint(1)" << std::endl;

        int x = static_cast<int>(round(vertex[1]));
        int y = static_cast<int>(round(vertex[2]));

        std::cout << "\tdraw_debugpoint(1)" << std::endl;
        std::cout << "\t=============================" << std::endl;
        std::cout << "\t\tPoint = [" << vertex << "]" << std::endl;
        std::cout << "\t\tColor = [" << color  << "]" << std::endl;

        this->draw_debugpoint(x, y, color);

        std::cout << "<--draw_debugpoint(1)" << std::endl;
    }

    /**
     * Draws a Disk on the screen representing a pixel.
     * @param x       The x-coordinate of the pixel.
     * @param y       The y-coordinate of the pixel.
     * @param color   The color of the pixel.
     */
    void draw_debugpoint(int x, int y, vector3_type const& color)
    {
        std::cout << "\t-->draw_debugpoint(2)" << std::endl;

        std::cout << "\t\tdraw_debugpoint(2)" << std::endl;
        std::cout << "\t\t==================" << std::endl;
        std::cout << "\t\t\tPoint = [" << x << ", " << y << "]" << std::endl;
        std::cout << "\t\t\tColor = [" << color  << "]" << std::endl;

        std::cout << "\t\tthis->m_frame_buffer.write_pixel(x, y, color);" << std::endl;
        this->m_frame_buffer.write_pixel(x, y, color);

        std::cout << "\t<--draw_debugpoint(2)" << std::endl;
    }


    /**
     * Draws a thin 2D line on the sreen (one pixel wide).
     * The start and end points are scaled by unit length. and no transformations are applied.
     * The method can be used for Debug purpurses.
     * @param v1    A vector3 which contains the start point (the third coordinate is ignored).
     * @param v2    A vector3 which contains the end point (the third coordinate is ignored).
     * @param color The color of the line.
     */
    void draw_debugline(vector3_type const& v1, vector3_type const& v2, vector3_type const& color)
    {
        int x1 = static_cast<int>(round(v1[1]));
        int y1 = static_cast<int>(round(v1[2]));
        int x2 = static_cast<int>(round(v2[1]));
        int y2 = static_cast<int>(round(v2[2]));

        this->draw_debugline(x1, y1, x2, y2, color);
    }

        /**
     * Draws a thin 2D line on the sreen (one pixel wide).
     * The start and end points are scaled by unit length. and no transformations are applied.
     * The method can be used for Debug purpurses.
     * @param x1 The x-coordinate of the start point.
     * @param y1 The y-coordinate of the start point.
     * @param x2 The x-coordinate of the end point.
     * @param y2 The y-coordinate of the end point.
     * @param color The color of the line.
     */
    void draw_debugline(int x1, int y1, int x2, int y2, vector3_type const& color)
    {
        int x_start = x1 * this->m_unitlength;
        int y_start = y1 * this->m_unitlength;
        int x_stop  = x2 * this->m_unitlength;
        int y_stop  = y2 * this->m_unitlength;

        int x_current = x_start;
        int y_current = y_start;

        int dx = x_stop - x_start;
        int dy = y_stop - y_start;

        int DeltaX = (dx < 0) ? -1 : 1;
        int DeltaY = (dy < 0) ? -1 : 1;

        int abs_2dx = std::abs(dx) << 1;
        int abs_2dy = std::abs(dy) << 1;

        if (abs_2dx > abs_2dy) {
        // x-dominant
        bool leftrightscan = (DeltaX > 0) ? true : false;
        int distance = abs_2dy - abs_2dx >> 1;
        while (true) {
            this->m_frame_buffer.write_pixel(x_current, y_current, color);
            if (x_current == x_stop) return;
            if ((distance > 0) || ((distance == 0) && leftrightscan)) {
            y_current += DeltaY;
            distance  -= abs_2dx;
            }
            x_current += DeltaX;
            distance  += abs_2dy;
        }
        }
        else {
        // y-dominant
        bool leftrightscan = (DeltaY > 0) ? true : false;
        int distance = abs_2dx - abs_2dy >> 1;
        while (true) {
            this->m_frame_buffer.write_pixel(x_current, y_current, color);
            if (y_current == y_stop) return;
            if ((distance > 0) || ((distance == 0) && leftrightscan)) {
            x_current += DeltaX;
            distance  -= abs_2dy;
            }
            y_current += DeltaY;
            distance  += abs_2dx;
        }
        }
    }


    void write_pixel_to_frame_buffer(int x, int y, vector3_type const& color)
    {
        if (this->m_unitlength == 1) {
        this->m_frame_buffer.write_pixel(x, y, color);
        }
        else {
        this->draw_disk(x * this->m_unitlength, y * this->m_unitlength,
                (this->m_unitlength - 1) / 2, color);
        }
    }

        void draw_disk(int Xcenter, int Ycenter, int Radius, vector3_type const& color)
    {
        int X = 0;
        int Y = Radius;
        int d = 1 - Radius;
        int deltaE  = 3;
        int deltaSE = -2 * Radius + 5;

        CirclePointsFill(Xcenter, Ycenter, X, Y, color);
        while (Y > X) {
        if (d < 0) {
            d += deltaE;
            deltaSE += 2;
        }
        else {
            d += deltaSE;
            deltaSE += 4;
            --Y;
        }
        ++X;
        deltaE += 2;
        CirclePointsFill(Xcenter, Ycenter, X, Y, color);
        }
    }


        void CirclePointsFill(int Xcenter, int Ycenter, int X, int Y, vector3_type const& color)
    {
        for (int x = Xcenter - X; x <= Xcenter + X; ++x) {
        this->m_frame_buffer.write_pixel(x, Ycenter - Y, color);
        }
        for (int x = Xcenter - X; x <= Xcenter + X; ++x) {
        this->m_frame_buffer.write_pixel(x, Ycenter + Y, color);
        }
        for (int x = Xcenter - Y; x <= Xcenter + Y; ++x) {
        this->m_frame_buffer.write_pixel(x, Ycenter - X, color);
        }
        for (int x = Xcenter - Y; x <= Xcenter + Y; ++x) {
        this->m_frame_buffer.write_pixel(x, Ycenter + X, color);
        }
    }


    /**
     * Draw Point.
     * This method process the vertex data that makes up a point (1 coordinate,
     * and 1 color). Vertex data is basically turned into pixels in
     * the framebuffer.
     *
     * Note: If renderpipeline is not correctly setup then an exception is thrown.
     *
     *
     * @param in_vertex1
     * @param in_color1
     */
    void draw_point(vector3_type const& in_vertex1,
            vector3_type const& in_color1)
    {
        //--- Test if render pipeline was set up correctly
        if(this->m_vertex_program == 0)
        throw std::logic_error("vertex program was not loaded");

        if(this->m_rasterizer == 0)
        throw std::logic_error("rasterizer was not loaded");

        if(this->m_fragment_program == 0)
        throw std::logic_error("fragment program was not loaded");

        //--- Temporaries used to hold output from vertex program
        vector3_type out_vertex1;
        vector3_type out_color1;

        //--- Ask vertex program to process all the vertex data.
        this->m_vertex_program->run(this->state(),
                    in_vertex1,  in_color1,
                    out_vertex1, out_color1);

        //--- Initialize rasterizer with output from the vertex program
        this->m_rasterizer->init(out_vertex1, out_color1);

        //--- Keep on processing fragments until there are none left
        while( this->m_rasterizer->more_fragments() )
        {
        //--- get screen location of the current fragment
        int screen_x = this->m_rasterizer->x();
        int screen_y = this->m_rasterizer->y();

        //--- extract old and new z value and perform a z-test
        real_type z_old = this->m_zbuffer.read( screen_x, screen_y );
        real_type z_new = this->m_rasterizer->depth();

        if( this->state().ztest( z_old, z_new ) )
        {
            //--- The fragment passed the z-test, now we need to ask
            //--- the fragment program to compute the color of the fragment.
            vector3_type out_color;               // uninitialized!
            out_color = this->m_rasterizer->color();    // now initialized!

            this->m_fragment_program->run(this->state(),
                          m_rasterizer->position(),
                          m_rasterizer->normal(),
                          m_rasterizer->color(),
                          out_color);

            //--- Finally we write the new z-value to the z-buffer
            //--- and the new color to the frame buffer.
            this->m_zbuffer.write( screen_x, screen_y, z_new);
            this->write_pixel_to_frame_buffer(screen_x, screen_y, out_color);
        }

        //--- We finished processing the fragment, so we
        //--- can advance to the next fragment.
        this->m_rasterizer->next_fragment();
        }
    }


/**
     * Draw Line.
     * This method process the vertex data that makes up a line (2 coordinates,
     * and 2 colors). Vertex data is basically turned into pixels in
     * the framebuffer.
     *
     * Note: If renderpipeline is not correctly setup then an exception is thrown.
     *
     *
     * @param in_vertex1
     * @param in_color1
     * @param in_vertex2
     * @param in_color2
     */
    void draw_line(vector3_type const& in_vertex1,
               vector3_type const& in_color1,
               vector3_type const& in_vertex2,
               vector3_type const& in_color2)
    {
        //--- Test if render pipeline was set up correctly
        if(!m_vertex_program)
        throw std::logic_error("vertex program was not loaded");

        if(!m_rasterizer)
        throw std::logic_error("rasterizer was not loaded");

        if(!m_fragment_program)
        throw std::logic_error("fragment program was not loaded");

        //--- Temporaries used to hold output from vertex program
        vector3_type out_vertex1;
        vector3_type out_vertex2;
        vector3_type out_color1;
        vector3_type out_color2;

        //--- Ask vertex program to process all the vertex data.
        m_vertex_program->run(this->state(),
                  in_vertex1,  in_color1,
                  out_vertex1, out_color1);

        m_vertex_program->run(this->state(),
                  in_vertex2,  in_color2,
                  out_vertex2, out_color2);

        //--- Initialize rasterizer with output from the vertex program
        m_rasterizer->init(out_vertex1, out_color1,
                   out_vertex2, out_color2);

        //--- Keep on processing fragments until there are none left
        while( m_rasterizer->more_fragments() )
        {
        //--- get screen location of the current fragment
        int screen_x = m_rasterizer->x();
        int screen_y = m_rasterizer->y();

        //--- extract old and new z value and perform a z-test
        real_type z_old = m_zbuffer.read( screen_x, screen_y );
        real_type z_new = m_rasterizer->depth();

        if( this->state().ztest( z_old, z_new ) )
        {
            //--- The fragment passed the z-test, now we need to ask
            //--- the fragment program to compute the color of the fragment.
            vector3_type out_color;               // uninitialized!
            out_color = m_rasterizer->color();    // now initialized!

            m_fragment_program->run(this->state(),
                        m_rasterizer->position(),
                        m_rasterizer->normal(),
                        m_rasterizer->color(),
                        out_color);

            //--- Finally we write the new z-value to the z-buffer
            //--- and the new color to the frame buffer.
            m_zbuffer.write( screen_x, screen_y, z_new);
            this->write_pixel_to_frame_buffer(screen_x, screen_y, out_color);
        }

        //--- We finished processing the fragment, so we
        //--- can advance to the next fragment.
        m_rasterizer->next_fragment();
        }
    }


    /**
     * Draw Triangle.
     * This method process the vertex data that makes up a triangle (3 coordinates,
     * 3  normals, and 3 colors). Vertex data is basically turned into pixels in
     * the framebuffer.
     *
     * Note: If renderpipeline is not correctly setup then an exception is thrown.
     *
     *
     * @param in_vertex1
     * @param in_normal1
     * @param in_color1
     * @param in_vertex2
     * @param in_normal2
     * @param in_color2
     * @param in_vertex3
     * @param in_normal3
     * @param in_color3
     */
    void draw_triangle(vector3_type const& in_vertex1,
               vector3_type const& in_normal1,
               vector3_type const& in_color1,
               vector3_type const& in_vertex2,
               vector3_type const& in_normal2,
               vector3_type const& in_color2,
               vector3_type const& in_vertex3,
               vector3_type const& in_normal3,
               vector3_type const& in_color3)
    {
        //--- Test if render pipeline was set up correctly
        if(!m_vertex_program)
        throw std::logic_error("vertex program was not loaded");

        if(!m_rasterizer)
        throw std::logic_error("rasterizer was not loaded");

        if(!m_fragment_program)
        throw std::logic_error("fragment program was not loaded");

        //--- Temporaries used to hold output from vertex program
        vector3_type out_vertex1;
        vector3_type out_vertex2;
        vector3_type out_vertex3;
        vector3_type out_normal1;
        vector3_type out_normal2;
        vector3_type out_normal3;
        vector3_type out_color1;
        vector3_type out_color2;
        vector3_type out_color3;

        //--- Ask vertex program to process all the vertex data.
        m_vertex_program->run(this->state(),
                  in_vertex1,  in_normal1,  in_color1,
                  out_vertex1, out_normal1, out_color1);

        m_vertex_program->run(this->state(),
                  in_vertex2, in_normal2, in_color2,
                  out_vertex2, out_normal2,  out_color2);

        m_vertex_program->run(this->state(),
                  in_vertex3, in_normal3, in_color3,
                  out_vertex3, out_normal3,  out_color3);

        //--- Initialize rasterizer with output from the vertex program
        m_rasterizer->init(out_vertex1, out_normal1, out_color1,
                   out_vertex2, out_normal2, out_color2,
                   out_vertex3, out_normal3, out_color3);

        //--- Keep on processing fragments until there are none left
        while( m_rasterizer->more_fragments() )
        {
        //--- get screen location of the current fragment
        int screen_x = m_rasterizer->x();
        int screen_y = m_rasterizer->y();

        //--- extract old and new z value and perform a z-test
        real_type z_old = m_zbuffer.read( screen_x, screen_y );
        real_type z_new = m_rasterizer->depth();

        if(  this->state().ztest( z_old, z_new ) )
        {
            //--- The fragment passed the z-test, now we need to ask
            //--- the fragment program to compute the color of the fragment.
            vector3_type out_color;               // uninitialized!
            out_color = m_rasterizer->color();    // now initialized!

            m_fragment_program->run(this->state(),
                        m_rasterizer->position(),
                        m_rasterizer->normal(),
                        m_rasterizer->color(),
                        out_color);

            //--- Finally we write the new z-value to the z-buffer
            //--- and the new color to the frame buffer.
            m_zbuffer.write( screen_x, screen_y, z_new);
            this->write_pixel_to_frame_buffer(screen_x, screen_y, out_color);
        }

        //--- We finished processing the fragment, so we
        //--- can advance to the next fragment.
        m_rasterizer->next_fragment();
        }
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
        m_frame_buffer.flush();
    }
    };
}// end namespace graphics

// GRAPHICS_RENDER_PIPELINE_H
#endif
