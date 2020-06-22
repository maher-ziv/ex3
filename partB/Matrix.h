#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H

#include <iostream>
#include <string>

#include "Auxiliaries.h"

namespace mtm {

    template<typename T>
    class Matrix {
        private:
        T** matrix;
        Dimensions dimension;
        void allocate_space();

        public:
        Matrix() = delete;
        Matrix (Dimensions dim, const T& initial_val = T());
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

        T& operator() (int row_val, int col_val);
        const T operator() (int row_val, int col_val) const;

        Matrix<bool> operator< (const T x) const;
        Matrix<bool> operator> (const T x) const;
        Matrix<bool> operator<= (const T x) const;
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

        // Exceptions
        class AccessIllegalElement {
            public:
            const std::string what() const {
                return "Mtm matrix error: An attempt to access an illegal element";
            }
        };
        class IllegalInitialization {
            public:
            const std::string what() const {
                return "Mtm matrix error: Illegal initialization values";
            }
        };
        class DimensionMismatch {
            public:
            Dimensions dimension1, dimension2;
            DimensionMismatch (Dimensions dim1, Dimensions dim2) : dim1 (dimension1), dim2 (dimension2) {}
            const std::string what() const {
                return "Mtm matrix error: Dimensionmismatch: " + Dimensions::toString (dimension1) +
                       Dimensions::toString (dimension2);
            }
        };

    };  // class Matrix

    template<typename T>
    Matrix<T> operator+ (const Matrix<T>& m1, const Matrix<T>& m2);
    template<typename T>
    Matrix<T> operator- (const Matrix<T>& m1, const Matrix<T>& m2);

    template<typename T>
    Matrix<T> operator+ (const Matrix<T>& m1, const T& t);
    template<typename T>
    Matrix<T> operator+ (const T& t, const Matrix<T>& m2);

    template<typename T>
    std::ostream& operator<< (std::ostream& os, const Matrix<T>& m);  // TODO

    template<typename T>
    bool all (const Matrix<T>& a);
    template<typename T>
    bool any (const Matrix<T>& a);


    template<typename T>
    void mtm::Matrix<T>::allocate_space() {
        matrix = new T*[height()];
        for (int i = 0; i < height(); i++) {  // TODO check the while !!!
            try {
                matrix[i] = new T[width()];
            } catch (const std::bad_alloc& e) {
                for (int j = 0; j < i; j++) {
                    delete[] matrix[j];
                }
                delete[] matrix;
                throw e;
            }
        }
    }

    template<typename T>
    mtm::Matrix<T>::Matrix(Dimensions dim, const T& initial_val) : dimension(dim) {
        allocate_space();
        for (int i = 0; i < height(); i++) {
            for (int j = 0; j < width(); j++) {
                matrix[i][j] = initial_val;
            }
        }
    }


    template<typename T>
    Matrix<T>::Matrix (const Matrix<T>& m) : dimension (m.dimension) {
        allocate_space();
        Matrix<T>::const_iterator it2 = m.begin();
        for (Matrix<T>::iterator it = begin(); it != end(); ++it, ++it2) {
            *it = *it2;
        }
    }

    template<typename T>
    Matrix<T>::~Matrix() {
        for (int i = 0; i < height(); i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator= (const Matrix<T>& m) {
        if (this == &m) {
            return *this;
        }
        T** tmp_data = new T*[m.height()];
        for (int i = 0; i < m.height(); i++) {
            try {
                tmp_data[i] = new T[m.width()];
            } catch (const std::bad_alloc& e) {  // TODO check if need to catch another throw
                for (int j = 0; j < i; j++) {
                    delete[] tmp_data[j];
                }
                delete[] tmp_data;
                throw e;
            }
            for (int j = 0; j < m.width(); j++) {
                tmp_data[i][j] = m.matrix[i][j];
            }
        }
        matrix = tmp_data;
        dimension = m.dimension;
        return *this;
    }

    template<typename T>
    mtm::Matrix<T> mtm::Matrix<T>::Diagonal (int dimension, const T& initial_val = T()){
        if ( dimension <= 0 ){
            throw IllegalInitialization(); // TODO test it
        }



    }





}  // namespace mtm

#endif  // EX3_MATRIX_H
