#include "ParabolicMethod.h"
#include <iostream>
#include <vector>

ParabolicMethod::ParabolicMethod(IFunction* const function, double tol, std::pair<double, double> const& section)
	: function{ function }, tol{ tol }, section{ section } {}

ParabolicMethod::~ParabolicMethod() {}

void ParabolicMethod::set_tolerance(double tol_) {
	tol = tol_;
}

void ParabolicMethod::set_section(std::pair<double, double> const& section_) {
	section = section_;
}

decltype(auto) ParabolicMethod::first_aproximation() {
	double a = section.first;
	double b = section.second;

	double x = (a + b) / 2;

	double fa = function->at(a);
	double fb = function->at(b);
	double fx = function->at(x);

	while (!(fa >= fx && fx <= fb)) {
		if (fa <= fx) {
			b = x;
			fb = fx;
		}
		else {
			a = x;
			fa = fx;
		}
		x = (a + b) / 2;
		fx = function->at(x);
	}
	return std::vector<std::pair<double, double>> { {a, fa}, { x, fx }, { b, fb }};
}

double ParabolicMethod::calculate() {
	double x1 = section.first;
	double x3 = section.second;

	if (x3 - x1 >= tol) {
		auto fa = first_aproximation();

		x1 = fa[0].first;
		double x2 = fa[1].first;
		x3 = fa[2].first;
		double f1 = fa[0].second;
		double f2 = fa[1].second;
		double f3 = fa[2].second;

		while (x3 - x1 >= tol) {
			double a1 = (f2 - f1) / (x2 - x1);
			double a2 = (1.0 / (x3 - x2)) * (((f3 - f1) / (x3 - x1)) - ((f2 - f1) / (x2 - x1)));

			double x = (1.0 / 2) * (x1 + x2 - a1 / a2);

			double f = function->at(x);

			if (x2 < x) {
				if (f2 <= f) {
					x3 = x;
					f3 = f;
				}
				else {
					x1 = x2;
					f1 = f2;
					x2 = x;
					f2 = f;
				}
			}
			else {
				if (f <= f2) {
					x3 = x2;
					f3 = f2;
					x2 = x;
					f2 = f;
				}
				else {
					x1 = x;
					f1 = f;
				}
			}
		}
	}

	return (x1 + x3) / 2;
}
