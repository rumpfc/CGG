#include "Material.h"
#include "Object3D.h"


Material::Material(Object3D* obj) : obj_(obj)
{
}


Material::~Material()
{
}


void Material::setColor(Color& color)
{
	color_.setColor(color);
	obj_->updateColor();
}


void Material::setColor(float r, float g, float b)
{
	color_.setColor(r, g, b);
	obj_->updateColor();
}


void Material::setColor(int colorcode)
{
	color_.setColor(colorcode);
	obj_->updateColor();
}


Color Material::getColor()
{
	return color_;
}
