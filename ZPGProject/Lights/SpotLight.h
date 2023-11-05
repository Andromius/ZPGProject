#pragma once
#include "PointLight.h"
class SpotLight :
	public PointLight
{
private:
	glm::vec3 _direction;
	float _angle;
	float _angleFadeStart;
public:
	SpotLight(float angle, float angleFadeStart, glm::vec3 position, glm::vec3 direction,
		glm::vec4 color = glm::vec4(1, 1, 1, 1), float attenuation = 0.05, float diffuseStrength = 0.2);

	glm::vec3 getDirection();
	void setDirection(glm::vec3 direction);
	float getAngle();
	float getAngleFadeStart();
};