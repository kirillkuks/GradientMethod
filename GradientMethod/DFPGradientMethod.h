#pragma once
#include "IGradientMethod.h"

class DFPGradientMethod : public IGradientMethod {
public:
	DFPGradientMethod(size_t dim, INDimFunction* const func, double tol);

	void set_tolerance(double tol_) override;
	IVector* calculate(double a) const override;

	~DFPGradientMethod() {}

private:
	void next_matrix_approximation(Matrix& A, IVector const* delta_x, IVector const* delta_y) const;

	size_t dim;
	INDimFunction* func;
	double tol;
};