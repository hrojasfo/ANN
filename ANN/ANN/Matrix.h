#pragma once
#include <vector>
#include <iostream>

template <class T>
class Matrix
{
	std::vector< std::vector<T> > matrix;
	int m;
	int n;
public:
	Matrix(int m, int n);
	~Matrix();
	void print();

};

template<class T>
Matrix<T>::Matrix(int m, int n)
{
	this->m = m;
	this->n = n;
	for (int i = 0; i < m; ++i) {
		std::vector<T> row;
		for (int j = 0; j < n; ++j) {
			row.push_back((T)rand() / RAND_MAX);
		}
		matrix.push_back(row);
	}
}

template<class T>
Matrix<T>::~Matrix()
{
}

template<class T>
void Matrix<T>::print()
{
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << '\n';
	}
}
