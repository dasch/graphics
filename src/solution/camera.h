#ifndef CAMERA_H
#define CAMERA_H
//
// Graphics Framework.
// Copyright (C) 2010 Department of Computer Science, University of Copenhagen
//
#include "graphics/graphics.h"

namespace graphics {
    
    /**
     * A virtual pin-hole camera.
     * The camera class produces the matrices necessary for the virtual world
     * to be rasterized.
     */
    template<typename math_types>
    class MyCamera : public Camera<math_types>
    {
    public:
        /// The actual type of the elements of vectors and matrices.
        typedef typename math_types::real_type      real_type;

        /// The actual type of a vector2.
        typedef typename math_types::vector2_type   vector2_type;

        /// The actual type of a vector3.
        typedef typename math_types::vector3_type   vector3_type;

        /// The actual type of a matrix4x4.
        typedef typename math_types::matrix4x4_type matrix4x4_type;
    
    public:

        /**
         * Creates a Camera with a default (empty) state.
         */
        MyCamera() : Camera<math_types>()
        {}


        /**
         * Destroys the Camera.
         */
        virtual ~MyCamera()
        {}

    protected:

        /**
         * Computes a matrix which transforms coordinates from the World-coordinate system to the Eye-coordinate system.
         * Foley et al. (p.229-284; 2nd edition)
         * @param vrp The View Reference Point.
         * @param vpn The View Plane Normal.
         * @param vup The View Up Vector.
         * @return    The view_orientation matrix.
         */
        matrix4x4_type compute_view_orientation_matrix(vector3_type const& vrp,
                                   vector3_type const& vpn,
                                   vector3_type const& vup)
        {
            matrix4x4_type M;    // The identity matrix.
            M[1][1] = 1, M[1][2] = 0, M[1][3] = 0, M[1][4] = 0;
            M[2][1] = 0, M[2][2] = 1, M[2][3] = 0, M[2][4] = 0; 
            M[3][1] = 0, M[3][2] = 0, M[3][3] = 1, M[3][4] = 0; 
            M[4][1] = 0, M[4][2] = 0, M[4][3] = 0, M[4][4] = 1;

            return M;
        }

        /**
         * Computes a matrix which transforms from the Eye-coordinate system to the Canonical View Volume.
         * Foley et al. (p.229-284; 2nd edition)
         * @param prp         The Projection Reference Point in Eye-coordinates.
         * @param lower_left  The lower left corner of the window in Eye-coordinates.
         * @param upper_right The upper right corner of the window in Eye-coordinates.
         * @param front_plane The closest distance from the origin in Eye-coordinates.
         * @param back_plane  The farthest distance from the origin in Eye-coordinates.
         * @return The view_projection matrix.
         */
        matrix4x4_type compute_view_projection_matrix(vector3_type const& prp,
                                  vector2_type const& lower_left,
                                  vector2_type const& upper_right,
                                  real_type    const& front_plane,
                                  real_type    const& back_plane)
            {
            matrix4x4_type M;    // The identity matrix.
            M[1][1] = 1, M[1][2] = 0, M[1][3] = 0, M[1][4] = 0;
            M[2][1] = 0, M[2][2] = 1, M[2][3] = 0, M[2][4] = 0; 
            M[3][1] = 0, M[3][2] = 0, M[3][3] = 1, M[3][4] = 0; 
            M[4][1] = 0, M[4][2] = 0, M[4][3] = 0, M[4][4] = 1;

            return M;
        }

        /**
         * Computes a projection matrix using the parameters for a perspective camera 
         * given by Foley et al. (p.229-284; 2nd edition)
         * The projection matrix should transforms from world coordinates to 
         * normalized projection coordinates.
         * This is done in a number of steps: compute_view_orientation, compute_view_projection, and compute_window_viewport.
         * The final matrix is stored in the graphics_state.
         *
         * @param vrp          View reference point
         * @param vpn         View-plane normal 
         * @param vup          View up vector
         * @param prp          Projection reference point
         * @param lower_left  Lower left corner of the view-plane
         * @param upper_right Upper right corner of the view-plane
         * @param front_plane Distance to front clipping plane
         * @param back_plane  Distance to back clipping plane
         */
        matrix4x4_type compute_projection_matrix(vector3_type const& vrp, vector3_type const& vpn,
                             vector3_type const& vup, vector3_type const& prp,
                             vector2_type const& lower_left,
                             vector2_type const& upper_right,
                             real_type    const& front_plane,
                             real_type    const& back_plane)
        {
            // ToDo add your magic here!

            matrix4x4_type M;    // The identity matrix.
            M[1][1] = 1, M[1][2] = 0, M[1][3] = 0, M[1][4] = 0;
            M[2][1] = 0, M[2][2] = 1, M[2][3] = 0, M[2][4] = 0; 
            M[3][1] = 0, M[3][2] = 0, M[3][3] = 1, M[3][4] = 0; 
            M[4][1] = 0, M[4][2] = 0, M[4][3] = 0, M[4][4] = 1;

            return M;
        }
    };

}// end namespace graphics

// CAMERA_H
#endif
