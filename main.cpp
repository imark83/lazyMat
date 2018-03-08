#include <iostream>
#include <cstdlib>
#include "mat.hpp"


template <class T>
void getRand (Mat_<T> &rop) {
  for (int i=0; i<rop.rows; ++i) for (int j=0; j<rop.cols; ++j)
    rop(i,j) = (rand() % 11) - 5;
}

int main(int argc, char const *argv[]) {
  do {
    Mat_<double> a(3,4,{1,2,3,4,5,6,7,8,9,10,11,12});
    Mat_<double> b(3,4,{5,6,7,8,9,10,11,12,13,14,15,16});
    Mat_<double> c(3,4,{2,3,4,5,6,7,8,9,10,11,12,13,14,15,16});
    Mat_<double> d(3,3,{2,3,4,5,6,7,8,9,10,11,12,13});


    std::cout << "a+b = \n" << a+b << std::endl;
    std::cout << "a+(b+c) = \n" << a+(b+c) << std::endl;
    std::cout << "a+(c+a) = \n" << (c+a)+a << std::endl;
    std::cout << "+(a+b) = \n" << (a+b) << std::endl;
    std::cout << "a+b = \n" << a+b << std::endl;




  } while (0);
  return 0;
}
