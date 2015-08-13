#ifndef RAY_H_
#define RAY_H_

#include "Vector3D.h"

/*
A ray is mainly used in Raycasting and Raytracing, but also finds usage in
other rendering tools like Radiosity and Pathtracing
*/

class Ray
{
private:
	Vector3D start_;
	Vector3D direction_;
public:
	Ray();
	Ray(Vector3D& start, Vector3D& direction);
	Ray(const Ray& src);
	virtual ~Ray();

	// normalize ray = normalize direction
	void normalize();

	// getter and setter
	void setStart(Vector3D& start);
	void setDirection(Vector3D& direction);

	Vector3D getStart();
	Vector3D getDirection();

	// calculate point by factor t
	// point = start_ + t * direction_
	Vector3D getPoint(double t);
};

#endif