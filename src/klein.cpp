int winWidth  = 1024;
int winHeight = 768;

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <sstream>


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


#include "graphics/graphics.h"
#include "solution/linear_interpolator.h"
#include "solution/point_rasterizer.h"
#include "solution/line_rasterizer.h"
#include "solution/triangle_rasterizer.h"
#include "solution/math_types.h"
#include "solution/camera.h"
#include "solution/vertex_program.h"
#include "solution/fragment_program.h"


/*******************************************************************\
*                                                                   *
*                  G l o b a l   V a r i a b l e s                  *
*                                                                   *
\*******************************************************************/

using namespace graphics;

typedef float                       real_type;
typedef ColumnVector<real_type,2>   vector2_type;
typedef ColumnVector<real_type,3>   vector3_type;
typedef ColumnVector<real_type,4>   vector4_type;
typedef Matrix<real_type, 4, 4>     matrix4x4_type;
typedef Matrix<int, 4, 4>           imatrix4x4_type;
typedef Matrix<vector3_type, 4, 4>           vmatrix4x4_type;

MyCamera<MyMathTypes>             camera;
RenderPipeline<MyMathTypes>       render_pipeline;
MyVertexProgram<MyMathTypes>      vertex_program;
MyFragmentProgram<MyMathTypes>    fragment_program;

LinearInterpolator<MyMathTypes, MyMathTypes::vector3_type> linear_interpolator;

MyPointRasterizer<MyMathTypes>    point_rasterizer;

MyLineRasterizer<MyMathTypes>     line_rasterizer;

MyTriangleRasterizer<MyMathTypes> triangle_rasterizer;

/*******************************************************************\
*                                                                   *
*                            C o l o r s                            *
*                                                                   *
\*******************************************************************/

MyMathTypes::vector3_type cblack( 0.0, 0.0, 0.0 );
MyMathTypes::vector3_type cwhite( 1.0, 1.0, 1.0 );
MyMathTypes::vector3_type cred(1.0, 0.0, 0.0);
MyMathTypes::vector3_type cgreen(0.0, 1.0, 0.0);
MyMathTypes::vector3_type cblue(0.0, 0.0, 1.0);
MyMathTypes::vector3_type cyellow(255.0 / 255.0, 245.0 / 255.0, 6.0 / 255.0);

void SetLightning()
{
  // Set up Phong light source
  // Ambient
  render_pipeline.state().ambient_intensity() = real_type(0.5);
  render_pipeline.state().ambient_color() = vector3_type(0.0, 0.0, 1.0);

  // Diffuse
  render_pipeline.state().light_position() = vector3_type(0.395325, -100.291267, 130.696048);
  render_pipeline.state().diffuse_color() = vector3_type(0.0, 1.0, 0.0);
  render_pipeline.state().diffuse_intensity() = real_type(0.75);
  // Specular
  render_pipeline.state().specular_color() = vector3_type(1.0, 1.0, 1.0);
  render_pipeline.state().specular_intensity() = real_type(0.9);
}
void SetCamera_5() {
  vector3_type vrp(0, 0, 1);
  vector3_type vpn(0, 0, -1);
  vector3_type vup(0, 1, 0);
  vector3_type prp(-30, 50, 70);

  vector2_type lower_left( -11.0, -11.0);
  vector2_type upper_right( 11.0,  11.0);

  real_type    front_plane(4.5);
  real_type    back_plane( -20.0);
  // Set eye_position
  render_pipeline.state().eye_position() = vrp;
  // Init camera
  camera.set_projection(vrp, vpn, vup, prp,
			  lower_left, upper_right,
			  front_plane, back_plane,
			  winWidth, winHeight);
}
void SetCamera_4() {
  vector3_type vrp(0, 0, 1);
  vector3_type vpn(0, 0, 1);
  vector3_type vup(0, 1, 0);
  vector3_type prp(0, 0, 70);

  vector2_type lower_left( -15.0, -15.0);
  vector2_type upper_right( 15.0,  15.0);

  real_type    front_plane(30.5);
  real_type    back_plane( -10.0);
  // Set eye_position
  render_pipeline.state().eye_position() = vrp;
  // Init camera
  camera.set_projection(vrp, vpn, vup, prp,
			  lower_left, upper_right,
			  front_plane, back_plane,
			  winWidth, winHeight);
}
void SetCamera_1() {
  vector3_type vrp(0, 20, 10);
  vector3_type vpn(0, 2, -1);
  vpn /= Norm(vpn);
  vector3_type vup(0, 1, 0);
  vector3_type prp(0, 40, 40);

  vector2_type lower_left( -10.0, -10.0);
  vector2_type upper_right( 10.0,  10.0);

  real_type    front_plane(0.0);
  real_type    back_plane( -100.0);
  // Set eye_position
  render_pipeline.state().eye_position() = vrp + prp;
  // Init camera
  camera.set_projection(vrp, vpn, vup, prp,
      lower_left, upper_right,
      front_plane, back_plane,
      winWidth, winHeight);
}
void SetCamera_2() {
  vector3_type vrp(0.5, 12.0, 10.0);
  vector3_type vpn(cos(90.0 * M_PI / 180.0), 5.0, sin(10.0 * M_PI / 180.0));
  vpn /= Norm(vpn);
  vector3_type vup(0.0, 0.0, 1.0);
  vector3_type prp(2.0, 10.0, 20.0);

  vector2_type lower_left( -8.0, -8.0);
  vector2_type upper_right( 8.0,  8.0);

//  real_type    front_plane(-12.5);
  real_type    front_plane(12.5);
  real_type    back_plane( -50.0);
  // Set eye_position
  render_pipeline.state().eye_position() = vrp + prp;
  // Init camera
  camera.set_projection(vrp, vpn, vup, prp,
      lower_left, upper_right,
      front_plane, back_plane,
      winWidth, winHeight);
}
void SetCamera_3() {
  vector3_type vrp(4.0, -3.0, -20.0);
  vector3_type vpn(0.5, 0.5, -1.0);
  vpn /= Norm(vpn);
  vector3_type vup(1.3, 0.1, -1.4);
  vector3_type prp(-1.3, -2.0, 40.0);

  vector2_type lower_left( -20.0, -20.0);
  vector2_type upper_right( 20.0,  20.0);

  real_type    front_plane(5.0);
  real_type    back_plane( -800.0);
  // Set eye_position
  render_pipeline.state().eye_position() = vrp + prp;
  // Init camera
  camera.set_projection(vrp, vpn, vup, prp,
      lower_left, upper_right,
      front_plane, back_plane,
      winWidth, winHeight);
}
// General Sampling
void GeneralSurfaces(real_type const& u_min,
    real_type const& u_max,
    real_type const& v_min,
    real_type const& v_max,
    int N,
    int M,
    void f(real_type const&,
      real_type const&,
      vector3_type*,
      vector3_type*))
{
  real_type u_current;
  real_type v_current;

  real_type delta_v = (v_max - v_min) / (M);
  real_type delta_u = (u_max - u_min) / (N);

  vector3_type p[4];
  vector3_type n[4];

  for (int v = 0; v < M; v++) {
    v_current = (v * delta_v) + v_min;
    for (int u = 0; u < N; u++) {
      u_current = (u * delta_u) + u_min;
      // Get the points
      //  p_3 --  p_2
      //   |       |
      //  p_0 --  p_1
      (*f)(u_current,           v_current,           &p[0], &n[0]);
      (*f)(u_current + delta_u, v_current,           &p[1], &n[1]);
      (*f)(u_current + delta_u, v_current + delta_v, &p[2], &n[2]);
      (*f)(u_current,           v_current + delta_v, &p[3], &n[3]);

      // Draw the 2 triangles
      render_pipeline.draw_triangle(p[0], n[0], cwhite, p[1], n[1], cwhite, p[2], n[2], cwhite);
      render_pipeline.draw_triangle(p[2], n[2], cwhite, p[3], n[3], cwhite, p[0], n[0], cwhite);
    }
  }
}
void bottom(real_type const& u,
    real_type const& v,
    vector3_type* p,
    vector3_type* n) {
  (*p) = vector3_type((2.5 + 1.5 * cos(v))*cos(u),
      (2.5 + 1.5 * cos(v))*sin(u),
      -2.5*sin(v));
  vector3_type du;
  vector3_type dv;

  // Partially derivated of top to u
  du = vector3_type(-(2.5 + 1.5 * cos(v)) * sin(u),
      (2.5 + 1.5 * cos(v)) * cos(u),
      0.0);
  // Partially derivated of top to u
  dv = vector3_type(-1.5 * sin(v) * cos(u),
      -1.5 * sin(v) * sin(u),
      -2.5 * cos(v));
  vector3_type normal = Cross(du, dv);
  (*n) = (normal / Norm(normal));
}
void handle(real_type const& u,
    real_type const& v,
    vector3_type* p,
    vector3_type* n) {
  (*p) = vector3_type((2.0 - 2.0 * cos(v) + sin(u)),
      cos(u),
      3*v);
  vector3_type du;
  vector3_type dv;

  // Partially derivated of top to u
  du = vector3_type(cos(u),
      -sin(u),
      0.0);
  // Partially derivated of top to u
  dv = vector3_type(2.0 * sin(v),
      0.0,
      3.0);
  vector3_type normal = Cross(du, dv);
  (*n) = (normal / Norm(normal));
}
void top(real_type const& u,
    real_type const& v,
    vector3_type* p,
    vector3_type* n) {
  // Return point
  (*p) = vector3_type(2.0 + (2.0 + cos(u)) * cos(v),
      sin(u),
      3.0 * M_PI + (2.0 + cos(u)) * sin(v));
  vector3_type du;
  vector3_type dv;

  // Partially derivated of top to u
  du = vector3_type(-sin(u) * cos(v),
      cos(u),
      -sin(u) * sin(v));
  // Partially derivated of top to u
  dv = vector3_type(-(2.0 + cos(u)) * sin(v),
      0.0,
      (2.0 + cos(u)) * cos(v));
  vector3_type normal = Cross(du, dv);
  (*n) = (normal / Norm(normal)) * -11;
}
void middle(real_type const& u,
    real_type const& v,
    vector3_type* p,
    vector3_type* n) {
  (*p) = vector3_type((2.5 + 1.5 * cos(v))*cos(u),
      (2.5 + 1.5 * cos(v))*sin(u),
      3*v);
  vector3_type du;
  vector3_type dv;

  // Partially derivated of top to u
  du = vector3_type(-(2.5 + 1.5 * cos(v)) * sin(u),
      (2.5 + 1.5 * cos(v)) * cos(u),
      0.0);
  // Partially derivated of top to v
  dv = vector3_type(-1.5 * sin(v) * cos(u),
      -1.5 * sin(v) * sin(u),
      3.0);
  vector3_type normal = Cross(du, dv);
  (*n) = (normal / Norm(normal)) * -1;
}
void draw_klein() {
//  SetCamera_1();
//  SetCamera_2();
//  SetCamera_3();
//  SetCamera_4();
//  SetCamera_5();
  SetLightning();

  real_type u_min = 0;
  real_type u_max = 2 * M_PI;
  real_type v_min = 0;
  real_type v_max = M_PI;
  GeneralSurfaces(u_min, u_max, v_min, v_max, 80, 80, &bottom);
  GeneralSurfaces(u_min, u_max, v_min, v_max, 80, 80, &handle);
  GeneralSurfaces(u_min, u_max, v_min, v_max, 80, 80, &top);
  GeneralSurfaces(u_min, u_max, v_min, v_max, 80, 80, &middle);
}
void reshape( int width, int height )
{
    winWidth = width;
    winHeight = height;
    glViewport( 0, 0, winWidth, winHeight );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glutPostRedisplay();
}

void display()
{
  // This is where things happen! - all of your drawings should go here!

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glMatrixMode( GL_MODELVIEW );
  //////////////////////////////////////////////////////////////////

  // >> TODO USE YOUR SOFTWARE RENDERPIPEINE TO DRAW <<

  MyMathTypes::real_type     infinity = -1.0;

  MyMathTypes::vector3_type  color( 0.0, 0.0, 1.0 );   // Blue Screen of Death Color

  render_pipeline.clear( infinity, color );

  // Called function here
  draw_klein();

  render_pipeline.flush();

  glFinish();
  bool AnyErrors = false;
  GLenum ErrorCode = GL_NO_ERROR;
  while ((ErrorCode = glGetError()) != GL_NO_ERROR) {
    std::cout << "display(): " << gluErrorString(ErrorCode) << std::endl;
    AnyErrors = true;
  }
  if (AnyErrors) {
    std::ostringstream errormessage;
    errormessage << "display(): " << "OpenGL Rendering Failure" << std::ends;
    throw std::runtime_error(errormessage.str());
  }
  glutSwapBuffers();
}

int main( int argc, char **argv )
{
    try {
      glutInit( &argc, argv );

      glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
      glutInitWindowSize( winWidth, winHeight );
      glutInitWindowPosition( 50, 50 );
      glutCreateWindow( "General Surfaces" );

      glClearColor( 1, 1, 1, 0 );
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      glutSwapBuffers();
      glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      glFinish();

      /////////////////////////////////////////////////////////////////

      // >> TODO INITIALIZE YOUR RENDERPIPELINE <<

      //--- connect hardware
      render_pipeline.load_vertex_program( vertex_program );
      render_pipeline.load_fragment_program( fragment_program );
      render_pipeline.load_rasterizer( triangle_rasterizer );

      //--- allocate memory
      render_pipeline.set_resolution(winWidth, winHeight );

      //--- set up graphics state
      render_pipeline.state().ambient_intensity() = 0.5;

      //--- init camera
      camera.init( render_pipeline );
      SetCamera_1();
      char c = argv[1][0];
      std::cout << c << std::endl;
      switch (c) {
        case '1':
          SetCamera_1();
          break;
        case '2':
          SetCamera_2();
          break;
        case '3':
          SetCamera_3();
          break;
        case '4':
          SetCamera_4();
          break;
        case '5':
          SetCamera_5();
          break;
        default:
          SetCamera_1();
      }

      glutDisplayFunc(display);
      glutReshapeFunc(reshape);

      glutMainLoop();
    }
    catch (std::exception const& Exception) {
      std::cout << Exception.what() << std::endl;
    }

    return 0;
}
