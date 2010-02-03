#ifndef RM_COLUMNVECTOR_H
#define RM_COLUMNVECTOR_H
// [[$Id: columnvector.nw,v 1.1 2005/08/10 12:57:15 kaiip Exp $]]

#include <iostream>
#include <iomanip>
#include <matrix/vector.h>

#ifndef RM_ROWVECTOR_H
template<typename Type, unsigned int N> class ColumnVector;
#include <matrix/rowvector.h>
#endif

template<typename Type, unsigned int N>
class ColumnVector : public Vector<Type,N> {
public:
    ColumnVector();
    ColumnVector(Type const X);
    ColumnVector(Type const X, Type const Y);
    ColumnVector(Type const X, Type const Y, Type const Z);
    ColumnVector(Type const X, Type const Y, Type const Z, Type const W);
    #ifdef PARAM
    ColumnVector(Type const FirstValue ...);
    #endif
    ColumnVector(ColumnVector<Type,N> const& Src);
    virtual ~ColumnVector();
    RowVector<Type,N> T() const;
    ColumnVector<Type,N> const& operator=(ColumnVector<Type,N> const& Src);
    ColumnVector<Type,N> const& operator+() const;
    ColumnVector<Type,N> operator+(ColumnVector<Type,N> const& Src) const;
    ColumnVector<Type,N> const& operator+=(ColumnVector<Type,N> const& Src);
    ColumnVector<Type,N> operator-() const;
    ColumnVector<Type,N> operator-(ColumnVector<Type,N> const& Src) const;
    ColumnVector<Type,N> const& operator-=(ColumnVector<Type,N> const& Src);
    ColumnVector<Type,N> operator*(Type const& Factor) const;
    ColumnVector<Type,N> const& operator*=(Type const& Factor);
    Type operator*(ColumnVector<Type,N> const& Vec) const;
    ColumnVector<Type,N> operator/(Type const& Factor) const;
    ColumnVector<Type,N> const& operator/=(Type const& Factor);
protected:
    /* No Protected Members so far */
private:
    /* No Private Variables */
    /* No Private Member Functions */
    /* class something; */
};

#if 0
template<typename Type, unsigned int N>
Type Norm(ColumnVector<Type,N> const& Vec, unsigned int const p = 2);
#else
template<typename Type, unsigned int N>
Real Norm(ColumnVector<Type,N> const& Vec, unsigned int const p = 2);
#endif
template<typename Type, unsigned int N>
Type Dot(ColumnVector<Type,N> const& Vec1, ColumnVector<Type,N> const& Vec2);
template<typename Type>
ColumnVector<Type,3> Cross(ColumnVector<Type,3> const& Vec1,
                           ColumnVector<Type,3> const& Vec2);
template<typename Type, unsigned int N>
ColumnVector<Type,N> operator*(Type const& Factor, ColumnVector<Type,N> const& Src);

#ifdef INSTANTIATE
#include <matrix/columnvector.C>
#endif
#endif
