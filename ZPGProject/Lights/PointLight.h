#pragma once
#include "Light.h"

class PointLight : public Light
{
protected:
	glm::vec3 _position;
	float _attenuation;
public:
	PointLight(glm::vec3 position, glm::vec4 color = glm::vec4(0, 0, 0.05f, 1), float attenuation = 0.05, float diffuseStrength = 0.2);
	
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	float getAttenuation();
};