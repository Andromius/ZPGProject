#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, glm::vec4 color, float attenuation, float diffuseStrength) : Light(color, diffuseStrength)
{
	_position = position;
	_attenuation = attenuation;
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

float PointLight::getAttenuation()
{
	return _attenuation;
}
