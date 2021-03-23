#include "DichotomyMethod.h"

DichotomyMethod::DichotomyMethod(IFunction* const func, double tol, std::pair<double, double> const& data)
	: function(func), tolerance(tol), section(data) {}

void DichotomyMethod::set_tolerance(double tol) {
	tolerance = tol;
}

void DichotomyMethod::set_section(std::pair<double, double> const& data) {
	section = data;
}

double DichotomyMethod::calculate() {
	double a = section.first;
	double b = section.second;
	while (b - a >= tolerance) {
		double delta = (b - a) / 1000;
		double x1 = (a + b) / 2 - delta;
		double x2 = (a + b) / 2 + delta;
		if (function->at(x2) > function->at(x1)) {
			b = x2;
		}
		else {
			a = x1;
		}
	}
	return (a + b) / 2;
}

DichotomyMethod::~DichotomyMethod() {}
