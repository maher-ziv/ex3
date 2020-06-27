#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H

#include <iostream>
#include <string>

#include "Auxiliaries.h"

namespace mtm {
    template<typename T>
    class Matrix;
    template<typename T>
    Matrix<T> operator+ (const Matrix<T>& m1, const Matrix<T>& m2);
    template<typename T>
    std::ostream& operator<< (std::ostream& os, const Matrix<T>& m);

    template<typename T>
    class Matrix {
        private:
        T** matrix;
        mtm::Dimensions dimension;
        void allocate_space();
        template<typename PT>  // PT = pointer_type
        class T_iterator;

        public:
        Matrix() = delete;
        Matrix (Dimensions dim, const T& initial_val = T());
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
        friend Matrix<T> operator+<T> (const Matrix<T>& m1, const Matrix<T>& m2);

        T& operator() (int row_val, int col_val);
        const T operator() (int row_val, int col_val) const;

        Matrix<bool> operator< (const T& x) const;
        Matrix<bool> operator> (const T& x) const;
        Matrix<bool> operator<= (const T& x) const;
        Matrix<bool> operator>= (const T& x) const;
        Matrix<bool> operator== (const T& x) const;
        Matrix<bool> operator!= (const T& x) const;

        friend std::ostream& operator<<<T> (std::ostream& os, const Matrix& m);

        typedef T_iterator<T> iterator;
        iterator begin();  // TODO check if const needed
        iterator end();

        typedef T_iterator<const T> const_iterator;
        const const_iterator begin() const;
        const const_iterator end() const;

        template<typename Predicate>
        Matrix<T> apply (Predicate pred) const;

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
        Dimensions dimension1, dimension2;

        public:
        DimensionMismatch (Dimensions dim1, Dimensions dim2) : dimension1 (dim1), dimension2 (dim2) {}
        const std::string what() const {
            return "Mtm matrix error: Dimension mismatch: " + dimension1.toString() + " " + dimension2.toString();
        }
    };

    template<typename T>
    int Matrix<T>::height() const {
        return dimension.getRow();
    }
    template<typename T>
    int Matrix<T>::width() const {
        return dimension.getCol();
    }
    template<typename T>
    int Matrix<T>::size() const {
        return (height() * width());
    }

    template<typename T>
    void Matrix<T>::allocate_space() {
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
    Matrix<T>::Matrix (Dimensions dim, const T& initial_val) : dimension (dim) {
        if (dim.getRow() <= 0 || dim.getCol() <= 0) {
            throw Matrix<T>::IllegalInitialization();
        }
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
                for (int j = 0; j < m.width(); j++) {
                    tmp_data[i][j] = m.matrix[i][j];
                }
            } catch (const std::bad_alloc& e) {  // TODO check if need to catch another throw
                for (int j = 0; j < i; j++) {
                    delete[] tmp_data[j];
                }
                delete[] tmp_data;
                throw e;
            } catch (...) {
                for (int j = 0; j < i; j++) {
                    delete[] tmp_data[j];
                }
                delete[] tmp_data;
                throw;
            }
        }
        matrix = tmp_data;
        dimension = m.dimension;
        return *this;
    }

    template<typename T>
    Matrix<T> Matrix<T>::Diagonal (int dimension, const T& initial_val) {
        if (dimension <= 0) {
            throw typename Matrix<T>::IllegalInitialization();  // TODO test it
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
    std::ostream& operator<< (std::ostream& os, const Matrix<T>& m) {
        return printMatrix (os, m.begin(), m.end(), m.width());
    }

    template<typename T>
    T& Matrix<T>::operator() (int row_val, int col_val) {
        if (row_val < 0 || row_val >= height() || col_val < 0 || col_val >= width()) {
            throw typename Matrix<T>::AccessIllegalElement();
        }
        return matrix[row_val][col_val];
    }

    template<typename T>
    const T Matrix<T>::operator() (int row_val, int col_val) const {
        if (row_val < 0 || row_val >= height() || col_val < 0 || col_val >= width()) {
            throw typename Matrix<T>::AccessIllegalElement();
        }
        return matrix[row_val][col_val];
    }

    template<class T>
    Matrix<T> Matrix<T>::operator-() const {
        Matrix<T> tmp (*this);
        for (typename Matrix<T>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
            (*it) *= -1;
        }
        return tmp;
    }

    template<typename T>
    Matrix<T> operator+ (const Matrix<T>& m1, const Matrix<T>& m2) {
        if (m1.height() != m2.height() || m1.width() != m2.width()) {
            Dimensions dim1 (m1.height(), m1.width());
            Dimensions dim2 (m2.height(), m2.width());
            //   typename Matrix<T>::DimensionMismatch res (dim1, dim2);
            throw typename Matrix<T>::DimensionMismatch (dim1, dim2);
        }
        Matrix<T> tmp (m1);
        typename Matrix<T>::const_iterator it1 = m1.begin(), it2 = m2.begin();
        for (typename Matrix<T>::iterator it = tmp.begin(); it != tmp.end(); ++it, ++it2, ++it1) {
            *it = *it1 + *it2;
        }
        return tmp;
    }
    template<typename T>
    Matrix<T> operator- (const Matrix<T>& m1, const Matrix<T>& m2) {
        return m1 + (-m2);
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator+= (const T& x) {
        for (typename Matrix<T>::iterator it = begin(); it != end(); ++it) {
            *it += x;
        }
        return *this;
    }

    template<typename T>  // TODO לבדןק אפ אפשר לקצר
    Matrix<T> operator+ (const Matrix<T>& m1, const T& t) {
        Matrix<T> tmp (m1);  // TODO לבדוק אם זה בסדר והוא באמת מחזיר עותק
        for (typename Matrix<T>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
            *it += t;
        }
        return tmp;
    }

    template<typename T>
    Matrix<T> operator+ (const T& t, const Matrix<T>& m) {
        Matrix<T> tmp (m);
        for (typename Matrix<T>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
            *it = t + *it;
        }
        return tmp;
    }

    template<typename T>
    Matrix<bool> Matrix<T>::operator< (const T& x) const {
        Matrix<bool> tmp (this->dimension);
        for (int i = 0; i < height(); i++) {
            for (int j = 0; j < width(); j++) {
                tmp (i, j) = (*this) (i, j) < x ? true : false;
            }
        }
        return tmp;
    }
    template<class T>
    Matrix<bool> Matrix<T>::operator> (const T& x) const {
        Matrix<bool> tmp (this->dimension);
        for (int i = 0; i < height(); i++) {
            for (int j = 0; j < width(); j++) {
                tmp (i, j) = (*this) (i, j) > x ? true : false;
            }
        }
        return tmp;
    }
    template<typename T>
    Matrix<bool> Matrix<T>::operator<= (const T& x) const {
        Matrix<bool> tmp = *this > x;
        return tmp != 1;  // TODO לשאול אם זה נחשב למספר קסם
    }
    template<typename T>
    Matrix<bool> Matrix<T>::operator>= (const T& x) const {
        Matrix<bool> tmp = *this < x;
        return tmp != 1;  // TODO לשאול אם זה נחשב למספר קסם
    }
    template<typename T>
    Matrix<bool> Matrix<T>::operator== (const T& x) const {
        Matrix<bool> tmp (this->dimension);
        for (int i = 0; i < this->height(); i++) {
            for (int j = 0; j < width(); j++) {
                tmp (i, j) = (*this) (i, j) == x ? true : false;
            }
        }
        return tmp;
    }
    template<typename T>
    Matrix<bool> Matrix<T>::operator!= (const T& x) const {
        Matrix<bool> tmp = ((*this) == x);
        return tmp == 0;  // TODO לשאול אם זה נחשב למספר קסם
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

    template<typename T>
    template<typename Predicate>
    Matrix<T> Matrix<T>::apply (Predicate pred) const {
        Matrix<T> tmp (dimension);
        typename Matrix<T>::const_iterator it = begin();
        for (typename Matrix<T>::iterator it2 = tmp.begin(); it2 != tmp.end(); ++it2, ++it) {
            *it2 = pred (*it);
        }
        return tmp;
    }

    // end-of Matrix

    template<typename T>
    template<typename PT>  // PT = pointer_type
    class Matrix<T>::T_iterator {
        private:
        const Matrix<T>* matrix;  // the matrix this iterator points to
        int row, col;
        bool is_last;
        T_iterator (const Matrix<T>* matrix, int row, int col, bool is_last = false)
            : matrix (matrix), row (row), col (col), is_last (is_last) {}
        friend class Matrix<T>;  // allow IntMatrix to call the c'tor

        public:
        T_iterator& operator= (const T_iterator& it) = default;  // TODO test it!!
        T_iterator (const T_iterator& it) = default;             // TODO test it!!

        PT& operator*() const {
            if (is_last || matrix->height() <= row - 1 || matrix->width() <= col - 1) {  // TODO
                throw typename Matrix<T>::AccessIllegalElement();
            }
            return matrix->matrix[row - 1][col - 1];
        }
        T_iterator& operator++() {
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
        T_iterator operator++ (int) {
            // return *this++;  // TODO test it
            T_iterator result = *this;
            ++*this;
            return result;
        }

        bool operator== (const T_iterator& it) const {
            return (row == it.row && col == it.col && is_last == it.is_last);
        }
        bool operator!= (const T_iterator& it) const {
            return !(*this == it);
        }
    };

    template<typename T>
    typename Matrix<T>::iterator Matrix<T>::begin() {
        return iterator (this, 1, 1, false);
    }

    template<typename T>
    typename Matrix<T>::iterator Matrix<T>::end() {
        return iterator (this, height(), width(), true);
    }

    template<typename T>
    const typename Matrix<T>::const_iterator Matrix<T>::begin() const {
        return const_iterator (this, 1, 1, false);
    }

    template<typename T>
    const typename Matrix<T>::const_iterator Matrix<T>::end() const {
        return const_iterator (this, height(), width(), true);
    }

    /*
        template<class T>
        class Matrix<T>::iterator {
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
            if (is_last || matrix->height() <= row - 1 || matrix->width() <= col - 1) {  // TODO
                throw typename Matrix<T>::AccessIllegalElement();
            }
            return matrix->matrix[row - 1][col - 1];
        }
        // end-iterator

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
        const T& Matrix<T>::const_iterator::operator*() const {
            if (is_last || matrix->height() <= row - 1 || matrix->width() <= col - 1) {
                throw typename Matrix<T>::AccessIllegalElement();  // TODO
            }
            return matrix->matrix[row - 1][col - 1];
        }

        /*
        // TODO ךבדוק אם אפשר לסדר את זה שיעבוד

            template<class T>
            class Matrix<T>::T_iterator {
               public:
                const Matrix<T>* matrix;  // the matrix this iterator points to
                int row, col;
                bool is_last;
                T_iterator (const Matrix<T>* matrix, int row, int col, bool is_last = false);
                friend class Matrix<T>;  // allow IntMatrix to call the c'tor

               //public:
                T_iterator& operator= (const T_iterator& it) = default;  // TODO test it!!
                T_iterator (const T_iterator& it) = default;             // TODO test it!!

                T& operator*() const;
                T_iterator& operator++();
                T_iterator operator++ (int);

                bool operator== (const T_iterator& it) const;
                bool operator!= (const T_iterator& it) const;
            };


            template<typename T>
            Matrix<T>::T_iterator::T_iterator (const Matrix<T>* matrix, int row, int col, bool is_last)
                : matrix (matrix), row (row), col (col), is_last (is_last) {}

            template<typename T>
            typename Matrix<T>::T_iterator& Matrix<T>::T_iterator::operator++() {
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
            typename Matrix<T>::T_iterator Matrix<T>::T_iterator::operator++ (int) {
                T_iterator result = *this;
                ++*this;
                return result;
            }

            template<typename T>
            bool Matrix<T>::T_iterator::operator== (const T_iterator& it) const {
                return (row == it.row && col == it.col && is_last == it.is_last);
            }

            template<typename T>
            bool Matrix<T>::T_iterator::operator!= (const T_iterator& it) const {
                return !(*this == it);
            }


            template<class T>
            class mtm::Matrix<T>::iterator : public Matrix<T>::T_iterator {
               private:
                iterator (const Matrix<T>* matrix, int row, int col, bool is_last = false);
                friend class Matrix<T>;  // allow IntMatrix to call the c'tor
               public:
                T& operator*() const;

            };


            template<typename T>
            Matrix<T>::iterator::iterator (const Matrix<T>* matrix, int row, int col, bool is_last)
                : T_iterator(matrix,row,col,is_last) {}

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
                if ( is_last|| matrix->height() <= row - 1 || matrix->width() <= col - 1) {  // TODO
                    throw typename Matrix<T>::AccessIllegalElement();
                }
                return matrix->matrix[row - 1][col - 1];
            }
          //iterator

            template<class T>
            class mtm::Matrix<T>::const_iterator {
               private:
                const_iterator (const Matrix<T>* matrix, int row, int col, bool is_last = false);
                friend class Matrix<T>;  // allow IntMatrix to call the c'tor
               public:
                const T& operator*() const;

            };

            template<typename T>
            Matrix<T>::const_iterator::const_iterator (const Matrix<T>* matrix, int row, int col, bool is_last)
                : T_iterator(matrix,row,col,is_last) {}

            template<typename T>
            const typename Matrix<T>::const_iterator Matrix<T>::begin() const {
                return const_iterator (this, 1, 1, false);
            }

            template<typename T>
            const typename Matrix<T>::const_iterator Matrix<T>::end() const {
                return const_iterator (this, height(), width(), true);
            }

            template<typename T>
            const T& Matrix<T>::const_iterator::operator*() const {
                if (is_last || matrix->height() <= row - 1 || matrix->width() <= col - 1) {
                    throw typename Matrix<T>::AccessIllegalElement(); //TODO
                }
                return matrix->matrix[row - 1][col - 1];
            }
        */
}  // namespace mtm

#endif  // EX3_MATRIX_H
