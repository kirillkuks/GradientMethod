#include "DFPGradientMethod.h"
#include "Matrix.h"
#include "IMethod.h"
#include <iostream>

DFPGradientMethod::DFPGradientMethod(size_t dim, INDimFunction* const func, double tol)
	: dim{ dim }, func{ func }, tol{ tol } {}

void DFPGradientMethod::set_tolerance(double tol_) {
	tol = tol_;
}

IVector* DFPGradientMethod::calculate(double a) const {
	auto optimal = IVector::create_vector({1, 1});

	if (!(0 < a && a < 1)) {
		a = 0.5;
	}

	Matrix A(dim);
	A.set_identity_matrix();
	auto grad_value = func->gradient_at(optimal);
	grad_value->for_each([](double x) { return -x; });

	auto fibonacci_method = IMethod::create_method(IMethod::METHOD::FIBONACCI, nullptr, tol, { 0, 1 });
	size_t iter_counter = 1;
	std::vector<IVector*> seq;

	while (grad_value->norm() >= tol) {
		optimal->print();
		std::cout << std::endl;
		auto pk = A.left_vector_multy(grad_value);

		auto function = IFunction::create_function([&](double ak) -> double {
			auto apk = pk->scale(ak);
			auto xk = IVector::add(optimal, apk);

			double res = func->at(xk);

			delete apk;
			delete xk;

			return res;
		});

		fibonacci_method->set_function(function);
		auto ak = fibonacci_method->calculate();
		//std::cout << "ak --- " << ak << std::endl;

		auto apk = pk->scale(ak);
		auto tmp = IVector::add(optimal, apk);
		seq.push_back(apk);
		std::swap(tmp, optimal);
		delete tmp;

		auto w = func->gradient_at(optimal);
		w->for_each([](double x) { return -x; });

		if (iter_counter % dim) {
			auto dw = IVector::sub(w, grad_value);

			next_matrix_approximation(A, apk, dw);
			++iter_counter;

			delete dw;
		}
		else {
			A.set_identity_matrix();
			iter_counter = 1;
		}


		std::swap(w, grad_value);
		delete w;

		delete function;
		delete pk;
	}

	optimal->print();
	std::cout << std::endl;

	for (size_t i = 1; i < seq.size(); ++i) {
		std::cout << "Norm: " << IVector::dot(seq[i], seq[i - 1]) << std::endl;
	}

	for (size_t i = 0; i < seq.size(); ++i) {
		delete seq[i];
	}

	delete grad_value;
	delete fibonacci_method;

	return optimal;
}

void DFPGradientMethod::next_matrix_approximation(Matrix& A, IVector const* delta_x, IVector const* delta_w) const {
	auto op1 = IVector::multy(delta_x, delta_x);
	auto vec = A.left_vector_multy(delta_w);
	auto op2 = IVector::multy(vec, vec);

	double n = IVector::dot(delta_w, delta_x);
	op1.for_each([&](double x) -> double { return x / n; });
	n = IVector::dot(delta_w, vec);
	op2.for_each([&](double x) -> double { return x / n; });

	A.sub_matrix(op1);
	A.sub_matrix(op2);

	delete vec;
}
