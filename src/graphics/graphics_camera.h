#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H
//
// Graphics Framework.
// Copyright (C) 2008 Department of Computer Science, University of Copenhagen
//

namespace graphics
{
    /**
     * A virtual pin-hole camera.
     * The camera class produces the matrices necessary for the virtual world
     * to be rasterized.
     */
    template<typename math_types>
    class Camera
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
    Camera() : m_state(0)
    {}

    /**
     * Destroys the Camera.
     */
    virtual ~Camera()
    {}

    /**
     * Initialize the Camera with a RenderPipeline.
     */
    void init(RenderPipeline<math_types>& R)
    { 
        m_state = &(R.state());
    }

    /**
     * Set the projection matrix.
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
    void set_projection(vector3_type const& vrp, vector3_type const& vpn,
                vector3_type const& vup, vector3_type const& prp,
                vector2_type const& lower_left,
                vector2_type const& upper_right, 
                real_type    const& front_plane,
                real_type    const& back_plane)
    {
        this->m_state->view_orientation() = this->compute_view_orientation(vrp, vpn, vup);

        this->m_state->view_projection()  = this->compute_view_projection_matrix(prp,
                                             lower_left,
                                             upper_right,
                                             front_plane,
                                             back_plane);

        matrix4x4_type M;
        M = this->m_state->view_projection() * this->m_state->view_orientation();

        this->m_state->projection() = M;
    }
      
    /**
     * Get the projection matrix.
     * @return The current projection matrix from world to screen.
     */
    matrix4x4_type get_projection() const
    {
        return this->m_state->projection();
    }

    /**
     * Get View-Orientation.
     * @return The transformation matrix which transforms from the world-coordinate system to the eye-coordinate system.
     */
    matrix4x4_type get_view_orientation() const
    {
        return this->m_state->view_orientation();
    }

        /**
     * Get View-Projection.
     * @return The transformation matrix which transforms from the eye-coordinate system to the canonical view-volume.
     */
    matrix4x4_type get_view_projection() const
    {
        return this->m_state->view_projection();
    }

        /**
     * Get window-viewport transformation.
     * @return The transformation matrix which transforms from the canonical view-volume to the screen-coordinate system.
     */
    matrix4x4_type get_window_viewport() const
    {
        return this->m_state->window_viewport();
    }

    /**
     * Set model-view matrix.
     *
     *@param M    Model-View matrix.
     */
    void set_model_view(matrix4x4_type const& M)
    {
        this->m_state->model() = M;
    }


    protected:

    /**
     * Computes a matrix which transforms coordinates from the World-coordinate system to the Eye-coordinate system.
     * Foley et al. (p.229-284; 2nd edition)
     * @param vrp The View Reference Point.
     * @param vpn The View Plane Normal.
     * @param vup The View Up Vector.
     * @return    The view_orientation matrix.
     */
    virtual matrix4x4_type compute_view_orientation_matrix(vector3_type const& vrp,
                                   vector3_type const& vpn,
                                   vector3_type const& vup) = 0;

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
    virtual matrix4x4_type compute_view_projection_matrix(vector3_type const& prp,
                                  vector2_type const& lower_left,
                                  vector2_type const& upper_right,
                                  real_type    const& front_plane,
                                  real_type    const& back_plane) = 0;

    /**
     * Computes a projection matrix using the parameters for a perspective camera 
     * given by Foley et al. (p.229-284; 2nd edition)
     * The projection matrix should transforms from world coordinates to 
     * normalized projection coordinates
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
    virtual matrix4x4_type compute_projection_matrix(vector3_type const& vrp,
                             vector3_type const& vpn,
                             vector3_type const& vup,
                             vector3_type const& prp,
                             vector2_type const& lower_left,
                             vector2_type const& upper_right,
                             real_type    const& front_plane,
                             real_type    const& back_plane) = 0;

    protected:
    
    /**
     * Stores a pointer to the state of the graphics pipeline.
     */
    GraphicsState<math_types>* m_state;

    };

}// end namespace graphics

// GRAPHICS_CAMERA_H
#endif
