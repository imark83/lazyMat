#ifndef __MAT_HPP__
#define __MAT_HPP__

#include "matOp.hpp"

template <class T>
class Mat_ : public virtualMat_<T> {
public:

  // CONSTRUCTOR
  Mat_() : virtualMat_<T>() {}
  Mat_(int rows, int cols) : virtualMat_<T>(rows, cols) {
    this->data = new int[rows*cols];
  }

  // MEMBER ACCESS
  int& operator()(int i, int j) {
    return this->data[this->cols*i+j];
  }
  const int& operator()(int i, int j) const {
    return this->data[this->cols*i+j];
  }

  // ASSIGNMENT
  Mat_ & operator=(const Mat_ &op) {
    delete [] this->data;
    this->rows = op.rows; this->cols = op.cols;
    this->data = new int[this->rows*this->cols];
    for(int i=0; i<this->rows; ++i) for(int j=0; j<this->cols; ++j)
      this->data[this->cols*i+j] = op.data[this->cols*i+j];

    return *this;
  }
  Mat_ & operator=(const matOperation_<T> &op) {
    op.eval();
    delete [] this->data;
    this->rows = op.rows; this->cols = op.cols;
    this->data = op.data; op.data = NULL;

    return *this;
  }

  // virtual method
  virtual void eval () const {}
};
#endif
