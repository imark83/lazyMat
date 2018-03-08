#ifndef __MATRIX_OP_HPP__
#define __MATRIX_OP_HPP__

#include "vmat.hpp"

template <class T>
class matOperation_ : public virtualMat_<T> {
public:
  matOperation_(int rows, int cols) : virtualMat_<T>(rows, cols) {}
};

template <class T>
class unaryMatOperation_ : public matOperation_<T> {
public:
  const virtualMat_<T> *op;
  unaryMatOperation_(const virtualMat_<T> &op)
      : op(&op), matOperation_<T>(op.rows, op.cols) {}
};

template <class T>
class binaryMatOperation_ : public matOperation_<T> {
public:
  const virtualMat_<T> *op1;
  const virtualMat_<T> *op2;


  binaryMatOperation_(const virtualMat_<T> &op1, const virtualMat_<T> &op2)
      : op1(&op1), op2(&op2), matOperation_<T>(op1.rows, op1.cols) {}
};

// ADDITION
template <class T>
class matAdd_ : public binaryMatOperation_<T> {
public:

  matAdd_(const virtualMat_<T> &op1, const virtualMat_<T> &op2)
      : binaryMatOperation_<T>(op1, op2) {
    if(op1.rows != op2.rows || op1.cols != op2.cols) {
      std::cerr << "addition dimmensions missmatch" << std::endl;
      exit(1);
    }
  }

  void eval () const {
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
};

template <class T>
matAdd_<T> operator+(const virtualMat_<T> &op1, const virtualMat_<T> &op2) {
  matAdd_<T> rop(op1, op2);
  return rop;
}


// SUBSTRACTION
template <class T>
class matSub_ : public binaryMatOperation_<T> {
public:

  matSub_(const virtualMat_<T> &op1, const virtualMat_<T> &op2)
      : binaryMatOperation_<T>(op1, op2) {
    if(op1.rows != op2.rows || op1.cols != op2.cols) {
      std::cerr << "addition dimmensions missmatch" << std::endl;
      exit(1);
    }
  }

  void eval () const {
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
};

template <class T>
matSub_<T> operator-(const virtualMat_<T> &op1, const virtualMat_<T> &op2) {
  matSub_<T> rop(op1, op2);
  return rop;
}

template <class T>
class matNeg_ : public unaryMatOperation_<T> {
public:
  matNeg_(const virtualMat_<T> &op)
      : unaryMatOperation_<T>(op) {}
  void eval () const {
    if(this->data != NULL) {
      std::cerr << "reevaluation" << std::endl;
      exit(1);
    }
    this->op->eval();
    this->data = new T[this->rows*this->cols];
    for(int i=0; i<this->rows; ++i) for(int j=0; j<this->cols; ++j)
      this->data[this->cols*i+j] = -this->op->data[this->op->cols*i+j];
  }
};

template <class T>
matNeg_<T> operator-(const virtualMat_<T> &op) {
  matNeg_<T> rop(op);
  return rop;
}

#endif
