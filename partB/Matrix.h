#ifndef EX3_MATRIX_H
#define EX3_MATRIX_H

#include <cstring>
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
        static T** allocate_space (int row_size, int col_size);
        static T** allocate_and_copy (T** src, int row_size, int col_size);
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
    class Matrix<T>::AccessIllegalElement : public std::exception {
       public:
        const char* what() const noexcept {
            return "Mtm matrix error: An attempt to access an illegal element";
        }
    };
    template<typename T>
    class Matrix<T>::IllegalInitialization : public std::exception {
       public:
        const char* what() const noexcept {
            return "Mtm matrix error: Illegal initialization values";
        }
    };
    template<typename T>
    class Matrix<T>::DimensionMismatch : public std::exception {
        Dimensions dimension1, dimension2;
        char* err;

       public:
        DimensionMismatch (Dimensions dim1, Dimensions dim2) : err (nullptr), dimension1 (dim1), dimension2 (dim2) {}
        const char* what() noexcept {
            std::string res =
                "Mtm matrix error: Dimension mismatch: " + dimension1.toString() + " " + dimension2.toString();
            err = new char[res.length() + 1];
            return strcpy (err, res.c_str());
        }
        ~DimensionMismatch() {
            delete[] err;
        }
    };

    /*
     *allocator - allocate space for new matrix of type T
     */
    template<typename T>
    T** Matrix<T>::allocate_space (int row_size, int col_size) {
        T** data = new T*[row_size];
        for (int i = 0; i < row_size; i++) {
            try {
                data[i] = new T[col_size];
            } catch (const std::bad_alloc& e) {
                for (int j = 0; j < i; j++) {
                    delete[] data[j];
                }
                delete[] data;
                throw e;
            }
        }
        return data;
    }
    /*
     *allocate_and_copy - allocate space for new matrix of type T
     *                    and copy the element of source matrix to
     *                    the new  matrix (destination)
     */
    template<typename T>
    T** Matrix<T>::allocate_and_copy (T** src, int row_size, int col_size) {
        T** dis = allocate_space (row_size, col_size);
        for (int i = 0; i < row_size; i++) {
            try {
                for (int j = 0; j < col_size; j++) {
                    dis[i][j] = src[i][j];
                }
            } catch (...) {
                for (int i = 0; i < row_size; i++) {
                    delete[] dis[i];
                }
                delete[] dis;
                throw;
            }
        }
        return dis;
    }
    /**
     *  @brief  Creates a matrix with default constructed elements.
     *  @param  dim  The dimension of elements to initially create.
     *  @param  initial_val initial valu of elements to initially create.
     *
     *  This constructor fills the %matrix with @T default
     *  constructed elements.
     */
    template<typename T>
    Matrix<T>::Matrix (Dimensions dim, const T& initial_val) : matrix (nullptr), dimension (dim) {
        if (dim.getRow() <= 0 || dim.getCol() <= 0) {
            throw Matrix<T>::IllegalInitialization();
        }
        matrix = allocate_space (dim.getRow(), dim.getCol());
        for (int i = 0; i < height(); i++) {
            for (int j = 0; j < width(); j++) {
                matrix[i][j] = initial_val;
            }
        }
    }

    /**
     *  @brief  %Matrix copy constructor.
     *  @param  m  A %Matrix of identical element type .
     *
     *  All the elements of @param m are copied.
     *  The newly-created %Matrix uses a copy of the allocator object used
     *  by @param m .
     */
    template<typename T>
    Matrix<T>::Matrix (const Matrix<T>& m) : matrix (nullptr), dimension (m.dimension) {
        matrix = allocate_space (dimension.getRow(), dimension.getCol());
        typename Matrix<T>::const_iterator it2 = m.begin();
        for (typename Matrix<T>::iterator it = begin(); it != end(); ++it, ++it2) {
            *it = *it2;  // TODO check if need to catch another throw
        }
    }

    /**
     *  The dtor only erases the elements, and note that if the
     *  elements themselves are pointers, the pointed-to memory is
     *  not touched in any way.  Managing the pointer is the user's
     *  responsibility.
     */
    template<typename T>
    Matrix<T>::~Matrix() {
        for (int i = 0; i < height(); i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    /**
     *  @brief  %Matrix assignment operator.
     *  @param  m  A %Matrix of identical element and allocator types.
     *
     *  All the elements of @a m are copied.
     *
     *  Whether the allocator is copied depends on the allocator traits.//TODO
     */
    template<typename T>
    Matrix<T>& Matrix<T>::operator= (const Matrix<T>& m) {
        T** tmp_data = allocate_and_copy (m.matrix, m.height(), m.width());
        for (int i = 0; i < height(); i++) {  // TODO
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = tmp_data;
        dimension = m.dimension;
        return *this;
    }

    // template<typename T>
    // Matrix<T>& Matrix<T>::operator= (const Matrix<T>& m) {
    //     if (this == &m) {
    //         return *this;
    //     }
    //     T** tmp_data = new T*[m.height()];
    //     for (int i = 0; i < m.height(); i++) {
    //         try {
    //             tmp_data[i] = new T[m.width()];
    //             for (int j = 0; j < m.width(); j++) {
    //                 tmp_data[i][j] = m.matrix[i][j];
    //             }
    //         } catch (const std::bad_alloc& e) {  // TODO check if need to catch another throw
    //             for (int j = 0; j < i; j++) {
    //                 delete[] tmp_data[j];
    //             }
    //             delete[] tmp_data;
    //             throw e;
    //         } catch (...) {
    //             for (int j = 0; j < i; j++) {
    //                 delete[] tmp_data[j];
    //             }
    //             delete[] tmp_data;
    //             throw;
    //         }
    //     }
    //     for (int i = 0; i < height(); i++) {  // TODO
    //         delete[] matrix[i];
    //     }
    //     delete[] matrix;
    //     matrix = tmp_data;
    //     dimension = m.dimension;
    //     return *this;
    // }

    /**
     *  @brief  Diagonal %Matrix constructor.
     *  @param  dimension  The dimension of the diagonal %Matrix.
     *  @param  initial_val initial value of elements to initially create.
     *
     *  This constructor fills the %matrix with @T default
     *  constructed elements.
     */
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

    /**
     *  @brief  returns transposed %Matrix .
     *
     * This Method fills the transposed %matrix with @T copy
     *  constructor.
     */
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
    /**  Returns the number of rows in the %Matrix.  */
    template<typename T>
    int Matrix<T>::height() const {
        return dimension.getRow();
    }
    /**  Returns the number of columns in the %Matrix.  */
    template<typename T>
    int Matrix<T>::width() const {
        return dimension.getCol();
    }
    /**  Returns the number of elements in the %Matrix.  */
    template<typename T>
    int Matrix<T>::size() const {
        return (height() * width());
    }

    template<typename T>
    std::ostream& operator<< (std::ostream& os, const Matrix<T>& m) {
        return printMatrix (os, m.begin(), m.end(), m.width());
    }

    // element access
    /**
     *  @brief  Subscript access to the data contained in the %Matrix.
     *  @param row_val
     *  @param col_val
     *   The index of the element for which data should be accessed.
     *
     *  @return  Read/write reference to data.
     *
     *  This operator allows for easy, array-style, data access.
     */
    template<typename T>
    T& Matrix<T>::operator() (int row_val, int col_val) {
        if (row_val < 0 || row_val >= height() || col_val < 0 || col_val >= width()) {
            throw typename Matrix<T>::AccessIllegalElement();
        }
        return matrix[row_val][col_val];
    }
    /**
     *  @brief  Subscript access to the data contained in the %Matrix.
     *  @param row_val
     *  @param col_val
     *   The index of the element for which data should be accessed.
     *
     *  @return  Read-only (constant) reference to data.
     *
     *  This operator allows for easy, array-style, data access.
     */
    template<typename T>
    const T Matrix<T>::operator() (int row_val, int col_val) const {
        if (row_val < 0 || row_val >= height() || col_val < 0 || col_val >= width()) {
            throw typename Matrix<T>::AccessIllegalElement();
        }
        return matrix[row_val][col_val];
    }

    /**
     *  @brief  returns //TODO -?? %Matrix .
     *
     * This Method fills the transposed %matrix with @T copy
     *  constructor.
     */
    template<class T>
    Matrix<T> Matrix<T>::operator-() const {
        Matrix<T> tmp (*this);
        for (typename Matrix<T>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
            (*it) *= -1;
        }
        return tmp;
    }

    /**
     *  @brief  returns new %Matrix  which is the  sum of  two %Matrices  .
     *  @param m1  @param m2 two  Matrices to add
     *
     * This Method fills the new Matrix with @T operator+
     *
     */
    template<typename T>
    Matrix<T> operator+ (const Matrix<T>& m1, const Matrix<T>& m2) {
        if (m1.height() != m2.height() || m1.width() != m2.width()) {
            Dimensions dim1 (m1.height(), m1.width());
            Dimensions dim2 (m2.height(), m2.width());
            throw typename Matrix<T>::DimensionMismatch (dim1, dim2);
        }
        Matrix<T> tmp (m1);
        typename Matrix<T>::const_iterator it1 = m1.begin(), it2 = m2.begin();
        for (typename Matrix<T>::iterator it = tmp.begin(); it != tmp.end(); ++it, ++it2, ++it1) {
            *it = *it1 + *it2;
        }
        return tmp;
    }

    /**
     *  @brief  returns new %Matrix  which is the  difference of  two %Matrices  .
     *  @param m1  @param m2 two  Matrices to subtract
     *
     * This Method fills the new Matrix with @T operator-
     *
     */
    template<typename T>
    Matrix<T> operator- (const Matrix<T>& m1, const Matrix<T>& m2) {
        return m1 + (-m2);
    }

    /**
     *  @brief  add @val to every element in %Matrix and returns it by reference.
     *  @param val  the value to add to  the Matrix .
     *
     * This Method fills the Matrix with @T operator+=
     */
    template<class T>
    Matrix<T>& Matrix<T>::operator+= (const T& val) {
        for (typename Matrix<T>::iterator it = begin(); it != end(); ++it) {
            *it += val;
        }
        return *this;
    }

    /**
     *  @brief  add @val to every element in %Matrix and returns new Matrix.
     *  @param m  the Matrix to add to .
     *  @param val  the value to add to the new Matrix .
     *
     * This Method fills the Matrix with @T operator+=
     */
    template<typename T>  // TODO לבדןק אפ אפשר לקצר
    Matrix<T> operator+ (const Matrix<T>& m, const T& val) {
        Matrix<T> tmp (m);  // TODO לבדוק אם זה בסדר והוא באמת מחזיר עותק
        for (typename Matrix<T>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
            *it += val;
        }
        return tmp;
    }

    /**
     *  @brief  add @val to every element in %Matrix and returns new Matrix.
     *  @param m  the Matrix to add to .
     *  @param val  the value to add to the new Matrix .
     *
     * This Method fills the Matrix with @T operator+=
     */
    template<typename T>
    Matrix<T> operator+ (const T& val, const Matrix<T>& m) {
        Matrix<T> tmp (m);
        for (typename Matrix<T>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
            *it = val + *it;
        }
        return tmp;
    }
    /**
     *  @brief  returns bool %Matrix i.e. Matrix<bool> which element is
     *            true of the the condition is true , false otherwise.
     *  @param x  the value to add to the new Matrix . //TODO
     *
     * This Method fills the returned Matrix with @T operator<
     */
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
    /**
     *  @brief  returns bool %Matrix i.e. Matrix<bool> which element is
     *            true of the the condition is true , false otherwise.
     *  @param x  the value to add to the new Matrix . //TODO
     *
     * This Method fills the returned Matrix with @T operator<
     */
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
    /**
     *  @brief  returns bool %Matrix i.e. Matrix<bool> which element is
     *            true of the the condition is true , false otherwise.
     *  @param x  the value to add to the new Matrix . //TODO
     *
     * This Method fills the returned Matrix with @T operator<
     */
    template<typename T>
    Matrix<bool> Matrix<T>::operator<= (const T& x) const {
        Matrix<bool> tmp = *this > x;
        return tmp != 1;  // TODO לשאול אם זה נחשב למספר קסם
    }
    /**
     *  @brief  returns bool %Matrix i.e. Matrix<bool> which element is
     *            true of the the condition is true , false otherwise.
     *  @param x  the value to add to the new Matrix . //TODO
     *
     * This Method fills the returned Matrix with @T operator<
     */
    template<typename T>
    Matrix<bool> Matrix<T>::operator>= (const T& x) const {
        Matrix<bool> tmp = *this < x;
        return tmp != 1;  // TODO לשאול אם זה נחשב למספר קסם
    }
    /**
     *  @brief  Matrix equality comparison.//TODO
     *  @param  x
     *  @return  True iff the size and elements of the vectors are equal.
     *
     *  This is an equivalence relation.  It is linear in the size of the
     *  vectors.  Vectors are considered equivalent if their sizes are equal,
     *  and if corresponding elements compare equal.
     */
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
    /**
     *  @brief  returns bool %Matrix i.e. Matrix<bool> which element is
     *            true of the the condition is true , false otherwise.
     *  @param x  the value to add to the new Matrix . //TODO
     *
     * This Method fills the returned Matrix with @T operator<
     */
    template<typename T>
    Matrix<bool> Matrix<T>::operator!= (const T& x) const {
        Matrix<bool> tmp = ((*this) == x);
        return tmp == 0;  // TODO לשאול אם זה נחשב למספר קסם
    }
    /**
     *  @brief  returns true iff every element of the matrix @a m is true ,
     *            false otherwise.
     *  @param m   the Matrix to . //TODO
     *
     * This Method assume type @T have operator! //TODO
     */
    template<typename T>
    bool all (const Matrix<T>& m) {
        for (typename Matrix<T>::const_iterator it = m.begin(); it != m.end(); ++it) {
            if (!(*it)) {
                return false;
            }
        }
        return true;
    }

    /**
     *  @brief  returns true iff exist at least one element of the matrix @a m is true ,
     *            false otherwise.
     *  @param m   the Matrix to . //TODO
     *
     * This Method assume type @T have converter from type T to type bool  //TODO
     */
    template<typename T>
    bool any (const Matrix<T>& m) {
        for (typename Matrix<T>::const_iterator it = m.begin(); it != m.end(); ++it) {
            if (*it) {
                return true;
            }
        }
        return false;
    }

    /**
     *  @brief  returns new matrix after applying function object  
     *          to every element in %Matrix .
     *            
     *  @param pred   Object with operator() i.e. function object or C function.
     *
     */
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

    // iterators
    /**
     *  Returns a read/write iterator that points to the first
     *  element in the %Matrix.  Iteration is done in ordinary
     *  element order.
     */
    template<typename T>
    typename Matrix<T>::iterator Matrix<T>::begin() {
        return iterator (this, 1, 1, false);
    }

    /**
     *  Returns a read/write iterator that points one past the last
     *  element in the %Matrix.  Iteration is done in ordinary
     *  element order.
     */
    template<typename T>
    typename Matrix<T>::iterator Matrix<T>::end() {
        return iterator (this, height(), width(), true);
    }
    /**
     *  Returns a read-only (constant) iterator that points to the
     *  first element in the %Matrix.  Iteration is done in ordinary
     *  element order.
     */
    template<typename T>
    const typename Matrix<T>::const_iterator Matrix<T>::begin() const {
        return const_iterator (this, 1, 1, false);
    }

    /**
     *  Returns a read-only (constant) iterator that points one past
     *  the last element in the %Matrix.  Iteration is done in
     *  ordinary element order.
     */
    template<typename T>
    const typename Matrix<T>::const_iterator Matrix<T>::end() const {
        return const_iterator (this, height(), width(), true);
    }

}  // namespace mtm

#endif  // EX3_MATRIX_H
