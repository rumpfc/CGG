#include "Renderer2D.h"
#include "Camera2D.h"
#include "Scene2D.h"
#include "Painter.h"
#include "Object2D.h"
#include "Surface2D.h"
#include "Line2D.h"
#include "Mathtools.h"

#include <iostream>

Renderer2D::Renderer2D() : Renderer()
{
	std::cout << "Renderer2D constructor" << std::endl;
	std::cout << "Prepare Camera" << std::endl;

	camera_ = new Camera2D();
	camera_->setScreenSize(width_, height_);

	std::cout << "Prepare scene" << std::endl;

	scene_ = new Scene2D();

	std::cout << "Scene with " << scene_->getObjectSize() << " objects created" << std::endl;
}

Renderer2D::Renderer2D(Camera2D& camera) : Renderer(camera.getScreenWidth(), camera.getScreenHeight())
{
	std::cout << "Renderer2D constructor" << std::endl;
	std::cout << "Prepare Camera" << std::endl;

	camera_ = new Camera2D(camera);

	std::cout << "Prepare scene" << std::endl;

	scene_ = new Scene2D();

	std::cout << "Scene with " << scene_->getObjectSize() << " objects created" << std::endl;
}

Renderer2D::~Renderer2D()
{
	delete camera_;
	delete scene_;
}


void Renderer2D::rasterization(Surface2D* triangle)
{
	// copy triangle points
	Vector3D p0(triangle->getP0()->toVector3D());
	Vector3D p1(triangle->getP1()->toVector3D());
	Vector3D p2(triangle->getP2()->toVector3D());

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
	double dir = Mathtools::cross(v1, v2).getZ();

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
			if ((x >= xl) && (x <= xr))
			{
				colorPixel(static_cast<int>(x), static_cast<int>(y), triangle->getColor(x, y));
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
			if ((x >= xl) && (x <= xr))
			{
				colorPixel(static_cast<int>(x), static_cast<int>(y), triangle->getColor(x, y));
			}

			x = x + 1.0;
		}


		xl = xl + mEdgeL;
		xr = xr + mEdgeR;
	}
}


void Renderer2D::render()
{
	// get Transform Matrix from camera, we need to transform each point before drawing it
	TransformMatrix2D transform = camera_->getTransformMatrix();

	// Painter to draw coordinate and border lines
	Painter painter(this);

	// coordinate lines, so that we have a clue where our points are
	Vector2D center = camera_->getCenter();

	// normally we only have center +/- half of width/height, but a rotated camera view
	// could make our coord lines shorter than expected, therefore we use full width/height

	Vector2D xBegin(center.getX() - camera_->getViewWidth(), 0.0);
	Vector2D xEnd(center.getX() + camera_->getViewWidth(), 0.0);

	Vector2D yBegin(0.0, center.getY() - camera_->getViewHeight());
	Vector2D yEnd(0.0, center.getY() + camera_->getViewHeight());

	Vector2D start = transform * xBegin;
	Vector2D end = transform * xEnd;

	painter.drawLine(start, end);

	start = transform * yBegin;
	end = transform * yEnd;

	painter.drawLine(start, end);

	// x-axis
	for (int x = static_cast<int>(xBegin.getX()); x <= static_cast<int>(xEnd.getX()); x++)
	{
		double sigma = (x % 5) == 0 ? 0.3 : 0.1;
		Vector2D temp1(x, -sigma);
		Vector2D temp2(x,  sigma);

		temp1 = transform * temp1;
		temp2 = transform * temp2;
		painter.drawLine(temp1, temp2);
	}

	// y-axis
	for (int y = static_cast<int>(yBegin.getY()); y <= static_cast<int>(yEnd.getY()); y++)
	{
		double sigma = (y % 5) == 0 ? 0.3 : 0.1;
		Vector2D temp1(-sigma, y);
		Vector2D temp2( sigma, y);

		temp1 = transform * temp1;
		temp2 = transform * temp2;
		painter.drawLine(temp1, temp2);
	}

	// draw objects, first triangles, then border lines

	for (size_t i = 0; i < scene_->getObjectSize(); i++)
	{
		Object2D* obj = scene_->getObject(i);

		if (obj)
		{
			if (obj->isFilled())
			{
				// draw triangles using rasterization
				for (unsigned int index = 0; index < obj->getTriangleSize(); index++)
				{
					Surface2D* triangle = obj->getTriangle(index);
					Vector2D p0 = transform * (*(triangle->getP0()));
					Vector2D p1 = transform * (*(triangle->getP1()));
					Vector2D p2 = transform * (*(triangle->getP2()));

					Color color(triangle->getColor());

					Surface2D transformedTriangle(p0, p1, p2, &color, triangle->getTexture());
					transformedTriangle.setTextureAnchorPoints(triangle->getT0(), triangle->getT1(), triangle->getT2());

					rasterization(&transformedTriangle);
				}
			}
			// draw border lines
			if (obj->isLined())
			{
				// draw border lines
				for (unsigned int index = 0; index < obj->getLineSize(); index++)
				{
					Line2D* line = obj->getLine(index);
					Vector2D p1 = transform * (*(line->getP1()));
					Vector2D p2 = transform * (*(line->getP2()));

					Color color(line->getColor());

					Line2D transformedLine(p1, p2, &color);

					painter.drawLine(transformedLine);
				}
			}
		}
	}
}