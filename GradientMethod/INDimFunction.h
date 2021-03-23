#pragma once
#include <functional>
#include <vector>

class INDimFunction {
protected:
	using xn_t = std::vector<double>;

public:
	static INDimFunction* create_function(std::function<double(xn_t)> const& func, std::function<xn_t(xn_t)> const& grad);

	virtual double at(xn_t const& x) const = 0;
	virtual size_t get_counter() const = 0;
	virtual void update_counter() = 0;

	virtual ~INDimFunction() = 0 {}

private:
	INDimFunction(INDimFunction const&) = delete;
	INDimFunction& operator=(INDimFunction const&) = delete;

protected:
	INDimFunction() = default;

};
