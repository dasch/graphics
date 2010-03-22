#ifndef FRAGMENT_PROGRAM_H
#define FRAGMENT_PROGRAM_H
//
// Graphics Framework.
// Copyright (C) 2010 Department of Computer Science, University of Copenhagen
//
#include <iostream>
#include <iomanip>
#include "graphics/graphics.h"

#define N 20

namespace graphics {

    template<typename math_types>
    class MyFragmentProgram : public FragmentProgram<math_types>
    {
    public:

    typedef typename FragmentProgram<math_types>::graphics_state_type graphics_state_type;
    typedef typename math_types::vector3_type                         vector3_type;

    public:
        void run(graphics_state_type const & state,
             vector3_type const & in_position,
             vector3_type const & in_normal,
             vector3_type const & in_color,
             vector3_type & out_color)
        {
            if (state.light_position() == vector3_type(0, 0, 0)) {
                out_color = in_color;
                return;
            }

            vector3_type normal = in_normal / Norm(in_normal);

            vector3_type A = ambient(state);
            vector3_type D = diffuse(state, in_position, normal);
            vector3_type S = specular(state, in_position, normal);

            vector3_type light = A + D + S;

            out_color = vector3_type(in_color[1] * light[1], in_color[2] * light[2], in_color[3] * light[3]);
        }

        vector3_type
        ambient(graphics_state_type const& state)
        {
            return state.ambient_intensity() * state.ambient_color();
        }

        vector3_type
        diffuse(graphics_state_type const& state, 
                vector3_type const & in_position,
                vector3_type const & in_normal)
        {
            vector3_type L = state.light_position() - in_position;
            L = L / Norm(L);

            return state.diffuse_color() * state.diffuse_intensity() * Dot(in_normal, L);
        }

        vector3_type
        specular(graphics_state_type const& state, 
                 vector3_type const & in_position,
                 vector3_type const & in_normal)
        {
            vector3_type L = state.light_position() - in_position;
            L = L / Norm(L);

            vector3_type R = (in_normal * 2) * Dot(in_normal, L) - L;

            vector3_type V = state.eye_position() - in_position;
            V = V / Norm(V);

            return state.specular_intensity() * state.specular_color() * pow(Dot(R, V), N);
        }
    };

}// end namespace graphics

// FRAGMENT_PROGRAM_H
#endif
