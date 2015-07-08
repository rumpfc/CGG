#ifndef CAMERA2D_H_
#define CAMERA2D_H_

/*
Camera with settings for 2D viewing
creates a TransformMatrix2D which displays each object in screen coordinates
 * double  window size
 * int     screen size
*/

#include "TransformMatrix2D.h"
#include "Vector2D.h"

class Camera2D
{
private:
	// Camera Center
	Vector2D center_;

	// viewport and screen size (width height)
	int sWidth_;
	int sHeight_;
	double vWidth_;
	double vHeight_;

	// Camera rotated in rotate_° degree
	double rotate_;
public:
	Camera2D();
	Camera2D(const Camera2D& src);
	virtual ~Camera2D();

	// settings we need for our transformation matrix
	void setViewport(double width, double height);
	void setCenter(double x, double y);
	void setCenter(Vector2D& center);
	void setScreenSize(int width, int height);
	void setRotation(double theta);

	void copyCameraSettings(const Camera2D& camera);

	int getScreenWidth();
	int getScreenHeight();

	double getViewWidth();
	double getViewHeight();

	Vector2D getCenter();

	TransformMatrix2D getTransformMatrix();
};

#endif
