#ifndef LINE2D_H_
#define LINE2D_H_

class Vector2D;

#include "Color.h"

/*
A line consists of 2 points
We use references of points and color from existing Object2Ds
A line can never create his own points

Line2D is drawn by Painter::drawLine(Line2D)
*/

class Line2D
{
private:
	Vector2D* points_[2];
	Color color_;
public:
	Line2D(Vector2D* p1, Vector2D* p2, Color* color = 0);
	Line2D(Vector2D& p1, Vector2D& p2, Color* color = 0);
	virtual ~Line2D();

	Color getColor();
	void setColor(Color color);

	Vector2D* getP1();
	Vector2D* getP2();
};

#endif