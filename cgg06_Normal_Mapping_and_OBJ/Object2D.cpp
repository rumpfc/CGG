#include "Object2D.h"
#include "Texture.h"
#include "Mathtools.h"


Object2D::Object2D() : line_(true), fill_(false)
{
	lineColor_.setColor(0.0, 0.0, 0.0);   // set to black
	fillColor_.setColor(1.0, 1.0, 1.0);   // set to white
}


Object2D::Object2D(const Object2D& src)
{
}


Object2D::~Object2D()
{
	for (Vector2D *point : points_)
	{
		if (point)
			delete point;
	}

	for (Line2D *line : lines_)
	{
		if (line)
			delete line;
	}

	for (Surface2D *tri : triangles_)
	{
		if (tri)
			delete tri;
	}
}


// update color methods -------------------------------------------------------

void Object2D::updateLineColor()
{
	for (Line2D *line : lines_)
	{
		if (line)
			line->setColor(lineColor_);
	}
}

void Object2D::updateFillColor()
{
	for (Surface2D *tri : triangles_)
	{
		if (tri)
			tri->setColor(fillColor_);
	}
}

// getter methods --------------------------------------------------

Vector2D* Object2D::getPoint(int index)
{
	return points_[index];
}


Line2D* Object2D::getLine(int index)
{
	return lines_[index];
}


Surface2D* Object2D::getTriangle(int index)
{
	return triangles_[index];
}


unsigned int Object2D::getPointSize()
{
	return points_.size();
}


unsigned int Object2D::getLineSize()
{
	return lines_.size();
}


unsigned int Object2D::getTriangleSize()
{
	return triangles_.size();
}


Color Object2D::getLineColor()
{
	return lineColor_;
}


Color Object2D::getFillColor()
{
	return fillColor_;
}

bool Object2D::isLined()
{
	return line_;
}

bool Object2D::isFilled()
{
	return fill_;
}


// setter methods

void Object2D::setLineColor(const Color& color)
{
	lineColor_.setColor(color);
	line_ = true;
	updateLineColor();
}

void Object2D::setLineColor(float red, float green, float blue)
{
	lineColor_.setColor(red, green, blue);
	line_ = true;
	updateLineColor();
}

void Object2D::setLineColor(const int colorcode)
{
	lineColor_.setColor(colorcode);
	line_ = true;
	updateLineColor();
}


void Object2D::setFillColor(const Color& color)
{
	fillColor_.setColor(color);
	fill_ = true;
	updateFillColor();
}

void Object2D::setFillColor(float red, float green, float blue)
{
	fillColor_.setColor(red, green, blue);
	fill_ = true;
	updateFillColor();
}

void Object2D::setFillColor(const int colorcode)
{
	fillColor_.setColor(colorcode);
	fill_ = true;
	updateFillColor();
}

void Object2D::setFill(bool fill)
{
	fill_ = fill;
}


// transformations ------------------------------------------------------------

void Object2D::rotate(const double degree)
{
	TransformMatrix2D rotation;
	rotation.rotate(degree);
	this->transform(rotation);
}

void Object2D::translate(const double tx, const double ty)
{
	TransformMatrix2D translation;
	translation.translate(tx, ty);
	transform(translation);
}

void Object2D::transform(TransformMatrix2D& matrix)
{
	for (Vector2D* point : points_)
	{
		point->setVector(matrix * (*point));
	}
}



void Object2D::linkTexture(Texture* texture)
{
	if (!texture)
	{
		for (Surface2D* triangle : triangles_)
			triangle->linkTexture(0);
		return;
	}

	// define any values for min/max range
	double minX = 0.0, minY = 0.0;
	double maxX = 0.0, maxY = 0.0;

	// get min/max values
	Mathtools::pointsMinMaxValues2D(points_, &minX, &minY, &maxX, &maxY);

	for (Surface2D* triangle : triangles_)
	{
		double x = 0.0, y = 0.0;
		double u = 0.0, v = 0.0;

		// first surface point
		x = triangle->getP0()->getX();
		y = triangle->getP0()->getY();

		u = (x - minX) / (maxX - minX);
		v = (y - minY) / (maxY - minY);

		Vector2D t0(u, v);

		// second surface point
		x = triangle->getP1()->getX();
		y = triangle->getP1()->getY();

		u = (x - minX) / (maxX - minX);
		v = (y - minY) / (maxY - minY);

		Vector2D t1(u, v);

		// third surface point
		x = triangle->getP2()->getX();
		y = triangle->getP2()->getY();

		u = (x - minX) / (maxX - minX);
		v = (y - minY) / (maxY - minY);

		Vector2D t2(u, v);

		triangle->linkTexture(texture);
		triangle->setTextureAnchorPoints(t0, t1, t2);
	}

	fill_ = true;
}