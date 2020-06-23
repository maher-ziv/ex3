#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H

#include <iostream>
#include <string>

#include "Auxiliaries.h"

namespace mtm {
    template<typename U>
    class Array;
    template<typename T>
    class Matrix;
    template<typename T>
    Matrix<T> operator+ (const Matrix<T>& m1, const Matrix<T>& m2);
    template<typename T>
    std::ostream& operator<< (std::ostream& os, const Matrix<T>& m);

    template<typename T>
    class Matrix {
       private:
        mtm::Array<T> matrix ;
        Dimensions dimension;

       public:
        Matrix() = delete;
        Matrix (Dimensions dim, const T& initial_val = T());
        // Matrix (T t);
        Matrix (const Matrix& m);
        ~Matrix();

        static Matrix Diagonal (const int dimension, const T& initial_val = T());
        Matrix transpose() const;
        //  Matrix apply(class()) const;// TODO test it
        int size() const;
        int height() const;
        int width() const;

        Matrix& operator= (const Matrix& m);
        Matrix operator-() const;
        Matrix& operator+= (T t);  // TODO test it

        friend Matrix<T> operator+<T> (const Matrix<T>& m1, const Matrix<T>& m2);
        T& operator() (int row_val, int col_val);
        const T operator() (int row_val, int col_val) const;

        Matrix<bool> operator< (const T x) const;
        Matrix<bool> operator> (const T x) const;
        Matrix<bool> operator<= (const T x) const;
        Matrix<bool> operator>= (const T x) const;
        Matrix<bool> operator== (const T x) const;
        Matrix<bool> operator!= (const T x) const;

        friend std::ostream& operator<<<T> (std::ostream& os, const Matrix& m);

        class iterator;
        iterator begin();  // TODO check if const needed
        iterator end();

        class const_iterator;
        const const_iterator begin() const;
        const const_iterator end() const;

        // Matrix<T>::~Matrix() { //TODO לבדוק אם של Aarray מספיק

        class AccessIllegalElement;
        class IllegalInitialization;
        class DimensionMismatch;

    };  // class Matrix
    // Exceptions
    template<typename T>
    class Matrix<T>::AccessIllegalElement {
       public:
        const std::string what() const {
            return "Mtm matrix error: An attempt to access an illegal element";
        }
    };
    template<typename T>
    class Matrix<T>::IllegalInitialization {
       public:
        const std::string what() const {
            return "Mtm matrix error: Illegal initialization values";
        }
    };
    template<typename T>
    class Matrix<T>::DimensionMismatch {
       public:
        Dimensions dimension1, dimension2;
        DimensionMismatch (Dimensions dim1, Dimensions dim2) : dimension1 (dim1), dimension2 (dim2) {}
        const std::string what() const {
            return "Mtm matrix error: Dimensionmismatch: " + dimension1.toString() + dimension2.toString();
        }
    };

    template<typename T>
    Matrix<T>::Matrix (Dimensions dim, const T& initial_val) : matrix (dim.getRow(), dim.getRow()), dimension (dim) {
        for (int i = 0; i < height(); i++) {
            for (int j = 0; j < width(); j++) {
                matrix (i, j) = initial_val;
            }
        }
    }

    template<typename T>
    Matrix<T>::Matrix (const Matrix<T>& m) : matrix (m.height(), m.width()), dimension (m.dimension) {
        typename Matrix<T>::const_iterator it2 = m.begin();
        for (typename Matrix<T>::iterator it = begin(); it != end(); ++it, ++it2) {
            *it = *it2;
        }
    }

    template<typename T>
    Matrix<T>& Matrix<T>::operator= (const Matrix<T>& m) {
        // if (this == &m) {
        //     return *this; //TODO לבדןק שבאמת אין צורך לזה
        // }
        Array<T> tmp (m.height(), m.width());
        for (int i = 0; i < m.height(); i++) {
            for (int j = 0; j < m.width(); j++) {
                tmp (i, j) = m.matrix (i, j);  // TODO לבדוק אם פה צריך לבדוק שההשמה הצליחה
            }
        }
        matrix = tmp;
        dimension = m.dimension;
        return *this;
    }

    template<typename T>
    Matrix<T> Matrix<T>::Diagonal (int dimension, const T& initial_val) {
        if (dimension <= 0) {
            throw Matrix::IllegalInitialization();  // TODO test it
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
                t_matrix (i, j) = matrix (j, i);
            }
        }
        return t_matrix;
    }

    template<class T>
    Matrix<T> Matrix<T>::operator-() const {
        Matrix<T> tmp (*this);
        for (typename Matrix<T>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
            *it *= -1;
        }
        return tmp;
    }

    template<typename T>
    Matrix<T> operator+ (const mtm::Matrix<T>& m1, const mtm::Matrix<T>& m2) {
        if (m1.height() != m2.height() || m1.width() != m2.width()) {
            mtm::Dimensions dim1 (m1.height(), m1.width());
            Dimensions dim2 (m2.height(), m2.width());
            typename Matrix<T>::DimensionMismatch res (dim1, dim2);
            throw res;
        }
        Matrix<T> tmp (m1);
        typename Matrix<T>::const_iterator it1 = m1.begin(), it2 = m2.begin();
        for (typename Matrix<T>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
            *it = *it1 + *it2;
        }
        return tmp;
    }
    template<typename T>
    Matrix<T> operator- (const Matrix<T>& m1, const Matrix<T>& m2) {
        return m1 + (-m2);
    }
    template<class T>
    Matrix<T>& Matrix<T>::operator+= (T t) {
        for (typename Matrix<T>::iterator it = begin(); it != end(); ++it) {
            *it += t;
        }
        return *this;
    }

    template<typename T>  // TODO לבדןק אפ אפשר לקצר
    Matrix<T> operator+ (const Matrix<T>& m1, T t) {
        Matrix<T> tmp (m1);  // TODO לבדוק אם זה בסדר והוא באמת מחזיר עותק
        for (typename Matrix<T>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
            *it += t;
        }
        return tmp;
    }

    template<typename T>
    Matrix<T> operator+ (T t, const Matrix<T>& m2) {
        return m2 + t;
    }

    template<typename T>
    Matrix<bool> Matrix<T>::operator< (T x) const {
        Matrix<bool> tmp (this->dimension);
        for (int i = 0; i < height(); i++) {
            for (int j = 0; j < width(); j++) {
                tmp (i, j) = (*this) (i, j) < x ? true : false;
            }
        }
        return tmp;
    }
    template<class T>
    Matrix<bool> Matrix<T>::operator> (T x) const {
        Matrix<bool> tmp (this->dimension);
        for (int i = 0; i < height(); i++) {
            for (int j = 0; j < width(); j++) {
                tmp (i, j) = (*this) (i, j) > x ? true : false;
            }
        }
        return tmp;
    }
    template<typename T>
    Matrix<bool> Matrix<T>::operator<= (T x) const {
        Matrix<bool> tmp = *this > x;
        return tmp != 1;  // TODO לשאול אם זה נחשב למספר קסם
    }
    template<typename T>
    Matrix<bool> Matrix<T>::operator>= (T x) const {
        Matrix<bool> tmp = *this < x;
        return tmp != 1;  // TODO לשאול אם זה נחשב למספר קסם
    }
    template<typename T>
    Matrix<bool> Matrix<T>::operator== (T x) const {
        Matrix<bool> tmp (this->dimension);
        for (int i = 0; i < this->height(); i++) {
            for (int j = 0; j < width(); j++) {
                tmp (i, j) = (*this) (i, j) == x ? true : false;
            }
        }
        return tmp;
    }
    template<typename T>
    Matrix<bool> Matrix<T>::operator!= (T x) const {
        Matrix<bool> tmp = ((*this) == x);
        return tmp == 0;  // TODO לשאול אם זה נחשב למספר קסם
    }
    template<typename T>
    std::ostream& operator<< (std::ostream& os, const Matrix<T>& m) {
        typename Matrix<T>::const_iterator begin = m.begin();
        typename Matrix<T>::const_iterator end = m.end();
        return printMatrix (os, begin, end, m.width());
    }

    template<typename T>
    T& Matrix<T>::operator() (int row_val, int col_val) {
        if (row_val < 0 || row_val >= height() || col_val < 0 || col_val >= width()) {
            throw AccessIllegalElement();
        }
        return matrix (row_val, col_val);
    }

    template<typename T>
    const T Matrix<T>::operator() (int row_val, int col_val) const {
        if (row_val < 0 || row_val >= height() || col_val < 0 || col_val >= width()) {
            throw AccessIllegalElement();
        }
        return matrix (row_val, col_val);
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
    //-- end-of Matrix ---

    template<class T>
    class mtm::Matrix<T>::iterator {
       private:
        Matrix<T>* matrix;  // the matrix this iterator points to
        int row, col;
        bool is_last;
        iterator (Matrix<T>* matrix, int row, int col, bool is_last = false);
        friend class Matrix<T>;  // allow IntMatrix to call the c'tor

       public:
        iterator& operator= (const iterator& it) = default;  // TODO test it!!
        iterator (const iterator& it) = default;             // TODO test it!!

        T& operator*();
        iterator& operator++();
        iterator operator++ (int);

        bool operator== (const iterator& it) const;
        bool operator!= (const iterator& it) const;
    };

    template<typename T>
    Matrix<T>::iterator::iterator (Matrix<T>* matrix, int row, int col, bool is_last)
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
    T& Matrix<T>::iterator::operator*() {
        return matrix->matrix (row - 1, col - 1);
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

        const T operator*() const;
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
        const_iterator result = *this;
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
    const typename Matrix<T>::const_iterator Matrix<T>::begin() const {
        return const_iterator (this, 1, 1, false);
    }

    template<typename T>
    const typename Matrix<T>::const_iterator Matrix<T>::end() const {
        return const_iterator (this, height(), width(), true);
    }

    template<typename T>
    const T Matrix<T>::const_iterator::operator*() const {
        return matrix->matrix (row - 1, col - 1);
    }

    // end of const_iterator

    template<typename T>
    class Array {
       public:
        T** data;
        int row_size;
        int col_size;
        friend class mtm::Matrix<T>;

        Array (int row = 1, int col = 1) : row_size (row), col_size (col) {
            data = new T*[row_size];
            for (int i = 0; i < row_size; i++) {  // TODO check the while !!!
                try {
                    data[i] = new T[col_size];
                } catch (const std::bad_alloc& e) {
                    for (int j = 0; j < i; j++) {
                        delete[] data[j];
                    }
                    delete[] data;
                    throw e;
                }
                for (int j = 0; j < col_size; j++) {
                    data[i][j] = T();
                }
            }
        }

        Array& operator= (const Array& m) {
            if (this == &m) {
                return *this;
            }
            T** tmp_data = new T*[m.row_size];
            for (int i = 0; i < m.row_size; i++) {
                try {
                    tmp_data[i] = new T[m.col_size];
                } catch (const std::bad_alloc& e) {  // TODO check if need to catch another throw
                    for (int j = 0; j < i; j++) {
                        delete[] tmp_data[j];
                    }
                    delete[] tmp_data;
                    throw e;
                }
                for (int j = 0; j < m.col_size; j++) {
                    tmp_data[i][j] = m.data[i][j];
                }
            }
            data = tmp_data;
            row_size = m.row_size;
            col_size = m.col_size;
            return *this;
        }

        ~Array() {
            for (int i = 0; i < row_size; i++) {
                delete[] data[i];
            }
            delete[] data;
        }

        T& operator() (int row_val, int col_val) {
            if (row_val < 0 || row_val >= row_size || col_val < 0 || col_val >= col_size) {
                throw typename Matrix<T>::AccessIllegalElement();  // TODO test it
            }
            return data[row_val][col_val];
        }

        const T operator() (int row_val, int col_val) const {
            if (row_val < 0 || row_val >= row_size || col_val < 0 || col_val >= col_size) {
                throw typename Matrix<T>::AccessIllegalElement();  // TODO test it
            }

            return data[row_val][col_val];
        }

        Array (const Array& arr) : row_size (arr.row_size), col_size (arr.col_size) {
            data = new T*[row_size];
            for (int i = 0; i < row_size; i++) {  // TODO check the while !!!
                try {
                    data[i] = new T[col_size];
                } catch (const std::bad_alloc& e) {
                    for (int j = 0; j < i; j++) {
                        delete[] data[j];
                    }
                    delete[] data;
                    throw e;
                }
                for (int j = 0; j < col_size; j++) {
                    data[i][j] = arr.data[i][j];
                }
            }
        }

         Array() = delete; //TODO לבדוק אם צריך
    };  // Array class

}  // namespace mtm

// namespace Array {

// }  // namespace Array

#endif  // EX3_MATRIX_H
