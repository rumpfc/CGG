#ifndef RECTANGLE2D_H_
#define RECTANGLE2D_H_

#include "Object2D.h"

/*
A rectangle has 2 edges of length "width" and 2 edges of length "height"
they are perpendicular to the anchored edges

initialize creates 4 points and 4 edges
*/

class Rectangle2D : public Object2D
{
private:
	double width_;
	double height_;

protected:
	// override initialize

	virtual void initialize();

public:
	Rectangle2D();
	Rectangle2D(double width, double height);
	virtual ~Rectangle2D();
};

#endif