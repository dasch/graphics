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
        out_color = in_color;
    }
    };

}// end namespace graphics

// FRAGMENT_PROGRAM_H
#endif
