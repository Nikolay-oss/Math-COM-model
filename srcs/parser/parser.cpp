#include "parser.hpp"

static void	skipIsspace(const char *str, size_t &i, size_t &j)
{
	while (i < j)
	{
		if (isspace(*(str + i)))
			i++;
		else
			break ;
		if (isspace(*(str + j)))
			j--;
		else
			break ;
	}
}

static bool	checkDigitsAroundDot(const char *str, size_t i)
{
	if (i == 0)
		return (false);
	else if (isdigit(*(str + i - 1)) && isdigit(*(str + i + 1)))
		return (true);
	return (false);
}

static bool	checkValue(const char *str, size_t size)
{
	size_t	i;
	size_t	j;
	bool	isDot;
	bool	isDigit;

	i = 0;
	j = size - 1;
	isDigit = false;
	isDot = false;
	skipIsspace(str, i, j);
	if (*(str + i) == '-')
		i++;
	while (i <= j)
	{
		if (isdigit(*(str + i)))
			isDigit = true;
		else if (*(str + i) == '.' && !isDot)
		{
			isDot = true;
			if (!checkDigitsAroundDot(str, i))
				return (false);
		}
		else
			return (false);
		i++;
	}
	return (isDigit);
}

bool	readValue(double &nbr)
{
	std::string	str;
	bool		isNbr;

	std::getline(std::cin, str);
	nbr = 0.0;
	isNbr = true;
	if (str.empty())
		return (isNbr);
	if (checkValue(str.c_str(), str.size()))
		nbr = stoi(str);
	else
		isNbr = false;
	return (isNbr);
}
