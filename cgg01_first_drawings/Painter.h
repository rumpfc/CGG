#ifndef PAINTER_H_
#define PAINTER_H_

#include "Color.h"

class Renderer;
class Vector2D;

class Painter
{
private:
	Renderer* renderer_;
	Color lineColor_;
	Color fillColor_;
	bool fill_;

public:
	Painter(Renderer* renderer);
	virtual ~Painter();

	void setLineColor(Color& color);
	void setLineColor(float r, float g, float b);
	void setLineColor(int colorcode);

	void setFillColor(Color& color);
	void setFillColor(float r, float g, float b);
	void setFillColor(int colorcode);

	void setFiller(bool fill);

	// drawing a line with Bresenham's algorithm
	void drawLine(int x1, int y1, int x2, int y2);
	void drawLine(Vector2D& p1, Vector2D& p2);

	void drawRect(int x, int y, int width, int height);
};

#endif