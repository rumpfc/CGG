#include "RendererSimpleDrawing.h"
#include "Color.h"
#include "Painter.h"

RendererSimpleDrawing::RendererSimpleDrawing() : Renderer()
{
}


RendererSimpleDrawing::RendererSimpleDrawing(const int width, const int height) : Renderer(width, height)
{
}


RendererSimpleDrawing::~RendererSimpleDrawing()
{
}


// let's draw something

void RendererSimpleDrawing::render()
{
	// create Painter class to draw on "this" Renderer

	Painter painter(this);

	// time to draw
	// TODO: Be creative ;)
	
	// green line
	painter.setLineColor(0x00ff00);
	painter.drawLine(5, 10, 60, 80);

	// red line
	painter.setLineColor(0xff0000);
	painter.drawLine(400, 300, 500, 100);

	// how about some blue ivy
	painter.setLineColor(0x3090c7);
	painter.drawLine(200, 100, 400, 100);

	// green rectangle with black lines
	painter.setLineColor(0x000000);
	painter.setFillColor(0x00ff00);

	painter.drawRect(350, 150, 110, 80);

	// now another rect, but without fill color
	painter.setFiller(false);
	painter.drawRect(350, 250, 110, 80);

	// ellipse
	painter.setFillColor(0xffff00);
	painter.setLineColor(0x000000);
	painter.drawEllipse(100, 300, 50, 80);

	// another ellipse without fill color
	painter.setFiller(false);
	painter.setLineColor(0x0000ff);
	painter.drawEllipse(160, 290, 80, 50);
}