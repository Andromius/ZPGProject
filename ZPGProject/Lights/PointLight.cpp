#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec4 color, float attenuationLinear, float attenuationQuadratic, float diffuseStrength) : Light(color, diffuseStrength)
{
	_position = position;
	_attenuationQuadratic = attenuationQuadratic;
	_attenuationLinear = attenuationLinear;
}

glm::vec3 PointLight::getPosition()
{
	return _position;
}

void PointLight::setPosition(glm::vec3 position)
{
	_position = position;
	notify(&LightEventHandler::onLightPositionChanged, _position, static_cast<void*>(this));
}

float PointLight::getAttenuationQuadratic()
{
	return _attenuationQuadratic;
}

float PointLight::getAttenuationLinear()
{
	return _attenuationLinear;
}
