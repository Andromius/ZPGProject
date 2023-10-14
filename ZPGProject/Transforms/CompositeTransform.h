#pragma once
#include "Transform.h"
#include "RotationTransform.h"
#include "ScaleTransform.h"
#include "TranslateTransform.h"
#include <vector>
class CompositeTransform :
	public Transform
{
private:
	std::vector<Transform*> _transforms;
public:
	// Inherited via Transform
	~CompositeTransform();
	glm::mat4 transform() override;
	CompositeTransform* addTransform(Transform* transform);
	CompositeTransform* addRotationTransform(float angle, glm::vec3 axis);
	CompositeTransform* addScaleTransform(glm::vec3 scale);
	CompositeTransform* addTranslateTransform(glm::vec3 vector);
};

