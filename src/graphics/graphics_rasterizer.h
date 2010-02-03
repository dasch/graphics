#ifndef GRAPHICS_RASTERIZER_H
#define GRAPHICS_RASTERIZER_H
//
// Graphics Framework.
// Copyright (C) 2008 Department of Computer Science, University of Copenhagen
//

#include <stdexcept>

namespace graphics
{

    /**
     * This class describes an interface class for implementing a rasterizer.
     * One needs to make an inherited class like:
     *
     *   template<typename math_types>
     *   class MyRasterizer : public Rasterizer<math_types>
     *   {
     *       // add your implementation here 
     *   };
     *
     * An instance of this new implementation can be passed to render pipeline 
     * using the load_rasterizer-method.
     *
     */
    template<typename math_types>
    class Rasterizer
    {
    public:
	typedef typename math_types::vector3_type     vector3_type;
	typedef typename math_types::real_type        real_type;

    public:
	Rasterizer(){}

    public:
	/**
	 * Initialize the Point Rasterizer.
	 * The rasterizer is specialized to scan-conversion of points only. It
	 * is passed vertex data as its argument.
	 *
	 * Colors can be given in whatever coordinate system that one
	 * pleases, but they should be linearly interpolated in screen-space.
	 *
	 * Vertex coordinates is implicitly assumed to have been transformed
	 * into screen-space prior to invocation.
	 *
	 * @param in_vertex1
	 * @param in_color1
	 *
	 */
	virtual void init(vector3_type const& in_vertex1,
			  vector3_type const& in_color1)
	{
	    throw std::logic_error("No Point Rasterizer loaded.");
	}

	/**
	 * Initialize the Line Rasterizer.
	 * The rasterizer is specialized to scan-conversion of lines only. It
	 * is passed vertex data as its argument.
	 *
	 * Colors can be given in whatever coordinate system that one
	 * pleases, but they should be linearly interpolated in screen-space.
	 *
	 * Vertex coordinates is implicitly assumed to have been transformed
	 * into screen-space prior to invocation.
	 *
	 * @param in_vertex1
	 * @param in_color1
	 * @param in_vertex2
	 * @param in_color2
	 *
	 */
	virtual void init(vector3_type const& in_vertex1,
			  vector3_type const& in_color1,
			  vector3_type const& in_vertex2,
			  vector3_type const& in_color2)
	{
	    throw std::logic_error("No Line Rasterizer loaded.");
	}

	/**
	 * Initialize the Triangle Rasterizer.
	 * The rasterizer is specialized to scan-conversion of triangles only. It
	 * is passed vertex data as its argument.
	 *
	 * Normals and colors can be given in whatever coordinate system that one
	 * pleases, but they should be linearly interpolated in screen-space.
	 *
	 * Vertex coordinates is implicitly assumed to have been transformed
	 * into screen-space prior to invocation.
	 *
	 * @param in_vertex1
	 * @param in_normal1
	 * @param in_color1
	 * @param in_vertex2
	 * @param in_normal2
	 * @param in_color2
	 * @param in_vertex3
	 * @param in_normal3
	 * @param in_color3
	 *
	 */
	virtual void init(vector3_type const& in_vertex1,
			  vector3_type const& in_normal1,
			  vector3_type const& in_color1,
			  vector3_type const& in_vertex2,
			  vector3_type const& in_normal2,
			  vector3_type const& in_color2,
			  vector3_type const& in_vertex3,
			  vector3_type const& in_normal3,
			  vector3_type const& in_color3)
	{
	    throw std::logic_error("No Triangle Rasterizer loaded.");
	}


	virtual bool DebugOn() = 0;

	virtual bool DebugOff() = 0;

	/**
	 * Current x position of rasterizer position.
	 *
	 * @return   The x-coordinate of the current ``pixel''.
	 */
	virtual int x() const = 0;

	/**
	 * Current y position of rasterizer position.
	 *
	 * @return   The y-coordinate of the current ``pixel''.
	 */
	virtual int y() const = 0;

	/**
	 * Retrive the current z-value (depth).
	 *
	 * @return  This method should return the current z-value of the current fragment.
	 The z-value should ideally be computed in the canonical view-volume.
	*/
	virtual real_type depth() const = 0;

	/**
	 * Get Position.
	 *
	 * @return   The current (world coordinate) position of the current fragment.
	 */
	virtual vector3_type position() const = 0;

	/**
	 * Get Normal.
	 *
	 * @return   The current (world coordinate) normal of the current fragment.
	 */
	virtual vector3_type const& normal() const = 0;
	
	/**
	 * Get Color.
	 *
	 * @return   The current vertex color of the fragment.
	 */
	virtual vector3_type const& color() const = 0;

	/**
	 * Rasterization Finished Query.
	 *
	 * @return   If the current triangle that is being rasterized has more fragments
	 then the return value is true otherwise it is false.
	*/
	virtual bool more_fragments() const = 0;

	/**
	 * This method will ask the rastersizer to rasterize the next fragment.
	 */
	virtual void next_fragment() = 0;
    };

}// end namespace graphics

// GRAPHICS_RASTERIZER_H
#endif
