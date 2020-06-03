#ifndef EX3_AUXILARIES_H
#define EX3_AUXILARIES_H
#include <string>
#include <iostream>



namespace mtm { 
    class Dimensions {
        unsigned int row, col;
    public:
        Dimensions(unsigned int row_t, unsigned int col_t) : row(row_t), col(col_t) {}
        std::string toString() const;
        bool operator==(const Dimensions& other) const;
        bool operator!=(const Dimensions& other) const;
        int getRow() const ;
        int getCol() const ;
    };
    
    std::string printMatrix(const int* matrix,const Dimensions& dim);
}



#endif //EX3_AUXILARIES_H
