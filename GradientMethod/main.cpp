#include <functional>
#include <vector>
#include <cassert>
#include <iostream>
#include "IGradientMethod.h"

#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define N 2

int main() {
	{
		auto a = 2, b = 4, c = 5;
		auto func = [a, b, c](IVector const* x) -> double {
			assert(x->size() == N);
			auto x1 = x->at(0), x2 = x->at(1);
			return a * x1 + x2 + 4 * sqrt(1 + b * x1 * x1 + c * x2 * x2);
		};
		auto grad = [a, b, c](IVector const* x) -> IVector* {
			auto size = x->size();
			assert(size == N);

			auto x1 = x->at(0), x2 = x->at(1);
			auto value = sqrt(1 + b * x1 * x1 + c * x2 * x2);
			return IVector::create_vector({ a + 4.0 * b * x1 / value, 1 + 4.0 * c * x2 / value });
		};


		std::vector<double> tols = { 0.0001 };
		size_t signs = 2;


		auto n_dim_function = INDimFunction::create_function(func, grad, nullptr);
		auto gradient_method = IGradientMethod::create_grad_method(IGradientMethod::ORDER::FIRST, N, n_dim_function, 0);
		auto DFP_method = IGradientMethod::create_grad_method(IGradientMethod::ORDER::DFP, N, n_dim_function, 0);

		for (auto tol : tols) {
			std::cout << "Tol: " << tol << std::endl;

			gradient_method->set_tolerance(tol);
			auto x = gradient_method->calculate();
			x->print();
			std::cout << "\n";
			std::cout << "Counter: " << n_dim_function->get_counter() << std::endl;
			std::cout << "Gradient counter: " << n_dim_function->get_grad_counter() << std::endl;
			std::cout << "Function value: " << n_dim_function->at(x) << std::endl;
			n_dim_function->update_counter();
			std::cout << "\n\n\n";

			delete x;

			/*DFP_method->set_tolerance(tol);
			auto y = DFP_method->calculate();
			std::cout << "Optimal:\n";
			y->print();
			std::cout << std::endl;
			std::cout << "Counter: " << n_dim_function->get_counter() << std::endl;
			std::cout << "Gradient counter: " << n_dim_function->get_grad_counter() << std::endl;
			std::cout << "Function value: " << n_dim_function->at(y) << std::endl;
			n_dim_function->update_counter();
			std::cout << "\n\n\n";

			delete y;*/
		}

		delete gradient_method;
		delete n_dim_function;
		delete DFP_method;
	}

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();

	return 0;
}
