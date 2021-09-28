#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <exception>

class Matrix
{
	public:
		class OutOfRangeException;
		class MatrixDimensionException;

		Matrix();
		Matrix(const size_t rows, const size_t cols, double initValue = 0.0);
		Matrix(const Matrix &m);
		~Matrix();
	
		double& operator()(const size_t i, const size_t j);
		const double& operator()(const size_t i, const size_t j) const;
		Matrix &operator=(const Matrix &m);
		Matrix& operator+=(const Matrix& m);
		Matrix operator+(const Matrix& m) const;
		Matrix& operator-=(const Matrix& m);
		Matrix operator-(const Matrix& m) const;
		Matrix& operator*=(const Matrix& m);
		Matrix& operator*=(const double value);
		Matrix operator*(const Matrix& m);

		void create_matrix(const size_t rows, const size_t cols);
		Matrix ones(const size_t rows, const size_t cols);
		Matrix transpose() const;
		Matrix inverse();
		size_t get_rsize() { return (rows); }
		size_t get_csize() { return (cols); }
		double determinant();
		void display() const;

	private:
		size_t rows;
		size_t cols;
		double** matrix;

		double sum_product(const double* row, const double* col, const size_t size);
		size_t find_row(Matrix& matr, const size_t i);
		void ft_swap(double* arg1, double* arg2, const size_t size);
		int triangular_view(Matrix& m);
		double alg_complement(const size_t row, const size_t col);
};

Matrix operator*(const Matrix& m, const double value);
Matrix operator*(const double value, const Matrix& m);

#endif
