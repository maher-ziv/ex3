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

        // iterator classes
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

    // template<typename T>
    // Matrix<T> operator+ (const Matrix<T>& m1, const T& t);
    // template<typename T>
    // Matrix<T> operator+ (const T& t, const Matrix<T>& m2);

    template<typename T, typename S>
    Matrix<T> operator+ (const S& m1, const T& t);

    template<typename T>
    Matrix<T> operator+ (const Matrix<T>& m1, const T& t) {
        return operator<Matrix<T>, T> + (m1, t);
    }
    template<typename T>
    Matrix<T> operator+ (const T& t, const Matrix<T>& m) {
        return operator<T, Matrix<T>> + (m, t);
    }

    template<typename T>
    std::ostream& operator<< (std::ostream& os, const Matrix<T>& m);  // TODO

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
    mtm::Matrix<T>::Matrix (Dimensions dim, const T& initial_val) : dimension (dim) {
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
        typename Matrix<T>::const_iterator it2 = m.begin();
        for (typename Matrix<T>::iterator it = begin(); it != end(); ++it, ++it2) {
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
    Matrix<T> Matrix<T>::Diagonal (int dimension, const T& initial_val) {
        if (dimension <= 0) {
            throw IllegalInitialization();  // TODO test it
        }
        Dimensions dim (dimension, dimension);
        Matrix<T> diagonal (dim);
        for (int i = 0; i < diagonal.height(); i++) {
            diagonal (i, i) = initial_val;
        }
        return diagonal;
    }

    template<typename T>
    Matrix<T> Matrix<T>::transpose() const {
        Dimensions t_dimension (width(), height());
        Matrix<T> t_matrix (t_dimension);
        for (int i = 0; i < width(); i++) {
            for (int j = 0; j < height(); j++) {
                t_matrix (i, j) = matrix[j][i];
            }
        }
        return t_matrix;
    }

    template<typename T>
    Matrix<T> operator+ (const Matrix<T>& m1, const Matrix<T>& m2) {}

    template<typename T>
    std::ostream& mtm::operator<< (std::ostream& os, const Matrix<T>& m) {
        typename Matrix<T>::const_iterator begin = m.begin();
        typename Matrix<T>::const_iterator end = m.end();
        return printMatrix (os, begin, end, m.width());
    }

    template<typename T>
    T& Matrix<T>::operator() (int row_val, int col_val) {
        if (row_val < 0 || row_val >= height() || col_val < 0 || col_val >= width()) {
            throw AccessIllegalElement();
        }
        return matrix[row_val][col_val];
    }

    template<typename T>
    const T Matrix<T>::operator() (int row_val, int col_val) const {
        if (row_val < 0 || row_val >= height() || col_val < 0 || col_val >= width()) {
            throw AccessIllegalElement();
        }
        return matrix[row_val][col_val];
    }

    template<typename T>
    bool all (const Matrix<T>& m) {
        for (typename Matrix<T>::const_iterator it = m.begin(); it != m.end(); ++it) {
            if (!(*it)) {
                return false;
            }
        }
        return true;
    }
    template<typename T>
    bool any (const Matrix<T>& m) {
        for (typename Matrix<T>::const_iterator it = m.begin(); it != m.end(); ++it) {
            if (*it) {
                return true;
            }
        }
        return false;
    }

    template<class T>
    class mtm::Matrix<T>::iterator {
       private:
        const Matrix<T>* matrix;  // the matrix this iterator points to
        int row, col;
        bool is_last;
        iterator (const Matrix<T>* matrix, int row, int col, bool is_last = false);
        friend class Matrix<T>;  // allow IntMatrix to call the c'tor

       public:
        iterator& operator= (const iterator& it) = default;  // TODO test it!!
        iterator (const iterator& it) = default;             // TODO test it!!

        T& operator*() const;
        iterator& operator++();
        iterator operator++ (int);

        bool operator== (const iterator& it) const;
        bool operator!= (const iterator& it) const;
    };

    template<typename T>
    Matrix<T>::iterator::iterator (const Matrix<T>* matrix, int row, int col, bool is_last)
        : matrix (matrix), row (row), col (col), is_last (is_last) {}

    template<typename T>
    typename Matrix<T>::iterator& Matrix<T>::iterator::operator++() {
        if (col == matrix->width()) {
            if (row != matrix->height()) {
                col = 1;
                row++;
                return *this;
            } else {
                is_last = true;
                return *this;
            }
        }
        col++;
        return *this;
    }

    template<typename T>
    typename Matrix<T>::iterator Matrix<T>::iterator::operator++ (int) {
        iterator result = *this;
        ++*this;
        return result;
    }

    template<typename T>
    bool Matrix<T>::iterator::operator== (const iterator& it) const {
        return (row == it.row && col == it.col && is_last == it.is_last);
    }

    template<typename T>
    bool Matrix<T>::iterator::operator!= (const iterator& it) const {
        return !(*this == it);
    }

    template<typename T>
    typename Matrix<T>::iterator Matrix<T>::begin() {
        return iterator (this, 1, 1, false);
    }

    template<typename T>
    typename Matrix<T>::iterator Matrix<T>::end() {
        return iterator (this, height(), width(), true);
    }

    template<typename T>
    T& Matrix<T>::iterator::operator*() const {
        return matrix->matrix[row - 1][col - 1];
    }


    template<class T>
    class mtm::Matrix<T>::const_iterator {
       private:
        const Matrix<T>* matrix;  // the matrix this iterator points to
        int row, col;
        bool is_last;
        const_iterator (const Matrix<T>* matrix, int row, int col, bool is_last = false);
        friend class Matrix<T>;  // allow IntMatrix to call the c'tor

       public:
        const_iterator& operator= (const const_iterator& it) = default;  // TODO test it!!
        const_iterator (const const_iterator& it) = default;             // TODO test it!!

       const T& operator*() const;
        const_iterator& operator++();
        const_iterator operator++ (int);

        bool operator== (const const_iterator& it) const;
        bool operator!= (const const_iterator& it) const;
    };

    template<typename T>
    Matrix<T>::const_iterator::const_iterator (const Matrix<T>* matrix, int row, int col, bool is_last)
        : matrix (matrix), row (row), col (col), is_last (is_last) {}

    template<typename T>
    typename Matrix<T>::const_iterator& Matrix<T>::const_iterator::operator++() {
        if (col == matrix->width()) {
            if (row != matrix->height()) {
                col = 1;
                row++;
                return *this;
            } else {
                is_last = true;
                return *this;
            }
        }
        col++;
        return *this;
    }

    template<typename T>
    typename Matrix<T>::const_iterator Matrix<T>::const_iterator::operator++ (int) {
       typename const_iterator result = *this;
        ++*this;
        return result;
    }

    template<typename T>
    bool Matrix<T>::const_iterator::operator== (const const_iterator& it) const {
        return (row == it.row && col == it.col && is_last == it.is_last);
    }

    template<typename T>
    bool Matrix<T>::const_iterator::operator!= (const const_iterator& it) const {
        return !(*this == it);
    }

    template<typename T>
    const typename  Matrix<T>::const_iterator Matrix<T>::begin() const {
        return const_iterator (this, 1, 1, false);
    }

    template<typename T>
   const typename Matrix<T>::const_iterator Matrix<T>::end() const {
        return const_iterator (this, height(), width(), true);
    }

    template<typename T>
    const T& Matrix<T>::const_iterator::operator*() const {
        return matrix->matrix[row - 1][col - 1];
    }

}  // namespace mtm

#endif  // EX3_MATRIX_H
