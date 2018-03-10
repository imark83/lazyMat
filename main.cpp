#include <iostream>
#include <cstdlib>
#include "cmat.hpp"


template <class T>
void getRand (Mat_<T> &rop) {
  for (int i=0; i<rop.rows; ++i) for (int j=0; j<rop.cols; ++j)
    rop(i,j) = (rand() % 11) - 5;
}

int main(int argc, char const *argv[]) {
  do {
    Mat a(3,3,{1,2,3,4,5,6,7,8,9});
    Mat b(3,3,{5,6,7,8,9,10,11,12,13});
    // Mat_<double> c(3,4,{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16});
    // Mat_<double> d(3,3,{2,3,4,5,6,7,8,9,10,11,12,13});

    std::cout << "a = \n" << a << std::endl;
    std::cout << "b = \n" << b << std::endl;
    // std::cout << "c = \n" << c << std::endl;

    CMat c(a);
    a= (b+a);
    c=a;
    c = c*Complex(0,1) + CMat(b);
    std::cout << "c = \n" << c << std::endl;


  } while (0);
  return 0;
}
