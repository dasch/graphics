#ifndef RM_QUATERNION_C
#define RM_QUATERNION_C

static char QuaternionVersion[] = 
     "$Id: quaternion.nw,v 1.1.1.1 2005/08/10 12:02:10 kaiip Exp $";

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
#include <matrix/debugmacros.h>
#include <matrix/typename.h>
#include <matrix/quaternion.h>

template<typename Type>
Quaternion<Type>::Quaternion()
{
    Trace("Quaternion<Type>", "Quaternion()");

    this->Clear();
}
template<typename Type>
Quaternion<Type>::Quaternion(Type const& Scalar,
                             Type const& Xvec, Type const& Yvec, Type const& Zvec)
{
    Trace("Quaternion<Type>", "Quaternion(4xType&)");

    this->s    = Scalar;
    this->v[1] = Xvec;
    this->v[2] = Yvec;
    this->v[3] = Zvec;
}
template<typename Type>
Quaternion<Type>::Quaternion(Type const& Scalar, Vector<Type,3> const& Vec)
{
    Trace("Quaternion<Type>", "Quaternion(Type&,Vector<Type,3>&)");

    this->s = Scalar;
    this->v = Vec;
}
template<typename Type>
Quaternion<Type>::Quaternion(Type const& Scalar)
{
    Trace("Quaternion<Type>", "Quaternion(Type&)");

    this->s    = Scalar;
    this->v[1] = Type();
    this->v[2] = Type();
    this->v[3] = Type();
}
template<typename Type>
Quaternion<Type>::Quaternion(Vector<Type,3> const& Vec)
{
    Trace("Quaternion<Type>", "Quaternion(Vector<Type,3>&)");

    this->s = Type();
    this->v = Vec;
}
template<typename Type>
Quaternion<Type>::Quaternion(Quaternion<Type> const& Quat)
{
    Trace("Quaternion<Type>", "Quaternion(Quaternion&");

//    for (unsigned int i = 0; i < 4; ++i) this->data[i] = Quat.data[i];

    this->s = Quat.s;
    this->v = Quat.v;
}
template<typename Type>
Quaternion<Type>::~Quaternion()
{
    Trace("Quaternion<Type>", "~Quaternion()");
}
template<typename Type>
void Quaternion<Type>::Clear()
{
    Trace("Quaternion<Type>", "Clear()");

    Type value = Type();
//    for (unsigned int i = 0; i < 4; ++i) this->data[i] = value;
    this->s    = value;
    this->v[1] = value;
    this->v[2] = value;
    this->v[3] = value;
}
template<typename Type>
void Quaternion<Type>::Put(std::ostream& s, int width) const
{
    Trace("Quaternion<Type>", "Put(ostream&, int)");
#if 0
    unsigned int const last = 4 - 1;
    for (unsigned int i = 0; i < last; ++i) s << std::setw(width) << this->DataItem(i) << ' ';
    s << std::setw(width) << this->DataItem(last);
#else
    s << std::setw(width) << this->s << ' ';
    s << std::setw(width) << this->v;
#endif
}
template<typename Type>
void Quaternion<Type>::Get(std::istream& s)
{
    Trace("Quaternion<Type>", "Get(istream&)");
#if 1
    Type data[4];
    for (unsigned int i = 0; i < 4; ++i) {
        s >> data[i];
        TraceMessage("Value read: " << this->data[i] << endl);
        if (!s) {
            std::ostringstream errormessage;
            errormessage << "file " << __FILE__ << ": line " << __LINE__ << ':' << std::endl;
//            errormessage << "    " << TypeName(typeid(*this).name()) << "::Get(istream&): ";
              errormessage << "    " << TypeName(*this) << "::Get(istream&): ";
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
    this->s = data[0];
    for (unsigned int j = 1; j < 4; ++j) this->v[j] = data[j];
#else
    for (unsigned int i = 0; i < 4; ++i) {
        s >> this->DataItem(i);
        TraceMessage("Value read: " << this->DateItem(i) << endl);
        if (!s) {
            std::ostringstream errormessage;
            errormessage << "file " << __FILE__ << ": line " << __LINE__ << ':' << std::endl;
//            errormessage << "    " << TypeName(typeid(*this).name()) << "::Get(istream&): ";
              errormessage << "    " << TypeName(*this) << "::Get(istream&): ";
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
#endif
}
template<typename Type>
Type& Quaternion<Type>::Value(unsigned int const Index)
{
    Trace("Quaternion<Type>", "Value(unsigned int) --- non-const");

    return const_cast<Type&>(this->DataItem(Index));
}
template<typename Type>
Type const& Quaternion<Type>::Value(unsigned int const Index) const
{
    Trace("Quaternion<Type>", "Value(unsigned int) --- const");

    return this->DataItem(Index);
}
template<typename Type>
Type const& Quaternion<Type>::ScalarPart() const
{
    Trace("Quaternion<Type>", "ScalarPart() --- const");

    return this->s;
}
template<typename Type>
Type Quaternion<Type>::ScalarPart(Type const& NewValue)
{
    Trace("Quaternion<Type>", "ScalarPart(Type&) --- const");

    Type const OldScalar = this->s;
    this->s = NewValue;

    return OldScalar;
}
template<typename Type>
Vector<Type,3> const& Quaternion<Type>::VectorPart() const
{
    Trace("Quaternion<Type>", "VectorPart() --- const");

    return this->v;
}
template<typename Type>
Vector<Type,3> Quaternion<Type>::VectorPart(Type const& Xnew, Type const& Ynew, Type const& Znew)
{
    Trace("Quaternion<Type>", "VectorPart(Type&,Type&,Typw&)");

    Vector<Type,3> oldV(this->v);
    this->v[1] = Xnew;
    this->v[2] = Ynew;
    this->v[3] = Znew;

    return oldV;
}
template<typename Type>
Vector<Type,3> Quaternion<Type>::VectorPart(Vector<Type,3> const& NewValue)
{
    Trace("Quaternion<Type>", "VectorPart(Vector<Type,3> const& NewValue)");

    Vector<Type,3> oldV(this->v);
    this->v = NewValue;

    return oldV;
}
template<typename Type>
Quaternion<Type> Quaternion<Type>::C() const
{
    Trace("Quaternion<Type>", "C()");

    return Quaternion<Type>(this->s, -this->v);
}
template<typename Type>
Real Quaternion<Type>::Norm() const
{
    Trace("Quaternion<Type>", "Norm()");

    Real value = this->s * this->s + this->v * this->v;

    Real norm = sqrt(value);
    
    return norm;
}
template<typename Type>
Quaternion<Type> Quaternion<Type>::I() const
{
    Trace("Quaternion<Type>", "I()");

    Real norm = this->Norm();
    Quaternion<Type> conjugate(this->C());
    return conjugate / (norm * norm);
}
template<typename Type>
Quaternion<Type> const& Quaternion<Type>::operator=(Quaternion<Type> const& Src)
{
    Trace("Quaternion<Type>", "operator=(Quaternion&)");

    if (this != &Src) {
        this->s = Src.s;
        this->v = Src.v;
    }
    return *this;
}
template<typename Type>
Type& Quaternion<Type>::operator[](unsigned int const Index)
{
    Trace("Quaternion<Type>", "operator[](unsigned int) --- non-const");

    return const_cast<Type&>(this->DataItem(Index));
}
template<typename Type>
Type const& Quaternion<Type>::operator[](unsigned int const Index) const
{
    Trace("Quaternion<Type>", "operator[](unsigned int) --- const");

    return this->DataItem(Index);
}
template<typename Type>
bool const Quaternion<Type>::operator==(Quaternion<Type> const& Src) const
{
    Trace("Quaternion<Type>", "operator==(Quaternion&)");

    if (this == &Src) return true;
    if (this->s != Src.s) return false;
    if (this->v != Src.v) return false;
    return true;
}
template<typename Type>
bool const Quaternion<Type>::operator!=(Quaternion<Type> const& Src) const
{
    Trace("Quaternion<Type>", "operator!=(Quaternion&)");

    return !(*this == Src);
}
template<typename Type>
Quaternion<Type> const& Quaternion<Type>::operator+() const
{
    Trace("Quaternion<Type>", "operator+()");

    return *this;
}
template<typename Type>
Quaternion<Type> Quaternion<Type>::operator+(Quaternion<Type> const& Src) const
{
    Trace("Quaternion<Type>", "operator+(Quaternion<Type>&)");

    Quaternion<Type> tmp(*this);
    return tmp += Src;
}
template<typename Type>
Quaternion<Type> const& Quaternion<Type>::operator+=(Quaternion<Type> const& Src)
{
    Trace("Quaternion<Type>", "operator+=(Quaternion<Type>&)");

    this->s += Src.s;
    this->v += Src.v;
    return *this;
}
template<typename Type>
Quaternion<Type> Quaternion<Type>::operator-() const
{
    Trace("Quaternion<Type>", "operator-()");

    Quaternion<Type> result(-this->ScalarPart(), -this->VectorPart());
    return result;
}
template<typename Type>
Quaternion<Type> Quaternion<Type>::operator-(Quaternion<Type> const& Src) const
{
    Trace("Quaternion<Type>", "operator-(Quaternion<Type>&)");

    Quaternion<Type> tmp(*this);
    return tmp -= Src;
}
template<typename Type>
Quaternion<Type> const& Quaternion<Type>::operator-=(Quaternion<Type> const& Src)
{
    Trace("Quaternion<Type>", "operator-=(Quaternion<Type>&)");

    this->s -= Src.s;
    this->v -= Src.v;
    return *this;
}
template<typename Type>
Quaternion<Type> Quaternion<Type>::operator*(Type const& Factor) const
{
    Trace("Quaternion<Type>", "operator*(Type&)");

    Quaternion<Type> tmp(*this);
    tmp *= Factor;
    return tmp;
}
template<typename Type>
Quaternion<Type> const& Quaternion<Type>::operator*=(Type const& Factor)
{
    Trace("Quaternion<Type>", "operator*=(Type&)");

    this->s *= Factor;
    this->v *= Factor;
    return *this;
}
template<typename Type>
Quaternion<Type> Quaternion<Type>::operator*(Quaternion<Type> const& Src) const
{
    Trace("Quaternion<Type>", "operator*(Quaternion<Type>&)");

    Quaternion<Type> tmp(*this);
    tmp *= Src;
    return tmp;
}
template<typename Type>
Quaternion<Type> const& Quaternion<Type>::operator*=(Quaternion<Type> const& Src)
{
    Trace("Quaternion<Type>", "operator*=(Quaternion<Type>&)");

    Type scalar = this->s * Src.s - this->v * Src.v;
    Vector<Type,3> vec;
    vec = Src.v * this->s + this->v * Src.s + Cross(this->v, Src.v);
    this->s = scalar;
    this->v = vec;

    return *this;
}
template<typename Type>
Quaternion<Type> Quaternion<Type>::operator/(Type const& Factor) const
{
    Trace("Quaternion<Type>", "operator/(Type&)");

    Quaternion<Type> tmp(*this);
    return tmp /= Factor;
}
template<typename Type>
Quaternion<Type> const& Quaternion<Type>::operator/=(Type const& Factor)
{
    Trace("Quaternion<Type>", "operator/=(Type&)");

    if (Factor == Type()) {
        std::ostringstream errormessage;
        errormessage << "file " << __FILE__ << ": line " << __LINE__ << ':' 
                     << std::endl;
//        errormessage << "    " << typeid(*this).name() 
//                     << "::operator/=(Type&): " << std::endl;
        errormessage << "    " << TypeName(*this) 
                     << "::operator/=("
                     << TypeName(Factor)
                     << "&): "
                     << std::endl;
//        errormessage << "    Factor = " << Factor
//                     << ". Illegal to divide by " << typeid(Type).name() 
//                     << ": " << Type() << std::ends;
        errormessage << "    Argument = " << Factor
                     << ". Illegal to divide by "
                     << TypeName(Factor) 
                     << ": " << Type() << std::ends;
        throw std::invalid_argument(errormessage.str());
    }

    this->s /= Factor;
    this->v /= Factor;

    return *this;
}
template<typename Type>
Quaternion<Type> Quaternion<Type>::operator/(Quaternion<Type> const& Src) const
{
    Trace("Quaternion<Type>", "operetor/(Quaternion&)");

    Quaternion<Type> tmp(*this);
    return tmp *= Src.I();
}
template<typename Type>
Quaternion<Type> const& Quaternion<Type>::operator/=(Quaternion<Type> const& Src)
{
    Trace("Quaternion<Type>", "operetor/=(Quaternion&)");

    Quaternion<Real> Zero(0, 0, 0, 0);
    if (Src == Zero) {
        std::ostringstream errormessage;
        errormessage << "file " << __FILE__ << ": line " << __LINE__ << ':' 
                     << std::endl;
//        errormessage << "    " << typeid(*this).name() 
//                     << "::operator/=(Type&): " << std::endl;
        errormessage << "    " << TypeName(*this) 
                     << "::operator/=("
                     << TypeName(Src)
                     << "&): "
                     << std::endl;
//        errormessage << "    Factor = " << Factor
//                     << ". Illegal to divide by " << typeid(Type).name() 
//                     << ": " << Type() << std::ends;
        errormessage << "    Argument = " << Src
                     << ". Illegal to divide by "
                     << TypeName(Src) 
                     << ": " << Zero << std::ends;
        throw std::invalid_argument(errormessage.str());
    }

    *this *= Src.I();
    return *this;
}
template<typename Type>
Type const& Quaternion<Type>::DataItem(unsigned int const Index) const
{
    Trace("Quaternion<Type>", "DataItem(unsigned int)");

    if ((Index < 1) || (Index > 4)) {
        std::ostringstream errormessage;
        errormessage << "file " << __FILE__ << ": line " << __LINE__ << ':' << std::endl;
//        errormessage << "    " << typeid(*this).name() << "::DataItem(unsigned int): " << std::endl;
//      errormessage << "Look Here: " << typeid(*this).name() << std::endl << std::flush;
        errormessage << "    " << TypeName(*this) << "::DataItem(unsigned int): " << std::endl;
        errormessage << "    Index = " << Index << " must be in the set {"
                     << 1 << ",...," << 4 << '}' << std::ends;
        throw std::out_of_range(errormessage.str());
    }

    switch (Index) {
      case 1:
        return this->s;
        break;
      default:
        return this->v[Index - 1];
        break;
    }
}
template<typename Type>
Quaternion<Type> Conjugate(Quaternion<Type> const& Quat)
{
    Quaternion<Type> result;
    result.ScalarPart(Quat.ScalarPart());
    result.VectorPart(-Quat.VectorPart());
    return result;
}
template<typename Type>
Real Norm(Quaternion<Type> const& Quat)
{
    Trace("", "Norm(Quaternion<Type>&)");

    return Quat.Norm();
}
template<typename Type>
Quaternion<Type> Inverse(Quaternion<Type> const& Quat)
{
    Real norm = Quat.Norm();
    Quaternion<Type> result(Quat.C());
    result /= (norm * norm);
    return result;
}
template<typename Type>
Quaternion<Type> operator*(Type const& Factor, Quaternion<Type> const& Src)
{
    Trace("Quaternion<Type>", "operator*(Type&, Quaternion<Type>&)");

    return Src * Factor;
}
template<typename Type>
std::ostream& operator<<(std::ostream& s, Quaternion<Type> const& Src)
{
    Trace("", "operator<<(ostream&, Vector&)");

    Src.Put(s, s.width());
    return s;
}
template<typename Type>
std::istream& operator>>(std::istream& s, Quaternion<Type>& Dest)
{
    Trace("", "operator>>(istream&, Quaternion<Type>&)");

    Dest.Get(s);
    return s;
}

#endif
