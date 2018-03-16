#include "cmat.hpp"

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



Mat real(const VirtualMat_<Complex> &op) {
  op.eval();
  Mat rop(op.rows,op.cols);
  for(size_t i=0; i<rop.rows*rop.cols; ++i)
    rop(i) = std::real(op(i));
}

//
double norm(const VirtualMat_<Complex> &op, int n) {
  switch (n) {
    case 0: return norm0(op);
    case 1: return norm1(op);
    default: return norm2(op);
  }
  return 0.0;
}

double norm0(const VirtualMat_<Complex> &op) {
  op.eval();
  double rop = 0.0;
  for(size_t i=0; i<op.rows*op.cols; ++i) {
    if ((double) std::abs(op(i)) > rop) rop = std::abs(op(i));
  }
  return rop;
}

double norm1(const VirtualMat_<Complex> &op) {
  op.eval();
  double rop = 0.0;
  for(size_t i=0; i<op.rows*op.cols; ++i)
    rop += std::abs(op(i));
  return rop;
}

double norm2(const VirtualMat_<Complex> &op) {
  op.eval();
  double rop = 0.0;
  for(size_t i=0; i<op.rows*op.cols; ++i)
    rop += std::abs(op(i))*std::abs(op(i));
  return sqrt(rop);
}
