#pragma once
#include <vector>
#include <iostream>
#include <cmath>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#define FIX 0.001

template <class T>
class Matrix
{
	T *matrix = nullptr;
	int rows = 0; // rows
	int cols = 0; // cols
	bool transpose = false;
public:
	Matrix();
	Matrix(int m, int n);
	Matrix(int m, int n, T val);
	Matrix(int m, int n, std::string type);
	Matrix(std::vector<T> vec);
	Matrix(const Matrix<T>& other);
	Matrix(Matrix<T>&& other);
	~Matrix();

	int get_row();
	int get_col();
	T& get(int i, int j);
	Matrix& transpose_matrix();

	void print();
	void setup_matrix(std::string type);

	Matrix<T> operator*(Matrix<T> &b);
	Matrix<T> operator+(Matrix<T> &b);
	Matrix<T> & operator=(const Matrix<T> & other);
//	Matrix<T> & operator=(Matrix<T>&& other);
	Matrix<T> delta();
	Matrix<T> delta_out(Matrix<T> &b);
	void add(Matrix<T> &b);
	void scalar_mult(T num);
	Matrix<T> one_to_one_mult(Matrix<T> &b);
	void sigmoid();
	void sigmoid(T scalar);
};

template<class T>
Matrix<T>::Matrix()
{
}

template<class T>
Matrix<T>::Matrix(int m, int n)
	: rows(m), cols(n)
{
	matrix = new T[rows*cols];
}

template<class T>
Matrix<T>::Matrix(int m, int n, T val)
	: rows(m), cols(n)
{
	matrix = new T[rows*cols];
	//matrix = new T*[rows];
	for (int i = 0; i < rows * cols; ++i) {
		matrix[i] = val;
	}
}

template<class T>
Matrix<T>::Matrix(int m, int n, std::string type)
	: rows(m), cols(n)
{
	setup_matrix(type);
}

template<class T>
Matrix<T>::Matrix(std::vector<T> vec)
{
	rows = 1;
	cols = vec.size();
	matrix = new T[cols];
	for (int i = 0; i < cols; ++i) matrix[i] = vec[i];
	
}

template<class T>
Matrix<T>::Matrix(const Matrix<T> &other)
{
	rows = other.rows;
	cols = other.cols;
	transpose = other.transpose;
	matrix = new T[rows*cols];
	std::copy(other.matrix, other.matrix + (rows*cols), matrix);
}

template<class t>
Matrix<t>::Matrix(Matrix<t> &&other)
{
	rows = other.rows;
	cols = other.cols;
	transpose = other.transpose;
	matrix = other.matrix;

	other.rows = 0;
	other.cols = 0;
	other.transpose = false;
	other.matrix = nullptr;
}

template<class T>
Matrix<T>::~Matrix()
{

	if (matrix != NULL) delete[] matrix;

}

template<class T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & other) {
	if (this != &other) {
		T * new_matrix = new T[other.rows*other.cols];
		std::copy(other.matrix, other.matrix + (other.rows*other.cols), new_matrix);
		rows = other.rows;
		cols = other.cols;
		delete[] matrix;
		transpose = other.transpose;
		matrix = new_matrix;

	}
	return *this;
}

//template<class T>
//Matrix<T> & Matrix<T>::operator=(Matrix<T> && other) {
//	delete[] matrix;
//	rows = other.rows;
//	cols = other.cols;
//	transpose = other.transpose;
//	matrix = other.matrix;
//
//	other.rows = 0;
//	other.cols = 0;
//	other.transpose = false;
//	other.matrix = nullptr;
//	return *this;
//}

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
T& Matrix<T>::get(int i, int j)
{
	int row_size = get_row();
	int col_size = get_col();
	int row = i;
	int col = j;
	if (transpose) {
		row = j;
		col = i;
	}
	if (i >= row_size) throw "Row out of limits";
	if (j >= col_size) throw "Column out of limits";
	return matrix[row*col_size + col];
}

template<class T>
Matrix<T>& Matrix<T>::transpose_matrix()
{
	transpose = !transpose;
	return *this;
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
	matrix = new T[rows*cols];
	for (int i = 0; i < rows; ++i) {
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
			matrix[i*cols + j] = val;
		}
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
	Matrix<T> result(row,col);
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			result.get(i, j) = 0;
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
	Matrix<T> result(row, col);
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

	Matrix<T> result(row, col);
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
void Matrix<T>::add(Matrix<T>& b)
{
	int row = this->get_row();
	int col = this->get_col();
	if (this->get_col() != b.get_col() || this->get_row() != b.get_row()) {
		throw "The Matrix dimensions are not the same";
	}
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			this->get(i, j) = this->get(i, j) + b.get(i, j);
		}
	}
}


