#ifndef TRANSFORMMATRIX3D_H_
#define TRANSFORMMATRIX3D_H_

// TransformMatrix3D is a 4x4 Matrix used for 3D transformations
//
// - rotations around x-/y-/z-axis by "theta" degree (not radiant)
// - translation by x/y/z
// - scale by x-/y-/z-times
//
// We ignore M + M and M - M (not needed in our guides)
// We use M * M and M * v (Vector3D)
//
// in Mathtools.h we define methods to directly create one of the
// 3 transformation matrices

class Vector3D;

class TransformMatrix3D
{
private:
	// 4x4 matrix k_[row][column]
	double k_[4][4];

	// unit matrix for initialization a new matrix before setting values
	void unitMatrix();
public:
	TransformMatrix3D();
	TransformMatrix3D(const TransformMatrix3D &src);
	virtual ~TransformMatrix3D();

	// getter and setter (at the same time)
	// usage: M.at(r,c) = number

	double& at(const int row, const int col);

	// transformation matrix types
	// only one possible, but can be combined with multiplication

	void translate(double tx = 0.0, double ty = 0.0, double tz = 0.0);
	void scale(double sx = 1.0, double sy = 1.0, double sz = 1.0);

	// 3 rotations for 3 axis

	void rotateAroundX(double theta = 0.0);
	void rotateAroundY(double theta = 0.0);
	void rotateAroundZ(double theta = 0.0);

	// operator overloading

	friend TransformMatrix3D operator*(TransformMatrix3D &M1, TransformMatrix3D &M2);
	friend Vector3D operator*(TransformMatrix3D &M, Vector3D &v);
};

#endif