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


// parameter values S and T for a triangle from Point

Vector2D Mathtools::getSAndTFromTriangle(Vector2D& point, Vector2D& p0, Vector2D& p1, Vector2D& p2)
{
	double x = point.getX();
	double y = point.getY();

	Vector2D v1 = p1 - p0;
	Vector2D v2 = p2 - p0;

	double s = (v2.getX() * (y - p0.getY()) - v2.getY() * (x - p0.getX())) / (v2.getX() * v1.getY() - v1.getX() * v2.getY());
	double t = (v1.getX() * (y - p0.getY()) - v1.getY() * (x - p0.getX())) / (v1.getX() * v2.getY() - v2.getX() * v1.getY());

	return Vector2D(s, t);
}

Vector3D Mathtools::barycentricCoordinates(Vector3D& point, Vector3D& p0, Vector3D& p1, Vector3D& p2)
{
	double area = triangleArea(p0, p1, p2);

	double alpha = triangleArea(point, p1, p2) / area;
	double beta = triangleArea(point, p0, p2) / area;
	double gamma = triangleArea(point, p0, p1) / area;

	return Vector3D(alpha, beta, gamma);
}

// reflect --------------------------------------------------------------------

Vector3D Mathtools::reflect(Vector3D& v, Vector3D& normal)
{
	return v - (2 * dot(v, normal) * normal);
}


// AABB tests -----------------------------------------------------------------

bool Mathtools::pointInsideAABB(Vector3D& point, Vector3D& center, Vector3D& size)
{
	Vector3D min = center - size;
	Vector3D max = center + size;

	return point.getX() >= min.getX() && point.getX() <= max.getX() &&
		point.getY() >= min.getY() && point.getY() <= max.getY() &&
		point.getZ() >= min.getZ() && point.getZ() <= max.getZ();
}

bool Mathtools::rayAABBIntersection(Ray& ray, Vector3D& center, Vector3D& size, double maxDist)
{
	return Mathtools::rayAABBIntersection(ray, center, size, &maxDist);
}

bool Mathtools::rayAABBIntersection(Ray& ray, Vector3D& center, Vector3D& size, double *dist)
{
	Vector3D start = ray.getStart();
	Vector3D dir = ray.getDirection();

	// if starting point is inside axis aligned bounding box, the ray goes through it for sure
	if (Mathtools::pointInsideAABB(start, center, size))
	{
		return true;
	}

	Vector3D min = center - size;
	Vector3D max = center + size;
	double t[6];

	// min is used for left, bottom and near plane
	t[0] = (min.getX() - start.getX()) / dir.getX();
	t[1] = (min.getY() - start.getY()) / dir.getY();
	t[2] = (min.getZ() - start.getZ()) / dir.getZ();
	 
	// max is used for right, top and far plane
	t[3] = (max.getX() - start.getX()) / dir.getX();
	t[4] = (max.getY() - start.getY()) / dir.getY();
	t[5] = (max.getZ() - start.getZ()) / dir.getZ();

	/* we have 6 different distance values, and therefore 6 different points
	   along the ray. we need to query from x, y and z just 2 values, 1 of them
	   is equal to to "min"/"max" (i.e. ray(tl) has min.x, y and z in query)
	*/

	Vector3D temp;

	for (int i = 0; i < 6; i++)
	{
		if (t[i] > *dist || t[i] < 0.0)
			continue;

		temp = ray.getPoint(t[i]);
		
		if ((i % 3) == 0)
		{
			// it's left/right, ask for y and z
			if (temp.getY() >= min.getY() && temp.getY() <= max.getY() &&
				temp.getZ() >= min.getZ() && temp.getZ() <= max.getZ())
			{
				*dist = t[i];
				return true;
			}
		}

		if ((i % 3) == 1)
		{
			// it's bottom/top, ask for x and z
			if (temp.getX() >= min.getX() && temp.getX() <= max.getX() &&
				temp.getZ() >= min.getZ() && temp.getZ() <= max.getZ())
			{
				*dist = t[i];
				return true;
			}
		}

		if ((i % 3) == 2)
		{
			// it's near/far, ask for x and y
			if (temp.getX() >= min.getX() && temp.getX() <= max.getX() &&
				temp.getY() >= min.getY() && temp.getY() <= max.getY())
			{
				*dist = t[i];
				return true;
			}
		}
	}

	// we never hit bounding box
	return false;
}

// inspired by Tomas Möller
// also using his definitions
bool Mathtools::triangleInsideAABB(Vector3D& t0, Vector3D& t1, Vector3D& t2, Vector3D& center, Vector3D& size)
{
	// test if a point is inside AABB
	if (Mathtools::pointInsideAABB(t0, center, size))
		return true;

	if (Mathtools::pointInsideAABB(t1, center, size))
		return true;

	if (Mathtools::pointInsideAABB(t2, center, size))
		return true;

	Vector3D v[3];
	Vector3D e[3];
	Vector3D f[3];

	// (v) move triangle so that AABB's center is at zero point
	v[0] = t0 - center;
	v[1] = t1 - center;
	v[2] = t2 - center;

	// (e) define AABB's normals
	e[0].setVector(1, 0, 0);
	e[1].setVector(0, 1, 0);
	e[2].setVector(0, 0, 1);

	// (f) get triangle's 3 edges
	f[0] = v[1] - v[0];
	f[1] = v[2] - v[1];
	f[2] = v[0] - v[2];

	// use the 3 edges (f), form rays and make ray/AABB intersection test
	// at least 1 edge has to hit AABB

	Ray testRay(t0, f[0]);

	if (Mathtools::rayAABBIntersection(testRay, center, size, 1.0))
		return true;

	testRay.setStart(t1);
	testRay.setDirection(f[1]);

	if (Mathtools::rayAABBIntersection(testRay, center, size, 1.0))
		return true;

	testRay.setStart(t2);
	testRay.setDirection(f[2]);

	if (Mathtools::rayAABBIntersection(testRay, center, size, 1.0))
		return true;

	
	// calculate cross product of AABB normal and triangle edge
	// get min and max values
	// calculate "radius" from AABB size
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Vector3D a = Mathtools::cross(e[i], f[j]);

			double p0 = Mathtools::dot(a, v[0]);
			double p1 = Mathtools::dot(a, v[1]);
			double p2 = Mathtools::dot(a, v[2]);

			double min = Mathtools::min(Mathtools::min(p0, p1), p2);
			double max = Mathtools::max(Mathtools::max(p0, p1), p2);

			double x = a.getX() < 0.0 ? -a.getX() : a.getX();
			double y = a.getY() < 0.0 ? -a.getY() : a.getY();
			double z = a.getZ() < 0.0 ? -a.getZ() : a.getZ();

			a.setVector(x, y, z);

			double rad = Mathtools::dot(size, a);
			if (min > rad || max < -rad)
				return false;
		}
	}
	
	return true;
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

// min value from 2 numbers

double Mathtools::min(double a, double b)
{
	return a < b ? a : b;
}