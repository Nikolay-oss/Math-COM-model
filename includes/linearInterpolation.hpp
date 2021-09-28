#ifndef LINEAR_INTERPOLATION_HPP
#define LINEAR_INTERPOLATION_HPP

#include <vector>

typedef std::vector<double> t_vect;

double	linearInterpolation(t_vect time_range, t_vect values_range, double time_new);

#endif
