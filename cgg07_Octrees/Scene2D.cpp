#include "Scene2D.h"
#include "TransformMatrix2D.h"
#include "Rectangle2D.h"
#include "Ellipse2D.h"
#include "Texture.h"


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

	for (std::pair<std::string, Texture*> it : textures_)
	{
		Texture* tex = it.second;
		if (tex)
			delete tex;
	}
}


void Scene2D::initialize()
{
	// initialize textures
	Image img;
	img.load("eiffel.ppm");

	Texture* tex = new Texture(img);
	textures_["eiffel"] = tex;

	img.load("liberty.ppm");

	tex = new Texture(img);
	textures_["liberty"] = tex;

	// initialize objects
	Object2D* obj = 0;

	// First transform, then link texture
	obj = new Rectangle2D(3.0, 4.0);
	obj->rotate(30);
	obj->translate(-4.0, 2.0);
	obj->linkTexture(textures_["eiffel"]);
	objects_.push_back(obj);

	// First link texture, then transform
	obj = new Rectangle2D(3.0, 4.0);
	obj->linkTexture(textures_["eiffel"]);
	obj->rotate(30);
	obj->translate(4.0, 2.0);
	objects_.push_back(obj);

	// in an ellipse, cause we can xD
	obj = new Ellipse2D(4, 3);
	obj->linkTexture(textures_["liberty"]);
	obj->translate(0.0, -2.5);
	obj->rotate(-9);
	objects_.push_back(obj);
}


void Scene2D::transform(TransformMatrix2D& matrix)
{
	for (Object2D* obj : objects_)
	{
		obj->transform(matrix);
	}
}


Object2D* Scene2D::getObject(int index)
{
	if (index < 0 || static_cast<size_t>(index) > objects_.size())
		return 0;

	return objects_[index];
}


unsigned int Scene2D::getObjectSize()
{
	return objects_.size();
}
