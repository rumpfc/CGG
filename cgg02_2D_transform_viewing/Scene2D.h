#ifndef SCENE2D_H_
#define SCENE2D_H_

#include <vector>

class TransformMatrix2D;
class Object2D;

/*
Scene2D contains a list of Object2Ds
We can transform each object according to a given TransformMatrix2D
*/

class Scene2D
{
private:
	std::vector<Object2D*> objects_;

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
