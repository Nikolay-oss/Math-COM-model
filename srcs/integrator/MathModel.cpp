#include "MathModel.hpp"
#include "mathFunc.hpp"
#include <cmath>

MathModel::MathModel()
{
	equationCount = 4;
	retMatrix = Matrix(equationCount, 1);
	g = 0;
	density = 0;
	Cx = 0;
	_T = 0;
	_H = 0;
	_p = 0;
	B = 0;
}
// исправить! разбито не по слоям
void	MathModel::selectAtmosphereLayer(const double h)
{
	if (h > 0 && h < 11019)
	{
		_T = 288.15;
		_H = 0;
		_p = 101325;
		B = -0.0065;
	}
	else if (h > 11019 && h < 20063)
	{
		_T = 216.65;
		_H = 11019;
		_p = 22699;
		B = 0;
	}
	else if (h > 20063 && h < 32162)
	{
		_T = 216.65;
		_H = 20063;
		_p = 5486.14;
		B = 0.001;
	}
	else if (h > 32162 && h < 47350)
	{
		_T = 228.65;
		_H = 32162;
		_p = 876;
		B = 0.0028;
	}
	else if (h > 47350 && h < 51412)
	{
		_T = 270.65;
		_H = 47350;
		_p = 112;
		B = -0.0028;
	}
}

void	MathModel::calculateAtmosphereParametrs(const double V, const double h)
{
	double	a;

	H = r * h / (r + h);
	T = _T + B * (H - _H);
	g = g0 * ft_pow2(r / (r + h));
	if (isEqual(B, 0, 0.0001))
		p = _p * exp(-g0 * (H - _H) / (R * T));
	else
		p = _p * pow(T / _T, -g0 / (B * R));
	density = p * M / (_R * T);
	a = 20.046796 * sqrt(T);
	Mach = V / a;
	Cx = linearInterpolation(Mo, Cxo, Mach);
}

Matrix	MathModel::func(double t, Matrix &curState)
{
	double	V;

	V = sqrt(ft_pow2(curState[0][0]) + ft_pow2(curState[1][0]));
	selectAtmosphereLayer(curState[3][0]);
	calculateAtmosphereParametrs(V, curState[3][0]);
	// retMatrix[0][0] = -Cx * Sm * density * ft_pow2(curState[0][0]) / (2 * m) - g * sin(lambda);
	retMatrix[0][0] = -Cx * Sm * density * V * curState[0][0] / (2 * m);
	retMatrix[1][0] = -Cx * Sm * density * V * curState[1][0] / (2 * m) - g;
	retMatrix[2][0] = curState[0][0];
	retMatrix[3][0] = curState[1][0];
	return (retMatrix);
}
