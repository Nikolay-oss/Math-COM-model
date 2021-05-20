#include "linearInterpolation.hpp"
#include "mathFunc.hpp"
#include <cmath>

static int	binarySearch(t_vect arr, size_t size, double value)
{
	int	middle_idx;
	int	step;

	middle_idx = (int)(size / 2);
	if (value > arr[middle_idx])
		step = 1;
	else
		step = -1;
	for (int i = middle_idx; (i > -1 && i < (int)size - 1); i += step)
	{
		if (value > arr[i] && value < arr[i + 1])
			return (i);
		else if (isEqual(arr[i], value, 0.0000001))
			return (i);
	}
	return (-1);
}

double		linearInterpolation(t_vect time_range, t_vect values_range, double time_new)
{
	double	value;
	int		i;

	value = 0.0;
	i = binarySearch(time_range, time_range.size(), time_new);
	if (i == -1)
		i = 0;
	value = values_range[i] + ((values_range[i + 1] - values_range[i]) * (time_new - time_range[i]))
		/ (time_range[i + 1] - time_range[i]);
	return (value);
}
