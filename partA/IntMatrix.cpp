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

mtm::IntMatrix::IntMatrix (int scalar_val) : dimension (1, 1) {
    matrix = new int*[height()];
    matrix[0] = new int[width()];
    matrix[0][0] = scalar_val;
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

    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            matrix[i][j] *= -1;
        }
    }
    return *this;
}

mtm::IntMatrix& mtm::IntMatrix::operator+= (const mtm::IntMatrix& b) {
    // matrix a and b not from the same dimension which mean casting happened and dime of b is one i.e.1x1
    if (size() > b.size()) {
        for (int i = 0; i < height(); i++) {
            for (int j = 0; j < width(); j++) {
                matrix[i][j] += b (0, 0);
            }
        }
    } else {
        for (int i = 0; i < height(); i++) {
            for (int j = 0; j < width(); j++) {
                matrix[i][j] += b (i, j);
            }
        }
    }
    return *this;
}
// TODO  לבדוק אם צריך גם זה או מספיק אחד לשניהם
IntMatrix& IntMatrix::operator+= (const int& num) {
    for (int i = 0; i < height(); i++) {
        for (int j = 0; j < width(); j++) {
            matrix[i][j] += num;
        }
    }
    return *this;
}

mtm::IntMatrix mtm::operator+ (const mtm::IntMatrix& m1, const mtm::IntMatrix& m2) {
    // if casting happened and dime of a or b is one i.e. 1x1  , this meanthat the user want to add scalar
    mtm::IntMatrix tmp_1 = m1.size() >= m2.size() ? m1 : m2;
    mtm::IntMatrix tmp_2 = tmp_1.size() == m1.size() ? m2 : m1;
    return tmp_1 += tmp_2;
}

mtm::IntMatrix mtm::operator- (const IntMatrix& m1, const IntMatrix& m2) {
    IntMatrix tmp = -m1;
    return tmp + m2;
}


IntMatrix IntMatrix::operator< (const int x) {
    IntMatrix tmp (*this);
    for (mtm::IntMatrix::iterator it = begin(), it_2 = tmp.begin(); it != end(); ++it, ++it_2) {
        *it_2 = (*it) < x ? 1 : 0;
    }
    return tmp;
}
IntMatrix IntMatrix::operator> (const int x) {
    IntMatrix tmp (*this);
    for (mtm::IntMatrix::iterator it = begin(), it_2 = tmp.begin(); it != end(); ++it, ++it_2) {
        *it_2 = x > *it ? 1 : 0;
    }
    return tmp;
}
IntMatrix IntMatrix::operator<= (const int x) {
    IntMatrix tmp (*this);
    for (mtm::IntMatrix::iterator it = begin(), it_2 = tmp.begin(); it != end(); ++it, ++it_2) {
        *it_2 = *it <= x ? 1 : 0;
    }
    return tmp;
}
IntMatrix IntMatrix::operator>= (const int x) {
    IntMatrix tmp (*this);
    for (mtm::IntMatrix::iterator it = begin(), it_2 = tmp.begin(); it != end(); ++it, ++it_2) {
        *it_2 = x >= *it ? 1 : 0;
    }
    return tmp;
}
IntMatrix IntMatrix::operator== (const int x) {
    IntMatrix tmp (*this);
    for (mtm::IntMatrix::iterator it = begin(), it_2 = tmp.begin(); it != end(); ++it, ++it_2) {
        *it_2 = *it == x ? 1 : 0;
    }
    return tmp;
}
IntMatrix IntMatrix::operator!= (const int x) {
    IntMatrix tmp (*this);
    for (mtm::IntMatrix::iterator it = begin(), it_2 = tmp.begin(); it != end(); ++it, ++it_2) {
        *it_2 = *it != x ? 1 : 0;
    }
    return tmp;
}

// TODO need testing
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

IntMatrix::T_iterator::T_iterator (const IntMatrix* matrix, int row, int col, bool is_last)
    : matrix (matrix), row (row), col (col), is_last (is_last) {}

IntMatrix::T_iterator& IntMatrix::T_iterator::operator= (const IntMatrix::T_iterator& it) {
    if (this == &it) {
        return *this;
    }
    matrix = it.matrix;
    row = it.row;
    col = it.col;
    is_last = it.is_last;
    return *this;
}
IntMatrix::T_iterator& IntMatrix::T_iterator::operator++() {
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

IntMatrix::T_iterator IntMatrix::T_iterator::operator++ (int) {
    T_iterator result = *this;
    ++*this;
    return result;
}

bool IntMatrix::T_iterator::operator== (const T_iterator& it) const {
    return (row == it.row && col == it.col && is_last == it.is_last);
}

bool IntMatrix::T_iterator::operator!= (const T_iterator& it) const {
    return !(*this == it);
}

IntMatrix::iterator::iterator (const IntMatrix* matrix, int row, int col, bool is_last)
    : IntMatrix::T_iterator (matrix, row, col, is_last) {}

IntMatrix::iterator IntMatrix::begin() {
    return iterator (this, 1, 1, false);
}

IntMatrix::iterator IntMatrix::end() {
    return iterator (this, height(), width(), true);
}

int& IntMatrix::iterator::operator*() const {
    return matrix->matrix[row - 1][col - 1];
}
IntMatrix::const_iterator::const_iterator (const IntMatrix* matrix, int row, int col, bool is_last)
    : IntMatrix::T_iterator (matrix, row, col, is_last) {}

const int& IntMatrix::const_iterator::operator*() const {
    return matrix->matrix[row - 1][col - 1];
}

const IntMatrix::const_iterator IntMatrix::begin() const {
    return const_iterator (this, 1, 1, false);
}

const IntMatrix::const_iterator IntMatrix::end() const {
    return const_iterator (this, height(), width(), true);
}


//===========================================================================================================
//                              ----test----
//===========================================================================================================

void mtm::IntMatrix::print (std::string name) {
    cout << endl << "--" << name << "--" << endl;
    for (int i = 0; i < height(); ++i) {
        for (int j = 0; j < width(); ++j) {
            cout << " " << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

// int main() {
//     mtm::Dimensions dim (5, 3), dim2 (2, 1);
//     mtm::IntMatrix m1 (dim);
//     mtm::IntMatrix m2 (dim, 5);
//     mtm::IntMatrix m4 (dim, 33);
//     mtm::IntMatrix id = mtm::IntMatrix::Identity (5);
//     m4 (4, 2) += 3;
//     m4 (0, 0) += 3;
//     IntMatrix::iterator it_begin = m4.begin();
//     cout << *it_begin << endl;
//     IntMatrix::iterator it_end = m4.end();
//     cout << *it_end << endl;

//     mtm::IntMatrix m6 (dim2, 33);
//     m6.print ("m6");
//     cout << m6 << endl;
//     for (mtm::IntMatrix::iterator it_a = m6.begin(); it_a != m6.end(); ++it_a) {
//         cout << *it_a << endl;
//     }

//     cout << "id\n" << id << endl;
//     cout << "m2\n" << m2 << endl;

//     mtm::IntMatrix m44 (dim2, 33);

//     for (mtm::IntMatrix::iterator it_a = m44.begin(); it_a != m44.end(); ++it_a) {
//         cout << *it_a << endl;
//         (*it_a) = 1;
//         cout << "new val \n" << *it_a << endl;
//     }
//     const mtm::IntMatrix m55 (dim2, 33);
//     mtm::IntMatrix::const_iterator it = m55.begin();
//     cout << m2 (1, 0) << endl;
//     cout << m2 (1, 0) + 5 << endl;
//     m2 (1, 0) = -3;
//     cout << m2 (1, 0) << endl;
//     m2 += 8;
//     m2.print ("m2");
//     cout << m2 (1, 0) << endl;
//     mtm::IntMatrix m5 (dim);
//     m5 = m4 + m2;
//     m5.print ("m5");
//     mtm::IntMatrix m_t = m2.transpose();
//     m_t.print ("m_t");
//     cout << m_t (2, 1) << endl;
//     cout << m_t (1, 2) << endl;
//     mtm::IntMatrix m3 = -m4;
//     m3.print ("m3");
//     m2.print ("m2");
//     mtm::IntMatrix m8 = m2 < 6;
//     m8.print ("m8");
// }
