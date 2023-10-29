#pragma once
#include <glm/mat4x4.hpp>
class Transform
{
protected:
	glm::mat4 matrix = glm::mat4(1.f);

public:
	virtual ~Transform() = default;
	virtual glm::mat4 transform() = 0;
	virtual void update();
};