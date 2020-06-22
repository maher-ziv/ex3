#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H

#include <iostream>
#include <string>

#include "Auxiliaries.h"

namespace mtm {

    template < typename T >
    class Matrix {
       private:
        T** matrix;
        mtm::Dimensions dimension;

       public:
        Matrix() = delete;
        Matrix (mtm::Dimensions dim, const T& initial_val = T());
        // IntMatrix (int scalar_val);
        Matrix (const Matrix& m);
        ~Matrix();

        static Matrix Diagonal (const int dimension, const T& initial_val = T());
        Matrix transpose() const;

        int size() const;
        int height() const;
        int width() const;

        Matrix& operator= (const Matrix& m);
        Matrix operator-() const;
        Matrix& operator+= (const T& num);

        int& operator() (int row_val, int col_val);
        const int operator() (int row_val, int col_val) const;

        Matrix< bool > operator< (const T x) const;
        Matrix< bool > operator> (const T x) const;
        Matrix<bool> operator<= (const T x const;
        Matrix<bool> operator>= (const T x) const;
        Matrix<bool> operator== (const T x) const;
        Matrix<bool> operator!= (const T x) const;

        friend std::ostream& operator<< (std::ostream& os, const Matrix& m);

        class iterator;
        iterator begin();  // TODO check if const needed
        iterator end();
        class const_iterator;
        const const_iterator begin() const;
        const const_iterator end() const;

    };  // class Matrix

    template < typename T >
    Matrix< T > operator+ (const Matrix< T >& m1, const Matrix< T >& m2);
    template < typename T >
    Matrix< T > operator- (const Matrix< T >& m1, const Matrix< T >& m2);

    template < typename T >
    Matrix< T > operator+ (const Matrix< T >& m1, const T& t);
    template < typename T >
    Matrix< T > operator+ (const T& t, const Matrix< T >& m2);

    template < typename T >
    std::ostream& operator<< (std::ostream& os, const Matrix< T >& m);  // TODO
    template < typename T >
    bool all (const Matrix< T >& a);
    template < typename T >
    bool any (const Matrix< T >& a);

}  // namespace mtm

#endif  // EX3_MATRIX_H
