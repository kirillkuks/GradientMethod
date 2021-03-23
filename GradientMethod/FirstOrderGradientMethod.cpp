#include "FirstOrderGradientMethod.h"
using xn_t = std::vector<double>;

FirstOrderGradientMethod::FirstOrderGradientMethod(size_t dim, INDimFunction const* func, double tol)
	: dim{ dim }, func{ func }, tol{ tol } {}

void FirstOrderGradientMethod::set_tolerance(double tol_) {
	tol = tol_;
}

xn_t FirstOrderGradientMethod::calculate() const {
	xn_t optimal(dim);



	return optimal;
}