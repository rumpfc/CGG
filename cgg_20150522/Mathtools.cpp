#include "Mathtools.h"


// Direction calculation

Vector2D Mathtools::direction(Vector2D &start, Vector2D &dest)
{
	return dest - start;
}

Vector3D Mathtools::direction(Vector3D &start, Vector3D &dest)
{
	return dest - start;
}

// Distance calculation -------------------------------------------------------

double Mathtools::distance(Vector2D &start, Vector2D &dest)
{
	return (dest - start).length();
}

double Mathtools::distance(Vector3D &start, Vector3D &dest)
{
	return (dest - start).length();
}

// Dot-Product ----------------------------------------------------------------

double Mathtools::dot(Vector2D &v1, Vector2D &v2)
{
	return v1 * v2;
}

double Mathtools::dot(Vector3D &v1, Vector3D &v2)
{
	return v1 * v2;
}


// Cross-Proudct --------------------------------------------------------------
 
Vector3D Mathtools::cross(Vector3D &v1, Vector3D &v2)
{
	return v1 % v2;
}


// sin and cos functions with "theta" degree input ----------------------------
// Upper case letters to avoid confusion from cmath library -------------------

double Mathtools::SIN(double x)
{
	return sin(x * PI / 180.0);
}

double Mathtools::COS(double x)
{
	return cos(x * PI / 180.0);
}


// 2D Transformation Matrix ---------------------------------------------------

TransformMatrix2D Mathtools::translate2D(double tx, double ty)
{
	TransformMatrix2D M;
	M.translate(tx, ty);

	return M;
}

TransformMatrix2D Mathtools::scale2D(double sx, double sy)
{
	TransformMatrix2D M;
	M.scale(sx, sy);

	return M;
}

TransformMatrix2D Mathtools::rotate2D(double theta)
{
	TransformMatrix2D M;
	M.rotate(theta);

	return M;
}

TransformMatrix2D Mathtools::mirror2D(bool x_axis, bool y_axis)
{
	TransformMatrix2D M;
	M.mirror(x_axis, y_axis);

	return M;
}


// 3D Transformation Matrix ---------------------------------------------------

TransformMatrix3D Mathtools::translate3D(double tx, double ty, double tz)
{
	TransformMatrix3D M;
	M.translate(tx, ty, tz);

	return M;
}

TransformMatrix3D Mathtools::scale3D(double sx, double sy, double sz)
{
	TransformMatrix3D M;
	M.scale(sx, sy, sz);

	return M;
}

TransformMatrix3D Mathtools::rotate3DAroundX(double theta)
{
	TransformMatrix3D M;
	M.rotateAroundX(theta);

	return M;
}

TransformMatrix3D Mathtools::rotate3DAroundY(double theta)
{
	TransformMatrix3D M;
	M.rotateAroundY(theta);

	return M;
}

TransformMatrix3D Mathtools::rotate3DAroundZ(double theta)
{
	TransformMatrix3D M;
	M.rotateAroundZ(theta);

	return M;
}

TransformMatrix3D Mathtools::rotate3D(double theta_x, double theta_y, double theta_z)
{
	return rotate3DAroundZ(theta_z) * rotate3DAroundY(theta_y) * rotate3DAroundX(theta_x);
}