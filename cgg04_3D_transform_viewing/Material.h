#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Color.h"

class Object3D;

class Material
{
private:
	Object3D* obj_;

	Color color_;
public:
	Material(Object3D* obj);
	virtual ~Material();

	void setColor(Color& color);
	void setColor(float r, float g, float b);
	void setColor(int colorcode);

	Color getColor();
};

#endif