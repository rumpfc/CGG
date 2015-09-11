#include "Image.h"
#include "Renderer3DRaycasting.h"
#include "Camera3D.h"
#include "Mathtools.h"

#include <iostream>
#include <ctime>

// Mathtools.h incluces all Vector and Transform classes
// #include "Mathtools.h"

int main(int argc, char** argv)
{
	clock_t start, end;
	start = clock();

	std::cout << "Computer Graphics Guide" << std::endl;
	
	Camera3D camera;
	camera.setCenter(10, 3, 0);
	camera.setLookat(0, 0, 3);
	camera.setLookUp(0, 1, 0);

	camera.setPerspective(60.0, 1.0, 100);
	camera.setScreenSize(800, 600);

	Renderer3DRaycasting renderer(camera);
	renderer.render();

	Image img = renderer.createImage();
	Image depthImg = renderer.createDepthImage();

	img.save("output/image");

	end = clock();

	float time = static_cast<float>(end - start) / CLOCKS_PER_SEC;

	std::cout << "This program took " << time << " seconds" << std::endl;

	return 0;
}
