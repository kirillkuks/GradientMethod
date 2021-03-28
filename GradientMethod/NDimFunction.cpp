#include "INDimFunction.h"

namespace {
	class NDimFunction : public INDimFunction {
	public:
		NDimFunction(std::function<double(IVector const*)> const& func, std::function<IVector*(IVector const*)> const& grad, Hesse* hesse);

		double at(IVector const* x) override;
		IVector* gradient_at(IVector const* x) override;
		size_t get_counter() const override;
		size_t get_grad_counter() const override;
		void update_counter() override;
		Matrix* get_hesse(IVector* point);

		~NDimFunction();

	private:
		std::function<double(IVector const*)> func;
		std::function<IVector*(IVector const*)> grad;
		size_t counter = 0;
		size_t grad_counter = 0;
		Hesse* hesse;
	};
}

INDimFunction* INDimFunction::create_function(std::function<double(IVector const*)> const& func, std::function<IVector*(IVector const*)> const& grad, Hesse* hesse) {
	return new NDimFunction(func, grad, hesse);
}

NDimFunction::NDimFunction(std::function<double(IVector const*)> const& func, std::function<IVector* (IVector const*)> const& grad, Hesse* hesse) : func{ func }, grad{ grad }, hesse{ hesse } {}

double NDimFunction::at(IVector const* x) {
	++counter;
	return func(x);
}

IVector* NDimFunction::gradient_at(IVector const* x) {
	grad_counter++;
	return grad(x);
}

size_t NDimFunction::get_counter() const {
	return counter;
}

size_t NDimFunction::get_grad_counter() const {
	return grad_counter;
}

void NDimFunction::update_counter() {
	counter = 0;
	grad_counter = 0;
}

Matrix* NDimFunction::get_hesse(IVector* point) {
	return hesse->at(point);
}

NDimFunction::~NDimFunction() {
	delete hesse;
}