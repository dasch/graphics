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

    private:

        bool valid;

        value_type v_start, v_stop, v_current, v_delta;
        int t_start, t_stop, t_current, t_delta;

    public:

        typedef typename math_types::vector3_type vector3_type;
        typedef typename math_types::real_type    real_type;

        LinearInterpolator() : Interpolator<math_types, value_type>()
        {
            valid = false;
        }

        LinearInterpolator(LinearInterpolator const& new_linearinterpolator)
            : Interpolator<math_types, value_type>(new_linearinterpolator)
              
        {
            valid = false;
        }

        virtual ~LinearInterpolator() {}

        void init(int t_start, int t_stop, value_type const& v_start, value_type const& v_stop)
        {
            this->t_start = t_start;
            this->t_stop = t_stop;
            this->t_current = t_start;
            this->t_delta = (t_start <= t_stop) ? 1 : -1;

            this->v_start = v_start;
            this->v_stop = v_stop;
            this->v_current = v_start;
            this->v_delta = ((v_stop - v_start) / std::fabs(t_stop - t_start)) * t_delta;

            valid = true;
        }

        value_type const& value() const
        {
            return v_current;
        }

        bool more_values() const
        {
            return valid;
        }

        void next_value()
        {
            t_current++;
            v_current += v_delta;

            if (t_current == t_stop)
                valid = false;
        }

        LinearInterpolator<math_types, value_type> const&
        operator=(LinearInterpolator const& newlinearinterpolator)
        {
            if (this != &newlinearinterpolator) {
            // copy the state variables of the argument to this instance
            }

            return *this;
        }

    };
}

#endif
