#ifndef RM_QUATERNION_H
#define RM_QUATERNION_H
// [[$Id: quaternion.nw,v 1.1.1.1 2005/08/10 12:02:10 kaiip Exp $]]

#include <matrix/typename.h>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <matrix/real.h>
#include <matrix/vector.h>
#include <matrix/matrix.h>

template<typename Type>
class Quaternion {
public:
    Quaternion();
    Quaternion(Type const& Scalar, Type const& Xvec, Type const& Yvec, Type const& Zvec);
    Quaternion(Type const& Scalar, Vector<Type,3> const& Vec);
    Quaternion(Type const& Scalar);
    Quaternion(Vector<Type,3> const& Vec);
    Quaternion(Quaternion<Type> const& Quat);
    virtual ~Quaternion();
    void Clear();
    void Put(std::ostream& s, int width = 0) const;
    void Get(std::istream& s);
    Type& Value(unsigned int const Index);
    Type const& Value(unsigned int const Index) const;
    Type const& ScalarPart() const;
    Type  ScalarPart(Type const& NewValue);
    Vector<Type,3> const& VectorPart() const;
    Vector<Type,3> VectorPart(Type const& Xnew, Type const& Ynew, Type const& Znew);
    Vector<Type,3> VectorPart(Vector<Type,3> const& NewValue);
    Quaternion<Type> C() const;
    Real Norm() const;
    Quaternion<Type> I() const;
    Quaternion<Type> const& operator=(Quaternion<Type> const& Src);
    Type& operator[](unsigned int const Index);
    Type const& operator[](unsigned int const Index) const;
    bool const operator==(Quaternion<Type> const& Src) const;
    bool const operator!=(Quaternion<Type> const& Src) const;
    Quaternion<Type> const& operator+() const;
    Quaternion<Type> operator+(Quaternion<Type> const& Src) const;
    Quaternion<Type> const& operator+=(Quaternion<Type> const& Src);
    Quaternion<Type> operator-() const;
    Quaternion<Type> operator-(Quaternion<Type> const& Src) const;
    Quaternion<Type> const& operator-=(Quaternion<Type> const& Src);
    Quaternion<Type> operator*(Type const& Factor) const;
    Quaternion<Type> const& operator*=(Type const& Factor);
    Quaternion<Type> operator*(Quaternion<Type> const& Src) const;
    Quaternion<Type> const& operator*=(Quaternion<Type> const& Src);
    Quaternion<Type> operator/(Type const& Factor) const;
    Quaternion<Type> const& operator/=(Type const& Factor);
    Quaternion<Type> operator/(Quaternion<Type> const& Src) const;
    Quaternion<Type> const& operator/=(Quaternion<Type> const& Src);
protected:
    /* No Protected Members so far */
private:
    Type s;
    Vector<Type,3> v;
    Type const& DataItem(unsigned int const Index) const;
    /* No Friends of class Quaternion */
};

template<typename Type>
Quaternion<Type> Conjugate(Quaternion<Type> const& Quat);
template<typename Type>
Real Norm(Quaternion<Type> const& Quat);
template<typename Type>
Quaternion<Type> Inverse(Quaternion<Type> const& Quat);
template<typename Type>
Quaternion<Type> operator*(Type const& Factor, Quaternion<Type> const& Src);
template<typename Type>
std::ostream& operator<<(std::ostream& s, Quaternion<Type> const& Src);
template<typename Type>
std::istream& operator>>(std::istream& s, Quaternion<Type>& Dest);

#ifdef INSTANTIATE
#include <matrix/quaternion.C>
#endif
#endif
