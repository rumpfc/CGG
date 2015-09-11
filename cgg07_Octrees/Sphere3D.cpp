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
	for (int r = 0; r < accuracy_; r++)
	{
		for (int c = 0; c < accuracy_; c++)
		{
			double phi = static_cast<double>(c)* Mathtools::PI * 2.0 / static_cast<double>(accuracy_);
			double theta = static_cast<double>(r)* Mathtools::PI / static_cast<double>(accuracy_);
			points_.push_back(new Vector3D(Mathtools::sphericalDirectionRadian(phi, theta) * radius_));
		}
	}

	for (int i = 0; i < accuracy_; i++)
		points_.push_back(new Vector3D(0.0, -radius_, 0.0));
}


void Sphere3D::initTriangles()
{
	for (int r = 0; r < accuracy_; r++)
	{
		for (int c = 0; c < accuracy_; c++)
		{
			int r0 = r, r1 = r + 1;
			int c0 = c, c1 = (c + 1) % accuracy_;

			// get 4 points
			Vector3D* p00 = points_[Mathtools::pixelIndex(accuracy_, r0, c0)];
			Vector3D* p01 = points_[Mathtools::pixelIndex(accuracy_, r0, c1)];
			Vector3D* p10 = points_[Mathtools::pixelIndex(accuracy_, r1, c0)];
			Vector3D* p11 = points_[Mathtools::pixelIndex(accuracy_, r1, c1)];

			// get 4 normals
			Vector3D n00 = *p00;
			Vector3D n01 = *p01;
			Vector3D n10 = *p10;
			Vector3D n11 = *p11;

			// get 4 texture coordinates
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

			triangle->assignNormalVectorToObjectPoint(p00, n00);
			triangle->assignNormalVectorToObjectPoint(p11, n11);
			triangle->assignNormalVectorToObjectPoint(p10, n10);

			triangles_.push_back(triangle);

			triangle = new Surface3D(p00, p01, p11);
			triangle->setObject(this);

			triangle->assignTexturePointToObjectPoint(p00, t00);
			triangle->assignTexturePointToObjectPoint(p11, t11);
			triangle->assignTexturePointToObjectPoint(p01, t01);

			triangle->assignNormalVectorToObjectPoint(p00, n00);
			triangle->assignNormalVectorToObjectPoint(p11, n11);
			triangle->assignNormalVectorToObjectPoint(p01, n01);

			triangles_.push_back(triangle);
		}
	}

	assignMaterialToSurfaces();
	update();
}
