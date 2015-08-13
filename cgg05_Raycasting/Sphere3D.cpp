#include "Sphere3D.h"
#include "Mathtools.h"


Sphere3D::Sphere3D() : accuracy_(30)
{
	radius_ = 3.0;
	initialize();
}


Sphere3D::Sphere3D(const double radius, const int accuracy) : accuracy_(accuracy)
{
	radius_ = radius;
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
	for (int r = 0; r <= accuracy_; r++)
	{
		for (int c = 0; c < accuracy_; c++)
		{
			double phi = static_cast<double>(c)* Mathtools::PI * 2.0 / static_cast<double>(accuracy_);
			double theta = static_cast<double>(r)* Mathtools::PI / static_cast<double>(accuracy_);
			points_.push_back(new Vector3D(Mathtools::sphericalDirectionRadian(phi, theta) * radius_));
		}
	}
}


void Sphere3D::initTriangles()
{
	for (int r = 0; r < accuracy_; r++)
	{
		for (int c = 0; c < accuracy_; c++)
		{
			int r0 = r, r1 = r + 1;
			int c0 = c, c1 = (c + 1) % accuracy_;

			Vector3D* p00 = points_[Mathtools::pixelIndex(accuracy_, r0, c0)];
			Vector3D* p01 = points_[Mathtools::pixelIndex(accuracy_, r0, c1)];
			Vector3D* p10 = points_[Mathtools::pixelIndex(accuracy_, r1, c0)];
			Vector3D* p11 = points_[Mathtools::pixelIndex(accuracy_, r1, c1)];

			Vector2D t00(static_cast<double>(c) / static_cast<double>(accuracy_),
				static_cast<double>(accuracy_ - r) / static_cast<double>(accuracy_));
			Vector2D t01(static_cast<double>(c + 1) / static_cast<double>(accuracy_),
				static_cast<double>(accuracy_ - r) / static_cast<double>(accuracy_));
			Vector2D t10(static_cast<double>(c) / static_cast<double>(accuracy_),
				static_cast<double>(accuracy_ - r - 1) / static_cast<double>(accuracy_));
			Vector2D t11(static_cast<double>(c + 1) / static_cast<double>(accuracy_),
				static_cast<double>(accuracy_ - r - 1) / static_cast<double>(accuracy_));

			Surface3D* triangle = new Surface3D(p00, p11, p10);
			triangle->setObject(this);

			triangle->assignTexturePointToObjectPoint(p00, t00);
			triangle->assignTexturePointToObjectPoint(p11, t11);
			triangle->assignTexturePointToObjectPoint(p10, t10);

			triangles_.push_back(triangle);

			triangle = new Surface3D(p00, p01, p11);
			triangle->setObject(this);

			triangle->assignTexturePointToObjectPoint(p00, t00);
			triangle->assignTexturePointToObjectPoint(p11, t11);
			triangle->assignTexturePointToObjectPoint(p01, t01);

			triangles_.push_back(triangle);
		}
	}

	assignMaterialToSurfaces();
}

// for now let's keep it simple
// we will interpolate in another section
Vector3D Sphere3D::getNormal(Vector3D& point)
{
	return (point - objectCenter_) / radius_;
}
