#ifndef MATH_TYPES_H
#define MATH_TYPES_H
//
// Graphics Framework.
// Copyright (C) 2007 Department of Computer Science, University of Copenhagen
//

#define INSTANTIATE
#  include <matrix/matrix.h>
#undef INSTANTIATE

namespace graphics {

  class MyMathTypes
  {
  public:
    typedef float                       real_type;
    typedef ColumnVector<real_type,2>   vector2_type;
    typedef ColumnVector<real_type,3>   vector3_type;
    typedef ColumnVector<real_type,4>   vector4_type;
    typedef Matrix<real_type, 4, 4>     matrix4x4_type;
  };



}// end namespace graphics

// MATH_TYPES_H
#endif
