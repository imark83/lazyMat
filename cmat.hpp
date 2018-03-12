#ifndef __CMAT_HPP__
#define __CMAT_HPP__

#include "mat.hpp"
#include <complex>


typedef Mat_<double> Mat;
typedef Mat_<Complex> CMat;


template<>
MatOperation_<double>::operator CMat() const{
  std::cout << "my cast OP!" << std::endl;
  CMat rop(this->rows,this->cols);
  this->eval();
  for(size_t i=0; i<rows*cols; ++i)
  rop(i) = (*this)(i);
  this->data = NULL;
  return rop;
}

CMat operator+(VirtualMat_<Complex> &op1, VirtualMat_<double> &op2) {
  op2.eval(); op1.eval();
  Mat resolvedOp2(op2);
  CMat rop(resolvedOp2);
  rop = op1 + rop;
  return rop;
}
//
// MatAdd_<Complex> operator+(
//   VirtualMat_<double> &op2,
//     VirtualMat_<Complex> &op1) {
//   return op1+op2;
// }


#endif
