#ifndef __MATRIX_OP_HPP__
#define __MATRIX_OP_HPP__


// MACRO FOR UNARY MATRIX OPERATION
#define UNARY_MAT_OPERATION(className) \
  template <class T>\
  class className : public UnaryMatOperation_<T> {\
  public:\
    className(const VirtualMat_<T> &op)\
        : UnaryMatOperation_<T>(op) {}\
    void eval () const;\
  };

// MACRO FOR BINARY MATRIX OPERATION
#define BINARY_MAT_OPERATION(className) \
  template <class T>\
  class className : public BinaryMatOperation_<T> {\
  public:\
    className(const VirtualMat_<T> &op1, const VirtualMat_<T> &op2)\
        : BinaryMatOperation_<T>(op1, op2) {}\
    void eval () const;\
  };



#include "vmat.hpp"

template <class T>
class MatOperation_ : public VirtualMat_<T> {
public:
  MatOperation_(int rows, int cols) : VirtualMat_<T>(rows, cols) {}
};

template <class T>
class UnaryMatOperation_ : public MatOperation_<T> {
public:
  const VirtualMat_<T> *op;
  UnaryMatOperation_(const VirtualMat_<T> &op)
      : op(&op), MatOperation_<T>(op.rows, op.cols) {}
};

template <class T>
class BinaryMatOperation_ : public MatOperation_<T> {
public:
  const VirtualMat_<T> *op1;
  const VirtualMat_<T> *op2;


  BinaryMatOperation_(const VirtualMat_<T> &op1, const VirtualMat_<T> &op2)
      : op1(&op1), op2(&op2), MatOperation_<T>(op1.rows, op1.cols) {}
};

// ADDITION
BINARY_MAT_OPERATION(MatAdd_)
template <class T>
void MatAdd_<T>::eval () const {
  if(this->data != NULL) {
    std::cerr << "reevaluation" << std::endl;
    exit(1);
  }
  this->op1->eval(); this->op2->eval();
  this->data = new int[this->rows*this->cols];
  for(int i=0; i<this->rows; ++i) for(int j=0; j<this->cols; ++j)
  this->data[this->cols*i+j] =
  this->op1->data[this->op1->cols*i+j]
  + this->op2->data[this->op2->cols*i+j];
}
template <class T>
MatAdd_<T> operator+(const VirtualMat_<T> &op1, const VirtualMat_<T> &op2) {
  MatAdd_<T> rop(op1, op2);
  return rop;
}


// SUBSTRACTION
BINARY_MAT_OPERATION(MatSub_)
template <class T>
void MatSub_<T>::eval () const {
  if(this->data != NULL) {
    std::cerr << "reevaluation" << std::endl;
    exit(1);
  }
  this->op1->eval(); this->op2->eval();
  this->data = new int[this->rows*this->cols];
  for(int i=0; i<this->rows; ++i) for(int j=0; j<this->cols; ++j)
    this->data[this->cols*i+j] =
        this->op1->data[this->op1->cols*i+j]
        - this->op2->data[this->op2->cols*i+j];
}
template <class T>
MatSub_<T> operator-(const VirtualMat_<T> &op1, const VirtualMat_<T> &op2) {
  MatSub_<T> rop(op1, op2);
  return rop;
}

// MATRIX MINUS UNARY OPERATOR
UNARY_MAT_OPERATION(MatNeg_)
template <class T>
void MatNeg_<T>::eval () const {
  if(this->data != NULL) {
    std::cerr << "reevaluation" << std::endl;
    exit(1);
  }
  this->op->eval();
  this->data = new T[this->rows*this->cols];
  for(int i=0; i<this->rows; ++i) for(int j=0; j<this->cols; ++j)
    this->data[this->cols*i+j] = -this->op->data[this->op->cols*i+j];
}
template <class T>
MatNeg_<T> operator-(const VirtualMat_<T> &op) {
  MatNeg_<T> rop(op);
  return rop;
}

#endif
