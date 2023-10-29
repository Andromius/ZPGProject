#include "GeneralAxisRotationTransform.h"
#include "ContinuousRotationTransform.h"
#include <iostream>

GeneralAxisRotationTransform::GeneralAxisRotationTransform(std::shared_ptr<DrawableObject> parent, glm::mat4 childMatrix, glm::vec3 axis, float angle, float speed)
{
	_childMatrix = childMatrix;
	_parent = parent;
	_axis = axis;
	_angle = angle;
	_speed = speed;
	_parentChildDistance = glm::vec3(_parent->getModelMatrix()[3]) - glm::vec3(_childMatrix[3]);
}

glm::mat4 GeneralAxisRotationTransform::transform()
{
	_transforms.clear();

	glm::mat4 parentMatrix = _parent->getModelMatrix();
	glm::vec3 translateToParent = glm::vec3(parentMatrix[3]) - glm::vec3(_childMatrix[3]);

	addTranslateTransform(translateToParent);
	addRotationTransform(_angle, _axis);
	addTranslateTransform(-_parentChildDistance);
	
	glm::mat4 inverse = glm::mat4(glm::inverse(glm::mat3(_childMatrix)));
	
	matrix = glm::mat4(1.f);
	matrix *= inverse;
	for (auto& transform : _transforms)
	{
		matrix *= transform->transform();
	}
	matrix *= glm::mat4(glm::mat3(_childMatrix));
	return matrix;
}

void GeneralAxisRotationTransform::update()
{
	_angle += _speed;
}
