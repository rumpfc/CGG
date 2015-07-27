#include "Sphere3D.h"
#include "Mathtools.h"


Sphere3D::Sphere3D() : radius_(3.0), accuracy_(30)
{
	initialize();
}


Sphere3D::Sphere3D(const double radius, const int accuracy) : radius_(radius), accuracy_(accuracy)
{
	initialize();
}


Sphere3D::Sphere3D(const Sphere3D& src)
{
}


Sphere3D::~Sphere3D()
{
}


void Sphere3D::initialize()
{
	initPoints();
	initTriangles();
}


// spherical coordinates

void Sphere3D::initPoints()
{
	double hSteps = Mathtools::PI * 2.0 / static_cast<double>(accuracy_);  // horizontal
	double vSteps = Mathtools::PI / static_cast<double>(accuracy_);        // vertical

	for (double theta = 0.0; theta < Mathtools::PI; theta += vSteps)
	{
		for (double phi = 0.0; phi < (2 * Mathtools::PI); phi += hSteps)
		{
			points_.push_back(new Vector3D(Mathtools::sphericalDirection(phi, theta) * radius_));
		}
	}
}


void Sphere3D::initTriangles()
{
	for (int r = 0; r < accuracy_-1; r++)
	{
		for (int c = 0; c < accuracy_; c++)
		{
			int index = Mathtools::pixelIndex(accuracy_, r, c);
			int r0 = r, r1 = r + 1;
			int c0 = c, c1 = (c + 1) % accuracy_;

			triangles_.push_back(new Surface3D(points_[Mathtools::pixelIndex(accuracy_, r0, c0)],
				points_[Mathtools::pixelIndex(accuracy_, r1, c1)],
				points_[Mathtools::pixelIndex(accuracy_, r1, c0)]));

			triangles_.push_back(new Surface3D(points_[Mathtools::pixelIndex(accuracy_, r0, c0)],
				points_[Mathtools::pixelIndex(accuracy_, r0, c1)],
				points_[Mathtools::pixelIndex(accuracy_, r1, c1)]));
		}
	}
}