#include "Scene3D.h"
#include "TransformMatrix3D.h"
#include "Cube3D.h"
#include "Sphere3D.h"
#include "Texture.h"
#include "Material.h"
#include "Light.h"
#include "OBJLoader.h"

#include <fstream>
#include <iostream>

Scene3D::Scene3D()
{
	initialize();
}


Scene3D::~Scene3D()
{
	for (std::pair<std::string, Object3D*> it : objects_)
	{
		Object3D* object = it.second;

		if (object)
			delete object;
	}

	for (std::pair<std::string, Light*> it : lights_)
	{
		Light* light = it.second;

		if (light)
			delete light;
	}

	for (std::pair<std::string, Texture*> it : textures_)
	{
		Texture* tex = it.second;
		if (tex)
			delete tex;
	}

	for (std::pair<std::string, Material*> it : materials_)
	{
		Material* mat = it.second;
		if (mat)
			delete mat;
	}
}


void Scene3D::initialize()
{
	initOBJFiles();
	// first initialize materials and textures
	initMaterials();
	initTextures();

	// after materials and textures we can initialize objects and lights
	initObjects();
	initLights();
}

void Scene3D::initMaterials()
{
	
	Material* material = 0;

	material = new Material();
	material->setColor(0xdddddd);
	material->setShining(50.0f);
	material->setAmbientColor(0x0f0f0f);
	materials_["metal"] = material;
	
}

void Scene3D::initTextures()
{
	Image img;
	Texture* tex = 0;

	img.load("sources/earth.ppm");
	tex = new Texture(img);
	textures_["earth"] = tex;

	// normal maps
	img.load("sources/earth_normalmap.ppm");
	tex = new Texture(img);
	textures_["earth_normal"] = tex;
	
}

void Scene3D::initObjects()
{
	Object3D* obj = 0;
	
	obj = new Sphere3D(3.0, 50);
	obj->setID("sphere1");
	obj->setMaterial(materials_["metal"]);
	obj->linkTexture(textures_["earth"]);
	obj->linkNormalMap(textures_["earth_normal"]);
	obj->rotateY(-90.0);
	obj->translate(0.0, 0.0, 8.0);
	objects_[obj->getID()] = obj;
}

void Scene3D::initLights()
{
	Light* light = 0;

	light = new Light();
	light->setPosition(9.0, 0.0, -2.0);
	light->setAmbientColor(0.1f, 0.1f, 0.1f);
	lights_["light1"] = light;
}


void Scene3D::initOBJFiles()
{
	//loadOBJ("testfile.obj");
	OBJLoader loader(this);
	loader.loadOBJ("sources/genie_lamp_05.obj");
}


void Scene3D::transform(TransformMatrix3D& matrix)
{

	for (std::pair<std::string,Object3D*> obj : objects_)
	{
		obj.second->transform(matrix);
	}

	for (std::pair<std::string, Light*> light : lights_)
	{
		light.second->transform(matrix);
	}
}


Surface3D* Scene3D::getClosestSurfaceAtRay(Ray& ray, double* dist)
{
	Surface3D* result = 0;

	for (std::pair<std::string, Object3D*> it : objects_)
	{
		Object3D* object = it.second;
		Surface3D* tempResult = object->intersect(ray, dist);

		if (tempResult)
			result = tempResult;
	}

	return result;
}


Object3D* Scene3D::getObject(const std::string& key)
{
	return objects_[key];
}


unsigned int Scene3D::getObjectSize()
{
	return objects_.size();
}


Light* Scene3D::getLight(const std::string& key)
{
	return lights_[key];
}


unsigned int Scene3D::getLightSize()
{
	return lights_.size();
}


std::vector<Surface3D*> Scene3D::getTriangleList()
{
	std::vector<Surface3D*> finalList;

	for (std::pair<std::string, Object3D*> obj : objects_)
	{
		std::vector<Surface3D*> triangleList = obj.second->getTriangleList();
		finalList.insert(finalList.end(), triangleList.begin(), triangleList.end());
	}

	return finalList;
}


std::vector<Light*> Scene3D::getLightList()
{
	std::vector<Light*> list;

	for (std::pair<std::string, Light*> it : lights_)
		list.push_back(it.second);

	return list;
}

std::vector<Object3D*> Scene3D::getObjectList()
{
	std::vector<Object3D*> list;

	for (std::pair<std::string, Object3D*> it : objects_)
		list.push_back(it.second);

	return list;
}

Material* Scene3D::getMaterial(const std::string& key)
{
	return materials_[key];
}


void Scene3D::addNewMaterial(std::string& key, Material* material)
{
	materials_[key] = material;
}

void Scene3D::addNewObject(std::string& key, Object3D* object)
{
	objects_[key] = object;
}

void Scene3D::buildOctrees()
{
	for (std::pair<std::string, Object3D*> object : objects_)
	{
		object.second->buildOctree();
	}
}