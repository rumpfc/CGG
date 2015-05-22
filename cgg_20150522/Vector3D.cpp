#include "Vector3D.h"

#include <cmath>


Vector3D::Vector3D(double x, double y, double z) : x_(x), y_(y), z_(z)
{
}

Vector3D::Vector3D(const Vector3D &src) : x_(src.x_), y_(src.y_), z_(src.z_)
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

// getter and setter methods --------------------------------------------------

void Vector3D::setVector(double x, double y, double z)
{
	x_ = x;
	y_ = y;
	z_ = z;
}

void Vector3D::setVector(Vector3D &v)
{
	x_ = v.x_;
	y_ = v.y_;
	z_ = v.z_;
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

// overloaded operators -------------------------------------------------------

Vector3D operator+(Vector3D &v1, Vector3D &v2)
{
	return Vector3D(v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_);
}

Vector3D operator-(Vector3D &v1, Vector3D &v2)
{
	return Vector3D(v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_);
}

Vector3D operator*(Vector3D &v, double d)
{
	return Vector3D(v.x_ * d, v.y_ * d, v.z_ * d);
}

Vector3D operator*(double d, Vector3D &v)
{
	return Vector3D(v.x_ * d, v.y_ * d, v.z_ * d);
}

Vector3D operator/(Vector3D &v, double d)
{
	return Vector3D(v.x_ / d, v.y_ / d, v.z_ / d);
}

void Vector3D::operator+=(Vector3D &v)
{
	x_ += v.x_;
	y_ += v.y_;
	z_ += v.z_;
}

void Vector3D::operator-=(Vector3D &v)
{
	x_ -= v.x_;
	y_ -= v.y_;
	z_ -= v.z_;
}

void Vector3D::operator*=(double d)
{
	x_ *= d;
	y_ *= d;
	z_ *= d;
}

void Vector3D::operator/=(double d)
{
	x_ /= d;
	y_ /= d;
	z_ /= d;
}


// extra overloaded operators

double operator*(Vector3D &v1, Vector3D &v2)
{
	return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_;
}

Vector3D operator%(Vector3D &v1, Vector3D &v2)
{
	double x = v1.y_ * v2.z_ - v2.y_ * v1.z_;
	double y = v1.z_ * v2.x_ - v2.z_ * v1.x_;
	double z = v1.x_ * v2.y_ - v2.x_ * v1.y_;

	return Vector3D(x, y, z);
}