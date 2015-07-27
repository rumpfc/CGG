#include "Scene3D.h"
#include "TransformMatrix3D.h"
#include "Cube3D.h"
#include "Sphere3D.h"
#include "Texture.h"


Scene3D::Scene3D()
{
	initialize();
}


Scene3D::~Scene3D()
{
	for (Object3D* object : objects_)
	{
		if (object)
			delete object;
	}

	for (std::pair<std::string, Texture*> it : textures_)
	{
		Texture* tex = it.second;
		if (tex)
			delete tex;
	}
}


void Scene3D::initialize()
{
	// initialize objects
	Object3D* obj = 0;

	obj = new Cube3D(2.0, 3.0, 4.0);
	obj->getMaterial()->setColor(0xff0055);
	obj->rotateY(20.0);
	obj->translate(-3.0, 1.0, 3.0);
	objects_.push_back(obj);

	obj = new Sphere3D(3.0, 50);
	obj->getMaterial()->setColor(0xbbbbcc);
	obj->translate(3.0, 0.0, 1.0);
	objects_.push_back(obj);
}


void Scene3D::transform(TransformMatrix3D& matrix)
{
	for (Object3D* obj : objects_)
	{
		obj->transform(matrix);
	}
}


Object3D* Scene3D::getObject(int index)
{
	if (index < 0 || static_cast<size_t>(index) > objects_.size())
		return 0;

	return objects_[index];
}


unsigned int Scene3D::getObjectSize()
{
	return objects_.size();
}


std::vector<Surface3D*> Scene3D::getTriangleList()
{
	std::vector<Surface3D*> finalList;

	for (Object3D* obj : objects_)
	{
		std::vector<Surface3D*> triangleList = obj->getTriangleList();
		finalList.insert(finalList.end(), triangleList.begin(), triangleList.end());
	}

	return finalList;
}