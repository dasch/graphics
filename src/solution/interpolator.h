#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <iostream>
#include <iomanip>
#include <cmath>

#include "graphics/graphics.h"
#include "solution/math_types.h"

// Pure Abstract class

namespace graphics {

/*******************************************************************\
*                                                                   *
*                      I n t e r p o l a t o r                      *
*                                                                   *
\*******************************************************************/

    template<typename math_types, typename value_type>
    class Interpolator {
    public:
    typedef typename math_types::vector3_type vector3_type;
        typedef typename math_types::real_type    real_type;

/*******************************************************************\
*                                                                   *
*                    I n t e r p o l a t o r ( )                    *
*                                                                   *
\*******************************************************************/

    Interpolator() {}

/*******************************************************************\
*                                                                   *
*       I n t e r p o l a t o r ( I n t e r p o l a t o r & )       *
*                                                                   *
\*******************************************************************/

    Interpolator(Interpolator const& new_interpolator) {}

/*******************************************************************\
*                                                                   *
*                   ~ I n t e r p o l a t o r ( )                   *
*                                                                   *
\*******************************************************************/

    virtual ~Interpolator()    {}

/*******************************************************************\
*                                                                   *
*     i n i t ( 2   x   i n t ,   2   x   v a l u e _ t y p e )     *
*                                                                   *
\*******************************************************************/

    virtual void init(int t_start, int t_stop, value_type const& Vstart, value_type const& Vstop) = 0;
    
/*******************************************************************\
*                                                                   *
*                             U s a g e                             *
*                                                                   *
\*******************************************************************/

    // Usage:
        //    while (more_values()) {
    //        value_type this_value = value();
    //        ...
        //        use this_value
    //        ...
    //        next_value();
        //    }

/*******************************************************************\
*                                                                   *
*                           v a l u e ( )                           *
*                                                                   *
\*******************************************************************/

    virtual value_type const& value() const = 0;

/*******************************************************************\
*                                                                   *
*                     m o r e _ v a l u e s ( )                     *
*                                                                   *
\*******************************************************************/

    virtual bool more_values() const = 0;

/*******************************************************************\
*                                                                   *
*                      n e x t _ v a l u e ( )                      *
*                                                                   *
\*******************************************************************/

    virtual void next_value()  = 0;

/*******************************************************************\
*                                                                   *
*           o p e r a t o r = ( I n t e r p o l a t o r )           *
*                                                                   *
\*******************************************************************/

    Interpolator<math_types, value_type> const& operator=(Interpolator const& new_interpolator) {}

/*******************************************************************\
*                                                                   *
*                 P r o t e c t e d   M e m b e r s                 *
*                                                                   *
\*******************************************************************/

    protected:

/*******************************************************************\
*                                                                   *
*                   P r i v a t e   M e m b e r s                   *
*                                                                   *
\*******************************************************************/


    private:
    
    };
}

#endif
