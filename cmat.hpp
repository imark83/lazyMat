#ifndef __CMAT_HPP__
#define __CMAT_HPP__

#include "mat.hpp"
#include <complex>


typedef std::complex<double> Complex;
typedef Mat_<double> Mat;
typedef Mat_<Complex> CMat_;


class CMat : public CMat_ {
public:

  CMat();
  CMat(int rows, int cols) : CMat_(rows, cols) {}
  CMat(const CMat &op) : CMat_(op) {}
  CMat(const CMat_ &op) : CMat_(op) {}
  CMat(const Mat &op);

  CMat &operator=(const CMat_ &op);

};

#endif
