#pragma once
#include <vector>
#include <functional>
#include "Matrix.h"
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

class Matrix;

class IVector {
protected:
	using xn_t = std::vector<double>;

public:
	static IVector* create_vector(xn_t const& x);
	static IVector* create_vector(size_t size);

	static IVector* add(IVector const* op1, IVector const* op2);
	static IVector* sub(IVector const* op1, IVector const* op2);
	static double dot(IVector const* op1, IVector const* op2);
	static Matrix multy(IVector const* op1, IVector const* op2);

	virtual IVector* scale(double a) const = 0;
	virtual double norm() const = 0;
	virtual double& at(size_t index) = 0;
	virtual double at(size_t index) const = 0;
	virtual size_t size() const = 0;
	virtual void for_each(std::function<double(double)> const& func) = 0;

	virtual void print() const = 0;

	virtual ~IVector() = 0 {}

private:
	IVector(IVector const&) = delete;
	IVector& operator=(IVector const&) = delete;

protected:
	IVector() = default;

};