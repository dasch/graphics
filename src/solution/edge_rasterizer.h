#ifndef EDGE_RASTERIZER_H
#define EDGE_RASTERIZER_H
//
// Graphics Framework.
// Copyright (C) 2010 Department of Computer Science, University of Copenhagen
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include "graphics/graphics.h"

namespace graphics {

    // Draws an edge from V1 to V2, or two edges - one from V1 to V2 and one from V2 to V3.
    // Edges are assumed NOT to be horizontal!
    template<typename math_types>
    class MyEdgeRasterizer
    {
        public:
        typedef typename math_types::real_type    real_type;
        typedef typename math_types::vector3_type vector3_type;

        public:
        MyEdgeRasterizer() : valid(true)
        {
            std::cout << "MyEdgeRasterizer::MyEdgeRasterizer(): called" << std::endl;
        }

        virtual ~MyEdgeRasterizer()
        {}

        void init(vector3_type const& in_vertex1,
                  vector3_type const& in_normal1,
                  vector3_type const& in_color1,
                  vector3_type const& in_vertex2,
                  vector3_type const& in_normal2,
                  vector3_type const& in_color2)
        {
            x_start = in_vertex1[1];
            y_start = in_vertex1[2];

            x_stop = in_vertex2[1];
            y_stop = in_vertex2[2];

            x_current = x_start;
            y_current = y_start;

            dx = x_stop - x_start;
            x_step = (dx < 0) ? -1 : 1;

            numerator = std::abs(dx);
            denominator = y_stop - y_start;
            accumulator = (dx > 0) ? denominator : 1;

            this->valid = true;
        }

        int x() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyEdgeRasterizer::x():Invalid State/Not Initialized");
            }

            return x_current;
        }

        int y() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyEdgeRasterizer::y():Invalid State/Not Initialized");
            }

            return y_current;
        }

        real_type depth() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyEdgeRasterizer::depth():Invalid State/Not Initialized");
            }

            return 0;
        }

        vector3_type position() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyEdgeRasterizer::position():Invalid State/Not Initialized");
            }

            return vector3_type(this->x(), this->y(), this->depth());
        }

        vector3_type normal() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyEdgeRasterizer::normal():Invalid State/Not Initialized");
            }

            return vector3_type(0.0, 0.0, 0.0);
        }

        vector3_type color() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyEdgeRasterizer::color():Invalid State/Not Initialized");
            }

            return vector3_type(0.0, 0.0, 0.0);
        }

        void print_variables()
        {
            std::cout << "MyEdgeRasterizer: local variables" << std::endl;
            std::cout << "=================================" << std::endl;
            std::cout << std::endl;
        }

        bool more_fragments() const
        {
            return (y_current < y_stop);
        }

        void next_fragment()
        {
            y_current++;
            accumulator += numerator;

            while (accumulator > denominator) {
                x_current += x_step;
                accumulator -= denominator;
            }
        }

        protected:

        private:

        bool valid;
        int x_start, y_start;
        int x_current, y_current;
        int x_stop, y_stop;
        int dx, x_step;
        int numerator, denominator, accumulator;
    };

}// end namespace graphics

// EDGE_RASTERIZER_H
#endif
