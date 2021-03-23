#include"FibonacciMethod.h"
#include"iostream"
#include<map>

FibonacciMethod::FibonacciMethod(IFunction* const func, double t, std::pair<double, double> const& seg) : function(func), tol(t), section(seg) {}

void FibonacciMethod::set_tolerance(double t) {
	tol = t;
}

void FibonacciMethod::set_section(std::pair<double, double> const& seg) {
	section = seg;
}

double FibonacciMethod::calculate() {
	std::map <int, int> fib_num;
	double num = ceil((section.second - section.first) / tol);
	fib_num[0] = 1;
	fib_num[1] = 1;
	for (int i = 1; fib_num[i] < num; i++) {
		fib_num[i + 1] = fib_num[i] + fib_num[i - 1];
	}
	double lambda = section.first + (double)fib_num[fib_num.size() - 3] / fib_num[fib_num.size() - 1] * (section.second - section.first);
	double mu = section.first + (double)fib_num[fib_num.size() - 2] / fib_num[fib_num.size() - 1] * (section.second - section.first);
	double a = section.first;
	double b = section.second;
	fib_num[1];
	for (size_t i = 1; i < fib_num.size() - 2; i++) {
		if (function->at(lambda) > function->at(mu)) {
			a = lambda;
			lambda = mu;
			mu = a + (double)fib_num[fib_num.size() - i - 2] / fib_num[fib_num.size() - i - 1] * (b - a);
		}
		else {
			b = mu;
			mu = lambda;
			lambda = a + (double)fib_num[fib_num.size() - i - 3] / fib_num[fib_num.size() - i - 1] * (b - a);
		}
	}
	return (a + b) / 2;
}

FibonacciMethod::~FibonacciMethod() {}
