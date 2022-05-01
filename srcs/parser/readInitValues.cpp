#include "parser.hpp"

static bool	showErrorMessage(std::string message)
{
	std::cerr << message << std::endl;
	return (false);
}

bool	readInitValues(double &h, double &lambda, double &v)
{
	std::cout << "H [m] -> ";
	if (!readValue(h))
		return (showErrorMessage("Invalid H parametr"));
	if (h < 0)
		return (showErrorMessage("Error: H < 0"));
	std::cout << "lambda (deg) -> ";
	if (!readValue(lambda))
		return (showErrorMessage("Invalid lambda parametr"));
	std::cout << "v [m/sec] -> ";
	if (!readValue(v))
		return (showErrorMessage("Invalid v parametr"));
	return (true);
}
