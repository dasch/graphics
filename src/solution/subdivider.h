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

    void
    divide_surface_into_triangles(surface_t *surface, unsigned int const depth, Triangle *triangles)
    {
        if (depth == 0) {
            surface_to_triangles(surface, &triangles[0], &triangles[1]);
            return;
        }
    }

    void
    subdivide_horizontal(surface_t *surface, surface_t *left, surface_t *right)
    {
        vertex_t p1, p2, p3, p4, tmp;

        for (int i = 1; i <= 4; i++) {
            p1 = (*surface)[i][1];
            p2 = (*surface)[i][2];
            p3 = (*surface)[i][3];
            p4 = (*surface)[i][4];

            tmp = (p2 + p3) / 2;

            (*left)[i][1] = p1;
            (*right)[i][4] = p4;

            (*left)[i][2] = (p1 + p2) / 2;
            (*right)[i][3] = (p3 + p4) / 2;

            (*left)[i][3] = ((*left)[i][2] + tmp) / 2;
            (*right)[i][2] = ((*right)[i][3] + tmp) / 2;

            (*left)[i][4] = ((*left)[i][3] + (*right)[i][2]) / 2;
            (*right)[i][1] = (*left)[i][4];
        }
    }

    void
    subdivide_vertical(surface_t *surface, surface_t *top, surface_t *bottom)
    {
        vertex_t p1, p2, p3, p4, tmp;

        for (int i = 1; i <= 4; i++) {
            p1 = (*surface)[1][i];
            p2 = (*surface)[2][i];
            p3 = (*surface)[3][i];
            p4 = (*surface)[4][i];

            tmp = (p2 + p3) / 2;

            (*top)[1][i] = p1;
            (*bottom)[4][i] = p4;

            (*top)[2][i] = (p1 + p2) / 2;
            (*bottom)[3][i] = (p3 + p4) / 2;

            (*top)[3][i] = ((*top)[2][i] + tmp) / 2;
            (*bottom)[2][i] = ((*bottom)[3][i] + tmp) / 2;

            (*top)[4][i] = ((*top)[3][i] + (*bottom)[2][i]) / 2;
            (*bottom)[1][i] = (*top)[4][i];
        }
    }

    void
    subdivide(surface_t *surface, surface_t &bl, surface_t &br, surface_t &tr, surface_t &tl)
    {
        surface_t left, right;

        subdivide_horizontal(surface, &left, &right);

        subdivide_vertical(&left, &bl, &tl);
        subdivide_vertical(&right, &br, &tr);
    }

    Triangle *
    draw_object(object_t *object, int& count)
    {
        surface_t *surface, bl, br, tl, tr;
        patch_list_t *patches;
        Triangle *triangles;

        patches = object->patches;

        count = patches->num_patches * 4 * 2;
        triangles = (Triangle*)malloc(sizeof(Triangle) * count);

        int i = 0;
        for (patch_t *patch = patches->head; patch != NULL; patch = patch->next) {
            surface = patch_to_surface(object->vertices, patch);

            subdivide(surface, bl, br, tr, tl);

            surface_to_triangles(&bl, &triangles[i++], &triangles[i++]);
            surface_to_triangles(&br, &triangles[i++], &triangles[i++]);
            surface_to_triangles(&tl, &triangles[i++], &triangles[i++]);
            surface_to_triangles(&tr, &triangles[i++], &triangles[i++]);
        }

        return triangles;
    }

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
