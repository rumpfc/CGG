#ifndef RENDERER2D_H_
#define RENDERER2D_H_

#include "Renderer.h"

class Camera2D;
class Scene2D;
class Surface2D;

class Renderer2D : public Renderer
{
private:
	// most important elements in our Renderer
	Camera2D* camera_;
	Scene2D* scene_;

	// no copy constructor
	Renderer2D(const Renderer2D& src);

	// the actual drawing algorithm: rasterization
	// no need to use Painter
	void rasterization(Surface2D* triangle);

public:
	Renderer2D();
	Renderer2D(Camera2D& camera);
	virtual ~Renderer2D();

	// override render method
	virtual void render();
};

#endif