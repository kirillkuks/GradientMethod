#include <functional>
#include <vector>
#include <cassert>
#include "IGradientMethod.h"

#define N 2

int main() {
	auto a = 2, b = 4, c = 5;
	auto func = [a, b, c](std::vector<double> const& x) -> double {
		assert(x.size() == N);
		auto x1 = x[0], x2 = x[1];
		return a * x1 + x2 + 4 * sqrt(1 + b * x1 * x1 + c * x2 * x2);
	};
	auto grad = [a, b, c](std::vector<double> const& x) -> std::vector<double> {
		auto size = x.size();
		assert(size == N);

		auto x1 = x[0], x2 = x[1];
		auto value = sqrt(1 + b * x1 * x1 + c * x2 * x2);
		return { a + 4 * b * x1 / value, 1 + 4 * c * x2 / value };
	};

	std::vector<double> tols = { 0.1, 0.001, 0.00001 };
	auto n_dim_function = INDimFunction::create_function(func, grad);
	auto gradient_method = IGradientMethod::create_grad_method(IGradientMethod::ORDER::FIRST, N, n_dim_function, tols[0]);

	delete gradient_method;
	delete n_dim_function;

	return 0;
}
