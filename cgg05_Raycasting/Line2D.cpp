#include "Line2D.h"
#include "Vector2D.h"

Line2D::Line2D(Vector2D* p1, Vector2D* p2, Color* color)
{
	points_[0] = p1;
	points_[1] = p2;

	if (color)
		color_.setColor(*color);
}

Line2D::Line2D(Vector2D& p1, Vector2D& p2, Color* color) : Line2D(&p1, &p2, color)
{
}

Line2D::~Line2D()
{
}


Color Line2D::getColor()
{
	return color_;
}


void Line2D::setColor(Color color)
{
	color_.setColor(color);
}


Vector2D* Line2D::getP1()
{
	return points_[0];
}


Vector2D* Line2D::getP2()
{
	return points_[1];
}
