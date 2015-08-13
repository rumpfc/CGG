#include "Camera3D.h"
#include "Mathtools.h"


Camera3D::Camera3D() : sWidth_(640), sHeight_(480), vWidth_(4.0), vHeight_(3.0),
fov_(60), far_(INFINITY), near_(1.0), orthogonal_(true), useFov_(false)
{
	lookat_.setVector(0.0, 0.0, 1.0);
	lookup_.setVector(0.0, 1.0, 0.0);
}


Camera3D::Camera3D(const Camera3D& src)
{
	copyCameraSettings(src);
}


Camera3D::~Camera3D()
{
}


void Camera3D::setScreenSize(int width, int height)
{
	sWidth_ = width;
	sHeight_ = height;
}

void Camera3D::setCameraParameters(double xc, double yc, double zc, double xl, double yl, double zl, double xu, double yu, double zu)
{
	center_.setVector(xc, yc, zc);
	lookat_.setVector(xl, yl, zl);
	lookup_.setVector(xu, yu, zu);
}

void Camera3D::setCenter(double x, double y, double z)
{
	center_.setVector(x, y, z);
}

void Camera3D::setLookat(double x, double y, double z)
{
	lookat_.setVector(x, y, z);
}

void Camera3D::setLookUp(double x, double y, double z)
{
	lookup_.setVector(x, y, z);
}

// sets parameters for orthogonal
void Camera3D::setOrthogonal(double width, double height, double near, double far)
{
	orthogonal_ = true;
	useFov_ = false;

	vWidth_ = width;
	vHeight_ = height;
	far_ = far;
	near_ = near;
}

void Camera3D::setOrthoFov(double fov)
{
	orthogonal_ = true;
	useFov_ = true;

	fov_ = fov;
}

// sets parameters for perspective
void Camera3D::setPerspective(double fov, double near, double far)
{
	orthogonal_ = false;

	fov_ = fov;
	far_ = far;
	near_ = near;
}

void Camera3D::setPerspectiveMode()
{
	orthogonal_ = false;
}

void Camera3D::setOrthogonalMode(bool useFov)
{
	orthogonal_ = true;
	useFov_ = useFov;
}

int Camera3D::getScreenWidth()
{
	return sWidth_;
}

int Camera3D::getScreenHeight()
{
	return sHeight_;
}

double Camera3D::getMaxDepth()
{
	return far_;
}

double Camera3D::getNearPlane()
{
	return near_;
}

double Camera3D::getFov()
{
	return fov_;
}

Vector3D Camera3D::getCenter()
{
	return center_;
}

// copy all settings from existing camera
void Camera3D::copyCameraSettings(const Camera3D& camera)
{
	center_.setVector(camera.center_);
	lookat_.setVector(camera.lookat_);
	lookup_.setVector(camera.lookup_);

	orthogonal_ = camera.orthogonal_;
	useFov_ = camera.useFov_;

	sWidth_ = camera.sWidth_;
	sHeight_ = camera.sHeight_;

	vWidth_ = camera.vWidth_;
	vHeight_ = camera.vHeight_;

	fov_ = camera.fov_;

	near_ = camera.near_;
	far_ = camera.far_;
}

TransformMatrix3D Camera3D::getLookatMatrix()
{
	TransformMatrix3D view;

	// camera transformation from world space to view space
	Vector3D forward = lookat_ - center_;
	forward.normalize();

	Vector3D right = Mathtools::cross(lookup_, forward);
	right.normalize();

	Vector3D up = Mathtools::cross(forward, right);

	// build matrix

	view.at(0, 0) = right.getX();
	view.at(0, 1) = right.getY();
	view.at(0, 2) = right.getZ();
	view.at(0, 3) = -Mathtools::dot(right, center_);

	view.at(1, 0) = up.getX();
	view.at(1, 1) = up.getY();
	view.at(1, 2) = up.getZ();
	view.at(1, 3) = -Mathtools::dot(up, center_);

	view.at(2, 0) = forward.getX();
	view.at(2, 1) = forward.getY();
	view.at(2, 2) = forward.getZ();
	view.at(2, 3) = -Mathtools::dot(forward, center_);

	return view;
}


TransformMatrix3D Camera3D::getProjectionMatrix()
{
	TransformMatrix3D norm;

	double aspect = static_cast<double>(sWidth_) / static_cast<double>(sHeight_);

	if (orthogonal_)
	{
		double xmax = vWidth_ / 2.0;
		double xmin = -xmax;

		double ymax = vHeight_ / 2.0;
		double ymin = -ymax;

		if (useFov_)
		{
			double t = Mathtools::TAN(fov_ / 2.0);

			xmax = far_ * aspect * t;
			xmin = -xmax;

			ymax = far_ * t;
			ymin = -ymax;
		}

		norm.orthogonal(xmin, xmax, ymin, ymax, near_, far_);
	}
	else
	{
		norm.perspective(fov_, aspect, near_, far_);
	}

	return norm;
}


TransformMatrix3D Camera3D::getScreenMatrix()
{
	TransformMatrix3D screen;

	screen.screen(sWidth_, sHeight_);

	return screen;
}