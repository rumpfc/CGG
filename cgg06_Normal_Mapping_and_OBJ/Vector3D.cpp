#include "Vector3D.h"
#include "Vector2D.h"

#include <cmath>


Vector3D::Vector3D() : x_(0.0), y_(0.0), z_(0.0), w_(1.0)
{
}


Vector3D::Vector3D(double x, double y, double z, double w) : x_(x), y_(y), z_(z), w_(w)
{
}

Vector3D::Vector3D(const Vector3D &src) : x_(src.x_), y_(src.y_), z_(src.z_), w_(src.w_)
{
}

Vector3D::~Vector3D()
{
}


// basic methods --------------------------------------------------------------

double Vector3D::length()
{
	return sqrt(x_*x_ + y_*y_ + z_*z_);
}


void Vector3D::normalize()
{
	double l = length();

	x_ /= l;
	y_ /= l;
	z_ /= l;
}

void Vector3D::homogeneousDivide()
{
	x_ /= w_;
	y_ /= w_;
	z_ /= w_;
	w_ /= w_;
}

// getter and setter methods --------------------------------------------------

void Vector3D::setVector(const double x, const double y, const double z, const double w)
{
	x_ = x;
	y_ = y;
	z_ = z;
	w_ = w;
}

void Vector3D::setVector(const Vector3D &v)
{
	x_ = v.x_;
	y_ = v.y_;
	z_ = v.z_;
	w_ = v.w_;
}

double Vector3D::getX()
{
	return x_;
}

double Vector3D::getY()
{
	return y_;
}

double Vector3D::getZ()
{
	return z_;
}

double Vector3D::getW()
{
	return w_;
}

// overloaded operators -------------------------------------------------------

Vector3D operator+(const Vector3D &v1, const Vector3D &v2)
{
	return Vector3D(v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_);
}

Vector3D operator-(const Vector3D &v1, const Vector3D &v2)
{
	return Vector3D(v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_);
}

Vector3D operator*(const Vector3D &v, const double d)
{
	return Vector3D(v.x_ * d, v.y_ * d, v.z_ * d);
}

Vector3D operator*(const double d, const Vector3D &v)
{
	return Vector3D(v.x_ * d, v.y_ * d, v.z_ * d);
}

Vector3D operator/(const Vector3D &v, const double d)
{
	return Vector3D(v.x_ / d, v.y_ / d, v.z_ / d);
}

void Vector3D::operator=(const Vector3D &v)
{
	x_ = v.x_;
	y_ = v.y_;
	z_ = v.z_;
}

void Vector3D::operator+=(const Vector3D &v)
{
	x_ += v.x_;
	y_ += v.y_;
	z_ += v.z_;
}

void Vector3D::operator-=(const Vector3D &v)
{
	x_ -= v.x_;
	y_ -= v.y_;
	z_ -= v.z_;
}

void Vector3D::operator*=(const double d)
{
	x_ *= d;
	y_ *= d;
	z_ *= d;
}

void Vector3D::operator/=(const double d)
{
	x_ /= d;
	y_ /= d;
	z_ /= d;
}


Vector3D Vector3D::operator-()
{
	double x = -x_;
	double y = -y_;
	double z = -z_;

	return Vector3D(x, y, z);
}

// extra overloaded operators

double operator*(const Vector3D &v1, const Vector3D &v2)
{
	return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_;
}

Vector3D operator%(const Vector3D &v1, const Vector3D &v2)
{
	double x = v1.y_ * v2.z_ - v2.y_ * v1.z_;
	double y = v1.z_ * v2.x_ - v2.z_ * v1.x_;
	double z = v1.x_ * v2.y_ - v2.x_ * v1.y_;

	return Vector3D(x, y, z);
}

// cast to Vector2D

Vector2D Vector3D::toVector2D()
{
	return Vector2D(x_/w_, y_/w_);
}