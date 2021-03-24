#include "IVector.h"

#include <cassert>
#include <iostream>

namespace {
	class VectorImpl : public IVector {
	public:
		VectorImpl(xn_t const& x);

		IVector* scale(double a) const override;
		double norm() const override;
		double& at(size_t index) override;
		double at(size_t index) const override;
		size_t size() const override;

		void print() const override;

		~VectorImpl() {}

	private:
		xn_t vec;
	};
}

IVector* IVector::create_vector(xn_t const& x) {
	return new VectorImpl(x);
}

IVector* IVector::create_vector(size_t size) {
	return new VectorImpl(xn_t(size));
}

IVector* IVector::add(IVector const* op1, IVector const* op2) {
	auto size = op1->size();
	assert(size == op2->size());

	xn_t v(size);
	for (size_t i = 0; i < size; ++i) {
		v[i] = op1->at(i) + op2->at(i);
	}
	return IVector::create_vector(v);
}

VectorImpl::VectorImpl(xn_t const& x) : vec{ x } {}

IVector* VectorImpl::scale(double a) const {
	xn_t v(vec);
	for (auto& elem : v) {
		elem *= a;
	}
	return IVector::create_vector(v);
}

double VectorImpl::norm() const {
	auto n = 0.0;
	for (auto elem : vec) {
		n += elem * elem;
	}
	return sqrt(n);
}

double& VectorImpl::at(size_t index) {
	assert(index < vec.size());
	return vec[index];
}

double VectorImpl::at(size_t index) const {
	assert(index < vec.size());
	return vec[index];
}

size_t VectorImpl::size() const {
	return vec.size();
}

void VectorImpl::print() const {
	std::cout << "<";
	for (auto elem : vec) {
		std::cout << elem << "; ";
	}
	std::cout << "\b\b" << ">";
}
