#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec4 color, float diffuseStrength) : Light(color, diffuseStrength)
{
	_direction = direction;
}

glm::vec3 DirectionalLight::getDirection()
{
	return _direction;
}

void DirectionalLight::setDirection(glm::vec3 direction)
{
	_direction = direction;
	notify(&LightEventHandler::onLightDirectionChanged, _direction, static_cast<void*>(this));
}
