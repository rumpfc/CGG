#include "Renderer3D.h"
#include "Surface3D.h"
#include "Scene3D.h"
#include "Mathtools.h"
#include "Image.h"

#include <iostream>

Renderer3D::Renderer3D() : depthBuffer_(0), Renderer()
{
	std::cout << "Renderer3D: Create Camera" << std::endl;
	camera_ = new Camera3D();

	std::cout << "Renderer3D: initialize depth buffer" << std::endl;
	initDepthBuffer(camera_->getMaxDepth());

	std::cout << "Renderer3D: initialize Scene" << std::endl;
	scene_ = new Scene3D();

	std::cout << "Renderer3D: Scene created with " << scene_->getObjectSize() << " objects" << std::endl;
}


Renderer3D::Renderer3D(Camera3D& camera) : depthBuffer_(0), Renderer(camera.getScreenWidth(), camera.getScreenHeight())
{
	std::cout << "Renderer3D: Create Camera" << std::endl;
	camera_ = new Camera3D(camera);

	std::cout << "Renderer3D: initialize depth buffer" << std::endl;
	initDepthBuffer(camera_->getMaxDepth());

	std::cout << "Renderer3D: initialize Scene" << std::endl;
	scene_ = new Scene3D();

	std::cout << "Renderer3D: Scene created with " << scene_->getObjectSize() << " objects" << std::endl;
}

Renderer3D::~Renderer3D()
{
	delete[] depthBuffer_;
	delete camera_;
	delete scene_;
}


void Renderer3D::initDepthBuffer(double value)
{
	if (depthBuffer_)
		delete[] depthBuffer_;

	depthBuffer_ = new double[width_*height_];

	for (int i = 0; i < width_*height_; i++)
	{
		depthBuffer_[i] = value;
	}
}

double Renderer3D::getDepth(int x, int y)
{
	if (x < 0 || x >= width_ || y < 0 || y >= height_)
		return 0.0;

	return depthBuffer_[Mathtools::pixelIndex(width_, y, x)];
}


void Renderer3D::setDepth(int x, int y, double depth)
{
	if (x < 0 || x >= width_ || y < 0 || y >= height_)
		return;

	depthBuffer_[Mathtools::pixelIndex(width_, y, x)] = depth;
}


void Renderer3D::setMaxDepth(double value)
{
	for (int i = 0; i < width_*height_; i++)
		depthBuffer_[i] = value;
}


Image Renderer3D::createDepthImage()
{
	int size = width_*height_;
	double max = -static_cast<double>(INFINITY);

	for (int i = 0; i < width_*height_; i++)
	{
		if (depthBuffer_[i] > max)
			max = depthBuffer_[i];
	}

	Color* depth = new Color[size];

	for (int i = 0; i < width_*height_; i++)
	{
		float value = static_cast<float>(depthBuffer_[i] / max);
		depth[i].setColor(value, value, value);
	}

	Image img(width_, height_, depth);

	delete[] depth;

	return img;
}

void Renderer3D::rasterization(Surface3D* triangle)
{
	// copy triangle points
	Vector3D p0(*(triangle->getP0()));
	Vector3D p1(*(triangle->getP1()));
	Vector3D p2(*(triangle->getP2()));

	// sort points according to y axis
	if (p0.getY() > p1.getY())
		std::swap(p0, p1);

	if (p0.getY() > p2.getY())
		std::swap(p0, p2);

	if (p1.getY() > p2.getY())
		std::swap(p1, p2);

	// figure out left, right and bottom edge

	Vector3D dl;    // delta left   edge
	Vector3D dr;    // delta right  edge
	Vector3D db;    // delta bottom edge

	Vector3D v1 = p1 - p0;
	Vector3D v2 = p2 - p0;

	// "normal" and "constant is needed for calculating z at (x,y)
	// compare with ray-plane intersection in "Raytracing"
	Vector3D normal = Mathtools::cross(v1, v2);
	double constant = -Mathtools::dot(p0, normal);
	double dir = normal.getZ();

	if (dir < 0.0)
	{
		// pointing left
		dl = p1 - p0;
		dr = p2 - p0;
	}
	else
	{
		// pointing right
		dl = p2 - p0;
		dr = p1 - p0;
	}

	// calculate delta bottom, always p1->p2
	db = p2 - p1;

	// middle difference per y-step
	double ml = dl.getX() / dl.getY();
	double mr = dr.getX() / dr.getY();
	double mb = db.getX() / db.getY();

	// prepare starting points
	double xl, xr, y, mEdgeL, mEdgeR;

	if ((p0.getY() - floor(p0.getY())) <= 0.5)
	{
		// we can include current pixel position
		y = floor(p0.getY()) + 0.5;
	}
	else
	{
		// ignore current pixel and go to next one
		y = ceil(p0.getY()) + 0.5;
	}

	if (dl.getX() != 0.0)
	{
		mEdgeL = ml;
	}
	else
	{
		mEdgeL = 0;
	}

	if (dr.getX() != 0.0)
	{
		mEdgeR = mr;
	}
	else
	{
		mEdgeR = 0;
	}

	xl = (y - p0.getY())*mEdgeL + p0.getX();
	xr = (y - p0.getY())*mEdgeR + p0.getX();

	// start drawing first part
	for (; y < p1.getY(); y = y + 1.0)
	{
		double x;
		if ((xl - floor(xl)) <= 0.5)
		{
			// take current pixel
			x = floor(xl) + 0.5;
		}
		else
		{
			// ignore current pixel
			x = ceil(xl) + 0.5;
		}

		while (x < xr)
		{
			// calculate z like in ray-plane intersection
			// t = - ((N*P) + d) / (N*v)
			// d = -(N*P0) or -(N*P1) or (N*P2) = constant
			//
			// t = - ((N*P) - (N*P0)) / (N*v)
			//
			// P  = (x/y/0)
			// N  = normal
			// p0 = Vector3D p0
			// v  = (0/0/1)
			//
			// z  = P_z + t * v_z = t

			double z = -((normal.getX() * x + normal.getY() * y + constant) / (normal.getZ()));

			if ((x >= xl) && (x <= xr) && (z >= 0.0) && (z < getDepth(static_cast<int>(x),static_cast<int>(y))))
			{
				setDepth(static_cast<int>(x), static_cast<int>(y), z);
				colorPixel(static_cast<int>(x), static_cast<int>(y), triangle->getColor(x, y, z));
			}
			x = x + 1.0;
		}

		xl = xl + mEdgeL;
		xr = xr + mEdgeR;
	}

	// prepare settings for second part

	if ((p1.getY() - floor(p1.getY())) <= 0.5)
	{
		// we can include current pixel position
		y = floor(p1.getY()) + 0.5;
	}
	else
	{
		// ignore current pixel and go to next one
		y = ceil(p1.getY()) + 0.5;
	}

	// next stage depends on direction of triangle
	if (dir < 0.0)
	{
		// looking left
		if (db.getX() != 0.0)
			mEdgeL = mb;
		else
			mEdgeL = 0.0;

		if (dr.getX() != 0.0)
			mEdgeR = mr;
		else
			mEdgeR = 0.0;

		xl = (y - p1.getY())*mEdgeL + p1.getX();
		xr = (y - p0.getY())*mEdgeR + p0.getX();
	}
	else
	{
		// looking right
		if (db.getX() != 0.0)
			mEdgeR = mb;
		else
			mEdgeR = 0.0;

		if (dl.getX() != 0.0)
			mEdgeL = ml;
		else
			mEdgeL = 0.0;

		xl = (y - p0.getY())*mEdgeL + p0.getX();
		xr = (y - p1.getY())*mEdgeR + p1.getX();
	}

	// start drawing second part
	for (; y < p2.getY(); y = y + 1.0)
	{
		double x;
		if ((xl - floor(xl)) <= 0.5)
		{
			// take current pixel
			x = floor(xl) + 0.5;
		}
		else
		{
			// ignore current pixel
			x = ceil(xl) + 0.5;
		}

		while (x < xr)
		{
			// calculate z like in ray-plane intersection
			// t = - ((N*P) + d) / (N*v)
			// d = -(N*P0) or -(N*P1) or (N*P2) = constant
			//
			// t = - ((N*P) - (N*P0)) / (N*v)
			//
			// P  = (x/y/0)
			// N  = normal
			// p0 = Vector3D p0
			// v  = (0/0/1)
			//
			// z  = P_z + t * v_z = t

			double z = -((normal.getX() * x + normal.getY() * y + constant) / (normal.getZ()));

			if ((x >= xl) && (x <= xr) && (z >= 0.0) && (z < getDepth(static_cast<int>(x), static_cast<int>(y))))
			{
				setDepth(static_cast<int>(x), static_cast<int>(y), z);
				colorPixel(static_cast<int>(x), static_cast<int>(y), triangle->getColor(x, y, z));
			}
			x = x + 1.0;
		}


		xl = xl + mEdgeL;
		xr = xr + mEdgeR;
	}
}