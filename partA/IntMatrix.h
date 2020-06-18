#ifndef EX3_INT_MATRIX_H
#define EX3_INT_MATRIX_H

#include <iostream>
#include "Auxiliaries.h"

namespace mtm {

    class IntMatrix {
       private:
        int** matrix;
        mtm::Dimensions dimension;

       public:
        IntMatrix() = delete;
        IntMatrix (mtm::Dimensions dimension, int initial_val = 0);
        IntMatrix (int scalar_val);
        IntMatrix (const IntMatrix& m);
        ~IntMatrix();

        IntMatrix& operator= (const IntMatrix& m);
        IntMatrix operator-() const;
        IntMatrix& operator+= (const IntMatrix& a);
        IntMatrix& operator+= (const int& num);  // TODO 
        int& operator() (int row_val, int col_val);
        int operator() (int row_val, int col_val) const;
        friend std::ostream& operator<<(std::ostream& os, const IntMatrix& m);
        IntMatrix operator< (const int x);  
        IntMatrix operator> (const int x);
        IntMatrix operator<= (const int x);
        IntMatrix operator>= (const int x);
        IntMatrix operator== (const int x);
        IntMatrix operator!= (const int x);

        int size() const;
        int height() const;
        int width() const;
        static IntMatrix Identity (int dimension);
        IntMatrix transpose() const;

        class iterator;
        iterator begin();  // TODO check if const needed
        iterator end();
        class const_iterator;
        const const_iterator begin() const;
        const const_iterator end() const;

        void print (std::string str = "");  // TODO test func
    };

    IntMatrix operator+ (const IntMatrix& m1, const IntMatrix& m2);
    IntMatrix operator- (const IntMatrix& m1, const IntMatrix& m2);
    std::ostream& operator<< (std::ostream& os, const IntMatrix& m);  // TODO
    bool all (const IntMatrix& a);
    bool any (const IntMatrix& a);

    class IntMatrix::iterator {
       private:
        const IntMatrix* matrix;  // the matrix this iterator points to
        int row, col;
        bool is_last;
        iterator (const IntMatrix* matrix, int row, int col, bool is_last = false);
        friend class IntMatrix;  // allow IntMatrix to call the c'tor
       public:
        iterator() = delete;
        iterator& operator= (const iterator& it);
        int& operator*();
        iterator& operator++();
        iterator operator++ (int);
        bool operator== (const iterator& it) const;
        bool operator!= (const iterator& it) const;
    };

    class IntMatrix::const_iterator : public IntMatrix::iterator {
       public:  // TODO check if needed to move to private  !!!! // TODO check if need to make destructor
        const_iterator (const IntMatrix* matrix, int row, int col, bool is_last = false);
        const int& operator*() const;
    };

}  // namespace mtm

#endif  // EX3_INT_MATRIX_H
