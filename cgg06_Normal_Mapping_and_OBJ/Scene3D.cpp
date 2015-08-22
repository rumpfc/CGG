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
	for (Object3D* object : objects_)
	{
		if (object)
			delete object;
	}

	for (Light* light : lights_)
	{
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
	obj->setMaterial(materials_["metal"]);
	obj->linkTexture(textures_["earth"]);
	obj->linkNormalMap(textures_["earth_normal"]);
	obj->rotateY(-90.0);
	obj->translate(0.0, 0.0, 8.0);
	objects_.push_back(obj);
}

void Scene3D::initLights()
{
	Light* light = 0;

	light = new Light();
	light->setPosition(9.0, 0.0, -2.0);
	light->setAmbientColor(0.1f, 0.1f, 0.1f);
	lights_.push_back(light);
}


void Scene3D::initOBJFiles()
{
	// loadOBJ("testfile.obj");
	OBJLoader loader(this);
	loader.loadOBJ("genie_lamp_05.obj");
}


void Scene3D::transform(TransformMatrix3D& matrix)
{
	for (Object3D* obj : objects_)
	{
		obj->transform(matrix);
	}

	for (Light* light : lights_)
	{
		light->transform(matrix);
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


Light* Scene3D::getLight(int index)
{
	if (index < 0 || static_cast<size_t>(index) > lights_.size())
		return 0;

	return lights_[index];
}


unsigned int Scene3D::getLightSize()
{
	return lights_.size();
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


std::vector<Light*> Scene3D::getLightList()
{
	return lights_;
}

Material* Scene3D::getMaterial(const std::string& key)
{
	return materials_[key];
}


void Scene3D::addNewMaterial(std::string& key, Material* material)
{
	materials_[key] = material;
}

void Scene3D::addNewObject(Object3D* object)
{
	objects_.push_back(object);
}