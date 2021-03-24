#pragma once
#include"IMethod.h"

class FibonacciMethod : public IMethod {
public:
	FibonacciMethod(IFunction* const, double, std::pair<double, double> const&);

	void set_tolerance(double) override;
	void set_section(std::pair<double, double> const&) override;
	void set_function(IFunction* const) override;

	double calculate() override;

	~FibonacciMethod();
private:
	IFunction* function;
	std::pair<double, double> section;
	double tol;
};
