#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "Image.h"

// A texture can be linked with 1 or more surfaces

class Texture
{
private:
	Image image_;
	bool repeat_;

public:
	Texture();
	Texture(Image& img);
	virtual ~Texture();

	Color getColor(double u, double v);
	void repeatMode(bool repeat);

	int getImageWidth();
	int getImageHeight();

	bool isRepeatMode();
};

#endif