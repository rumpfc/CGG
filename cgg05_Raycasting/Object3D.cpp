#include "Object3D.h"
#include "Mathtools.h"
#include "Ray.h"


Object3D::Object3D() : texture_(0), radius_(0.0)
{
	material_ = new Material();
}


Object3D::Object3D(const Object3D& src)
{
}


Object3D::~Object3D()
{
	for (Vector3D *point : points_)
	{
		if (point)
			delete point;
	}

	for (Surface3D *tri : triangles_)
	{
		if (tri)
			delete tri;
	}
}


void Object3D::assignMaterialToSurfaces()
{
	for (Surface3D *tri : triangles_)
	{
		tri->setMaterial(material_);
	}
}


Surface3D* Object3D::intersect(Ray& ray, double* dist)
{
	// seperating sphere components into b and c

	Vector3D distance = objectCenter_ - ray.getStart();
	Vector3D direction = ray.getDirection();
	direction.normalize(); // just in case
	double l = distance.length();

	double b = Mathtools::dot(distance, direction);
	double c = l * l;

	double temp = b*b - c + radius_*radius_;

	if (temp < 0.0)
		return 0;

	Surface3D* foundSurface = 0;

	for (Surface3D *tri : triangles_)
	{
		double temp = *dist;
		if (tri->intersection(ray, &temp))
		{
			*dist = temp;
			foundSurface = tri;
		}
	}

	return foundSurface;
}


void Object3D::setMaterial(Material* material)
{
	material_->copyMaterial(*material);
}

Vector3D* Object3D::getPoint(int index)
{
	return points_[index];
}


Surface3D* Object3D::getTriangle(int index)
{
	return triangles_[index];
}


unsigned int Object3D::getPointSize()
{
	return points_.size();
}


unsigned int Object3D::getTriangleSize()
{
	return triangles_.size();
}


Material* Object3D::getMaterial()
{
	return material_;
}

std::vector<Surface3D*> Object3D::getTriangleList()
{
	return triangles_;
}


Texture* Object3D::getTexture()
{
	return texture_;
}


void Object3D::linkTexture(Texture* texture)
{
	// to be continued
	if (!texture)
		return;

	for (Surface3D* triangle : triangles_)
	{
		if (triangle)
			triangle->linkTexture(texture);
	}

	// actual linking happens in derived classes
}


void Object3D::rotate(const double rx, const double ry, const double rz)
{
	TransformMatrix3D x, y, z;
	x.rotateAroundX(rx);
	y.rotateAroundY(ry);
	z.rotateAroundZ(rz);

	TransformMatrix3D transform = x * y * z;
	this->transform(transform);
}

void Object3D::rotateX(const double rx)
{
	TransformMatrix3D transform;
	transform.rotateAroundX(rx);
	this->transform(transform);
}

void Object3D::rotateY(const double ry)
{
	TransformMatrix3D transform;
	transform.rotateAroundY(ry);
	this->transform(transform);
}

void Object3D::rotateZ(const double rz)
{
	TransformMatrix3D transform;
	transform.rotateAroundZ(rz);
	this->transform(transform);
}

void Object3D::translate(const double tx, const double ty, const double tz)
{
	TransformMatrix3D transform;
	transform.translate(tx, ty, tz);
	this->transform(transform);
}

void Object3D::scale(const double sx, const double sy, const double sz)
{
	TransformMatrix3D transform;
	transform.scale(sx, sy, sz);
	this->transform(transform);
}


void Object3D::transform(TransformMatrix3D& matrix)
{
	for (Vector3D* point : points_)
	{
		point->setVector(matrix * (*point));
	}

	objectCenter_ = matrix * objectCenter_;
}
