#include "Ellipse2D.h"


Ellipse2D::Ellipse2D() : rx_(3.0), ry_(2.0), Object2D()
{
	initialize();
}


Ellipse2D::Ellipse2D(double rx, double ry) : rx_(rx), ry_(ry), Object2D()
{
	initialize();
}


Ellipse2D::~Ellipse2D()
{
}


void Ellipse2D::initialize()
{
	double inc = Mathtools::PI * 2.0 / 100.0;

	// init points
	// x = rx * cos(phi)
	// y = ry * sin(phi)

	for (int t = 0; t < 100; t++)
	{
		double x = rx_ * cos(static_cast<double>(t)* inc);
		double y = ry_ * sin(static_cast<double>(t)* inc);

		points_.push_back(new Vector2D(x, y));
	}

	// connect points with lines

	for (int t = 0; t < 99; t++)
	{
		lines_.push_back(new Line2D(points_[t], points_[t + 1]));
	}

	lines_.push_back(new Line2D(points_.back(), points_.front(), &lineColor_));

	for (int t = 1; t < 99; t++)
	{
		triangles_.push_back(new Surface2D(points_[0], points_[t], points_[t+1], &fillColor_));
	}
}