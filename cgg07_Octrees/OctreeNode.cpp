#include "OctreeNode.h"
#include "Surface3D.h"

#include <map>
#include <iostream>

unsigned int OctreeNode::LEVEL_MAX = 4;
unsigned int OctreeNode::LIMIT_MAX = 10;

OctreeNode::OctreeNode(Vector3D& center, Vector3D& size, unsigned int level, OctreeNode* parent) :
center_(center), size_(size), level_(level), parent_(parent)
{
	double x = center_.getX();
	double y = center_.getY();
	double z = center_.getZ();

	childCenter_[0].setVector(x - size.getX() / 2.0, y + size.getY() / 2.0, z - size.getZ() / 2.0);
	childCenter_[1].setVector(x + size.getX() / 2.0, y + size.getY() / 2.0, z - size.getZ() / 2.0);
	childCenter_[2].setVector(x - size.getX() / 2.0, y - size.getY() / 2.0, z - size.getZ() / 2.0);
	childCenter_[3].setVector(x + size.getX() / 2.0, y - size.getY() / 2.0, z - size.getZ() / 2.0);
	childCenter_[4].setVector(x - size.getX() / 2.0, y + size.getY() / 2.0, z + size.getZ() / 2.0);
	childCenter_[5].setVector(x + size.getX() / 2.0, y + size.getY() / 2.0, z + size.getZ() / 2.0);
	childCenter_[6].setVector(x - size.getX() / 2.0, y - size.getY() / 2.0, z + size.getZ() / 2.0);
	childCenter_[7].setVector(x + size.getX() / 2.0, y - size.getY() / 2.0, z + size.getZ() / 2.0);

	for (int i = 0; i < 8; i++)
	{
		child_[i] = 0;
	}
}


OctreeNode::~OctreeNode()
{
	for (int i = 0; i < 8; i++)
	{
		if (child_[i])
			delete child_[i];
	}
}


Surface3D* OctreeNode::intersection(Ray& ray, double* dist)
{
	Surface3D* result = 0;
	Vector3D halfSize = size_ / 2.0;

	if (Mathtools::rayAABBIntersection(ray, center_, size_, *dist))
	{
		if (!limitReached_ || level_ == LEVEL_MAX)
		{
			for (Surface3D* surface : list_)
			{
				double temp = *dist;
				if (surface->intersection(ray, &temp))
				{
					result = surface;
					*dist = temp;
				}
			}
		}
		else
		{
			std::multimap<double, int> cubeOrder;

			for (int i = 0; i < 8; i++)
			{
				double tempDist = Mathtools::INF;
				if (child_[i] && Mathtools::rayAABBIntersection(ray, childCenter_[i], halfSize, &tempDist))
				{
					cubeOrder.insert(std::pair<double, unsigned int>(tempDist, i));
				}
			}
			
			for (std::pair<double, int> order : cubeOrder)
			{
				int index = order.second;

				if (child_[index])
				{
					Surface3D* tempResult = child_[index]->intersection(ray, dist);
					if (tempResult)
					{
						result = tempResult;
					}
				}
			}
		}
	}

	return result;
}

void OctreeNode::addSurface(Surface3D* surface)
{
	Vector3D halfSize = size_ / 2.0;

	if (!limitReached_ || level_ == LEVEL_MAX)
	{
		list_.push_back(surface);

		if (list_.size() >= LIMIT_MAX && level_ < LEVEL_MAX)
		{
			limitReached_ = true;
			for (Surface3D* tri : list_)
			{
				// test if "surface" belongs to that sub cube
				Vector3D p0 = *(tri->getP0());
				Vector3D p1 = *(tri->getP1());
				Vector3D p2 = *(tri->getP2());

				for (int i = 0; i < 8; i++)
				{
					if (Mathtools::triangleInsideAABB(p0, p1, p2, childCenter_[i], halfSize))
					{
						if (child_[i] == 0)
							child_[i] = new OctreeNode(childCenter_[i], halfSize, level_ + 1, this);

						child_[i]->addSurface(tri);
					}
				}
			}
			list_.clear();
		}
	}
	else
	{
		// test if "surface" belongs to that sub cube
		Vector3D p0 = *(surface->getP0());
		Vector3D p1 = *(surface->getP1());
		Vector3D p2 = *(surface->getP2());

		for (int i = 0; i < 8; i++)
		{
			if (Mathtools::triangleInsideAABB(p0, p1, p2, childCenter_[i], halfSize))
			{
				if (child_[i] == 0)
					child_[i] = new OctreeNode(childCenter_[i], halfSize, level_ + 1, this);

				child_[i]->addSurface(surface);
			}
		}
	}
}


void OctreeNode::setLevelMax(unsigned int levelMax)
{
	LEVEL_MAX = levelMax;
}


void OctreeNode::setLimitMax(unsigned int limitMax)
{
	LIMIT_MAX = limitMax;
}