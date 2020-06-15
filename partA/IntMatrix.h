#ifndef EX3_INT_MATRIX_H
#define EX3_INT_MATRIX_H

#include <iostream>
#include "Auxiliaries.h"

namespace mtm {

    class IntMatrix{
        
        private:
            int** matrix;
            mtm::Dimensions dimension;
            int init_val; //TODO check if necceary
            void allocSpace();
            //const int** allocSpace();
        public:
            IntMatrix(mtm::Dimensions dimension = {1,1}, int init_val = 0); // TODO check if that ok {1 ,1}
            IntMatrix(int scalar_val);
            IntMatrix Identity(int dimension);
            IntMatrix transpose() const ;
            IntMatrix operator-() const;
            IntMatrix& operator+=(const IntMatrix& a);
            //IntMatrix& operator+=(const int& num);
            int& operator()(int row_val , int col_val ); // TODO make cost operator()
            int operator()(int row_val , int col_val ) const ;
            class iterator ;
            class const_iterator ;
            int size() const;

    };

    IntMatrix operator+(const IntMatrix& a ,const IntMatrix& b);
    bool all(const IntMatrix& a);
    bool any(const IntMatrix& a);

    


}

#endif  //EX3_INT_MATRIX_H