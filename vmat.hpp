#ifndef __VMAT_HPP__
#define __VMAT_HPP__

template <class T>
class VirtualMat_ {
public:
  int rows;
  int cols;
  mutable T *data;

  VirtualMat_() : rows(0), cols(0), data(NULL) {}
  VirtualMat_(int rows, int cols) : rows(rows), cols(cols), data(NULL) {}
  ~VirtualMat_() {
    if(data != NULL) delete [] data;
  }

  virtual void eval () const = 0;
};
#endif
