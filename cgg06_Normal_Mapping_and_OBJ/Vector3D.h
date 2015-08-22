#ifndef VECTOR3D_H_
#define VECTOR3D_H_

class Vector2D;

class Vector3D
{
private:
	// Coordinates along x-, y-axis and z-axis
	double x_;
	double y_;
	double z_;

	// homogenous factor
	double w_;

public:
	Vector3D();
	Vector3D(double x, double y, double z, double w = 1.0);   // standard constructor
	Vector3D(const Vector3D &src);                              // copy constructor
	virtual ~Vector3D();                                        // destructor

	// basic methods we will need the most
	double length();
	void normalize();
	void homogeneousDivide();

	// getter/setter

	void setVector(const double x, const double y, const double z, const double w = 1.0);
	void setVector(const Vector3D &v);

	double getX();
	double getY();
	double getZ();
	double getW();

	// overloading operators for vector calculations

	friend Vector3D operator+(const Vector3D &v1, const Vector3D &v2);
	friend Vector3D operator-(const Vector3D &v1, const Vector3D &v2);
	friend Vector3D operator*(const Vector3D &v, const double d);
	friend Vector3D operator*(const double d, const Vector3D &v);
	friend Vector3D operator/(const Vector3D &v, const double d);

	void operator=(const Vector3D &v);
	void operator+=(const Vector3D &v);
	void operator-=(const Vector3D &v);
	void operator*=(const double d);
	void operator/=(const double d);

	Vector3D operator-();

	// not really needed, but just in case: Dot-Product (*) and Cross-Prodcu (%)
	// we will use dot(v1, v2) and cross(v1, v2) from "Mathtools.h"

	friend double operator*(const Vector3D &v1, const Vector3D &v2);
	friend Vector3D operator%(const Vector3D &v1, const Vector3D &v2);

	// cast to Vector2D
	Vector2D toVector2D();
};

#endif
