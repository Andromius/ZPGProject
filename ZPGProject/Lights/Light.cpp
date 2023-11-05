#include "Light.h"

Light::Light(glm::vec4 color, float diffuseStrength)
{
	_color = color;
	_diffuseStrength = diffuseStrength;
}

Light::~Light()
{

}

void Light::setColor(glm::vec4 color)
{
	_color = color;
	notify(&LightEventHandler::onLightColorChanged, _color, static_cast<void*>(this));
}

glm::vec4 Light::getColor()
{
	return _color;
}

float Light::getDiffuseStrength()
{
	return _diffuseStrength;
}

