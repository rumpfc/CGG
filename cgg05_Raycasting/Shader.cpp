#include "Shader.h"
#include "Surface3D.h"
#include "Light.h"
#include "Mathtools.h"
#include "Object3D.h"

Color Shader::phong(Vector3D& point, Surface3D* triangle, std::vector<Light*> lights)
{
	if (lights.size() == 0 || !triangle)
		return Color();

	Color finalColor;

	Material* material = triangle->getMaterial();

	Vector3D normal;

	if (triangle->getObject())
		normal = triangle->getObject()->getNormal(point);
	else
		normal = triangle->getNormal();

	for (Light* light : lights)
	{
		finalColor += triangle->getColor(point) * material->getAmbientColor() * light->getAmbientColor();

		Vector3D lightDir = light->getPosition() - point;
		double distance = lightDir.length(); // for attenuation
		lightDir.normalize();

		double coeff = Mathtools::dot(normal, lightDir);

		double attenuation = 1.0 / (light->getConstantAttenuation() + light->getLinearAttenuation() * distance + light->getQuadraticAttenuation() * distance * distance);

		finalColor += triangle->getColor(point) * material->getDiffuseColor() * light->getDiffuseColor() * Mathtools::max(coeff,0.0) * attenuation;

		if (coeff > 0.0)
		{
			Vector3D viewDir = -point;
			viewDir.normalize();
			lightDir = -lightDir;
			Vector3D reflectedLightDir = Mathtools::reflect(lightDir, normal);
			reflectedLightDir.normalize();

			coeff = Mathtools::dot(reflectedLightDir, viewDir);

			finalColor += material->getSpecularColor() * light->getSpecularColor() * pow(Mathtools::max(coeff, 0.0), material->getShining()) * attenuation;
		}
		
	}

	return finalColor;
}