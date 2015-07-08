#include "Image.h"
#include "Renderer2D.h"
#include "Camera2D.h"

#include <iostream>

// Mathtools.h incluces all Vector and Transform classes
// #include "Mathtools.h"

int main(int argc, char** argv)
{
	std::cout << "Computer Graphics Guide" << std::endl;

	/* 
		create Camera with screen and viewport settings
		create renderer, set background color and start rendering
		width  = 800
		height = 600
	*/
	Camera2D camera;
	camera.setViewport(16, 12);
	camera.setScreenSize(800, 600);
	camera.setCenter(1.0, -3.0);
	camera.setRotation(15.0);

	Renderer2D renderer(camera);
	renderer.setBackgroundColor(0xffffff);
	renderer.render();

	// get an image and save it as PPM file
	Image img = renderer.createImage();
	img.save("image");

	return 0;
}
