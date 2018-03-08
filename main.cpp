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
    Mat_<double> a(2,2);
    Mat_<double> b(2,2);
    Mat_<double> c(2,3);
    Mat_<double> d(3,5);
    Mat_<double> e(2,2);

    getRand(a);
    getRand(b);
    getRand(c);
    getRand(d);

    std::cout << "a = \n" << a << std::endl;
    std::cout << "b = \n" << b << std::endl;
    std::cout << "a.*b = \n" << (a^b) << std::endl;
    std::cout << "a+b = \n" << (a+b) << std::endl;
    std::cout << "a.^2 = \n" << pow2(a) << std::endl;

    std::cout << "d = \n" << d << std::endl;
    std::cout << "diff(d,1) = \n" << diffX(d) << std::endl;
    std::cout << "diff(d,2) = \n" << diffY(d) << std::endl;


  } while (0);
  return 0;
}
