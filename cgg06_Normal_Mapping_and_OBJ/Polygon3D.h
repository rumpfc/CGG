#ifndef POLYGON3D_H_
#define POLYGON3D_H_

#include "Object3D.h"

class Polygon3D : public Object3D
{
protected:
	virtual void initialize();
public:
	Polygon3D();
	virtual ~Polygon3D();

	void addPoint(Vector3D* point);
	void addSurface(Surface3D* surface);
};

#endif