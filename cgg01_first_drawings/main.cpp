#include "Image.h"
#include "RendererSimpleDrawing.h"

#include <iostream>

// Mathtools.h incluces all Vector and Transform classes
// #include "Mathtools.h"

int main(int argc, char** argv)
{
	std::cout << "Computer Graphics Guide" << std::endl;

	/* create renderer, set background color and start rendering
	   width  = 640
	   height = 480
	   try to change image size, as long as it's positive
	   doesn't actually matter, we use abs(x) to make it positive ;)
	*/
	RendererSimpleDrawing renderer(640, 480);
	renderer.setBackgroundColor(0xffffff);
	renderer.render();

	// get an image and save it as PPM file
	Image img = renderer.createImage();
	img.save("image");

	return 0;
}
