#include "Texture.h"
#include "Mathtools.h"


Texture::Texture() : repeat_(false)
{
}


Texture::Texture(Image& img) : repeat_(false)
{
	image_.copy(img);
}


Texture::~Texture()
{
}

// texture coordinates to pixel coordinates
// impossible to get integer values, we have to interpolate between 4 pixels
// the real center of a pixel is half values of row and col
// r.5 and c.5

Color Texture::getColor(double u, double v)
{
	if (!repeat_ && (u < 0.0 || u > 1.0 || v < 0.0 || v > 1.0))
		return Color();

	double col = u * static_cast<double>(image_.getWidth());
	double row = (1.0-v) * static_cast<double>(image_.getHeight());

	double prio_row = Mathtools::trunc(row) + 0.5;
	double prio_col = Mathtools::trunc(col) + 0.5;

	double diff_row = row - prio_row;
	double diff_col = col - prio_col;

	// define ratio, upper and lower row of interpolation
	int row_top, row_bot;

	if (diff_row < 0.0)
	{
		row_top = static_cast<int>(Mathtools::trunc(prio_row) - 1.0);
		row_bot = static_cast<int>(Mathtools::trunc(prio_row));

		// use positiv value from top point
		diff_row += 1.0;

		if (row_top < 0)
			row_top = row_bot;
	}
	else
	{
		row_top = static_cast<int>(Mathtools::trunc(prio_row));
		row_bot = static_cast<int>(Mathtools::trunc(prio_row) + 1.0);

		if (row_bot >(image_.getHeight() - 1))
			row_bot = row_top;
	}

	// define ratio, left and right column
	int col_left, col_right;

	if (diff_col < 0.0)
	{
		col_left  = static_cast<int>(Mathtools::trunc(prio_col) - 1.0);
		col_right = static_cast<int>(Mathtools::trunc(prio_col));

		// use positiv value from left point
		diff_col += 1.0;

		if (col_left < 0)
			col_left = col_right;
	}
	else
	{
		col_left  = static_cast<int>(Mathtools::trunc(prio_col));
		col_right = static_cast<int>(Mathtools::trunc(prio_col) + 1.0);

		if (col_right >(image_.getWidth() - 1))
			col_right = col_left;
	}

	Color P_00 = image_.getPixel(row_top, col_left);
	Color P_01 = image_.getPixel(row_top, col_right);
	Color P_10 = image_.getPixel(row_bot, col_left);
	Color P_11 = image_.getPixel(row_bot, col_right);

	// Interpolate between columns of both rows
	Color R0 = P_00 * (1.0 - diff_col) + P_01 * diff_col;
	Color R1 = P_10 * (1.0 - diff_col) + P_11 * diff_col;

	// now interpolate between new rows R0 and R1
	
	Color result = R0 * (1.0 - diff_row) + R1 * diff_row;

	return result;
}


void Texture::repeatMode(bool repeat)
{
	repeat_ = repeat;
}


bool Texture::isRepeatMode()
{
	return repeat_;
}


int Texture::getImageWidth()
{
	return image_.getWidth();
}

int Texture::getImageHeight()
{
	return image_.getHeight();
}