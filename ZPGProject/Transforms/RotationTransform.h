#pragma once
#include "Transform.h"

class RotationTransform : public Transform
{
private:
	float _angle;
	glm::vec3 _axis;
public:
	RotationTransform(float angle, glm::vec3 axis);
	// Inherited via Transform
	glm::mat4 transform() override;
};

