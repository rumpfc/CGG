#include "Material.h"


Material::Material() : shining_(1.0f)
{
	ambient_.setColor(0xdddddd);
	diffuse_.setColor(0xdddddd);
	specular_.setColor(0xdddddd);
}


Material::Material(const Material& src)
{
	copyMaterial(src);
}


Material::~Material()
{
}


void Material::copyMaterial(const Material& material)
{
	ambient_.setColor(material.ambient_);
	diffuse_.setColor(material.diffuse_);
	specular_.setColor(material.specular_);

	shining_ = material.shining_;
}


void Material::setColor(Color& color)
{
	ambient_.setColor(color);
	diffuse_.setColor(color);
	specular_.setColor(color);
}


void Material::setColor(float r, float g, float b)
{
	ambient_.setColor(r, g, b);
	diffuse_.setColor(r, g, b);
	specular_.setColor(r, g, b);
}


void Material::setColor(int colorcode)
{
	ambient_.setColor(colorcode);
	diffuse_.setColor(colorcode);
	specular_.setColor(colorcode);
}


void Material::setAmbientColor(Color& color)
{
	ambient_.setColor(color);
}


void Material::setAmbientColor(float r, float g, float b)
{
	ambient_.setColor(r, g, b);
}


void Material::setAmbientColor(int colorcode)
{
	ambient_.setColor(colorcode);
}


void Material::setDiffuseColor(Color& color)
{
	diffuse_.setColor(color);
}


void Material::setDiffuseColor(float r, float g, float b)
{
	diffuse_.setColor(r, g, b);
}


void Material::setDiffuseColor(int colorcode)
{
	diffuse_.setColor(colorcode);
}


void Material::setSpecularColor(Color& color)
{
	specular_.setColor(color);
}


void Material::setSpecularColor(float r, float g, float b)
{
	specular_.setColor(r, g, b);
}


void Material::setSpecularColor(int colorcode)
{
	specular_.setColor(colorcode);
}


void Material::setShining(float shining)
{
	shining_ = shining < 1.0f ? 1.0f : shining;
}


Color Material::getAmbientColor()
{
	return ambient_;
}

Color Material::getDiffuseColor()
{
	return diffuse_;
}

Color Material::getSpecularColor()
{
	return specular_;
}


float Material::getShining()
{
	return shining_;
}