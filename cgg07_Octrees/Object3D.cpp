#include "Object3D.h"
#include "Mathtools.h"
#include "Ray.h"
#include "Octree.h"

#include <iostream>
#include <string>

Object3D::Object3D() : texture_(0), octree_(0)
{
	material_ = new Material();
}

Object3D::Object3D(const std::string& id) : texture_(0), octree_(0), id_(id)
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

	if (octree_)
		delete octree_;

	if (material_)
		delete material_;
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
	if (octree_)
		return octree_->intersection(ray, dist);

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


void Object3D::setID(const std::string& id)
{
	id_ = id;
}

std::string Object3D::getID()
{
	return id_;
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

void Object3D::linkNormalMap(Texture* normalMap)
{
	// to be continued
	if (!normalMap)
		return;

	for (Surface3D* triangle : triangles_)
	{
		if (triangle)
			triangle->linkNormalMap(normalMap);
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

	for (Surface3D* tri : triangles_)
	{
		tri->transformNormals(matrix);
	}

	update();
}


void Object3D::update()
{
	if (!octree_)
		return;

	octree_->clear();
	int counter = 0;
	int max = triangles_.size();

	std::cout << id_ << ": Adding " << max << " triangles to Octree...";
	for (Surface3D* tri : triangles_)
	{
		octree_->addSurface(tri);
	}
	std::cout << " finished!" << std::endl;
}


void Object3D::buildOctree()
{
	octree_ = new Octree(this);
	update();
}