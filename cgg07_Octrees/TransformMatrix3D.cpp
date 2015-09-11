#include "TransformMatrix3D.h"
#include "Mathtools.h"

TransformMatrix3D::TransformMatrix3D()
{
	unitMatrix();
}


TransformMatrix3D::TransformMatrix3D(const TransformMatrix3D &src)
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			k_[r][c] = src.k_[r][c];
		}
	}
}


TransformMatrix3D::~TransformMatrix3D()
{
}


double& TransformMatrix3D::at(const int row, const int col)
{
	return k_[row][col];
}


// determinate

double TransformMatrix3D::det()
{
	double result = 0.0;
	const int size = 4;

	// sum first

	for (int c = 0; c < size; c++)
	{
		double product = 1.0;

		for (int r = 0; r < size; r++)
		{
			product *= k_[r][(r + c) % size];
		}

		result += product;
	}

	// now substract

	for (int c = 0; c < size; c++)
	{
		double product = 1.0;

		for (int r = 0; r < size; r++)
		{
			product *= k_[r][((size - 1) - r + c) % size];
		}

		result -= product;
	}

	return result;
}


// inverse

void TransformMatrix3D::inverse()
{
	TransformMatrix3D result;
	double totalDet = this->det();

	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			TransformMatrix3D temp = this->cofactor(r, c);
			double det = temp.det();
			result.at(r, c) = det / totalDet;
		}
	}

	result.transpose();

	*this = result;
}

// transpose

void TransformMatrix3D::transpose()
{
	// no need to go to last row, the row before is the last to consider
	for (int r = 0; r < 3; r++)
	{
		for (int c = r + 1; c < 4; c++)
		{
			std::swap(k_[r][c], k_[c][r]);
		}
	}
}

// cofactor of matrix at row/col

TransformMatrix3D TransformMatrix3D::cofactor(int row, int col)
{
	TransformMatrix3D result(*this);
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (r == row || c == col)
				result.at(r, c) = static_cast<double>(r == row && c == col);
		}
	}
	return result;
}


// matrix builder

void TransformMatrix3D::buildMatrixFromVectors(Vector3D& r0, Vector3D& r1, Vector3D& r2)
{
	unitMatrix();

	k_[0][0] = r0.getX();
	k_[0][1] = r0.getY();
	k_[0][2] = r0.getZ();

	k_[1][0] = r1.getX();
	k_[1][1] = r1.getY();
	k_[1][2] = r1.getZ();

	k_[2][0] = r2.getX();
	k_[2][1] = r2.getY();
	k_[2][2] = r2.getZ();
}


/* unit matrix initialization
//
//  /  1   0   0   0  \
//  |  0   1   0   0  |
//  |  0   0   1   0  |
//  \  0   0   0   1  /
*/

void TransformMatrix3D::unitMatrix()
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			k_[r][c] = (r == c);
		}
	}
}


/* translation matrix
//
//  /  1   0   0  tx  \
//  |  0   1   0  ty  |
//  |  0   0   1  tz  |
//  \  0   0   0   1  /
*/

void TransformMatrix3D::translate(const double tx, const double ty, const double tz)
{
	unitMatrix();

	k_[0][3] = tx;
	k_[1][3] = ty;
	k_[2][3] = tz;
}


/* scale matrix
//
//  / sx   0   0   0  \
//  |  0  sy   0   0  |
//  |  0   0  sz   0  |
//  \  0   0   0   1  /
*/

void TransformMatrix3D::scale(const double sx, const double sy, const double sz)
{
	unitMatrix();

	k_[0][0] = sx;
	k_[1][1] = sy;
	k_[2][2] = sz;
}


/* Z rotation matrix
//
//  /  cos(t)   -sin(t)      0         0  \
//  |  sin(t)    cos(t)      0         0  |
//  |    0         0         1         0  |
//  \    0         0         0         1  /
*/

void TransformMatrix3D::rotateAroundZ(const double theta)
{
	unitMatrix();

	double c = Mathtools::COS(theta);
	double s = Mathtools::SIN(theta);

	k_[0][0] = c;
	k_[0][1] = -s;
	k_[1][0] = s;
	k_[1][1] = c;
}


/* X rotation matrix
//
//  /    1         0         0         0  \
//  |    0       cos(t)   -sin(t)      0  |
//  |    0       sin(t)    cos(t)      0  |
//  \    0         0         0         1  /
*/

void TransformMatrix3D::rotateAroundX(const double theta)
{
	unitMatrix();

	double c = Mathtools::COS(theta);
	double s = Mathtools::SIN(theta);

	k_[1][1] = c;
	k_[1][2] = -s;
	k_[2][1] = s;
	k_[2][2] = c;
}


/* Y rotation matrix
//
//  /  cos(t)      0       sin(t)      0  \
//  |    0         1         0         0  |
//  | -sin(t)      0       cos(t)      0  |
//  \    0         0         0         1  /
*/

void TransformMatrix3D::rotateAroundY(const double theta)
{
	unitMatrix();

	double c = Mathtools::COS(theta);
	double s = Mathtools::SIN(theta);

	k_[0][0] = c;
	k_[0][2] = s;
	k_[2][0] = -s;
	k_[2][2] = c;
}


// projection matrix

void TransformMatrix3D::orthogonal(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)
{
	unitMatrix();

	k_[0][0] = 2.0 / (xmax - xmin);
	k_[1][1] = 2.0 / (ymax - ymin);
	k_[2][2] = 2.0 / (zmax - zmin);

	k_[0][3] = -(xmax + xmin) / (xmax - xmin);
	k_[1][3] = -(ymax + ymin) / (ymax - ymin);
	k_[2][3] = -(zmax + zmin) / (zmax - zmin);
}


void TransformMatrix3D::perspective(double fov, double aspect, double near, double far)
{
	unitMatrix();

	double t = Mathtools::TAN(fov / 2.0);

	k_[0][0] = 1.0 / (aspect*t);
	k_[1][1] = 1.0 / t;
	k_[2][2] = (far + near) / (far - near);
	k_[2][3] = -(2 * far*near) / (far - near);

	k_[3][2] = 1;
	k_[3][3] = 0;
}


void TransformMatrix3D::screen(int width, int height)
{
	unitMatrix();

	k_[0][0] = static_cast<double>(width) / 2.0;
	k_[0][3] = k_[0][0];

	k_[1][1] = -static_cast<double>(height) / 2.0;
	k_[1][3] = -k_[1][1];

	k_[2][2] = 0.5;
	k_[2][3] = 0.5;
}


// operator overloading -------------------------------------------------------

TransformMatrix3D operator*(const TransformMatrix3D &M1, const TransformMatrix3D &M2)
{
	TransformMatrix3D result;

	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			double pre = 0.0;
			for (int t = 0; t < 4; t++)
			{
				pre += M1.k_[r][t] * M2.k_[t][c];
			}
			result.k_[r][c] = pre;
		}
	}

	return result;
}


Vector3D operator*(const TransformMatrix3D &M, Vector3D &v)
{
	double x = M.k_[0][0] * v.getX() + M.k_[0][1] * v.getY() + M.k_[0][2] * v.getZ() + M.k_[0][3] * v.getW();
	double y = M.k_[1][0] * v.getX() + M.k_[1][1] * v.getY() + M.k_[1][2] * v.getZ() + M.k_[1][3] * v.getW();
	double z = M.k_[2][0] * v.getX() + M.k_[2][1] * v.getY() + M.k_[2][2] * v.getZ() + M.k_[2][3] * v.getW();
	double w = M.k_[3][0] * v.getX() + M.k_[3][1] * v.getY() + M.k_[3][2] * v.getZ() + M.k_[3][3] * v.getW();

	return Vector3D(x, y, z, w);
}


void TransformMatrix3D::operator=(const TransformMatrix3D& src)
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			k_[r][c] = src.k_[r][c];
		}
	}
}