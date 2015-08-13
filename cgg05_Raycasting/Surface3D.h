#ifndef SURFACE3D_H_
#define SURFACE3D_H_

#include "Material.h"
#include "Vector3D.h"
#include "Vector2D.h"

class Texture;
class Ray;
class Object3D;

/*
A surface has a color and 3 points, forming a triangle
Can optionally set reference to belonging object
*/

class Surface3D
{
private:
	Vector3D* points_[3];
	Vector2D texturePoints_[3];
	Material* material_;
	Texture* texture_;

	Object3D* object_;

public:
	Surface3D(Vector3D& p0, Vector3D& p1, Vector3D& p2, Material* material = 0, Texture* texture = 0);
	Surface3D(Vector3D* p0, Vector3D* p1, Vector3D* p2, Material* material = 0, Texture* texture = 0);
	virtual ~Surface3D();

	// getter methods for fill color (getColor()) and texture color at coordinate x,y,z
	Color getColor();                                // without texture
	Color getColor(Vector3D& point);
	Color getColor(double x, double y, double z);    // with and without textures

	Material* getMaterial();

	Object3D* getObject();

	double getArea();

	Texture* getTexture();

	// used for different shading algorithms
	Vector3D getNormal();
	Vector3D getCenter();

	// is inside query
	bool isInside(Vector3D& point);

	// set Material
	void setMaterial(Material* material);

	void setObject(Object3D* object);

	// intersection with a ray
	// returns true if ray goes through surface and intersection is closer than distance
	// safes new distance
	bool intersection(Ray& ray, double* distance);

	// set texture used if getTextureColor(x,y) is called
	void linkTexture(Texture* texture);

	// normally between 0 and 1, but can be larger for repeated texturing
	void setTextureAnchorPoints(Vector2D& t0, Vector2D& t1, Vector2D& t2);

	// assign a texture point to an point linked to an object point
	// places texture coordinate to correct position
	// does nothing if "point" doesn't exist in this surface
	void assignTexturePointToObjectPoint(Vector3D* point, Vector2D& texturePoint);

	Vector3D* getP0();
	Vector3D* getP1();
	Vector3D* getP2();

	Vector2D& getT0();
	Vector2D& getT1();
	Vector2D& getT2();
};

#endif