#ifndef TRIANGLE_RASTERIZER_H
#define TRIABGLE_RASTERIZER_H
//
// Graphics Framework.
// Copyright (C) 2010 Department of Computer Science, University of Copenhagen
//

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include "graphics/graphics.h"
#include "edge_rasterizer.h"
#include "linear_interpolator.h"

namespace graphics
{

  template<typename math_types>
    class MyTriangleRasterizer : public Rasterizer<math_types>
  {
    public:
      typedef typename math_types::vector3_type vector3_type;
      typedef typename math_types::real_type    real_type;

    protected:

    public:
      MyTriangleRasterizer() : valid(false), Debug(false)
        {}

      virtual ~MyTriangleRasterizer()
        {}

      void init(vector3_type const& in_vertex1,
                vector3_type const& in_normal1,
                vector3_type const& in_color1,
                vector3_type const& in_world_coord1,
                vector3_type const& in_vertex2,
                vector3_type const& in_normal2,
                vector3_type const& in_color2,
                vector3_type const& in_world_coord2,
                vector3_type const& in_vertex3,
                vector3_type const& in_normal3,
                vector3_type const& in_color3,
                vector3_type const& in_world_coord3)
      {
        // Convert x and y coordinates to integers
        vertex[0] = vector3_type (static_cast<int>(round(in_vertex1[1])),
                                  static_cast<int>(round(in_vertex1[2])),
                                  in_vertex1[3]);
        vertex[1] = vector3_type (static_cast<int>(round(in_vertex2[1])),
                                  static_cast<int>(round(in_vertex2[2])),
                                  in_vertex2[3]);
        vertex[2] = vector3_type (static_cast<int>(round(in_vertex3[1])),
                                  static_cast<int>(round(in_vertex3[2])),
                                  in_vertex3[3]);

        // Save colors
        this->colors[0] = in_color1;
        this->colors[1] = in_color2;
        this->colors[2] = in_color3;

        // Save normals
        this->normals[0] = in_normal1;
        this->normals[1] = in_normal2;
        this->normals[2] = in_normal3;

        // Save world coordinates
        this->world_coords[0] = in_world_coord1;
        this->world_coords[1] = in_world_coord2;
        this->world_coords[2] = in_world_coord3;

        this->Debug = false;
        this->is_degenerate = false;
        this->initialize_triangle();
        this->valid = true;
      }

      bool DebugOn() {
        bool oldvalue = this->Debug;
        this->Debug = true;

        return oldvalue;
      }

      bool DebugOff() {
        bool oldvalue = this->Debug;
        this->Debug = false;

        return oldvalue;
      }

      bool Valid() const
      {
        return true;
      }

      bool Degenerate() const
      {
        // implement the real version
        return this->is_degenerate;
      }

      int x() const
      {
        if (!this->valid) {
          throw std::runtime_error("MyTriangleRasterizer::x():Invalid State/Not Initialized");
        }
        return this->x_current;
      }

      int y() const
      {
        if (!this->valid) {
          throw std::runtime_error("MyTriangleRasterizer::y():Invalid State/Not Initialized");
        }
        return this->y_current;
      }

      real_type depth() const
      {
        if (!this->valid) {
          throw std::runtime_error("MyTriangleRasterizer::depth():Invalid State/Not Initialized");
        }
        // implement the real version
        return this->depth_interpolator.value();
      }

      // Returns position in world coordinates
      vector3_type position() const
      {
        if (!this->valid) {
          throw std::runtime_error("MyTriangleRasterizer::position():Invalid State/Not Initialized");
        }
        return this->world_interpolator.value();
      }

      vector3_type const& normal() const
      {
        if (!this->valid) {
          throw std::runtime_error("MyTriangleRasterizer::normal():Invalid State/Not Iitialized");
        }
        // implement the real version
        return this->normal_interpolator.value();
      }

      vector3_type const& color() const
      {
        if (!this->valid) {
          throw std::runtime_error("MyTriangleRasterizer::color():Invalid State/Not Initialized");
        }
        // implement the real version
        return this->color_interpolator.value();
      }

      void print_variables() {
        std::cout << "MyTriangleRasterizer: local variables" << std::endl;
        std::cout << "=====================================" << std::endl;
        std::cout << "\tx_current:\t" << x_current << std::endl;
        std::cout << "\tx_stop:\t\t" << x_stop << std::endl;
        std::cout << "\ty_current:\t" << y_current << std::endl;
        std::cout << std::endl;
      }

      /*******************************************************************\
       *                                                                   *
       *                  m o r e _ f r a g m e n t s ( )                  *
       *                                                                   *
      \*******************************************************************/

      bool more_fragments() const {
        return this->left_edge.more_fragments() ||
               this->right_edge.more_fragments() ||
               this->x_current < this->x_stop;
      }

      /*******************************************************************\
       *                                                                   *
       *                   n e x t _ f r a g m e n t ( )                   *
       *                                                                   *
      \*******************************************************************/

      void next_fragment() {
        this->x_current++;
        // Interpolators
        this->depth_interpolator.next_value();
        this->color_interpolator.next_value();
        this->normal_interpolator.next_value();
        this->world_interpolator.next_value();

        SearchForNonEmptyScanline();
      }

    private:
      // Initialize the current triangle for rasterization
      void initialize_triangle() {
        // Determine order
        this->lower_left = this->LowerLeft();
        this->upper_left = this->UpperLeft();
        this->the_other = 3 - this->lower_left - this->upper_left;
        //std::cout << this->vertex[0] << std::endl;
        //std::cout << this->vertex[1] << std::endl;
        //std::cout << this->vertex[2] << std::endl;

        vector3_type v_ll (vertex[this->lower_left][1], vertex[this->lower_left][2], 0);
        vector3_type v_ul (vertex[this->upper_left][1], vertex[this->upper_left][2], 0);
        vector3_type v_ot (vertex[this->the_other][1], vertex[this->the_other][2], 0);
        int c = Cross(v_ul - v_ll, v_ot - v_ll)[3];
        if (c < 0)
        {
          this->left_edge.init(vertex[this->lower_left],  this->normals[this->lower_left], this->colors[this->lower_left], this->world_coords[this->lower_left],
                               vertex[this->upper_left],  this->normals[this->upper_left], this->colors[this->upper_left], this->world_coords[this->upper_left]);
          this->right_edge.init(vertex[this->lower_left], this->normals[this->lower_left], this->colors[this->lower_left], this->world_coords[this->lower_left],
                                vertex[this->the_other],  this->normals[this->the_other], this->colors[this->the_other],   this->world_coords[this->the_other],
                                vertex[this->upper_left], this->normals[this->upper_left], this->colors[this->upper_left], this->world_coords[this->upper_left]);
        } else if (c > 0)
        {
          this->left_edge.init(vertex[this->lower_left],  this->normals[this->lower_left], this->colors[this->lower_left], this->world_coords[this->lower_left],
                               vertex[this->the_other],   this->normals[this->the_other], this->colors[this->the_other],   this->world_coords[this->the_other],
                               vertex[this->upper_left],  this->normals[this->upper_left], this->colors[this->upper_left], this->world_coords[this->upper_left]);
          this->right_edge.init(vertex[this->lower_left], this->normals[this->lower_left], this->colors[this->lower_left], this->world_coords[this->lower_left],
                                vertex[this->upper_left], this->normals[this->upper_left], this->colors[this->upper_left], this->world_coords[this->upper_left]);
        }
        else
        {
          this->is_degenerate = true;
          return;
        }
        // Get first drawable point
        SearchForNonEmptyScanline();
      }

      // A triangle is degenerate if all three points are co-linear
      bool degenerate() {
        return is_degenerate;
      }

      // LowerLeft() returns the index of the vertex with the smallest y-coordinate
      // If there is a horizontal edge, the vertex with the smallest
      // x-coordinate is chosen.
      // The computations should be done in integer coordinates.
      int LowerLeft() {
        int ll = 0;
        for(int i=0;i<3;i++) {
          if ((this->vertex[i][2] < this->vertex[ll][2]) ||
             ((this->vertex[i][2] == this->vertex[ll][2]) &&
               this->vertex[i][1] < this->vertex[ll][1])) {
            ll = i;
          }
        }
        return ll;
      }

      // UpperLeft() returns the index of the vertex with the greatest y-coordinate
      // If there is a horizontal edge, the vertex with the smallest
      // x-coordinate is chosen.
      // The computations should be done in integer coordinates.
      int UpperLeft() {
        int ul = 0;
        for(int i=0;i<3;i++) {
          if ((vertex[i][2] > vertex[ul][2]) ||
             ((vertex[i][2] == vertex[ul][2]) &&
               vertex[i][1] < vertex[ul][1])) {
            ul = i;
          }
        }
        return ul;
      }

      void SearchForNonEmptyScanline() {
        while(this->x_current == this->x_stop &&
             (this->left_edge.more_fragments() || this->right_edge.more_fragments())) {

          this->x_current = this->left_edge.x();
          this->y_current = this->left_edge.y();
          this->x_stop = this->right_edge.x();

          this->depth_interpolator.init(this->x_current,
                                        this->x_stop,
                                        this->left_edge.depth(),
                                        this->right_edge.depth());
          this->color_interpolator.init(this->x_current,
                                        this->x_stop,
                                        this->left_edge.color(),
                                        this->right_edge.color());
          this->normal_interpolator.init(this->x_current,
                                         this->x_stop,
                                         this->left_edge.normal(),
                                         this->right_edge.normal());
          this->world_interpolator.init(this->x_current,
                                        this->x_stop,
                                        this->left_edge.position(),
                                        this->right_edge.position());
          this->left_edge.next_fragment();
          this->right_edge.next_fragment();
        }
      }

      void choose_color(int x) {
        // x is the position on a scanline in a triangle - they all have different colors:
        //    xstart  : green
        //    xcurrent: yellow
        //    xstop   : red
        // This is like a trafic-light: green->go ahead, yellow->be carefull, red->stop!

        // implement the real version
      }

      // Private Variables
      vector3_type vertex[3];
      vector3_type colors[3];
      vector3_type normals[3];
      vector3_type world_coords[3];

      vector3_type dummy_vector;

      // The Debug variable
      bool Debug;

      // Indices into the vertex table
      int lower_left;
      int upper_left;
      int the_other;

      int x_current, x_stop, y_current;

      bool valid;
      bool is_degenerate;

      MyEdgeRasterizer<MyMathTypes> left_edge;
      MyEdgeRasterizer<MyMathTypes> right_edge;

      LinearInterpolator<MyMathTypes, MyMathTypes::real_type> depth_interpolator;
      LinearInterpolator<MyMathTypes, MyMathTypes::vector3_type> color_interpolator;
      LinearInterpolator<MyMathTypes, MyMathTypes::vector3_type> normal_interpolator;
      LinearInterpolator<MyMathTypes, MyMathTypes::vector3_type> world_interpolator;
  };

}                                // end namespace graphics


// TRIANGLE_RASTERIZER_H
#endif
