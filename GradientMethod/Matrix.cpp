#include"Matrix.h"

Hesse::Hesse(std::vector<std::function<double(IVector const*)>> d, int n, int m): n(n), m(m){
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			data[{i, j}] = d[i * m + j];
		}
	}
}

Matrix* Hesse::at(IVector* point) {
	std::vector<double> vector = std::vector<double>(n * m);
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			vector[i * m + j] = data[{i, j}](point);
		}
	}
	return new Matrix(vector, n, m);
}

Matrix::Matrix(std::vector<double> d, int n, int m) : n(n), m(m) {
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < m; j++) {
			data[{i, j}] = d[i * m + j];
		}
	}
}

IVector* Matrix::LDL(IVector* point) {
	std::vector<double> D = std::vector<double>(n);
	std::map<std::pair<size_t, size_t>, double> L;
	for (size_t i = 0; i < n - 1; i++) {
		D[i] = data[{i, i}];
		for (size_t j = 0; j < i; j++) {
			D[i] -= D[j] * L[{i, j}] * L[{i, j}];
		}
		L[{i + 1, i}] = data[{ i + 1, i }];
		for (size_t j = 0; j < i; j++) {
			L[{i + 1, i}] -= D[j] * L[{i, j}] * L[{i + 1, j}];
		}
		L[{i + 1, i}] /= D[i];
	}
	D[n - 1] = data[{n - 1, n - 1}];
	for (size_t j = 0; j < n - 1; j++) {
		D[n - 1] -= D[j] * L[{n - 1, j}] * L[{n - 1, j}];
	}
	std::vector<double> C = std::vector<double>(n);
	for (size_t i = 0; i < n; i++) {
		C[i] = -point->at(i);
		for (size_t j = 0; j < i; j++) {
			C[i] -= L[{i, j}] * C[j];
		}
	}
	for (size_t i = 0; i < n; i++) {
		C[i] /= D[i];
	}
	D.clear();
	std::vector<double> result = std::vector<double>(n);
	for (int i = n - 1; i >= 0; i--) {
		result[i] = C[i];
		for (size_t j = i + 1; j < n; j++) {
			result[i] -= L[{j, i}] * result[j];
		}
	}
	L.clear();
	return IVector::create_vector(result);
}

Matrix::~Matrix() {
	data.clear();
	n = 0;
	m = 0;
}