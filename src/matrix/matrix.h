#ifndef RM_MATRIX_H
#define RM_MATRIX_H
// [[$Id: matrix.nw,v 1.1 2005/08/10 12:58:45 kaiip Exp $]]

//#define DEBUG

#include <iostream>
#include <iomanip>
#include <limits>
#include <matrix/real.h>
//#include <matrix/limits.h>
#include <matrix/rowvector.h>
#include <matrix/columnvector.h>

typedef enum{NoPivoting, PartialPivoting, CompletePivoting} PivotType;

template<typename Type, unsigned int M, unsigned int N>
class Matrix {
public:
    Matrix();
    #ifdef PARAM
    Matrix(Type const FirstValue ...);
    #endif
    Matrix(Matrix<Type,M,N> const& Src);
    virtual ~Matrix();
    unsigned int const Rows() const;
    RowVector<Type,N> Row(unsigned int const Index) const;
    RowVector<Type,N> Row(unsigned int const Index, RowVector<Type,N> const& NewRow);
    unsigned int const Columns() const;
    ColumnVector<Type,M> Column(unsigned int const Index) const;
    ColumnVector<Type,M> Column(unsigned int const Index,
                                ColumnVector<Type,M> const& NewColumn);
    RowVector<Type,N>&       Value(unsigned int const Index);
    RowVector<Type,N> const& Value(unsigned int const Index) const;
    #if 0
    Type Norm(unsigned int const p = 1) const;
    #else
    Real Norm(unsigned int const p = 1) const;
    #endif
    Matrix<Type,N,M> T() const;
    void Clear();
    void Put(std::ostream& s, int width = 0) const;
    void Get(std::istream& s);
    Matrix const& operator=(Matrix const& Src);
    RowVector<Type,N>&       operator[](unsigned int const Index);
    RowVector<Type,N> const& operator[](unsigned int const Index) const;
    bool const operator==(Matrix<Type,M,N> const& Src) const;
    bool const operator!=(Matrix<Type,M,N> const& Src) const;
    Matrix<Type,M,N> const& operator+() const;
    Matrix<Type,M,N> operator+(Matrix<Type,M,N> const& Src) const;
    Matrix<Type,M,N> const& operator+=(Matrix<Type,M,N> const& Src);
    Matrix<Type,M,N> operator-() const;
    Matrix<Type,M,N> operator-(Matrix<Type,M,N> const& Src) const;
    Matrix<Type,M,N> const& operator-=(Matrix<Type,M,N> const& Src);
    Matrix<Type,M,N> operator*(Type const& Factor) const;
    Matrix<Type,M,N> const& operator*=(Type const& Factor);
    Matrix<Type,M,N> operator/(Type const& Factor) const;
    Matrix<Type,M,N> const& operator/=(Type const& Factor);
protected:
    /* No Protected Members so far */
private:
    ColumnVector<RowVector<Type,N>,M> data;
    /* No Private Member Functions so far*/
    /* No Friends so far */
};

#if 0
template<typename Type, unsigned int M, unsigned int N>
Type Norm(Matrix<Type,M,N> const& Mat, unsigned int const p = 1);
#else
template<typename Type, unsigned int M, unsigned int N>
Real Norm(Matrix<Type,M,N> const& Mat, unsigned int const p = 1);
#endif
template<typename Type, unsigned int M>
Matrix<Type,M,M> Inverse(Matrix<Type,M,M> const& A, Type const epsilon = Type());
template<typename Type, unsigned int M>
ColumnVector<Type,M> 
Solve(Matrix<Type,M,M> const& Amatrix, ColumnVector<Type,M> const& Bvector,
      PivotType const Pivoting = NoPivoting, Type const epsilon = Type());
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> 
Solve(Matrix<Type,M,M> const& Amatrix, Matrix<Type,M,N> const& Bmatrix,
      PivotType const Pivoting = NoPivoting, Type const epsilon = Type());
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> operator*(Type const& Factor, Matrix<Type,M,N> const& Src);
template<typename Type, unsigned int M, unsigned int N>
RowVector<Type,N> operator*(RowVector<Type,M> const& Vec,
                            Matrix<Type,M,N> const&  Mat);
template<typename Type, unsigned int M, unsigned int N>
ColumnVector<Type,M> operator*(Matrix<Type,M,N> const& Mat,
                               ColumnVector<Type,N> const& Vec);
template<typename Type, unsigned int M, unsigned int K, unsigned int N>
Matrix<Type,M,N> operator*(Matrix<Type,M,K> const& Src1,
                           Matrix<Type,K,N> const& Src2);
template<typename Type, unsigned int M, unsigned int N>
Matrix<Type,M,N> operator*(ColumnVector<Type,M> const& Col, RowVector<Type,N> const& Row);
template<typename Type, unsigned int M, unsigned int N>
std::ostream& operator<<(std::ostream& s, Matrix<Type,M,N> const& Src);
template<typename Type, unsigned int M, unsigned int N>
std::istream& operator>>(std::istream& s, Matrix<Type,M,N>& Dest);

#ifdef INSTANTIATE
#include <matrix/matrix.C>
#endif
#endif
