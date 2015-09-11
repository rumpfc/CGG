#include "Octree.h"
#include "OctreeNode.h"
#include "Object3D.h"

Octree::Octree(Object3D* object) : object_(object)
{
	setRootCenterAndSize();
}


Octree::Octree(const Octree& src)
{
}


Octree::~Octree()
{
	delete root_;
}


void Octree::setRootCenterAndSize()
{
	if (object_ == 0)
		return;

	unsigned int pointSize = object_->getPointSize();
	double inf = static_cast<double>(INFINITY);
	double eps = Mathtools::EPSILON;

	double xmin = inf, ymin = inf, zmin = inf;
	double xmax = -inf, ymax = -inf, zmax = -inf;

	for (unsigned int i = 0; i < pointSize; i++)
	{
		Vector3D *p = object_->getPoint(i);

		if (p->getX() < xmin)
			xmin = p->getX();

		if (p->getY() < ymin)
			ymin = p->getY();

		if (p->getZ() < zmin)
			zmin = p->getZ();

		if (p->getX() > xmax)
			xmax = p->getX();

		if (p->getY() > ymax)
			ymax = p->getY();

		if (p->getZ() > zmax)
			zmax = p->getZ();
	}

	Vector3D center((xmax + xmin) / 2.0, (ymax + ymin) / 2.0, (zmax + zmin) / 2.0);
	Vector3D size((xmax - xmin) / 2.0 + eps, (ymax - ymin) / 2.0 + eps, (zmax - zmin) / 2.0 + eps);
	root_ = new OctreeNode(center, size, 0);
}

Surface3D* Octree::intersection(Ray& ray, double* dist)
{
	return root_->intersection(ray, dist);
}


void Octree::addSurface(Surface3D* surface)
{
	root_->addSurface(surface);
}


void Octree::clear()
{
	delete root_;
	root_ = 0;
	setRootCenterAndSize();
}
