#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <cstddef>

class Matrix
{
public:
	Matrix();
	Matrix(const size_t rows, const size_t cols);
	Matrix(const Matrix &m);
	~Matrix();
	size_t	get_rsize() { return (rows); }
	size_t	get_csize() { return (cols); }
	void	create_matrix(const size_t rows, const size_t cols);
	double	*operator[](const size_t i) { return (matrix[i]); }
	Matrix	&operator=(const Matrix &m);
	Matrix	operator+(const Matrix& m);
	Matrix	operator-(const Matrix& m);
	Matrix	operator*(Matrix& m);
	Matrix	multiply(const double scalar);
	Matrix	transpose();
	Matrix	inverse();
	double	determinant();
	void	display();

private:
	size_t	rows;
	size_t	cols;
	double	**matrix;

	double	sum_product(const double* row, const double* col, const size_t size);
	int		triangular_view(Matrix& m);
	size_t	find_row(Matrix& matr, const size_t i);
	void	ft_swap(double* arg1, double* arg2, const size_t size);
	double	alg_complement(const size_t row, const size_t col);
};

#endif
