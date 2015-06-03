#include "Painter.h"
#include "Renderer.h"
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


void Painter::drawLine(int x1, int y1, int x2, int y2)
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
	renderer_->colorPixel(x, y, lineColor_);

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
		renderer_->colorPixel(x, y, lineColor_);
	}
}

void Painter::drawLine(Vector2D& p1, Vector2D& p2)
{
	// no need to reinvent the wheel
	this->drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

void Painter::drawRect(int x, int y, int width, int height)
{
	if (!renderer_)
		return;

	// fill color as line color
	Color temp(lineColor_);
	lineColor_.setColor(fillColor_);

	if (fill_)
	{
		// filling a rectangle is like drawing multiple lines in each row
		for (int r = 0; r <= height; r++)
		{
			this->drawLine(x, y + r, x + width, y + r);
		}
	}

	lineColor_.setColor(temp);
	
	this->drawLine(x, y, x + width, y);
	this->drawLine(x+width, y, x + width, y+height);
	this->drawLine(x+width, y+height, x, y+height);
	this->drawLine(x, y+height, x, y);
}