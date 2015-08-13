#ifndef CAMERA3D_H_
#define CAMERA3D_H_

#include "Vector3D.h"
#include "TransformMatrix3D.h"

/*
Camera with settings for 3D viewing

 - orthogonal mode with x, y and z borders
 - perspective mode with fov, aspect, far and near

 - orthogonal mode can also use fov and aspect if wished
*/

class Camera3D
{
private:
	// camera parameters
	Vector3D center_;
	Vector3D lookat_;
	Vector3D lookup_;

	// is camera in orthogonal mode and shall fov be used
	/// true  = orthogonal
	/// false = perspective
	bool orthogonal_;
	bool useFov_;

	// screen size, also used for aspect calculation
	int sWidth_;
	int sHeight_;

	// viewport width and height for orthogonal if fov_ not used
	double vWidth_;
	double vHeight_;

	// far and near positions
	double near_;
	double far_;

	// field of vision in degree for perspective and maybe for orthogonal
	double fov_;

public:
	Camera3D();
	Camera3D(const Camera3D& src);
	virtual ~Camera3D();

	void setScreenSize(int width, int height);
	void setCameraParameters(double xc, double yc, double zc, double xl, double yl, double zl, double xu = 0.0, double yu = 1.0, double zu = 1.0);
	void setCenter(double x, double y, double z);
	void setLookat(double x, double y, double z);
	void setLookUp(double x, double y, double z);

	// sets parameters for orthogonal
	void setOrthogonal(double width, double height, double near, double far);
	void setOrthoFov(double fov);

	// sets parameters for perspective
	void setPerspective(double fov, double near, double far);

	void setPerspectiveMode();
	void setOrthogonalMode(bool useFov = false);
	
	// copy all settings from existing camera
	void copyCameraSettings(const Camera3D& camera);

	int getScreenWidth();
	int getScreenHeight();

	Vector3D getCenter();

	double getMaxDepth();
	double getNearPlane();

	double getFov();

	TransformMatrix3D getLookatMatrix();
	TransformMatrix3D getProjectionMatrix();
	TransformMatrix3D getScreenMatrix();
};

#endif