#ifndef RENDERER3D_H_
#define RENDERER3D_H_

#include "Renderer.h"
#include "Camera3D.h"

class Surface3D;
class Scene3D;

/*
abstract class for 3D rendering
contains standard rasterization algorithm which can also be used for
radiosity

contains depth buffer of size W*H
*/

class Renderer3D : public Renderer
{
protected:
	double* depthBuffer_;

	Camera3D* camera_;
	Scene3D* scene_;

	// this function will be used in "rasterization" and "radiosity"
	void rasterization(Surface3D* triangle);

	// init depth buffer

	void initDepthBuffer(double value);

	void setMaxDepth(double max);

public:
	Renderer3D();
	Renderer3D(Camera3D& camera);
	virtual ~Renderer3D();

	// abstract
	virtual void render() = 0;
	
	double getDepth(int x, int y);
	void setDepth(int x, int y, double depth);

	Image createDepthImage();
};

#endif