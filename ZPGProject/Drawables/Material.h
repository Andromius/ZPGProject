#pragma once
#include <glm/glm.hpp>
class Material
{
private:
	glm::vec4 _color;
	float _specularStrength;
	int _shininess;

public:
	Material(glm::vec4 color = glm::vec4(0.385, 0.647, 0.812, 1), float specularStrength = 1, int shininess = 1);
	glm::vec4& getColor();
	float getSpecularStrength();
	int getShininess();
};