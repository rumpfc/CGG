#include "Vector2D.h"
#include "Vector3D.h"

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

void Vector2D::setVector(const double x, const double y)
{
	x_ = x;
	y_ = y;
}

void Vector2D::setVector(const Vector2D &v)
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

Vector2D operator+(const Vector2D &v1, const Vector2D &v2)
{
	return Vector2D(v1.x_ + v2.x_, v1.y_ + v2.y_);
}

Vector2D operator-(const Vector2D &v1, const Vector2D &v2)
{
	return Vector2D(v1.x_ - v2.x_, v1.y_ - v2.y_);
}

Vector2D operator*(const Vector2D &v, const double d)
{
	return Vector2D(v.x_ * d, v.y_ * d);
}

Vector2D operator*(const double d, const Vector2D &v)
{
	return Vector2D(v.x_ * d, v.y_ * d);
}

Vector2D operator/(const Vector2D &v, const double d)
{
	return Vector2D(v.x_ / d, v.y_ / d);
}

void Vector2D::operator=(const Vector2D &v)
{
	x_ = v.x_;
	y_ = v.y_;
}

void Vector2D::operator+=(const Vector2D &v)
{
	x_ += v.x_;
	y_ += v.y_;
}

void Vector2D::operator-=(const Vector2D &v)
{
	x_ -= v.x_;
	y_ -= v.y_;
}

void Vector2D::operator*=(const double d)
{
	x_ *= d;
	y_ *= d;
}

void Vector2D::operator/=(const double d)
{
	x_ /= d;
	y_ /= d;
}


// extra overloaded operators

double operator*(const Vector2D &v1, const Vector2D &v2)
{
	return v1.x_ * v2.x_ + v1.y_ * v2.y_;
}


// cast to Vector3D

Vector3D Vector2D::toVector3D()
{
	return Vector3D(x_, y_, 0.0);
}