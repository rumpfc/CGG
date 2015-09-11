#ifndef OCTREENODE_H_
#define OCTREENODE_H_

#include <vector>

#include "Mathtools.h"

class Surface3D;
class Ray;

/*
An Octree node is an AABB (Axis-Aligned Bounding Box).

Each node has a parent and 8 children. The first 4 children can
If this node is the root node,
parent is NULL (only in class Octree)

A node can store a LIMIT_MAX number of Surface3D. LIMIT_MAX will be ignored if
this node's level_ is equal to LEVEL_MAX, then LIMIT_MAX is ignored

If LIMIT_MAX is reached, limitReached_ will become true and distributes list_'s
content to the 8 child nodes according to their positionings.

A Surface3D can be stored in more than one child node if the size is too large
*/

class OctreeNode
{
private:
	static unsigned int LEVEL_MAX;
	static unsigned int LIMIT_MAX;

	Vector3D size_;
	Vector3D center_;

	Vector3D childCenter_[8];

	unsigned int level_;
	OctreeNode* parent_;
	OctreeNode* child_[8];

	bool limitReached_;
	std::vector<Surface3D*> list_;
public:
	OctreeNode(Vector3D& center, Vector3D& size, unsigned int level, OctreeNode* parent = 0);
	virtual ~OctreeNode();

	Surface3D* intersection(Ray& ray, double *dist);
	void addSurface(Surface3D* surface);

	static void setLevelMax(unsigned int levelMax);
	static void setLimitMax(unsigned int limitMax);
};

#endif