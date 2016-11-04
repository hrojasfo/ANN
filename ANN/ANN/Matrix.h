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
	Matrix(int m, int n, std::string type);
	~Matrix();
	void print();
	void setup_matrix(std::string type);
	T get(int i, int j);
};

template<class T>
Matrix<T>::Matrix(int m, int n)
{
	this->m = m;
	this->n = n;
	setup_matrix("rand");
}

template<class T>
inline Matrix<T>::Matrix(int m, int n, std::string type)
{
	this->m = m;
	this->n = n;
	setup_matrix(type);
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

template<class T>
void Matrix<T>::setup_matrix(std::string type)
{
	for (int i = 0; i < m; ++i) {
		std::vector<T> row;
		
		for (int j = 0; j < n; ++j) {
			T val;
			if (type == "ident") {
				val = (i == j) ? 1 : 0;
			}
			else if (type == "rand") {
				val = (T)rand() / RAND_MAX;
			}
			else if (type == "ones") {
				val = 1;
			} else if(type == "zeros") {
				val = 0;
			}
			row.push_back(val);
		}
		matrix.push_back(row);
	}
}

template<class T>
T Matrix<T>::get(int i, int j)
{
	return matrix[i][j];
}
