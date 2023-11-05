#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
private:
	glm::vec3 _direction;

public:
	DirectionalLight(glm::vec3 direction, glm::vec4 color = glm::vec4(1, 1, 1, 1), float diffuseStrength = 0.2);
	glm::vec3 getDirection();
	void setDirection(glm::vec3 direction);
};