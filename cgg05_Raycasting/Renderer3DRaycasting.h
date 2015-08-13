#ifndef RENDERER3DRAYCASTING_H_
#define RENDERER3DRAYCASTING_H_

#include "Renderer3D.h"

class Color;
class Ray;

class Renderer3DRaycasting : public Renderer3D
{
private:
	Color raycasting(Ray& ray, double* dist);

	Renderer3DRaycasting(const Renderer3DRaycasting& src);
public:
	Renderer3DRaycasting();
	Renderer3DRaycasting(Camera3D& camera);
	virtual ~Renderer3DRaycasting();

	virtual void render();
};

#endif