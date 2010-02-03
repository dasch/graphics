#ifndef COLOR_H
#defing COLOR_H

#include <iostream>
#include <iomanip>

#include "solution/math_types.h"

namespace graphics {

/*******************************************************************\
*                                                                   *
*                             C o l o r                             *
*                                                                   *
\*******************************************************************/

    template <typename math_types>
    class Color {
    public:
    typedef math_types::real_type    real_type;
    typedef math_types::vector3_type vector3_type;

    public:

/*******************************************************************\
*                                                                   *
*                           C o l o r ( )                           *
*                                                                   *
\*******************************************************************/

    Color()
    {}

/*******************************************************************\
*                                                                   *
*                          ~ C o l o r ( )                          *
*                                                                   *
\*******************************************************************/

    virtual ~Color()
    {}

/*******************************************************************\
*                                                                   *
*                         i n i t ( . . . )                         *
*                                                                   *
\*******************************************************************/

    void init(real_type ka, vector3_type Oa,
              real_type kd, vector3_type Od,
              real_type ks, vector3_type Os,
              int shininess)
    {
        // Initialize the state of a color
    }

/*******************************************************************\
*                                                                   *
*                   A m b i e n t C o l o r ( )                     *
*                                                                   *
\*******************************************************************/

    vector3_type AmbientColor()
    {
        // Return the ambient color
        return this->dummy_color;
    }

/*******************************************************************\
*                                                                   *
*                    D i f f u s e C o l o r ( )                    *
*                                                                   *
\*******************************************************************/

    vector3_type DiffuseColor()
    {
        // Return the diffuse color
        return this->dummy_color;
    }

/*******************************************************************\
*                                                                   *
*                   S p e c u l a r C o l o r ( )                   *
*                                                                   *
\*******************************************************************/

    vector3_type SpecularColor()
    {
        // Return the specular color
        return this->dummy_color;
    }

/*******************************************************************\
*                                                                   *
*                       S h i n i n e s s ( )                       *
*                                                                   *
\*******************************************************************/

    int Shininess()
    {
        // return the shininess
        return 1;
    }


    protected:

/*******************************************************************\
*                                                                   *
*                 P r i v a t e   V a r i a b l e s                 *
*                                                                   *
\*******************************************************************/

    private:
    real_type    dummy_k;
    vector3_type dummy_color;
    };
}

#endif
