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


// Triangle area --------------------------------------------------------------

double Mathtools::triangleArea(Vector3D& p0, Vector3D& p1, Vector3D& p2)
{
	Vector3D v1 = p1 - p0;
	Vector3D v2 = p2 - p0;

	Vector3D temp = cross(v1, v2);

	return 0.5 * temp.length();
}

// sin, cos and tan functions with "theta" degree input -----------------------
// Upper case letters to avoid confusion from cmath library -------------------

double Mathtools::SIN(double x)
{
	return sin(x * PI / 180.0);
}

double Mathtools::COS(double x)
{
	return cos(x * PI / 180.0);
}

double Mathtools::TAN(double x)
{
	return tan(x * PI / 180.0);
}


/* spherical coordinates
/// x = r * sin(theta) * cos(phi)
/// y = r * cos(theta)
/// z = r * sin(theta) * sin(phi)
*/

Vector3D Mathtools::sphericalDirectionRadian(const double phi, const double theta)
{
	double x = cos(phi) * sin(theta);
	double y = cos(theta);
	double z = sin(phi) * sin(theta);

	return Vector3D(x, y, z);
}

Vector3D Mathtools::sphericalDirectionDegree(const double phi, const double theta)
{
	// using Mathtool's cos and sin versions
	double x = COS(phi) * SIN(theta);
	double y = COS(theta);
	double z = SIN(phi) * SIN(theta);

	return Vector3D(x, y, z);
}


// reflect --------------------------------------------------------------------

Vector3D Mathtools::reflect(Vector3D& v, Vector3D& normal)
{
	return v - (2 * dot(v, normal) * normal);
}


// integral and fractional part calculation -----------------------------------

double Mathtools::trunc(double x)
{
	double i;
	modf(x, &i);
	return i;
}

double Mathtools::fract(double x)
{
	double i;
	return modf(x, &i);
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


// pixel index in color arrays

int Mathtools::pixelIndex(int width, int row, int col)
{
	return width * row + col;
}

// min/max of set of points
// return values within parameters as pointers
void Mathtools::pointsMinMaxValues2D(std::vector<Vector2D*>& points, double* minX, double* minY, double* maxX, double* maxY)
{
	*minX = *minY = static_cast<double>(INFINITY);
	*maxX = *maxY = -static_cast<double>(INFINITY);

	for (Vector2D* point : points)
	{
		if (point->getX() < *minX)
			*minX = point->getX();

		if (point->getX() > *maxX)
			*maxX = point->getX();

		if (point->getY() < *minY)
			*minY = point->getY();

		if (point->getY() > *maxY)
			*maxY = point->getY();
	}
}

// max value from 2 numbers

double Mathtools::max(double a, double b)
{
	return a > b ? a : b;
}