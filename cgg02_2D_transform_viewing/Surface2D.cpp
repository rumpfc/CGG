#include "Surface2D.h"
#include "Vector2D.h"


Surface2D::Surface2D(Vector2D* p0, Vector2D* p1, Vector2D* p2, Color* color)
{
	points_[0] = p0;
	points_[1] = p1;
	points_[2] = p2;

	if (color)
		color_.setColor(*color);
}


Surface2D::Surface2D(Vector2D& p0, Vector2D& p1, Vector2D& p2, Color* color) : Surface2D(&p0, &p1, &p2, color)
{
}


Surface2D::~Surface2D()
{
}


Color& Surface2D::getColor()
{
	return color_;
}


void Surface2D::setColor(Color& color)
{
	color_.setColor(color);
}


Vector2D* Surface2D::getP0()
{
	return points_[0];
}


Vector2D* Surface2D::getP1()
{
	return points_[1];
}


Vector2D* Surface2D::getP2()
{
	return points_[2];
}
