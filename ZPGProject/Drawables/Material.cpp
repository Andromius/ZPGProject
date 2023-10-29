#include "Material.h"

Material::Material(glm::vec4 color, float specularStrength, int shininess)
{
	_color = color;
	_specularStrength = specularStrength;
	_shininess = shininess;
}

glm::vec4 Material::getColor()
{
	return _color;
}

float Material::getSpecularStrength()
{
	return _specularStrength;
}

int Material::getShininess()
{
	return _shininess;
}
