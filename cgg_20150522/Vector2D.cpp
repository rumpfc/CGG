#include "Vector2D.h"

#include <cmath>


Vector2D::Vector2D(double x, double y) : x_(x), y_(y)
{
}

Vector2D::Vector2D(const Vector2D &src) : x_(src.x_), y_(src.y_)
{
}

Vector2D::~Vector2D()
{
}


// basic methods --------------------------------------------------------------

double Vector2D::length()
{
	return sqrt(x_*x_ + y_*y_);
}


void Vector2D::normalize()
{
	double l = length();

	x_ /= l;
	y_ /= l;
}

// getter and setter methods --------------------------------------------------

void Vector2D::setVector(double x, double y)
{
	x_ = x;
	y_ = y;
}

void Vector2D::setVector(Vector2D &v)
{
	x_ = v.x_;
	y_ = v.y_;
}

double Vector2D::getX()
{
	return x_;
}

double Vector2D::getY()
{
	return y_;
}

// overloaded operators -------------------------------------------------------

Vector2D operator+(Vector2D &v1, Vector2D &v2)
{
	return Vector2D(v1.x_ + v2.x_, v1.y_ + v2.y_);
}

Vector2D operator-(Vector2D &v1, Vector2D &v2)
{
	return Vector2D(v1.x_ - v2.x_, v1.y_ - v2.y_);
}

Vector2D operator*(Vector2D &v, double d)
{
	return Vector2D(v.x_ * d, v.y_ * d);
}

Vector2D operator*(double d, Vector2D &v)
{
	return Vector2D(v.x_ * d, v.y_ * d);
}

Vector2D operator/(Vector2D &v, double d)
{
	return Vector2D(v.x_ / d, v.y_ / d);
}

void Vector2D::operator+=(Vector2D &v)
{
	x_ += v.x_;
	y_ += v.y_;
}

void Vector2D::operator-=(Vector2D &v)
{
	x_ -= v.x_;
	y_ -= v.y_;
}

void Vector2D::operator*=(double d)
{
	x_ *= d;
	y_ *= d;
}

void Vector2D::operator/=(double d)
{
	x_ /= d;
	y_ /= d;
}


// extra overloaded operators

double operator*(Vector2D &v1, Vector2D &v2)
{
	return v1.x_ * v2.x_ + v1.y_ * v2.y_;
}
