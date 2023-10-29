#pragma once
#include "RotationTransform.h"
class ContinuousRotationTransform : public RotationTransform
{
private:
	float _speed;
public:
	ContinuousRotationTransform(float angle, glm::vec3 axis, float speed);
	glm::mat4 transform() override;
};