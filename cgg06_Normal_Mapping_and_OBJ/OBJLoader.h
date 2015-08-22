#ifndef OBJLOADER_H_
#define OBJLOADER_H_

#include <fstream>
#include <vector>
#include <map>

class Vector3D;
class Vector2D;
class Scene3D;

enum SurfaceIndex { POINT, TEXTURE, NORMAL };

class OBJLoader
{
private:
	Scene3D* scene_;

	std::vector<Vector3D*> pointList;
	std::vector<Vector2D> texturePointList;
	std::vector<Vector3D> normalVectorList;

	// seperate inputs by whitespace
	// cuts of everything after first '#'
	std::vector<std::string> commandSeperator(const std::string& input, char delim = ' ');
	std::map<SurfaceIndex, int> indexSeperator(const std::string& input, char delim = '/');

public:
	OBJLoader(Scene3D* scene);
	virtual ~OBJLoader();

	void loadOBJ(const std::string& filename);
	void loadMTL(const std::string& filename);
};

#endif