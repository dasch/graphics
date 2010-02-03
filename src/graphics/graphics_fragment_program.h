#ifndef GRAPHICS_FRAGMENT_PROGRAM_H
#define GRAPHICS_FRAGMENT_PROGRAM_H
//
// Graphics Framework.
// Copyright (C) 2007 Department of Computer Science, University of Copenhagen
//

#include "graphics_state.h"

namespace graphics
{

  template< typename math_types >
  class FragmentProgram
  {
  public:

    typedef typename math_types::vector3_type     vector3_type;
    typedef typename  math_types::real_type       real_type;
    typedef GraphicsState<math_types>             graphics_state_type;

  public:

    virtual void run( 
        graphics_state_type const & state
      , vector3_type const & in_position
      , vector3_type const & in_normal
      , vector3_type const & in_color
      , vector3_type & out_color
      ) = 0;

  };

}// end namespace graphics

// GRAPHICS_FRAGMENT_PROGRAM_H
#endif
