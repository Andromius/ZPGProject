#include "CompositeTransform.h"
#include "ContinuousBezierTransform.h"

CompositeTransform::~CompositeTransform()
{
	_transforms.clear();
}

glm::mat4 CompositeTransform::transform()
{
	matrix = glm::mat4(1.f);
	for (auto& transform : _transforms)
	{
		matrix *= transform->transform();
	}
	return matrix;
}

glm::mat4 CompositeTransform::transformUntil(int index)
{
	matrix = glm::mat4(1.f);
	for (size_t i = 0; i < index; i++)
	{
		if (i >= _transforms.size())
		{
			return matrix;
		}
		matrix *= _transforms[i]->transform();
	}
	return matrix;
}

void CompositeTransform::update()
{
	for (auto& transform : _transforms)
	{
		transform->update();
	}
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

CompositeTransform& CompositeTransform::addContinuousBezierTransform(float delta, float start)
{
	_transforms.push_back(std::make_shared<ContinuousBezierTransform>(delta, start));
	return *this;
}

Transform* CompositeTransform::getTransform(int index)
{
	return index < _transforms.size() ? _transforms[index].get() : nullptr;
}
