#ifndef RENDERER_H_
#define RENDERER_H_

#include "Color.h"

class Image;

/*
Abstract render class

We use this class to create our image output. A color buffer (W x H) lets us
draw everything we want. What is drawn can be described in overloaded
render() method. Width and Height is set in constructor and can't be changed
afterwards (it would destroy our image)
*/

class Renderer
{
private:
	// initialize our color buffer where we want to draw
	void initBuffer();
protected:
	// color buffer and size of buffer
	Color backgroundColor_;
	Color* buffer_;
	int width_, height_;
public:
	Renderer();
	Renderer(const int width, const int height);
	virtual ~Renderer();

	// set background color
	void setBackgroundColor(Color& color);
	void setBackgroundColor(float r, float g, float b);
	void setBackgroundColor(int colorcode);

	// render method (overload)
	virtual void render() = 0;

	// color pixel coordinate
	void colorPixel(int x, int y, Color color);

	Color* getColor(int x, int y);

	// create an Image

	Image createImage();
};

#endif