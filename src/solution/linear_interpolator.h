#ifndef LINEARINTERPOLATOR
#define LINEARINTERPOLATOR

#include <iostream>
#include <iomanip>
#include <cmath>

#include "graphics/graphics.h"
#include "solution/math_types.h"

#include "interpolator.h"


namespace graphics {

/*******************************************************************\
*                                                                   *
*                L i n e a r I n t e r p o l a t o r                *
*                                                                   *
\*******************************************************************/

    template <typename math_types, typename value_type>
    class LinearInterpolator : public Interpolator<math_types, value_type> {
    public:
	typedef typename math_types::vector3_type vector3_type;
	typedef typename math_types::real_type    real_type;

    public:
	LinearInterpolator() : Interpolator<math_types, value_type>()
	{
	    // implement the real version
	}

	LinearInterpolator(LinearInterpolator const& new_linearinterpolator)
	    : Interpolator<math_types, value_type>(new_linearinterpolator)
	      
	{
	    // implement the real version
	}

/*******************************************************************\
*                                                                   *
*                ~ L i n e a r I n t e r p o l a t o r ( )          *
*                                                                   *
\*******************************************************************/

	virtual ~LinearInterpolator() {}


/*******************************************************************\
*                                                                   *
*     i n i t ( 2   x   i n t ,   2   x   v a l u e _ t y p e &)    *
*                                                                   *
\*******************************************************************/

	void init(int t_start, int t_stop, value_type const& Vstart, value_type const& Vstop)
        {
	    // implement the real version
	}

/*******************************************************************\
*                                                                   *
*                           V a l u e ( )                           *
*                                                                   *
\*******************************************************************/

	value_type const& value() const
	{
	    // implement the real version

	    return this->dummy_value;
	}

/*******************************************************************\
*                                                                   *
*                     m o r e _ v a l u e s ( )                     *
*                                                                   *
\*******************************************************************/

	bool more_values() const
	{
	    return false;
	}

/*******************************************************************\
*                                                                   *
*                      n e x t _ v a l u e ( )                      *
*                                                                   *
\*******************************************************************/

	void next_value()
	{
	    // implement the real version
	}

	
/*******************************************************************\
*                                                                   *
*     o p e r a t o r = ( L i n e a r I n t e r p o l a t o r )     *
*                                                                   *
\*******************************************************************/

	LinearInterpolator<math_types, value_type> const&
	operator=(LinearInterpolator const& newlinearinterpolator)
	{
	    if (this != &newlinearinterpolator) {
		// copy the state variables of the argument to this instance
	    }

	    return *this;
	}


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
	value_type dummy_value;
    };
}

#endif
