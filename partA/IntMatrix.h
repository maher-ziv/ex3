#ifndef EX3_INT_MATRIX_H
#define EX3_INT_MATRIX_H

#include <iostream>
#include "Auxiliaries.h"

namespace mtm {

    class IntMatrix{
        private:
            int** matrix;
            mtm::Dimensions dimension;
        public:
            IntMatrix(mtm::Dimensions dimension, int init_val = 0);
            IntMatrix(int matrix_val);
            IntMatrix Identity(int dimension);
            IntMatrix transpose() const ;
            IntMatrix operator-() const;
            IntMatrix& operator+=(const IntMatrix& a);
            int& operator()(int row_val , int col_val ); // TODO make cost operator()

            class iterator ;
            class const_iterator ;

    };

    IntMatrix operator+(const IntMatrix& a ,const IntMatrix& b);
    bool all(const IntMatrix& a);
    bool any(const IntMatrix& a);

    


}

#endif  //EX3_INT_MATRIX_H