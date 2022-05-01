#include "Matrix.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>

class Matrix::OutOfRangeException : public std::exception
{
	public:
		const char* what() const noexcept override
		{
			return ("index out of range");
		}
};

class Matrix::MatrixDimensionException : public std::exception
{
	public:
		MatrixDimensionException() : msg("matrix dimensions must agree")
		{ }

		MatrixDimensionException(const std::string& msg) : msg(msg)
		{ }

		const char* what() const noexcept override
		{
			return (msg.c_str());
		}

	private:
		const std::string msg;
};

Matrix::Matrix() : rows(0), cols(0), matrix(nullptr)
{ }

Matrix::Matrix(const size_t rows, const size_t cols, double initValue) : rows(rows), cols(cols)
{
	if (rows == 0 || cols == 0)
		throw MatrixDimensionException("the dimension of the matrix cannot be zero");

	matrix = new double*[rows];
	for (size_t i = 0; i < rows; i++)
	{
		matrix[i] = new double[cols];
		std::fill_n(matrix[i], cols, initValue);
	}
}

Matrix::Matrix(const Matrix& m) : rows(m.rows), cols(m.cols)
{
	if (!m.matrix)
	{
		matrix = nullptr;
		return ;
	}
	matrix = new double*[rows];
	for (size_t i = 0; i < rows; i++)
	{
		matrix[i] = new double[cols];
		for (size_t j = 0; j < cols; j++)
			matrix[i][j] = m.matrix[i][j];
	}
}

Matrix::~Matrix()
{
	for (size_t i = 0; i < rows; i++)
		delete[] matrix[i];
	delete[] matrix;
}

double& Matrix::operator()(const size_t i, const size_t j) 
{
	if (i >= rows || j >= cols)
		throw OutOfRangeException();
	return (matrix[i][j]);
}

const double& Matrix::operator()(const size_t i, const size_t j) const
{
	if (i >= rows || j >= cols)
		throw OutOfRangeException();
	return (matrix[i][j]);
}

Matrix&	Matrix::operator=(const Matrix& m)
{
	if (this == &m)
		return (*this);
	for (size_t i = 0; i < rows; i++)
		delete[] matrix[i];
	delete[] matrix;
	rows = m.rows;
	cols = m.cols;
	if (m.matrix)
	{
		matrix = new double*[rows];
		for (size_t i = 0; i < rows; i++)
		{
			matrix[i] = new double[cols];
			for (size_t j = 0; j < cols; j++)
				matrix[i][j] = m.matrix[i][j];
		}
	}
	else
		matrix = nullptr;
	return (*this);
}

Matrix& Matrix::operator+=(const Matrix& m) 
{
	if (rows != m.rows || cols != m.cols)
		throw MatrixDimensionException();

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
			matrix[i][j] = matrix[i][j] + m.matrix[i][j];
	}
	return (*this);
}

Matrix	Matrix::operator+(const Matrix& m) const
{
	Matrix	res_matrix(*this);

	if (rows != m.rows || cols != m.cols)
		throw MatrixDimensionException();

	res_matrix += m;
	return (res_matrix);
}

Matrix& Matrix::operator-=(const Matrix& m) 
{
	if (rows != m.rows || cols != m.cols)
		throw MatrixDimensionException();

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
			matrix[i][j] = matrix[i][j] - m.matrix[i][j];
	}
	return (*this);
}

Matrix	Matrix::operator-(const Matrix& m) const
{
	Matrix	res_matrix(*this);

	if (rows != m.rows || cols != m.cols)
		throw MatrixDimensionException();

	res_matrix -= m;
	return (res_matrix);
}

Matrix& Matrix::operator*=(const Matrix& m) 
{
	Matrix	res_matrix(rows, m.cols);
	Matrix	m_transpose;

	if (cols != m.rows)
		throw MatrixDimensionException();
	
	m_transpose = m.transpose();
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < m.cols; j++)
			res_matrix(i, j) = sum_product(matrix[i], m_transpose.matrix[j], cols);
	}
	*this = res_matrix;
	return (*this);
}

Matrix& Matrix::operator*=(const double value)
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
			matrix[i][j] *= value;
	}
	return (*this);
}

Matrix	Matrix::operator*(const Matrix& m)
{
	Matrix	res_matrix(rows, m.cols);
	Matrix	m_transpose;

	if (cols != m.rows)
		throw MatrixDimensionException();

	m_transpose = m.transpose();
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < m.cols; j++)
			res_matrix(i, j) = sum_product(matrix[i], m_transpose.matrix[j], cols);
	}
	return (res_matrix);
}

void	Matrix::create_matrix(const size_t rows, const size_t cols)
{
	this->rows = rows;
	this->cols = cols;
	matrix = new double* [rows];
	for (size_t i = 0; i < rows; i++)
		matrix[i] = new double[cols] {0.0};
}

Matrix	Matrix::ones(const size_t rows, const size_t cols)
{
	create_matrix(rows, cols);
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
			matrix[i][j] = 1;
	}
	return (*this);
}

Matrix	Matrix::transpose() const
{
	Matrix	res_matrix(cols, rows);

	for (size_t i = 0; i < cols; i++)
	{
		for (size_t j = 0; j < rows; j++)
			res_matrix.matrix[i][j] = matrix[j][i];
	}
	return (res_matrix);
}

Matrix	Matrix::inverse()
{
	Matrix	alg_comp(rows, cols);

	if (rows == 1 && cols == 1)
	{
		alg_comp.matrix[0][0] = 1 / matrix[0][0];
		return (alg_comp);
	}
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
			alg_comp(i, j) = alg_complement(i, j);
	}
	alg_comp = alg_comp.transpose();
	return (alg_comp * (1 / this->determinant()));
}

double	Matrix::determinant()
{
	Matrix	m;
	int		sign;
	double	det;

	if (rows == 1 && cols == 1)
		return (matrix[0][0]);
	m = *this;
	sign = triangular_view(m);
	det = m.matrix[0][0];
	for (size_t i = 1; i < rows; i++)
		det *= m(i, i);
	return (sign * det);
}

void	Matrix::display() const
{
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
			std::cout << matrix[i][j] << "\t";
		std::cout << std::endl;
	}
}

double	Matrix::sum_product(const double* row, const double* col, const size_t size)
{
	double	sum;

	sum = 0.0;
	for (size_t i = 0; i < size; i++)
		sum += row[i] * col[i];
	return (sum);
}

size_t	Matrix::find_row(Matrix& matr, const size_t i)
{
	double	max_element;
	size_t	idx;

	idx = i;
	max_element = fabs(matr(i, i));
	for (size_t j = i + 1; j < matr.rows; j++)
	{
		if (max_element < fabs(matr(j, i)))
		{
			max_element = matr(j, i);
			idx = j;
		}
	}
	return (idx);
}

void	Matrix::ft_swap(double* arg1, double* arg2, const size_t size)
{
	double	tmp;

	for (size_t i = 0; i < size; i++)
	{
		tmp = arg1[i];
		arg1[i] = arg2[i];
		arg2[i] = tmp;
	}
}

int		Matrix::triangular_view(Matrix& m)
{
	int		sign;
	size_t	idx;
	double	tmp;

	sign = 1;
	for (size_t i = 0; i < rows - 1; i++)
	{
		if (i != (idx = find_row(m, i)))
		{
			ft_swap(m.matrix[i], m.matrix[idx], m.cols);
			sign *= -1;
		}
		for (size_t j = i + 1; j < rows; j++)
		{
			tmp = m(j, i) / m(i, i);
			for (size_t k = 0; k < cols; k++)
				m(i, k) -= m(i, k) * tmp;
		}
	}
	return (sign);
}

double	Matrix::alg_complement(const size_t row, const size_t col)
{
	Matrix	minor(rows - 1, cols - 1);
	size_t	r_idx;
	size_t	c_idx;

	r_idx = 0;
	for (size_t i = 0; i < rows; i++)
	{
		c_idx = 0;
		for (size_t j = 0; j < cols; j++)
		{
			if (i != row && j != col)
			{
				minor(r_idx, c_idx) = matrix[i][j];
				c_idx++;
			}
		}
		if (i != row)
			r_idx++;
	}
	return (pow(-1, row + col) * minor.determinant());
}

Matrix operator*(const double value, const Matrix& m) 
{
	Matrix res_matrix(m);
	return (res_matrix *= value);
}

Matrix operator*(const Matrix& m, const double value) 
{
	Matrix res_matrix(m);
	return (res_matrix *= value);
}
