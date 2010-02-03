#ifndef RM_REAL_H
#define RM_REAL_H
// [[$Id: nreal.h,v 1.1.1.1 2005/08/10 12:02:09 kaiip Exp $]]

#include <cctype>
#include <matrix/trace.h>

#define REAL_IS_DOUBLE

#ifdef REAL_IS_FLOAT
typedef float Real;
#endif

#ifdef REAL_IS_DOUBLE
typedef double Real;
#endif

#ifdef REAL_IS_LONG_DOUBLE
typedef long double Real;
#endif

Real Norm(Real const& x, unsigned int const p = 2)
{
    Trace("", "Norm(Real&, unsigned int)");

    return x < Real() ? -x : x;
}

#endif
