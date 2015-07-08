#include "Rectangle2D.h"


Rectangle2D::Rectangle2D() : width_(10.0), height_(5.0), Object2D()
{
	initialize();
}


Rectangle2D::Rectangle2D(double width, double height) :
	width_(width), height_(height), Object2D()
{
	initialize();
}


Rectangle2D::~Rectangle2D()
{
}


/*
P00-------------P01
 |               |
 |               |
 |               |
P03-------------P02
*/

void Rectangle2D::initialize()
{
	points_.push_back(new Vector2D(-width_ / 2.0,  height_ / 2.0));        // P00
	points_.push_back(new Vector2D( width_ / 2.0,  height_ / 2.0));        // P01
	points_.push_back(new Vector2D( width_ / 2.0, -height_ / 2.0));        // P02
	points_.push_back(new Vector2D(-width_ / 2.0, -height_ / 2.0));        // P03

	lines_.push_back(new Line2D(points_[0], points_[1], &lineColor_));     // P00 -> P01
	lines_.push_back(new Line2D(points_[1], points_[2], &lineColor_));     // P01 -> P02
	lines_.push_back(new Line2D(points_[2], points_[3], &lineColor_));     // P02 -> P03
	lines_.push_back(new Line2D(points_[3], points_[0], &lineColor_));     // P03 -> P00

	triangles_.push_back(new Surface2D(points_[0], points_[1], points_[3], &fillColor_));
	triangles_.push_back(new Surface2D(points_[1], points_[2], points_[3], &fillColor_));
}