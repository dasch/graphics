#ifndef LINEARINTERPOLATOR
#define LINEARINTERPOLATOR

#include <iostream>
#include <iomanip>
#include <cmath>

#include "graphics/graphics.h"
#include "solution/math_types.h"

#include "interpolator.h"


namespace graphics {

    template <typename math_types, typename value_type>
    class LinearInterpolator : public Interpolator<math_types, value_type> {

    public:

        typedef typename math_types::vector3_type vector3_type;
        typedef typename math_types::real_type    real_type;

        LinearInterpolator() : Interpolator<math_types, value_type>()
        {
            // implement the real version
        }

        LinearInterpolator(LinearInterpolator const& new_linearinterpolator)
            : Interpolator<math_types, value_type>(new_linearinterpolator)
              
        {
            // implement the real version
        }

        virtual ~LinearInterpolator() {}

        void init(int t_start, int t_stop, value_type const& Vstart, value_type const& Vstop)
        {
            // implement the real version
        }

        value_type const& value() const
        {
            // implement the real version

            return this->dummy_value;
        }

        bool more_values() const
        {
            return false;
        }

        void next_value()
        {
            // implement the real version
        }

        LinearInterpolator<math_types, value_type> const&
        operator=(LinearInterpolator const& newlinearinterpolator)
        {
            if (this != &newlinearinterpolator) {
            // copy the state variables of the argument to this instance
            }

            return *this;
        }


    private:

        value_type dummy_value;

    };
}

#endif
