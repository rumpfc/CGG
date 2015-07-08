#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>

// Image stores pixel color and saves as PPM file
// U can open it with IrfanView
// Link: http://irfanview.tuwien.ac.at/

class Color;

class Image
{
private:
	// Image size
	int width_;
	int height_;

	// Pixelbuffer (size = width_ * height_)
	Color* pixel_;

public:
	Image(int width = 640, int height = 480);      // standard size
	Image(int width, int height, Color* buffer);   // constructor for existing colors
	Image(const Image& src);
	virtual ~Image();

	// get and set pixel
	Color& at(const int row, const int col);

	// save Image as PPM
	// automatically adds ".ppm"
	void save(const std::string& filename);
};

#endif