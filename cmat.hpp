#ifndef __CMAT_HPP__
#define __CMAT_HPP__

#include "mat.hpp"
#include <complex>


typedef Mat_<double> Mat;
typedef Mat_<Complex> CMat;



// COMPLEX FUNCTIONS

CMat conj(const VirtualMat_<Complex> &op);
Mat abs(const VirtualMat_<Complex> &op);
Mat real(const VirtualMat_<Complex> &op);
double norm(const VirtualMat_<Complex> &op, int n=2);
double norm2(const VirtualMat_<Complex> &op);
double norm1(const VirtualMat_<Complex> &op);


// sign of real part
CMat sign(const VirtualMat_<Complex> &op);
// max between real part of CMat and number
CMat max(const VirtualMat_<Complex> &op1, double op2);


#endif
