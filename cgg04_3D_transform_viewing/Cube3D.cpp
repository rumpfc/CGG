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

	// top
	triangles_.push_back(new Surface3D(points_[0], points_[1], points_[2]));
	triangles_.push_back(new Surface3D(points_[0], points_[2], points_[3]));

	// bottom
	triangles_.push_back(new Surface3D(points_[4], points_[6], points_[5]));
	triangles_.push_back(new Surface3D(points_[4], points_[7], points_[6]));

	// front
	triangles_.push_back(new Surface3D(points_[0], points_[3], points_[4]));
	triangles_.push_back(new Surface3D(points_[3], points_[7], points_[4]));

	// back
	triangles_.push_back(new Surface3D(points_[1], points_[5], points_[2]));
	triangles_.push_back(new Surface3D(points_[5], points_[6], points_[2]));

	// left
	triangles_.push_back(new Surface3D(points_[4], points_[5], points_[0]));
	triangles_.push_back(new Surface3D(points_[5], points_[1], points_[0]));

	// right
	triangles_.push_back(new Surface3D(points_[3], points_[6], points_[7]));
	triangles_.push_back(new Surface3D(points_[3], points_[2], points_[6]));
}
