#include "launchCalculations.hpp"
#include "RungeKutta.hpp"
#include "MathModel.hpp"
#include "mathFunc.hpp"
#include <cmath>

static void	initState(Matrix &state, double h, double lambda, double v)
{
	state[0][0] = v * cos(deg2rad(lambda));
	state[1][0] = v * sin(deg2rad(lambda));
	state[2][0] = 0;
	state[3][0] = h;
}

static double	calcRel(double xStart, double xEnd)
{
	return (xEnd - xStart);
}

void	launchCalculations(Matrix &sysSolve, Matrix &t, double h, double lambda, double v)
{
	RungeKutta	rk;
	MathModel	model;
	Matrix		state(4, 1);

	initState(state, h, lambda, v);
	rk.setDelta(0.01);
	rk.setLimits(0, 200);
	rk.setStopIntegrationOption(0, 3);
	sysSolve = rk.integrate(&model, state);
	t = rk.getTimeRange();
}
