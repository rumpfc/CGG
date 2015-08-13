#include "Image.h"
#include "Renderer3DRaycasting.h"
#include "Camera3D.h"

#include <iostream>

// Mathtools.h incluces all Vector and Transform classes
// #include "Mathtools.h"

int main(int argc, char** argv)
{
	std::cout << "Computer Graphics Guide" << std::endl;
	
	Camera3D camera;
	camera.setCenter(2, 3, -5);
	camera.setLookat(0, 0, 0);
	camera.setLookUp(0, 1, 0);

	camera.setPerspective(60.0, 1.0, 100);
	camera.setScreenSize(800, 600);

	Renderer3DRaycasting renderer(camera);
	renderer.render();

	Image img = renderer.createImage();
	Image depthImg = renderer.createDepthImage();

	img.save("output/image");
	depthImg.save("output/imageDepth");

	return 0;
}
