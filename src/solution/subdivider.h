#ifndef SUBDIVIDER_H
#define SUBDIVIDER_H

#include "solution/math_types.h"
#include "solution/parser.h"
#include "solution/triangle.h"


using namespace std;


namespace graphics
{
    typedef MyMathTypes::matrix4x4_type matrix4x4_t;
    typedef Matrix<vertex_t, 4, 4> surface_t;

    void debug_surface(surface_t *surface);

    surface_t *
    patch_to_surface(vertex_t *vertices, patch_t *patch)
    {
        surface_t *surface = (surface_t*)malloc(sizeof(surface_t));

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                (*surface)[i+1][j+1] = vertices[patch->vertices[i * 4 + j]];
            }
        }

        return surface;
    }

    void
    surface_to_triangles(surface_t *surface, Triangle *t1, Triangle *t2)
    {
        if (surface == NULL)
            throw new runtime_error("surface must not be NULL");

        vertex_t v1, v2, v3, v4;

        v1 = (*surface)[1][1];
        v2 = (*surface)[4][1];
        v3 = (*surface)[4][4];
        v4 = (*surface)[1][4];
        
        *t1 = Triangle(v1, v2, v4);
        *t2 = Triangle(v2, v3, v4);
    }

    //void
    //divide_surface_into_triangles(surface_t *surface, unsigned int const depth, Triangle *triangles)
    //{
    //    if (depth == 1)
    //        surface_to_triangles(surface, &triangles[0], &triangles[1]);
    //}

    void
    debug_surface(surface_t *s)
    {
        cout << "(" << (*s)[1][1] << ")  (" <<(*s)[1][2] << ")  (" << (*s)[1][3] << ")  (" << (*s)[1][4] << ")" << endl;
        cout << "(" << (*s)[2][1] << ")  (" <<(*s)[2][2] << ")  (" << (*s)[2][3] << ")  (" << (*s)[2][4] << ")" << endl;
        cout << "(" << (*s)[3][1] << ")  (" <<(*s)[3][2] << ")  (" << (*s)[3][3] << ")  (" << (*s)[3][4] << ")" << endl;
        cout << "(" << (*s)[4][1] << ")  (" <<(*s)[4][2] << ")  (" << (*s)[4][3] << ")  (" << (*s)[4][4] << ")" << endl;
        cout << endl << flush;
    }
}

#endif
