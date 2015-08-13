#include "Light.h"


Light::Light()
{
	setColor(0xffffff);
	ambient_.setColor(0x000000);

	constantAttenuation_ = 1.0f;
	linearAttenuation_ = 0.0f;
	quadraticAttenuation_ = 0.0f;
}


Light::Light(const Light& src)
{
	position_.setVector(src.position_);

	ambient_.setColor(src.ambient_);
	diffuse_.setColor(src.diffuse_);
	specular_.setColor(src.specular_);

	constantAttenuation_ = src.constantAttenuation_;
	linearAttenuation_ = src.linearAttenuation_;
	quadraticAttenuation_ = src.quadraticAttenuation_;
}


Light::~Light()
{
}


void Light::setPosition(Vector3D& position)
{
	position_.setVector(position);
}

void Light::setPosition(double x, double y, double z)
{
	position_.setVector(x, y, z);
}

void Light::setConstantAttenuation(float constant)
{
	constantAttenuation_ = constant;
}

void Light::setLinearAttenuation(float linear)
{
	linearAttenuation_ = linear;
}

void Light::setQuadraticAttenuation(float quadratic)
{
	quadraticAttenuation_ = quadratic;
}

void Light::setAttenuation(float constant, float linear, float quadratic)
{
	constantAttenuation_ = constant;
	linearAttenuation_ = linear;
	quadraticAttenuation_ = quadratic;
}


void Light::setColor(Color& color)
{
	ambient_.setColor(color);
	diffuse_.setColor(color);
	specular_.setColor(color);
}


void Light::setColor(float r, float g, float b)
{
	ambient_.setColor(r, g, b);
	diffuse_.setColor(r, g, b);
	specular_.setColor(r, g, b);
}


void Light::setColor(int colorcode)
{
	ambient_.setColor(colorcode);
	diffuse_.setColor(colorcode);
	specular_.setColor(colorcode);
}


void Light::setAmbientColor(Color& color)
{
	ambient_.setColor(color);
}


void Light::setAmbientColor(float r, float g, float b)
{
	ambient_.setColor(r, g, b);
}


void Light::setAmbientColor(int colorcode)
{
	ambient_.setColor(colorcode);
}


void Light::setDiffuseColor(Color& color)
{
	diffuse_.setColor(color);
}


void Light::setDiffuseColor(float r, float g, float b)
{
	diffuse_.setColor(r, g, b);
}


void Light::setDiffuseColor(int colorcode)
{
	diffuse_.setColor(colorcode);
}


void Light::setSpecularColor(Color& color)
{
	specular_.setColor(color);
}


void Light::setSpecularColor(float r, float g, float b)
{
	specular_.setColor(r, g, b);
}


void Light::setSpecularColor(int colorcode)
{
	specular_.setColor(colorcode);
}


Color Light::getAmbientColor()
{
	return ambient_;
}

Color Light::getDiffuseColor()
{
	return diffuse_;
}

Color Light::getSpecularColor()
{
	return specular_;
}


float Light::getConstantAttenuation()
{
	return constantAttenuation_;
}

float Light::getLinearAttenuation()
{
	return linearAttenuation_;
}

float Light::getQuadraticAttenuation()
{
	return quadraticAttenuation_;
}

Vector3D Light::getPosition()
{
	return position_;
}


void Light::transform(TransformMatrix3D& matrix)
{
	position_ = matrix * position_;
}