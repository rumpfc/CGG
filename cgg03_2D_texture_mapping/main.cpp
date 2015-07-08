#include "Image.h"
#include "Renderer2D.h"
#include "Camera2D.h"

#include <iostream>

// Mathtools.h incluces all Vector and Transform classes
// #include "Mathtools.h"

int main(int argc, char** argv)
{
	std::cout << "Computer Graphics Guide" << std::endl;
	
	Camera2D camera;
	camera.setCenter(0, 0);
	camera.setScreenSize(800, 600);
	camera.setViewport(16.0, 12.0);

	Renderer2D renderer(camera);
	renderer.setBackgroundColor(0xffffff);
	renderer.render();

	Image img = renderer.createImage();
	img.save("image");

	return 0;
}
