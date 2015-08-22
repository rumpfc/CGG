#ifndef SCENE2D_H_
#define SCENE2D_H_

#include <vector>
#include <map>

class TransformMatrix2D;
class Object2D;
class Texture;

/*
Scene2D contains a list of Object2Ds and Textures
We can transform each object according to a given TransformMatrix2D
*/

class Scene2D
{
private:
	std::vector<Object2D*> objects_;
	std::map<std::string, Texture*> textures_;

	// initialize scene ( = create)
	void initialize();
public:
	Scene2D();
	virtual ~Scene2D();

	// transform scene
	void transform(TransformMatrix2D& matrix);

	// get object
	Object2D* getObject(int index);
	unsigned int getObjectSize();
};

#endif
