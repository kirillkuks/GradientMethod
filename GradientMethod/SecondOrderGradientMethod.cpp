#include "SecondOrderGradientMethod.h"
#include "IMethod.h"
#include <iostream>

SecondOrderGradientMethod::SecondOrderGradientMethod(size_t dim, INDimFunction* const func, double tol)
	: dim{ dim }, func{ func }, tol{ tol } {}

void SecondOrderGradientMethod::set_tolerance(double tol_) {
	tol = tol_;
}

IVector* SecondOrderGradientMethod::calculate(double a) const {
	IVector* optimal = IVector::create_vector(dim);
	a = 1;
	Matrix* matrix = func->get_hesse(optimal);
	IVector* p = matrix->LDL(func->gradient_at(optimal));
	while (p->norm() > tol) {
		optimal = IVector::add(optimal, p);
		delete matrix;
		matrix = func->get_hesse(optimal);
		delete p;
		p = matrix->LDL(func->gradient_at(optimal));
	}
	delete matrix;
	delete p;
	return optimal;
}
