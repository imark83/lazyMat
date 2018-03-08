#include <iostream>
#include <cstdlib>
#include "mat.hpp"

template <class T>
T min(T a, T b) {if(a<b) return a; return b;}
template <class T>
T max(T a, T b) {if(a>b) return a; return b;}



// FRIEND OPERATORS
template <class T>
std::ostream & operator<<(std::ostream &output, const Mat_<T> &op) {
  int rows = min((int) op.rows, 8);
  int cols = min((int) op.cols, 7);
  for(int i=0; i<rows; ++i){
    for(int j=0; j<cols; ++j)
      output << op(i,j) << "  ";
    if(op.cols > 7) output << "...";
    output << std::endl;
  }
  if(op.rows > 8) output << "..." << std::endl;
  return output;
}

template <class T>
std::ostream & operator<<(std::ostream &output, const MatOperation_<T> &op) {
  Mat_<T> tmp;
  tmp = op;
  output << tmp;
  return output;
}



void getRand (Mat_<int> &rop) {
  for (int i=0; i<rop.rows; ++i) for (int j=0; j<rop.cols; ++j)
    rop(i,j) = (rand() % 11) - 5;
}

int main(int argc, char const *argv[]) {
  do {
    Mat_<int> a(2,2);
    Mat_<int> b(2,2);
    Mat_<int> c(2,2);
    Mat_<int> d(2,2);
    Mat_<int> e(2,2);

    getRand(a);
    getRand(b);
    getRand(c);
    getRand(d);
    e = (a+b) - (c+d);

    std::cout << "a = \n" << a << std::endl;
    std::cout << "b = \n" << b << std::endl;
    std::cout << "c = \n" << c << std::endl;
    std::cout << "d = \n" << d << std::endl;

    std::cout << "-a = \n" << (-a) << std::endl;
    std::cout << "a+b = \n" << a+b << std::endl;

  } while (0);
  return 0;
}
