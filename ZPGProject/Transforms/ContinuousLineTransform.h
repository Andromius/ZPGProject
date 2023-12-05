#pragma once
#include "TranslateTransform.h"
class ContinuousLineTransform : public Transform
{
private:
	glm::vec3 _point;
	glm::vec3 _direction;

protected:
	float _delta;
	float _start;
	bool _goBack = false;
	ContinuousLineTransform(float delta, float start);

public:
	ContinuousLineTransform(glm::vec3 point, glm::vec3 direction, float delta = 0.01f, float start = 0);
	glm::mat4 transform() override;
	void update() override;
};