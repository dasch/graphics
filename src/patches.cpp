#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

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

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768

MyCamera<MyMathTypes>             camera;
RenderPipeline<MyMathTypes>       render_pipeline;
MyVertexProgram<MyMathTypes>      vertex_program;
MyFragmentProgram<MyMathTypes>    fragment_program;
MyTriangleRasterizer<MyMathTypes> triangle_rasterizer;
MyLineRasterizer<MyMathTypes>     line_rasterizer;

MyMathTypes::vector3_type cblack( 0.0, 0.0, 0.0 );
MyMathTypes::vector3_type cwhite( 1.0, 1.0, 1.0 );
MyMathTypes::vector3_type cred(1.0, 0.0, 0.0);
MyMathTypes::vector3_type cgreen(0.0, 1.0, 0.0);
MyMathTypes::vector3_type cblue(0.0, 0.0, 1.0);
MyMathTypes::vector3_type cyellow(255.0 / 255.0, 245.0 / 255.0, 6.0 / 255.0);

void debug_patches(object_t *object);
void draw(Triangle *triangles, unsigned int count);
void DrawLinez();
void display();


void
draw_patches()
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

    draw(triangles, 2);
}


int
main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition( 50, 50 );
    glutCreateWindow( "Blue Screen of Death" );

    glClearColor( 1, 1, 1, 0 );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glutSwapBuffers();
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glFinish();

    //--- connect hardware
    render_pipeline.load_vertex_program(vertex_program);
    render_pipeline.load_fragment_program(fragment_program);

    //--- allocate memory
    render_pipeline.set_resolution(WIN_WIDTH, WIN_HEIGHT);

    //--- set up graphics state
    render_pipeline.state().ambient_intensity() = 0.5;

    //--- init camera
    camera.init( render_pipeline );

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}


void
display()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode( GL_MODELVIEW );

    MyMathTypes::real_type     infinity = -1.0;

    MyMathTypes::vector3_type  color( 0.0, 0.0, 1.0 );   // Blue Screen of Death Color

    render_pipeline.clear( infinity, color );

    draw_patches();

    render_pipeline.flush();

    glFinish();
    glutSwapBuffers();
}


void
draw(Triangle *triangles, unsigned int count)
{
    Triangle *t;

    render_pipeline.load_rasterizer(triangle_rasterizer);
    render_pipeline.load_vertex_program(vertex_program);

    MyMathTypes::vector3_type vrp(0, 0, 0);
    MyMathTypes::vector3_type vpn(0, 0, 1);
    MyMathTypes::vector3_type vup(0, 1, 0);
    MyMathTypes::vector3_type prp(0, 0, 1);

    MyMathTypes::vector2_type lower_left(-25.0, -25.0);
    MyMathTypes::vector2_type upper_right(25.0,  25.0);

    MyMathTypes::real_type    front_plane(0.0);
    MyMathTypes::real_type    back_plane(-11.0);

    MyMathTypes::vector3_type  n(0.0, 0.0, 1.0);

    camera.set_projection(vrp, vpn, vup, prp,
			  lower_left, upper_right,
			  front_plane, back_plane,
			  WIN_WIDTH, WIN_HEIGHT);

    for (int i = 0; i < count; i++) {
        t = &triangles[i];
        render_pipeline.draw_triangle(t->v1(), n, cred,
                                      t->v2(), n, cred,
                                      t->v3(), n, cred);
    }
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


void DrawLinez()
{
    MyMathTypes::vector3_type red(1.0, 0.0, 0.0);
    MyMathTypes::vector3_type green(0.0, 1.0, 0.0);

    MyMathTypes::vector3_type  p0(-30.0, -30.0, -10.0);
    MyMathTypes::vector3_type  p1( 30.0, -30.0, -10.0);
    MyMathTypes::vector3_type  p2(  0.0,  30.0, -10.0);

    MyMathTypes::vector3_type  p3(0.0, -1.0, 0.0);
    MyMathTypes::vector3_type  p4(0.0, -1.0, -10.0);

    MyMathTypes::vector3_type  p5(-50.0, 0.0, -11.0);
    MyMathTypes::vector3_type  p6( 50.0, 0.0,  -9.0);

    MyMathTypes::vector3_type  n(0.0, 0.0, 1.0);

    render_pipeline.load_rasterizer( triangle_rasterizer );
    render_pipeline.load_vertex_program( vertex_program );

    MyMathTypes::vector3_type vrp(0, 0, 0);
    MyMathTypes::vector3_type vpn(0, 0, 1);
    MyMathTypes::vector3_type vup(0, 1, 0);
    MyMathTypes::vector3_type prp(0, 0, 1);

    MyMathTypes::vector2_type lower_left( -50.0, -50.0);
    MyMathTypes::vector2_type upper_right( 50.0,  50.0);

    MyMathTypes::real_type    front_plane(0.0);
    MyMathTypes::real_type    back_plane(-11.0);

    camera.set_projection(vrp, vpn, vup, prp,
			  lower_left, upper_right,
			  front_plane, back_plane,
			  WIN_WIDTH, WIN_HEIGHT);

    std::cout << "drawing triangle" << std::endl;
    render_pipeline.draw_triangle(p0, n, cred, p1, n, cgreen, p2, n, cyellow);

    render_pipeline.load_rasterizer(line_rasterizer);

    std::cout << "drawing line along z axis" << std::endl;
    render_pipeline.draw_line(p3, cblack, p4, cblack);

    std::cout << "drawing line x axis" << std::endl;
    render_pipeline.draw_line(p5, cwhite, p6, cblack);
}
