#pragma once
#include <functional>
#include <vector>
#include "IVector.h"
#include "Matrix.h"

class INDimFunction {
protected:
	using xn_t = std::vector<double>;

public:
	static INDimFunction* create_function(std::function<double(IVector const*)> const& func, std::function<IVector* (IVector const*)> const& grad, Hesse* hesse);


	virtual double at(IVector const* x) = 0;
	virtual IVector* gradient_at(IVector const* x) = 0;
	virtual size_t get_counter() const = 0;
	virtual size_t get_grad_counter() const = 0;
	virtual void update_counter() = 0;
	virtual Matrix* get_hesse(IVector*) = 0;

	virtual ~INDimFunction() = 0 {}

private:
	INDimFunction(INDimFunction const&) = delete;
	INDimFunction& operator=(INDimFunction const&) = delete;

protected:
	INDimFunction() = default;

};
