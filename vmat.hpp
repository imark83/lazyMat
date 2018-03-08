#ifndef __VMAT_HPP__
#define __VMAT_HPP__

template <class T>
class virtualMat_ {
public:
  int rows;
  int cols;
  mutable T *data;

  virtualMat_() : rows(0), cols(0), data(NULL) {}
  virtualMat_(int rows, int cols) : rows(rows), cols(cols), data(NULL) {}
  ~virtualMat_() {
    if(data != NULL) delete [] data;
  }

  virtual void eval () const = 0;
};
#endif
