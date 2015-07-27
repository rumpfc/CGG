#ifndef OBJECT3D_H_
#define OBJECT3D_H_

#include "Mathtools.h"
#include "Surface3D.h"
#include "Material.h"
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

class Object3D
{
protected:
	// list of points, lines and triangles
	std::vector<Vector3D*> points_;
	std::vector<Surface3D*> triangles_;

	// Texture
	Texture* texture_;

	Material* material_;

	// no copy constructor allowed

	Object3D(const Object3D& src);

	// abstract method initialize (called in Object3D constructor)
	// override in all derived classes

	virtual void initialize() = 0;

public:
	Object3D();
	virtual ~Object3D();

	// getter methods (no setters for points and lines)

	Vector3D* getPoint(int index);
	Surface3D* getTriangle(int index);

	unsigned int getPointSize();
	unsigned int getTriangleSize();

	std::vector<Surface3D*> getTriangleList();

	Material* getMaterial();

	Texture* getTexture();

	// update called from Material if something has changed

	void updateColor();

	// link Texture with this object and set texture coordinates to
	// each surface

	void linkTexture(Texture* texture);

	// transformations
	void rotate(const double rx, const double ry, const double rz);
	void rotateX(const double rx);
	void rotateY(const double ry);
	void rotateZ(const double rz);

	void translate(const double tx, const double ty, const double tz);
	void scale(const double sx, const double sy, const double sz);

	void transform(TransformMatrix3D& matrix);
};

#endif