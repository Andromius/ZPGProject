#include "CompositeTransform.h"

CompositeTransform::~CompositeTransform()
{
	_transforms.clear();
}

glm::mat4 CompositeTransform::transform()
{
	for (auto& transform : _transforms)
	{
		matrix *= transform->transform();
	}
	_transforms.clear();
	return matrix;
}

CompositeTransform& CompositeTransform::addTransform(std::shared_ptr<Transform> transform)
{
	_transforms.push_back(transform);
	return *this;
}

CompositeTransform& CompositeTransform::addRotationTransform(float angle, glm::vec3 axis)
{
	_transforms.push_back(std::make_shared<RotationTransform>(angle, axis));
	return *this;
}

CompositeTransform& CompositeTransform::addScaleTransform(glm::vec3 scale)
{
	_transforms.push_back(std::make_shared<ScaleTransform>(scale));
	return *this;
}

CompositeTransform& CompositeTransform::addTranslateTransform(glm::vec3 vector)
{
	_transforms.push_back(std::make_shared<TranslateTransform>(vector));
	return *this;
}
