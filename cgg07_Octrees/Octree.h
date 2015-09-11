#ifndef OCTREE_H_
#define OCTREE_H_

class OctreeNode;
class Surface3D;
class Ray;
class Object3D;

/*
An octree consists of 8 sub octrees, stored within an octree node
Octree only saves root node, getting an Object3D to figure out the bouncing values
*/

class Octree
{
private:
	OctreeNode* root_;
	Object3D* object_;

	Octree(const Octree& src);

	void setRootCenterAndSize();
public:
	Octree(Object3D* object);
	virtual ~Octree();

	Surface3D* intersection(Ray& ray, double* dist);
	void addSurface(Surface3D* surface);

	void clear();
};

#endif