// char MatrixVersion[] = 
//    "$Id: matrix.nw,v 1.1 2005/08/10 12:58:45 kaiip Exp $";

#include <stdexcept>
#include <cstdarg>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <cctype>
#if 0
#include <NEWMAT/newmat.h>
#include <NEWMAT/newmatio.h>
#endif
#include <matrix/trace.h>
#include <matrix/matrix.h>
#if 0
#include <matrix/simplearray.h>
#endif

template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N>::Matrix()
{
    Trace("Matrix<Type,M,N>", "Matrix()");
}
#ifdef PARAM
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N>::Matrix(Type const FirstValue ...)
{
    Trace("Matrix<Type,M,N>", "Matrix(Type ...)");

    va_list parameterlist;
    va_start(parameterlist, FirstValue);
        // Handle the first row special
        this->data[1][1] = FirstValue;
        for (unsigned int k = 2; k <= N; ++k) {
            this->data[1][k] = va_arg(parameterlist, Type const);
        }
        // Handle rows 2,...,M in two loops
        for (unsigned int i = 2; i <= M; ++i) {
            for (unsigned int j = 1; j <= N; ++j) {
                this->data[i][j] = va_arg(parameterlist, Type const);
            }
        }
    va_end(parameterlist);
}
#endif
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N>::Matrix(Matrix<Type,M,N> const& Src)
{
    Trace("Matrix<Type,M,N>", "Matrix(Matrix&");

    for (unsigned int i = 1; i <= M; ++i) this->data[i] = Src.data[i];
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N>::~Matrix()
{
    Trace("Matrix<Type,M,N>", "~Matrix()");
}
template<typename Type, unsigned int M, unsigned int N>
unsigned int const Matrix<Type,M,N>::Rows() const
{
    Trace("Matrix<Type,M,N>", "Rows()");

    return M;
}
template<typename Type, unsigned int M, unsigned int N>
RowVector<Type,N> Matrix<Type,M,N>::Row(unsigned int const Index) const
{
    Trace("Matrix<Type,M,N>", "Row(unsigned int)");

    return this->Value(Index);
}
template<typename Type, unsigned int M, unsigned int N>
RowVector<Type,N> Matrix<Type,M,N>::Row(unsigned int const Index, 
                                        RowVector<Type,N> const& NewRowVector)
{
    Trace("Matrix<Type,M,N>", "Row(unsigned int, RowVector<Type,N>&)");

    RowVector<Type,N> OldRow(this->Value(Index));
    this->Value(Index) = NewRowVector;
    return OldRow;     
}
template<typename Type, unsigned int M, unsigned int N>
unsigned int const Matrix<Type,M,N>::Columns() const
{
    Trace("Matrix<Type,M,N>", "Columns()");

    return N;
}
template<typename Type, unsigned int M, unsigned int N>
ColumnVector<Type,M> Matrix<Type,M,N>::Column(unsigned int const Index) const
{
    Trace("Matrix<Type,M,N>", "Column(unsigned int)");

    ColumnVector<Type,M> Column;
    for (unsigned int i = 1; i <= M; ++i) Column[i] = this->Value(i)[Index];
    return Column;
}
template<typename Type, unsigned int M, unsigned int N>
ColumnVector<Type,M> 
Matrix<Type,M,N>::Column(unsigned int const Index, ColumnVector<Type,M> const& NewColumn)
{
    Trace("Matrix<Type,M,N>", "Column(unsigned int, ColumnVector<Type,M>&)");

    ColumnVector<Type,M> OldColumn;
    for (unsigned int i = 1; i <= M; ++i) {
        OldColumn[i] = this->Value(i)[Index];
        this->Value(i)[Index] = NewColumn[i];
    }
    return OldColumn;
}
template<typename Type, unsigned int M, unsigned int N>
RowVector<Type,N>& Matrix<Type,M,N>::Value(unsigned int const Index)
{
    Trace("Matrix<Type,M,N>", "Value(unsigned int) --- non-const");

    return this->data[Index];
}
template<typename Type, unsigned int M, unsigned int N>
RowVector<Type,N> const& Matrix<Type,M,N>::Value(unsigned int const Index) const
{
    Trace("Matrix<Type,M,N>", "Value(unsigned int) --- const");

    return this->data[Index];
}
#if 0
template<typename Type, unsigned int M, unsigned int N>
Type Matrix<Type,M,N>::Norm(unsigned int const p) const
#else
template<typename Type, unsigned int M, unsigned int N>
Real Matrix<Type,M,N>::Norm(unsigned int const p) const
#endif
{
    Trace("Matrix<Type,M,N>", "Norm(Matrix<Type,M,N>&, unsigned int)");

    unsigned int i, j;

#if 0
    Type norm  = Type();
    Type value = Type();
#else
    double norm  = 0.0;
    double value = 0.0;
#endif

    switch (p) {
    case 0: 
        for (i = 1; i <= M; ++i) {
            value = Type();
            for (j = 1; j <= N; ++j) value += ::Norm((*this)[i][j], 0);
            if (value > norm) norm = value;
        }
        break;
    case 1:
        for (j = 1; j <= N; ++j) {
            value = Type();
            for (i = 1; i <= M; ++i) value += ::Norm((*this)[i][j], 1);
            if (value > norm) norm = value;
        }
        break;
    default: {
            std::ostringstream errormessage;
            errormessage << "file " << __FILE__ << ": line " << __LINE__ << ':' << std::endl;
            errormessage << "    " << "\"\"" << "Matrix<Type,M,N>::Norm(unsigned int): " << std::endl;
            errormessage << "    The " << p << "-norm is not implemented" << std::ends;
            throw std::invalid_argument(errormessage.str());
        }
    }
    return norm;
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,N,M> Matrix<Type,M,N>::T() const
{
    Trace("Matrix<Type,M,N>", "T()");

    Matrix<Type,N,M> result;
    for (unsigned int i = 1; i <= N; ++i) {
        for (unsigned int j = 1; j <= M; ++j) {
            result[i][j] = this->data[j][i];
        }
    }
    return result;
}
template<typename Type, unsigned int M, unsigned int N>
void Matrix<Type,M,N>::Clear()
{
    Trace("Matrix<Type,M,N>", "Clear()");

    for (unsigned int i = 1; i <= M; ++i) this->data.Clear();
}
template<typename Type, unsigned int M, unsigned int N>
void Matrix<Type,M,N>::Put(std::ostream& s, int width) const
{
    Trace("Matrix<Type,M,N>", "Put(ostream&, int)");

    s << std::endl;
    for (unsigned int i = 1; i <= M; ++i) s << std::setw(width) << this->data[i] << std::endl;
}
template<typename Type, unsigned int M, unsigned int N>
void Matrix<Type,M,N>::Get(std::istream& s)
{
    Trace("Matrix<Type,M,N>", "Get(istream&)");

    this->data.Get(s);
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> const& 
Matrix<Type,M,N>::operator=(Matrix<Type,M,N> const& Src)
{
    Trace("Matrix<Type,M,N>", "operator=(Matrix&)");

    if (this != &Src) {
        for (unsigned int i = 1; i <= M; ++i) this->data[i] = Src.data[i];
    }
    return *this;
}
template<typename Type, unsigned int M, unsigned int N>
RowVector<Type,N>& Matrix<Type,M,N>::operator[](unsigned int const Index)
{
    Trace("Matrix<Type,M,N>", "operator[](unsigned int) --- non-const");

    return this->data[Index];
}
template<typename Type, unsigned int M, unsigned int N>
RowVector<Type,N> const& Matrix<Type,M,N>::operator[](unsigned int const Index) const
{
    Trace("Matrix<Type,M,N>", "operator[](unsigned int) --- const");

    return this->data[Index];
}
template<typename Type, unsigned int M, unsigned int N>
bool const Matrix<Type,M,N>::operator==(Matrix<Type,M,N> const& Src) const
{
    Trace("Matrix<Type,M,N>", "operator==(Matrix&)");

    return this->data == Src.data;
}
template<typename Type, unsigned int M, unsigned int N>
bool const Matrix<Type,M,N>::operator!=(Matrix<Type,M,N> const& Src) const
{
    Trace("Matrix<Type,M,N>", "operator!=(Matrix&)");

    return this->data != Src.data;
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> const& Matrix<Type,M,N>::operator+() const
{
    Trace("Matrix<Type,M,N>", "operator+()");

    return *this;
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> Matrix<Type,M,N>::operator+(Matrix<Type,M,N> const& Src) const
{
    Trace("Matrix<Type,M,N>", "operator+(Matrix<Type,M,N>&)");

    Matrix<Type,M,N> tmp(*this);
    return tmp += Src;
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> const& 
Matrix<Type,M,N>::operator+=(Matrix<Type,M,N> const& Src)
{
    Trace("Matrix<Type,M,N>", "operator+=(Matrix<Type,M,N>&)");

    this->data += Src.data;
    return *this;
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> Matrix<Type,M,N>::operator-() const
{
    Trace("Matrix<Type,M,N>", "operator-()");

    Matrix<Type,M,N> tmp;
    return tmp -= *this;
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> Matrix<Type,M,N>::operator-(Matrix<Type,M,N> const& Src) const
{
    Trace("Matrix<Type,M,N>", "operator-(Matrix<Type,M,N>&)");

    Matrix<Type,M,N> tmp(*this);
    return tmp -= Src;
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> const& Matrix<Type,M,N>::operator-=(Matrix<Type,M,N> const& Src)
{
    Trace("Matrix<Type,M,N>", "operator-=(Matrix<Type,M,N>&)");

    this->data -= Src.data;
    return *this;
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> Matrix<Type,M,N>::operator*(Type const& Factor) const
{
    Trace("Matrix<Type,M,N>", "operator*(Type&)");

    Matrix<Type,M,N> tmp(*this);
    return tmp *= Factor;
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> const& Matrix<Type,M,N>::operator*=(Type const& Factor)
{
    Trace("Matrix<Type,M,N>", "operator*=(Type&)");

    for (unsigned int i = 1; i <= M; ++i) this->data[i] *= Factor;
    return *this;
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> Matrix<Type,M,N>::operator/(Type const& Factor) const
{
    Trace("Matrix<Type,M,N>", "operator/(Type&)");

    Matrix<Type,M,N> tmp(*this);
    return tmp /= Factor;
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> const& Matrix<Type,M,N>::operator/=(Type const& Factor)
{
    Trace("Matrix<Type,M,N>", "operator/=(Type&)");

    if (Factor == Type()) {
        std::ostringstream errormessage;
        errormessage << "file " << __FILE__ << ": line " << __LINE__ << ':' 
                     << std::endl;
        errormessage << "    " << typeid(*this).name() 
                     << "::operator/=(Type&): " << std::endl;
        errormessage << "    Factor = " << Factor
                     << ". Illegal to divide by " << typeid(Type).name() 
                     << ": " << Type() << std::ends;
        throw std::invalid_argument(errormessage.str());
    }

    for (unsigned int i = 1; i <= M; ++i) this->data[i] /= Factor;
    return *this;
}
/* No Private Private Member Functions so far*/
#ifndef DEBUG
#define PrintDebugMessage(Text)
#else
#define PrintDebugMessage(Text)                                       ??/
{                                                                     ??/
    std::cout << Text << std::endl;                                   ??/
}
#endif
#ifndef DEBUG
#define PrintPivotingMethod(PivotType)
#else
#define PrintPivotingMethod(PivotType)                                 ??/
{                                                                           ??/
    switch ((PivotType)) {                                                  ??/
    case NoPivoting:                                                        ??/
        PrintDebugMessage("NoPivoting");                                    ??/
        break;                                                              ??/
    case PartialPivoting:                                                   ??/
        PrintDebugMessage("PartialPivoting");                               ??/
        break;                                                              ??/
    case CompletePivoting:                                                  ??/
        PrintDebugMessage("CompletePivitoting");                            ??/
        break;                                                              ??/
    default:                                                                ??/
        PrintDebugMessage("Pivoting == " << Pivoting << ": No such pivoting method");                                                                          ??/
    }                                                                       ??/
}
#endif
#ifndef DEBUG
#define PrintRealLimits(Type)
#else
#define PrintRealLimits(Type)                                           ??/
{                                                                             ??/
    std::cout << "epsilon     = " << std::numeric_limits<Type>::epsilon()     << std::endl; ??/
    std::cout << "Epsilon     = " << Epsilon                             << std::endl; ??/
    std::cout << "#Digits(10) = " << std::numeric_limits<Type>::digits10      << std::endl; ??/
    std::cout << "#Digits(2)  = " << std::numeric_limits<Type>::digits        << std::endl; ??/
    std::cout << "radix       = " << std::numeric_limits<Type>::radix         << std::endl; ??/
    std::cout << "round_error = " << std::numeric_limits<Type>::round_error() << std::endl; ??/
    std::cout << "traps       = " << std::numeric_limits<Type>::traps         << std::endl; ??/
}
#endif
#ifndef DEBUG
#define PrintLinearSystem(Text)
#else
#define PrintLinearSystem(Text)                                     ??/
{                                                                       ??/
    unsigned int row, col;                                                      ??/
    PrintDebugMessage(Text);                                            ??/
    std::cout << "    | ";                                              ??/
    for (col = 1; col <= A.Columns(); ++col) {                          ??/
        std::cout << "     " << cperm[col] << "     | ";                ??/
    }                                                                   ??/
    std::cout << std::endl;                                             ??/
    std::cout << "----+";                                               ??/
    for (col = 1; col <= A.Columns()+1; ++col) std::cout << "------------+"; ??/
    std::cout << std::endl;                                             ??/
    for (row = 1; row <= A.Rows(); ++row) {                             ??/
        std::cout << std::setw(3) << rperm[row] << " |";                ??/
        for (col = 1; col <= A.Columns(); ++col) {                      ??/
            std::cout << ' ' << std::setw(10)                           ??/
                      << ScaleFactor[rperm[row]] * A[rperm[row]][cperm[col]] ??/
                      << ' ';                                                ??/
            if (col < A.Columns()) std::cout << ' ';                         ??/
        }                                                               ??/
        std::cout << "| " << std::setw(10)                              ??/
                  << ScaleFactor[rperm[row]] * B[rperm[row]] << std::endl;   ??/
    }                                                                   ??/
    std::cout << std::endl;                                             ??/
}
#endif
#if 0
template<typename Type, unsigned int M, unsigned int N>
Type Norm(Matrix<Type,M,N> const& Mat, unsigned int const p)
#else
template<typename Type, unsigned int M, unsigned int N>
Real Norm(Matrix<Type,M,N> const& Mat, unsigned int const p)
#endif
{
    Trace("", "Norm(Matrix<Type,M,N>&, unsigned int)");

    return Mat.Norm(p);
}
template<typename Type, unsigned int M>
Matrix<Type,M,M> Inverse(Matrix<Type,M,M> const& A, Type const epsilon)
{
    Trace("", "Inverse(Matrix<Type,M,M> const&, Type)");

    Matrix<Type,M,M> E;
    for (unsigned int i = 1; i <= M; ++i) E[i][i] = Type(1);

    Matrix<Type,M,M> Ainv;
    Matrix<Type,M,M> Residual;
    Matrix<Type,M,M> OldAinv;
    Matrix<Type,M,M> OldResidual;

    Matrix<Type,M,M> NewAinv;
    Matrix<Type,M,M> NewResidual;
    Matrix<Type,M,M> OldAinvDiff;
    Matrix<Type,M,M> NewAinvDiff;
    unsigned int const MaxIterations = 200;
    bool  Converging = false;
    unsigned int  ConvergenceCount         = 0;
    unsigned int const MinConvergenceCount = 5;
    Type const Epsilon = epsilon != Type() ?
                         epsilon :
                         Type(0.5 * pow(10.0, - (std::numeric_limits<Type>::digits10 - 1)));
    unsigned int IterationCount = 1;
    Ainv     = Solve(A, E, CompletePivoting, Epsilon);
    Residual = E - A * Ainv;

    PrintDebugMessage("Epsilon == " << Epsilon);
    PrintDebugMessage("Ainv(0):" << std::setprecision(4) << std::setw(10) << Ainv);
    PrintDebugMessage("Residual(0):" << std::setprecision(4) << std::setw(10) << Residual);
    PrintDebugMessage("|Residual(0)| = " << std::setprecision(4) << std::setw(10) << Norm(Residual, 1) << std::endl);
    #ifdef DEBUG
    std::ofstream outputres("Residual.gpl");
    if (!outputres)
        throw std::runtime_error("::Inverse: Cannot open file `Residual.gpl'");

    std::ofstream outputainvdiff("AinvDiff.gpl");
    if (!outputainvdiff)
        throw std::runtime_error("::Inverse: Cannot open file `AinvDiff.gpl'");

    outputres << std::setw(3) << 0 << ' ' << std::setprecision(4) << std::setw(10) << Norm(Residual, 1) << std::endl;
    #endif

    if (Norm(E - A * Ainv, 1) < Epsilon) return Ainv;
    OldAinv = Ainv;
    OldResidual = E - A * Ainv;

    for (IterationCount = 1; IterationCount <= MaxIterations; ++IterationCount) {
        NewAinvDiff = Ainv * OldResidual;    // was: OldAinv
        NewAinv     = OldAinv + NewAinvDiff;
        NewResidual = E - A * NewAinv;

        #ifdef DEBUG
        outputres << std::setw(3) << IterationCount << ' '
                  << std::setprecision(4) << std::setw(10) << Norm(NewResidual, 1) << std::endl;
        outputainvdiff << std::setw(3) << IterationCount << ' '
                       << std::setprecision(4) << std::setw(10) << Norm(NewAinvDiff, 1) << std::endl;
        #endif

        PrintDebugMessage("AinvDiff(" << IterationCount << "):"
                          << std::setprecision(4) << std::setw(10) << NewAinvDiff);
        PrintDebugMessage("|AinvDiff(" << IterationCount << ")| = "
                          << std::setprecision(4) << std::setw(10) << Norm(NewAinvDiff, 1) << std::endl);

        PrintDebugMessage("Residual(" << IterationCount << "):"
                          << std::setprecision(4) << std::setw(10) << NewResidual);
        PrintDebugMessage("|Residual(" << IterationCount << ")| = "
                          << std::setprecision(4) << std::setw(10) << Norm(NewResidual, 1));
        if (Norm(NewResidual, 1) < Epsilon) {
            PrintDebugMessage("Converged: Norm(NewResidual, 1) = " << Norm(NewResidual, 1) << " < Epsilon == " << Epsilon);

            Ainv = NewAinv;
            break;
        }
        if (!Converging) {
            if (Norm(NewResidual, 1) <= Norm(OldResidual, 1)) {
                PrintDebugMessage("|Residual(" << IterationCount << ")| decreasing" << std::endl);
                ++ConvergenceCount;
            }
            else {
                PrintDebugMessage("|Residual(" << IterationCount << ")| increasing" << std::endl);
                ConvergenceCount = 0;
            }
            Converging = (ConvergenceCount >= MinConvergenceCount);
        }
        if (Converging && (Norm(NewResidual, 1) >= Norm(OldResidual, 1))) {
            PrintDebugMessage("Converging && (Norm(NewResidual, 1) >= Norm(OldResidual, 1)");
            break;
        }
        if (Converging && (Norm(NewAinvDiff, 1) < Epsilon)) {
            PrintDebugMessage("Converging && (Norm(NewAinvDiff, 1) < Epsilon)");

            Ainv = NewAinv;
            break;
        }
        if (Converging && (Norm(NewAinvDiff, 1) >= Norm(OldAinvDiff, 1))) {
            PrintDebugMessage("Diverging: Converging && (Norm(NewAinvDiff, 1) >= Norm(OldAinvDiff, 1))");
            break;
        }
        if (Norm(NewResidual, 1) < Norm(OldResidual, 1)) Ainv = NewAinv;
        OldAinv     = NewAinv;
        OldResidual = NewResidual;
        OldAinvDiff = NewAinvDiff;
    }

    #ifdef DEBUG
    outputres.close();
    outputainvdiff.close();
    #endif

#if 0
    PrintDebugMessage("Ainv(" << IterationCount << "): "
                      << std::setprecision(4) << std::setw(10) << Ainv);
    PrintDebugMessage("Residual(" << IterationCount<< "):"
                      << std::setprecision(4)
                      << std::setw(10) << Residual);
    PrintDebugMessage("|Residual(" << IterationCount << ")| = " 
                      << std::setprecision(4) << std::setw(10)
                      << Norm(E - A * Ainv, 1));
    PrintDebugMessage("(A * Ainv)(" << IterationCount << ") "
                      << std::setprecision(4) << std::setw(10) << A * Ainv);
#endif

#ifdef DEBUG
    if (IterationCount >= MaxIterations) {
        PrintDebugMessage("IterationCount == " << IterationCount
                          << " >= MaxIterations == " << MaxIterations);
    }
#endif

    return Ainv;
}
template<typename Type, unsigned int M>
ColumnVector<Type,M> 
Solve(Matrix<Type,M,M> const& Amatrix, ColumnVector<Type,M> const& Bvector,
      PivotType const Pivoting, Type const epsilon)
{
    Trace("", "Solve(Matrix<Type,M,M>&, ColumnVector<Type,M>&, PivotType, Type)");

    Matrix<Type,M,1>  Bmatrix;
    Bmatrix.Column(1, Bvector);
    Matrix<Type,M,1>     Xmatrix = Solve(Amatrix, Bmatrix, Pivoting, epsilon);
    ColumnVector<Type,M> Xvector = Xmatrix.Column(1);
    return Xvector;
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> 
Solve(Matrix<Type,M,M> const& Amatrix, Matrix<Type,M,N> const& Bmatrix,
      PivotType const Pivoting, Type const epsilon)
{
    Trace("", "Solve(Matrix<Type,M,M>&, Matrix<Type,M,N>&, PivotType, Type)");

    unsigned int i, j, k;
    Type const Epsilon = epsilon != Type() ?
                         epsilon :
                         Type(0.5 * pow(10.0, - (std::numeric_limits<Type>::digits10 - 1)));
    Matrix<Type,M,M> A(Amatrix);
    Matrix<Type,M,N> B(Bmatrix);
    Vector<Type,M> ScaleFactor;

    for (i = 1; i <= M; ++i) ScaleFactor[i] = Type(1);
    Vector<unsigned int,M> rperm, cperm;
    for (i = 1; i <= M; ++i) rperm[i] = cperm[i] = i;

    PrintRealLimits(Type);
    PrintPivotingMethod(Pivoting);
    PrintLinearSystem("Original Linear System:");
    
    for (i = 1; i < M; ++i) {
        if ((Pivoting == PartialPivoting) || (Pivoting == CompletePivoting)) {
            PrintDebugMessage("Scale System");

            for (j = i; j <= M; ++j) {
                // Find the maximum absolute value of row $j$
                Real maxnorm = Norm(A[rperm[j]], 0);

                // Compute an integer exponent $n_j$ that satisfies the relation $\dfrac{1}{2} \le 2^{n_j} \mathit{maxnorm} \le 1$
                double n   = floor(-log(maxnorm));

                // Compute the scale factor $2^{n_j}$
                //ScaleFactor[rperm[j]] = pow(static_cast<Type>(2), static_cast<int>(n));
                ScaleFactor[rperm[j]] = pow(2.0, n);
            }

            PrintLinearSystem("Scaled Linear System:");

            if (Pivoting == PartialPivoting) {
                // Find the maximum element $ | a_{ii} | \ge | a_{ji} |; j = i + 1, \ldots, M $
                PrintDebugMessage("Partial Pivoting");

                unsigned int jmax = i;
                Type MaxAji = ScaleFactor[rperm[i]] * Norm(A[rperm[i]][i]);
                for (j = i + 1; j <= M; ++j) {
                    if (ScaleFactor[rperm[j]] * Norm(A[rperm[j]][i]) > MaxAji) {
                        jmax = j;
                        MaxAji = ScaleFactor[rperm[j]] * Norm(A[rperm[j]][i]);
                    }
                }

                // Update [[rperm]] indicating that rows $ i $ and $ j_{\mathit{max}} $ has been interchanged
                if (jmax != i) {
                    PrintDebugMessage("Interchange rows: " << rperm[i] << " and " << rperm[jmax]);

                    unsigned int tmp = rperm[i]; rperm[i] = rperm[jmax]; rperm[jmax] = tmp;
                }
            }
            if (Pivoting == CompletePivoting) {
                PrintDebugMessage("Complete Pivoting");

                // Find the maximum absolute value of the submatrix
                unsigned int jmax = i;
                unsigned int kmax = i;
                Type MaxAjk = ScaleFactor[rperm[i]] * Norm(A[rperm[i]][cperm[i]]);
                for (j = i; j <= M; ++j) {
                    for (k = i; k <= M; ++k) {
                        if (ScaleFactor[rperm[j]] * Norm(A[rperm[j]][cperm[k]]) > MaxAjk) {
                            jmax = j;
                            kmax = k;
                            MaxAjk = ScaleFactor[rperm[j]] * Norm(A[rperm[j]][cperm[k]]);
                        }
                    }
                }

                // Update [[rperm]] indicating that rows $ i $ and $ j_{\mathit{max}} $ has been interchanged
                if (jmax != i) {
                    PrintDebugMessage("Interchange rows: " << rperm[i] << " and " << rperm[jmax]);

                    unsigned int tmp = rperm[i]; rperm[i] = rperm[jmax]; rperm[jmax] = tmp;
                }

                // Update [[cperm]] indicating that columns $ i $ and $ k_{\mathit{max}} $ has been interchanged
                if (kmax != i) {
                    PrintDebugMessage("Interchange columns: " << cperm[i] << " and " << cperm[kmax]);

                    unsigned int tmp = cperm[i]; cperm[i] = cperm[kmax]; cperm[kmax] = tmp;
                }
            }
            PrintLinearSystem("Scaled Linear System after Pivoting:");
        }
        if (Norm(A[rperm[i]][cperm[i]]) < Epsilon) {
            std::ostringstream errormessage;
            errormessage << "file " << __FILE__ << ": line " << __LINE__ << ':' << std::endl;
            errormessage << "    "
                         << "Solve(Matrix<Type,M,M>&, Matrix<Type,M,N>&, PivotType): "
                         << std::endl;
            errormessage << "    The matrix is singular" << std::ends;
            throw std::runtime_error(errormessage.str());
        }

        // Make zeroes under the diagonal in the rest of the rows
        for (j = i + 1; j <= M; ++j) {
            Type factor = A[rperm[j]][cperm[i]] / A[rperm[i]][cperm[i]];
            A[rperm[j]] -= A[rperm[i]] * factor;
            B[rperm[j]] -= B[rperm[i]] * factor;

            PrintLinearSystem("Elimination of variable " << i << " from equation " << j);

        #ifdef DEBUG
            for (k = 1; k <= M; ++k) { // was k = j ...
                if (Norm(A[rperm[j]][cperm[k]]) < Epsilon) {
                    A[rperm[j]][cperm[k]] = Type();
                }
            }
            for (k = 1; k <= N; ++k) {
                if (Norm(B[rperm[j]][k]) < Epsilon) B[rperm[j]][k] = Type();
            }
        #endif
        } 

        PrintLinearSystem("Linear System after Elimination of variable " << i << ":");
    }
    Matrix<Type,M,N> X;
    for (i = M; i > 0; --i) {
        RowVector<Type,N> tmp = B[rperm[i]];
        for (j = i + 1; j <= M; ++j) tmp -= A[rperm[i]][cperm[j]] * X[cperm[j]];
        X[cperm[i]] = tmp / A[rperm[i]][cperm[i]];
    }

    return X;
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> operator*(Type const& Factor, Matrix<Type,M,N> const& Src)
{
    Trace("", "operator*(Type&, Matrix<Type,M,N>&)");

    return Src * Factor;
}
template<typename Type, unsigned int M, unsigned int N>
RowVector<Type,N> operator*(RowVector<Type,M> const& Vec,
                            Matrix<Type,M,N> const& Mat)
{
    Trace("", "operator*(RowVector<Type,M>&, Matrix<Type,M,N>&)");

    RowVector<Type,N> Result;
    for (unsigned int j = 1; j <= N; ++j) {
        Type element = Type();
        for (unsigned int k = 1; k <= M; ++k) element += Vec[k] * Mat[k][j];
        Result[j] = element;
    }
    return Result;
}
template<typename Type, unsigned int M, unsigned int N>
ColumnVector<Type,M> operator*(Matrix<Type,M,N> const& Mat,
                               ColumnVector<Type,N> const& Vec)
{
    Trace("", "operator*(Matrix<Type,M,N>&, ColumnVector<Type,N>&)");

    ColumnVector<Type,M> Result;
    for (unsigned int i = 1; i <= M; ++i) {
        Type element = Type();
        for (unsigned int k = 1; k <= N; ++k) element += Mat[i][k] * Vec[k];
        Result[i] = element;
    }
    return Result;
}
template<typename Type, unsigned int M, unsigned int K, unsigned int N>
Matrix<Type,M,N> operator*(Matrix<Type,M,K> const& Src1,
                           Matrix<Type,K,N> const& Src2)
{
    Trace("", "operator*(Matrix<Type,M,K>&, Matrix<Type,K,N>&)");

    Matrix<Type,M,N> Result;
    for (unsigned int i = 1; i <= M; ++i) {
        for (unsigned int j = 1; j <= N; ++j) {
            Type element = Type();
            for (unsigned int k = 1; k <= K; ++k) element += Src1[i][k] * Src2[k][j];
            Result[i][j] = element;
        }
    }
    return Result;
}
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> operator*(ColumnVector<Type,M> const& Col,
                           RowVector<Type,N> const& Row)
{
    Trace("", "operator*(ColumnVector<Type,M>&, RowVector<Type,N>&)");

    Matrix<Type,M,N> Result;
    for (unsigned int i = 1; i <= M; ++i) {
        for (unsigned int j = 1; j <= N; ++j) {
            Result[i][j] = Col[i] * Row[j];
        }
    }
    return Result;
}
template<typename Type, unsigned int M, unsigned int N>
std::ostream& operator<<(std::ostream& s, Matrix<Type,M,N> const& Src)
{
    Trace("", "operator<<(ostream&, Matrix<Type,M,N>&)");

    Src.Put(s, s.width());
    return s;
}
template<typename Type, unsigned int M, unsigned int N>
std::istream& operator>>(std::istream& s, Matrix<Type,M,N>& Dest)
{
    Trace("", "operator>>(istream&, Matrix&)");

    Dest.Get(s);
    return s;
}
#undef PrintDebugMessage
#undef PrintPivotingMethod
#undef PrintRealLimits
#undef PrintLinearSystem
