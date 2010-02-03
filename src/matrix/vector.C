#ifndef RM_VECTOR_C
#define RM_VECTOR_C

static char VectorVersion[] = 
     "$Id: vector.nw,v 1.1 2005/08/10 13:02:46 kaiip Exp $";

#include <new> // test for exception badalloc
#include <stdexcept>
#include <cstdarg>
#include <sstream>
#include <fstream>
#include <string>
#include <typeinfo>
#include <cctype>
#include <cmath>
#include <matrix/trace.h>
#include <matrix/typename.h>
#include <matrix/vector.h>

template<typename Type, unsigned int N>
Vector<Type,N>::Vector()
{
    Trace("Vector<Type,N>", "Vector()");

    this->Clear();
}
template<typename Type, unsigned int N>
Vector<Type,N>::Vector(Type const X)
{
    Trace("Vector<Type,N>", "Vector(Type)");

    this->Clear();
    if (this->Dimension() >= 1) {
        this->Value(1) = X;
    }   
}
template<typename Type, unsigned int N>
Vector<Type,N>::Vector(Type const X, Type const Y)
{
    Trace("Vector<Type,N>", "Vector(Type, Type)");

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
Vector<Type,N>::Vector(Type const X, Type const Y, Type const Z)
{
    Trace("Vector<Type,N>", "Vector(Type, Type, Type)");

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
Vector<Type,N>::Vector(Type const X, Type const Y, Type const Z, Type const W)
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
Vector<Type,N>::Vector(Type const FirstValue ...)
{
    Trace("Vector<Type,N>", "Vector(Type ...)");

    va_list parameterlist;
        va_start(parameterlist, FirstValue);
        this->Value(1) = FirstValue;
        for (unsigned int index = 2; index <= N; ++index) {
            this->Value(index) = Type(va_arg(parameterlist, Type const));
        }
    va_end(parameterlist);
}
#endif
#if 0
template<unsigned int N>
Vector<float,N>::Vector(double const FirstValue ...)
{
    Trace("Vector<float,N>", "Vector(float ...)");

    va_list parameterlist;
    va_start(parameterlist, FirstValue);
        this->Value(1) = float(FirstValue);
        for (unsigned int index = 2; index <= N; ++index) {
            this->Value(index) = static_cast<float>(va_arg(parameterlist, double const));
        }
    va_end(parameterlist);
}
#endif
template<typename Type, unsigned int N>
Vector<Type,N>::Vector(Vector<Type,N> const& Src)
{
    Trace("Vector<Type,N>", "Vector(Vector&");

    for (unsigned int i = 0; i < N; ++i) this->data[i] = Src.data[i];
}
template<typename Type, unsigned int N>
Vector<Type,N>::~Vector()
{
    Trace("Vector<Type,N>", "~Vector()");
}
template<typename Type, unsigned int N>
unsigned int const Vector<Type,N>::Dimension() const
{
    Trace("Vector<Type,N>", "Dimension()");

    return N;
}
template<typename Type, unsigned int N>
void Vector<Type,N>::Clear()
{
    Trace("Vector<Type,N>", "Clear()");

    Type value = Type();
    for (unsigned int i = 0; i < N; ++i) this->data[i] = value;
}
template<typename Type, unsigned int N>
void Vector<Type,N>::Put(std::ostream& s, int width) const
{
    Trace("Vector<Type,N>", "Put(ostream&, int)");

    unsigned int const last = N - 1;
    for (unsigned int i = 0; i < last; ++i) s << std::setw(width) << this->data[i] << ' ';
    s << std::setw(width) << this->data[last];
}
template<typename Type, unsigned int N>
void Vector<Type,N>::Get(std::istream& s)
{
    Trace("Vector<Type,N>", "Get(istream&)");

    for (unsigned int i = 0; i < N; ++i) {
        s >> this->data[i];
        TraceMessage("Value read: " << this->data[i] << endl);
        if (!s) {
            std::ostringstream errormessage;
            errormessage << "file " << __FILE__ << ": line " << __LINE__ << ':' << std::endl;
#if 0
            errormessage << "    " << typeid(*this).name() << "::Get(istream&): ";
#else
            errormessage << "    " << TypeName(typeid(*this).name()) << "::Get(istream&): "
                         << std::endl;
            errormessage << "    " << TypeName(*this) << "::Get(istream&): ";
#endif
            if (s.eof()) {
                errormessage<< "End of File" << std::ends;
                throw std::runtime_error(errormessage.str());
            }
            else {
                errormessage << "Bad Input" << std::ends;
                throw std::range_error(errormessage.str());
            }
        }
    }
}
template<typename Type, unsigned int N>
Type& Vector<Type,N>::Value(unsigned int const Index)
{
    Trace("Vector<Type,N>", "Value(unsigned int) --- non-const");
    TraceMessage("N == " << N << ", Index == " << Index << std::endl);
    return const_cast<Type&>(this->DataItem(Index));
}
template<typename Type, unsigned int N>
Type const& Vector<Type,N>::Value(unsigned int const Index) const
{
    Trace("Vector<Type,N>", "Value(unsigned int) --- const");
    TraceMessage("N == " << N << ", Index == " << Index << std::endl);
    return this->DataItem(Index);
}
template<typename Type, unsigned int N>
Real Vector<Type,N>::Norm(unsigned int const p) const
{
    Trace("Vector<Type,N>", "Norm(unsigned int)");

    unsigned int i;
    Real norm  = 0;
    Real value = 0;

    switch (p) {
    case 0:
        norm = ::Norm(this->DataItem(1), 0);
        for (i = 2; i <= N; ++i) {
            value = ::Norm(this->DataItem(i), 0);
            if (norm < value) norm = value;
        }
        break;
    case 1:
        norm = ::Norm(this->DataItem(1), 1);
        for (i = 2; i <= N; ++i) norm += ::Norm(this->DataItem(i), 1);
        break;
    case 2:
        for (i = 1; i <= N; ++i) {
            value = ::Norm(this->DataItem(i), 2);
            norm += (value * value);
        }
        norm = sqrt(norm);
        break;
    default:
#if 1
        for (i = 1; i <= N; ++i) {
            //norm += Pow(::Norm(this->DataItem(i), p), static_cast<int>(p));
            norm += pow(::Norm(this->DataItem(i), p), static_cast<Real>(p));
        }
        norm = pow(norm, 1.0 / static_cast<Real>(p));
        break;
#else
        {
            std::ostringstream errormessage;
            errormessage << "file " << __FILE__ << ": line " << __LINE__ << ':' << std::endl;
            errormessage << "    " << "Norm(unsigned int): " << std::endl;
            errormessage << "    The " << p << "-norm is not implemented" << std::ends;
            throw std::invalid_argument(errormessage.str());
        }
#endif
    }
    return norm;
}
template<typename Type, unsigned int N>
Vector<Type,N> const& Vector<Type,N>::operator=(Vector<Type,N> const& Src)
{
    Trace("Vector<Type,N>", "operator=(Vector&)");

    if (this != &Src) {
        for (unsigned int i = 0; i < N; ++i) this->data[i] = Src.data[i];
    }
    return *this;
}
template<typename Type, unsigned int N>
Type& Vector<Type,N>::operator[](unsigned int const Index)
{
    Trace("Vector<Type,N>", "operator[](unsigned int) --- non-const");

    return const_cast<Type&>(this->DataItem(Index));
}
template<typename Type, unsigned int N>
Type const& Vector<Type,N>::operator[](unsigned int const Index) const
{
    Trace("Vector<Type,N>", "operator[](unsigned int) --- const");

    return this->DataItem(Index);
}
template<typename Type, unsigned int N>
bool const Vector<Type,N>::operator==(Vector<Type,N> const& Src) const
{
    Trace("Vector<Type,N>", "operator==(Vector&)");

    if (this == &Src) return true;
    for (unsigned int i = 0; i < N; ++i) if (this->data[i] != Src.data[i]) return false;
    return true;
}
template<typename Type, unsigned int N>
bool const Vector<Type,N>::operator!=(Vector<Type,N> const& Src) const
{
    Trace("Vector<Type,N>", "operator!=(Vector&)");

    return !(*this == Src);
}
template<typename Type, unsigned int N>
Vector<Type,N> const& Vector<Type,N>::operator+() const
{
    Trace("Vector<Type,N>", "operator+()");

    return *this;
}
template<typename Type, unsigned int N>
Vector<Type,N> Vector<Type,N>::operator+(Vector<Type,N> const& Src) const
{
    Trace("Vector<Type,N>", "operator+(Vector<Type,N>&)");

    Vector<Type,N> tmp(*this);
    return tmp += Src;
}
template<typename Type, unsigned int N>
Vector<Type,N> const& Vector<Type,N>::operator+=(Vector<Type,N> const& Src)
{
    Trace("Vector<Type,N>", "operator+=(Vector<Type,N>&)");

    for (unsigned int i = 0; i < N; ++i) this->data[i] += Src.data[i];
    return *this;
}
template<typename Type, unsigned int N>
Vector<Type,N> Vector<Type,N>::operator-() const
{
    Trace("Vector<Type,N>", "operator-()");

    Vector<Type,N> tmp;
    return tmp -= *this;
}
template<typename Type, unsigned int N>
Vector<Type,N> Vector<Type,N>::operator-(Vector<Type,N> const& Src) const
{
    Trace("Vector<Type,N>", "operator-(Vector<Type,N>&)");

    Vector<Type,N> tmp(*this);
    return tmp -= Src;
}
template<typename Type, unsigned int N>
Vector<Type,N> const& Vector<Type,N>::operator-=(Vector<Type,N> const& Src)
{
    Trace("Vector<Type,N>", "operator-=(Vector<Type,N>&)");

    for (unsigned int i = 0; i < N; ++i) this->data[i] -= Src.data[i];
    return *this;
}
template<typename Type, unsigned int N>
Vector<Type,N> Vector<Type,N>::operator*(Type const& Factor) const
{
    Trace("Vector<Type,N>", "operator*(Type&)");

    Vector<Type,N> tmp(*this);
    return tmp *= Factor;
}
template<typename Type, unsigned int N>
Vector<Type,N> const& Vector<Type,N>::operator*=(Type const& Factor)
{
    Trace("Vector<Type,N>", "operator*=(Type&)");

    for (unsigned int i = 0; i < N; ++i) this->data[i] *= Factor;
    return *this;
}
template<typename Type, unsigned int N>
Type Vector<Type,N>::operator*(Vector<Type,N> const& Src) const
{
    Trace("Vector<Type,N>", "operator*(Vector<Type,N>&)");

    Type sum = Type();
    for (unsigned int i = 1; i <= N; ++i) sum += (this->Value(i) * Src.Value(i));

    return sum;
}
template<typename Type, unsigned int N>
Vector<Type,N> Vector<Type,N>::operator/(Type const& Factor) const
{
    Trace("Vector<Type,N>", "operator/(Type&)");

    Vector<Type,N> tmp(*this);
    return tmp /= Factor;
}
template<typename Type, unsigned int N>
Vector<Type,N> const& Vector<Type,N>::operator/=(Type const& Factor)
{
    Trace("Vector<Type,N>", "operator/=(Type&)");

    if (Factor == Type()) {
        std::ostringstream errormessage;
        errormessage << "file " << __FILE__ << ": line " << __LINE__ << ':' 
                     << std::endl;
#if 0
        errormessage << "    " << typeid(*this).name() 
                     << "::operator/=(Type&): " << std::endl;
        errormessage << "    Factor = " << Factor
                     << ". Illegal to divide by " << typeid(Type).name() 
                     << ": " << Type() << std::ends;
#else
        errormessage << "    " << TypeName(*this) 
                     << "::operator/=("
                     << TypeName(Factor)
                     << "&): "
                     << std::endl;
        errormessage << "    Argument = " << Factor
                     << ". Illegal to divide by "
                     << TypeName(Factor) 
                     << ": " << Type() << std::ends;
#endif
        throw std::invalid_argument(errormessage.str());
    }

    for (unsigned int i = 0; i < N; ++i) this->data[i] /= Factor;
    return *this;
}
template<typename Type, unsigned int N>
Type const& Vector<Type,N>::DataItem(unsigned int const Index) const
{
    Trace("Vector<Type,N>", "DataItem(unsigned int)");

    if ((Index < 1) || (Index > N)) {
        std::ostringstream errormessage;
        errormessage << "file " << __FILE__ << ": line " << __LINE__ << ':' << std::endl;
#if 1
        errormessage << "    " << typeid(*this).name() << "::DataItem(unsigned int): " << std::endl;
        errormessage << "Look Here: " << typeid(*this).name() << std::endl << std::flush;
#else
        errormessage << "    " << TypeName(*this) << "::DataItem(unsigned int): " << std::endl;
        errormessage << "    Index = " << Index << " must be in the set {"
                     << 1 << ",...," << N << '}' << std::ends;
#endif
        throw std::out_of_range(errormessage.str());
    }
    return this->data[Index - 1];
}
template<typename Type, unsigned int N>
Real Norm(Vector<Type,N> const& Vec, unsigned int const p)
{
    Trace("", "Norm(Vector<Type,N>&, unsigned int)");

    return Vec.Norm(p);
}
template<typename Type, unsigned int N>
Type Dot(Vector<Type,N> const& Vec1, Vector<Type,N> const& Vec2)
{
    Trace("", "Dot(Vector<Type,N>&, Vector<Type,N>&)");

    return Vec1 * Vec2;
}
template<typename Type>
Vector<Type,3> Cross(Vector<Type,3> const& Vec1, Vector<Type,3> const& Vec2)
{
    Trace("Vector<Type,N>", "Cross(Vector<Type,N>&, Vector<Type,N>&)");

    Vector<Type,3> result(Vec1 ^ Vec2);
    return result;
}
template<typename Type, unsigned int N>
Vector<Type,N> operator*(Type const& Factor, Vector<Type,N> const& Src)
{
    Trace("", "operator*(Type&, Vector<Type,N>&)");

    return Src * Factor;
}
template<typename Type>
Vector<Type,3> operator^(Vector<Type,3> const& Vec1, Vector<Type,3> const& Vec2)
{
    Trace("", "operator^(Vector<Type,3>&, Vector<Type,3>&)");

    Vector<Type,3> Vec;
    
    Vec[1] = Vec1[2] * Vec2[3] - Vec1[3] * Vec2[2];
    Vec[2] = Vec1[3] * Vec2[1] - Vec1[1] * Vec2[3];
    Vec[3] = Vec1[1] * Vec2[2] - Vec1[2] * Vec2[1];

    return Vec;
}
template<typename Type, unsigned int N>
std::ostream& operator<<(std::ostream& s, Vector<Type,N> const& Src)
{
    Trace("", "operator<<(ostream&, Vector&)");

    Src.Put(s, s.width());
    return s;
}
template<typename Type, unsigned int N>
std::istream& operator>>(std::istream& s, Vector<Type,N>& Dest)
{
    Trace("", "operator>>(istream&, Vector<Type,N>&)");

    Dest.Get(s);
    return s;
}

#endif
