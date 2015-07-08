#ifndef OBJECT2D_H_
#define OBJECT2D_H_

#include "Mathtools.h"
#include "Line2D.h"
#include "Surface2D.h"
#include "Color.h"

#include <vector>

class Texture;

/*
Abstract class for drawable 2D objects
Contains a list of points, triangles (surfaces) and lines

2D Objects can be transformed

Can contain reference pointing to a Texture and assigns texture coordinates
for each point parallel to x- and y-axis, ignoring rotations etc.
*/

class Object2D
{
protected:
	// list of points, lines and triangles
	std::vector<Vector2D*> points_;
	std::vector<Line2D*> lines_;
	std::vector<Surface2D*> triangles_;

	// Texture
	Texture* texture_;

	// boundary and rotation value

	// lineColor_ always needed, we want to draw lines (incl. Polylines)
	// fillColor_ only needed for fillable objects (triangle, rectangle etc.)
	Color lineColor_;
	Color fillColor_;

	bool fill_;
	bool line_;

	// update called when line color or fill color is changed

	void updateLineColor();
	void updateFillColor();

	// no copy constructor allowed

	Object2D(const Object2D& src);

	// abstract method initialize (called in Object2D constructor)
	// override in all derived classes

	virtual void initialize() = 0;

public:
	Object2D();
	virtual ~Object2D();

	// getter methods (no setters for points and lines)

	Vector2D* getPoint(int index);
	Line2D*   getLine(int index);
	Surface2D* getTriangle(int index);

	unsigned int getPointSize();
	unsigned int getLineSize();
	unsigned int getTriangleSize();

	Color getLineColor();
	Color getFillColor();

	bool isFilled();
	bool isLined();

	Texture* getTexture();

	// setter methods

	void setLineColor(const Color& color);
	void setLineColor(float red, float green, float blue);
	void setLineColor(const int colorcode);

	void setFillColor(const Color& color);
	void setFillColor(float red, float green, float blue);
	void setFillColor(const int colorcode);

	void setFill(bool fill);

	// link Texture with this object and set texture coordinates to
	// each surface

	void linkTexture(Texture* texture);

	// transformations
	void rotate(const double degree);
	void translate(const double tx, const double ty);
	void transform(TransformMatrix2D& matrix);

	// abstract query for a point being inside of this object

	bool pointIsInside(Vector2D& point);
};

#endif