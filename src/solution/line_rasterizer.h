#ifndef LINE_RASTERIZER_H
#define LINE_RASTERIZER_H
//
// Graphics Framework.
// Copyright (C) 2010 Department of Computer Science, University of Copenhagen
//

#include <iostream>
#include <iomanip>
#include <cmath>

#include "graphics/graphics.h"
#include "linear_interpolator.h"


/*******************************************************************\
*                                                                   *
*                N a m e S p a c e   g r a p h i c s                *
*                                                                   *
\*******************************************************************/

namespace graphics {

/*******************************************************************\
*                                                                   *
*            C l a s s   M y L i n e R a s t e r i z e r            *
*                                                                   *
\*******************************************************************/

    template<typename math_types>
    class MyLineRasterizer : public Rasterizer<math_types>
    {
    public:

        typedef typename math_types::vector3_type      vector3_type;

        typedef typename math_types::real_type         real_type;

    private:

        LinearInterpolator<math_types, real_type> depths;
        LinearInterpolator<math_types, vector3_type> colors;

        void         (MyLineRasterizer::*innerloop)();

        bool         valid;

        bool         Debug;

        int x_current, y_current;
        int x_start, y_start;
        int x_stop, y_stop;
        int dx, dy;
        int abs_2dx , abs_2dy;
        int x_step, y_step;
        int d;
        bool left_right;

        vector3_type dummy_vector;

    public:

        MyLineRasterizer() : Debug(false), valid(false)
        {}


        virtual ~MyLineRasterizer() {}


        void init(vector3_type const& in_vertex1,
                  vector3_type const& in_color1,
                  vector3_type const& in_vertex2,
                  vector3_type const& in_color2)
        {
            dummy_vector = vector3_type(0, 0, 1);

            x_start = in_vertex1[1];
            y_start = in_vertex1[2];
            x_stop = in_vertex2[1];
            y_stop = in_vertex2[2];

            dx = x_stop - x_start;
            dy = y_stop - y_start;

            abs_2dx = std::abs(dx) << 1;
            abs_2dy = std::abs(dy) << 1;

            x_step = (dx < 0) ? -1 : 1;
            y_step = (dy < 0) ? -1 : 1;

            bool x_dominant = (abs_2dx > abs_2dy);
            left_right = x_dominant ? (x_step > 0) : (y_step > 0);

            x_current = x_start;
            y_current = y_start;

            if (x_dominant) {
                d = abs_2dy - (abs_2dx >> 1);
                this->innerloop = &MyLineRasterizer::x_dominant_innerloop;
                depths.init(x_start, x_stop, in_vertex1[3], in_vertex2[3]);
                colors.init(x_start, x_stop, in_color1, in_color2);
            } else {
                d = abs_2dx - (abs_2dy >> 1);
                this->innerloop = &MyLineRasterizer::y_dominant_innerloop;
                depths.init(y_start, y_stop, in_vertex1[3], in_vertex2[3]);
                colors.init(y_start, y_stop, in_color1, in_color2);
            }

            this->Debug = false;
            this->valid = true;
        }

        bool DebugOn()
        {
            bool oldvalue = this->Debug;
            this->Debug = true;

            return oldvalue;
        }

        bool DebugOff()
        {
            bool oldvalue = this->Debug;
            this->Debug = false;

            return oldvalue;
        }

        int x() const
        {
            if (!this->valid) {
            throw std::runtime_error("MyLineRasterizer::x():Invalid State/Not Initialized");
            }
            return this->x_current;     
        }

        int y() const
        {
            if (!this->valid) {
            throw std::runtime_error("MyLineRasterizer::y():Invalid State/Not Initialized");
            }
            return this->y_current;     
        }

        real_type depth() const     
        {
            if (!this->valid) {
            throw std::runtime_error("MyLineRasterizer::depth():Invalid State/Not Initialized");
            }

            return depths.value();
        }

        vector3_type position() const 
        {
            if (!this->valid) {
                throw std::runtime_error("MyLineRasterizer::position():Invalid State/Not Initialized");
            }

            return vector3_type(this->x(), this->y(), this->depth());
        }

        vector3_type const& normal() const     
        {
            if (!this->valid) {
                throw std::runtime_error("MyLineRasterizer::normal():Invalid State/Not Initialized");
            }

            return this->dummy_vector;    // The program should never come here!
        }

        vector3_type const& color() const 
        {
            if (!this->valid) {
                throw std::runtime_error("MyLineRasterizer::color():Invalid State/Not Initialized");
            }

            return colors.value();
        }

        bool more_fragments() const 
        {
            return this->valid;
        }

        void next_fragment()    
        {
            // Dereference a pointer to a private member function.
            // It looks strange, but it is the way to do it!
            (this->*innerloop)();
            depths.next_value();
            colors.next_value();
        }

        void print_variables()
        {
            std::cout << "MyLineRasterizer: local variables" << std::endl;
            std::cout << "=================================" << std::endl;
            std::cout << "\tvalid     == " << this->valid    << std::endl;
        }

    private:

        void x_dominant_innerloop()
        {
            if (x_current == x_stop) {
                valid = false;
            } else {
                if (d > 0 || (d == 0 && left_right)) {
                    y_current += y_step;
                    d -= abs_2dx;
                }

                x_current += x_step;
                d += abs_2dy;
            }
        }

        void y_dominant_innerloop()
        {
            if (y_current == y_stop) {
                valid = false;
            } else {
                if (d > 0 || (d == 0 && left_right)) {
                    x_current += x_step;
                    d -= abs_2dy;
                }

                y_current += y_step;
                d += abs_2dx;
            }
        }
    };

}// end namespace graphics

// LINE_RASTERIZER_H
#endif
