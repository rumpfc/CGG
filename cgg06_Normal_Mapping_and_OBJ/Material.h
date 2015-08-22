#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Color.h"

/*
Material contains information we need for shading

 - ambient color
 - diffuse color
 - specular color
 - shining exponent
*/

class Material
{
private:
	Color ambient_;
	Color diffuse_;
	Color specular_;

	float shining_;
public:
	Material();
	Material(const Material& src);
	virtual ~Material();

	void copyMaterial(const Material& material);

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

	void setShining(float shining);

	Color getAmbientColor();
	Color getDiffuseColor();
	Color getSpecularColor();
	float getShining();
};

#endif