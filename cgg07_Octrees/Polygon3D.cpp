#include "Polygon3D.h"
#include "Octree.h"


Polygon3D::Polygon3D()
{
}


Polygon3D::~Polygon3D()
{
}


void Polygon3D::initialize()
{
}


void Polygon3D::addPoint(Vector3D* point)
{
	points_.push_back(point);
}


void Polygon3D::addSurface(Surface3D* surface)
{
	triangles_.push_back(surface);
}