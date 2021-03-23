#pragma once
#include"IMethod.h"

class DichotomyMethod : public IMethod {
public:
	DichotomyMethod(IFunction* const, double, std::pair<double, double> const&);

	void set_tolerance(double) override;
	void set_section(std::pair<double, double> const&) override;

	double calculate() override;

	~DichotomyMethod();

private:
	double tolerance;
	std::pair<double, double> section;
	IFunction* const function;
};
