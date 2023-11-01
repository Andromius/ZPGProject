#pragma once
#include <glm/glm.hpp>
#include "Observables/ObservableObject.h"
#include "Events/LightEventHandler.h"
#include "Events/WindowEventHandler.h"

class Light :
	public ObservableObject<LightEventHandler>
{
private:
	glm::vec3 _position;
	glm::vec4 _color;
	float _attenuation;

public:
	Light(glm::vec3 position, glm::vec4 color = glm::vec4(1,1,1,1), float attenuation = 0.05);
	~Light();

	void setPosition(glm::vec3 position);
	void setColor(glm::vec4 color);
	glm::vec3 getPosition();
	glm::vec4 getColor();
	float getAttenuation();
};

