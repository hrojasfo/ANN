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
	Matrix();
	~Matrix();
	void print();
	void setup_matrix(std::string type);
	T& get(int i, int j);
	Matrix<T> operator*(Matrix<T> &b);
	int get_row();
	int get_col();

};

template<class T>
Matrix<T>::Matrix(int m, int n)
{
	this->m = m;
	this->n = n;
	setup_matrix("rand");
}

template<class T>
Matrix<T>::Matrix(int m, int n, std::string type)
{
	this->m = m;
	this->n = n;
	setup_matrix(type);
}

template<class T>
Matrix<T>::Matrix()
{
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
T& Matrix<T>::get(int i, int j)
{
	if (i >= m) {
		throw "Row out of limits";
	}
	if (j >= n) {
		throw "Column out of limits";
	}
	return matrix[i][j];
}

template<class T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& b)
{
	int row = this->get_row();
	int col = b.get_col();
	if (this->get_col() != b.get_row()) {
		throw "Column of firs operand must be equal to second's row";
	}
	Matrix<T> result(row,col,"zeros");
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			for (int k = 0; k < this->get_col(); ++ k) {
				result.get(i, j) += this->get(i, k) * b.get(k, j);
			}
		}
	}
	return result;
}

template<class T>
int Matrix<T>::get_row()
{
	return m;
}

template<class T>
int Matrix<T>::get_col()
{
	return n;
}
