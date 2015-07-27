#ifndef SURFACE2D_H_
#define SURFACE2D_H_

#include "Color.h"
#include "Vector2D.h"

class Texture;

/*
A surface has a color and 3 points, forming a triangle
used to render it for rasterization algorithm
*/

class Surface2D
{
private:
	Vector2D* points_[3];
	Vector2D texturePoints_[3];
	Color color_;
	Texture* texture_;
public:
	Surface2D(Vector2D& p0, Vector2D& p1, Vector2D& p2, Color* color = 0, Texture* texture = 0);
	Surface2D(Vector2D* p0, Vector2D* p1, Vector2D* p2, Color* color = 0, Texture* texture = 0);
	virtual ~Surface2D();

	// getter methods for fill color (getColor()) and texture color at coordinate x,y
	Color getColor();                      // without texture
	Color getColor(double x, double y);    // with and without textures

	Texture* getTexture();

	// set fill color
	void setColor(Color color);

	// set texture used if getTextureColor(x,y) is called
	void linkTexture(Texture* texture);

	// normally between 0 and 1, but can be larger for repeated texturing
	void setTextureAnchorPoints(Vector2D& t0, Vector2D& t1, Vector2D& t2);

	Vector2D* getP0();
	Vector2D* getP1();
	Vector2D* getP2();

	Vector2D& getT0();
	Vector2D& getT1();
	Vector2D& getT2();
};

#endif