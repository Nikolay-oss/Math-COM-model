#ifndef DRAW_GRAPH_HPP
#define DRAW_GRAPH_HPP

#include "sciplot.hpp"
#include "Matrix.hpp"

typedef std::vector<double> t_vec;

void	drawGraph(t_vec &x, t_vec &y, std::string legendName, std::string colorLine);
void	copyXYToVector(Matrix &m, t_vec &x, t_vec &y);

#endif
