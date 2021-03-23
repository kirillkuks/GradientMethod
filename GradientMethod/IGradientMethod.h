#pragma once
#include "INDimFunction.h"

class IGradientMethod {
protected:
	using xn_t = std::vector<double>;

public:
	enum class ORDER {
		FIRST,
		SECOND
	};

	static IGradientMethod* create_grad_method(ORDER order, size_t dim, INDimFunction const* func, double tol);

	virtual void set_tolerance(double tol) = 0;
	virtual xn_t calculate() const = 0;
	
	virtual ~IGradientMethod() = 0 {}

private:
	IGradientMethod(IGradientMethod const&) = delete;
	IGradientMethod& operator=(IGradientMethod const&) = delete;

protected:
	IGradientMethod() = default;

};
