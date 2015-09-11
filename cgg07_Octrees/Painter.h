#ifndef PAINTER_H_
#define PAINTER_H_

#include "Color.h"

class Renderer;
class Vector2D;
class Object2D;
class Line2D;
class Triangle;

class Painter
{
private:
	Renderer* renderer_;
	Color lineColor_;
	Color fillColor_;
	bool fill_;

	// method which draws lines with an color input
	// Bresenham's algorithm
	void bresenham(int x1, int y1, int x2, int y2, Color color);
	
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

	// drawing a line
	void drawLine(int x1, int y1, int x2, int y2);
	void drawLine(Vector2D& p1, Vector2D& p2);
	void drawLine(Line2D& line);

	// drawing a rectangle
	void drawRect(int x, int y, int width, int height);
	void drawRect(Vector2D& topleft, Vector2D& bottomright);

	// draw an ellipse
	void drawEllipse(int mx, int my, int rx, int ry);

};

#endif