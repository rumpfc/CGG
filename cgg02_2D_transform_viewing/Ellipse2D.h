#ifndef ELLIPSE2D_H_
#define ELLIPSE2D_H_

#include "Object2D.h"

/*
An ellipse has 2 different radient values, along x- and y-axis

x = rx * cos(phi)
y = ry * sin(phi)

accuracy determines how many points shall be created (at least 10, default = 100)
*/

class Ellipse2D : public Object2D
{
private:
	int accuracy_;

	double rx_;
	double ry_;

protected:
	virtual void initialize();
public:
	Ellipse2D();
	Ellipse2D(double rx, double ry, int accuracy = 100);
	virtual ~Ellipse2D();
};

#endif