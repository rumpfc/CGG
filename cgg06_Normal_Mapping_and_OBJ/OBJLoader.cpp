#include "OBJLoader.h"
#include "Scene3D.h"
#include "Material.h"
#include "Surface3D.h"
#include "Polygon3D.h"

#include <iostream>
#include <sstream>
#include <string>

OBJLoader::OBJLoader(Scene3D* scene) : scene_(scene)
{
}


OBJLoader::~OBJLoader()
{
}


std::vector<std::string> OBJLoader::commandSeperator(const std::string& input, char delim)
{
	std::vector<std::string> output;
	std::string item;

	for (unsigned int i = 0; i < input.length(); i++)
	{
		char c = input.at(i);
		if (c == '#')
			return output;

		if (c == delim)
		{
			output.push_back(item);
			item.clear();
		}
		else
		{
			item.push_back(c);
		}
		
	}

	output.push_back(item);

	return output;
}


std::map<SurfaceIndex, int> OBJLoader::indexSeperator(const std::string& input, char delim)
{
	std::map<SurfaceIndex, int> output;
	std::vector<std::string> temp = commandSeperator(input, delim);
	
	if (temp.size() > 0)
		output[POINT] = stoi(temp[0]) - 1;

	if (temp.size() > 1 && !temp[1].empty())
		output[TEXTURE] = stoi(temp[1]) - 1;

	if (temp.size() > 2)
		output[NORMAL] = stoi(temp[2]) - 1;

	return output;
}


void OBJLoader::loadOBJ(const std::string& filename)
{
	std::ifstream is(filename.c_str());

	if (!is.is_open())
	{
		std::cout << "OBJLoader Error: Can't open OBJ-File " << filename << std::endl;
		return;
	}

	std::cout << "OBJLoader: Reading object file " << filename << std::endl;

	Polygon3D* object = 0;
	Material* material = 0;

	while (!is.eof())
	{
		char temp[256];
		is.getline(temp, 256);

		std::string input(temp);

		// seperate
		std::vector<std::string> command = commandSeperator(input, ' ');

		if (command.size() == 0)
			continue;

		if (command[0].compare("mtllib") == 0)
		{
			std::cout << "OBJLoader: Found MTL file " << command[1] << std::endl;
			loadMTL(command[1]);
		}
		else if (command[0].compare("o") == 0)
		{
			object = new Polygon3D();
			scene_->addNewObject(object);
		}
		else if (command[0].compare("v") == 0)
		{
			Vector3D* point = new Vector3D(std::stod(command[1]), std::stod(command[2]), std::stod(command[3]));
			pointList.push_back(point);
			object->addPoint(point);
		}
		else if (command[0].compare("vt") == 0)
		{
			Vector2D point(std::stod(command[1]), std::stod(command[2]));
			texturePointList.push_back(point);
		}
		else if (command[0].compare("vn") == 0)
		{
			Vector3D point(std::stod(command[1]), std::stod(command[2]), std::stod(command[3]));
			normalVectorList.push_back(point);
		}
		else if (command[0].compare("usemtl") == 0)
		{
			material = scene_->getMaterial(command[1]);
		}
		else if (command[0].compare("f") == 0)
		{
			Surface3D* surface = 0;

			if (command.size() == 4)
			{
				std::map<SurfaceIndex, int> facePoint[3];
				facePoint[0] = indexSeperator(command[1], '/');
				facePoint[1] = indexSeperator(command[2], '/');
				facePoint[2] = indexSeperator(command[3], '/');

				Vector3D *p[3];
				Vector2D t[3];
				Vector3D n[3];
				bool hasTexturePoint = false;
				bool hasNormalVectors = false;

				std::map<SurfaceIndex, int>::iterator it;

				for (int i = 0; i < 3; i++)
				{
					for (it = facePoint[i].begin(); it != facePoint[i].end(); it++)
					{
						if (it->first == POINT)
							p[i] = pointList[it->second];

						if (it->first == TEXTURE)
						{
							t[i].setVector(texturePointList[it->second]);
							hasTexturePoint = true;
						}

						if (it->first == NORMAL)
						{
							n[i].setVector(normalVectorList[it->second]);
							hasNormalVectors = true;
						}
					}
				}

				surface = new Surface3D(p[0], p[1], p[2], material);
				
				if (hasTexturePoint)
					surface->setTextureAnchorPoints(t[0], t[1], t[2]);

				if (hasNormalVectors)
					surface->setNormalVectors(n[0], n[1], n[2]);

				object->addSurface(surface);
			}

			if (command.size() == 5)
			{
				std::map<SurfaceIndex, int> facePoint[4];
				facePoint[0] = indexSeperator(command[1], '/');
				facePoint[1] = indexSeperator(command[2], '/');
				facePoint[2] = indexSeperator(command[3], '/');
				facePoint[3] = indexSeperator(command[4], '/');

				Vector3D *p[4];
				Vector2D t[4];
				Vector3D n[4];
				bool hasTexturePoint = false;
				bool hasNormalVectors = false;

				std::map<SurfaceIndex, int>::iterator it;

				for (int i = 0; i < 4; i++)
				{
					for (it = facePoint[i].begin(); it != facePoint[i].end(); it++)
					{
						if (it->first == POINT)
							p[i] = pointList[it->second];

						if (it->first == TEXTURE)
						{
							t[i].setVector(texturePointList[it->second]);
							hasTexturePoint = true;
						}

						if (it->first == NORMAL)
						{
							n[i].setVector(normalVectorList[it->second]);
							hasNormalVectors = true;
						}
					}
				}

				// first triangle of rectangle
				surface = new Surface3D(p[0], p[1], p[2], material);

				if (hasTexturePoint)
					surface->setTextureAnchorPoints(t[0], t[1], t[2]);

				if (hasNormalVectors)
					surface->setNormalVectors(n[0], n[1], n[2]);

				object->addSurface(surface);

				// second triangle of rectangle
				surface = new Surface3D(p[0], p[2], p[3], material);

				if (hasTexturePoint)
					surface->setTextureAnchorPoints(t[0], t[2], t[3]);

				if (hasNormalVectors)
					surface->setNormalVectors(n[0], n[2], n[3]);

				object->addSurface(surface);
			}
		}
	}

	is.close();
}


void OBJLoader::loadMTL(const std::string& filename)
{
	std::ifstream is(filename.c_str());

	if (!is.is_open())
	{
		std::cout << "OBJLoader Error: Can't open MTL-File " << filename << std::endl;
		return;
	}

	std::cout << "OBJLoader: Reading material file " << filename << std::endl;

	Material* material = 0;

	while (!is.eof())
	{
		char temp[256];
		is.getline(temp, 256);

		std::string input(temp);

		// seperate
		std::vector<std::string> command = commandSeperator(input);

		if (command.size() == 0)
			continue;

		if (command[0].compare("newmtl") == 0)
		{
			material = new Material();
			scene_->addNewMaterial(command[1], material);
		}
		else if (command[0].compare("Ns") == 0)
		{
			if (material)
			{
				material->setShining(std::stof(command[1]));
			}
		}
		else if (command[0].compare("Ka") == 0)
		{
			if (material)
			{
				Color color(std::stof(command[1]), std::stof(command[2]), std::stof(command[3]));
				material->setAmbientColor(color);
			}
		}
		else if (command[0].compare("Kd") == 0)
		{
			if (material)
			{
				Color color(std::stof(command[1]), std::stof(command[2]), std::stof(command[3]));
				material->setDiffuseColor(color);
			}
		}
		else if (command[0].compare("Ks") == 0)
		{
			if (material)
			{
				Color color(std::stof(command[1]), std::stof(command[2]), std::stof(command[3]));
				material->setSpecularColor(color);
			}
		}
	}

	is.close();
}