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
class Ray;

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
	std::map<std::string, Object3D*> objects_;
	std::map<std::string, Light*> lights_;
	std::map<std::string, Texture*> textures_;
	std::map<std::string, Material*> materials_;

	// initialize scene ( = create)
	void initialize();

	void initOBJFiles();
	void initObjects();
	void initLights();
	void initTextures();
	void initMaterials();
public:
	Scene3D();
	virtual ~Scene3D();

	// transform scene
	void transform(TransformMatrix3D& matrix);

	// find closest surface at ray
	Surface3D* getClosestSurfaceAtRay(Ray& ray, double* dist);

	// get object
	Object3D* getObject(const std::string& index);
	unsigned int getObjectSize();

	Light* getLight(const  std::string& index);
	unsigned int getLightSize();

	Material* getMaterial(const std::string& key);

	void loadOBJ(const std::string& filename);
	void loadMTL(const std::string& filename);

	void addNewMaterial(std::string& key, Material* material);
	void addNewObject(std::string& key, Object3D* object);

	void buildOctrees();

	std::vector<Surface3D*> getTriangleList();
	std::vector<Light*> getLightList();
	std::vector<Object3D*> getObjectList();
};

#endif