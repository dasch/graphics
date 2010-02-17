#ifndef TRIANGLE_RASTERIZER_H
#define TRIABGLE_RASTERIZER_H
//
// Graphics Framework.
// Copyright (C) 2010 Department of Computer Science, University of Copenhagen
//

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include "graphics/graphics.h"
#include "edge_rasterizer.h"
// #include "linear_interpolator"



namespace graphics {

    template<typename math_types>
    class MyTriangleRasterizer : public Rasterizer<math_types>
    {
        public:
        typedef typename math_types::vector3_type vector3_type;
        typedef typename math_types::real_type    real_type;

        protected:


        public:
        MyTriangleRasterizer() : valid(false), Debug(false)
        {}


        virtual ~MyTriangleRasterizer()
        {}


        void init(vector3_type const& in_vertex1,
                  vector3_type const& in_normal1,
                  vector3_type const& in_color1,
                  vector3_type const& in_vertex2,
                  vector3_type const& in_normal2,
                  vector3_type const& in_color2,
                  vector3_type const& in_vertex3,
                  vector3_type const& in_normal3,
                  vector3_type const& in_color3) 
        {
            // This is a triangle rasterizer
            // Save the original parameters

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

        bool Valid() const
        {
            // implement the real version
            return true;
        }

        bool Degenerate() const
        {
            // implement the real version
            return false;
        }

        int x() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyTriangleRasterizer::x():Invalid State/Not Initialized");
            }

            return 0;
        }

        int y() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyTriangleRasterizer::y():Invalid State/Not Initialized");
            }

            return 0;
        }

        real_type depth() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyTriangleRasterizer::depth():Invalid State/Not Initialized");
            }

            return 0.0;
        }

        vector3_type position() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyTriangleRasterizer::position():Invalid State/Not Initialized");
            }

            return vector3_type(this->x(), this->y(), this->depth());
        }

        vector3_type const& normal() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyTriangleRasterizer::normal():Invalid State/Not Iitialized");
            }

            return this->dummy_vector;
        }

        vector3_type const& color() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyTriangleRasterizer::color():Invalid State/Not Initialized");
            }

            return this->dummy_vector;
        }

        void print_variables()
        {
            std::cout << "MyTriangleRasterizer: local variables" << std::endl;
            std::cout << "=====================================" << std::endl;
            std::cout << "\tvalid     == " << this->valid    << std::endl;
            std::cout << std::endl;
        }

        bool more_fragments() const
        {
            // implement the real version
            return false;
        }

        void next_fragment()
        {
            // implement the real version
        }

        private:
        // Initialize the current triangle for rasterization
        void initialize_triangle()
        {
            // implement the real version
            this->valid = true;    // necessary?
        }


        // A triangle is degenerate if all three points are co-linear
        bool degenerate()
        {
            return false;
        }


        // LowerLeft() returns the index of the vertex with the smallest y-coordinate
        // If there is a horizontal edge, the vertex with the smallest 
        // x-coordinate is chosen.
        // The computations should be done in integer coordinates.
        int LowerLeft()
        {
            return 0;
        }

        // UpperLeft() returns the index of the vertex with the greatest y-coordinate
        // If there is a horizontal edge, the vertex with the smallest 
        // x-coordinate is chosen.
        // The computations should be done in integer coordinates.
        int UpperLeft()
        {
            return 0;
        }

        bool SearchForNonEmptyScanline()
        {
            // Assumes that the current scanline is empty!

            // implement the real version
            return this->valid;
        }

        void choose_color(int x)
        {
            // x is the position on a scanline in a triangle - they all have different colors:
            //    xstart  : green
            //    xcurrent: yellow
            //    xstop   : red
            // This is like a trafic-light: green->go ahead, yellow->be carefull, red->stop!

            // implement the real version
        }


        // Private Variables

        vector3_type dummy_vector;

        // The Debug variable
        bool Debug;


        // Indices into the vertex table
        int lower_left;
        int upper_left;
        int the_other;

        bool valid;
    };

}// end namespace graphics

// TRIANGLE_RASTERIZER_H
#endif
