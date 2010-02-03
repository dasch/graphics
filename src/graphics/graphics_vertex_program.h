#ifndef GRAPHICS_VERTEX_PROGRAM_H
#define GRAPHICS_VERTEX_PROGRAM_H
//
// Graphics Framework.
// Copyright (C) 2008 Department of Computer Science, University of Copenhagen
//

#include "graphics_state.h"

namespace graphics
{
    template< typename math_types >
    class VertexProgram
    {
    public:
	typedef typename math_types::vector3_type     vector3_type;
	typedef typename  math_types::real_type       real_type;
	typedef GraphicsState<math_types>             graphics_state_type;

    public:
	virtual void run( graphics_state_type const& state,
			  vector3_type const& in_vertex,
			  vector3_type const& in_color,
			  vector3_type& out_vertex,
			  vector3_type& out_color ) = 0;

	virtual void run( graphics_state_type const& state,
			  vector3_type const& in_vertex,
			  vector3_type const& in_normal,
			  vector3_type const& in_color,
			  vector3_type& out_vertex,
			  vector3_type& out_normal,
			  vector3_type& out_color ) = 0;

    };

}// end namespace graphics

// GRAPHICS_VERTEX_PROGRAM_H
#endif
