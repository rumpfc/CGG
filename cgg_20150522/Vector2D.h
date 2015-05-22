#ifndef VECTOR2D_H_
#define VECTOR2D_H_

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

	void setVector(double x, double y);
	void setVector(Vector2D &v);

	double getX();
	double getY();

	// overloading operators for vector calculations

	friend Vector2D operator+(Vector2D &v1, Vector2D &v2);
	friend Vector2D operator-(Vector2D &v1, Vector2D &v2);
	friend Vector2D operator*(Vector2D &v, double d);
	friend Vector2D operator*(double d, Vector2D &v);
	friend Vector2D operator/(Vector2D &v, double d);

	void operator+=(Vector2D &v);
	void operator-=(Vector2D &v);
	void operator*=(double d);
	void operator/=(double d);

	// not really needed, but just in case: Dot-Product (*)
	// we will use dot(v1, v2) from "Mathtools.h"

	friend double operator*(Vector2D &v1, Vector2D &v2);
};

#endif
