#pragma once
#include <glm/glm.hpp>
#include "Observables/ObservableObject.h"
#include "Events/LightEventHandler.h"

class Light :
	public ObservableObject<LightEventHandler>
{
protected:
	glm::vec4 _color;
	float _diffuseStrength;

public:
	Light(glm::vec4 color = glm::vec4(1, 1, 1, 1), float diffuseStrength = 0.2);
	virtual ~Light() = 0;

	void setColor(glm::vec4 color);
	glm::vec4 getColor();
	float getDiffuseStrength();
};

