#ifndef SCENE3D_H_
#define SCENE3D_H_

#include <vector>
#include <map>

class TransformMatrix3D;
class Object3D;
class Texture;
class Surface3D;
class Light;
class Material;

/*
Scene2D contains a list of

 - Object3D
 - Light sources
 - Textures
 - Materials

We can transform each object according to a given TransformMatrix3D
*/

class Scene3D
{
private:
	std::vector<Object3D*> objects_;
	std::vector<Light*> lights_;
	std::map<std::string, Texture*> textures_;
	std::map<std::string, Material*> materials_;
	

	// initialize scene ( = create)
	void initialize();

	void initObjects();
	void initLights();
	void initTextures();
	void initMaterials();
public:
	Scene3D();
	virtual ~Scene3D();

	// transform scene
	void transform(TransformMatrix3D& matrix);

	// get object
	Object3D* getObject(int index);
	unsigned int getObjectSize();

	Light* getLight(int index);
	unsigned int getLightSize();

	std::vector<Surface3D*> getTriangleList();
	std::vector<Light*> getLightList();
};

#endif