#ifndef __MATRIX_OP_HPP__
#define __MATRIX_OP_HPP__

#include "vmat.hpp"
#include <iostream>

template <class T>
class Mat_;

// MACRO FOR UNARY MATRIX OPERATION
#define UNARY_MAT_OPERATION(className) \
  template <class T>\
  class className : public UnaryMatOperation_<T> {\
  public:\
    className(const VirtualMat_<T> &op)\
        : UnaryMatOperation_<T>(op) {}\
    void eval() const;\
  };

// MACRO FOR BINARY MATRIX OPERATION
#define BINARY_MAT_OPERATION(className) \
  template <class T>\
  class className : public BinaryMatOperation_<T> {\
  public:\
    className(const VirtualMat_<T> &op1, const VirtualMat_<T> &op2)\
        : BinaryMatOperation_<T>(op1, op2) {}\
    void eval() const;\
  };


// MACRO FOR SCALAR PRODUCT MATRIX OPERATION
#define SCALAR_PRODUCT_MAT_OPERATION(className) \
template <class T>\
class className : public ScalarProductMatOperation_<T> {\
public:\
    className(const T op1, const VirtualMat_<T> &op2)\
        : ScalarProductMatOperation_<T>(op1, op2) {}\
    void eval() const;\
  };


template <class T>
class MatOperation_ : public VirtualMat_<T> {
public:
  MatOperation_(int rows, int cols) : VirtualMat_<T>(rows, cols) {}

  operator Mat_<Complex>() const;

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
      : op1(&op1), op2(&op2), MatOperation_<T>(op1.rows, op2.cols) {}
};

template <class T>
class ScalarProductMatOperation_ : public MatOperation_<T> {
public:
  const T op1;
  const VirtualMat_<T> *op2;


  ScalarProductMatOperation_(const T op1, const VirtualMat_<T> &op2)
      : op1(op1), op2(&op2), MatOperation_<T>(op2.rows, op2.cols) {}
};

// ADDITION
BINARY_MAT_OPERATION(MatAdd_)
template <class T>
void MatAdd_<T>::eval() const {
  if(this->op1->rows != this->op2->rows || this->op1->cols != this->op2->cols) {
    std::cerr << "dimensions missmatch" << std::endl;
    exit(1);
  }
  if(this->data != NULL) {
    std::cerr << "reevaluation" << std::endl;
    exit(1);
  }

  if(this->op1->data == NULL) {
    this->op1->eval(); this->op2->eval();
    this->data = this->op1->data;
    this->op1->data = NULL;
    for(size_t i=0; i<this->rows*this->cols; ++i)
      (*this)(i) += (*(this->op2))(i);
  } else if(this->op2->data == NULL) {
    this->op1->eval(); this->op2->eval();
    this->data = this->op2->data;
    this->op2->data = NULL;
    for(size_t i=0; i<this->rows*this->cols; ++i)
      (*this)(i) += (*(this->op1))(i);
  } else {
    this->op1->eval(); this->op2->eval();
    this->data = new T[this->rows*this->cols];
    for(size_t i=0; i<this->rows*this->cols; ++i)
      (*this)(i) = (*(this->op1))(i) + (*(this->op2))(i);
  }
}
template <class T>
MatAdd_<T> operator+(const VirtualMat_<T> &op1, const VirtualMat_<T> &op2) {
  return MatAdd_<T>(op1, op2);
}

// MatAdd_<Complex> operator+(VirtualMat_<Complex> &op1,
//       VirtualMat_<double> &op2) {
//   CMat tmp(op2);
//   return op1 + tmp;
// }



// MATRIX MINUS UNARY OPERATOR
UNARY_MAT_OPERATION(MatNeg_)
template <class T>
void MatNeg_<T>::eval() const {
  if(this->data != NULL) {
    std::cerr << "reevaluation" << std::endl;
    exit(1);
  }
  // CHECK WHETHER OP2 IS MATOP OR PURE MAT
  if(this->op->data == NULL) {
    this->op->eval();
    this->data = this->op->data;
    this->op->data = NULL;
    for(size_t i=0; i<this->rows*this->cols; ++i)
      (*this)(i) = -(*this)(i);

  } else {
    this->op->eval();
    this->data = new T[this->rows*this->cols];
    for(size_t i=0; i<this->rows*this->cols; ++i)
      (*this)(i) = -(*(this->op))(i);
  }
}
template <class T>
MatNeg_<T> operator-(const VirtualMat_<T> &op) {
  return MatNeg_<T>(op);
}


// SUBSTRACTION
BINARY_MAT_OPERATION(MatSub_)
template <class T>
void MatSub_<T>::eval() const {
  if(this->op1->rows != this->op2->rows || this->op1->cols != this->op2->cols) {
    std::cerr << "dimensions missmatch" << std::endl;
    exit(1);
  }
  if(this->data != NULL) {
    std::cerr << "reevaluation" << std::endl;
    exit(1);
  }

  if(this->op1->data == NULL) {
    this->op1->eval(); this->op2->eval();
    this->data = this->op1->data;
    this->op1->data = NULL;
    for(size_t i=0; i<this->rows*this->cols; ++i)
      (*this)(i) -= (*(this->op2))(i);
  } else if(this->op2->data == NULL) {
    this->op1->eval(); this->op2->eval();
    this->data = this->op2->data;
    this->op2->data = NULL;
    for(size_t i=0; i<this->rows*this->cols; ++i)
      (*this)(i) = -((*this)(i) - (*(this->op1))(i));
  } else {
    this->op1->eval(); this->op2->eval();
    this->data = new T[this->rows*this->cols];
    for(size_t i=0; i<this->rows*this->cols; ++i)
      (*this)(i) = (*(this->op1))(i) - (*(this->op2))(i);
  }
}
template <class T>
MatSub_<T> operator-(const VirtualMat_<T> &op1, const VirtualMat_<T> &op2) {
  return MatSub_<T>(op1, op2);
}

// SCALAR PRODUCT
SCALAR_PRODUCT_MAT_OPERATION(MatScalarProd_)
template <class T>
void MatScalarProd_<T>::eval() const {
  if(this->data != NULL) {
    std::cerr << "reevaluation" << std::endl;
    exit(1);
  }
  // CHECK WHETHER OP2 IS MATOP OR PURE MAT
  if(this->op2->data == NULL) {
    this->op2->eval();
    this->data = this->op2->data;
    this->op2->data = NULL;
    for(size_t i=0; i<this->rows*this->cols; ++i) {
      (*this)(i) *= (this->op1);
    }
  } else {
    this->op2->eval();
    this->data = new T[this->rows*this->cols];
    for(size_t i=0; i<this->rows*this->cols; ++i) {
      (*this)(i) =
            (this->op1) * (*(this->op2))(i);
    }
  }
}
template <class T>
MatScalarProd_<T> operator*(const T op1, const VirtualMat_<T> &op2) {
  return MatScalarProd_<T>(op1, op2);
}
template <class T>
MatScalarProd_<T> operator*(const VirtualMat_<T> &op2, const T op1) {
  return MatScalarProd_<T>(op1, op2);
}
template <class T>
MatScalarProd_<T> operator*(const int op1, const VirtualMat_<T> &op2) {
  return MatScalarProd_<T>(T(op1), op2);
}
template <class T>
MatScalarProd_<T> operator*(const VirtualMat_<T> &op2, const int op1) {
  return MatScalarProd_<T>(T(op1), op2);
}


// DIVISION matrix / scalar
// store scalar -> op1, matrix ->op2
SCALAR_PRODUCT_MAT_OPERATION(MatScalarDivision_)
template <class T>
void MatScalarDivision_<T>::eval() const {
  if(this->data != NULL) {
    std::cerr << "reevaluation" << std::endl;
    exit(1);
  }
  // CHECK WHETHER OP2 IS MATOP OR PURE MAT
  if(this->op2->data == NULL) {
    this->op2->eval();
    this->data = this->op2->data;
    this->op2->data = NULL;
    for(size_t i=0; i<this->rows*this->cols; ++i) {
      (*this)(i) /= (this->op1);
    }
  } else {
    this->data = new T[this->rows*this->cols];
    for(size_t i=0; i<this->rows*this->cols; ++i) {
      (*this)(i) =
            (*(this->op2))(i) / (this->op1);
    }
  }
}
template <class T>
MatScalarDivision_<T> operator/(const VirtualMat_<T> &op2, const T op1) {
  return MatScalarDivision_<T>(op1, op2);
}
template <class T>
MatScalarDivision_<T> operator/(const VirtualMat_<T> &op2, const int op1) {
  return MatScalarDivision_<T>(T(op1), op2);
}


// CLASSICAL MATRIX PRODUCT
BINARY_MAT_OPERATION(MatProd_)
template <class T>
void MatProd_<T>::eval() const {
  if(this->op1->cols != this->op2->rows) {
    std::cerr << "dimensions missmatch" << std::endl;
    exit(1);
  }
  if(this->data != NULL) {
    std::cerr << "reevaluation" << std::endl;
    exit(1);
  }
  this->op1->eval();
  this->op2->eval();
  this->data = new T[this->rows*this->cols];
  for(size_t i=0; i<this->rows; ++i) for(size_t j=0; j<this->cols; ++j) {
    // (*this)(i,j) = T(0);
    (*this)(i,j) = T(0);
    for(size_t k=0; k<this->op1->cols; ++k)
      (*this)(i,j) = (*this)(i,j) + (*(this->op1))(i,k) * (*(this->op2))(k,j);
  }
}
template <class T>
MatProd_<T> operator*(const VirtualMat_<T> &op1, const VirtualMat_<T> &op2) {
  return MatProd_<T>(op1, op2);
}


// POINT TO POINT PRODUCT
BINARY_MAT_OPERATION(MatPointProd_)
template <class T>
void MatPointProd_<T>::eval() const {
  if(this->op1->rows != this->op2->rows || this->op1->cols != this->op2->cols) {
    std::cerr << "dimensions missmatch" << std::endl;
    exit(1);
  }
  if(this->data != NULL) {
    std::cerr << "reevaluation" << std::endl;
    exit(1);
  }
  if(this->op1->data == NULL) {
    this->op1->eval(); this->op2->eval();
    this->data = this->op1->data;
    this->op1->data = NULL;
    for(size_t i=0; i<this->rows*this->cols; ++i)
      (*this)(i) *= (*(this->op2))(i);
  } else if(this->op2->data == NULL) {
    this->op1->eval(); this->op2->eval();
    this->data = this->op2->data;
    this->op2->data = NULL;
    for(size_t i=0; i<this->rows*this->cols; ++i)
      (*this)(i) *=(*(this->op1))(i);
  } else {
    this->op1->eval(); this->op2->eval();
    this->data = new T[this->rows*this->cols];
    for(size_t i=0; i<this->rows*this->cols; ++i)
    (*this)(i) = (*(this->op1))(i) * (*(this->op2))(i);
  }
}
template <class T>
MatPointProd_<T> operator^(const VirtualMat_<T> &op1,
        const VirtualMat_<T> &op2) {
  return MatPointProd_<T>(op1, op2);
}
// POINT SQUARE
template <class T>
MatPointProd_<T> pow2(const VirtualMat_<T> &op) {
  return MatPointProd_<T>(op, op);
}


// POINT TO POINT DIVISION
BINARY_MAT_OPERATION(MatPointDiv_)
template <class T>
void MatPointDiv_<T>::eval() const {
  if(this->op1->rows != this->op2->rows || this->op1->cols != this->op2->cols) {
    std::cerr << "dimensions missmatch" << std::endl;
    exit(1);
  }
  if(this->data != NULL) {
    std::cerr << "reevaluation" << std::endl;
    exit(1);
  }
  if(this->op1->data == NULL) {
    this->op1->eval(); this->op2->eval();
    this->data = this->op1->data;
    this->op1->data = NULL;
    for(size_t i=0; i<this->rows*this->cols; ++i)
      (*this)(i) /= (*(this->op2))(i);
  } else if(this->op2->data == NULL) {
    this->op1->eval(); this->op2->eval();
    this->data = this->op2->data;
    this->op2->data = NULL;
    for(size_t i=0; i<this->rows*this->cols; ++i)
      (*this)(i) = (*(this->op1))(i) / (*this)(i);
  } else {
    this->op1->eval(); this->op2->eval();
    this->data = new T[this->rows*this->cols];
    for(size_t i=0; i<this->rows*this->cols; ++i)
      (*this)(i) = (*(this->op1))(i) / (*(this->op2))(i);
  }
}
template <class T>
MatPointDiv_<T> operator/(const VirtualMat_<T> &op1,
        const VirtualMat_<T> &op2) {
  return MatPointDiv_<T>(op1, op2);
}


// DIFF operator by rows. Adds final row with zeros
UNARY_MAT_OPERATION(MatDiffX_)
template <class T>
void MatDiffX_<T>::eval() const {
  if(this->op->rows < 2) {
    std::cerr << "Minimum number of rows to differenciate is 2" << std::endl;
    exit(1);
  }
  this->data = new T[this->rows*this->cols];
  for(size_t i=this->rows-2; i>=0; --i) for(size_t j=0; j<this->cols; ++j)
    (*this)(i,j) = (*(this->op))(i+1,j) - (*(this->op))(i,j);
  for(size_t j=0; j<this->rows; ++j)
    (*this)(this->rows-1,j) = T(0);

}
template <class T>
MatDiffX_<T> diffX(const VirtualMat_<T> &op) {
  return MatDiffX_<T>(op);
}



// DIFF operator by cols. Adds final col with zeros
UNARY_MAT_OPERATION(MatDiffY_)
template <class T>
void MatDiffY_<T>::eval() const {
  if(this->op->rows < 2) {
    std::cerr << "Minimum number of rows to differenciate is 2" << std::endl;
    exit(1);
  }
  this->data = new T[this->rows*this->cols];
  for(size_t j=this->cols-2; j>=0; --j) for(size_t i=0; i<this->rows; ++i)
    (*this)(i,j) = (*(this->op))(i,j+1) - (*(this->op))(i,j);
  for(size_t i=0; i<this->rows; ++i)
    (*this)(i,this->cols-1) = T(0);
}
template <class T>
MatDiffY_<T> diffY(const VirtualMat_<T> &op) {
  return MatDiffY_<T>(op);
}

#endif
