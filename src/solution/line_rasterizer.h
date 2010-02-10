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

        MyLineRasterizer() : Debug(false), valid(false)
        {}


        virtual ~MyLineRasterizer() {}


        void init(vector3_type const& in_vertex1,
                  vector3_type const& in_color1,
                  vector3_type const& in_vertex2,
                  vector3_type const& in_color2)
        {
            // This is a line rasterizer
            // The vertices are in 3D screen coordinates

            // Determine if the line is x-dominat or y-dominant
            // if (?) {
            // The line is x-dominant

            // Set up a pointer for the inner-loop for an x-donmiant line
            // This is a pointer to a private member function!
            // Therefore it looks very strange, but this is how to do it!
            
                // this->innerloop = &MyLineRasterizer::x_dominant_innerloop;
            //}
            //else {
            // The line is y-dominant

                    // Set up a pointer for the inner-loop for a y-donmiant line
            // This is a pointer to a private member function!
            // Therefore it looks very strange, but this is how to do it!

            // this->innerloop = &MyLineRasterizer::y_dominant_innerloop;
            //}

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
            return 0;     
        }

        int y() const
        {
            if (!this->valid) {
            throw std::runtime_error("MyLineRasterizer::y():Invalid State/Not Initialized");
            }
            return 0;
        }

        real_type depth() const     
        {
            if (!this->valid) {
            throw std::runtime_error("MyLineRasterizer::depth():Invalid State/Not Initialized");
            }
            return 0.0;
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

            return this->dummy_vector;
        }

        bool more_fragments() const 
        {
            // Usage:
            //    Assume a pointer variable rasterizer is set up probably
            //     while (rasterizer->more_fragments()) {
            //         int x = rasterize->x();
            //         int y = rasterizer->y();
            //         MyMathTypes::real_type depth = rasterizer->depth();
            //         MyMathTypes::vector3_type    = rasterizer->position();
            //         MyMathTypes::vector3_type    = rasterizer->color();
            //             ...
            //             use the values ...
            //             ...
            //         rasterizer->next_fragment();
            //    }

            return false;
        }

        void next_fragment()    
        {
            // Dereference a pointer to a private member function.
            // It looks strange, but it is the way to do it!
            (this->*innerloop)();
        }

        void print_variables()
        {
            std::cout << "MyLineRasterizer: local variables" << std::endl;
            std::cout << "=================================" << std::endl;
            std::cout << "\tvalid     == " << this->valid    << std::endl;
        }

        private:

        void x_dominant_innerloop()
        {}

        void y_dominant_innerloop()
        {}

        // This looks strange, byt it is the definition of a pointer to a 
        // private member function! That is how it is done!
        void         (MyLineRasterizer::*innerloop)();

        bool         valid;

        bool         Debug;

        vector3_type dummy_vector;
    };

}// end namespace graphics

// LINE_RASTERIZER_H
#endif
