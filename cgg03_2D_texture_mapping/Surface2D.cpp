#include "Surface2D.h"
#include "Vector2D.h"
#include "Texture.h"


Surface2D::Surface2D(Vector2D* p0, Vector2D* p1, Vector2D* p2, Color* color, Texture* texture)
{
	points_[0] = p0;
	points_[1] = p1;
	points_[2] = p2;

	if (color)
		color_.setColor(*color);

	texture_ = texture;
}


Surface2D::Surface2D(Vector2D& p0, Vector2D& p1, Vector2D& p2, Color* color, Texture* texture) : Surface2D(&p0, &p1, &p2, color, texture)
{
}


Surface2D::~Surface2D()
{
}


Color Surface2D::getColor()
{
	return color_;
}


Color Surface2D::getColor(double x, double y)
{
	if (!texture_)
		return color_;

	// calculate paramedic values s and t from formula
	// v0 = P1 - P0
	// v1 = P2 - P0
	// 
	// P  = P0 + v0 * s + v1 * t

	Vector2D v1 = *points_[1] - *points_[0];
	Vector2D v2 = *points_[2] - *points_[0];

	double s = (v2.getX() * (y - points_[0]->getY()) - v2.getY() * (x - points_[0]->getX())) / (v2.getX() * v1.getY() - v1.getX() * v2.getY());
	double t = (v1.getX() * (y - points_[0]->getY()) - v1.getY() * (x - points_[0]->getX())) / (v1.getX() * v2.getY() - v2.getX() * v1.getY());
	
	// use s and t on texture anchor points to get u and v

	v1 = texturePoints_[1] - texturePoints_[0];
	v2 = texturePoints_[2] - texturePoints_[0];

	double u = texturePoints_[0].getX() + v1.getX() * s + v2.getX() * t;
	double v = texturePoints_[0].getY() + v1.getY() * s + v2.getY() * t;

	if (!texture_->isRepeatMode() && (u < 0.0 || u > 1.0 || v < 0.0 || v > 1.0))
		return color_;

	return texture_->getColor(u, v);
}


Texture* Surface2D::getTexture()
{
	return texture_;
}


void Surface2D::setColor(Color color)
{
	color_.setColor(color);
}

// surface points -------------------------------------------------------------
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

// texture anchor points ------------------------------------------------------
Vector2D& Surface2D::getT0()
{
	return texturePoints_[0];
}


Vector2D& Surface2D::getT1()
{
	return texturePoints_[1];
}


Vector2D& Surface2D::getT2()
{
	return texturePoints_[2];
}


void Surface2D::linkTexture(Texture* texture)
{
	texture_ = texture;
}


void Surface2D::setTextureAnchorPoints(Vector2D& t0, Vector2D& t1, Vector2D& t2)
{
	texturePoints_[0].setVector(t0);
	texturePoints_[1].setVector(t1);
	texturePoints_[2].setVector(t2);
}