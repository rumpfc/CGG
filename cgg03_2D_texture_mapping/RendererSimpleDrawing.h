#ifndef RENDERERSIMPLEDRAWING_H_
#define RENDERERSIMPLEDRAWING_H_

#include "Renderer.h"

class RendererSimpleDrawing : public Renderer
{
public:
	RendererSimpleDrawing();
	RendererSimpleDrawing(const int width, const int height);
	virtual ~RendererSimpleDrawing();

	// override render method
	virtual void render();
};

#endif