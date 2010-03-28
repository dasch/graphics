#ifndef SUBDIVIDER_H
#define SUBDIVIDER_H

#include "solution/math_types.h"
#include "solution/parser.h"

namespace graphics
{
    typedef MyMathTypes::vector3_type vector3_t;
    typedef MyMathTypes::matrix4x4_type matrix4x4_t;
    typedef Matrix<vector3_t, 4, 4> surface_t;

    typedef vector3_t *triangle_t;

    surface_t *
    patch_to_surface(vertex_t *vertices, patch_t *patch)
    {
        surface_t *surface = (surface_t*)malloc(sizeof(surface_t));

        std::cout << "patch: " << patch->vertices[4] << std::endl;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << "i = " << i << ", j = " << j << ", patch = " << patch->vertices[i * 4 + j] << endl;
                surface[i+1][j+1] = vertices[patch->vertices[i * 4 + j]];
            }
        }

        return surface;
    }

//    class Subdivider
//    {
//    private:
//
//        surface_t *_surface;
//        triangle_t _triangle;
//        bool _valid;
//
//    public:
//
//        void
//        init(surface_t *surface)
//        {
//            _surface = surface;
//            _valid = true;
//
//            _triangle = (triangle_t)malloc(sizeof(vector3_t) * 3);
//
//            _triangle[0] = surface[1][1];
//            _triangle[1] = surface[1][4];
//            _triangle[2] = surface[4][1];
//        }
//
//        bool
//        more_triangles()
//        {
//            return _num_divisions < 3;
//        }
//
//        void
//        next_triangle()
//        {
//            _triangle = (triangle_t)malloc(sizeof(vector3_t) * 3);
//
//            _triangle[0] = surface[4][4];
//            _triangle[1] = surface[1][4];
//            _triangle[2] = surface[4][1];
//
//            _valid = false;
//        }
//
//        triangle_t
//        current_triangle()
//        {
//            return _triangle;
//        }
//    };
}

#endif
