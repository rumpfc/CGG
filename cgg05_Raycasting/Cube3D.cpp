#include "Cube3D.h"


Cube3D::Cube3D() : width_(2.0), height_(2.0), depth_(2.0)
{
	initialize();
}


Cube3D::Cube3D(double width, double height, double depth) :
	width_(width), height_(height), depth_(depth)
{
	initialize();
}


Cube3D::Cube3D(const Cube3D& src)
{
}

Cube3D::~Cube3D()
{
}


/*
   

   P1  +-----------+ P2
      /|          /|
     / |         / |
    /  |        /  |
P0 +-----------+ P3|
   |   |       |   |
   |P5 +-------|---+ P6
   |  /        |  /
   | /         | /
   |/          |/
P4 +-----------+ P7

 -  8 Points
 - 12 Triangles
 - connecting them counter clockwise
*/

void Cube3D::initialize()
{
	double x = width_ / 2.0;
	double y = height_ / 2.0;
	double z = depth_ / 2.0;

	radius_ = sqrt(x*x + y*y + z*z);

	// top, y > 0
	points_.push_back(new Vector3D(-x, y, -z));
	points_.push_back(new Vector3D(-x, y, z));
	points_.push_back(new Vector3D(x, y, z));
	points_.push_back(new Vector3D(x, y, -z));

	// bottom, y < 0
	points_.push_back(new Vector3D(-x, -y, -z));
	points_.push_back(new Vector3D(-x, -y, z));
	points_.push_back(new Vector3D(x, -y, z));
	points_.push_back(new Vector3D(x, -y, -z));

	// we set for each corner point certain texture coordinates

	Vector2D rect[4];

	/* rect
	1---2
	|   |
	|   |
	0---3
	*/

	// top---------------------------------------------------------------------
	triangles_.push_back(new Surface3D(points_[0], points_[1], points_[2]));
	triangles_.push_back(new Surface3D(points_[0], points_[2], points_[3]));

	rect[0].setVector(0.25, 2.0 / 3.0);
	rect[1].setVector(0.25, 1.0);
	rect[2].setVector(0.5, 1.0);
	rect[3].setVector(0.5, 2.0 / 3.0);

	for (int i = 0; i <= 1; i++)
	{
		triangles_[i]->assignTexturePointToObjectPoint(points_[0], rect[0]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[1], rect[1]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[2], rect[2]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[3], rect[3]);

		triangles_[i]->setObject(this);
	}

	// bottom------------------------------------------------------------------
	triangles_.push_back(new Surface3D(points_[4], points_[6], points_[5]));
	triangles_.push_back(new Surface3D(points_[4], points_[7], points_[6]));

	rect[0].setVector(0.25, 0.0);
	rect[1].setVector(0.25, 1.0 / 3.0);
	rect[2].setVector(0.5, 1.0 / 3.0);
	rect[3].setVector(0.5, 0.0);

	for (int i = 2; i <= 3; i++)
	{
		triangles_[i]->assignTexturePointToObjectPoint(points_[5], rect[0]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[4], rect[1]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[7], rect[2]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[6], rect[3]);

		triangles_[i]->setObject(this);
	}

	// front-------------------------------------------------------------------
	triangles_.push_back(new Surface3D(points_[0], points_[3], points_[4]));
	triangles_.push_back(new Surface3D(points_[3], points_[7], points_[4]));

	rect[0].setVector(0.25, 1.0 / 3.0);
	rect[1].setVector(0.25, 2.0 / 3.0);
	rect[2].setVector(0.5, 2.0 / 3.0);
	rect[3].setVector(0.5, 1.0 / 3.0);

	for (int i = 4; i <= 5; i++)
	{
		triangles_[i]->assignTexturePointToObjectPoint(points_[4], rect[0]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[0], rect[1]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[3], rect[2]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[7], rect[3]);

		triangles_[i]->setObject(this);
	}

	// back--------------------------------------------------------------------
	triangles_.push_back(new Surface3D(points_[1], points_[5], points_[2]));
	triangles_.push_back(new Surface3D(points_[5], points_[6], points_[2]));

	rect[0].setVector(0.75, 1.0 / 3.0);
	rect[1].setVector(0.75, 2.0 / 3.0);
	rect[2].setVector(1.0, 2.0 / 3.0);
	rect[3].setVector(1.0, 1.0 / 3.0);

	for (int i = 6; i <= 7; i++)
	{
		triangles_[i]->assignTexturePointToObjectPoint(points_[6], rect[0]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[2], rect[1]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[1], rect[2]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[5], rect[3]);

		triangles_[i]->setObject(this);
	}

	// left--------------------------------------------------------------------
	triangles_.push_back(new Surface3D(points_[4], points_[5], points_[0]));
	triangles_.push_back(new Surface3D(points_[5], points_[1], points_[0]));

	rect[0].setVector(0.0, 1.0 / 3.0);
	rect[1].setVector(0.0, 2.0 / 3.0);
	rect[2].setVector(0.25, 2.0 / 3.0);
	rect[3].setVector(0.25, 1.0 / 3.0);

	for (int i = 8; i <= 9; i++)
	{
		triangles_[i]->assignTexturePointToObjectPoint(points_[5], rect[0]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[1], rect[1]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[0], rect[2]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[4], rect[3]);

		triangles_[i]->setObject(this);
	}

	// right-------------------------------------------------------------------
	triangles_.push_back(new Surface3D(points_[3], points_[6], points_[7]));
	triangles_.push_back(new Surface3D(points_[3], points_[2], points_[6]));

	rect[0].setVector(0.5, 1.0 / 3.0);
	rect[1].setVector(0.5, 2.0 / 3.0);
	rect[2].setVector(0.75, 2.0 / 3.0);
	rect[3].setVector(0.75, 1.0 / 3.0);

	for (int i = 10; i <= 11; i++)
	{
		triangles_[i]->assignTexturePointToObjectPoint(points_[7], rect[0]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[3], rect[1]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[2], rect[2]);
		triangles_[i]->assignTexturePointToObjectPoint(points_[6], rect[3]);

		triangles_[i]->setObject(this);
	}

	assignMaterialToSurfaces();
}

// return normal of first triangle you can find in list
Vector3D Cube3D::getNormal(Vector3D& point)
{
	Vector3D normal;
	for (Surface3D* tri : triangles_)
	{
		if (tri->isInside(point))
			normal = tri->getNormal();
	}

	return normal;
}