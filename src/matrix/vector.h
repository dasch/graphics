#ifndef RM_VECTOR_H
#define RM_VECTOR_H
// [[$Id: vector.nw,v 1.1 2005/08/10 13:02:46 kaiip Exp $]]

//#define PARAM

//#include <matrix/typename.h>
#include <iostream>
#include <iomanip>
#include <cctype>    // was #include <sys/types.h>
#include <matrix/real.h>

template<typename Type, unsigned int N>
class Vector {
public:

  typedef Type value_type;

    Vector();
    Vector(Type const X);
    Vector(Type const X, Type const Y);
    Vector(Type const X, Type const Y, Type const Z);
    Vector(Type const X, Type const Y, Type const Z, Type const W);
    #ifdef PARAM
    Vector(Type const FirstValue ...);
    #endif
    Vector(Vector<Type,N> const& Src);
    virtual ~Vector();
    unsigned int const Dimension() const;
    void Clear();
    void Put(std::ostream& s, int width = 0) const;
    void Get(std::istream& s);
    Type& Value(unsigned int const Index);
    Type const& Value(unsigned int const Index) const;
    Real Norm(unsigned int const p = 2) const;
    Vector<Type,N> const& operator=(Vector<Type,N> const& Src);
    Type& operator[](unsigned int const Index);
    Type const& operator[](unsigned int const Index) const;
    bool const operator==(Vector<Type,N> const& Src) const;
    bool const operator!=(Vector<Type,N> const& Src) const;
    Vector<Type,N> const& operator+() const;
    Vector<Type,N> operator+(Vector<Type,N> const& Src) const;
    Vector<Type,N> const& operator+=(Vector<Type,N> const& Src);
    Vector<Type,N> operator-() const;
    Vector<Type,N> operator-(Vector<Type,N> const& Src) const;
    Vector<Type,N> const& operator-=(Vector<Type,N> const& Src);
    Vector<Type,N> operator*(Type const& Factor) const;
    Vector<Type,N> const& operator*=(Type const& Factor);
    Type operator*(Vector<Type,N> const& Src) const;
    Vector<Type,N> operator/(Type const& Factor) const;
    Vector<Type,N> const& operator/=(Type const& Factor);
protected:
    /* No Protected Members so far */
private:
    Type data[N];
    Type const& DataItem(unsigned int const Index) const;
    /* No Friends of class Vector */
};

template<typename Type, unsigned int N>
Real Norm(Vector<Type,N> const& Vec, unsigned int const p = 2);
template<typename Type, unsigned int N>
Type Dot(Vector<Type,N> const& Vec1, Vector<Type,N> const& Vec2);
template<typename Type>
Vector<Type,3> Cross(Vector<Type,3> const& Vec1, Vector<Type,3> const& Vec2);
template<typename Type, unsigned int N>
Vector<Type,N> operator*(Type const& Factor, Vector<Type,N> const& Src);
template<typename Type>
Vector<Type,3> operator^(Vector<Type,3> const& Vec1, Vector<Type,3> const& Vec2);
template<typename Type, unsigned int N>
std::ostream& operator<<(std::ostream& s, Vector<Type,N> const& Src);
template<typename Type, unsigned int N>
std::istream& operator>>(std::istream& s, Vector<Type,N>& Dest);

#ifdef INSTANTIATE
#include <matrix/vector.C>
#endif
#endif
