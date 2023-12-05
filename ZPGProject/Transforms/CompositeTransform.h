#pragma once
#include "RotationTransform.h"
#include "ScaleTransform.h"
#include "TranslateTransform.h"
#include <vector>
#include <memory>
class CompositeTransform :
	public Transform
{
protected:
	std::vector<std::shared_ptr<Transform>> _transforms;
public:
	// Inherited via Transform
	~CompositeTransform();
	glm::mat4 transform() override;
	glm::mat4 transformUntil(int index);
	void update() override;
	CompositeTransform& addTransform(std::shared_ptr<Transform> transform);
	CompositeTransform& addRotationTransform(float angle, glm::vec3 axis);
	CompositeTransform& addScaleTransform(glm::vec3 scale);
	CompositeTransform& addTranslateTransform(glm::vec3 vector);
	CompositeTransform& addContinuousBezierTransform(float delta = 0.01f, float start = 0);

	Transform* getTransform(int index);
};

