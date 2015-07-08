#ifndef VECTOR2D_H_
#define VECTOR2D_H_

class Vector3D;

class Vector2D
{
private:
	// Coordinates along x- and y-axis
	double x_;
	double y_;

public:
	Vector2D(double x = 0.0, double y = 0.0);   // standard constructor
	Vector2D(const Vector2D &src);              // copy constructor
	virtual ~Vector2D();                        // destructor

	// basic methods we will need the most
	double length();
	void normalize();

	// getter/setter

	void setVector(const double x, const double y);
	void setVector(const Vector2D &v);

	double getX();
	double getY();

	// overloading operators for vector calculations

	friend Vector2D operator+(const Vector2D &v1, const Vector2D &v2);
	friend Vector2D operator-(const Vector2D &v1, const Vector2D &v2);
	friend Vector2D operator*(const Vector2D &v, const double d);
	friend Vector2D operator*(const double d, const Vector2D &v);
	friend Vector2D operator/(const Vector2D &v, const double d);

	void operator=(const Vector2D &v);
	void operator+=(const Vector2D &v);
	void operator-=(const Vector2D &v);
	void operator*=(const double d);
	void operator/=(const double d);

	// not really needed, but just in case: Dot-Product (*)
	// we will use dot(v1, v2) from "Mathtools.h"

	friend double operator*(const Vector2D &v1, const Vector2D &v2);

	// cast to Vector3D
	Vector3D toVector3D();
};

#endif
