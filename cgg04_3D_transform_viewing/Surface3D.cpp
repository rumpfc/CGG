#include "Surface3D.h"
#include "Vector3D.h"
#include "Texture.h"
#include "Mathtools.h"


Surface3D::Surface3D(Vector3D* p0, Vector3D* p1, Vector3D* p2, Color* color, Texture* texture)
{
	points_[0] = p0;
	points_[1] = p1;
	points_[2] = p2;

	if (color)
		color_.setColor(*color);

	texture_ = texture;
}


Surface3D::Surface3D(Vector3D& p0, Vector3D& p1, Vector3D& p2, Color* color, Texture* texture) : Surface3D(&p0, &p1, &p2, color, texture)
{
}


Surface3D::~Surface3D()
{
}


Color Surface3D::getColor()
{
	return color_;
}


double Surface3D::getArea()
{
	return Mathtools::triangleArea(*points_[0], *points_[1], *points_[2]);
}

Color Surface3D::getColor(double x, double y, double z)
{
	if (!texture_)
		return color_;

	Vector3D p(x, y, z);

	double area = this->getArea();

	double alpha = Mathtools::triangleArea(p, *points_[1], *points_[2]) / area;
	double beta = Mathtools::triangleArea(p, *points_[1], *points_[2]) / area;
	double gamma = Mathtools::triangleArea(p, *points_[1], *points_[2]) / area;

	double temp = alpha + beta + gamma;

	if (temp < (1.0 - Mathtools::EPSILON) || temp > (1.0 + Mathtools::EPSILON))
		return color_;

	double s = beta;
	double t = gamma;

	Vector2D v1 = texturePoints_[1] - texturePoints_[0];
	Vector2D v2 = texturePoints_[2] - texturePoints_[0];

	double u = texturePoints_[0].getX() + v1.getX() * s + v2.getX() * t;
	double v = texturePoints_[0].getY() + v1.getY() * s + v2.getY() * t;

	if (!texture_->isRepeatMode() && (u < 0.0 || u > 1.0 || v < 0.0 || v > 1.0))
		return color_;

	return texture_->getColor(u, v);
}


Texture* Surface3D::getTexture()
{
	return texture_;
}


Vector3D Surface3D::getNormal()
{
	Vector3D v1 = *points_[1] - *points_[0];
	Vector3D v2 = *points_[2] - *points_[0];

	Vector3D normal = Mathtools::cross(v1, v2);
	normal.normalize();

	return normal;
}


Vector3D Surface3D::getCenter()
{
	Vector3D sum = *points_[0] + *points_[1] + *points_[2];
	sum = sum / 3.0;

	return sum;
}


void Surface3D::setColor(Color color)
{
	color_.setColor(color);
}

// surface points -------------------------------------------------------------
Vector3D* Surface3D::getP0()
{
	return points_[0];
}


Vector3D* Surface3D::getP1()
{
	return points_[1];
}


Vector3D* Surface3D::getP2()
{
	return points_[2];
}

// texture anchor points ------------------------------------------------------
Vector2D& Surface3D::getT0()
{
	return texturePoints_[0];
}


Vector2D& Surface3D::getT1()
{
	return texturePoints_[1];
}


Vector2D& Surface3D::getT2()
{
	return texturePoints_[2];
}


void Surface3D::linkTexture(Texture* texture)
{
	texture_ = texture;
}


void Surface3D::setTextureAnchorPoints(Vector2D& t0, Vector2D& t1, Vector2D& t2)
{
	texturePoints_[0].setVector(t0);
	texturePoints_[1].setVector(t1);
	texturePoints_[2].setVector(t2);
}