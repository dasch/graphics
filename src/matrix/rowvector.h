#ifndef RM_ROWVECTOR_H
#define RM_ROWVECTOR_H
// [[$Id: rowvector.nw,v 1.1 2005/08/10 13:01:42 kaiip Exp $]]

#include <iostream>
#include <iomanip>
#include <matrix/vector.h>

#ifndef RM_COLUMNVECTOR_H
template<typename Type, unsigned int N> class RowVector;
#include <matrix/columnvector.h>
#endif

template<typename Type, unsigned int N>
class RowVector : public Vector<Type,N> {
public:
    RowVector();
    RowVector(Type const X);
    RowVector(Type const X, Type const Y);
    RowVector(Type const X, Type const Y, Type const Z);
    RowVector(Type const X, Type const Y, Type const Z, Type const W);
    #ifdef PARAM
    RowVector(Type const FirstValue ...);
    #endif
    RowVector(RowVector<Type,N> const& Src);
    virtual ~RowVector();
    ColumnVector<Type,N> T() const;
    RowVector<Type,N> const& operator=(RowVector<Type,N> const& Src);
    RowVector<Type,N> const& operator+() const;
    RowVector<Type,N> operator+(RowVector<Type,N> const& Src) const;
    RowVector<Type,N> const& operator+=(RowVector<Type,N> const& Src);
    RowVector<Type,N> operator-() const;
    RowVector<Type,N> operator-(RowVector<Type,N> const& Src) const;
    RowVector<Type,N> const& operator-=(RowVector<Type,N> const& Src);
    RowVector<Type,N> operator*(Type const& Factor) const;
    RowVector<Type,N> const& operator*=(Type const& Factor);
    Type operator*(RowVector<Type,N> const& Src) const;
    RowVector<Type,N> operator/(Type const& Factor) const;
    RowVector<Type,N> const& operator/=(Type const& Factor);
protected:
    /* No Protected Members so far */
private:
    /* No Private Variables */
    /* No Private Member Functions */
    /* class something; */
};

#if 0
template<typename Type, unsigned int N>
Type Norm(RowVector<Type,N> const& Vec, unsigned int const p = 2);
#else
template<typename Type, unsigned int N>
Real Norm(RowVector<Type,N> const& Vec, unsigned int const p = 2);
#endif
template<typename Type, unsigned int N>
Type Dot(RowVector<Type,N> const& Vec1, RowVector<Type,N> const& Vec2);
template<typename Type>
RowVector<Type,3> Cross(RowVector<Type,3> const& Vec1,
                        RowVector<Type,3> const& Vec2);
template<typename Type, unsigned int N>
RowVector<Type,N> operator*(Type const& Factor, RowVector<Type,N> const& Src);

#ifdef INSTANTIATE
#include <matrix/rowvector.C>
#endif
#endif
