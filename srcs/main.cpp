#include "drawGraph.hpp"
#include "parser.hpp"
#include "launchCalculations.hpp"
#include <cstdlib>
#include <iostream>

#define GRAPH

int main()
{
	Matrix	sysSolve;
	Matrix	t;
	double	h;
	double	lambda;
	double	v;
	t_vec	x;
	t_vec	y;

	if (!readInitValues(h, lambda, v))
		return (EXIT_FAILURE);
	launchCalculations(sysSolve, t, h, lambda, v);
	std::cout << "Rel -> " << sysSolve(sysSolve.get_rsize() - 1, 2) << std::endl;
	std::cout << "Fall time -> " << t(t.get_rsize() - 1, 0) << std::endl;
	#ifdef GRAPH
		copyXYToVector(sysSolve, x, y);
		drawGraph(x, y, "Trajectory", "red");
	#endif
	return (EXIT_SUCCESS);
}
