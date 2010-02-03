#ifndef EDGE_RASTERIZER_H
#define EDGE_RASTERIZER_H
//
// Graphics Framework.
// Copyright (C) 2010 Department of Computer Science, University of Copenhagen
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include "graphics/graphics.h"

namespace graphics {

    // Draws an edge from V1 to V2, or two edges - one from V1 to V2 and one from V2 to V3.
    // Edges are assumed NOT to be horizontal!
    template<typename math_types>
    class MyEdgeRasterizer
    {
    public:
    typedef typename math_types::real_type    real_type;
    typedef typename math_types::vector3_type vector3_type;

    public:
    MyEdgeRasterizer() : valid(false)
    {
        std::cout << "MyEdgeRasterizer::MyEdgeRasterizer(): called" << std::endl;
    }

    virtual ~MyEdgeRasterizer()
    {}

    void init(vector3_type const& in_vertex1,
          vector3_type const& in_normal1,
          vector3_type const& in_color1,
          vector3_type const& in_vertex2,
          vector3_type const& in_normal2,
          vector3_type const& in_color2)
        {
        // Save the original parameters

        std::cout << "edge_rasterizer::init(...) - One Edge" << std::endl;

        // There is only one edge

        this->valid = true;
        }
    
    void init(vector3_type const& in_vertex1,
          vector3_type const& in_normal1,
          vector3_type const& in_color1,
          vector3_type const& in_vertex2,
          vector3_type const& in_normal2,
          vector3_type const& in_color2,
          vector3_type const& in_vertex3,
          vector3_type const& in_normal3,
          vector3_type const& in_color3)
        {
        // Save the original parameters

        std::cout << "edge_rasterizer::init(...) - Two Edges" << std::endl;

        // There are two edges

        this->valid = true;
        }
    

    int x() const
    {
        if (!this->valid) {
        throw std::runtime_error("MyEdgeRasterizer::x():Invalid State/Not Initialized");
            }
        return 0;
    }

    int y() const
    {
        if (!this->valid) {
        throw std::runtime_error("MyEdgeRasterizer::y():Invalid State/Not Initialized");
            }
        return 0;
    }

    real_type depth() const
    {
        if (!this->valid) {
        throw std::runtime_error("MyEdgeRasterizer::depth():Invalid State/Not Initialized");
            }
        return 0;
    }

    vector3_type position() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyEdgeRasterizer::position():Invalid State/Not Initialized");
            }
            return vector3_type(this->x(), this->y(), this->depth());
        }

    vector3_type normal() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyEdgeRasterizer::normal():Invalid State/Not Initialized");
            }
            return vector3_type(0.0, 0.0, 0.0);
        }

    vector3_type color() const
        {
            if (!this->valid) {
                throw std::runtime_error("MyEdgeRasterizer::color():Invalid State/Not Initialized");
            }
            return vector3_type(0.0, 0.0, 0.0);
        }

    void print_variables()
        {
        std::cout << "MyEdgeRasterizer: local variables" << std::endl;
        std::cout << "=================================" << std::endl;
        std::cout << std::endl;
    }

    bool more_fragments() const
    {
        // Implement the real version
        return false;
    }

    void next_fragment()
        {
        // Implement the real version
    }

    protected:

    private:
    void initialize_current_edge(int start_index, int stop_index)
    {
        // Ensure that the edge has its first vertex lower than the second one

        // Implement the real version
    }

    bool valid;
    };

}// end namespace graphics

// EDGE_RASTERIZER_H
#endif
