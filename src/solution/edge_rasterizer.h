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

        private:
        LinearInterpolator<math_types, real_type> depths;
        LinearInterpolator<math_types, vector3_type> i_colors;

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
                  vector3_type const& in_color2,
                  vector3_type const& in_vertex3,
                  vector3_type const& in_normal3,
                  vector3_type const& in_color3)
        {
            vertices[0] = in_vertex1;
            vertices[1] = in_vertex2;
            vertices[2] = in_vertex3;

            colors[0] = in_color1;
            colors[1] = in_color2;
            colors[2] = in_color3;

            if (in_vertex1[2] == in_vertex2[2]) {
                two_edges = false;
                initialize_edge(1, 2);
            } else {
                two_edges = true;
                initialize_edge(0, 1);
            }
        }

        void init(vector3_type const& in_vertex1,
                  vector3_type const& in_normal1,
                  vector3_type const& in_color1,
                  vector3_type const& in_vertex2,
                  vector3_type const& in_normal2,
                  vector3_type const& in_color2)
        {
            vertices[0] = in_vertex1;
            vertices[1] = in_vertex2;

            colors[0] = in_color1;
            colors[1] = in_color2;

            two_edges = false;

            initialize_edge(0, 1);
        }

        void initialize_edge(int i, int j)
        {
            vector3_type start, stop;

            start = vertices[i];
            stop  = vertices[j];

            x_start = static_cast<int>(round(start[1]));
            y_start = static_cast<int>(round(start[2]));

            x_stop = static_cast<int>(round(stop[1]));
            y_stop = static_cast<int>(round(stop[2]));

            x_current = x_start;
            y_current = y_start;

            dx = x_stop - x_start;
            x_step = (dx < 0) ? -1 : 1;

            numerator = std::abs(dx);
            denominator = y_stop - y_start;
            accumulator = (dx > 0) ? denominator : 1;

            depths.init(y_start, y_stop, vertices[i][3], vertices[j][3]);
            i_colors.init(y_start, y_stop, colors[i], colors[j]);

            this->valid = (y_current < y_stop);
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

            return depths.value();;
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

            return i_colors.value();
        }

        void print_variables()
        {
            std::cout << "MyEdgeRasterizer: local variables" << std::endl;
            std::cout << "=================================" << std::endl;
            std::cout << std::endl;
        }

        bool more_fragments() const
        {
            return valid;
        }

        void next_fragment()
        {
            y_current++;

            if (y_current == y_stop) {
                if (!two_edges) {
                    valid = false;
                } else {
                    initialize_edge(1, 2);
                    two_edges = false;
                }
            } else {
                accumulator += numerator;

                while (accumulator > denominator) {
                    x_current += x_step;
                    accumulator -= denominator;
                }
            }

            depths.next_value();
            i_colors.next_value();
        }

        protected:

        private:

        bool valid, two_edges;
        int x_start, y_start;
        int x_current, y_current;
        int x_stop, y_stop;
        int dx, x_step;
        int numerator, denominator, accumulator;

        vector3_type vertices[3], colors[3];
    };

}// end namespace graphics

// EDGE_RASTERIZER_H
#endif
