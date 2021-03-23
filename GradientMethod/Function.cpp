#include "IFunction.h"

namespace {
	class FunctionImpl : public IFunction {
	public:
		FunctionImpl(std::function<double(double)> const&);

		double at(double) override;
		size_t get_counter() const override;
		void update_counter() override;

		~FunctionImpl();
	private:
		std::function<double(double)> func;
		size_t counter = 0;
	};
}

IFunction* IFunction::create_function(std::function<double(double)> const& func) {
	return new FunctionImpl(func);
}

IFunction::~IFunction() {}

FunctionImpl::FunctionImpl(std::function<double(double)> const& func) : func{ func } {}

double FunctionImpl::at(double x) {
	++counter;
	return func(x);
}

size_t FunctionImpl::get_counter() const {
	return counter;
}

void FunctionImpl::update_counter() {
	counter = 0;
	return;
}

FunctionImpl::~FunctionImpl() {}
