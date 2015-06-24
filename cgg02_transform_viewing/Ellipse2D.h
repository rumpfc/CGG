#ifndef ELLIPSE2D_H_
#define ELLIPSE2D_H_

#include "Object2D.h"

class Ellipse2D : public Object2D
{
private:
	double rx_;
	double ry_;

protected:
	virtual void initialize();
public:
	Ellipse2D();
	Ellipse2D(double rx, double ry);
	virtual ~Ellipse2D();
};

#endif