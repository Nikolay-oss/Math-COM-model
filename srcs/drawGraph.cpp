#include "drawGraph.hpp"

using namespace sciplot;

void	drawGraph(t_vec &x, t_vec &y, std::string legendName, std::string colorLine)
{
	Plot	plot;

	plot.size(800, 512);
	plot.xlabel("X").fontSize(12).textColor("red");
	plot.ylabel("Y").fontSize(12).textColor("red");
	plot.grid().lineColor("black").dashType(1).show();

	plot.legend()
	.atOutsideBottom()
	.displayHorizontal()
	.displayExpandWidthBy(2);

	plot.drawCurve(x, y)
	.label(legendName)
	.lineWidth(2)
	.lineColor(colorLine);
	plot.show();
}

void	copyXYToVector(Matrix &m, t_vec &x, t_vec &y)
{
	for (size_t i = 0; i < m.get_rsize(); i++)
	{
		x.push_back(m(i, 2));
		y.push_back(m(i, 3));
	}
}
