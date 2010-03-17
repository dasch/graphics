//
// Graphics Framework.
// Copyright (C) 2008 Department of Computer Science, University of Copenhagen
//

/*******************************************************************\
*                                                                   *
*           D r a w   L i n e s   o r   T r i a n g l e s           *
*                                                                   *
\*******************************************************************/

#define DRAWGRID       1
#define DRAWPOINTS     1
#define DEBUGPOINTS    1
#define DRAWLINES      1
#define DRAWHOUSE      1
#define DEBUGLINES     1
#define DRAWTRIANGLES  1
#define DEBUGTRIANGLES 1


/*******************************************************************\
*                                                                   *
*               L i n e s     o r   T r i a n g l e s               *
*                                                                   *
\*******************************************************************/

static char figure      = '0';

static int  GridVisible = 0;
static int  UnitLength  = 1;
static int  XSpacing    = 1;
static int  YSpacing    = 1;
static int  v           = 0;
static int  l           = 0;


/*******************************************************************\
*                                                                   *
*                       W i n d o w   S i z e                       *
*                                                                   *
\*******************************************************************/

int winWidth  = 1024;
int winHeight = 768;


/*******************************************************************\
*                                                                   *
*                  B i l l   G a t e s '   S h i t                  *
*                                                                   *
\*******************************************************************/

#ifdef WIN32
#  define WIN32_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#  undef WIN32_LEAN_AND_MEAN
#  undef NOMINMAX
#endif

/*******************************************************************\
*                                                                   *
*                     I n c l u d e   F i l e s                     *
*                                                                   *
\*******************************************************************/

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <sstream>


//For MAC OS X
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

/*******************************************************************\
*                                                                   *
*                  G l o b a l   V a r i a b l e s                  *
*                                                                   *
\*******************************************************************/

using namespace graphics;

MyCamera<MyMathTypes>             camera;
RenderPipeline<MyMathTypes>       render_pipeline;
MyVertexProgram<MyMathTypes>      vertex_program;
MyFragmentProgram<MyMathTypes>    fragment_program;

LinearInterpolator<MyMathTypes, MyMathTypes::vector3_type> linear_interpolator;
//MyLineRasterizer<MyMathTypes, linear_interpolator>     line_rasterizer;

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


/*******************************************************************\
*                                                                   *
*                        D r a w G r i d ( )                        *
*                                                                   *
\*******************************************************************/

void DrawGrid()
{
    MyMathTypes::vector3_type cblack(0.0, 0.0, 0.0);

    render_pipeline.unit_length(UnitLength);
    render_pipeline.draw_grid(XSpacing, YSpacing, cblack);
    render_pipeline.unit_length(1);
}

void DrawFinalTriangle()
{
  std::cout << "Test triangle for final assignment" << std::endl;
  
  render_pipeline.load_rasterizer( triangle_rasterizer );
  render_pipeline.load_vertex_program( vertex_program );

  MyMathTypes::vector3_type vrp(0.0, 0.0, 125.0);
  MyMathTypes::vector3_type vpn(0.0, 0.0, 1.0);
  MyMathTypes::vector3_type vup(0.0, 1.0, 0.0);
  MyMathTypes::vector3_type prp(0.0, 0.0, 50.0);

  MyMathTypes::vector2_type lower_left( -25.0, -25.0);
  MyMathTypes::vector2_type upper_right( 25.0,  25.0);

  MyMathTypes::real_type    front_plane(10.0);
  MyMathTypes::real_type    back_plane(-800.0);

  camera.set_projection(vrp, vpn, vup, prp,
			  lower_left, upper_right,
			  front_plane, back_plane,
			  winWidth, winHeight);

  MyMathTypes::vector3_type  v1( -33.978017, -34.985076, 50.214926 );
  MyMathTypes::vector3_type  v2( 84.192943, -13.784394, -50.214926 );
  MyMathTypes::vector3_type  v3( -16.236910, 83.754546, -50.214926 );

  MyMathTypes::vector3_type  n1( 0.0, 0.0, 1.0 );
  MyMathTypes::vector3_type  n2( 0.0, 0.0, 1.0 );
  MyMathTypes::vector3_type  n3( 0.0, 0.0, 1.0 );

  MyMathTypes::vector3_type  c1( 1.0, 0.0, 0.0 );
  MyMathTypes::vector3_type  c2( 1.0, 0.0, 0.0 );
  MyMathTypes::vector3_type  c3( 1.0, 0.0, 0.0 );

  render_pipeline.draw_triangle(v1,  n1, c1,  v2,  n2, c2,  v3,  n3, c3);
}


/*******************************************************************\
*                                                                   *
*                        D r a w L i n e z ( )                      *
*                                                                   *
\*******************************************************************/

void DrawLinez()
{
    MyMathTypes::vector3_type red(1.0, 0.0, 0.0);
    MyMathTypes::vector3_type green(0.0, 1.0, 0.0);

    MyMathTypes::vector3_type  p0(-30.0, -30.0, -10.0);
    MyMathTypes::vector3_type  p1( 30.0, -30.0, -10.0);
    MyMathTypes::vector3_type  p2(  0.0,  30.0, -10.0);

    MyMathTypes::vector3_type  p3(0.0, 0.0, 0.0);
    MyMathTypes::vector3_type  p4(0.0, 0.0, -10.0);

    MyMathTypes::vector3_type  p5(-50.0, 0.0, 0.0);
    MyMathTypes::vector3_type  p6(50.0, 0.0, 0.0);

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
			  winWidth, winHeight);

    std::cout << "drawing triangle" << std::endl;
    render_pipeline.draw_triangle(p0, n, red, p1, n, red, p2, n, red);

    render_pipeline.load_rasterizer(line_rasterizer);

    std::cout << "drawing line along z axis" << std::endl;
    render_pipeline.draw_line(p3, green, p4, green);

    std::cout << "drawing line x axis" << std::endl;
    render_pipeline.draw_line(p5, green, p6, green);
}


/*******************************************************************\
*                                                                   *
*                       D r a w P o i n t  ( )                      *
*                                                                   *
\*******************************************************************/

void DrawPoint()
{
    render_pipeline.load_rasterizer(point_rasterizer);

    // Do the fun stuff here

    int x_start = 150;
    int x_width = 400;
    int x_stop  = x_start + x_width;

    int y_start = 200;
    int y_width = 400;
    int y_stop  = y_start + y_width;

#ifdef KENNY_ZBUFFER
    MyMathTypes::real_type depth =  0.5;
#else
    MyMathTypes::real_type depth = -0.5;
#endif

    for (int x = x_start; x < x_stop; ++x) {
        for (int y = y_start; y < y_stop; ++y) {
            MyMathTypes::vector3_type point(x, y, depth);
            render_pipeline.draw_point(point, cyellow);
        }
    }

    x_start = 250;
    x_width = 500;
    x_stop  = x_start + x_width;

    y_start = 100;
    y_width = 400;
    y_stop  = y_start + y_width;

#ifdef KENNY_ZBUFFER
    depth =  0.75;
#else
    depth = -0.75;
#endif

    for (int x = x_start; x < x_stop; ++x) {
        for (int y = y_start; y < y_stop; ++y) {
            MyMathTypes::vector3_type point(x, y, depth);
            render_pipeline.draw_point(point, cred);
        }
    }
}


/*******************************************************************\
*                                                                   *
*                      D e b u g P o i n t  ( )                     *
*                                                                   *
\*******************************************************************/

void DebugPoint()
{
    UnitLength = 50;
    XSpacing   = 1;
    YSpacing   = 1;

    render_pipeline.load_rasterizer(point_rasterizer);
    render_pipeline.DebugOn();
    render_pipeline.unit_length(UnitLength);

    // Do the fun stuff here

#if 0
    int x_start = 7;
    int x_width = 8;
    int x_stop  = x_start + x_width;

    int y_start = 5;
    int y_width = 6;
    int y_stop  = y_start + y_width;
#else
    int x_start = 150 / UnitLength;
    int x_width = 400 / UnitLength;
    int x_stop  = x_start + x_width;

    int y_start = 200 / UnitLength;
    int y_width = 400 / UnitLength;
    int y_stop  = y_start + y_width;
#endif

#ifdef KENNY_ZBUFFER
    int depth =  0.5;
#else
    int depth = -0.5;
#endif

    for (int x = x_start; x < x_stop; ++x) {
        for (int y = y_start; y < y_stop; ++y) {
            MyMathTypes::vector3_type point(x, y, depth);
            render_pipeline.draw_point(point, cyellow);
        }
    }

    x_start = 250 / UnitLength;
    x_width = 500 / UnitLength;
    x_stop  = x_start + x_width;

    y_start = 100 / UnitLength;
    y_width = 400 / UnitLength;
    y_stop  = y_start + y_width;

#ifdef KENNY_ZBUFFER
    depth =  0.75;
#else
    depth = -0.75;
#endif

    for (int x = x_start; x < x_stop; ++x) {
        for (int y = y_start; y < y_stop; ++y) {
            MyMathTypes::vector3_type point(x, y, depth);
            render_pipeline.draw_point(point, cred);
        }
    }

    render_pipeline.draw_grid(XSpacing, YSpacing, cblack);
    render_pipeline.DebugOff();
    render_pipeline.unit_length(1);
}


/*******************************************************************\
*                                                                   *
*                         H o u s e D a t a                         *
*                                                                   *
\*******************************************************************/

// Front Wall
MyMathTypes::real_type const front_depth = 54.0;
MyMathTypes::vector3_type FrontWall[] = {
    MyMathTypes::vector3_type( 0.0,  0.0, front_depth),
    MyMathTypes::vector3_type(16.0,  0.0, front_depth),
    MyMathTypes::vector3_type(16.0, 10.0, front_depth),
    MyMathTypes::vector3_type( 8.0, 16.0, front_depth),
    MyMathTypes::vector3_type( 0.0, 10.0, front_depth)
};
int const NFrontWallVertices = sizeof(FrontWall) / sizeof(MyMathTypes::vector3_type);

// Back Wall
MyMathTypes::real_type const back_depth = 30.0;
//MyMathTypes::real_type const back_depth = -100.0;
MyMathTypes::vector3_type BackWall[] = {
    MyMathTypes::vector3_type( 0.0,  0.0, back_depth),
    MyMathTypes::vector3_type(16.0,  0.0, back_depth),
    MyMathTypes::vector3_type(16.0, 10.0, back_depth),
    MyMathTypes::vector3_type( 8.0, 16.0, back_depth),
    MyMathTypes::vector3_type( 0.0, 10.0, back_depth)
};
int const NBackWallVertices = sizeof(BackWall) / sizeof(MyMathTypes::vector3_type);


/*******************************************************************\
*                                                                   *
*                       D r a w H o u s e ( )                       *
*                                                                   *
\*******************************************************************/

void DrawHouse()
{
    // Test program for the transformations and projections

    //std::cout << "Test program for the transformations and projections" << std::endl;

    // Draw the front wall
    for (int i = 1; i < NFrontWallVertices; ++i) {
	render_pipeline.draw_line( FrontWall[i-1], cwhite,
				   FrontWall[i], cwhite );
    }
    render_pipeline.draw_line( FrontWall[NFrontWallVertices-1], cwhite, 
			       FrontWall[0], cwhite );

    // Draw the back wall
    for (int i = 1; i < NBackWallVertices; ++i) {
	render_pipeline.draw_line(BackWall[i-1], cred, 
				  BackWall[i], cred );
    }
    render_pipeline.draw_line( BackWall[NBackWallVertices-1], cred, 
			       BackWall[0], cred );

    // Draw the side walls
    for (int i = 0; i < NFrontWallVertices; ++i) {
	render_pipeline.draw_line( FrontWall[i], cgreen, 
				   BackWall[i], cgreen );
    }

    // Reset the framebuffer resolution to the original values
    //render_pipeline.set_resolution(::winWidth, ::winHeight);
    // TODO: Uncomment this:
    //camera.reset();
}


/*******************************************************************\
*                                                                   *
*                  F o l e y _ F i g _ 6 _ 2 7 ( )                  *
*                                                                   *
\*******************************************************************/

void Foley_Fig_6_27()
{
    std::cout << "Draw the House in Foley, Fig 6.27." << std::endl;

    render_pipeline.load_rasterizer( line_rasterizer );
    render_pipeline.load_vertex_program( vertex_program );

    MyMathTypes::vector3_type vrp(0, 0, 0);
    MyMathTypes::vector3_type vpn(0, 0, 1);
    MyMathTypes::vector3_type vup(0, 1, 0);
    MyMathTypes::vector3_type prp(8, 6, 84);

    MyMathTypes::vector2_type lower_left( -50.0, -50.0);
    MyMathTypes::vector2_type upper_right( 50.0,  50.0);

    MyMathTypes::real_type    front_plane(60.0);
    MyMathTypes::real_type    back_plane( 25.0);

    camera.set_projection(vrp, vpn, vup, prp,
			  lower_left, upper_right,
			  front_plane, back_plane,
			  winWidth, winHeight);

    DrawHouse();
}


/*******************************************************************\
*                                                                   *
*                  F o l e y _ F i g _ 6 _ 2 8 ( )                  *
*                                                                   *
\*******************************************************************/

void Foley_Fig_6_28()
{
    std::cout << "Draw the House in Foley, Fig 6.28." << std::endl;

    render_pipeline.load_rasterizer( line_rasterizer );
    render_pipeline.load_vertex_program( vertex_program );

    MyMathTypes::vector3_type vrp(0, 0, 54);
    MyMathTypes::vector3_type vpn(0, 0, 1);
    MyMathTypes::vector3_type vup(0, 1, 0);
    MyMathTypes::vector3_type prp(8, 6, 30);

    MyMathTypes::vector2_type lower_left( -1.0, -1.0);
    MyMathTypes::vector2_type upper_right(17.0, 17.0);

    MyMathTypes::real_type    front_plane(  1.0);
    MyMathTypes::real_type    back_plane( -35.0);

    camera.set_projection(vrp, vpn, vup, prp,
			  lower_left, upper_right,
			  front_plane, back_plane,
			  winWidth, winHeight);

    DrawHouse();
}


/*******************************************************************\
*                                                                   *
*                  F o l e y _ F i g _ 6 _ 3 1 ( )                  *
*                                                                   *
\*******************************************************************/

void Foley_Fig_6_31()
{
    std::cout << "Draw the House in Foley, Fig 6.31." << std::endl;

    render_pipeline.load_rasterizer( line_rasterizer );
    render_pipeline.load_vertex_program( vertex_program );

    MyMathTypes::vector3_type vrp(16, 0, 54);
    MyMathTypes::vector3_type vpn(0, 0, 1);
    MyMathTypes::vector3_type vup(0, 1, 0);
    MyMathTypes::vector3_type prp(20, 25, 20);

    MyMathTypes::vector2_type lower_left( -20.0, -5.0);
    MyMathTypes::vector2_type upper_right( 20.0,  35.0);

    MyMathTypes::real_type    front_plane(  1.0);
    MyMathTypes::real_type    back_plane( -35.0);

    camera.set_projection(vrp, vpn, vup, prp,
			  lower_left, upper_right,
			  front_plane, back_plane,
			  winWidth, winHeight);

    DrawHouse();
}


/*******************************************************************\
*                                                                   *
*                  F o l e y _ F i g _ 6 _ 2 2 ( )                  *
*                                                                   *
\*******************************************************************/

void Foley_Fig_6_22()
{
    std::cout << "Draw the House in Foley, Fig 6.22." << std::endl;

    render_pipeline.load_rasterizer( line_rasterizer );
    render_pipeline.load_vertex_program( vertex_program );

    MyMathTypes::vector3_type vrp(16, 0, 54);
    MyMathTypes::vector3_type vpn(1, 0, 1);
    MyMathTypes::vector3_type vup(0, 1, 0);
    MyMathTypes::vector3_type prp(0, 25, 20 * sqrt(2.0));

    MyMathTypes::vector2_type lower_left( -20.0, -5.0);
    MyMathTypes::vector2_type upper_right( 20.0,  35.0);

    MyMathTypes::real_type    front_plane(  1.0);
    MyMathTypes::real_type    back_plane( -35.0);

    camera.set_projection(vrp, vpn, vup, prp,
			  lower_left, upper_right,
			  front_plane, back_plane,
			  winWidth, winHeight);

    DrawHouse();
}


/*******************************************************************\
*                                                                   *
*                  F o l e y _ F i g _ 6 _ 3 4 ( )                  *
*                                                                   *
\*******************************************************************/

void Foley_Fig_6_34()
{
    std::cout << "Draw the House in Foley, Fig 6.34." << std::endl;

    render_pipeline.load_rasterizer( line_rasterizer );
    render_pipeline.load_vertex_program( vertex_program );

    MyMathTypes::vector3_type vrp(16, 0, 54);
    MyMathTypes::vector3_type vpn(1, 0, 1);
    MyMathTypes::vector3_type vup(-sin(10.0 * M_PI / 180.0),
				   cos(10.0 * M_PI / 180.0),
				   sin(10.0 * M_PI / 180.0));
    //std::cout << "vup = [" << vup << "]^T" << std::endl;
    MyMathTypes::vector3_type prp(0, 25, 20 * sqrt(2.0));

    MyMathTypes::vector2_type lower_left( -20.0, -5.0);
    MyMathTypes::vector2_type upper_right( 20.0,  35.0);

    MyMathTypes::real_type    front_plane(  1.0);
    MyMathTypes::real_type    back_plane( -35.0);

    camera.set_projection(vrp, vpn, vup, prp,
			  lower_left, upper_right,
			  front_plane, back_plane,
			  winWidth, winHeight);

    DrawHouse();
}


/*******************************************************************\
*                                                                   *
*                       D r a w L i n e s ( )                       *
*                                                                   *
\*******************************************************************/

void DrawLines()
{
    // TestProgram: It tests drawing of lines.
    MyMathTypes::vector3_type  l0(  100.0, 100.0, 0.0 );
    MyMathTypes::vector3_type  l1(  150.0, 100.0, 0.0 );
    MyMathTypes::vector3_type  l2(  100.0, 150.0, 0.0 );
    MyMathTypes::vector3_type  l3(   50.0, 100.0, 0.0 );
    MyMathTypes::vector3_type  l4(  100.0,  50.0, 0.0 );
    MyMathTypes::vector3_type  l5(  200.0, 100.0, 0.0 );
    MyMathTypes::vector3_type  l6(  100.0, 200.0, 0.0 );

    render_pipeline.load_rasterizer( line_rasterizer );

    render_pipeline.draw_line( l0, cwhite, l1, cwhite );
    render_pipeline.draw_line( l0, cwhite, l2, cwhite );
    render_pipeline.draw_line( l0, cwhite, l3, cwhite );
    render_pipeline.draw_line( l0, cwhite, l4, cwhite );

    render_pipeline.draw_line( l1, cwhite, l2, cwhite );
    render_pipeline.draw_line( l2, cwhite, l3, cwhite );
    render_pipeline.draw_line( l3, cwhite, l4, cwhite );
    render_pipeline.draw_line( l4, cwhite, l1, cwhite );


    // Draw a circle
    double Nedges =  50;
    double Radius = 300;

    double DeltaAngle = 2.0 * M_PI / Nedges;
    double AngleStop  = 2.0 * M_PI;
    MyMathTypes::vector3_type Center(winWidth / 2, winHeight / 2, 0);
    MyMathTypes::vector3_type Pnew;
    MyMathTypes::vector3_type Pold(Center[1] + Radius, Center[2], 0.0);
    MyMathTypes::vector3_type Pstart = Pold;

    for (double Angle = DeltaAngle; Angle < AngleStop; Angle += DeltaAngle) {
        // render_pipeline.draw_line(Center, cwhite, Pold, cwhite);
        render_pipeline.draw_line(Center, cblack, Pold, cwhite);
        Pnew[1] = Center[1] + Radius * cos(Angle);
        Pnew[2] = Center[2] + Radius * sin(Angle);
        Pnew[3] = 0.0;
        render_pipeline.draw_line(Pold, cwhite, Pnew, cwhite);
        // render_pipeline.draw_line(Pold, cyellow, Pnew, cyellow);
        Pold = Pnew;
    }
    //std::cout << "Pstart = [" << Pstart << "], Pnew = [" << Pnew << "]" << std::endl;
    // render_pipeline.draw_line(Center, cwhite, Pold, cwhite);
    render_pipeline.draw_line(Center, cblack, Pold, cwhite);
    render_pipeline.draw_line(Pold, cwhite, Pstart, cwhite);
    // render_pipeline.draw_line(Pold, cyellow, Pstart, cyellow);
}


/*******************************************************************\
*                                                                   *
*                   L o c a l   L i n e   D a t a                   *
*                                                                   *
\*******************************************************************/

#if 1
MyMathTypes::vector3_type LineStop[] = {
    MyMathTypes::vector3_type(18.0,  7.0, 0.0),
//
    MyMathTypes::vector3_type(18.0,  7.0, 0.0),
    MyMathTypes::vector3_type(18.0,  8.0, 0.0),
    MyMathTypes::vector3_type(18.0,  9.0, 0.0),
    MyMathTypes::vector3_type(18.0, 10.0, 0.0),
    MyMathTypes::vector3_type(18.0, 11.0, 0.0),
    MyMathTypes::vector3_type(18.0, 12.0, 0.0),
    MyMathTypes::vector3_type(18.0, 13.0, 0.0),
//
    MyMathTypes::vector3_type(17.0, 13.0, 0.0),
    MyMathTypes::vector3_type(16.0, 13.0, 0.0),
    MyMathTypes::vector3_type(15.0, 13.0, 0.0),
    MyMathTypes::vector3_type(14.0, 13.0, 0.0),
    MyMathTypes::vector3_type(13.0, 13.0, 0.0),
    MyMathTypes::vector3_type(12.0, 13.0, 0.0),
    MyMathTypes::vector3_type(11.0, 13.0, 0.0),
    MyMathTypes::vector3_type(10.0, 13.0, 0.0),
//
    MyMathTypes::vector3_type( 9.0, 13.0, 0.0),
    MyMathTypes::vector3_type( 8.0, 13.0, 0.0),
    MyMathTypes::vector3_type( 7.0, 13.0, 0.0),
    MyMathTypes::vector3_type( 6.0, 13.0, 0.0),
    MyMathTypes::vector3_type( 5.0, 13.0, 0.0),
    MyMathTypes::vector3_type( 4.0, 13.0, 0.0),
    MyMathTypes::vector3_type( 3.0, 13.0, 0.0),
    MyMathTypes::vector3_type( 2.0, 13.0, 0.0),
//
    MyMathTypes::vector3_type( 2.0, 12.0, 0.0),
    MyMathTypes::vector3_type( 2.0, 11.0, 0.0),
    MyMathTypes::vector3_type( 2.0, 10.0, 0.0),
    MyMathTypes::vector3_type( 2.0,  9.0, 0.0),
    MyMathTypes::vector3_type( 2.0,  8.0, 0.0),
    MyMathTypes::vector3_type( 2.0,  7.0, 0.0),
    MyMathTypes::vector3_type( 2.0,  6.0, 0.0),
    MyMathTypes::vector3_type( 2.0,  5.0, 0.0),
    MyMathTypes::vector3_type( 2.0,  4.0, 0.0),
    MyMathTypes::vector3_type( 2.0,  3.0, 0.0),
    MyMathTypes::vector3_type( 2.0,  2.0, 0.0),
//
    MyMathTypes::vector3_type( 3.0,  2.0, 0.0),
    MyMathTypes::vector3_type( 4.0,  2.0, 0.0),
    MyMathTypes::vector3_type( 5.0,  2.0, 0.0),
    MyMathTypes::vector3_type( 6.0,  2.0, 0.0),
    MyMathTypes::vector3_type( 7.0,  2.0, 0.0),
    MyMathTypes::vector3_type( 8.0,  2.0, 0.0),
    MyMathTypes::vector3_type( 9.0,  2.0, 0.0),
    MyMathTypes::vector3_type(10.0,  2.0, 0.0),
    MyMathTypes::vector3_type(11.0,  2.0, 0.0),
    MyMathTypes::vector3_type(12.0,  2.0, 0.0),
    MyMathTypes::vector3_type(13.0,  2.0, 0.0),
    MyMathTypes::vector3_type(14.0,  2.0, 0.0),
    MyMathTypes::vector3_type(15.0,  2.0, 0.0),
    MyMathTypes::vector3_type(16.0,  2.0, 0.0),
    MyMathTypes::vector3_type(17.0,  2.0, 0.0),
    MyMathTypes::vector3_type(18.0,  2.0, 0.0),
//
    MyMathTypes::vector3_type(18.0,  3.0, 0.0),
    MyMathTypes::vector3_type(18.0,  4.0, 0.0),
    MyMathTypes::vector3_type(18.0,  5.0, 0.0),
    MyMathTypes::vector3_type(18.0,  6.0, 0.0)
};

#endif

int lmax = sizeof(LineStop) / sizeof(MyMathTypes::vector3_type);


/*******************************************************************\
*                                                                   *
*                      D e b u g L i n e s ( )                      *
*                                                                   *
\*******************************************************************/

void DebugLines()
{
    UnitLength = 50;
    XSpacing   = 1;
    YSpacing   = 1;

    render_pipeline.load_rasterizer(line_rasterizer);

    render_pipeline.DebugOn();
    render_pipeline.unit_length(UnitLength);

    MyMathTypes::vector3_type LineStart(10, 7, 0);

    // The variable l is global, and don't worry about it - display() updates it!

//    render_pipeline.draw_line(LineStart, cyellow, LineStop[l], cyellow);
    render_pipeline.draw_line(LineStart, cblack, LineStop[l], cwhite);

    render_pipeline.draw_grid(XSpacing, YSpacing, cblack);
    render_pipeline.draw_debugline(LineStart, LineStop[l], cwhite);
    render_pipeline.DebugOff();
    render_pipeline.unit_length(1);
}


/*******************************************************************\
*                                                                   *
*                   D r a w T r i a n g l e s ( )                   *
*                                                                   *
\*******************************************************************/

//#define NEWTRIANGLES

void DrawTriangles()
{
    // TestProgram: It tests drawing of triangles.

    render_pipeline.load_rasterizer( triangle_rasterizer );

#ifdef NEWTRIANGLES
    // The new test which should show better that the trianles work.

    // The Center of the window is (400, 400)

    // Lower triangle
    MyMathTypes::vector3_type  v1( 400.0, 100.0, 0.0 );
    MyMathTypes::vector3_type  v2( 700.0, 100.0, 0.0 );
    MyMathTypes::vector3_type  v3( 550.0, 400.0, 0.0 );

    MyMathTypes::vector3_type  n1( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  n2( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  n3( 0.0, 0.0, 1.0 );

    MyMathTypes::vector3_type  c1( 1.0, 0.0, 0.0 );
    MyMathTypes::vector3_type  c2( 1.0, 0.0, 0.0 );
    MyMathTypes::vector3_type  c3( 1.0, 0.0, 0.0 );

    render_pipeline.draw_triangle(v1,  n1, c1,  v2,  n2, c2,  v3,  n3, c3);

    // Upper triangle
    MyMathTypes::vector3_type  v4( 550.0, 400.0, 0.0 );
    MyMathTypes::vector3_type  v5( 700.0, 700.0, 0.0 );
    MyMathTypes::vector3_type  v6( 400.0, 700.0, 0.0 );

    MyMathTypes::vector3_type  n4( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  n5( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  n6( 0.0, 0.0, 1.0 );

    MyMathTypes::vector3_type  c4( 0.0, 1.0, 0.0 );
    MyMathTypes::vector3_type  c5( 0.0, 1.0, 0.0 );
    MyMathTypes::vector3_type  c6( 0.0, 1.0, 0.0 );

    render_pipeline.draw_triangle(v4,  n4, c4,  v5,  n5, c5,  v6,  n6, c6);

    // Left triangle
    MyMathTypes::vector3_type  v7( 400.0, 400.0, 0.0 );
    MyMathTypes::vector3_type  v8( 100.0, 700.0, 0.0 );
    MyMathTypes::vector3_type  v9( 400.0, 100.0, 0.0 );

    MyMathTypes::vector3_type  n7( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  n8( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  n9( 0.0, 0.0, 1.0 );

    MyMathTypes::vector3_type  c7( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  c8( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  c9( 0.0, 0.0, 1.0 );

    render_pipeline.draw_triangle(v7,  n7, c7,  v8,  n8, c8,  v9,  n9, c9);

#else

    // Old Triangles

    // Lower left triangle with a lower horizontal edge
    MyMathTypes::vector3_type  v1( 100.0, 100.0, 0.0 );
    MyMathTypes::vector3_type  v2( 400.0, 100.0, 0.0 );
    MyMathTypes::vector3_type  v3( 250.0, 300.0, 0.0 );

    MyMathTypes::vector3_type  n1( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  n2( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  n3( 0.0, 0.0, 1.0 );

    MyMathTypes::vector3_type  c1( 1.0, 0.0, 0.0 );
    MyMathTypes::vector3_type  c2( 1.0, 0.0, 0.0 );
    MyMathTypes::vector3_type  c3( 1.0, 0.0, 0.0 );

    render_pipeline.draw_triangle(  v1,  n1, cyellow,  v2,  n2, cyellow,  v3,  n3, cyellow);

    // Upper left triangle with a upper horizontal edge
    MyMathTypes::vector3_type  v4( 100.0, winHeight - v1[2], 0.0 );
    MyMathTypes::vector3_type  v5( 250.0, winHeight - v3[2], 0.0 );
    MyMathTypes::vector3_type  v6( 400.0, winHeight - v2[2], 0.0 );

    MyMathTypes::vector3_type  n4( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  n5( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  n6( 0.0, 0.0, 1.0 );

    MyMathTypes::vector3_type  c4( 1.0, 0.0, 0.0 );
    MyMathTypes::vector3_type  c5( 1.0, 0.0, 0.0 );
    MyMathTypes::vector3_type  c6( 1.0, 0.0, 0.0 );

    render_pipeline.draw_triangle(  v4,  n4, cyellow,  v5,  n5, cyellow,  v6,  n6, cyellow);

    // General triangle with the third point the the right
    MyMathTypes::vector3_type  v7( winWidth /  2 + 200.0, 100.0, 0.0 );
    MyMathTypes::vector3_type  v8( winWidth /  2 + 100.0, 400.0, 0.0 );
    MyMathTypes::vector3_type  v9( winWidth /  2 + 300.0, 250.0, 0.0 );

    MyMathTypes::vector3_type  n7( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  n8( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  n9( 0.0, 0.0, 1.0 );

    MyMathTypes::vector3_type  c7( 1.0, 0.0, 0.0 );
    MyMathTypes::vector3_type  c8( 1.0, 0.0, 0.0 );
    MyMathTypes::vector3_type  c9( 1.0, 0.0, 0.0 );

    render_pipeline.draw_triangle(  v7,  n7, cyellow,  v8,  n8, cyellow,  v9,  n9, cyellow);

    // General triangle with the third point the the left
    MyMathTypes::vector3_type  v10( winWidth /  2 + 250.0, winHeight - 100.0, 0.0 );
    MyMathTypes::vector3_type  v11( winWidth /  2 + 300.0, winHeight - 400.0, 0.0 );
    MyMathTypes::vector3_type  v12( winWidth /  2 + 100.0, winHeight - 250.0, 0.0 );

    MyMathTypes::vector3_type  n10( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  n11( 0.0, 0.0, 1.0 );
    MyMathTypes::vector3_type  n12( 0.0, 0.0, 1.0 );

    MyMathTypes::vector3_type  c10( 1.0, 0.0, 0.0 );
    MyMathTypes::vector3_type  c11( 1.0, 0.0, 0.0 );
    MyMathTypes::vector3_type  c12( 1.0, 0.0, 0.0 );

    render_pipeline.draw_triangle( v10, n10, cyellow, v11, n11, cyellow, v12, n12, cyellow);

#endif
}


/*******************************************************************\
*                                                                   *
*               L o c a l   T r i a n g l e   D a t a               *
*                                                                   *
\*******************************************************************/

#if 1
MyMathTypes::vector3_type Vertex1[] = {
    MyMathTypes::vector3_type(9.0, 1.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
//
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
//
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
//
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
//
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
//
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
//
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0)
};

MyMathTypes::vector3_type Vertex2[] = {
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
//
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
//
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
//
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
//
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
//
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
//
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0)
};

MyMathTypes::vector3_type Vertex3[] = {
    MyMathTypes::vector3_type(1.0, 1.0, 0.0),
    MyMathTypes::vector3_type(1.0, 1.0, 0.0),
    MyMathTypes::vector3_type(2.0, 1.0, 0.0),
    MyMathTypes::vector3_type(3.0, 1.0, 0.0),
    MyMathTypes::vector3_type(4.0, 1.0, 0.0),
//
    MyMathTypes::vector3_type(5.0, 1.0, 0.0),
    MyMathTypes::vector3_type(6.0, 1.0, 0.0),
    MyMathTypes::vector3_type(7.0, 1.0, 0.0),
    MyMathTypes::vector3_type(8.0, 1.0, 0.0),
    MyMathTypes::vector3_type(9.0, 2.0, 0.0),
//
    MyMathTypes::vector3_type(9.0, 3.0, 0.0),
    MyMathTypes::vector3_type(9.0, 4.0, 0.0),
    MyMathTypes::vector3_type(9.0, 5.0, 0.0),
    MyMathTypes::vector3_type(9.0, 6.0, 0.0),
    MyMathTypes::vector3_type(9.0, 7.0, 0.0),
//
    MyMathTypes::vector3_type(9.0, 8.0, 0.0),
    MyMathTypes::vector3_type(9.0, 9.0, 0.0),
    MyMathTypes::vector3_type(8.0, 9.0, 0.0),
    MyMathTypes::vector3_type(7.0, 9.0, 0.0),
    MyMathTypes::vector3_type(6.0, 9.0, 0.0),
//
    MyMathTypes::vector3_type(5.0, 9.0, 0.0),
    MyMathTypes::vector3_type(4.0, 9.0, 0.0),
    MyMathTypes::vector3_type(3.0, 9.0, 0.0),
    MyMathTypes::vector3_type(2.0, 9.0, 0.0),
    MyMathTypes::vector3_type(1.0, 9.0, 0.0),
//
    MyMathTypes::vector3_type(1.0, 8.0, 0.0),
    MyMathTypes::vector3_type(1.0, 7.0, 0.0),
    MyMathTypes::vector3_type(1.0, 6.0, 0.0),
    MyMathTypes::vector3_type(1.0, 5.0, 0.0),
    MyMathTypes::vector3_type(1.0, 4.0, 0.0),
//
    MyMathTypes::vector3_type(1.0, 3.0, 0.0),
    MyMathTypes::vector3_type(1.0, 2.0, 0.0)
};

#endif

int vmax = sizeof(Vertex3) / sizeof(MyMathTypes::vector3_type);

/*******************************************************************\
*                                                                   *
*                  D e b u g T r i a n g l e s ( )                  *
*                                                                   *
\*******************************************************************/

void DebugTriangles()
{
    MyMathTypes::vector3_type ZeroNormal(0.0, 0.0, 0.0);

    UnitLength = 50;
    XSpacing   = 1;
    YSpacing   = 1;

    render_pipeline.load_rasterizer(triangle_rasterizer);
    render_pipeline.DebugOn();
    render_pipeline.unit_length(UnitLength);

//#define ONETRIANGLE
#ifdef ONETRIANGLE
    // Only one triangle
    MyMathTypes::vector3_type V1(1, 2, 0);
    MyMathTypes::vector3_type V2(9, 2 ,0);
    MyMathTypes::vector3_type V3(1, 9 ,0);

    render_pipeline.draw_triangle(V1, ZeroNormal, cwhite,
                  V2, ZeroNormal, cwhite,
                  V3, ZeroNormal, cwhite);

    render_pipeline.draw_grid(XSpacing, YSpacing, cblack);

    render_pipeline.draw_debugline(V1, V2, cwhite);
    render_pipeline.draw_debugline(V2, V3, cwhite);
    render_pipeline.draw_debugline(V3, V1, cwhite); // was cgreen

#else
    // Many triangles

    // The variable v is global, and don't worry about it - display() updates it!

    render_pipeline.draw_triangle(Vertex1[v], ZeroNormal, cwhite,
                  Vertex2[v], ZeroNormal, cwhite,
                  Vertex3[v], ZeroNormal, cwhite);

    render_pipeline.draw_grid(XSpacing, YSpacing, cblack);

    render_pipeline.draw_debugline(Vertex1[v], Vertex2[v], cwhite);
    render_pipeline.draw_debugline(Vertex2[v], Vertex3[v], cwhite);
    render_pipeline.draw_debugline(Vertex3[v], Vertex1[v], cwhite); // was cgreen

    render_pipeline.unit_length(1);
    render_pipeline.DebugOff();
#endif
}

/*******************************************************************\
*                                                                   *
*                         r e s h a p e ( )                         *
*                                                                   *
\*******************************************************************/

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
};

/*******************************************************************\
*                                                                   *
*                           u s a g e ( )                           *
*                                                                   *
\*******************************************************************/

void usage()
{
    std::cout << std::endl << std::flush;
    std::cout << "Legal keystrokes in the Window:"  << std::endl << std::flush;
    std::cout << "==============================="  << std::endl << std::flush;
    std::cout << "\th : Help Message"               << std::endl << std::flush;
    std::cout << "\t? : Help Message"               << std::endl << std::flush;
    std::cout << std::endl << std::flush;

    std::cout << "\tc : Clear Screen"               << std::endl << std::flush;
    std::cout << "\tq : Quit"                       << std::endl << std::flush;
    std::cout << std::endl << std::flush;

    std::cout << "\tPoints:"                        << std::endl << std::flush;
    std::cout << "\t-------"                        << std::endl << std::flush;
    std::cout << "\tp : Draw Points"                << std::endl << std::flush;
    std::cout << "\tP : Debug Points"               << std::endl << std::flush;
    std::cout << std::endl << std::flush;

    std::cout << "\tLines:"                         << std::endl << std::flush;
    std::cout << "\t------"                         << std::endl << std::flush;
    std::cout << "\tl : Draw Lines"                 << std::endl << std::flush;
    std::cout << "\tL : Debug Lines - forward"      << std::endl << std::flush;
    std::cout << "\tK : Debug Lines - backward"     << std::endl << std::flush;
    std::cout << std::endl << std::flush;

    std::cout << "\tTriangles:"                     << std::endl << std::flush;
    std::cout << "\t----------"                     << std::endl << std::flush;
    std::cout << "\tt : Draw Triangles"             << std::endl << std::flush;
    std::cout << "\tT : Debug Triangles - forward"  << std::endl << std::flush;
    std::cout << "\tR : Debug Triangles - backward" << std::endl << std::flush;
    std::cout << std::endl << std::flush;

    std::cout << "Keystroke: "                      << std::flush;
}

/*******************************************************************\
*                                                                   *
*         k e y b o a r d ( u c h a r ,   i n t ,   i n t )         *
*                                                                   *
\*******************************************************************/

void keyboard(unsigned char Key, int Xmouse, int Ymouse)
{
    glutSetWindowTitle("Foundations of Computer Graphics");

    std::cout << "You typed '" << Key << "': ";
    switch (Key) {
    case 'h':
    case '?':
    usage();
    break;
    case 'q':
    case 'Q':
        // quit the program
        std::cout << "Quit" << std::endl << std::flush;
        exit(0);
        break;
    case 'c':
    case 'C':
    // clear the screen
    std::cout << "Clear Screen" << std::endl << std::flush;
    figure = 'c';
    glutPostRedisplay();
    break;
    case 'p':
    // draw points
    std::cout << "Draw Point" << std::endl << std::flush;
    figure = 'p';
    glutPostRedisplay();
    break;
    case 'P':
    // debug points
    std::cout << "Debug Point" << std::endl << std::flush;
    figure = 'P';
    glutPostRedisplay();
    break;
    case 'l':
    // draw lines
    std::cout << "Draw Lines" << std::endl << std::flush;
    figure = 'l';
    glutPostRedisplay();
    break;
    case 'L':
    // debug lines
    std::cout << "Debug Lines - forward" << std::endl << std::flush;
    ++l;
    if (l >= lmax) l = 1;
    std::cout << "l = " << l << std::endl << std::flush;
    figure = 'L';
    glutPostRedisplay();
    break;
    case 'K':
    // debug lines
    std::cout << "Debug Lines - backward" << std::endl << std::flush;
    --l;
    if (l <= 0) l = lmax - 1;
    std::cout << "l = " << l << std::endl << std::flush;
    figure = 'K';
    glutPostRedisplay();
    break;
    case 't':
    // draw triangles
    std::cout << "Draw Triangles" << std::endl << std::flush;
    figure = 't';
    glutPostRedisplay();
    break;
    case 'T':
    // debug triangles - forward
    std::cout << "Debug Triangles - forward" << std::endl << std::flush;
    ++v;
    if (v >= vmax) v = 1;
    std::cout << "v = " << v << std::endl << std::flush;
    figure = 'T';
    glutPostRedisplay();
    break;
    case 'R':
     // debug triangles - backward
    std::cout << "Debug Triangles - backward" << std::endl << std::flush;
    --v;
    if (v <= 0) v = vmax - 1;
    std::cout << "v = " << v << std::endl << std::flush;
    figure = 'T';
    glutPostRedisplay();
    break;
    case 'f':
        std::cout << "Debug House" << std::endl << std::flush;

        v++;

        figure = 'f';
        glutPostRedisplay();
        break;
    case 'u':
        std::cout << "Debug Linez" << std::endl << std::flush;

        v++;

        figure = 'u';
        glutPostRedisplay();
        break;
    case 'd':
    case 'D':
        // call the DisplayCallback as soon as possible
        std::cout << "Redisplay" << std::endl << std::flush;
        glutPostRedisplay();
        break;
    case 'g':
    case 'G':
        // toggle the grid on and off
        std::cout << "Toggle Grid";
    figure = 'g';
        GridVisible = GridVisible ? 0 : 1;
    //glutPostRedisplay();
        break;
    default:
    std::cout << "No action defined for key '" << Key << "'" << std::endl << std::flush;
    std::cout << std::endl << std::flush;
    }
    std::cout << std::endl << std::flush;
    usage();

    //glutPostRedisplay();
}


/*******************************************************************\
*                                                                   *
*                         d i s p l a y ( )                         *
*                                                                   *
\*******************************************************************/

void display()
{
    // This is where things happen! - all of your drawings should go here!

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode( GL_MODELVIEW );
    //////////////////////////////////////////////////////////////////

    // >> TODO USE YOUR SOFTWARE RENDERPIPEINE TO DRAW <<

#ifdef KENNY_ZBUFFER
    MyMathTypes::real_type     infinty  =  1.0;
#else
    MyMathTypes::real_type     infinity = -1.0;
#endif

    MyMathTypes::vector3_type  color( 0.0, 0.0, 1.0 );   // Blue Screen of Death Color

    //  camera.set_model_view( ...... );
    //  camera.set_projection( ...... );

    render_pipeline.clear( infinity, color );


/*******************************************************************\
*                                                                   *
*                        D r a w G r i d ( )                        *
*                                                                   *
\*******************************************************************/

#if DRAWGRID
    //std::cout << "GridVisible == " << GridVisible << std::endl;
    //if (GridVisible) DrawGrid();
#endif


/*******************************************************************\
*                                                                   *
*                      D r a w P o i n t s ( )                      *
*                                                                   *
\*******************************************************************/

#if DRAWPOINTS
    if (figure == 'p') {
    DrawPoint();
    }
#endif

/*******************************************************************\
*                                                                   *
*                     D e b u g P o i n t s ( )                     *
*                                                                   *
\*******************************************************************/

#if DEBUGPOINTS
    if (figure == 'P') {
    DebugPoint();
    }
#endif

/*******************************************************************\
*                                                                   *
*                      D r a w L i n e s ( )                        *
*                                                                   *
\*******************************************************************/

#if DRAWLINES
    if (figure == 'l') {
    DrawLines();
    }
#endif

    // Remember that you can load different rasterizers (line, triangle) by the call:
    // render_pipeline.load_rasterizer(new_rasterizer);
    //
    // The same is true for vertex_programs and fragment_programs

    // std::cout << "Load line_rasterizer" << std::endl;
    // render_pipeline.load_rasterizer( line_rasterizer );
    // render_pipeline.draw_line( v1, c1, v2, c2 );

    // std::cout << "Load triangle_rasterizer" << std::endl;
    // std::cout << "Draw a triangle" << std::endl;
    // render_pipeline.draw_triangle( v1, n1, c1, v2, n2, c2, v3, n3, c3);


/*******************************************************************\
*                                                                   *
*                      D e b u g L i n e s ( )                      *
*                                                                   *
\*******************************************************************/

#if DEBUGLINES
    if (figure == 'L') {
    DebugLines();
    }
    if (figure == 'K') {
    DebugLines();
    }
#endif


/*******************************************************************\
*                                                                   *
*                   D r a w T r i a n t l e s ( )                   *
*                                                                   *
\*******************************************************************/

#if DRAWTRIANGLES
    if (figure == 't') {
    DrawTriangles();
    }
#endif


    if (figure == 'u') {
        DrawLinez();
    }


#if DRAWHOUSE
    if (figure == 'f') {
        v = (v - 1) % 5 + 1;

        switch (v) {
        case 1:
            Foley_Fig_6_27();
            break;
        case 2:
            Foley_Fig_6_28();
            break;
        case 3:
            Foley_Fig_6_31();
            break;
        case 4:
            Foley_Fig_6_22();
            break;
        case 5:
            Foley_Fig_6_34();
            break;
        }
    }
#endif


/*******************************************************************\
*                                                                   *
*                  D e b u g T r i a n g l e s ( )                  *
*                                                                   *
\*******************************************************************/

#if DEBUGTRIANGLES
    if (figure == 'T') {
    DebugTriangles();
    }
    if (figure == 'R') {
    //--v;
    DebugTriangles();
    }
#endif

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
        //errormessage << "file " << __FILE__ << ": line " << __LINE__ << ':' << std::endl;
        //errormessage << "    " << typeid(*this).name() << "::draw(): " << std::endl;
        errormessage << "display(): " << "OpenGL Rendering Failure" << std::ends;

        throw std::runtime_error(errormessage.str());
    }

    glutSwapBuffers();
    //glutPostRedisplay();
}

/*******************************************************************\
*                                                                   *
*                            m a i n ( )                            *
*                                                                   *
\*******************************************************************/

int main( int argc, char **argv )
{
    try {
        glutInit( &argc, argv );

        glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_STENCIL);
        glutInitWindowSize( winWidth, winHeight );
        glutInitWindowPosition( 50, 50 );
        glutCreateWindow( "Blue Screen of Death" );

        glClearColor( 1, 1, 1, 0 );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glutSwapBuffers();
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glFinish();

        //////////////////////////////////////////////////////////////////

        // >> TODO INITIALIZE YOUR RENDERPIPELINE <<

        //--- connect hardware
        render_pipeline.load_vertex_program( vertex_program );
        render_pipeline.load_fragment_program( fragment_program );

        // Load the appropriate rasterizer when it is needed,
        // i.e. render_pipeline.load_rasterizer(line_rasterizer | triangle_rasterizer);
            // old: render_pipeline.load_rasterizer( rasterizer);

        //--- allocate memory
        render_pipeline.set_resolution(winWidth, winHeight );

        //--- set up graphics state
        render_pipeline.state().ambient_intensity() = 0.5;

        //--- init camera
        camera.init( render_pipeline );

        usage();

        //////////////////////////////////////////////////////////////////
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(keyboard);

        glutMainLoop();
    } catch (std::exception const& Exception) {
        std::cout << Exception.what() << std::endl;
    }

    return 0;
}
