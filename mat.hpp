#ifndef __MAT_HPP__
#define __MAT_HPP__

#include <vector>
#include <cstring>
#include "matOp.hpp"
#include <complex>

template <class T>
class Mat_ : public VirtualMat_<T> {
public:

  // CONSTRUCTOR
  Mat_() : VirtualMat_<T>() {}
  Mat_(int rows, int cols) : VirtualMat_<T>(rows, cols) {
    this->data = new T[rows*cols];
  }
  Mat_(const Mat_ &op) : VirtualMat_<T>(op.rows, op.cols) {
    // if (op.data != NULL)
    this-> data = new T[op.rows*op.cols];
    memcpy(this->data, op.data, op.rows*op.cols*sizeof(T));
  }
  Mat_(int rows, int cols, std::vector<T> op)
        : VirtualMat_<T>(rows, cols) {
    this->data = new T[rows*cols];
    for(size_t i=0; i<rows*cols; ++i)
      this->data[i] = op[i];
  }

  operator Mat_<std::complex<double> >() const {
    std::cout << "my cast!" << std::endl;
    Mat_<std::complex<double> > rop(this->rows,this->cols);
    for(size_t i = 0; i<this->rows*this->cols; ++i)
      rop(i) = this->data[i];

    return rop;
  }

  // ASSIGNMENT
  Mat_ & operator=(const Mat_ &op) {
    delete [] this->data;
    this->rows = op.rows; this->cols = op.cols;
    this->data = new T[this->rows*this->cols];
    for(int i=0; i<this->rows; ++i) for(int j=0; j<this->cols; ++j)
      this->data[this->cols*i+j] = op.data[this->cols*i+j];

    return *this;
  }
  Mat_ & operator=(const MatOperation_<T> &op) {
    op.eval();
    delete [] this->data;
    this->rows = op.rows; this->cols = op.cols;
    this->data = op.data; op.data = NULL;

    return *this;
  }

  // virtual method
  virtual void eval () const {}
};


// FRIEND OPERATORS
// OUTPUT STREAM
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

#endif
