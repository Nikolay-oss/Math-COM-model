#include "RungeKutta.hpp"
#include "mathFunc.hpp"
#include <iostream>

RungeKutta::RungeKutta()
{
	dt = 0.001;
	stepsCount = 0;
	tStart = 0;
	tEnd = 0;
	stopValue = 0;
	equationIdx = 0;
	stopIntegrationFlag = false;
}

RungeKutta::RungeKutta(const double tStart, const double tEnd, const double dt)
{
	this->tStart = tStart;
	this->tEnd = tEnd;
	this->dt = dt;
	stepsCount = 0;
	stopValue = 0;
	equationIdx = 0;
	stopIntegrationFlag = false;
}

void	RungeKutta::setDelta(const double dt)
{
	this->dt = dt;
}

void	RungeKutta::setLimits(const double tStart, const double tEnd)
{
	if (tEnd < tStart)
	{
		std::cerr << "The right limit of integration cannot be less than the left one\n";
		return ;
	}
	this->tStart = tStart;
	this->tEnd = tEnd;
}

void	RungeKutta::calcStepsCount()
{
	if (tEnd < tStart)
		return ;
	stepsCount = static_cast<size_t>((tEnd - tStart) / dt);
}

void	RungeKutta::copyStateValues(const size_t rowIdx, bool isCopyToState)
{
	for (size_t i = 0; i < sysSolve.get_csize(); i++)
	{
		if (isCopyToState)
			curState[i][0] = sysSolve[rowIdx][i];
		else
			sysSolve[rowIdx][i] = curState[i][0];
	}
}

void	RungeKutta::setStopIntegrationOption(const double stopValue, const size_t equationIdx)
{
	this->stopValue = stopValue;
	this->equationIdx = equationIdx;
	stopIntegrationFlag = true;
}

void	RungeKutta::updateMatrix(const size_t newSize)
{
	Matrix	newSysSolve;
	Matrix	newT;

	newSysSolve.create_matrix(newSize, sysSolve.get_csize());
	newT.create_matrix(newSize, t.get_csize());
	for (size_t i = 0; i < newSize; i++)
	{
		newT[i][0] = t[i][0];
		for (size_t j = 0; j < sysSolve.get_csize(); j++)
		{
			newSysSolve[i][j] = sysSolve[i][j];
		}
	}
	sysSolve = newSysSolve;
	t = newT;
}

Matrix	RungeKutta::integrate(AMathModel *model, const Matrix &initState)
{
	calcStepsCount();
	sysSolve = Matrix(stepsCount, model->equationCount);
	t = Matrix(stepsCount, 1);
	curState = initState;
	copyStateValues(0, false);

	t[0][0] = tStart;
	for (size_t i = 1; i < stepsCount; i++)
	{
		t[i][0] = t[i - 1][0] + dt;
		for (size_t j = 0; j < model->equationCount; j++)
		{
			k[0] = model->func(t[i - 1][0], curState)[j][0] * dt;
			curState = curState + curState.multiply(dt / 2 * k[0]);
			k[1] = model->func(t[i - 1][0] + dt / 2, curState)[j][0] * dt;
			curState = curState + curState.multiply(dt / 2 * k[1]);
			k[2] = model->func(t[i - 1][0] + dt / 2, curState)[j][0] * dt;
			curState = curState + curState.multiply(dt * k[2]);
			k[3] = model->func(t[i - 1][0] + dt, curState)[j][0] * dt;
			sysSolve[i][j] = sysSolve[i - 1][j] + (k[0] + 2 * k[1] + 2 * k[2] + k[3]) / 6;
		}
		copyStateValues(i, true);
		if (stopIntegrationFlag && isEqual(curState[equationIdx][0], stopValue, 0.2))
		{
			updateMatrix(i + 1);
			break ;
		}
	}
	return (sysSolve);
}
