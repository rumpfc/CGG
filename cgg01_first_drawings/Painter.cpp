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

	int x, y, t, dx, dy, incx, incy, pdx, pdy, ddx, ddy, es, el, err;

	/* Entfernung in beiden Dimensionen berechnen */
	dx = x2 - x1;
	dy = y2 - y1;

	/* Vorzeichen des Inkrements bestimmen */
	incx = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
	incy = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;;
	if (dx<0) dx = -dx;
	if (dy<0) dy = -dy;

	/* feststellen, welche Entfernung größer ist */
	if (dx>dy)
	{
		/* x ist schnelle Richtung */
		pdx = incx; pdy = 0;    /* pd. ist Parallelschritt */
		ddx = incx; ddy = incy; /* dd. ist Diagonalschritt */
		es = dy;   el = dx;   /* Fehlerschritte schnell, langsam */
	}
	else
	{
		/* y ist schnelle Richtung */
		pdx = 0;    pdy = incy; /* pd. ist Parallelschritt */
		ddx = incx; ddy = incy; /* dd. ist Diagonalschritt */
		es = dx;   el = dy;   /* Fehlerschritte schnell, langsam */
	}

	/* Initialisierungen vor Schleifenbeginn */
	x = x1;
	y = y1;
	err = el / 2;
	renderer_->colorPixel(x, y, lineColor_);

	/* Pixel berechnen */
	for (t = 0; t < el; ++t) /* t zaehlt die Pixel, el ist auch Anzahl */
	{
		/* Aktualisierung Fehlerterm */
		err -= es;
		if (err < 0)
		{
			/* Fehlerterm wieder positiv (>=0) machen */
			err += el;
			/* Schritt in langsame Richtung, Diagonalschritt */
			x += ddx;
			y += ddy;
		}
		else
		{
			/* Schritt in schnelle Richtung, Parallelschritt */
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