#include "Image.h"
#include "Color.h"
#include "Mathtools.h"

#include <fstream>
#include <iostream>


Image::Image(int width, int height) : width_(width), height_(height)
{
	int pixels = width_*height_;
	pixel_ = new Color[pixels];
}


Image::Image(int width, int height, Color* buffer) : width_(width), height_(height)
{
	int pixels = width_*height_;
	pixel_ = new Color[pixels];

	for (int p = 0; p < pixels; p++)
	{
		pixel_[p].setColor(buffer[p]);
	}
}


Image::Image(const Image& src) : width_(src.width_), height_(src.height_)
{
	int pixels = width_*height_;
	pixel_ = new Color[pixels];

	for (int p = 0; p < pixels; p++)
	{
		pixel_[p].setColor(src.pixel_[p]);
	}
}


Image::~Image()
{
	// delete pixels
	delete[] pixel_;
}


Color& Image::at(const int row, const int col)
{
	return pixel_[Mathtools::pixelIndex(width_, row, col)];
}


void Image::save(const std::string& filename)
{
	std::ofstream of;
	std::string name = filename + ".ppm";

	of.open(name.c_str(), std::ios::binary);

	if (!of.is_open())
	{
		std::cout << "Error: Couldn't create file " << filename << ".ppm\n";
		return;
	}

	/*
	PPM binary format:
	P6
	<width string> <height string>
	<max color value string>
	<RGB binary color code>
	*/

	of << "P6\n";
	of << width_ << " " << height_ << "\n";
	of << "255\n";

	int pixels = width_ * height_;
	for (int p = 0; p < pixels; p++)
	{
		// write 8Bit color value instead of float value
		of << pixel_[p].getRed8B() << pixel_[p].getGreen8B() << pixel_[p].getBlue8B();
	}

	of.close();
}