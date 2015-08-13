#ifndef RENDERER3DRASTERIZATION_H_
#define RENDERER3DRASTERIZATION_H_

#include "Renderer3D.h"

class Renderer3DRasterization : public Renderer3D
{
private:
	Renderer3DRasterization(const Renderer3DRasterization& src);
public:
	Renderer3DRasterization();
	Renderer3DRasterization(Camera3D& camera);
	virtual ~Renderer3DRasterization();

	virtual void render();
};

#endif