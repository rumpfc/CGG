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


// unit matrix initialization
//
//  /  1   0   0  \
//  |  0   1   0  |
//  \  0   0   1  /

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


// translation matrix
//
//  /  1   0  tx  \
//  |  0   1  ty  |
//  \  0   0   1  /

void TransformMatrix2D::translate(double tx, double ty)
{
	unitMatrix();

	k_[0][2] = tx;
	k_[1][2] = ty;
}


// scale matrix
//
//  / sx   0   0  \
//  |  0  sy   0  |
//  \  0   0   1  /

void TransformMatrix2D::scale(double sx, double sy)
{
	unitMatrix();

	k_[0][0] = sx;
	k_[1][1] = sy;
}


// rotation matrix
//  /  cos(t)   -sin(t)   0  \
//  |  sin(t)    cos(t)   0  |
//  \    0         0      1  /

void TransformMatrix2D::rotate(double theta)
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

void TransformMatrix2D::mirror(bool x_axis, bool y_axis)
{
	unitMatrix();
	
	k_[0][0] = y_axis ? -1.0 : 1.0;
	k_[1][1] = x_axis ? -1.0 : 1.0;
}


TransformMatrix2D operator*(TransformMatrix2D &M1, TransformMatrix2D &M2)
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


Vector2D operator*(TransformMatrix2D &M, Vector2D &v)
{
	double x = M.k_[0][0] * v.getX() + M.k_[0][1] * v.getY() + M.k_[0][2];
	double y = M.k_[1][0] * v.getX() + M.k_[1][1] * v.getY() + M.k_[1][2];

	return Vector2D(x, y);
}