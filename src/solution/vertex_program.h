#ifndef VERTEX_PROGRAM_H
#define VERTEX_PROGRAM_H
//
// Graphics Framework.
// Copyright (C) 2008 Department of Computer Science, University of Copenhagen
//
#include "graphics/graphics.h"

namespace graphics {

    template<typename math_types>
    class MyVertexProgram : public VertexProgram<math_types>
    {
    public:
        typedef typename VertexProgram<math_types>::graphics_state_type  graphics_state_type;
        typedef typename math_types::vector3_type                        vector3_type;
        typedef typename math_types::vector4_type                        vector4_type;
        typedef typename math_types::matrix4x4_type                      matrix4x4_type;
        typedef typename math_types::real_type                           real_type;

    public:

        void run(graphics_state_type const& state,
             vector3_type const& in_vertex,
             vector3_type const& in_color,
             vector3_type& out_vertex,
             vector3_type& out_color)
        {
            matrix4x4_type M = state.projection();
            matrix4x4_type N = state.window_viewport();
            
            out_vertex = euclidean(N * M * homogeneous(in_vertex));

            std::cout << "vertex: (" << in_vertex << ") -> (" << out_vertex << ")" << std::endl;

            out_color =  in_color;
        }


        void run(graphics_state_type const& state,
             vector3_type const& in_vertex,
             vector3_type const& in_normal,
             vector3_type const& in_color,
             vector3_type& out_vertex,
             vector3_type& out_normal,
             vector3_type& out_color)
        {
            matrix4x4_type M = state.projection();
            matrix4x4_type N = state.window_viewport();
            
            out_vertex = euclidean(N * M * homogeneous(in_vertex));

            out_normal = in_normal;
            out_color =  in_color;
        }

    private:

        /**
         * Convert a Euclidean vector to a homogeneous one.
         */
        vector4_type homogeneous(vector3_type vector)
        {
            vector4_type homo;

            homo[1] = vector[1];
            homo[2] = vector[2];
            homo[3] = vector[3];
            homo[4] = 1;

            return homo;
        }

        /**
         * Convert a homogeneous vector to a Euclidean one.
         */
        vector3_type euclidean(vector4_type vector)
        {
            vector3_type euc;
            real_type w = vector[4];

            euc[1] = vector[1] / w;
            euc[2] = vector[2] / w;
            euc[3] = vector[3] / w;

            return euc;
        }
    };

}// end namespace graphics

// VERTEX_PROGRAM_H
#endif
