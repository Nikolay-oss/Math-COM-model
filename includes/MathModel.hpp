#ifndef MATH_MODEL_HPP
#define MATH_MODEL_HPP
#include "matrix.hpp"
#include "linearInterpolation.hpp"
#include <cstddef>

class AMathModel
{
public:
	size_t	equationCount = 0;
	/*
	*	describe model parameters in child class
	*/

	virtual Matrix	func(double t, Matrix &curState) = 0;

protected:
	Matrix	retMatrix;
};

class MathModel : public AMathModel
{
public:
	// Earth radius
	const double	r = 6356767;
	const double	m = 125.3;
	const double	g0 = 9.80665;
	const double	M = 28.96442;
	const double	_R = 8314.32;
	const double	R = 287.05287;
	// Midel square
	const double	Sm = 0.0615;

	// initial values ​​of atmospheric parameters on the current layer
	double			_T;
	double			_H;
	double			_p;

	// values ​​of atmospheric parameters on the current layer
	double			T;
	double			H;
	double			g;
	double			p;
	double			density;
	// drag coefficient
	double			Cx;
	double			B;
	// mach number
	double	Mach;

	t_vect Mo = { 0.0,  0.4,  0.55,  0.65,  0.75, 0.8,  0.85,  0.9,  1.0, 1.05,  1.1,  1.15,  1.25,  1.35,  1.5, 1.75, 2.0, 2.5, 3.0};
	t_vect Cxo = { 0.53, 0.53, 0.539, 0.568, 0.643, 0.7, 0.781, 0.87, 1.035, 1.1, 1.146, 1.18, 1.216, 1.221, 1.22, 1.15, 1.1, 0.998, 0.905 };

	MathModel();
	Matrix	func(double t, Matrix &curState) override;

private:
	void	calculateAtmosphereParametrs(const double V, const double h);
	void	selectAtmosphereLayer(const double h);
};

#endif
