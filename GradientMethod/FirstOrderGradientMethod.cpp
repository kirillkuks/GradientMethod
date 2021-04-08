#include "FirstOrderGradientMethod.h"

#include "IMethod.h"
#include <iostream>

using xn_t = std::vector<double>;

FirstOrderGradientMethod::FirstOrderGradientMethod(size_t dim, INDimFunction* const func, double tol)
	: dim{ dim }, func{ func }, tol{ tol } {}

void FirstOrderGradientMethod::set_tolerance(double tol_) {
	tol = tol_;
}

IVector* FirstOrderGradientMethod::calculate(double a) const {
	auto optimal = IVector::create_vector({0, 0});

	if (!(0 < a && a < 1)) {
		a = 0.5;
	}

	std::vector<IVector*> seq;
	auto grad_value = func->gradient_at(optimal);

	IMethod* fibonacci_method = IMethod::create_method(IMethod::METHOD::FIBONACCI, nullptr, tol, { 0, 1 });

	while (grad_value->norm() >= tol) {
		optimal->print();
		std::cout << std::endl;
		IFunction* function = IFunction::create_function([&](double ak) -> double {
			auto v = grad_value->scale(-ak);
			auto vk = IVector::add(optimal, v);

			auto res = func->at(vk);

			delete v;
			delete vk;

			return res;
		});

		fibonacci_method->set_function(function);
		auto ak = fibonacci_method->calculate();
		//std::cout << "ak --- " << ak << std::endl;

		auto tmp = grad_value->scale(-ak);
		auto t = IVector::add(optimal, tmp);

		seq.push_back(tmp);

		delete optimal;

		optimal = t;

		delete grad_value;
		grad_value = func->gradient_at(optimal);

		delete function;
	}

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