#ifndef VECTOR3D_H_
#define VECTOR3D_H_

class Vector3D
{
private:
	// Coordinates along x-, y-axis and z-axis
	double x_;
	double y_;
	double z_;

public:
	Vector3D(double x = 0.0, double y = 0.0, double z = 0.0);   // standard constructor
	Vector3D(const Vector3D &src);                              // copy constructor
	virtual ~Vector3D();                                        // destructor

	// basic methods we will need the most
	double length();
	void normalize();

	// getter/setter

	void setVector(double x, double y, double z);
	void setVector(Vector3D &v);

	double getX();
	double getY();
	double getZ();

	// overloading operators for vector calculations

	friend Vector3D operator+(Vector3D &v1, Vector3D &v2);
	friend Vector3D operator-(Vector3D &v1, Vector3D &v2);
	friend Vector3D operator*(Vector3D &v, double d);
	friend Vector3D operator*(double d, Vector3D &v);
	friend Vector3D operator/(Vector3D &v, double d);

	void operator+=(Vector3D &v);
	void operator-=(Vector3D &v);
	void operator*=(double d);
	void operator/=(double d);

	// not really needed, but just in case: Dot-Product (*) and Cross-Prodcu (%)
	// we will use dot(v1, v2) and cross(v1, v2) from "Mathtools.h"

	friend double operator*(Vector3D &v1, Vector3D &v2);
	friend Vector3D operator%(Vector3D &v1, Vector3D &v2);
};

#endif
