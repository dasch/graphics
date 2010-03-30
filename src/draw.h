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
#include "solution/triangle.h"
#include "solution/bezier.h"


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

typedef MyMathTypes::vector3_type vector3_type;
typedef MyMathTypes::vector2_type vector2_type;
typedef MyMathTypes::real_type real_type;

vector3_type vrp(0, 0, 1);
vector3_type vpn(0, 0, 1);
vector3_type vup(0, 1, 0);
vector3_type prp(0, -70, 70);

vector2_type lower_left( -5.0, -5.0);
vector2_type upper_right( 5.0,  5.0);

real_type front_plane(60.0);
real_type back_plane( -10.0);

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

object_t *OBJECT;


void
draw_patches()
{
    patch_list_t *patches;
    surface_t surface;
    Bezier bezier(6);
    int i = 0;

    patches = OBJECT->patches;

    for (patch_t *patch = patches->head; patch != NULL; patch = patch->next) {
        surface = patch_to_surface(OBJECT->vertices, patch);

        bezier.init(surface);

        cout << endl << "Patch #" << i++ << ", number of triangles: " << bezier.getCount() << endl;

        draw(bezier.getTriangles(), bezier.getCount());
    }
}

void
keyboard(unsigned char key, int mouse_x, int mouse_y)
{
    switch (key) {
        case 'q':
            exit(0);
    }
}

int
run(object_t *object, int argc, char **argv)
{
    glutInit(&argc, argv);

    OBJECT = object;

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
    glutKeyboardFunc(keyboard);

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


vertex_t
get_normal(vertex_t v1,
           vertex_t v2,
           vertex_t common)
{
  vertex_t v3, v4;
  v3 = common - v1;
  v4 = common - v2;

  if (Norm(Cross(v3, v4)) == 0) {
      cout << "normal was invalid" << endl;
      return vertex_t(0, 0, 1);
  }

  return Cross(v3, v4) / Norm(Cross(v3, v4));
}


void
draw(Triangle *triangles, unsigned int count)
{
    Triangle *t;
    vertex_t v1, v2, v3, n1, n2, n3;

    render_pipeline.load_rasterizer(triangle_rasterizer);
    render_pipeline.load_vertex_program(vertex_program);

    render_pipeline.state().ambient_intensity() = real_type(0.5);
    render_pipeline.state().ambient_color() = vector3_type(0.0, 1.0, 0.0);

    render_pipeline.state().light_position() = vector3_type(366.395325, 674.291267, -143.696048);

    render_pipeline.state().diffuse_color() = vector3_type(1.0, 1.0, 1.0);
    render_pipeline.state().diffuse_intensity() = real_type(0.75);

    render_pipeline.state().specular_color() = vector3_type(1.0, 1.0, 1.0);
    render_pipeline.state().specular_intensity() = real_type(0.9);

    camera.set_projection(vrp, vpn, vup, prp,
			  lower_left, upper_right,
			  front_plane, back_plane,
			  WIN_WIDTH, WIN_HEIGHT);

    for (int i = 0; i < count; i++) {
        t = &triangles[i];

        v1 = t->v1();
        v2 = t->v2();
        v3 = t->v3();

        n1 = get_normal(v2, v3, v1);
        n2 = get_normal(v3, v1, v2);
        n3 = get_normal(v1, v2, v3);

        render_pipeline.draw_triangle(t->v1(), n1, cred,
                                      t->v2(), n2, cred,
                                      t->v3(), n3, cred);
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
