#ifndef TRIANGLE_H
#define TRIANGLE_H

using namespace graphics;

typedef MyMathTypes::vector3_type vertex_t;

namespace graphics
{
    /**
     * Represents a triangle in space.
     */
    class Triangle
    {
    private:
        vertex_t _v1, _v2, _v3;

    public:
        Triangle(vertex_t const &v1, vertex_t const &v2, vertex_t const &v3)
        {
            _v1 = v1;
            _v2 = v2;
            _v3 = v3;
        }

        vertex_t const& v1()
        {
            return _v1;
        }

        vertex_t const& v2()
        {
            return _v2;
        }

        vertex_t const& v3()
        {
            return _v3;
        }
    };
}

#endif
