#pragma once
#include <glm/glm.hpp>
#include "Observables/ObservableObject.h"

class Light : 
	public ObservableObject
{
public:
	glm::vec3 _position;
	glm::vec4 _color;

public:
	Light(glm::vec3 position, glm::vec4 color = glm::vec4(1,1,1,1));
};

