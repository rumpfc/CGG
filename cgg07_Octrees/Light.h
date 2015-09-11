#ifndef LIGHT_H_
#define LIGHT_H_

#include "Vector3D.h"
#include "Color.h"
#include "TransformMatrix3D.h"

class Light
{
private:
	Vector3D position_;

	Color ambient_;
	Color diffuse_;
	Color specular_;

	float constantAttenuation_;
	float linearAttenuation_;
	float quadraticAttenuation_;
public:
	Light();
	Light(const Light& src);
	virtual ~Light();

	// getter and setter for posistion and color types

	void setPosition(Vector3D& position);
	void setPosition(double x, double y, double z);

	void setConstantAttenuation(float constant);
	void setLinearAttenuation(float linear);
	void setQuadraticAttenuation(float quadratic);

	void setAttenuation(float constant, float linear, float quadratic);

	void setColor(Color& color);
	void setColor(float r, float g, float b);
	void setColor(int colorcode);

	void setAmbientColor(Color& color);
	void setAmbientColor(float r, float g, float b);
	void setAmbientColor(int colorcode);

	void setDiffuseColor(Color& color);
	void setDiffuseColor(float r, float g, float b);
	void setDiffuseColor(int colorcode);

	void setSpecularColor(Color& color);
	void setSpecularColor(float r, float g, float b);
	void setSpecularColor(int colorcode);

	Color getAmbientColor();
	Color getDiffuseColor();
	Color getSpecularColor();

	float getConstantAttenuation();
	float getLinearAttenuation();
	float getQuadraticAttenuation();

	Vector3D getPosition();

	// transform position

	void transform(TransformMatrix3D& matrix);
};

#endif