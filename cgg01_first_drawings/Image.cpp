#include "Image.h"
#include "Color.h"
#include "Mathtools.h"

#include <fstream>
#include <iostream>


Image::Image(int width, int height) : width_(width), height_(height)
{
	pixel_ = new Color*[height_];

	for (int row = 0; row < height_; row++)
	{
		pixel_[row] = new Color[width_];
	}
}


Image::Image(int width, int height, Color* buffer) : width_(width), height_(height)
{
	pixel_ = new Color*[height_];

	for (int row = 0; row < height_; row++)
	{
		pixel_[row] = new Color[width_];

		for (int col = 0; col < width_; col++)
		{
			pixel_[row][col].setColor(buffer[Mathtools::pixelIndex(width_, row, col)]);
		}
	}
}


Image::Image(const Image& src) : width_(src.width_), height_(src.height_)
{
	pixel_ = new Color*[height_];

	for (int row = 0; row < height_; row++)
	{
		pixel_[row] = new Color[width_];

		for (int col = 0; col < width_; col++)
		{
			pixel_[row][col].setColor(src.pixel_[row][col]);
		}
	}
}


Image::~Image()
{
	// delete coloms at each row
	for (int row = 0; row < height_; row++)
	{
		delete[] pixel_[row];
	}

	// delete rows
	delete[] pixel_;
}


Color& Image::at(const int row, const int col)
{
	return pixel_[row][col];
}


void Image::save(const std::string& filename)
{
	std::ofstream of;

	of.open(filename + ".ppm", std::ios::binary);

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

	for (int row = 0; row < height_; row++)
	{
		for (int col = 0; col < width_; col++)
		{
			// write 8Bit color value instead of float value
			of << at(row, col).getRed8B() << at(row, col).getGreen8B() << at(row, col).getBlue8B();
		}
	}

	of.close();
}