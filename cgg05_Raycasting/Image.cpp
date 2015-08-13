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

void Image::eat_comment(std::ifstream& f)
{
	// we assume a comment in PNM header is not longer than 1024 characters
	char buffer[1024];
	char p;

	// newline Unix:    "\n"
	// newline Windows: "\r\n"

	while (p = f.peek(), p == '\n' || p == '\r')
	{
		f.get();
	}
	if (p == '#')
	{
		f.getline(buffer, 1023);
	}
}

void Image::initialize(int width, int height)
{
	if (pixel_)
		delete[] pixel_;

	width_ = width;
	height_ = height;
	
	int pixels = width * height;
	pixel_ = new Color[pixels];
}


void Image::copy(Image& src)
{
	width_ = src.width_;
	height_ = src.height_;

	int pixels = width_*height_;
	pixel_ = new Color[pixels];

	for (int p = 0; p < pixels; p++)
	{
		pixel_[p].setColor(src.pixel_[p]);
	}
}


Color Image::getPixel(const int row, const int col)
{
	if (row < 0 || row >= height_ || col < 0 || col >= width_)
		return Color();
	return pixel_[Mathtools::pixelIndex(width_, row, col)];
}


int Image::getWidth()
{
	return width_;
}

int Image::getHeight()
{
	return height_;
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

	of << "P6\n" << width_ << " " << height_ << "\n255\n";

	int pixels = width_ * height_;
	for (int p = 0; p < pixels; p++)
	{
		// write 8Bit color value instead of float value
		of << pixel_[p].getRed8B() << pixel_[p].getGreen8B() << pixel_[p].getBlue8B();
	}

	of.close();
}

// load PNM file
// inspired source: http://josiahmanson.com/prose/optimize_ppm/

void Image::load(const std::string& filename)
{

	std::ifstream ifs(filename.c_str(), std::ios::binary);

	// check if file exists
	if (!ifs.is_open())
	{
		std::cout << "Error: Unable to open file \"" << filename << "\"" << std::endl;
		return;
	}

	// we got file

	std::cout << "Reading file header of \"" << filename << "\"" << std::endl;

	eat_comment(ifs);

	// read and evaluate magic number
	std::string magic_number;
	ifs >> magic_number;

	ANYMAP map = PPM;
	bool ascii = false;

	if (magic_number.compare("P1") == 0)
	{
		// P1 = PBM in ASCII
		map = PBM;
		ascii = true;
	}
	else if (magic_number.compare("P2") == 0)
	{
		// P2 = PGM in ASCII
		map = PGM;
		ascii = true;
	}
	else if (magic_number.compare("P3") == 0)
	{
		// P3 = PPM in ASCII
		map = PPM;
		ascii = true;
	}
	else if (magic_number.compare("P4") == 0)
	{
		// P4 = PBM in binary
		map = PBM;
		ascii = false;
	}
	else if (magic_number.compare("P5") == 0)
	{
		// P5 = PGM in binary
		map = PGM;
		ascii = false;
	}
	else if (magic_number.compare("P6") == 0)
	{
		// P6 = PPM in binary
		map = PPM;
		ascii = false;
	}
	else
	{
		std::cout << "Error, Magic number doesn't fit in anymap format!" << std::endl;
		ifs.close();
		return;
	}

	// read width and height

	int width = 1, height = 1;

	eat_comment(ifs);
	ifs >> width;

	eat_comment(ifs);
	ifs >> height;

	// let's hope size is not smaller than 1
	if (width < 1 || height < 1)
	{
		std::cout << "Error: Unsupported size " << width << "/" << height << std::endl;
		ifs.close();
		return;
	}

	// read color depth if not PBM
	int color_depth = 1;

	if (magic_number.compare("P1") != 0 && magic_number.compare("P4") != 0)
	{
		eat_comment(ifs);
		ifs >> color_depth;

		if (color_depth < 1 || color_depth > 255)
		{
			std::cout << "Error: Unsupported color depth " << color_depth << std::endl;
			ifs.close();
			return;
		}
	}

	// stringstream is currently at a ' ' or '\n', move it by 1
	ifs.get();

	std::cout << "Loading content file \"" << filename << "\"" << std::endl;

	initialize(width, height);
	
	if (ascii)
		getColorsFromAscii(ifs, map, color_depth);
	else
		getColorsFromBinary(ifs, map, color_depth);

	ifs.close();
}


void Image::getColorsFromAscii(std::ifstream& ss, ANYMAP mode, unsigned int color_depth)
{
	if (mode == PBM)
	{
		int color = 0;
		int index = 0;
		while (!ss.eof())
		{
			ss >> color;

			pixel_[index++].setColor(color == 0 ? 0xffffff : 0x000000);
		}
	}
	else if (mode == PGM)
	{
		int color = 0;
		int index = 0;
		while (!ss.eof())
		{
			ss >> color;

			float red = static_cast<float>(color) / static_cast<float>(color_depth);
			float green = static_cast<float>(color) / static_cast<float>(color_depth);
			float blue = static_cast<float>(color) / static_cast<float>(color_depth);

			pixel_[index++].setColor(red, green, blue);
		}
	}
	else if (mode == PPM)
	{
		int r = 0, g = 0, b = 0;
		int index = 0;
		while (!ss.eof())
		{
			ss >> r >> g >> b;
			
			float red = static_cast<float>(r) / static_cast<float>(color_depth);
			float green = static_cast<float>(g) / static_cast<float>(color_depth);
			float blue = static_cast<float>(b) / static_cast<float>(color_depth);

			pixel_[index++].setColor(red, green, blue);
		}
	}
}


void Image::getColorsFromBinary(std::ifstream& ss, ANYMAP mode, unsigned int color_depth)
{
	if (mode == PBM)
	{
		int index = 0;
		int row = 0;

		while (!ss.eof())
		{
			int color = ss.get();

			int b = 0;
			while (b < 8 && index < Mathtools::pixelIndex(width_, row, width_-1))
			{
				pixel_[index++].setColor((color >> (7-b)) & 1 ? 0x000000 : 0xffffff);
				b++;
			}
			row++;
		}
	}
	else if (mode == PGM)
	{
		int index = 0;
		while (!ss.eof())
		{
			int color = ss.get();

			float red = static_cast<float>(color) / static_cast<float>(color_depth);
			float green = static_cast<float>(color) / static_cast<float>(color_depth);
			float blue = static_cast<float>(color) / static_cast<float>(color_depth);

			pixel_[index++].setColor(red, green, blue);
		}
	}
	else if (mode == PPM)
	{
		int index = 0;

		while (!ss.eof())
		{
			int color = ss.get();
			float red = static_cast<float>(color) / static_cast<float>(color_depth);

			color = ss.get();
			float green = static_cast<float>(color) / static_cast<float>(color_depth);

			color = ss.get();
			float blue = static_cast<float>(color) / static_cast<float>(color_depth);

			pixel_[index++].setColor(red, green, blue);
		}
	}
}