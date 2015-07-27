#include "Image.h"
#include "Renderer3DRasterization.h"
#include "Camera3D.h"

#include <iostream>

// Mathtools.h incluces all Vector and Transform classes
// #include "Mathtools.h"

int main(int argc, char** argv)
{
	std::cout << "Computer Graphics Guide" << std::endl;
	
	Camera3D camera;
	camera.setCenter(2.5, 2, -5);
	camera.setLookat(0, 0, 0);
	camera.setLookUp(0, 1, 0);

	camera.setPerspective(60.0, 1.0, 20.0);
	// camera.setOrthogonal(4.0, 3.0, 1.0, 20);
	// camera.setOrthoFov(60.0);
	camera.setScreenSize(800, 600);

	Renderer3DRasterization renderer(camera);
	renderer.setBackgroundColor(0xffffff);
	renderer.render();

	Image img = renderer.createImage();
	Image depthImg = renderer.createDepthImage();

	img.save("imagePerspective");
	depthImg.save("depthPerspective");

	return 0;
}
