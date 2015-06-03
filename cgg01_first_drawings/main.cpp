#include "Image.h"
#include "RendererSimpleDrawing.h"

#include <iostream>

// Mathtools.h incluces all Vector and Transform classes
// #include "Mathtools.h"

int main(int argc, char** argv)
{
	std::cout << "Computer Graphics Guide" << std::endl;

	RendererSimpleDrawing renderer(640, 480);
	renderer.setBackgroundColor(0xffffff);
	renderer.render();

	Image* img = renderer.createImage();
	img->save("image");
	delete img;

	return 0;
}
