#include "Renderer3DRaycasting.h"
#include "Color.h"
#include "Scene3D.h"
#include "Mathtools.h"
#include "Ray.h"
#include "Object3D.h"
#include "Shader.h"

#include <iostream>


Renderer3DRaycasting::Renderer3DRaycasting() : Renderer3D()
{
}


Renderer3DRaycasting::Renderer3DRaycasting(Camera3D& camera) : Renderer3D(camera)
{
}


Renderer3DRaycasting::Renderer3DRaycasting(const Renderer3DRaycasting& src)
{
}


Renderer3DRaycasting::~Renderer3DRaycasting()
{
}


Color Renderer3DRaycasting::raycasting(Ray& ray, double* dist)
{
	const int objectSize = scene_->getObjectSize();

	Surface3D* surface = NULL;

	for (int i = 0; i < objectSize; i++)
	{
		Surface3D* temp = NULL;
		Object3D* obj = scene_->getObject(i);
		temp = obj->intersect(ray, dist);

		if (temp)
			surface = temp;
	}

	if (surface == NULL)
	{
		return backgroundColor_;
	}
	
	Vector3D P = ray.getPoint(*dist);
	return Shader::phong(P, surface, scene_->getLightList());
}


void Renderer3DRaycasting::render()
{
	// transform objects in scene
	TransformMatrix3D transform = camera_->getLookatMatrix();
	scene_->transform(transform);

	// create the viewplane
	double aspect = static_cast<double>(width_) / static_cast<double>(height_);
	
	double topEdge = camera_->getNearPlane() * Mathtools::TAN(camera_->getFov() / 2.0);
	double leftEdge = -topEdge * aspect;

	double step_x = 2.0*(-leftEdge) / static_cast<double>(width_);
	double step_y = 2.0*topEdge / static_cast<double>(height_);

	// shoot through every

	for (int y = 0; y < height_; y++)
	{
		for (int x = 0; x < width_; x++)
		{
			// prepare ray
			double px = leftEdge + step_x / 2.0 + static_cast<int>(x) * step_x;
			double py = topEdge - step_y / 2.0 - static_cast<int>(y) * step_y;
			double pz = camera_->getNearPlane();

			Vector3D start(0.0, 0.0, 0.0);
			Vector3D dir(px, py, pz);
			dir.normalize();

			Ray ray(start, dir);

			// set max distance
			double dist = camera_->getMaxDepth();

			// all set, shoot ray and get a color
			Color color = raycasting(ray, &dist);

			colorPixel(x, y, color);
			setDepth(x, y, dist);
		}
		std::cout << "\rRendering...\t" << static_cast<float>((y+1) * 100) / static_cast<float>(height_) << "%\t\t";
	}
	std::cout << std::endl;
}