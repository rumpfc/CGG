#include "Camera2D.h"


Camera2D::Camera2D() :
	vWidth_(8.0), vHeight_(6.0), sWidth_(640), sHeight_(480), rotate_(0.0)
{
}

Camera2D::Camera2D(const Camera2D& src) :
	vWidth_(src.vWidth_), vHeight_(src.vHeight_), sWidth_(src.sWidth_), sHeight_(src.sHeight_), rotate_(src.rotate_)
{
	center_.setVector(src.center_);
}

Camera2D::~Camera2D()
{
}


void Camera2D::setViewport(double width, double height)
{
	vWidth_ = width;
	vHeight_ = height;
}

void Camera2D::setScreenSize(int width, int height)
{
	sWidth_ = width;
	sHeight_ = height;
}

void Camera2D::setCenter(double x, double y)
{
	center_.setVector(x, y);
}

void Camera2D::setCenter(Vector2D& center)
{
	center_.setVector(center);
}

void Camera2D::setRotation(double theta)
{
	rotate_ = theta;
}

void Camera2D::copyCameraSettings(const Camera2D& camera)
{
	vWidth_ = camera.vWidth_;
	vHeight_ = camera.vHeight_;
	sWidth_ = camera.sWidth_;
	sHeight_ = camera.sHeight_;
	center_.setVector(camera.center_);
}


int Camera2D::getScreenWidth()
{
	return sWidth_;
}

int Camera2D::getScreenHeight()
{
	return sHeight_;
}


double Camera2D::getViewWidth()
{
	return vWidth_;
}

double Camera2D::getViewHeight()
{
	return vHeight_;
}


Vector2D Camera2D::getCenter()
{
	return center_;
}

TransformMatrix2D Camera2D::getTransformMatrix()
{
	TransformMatrix2D viewport, screen, rotation;

	viewport.viewport(
		center_.getX() - vWidth_ / 2.0,
		center_.getY() - vHeight_ / 2.0,
		center_.getX() + vWidth_ / 2.0,
		center_.getY() + vHeight_ / 2.0);

	screen.screen(sWidth_, sHeight_);

	rotation.rotate(rotate_);

	return (screen * viewport * rotation);
}
