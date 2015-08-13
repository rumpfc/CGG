#include "Painter.h"
#include "Renderer.h"
#include "Object2D.h"
#include "Mathtools.h"


Painter::Painter(Renderer* renderer) : renderer_(renderer), fill_(false)
{
}


Painter::~Painter()
{
}


void Painter::setLineColor(Color& color)
{
	lineColor_.setColor(color);
}

void Painter::setLineColor(float r, float g, float b)
{
	lineColor_.setColor(r, g, b);
}

void Painter::setLineColor(int colorcode)
{
	lineColor_.setColor(colorcode);
}

void Painter::setFillColor(Color& color)
{
	fillColor_.setColor(color);
	fill_ = true;
}

void Painter::setFillColor(float r, float g, float b)
{
	fillColor_.setColor(r, g, b);
	fill_ = true;
}

void Painter::setFillColor(int colorcode)
{
	fillColor_.setColor(colorcode);
	fill_ = true;
}

void Painter::setFiller(bool fill)
{
	fill_ = fill;
}

// line drawing method which uses a color input
// Bresenham's algorithm

void Painter::bresenham(int x1, int y1, int x2, int y2, Color color)
{
	// Do we have a Renderer to draw onto
	if (!renderer_)
		return;

	// source of implementation (german wiki):
	// http://de.wikipedia.org/wiki/Bresenham-Algorithmus#C-Implementierung

	int x, y, t, dx, dy, incx, incy, pdx, pdy, ddx, ddy, ef, es, err;

	/* Distance between x and y */
	dx = x2 - x1;
	dy = y2 - y1;

	/* figure out sign (+/-) */
	incx = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
	incy = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;;
	if (dx<0) dx = -dx;
	if (dy<0) dy = -dy;

	/* which distance (dx or dy) is larger */
	if (dx>dy)
	{
		/* x is faster */
		pdx = incx; pdy = 0;    /* step parallel */
		ddx = incx; ddy = incy; /* step diagonal */
		ef = dy;   es = dx;    /* error for fast steps (es) and slow steps (el) */
	}
	else
	{
		/* y is faster */
		pdx = 0;    pdy = incy; /* step parallel */
		ddx = incx; ddy = incy; /* step diagonal */
		ef = dx;   es = dy;   /* error for fast steps (es) and slow steps (el) */
	}

	/* initialize */
	x = x1;
	y = y1;
	err = es / 2;
	renderer_->colorPixel(x, y, color);

	/* calculate pixel */
	for (t = 0; t < es; ++t) /* t zaehlt die Pixel, el ist auch Anzahl */
	{
		/* update error */
		err -= ef;
		if (err < 0)
		{
			/* make error term positiv (>= 0) */
			err += es;
			/* step diagonal */
			x += ddx;
			y += ddy;
		}
		else
		{
			/* step parallel */
			x += pdx;
			y += pdy;
		}
		renderer_->colorPixel(x, y, color);
	}
}



void Painter::drawLine(int x1, int y1, int x2, int y2)
{
	bresenham(x1, y1, x2, y2, lineColor_);
}

void Painter::drawLine(Vector2D& p1, Vector2D& p2)
{
	// no need to reinvent the wheel
	int x1 = static_cast<int>(p1.getX());
	int y1 = static_cast<int>(p1.getY());
	int x2 = static_cast<int>(p2.getX());
	int y2 = static_cast<int>(p2.getY());

	bresenham(x1, y1, x2, y2, lineColor_);
}

void Painter::drawLine(Line2D& line)
{
	int x1 = static_cast<int>(line.getP1()->getX());
	int y1 = static_cast<int>(line.getP1()->getY());
	int x2 = static_cast<int>(line.getP2()->getX());
	int y2 = static_cast<int>(line.getP2()->getY());

	bresenham(x1, y1, x2, y2, line.getColor());
}

void Painter::drawRect(int x, int y, int width, int height)
{
	if (!renderer_)
		return;

	// fill color as line color

	if (fill_)
	{
		// filling a rectangle is like drawing multiple lines in each row
		for (int r = 0; r <= height; r++)
		{
			bresenham(x, y + r, x + width, y + r, fillColor_);
		}
	}

	// draw border lines
	
	bresenham(x, y, x + width, y, lineColor_);
	bresenham(x + width, y, x + width, y + height, lineColor_);
	bresenham(x + width, y + height, x, y + height, lineColor_);
	bresenham(x, y + height, x, y, lineColor_);
}


void Painter::drawRect(Vector2D& topleft, Vector2D& bottomright)
{
	Vector2D diff = bottomright - topleft;

	int x      = static_cast<int>(topleft.getX());
	int y      = static_cast<int>(topleft.getY());
	int width  = static_cast<int>(diff.getX());
	int height = static_cast<int>(diff.getY());

	drawRect(x, y, width, height);
}


void Painter::drawEllipse(int mx, int my, int rx, int ry)
{
	if (!renderer_)
		return;

	// source of implementation (german wiki):
	// http://de.wikipedia.org/wiki/Bresenham-Algorithmus#Ellipsen

	int dx = 0, dy = ry;
	int rx2 = rx*rx, ry2 = ry*ry;
	int err = ry2 - (2 * ry - 1)*rx2, e2;

	// for our fill color we need to check if the current row (dy) was drawn already
	// first initiation is never drawn

	int lastDy = dy;
	do
	{
		if (fill_ && (dy != lastDy))
		{
			bresenham(mx - dx, my + dy, mx + dx, my + dy, fillColor_);
			bresenham(mx - dx, my - dy, mx + dx, my - dy, fillColor_);
			lastDy = dy;
		}

		renderer_->colorPixel(mx + dx, my + dy, lineColor_);
		renderer_->colorPixel(mx - dx, my + dy, lineColor_);
		renderer_->colorPixel(mx - dx, my - dy, lineColor_);
		renderer_->colorPixel(mx + dx, my - dy, lineColor_);

		e2 = 2 * err;

		if (e2 < (2 * dx + 1)*ry2)
		{
			dx++;
			err += (2 * dx + 1)*ry2;
		}

		if (e2 > -(2 * dy - 1)*rx2)
		{
			dy--;
			err -= (2 * dy - 1)*rx2;
		}
	} while (dy >= 0);

	while (dx++ < rx)
	{
		renderer_->colorPixel(mx + dx, my, lineColor_);
		renderer_->colorPixel(mx - dx, my, lineColor_);
	}
}

