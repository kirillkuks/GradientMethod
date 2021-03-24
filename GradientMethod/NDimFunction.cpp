#include "INDimFunction.h"

namespace {
	class NDimFunction : public INDimFunction {
	public:
		NDimFunction(std::function<double(IVector const*)> const& func, std::function<IVector*(IVector const*)> const& grad);

		double at(IVector const* x) override;
		IVector* gradient_at(IVector const* x) override;
		size_t get_counter() const override;
		void update_counter() override;

		~NDimFunction() {}

	private:
		std::function<double(IVector const*)> func;
		std::function<IVector*(IVector const*)> grad;
		size_t counter = 0;
	};
}

INDimFunction* INDimFunction::create_function(std::function<double(IVector const*)> const& func, std::function<IVector*(IVector const*)> const& grad) {
	return new NDimFunction(func, grad);
}

NDimFunction::NDimFunction(std::function<double(IVector const*)> const& func, std::function<IVector*(IVector const*)> const& grad) : func{ func }, grad{ grad } {}

double NDimFunction::at(IVector const* x) {
	++counter;
	return func(x);
}

IVector* NDimFunction::gradient_at(IVector const* x) {
	return grad(x);
}

size_t NDimFunction::get_counter() const {
	return counter;
}

void NDimFunction::update_counter() {
	counter = 0;
}
