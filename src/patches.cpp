
#include "graphics/graphics.h"
#include "solution/linear_interpolator.h"
#include "solution/point_rasterizer.h"
#include "solution/line_rasterizer.h"
#include "solution/triangle_rasterizer.h"
#include "solution/math_types.h"
#include "solution/camera.h"
#include "solution/vertex_program.h"
#include "solution/fragment_program.h"
#include "solution/parser.h"
#include "solution/subdivider.h"
#include "solution/triangle.h"


using namespace std;
using namespace graphics;


void debug_patches(object_t *object);


int
main(int argc, char **argv)
{
    object_t *object;
    vertex_t vertex;
    surface_t *surface;
    Triangle *triangles, *t1, *t2;

    object = object_init();

    parse_data_file("data/patches.data", object);

    triangles = (Triangle*)malloc(sizeof(Triangle)*2);

    surface = patch_to_surface(object->vertices, object->patches->head);
    surface_to_triangles(surface, &triangles[0], &triangles[1]);

    t1 = &triangles[0];

    cout << "v1: " << t1->v1() << ", ";
    cout << "v2: " << t1->v2() << ", ";
    cout << "v3: " << t1->v3() << endl;

    return 0;
}


void
debug_patches(object_t *object)
{
    vertex_t vertex;

    for (int i = 1; i <= object->num_vertices; i++) {
        vertex = object->vertices[i];

        cout << "Vertex " << setw(3) << i << ": ";

        cout.precision(4);
        cout << "(x, y, z) = ("
             << setw(6) << vertex[1] << ", "
             << setw(6) << vertex[2] << ", "
             << setw(6) << vertex[3]
             << ')' << endl;
    }

    for (patch_t *patch = object->patches->head; patch != NULL; patch = patch->next) {
        cout << "patch number: "
            << setw(2) << patch->number << endl << flush;
        cout << "patch indices: " << endl << '\t'
            << setw(6) << patch->vertices[ 0] << ", "
            << setw(6) << patch->vertices[ 1] << ", "
            << setw(6) << patch->vertices[ 2] << ", "
            << setw(6) << patch->vertices[ 3] << endl;

        cout << '\t'
            << setw(6) << patch->vertices[ 4] << ", "
            << setw(6) << patch->vertices[ 5] << ", "
            << setw(6) << patch->vertices[ 6] << ", "
            << setw(6) << patch->vertices[ 7] << endl;

        cout << '\t'
            << setw(6) << patch->vertices[ 8] << ", "
            << setw(6) << patch->vertices[ 9] << ", "
            << setw(6) << patch->vertices[10] << ", "
            << setw(6) << patch->vertices[11] << endl;

        cout << '\t'
            << setw(6) << patch->vertices[12] << ", "
            << setw(6) << patch->vertices[13] << ", "
            << setw(6) << patch->vertices[14] << ", "
            << setw(6) << patch->vertices[15] << endl;
    }
}
