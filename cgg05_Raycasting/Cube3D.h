#ifndef CUBE3D_H_
#define CUBE3D_H_

#include "Object3D.h"

class Cube3D : public Object3D
{
private:
	double width_;
	double height_;
	double depth_;

	Cube3D(const Cube3D& src);

protected:
	virtual void initialize();

public:
	Cube3D();
	Cube3D(double width, double height, double depth);
	virtual ~Cube3D();

	virtual Vector3D getNormal(Vector3D& point);
};

#endif