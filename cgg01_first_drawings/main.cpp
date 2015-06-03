#include "Image.h"
#include "RendererSimpleDrawing.h"

#include <iostream>

// Mathtools.h incluces all Vector and Transform classes
// #include "Mathtools.h"

int main(int argc, char** argv)
{
	std::cout << "Computer Graphics Guide" << std::endl;

	// create renderer, set background color and start rendering
	RendererSimpleDrawing renderer(640, 480);
	renderer.setBackgroundColor(0xffffff);
	renderer.render();

	// get an image and save it as PPM file
	Image img = renderer.createImage();
	img.save("image");

	return 0;
}
