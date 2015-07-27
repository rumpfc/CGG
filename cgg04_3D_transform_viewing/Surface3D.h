#ifndef SURFACE3D_H_
#define SURFACE3D_H_

#include "Color.h"
#include "Vector3D.h"
#include "Vector2D.h"

class Texture;

/*
A surface has a color and 3 points, forming a triangle
*/

class Surface3D
{
private:
	Vector3D* points_[3];
	Vector2D texturePoints_[3];
	Color color_;
	Texture* texture_;
public:
	Surface3D(Vector3D& p0, Vector3D& p1, Vector3D& p2, Color* color = 0, Texture* texture = 0);
	Surface3D(Vector3D* p0, Vector3D* p1, Vector3D* p2, Color* color = 0, Texture* texture = 0);
	virtual ~Surface3D();

	// getter methods for fill color (getColor()) and texture color at coordinate x,y,z
	Color getColor();                                // without texture
	Color getColor(double x, double y, double z);    // with and without textures

	double getArea();

	Texture* getTexture();

	// used for different shading algorithms
	Vector3D getNormal();
	Vector3D getCenter();

	// set fill color
	void setColor(Color color);

	// set texture used if getTextureColor(x,y) is called
	void linkTexture(Texture* texture);

	// normally between 0 and 1, but can be larger for repeated texturing
	void setTextureAnchorPoints(Vector2D& t0, Vector2D& t1, Vector2D& t2);

	Vector3D* getP0();
	Vector3D* getP1();
	Vector3D* getP2();

	Vector2D& getT0();
	Vector2D& getT1();
	Vector2D& getT2();
};

#endif