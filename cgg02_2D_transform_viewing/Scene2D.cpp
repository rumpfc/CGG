#include "Scene2D.h"
#include "TransformMatrix2D.h"
#include "Rectangle2D.h"
#include "Ellipse2D.h"

#include <iostream>


Scene2D::Scene2D()
{
	initialize();
}


Scene2D::~Scene2D()
{
	for (Object2D* object : objects_)
	{
		if (object)
			delete object;
	}
}


void Scene2D::initialize()
{
	Object2D* obj = new Rectangle2D(3.0, 4.0);
	obj->setLineColor(0x0000ff);
	obj->setFillColor(0xff00ff);
	obj->rotate(30);
	objects_.push_back(obj);

	obj = new Rectangle2D(5.0, 2.0);
	obj->setLineColor(0x000000);
	obj->setFillColor(0x00ffff);
	objects_.push_back(obj);

	obj = new Ellipse2D(4.0, 2.0);
	obj->rotate(-20);
	obj->translate( 3.0, -3.0);
	obj->setFillColor(0xffff00);
	objects_.push_back(obj);
}


void Scene2D::transform(TransformMatrix2D& matrix)
{
	std::cout << "Transform objects" << std::endl;
	for (Object2D* obj : objects_)
	{
		obj->transform(matrix);
	}
}


Object2D* Scene2D::getObject(int index)
{
	if (index < 0 || static_cast<size_t>(index) > objects_.size())
		return NULL;

	return objects_[index];
}


unsigned int Scene2D::getObjectSize()
{
	return objects_.size();
}
