#include <iostream>
#include "IntMatrix.h"
using std::cout;
using std::endl;
using mtm::IntMatrix;
using mtm::Dimensions;

IntMatrix::IntMatrix(Dimensions d, int init_val ):dimension(d){
    
    matrix = new int* [dimension.getRow()];
    for(int i=0 ; i < dimension.getRow() ; i++){
        matrix[i] = new int[dimension.getCol()];
            for( int j=0 ; j < dimension.getCol() ; j++){
                matrix[i][j] = init_val;
            }
    }
}

IntMatrix IntMatrix::Identity(int dimension){
    
    Dimensions dim(dimension,dimension);
    IntMatrix identity(dim);
    for(int i=0 ; i <dimension ; i++){
        identity(i,i) = 1; //TODO check if it's OK to write  1 
    }
    return identity;
}

IntMatrix IntMatrix::transpose() const{

    int t_row = dimension.getCol() , t_col = dimension.getRow() ;
    Dimensions t_dimension(t_row,t_col);
    IntMatrix t_matrix(t_dimension);
    for(int i=0 ; i < t_row ; i++){
        for(int j=0 ; j < t_col ; j++){
            t_matrix(i,j) = matrix[j][i];
        }
    }
    return t_matrix;
}

int& IntMatrix::operator()(int row_val , int col_val){
    return matrix[row_val][col_val];
}

IntMatrix IntMatrix::operator-() const{

    IntMatrix tmp = *this; //TODO test it if this works !!
    // for(int i=0 ; i < dimension.getRow()  ; i++){
    //   for(int j=0 ; j < dimension.getCol()  ; j++){
    //     tmp(i,j)*=-1;
    //   }
    // }
    
    for(IntMatrix::iterator it = tmp.begin() ;it !=tmp.end() ;++it ) { //TODO pick one
        (*it) *= -1;
    }
    return tmp ;
}

IntMatrix& IntMatrix::operator+=(const IntMatrix& a){

    for(IntMatrix::iterator it_a = a.begin() , it_b = *this.begin() ; it_a !=a.end() ; ++it_a , ++it_b ) { 
        *it_b = *it_a;
    }
    return *this;
}

IntMatrix operator+(const IntMatrix& a ,const IntMatrix& b);{
    IntMatrix tmp = a;
    return tmp += b;
}


bool mtm::all(const IntMatrix& a){

    for(IntMatrix::const_iterator it = a.begin() ;it !=a.end() ; ++it ) { 
        if(!(*it)){
            return false;
        }
    }
    return true;
}
bool mtm::any(const IntMatrix& a){

    for(IntMatrix::const_iterator it = a.begin() ;it !=a.end() ; ++it ) { 
        if((*it)){
            return true;
        }
    }
    return false;
}





int main(){

    
    Dimensions dim(5 ,3);
    IntMatrix m1(dim);
    IntMatrix m2(dim , 5);

    cout << m2(1,0) << endl;

    m2(1,0) = 99;
    m2(2,1) = 8;
    cout << m2(1,0) << endl;

    IntMatrix m_t = m2.transpose();
    cout << m_t(2,1) << endl;
    cout << m_t(1,2) << endl;


    
    
}