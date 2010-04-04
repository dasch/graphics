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
    patch_to_surface(vertex_t const *vertices, patch_t const *patch)
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
        Bezier(unsigned int const depth)
        {
            _depth = depth;
            _triangles = (Triangle*)malloc(sizeof(Triangle) * pow(4, depth + 1) * 2);
        }

        /**
         *
         */
        void
        init(surface_t const &surface)
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
        bezier(surface_t const &surface, int const depth)
        {
            surface_t bl, br, tr, tl;

            if (depth <= 0 && is_convex(surface)) {
                draw_surface(surface);
                return;
            }

            subdivide(surface, bl, br, tr, tl);

            bezier(bl, depth - 1);
            bezier(br, depth - 1);
            bezier(tr, depth - 1);
            bezier(tl, depth - 1);
        }

        static inline void
        subdivide_horizontal(surface_t const &surface, surface_t &left, surface_t &right)
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

        static inline void
        subdivide_vertical(surface_t const &surface, surface_t &top, surface_t &bottom)
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
        subdivide(surface_t const &surface, surface_t &bl, surface_t &br, surface_t &tr, surface_t &tl)
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
        draw_surface(surface_t const &surface)
        {
            vertex_t v[4], t[4], s[4], n[4];

            v[0] = surface[1][1];
            v[1] = surface[1][4];
            v[2] = surface[4][1];
            v[3] = surface[4][4];

            t[0] = surface[1][2] - v[0];
            t[1] = surface[1][3] - v[1];
            t[2] = surface[4][2] - v[2];
            t[3] = surface[4][3] - v[3];

            s[0] = surface[2][1] - v[0];
            s[1] = surface[2][4] - v[1];
            s[2] = surface[3][1] - v[2];
            s[3] = surface[3][4] - v[3];

            // Merge tangents.
            for (int i = 0; i < 4; i++) {
                for (int j = i+1; j < 4; j++) {
                    if (v[i] != v[j])
                        continue;

                    if (t[i] == 0 && t[j] == 0 && j-i == 1) {
                        // Merge horizontally.
                        t[i] = s[j];
                        t[j] = s[i];
                    } else if (s[i] == 0 && s[j] == 0 && j-i == 2) {
                        // Merge vertically.
                        s[i] = t[j];
                        s[j] = t[i];
                    }
                }
            }

            n[0] = Cross(s[0], t[0]);
            n[1] = Cross(t[1], s[1]);
            n[2] = Cross(t[2], s[2]);
            n[3] = Cross(s[3], t[3]);

            for (int i = 0; i < 4; i++) {
                if (Norm(n[i]) == 0) {
                    n[i] = vertex_t(0, 0, 1);
                } else {
                    n[i] /= Norm(n[i]);
                }
            }

            _triangles[_count++] = Triangle(v[2], n[2], v[3], n[3], v[0], n[0]);
            _triangles[_count++] = Triangle(v[1], n[1], v[0], n[0], v[3], n[3]);
        }

        static bool
        is_convex(surface_t const &surface)
        {
            vertex_t v1, v2, v3, v4;

            for (int i = 1; i <= 4; i++) {
                v1 = surface[i][1];
                v2 = surface[i][2];
                v3 = surface[i][3];
                v4 = surface[i][4];

                if (!is_convex_curve(v1, v2, v3, v4)) {
                    cout << "not convex!" << endl;
                    return false;
                }
            }

            for (int i = 1; i <= 4; i++) {
                v1 = surface[1][i];
                v2 = surface[2][i];
                v3 = surface[3][i];
                v4 = surface[4][i];

                if (!is_convex_curve(v1, v2, v3, v4)) {
                    cout << "not convex!" << endl;
                    return false;
                }
            }

            return true;
        }

        static bool
        is_convex_curve(vertex_t const &v1,
                        vertex_t const &v2,
                        vertex_t const &v3,
                        vertex_t const &v4)
        {
            vertex_t base, v1v2, v1v3;

            base = v4 - v1;
            v1v2 = v2 - v1;
            v1v3 = v3 - v1;

            return !(base * v1v2 > base * v1v3);
        }

        void
        debug_surface(surface_t const &s)
        {
            cout << "(" << s[1][1] << ")  (" <<s[1][2] << ")  (" << s[1][3] << ")  (" << s[1][4] << ")" << endl;
            cout << "(" << s[2][1] << ")  (" <<s[2][2] << ")  (" << s[2][3] << ")  (" << s[2][4] << ")" << endl;
            cout << "(" << s[3][1] << ")  (" <<s[3][2] << ")  (" << s[3][3] << ")  (" << s[3][4] << ")" << endl;
            cout << "(" << s[4][1] << ")  (" <<s[4][2] << ")  (" << s[4][3] << ")  (" << s[4][4] << ")" << endl;
            cout << endl << flush;
        }

        vertex_t
        Normal(vertex_t const &original,
               vertex_t const &left,
               vertex_t const &right)
        {
            vertex_t v1 = original - left;
            vertex_t v2 = original - right;
            vertex_t c  = Cross(v2, v1);

            if (Norm(c) == 0)
                return vertex_t(0, 0, 1);

            return c / Norm(c);
        }
    };
}

#endif
