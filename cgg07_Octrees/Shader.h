#ifndef SHADER_H_
#define SHADER_H_

#include <vector>

#include "Color.h"

class Surface3D;
class Light;
class Vector3D;

namespace Shader
{
	Color phong(Vector3D& point, Surface3D* triangle, std::vector<Light*> lights);
}

#endif