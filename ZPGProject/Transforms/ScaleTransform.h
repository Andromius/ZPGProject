#pragma once
#include "Transform.h"
class ScaleTransform : 
	public Transform
{
private:
	glm::vec3 _scale;
public:
	ScaleTransform(glm::vec3 scale);

	// Inherited via Transform
	glm::mat4 transform() override;

};

