#pragma once
#include<functional>
#include<vector>
#include<map>
#include "IVector.h"

class IVector;

class Matrix {
public:
	Matrix(std::vector<double>, size_t, size_t);
	Matrix(size_t size);
	Matrix(Matrix const& mat);

	double& at(size_t i, size_t j);
	double at(size_t i, size_t j) const;
	IVector* left_vector_multy(IVector const* vec) const;
	void set_identity_matrix();

	void sub_matrix(Matrix const& mat);
	void for_each(std::function<double(double)> const& func);

	IVector* LDL(IVector*);

	~Matrix();

private:
	size_t n, m;
	double** data;
	double* matrix;
};

class Hesse {
public:
	Hesse(std::vector<std::function<double(IVector const*)>>, size_t, size_t);
	Matrix* at(IVector*);
	size_t get_counter();
	void update_counter();
	~Hesse();
private:
	size_t n, m;
	size_t num_calls;
	std::map<std::pair<size_t, size_t>, std::function<double(IVector const*)>> data;
};
