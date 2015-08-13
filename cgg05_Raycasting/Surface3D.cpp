#include "Surface3D.h"
#include "Vector3D.h"
#include "Texture.h"
#include "Mathtools.h"
#include "Ray.h"
#include "Object3D.h"


Surface3D::Surface3D(Vector3D* p0, Vector3D* p1, Vector3D* p2, Material* material, Texture* texture) : material_(material), texture_(texture)
{
	points_[0] = p0;
	points_[1] = p1;
	points_[2] = p2;
}


Surface3D::Surface3D(Vector3D& p0, Vector3D& p1, Vector3D& p2, Material* material, Texture* texture) : Surface3D(&p0, &p1, &p2, material, texture)
{
}


Surface3D::~Surface3D()
{
}


Material* Surface3D::getMaterial()
{
	return material_;
}


Color Surface3D::getColor()
{
	if (material_)
		return material_->getDiffuseColor();

	return Color();
}

// we use barycentric coordinates to determine if point is inside of surface
bool Surface3D::isInside(Vector3D& point)
{
	double area = this->getArea();

	double alpha = Mathtools::triangleArea(point, *points_[1], *points_[2]) / area;
	double beta = Mathtools::triangleArea(point, *points_[0], *points_[2]) / area;
	double gamma = Mathtools::triangleArea(point, *points_[0], *points_[1]) / area;

	double temp = alpha + beta + gamma;

	if (temp > (1.0 - Mathtools::EPSILON) && temp < (1.0 + Mathtools::EPSILON))
		return true;

	return false;
}


double Surface3D::getArea()
{
	return Mathtools::triangleArea(*points_[0], *points_[1], *points_[2]);
}

Color Surface3D::getColor(Vector3D& point)
{
	if (!texture_)
	{
		if (material_)
			return material_->getDiffuseColor();
		else
			return Color();
	}
		

	double area = this->getArea();

	double alpha = Mathtools::triangleArea(point, *points_[1], *points_[2]) / area;
	double beta = Mathtools::triangleArea(point, *points_[0], *points_[2]) / area;
	double gamma = Mathtools::triangleArea(point, *points_[0], *points_[1]) / area;

	double temp = alpha + beta + gamma;

	if (temp < (1.0 - Mathtools::EPSILON) || temp >(1.0 + Mathtools::EPSILON))
	{
		if (material_)
			return material_->getDiffuseColor();
		else
			return Color();
	}

	double s = beta;
	double t = gamma;

	Vector2D v1 = texturePoints_[1] - texturePoints_[0];
	Vector2D v2 = texturePoints_[2] - texturePoints_[0];

	double u = texturePoints_[0].getX() + v1.getX() * s + v2.getX() * t;
	double v = texturePoints_[0].getY() + v1.getY() * s + v2.getY() * t;

	if (!texture_->isRepeatMode() && (u < 0.0 || u > 1.0 || v < 0.0 || v > 1.0))
	{
		if (material_)
			return material_->getDiffuseColor();
		else
			return Color();
	}

	return texture_->getColor(u, v);
}

Color Surface3D::getColor(double x, double y, double z)
{
	Vector3D p(x,y,z);
	return getColor(p);
}


Object3D* Surface3D::getObject()
{
	return object_;
}

// Ray-Triangle-Intersection
// Möller-Trumbore algorithm
// https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
// calculates u and v for triangle parameter and distance from Ray origin

bool Surface3D::intersection(Ray& ray, double* distance)
{
	Vector3D e1 = *points_[1] - *points_[0];
	Vector3D e2 = *points_[2] - *points_[0];

	Vector3D direction = ray.getDirection();
	Vector3D p = Mathtools::cross(direction, e2);
	double det = Mathtools::dot(e1, p);

	// if determinant equal to 0, ray is parallel to surface
	if (det > -Mathtools::EPSILON && det < Mathtools::EPSILON)
		return false;
	
	double inv_det = 1.0 / det;

	Vector3D T = ray.getStart() - *points_[0];
	
	double u = Mathtools::dot(T, p) * inv_det;

	// u must be between 0 and 1 to be inside of triangle
	if (u < 0.0 || u > 1.0)
		return false;

	Vector3D Q = Mathtools::cross(T, e1);

	double v = Mathtools::dot(direction, Q) * inv_det;

	// v must be between 0 and 1, in addition u+v < 1

	if (v < 0.0 || (u + v) > 1.0)
		return false;

	double t = Mathtools::dot(e2, Q) * inv_det;

	// t must be greater than 0 and within max distance
	if (t > Mathtools::EPSILON && t < *distance)
	{
		*distance = t;
		return true;
	}
	
	return false;
}


Texture* Surface3D::getTexture()
{
	return texture_;
}


Vector3D Surface3D::getNormal()
{
	Vector3D v1 = *points_[1] - *points_[0];
	Vector3D v2 = *points_[2] - *points_[0];

	Vector3D normal = Mathtools::cross(v1, v2);
	normal.normalize();

	return normal;
}


Vector3D Surface3D::getCenter()
{
	Vector3D sum = *points_[0] + *points_[1] + *points_[2];
	sum = sum / 3.0;

	return sum;
}


void Surface3D::setMaterial(Material* material)
{
	material_ = material;
}


void Surface3D::setObject(Object3D* object)
{
	object_ = object;
}


// surface points -------------------------------------------------------------
Vector3D* Surface3D::getP0()
{
	return points_[0];
}


Vector3D* Surface3D::getP1()
{
	return points_[1];
}


Vector3D* Surface3D::getP2()
{
	return points_[2];
}

// texture anchor points ------------------------------------------------------
Vector2D& Surface3D::getT0()
{
	return texturePoints_[0];
}


Vector2D& Surface3D::getT1()
{
	return texturePoints_[1];
}


Vector2D& Surface3D::getT2()
{
	return texturePoints_[2];
}


void Surface3D::linkTexture(Texture* texture)
{
	texture_ = texture;
}


void Surface3D::setTextureAnchorPoints(Vector2D& t0, Vector2D& t1, Vector2D& t2)
{
	texturePoints_[0].setVector(t0);
	texturePoints_[1].setVector(t1);
	texturePoints_[2].setVector(t2);
}


void Surface3D::assignTexturePointToObjectPoint(Vector3D* point, Vector2D& texturePoint)
{
	if (point == 0)
		return;

	for (int i = 0; i < 3; i++)
	{
		if (points_[i] == point)
		{
			texturePoints_[i].setVector(texturePoint);
			return;
		}
	}
}