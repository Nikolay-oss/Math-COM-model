#ifndef RUNGE_KUTTA_HPP
#define RUNGE_KUTTA_HPP
#include "MathModel.hpp"

class RungeKutta
{
public:
	RungeKutta();
	/**
	 * @brief Construct a new Runge Kutta object
	 * 
	 * @param tStart Left border
	 * @param tEnd Right border
	 * @param dt Step
	 */
	RungeKutta(const double tStart, const double tEnd, const double dt);
	void	setDelta(const double dt);
	void	setLimits(const double tStart, const double tEnd);
	void	setStopIntegrationOption(const double stopValue, const size_t equationIdx);
	Matrix	integrate(AMathModel *model, const Matrix &initState);
	Matrix	getTimeRange() { return (t); }

private:
	Matrix	sysSolve;
	Matrix	t;
	double	k[4];
	Matrix	curState;
	double	dt;
	size_t	stepsCount;
	double	tStart;
	double	tEnd;
	double	stopValue;
	size_t	equationIdx;
	bool	stopIntegrationFlag;

	void	calcStepsCount();
	void	copyStateValues(const size_t rowIdx, bool isCopyToState);
	void	updateMatrix(const size_t newSize);
};

#endif
