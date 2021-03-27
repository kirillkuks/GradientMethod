#pragma once
#include "IGradientMethod.h"

class SecondOrderGradientMethod : public IGradientMethod {
public:
	SecondOrderGradientMethod(size_t dim, INDimFunction* const func, double tol);

	void set_tolerance(double tol) override;
	IVector* calculate(double a) const override;

	~SecondOrderGradientMethod() {}
private:
	size_t dim;
	INDimFunction* func;
	double tol;
};