#pragma once
#include<functional>
#include<vector>
#include<map>
#include "IVector.h"

class Matrix {
public:
	Matrix(std::vector<double>, int, int);
	IVector* LDL(IVector*);
	~Matrix();
private:
	int n, m;
	double** data;
};

class Hesse {
public:
	Hesse(std::vector<std::function<double(IVector const*)>>, int, int);
	Matrix* at(IVector*);
	size_t get_counter();
	void update_counter();
	~Hesse();
private:
	int n, m;
	int num_calls;
	std::map<std::pair<size_t, size_t>, std::function<double(IVector const*)>> data;
};