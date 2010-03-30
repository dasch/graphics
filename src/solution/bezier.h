#ifndef BEZIER_H
#define BEZIER_H

#include "solution/math_types.h"
#include "solution/parser.h"
#include "solution/triangle.h"

using namespace std;

namespace graphics
{
    typedef MyMathTypes::matrix4x4_type matrix4x4_t;
    typedef Matrix<vertex_t, 4, 4> surface_t;

    surface_t
    patch_to_surface(vertex_t *vertices, patch_t *patch)
    {
        surface_t surface;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                surface[i+1][j+1] = vertices[patch->vertices[i * 4 + j]];
            }
        }

        return surface;
    }


    class Bezier
    {
    private:
        Triangle *_triangles;
        unsigned int _count, _depth;

    public:

        /**
         *
         */
        Bezier(unsigned int depth)
        {
            _depth = depth;
            _triangles = (Triangle*)malloc(sizeof(Triangle) * pow(4, depth) * 2);
        }

        /**
         *
         */
        void
        init(surface_t &surface)
        {
            _count = 0;

            bezier(surface, _depth);
        }

        Triangle *
        getTriangles()
        {
            return _triangles;
        }

        unsigned int
        getCount()
        {
            return _count;
        }

    private:

        void
        bezier(surface_t &surface, unsigned int depth)
        {
            surface_t bl, br, tr, tl;

            if (depth == 0) {
                draw_surface(surface);
                return;
            }

            subdivide(surface, bl, br, tr, tl);

            bezier(bl, depth - 1);
            bezier(br, depth - 1);
            bezier(tr, depth - 1);
            bezier(tl, depth - 1);
        }

        void
        subdivide_horizontal(surface_t &surface, surface_t &left, surface_t &right)
        {
            vertex_t p1, p2, p3, p4, tmp;

            for (int i = 1; i <= 4; i++) {
                p1 = surface[i][1];
                p2 = surface[i][2];
                p3 = surface[i][3];
                p4 = surface[i][4];

                tmp = (p2 + p3) / 2;

                left[i][1] = p1;
                right[i][4] = p4;

                left[i][2] = (p1 + p2) / 2;
                right[i][3] = (p3 + p4) / 2;

                left[i][3] = (left[i][2] + tmp) / 2;
                right[i][2] = (right[i][3] + tmp) / 2;

                left[i][4] = (left[i][3] + right[i][2]) / 2;
                right[i][1] = left[i][4];
            }
        }

        void
        subdivide_vertical(surface_t &surface, surface_t &top, surface_t &bottom)
        {
            vertex_t p1, p2, p3, p4, tmp;

            for (int i = 1; i <= 4; i++) {
                p1 = surface[1][i];
                p2 = surface[2][i];
                p3 = surface[3][i];
                p4 = surface[4][i];

                tmp = (p2 + p3) / 2;

                top[1][i] = p1;
                bottom[4][i] = p4;

                top[2][i] = (p1 + p2) / 2;
                bottom[3][i] = (p3 + p4) / 2;

                top[3][i] = (top[2][i] + tmp) / 2;
                bottom[2][i] = (bottom[3][i] + tmp) / 2;

                top[4][i] = (top[3][i] + bottom[2][i]) / 2;
                bottom[1][i] = top[4][i];
            }
        }

        /**
         * Divide the surface into four sub-surfaces.
         */
        void
        subdivide(surface_t &surface, surface_t &bl, surface_t &br, surface_t &tr, surface_t &tl)
        {
            surface_t left, right;

            subdivide_horizontal(surface, left, right);

            subdivide_vertical(left, tl, bl);
            subdivide_vertical(right, tr, br);
        }

        /**
         * Draw the two triangles that make up the surface.
         */
        void
        draw_surface(surface_t &surface)
        {
            vertex_t v1, v2, v3, v4;

            v1 = surface[1][1];
            v2 = surface[4][1];
            v3 = surface[4][4];
            v4 = surface[1][4];
            
            _triangles[_count++] = Triangle(v1, v2, v4);
            _triangles[_count++] = Triangle(v4, v2, v3);
        }

        void
        debug_surface(surface_t &s)
        {
            cout << "(" << s[1][1] << ")  (" <<s[1][2] << ")  (" << s[1][3] << ")  (" << s[1][4] << ")" << endl;
            cout << "(" << s[2][1] << ")  (" <<s[2][2] << ")  (" << s[2][3] << ")  (" << s[2][4] << ")" << endl;
            cout << "(" << s[3][1] << ")  (" <<s[3][2] << ")  (" << s[3][3] << ")  (" << s[3][4] << ")" << endl;
            cout << "(" << s[4][1] << ")  (" <<s[4][2] << ")  (" << s[4][3] << ")  (" << s[4][4] << ")" << endl;
            cout << endl << flush;
        }
    };
}

#endif
