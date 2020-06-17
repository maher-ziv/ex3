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
        IntMatrix ( mtm::Dimensions dimension, int initial_val = 0 );// TODO check if this ok or need to// move// it private
        IntMatrix ( int scalar_val );
        IntMatrix ( const IntMatrix& m );
        IntMatrix Identity ( int dimension );
        IntMatrix transpose() const;
        IntMatrix operator-() const;
        IntMatrix& operator+= ( const IntMatrix& a );
        // IntMatrix& operator+=(const int& num);//TODO
        int& operator() ( int row_val, int col_val );
        int operator() ( int row_val, int col_val ) const;
        int size() const;
        int height() const;
        int width() const;

        class iterator;
        class const_iterator;

        static void printM ( const IntMatrix& m );  // TODO test func
    };

    IntMatrix operator+ ( const IntMatrix& a, const IntMatrix& b );
    bool all ( const IntMatrix& a );
    bool any ( const IntMatrix& a );

}  // namespace mtm

#endif  // EX3_INT_MATRIX_H