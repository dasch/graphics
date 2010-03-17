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

        private:
        LinearInterpolator<math_types, typename math_types::real_type> depth_interpolator;

        protected:

        MyEdgeRasterizer<MyMathTypes> left_edge, right_edge;

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
            edges[0] = in_vertex1;
            edges[1] = in_vertex2;
            edges[2] = in_vertex3;

            normals[0] = in_normal1;
            normals[1] = in_normal2;
            normals[2] = in_normal3;

            colors[0] = in_color1;
            colors[1] = in_color2;
            colors[2] = in_color3;

            vertices[0][1] = static_cast<int>(round(edges[0][1]));
            vertices[0][2] = static_cast<int>(round(edges[0][2]));
            vertices[0][3] = 0;

            vertices[1][1] = static_cast<int>(round(edges[1][1]));
            vertices[1][2] = static_cast<int>(round(edges[1][2]));
            vertices[1][3] = 0;

            vertices[2][1] = static_cast<int>(round(edges[2][1]));
            vertices[2][2] = static_cast<int>(round(edges[2][2]));
            vertices[2][3] = 0;

            lower_left = LowerLeft();
            upper_left = UpperLeft();
            the_other = 3 - lower_left - upper_left;

            vector3_type ll, ul, ot;

            ll = vertices[lower_left];
            ul = vertices[upper_left];
            ot = vertices[the_other];

            vector3_type cross = Cross(ul - ll, ot - ll);

            if (cross[3] < 0) {
                left_edge.init(edges[lower_left], normals[lower_left], colors[lower_left],
                               edges[upper_left], normals[upper_left], colors[upper_left]);

                right_edge.init(edges[lower_left], normals[lower_left], colors[lower_left],
                                edges[the_other], normals[the_other], colors[the_other],
                                edges[upper_left], normals[upper_left], colors[upper_left]);
            } else if (cross[3] > 0) {
                left_edge.init(edges[lower_left], normals[lower_left], colors[lower_left],
                               edges[the_other], normals[the_other], colors[the_other],
                               edges[upper_left], normals[upper_left], colors[upper_left]);

                right_edge.init(edges[lower_left], normals[lower_left], colors[lower_left],
                                edges[upper_left], normals[upper_left], colors[upper_left]);

            } else {
                return;
            }

            x_current = left_edge.x();
            y_current = left_edge.y();

            x_stop = right_edge.x();

            this->Debug = false;
            this->valid = true;

            while (SearchForNonEmptyScanline()) {
                x_current = left_edge.x();
                y_current = left_edge.y();

                x_stop = right_edge.x();

                left_edge.next_fragment();
                right_edge.next_fragment();
            }

            depth_interpolator.init(left_edge.x(), right_edge.x(), left_edge.depth(), right_edge.depth());
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
            return valid;
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

            return x_current;
        }

        int y() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyTriangleRasterizer::y():Invalid State/Not Initialized");
            }

            return y_current;
        }

        real_type depth() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyTriangleRasterizer::depth():Invalid State/Not Initialized");
            }

            return depth_interpolator.value();
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
            return left_edge.more_fragments()
                || right_edge.more_fragments()
                || x_current < x_stop;
        }

        void next_fragment()
        {
            x_current++;

            while (SearchForNonEmptyScanline()) {
                x_current = left_edge.x();
                y_current = left_edge.y();

                x_stop = right_edge.x();

                left_edge.next_fragment();
                right_edge.next_fragment();
            }

            depth_interpolator.init(left_edge.x(), right_edge.x(), left_edge.depth(), right_edge.depth());
        }

        private:

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
            int ll = 0;
            vector3_type a, b;

            for (int i = 0; i < 3; i++) {
                a = vertices[i];
                b = vertices[ll];

                if (a[2] < b[2] || (a[2] == b[2] && a[1] < b[1])) {
                    ll = i;
                }
            }

            return ll;
        }

        // UpperLeft() returns the index of the vertex with the greatest y-coordinate
        // If there is a horizontal edge, the vertex with the smallest 
        // x-coordinate is chosen.
        // The computations should be done in integer coordinates.
        int UpperLeft()
        {
            int ul = 0;
            vector3_type a, b;

            for (int i = 0; i < 3; i++) {
                a = vertices[i];
                b = vertices[ul];

                if (a[2] > b[2] || (a[2] == b[2] && a[1] < b[1])) {
                    ul = i;
                }
            }

            return ul;
        }

        bool SearchForNonEmptyScanline()
        {
            return (x_current == x_stop)
                && (left_edge.more_fragments() || right_edge.more_fragments());
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

        vector3_type edges[3], normals[3], colors[3];
        vector3_type vertices[3];

        int x_current, y_current;
        int x_stop;

        bool valid;
    };

}// end namespace graphics

// TRIANGLE_RASTERIZER_H
#endif
