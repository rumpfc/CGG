#include "Renderer3DRasterization.h"
#include "Scene3D.h"
#include "Surface3D.h"
#include "Mathtools.h"

#include <vector>
#include <iostream>

Renderer3DRasterization::Renderer3DRasterization() : Renderer3D()
{
}


Renderer3DRasterization::Renderer3DRasterization(Camera3D& camera) : Renderer3D(camera)
{
}


Renderer3DRasterization::Renderer3DRasterization(const Renderer3DRasterization& src)
{
}


Renderer3DRasterization::~Renderer3DRasterization()
{
}


void Renderer3DRasterization::render()
{
	setMaxDepth(1.0);

	TransformMatrix3D lookat = camera_->getLookatMatrix();
	TransformMatrix3D proj = camera_->getProjectionMatrix();
	TransformMatrix3D screen = camera_->getScreenMatrix();

	TransformMatrix3D transform = screen * proj * lookat;

	std::vector<Surface3D*> list = scene_->getTriangleList();

	std::cout << "Renderer3DRasterization: Found " << list.size() << " triangles" << std::endl;

	int counter = 0;
	int max = list.size();

	for (Surface3D* triangle : list)
	{
		Color color = triangle->getColor();

		// color shading according to Lambert
		// normally we need a light source, but we use camera this time

		Vector3D normal = triangle->getNormal();
		Vector3D center = triangle->getCenter();

		// get direction to camera

		Vector3D d = camera_->getCenter() - center;
		d.normalize();

		double lambert = Mathtools::dot(d, normal);

		color = color * (lambert < 0.0 ? 0.0 : lambert);

		Material material;
		material.setColor(color);

		Vector3D p0 = transform * *(triangle->getP0());
		Vector3D p1 = transform * *(triangle->getP1());
		Vector3D p2 = transform * *(triangle->getP2());

		// in case we used perspective projection: divide by homogeneous coordinate "w"
		p0.homogeneousDivide();
		p1.homogeneousDivide();
		p2.homogeneousDivide();

		
		Surface3D transformedTriangle(p0, p1, p2, &material, triangle->getTexture());
		transformedTriangle.setTextureAnchorPoints(triangle->getT0(), triangle->getT1(), triangle->getT2());

		rasterization(&transformedTriangle);

		std::cout << "\rRendering... Triangle " << ++counter << " of " << max << "\t\t";
	}

	std::cout << std::endl;
}