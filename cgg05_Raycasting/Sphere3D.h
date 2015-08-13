#ifndef SPHERE3D_H_
#define SPHERE3D_H_

#include "Object3D.h"

class Sphere3D : public Object3D
{
private:
	int accuracy_;

	Sphere3D(const Sphere3D& src);

	void initPoints();
	void initTriangles();

protected:
	virtual void initialize();

public:
	Sphere3D();
	Sphere3D(const double radius, const int accuracy = 30);
	virtual ~Sphere3D();

	virtual Vector3D getNormal(Vector3D& point);
};

#endif