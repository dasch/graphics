#ifndef LINE_RASTERIZER_H
#define LINE_RASTERIZER_H
//
// Graphics Framework.
// Copyright (C) 2010 Department of Computer Science, University of Copenhagen
//

#include <iostream>
#include <iomanip>
#include <cmath>

#include "graphics/graphics.h"
#include "linear_interpolator.h"


/*******************************************************************\
*                                                                   *
*                N a m e S p a c e   g r a p h i c s                *
*                                                                   *
\*******************************************************************/

namespace graphics {

/*******************************************************************\
*                                                                   *
*            C l a s s   M y L i n e R a s t e r i z e r            *
*                                                                   *
\*******************************************************************/

    template<typename math_types>
    class MyLineRasterizer : public Rasterizer<math_types>
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
*                M y L i n e R a s t e r i z e r ( )                *
*                                                                   *
\*******************************************************************/

    MyLineRasterizer() : Debug(false), valid(false)
    {}


/*******************************************************************\
*                                                                   *
*                ~ M y L i n e R a s t e r i z e r ( )              *
*                                                                   *
\*******************************************************************/

    virtual ~MyLineRasterizer() {}


/*******************************************************************\
*                                                                   *
*           i n i t ( 4   x   v e c t o r 3 _ t y p e & )           *
*                                                                   *
\*******************************************************************/

    void init( vector3_type const& in_vertex1,
           vector3_type const& in_color1,
           vector3_type const& in_vertex2,
           vector3_type const& in_color2)
    {
        // This is a line rasterizer
        // The vertices are in 3D screen coordinates

        // Determine if the line is x-dominat or y-dominant
        // if (?) {
        // The line is x-dominant

        // Set up a pointer for the inner-loop for an x-donmiant line
        // This is a pointer to a private member function!
        // Therefore it looks very strange, but this is how to do it!
        
            // this->innerloop = &MyLineRasterizer::x_dominant_innerloop;
        //}
        //else {
        // The line is y-dominant

                // Set up a pointer for the inner-loop for a y-donmiant line
        // This is a pointer to a private member function!
        // Therefore it looks very strange, but this is how to do it!

        // this->innerloop = &MyLineRasterizer::y_dominant_innerloop;
        //}

        this->Debug = false;
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
        throw std::runtime_error("MyLineRasterizer::x():Invalid State/Not Initialized");
        }
        return 0;     
    }


/*******************************************************************\
*                                                                   *
*                               y ( )                               *
*                                                                   *
\*******************************************************************/

    int y() const
    {
        if (!this->valid) {
        throw std::runtime_error("MyLineRasterizer::y():Invalid State/Not Initialized");
        }
        return 0;
    }


/*******************************************************************\
*                                                                   *
*                           d e p t h ( )                           *
*                                                                   *
\*******************************************************************/

    real_type depth() const     
    {
        if (!this->valid) {
        throw std::runtime_error("MyLineRasterizer::depth():Invalid State/Not Initialized");
        }
        return 0.0;
    }


/*******************************************************************\
*                                                                   *
*                        p o s i t i o n ( )                        *
*                                                                   *
\*******************************************************************/

    vector3_type position() const 
        {
        if (!this->valid) {
        throw std::runtime_error("MyLineRasterizer::position():Invalid State/Not Initialized");
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
        throw std::runtime_error("MyLineRasterizer::normal():Invalid State/Not Initialized");
        }
        return this->dummy_vector;    // The program should never come here!
    }


/*******************************************************************\
*                                                                   *
*                           c o l o r ( )                           *
*                                                                   *
\*******************************************************************/

    vector3_type const& color() const 
    {
        if (!this->valid) {
        throw std::runtime_error("MyLineRasterizer::color():Invalid State/Not Initialized");
        }
        return this->dummy_vector;
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

        return false;
    }


/*******************************************************************\
*                                                                   *
*                   n e x t _ f r a g m e n t ( )                   *
*                                                                   *
\*******************************************************************/

    void next_fragment()    
    {
        // Dereference a pointer to a private member function.
        // It looks strange, but it is the way to do it!
        (this->*innerloop)();
         }


/*******************************************************************\
*                                                                   *
*                 p r i n t _ v a r i a b l e s ( )                 *
*                                                                   *
\*******************************************************************/

    void print_variables()
    {
        std::cout << "MyLineRasterizer: local variables" << std::endl;
        std::cout << "=================================" << std::endl;
        std::cout << "\tvalid     == " << this->valid    << std::endl;
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
*                x _ d o m i n a n t _ i n n e r l o o p ( )        *
*                                                                   *
\*******************************************************************/

    void x_dominant_innerloop()
    {}


/*******************************************************************\
*                                                                   *
*            y _ d o m i n a n t _ i n n e r l o o p ( )            *
*                                                                   *
\*******************************************************************/

    void y_dominant_innerloop()
    {}


/*******************************************************************\
*                                                                   *
*                 P r i v a t e   V a r i a b l e s                 *
*                                                                   *
\*******************************************************************/

    // This looks strange, byt it is the definition of a pointer to a 
    // private member function! That is how it is done!
    void         (MyLineRasterizer::*innerloop)();

    bool         valid;

    bool         Debug;

    vector3_type dummy_vector;
    };

}// end namespace graphics

// LINE_RASTERIZER_H
#endif
