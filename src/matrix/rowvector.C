//char RowVectorVersion[] = 
//     "$Id: rowvector.nw,v 1.1 2005/08/10 13:01:42 kaiip Exp $";

#include <stdexcept>
#include <cstdarg>
#include <sstream>
#include <string>
#include <typeinfo>
#include <cctype>
#include <matrix/trace.h>
#include <matrix/rowvector.h>

template<typename Type, unsigned int N>
RowVector<Type,N>::RowVector()
{
    Trace("RowVector<Type,N>", "RowVector()");
}
template<typename Type, unsigned int N>
RowVector<Type,N>::RowVector(Type const X) : Vector<Type,N>(X)
{
    Trace("RowVector<Type,N>", "RowVector(Type)");

    this->Clear();
    if (this->Dimension() >= 1) {
        this->Value(1) = X;
    }   
}
template<typename Type, unsigned int N>
RowVector<Type,N>::RowVector(Type const X, Type const Y) : Vector<Type,N>(X, Y)
{
    Trace("RowVector<Type,N>", "RowVector(Type, Type)");

    this->Clear();
    switch (N) {
    case 1:
        this->Value(1) = X;
        break;
    default:
        this->Value(1) = X;
        this->Value(2) = Y;
    }
}
template<typename Type, unsigned int N>
RowVector<Type,N>::RowVector(Type const X, Type const Y, Type const Z)
                 : Vector<Type,N>(X, Y, Z)
{
    Trace("RowVector<Type,N>", "RowVector(Type, Type, Type)");

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
}
template<typename Type, unsigned int N>
RowVector<Type,N>::RowVector(Type const X, Type const Y, Type const Z, Type const W)
                 : Vector<Type,N>(X, Y, Z, W)
{
    Trace("Vector<Type,N>", "Vector(Type, Type, Type, Type)");

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
}
#ifdef PARAM
template<typename Type, unsigned int N>
RowVector<Type,N>::RowVector(Type const FirstValue ...)
{
    Trace("RowVector<Type,N>", "RowVector(Type ...)");

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
RowVector<Type,N>::RowVector(RowVector<Type,N> const& Src) : Vector<Type,N>(Src)
{
    Trace("RowVector<Type,N>", "RowVector(RowVector&");
}
template<typename Type, unsigned int N>
RowVector<Type,N>::~RowVector()
{
    Trace("RowVector<Type,N>", "~RowVector()");
}
template<typename Type, unsigned int N>
ColumnVector<Type,N> RowVector<Type,N>::T() const
{
    Trace("RowVector<Type,N>", "T()");

    ColumnVector<Type,N> Result;
    for (unsigned int i = 1; i <= N; ++i) Result.Value(i) = this->Value(i);
    return Result;
}
template<typename Type, unsigned int N>
RowVector<Type,N> const& 
RowVector<Type,N>::operator=(RowVector<Type,N> const& Src)
{
    Trace("RowVector<Type,N>", "operator=(RowVector&)");

    if (this != &Src) {
        this->Vector<Type,N>::operator=(Src);
    }
    return *this;
}
template<typename Type, unsigned int N>
RowVector<Type,N> const& RowVector<Type,N>::operator+() const
{
    Trace("RowVector<Type,N>", "operator+()");

    return *this;
}
template<typename Type, unsigned int N>
RowVector<Type,N> RowVector<Type,N>::operator+(RowVector<Type,N> const& Src) const
{
    Trace("RowVector<Type,N>", "operator+(RowVector<Type,N>&)");

    RowVector<Type,N> tmp(*this);
    return tmp += Src;
}
template<typename Type, unsigned int N>
RowVector<Type,N> const& 
RowVector<Type,N>::operator+=(RowVector<Type,N> const& Src)
{
    Trace("RowVector<Type,N>", "operator+=(RowVector<Type,N>&)");

    this->Vector<Type,N>::operator+=(Src);
    return *this;
}
template<typename Type, unsigned int N>
RowVector<Type,N> RowVector<Type,N>::operator-() const
{
    Trace("RowVector<Type,N>", "operator-()");

    RowVector<Type,N> tmp;
    return tmp -= *this;
}
template<typename Type, unsigned int N>
RowVector<Type,N> 
RowVector<Type,N>::operator-(RowVector<Type,N> const& Src) const
{
    Trace("RowVector<Type,N>", "operator-(RowVector<Type,N>&)");

    RowVector<Type,N> tmp(*this);
    return tmp -= Src;
}
template<typename Type, unsigned int N>
RowVector<Type,N> const& 
RowVector<Type,N>::operator-=(RowVector<Type,N> const& Src)
{
    Trace("RowVector<Type,N>", "operator-=(RowVector<Type,N>&)");

    this->Vector<Type,N>::operator-=(Src);
    return *this;
}
template<typename Type, unsigned int N>
RowVector<Type,N> RowVector<Type,N>::operator*(Type const& Factor) const
{
    Trace("RowVector<Type,N>", "operator*(Type&)");

    RowVector<Type,N> tmp(*this);
    return tmp *= Factor;
}
template<typename Type, unsigned int N>
RowVector<Type,N> const& RowVector<Type,N>::operator*=(Type const& Factor)
{
    Trace("RowVector<Type,N>", "operator*=(Type&)");

    this->Vector<Type,N>::operator*=(Factor);
    return *this;
}
template<typename Type, unsigned int N>
Type RowVector<Type,N>::operator*(RowVector<Type,N> const& Src) const
{
    Trace("RowVector<Type,N>", "operator*(RowVector<Type,N>&)");

    Type sum = Type();
    for (unsigned int i = 1; i <= N; ++i) sum += (this->Value(i) * Src.Value(i));

    return sum;
}
template<typename Type, unsigned int N>
RowVector<Type,N> RowVector<Type,N>::operator/(Type const& Factor) const
{
    Trace("RowVector<Type,N>", "operator/(Type&)");

    RowVector<Type,N> tmp(*this);
    return tmp /= Factor;
}
template<typename Type, unsigned int N>
RowVector<Type,N> const& RowVector<Type,N>::operator/=(Type const& Factor)
{
    Trace("RowVector<Type,N>", "operator/=(Type&)");
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
Type Norm(RowVector<Type,N> const& Vec, unsigned int const p)
#else
template<typename Type, unsigned int N>
Real Norm(RowVector<Type,N> const& Vec, unsigned int const p)
#endif
{
    Trace("", "Norm(RowVector<Type,N>&, unsigned int)");

    return Vec.Norm(p);
}
template<typename Type, unsigned int N>
Type Dot(RowVector<Type,N> const& Vec1, RowVector<Type,N> const& Vec2)
{
    Trace("", "Dot(RowVector, RowVector)");

    return Vec1 * Vec2;
}
template<typename Type>
RowVector<Type,3> Cross(RowVector<Type,3> const& Vec1,
                        RowVector<Type,3> const& Vec2)
{
    Trace("", "Cross(RowVector, RowVector");

    RowVector<Type,3> Vec;
    
    Vec[1] = Vec1[2] * Vec2[3] - Vec1[3] * Vec2[2];
    Vec[2] = Vec1[3] * Vec2[1] - Vec1[1] * Vec2[3];
    Vec[3] = Vec1[1] * Vec2[2] - Vec1[2] * Vec2[1];

    return Vec;
}
template<typename Type, unsigned int N>
ColumnVector<Type,N> Transpose(RowVector<Type,N> const& Vec)
{
    Trace("", "Transpose(RowVector&)");

    ColumnVector<Type,N> transpose;
    for (int i = 1; i <= N; ++i) {
        transpose[i] = Vec[i];
    }
    return transpose;
}
template<typename Type, unsigned int N>
RowVector<Type,N> operator*(Type const& Factor, RowVector<Type,N> const& Src)
{
    Trace("RowVector<Type,N>", "operator*(Type&, RowVector<Type,N>&)");

    return Src * Factor;
}
