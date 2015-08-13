#ifndef MATHTOOLS_H_
#define MATHTOOLS_H_

#include <cmath>
#include <vector>

#include "Vector2D.h"
#include "Vector3D.h"
#include "TransformMatrix2D.h"
#include "TransformMatrix3D.h"

namespace Mathtools
{
	// Direction Vector from start to destination
	Vector2D direction(Vector2D &start, Vector2D &dest);
	Vector3D direction(Vector3D &start, Vector3D &dest);

	// Distance between starting Vector/Point and destination Vector/Point
	double distance(Vector2D &start, Vector2D &dest);
	double distance(Vector3D &start, Vector3D &dest);

	// Dot Product for 2D and 3D
	double dot(Vector2D &v1, Vector2D &v2);
	double dot(Vector3D &v1, Vector3D &v2);

	// Cross Product for 3D
	Vector3D cross(Vector3D &v1, Vector3D &v2);

	// triangle area
	double triangleArea(Vector3D& p0, Vector3D& p1, Vector3D& p2);

	// 2D Transformation Matrix creator
	TransformMatrix2D translate2D(double tx = 0.0, double ty = 0.0);
	TransformMatrix2D scale2D(double sx = 1.0, double sy = 1.0);
	TransformMatrix2D rotate2D(double theta = 0.0);
	TransformMatrix2D mirror2D(bool x_axis = false, bool y_axis = false);

	// 3D Transformation Matrix creator
	TransformMatrix3D translate3D(double tx = 0.0, double ty = 0.0, double tz = 0.0);
	TransformMatrix3D scale3D(double sx = 0.0, double sy = 0.0, double sz = 0.0);

	TransformMatrix3D rotate3DAroundX(double theta = 0.0);
	TransformMatrix3D rotate3DAroundY(double theta = 0.0);
	TransformMatrix3D rotate3DAroundZ(double theta = 0.0);

	// combination of all 3 rotations, multiplying in x-/y-/z-axis
	TransformMatrix3D rotate3D(double theta_x = 0.0, double theta_y = 0.0, double theta_z = 0.0);

	// const values
	static const double PI = acos(-1.0);
	static const double EPSILON = 0.000001;

	// sin, cos and tan (degree mode)
	double SIN(double x);
	double COS(double x);
	double TAN(double x);

	// spherical coordinates
	Vector3D sphericalDirectionRadian(const double phi, const double theta);
	Vector3D sphericalDirectionDegree(const double phi, const double theta);

	// reflect Vector according to normal
	Vector3D reflect(Vector3D& v, Vector3D& normal);

	// integral part of floating point number
	double trunc(double x);

	// fractional part of floating point number (0 <= f < 1
	double fract(double x);

	// Pixel index for Color arrays
	int pixelIndex(int width, int row, int col);

	// min/max range of a set of points (values set in parameter)
	void pointsMinMaxValues2D(std::vector<Vector2D*>& points, double* minX, double* minY, double* maxX, double* maxY);

	// get max from 2 doubles
	double max(double a, double b);
}

#endif