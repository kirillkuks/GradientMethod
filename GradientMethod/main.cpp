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
		auto funcDer11 = [a, b, c](IVector const* x) -> double {
			assert(x->size() == N);
			auto x1 = x->at(0), x2 = x->at(1);
			return (4 * b + 4 * b * c * x2 * x2) / ((1 + b * x1 * x1 + c * x2 * x2) * sqrt(1 + b * x1 * x1 + c * x2 * x2));
		};
		auto funcDer12 = [a, b, c](IVector const* x) -> double {
			assert(x->size() == N);
			auto x1 = x->at(0), x2 = x->at(1);
			return (4 * b * c * x1 * x2) / ((1 + b * x1 * x1 + c * x2 * x2) * sqrt(1 + b * x1 * x1 + c * x2 * x2));
		};
		auto funcDer22 = [a, b, c](IVector const* x) -> double {
			assert(x->size() == N);
			auto x1 = x->at(0), x2 = x->at(1);
			return (4 * c + 4 * b * c * x1 * x1) / ((1 + b * x1 * x1 + c * x2 * x2) * sqrt(1 + b * x1 * x1 + c * x2 * x2));
		};
		auto grad = [a, b, c](IVector const* x) -> IVector* {
			auto size = x->size();
			assert(size == N);

			auto x1 = x->at(0), x2 = x->at(1);
			auto value = sqrt(1 + b * x1 * x1 + c * x2 * x2);
			return IVector::create_vector({a + 4.0 * b * x1 / value, 1 + 4.0 * c * x2 / value });
		};


		std::vector<double> tols = { 0.1, 0.001, 0.000001 };
		std::vector < std::function<double(IVector const*)>> ders = std::vector < std::function<double(IVector const*)>>{funcDer11, funcDer12, funcDer12, funcDer22};
		Hesse* matrix = new Hesse(ders, 2, 2);
		auto n_dim_function = INDimFunction::create_function(func, grad, matrix);
		auto n_dim_function2 = INDimFunction::create_function(func, grad, matrix);
		auto gradient_method = IGradientMethod::create_grad_method(IGradientMethod::ORDER::FIRST, N, n_dim_function, 0);
		auto gradient_method2 = IGradientMethod::create_grad_method(IGradientMethod::ORDER::SECOND, N, n_dim_function2, 0);

		for (auto tol : tols) {
			gradient_method->set_tolerance(tol);
			gradient_method2->set_tolerance(tol);
			IVector* x = gradient_method->calculate();
			IVector* y = gradient_method2->calculate();

			std::cout << "Tolerance: " << tol << "\nOptimal point: ";
			x->print();
			std::cout << "\n";
			y->print();
			std::cout << "\n";
			std::cout << "Counter: " << n_dim_function->get_counter() << std::endl;
			std::cout << "Function value: " << n_dim_function->at(x) << std::endl;
			std::cout << "Counter: " << matrix->get_counter() + n_dim_function2->get_grad_counter() << std::endl;
			std::cout << "Function value: " << n_dim_function2->at(y) << std::endl;
			n_dim_function->update_counter();
			matrix->update_counter();
			std::cout << "\n\n\n";

			delete x;
			delete y;
		}

		delete gradient_method;
		delete n_dim_function;
		delete gradient_method2;
		delete n_dim_function2;

	}

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();

	return 0;
}
