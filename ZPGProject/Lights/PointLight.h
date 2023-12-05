#pragma once
#include "Light.h"

class PointLight : public Light
{
protected:
	glm::vec3 _position;
	float _attenuationLinear;
	float _attenuationQuadratic;
public:
	PointLight(glm::vec3 position, glm::vec4 color = glm::vec4(0, 0, 0.05f, 1), float attenuationLinear = 0, float attenuationQuadratic = 0.05, float diffuseStrength = 0.2);
	
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	float getAttenuationQuadratic();
	float getAttenuationLinear();
};