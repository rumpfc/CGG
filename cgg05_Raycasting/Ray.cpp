#include "Ray.h"


Ray::Ray()
{
	direction_.setVector(0.0, 0.0, 1.0);
}


Ray::Ray(Vector3D& start, Vector3D& direction) : start_(start), direction_(direction)
{
}


Ray::Ray(const Ray& src) : start_(src.start_), direction_(src.direction_)
{
}


Ray::~Ray()
{
}

void Ray::normalize()
{
	direction_.normalize();
}


void Ray::setStart(Vector3D& start)
{
	start_ = start;
}


void Ray::setDirection(Vector3D& direction)
{
	direction_ = direction;
}


Vector3D Ray::getStart()
{
	return start_;
}


Vector3D Ray::getDirection()
{
	return direction_;
}


Vector3D Ray::getPoint(double t)
{
	return start_ + t * direction_;
}