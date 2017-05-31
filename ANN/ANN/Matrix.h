#pragma once
#include <vector>
#include <iostream>
#include <cmath>

#define FIX 1

template <class T>
class Matrix
{
	std::vector< std::vector<T> > matrix;
	int rows; // rows
	int cols; // cols
	bool transpose = false;
public:
	Matrix(int m, int n);
	Matrix(int m, int n, T val);
	Matrix(int m, int n, std::string type);
	Matrix(std::vector<T> vec);
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
	void push(T num);
	void pop();
	Matrix<T> one_to_one_mult(Matrix<T> &b);
	void sigmoid();
	void sigmoid(T scalar);
	int get_row();
	int get_col();
	Matrix& transpose_matrix();

};

template<class T>
Matrix<T>::Matrix(int m, int n)
{
	this->rows = m;
	this->cols = n;
	
	setup_matrix("rand");
}

template<class T>
Matrix<T>::Matrix(int m, int n, T val)
{
	this->rows = m;
	this->cols = n;
	for (int i = 0; i < m; ++i) {
		std::vector<T> row;
		for (int j = 0; j < n; ++j) {
			row.push_back(val);
		}
		matrix.push_back(row);
	}
}

template<class T>
Matrix<T>::Matrix(int m, int n, std::string type)
{
	this->rows = m;
	this->cols = n;
	setup_matrix(type);
}

template<class T>
Matrix<T>::Matrix(std::vector<T> vec)
{
	matrix.push_back(vec);
	rows = 1;
	cols = vec.size();
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
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			std::cout << this->get(i, j) << " ";
		}
		std::cout << '\n';
	}
}

template<class T>
void Matrix<T>::setup_matrix(std::string type)
{
	for (int i = 0; i < rows; ++i) {
		std::vector<T> row;
		
		for (int j = 0; j < cols; ++j) {
			T val;
			if (type == "ident") {
				val = (i == j) ? 1.0 : 0.0;
			}
			else if (type == "rand") {
				val = FIX * (T)rand() / RAND_MAX;
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
		if (i >= cols) {
			throw "Row out of limits";
		}
		if (j >= rows) {
			throw "Column out of limits";
		}
		return matrix[j][i];
	} else {
		if (i >= rows) {
			throw "Row out of limits";
		}
		if (j >= cols) {
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
void Matrix<T>::push(T num)
{
	int row = this->get_row();
	int col = this->get_col();
	if (row != 1 && col != 1) {
		throw "At leat one dimention should be one to do a push";
	}
	if (matrix.size() == 1) {
		matrix.at(0).push_back(num);
		++cols;
	}
	else {
		std::vector<T> pushed;
		pushed.push_back(num);
		matrix.push_back(pushed);
		++rows;
	}
}

template<class T>
void Matrix<T>::pop()
{
	if (matrix.size() == 1) {
		if (matrix.at(0).size() > 0) {
			matrix.at(0).pop_back();
			--cols;
		}
	}
	else {
		if (matrix.size() > 0) {
			matrix.pop_back();
			--rows;
		}
	}
}

template<class T>
Matrix<T> Matrix<T>::one_to_one_mult(Matrix<T>& b)
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
void Matrix<T>::sigmoid(T scalar)
{
	for (int i = 0; i < this->get_row(); ++i) {
		for (int j = 0; j < this->get_col(); ++j) {
			this->get(i, j) = scalar / (1 + exp(-this->get(i, j)));
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
	return (transpose) ? cols : rows;
}

template<class T>
int Matrix<T>::get_col()
{
	return (transpose) ? rows : cols;
}

template<class T>
Matrix<T>& Matrix<T>::transpose_matrix()
{
	transpose = !transpose;
	return *this;
}
