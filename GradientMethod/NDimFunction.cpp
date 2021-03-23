#include "INDimFunction.h"

namespace {
	class NDimFunction : public INDimFunction {
	public:
		NDimFunction(std::function<double(xn_t)> const& func, std::function<xn_t(xn_t)> const& grad);

		double at(xn_t const& x) const override;
		size_t get_counter() const override;
		void update_counter() override;

		~NDimFunction() {}

	private:
		std::function<double(xn_t)> func;
		std::function<xn_t(xn_t)> grad;
		size_t counter = 0;
	};
}

INDimFunction* INDimFunction::create_function(std::function<double(xn_t)> const& func, std::function<xn_t(xn_t)> const& grad) {
	return new NDimFunction(func, grad);
}

NDimFunction::NDimFunction(std::function<double(xn_t)> const& func, std::function<xn_t(xn_t)> const& grad) : func{ func }, grad{ grad } {}

double NDimFunction::at(xn_t const& x) const {
	return func(x);
}

size_t NDimFunction::get_counter() const {
	return counter;
}

void NDimFunction::update_counter() {
	counter = 0;
}
