#include "SpotLight.h"

SpotLight::SpotLight(float angle, float angleFadeStart,
	glm::vec3 position, glm::vec3 direction, glm::vec4 color,
	float attenuationLinear, float attenuationQuadratic, float diffuseStrength)
	: PointLight(position, color, attenuationLinear, attenuationQuadratic, diffuseStrength)
{
	_direction = direction;
	_angle = angle;
	_angleFadeStart = angleFadeStart;
}

glm::vec3 SpotLight::getDirection()
{
	return _direction;
}

void SpotLight::setDirection(glm::vec3 direction)
{
	_direction = direction;
	notify(&LightEventHandler::onLightDirectionChanged, _direction, static_cast<void*>(this));
}

float SpotLight::getAngle()
{
	return _angle;
}

float SpotLight::getAngleFadeStart()
{
	return _angleFadeStart;
}
