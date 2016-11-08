#pragma once
#include <vector>
#include <iostream>
#include <cmath>

template <class T>
class Matrix
{
	std::vector< std::vector<T> > matrix;
	int m;
	int n;
	bool transpose = false;
public:
	Matrix(int m, int n);
	Matrix(int m, int n, std::string type);
	Matrix();
	~Matrix();
	void print();
	void setup_matrix(std::string type);
	T& get(int i, int j);
	Matrix<T> operator*(Matrix<T> &b);
	Matrix<T> operator+(Matrix<T> &b);
	Matrix<T> delta();
	Matrix<T> delta_out(Matrix<T> &b);
	void scalar_mult(T num);
	Matrix<T> one_to_one_mult(Matrix<T> &b);
	void sigmoid();
	int get_row();
	int get_col();
	Matrix& transpose_matrix();

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
			std::cout << this->get(i, j) << " ";
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
	if (transpose) {
		if (i >= n) {
			throw "Row out of limits";
		}
		if (j >= m) {
			throw "Column out of limits";
		}
		return matrix[j][i];
	} else {
		if (i >= m) {
			throw "Row out of limits";
		}
		if (j >= n) {
			throw "Column out of limits";
		}
		return matrix[i][j];
	}
}

template<class T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& b)
{
	int row = this->get_row();
	int col = b.get_col();
	if (this->get_col() != b.get_row()) {
		throw "Column of first operand must be equal to second's row";
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
Matrix<T> Matrix<T>::operator+(Matrix<T>& b)
{
	int row = this->get_row();
	int col = this->get_col();
	if (this->get_col() != b.get_col() || this->get_row() != b.get_row()) {
		throw "The Matrix dimensions are not the same";
	}
	Matrix<T> result(row, col, "zeros");
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			result.get(i, j) = this->get(i, j) + b.get(i, j);
		}
	}
	return result;
}

template<class T>
Matrix<T> Matrix<T>::delta()
{
	int row = this->get_row();
	int col = this->get_col();

	Matrix<T> result(row, col, "zeros");
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			T data = this->get(i, j);
			result.get(i, j) = data * (1 - data);
		}
	}
	return result;
}

template<class T>
void Matrix<T>::scalar_mult(T num)
{
	int row = this->get_row();
	int col = this->get_col();

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			this->get(i, j) = num * this->get(i, j);
		}
	}
	return;
}

template<class T>
inline Matrix<T> Matrix<T>::one_to_one_mult(Matrix<T>& b)
{
	int row = this->get_row();
	int col = this->get_col();
	if (this->get_col() != b.get_col() || this->get_row() != b.get_row()) {
		throw "The Matrix dimensions are not the same";
	}
	Matrix<T> result(row, col, "zeros");
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			result.get(i, j) = this->get(i, j) * b.get(i, j);
		}
	}
	return result;

}

template<class T>
void Matrix<T>::sigmoid()
{
	for (int i = 0; i < this->get_row(); ++i) {
		for (int j = 0; j < this->get_col(); ++j) {
			this->get(i, j) = 1 / (1 + exp(-this->get(i, j)));
		}
	}
}

template<class T>
Matrix<T> Matrix<T>::delta_out(Matrix<T>& b)
{
	int row = this->get_row();
	int col = this->get_col();
	if (this->get_col() != b.get_col() || this->get_row() != b.get_row()) {
		throw "The Matrix dimensions are not the same";
	}
	Matrix<T> result(row, col, "zeros");
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			T data = this->get(i, j);
			result.get(i, j) = data * (1 - data) * (data - b.get(i, j));
		}
	}
	return result;
}

template<class T>
int Matrix<T>::get_row()
{
	return (transpose) ? n : m;
}

template<class T>
int Matrix<T>::get_col()
{
	return (transpose) ? m : n;
}

template<class T>
Matrix<T>& Matrix<T>::transpose_matrix()
{
	transpose = !transpose;
	return *this;
}
