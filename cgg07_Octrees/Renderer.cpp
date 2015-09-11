#include "Renderer.h"
#include "Color.h"
#include "Image.h"
#include "Mathtools.h"

#include <iostream>


Renderer::Renderer() : buffer_(0), width_(640), height_(480)
{
	initBuffer();
}

Renderer::Renderer(const int width, const int height) : buffer_(0), width_(std::abs(width)), height_(std::abs(height))
{
	initBuffer();
}


Renderer::~Renderer()
{
	delete[] buffer_;
}

void Renderer::setBackgroundColor(Color& color)
{
	backgroundColor_.setColor(color);

	for (int i = 0; i < width_*height_; i++)
	{
		buffer_[i].setColor(color);
	}
}


void Renderer::setBackgroundColor(float r, float g, float b)
{
	backgroundColor_.setColor(r, g, b);

	for (int i = 0; i < width_*height_; i++)
	{
		buffer_[i].setColor(r, g, b);
	}
}


void Renderer::setBackgroundColor(int colorcode)
{
	backgroundColor_.setColor(colorcode);

	for (int i = 0; i < width_*height_; i++)
	{
		buffer_[i].setColor(colorcode);
	}
}


void Renderer::initBuffer()
{
	if (buffer_)
		delete[] buffer_;

	buffer_ = new Color[width_*height_];
}


void Renderer::colorPixel(int x, int y, Color color)
{
	if (x < 0 || x >= width_ || y < 0 || y >= height_)
		return;

	getColor(x, y)->setColor(color);
}


Color* Renderer::getColor(int x, int y)
{
	if (x < 0 || x >= width_ || y < 0 || y >= height_)
		return 0;

	return &buffer_[Mathtools::pixelIndex(width_, y, x)];
}


Image Renderer::createImage()
{
	return Image(width_, height_, buffer_);
}