#ifndef SURFACE2D_H_
#define SURFACE2D_H_

#include "Color.h"

class Vector2D;

/*
A surface has a color and 3 points, forming a triangle
used to render it for rasterization algorithm
*/

class Surface2D
{
private:
	Vector2D* points_[3];
	Color color_;
public:
	Surface2D(Vector2D& p0, Vector2D& p1, Vector2D& p2, Color* color = 0);
	Surface2D(Vector2D* p0, Vector2D* p1, Vector2D* p2, Color* color = 0);
	virtual ~Surface2D();

	Color& getColor();
	void setColor(Color& color);

	Vector2D* getP0();
	Vector2D* getP1();
	Vector2D* getP2();
};

#endif