#ifndef POINT_RASTERIZER_H
#define POINT_RASTERIZER_H
//
// Graphics Framework.
// Copyright (C) 2008 Department of Computer Science, University of Copenhagen
//

#include <iostream>
#include <iomanip>
#include <cmath>

#include "graphics/graphics.h"


/*******************************************************************\
*                                                                   *
*                N a m e S p a c e   g r a p h i c s                *
*                                                                   *
\*******************************************************************/

namespace graphics {

/*******************************************************************\
*                                                                   *
*           c l a s s   M y P o i n t R a s t e r i z e r           *
*                                                                   *
\*******************************************************************/

    template<typename math_types>
    class MyPointRasterizer : public Rasterizer<math_types>
    {

/*******************************************************************\
*                                                                   *
*                       P u l i c   T y p e s                       *
*                                                                   *
\*******************************************************************/

    public:

/*******************************************************************\
*                                                                   *
*                      v e c t o r 3 _ t y p e                      *
*                                                                   *
\*******************************************************************/

    typedef typename math_types::vector3_type      vector3_type;

/*******************************************************************\
*                                                                   *
*                         r e a l _ t y p e                         *
*                                                                   *
\*******************************************************************/

    typedef typename math_types::real_type         real_type;



/*******************************************************************\
*                                                                   *
*                    P u b l i c   M e m b e r s                    *
*                                                                   *
\*******************************************************************/

    public:

/*******************************************************************\
*                                                                   *
*               M y P o i n t R a s t e r i z e r ( )               *
*                                                                   *
\*******************************************************************/

    MyPointRasterizer() : zero_normal(0, 0, 0), valid(false), Debug(false)
    {}


/*******************************************************************\
*                                                                   *
*              ~ M y P o i n t R a s t e r i z e r ( )              *
*                                                                   *
\*******************************************************************/

    virtual ~MyPointRasterizer() {}


/*******************************************************************\
*                                                                   *
*           i n i t ( 2   x   v e c t o r 3 _ t y p e & )           *
*                                                                   *
\*******************************************************************/

    void init( vector3_type const& in_vertex1,
           vector3_type const& in_color1)
    {
        // This is a point rasterizer
        // The vertex is in 3D screen coordinates

        this->zero_normal = vector3_type(0, 0, 0);

        // Convert (x, y) to integer coordinates
        this->x_start = static_cast<int>(round(in_vertex1[1]));
        this->y_start = static_cast<int>(round(in_vertex1[2]));
        this->z_start = in_vertex1[3];

        this->color_start   = in_color1;

        this->valid = true;
    }


/*******************************************************************\
*                                                                   *
*                         D e b u g O n ( )                         *
*                                                                   *
\*******************************************************************/

    bool DebugOn()
    {
        bool oldvalue = this->Debug;
        this->Debug = true;

        return oldvalue;
    }

/*******************************************************************\
*                                                                   *
*                        D e b u g O f f ( )                        *
*                                                                   *
\*******************************************************************/

    bool DebugOff()
    {
        bool oldvalue = this->Debug;
        this->Debug = false;

        return oldvalue;
    }

/*******************************************************************\
*                                                                   *
*                               x ( )                               *
*                                                                   *
\*******************************************************************/

    int x() const
    {
        if (!this->valid) {
        throw std::runtime_error("MyPointRasterizer::x():Invalid State/Not Initialized");
        }
        return this->x_start;
    }


/*******************************************************************\
*                                                                   *
*                               y ( )                               *
*                                                                   *
\*******************************************************************/

    int y() const
    {
        if (!this->valid) {
        throw std::runtime_error("MyPointRasterizer::y():Invalid State/Not Initialized");
        }
        return this->y_start;
    }


/*******************************************************************\
*                                                                   *
*                           d e p t h ( )                           *
*                                                                   *
\*******************************************************************/

    real_type depth() const     
    {
        if (!this->valid) {
        throw std::runtime_error("MyPointRasterizer::depth():Invalid State/Not Initialized");
        }
        return this->z_start;
    }


/*******************************************************************\
*                                                                   *
*                        p o s i t i o n ( )                        *
*                                                                   *
\*******************************************************************/

    vector3_type position() const 
        {
        if (!this->valid) {
        throw std::runtime_error("MyPointRasterizer::position():Invalid State/Not Initialized");
        }
        return vector3_type(this->x(), this->y(), this->depth());
    }


/*******************************************************************\
*                                                                   *
*                          n o r m a l ( )                          *
*                                                                   *
\*******************************************************************/

    vector3_type const& normal() const     
    {
        if (!this->valid) {
        throw std::runtime_error("MyPointRasterizer::normal():Invalid State/Not Initialized");
        }
        return this->zero_normal;    // The program should never come here!
    }


/*******************************************************************\
*                                                                   *
*                           c o l o r ( )                           *
*                                                                   *
\*******************************************************************/

    vector3_type const& color() const
    {
        if (!this->valid) {
        throw std::runtime_error("MyPointRasterizer::color():Invalid State/Not Initialized");
        }
        return this->color_start;
    }


/*******************************************************************\
*                                                                   *
*                  m o r e _ f r a g m e n t s ( )                  *
*                                                                   *
\*******************************************************************/


    bool more_fragments() const
    {
            // Usage:
        //    Assume a pointer variable rasterizer is set up probably
        //     while (rasterizer->more_fragments()) {
        //         int x = rasterize->x();
        //         int y = rasterizer->y();
        //         MyMathTypes::real_type depth = rasterizer->depth();
        //         MyMathTypes::vector3_type    = rasterizer->position();
        //         MyMathTypes::vector3_type    = rasterizer->color();
        //             ...
        //             use the values ...
        //             ...
        //         rasterizer->next_fragment();
        //    }

        return this->valid;
    }


/*******************************************************************\
*                                                                   *
*                   n e x t _ f r a g m e n t ( )                   *
*                                                                   *
\*******************************************************************/

    void next_fragment()
    {
        if (this->valid) this->valid = false;
    }


/*******************************************************************\
*                                                                   *
*                 p r i n t _ v a r i a b l e s ( )                 *
*                                                                   *
\*******************************************************************/

    void print_variables()
    {
        std::cout << "MyPointRasterizer: local variables" << std::endl;
        std::cout << "==================================" << std::endl;
        std::cout << "\tvalid     == " << this->valid    << std::endl;
        std::cout << std::endl;
        std::cout << "\tx_start   == " << this->x_start   << std::endl;
        std::cout << "\ty_start   == " << this->y_start   << std::endl;
        std::cout << std::endl;
        std::cout << "\tDebug == " << this->Debug << std::endl;
        std::cout << std::endl;
    }

    protected:


/*******************************************************************\
*                                                                   *
*                   P r i v a t e   M e m b e r s                   *
*                                                                   *
\*******************************************************************/

    private:


/*******************************************************************\
*                                                                   *
*                 P r i v a t e   V a r i a b l e s                 *
*                                                                   *
\*******************************************************************/

    int          x_start;
    int          y_start;
    real_type    z_start;

    vector3_type color_start;

    vector3_type zero_normal;

    bool         valid;

    bool         Debug;
    };

}// end namespace graphics

// POINT_RASTERIZER_H
#endif
