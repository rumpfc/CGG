#include "TransformMatrix2D.h"
#include "Mathtools.h"

TransformMatrix2D::TransformMatrix2D()
{
	unitMatrix();
}


TransformMatrix2D::TransformMatrix2D(const TransformMatrix2D &src)
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			k_[r][c] = src.k_[r][c];
		}
	}
}


TransformMatrix2D::~TransformMatrix2D()
{
}


double& TransformMatrix2D::at(const int row, const int col)
{
	return k_[row][col];
}


// determinant

double TransformMatrix2D::det()
{
	double result = 0.0;
	const int size = 3;

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
			product *= k_[r][((size-1) - r + c) % size];
		}

		result -= product;
	}

	return result;
}


/* unit matrix initialization
//
//  /  1   0   0  \
//  |  0   1   0  |
//  \  0   0   1  /
*/

void TransformMatrix2D::unitMatrix()
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			k_[r][c] = (r == c);
		}
	}
}


/* translation matrix
//
//  /  1   0  tx  \
//  |  0   1  ty  |
//  \  0   0   1  /
*/

void TransformMatrix2D::translate(const double tx, const double ty)
{
	unitMatrix();

	k_[0][2] = tx;
	k_[1][2] = ty;
}


/* scale matrix
//
//  / sx   0   0  \
//  |  0  sy   0  |
//  \  0   0   1  /
*/

void TransformMatrix2D::scale(const double sx, const double sy)
{
	unitMatrix();

	k_[0][0] = sx;
	k_[1][1] = sy;
}


/* rotation matrix
//
//  /  cos(t)   -sin(t)   0  \
//  |  sin(t)    cos(t)   0  |
//  \    0         0      1  /
*/

void TransformMatrix2D::rotate(const double theta)
{
	unitMatrix();

	double c = Mathtools::COS(theta);
	double s = Mathtools::SIN(theta);

	k_[0][0] = c;
	k_[0][1] = -s;
	k_[1][0] = s;
	k_[1][1] = c;
}


// mirror matrix
// along x-axis = inversed y values
// along y-axis = inversed x values

void TransformMatrix2D::mirror(const bool x_axis, const bool y_axis)
{
	unitMatrix();
	
	k_[0][0] = y_axis ? -1.0 : 1.0;
	k_[1][1] = x_axis ? -1.0 : 1.0;
}


// transformation from world to viewport
// returns normalized square from -1 to +1

void TransformMatrix2D::viewport(double xmin, double ymin, double xmax, double ymax)
{
	unitMatrix();
	
	k_[0][0] = 2.0 / (xmax - xmin);
	k_[0][2] = -((xmax + xmin) / (xmax - xmin));

	k_[1][1] = 2.0 / (ymax - ymin);
	k_[1][2] = -((ymax + ymin) / (ymax - ymin));
}

void TransformMatrix2D::screen(int width, int height)
{
	unitMatrix();

	k_[0][0] = static_cast<double>(width) / 2.0;
	k_[0][2] = static_cast<double>(width) / 2.0;

	k_[1][1] = static_cast<double>(-height) / 2.0;
	k_[1][2] = static_cast<double>(height) / 2.0;
}

// operator overloading -------------------------------------------------------

TransformMatrix2D operator*(const TransformMatrix2D &M1, const TransformMatrix2D &M2)
{
	TransformMatrix2D result;

	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			double pre = 0.0;
			for (int t = 0; t < 3; t++)
			{
				pre += M1.k_[r][t] * M2.k_[t][c];
			}
			result.k_[r][c] = pre;
		}
	}

	return result;
}


Vector2D operator*(const TransformMatrix2D &M, Vector2D &v)
{
	double x = M.k_[0][0] * v.getX() + M.k_[0][1] * v.getY() + M.k_[0][2];
	double y = M.k_[1][0] * v.getX() + M.k_[1][1] * v.getY() + M.k_[1][2];

	return Vector2D(x, y);
}