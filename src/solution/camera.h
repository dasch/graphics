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

        /// The actual type of a vector4.
        typedef typename math_types::vector4_type   vector4_type;

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
            matrix4x4_type M = identity();

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
            matrix4x4_type M = identity();

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
            matrix4x4_type M = identity();

            return M;
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

        matrix4x4_type identity()
        {
            matrix4x4_type M;

            M[1][1] = 1, M[1][2] = 0, M[1][3] = 0, M[1][4] = 0;
            M[2][1] = 0, M[2][2] = 1, M[2][3] = 0, M[2][4] = 0; 
            M[3][1] = 0, M[3][2] = 0, M[3][3] = 1, M[3][4] = 0; 
            M[4][1] = 0, M[4][2] = 0, M[4][3] = 0, M[4][4] = 1;

            return M;
        }

        matrix4x4_type translate(vector3_type diff)
        {
            matrix4x4_type M = identity();

            M[1][4] = diff[1];
            M[2][4] = diff[2];
            M[3][4] = diff[3];

            return M;
        }

        matrix4x4_type scale(vector3_type factor)
        {
            matrix4x4_type M = identity();

            M[1][1] = factor[1];
            M[2][2] = factor[2];
            M[3][3] = factor[3];

            return M;
        }

        matrix4x4_type x_rotate(real_type angle)
        {
            matrix4x4_type M = identity();

            M[2][2] = cos(angle);
            M[2][3] = -sin(angle);
            M[3][2] = sin(angle);
            M[3][3] = cos(angle);

            return M;
        }

        matrix4x4_type y_rotate(real_type angle)
        {
            matrix4x4_type M = identity();

            M[1][1] = cos(angle);
            M[1][3] = sin(angle);
            M[3][1] = -sin(angle);
            M[3][3] = cos(angle);

            return M;
        }

        matrix4x4_type z_rotate(real_type angle)
        {
            matrix4x4_type M = identity();

            M[1][1] = cos(angle);
            M[1][2] = -sin(angle);
            M[2][1] = sin(angle);
            M[2][2] = cos(angle);

            return M;
        }

        matrix4x4_type xy_shear(real_type sx, real_type sy)
        {
            matrix4x4_type M = identity();

            M[1][3] = sx;
            M[2][3] = sy;

            return M;
        }

        matrix4x4_type xz_shear(real_type sx, real_type sz)
        {
            matrix4x4_type M = identity();

            M[1][2] = sx;
            M[3][2] = sz;

            return M;
        }

        matrix4x4_type yz_shear(real_type sy, real_type sz)
        {
            matrix4x4_type M = identity();

            M[2][1] = sy;
            M[3][1] = sz;

            return M;
        }

    };

}// end namespace graphics

// CAMERA_H
#endif
