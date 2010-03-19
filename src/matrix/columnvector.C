//char ColumnVectorVersion[] = 
//     "$Id: columnvector.nw,v 1.1 2005/08/10 12:57:15 kaiip Exp $";

#include <stdexcept>
#include <cstdarg>
#include <sstream>
#include <string>
#include <typeinfo>
#include <cctype>
#include <matrix/trace.h>
#include <matrix/columnvector.h>

template<typename Type, unsigned int N>
ColumnVector<Type,N>::ColumnVector()
{
    Trace("ColumnVector<Type,N>", "ColumnVector()");
}
template<typename Type, unsigned int N>
ColumnVector<Type,N>::ColumnVector(Type const X) : Vector<Type,N>(X)
{
    Trace("ColumnVector<Type,N>", "ColumnVector(Type)");
#if 0
    this->Clear();
    if (this->Dimension() >= 1) {
        this->Value(1) = X;
    }
#endif   
}
template<typename Type, unsigned int N>
ColumnVector<Type,N>::ColumnVector(Type const X, Type const Y) : Vector<Type,N>(X, Y)
{
    Trace("ColumnVector<Type,N>", "ColumnVector(Type, Type)");
#if 0
    this->Clear();
    switch (N) {
    case 1:
        this->Value(1) = X;
        break;
    default:
        this->Value(1) = X;
        this->Value(2) = Y;
    }
#endif
}
template<typename Type, unsigned int N>
ColumnVector<Type,N>::ColumnVector(Type const X, Type const Y, Type const Z)
                    : Vector<Type,N>(X, Y, Z)
{
    Trace("ColumnVector<Type,N>", "ColumnVector(Type, Type, Type)");
#if 0
    this->Clear();
    switch (N) {
    case 1:
        this->Value(1) = X;
        break;
    case 2:
        this->Value(1) = X;
        this->Value(2) = Y;
        break;
    default:
        this->Value(1) = X;
        this->Value(2) = Y;
        this->Value(3) = Z;
    }
#endif
}
template<typename Type, unsigned int N>
ColumnVector<Type,N>::ColumnVector(Type const X, Type const Y, Type const Z, Type const W)
                    : Vector<Type,N>(X, Y, Z, W)
{
    Trace("ColumnVector<Type,N>", "ColumnVector(Type, Type, Type, Type)");
#if 0
    this->Clear();
    switch (N) {
    case 1:
        this->Value(1) = X;
        break;
    case 2:
        this->Value(1) = X;
        this->Value(2) = Y;
        break;
    case 3:
        this->Value(1) = X;
        this->Value(2) = Y;
        this->Value(3) = Z;
    default:
        this->Value(1) = X;
        this->Value(2) = Y;
        this->Value(3) = Z;
        this->Value(4) = W;
    }
#endif
}
#ifdef PARAM
template<typename Type, unsigned int N>
ColumnVector<Type,N>::ColumnVector(Type const FirstValue ...)
{
    Trace("ColumnVector<Type,N>", "ColumnVector(Type ...)");

    va_list parameterlist;
    va_start(parameterlist, FirstValue);
        this->Value(1) = FirstValue;
        for (unsigned int index = 2; index <= N; ++index) {
            this->Value(index) = va_arg(parameterlist, Type const);
        }
    va_end(parameterlist);
}
#endif
template<typename Type, unsigned int N>
ColumnVector<Type,N>::ColumnVector(ColumnVector<Type,N> const& Src) : Vector<Type,N>(Src)
{
    Trace("ColumnVector<Type,N>", "ColumnVector(ColumnVector&");
}
template<typename Type, unsigned int N>
ColumnVector<Type,N>::~ColumnVector()
{
    Trace("ColumnVector<Type,N>", "~ColumnVector()");
}
#if 1
template<typename Type, unsigned int N>
RowVector<Type,N> ColumnVector<Type,N>::T() const
{
    Trace("ColumnVector<Type,N>", "T()");

    RowVector<Type,N> Result;
    for (unsigned int i = 1; i <= N; ++i) Result.Value(i) = this->Value(i);
    return Result;
}
#endif
template<typename Type, unsigned int N>
ColumnVector<Type,N> const& 
ColumnVector<Type,N>::operator=(ColumnVector<Type,N> const& Src)
{
    Trace("ColumnVector<Type,N>", "operator=(ColumnVector&)");

    if (this != &Src) {
        this->Vector<Type,N>::operator=(Src);
    }
    return *this;
}
template<typename Type, unsigned int N>
ColumnVector<Type,N> const& ColumnVector<Type,N>::operator+() const
{
    Trace("ColumnVector<Type,N>", "operator+()");

    return *this;
}
template<typename Type, unsigned int N>
ColumnVector<Type,N> ColumnVector<Type,N>::operator+(ColumnVector<Type,N> const& Src) const
{
    Trace("ColumnVector<Type,N>", "operator+(ColumnVector<Type,N>&)");

    ColumnVector<Type,N> tmp(*this);
    return tmp += Src;
}
template<typename Type, unsigned int N>
ColumnVector<Type,N> const& 
ColumnVector<Type,N>::operator+=(ColumnVector<Type,N> const& Src)
{
    Trace("ColumnVector<Type,N>", "operator+=(ColumnVector<Type,N>&)");

    this->Vector<Type,N>::operator+=(Src);
    return *this;
}
template<typename Type, unsigned int N>
ColumnVector<Type,N> ColumnVector<Type,N>::operator-() const
{
    Trace("ColumnVector<Type,N>", "operator-()");

    ColumnVector<Type,N> tmp;
    return tmp -= *this;
}
template<typename Type, unsigned int N>
ColumnVector<Type,N> 
ColumnVector<Type,N>::operator-(ColumnVector<Type,N> const& Src) const
{
    Trace("ColumnVector<Type,N>", "operator-(ColumnVector<Type,N>&)");

    ColumnVector<Type,N> tmp(*this);
    return tmp -= Src;
}
template<typename Type, unsigned int N>
ColumnVector<Type,N> const& 
ColumnVector<Type,N>::operator-=(ColumnVector<Type,N> const& Src)
{
    Trace("ColumnVector<Type,N>", "operator-=(ColumnVector<Type,N>&)");

    this->Vector<Type,N>::operator-=(Src);
    return *this;
}
template<typename Type, unsigned int N>
ColumnVector<Type,N> ColumnVector<Type,N>::operator*(Type const& Factor) const
{
    Trace("ColumnVector<Type,N>", "operator*(Type&)");

    ColumnVector<Type,N> tmp(*this);
    return tmp *= Factor;
}
template<typename Type, unsigned int N>
ColumnVector<Type,N> const& ColumnVector<Type,N>::operator*=(Type const& Factor)
{
    Trace("ColumnVector<Type,N>", "operator*=(Type&)");

    this->Vector<Type,N>::operator*=(Factor);
    return *this;
}
template<typename Type, unsigned int N>
Type ColumnVector<Type,N>::operator*(ColumnVector<Type,N> const& Vec) const
{
    Trace("ColumnVector<Type,N>", "operator*(ColumnVector<Type,N>&)");

    Type dotproduct = Type();
    for (unsigned int i = 1; i <= N; ++i) {
        dotproduct += this->Value(i) * Vec[i];
    }
    return dotproduct;
}
template<typename Type, unsigned int N>
ColumnVector<Type,N> ColumnVector<Type,N>::operator/(Type const& Factor) const
{
    Trace("ColumnVector<Type,N>", "operator/(Type&)");

    ColumnVector<Type,N> tmp(*this);
    return tmp /= Factor;
}
template<typename Type, unsigned int N>
ColumnVector<Type,N> const& ColumnVector<Type,N>::operator/=(Type const& Factor)
{
    Trace("ColumnVector<Type,N>", "operator/=(Type&)");
#if 0
    if (Factor == Type()) {
        ostrstream errormessage;
        errormessage << "file " << __FILE__ << ": line " << __LINE__ << ':' 
                     << endl;
        errormessage << "    " << typeid(*this).name() 
                     << "::operator/=(Type&): " << endl;
        errormessage << "    Factor = " << Factor
                     << ". Illegal to divide by " << typeid(Type).name() 
                     << ": " << Type() << ends;
        throw invalid_argument(errormessage.str());
    }
#endif
    this->Vector<Type,N>::operator/=(Factor);
    return *this;
}
#if 0
template<typename Type, unsigned int N>
Type Norm(ColumnVector<Type,N> const& Vec, unsigned int const p)
#else
template<typename Type, unsigned int N>
Real Norm(ColumnVector<Type,N> const& Vec, unsigned int const p)
#endif
{
    Trace("", "Norm(ColumnVector<Type,N>&, unsigned int)");

    return Vec.Norm(p);
}
template<typename Type, unsigned int N>
Type Dot(ColumnVector<Type,N> const& Vec1, ColumnVector<Type,N> const& Vec2)
{
    Trace("", "Dot(ColumnVector, ColumnVector)");

    return Vec1 * Vec2;
}
template<typename Type>
ColumnVector<Type,3> Cross(ColumnVector<Type,3> const& Vec1,
                           ColumnVector<Type,3> const& Vec2)
{
    Trace("", "Cross(ColumnVector, ColumnVector");

    ColumnVector<Type,3> Vec;
    
    Vec[1] = Vec1[2] * Vec2[3] - Vec1[3] * Vec2[2];
    Vec[2] = Vec1[3] * Vec2[1] - Vec1[1] * Vec2[3];
    Vec[3] = Vec1[1] * Vec2[2] - Vec1[2] * Vec2[1];

    return Vec;
}
template<typename Type, unsigned int N>
RowVector<Type,N> Transpose(ColumnVector<Type,N> const& Vec)
{
    Trace("", "Transpose(ColumnVector&)");

    RowVector<Type,N> transpose;
    for (int i = 1; i <= N; ++i) {
        transpose[i] = Vec[i];
    }
    return transpose;
}
template<typename Type, unsigned int N>
ColumnVector<Type,N> operator*(Type const& Factor, ColumnVector<Type,N> const& Src)
{
    Trace("ColumnVector<Type,N>", "operator*(Type&, ColumnVector<Type,N>&)");

    return Src * Factor;
}
