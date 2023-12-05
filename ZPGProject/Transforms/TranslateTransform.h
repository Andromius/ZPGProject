#pragma once
#include "Transform.h"
class TranslateTransform : 
	public Transform
{
protected:
	glm::vec3 _translateVector;

public:
	TranslateTransform(glm::vec3 vector);

	// Inherited via Transform
	glm::mat4 transform() override;
};

