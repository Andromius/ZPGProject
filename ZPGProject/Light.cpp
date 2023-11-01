#include "Light.h"

Light::Light(glm::vec3 position, glm::vec4 color, float attenuation)
{
	_position = position;
	_color = color;
	_attenuation = attenuation;
}

Light::~Light()
{

}

void Light::setPosition(glm::vec3 position)
{
	_position = position;
	notify(&LightEventHandler::onLightChanged);
}

void Light::setColor(glm::vec4 color)
{
	_color = color;
	notify(&LightEventHandler::onLightChanged);
}

glm::vec3 Light::getPosition()
{
	return _position;
}

glm::vec4 Light::getColor()
{
	return _color;
}

float Light::getAttenuation()
{
	return _attenuation;
}

