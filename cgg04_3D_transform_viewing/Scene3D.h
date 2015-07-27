#ifndef SCENE3D_H_
#define SCENE3D_H_

#include <vector>
#include <map>

class TransformMatrix3D;
class Object3D;
class Texture;
class Surface3D;

/*
Scene2D contains a list of Object2Ds and Textures
We can transform each object according to a given TransformMatrix2D
*/

class Scene3D
{
private:
	std::vector<Object3D*> objects_;
	std::map<std::string, Texture*> textures_;

	// initialize scene ( = create)
	void initialize();
public:
	Scene3D();
	virtual ~Scene3D();

	// transform scene
	void transform(TransformMatrix3D& matrix);

	// get object
	Object3D* getObject(int index);
	unsigned int getObjectSize();

	std::vector<Surface3D*> getTriangleList();
};

#endif