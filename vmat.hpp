#ifndef __VMAT_HPP__
#define __VMAT_HPP__


template <class T>
T min(T a, T b) {if(a<b) return a; return b;}
template <class T>
T max(T a, T b) {if(a>b) return a; return b;}




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

  // MEMBER ACCESS
  T & operator()(int i, int j) const {
    return data[cols*i+j];
  }
  T & operator()(int i) const {
    return data[i];
  }
  // T & operator()(int i, int j) {
  //   return data[cols*i+j];
  // }

  virtual void eval () const = 0;
};
#endif
