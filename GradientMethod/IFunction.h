#pragma once
#include <functional>

class IFunction {
public:
	static IFunction* create_function(std::function<double(double)> const&);

	virtual double at(double) = 0;
	virtual size_t get_counter() const = 0;
	virtual void update_counter() = 0;

	virtual ~IFunction() = 0;

private:
	IFunction(IFunction const&) = delete;
	IFunction& operator=(IFunction const&) = delete;
protected:
	IFunction() = default;
};
