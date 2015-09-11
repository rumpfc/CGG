#ifndef IMAGE_H_
#define IMAGE_H_

#include <string>
#include <sstream>

#include "Color.h"

// Image stores pixel color and saves as PPM file
// Can also load anything which belongs to categorie "Portable Anymap" (PBM, PGM, PPM)
// You can open it with IrfanView on Windows and Mac OS (standard in Linux)
// Link: http://irfanview.tuwien.ac.at/

class Image
{
private:
	// Image size
	int width_;
	int height_;

	// Pixelbuffer (size = width_ * height_)
	Color* pixel_;

	// init pixel buffer
	void initialize(int width, int height);

	// for loading anymaps, we need to know which version we have
	enum ANYMAP { PBM, PGM, PPM };

	// removes comments of PNM files starting with '#'
	// source: http://josiahmanson.com/prose/optimize_ppm/
	void eat_comment(std::ifstream& f);

	// load informations from stringstream
	void getColorsFromAscii(std::ifstream& ss, ANYMAP mode, unsigned int color_depth = 255);
	void getColorsFromBinary(std::ifstream& ss, ANYMAP mode, unsigned int color_depth = 255);

public:
	Image(int width = 640, int height = 480);      // standard size
	Image(int width, int height, Color* buffer);   // constructor for existing colors
	Image(const Image& src);
	virtual ~Image();

	// copy content of other Image object
	void copy(Image& src);

	// get and set pixel
	Color getPixel(const int row, const int col);
	int getWidth();
	int getHeight();

	// save Image as PPM
	// automatically adds ".ppm"
	void save(const std::string& filename);

	// load existing anymap (PBM, PGM or PPM)
	// Possible in both ASCII and Bit code
	// inspired source: http://josiahmanson.com/prose/optimize_ppm/
	void load(const std::string& filename);
};

#endif