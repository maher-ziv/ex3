#include "IntMatrix.h"

#include <iostream>
#include <string>
using mtm::Dimensions;
using mtm::IntMatrix;
using std::cout;
using std::endl;

mtm::IntMatrix::IntMatrix (Dimensions dim, int initial_val) : dimension (dim) {
    matrix = new int*[height()];
    for (int i = 0; i < height(); i++) {
        matrix[i] = new int[width()];
        for (int j = 0; j < width(); j++) {
            matrix[i][j] = initial_val;
        }
    }
}

mtm::IntMatrix::IntMatrix (const IntMatrix& m) : dimension (m.dimension) {
    matrix = new int*[height()];
    for (int i = 0; i < height(); i++) {
        matrix[i] = new int[width()];
        for (int j = 0; j < width(); j++) {
            matrix[i][j] = m.matrix[i][j];
        }
    }
}

mtm::IntMatrix::~IntMatrix() {
    for (int i = 0; i < height(); ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

mtm::IntMatrix mtm::IntMatrix::Identity (int dimension) {
    Dimensions dim (dimension, dimension);
    mtm::IntMatrix identity (dim);
    for (int i = 0; i < dimension; i++) {
        identity (i, i) = 1;
    }
    return identity;
}

int mtm::IntMatrix::height() const {
    return dimension.getRow();
}

int mtm::IntMatrix::width() const {
    return dimension.getCol();
}

int mtm::IntMatrix::size() const {
    return (height() * width());
}

mtm::IntMatrix mtm::IntMatrix::transpose() const {
    Dimensions t_dimension (width(), height());
    mtm::IntMatrix t_matrix (t_dimension);
    for (int i = 0; i < width(); i++) {
        for (int j = 0; j < height(); j++) {
            t_matrix (i, j) = matrix[j][i];
        }
    }
    return t_matrix;
}

mtm::IntMatrix& mtm::IntMatrix::operator= (const IntMatrix& m) {
    if (this == &m) {
        return *this;
    }
    for (int i = 0; i < height(); ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    dimension = m.dimension;
    matrix = new int*[height()];
    for (int i = 0; i < height(); i++) {
        matrix[i] = new int[width()];
        for (int j = 0; j < width(); j++) {
            matrix[i][j] = m.matrix[i][j];
        }
    }
    return *this;
}

int& mtm::IntMatrix::operator() (int row_val, int col_val) {
    return matrix[row_val][col_val];
}

int mtm::IntMatrix::operator() (int row_val, int col_val) const {
    int res = matrix[row_val][col_val];
    return res;
}

mtm::IntMatrix mtm::IntMatrix::operator-() const {
    IntMatrix tmp (*this);
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            tmp.matrix[i][j] *= -1;
        }
    }
    return tmp;
}

IntMatrix& IntMatrix::operator+= (const int num) {
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            matrix[i][j] += num;
        }
    }
    return *this;
}

mtm::IntMatrix mtm::operator+ (const mtm::IntMatrix& m1, const mtm::IntMatrix& m2) {
    IntMatrix tmp (m1);
    IntMatrix::const_iterator it1 = m1.begin(), it2 = m2.begin();
    for (IntMatrix::iterator it = tmp.begin(); it != tmp.end(); ++it , ++it1,++it2) {
        *it = *it1 + *it2;
    }
    return tmp;
}

mtm::IntMatrix mtm::operator- (const IntMatrix& m1, const IntMatrix& m2) {
    IntMatrix tmp = -m2;
    return m1 + tmp;
}
IntMatrix mtm::operator+ (const IntMatrix& m,  int x) {
    IntMatrix tmp (m);
    return tmp+=x;
}
IntMatrix mtm::operator+ (  int  x, const IntMatrix& m){
    return m+x;
}
IntMatrix IntMatrix::operator< (const int x) const {
    IntMatrix tmp (*this);
    mtm::IntMatrix::iterator it_2 = tmp.begin();
    for (mtm::IntMatrix::const_iterator it = begin(); it != end(); ++it, ++it_2) {
        *it_2 = (*it) < x ? 1 : 0;
    }
    return tmp;
}

IntMatrix IntMatrix::operator> (const int x) const {
    IntMatrix tmp (*this);
    mtm::IntMatrix::iterator it_2 = tmp.begin();
    for (mtm::IntMatrix::const_iterator it = begin(); it != end(); ++it, ++it_2) {
        *it_2 = *it > x ? 1 : 0;
    }
    return tmp;
}

IntMatrix IntMatrix::operator<= (const int x) const {
    IntMatrix tmp = *this > x;
    return tmp != 1; 
}

IntMatrix IntMatrix::operator>= (const int x) const {
    IntMatrix tmp = *this < x;
    return tmp != 1; 
}

IntMatrix IntMatrix::operator== (const int x) const {
    IntMatrix tmp (*this);
    mtm::IntMatrix::iterator it_2 = tmp.begin();
    for (mtm::IntMatrix::const_iterator it = begin(); it != end(); ++it, ++it_2) {
        *it_2 = *it == x ? 1 : 0;
    }
    return tmp;
}

IntMatrix IntMatrix::operator!= (const int x) const {
    IntMatrix tmp = *this == x;
    return tmp == 0;  
}

std::ostream& mtm::operator<< (std::ostream& os, const IntMatrix& m) {
    int* tmp = new int[m.size()];
    int i = 0;
    for (mtm::IntMatrix::const_iterator it = m.begin(); it != m.end(); ++it) {
        tmp[i] = *it;
        i++;
    }
    std::string res = mtm::printMatrix (tmp, m.dimension);
    delete[] tmp;
    return os << res;
}

bool mtm::all (const mtm::IntMatrix& a) {
    for (mtm::IntMatrix::const_iterator it = a.begin(); it != a.end(); ++it) {
        if (!(*it)) {
            return false;
        }
    }
    return true;
}

bool mtm::any (const mtm::IntMatrix& a) {
    for (mtm::IntMatrix::const_iterator it = a.begin(); it != a.end(); ++it) {
        if ((*it)) {
            return true;
        }
    }
    return false;
}

// class IntMatrix::iterator
IntMatrix::iterator::iterator (const IntMatrix* matrix, int row, int col, bool is_last)
    : matrix (matrix), row (row), col (col), is_last (is_last) {}

mtm::IntMatrix::iterator& mtm::IntMatrix::iterator::operator= (const mtm::IntMatrix::iterator& it) {
    if (this == &it) {
        return *this;
    }
    matrix = it.matrix;
    row = it.row;
    col = it.col;
    is_last = it.is_last;
    return *this;
}
IntMatrix::iterator& IntMatrix::iterator::operator++() {
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

IntMatrix::iterator IntMatrix::iterator::operator++ (int) {
    iterator result = *this;
    ++*this;
    return result;
}

bool IntMatrix::iterator::operator== (const iterator& it) const {
    return (row == it.row && col == it.col && is_last == it.is_last);
}

bool IntMatrix::iterator::operator!= (const iterator& it) const {
    return !(*this == it);
}

IntMatrix::iterator IntMatrix::begin() {
    return iterator (this, 1, 1, false);
}

IntMatrix::iterator IntMatrix::end() {
    return iterator (this, height(), width(), true);
}

int& IntMatrix::iterator::operator*() const {
    return matrix->matrix[row - 1][col - 1];
}

// class IntMatrix::const_iterator
IntMatrix::const_iterator::const_iterator (const IntMatrix* matrix, int row, int col, bool is_last)
    : matrix (matrix), row (row), col (col), is_last (is_last) {}

IntMatrix::const_iterator& IntMatrix::const_iterator::operator= (const IntMatrix::const_iterator& it) {
    if (this == &it) {
        return *this;
    }
    matrix = it.matrix;
    row = it.row;
    col = it.col;
    is_last = it.is_last;
    return *this;
}
IntMatrix::const_iterator& IntMatrix::const_iterator::operator++() {
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

IntMatrix::const_iterator IntMatrix::const_iterator::operator++ (int) {
    const_iterator result = *this;
    ++*this;
    return result;
}

bool IntMatrix::const_iterator::operator== (const const_iterator& it) const {
    return (row == it.row && col == it.col && is_last == it.is_last);
}

bool IntMatrix::const_iterator::operator!= (const const_iterator& it) const {
    return !(*this == it);
}

const IntMatrix::const_iterator IntMatrix::begin() const {
    return const_iterator (this, 1, 1, false);
}

const IntMatrix::const_iterator IntMatrix::end() const {
    return const_iterator (this, height(), width(), true);
}

const int& IntMatrix::const_iterator::operator*() const {
    return matrix->matrix[row - 1][col - 1];
}
