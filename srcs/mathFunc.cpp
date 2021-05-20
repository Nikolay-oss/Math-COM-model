#include "mathFunc.hpp"
#include <cmath>

double	ft_pow2(double arg)
{
	return (arg * arg);
}

double	deg2rad(double angle)
{
	return (angle * M_PI / 180);
}

bool	isEqual(const double arg1, const double arg2, const double precision)
{
	return (fabs(arg2 - arg1) < precision);
}
