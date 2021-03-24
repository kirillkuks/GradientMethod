#pragma once
#include "IGradientMethod.h"

class FirstOrderGradientMethod : public IGradientMethod {
public:
	FirstOrderGradientMethod(size_t dim, INDimFunction* const func, double tol);

	void set_tolerance(double tol) override;
	IVector* calculate(double a) const override;

	~FirstOrderGradientMethod() {}

private:
	size_t dim;
	INDimFunction* func;
	double tol;
};
