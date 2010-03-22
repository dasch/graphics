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
        LinearInterpolator<math_types, real_type> depths;
        LinearInterpolator<math_types, vector3_type> i_colors;
        LinearInterpolator<math_types, vector3_type> i_world;

        protected:

        MyEdgeRasterizer<MyMathTypes> left_edge, right_edge;

        public:
        MyTriangleRasterizer() : valid(false), Debug(false)
        {}


        virtual ~MyTriangleRasterizer()
        {}


        void init(vector3_type const& in_vertex1,
                  vector3_type const& in_world1,
                  vector3_type const& in_normal1,
                  vector3_type const& in_color1,
                  vector3_type const& in_vertex2,
                  vector3_type const& in_world2,
                  vector3_type const& in_normal2,
                  vector3_type const& in_color2,
                  vector3_type const& in_vertex3,
                  vector3_type const& in_world3,
                  vector3_type const& in_normal3,
                  vector3_type const& in_color3) 
        {
            this->Debug = false;
            this->valid = true;

            edges[0] = in_vertex1;
            edges[1] = in_vertex2;
            edges[2] = in_vertex3;

            normals[0] = in_normal1;
            normals[1] = in_normal2;
            normals[2] = in_normal3;

            colors[0] = in_color1;
            colors[1] = in_color2;
            colors[2] = in_color3;

            world[0] = in_world1;
            world[1] = in_world2;
            world[2] = in_world3;

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
                left_edge.init(edges[lower_left], world[lower_left], normals[lower_left], colors[lower_left],
                               edges[upper_left], world[upper_left], normals[upper_left], colors[upper_left]);

                right_edge.init(edges[lower_left], world[lower_left], normals[lower_left], colors[lower_left],
                                edges[the_other],  world[the_other],  normals[the_other],  colors[the_other],
                                edges[upper_left], world[upper_left], normals[upper_left], colors[upper_left]);
            } else if (cross[3] > 0) {
                left_edge.init(edges[lower_left], world[lower_left], normals[lower_left], colors[lower_left],
                               edges[the_other],  world[the_other],  normals[the_other],  colors[the_other],
                               edges[upper_left], world[upper_left], normals[upper_left], colors[upper_left]);

                right_edge.init(edges[lower_left], world[lower_left], normals[lower_left], colors[lower_left],
                                edges[upper_left], world[upper_left], normals[upper_left], colors[upper_left]);

            } else {
                std::cout << edges[0] << edges[1] << edges[2] << std::endl;
                std::cout << lower_left << ", " << upper_left << ", " << the_other << std::endl;
                std::cout << "TriangleRasterizer: UH OH!" << std::endl;
                std::cout << "lower_left: " << edges[lower_left] << std::endl;
                std::cout << "upper_left: " << edges[upper_left] << std::endl;
                std::cout << "the_other:  " << edges[the_other] << std::endl;
                throw new std::runtime_error("UH OH!");
            }

            x_current = left_edge.x();
            y_current = left_edge.y();

            x_stop = right_edge.x();

            depths.init(left_edge.x(), right_edge.x(), left_edge.depth(), right_edge.depth());
            i_colors.init(left_edge.x(), right_edge.x(), left_edge.color(), right_edge.color());
            i_world.init(left_edge.x(), right_edge.x(), left_edge.position(), right_edge.position());

            SearchForNonEmptyScanline();
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

            return depths.value();
        }

        vector3_type position() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyTriangleRasterizer::position():Invalid State/Not Initialized");
            }

            return i_world.value();
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

            return i_colors.value();
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

            depths.next_value();
            i_colors.next_value();
            i_world.next_value();

            SearchForNonEmptyScanline();
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

        void SearchForNonEmptyScanline()
        {
            while (x_current == x_stop && (left_edge.more_fragments() || right_edge.more_fragments())) {
                x_current = left_edge.x();
                y_current = left_edge.y();

                x_stop = right_edge.x();

                depths.init(left_edge.x(), right_edge.x(), left_edge.depth(), right_edge.depth());
                i_colors.init(left_edge.x(), right_edge.x(), left_edge.color(), right_edge.color());
                i_world.init(left_edge.x(), right_edge.x(), left_edge.position(), right_edge.position());

                left_edge.next_fragment();
                right_edge.next_fragment();
            }
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
        vector3_type vertices[3], world[3];

        int x_current, y_current;
        int x_stop;

        bool valid;
    };

}// end namespace graphics

// TRIANGLE_RASTERIZER_H
#endif
