#include <iostream>
#include "IntMatrix.h"

using std::cout;
using std::endl;
using mtm::Dimensions;

mtm::IntMatrix::IntMatrix(Dimensions dim, int initial_val ) :
    dimension(dim) {
        matrix = new int* [dimension.getRow()];
        for( int i=0 ; i < dimension.getRow() ; i++ ) {
            matrix[i] = new int[dimension.getCol()];
            for ( int j = 0 ; j < dimension.getCol() ; j++ ) {
                matrix[i][j] = initial_val;
            }
        }
}


mtm::IntMatrix::IntMatrix(const IntMatrix& m) {

    Dimensions dim (std::max(m.height() , height()), std::max(m.width() , width()));


    



   
}





mtm::IntMatrix::IntMatrix(int scalar_val): dimension(1,1) {

    matrix = new int* [dimension.getRow()];
    matrix[0] = new int[dimension.getCol()];
    matrix[0][0] = scalar_val;

}

mtm::IntMatrix mtm::IntMatrix::Identity(int dimension) {

    Dimensions dim(dimension,dimension);
    mtm::IntMatrix identity(dim);
    for ( int i = 0 ; i < dimension ; i++ ) {
        identity(i,i) = 1; //TODO check if it's OK to write  1 
    }
    return identity;
}


int mtm::IntMatrix::height() const {
    return dimension.getRow();
}

int mtm::IntMatrix::width() const {
    return dimension.getCol() ;
}

int mtm::IntMatrix::size() const {
    return ( this->height() * this->width() );
}

mtm::IntMatrix mtm::IntMatrix::transpose() const {

    int t_row = dimension.getCol()  , t_col = dimension.getRow() ;
    Dimensions t_dimension(t_row,t_col);
    mtm::IntMatrix t_matrix(t_dimension);
    for ( int i = 0 ; i < t_row ; i++) {
        for ( int j = 0 ; j < t_col ; j++ ) {
            t_matrix(i,j) = matrix[j][i];
        }
    }
    return t_matrix;
}

int& mtm::IntMatrix::operator()(int row_val , int col_val) {
    return matrix[row_val][col_val];
}

int mtm::IntMatrix::operator()(int row_val , int col_val ) const {
    int res = matrix[row_val][col_val];
    return res;
}


mtm::IntMatrix mtm::IntMatrix::operator-() const {

    mtm::IntMatrix tmp = *this; //TODO test it if this works !!
    // for(int i=0 ; i < dimension.getRow()  ; i++){
    //   for(int j=0 ; j < dimension.getCol()  ; j++){
    //     tmp(i,j)*=-1;
    //   }
    // }
    
    for ( mtm::IntMatrix::iterator it = tmp.begin() ;it !=tmp.end() ;++it ) { //TODO pick one
        (*it) *= -1;
    }
    return tmp ;
}


mtm::IntMatrix& mtm::IntMatrix::operator+=(const mtm::IntMatrix& b){

    if ( a.size() > b.size() ) { // matrix a and b not from the same dimension which mean casting happened and dime of b is one i.e. 1x1
        for (mtm::IntMatrix::iterator it_a = (*this).begin() ; it_a != a.end() ; ++it_a) { 
          *it_a += b(0,0);
        }
    }else{
        for (mtm::IntMatrix::iterator it_a = this->begin() ,it_b = b.begin() ; it_a != a.end() ; ++it_a , ++it_b ) { 
            *it_a += *it_b;
        }
    }
    return *this;
}

// IntMatrix& operator+=(const int& num){
//     for(IntMatrix::iterator it_a = this.begin() ; it_a != a.end() ; ++it_a) { 
//         *it_a += num;.
//     }
//     return *this;
// }

mtm::IntMatrix operator+(const mtm::IntMatrix& a ,const mtm::IntMatrix& b){
    //if casting happened and dime of a or b is one i.e. 1x1  , this mean that the user want to add scalar
    mtm::IntMatrix tmp_1 = a.size() >= b.size() ? a : b; 
    mtm::IntMatrix tmp_2 = tmp_1.size() == a.size() ? b : a;
    return tmp_1 += tmp_2;
}

bool mtm::all(const mtm::IntMatrix& a){

    for(mtm::IntMatrix::const_iterator it = a.begin() ;it !=a.end() ; ++it ) { 
        if(!(*it)){
            return false;
        }
    }
    return true;
}
bool mtm::any(const mtm::IntMatrix& a){

    for(mtm::IntMatrix::const_iterator it = a.begin() ;it !=a.end() ; ++it ) { 
        if((*it)){
            return true;
        }
    }
    return false;
}












//===========================================================================================================
//                              ----test----
//===========================================================================================================
mtm::IntMatrix& mtm::IntMatrix::operator+=(const mtm::IntMatrix& b){

    if ( dimension.getRow() > b.dimension.getRow() ) { // matrix a and b not from the same dimension which mean casting happened and dime of b is one i.e. 1x1
        for(int i=0 ; i <  dimension.getRow() ; i++){
            for(int j=0 ; j < dimension.getCol() ; j++){
                (*this)(i,j) += b(0,0);
            }
        }
    }else{
        for(int i=0 ; i <  dimension.getRow() ; i++){
            for(int j=0 ; j < dimension.getCol() ; j++){
                (*this)(i,j) += b(i,j);
            }
        }
    }
    return *this;
}

// mtm::IntMatrix operator+(const mtm::IntMatrix& a ,const mtm::IntMatrix& b){
//     //if casting happened and dime of a or b is one i.e. 1x1  , this mean that the user want to add scalar
//     mtm::IntMatrix tmp_1 = a.size() >= b.size() ? a : b; 
//     mtm::IntMatrix tmp_2 = tmp_1.size() == a.size() ? b : a;
//     return tmp_1 += tmp_2;
// }



void  mtm::IntMatrix::print( const IntMatrix& m){   
    printf("\n\n");
    int i, j;
    for (i = 0; i < dimension.getRow(); ++i)
    {
        for (j = 0; j < dimension.getCol(); ++j)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
    printf("\n\n");
}

int main(){
    
    using mtm::IntMatrix;
    using mtm::Dimensions;
 

    Dimensions dim(5 ,3);
    IntMatrix m1(dim);
    IntMatrix m2(dim , 5);
    IntMatrix m3;
    //IntMatrix::print(m2);

    cout << m2(1,0) << endl;
    cout << m2(1,0) + m3(0,0) << endl;
    m2(1,0) = -3; 
    cout << m2(1,0) << endl;
    m2 += 8;
    cout << m2(1,0) << endl;

    IntMatrix m_t = m2.transpose();
    cout << m_t(2,1) << endl;
    cout << m_t(1,2) << endl;
}